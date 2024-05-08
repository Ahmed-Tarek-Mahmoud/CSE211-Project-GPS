#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "GPIO_program.c"
#include "GPIO_interface.h"
#include "string.h"

void LCD_Init(void){

	  GPIO_Init(LCD_DATA_PORT);
      GPIO_Init(LCD_CONTROL_PORT);
			
	#if LCD_MODE == LCD_8_BIT_MODE
			
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D0_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D1_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D2_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D3_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D4_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D5_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D6_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D7_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_RS_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_EN_PIN, GPIO_OUTPUT);
			
			STK_Delay(1);
            LCD_SendCommand(LCD_8_BIT_MODE_COMMAND);
            LCD_SendCommand(LCD_CLEAR_COMMAND);
            LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_BLINKING);
              		
			
		
	#elif LCD_MODE == LCD_4_BIT_MODE
			
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D4_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D5_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D6_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D7_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_RS_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_EN_PIN, GPIO_OUTPUT);
		  
            STK_Delay(1);
            LCD_SendCommand(LCD_4_BIT_MODE_COMMAND);
            LCD_SendCommand(LCD_CLEAR_COMMAND);
            LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_BLINKING);		
		    
	#endif	
	

}

static void send_pulse(void){
	
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, GPIO_HIGH);
	STK_Delay(2);
	GPIO_SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, GPIO_LOW);
    STK_Delay(2);

}




void LCD_SendCommand(uint8_t Command){

  GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_LOW );
  GPIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RW_PIN, GPIO_LOW );
	
	
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
		
			Command = Command <<4;
		
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
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, Character & (0x01 << LCD_D4_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, Character & (0x01 << LCD_D5_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, Character & (0x01 << LCD_D6_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, Character & (0x01 << LCD_D7_PIN));
		send_pulse();
		Character = Character << 4;
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, Character & (0x01 << LCD_D4_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, Character & (0x01 << LCD_D5_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, Character & (0x01 << LCD_D6_PIN));
		GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, Character & (0x01 << LCD_D7_PIN));
		send_pulse();
    
	#endif
}
        


void LCD_SendString(uint8_t *String){
    int Local_Counter=0;
    while(*(String + Local_Counter) != '\0'){
        LCD_SendChar(*(String + Local_Counter));
        Local_Counter++;
        LCD_SendCommand(LCD_INCREMENT_CURSOR);
    }
}

void LCD_SendNumber(float number){
    char buffer[10];
    dtostrf(number, -7, 3, buffer);
    LCD_SendString(buffer);

}

void LCD_clear(){
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}

void LCD_setCursor( uint8_t row , uint8_t column ){
	if(row==1){
		LCD_SendCommand(LCD_CURSOR_BEGIN_FIRST_LINE);
	}
	else if(row==2){
		LCD_SendCommand(LCD_CURSOR_BEGIN_SECOND_LINE);
	}
	while(column != 1){
		LCD_SendCommand(LCD_INCREMENT_CURSOR);
		column--;
	}

}