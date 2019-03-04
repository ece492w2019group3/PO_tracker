#ifndef UART_H
#define UART_H
#include <alt_16550_uart.h>

void UART_Init(void);

ALT_STATUS_CODE UART_printn(char * str, size_t len);

ALT_STATUS_CODE UART_print(char * str);

#endif //UART_H
