#include <stdint.h>

#include "GPIO_interface.h"

#include "tm4c123gh6pm.h"

void GPIO_Init(uint8_t PortId){
	SYSCTL_RCGCGPIO_R |= (1<<PortId);
	while((SYSCTL_PRGPIO_R & (1<<PortId))==0);
	switch(PortId){
		case GPIO_PORTA:
			GPIO_PORTA_LOCK_R = 0x4C4F434B;
			GPIO_PORTA_CR_R = 0xFF;
			GPIO_PORTA_AFSEL_R = 0x00;
			GPIO_PORTA_PCTL_R = 0x00000000;
			GPIO_PORTA_AMSEL_R=0x00;
			GPIO_PORTA_DEN_R=0xFF;
			break;
		case GPIO_PORTB:
			GPIO_PORTB_LOCK_R = 0x4C4F434B;
			GPIO_PORTB_CR_R = 0xFF;
			GPIO_PORTB_AFSEL_R = 0x00;
			GPIO_PORTB_PCTL_R = 0x00000000;
			GPIO_PORTB_AMSEL_R=0x00;
			GPIO_PORTB_DEN_R=0xFF;
			break;
		//risky port
		case GPIO_PORTC:
			// GPIO_PROTC_LOCK_R = 0x4C4F434B;
			// GPIO_PORTC_CR_R = 0xFF;
			// GPIO_PORTC_AFSEL_R = 0x00;
			// GPIO_PORTC_PCTL_R = 0x00000000;
			// GPIO_PORTC_AMSEL_R=0x00;
			// GPIO_PORTC_DEN_R=0xFF;
			break;
		case GPIO_PORTD:
			GPIO_PORTD_LOCK_R = 0x4C4F434B;
			GPIO_PORTD_CR_R = 0xFF;
			GPIO_PORTD_AFSEL_R = 0x00;
			GPIO_PORTD_PCTL_R = 0x00000000;
			GPIO_PORTD_AMSEL_R=0x00;
			GPIO_PORTD_DEN_R=0xFF;
			break;
		case GPIO_PORTE:
			GPIO_PORTE_LOCK_R = 0x4C4F434B;
			GPIO_PORTE_CR_R = 0xFF;
			GPIO_PORTE_AFSEL_R = 0x00;
			GPIO_PORTE_PCTL_R = 0x00000000;
			GPIO_PORTE_AMSEL_R=0x00;
			GPIO_PORTE_DEN_R=0xFF;
			break;
		case GPIO_PORTF:
			GPIO_PORTF_LOCK_R = 0x4C4F434B;	
			GPIO_PORTF_CR_R = 0xFF;
			GPIO_PORTF_AFSEL_R = 0x00;
			GPIO_PORTF_PCTL_R = 0x00000000;
			GPIO_PORTF_AMSEL_R=0x00;
			GPIO_PORTF_DEN_R=0xFF;
			break;
	}
}

void GPIO_SetPinDirection (uint8_t PortId, uint8_t PinId,uint8_t PinDirection){
	switch (PortId){
		case GPIO_PORTA:
			if (PinDirection==1){
				GPIO_PORTA_DIR_R |= (1<<PinId);
			}	
			else if (PinDirection==0){
				GPIO_PORTA_DIR_R &= ~(1<<PinId);
			}
			break;
		case GPIO_PORTB:
			if (PinDirection==1){
				GPIO_PORTB_DIR_R |= (1<<PinId);
			}	
			else if (PinDirection==0){
				GPIO_PORTB_DIR_R &= ~(1<<PinId);
			}
			break;
		case GPIO_PORTC:
			if (PinDirection==1){
				GPIO_PORTC_DIR_R |= (1<<PinId);
			}	
			else if (PinDirection==0){
				GPIO_PORTC_DIR_R &= ~(1<<PinId);
			}
			break;
		case GPIO_PORTD:
			if (PinDirection==1){
				GPIO_PORTD_DIR_R |= (1<<PinId);
			}	
			else if (PinDirection==0){
				GPIO_PORTD_DIR_R &= ~(1<<PinId);
			}
			break;
		case GPIO_PORTE:
			if (PinDirection==1){
				GPIO_PORTE_DIR_R |= (1<<PinId);
			}	
			else if (PinDirection==0){
				GPIO_PORTE_DIR_R &= ~(1<<PinId);
			}
			break;
		case GPIO_PORTF:
			if (PinDirection==1){
				GPIO_PORTF_DIR_R |= (1<<PinId);
			}	
			else if (PinDirection==0){
				GPIO_PORTF_DIR_R &= ~(1<<PinId);
			}
			break;
	}

}

void GPIO_SetPinValue(uint8_t PortId, uint8_t PinId, uint8_t PinValue){
	switch(PortId){
		case GPIO_PORTA:
            if (PinValue==1){
                GPIO_PORTA_DATA_R |= (1<<PinId);
            }
            else if (PinValue==0){
                GPIO_PORTA_DATA_R &= ~(1<<PinId);
            }
            break;
		case GPIO_PORTB:
            if (PinValue==1){
                GPIO_PORTB_DATA_R |= (1<<PinId);
            }
            else if (PinValue==0){
                GPIO_PORTB_DATA_R &= ~(1<<PinId);
            }
            break;
		case GPIO_PORTC:
            if (PinValue==1){
                GPIO_PORTC_DATA_R |= (1<<PinId);
            }
            else if (PinValue==0){
                GPIO_PORTC_DATA_R &= ~(1<<PinId);
            }
            break;
		case GPIO_PORTD:
            if (PinValue==1){
                GPIO_PORTD_DATA_R |= (1<<PinId);
            }
            else if (PinValue==0){
                GPIO_PORTD_DATA_R &= ~(1<<PinId);
            }
            break;
		case GPIO_PORTE:
            if (PinValue==1){
                GPIO_PORTE_DATA_R |= (1<<PinId);
            }
            else if (PinValue==0){
                GPIO_PORTE_DATA_R &= ~(1<<PinId);
            }
            break;
		case GPIO_PORTF:
            if (PinValue==1){
                GPIO_PORTF_DATA_R |= (1<<PinId);
            }
            else if (PinValue==0){
                GPIO_PORTF_DATA_R &= ~(1<<PinId);
            }
            break;
	}

}

void GPIO_GetPinValue(uint8_t PortId, uint8_t PinId, uint8_t *ReturnedValue){
	switch(PortId){
		case GPIO_PORTA:
             *ReturnedValue = GPIO_PORTA_DATA_R & (1<<PinId);
            break;
		case GPIO_PORTB:
             *ReturnedValue = GPIO_PORTB_DATA_R & (1<<PinId);
            break;
		case GPIO_PORTC:
             *ReturnedValue = GPIO_PORTC_DATA_R & (1<<PinId);
            break;
		case GPIO_PORTD:
             *ReturnedValue = GPIO_PORTD_DATA_R & (1<<PinId);
            break;
		case GPIO_PORTE:
             *ReturnedValue = GPIO_PORTE_DATA_R & (1<<PinId);
            break;
		case GPIO_PORTF:
             *ReturnedValue = GPIO_PORTF_DATA_R & (1<<PinId);
            break;
		
	}
}

	
