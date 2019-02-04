--------------------------------------------------------------------------------
--
--   	FileName:         new_component.vhd
--		Entities: new_component
--		Authors: Maxime Houle
-- 	Date: February 2nd, 2019
--		Project: Positional Tracking with an IMU
--		Description: I2C interface acting as an slave to the processing unit,
--						implements a state machine to handle I2C protocol.
--
--		Derived from 
--		https://www.digikey.com/eewiki/download/attachments/10125324/i2c_master.vhd
-- 	Accessed on February 2nd, 2019, Originally created by Scott Larson
-- 
--------------------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity new_component is
	port (
		clk       : in    std_logic                     := '0';             --      clock.clk
		rst_n     : in    std_logic                     := '0';             -- reset_sink.reset_n
		addr      : in    std_logic_vector(6 downto 0)  := (others => '0'); --        csr.address
		read      : in    std_logic                     := '0';             --           .read
		write     : in    std_logic                     := '0';             --           .write
		readdata  : out   std_logic_vector(31 downto 0);                    --           .readdata
		writedata : in    std_logic_vector(31 downto 0) := (others => '0'); --           .writedata
		sda       : inout std_logic                     := '0';             -- i2c_serial.sda
		scl       : inout std_logic                     := '0'              --           .scl
	);
end entity new_component;

architecture rtl of new_component is
  CONSTANT input_clk : INTEGER := 50_000_000; --input clock speed from user logic in Hz
  CONSTANT bus_clk   : INTEGER := 400_000;
  CONSTANT divider  :  INTEGER := (input_clk/bus_clk)/4; --number of clocks in 1/4 cycle of scl
  
  TYPE machine IS(ready, start, command, slv_ack1, wr, rd, slv_ack2, mstr_ack, stop); --needed states
  SIGNAL state         : machine;                        --state machine
  SIGNAL data_clk      : STD_LOGIC;                      --data clock for sda
  SIGNAL data_clk_prev : STD_LOGIC;                      --data clock during previous system clock
  SIGNAL scl_clk       : STD_LOGIC;                      --constantly running internal scl
  SIGNAL scl_ena       : STD_LOGIC := '0';               --enables internal scl to output
  SIGNAL sda_int       : STD_LOGIC := '1';               --internal sda
  SIGNAL sda_ena_n     : STD_LOGIC;                      --enables internal sda to output
  SIGNAL addr_rw       : STD_LOGIC_VECTOR(7 DOWNTO 0);   --latched in address and read/write
  SIGNAL data_tx       : STD_LOGIC_VECTOR(7 DOWNTO 0);   --latched in data to write to slave
  SIGNAL data_rx       : STD_LOGIC_VECTOR(7 DOWNTO 0);   --data received from slave
  SIGNAL bit_cnt       : INTEGER RANGE 0 TO 7 := 7;      --tracks bit number in transaction
  SIGNAL stretch       : STD_LOGIC := '0';               --identifies if slave is stretching scl
  SIGNAL busy			  : STD_LOGIC := '0';
  SIGNAL ack_error     : STD_LOGIC := '0';
begin


	--generate the timing for the bus clock (scl_clk) and the data clock (data_clk)
  PROCESS(clk, rst_n)
    VARIABLE count  :  INTEGER RANGE 0 TO divider*4;  --timing for clock generation
  BEGIN
    IF(rst_n = '0') THEN                --reset asserted
      stretch <= '0';
      count := 0;
    ELSIF(clk'EVENT AND clk = '1') THEN
      data_clk_prev <= data_clk;          --store previous value of data clock
      IF(count = divider*4-1) THEN        --end of timing cycle
        count := 0;                       --reset timer
      ELSIF(stretch = '0') THEN           --clock stretching from slave not detected
        count := count + 1;               --continue clock generation timing
      END IF;
      CASE count IS
        WHEN 0 TO divider-1 =>            --first 1/4 cycle of clocking
          scl_clk <= '0';
          data_clk <= '0';
        WHEN divider TO divider*2-1 =>    --second 1/4 cycle of clocking
          scl_clk <= '0';
          data_clk <= '1';
        WHEN divider*2 TO divider*3-1 =>  --third 1/4 cycle of clocking
          scl_clk <= '1';                 --release scl
          IF(scl = '0') THEN              --detect if slave is stretching clock
            stretch <= '1';
          ELSE
            stretch <= '0';
          END IF;
          data_clk <= '1';
        WHEN OTHERS =>                    --last 1/4 cycle of clocking
          scl_clk <= '1';
          data_clk <= '0';
      END CASE;
    END IF;
  END PROCESS;

  --state machine and writing to sda during scl low (data_clk rising edge)
  PROCESS(clk, rst_n)
  BEGIN
    IF(rst_n = '0') THEN                 --reset asserted
      state <= ready;                      --return to initial state
      scl_ena <= '0';                      --sets scl high impedance
      sda_int <= '1';                      --sets sda high impedance
      ack_error <= '0';                    --clear acknowledge error flag
      bit_cnt <= 7;                        --restarts data bit counter
      readdata <= "00000000000000000000000000000000";               --clear data read port
    ELSIF(clk'EVENT AND clk = '1') THEN
      IF(data_clk = '1' AND data_clk_prev = '0') THEN  --data clock rising edge
        CASE state IS
		  -- READY STATE
          WHEN ready =>                      --idle state
            IF(read = '1') THEN              --transaction requested
              addr_rw <= addr & '1';         --collect requested slave address and command
              data_tx <= writedata(7 downto 0);            --collect requested data to write
              state <= start;				  		--go to start bit
				ELSIF(write = '1') THEN
				  addr_rw <= addr & '0';
				  data_tx <= writedata(7 downto 0);
				  state <= start;
            ELSE                             --remain idle
              busy <= '0';                   --unflag busy
              state <= ready;                --remain idle
            END IF;
				
          WHEN start =>                      --start bit of transaction
            busy <= '1';                     --resume busy if continuous mode
            sda_int <= addr_rw(bit_cnt);     --set first address bit to bus
            state <= command;                --go to command
				
          WHEN command =>                    --address and command byte of transaction
            IF(bit_cnt = 0) THEN             --command transmit finished
              sda_int <= '1';                --release sda for slave acknowledge
              bit_cnt <= 7;                  --reset bit counter for "byte" states
              state <= slv_ack1;             --go to slave acknowledge (command)
            ELSE                             --next clock cycle of command state
              bit_cnt <= bit_cnt - 1;        --keep track of transaction bits
              sda_int <= addr_rw(bit_cnt-1); --write address/command bit to bus
              state <= command;              --continue with command
            END IF;
				
          WHEN slv_ack1 =>                   --slave acknowledge bit (command)
            IF(addr_rw(0) = '0') THEN        --write command
              sda_int <= data_tx(bit_cnt);   --write first bit of data
              state <= wr;                   --go to write byte
            ELSE                             --read command
              sda_int <= '1';                --release sda from incoming data
              state <= rd;                   --go to read byte
            END IF;
				
          WHEN wr =>                         --write byte of transaction
            busy <= '1';                     --resume busy if continuous mode
            IF(bit_cnt = 0) THEN             --write byte transmit finished
              sda_int <= '1';                --release sda for slave acknowledge
              bit_cnt <= 7;                  --reset bit counter for "byte" states
              state <= slv_ack2;             --go to slave acknowledge (write)
            ELSE                             --next clock cycle of write state
              bit_cnt <= bit_cnt - 1;        --keep track of transaction bits
              sda_int <= data_tx(bit_cnt-1); --write next bit to bus
              state <= wr;                   --continue writing
            END IF;
				
          WHEN rd =>                         --read byte of transaction
            busy <= '1';                     --resume busy if continuous mode
            IF(bit_cnt = 0) THEN             --read byte receive finished
              IF(read = '1' AND addr_rw = addr & '1') THEN  --continuing with another read at same address
                sda_int <= '0';              --acknowledge the byte has been received
              ELSE                           --stopping or continuing with a write
                sda_int <= '1';              --send a no-acknowledge (before stop or repeated start)
              END IF;
              bit_cnt <= 7;                  --reset bit counter for "byte" states
              readdata(7 downto 0) <= data_rx;            --output received data
              state <= mstr_ack;             --go to master acknowledge
            ELSE                             --next clock cycle of read state
              bit_cnt <= bit_cnt - 1;        --keep track of transaction bits
              state <= rd;                   --continue reading
            END IF;
				
          WHEN slv_ack2 =>                   --slave acknowledge bit (write)
            IF(write = '1') THEN               --continue transaction
              busy <= '0';                   --continue is accepted
              addr_rw <= addr & '0';          --collect requested slave address and command
              data_tx <= writedata(7 downto 0);            --collect requested data to write
              IF(addr_rw = addr & '0') THEN   --continue transaction with another write
                sda_int <= writedata(bit_cnt); --write first bit of data
                state <= wr;                 --go to write byte
              ELSE                           --continue transaction with a read or new slave
                state <= start;              --go to repeated start
              END IF;
            ELSE                             --complete transaction
              state <= stop;                 --go to stop bit
            END IF;
				
          WHEN mstr_ack =>                   --master acknowledge bit after a read
            IF(read = '1') THEN              --continue transaction
              busy <= '0';                   --continue is accepted and data received is available on bus
              addr_rw <= addr & '1';         --collect requested slave address and command
              data_tx <= writedata(7 downto 0);            --collect requested data to write
              IF(addr_rw = addr & '1') THEN  --continue transaction with another read
                sda_int <= '1';              --release sda from incoming data
                state <= rd;                 --go to read byte
              ELSE                           --continue transaction with a write or new slave
                state <= start;              --repeated start
              END IF;    
            ELSE                             --complete transaction
              state <= stop;                 --go to stop bit
            END IF;
				
          WHEN stop =>                       --stop bit of transaction
            busy <= '0';                     --unflag busy
            state <= ready;                  --go to idle state
        END CASE;    
		  
      ELSIF(data_clk = '0' AND data_clk_prev = '1') THEN  --data clock falling edge
        CASE state IS
          WHEN start =>                  
            IF(scl_ena = '0') THEN                  --starting new transaction
              scl_ena <= '1';                       --enable scl output
              ack_error <= '0';                     --reset acknowledge error output
            END IF;
          WHEN slv_ack1 =>                          --receiving slave acknowledge (command)
            IF(sda /= '0' OR ack_error = '1') THEN  --no-acknowledge or previous no-acknowledge
              ack_error <= '1';                     --set error output if no-acknowledge
            END IF;
          WHEN rd =>                                --receiving slave data
            data_rx(bit_cnt) <= sda;                --receive current slave data bit
          WHEN slv_ack2 =>                          --receiving slave acknowledge (write)
            IF(sda /= '0' OR ack_error = '1') THEN  --no-acknowledge or previous no-acknowledge
              ack_error <= '1';                     --set error output if no-acknowledge
            END IF;
          WHEN stop =>
            scl_ena <= '0';                         --disable scl
          WHEN OTHERS =>
            NULL;
        END CASE;
      END IF;
    END IF;
  END PROCESS;  

  --set sda output
  WITH state SELECT
    sda_ena_n <= data_clk_prev WHEN start,     --generate start condition
                 NOT data_clk_prev WHEN stop,  --generate stop condition
                 sda_int WHEN OTHERS;          --set to internal sda signal    
      
  --set scl and sda outputs
  scl <= '0' WHEN (scl_ena = '1' AND scl_clk = '0') ELSE 'Z';
  sda <= '0' WHEN sda_ena_n = '0' ELSE 'Z';

end architecture rtl; -- of new_component
