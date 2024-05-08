//****************************************************//
//               File: Driver Program                 //
//               Date: 27 April 2024                  // 
//****************************************************//


/*************< System *******************************/
#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "string.h"

/*************< System *******************************/

#include "GPIO_interface.h"
#include "UART_interface.h"
#include "STK_interface.h"
#include "LCD_interface.h"
#include "GPS.h"

/*************< HAL *******************************/
#include "LED_interface.h"

float Lats[400] ={},Longs[400]={}; 
uint16_t cnt =0;
uint16_t DistAcc = 0;

int main(void){

    sysInit();

    uint8_t marker = 0;
    EEPROMRead(&marker , 0x0 , sizeof(marker));       // read the EEPROM marker

    if (marker == 1)
    {
      LCD_SendString("Connect UART");
      PC_Data();
    }
    

    UART_OutString("Enter 'Y' for final destination or 'N' for normal flow\n",UART5);
    uint8_t mode;
    UART_getString(&mode,2,UART5);

    float Latfinal = -1,Longfinal=-1;
    if (strcmp(mode,"Y") == 0)
    {   
        UART_OutString("Enter final latitude then enter the final longitude\n",UART5);
        string Latf , Longf;
        UART_getString(&Latf , 8, UART5);
        UART_getString(&Longf , 8,UART5);
        Latfinal = stof(Latf);
        Longfinal = stof(Longf);
    }

    
    float curLat = -1,curLong=-1,prevLat=-1,prevLong=-1,vel=-1;

    while (1)
    {    
       while (!GPS_ReceiveLog(&curLat , &curLong, &vel) || vel == 0 ); // Loop until valid log or velocity not equal zero
      if (prevLat == -1 && prevLong == -1)
      {
        prevLat = curLat;
        prevLong = curLong;
      }
      Lats[cnt] = curLat;
      Longs[cnt] = curLong;
      cnt++;
      DistAcc += GPS_CalcDist(curLat,curLong,prevLat,prevLong);

      if (strcmp(mode,"Y") == 0 && abs(curLat - Latfinal) <= 1e-6  && abs(curLong - Longfinal) <= 1e-6 )
      {
        /* Terminate */
        break;
      }
      
      if (strcmp(mode,"N") == 0 && DistAcc >= 100)
      {
        /* Terminate */
        break;
      }

      prevLat = curLat;
      prevLong = curLong;
      LCD_clear();
      STK_Delay(200);  
      LCD_SendString("Distance: ");
      LCD_SendNumber(DistAcc);
      LCD_setCursor(1,0);
      LCD_SendString("Velocity: ");
      LCD_SendNumber(vel);
    }
    LEDx_On(RGB_RED);
    LCD_clear();
    STK_Delay(200);
    LCD_SendString("Distance: ");
    LCD_SendNumber(DistAcc);
    LCD_setCursor(1,0);
    LCD_SendString("Velocity: ");
    LCD_SendNumber(vel);
    STK_Delay(2000);
    LCD_clear();
    STK_Delay(200);
    LCD_SendString("Press SW1");
    uint8_t val=1;
    GPIO_GetPinValue(GPIO_PORTF,PIN4,&val);
    while (val != 0 )
    {
      GPIO_GetPinValue(GPIO_PORTF,PIN4,&val);
    }
    EEPROMsaving();
    
    
}


void EEPROMsaving(){
    
    uint8_t marker = 1;
    EEPROMProgram(&marker , 0x0 , sizeof(marker));    // write data int the EEPROM

    EEPROMProgram(Lats , 0x4 , sizeof(Lats));          // write Latitudes in the EEPROM
    EEPROMProgram(Longs , 0x7D4 , sizeof(Longs));      // write Longitudes in the EEPROM
    LEDx_On(RGB_GREEN);
    while (1);
       
}

void sysInit(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	  SysCtlDelay(20000000);
	  SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

    EEPROMInit();
    EEPROMMassErase();  // erases EEPROM ( factory reset )
    GPIO_Init(GPIO_PORTF);
    GPIO_Init(GPIO_PORTB);
    UART_Init(UART5,9600,DATA_8bits,UART_PARITY_NONE,STOP_1bit);
    UART_Init(UART7,9600,DATA_8bits,UART_PARITY_NONE,STOP_1bit);
    Switch_Init(PF_SW1);
    Switch_Init(PF_SW2);
    STK_Init();
    __asm("CPSIE i"); // Enable interrupts globally
    NVIC_EnableInterrupt(30); // Enable port F interrupt
    SW2_InterruptInit();
    LCD_Init();
    LEDx_On(0);
}

void PC_Data(){
    char cmd[2] = {};
    UART_getString(cmd,2,UART5);
    while (strcmp(cmd,"U") != 0)
    {
      UART_OutString("Please enter 'U'\n",UART5);
      UART_getString(cmd,2,UART5);
    }

    EEPROMRead(Lats , 0x4 , sizeof(Lats));           // read the EEPROM marker
    EEPROMRead(Longs , 0x7D4 , sizeof(Longs));       // read the EEPROM marker
    string sss;
    UART_OutString("Lats   Longs\n",UART5);
    for (uint8_t i = 0; i < 400; i++)
    {
       dtostrf(Lats[i],-7,3,sss);
       UART_OutString(sss,UART5);
       UART_OutString("   ",UART5);
       dtostrf(Longs[i],-7,3,sss);
       UART_OutString(sss,UART5);
    } 

    
}

void GPIOF_Handler(){
  
    LEDx_On(RGB_RED);
    LCD_clear();
    STK_Delay(200);
    LCD_SendString("Distance: ");
    LCD_SendNumber(DistAcc);
    LCD_setCursor(1,0);
    LCD_SendString("Velocity: ");
    LCD_SendNumber(vel);
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
    EEPROMsaving();
}