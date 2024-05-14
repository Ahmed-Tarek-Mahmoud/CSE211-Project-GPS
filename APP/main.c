

/*************< System *******************************/
#include "stdint.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\tm4c123gh6pm.h"
#include "stdbool.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
/*************< System *******************************/

#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Milestone 1\TivaWare_C_Series-2.2.0.295\driverlib\eeprom.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/flash.h"
#include "driverlib/eeprom.h"
#include "driverlib/fpu.h"


#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\GPIO\GPIO_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\UART\UART_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\STK\STK_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\HAL\LCD\LCD_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\HAL\GPS\GPS.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\NVIC\NVIC.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\HAL\LED\LED_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\HAL\LCD\LCD_config.h"

void EEPROMsaving(void);
void sysInit(void);
void PC_Data(void);
void GPIOF_Handler(void);

double Lats[400];
double Longs[400];
uint16_t cnt =0;
volatile double DistAcc = 0;
volatile double vel=0;
volatile double curLat = -1,curLong=-1,prevLat=-1,prevLong=-1;
volatile double Latfinal = -1,Longfinal=-1;
int main(void){

	sysInit();
	
	
	LCD_clear();
	
	LCD_SendString("Program Start");
	STK_Delay(500);
  LCD_setCursor(1,0);
	STK_Delay(500);
  LCD_SendString("Initializing..");
	

    
    uint8_t marker = 0;
    EEPROMRead(&marker , 0x0 , sizeof(marker));       // read the EEPROM marker

    if (marker == 1)
    {
      LCD_SendString("Connect UART");
      PC_Data();
			
    }
    

    UART_OutString("Enter 'Y' for final destination or 'N' for normal flow\n",UART7);
    char mode[2]={0};
    UART_getString(mode,2,UART7);
   
    if (mode[0]=='Y')
    {   
        UART_OutString("Enter final latitude then enter the final longitude\n",UART7);
        char * Latf = NULL;
        char * Longf = NULL;
        UART_getString(Latf , 12, UART7);
        UART_getString(Longf , 12,UART7);
        Latfinal = atof(Latf);
        Longfinal = atof(Longf);
    }
    
    while (1)
    {    
			
				while (GPS_ReceiveLog(&curLat , &curLong, &vel , UART7) != 1){ // Loop until valid log or velocity not equal zero
				}
				
			if(prevLat==-1 && prevLong==-1){
			prevLat=curLat;
			prevLong=curLong;
			
			}
				
			if((fabs(curLat - prevLat) <= 1e-4 && 	fabs(curLong - prevLong) <= 1e-4) || vel <=0.1)	continue;  
		 
			Lats[cnt]=curLong;
      Longs[cnt]=curLat;	
			
			DistAcc = DistAcc + GPS_CalcDist(&curLat,&curLong,&prevLat,&prevLong);
      cnt=cnt+1;
      
			
      if (strcmp(mode,"Y") == 0 &&( fabs(curLat - Latfinal) <= 1e-6 ) && (fabs(curLong - Longfinal) <= 1e-6 ))
      {
        
        break;
      }
      
      if (strcmp(mode,"N") == 0 && DistAcc >= 100)
      {
        
        break;
      }

      prevLat = curLat;
      prevLong = curLong;
      LCD_clear();
      STK_Delay(500);  
      LCD_SendString("Distance: ");
      LCD_SendNumber(DistAcc);
      LCD_setCursor(1,0);
      LCD_SendString("Velocity: ");
      LCD_SendNumber(vel);
      STK_Delay(2000); 
			
    }
		
    LEDx_On(RGB_RED);
    LCD_clear();
    STK_Delay(1000);
    LCD_SendString("Distance: ");
    LCD_SendNumber(DistAcc);
    LCD_setCursor(1,0);
   // LCD_SendString("Velocity: ");
    //LCD_SendNumber(vel);
    STK_Delay(2000);
    LCD_clear();
    STK_Delay(1000);
    LEDx_On(RGB_RED);
		//PC_Data();   // remove comment to send data to pc directly
    
		uint8_t val=1;
    GPIO_GetPinValue(GPIO_PORTF,PIN4,&val);
    while (val != 0 )
    {
      GPIO_GetPinValue(GPIO_PORTF,PIN4,&val);
    }
		
    EEPROMsaving();
    
    while(1);
}


void EEPROMsaving(void){
    
    uint8_t marker = 1;
    EEPROMProgram(&marker , 0x0 , sizeof(marker));    // write data int the EEPROM

    EEPROMProgram(Lats , 0x4 , sizeof(Lats));          // write Latitudes in the EEPROM
    EEPROMProgram(Longs , 0x7D4 , sizeof(Longs));      // write Longitudes in the EEPROM
    LEDx_On(RGB_GREEN);
    while (1);  // program finished
       
}

void sysInit(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	  SysCtlDelay(20000000);
	  SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

    EEPROMInit();
     
	  FPUEnable();
    STK_Init(16000);
    GPIO_Init(GPIO_PORTA);
    GPIO_Init(GPIO_PORTF);
    GPIO_Init(GPIO_PORTE);
    GPIO_Init(GPIO_PORTB);
    LCD_Init();
    UART_Init(UART5,9600,DATA_8bits,UART_PARITY_NONE,STOP_1bit);
    UART_Init(UART7,9600,DATA_8bits,UART_PARITY_NONE,STOP_1bit);
    Switch_Init(PF_SW1);
    Switch_Init(PF_SW2);
    __asm("CPSIE i"); // Enable interrupts globally
    NVIC_EnableInterrupt(30); // Enable port F interrupt
    SW2_InterruptInit();
    
    LEDx_On(0);
}

void PC_Data(){
	  LCD_clear();
    STK_Delay(100);
	  LCD_SendString("Open Serial");
    char cmd[2] = {0};
		UART_OutString("Please enter 'U'\n",UART7);
    UART_getString(cmd,2,UART7);
    while ( cmd[0] != 'U')
    {
      UART_OutString("Please enter 'U'\n",UART7);
      UART_getString(cmd,2,UART7);
    }

    EEPROMRead(Lats , 0x4 , sizeof(Lats));           // read the EEPROM marker
    EEPROMRead(Longs , 0x7D4 , sizeof(Longs));       // read the EEPROM marker
    char sss[10]={0};
    UART_OutString("Lats   Longs\n",UART7);
		uint8_t i;
    for (i = 0; i < 17; i++)
    {
       sprintf(sss,"%f",Lats[i]);
       UART_OutString(sss,UART7);
       UART_OutString("   ",UART7);
       sprintf(sss,"%f",Longs[i]);
       UART_OutString(sss,UART7);
			UART_OutString("\n",UART7);
    } 
    EEPROMMassErase();  // erases EEPROM ( factory reset )
		UART_OutString("END",UART7);
		LCD_clear();
		STK_Delay(100);
	  LCD_SendString("Success");
		while(1);
    
}

void GPIOF_Handler(){
    
    LEDx_On(RGB_RED);
	  LCD_clear();
    STK_Delay(200);
    LCD_SendString("Distance: ");
    LCD_SendNumber(DistAcc);
    LCD_setCursor(1,0);
   // LCD_SendString("Velocity: ");
    //LCD_SendNumber(vel);
    STK_Delay(2000);
    LCD_clear();
    STK_Delay(200);
    LCD_SendString("Press SW1");
    uint8_t val=1;
    GPIO_GetPinValue(GPIO_PORTF,PIN4,&val);
    while (val !=0 )
    {
      GPIO_GetPinValue(GPIO_PORTF,PIN4,&val);
    }
	  NVIC_ClearPendingFlag(30); // Manually clearing the flag
    LEDx_On(RGB_GREEN);
		PC_Data();
		EEPROMsaving();
}


