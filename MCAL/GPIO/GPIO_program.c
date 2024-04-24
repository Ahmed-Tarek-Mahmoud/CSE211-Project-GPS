#include <stdint.h>

#include "GPIO_interface.h"

#include "tm4c123gh6pm.h"

void GPIO_Init(uint8_t PortID){
	SYSCTL_RCGCGPIO_R |= (1<<PortID);
	while((SYSCTL_PRGPIO_R & (1<<PortID))==0);
	switch(PortID){
		case GPIO_PORTA:
			GPIO_PROTA_LOCK_R = 0x4C4F434B;
			GPIO_PORTA_CR_R = 0xFF;
			GPIO_PORTA_AFSEL_R = 0x00;
			GPIO_PORTA_PCTL_R = 0x00000000;
			GPIO_PORTA_AMSEL_R=0x00;
			GPIO_PORTA_DEN_R=0xFF;
			break;
		case GPIO_PORTB:
			GPIO_PROTB_LOCK_R = 0x4C4F434B;
			GPIO_PORTB_CR_R = 0xFF;
			GPIO_PORTB_AFSEL_R = 0x00;
			GPIO_PORTB_PCTL_R = 0x00000000;
			GPIO_PORTB_AMSEL_R=0x00;
			GPIO_PORTB_DEN_R=0xFF;
			break;
		//risky port
		case GPIO_PORTC:
			GPIO_PROTC_LOCK_R = 0x4C4F434B;
			GPIO_PORTC_CR_R = 0xFF;
			GPIO_PORTC_AFSEL_R = 0x00;
			GPIO_PORTC_PCTL_R = 0x00000000;
			GPIO_PORTC_AMSEL_R=0x00;
			GPIO_PORTC_DEN_R=0xFF;
			break;
		case GPIO_PORTD:
			GPIO_PROTD_LOCK_R = 0x4C4F434B;
			GPIO_PORTD_CR_R = 0xFF;
			GPIO_PORTD_AFSEL_R = 0x00;
			GPIO_PORTD_PCTL_R = 0x00000000;
			GPIO_PORTD_AMSEL_R=0x00;
			GPIO_PORTD_DEN_R=0xFF;
			break;
		case GPIO_PORTE:
			GPIO_PROTE_LOCK_R = 0x4C4F434B;
			GPIO_PORTE_CR_R = 0xFF;
			GPIO_PORTE_AFSEL_R = 0x00;
			GPIO_PORTE_PCTL_R = 0x00000000;
			GPIO_PORTE_AMSEL_R=0x00;
			GPIO_PORTE_DEN_R=0xFF;
			break;
		case GPIO_PORTF:
			GPIO_PROTF_LOCK_R = 0x4C4F434B;	
			GPIO_PORTF_CR_R = 0xFF;
			GPIO_PORTF_AFSEL_R = 0x00;
			GPIO_PORTF_PCTL_R = 0x00000000;
			GPIO_PORTF_AMSEL_R=0x00;
			GPIO_PORTF_DEN_R=0xFF;
			break;
	}
}

void GPIO_SetPinDirection (uint8_t PortId, uint8_t PinId,uint8_t PinDirection){
	switch (PortID){
		case GPIO_PORTA:
			if (PinDirection==1){
				GPTO_PORTA_DIR_R |= (1<<PinID);
			}	
			else if (PinDirection==0){
				GPTO_PORTA_DIR_R &= ~(1<<PinID);
			}
			break;
		case GPIO_PORTB:
			if (PinDirection==1){
				GPTO_PORTB_DIR_R |= (1<<PinID);
			}	
			else if (PinDirection==0){
				GPTO_PORTB_DIR_R &= ~(1<<PinID);
			}
			break;
		case GPIO_PORTC:
			if (PinDirection==1){
				GPTO_PORTC_DIR_R |= (1<<PinID);
			}	
			else if (PinDirection==0){
				GPTO_PORTC_DIR_R &= ~(1<<PinID);
			}
			break;
		case GPIO_PORTD:
			if (PinDirection==1){
				GPTO_PORTD_DIR_R |= (1<<PinID);
			}	
			else if (PinDirection==0){
				GPTO_PORTD_DIR_R &= ~(1<<PinID);
			}
			break;
		case GPIO_PORTE:
			if (PinDirection==1){
				GPTO_PORTE_DIR_R |= (1<<PinID);
			}	
			else if (PinDirection==0){
				GPTO_PORTE_DIR_R &= ~(1<<PinID);
			}
			break;
		case GPIO_PORTF:
			if (PinDirection==1){
				GPTO_PORTF_DIR_R |= (1<<PinID);
			}	
			else if (PinDirection==0){
				GPTO_PORTF_DIR_R &= ~(1<<PinID);
			}
			break;
	}
}
	
