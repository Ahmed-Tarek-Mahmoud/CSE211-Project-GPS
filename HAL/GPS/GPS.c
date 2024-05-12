/*************< System *******************************/
#include "stdint.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\tm4c123gh6pm.h"
#include "stdbool.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
/*************< System *******************************/

#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Milestone 1\TivaWare_C_Series-2.2.0.295\driverlib\eeprom.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/flash.h"
#include "driverlib/eeprom.h"
#include "driverlib/fpu.h"


#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\GPIO\GPIO_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\UART\UART_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\STK\STK_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\HAL\LCD\LCD_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\HAL\GPS\GPS.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\NVIC\NVIC.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\HAL\LED\LED_interface.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\HAL\LCD\LCD_config.h"




float EarthRadius = 6371;
float ATOF(const char *str);
float BASE_10_POWER(char exp);
uint8_t GPS_ReceiveLog(float *LatReturn, float *LongReturn , float *VelocityReturn,uint8_t uartNo)
{
	
    
    char ReqLog [] = "$GPRMC,";
    char  ReceivedData [80]; //Array to receive data from gps 
    memset(ReceivedData,0,80);
    int8_t i = 0;

    //checks if the recieved log is the required log 

    do { 
			char c= UART_receiveChar(UART5);
        if (c == ReqLog[i]) 
        {
            i++;
					UART_OutString("do1\n",UART7);
					
        }
        else 
        {
					i=0;
					//UART_OutString("do2\n",UART7);
        }
    }while (i!=7); 

    i=0; //sets i back to zero for further use

    //If the required log is sent store the recieved char into the array
		
		ReceivedData[0] = UART_receiveChar(UART5);

    while (ReceivedData[i] != '*')
    {
			i++;
      ReceivedData[i] = UART_receiveChar(UART5);
    }

    return GPS_LogParsing(ReceivedData, LatReturn, LongReturn ,VelocityReturn);
    
}

uint8_t GPS_LogParsing(char *RecievedSentence,float *LatReturn, float *LongReturn , float *VelocityReturn)
{
    int8_t i =0;
    char *storedData[12]; //Array to store data from gps 
    char delimiter [] = ","; //Delimiter for tokens
    char *token; //Array to store tokens 

    token = strtok(RecievedSentence,delimiter);
    //token = strtok(NULL,delimiter);
    while (token != NULL)
    {
      storedData[i++] = token; //stored data is an array of strings
      token = strtok(NULL,delimiter);
			//UART_OutString("do3\n",UART7);
    }

    if (storedData[1][0]=='A')
    {
			UART_OutString("GOOD",UART7);

        if (storedData[3][0]=='N')
        {
					 *LatReturn = ATOF(storedData[2]);
        }
        else if(storedData[3][0]=='S')
        {
            *LatReturn = -1 * ATOF(storedData[2]);
        }


        if (storedData[5][0]=='E')
        {
            *LongReturn = ATOF(storedData[4]);
        }
        else if (storedData[5][0]=='W')
        {
            *LongReturn = -1 * ATOF(storedData[4]);
        }

        *VelocityReturn = ATOF(storedData[6]);
				//memset(storedData,0,12);
        return Valid;
    }
    else if (storedData[1][0]=='V')
    {
		 UART_OutString("BAD",UART7);
			//memset(storedData,0,12);
        return NotValid;
    }
		UART_OutString("NEITHER   ",UART7);
			UART_OutString(storedData[0],UART7);
		UART_OutString(storedData[1],UART7);
			UART_OutString(storedData[2],UART7);
	//	memset(storedData,0,12);
    //return NotValid by default 
    return NotValid;

}

float GPS_ToDegree(float decimal){
    int degree = decimal / 100.0;
    float minutes = (decimal - (float)degree*100) / 60; // Calculate minutes correctly
    float seconds = (decimal - (int)decimal) * 60; // Calculate seconds correctly

    return (degree + minutes);
}

float GPS_ToRadian(float degree){
	
		UART_OutString("hhhh\n",UART7);

    return ( degree * (PI /180.0) );
}

float GPS_CalcDist(float LatA , float LongA , float LatB , float LongB){
		  
    //Rad Angles
    float RadLatA ;
		RadLatA =  GPS_ToRadian( (LatA) );
    float RadLongA;
	  RadLongA =   GPS_ToRadian( (LongA) );
    float RadLatB ;
		RadLatB = GPS_ToRadian( (LatB) );
    float RadLongB;
		RadLongB =  GPS_ToRadian( (LongB) );
    //Difference
    float LatDiff = fabs(RadLatB - RadLatA) ; 
     float LongDiff = fabs(RadLongB - RadLongA) ; 

    //Distance Calculation (Haversine Formula)
	char aaa[10] = {0};

    float  a = pow(sin((LatDiff)/2) , 2) + (cos(RadLatA) * cos(RadLatB)) * pow(sin((LongDiff)/2) , 2);
	
    float c = 2.0 * atan2(sqrt(a) , sqrt(1-a));
		
		float dd = (EarthRadius * c);

		UART_OutString("\nhamada\n",UART7);
    return dd;
}


float ATOF(const char *str){

    float result = 0;
    bool decimal_found = false;
    int decimal_position = 0;

    while (*str != '\0') {
        if (*str == '.') {
            decimal_found = true;
            str++;
            continue;
        }
        if (!isdigit(*str)) {
            // Handle invalid input
            return 0.0;
        }
        if (decimal_found) {
            result += (*str - 48) / (float)(10 * (++decimal_position));
        } else {
					  char ss = *str;
            result = result * 10 ;
					  result = result + (ss - 48);
        }
        str++;
    }

    return result;
}