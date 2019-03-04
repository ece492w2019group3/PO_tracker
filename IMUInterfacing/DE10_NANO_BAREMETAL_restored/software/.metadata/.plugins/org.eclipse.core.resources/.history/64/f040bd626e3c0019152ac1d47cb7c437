#include <os.h>
#include <stdbool.h>
#include "socal/hps.h"
#include "socal/socal.h"
#include "lib_def.h"
#include "os_cpu.h"
#include <string.h>
#include "../HWLIBS/alt_i2c.h"
#include "../models/models.h"
#include "../UART/uart.h"
#include "i2c_driver.h"
#include "bsp.h"
#include "bsp_int.h"

static ALT_I2C_DEV_t * i2c2_device;
#define HALF_FULL 32
#define RX_BUFFER_SIZE 256
#define TX_BUFFER_SIZE 256
static uint8_t I2C2_Internal_RX_Buffer[RX_BUFFER_SIZE] = { 0 };
static uint8_t I2C2_Internal_TX_Buffer[TX_BUFFER_SIZE] = { 0 };
static uint8_t TX_Size = 0;
static uint32_t rx_write_pos = 0;
static uint32_t rx_read_pos = 0;

OS_EVENT * read_semaphore;
OS_EVENT * write_semaphore;
OS_EVENT * write_complete_semaphore;

void init_I2C2(ALT_I2C_DEV_t * device)
{
	ALT_STATUS_CODE err;
    read_semaphore = OSSemCreate(0);
    write_semaphore = OSSemCreate(0);
    write_complete_semaphore = OSSemCreate(0);
    
    i2c2_device = device;
    err = alt_i2c_init(ALT_I2C_I2C1, i2c2_device);
    if(err != ALT_E_SUCCESS) UART_print("Error initializing i2c2\r\n");
    err =  alt_i2c_disable(i2c2_device);
    if(err != ALT_E_SUCCESS) UART_print("Error disabling i2c2\r\n");
    
    ALT_I2C_SLAVE_CONFIG_t slave_config = { .addr_mode = ALT_I2C_ADDR_MODE_7_BIT,
                                            .addr = 17,
                                            .nack_enable = false};
    
    err = alt_i2c_slave_config_set(i2c2_device, &slave_config);
        if(err != ALT_E_SUCCESS) UART_print("Error configuring slave device\r\n");

    err = alt_i2c_op_mode_set(i2c2_device, ALT_I2C_MODE_SLAVE);
    if(err != ALT_E_SUCCESS) UART_print("Error setting i2c2 mode\r\n");
    err = alt_i2c_sda_hold_time_set(i2c2_device, 30);
    if(err != ALT_E_SUCCESS) UART_print("Error setting i2c2 SDA Hold Time\r\n");
    err = alt_i2c_sda_setup_time_set(i2c2_device, 11);
    if(err != ALT_E_SUCCESS) UART_print("Error setting i2c2 SDA setup Time\r\n");
    err = alt_i2c_int_disable(i2c2_device, ALT_I2C_STATUS_INT_ALL);
    if(err != ALT_E_SUCCESS) UART_print("Error clearing interrupts\r\n");
    err = alt_i2c_int_enable(i2c2_device,
                        ALT_I2C_STATUS_STOP_DET | 
                        ALT_I2C_STATUS_RX_DONE | 
                        ALT_I2C_STATUS_RX_FULL |
                        ALT_I2C_STATUS_RD_REQ |
						ALT_I2C_STATUS_START_DET |
						ALT_I2C_STATUS_TX_ABORT);
    if(err != ALT_E_SUCCESS) UART_print("Error enabling interrupts\n");
    init_I2C2_interrupt();

    err = alt_i2c_rx_fifo_threshold_set(i2c2_device, HALF_FULL);
    if(err != ALT_E_SUCCESS) UART_print("Error setting fifo\r\n");
    err =alt_i2c_enable(i2c2_device);
    if(err != ALT_E_SUCCESS) UART_print("Error enabling device\r\n");
}

void test_I2C2_as_master(ALT_I2C_DEV_t * device)
{
    ALT_STATUS_CODE err;
    read_semaphore = OSSemCreate(0);
    write_semaphore = OSSemCreate(0);
    write_complete_semaphore = OSSemCreate(0);
    
    i2c2_device = device;
    err = alt_i2c_init(ALT_I2C_I2C1, i2c2_device);
    if(err != ALT_E_SUCCESS) UART_print("Error initializing i2c2\r\n");
    err = alt_i2c_disable(i2c2_device);
    if(err != ALT_E_SUCCESS) UART_print("Error disabling i2c2\r\n");
    ALT_I2C_MASTER_CONFIG_t master_config = {
        .addr_mode = ALT_I2C_ADDR_MODE_7_BIT,
        .restart_enable = true,
        .speed_mode = ALT_I2C_SPEED_STANDARD,
        .ss_scl_hcnt = 0x341,
        .ss_scl_lcnt = 0x2FB,
		.fs_spklen = 11
    };

    
    err = alt_i2c_master_config_set(i2c2_device, &master_config);
    if(err != ALT_E_SUCCESS) UART_print("Error configuring master device\r\n");
    err = alt_i2c_op_mode_set(i2c2_device, ALT_I2C_MODE_MASTER);
        if(err != ALT_E_SUCCESS) UART_print("Error setting i2c2 mode\r\n");
    err = alt_i2c_int_disable(i2c2_device, ALT_I2C_STATUS_INT_ALL);
    if(err != ALT_E_SUCCESS) UART_print("Error clearing interrupts\r\n");
    err = alt_i2c_int_enable(i2c2_device,
                        ALT_I2C_STATUS_STOP_DET | 
                        ALT_I2C_STATUS_RX_DONE | 
                        ALT_I2C_STATUS_RX_FULL |
                        ALT_I2C_STATUS_RD_REQ);
    if(err != ALT_E_SUCCESS) UART_print("Error enabling interrupts\n");
    init_I2C2_interrupt();

    err = alt_i2c_rx_fifo_threshold_set(i2c2_device, HALF_FULL);
    if(err != ALT_E_SUCCESS) UART_print("Error setting fifo\r\n");
    err = alt_i2c_enable(i2c2_device);
    if(err != ALT_E_SUCCESS) UART_print("Error enabling device\r\n");
    err = alt_i2c_is_enabled(i2c2_device);
    if(err != ALT_E_TRUE) UART_print("Device is not enabled\r\n");
    err = alt_i2c_master_config_get(i2c2_device, &master_config);
    if(err != ALT_E_SUCCESS) UART_print("Could not fetch config!\r\n");

}

void test_target_device()
{
	ALT_STATUS_CODE err;
	err = alt_i2c_master_target_set(i2c2_device, 17);
	if(err != ALT_E_SUCCESS) UART_print("Error targeting device\r\n");
}

void test_master_send()
{
	int test = 5;
	ALT_STATUS_CODE err;
	err = alt_i2c_master_transmit(i2c2_device, (void *)(&test), 4, 1, 1);
    if(err != ALT_E_SUCCESS) UART_print("Error transmitting to device 17\r\n");
}

void init_I2C2_interrupt(void)
{
    BSP_IntVectSet(I2C1_INTERRUPT_VECTOR,   // 192 is interrupt source for i2c2
                1,    // prio
                DEF_BIT_00,	    // cpu target list
                I2C2_ISR_Handler  // ISR
                );
    BSP_IntSrcEn(I2C1_INTERRUPT_VECTOR);
}

void I2C2_ISR_Handler(CPU_INT32U cpu_id) {
    uint32_t mask = 0;

    alt_i2c_int_status_get(i2c2_device, &mask);
    uint32_t rx_count = 0;
    //RX buffer over watermark or write complete
    if(mask & ALT_I2C_STATUS_RX_FULL)
    {
        alt_i2c_rx_fifo_level_get(i2c2_device, &rx_count);
        for(int i = 0; i < rx_count; i++)
        {
            alt_i2c_slave_receive(i2c2_device, &(I2C2_Internal_RX_Buffer[rx_write_pos]));
            rx_write_pos = (rx_write_pos + 1) % RX_BUFFER_SIZE;
        }
        alt_i2c_int_clear(i2c2_device, ALT_I2C_STATUS_RX_FULL);
    }
    else if(mask & ALT_I2C_STATUS_STOP_DET)
    {
    	alt_i2c_rx_fifo_level_get(i2c2_device, &rx_count);
        for(int i = 0; i < rx_count; i++)
        {
            alt_i2c_slave_receive(i2c2_device, &(I2C2_Internal_RX_Buffer[rx_write_pos]));
            rx_write_pos = (rx_write_pos + 1) % RX_BUFFER_SIZE;
        }
        if(rx_count > 0)
        {
            OSSemPost(read_semaphore);
        }
        alt_i2c_int_clear(i2c2_device, ALT_I2C_STATUS_STOP_DET);
    }
    else if(mask & ALT_I2C_STATUS_RX_DONE)
    {
    	alt_i2c_int_clear(i2c2_device, ALT_I2C_STATUS_RX_DONE);
        OSSemPost(write_complete_semaphore);
    }
    //Read required
    else if(mask & ALT_I2C_STATUS_RD_REQ)
    {
        alt_i2c_int_clear(i2c2_device, ALT_I2C_STATUS_RD_REQ | ALT_I2C_STATUS_TX_ABORT);
        if(TX_Size > 0)
        {
        	alt_i2c_slave_bulk_transmit(i2c2_device, I2C2_Internal_TX_Buffer, TX_Size);
        }
        else
        {
        	uint8_t sevens[6] = {0x07, 0x07, 0x07};
        	alt_i2c_slave_bulk_transmit(i2c2_device, sevens, 6);
        }
    }

    alt_i2c_int_clear(i2c2_device, ALT_I2C_STATUS_START_DET | ALT_I2C_STATUS_TX_ABORT);
}

ALT_STATUS_CODE write(void * data, size_t size)
{
	TX_Size = size;
	uint8_t err = 0;
	const char * buffer = data;
	for(int i = 0; i < size; i++)
	{
		I2C2_Internal_TX_Buffer[i] = buffer[i];
	}
	OSSemPend(write_complete_semaphore,0,&err);
}

void read(void * data, size_t size)
{
	uint8_t err;
    OSSemPend(read_semaphore, 0, &err);
    while(size > 0)
    {
        memcpy(data, &I2C2_Internal_RX_Buffer[rx_read_pos], 1);
        data++;
        rx_read_pos = (rx_read_pos + 1) % RX_BUFFER_SIZE;
        size--;
    }
}

