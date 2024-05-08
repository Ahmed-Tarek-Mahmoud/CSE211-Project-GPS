#include <stdint.h>

#include "LED_interface.h"

#include "tm4c123gh6pm.h"


void Switch_Init(uint8_t SwitchNo)
{
    GPIO_Init(GPIO_PORTF);
   
   if (SwitchNo == PF_SW1)
   {
    GPIO_PORTF_PUR_R |= PF_PIN4_PUR;
    GPIO_SetPinDirection(GPIO_PORTF,PIN4,INPUT);
   }
   else if (SwitchNo == PF_SW2)
   {
    GPIO_PORTF_PUR_R |= PF_PIN0_PUR;
    GPIO_SetPinDirection(GPIO_PORTF,PIN0,INPUT);
   }

}

void LEDx_On(uint8_t LedColor)
{
    GPIO_SetPinValue(GPIO_PORTF,PIN1,OFF);
    GPIO_SetPinValue(GPIO_PORTF,PIN2,OFF);
    GPIO_SetPinValue(GPIO_PORTF,PIN3,OFF);

   if (LedColor == RGB_RED)
   {
    GPIO_SetPinDirection(GPIO_PORTF,PIN1,OUTPUT);
		GPIO_SetPinValue(GPIO_PORTF,PIN1,ON);
   }
   else if (LedColor == RGB_BLUE)
   {
     GPIO_SetPinDirection(GPIO_PORTF,PIN2,OUTPUT);
		 GPIO_SetPinValue(GPIO_PORTF,PIN2,ON);
   }
	 else if(LedColor == RGB_GREEN)
	 {
		 GPIO_SetPinDirection(GPIO_PORTF,PIN3,OUTPUT);
		 GPIO_SetPinValue(GPIO_PORTF,PIN3,ON);	
	 }
}