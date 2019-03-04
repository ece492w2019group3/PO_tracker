#include "uart.h"
#include <string.h>
#include <alt_16550_uart.h>
#include <stdbool.h>

static ALT_16550_HANDLE_t hdl_uart0;
static bool initialized = false;

void UART_Init(void)
{
    ALT_16550_DEVICE_t uart0 = ALT_16550_DEVICE_SOCFPGA_UART0;
    ALT_STATUS_CODE err = alt_16550_init(uart0, NULL, NULL, &hdl_uart0);
    err = alt_16550_enable(&hdl_uart0);
    err = alt_16550_fifo_enable(&hdl_uart0);
    err = alt_16550_fifo_clear_rx(&hdl_uart0);
    initialized = true;
}

ALT_STATUS_CODE UART_printn(char * str, size_t len)
{
    if(!initialized) UART_Init();
    return alt_16550_fifo_write_safe(&hdl_uart0, str, len, true);
}

ALT_STATUS_CODE UART_print(char * str)
{
    return UART_printn(str, strlen(str));
}
