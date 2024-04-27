//****************************************************//
//               File: Driver Program                 //
//               Date: 27 April 2024                  // 
//****************************************************//


/*************< System *******************************/
#include "stdint.h"
#include "tm4c123gh6pm.h"

/*************< System *******************************/

#include "GPIO_interface.h"
#include "UART_interface.h"

/*************< HAL *******************************/
#include "LED_interface.h"

int main(void){
    GPIO_Init(GPIO_PORTF);
    Switch_Init(PF_SW1);

    while (1)
    {
        uint8_t state;
        GPIO_GetPinValue(GPIO_PORTF,PIN4,&state);
        if (state == GPIO_LOW)
        {
            LEDx_On(RGB_RED);
        }
        
    }
    
}