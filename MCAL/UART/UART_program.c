#include <stdint.h>

#include "UART_interface.h"

#include "tm4c123gh6pm.h"


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
					clear_bit(GPIO_PORTA_DIR_R,0);
					set_bit(GPIO_PORTA_DIR_R,1);
					GPIO_PORTA_AMSEL_R &= ~(0x03);
					UART0_CTL_R &= ~(0x0001);
					UART0_IBRD_R = (uint32_t)( UART_CLOCK / (BaudRate * 16));
					UART0_FBRD_R = (uint32_t)(((UART_CLOCK / (BaudRate * 16.0))-((uint32_t)(UART_CLOCK / (BaudRate * 16))))*64+0.5);
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
					clear_bit(GPIO_PORTC_DIR_R,4);
					set_bit(GPIO_PORTC_DIR_R,5);
					GPIO_PORTC_AMSEL_R &= ~(0x30);
					UART1_CTL_R &= ~(0x0001);
					UART1_IBRD_R = (uint32_t)( UART_CLOCK / (BaudRate * 16));
					UART1_FBRD_R = (uint32_t)(((UART_CLOCK / (BaudRate * 16.0))-((uint32_t)(UART_CLOCK / (BaudRate * 16))))*64+0.5);
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
///////////////////////////////////////// UART2 /////////////////////////////////////////
		case UART2:
					SYSCTL_RCGCGPIO_R |=0x08;
					while(!(SYSCTL_PRGPIO_R & 0x08));
					GPIO_PORTD_AFSEL_R |= 0xC0;
					GPIO_PORTD_PCTL_R =(GPIO_PORTD_PCTL_R&0x00FFFFFF) + 0x11000000;
					GPIO_PORTD_DEN_R |= 0xC0;
					clear_bit(GPIO_PORTD_DIR_R,6);
					set_bit(GPIO_PORTD_DIR_R,7);
					GPIO_PORTD_AMSEL_R &= ~(0xC0);
					UART2_CTL_R &= ~(0x0001);
					UART2_IBRD_R = (uint32_t)( UART_CLOCK / (BaudRate * 16));
					UART2_FBRD_R = (uint32_t)(((UART_CLOCK / (BaudRate * 16.0))-((uint32_t)(UART_CLOCK / (BaudRate * 16))))*64+0.5);
					UART2_LCRH_R |=0x10;
					if(DataBits==DATA_5bits){
						UART2_LCRH_R &= ~(0x60);                    //clear bit 5,6
					}
					else if(DataBits==DATA_6bits){
						UART2_LCRH_R &= ~(0x40);                    //clear bit 6
						UART2_LCRH_R |=  (0x20);                    //set bit 5
					}
					else if(DataBits==DATA_7bits){
						UART2_LCRH_R &= ~(0x20);	                //clear bit 5
						UART2_LCRH_R |=  (0x40);	                //set bit 6
					}
					else if(DataBits==DATA_8bits){
						UART2_LCRH_R |=  (0x60);	                //set bit 5,6
					}
					//parity 0-->none  1-->odd  2-->even
					if(Parity==UART_PARITY_NONE)
						clear_bit(UART2_LCRH_R,1);
					else if(Parity==UART_PARITY_ODD){             	//odd
						set_bit(UART2_LCRH_R,1);
						clear_bit(UART2_LCRH_R,2);
					}
					else if(Parity==UART_PARITY_EVEN){				//even
						set_bit(UART2_LCRH_R,1);
						set_bit(UART2_LCRH_R,2);
					}
					//stop bits
					if(StopBits==STOP_1bit)
						clear_bit(UART2_LCRH_R,3);
					else if(StopBits==STOP_2bit)
						set_bit(UART2_LCRH_R,3);
					UART2_CTL_R |= 0x0301;
					break;
///////////////////////////////////////// UART3 /////////////////////////////////////////
		case UART3:
					SYSCTL_RCGCGPIO_R |=0x04;
					while(!(SYSCTL_PRGPIO_R & 0x04));
					GPIO_PORTC_AFSEL_R |= 0xC0;
					GPIO_PORTC_PCTL_R =(GPIO_PORTA_PCTL_R&0x00FFFFFF) + 0x11000000;
					GPIO_PORTC_DEN_R |= 0xC0;
					clear_bit(GPIO_PORTC_DIR_R,6);
					set_bit(GPIO_PORTC_DIR_R,7);
					GPIO_PORTC_AMSEL_R &= ~(0xC0);
					UART3_CTL_R &= ~(0x0001);
					UART3_IBRD_R = (uint32_t)( UART_CLOCK / (BaudRate * 16));
					UART3_FBRD_R = (uint32_t)(((UART_CLOCK / (BaudRate * 16.0))-((uint32_t)(UART_CLOCK / (BaudRate * 16))))*64+0.5);
					UART3_LCRH_R |=0x10;
					if(DataBits==DATA_5bits){
						UART3_LCRH_R &= ~(0x60);                    //clear bit 5,6
					}
					else if(DataBits==DATA_6bits){
						UART3_LCRH_R &= ~(0x40);                    //clear bit 6
						UART3_LCRH_R |=  (0x20);                    //set bit 5
					}
					else if(DataBits==DATA_7bits){
						UART3_LCRH_R &= ~(0x20);	                //clear bit 5
						UART3_LCRH_R |=  (0x40);	                //set bit 6
					}
					else if(DataBits==DATA_8bits){
						UART3_LCRH_R |=  (0x60);	                //set bit 5,6
					}
					//parity 0-->none  1-->odd  2-->even
					if(Parity==UART_PARITY_NONE)
						clear_bit(UART3_LCRH_R,1);
					else if(Parity==UART_PARITY_ODD){             	//odd
						set_bit(UART3_LCRH_R,1);
						clear_bit(UART3_LCRH_R,2);
					}
					else if(Parity==UART_PARITY_EVEN){				//even
						set_bit(UART3_LCRH_R,1);
						set_bit(UART3_LCRH_R,2);
					}
					//stop bits
					if(StopBits==STOP_1bit)
						clear_bit(UART3_LCRH_R,3);
					else if(StopBits==STOP_2bit)
						set_bit(UART3_LCRH_R,3);
					UART3_CTL_R |= 0x0301;
					break;
///////////////////////////////////////// UART4 /////////////////////////////////////////
		case UART4:
					SYSCTL_RCGCGPIO_R |=0x04;
					while(!(SYSCTL_PRGPIO_R & 0x04));
					GPIO_PORTC_AFSEL_R |= 0x30;
					GPIO_PORTC_PCTL_R =(GPIO_PORTC_PCTL_R&0xFF00FFFF) + 0x00110000;
					GPIO_PORTC_DEN_R |= 0x30;
					clear_bit(GPIO_PORTC_DIR_R,4);
					set_bit(GPIO_PORTC_DIR_R,5);
					GPIO_PORTC_AMSEL_R &= ~(0x30);
					UART4_CTL_R &= ~(0x0001);
					UART4_IBRD_R = (uint32_t)( UART_CLOCK / (BaudRate * 16));
					UART4_FBRD_R = (uint32_t)(((UART_CLOCK / (BaudRate * 16.0))-((uint32_t)(UART_CLOCK / (BaudRate * 16))))*64+0.5);
					UART4_LCRH_R |=0x10;
					if(DataBits==DATA_5bits){
						UART4_LCRH_R &= ~(0x60);                    //clear bit 5,6
					}
					else if(DataBits==DATA_6bits){
						UART4_LCRH_R &= ~(0x40);                    //clear bit 6
						UART4_LCRH_R |=  (0x20);                    //set bit 5
					}
					else if(DataBits==DATA_7bits){
						UART4_LCRH_R &= ~(0x20);	                //clear bit 5
						UART4_LCRH_R |=  (0x40);	                //set bit 6
					}
					else if(DataBits==DATA_8bits){
						UART4_LCRH_R |=  (0x60);	                //set bit 5,6
					}
					//parity 0-->none  1-->odd  2-->even
					if(Parity==UART_PARITY_NONE)
						clear_bit(UART4_LCRH_R,1);
					else if(Parity==UART_PARITY_ODD){             	//odd
						set_bit(UART4_LCRH_R,1);
						clear_bit(UART4_LCRH_R,2);
					}
					else if(Parity==UART_PARITY_EVEN){				//even
						set_bit(UART4_LCRH_R,1);
						set_bit(UART4_LCRH_R,2);
					}
					//stop bits
					if(StopBits==STOP_1bit)
						clear_bit(UART4_LCRH_R,3);
					else if(StopBits==STOP_2bit)
						set_bit(UART4_LCRH_R,3);
					UART4_CTL_R |= 0x0301;
					break;
///////////////////////////////////////// UART5 /////////////////////////////////////////
		case UART5:
					SYSCTL_RCGCGPIO_R |=0x10;
					while(!(SYSCTL_PRGPIO_R & 0x10));
					GPIO_PORTE_AFSEL_R |= 0x30;
					GPIO_PORTE_PCTL_R =(GPIO_PORTA_PCTL_R&0xFF00FFFF) + 0x00110000;
					GPIO_PORTE_DEN_R |= 0x30;
					clear_bit(GPIO_PORTE_DIR_R,4);
					set_bit(GPIO_PORTE_DIR_R,5);
					GPIO_PORTE_AMSEL_R &= ~(0x30);
					UART5_CTL_R &= ~(0x0001);
					UART5_IBRD_R = (uint32_t)( UART_CLOCK / (BaudRate * 16));
					UART5_FBRD_R = (uint32_t)(((UART_CLOCK / (BaudRate * 16.0))-((uint32_t)(UART_CLOCK / (BaudRate * 16))))*64+0.5);
					UART5_LCRH_R |=0x10;
					if(DataBits==DATA_5bits){
						UART5_LCRH_R &= ~(0x60);  //clear bit 5,6
					}
					else if(DataBits==DATA_6bits){
						UART5_LCRH_R &= ~(0x40);  //clear bit 6
						UART5_LCRH_R |=  (0x20);  //set bit 5
					}
					else if(DataBits==DATA_7bits){
						UART5_LCRH_R &= ~(0x20);	//clear bit 5
						UART5_LCRH_R |=  (0x40);	//set bit 6
					}
					else if(DataBits==DATA_8bits){
						UART5_LCRH_R |=  (0x60);	//set bit 5,6
					}
					//parity 0-->none  1-->odd  2-->even
					if(Parity==UART_PARITY_NONE)
						clear_bit(UART5_LCRH_R,1);
					else if(Parity==UART_PARITY_ODD){             	//odd
						set_bit(UART5_LCRH_R,1);
						clear_bit(UART5_LCRH_R,2);
					}
					else if(Parity==UART_PARITY_EVEN){								//even
						set_bit(UART5_LCRH_R,1);
						set_bit(UART5_LCRH_R,2);
					}
					//stop bits
					if(StopBits==STOP_1bit)
						clear_bit(UART5_LCRH_R,3);
					else if(StopBits==STOP_2bit)
						set_bit(UART5_LCRH_R,3);
					UART5_CTL_R |= 0x0301;
					break;
///////////////////////////////////////// UART6 /////////////////////////////////////////
		case UART6:
					SYSCTL_RCGCGPIO_R |=0x08;
					while(!(SYSCTL_PRGPIO_R & 0x08));
					GPIO_PORTD_AFSEL_R |= 0x30;
					GPIO_PORTD_PCTL_R =(GPIO_PORTA_PCTL_R&0xFF00FFFF) + 0x00110000;
					GPIO_PORTD_DEN_R |= 0x30;
					clear_bit(GPIO_PORTE_DIR_R,4);
					set_bit(GPIO_PORTE_DIR_R,5);
					GPIO_PORTD_AMSEL_R &= ~(0x30);
					UART6_CTL_R &= ~(0x0001);
					UART6_IBRD_R = (uint32_t)( UART_CLOCK / (BaudRate * 16));
					UART6_FBRD_R = (uint32_t)(((UART_CLOCK / (BaudRate * 16.0))-((uint32_t)(UART_CLOCK / (BaudRate * 16))))*64+0.5);
					UART6_LCRH_R |=0x10;
					if(DataBits==DATA_5bits){
						UART6_LCRH_R &= ~(0x60);  //clear bit 5,6
					}
					else if(DataBits==DATA_6bits){
						UART6_LCRH_R &= ~(0x40);  //clear bit 6
						UART6_LCRH_R |=  (0x20);  //set bit 5
					}
					else if(DataBits==DATA_7bits){
						UART6_LCRH_R &= ~(0x20);	//clear bit 5
						UART6_LCRH_R |=  (0x40);	//set bit 6
					}
					else if(DataBits==DATA_8bits){
						UART6_LCRH_R |=  (0x60);	//set bit 5,6
					}
					//parity 0-->none  1-->odd  2-->even
					if(Parity==UART_PARITY_NONE)
						clear_bit(UART6_LCRH_R,1);
					else if(Parity==UART_PARITY_ODD){             	//odd
						set_bit(UART6_LCRH_R,1);
						clear_bit(UART6_LCRH_R,2);
					}
					else if(Parity==UART_PARITY_EVEN){								//even
						set_bit(UART6_LCRH_R,1);
						set_bit(UART6_LCRH_R,2);
					}
					//stop bits
					if(StopBits==STOP_1bit)
						clear_bit(UART6_LCRH_R,3);
					else if(StopBits==STOP_2bit)
						set_bit(UART6_LCRH_R,3);
					UART6_CTL_R |= 0x0301;
					break;
///////////////////////////////////////// UART7 /////////////////////////////////////////
		case UART7:
					SYSCTL_RCGCGPIO_R |=0x10;
					while(!(SYSCTL_PRGPIO_R & 0x10));
					GPIO_PORTE_AFSEL_R |= 0x03;
					GPIO_PORTE_PCTL_R =(GPIO_PORTA_PCTL_R&0xffffff00) + 0x00000011;
					GPIO_PORTE_DEN_R |= 0x03;
					clear_bit(GPIO_PORTE_DIR_R,0);
					set_bit(GPIO_PORTE_DIR_R,1);
					GPIO_PORTE_AMSEL_R &= ~(0x03);
					UART7_CTL_R &= ~(0x0001);
					UART7_IBRD_R = (uint32_t)( UART_CLOCK / (BaudRate * 16));
					UART7_FBRD_R = (uint32_t)(((UART_CLOCK / (BaudRate * 16.0))-((uint32_t)(UART_CLOCK / (BaudRate * 16))))*64+0.5);
					UART7_LCRH_R |=0x10;
					if(DataBits==DATA_5bits){
						UART7_LCRH_R &= ~(0x60);  //clear bit 5,6
					}
					else if(DataBits==DATA_6bits){
						UART7_LCRH_R &= ~(0x40);  //clear bit 6
						UART7_LCRH_R |=  (0x20);  //set bit 5
					}
					else if(DataBits==DATA_7bits){
						UART7_LCRH_R &= ~(0x20);	//clear bit 5
						UART7_LCRH_R |=  (0x40);	//set bit 6
					}
					else if(DataBits==DATA_8bits){
						UART7_LCRH_R |=  (0x60);	//set bit 5,6
					}
					//parity 0-->none  1-->odd  2-->even
					if(Parity==UART_PARITY_NONE)
						clear_bit(UART7_LCRH_R,1);
					else if(Parity==UART_PARITY_ODD){             	//odd
						set_bit(UART7_LCRH_R,1);
						clear_bit(UART7_LCRH_R,2);
					}
					else if(Parity==UART_PARITY_EVEN){								//even
						set_bit(UART7_LCRH_R,1);
						set_bit(UART7_LCRH_R,2);
					}
					//stop bits
					if(StopBits==STOP_1bit)
						clear_bit(UART7_LCRH_R,3);
					else if(StopBits==STOP_2bit)
						set_bit(UART7_LCRH_R,3);
					UART7_CTL_R |= 0x0301;
					break;					
        }

}
/////////////////////////////////////////  	END  /////////////////////////////////////////////

void set_bit(uint32_t Register ,uint8_t Bit_No){
	Register |=(1<<Bit_No);
}

void clear_bit(uint32_t Register ,uint8_t Bit_No){
    Register &= ~(1<<Bit_No);
}
