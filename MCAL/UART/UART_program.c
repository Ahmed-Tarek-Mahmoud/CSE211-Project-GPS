#include <stdint.h>

#include "UART_interface.h"

#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\tm4c123gh6pm.h"


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
					GPIO_PORTC_PCTL_R =(GPIO_PORTC_PCTL_R&0x00FFFFFF) + 0x11000000;
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
			    SYSCTL_RCGCUART_R |= 0x20;  // Enable UART5 clock
		      uint8_t x; 
					SYSCTL_RCGCGPIO_R |=0x10;
					while(!(SYSCTL_PRGPIO_R & 0x10));
					GPIO_PORTE_AFSEL_R |= 0x30;
					GPIO_PORTE_PCTL_R =(GPIO_PORTE_PCTL_R&0xFF00FFFF) + 0x00110000;
					GPIO_PORTE_DEN_R |= 0x30;
					clear_bit(GPIO_PORTE_DIR_R,4);
					set_bit(GPIO_PORTE_DIR_R,5);
					GPIO_PORTE_AMSEL_R &= ~(0x30);
					UART5_CTL_R &= ~(0x0001);
					UART5_IBRD_R = 104;
					UART5_FBRD_R = 11;
					UART5_LCRH_R |=0x10; // FIFO
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
					GPIO_PORTD_PCTL_R =(GPIO_PORTD_PCTL_R&0xFF00FFFF) + 0x00110000;
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
			    SYSCTL_RCGCUART_R |= 0x80;
					SYSCTL_RCGCGPIO_R |=0x10;
		      uint8_t xx;
					while(!(SYSCTL_PRGPIO_R & 0x10));
					GPIO_PORTE_AFSEL_R |= 0x03;
					GPIO_PORTE_PCTL_R =(GPIO_PORTE_PCTL_R&0xffffff00) + 0x00000011;
					GPIO_PORTE_DEN_R |= 0x03;
					clear_bit(GPIO_PORTE_DIR_R,0);
					set_bit(GPIO_PORTE_DIR_R,1);
					GPIO_PORTE_AMSEL_R &= ~(0x03);
					UART7_CTL_R &= ~(0x0001);
					UART7_IBRD_R = 104;
					UART7_FBRD_R = 11;
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



void UART_sendChar(uint8_t uartNo,char data){
	// char out
	switch (uartNo)
	{
	case UART0:
		while((UART0_FR_R & 0x0020) != 0);	
	    UART0_DR_R = data;
		break;
	case UART1:
		while((UART1_FR_R & 0x0020) != 0);	
	    UART1_DR_R = data;
		break;
	case UART2:
		while((UART2_FR_R & 0x0020) != 0);	
	    UART2_DR_R = data;
		break;
	case UART3:
		while((UART3_FR_R & 0x0020) != 0);	
	    UART3_DR_R = data;
		break;
	case UART4:
		while((UART4_FR_R & 0x0020) != 0);	
	    UART4_DR_R = data;
		break;
	case UART5:
		while((UART5_FR_R & 0x0020) != 0);	
	    UART5_DR_R = data;
		break;
	case UART6:
		while((UART6_FR_R & 0x0020) != 0);	
	    UART6_DR_R = data;
		break;
	case UART7:
		while((UART7_FR_R & 0x0020) != 0);	
	    UART7_DR_R = data;
		break;

	default:
	    // error 
		break;
	}
	
}



char UART_receiveChar(uint8_t uartNo){
	// char in
	
    switch (uartNo)
	{
	case UART0:
		while((UART0_FR_R & 0x0010) != 0);
	    return (char) UART0_DR_R;
		
	case UART1:
		while((UART1_FR_R & 0x0010) != 0);
	    return (char) UART1_DR_R;
		
	case UART2:
		while((UART2_FR_R & 0x0010) != 0);
	    return (char) UART2_DR_R;
		
	case UART3:
		while((UART3_FR_R & 0x0010) != 0);
	    return (char) UART3_DR_R;
		
	case UART4:
		while((UART4_FR_R & 0x0010) != 0);
	    return (char) UART4_DR_R;
		
	case UART5:
		while((UART5_FR_R & 0x0010) != 0);
	    return (char) UART5_DR_R;
		
	case UART6:
		while((UART6_FR_R & 0x0010) != 0);
	    return (char) UART6_DR_R;
		
	case UART7:
		while((UART7_FR_R & 0x0010) != 0);
	    return (char) UART7_DR_R;

	default:
	    // error
    return '0';	
	}

}


void UART_getString(char *cmd, uint32_t len,uint8_t uartNo){
	char character;
	int i;
	for(i = 0; i<len ;i++){
		character = UART_receiveChar(uartNo);
		
	if(character != 0x0D){
			UART_sendChar(uartNo,character);
			cmd[i] = character;
		if(character == 0x2A){
			break;
		}
		}
		else if(character == 0x0D) {
			UART_sendChar(uartNo , character);
			cmd[i] = character;
			break;
		}
	}
}

void UART_OutString(char *ptr,uint8_t uartNo){
	while(*ptr){
		UART_sendChar(uartNo , *ptr);
		ptr++;
	}
}

/////////////////////////////////////////  	END  /////////////////////////////////////////////


