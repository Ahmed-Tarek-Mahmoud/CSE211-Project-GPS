#include "NVIC.h"

#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\tm4c123gh6pm.h"

//////////////////////////////////////////////////// * EnableInterrupt * ////////////////////////////////////////////////////
void NVIC_EnableInterrupt(uint8_t IntNumber){
			//pointer to the register of Enable needed
			volatile uint32_t *ptr;
			//offset to be added to the address of the first priority register and to store the bit we want to access
			uint8_t offset;
			//setting the offset(each enable reg have 32 bit, one for each interrupt )
			offset=(IntNumber/32)*4;
			//choosing the register upon the IRQ
			ptr=(uint32_t *)(0xE000E100+offset);
			offset=IntNumber%32;
			*ptr|=(1<<offset);
}

//////////////////////////////////////////////////// * DisableInterrupt * ////////////////////////////////////////////////////
void NVIC_DisableInterrupt(uint8_t IntNumber){
			//pointer to the register of disable needed
			volatile uint32_t *ptr;
			//offset to be added to the address of the first disable register and to store the bit we want to access
			uint8_t offset;
			//setting the offset(each enable reg have 32 bit, one for each interrupt )
			offset=(IntNumber/32)*4;
			//choosing the register upon the IRQ
			ptr=(uint32_t *)(0xE000E180+offset);
			offset=IntNumber%32;
			*ptr|=(1<<offset);

}

//////////////////////////////////////////////////// * SetPendingFlag * ////////////////////////////////////////////////////
void NVIC_SetPendingFlag(uint8_t IntNumber){
			//pointer to the register of pending needed
			volatile uint32_t *ptr;
			//offset to be added to the address of the first pending register and to store the bit we want to access
			uint8_t offset;
			//setting the offset(each enable reg have 32 bit, one for each interrupt )
			offset=(IntNumber/32)*4;
			//choosing the register upon the IRQ
			ptr=(uint32_t *)(0xE000E200+offset);
			offset=IntNumber%32;
			*ptr|=(1<<offset);

}

//////////////////////////////////////////////////// * ClearPendingFlag * ////////////////////////////////////////////////////
void NVIC_ClearPendingFlag(uint8_t IntNumber){
			//pointer to the register of unpending needed
			volatile uint32_t *ptr;
			//offset to be added to the address of the first unpending register and to store the bit we want to access
			uint8_t offset;
			//setting the offset(each enable reg have 32 bit, one for each interrupt )
			offset=(IntNumber/32)*4;
			//choosing the register upon the IRQ
			ptr=(uint32_t *)(0xE000E280+offset);
			offset=IntNumber%32;
			*ptr|=(1<<offset);

}
//////////////////////////////////////////////////// * GetActiveFlag * ////////////////////////////////////////////////////

void NVIC_GetActiveFlag(uint8_t IntNumber, uint8_t *Result){
			//pointer to the register of disable needed
			volatile uint32_t *ptr;
			//offset to be added to the address of the first unpending register and to store the bit we want to access
			uint8_t offset;
			//setting the offset(each enable reg have 32 bit, one for each interrupt )
			offset=(IntNumber/32)*4;
			//choosing the register upon the IRQ
			ptr=(uint32_t *)(0xE000E300+offset);
			offset=IntNumber%32;
			//reads the bit corresponding to the wanted IRQ
			if(*ptr&(1<<offset))
				*Result=1;
			else
				*Result=0;
}
//////////////////////////////////////////////////// * SetPriority * ////////////////////////////////////////////////////
void NVIC_SetPriority(uint8_t IRQ,uint8_t priority){
			//pointer to the register of priority needed
			volatile uint32_t *ptr;
			//offset to be added to the address of the first priority register
			uint8_t offset;
			//setting the offset
			offset=(IRQ/4)*4;
			//choosing the register upon the IRQ
			ptr=(uint32_t *)(0xE000E400+offset);
			//choosing the segment to write in
			switch(IRQ%4){
				case 0:
					*ptr=(*ptr&0xFFFFFF00)|(priority<<5);
					break;
				case 1:
					*ptr=(*ptr&0xFFFF00FF)|(priority<<13);
					break;
				case 2:
					*ptr=(*ptr&0xFF00FFFF)|(priority<<21);
					break;
				case 3:
					*ptr=(*ptr&0x00FFFFFF)|(priority<<29);
					break;
				}
}

///////////////////////////////////////////// * Enable port F switch Interrupt * /////////////////////////////////////////////
void SW2_InterruptInit(void){
		// Interrupt Sense (0 for edge sensitive , 1 for level sensitive)
		GPIO_PORTF_IS_R &= ~0x01;
		// Interrupt Both Edges
		GPIO_PORTF_IBE_R &= ~0x01;
		// Interrupt Event (0 for falling edge , 1 for rising edge)
		GPIO_PORTF_IEV_R &= ~0x01;
		// Interrupt Mask
		GPIO_PORTF_IM_R |=0x01;
		// Interrupt Clear
		GPIO_PORTF_ICR_R |= 0x01;
}
