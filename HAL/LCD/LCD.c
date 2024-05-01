#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "GPIO_program.c"
#include "GPIO_interface.h"

void LCD_Init(void){
	switch(LCD_MODE){

	  GPIO_Init(LCD_DATA_PORT);
    GPIO_Init(LCD_CONTROL_PORT);
			
		case LCD_8_BIT_MODE:
			
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
      LCD_SendCommand(LCD_DISPLAY_ON_COMMAND);
      break;  		
			
		
		case LCD_4_BIT_MODE:
			
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D4_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D5_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D6_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_D7_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_RS_PIN, GPIO_OUTPUT);
			GPIO_SetPinDirection(LCD_DATA_PORT, LCD_EN_PIN, GPIO_OUTPUT);
		  
      STK_Delay(1);
      LCD_SendCommand(LCD_4_BIT_MODE_COMMAND);
      LCD_SendCommand(LCD_CLEAR_COMMAND);
      LCD_SendCommand(LCD_DISPLAY_ON_COMMAND);		
		  break;
		
	}

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
	
	switch(LCD_MODE){
		
		case LCD_8_BIT_MODE:
			GPIO_SetPinValue(LCD_DATA_PORT, LCD_D0_PIN, Command >> 0 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D1_PIN, Command >> 1 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D2_PIN, Command >> 2 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D3_PIN, Command >> 3 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, Command >> 4 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, Command >> 5 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, Command >> 6 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, Command >> 7 & 0x01);
		  send_pulse();
		  
		  break;
		
		case LCD_4_BIT_MODE:
			GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, Command >> 4 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, Command >> 5 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, Command >> 6 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, Command >> 7 & 0x01);
		  send_pulse();
		
		  command = command <<4;
		
		  GPIO_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN, Command >> 4 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D5_PIN, Command >> 5 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D6_PIN, Command >> 6 & 0x01);
      GPIO_SetPinValue(LCD_DATA_PORT, LCD_D7_PIN, Command >> 7 & 0x01);
		  send_pulse();
		  
	   	break;
	

	}
		

}
