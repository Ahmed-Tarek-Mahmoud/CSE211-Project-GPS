#include "STK_config.h"
#include "STK_interface.h"
#include "tm4c123gh6pm.h"



void STK_Init(uint32_t Ticks){

        STK_Disable();
        STK_Reset();
        STK_SetReloadValue(Ticks);
        STK_Enable();

}




void STK_Reset(void){

        NVIC_ST_CTRL_R  &= ~NVIC_ST_CTRL_COUNT;
        NVIC_ST_RELOAD_R =0;
        NVIC_ST_CURRENT_R =0;
}



void STK_GetCurrentValue(uint32_t *Current){

    *Current=NVIC_ST_CURRENT_R;

}

void STK_SetReloadValue(uint32_t Ticks){

        NVIC_ST_RELOAD_R=Ticks-1;

}

void STK_Enable(void){

        NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
        NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;
}

void STK_Disable(void){

        NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE;
        NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_CLK_SRC; // redundant step

}

void STK_EnableInterrupt(void){

        NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;

}

void STK_DisableInterrupt(void){

        NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_INTEN;


}

void STK_Delay(uint32_t DelayMs){

        //in case for using interrupt once for the whole time

        STK_DisableInterrupt();
        for(uint32_t i;i< (DelayMs-1) ;i++){
            STK_Init(80000);
            while( (NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0);
        }
        STK_EnableInterrupt();
        STK_Init(80000);


}
