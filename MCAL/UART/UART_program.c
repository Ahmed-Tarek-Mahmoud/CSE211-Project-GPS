#include <stdint.h>

#include "UART_interface.h"

#include "tm4c123gh6pm.h"

void clear_bit(uint32_t REGISTER ,uint8_t BIT_NO);
void set_bit(uint32_t REGISTER ,uint8_t BIT_NO);

void UART_Init(uint8_t UARTNo,uint32_t BaudRate, uint8_t DataBits, uint8_t Parity, uint8_t StopBits){
        set_bit(SYSCTL_RCGCUART_R,UARTNo);
        switch(UARTNo){
///////////////////////////////////////// UART0 /////////////////////////////////////////
            case UART0:
					SYSCTL_RCGCGPIO_R |=(1<<UARTNo);
					while(!(SYSCTL_PRGPIO_R & 0x01));
					GPIO_PORTA_AFSEL_R |= 0x03;
					GPIO_PORTA_PCTL_R =(GPIO_PORTA_PCTL_R&0xFFFFFF00) + 0x00000011;
					GPIO_PORTA_DEN_R |= 0x03;
					GPIO_PORTA_AMSEL_R &= ~(0x03);
					UART0_CTL_R &= ~(0x0001);
					UART0_IBRD_R = (uint32_t)( UART_CLOCK / (BaudRate * 16));
					UART0_FBRD_R = (uint32_t)(((UART_CLOCK / (BaudRate * 16))-((uint32_t)(UART_CLOCK / (BaudRate * 16))))*64+0.5);
					UART0_LCRH_R |=0x10;
					if(DataBits==DATA_5bits){
						UART0_LCRH_R &= ~(0x60);  //clear bit 5,6
					}
					else if(DataBits==DATA_6bits){
						UART0_LCRH_R &= ~(0x40);  //clear bit 6
						UART0_LCRH_R |=  (0x20);  //set bit 5
					}
					else if(DataBits==DATA_7bits){
						UART0_LCRH_R &= ~(0x20);	//clear bit 5
						UART0_LCRH_R |=  (0x40);	//set bit 6
					}
					else if(DataBits==DATA_8bits){
						UART0_LCRH_R |=  (0x60);	//set bit 5,6
					}
					//parity 0-->none  1-->odd  2-->even	
					if(Parity==UART_PARITY_NONE)
						clear_bit(UART0_LCRH_R,1);
					else if(Parity==UART_PARITY_ODD){             		//odd
						set_bit(UART0_LCRH_R,1);
						clear_bit(UART0_LCRH_R,2);
					}
					else if(Parity==UART_PARITY_EVEN){								//even
						set_bit(UART0_LCRH_R,1);
						set_bit(UART0_LCRH_R,2);
					}
					//stop bits
					if(StopBits==STOP_1bit)
						clear_bit(UART0_LCRH_R,3);
					else if(StopBits==STOP_2bit)
						set_bit(UART0_LCRH_R,3);
					UART0_CTL_R |= 0x0301;
					break;
///////////////////////////////////////// UART1 /////////////////////////////////////////					
		case UART1:
					SYSCTL_RCGCGPIO_R |=0x04;
					while(!(SYSCTL_PRGPIO_R & 0x04));
					GPIO_PORTC_AFSEL_R |= 0x30;
					GPIO_PORTC_PCTL_R =(GPIO_PORTC_PCTL_R&0xFF00FFFF) + 0x00220000;
					GPIO_PORTC_DEN_R |= 0x30;
					GPIO_PORTC_AMSEL_R &= ~(0x30);
					UART1_CTL_R &= ~(0x0001);
					UART1_IBRD_R = (uint32_t)( UART_CLOCK / (BaudRate * 16));
					UART1_FBRD_R = (uint32_t)(((UART_CLOCK / (BaudRate * 16))-((uint32_t)(UART_CLOCK / (BaudRate * 16))))*64+0.5);
					UART1_LCRH_R |=0x10;
					if(DataBits==DATA_5bits){
						UART1_LCRH_R &= ~(0x60);  //clear bit 5,6
					}
					else if(DataBits==DATA_6bits){
						UART1_LCRH_R &= ~(0x40);  //clear bit 6
						UART1_LCRH_R |=  (0x20);  //set bit 5
					}
					else if(DataBits==DATA_7bits){
						UART1_LCRH_R &= ~(0x20);	//clear bit 5
						UART1_LCRH_R |=  (0x40);	//set bit 6
					}
					else if(DataBits==DATA_8bits){
						UART1_LCRH_R |=  (0x60);	//set bit 5,6
					}
					//parity 0-->none  1-->odd  2-->even	
					if(Parity==UART_PARITY_NONE)
						clear_bit(UART1_LCRH_R,1);
					else if(Parity==UART_PARITY_ODD){             	//odd
						set_bit(UART1_LCRH_R,1);
						clear_bit(UART1_LCRH_R,2);
					}
					else if(Parity==UART_PARITY_EVEN){								//even
						set_bit(UART1_LCRH_R,1);
						set_bit(UART1_LCRH_R,2);
					}
					//stop bits
					if(StopBits==STOP_1bit)
						clear_bit(UART1_LCRH_R,3);
					else if(StopBits==STOP_2bit)
						set_bit(UART1_LCRH_R,3);
					UART1_CTL_R |= 0x0301;
					break;
        }

}
void set_bit(uint32_t REGISTER ,uint8_t BIT_NO){
	REGISTER |=(1<<BIT_NO);
}

void clear_bit(uint32_t REGISTER ,uint8_t BIT_NO){
REGISTER &= ~(1<<BIT_NO);
}