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
#define clear_bit( Register ,Bit_No) Register &= ~(1<<Bit_No)
#define set_bit( Register , Bit_No) Register |=(1<<Bit_No)

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


/**
 * @brief   The function first waits for the transmit buffer to be available (not full) before 
 *			sending the byte of data. This is done using a while loop that checks the value of the 
 *			UART_FR_TXFF flag in the UART status register (UARTx_FR_R). 
 *			The flag is set if the transmit buffer is full, which means that the UART is currently 
 *			busy sending data and cannot accept any more data until some of the buffer space has 
 *			been freed up.
 *
 *			Once the transmit buffer is available, the function sends the data byte by writing 
 *			it to the UART data register (UARTx_DR_R), where it will be transmitted over 
 *			the communication channel. 
 *
 * @param uartNo : UART number to choose 
 *                  UARTx -> x in [0:7]
 * 
 * @param data : data to be transmitted
*/

void UART_sendChar(uint8_t uartNo,char data);

/**
 * @brief   The function first waits for the receive buffer to have data available before receiving 
 *			the byte of data. This is done using a while loop that checks the value of the 
 *			UART_FR_RXFE flag in the UART status register (UARTx_FR_R). The flag is set if 
 *			the receive buffer is empty, which means that the UART is currently not receiving 
 *			any data and cannot provide any data until some data is received.
 *
 *			Once the receive buffer has data available, the function receives the data byte 
 *			by reading it from the UART data register (UARTx_DR_R) and storing it at the 
 *			memory location pointed to by the second argument passed to the function.
 *
 * @param uartNo : UART number to choose 
 *                  UARTx -> x in [0:7]
 * @return  character received
*/

char UART_receiveChar(uint8_t uartNo);

/**
 * @brief   This function is responsible for recieving a string with specific maximum length by uart protocol for a specific uart number
 *          Internally it calls the receiveChar() function to read character by character and it assigns the values in the passed character 
 *          array using the pointer to character array parameter
 * 
 * @param cmd : pointer to character array to receive the string in it.
 * 
 * @param len : maximum length of the string.
 * 
 * @param uartNo : UART number to choose 
 *                  UARTx -> x in [0:7] 
*/

void UART_getString(char *cmd, uint32_t len,uint8_t uartNo);

/**
 * @brief This function is responsible for sending a string using a specified uart number
 *        Internally it calls the sendChar() function to send character by character and 
 *        it then increment the pointer to stand on the next element in the string.
 * 
 * @param ptr : pointer to the start of the transmitted string
 * 
 * @param uartNo :  UART number to choose 
 *                  UARTx -> x in [0:7] 
*/

void UART_OutString(char *ptr,uint8_t uartNo);

#endif
