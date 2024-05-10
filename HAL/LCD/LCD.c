#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\tm4c123gh6pm.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\GPIO\GPIO_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\STK\STK_interface.h"
#include "string.h"
#include <stdio.h>

static void send_pulse(void);
void lcd_send_number(int num);
void LCD_Init(void){

	  
			
	#if LCD_MODE == LCD_8_BIT_MODE
			
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D0_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D1_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D2_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D3_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D4_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D5_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D6_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D7_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_EN_PIN, GPIO_OUTPUT);
			
			STK_Delay(1);
            LCD_SendCommand(LCD_8_BIT_MODE_COMMAND);
            LCD_SendCommand(LCD_CLEAR_COMMAND);
            LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_BLINKING);
              		
			
		
	#elif LCD_MODE == LCD_4_BIT_MODE
				  
			GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RW_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_EN_PIN, GPIO_OUTPUT);
			
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D4_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D5_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D6_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D7_PIN, GPIO_OUTPUT);
			
		  STK_Delay(2);
			LCD_SendCommand(LCD_4_BIT_MODE_COMMAND1);
			LCD_SendCommand(LCD_4_BIT_MODE_COMMAND2);
			LCD_SendCommand(LCD_4_BIT_MODE_COMMAND3);
			LCD_SendCommand(0x0C);
			LCD_SendCommand(LCD_INCREMENT_CURSOR);
			LCD_SendCommand(LCD_CURSOR_BEGIN_FIRST_LINE);	
      LCD_SendCommand(LCD_CLEAR_COMMAND);		
			LCD_SendCommand(0x0E);
			LCD_SendCommand(0x0F);
			//STK_Delay(1);
      //LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_BLINKING);	
          
          
	#endif	
	

}

static void send_pulse(void){
	
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, GPIO_HIGH);
	STK_Delay(10);
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, GPIO_LOW);

}




void LCD_SendCommand(uint8_t Command){

  GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_LOW );
  GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, GPIO_LOW );
	
	
		#if LCD_MODE == LCD_8_BIT_MODE
		
			GPIO_SetPinValue(LCD_DATA_PORT, LCD_D0_PIN, Command >> 0 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D1_PIN, Command >> 1 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D2_PIN, Command >> 2 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D3_PIN, Command >> 3 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, Command >> 4 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, Command >> 5 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, Command >> 6 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, Command >> 7 & 0x01);
		    send_pulse();
		  
		
		#elif LCD_MODE == LCD_4_BIT_MODE
						
			
			      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, Command >> 4 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, Command >> 5 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, Command >> 6 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, Command >> 7 & 0x01);
						send_pulse();
		
			      Command = Command << 4;
		        
		        GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, Command >> 4 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, Command >> 5 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, Command >> 6 & 0x01);
            GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, Command >> 7 & 0x01);
		        send_pulse();
		  
	   	#endif  
	
	
}

void LCD_SendChar(uint8_t Character){
    GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_HIGH);
    GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, GPIO_LOW);
    #if LCD_MODE == LCD_8_BIT_MODE
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D0_PIN, Character & (0x01 << LCD_D0_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D1_PIN, Character & (0x01 << LCD_D1_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D2_PIN, Character & (0x01 << LCD_D2_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D3_PIN, Character & (0x01 << LCD_D3_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, Character & (0x01 << LCD_D4_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, Character & (0x01 << LCD_D5_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, Character & (0x01 << LCD_D6_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, Character & (0x01 << LCD_D7_PIN));
		send_pulse();
	
    #elif LCD_MODE == LCD_4_BIT_MODE
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, (Character >> 4) & 0x01);
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, (Character >> 5) & 0x01);
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, (Character >> 6) & 0x01);
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, (Character >> 7) & 0x01);
		send_pulse();
		Character = (Character << 4);
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, (Character >> 4) & 0x01);
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, (Character >> 5)& 0x01);
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, (Character >> 6) & 0x01);
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, (Character >> 7) & 0x01);
		send_pulse();
    
	#endif
}
        


void LCD_SendString(uint8_t *String){
    int Local_Counter=0;
    while(String[Local_Counter] != '\0'){
        LCD_SendChar(String[Local_Counter]);
        Local_Counter++;
       // LCD_SendCommand(LCD_INCREMENT_CURSOR);
    }
}

// I need to revise it 
void LCD_SendNumber(float number){
    char buffer[10] ={0};
    sprintf(buffer, "%f", number);
    LCD_SendString(buffer);
}

void LCD_clear(void){
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}

void LCD_setCursor( uint8_t row , uint8_t col ){
	uint8_t position = 0x00;

    // Determine the position based on row and column
    switch (row) {
        case 0:
            position = 0x00 + col;
            break;
        case 1:
            position = 0x40 + col;
            break;
        // Add more cases if your LCD has more than 2 rows
        default:
            break;
    }

    // Send command to set cursor position
    LCD_SendCommand(128 + position);

}

// Function to convert an integer to a string
void int_to_str(int num, char *str) {
    sprintf(str, "%d", num);
}

// Function to send a number to the LCD
void lcd_send_number(int num) {
    char num_str[16]; // Buffer to hold the string representation of the number
    
    // Convert integer to string
    int_to_str(num, num_str);
    
    // Send the string to the LCD
    LCD_SendString(num_str);
}
