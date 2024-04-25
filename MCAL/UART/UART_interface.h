#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

/*************************< UART Number ****************************/
#define UART_CLOCK 							16000000
#define UART0                               0
#define UART1                               1
#define UART2                               2
#define UART3                               3
#define UART4                               4
#define UART5                               5
#define UART6                               6
#define UART7                               7
#define	DATA_5bits							5
#define DATA_6bits							6
#define DATA_7bits							7
#define DATA_8bits							8
#define UART_PARITY_NONE				    0
#define UART_PARITY_ODD					    1
#define UART_PARITY_EVEN				    2
#define STOP_1bit							1
#define STOP_2bit							2




/*************************< Functions ****************************/


/**
 * @brief   This function UART_Init initializes a UART (Universal Asynchronous Receiver/Transmitter)
 *			module for a specified UART number, with the specified baud rate, data bits,
 *			parity, and stop bits. The function first calculates the divisor value for the
 *			specified baud rate and sets the clock for the UART and GPIO pins.
 *			It then configures the UART pins for the specified UART number and sets the data
 *			frame. Finally, it enables the UART.
 *          Number of arguments: 5
 *
 * @param   UART_No: options will be:
 *                                      1) UART0
 *										2) UART1
 *										3) UART2
 *										4) UART3
 *										5) UART4
 *										6) UART5
 *										7) UART6
 *										8) UART7
 * @param   BaudRate : options will be:                                 // * NOT USED * //
 *
 *                                      1) UART_BDR_4800
 *                                      2) UART_BDR_9600
 *                                      3) UART_BDR_57600
 *
 * @param  DataBits : options will be:
 *                                      1) DATA_5bits
 *                                      2) DATA_6bits
 *                                      3) DATA_7bits
 *                                      4) DATA_8bits
 *
 * @param  Parity : options will be:
 *                                      1) UART_PARITY_NONE
 *                                      2) UART_PARITY_ODD
 *                                      3) UART_PARITY_EVEN
 *
 * @param  StopBits : options will be:
 *                                      1) STOP_1bit
 *                                      2) STOP_2bit
 *
 *
*/
void UART_Init(uint8_t UARTNo,uint32_t BaudRate, uint8_t DataBits, uint8_t Parity, uint8_t StopBits);
void clear_bit(uint32_t Register ,uint8_t Bit_No);
void set_bit(uint32_t Register ,uint8_t Bit_No);

#endif
