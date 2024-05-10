#ifndef HAL_LCD_INTERFACE
#define HAL_LCD_INTERFACE

#include "stdint.h"

/** @brief 	This function is responsible for initializing an LCD display module.
 *			The function first checks if the LCD mode is set to 8-bit or 4-bit mode using preprocessor directives. Depending on the mode, 
 *          it initializes the necessary pins for the LCD display module using the GPIO_Init() function. 
 *          If the data pins and control pins are on separate ports, it initializes both ports.
 * 			The function then sets the direction of the necessary pins to output using the GPIO_SetPinDirection() function. 
 *          The necessary pins include data pins D0-D7, RS (Register Select) pin, and EN (Enable) pin.
 *			The function then waits for 1 millisecond using the STK_Delay() function (will be implemented) to give the LCD display module time to power up.
 *			Next, the function sends commands to the LCD display module using the LCD_SendCommand() function. 
 *          The commands include setting the LCD mode to 8-bit or 4-bit mode, clearing the display, and turning on the display.
 *			If the LCD mode is not set to 8-bit or 4-bit mode, the function throws an error using a preprocessor directive.
 *
 * 
 *
 */

void LCD_Init(void);

/** @brief	This function is responsible for sending a command to the LCD display module.
 *			The function first sets the RS (Register Select) pin to low to indicate that a command is being sent.
 *           It also sets the RW (Read/Write) pin to low to indicate that the operation is a write operation.
 *			Depending on the LCD mode (8-bit or 4-bit), the function sets the necessary data pins.
 *			The function then sets the EN (Enable) pin to high to enable the LCD display module to read the command. 
 *          After a short delay using the STK_Delay(), the function sets the EN pin to low to complete the command.
 * 
 *          Difference between the 2 modes:
 *			If the LCD mode is set to 4-bit mode, the function shifts the 4 least significant bits of the command to the 4 most significant bits and repeats the same process for these bits.
 *          If the LCD mode is set to 8-bit mode, data is represented normally.
 *			If the LCD mode is not set to 8-bit or 4-bit mode, the function throws an error using a preprocessor directive.
 *
 * 
 *  @param Command : command to be displayed.
 * 
 *     please define the following commands as macros:
 *                                     1) For Hex Code-01, the LCD command will be the clear LCD screen
 *                                     2) For Hex Code-04, the LCD command will be decrement cursor
 *                                     3) For Hex Code-06, the LCD command will be Increment cursor
 *                                     4) For Hex Code-05, the LCD command will be Shift display right
 *                                     5) For Hex Code-07, the LCD command will be Shift display left
 *                                     6) For Hex Code-08, the LCD command will be Display off, cursor off
 *                                     7) For Hex Code-0F, the LCD command will be cursor blinking, Display on
 *                                     8) For Hex Code-10, the LCD command will be Shift cursor position to left
 *                                     9) For Hex Code-14, the LCD command will be Shift cursor position to the right
 *                                    10) For Hex Code-18, the LCD command will be Shift the entire display to the left
 *                                    11) For Hex Code-1C, the LCD command will be Shift the entire display to the right
 *                                    12) For Hex Code-80, the LCD command will be Force cursor to the beginning ( 1st line)
 *                                    13) For Hex Code-C0, the LCD command will be Force cursor to the beginning ( 2nd line)
 *                                    14) For Hex Code-38, the LCD command will be 2 lines and 5×7 matrix
 */

void LCD_SendCommand(uint8_t Command);

/** @brief	This function is responsible for sending a character to the LCD display module.
 *			The function first sets the RS (Register Select) pin to high to indicate that a data character is being sent. It also sets the RW (Read/Write) pin to low to indicate that the operation is a write operation.
 *			Depending on the LCD mode (8-bit or 4-bit), the function sets the necessary data pins to the corresponding bits of the character using the GPIO_SetPinValue() function.
 *			The function then sets the EN (Enable) pin to high to enable the LCD display module to read the character. After a short delay (about 1 or 2 ms) using the STK_Delay() function, the function sets the EN pin to low to complete the character transmission.
 *			If the LCD mode is set to 4-bit mode, the function shifts the 4 least significant bits of the character to the 4 most significant bits and repeats the same process for these bits.
 *			If the LCD mode is not set to 8-bit or 4-bit mode, the function throws an error using a preprocessor directive.
 * 
 *          Difference between the 2 modes (GPT):
 *			The main difference between 8-bit and 4-bit modes in LCD interfacing lies in how many data lines are used to send commands and data to the LCD.
 *
 *           1. **8-bit Mode:**
 *              - In 8-bit mode, 8 data lines (D0-D7) are used to transmit both commands and data to the LCD.
 *              - This mode allows faster data transfer since all 8 bits of data are sent in parallel.
 *              - Typically, 8-bit mode requires more GPIO pins on the microcontroller for data transmission.
 *           
 *           2. **4-bit Mode:**
 *              - In 4-bit mode, only 4 data lines (D4-D7) are used to transmit commands and data to the LCD. The other 4 data lines (D0-D3) are not used.
 *              - The 4-bit mode is slower compared to 8-bit mode because data is sent in two 4-bit nibbles sequentially.
 *              - 4-bit mode saves GPIO pins on the microcontroller, making it more suitable for projects with limited GPIO resources.
 *              - Despite being slower, the difference in speed may not be noticeable in many applications.
 *           
 *           Both modes have their advantages and disadvantages, but 4-bit mode is often preferred in projects where GPIO pin count is a concern, and the slight decrease in speed is acceptable. Additionally, 4-bit mode is sufficient for many applications and significantly reduces the number of connections required between the microcontroller and the LCD.
 *
 * 
 *  @param Character  : character to be displayed.
 */

void LCD_SendChar(uint8_t Character);

/** \brief	This function is responsible for sending a string of characters to the LCD display module. The function takes a single parameter, which is a pointer to the beginning of the string.
 * 			The function uses a while loop to iterate through each character of the string. The loop continues until it reaches the null character ('\0') at the end of the string.
 * 			For each character in the string, the function calls the LCD_SendChar() function to send the character to the LCD display module.
 * 			The function uses a local variable called Local_Counter to keep track of the current character in the string. This variable is incremented by 1 after each character is sent to the LCD display module.
 *			Overall, this function is useful for displaying strings of text on the LCD display module.
 *
 * @param	String : pointer to the string you want to display on the LCD
 * 
 *
 */

void LCD_SendString(uint8_t *String);

/**
 * @brief	This function is responsible for sending a floating-point number to the LCD.
 *          please handle displaying the float point '.' and negative sign '-' for negative numbers
 * 
 *          Useful idea and remove it after implementing: 
 *          parse the number into a character array
 *          
 *  @param	number : number you want to display on the LCD        
*/

void LCD_SendNumber(float number);

/**
 * @brief This function clears the lcd using the command macro and function LCD_SendCommand()
*/

void LCD_clear(void);


/**
 * @brief	This function is responsible for moving the cursor of the LCD display module to a specific position on the screen.
 *          it takes two inputs which are the coordinates
 * 
 * @param   row : represents the row number
 * 
 * @param   column : represents the column number
 * 
*/

void LCD_setCursor( uint8_t row , uint8_t column );



void lcd_send_number(int num);

#endif
