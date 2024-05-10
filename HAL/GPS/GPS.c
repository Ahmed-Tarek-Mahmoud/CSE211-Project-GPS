#include <stdint.h>
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\tm4c123gh6pm.h"
#include "GPS.h"
#include <math.h>
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\UART\UART_interface.h"
#include "stdlib.h"
#include "C:\Users\Ahmed Tarek\Desktop\Embedded labs\Project v1\MCAL\STK\STK_interface.h"

int EarthRadius = 6371000;

uint8_t GPS_ReceiveLog(float *LatReturn, float *LongReturn , float *VelocityReturn,uint8_t uartNo)
{
    
    char ReqLog [] = "$GPRMC,";
    char ReceivedData [] ="$GPRMC,030428.00,A,2232,N,11404,E,1,,070314,,,A*" ; //Array to receive data from gps 
      //memset(ReceivedData,0,80);
    int8_t i = 0;

    //checks if the recieved log is the required log 
/*
    do { 
        if (UART_receiveChar(uartNo) == ReqLog[i]) 
        {
            i++;
        }
        else 
        {
            i=0;
        }
				UART_OutString("do1\n",UART7);
    }while (i!=7); 
*/
    i=0; //sets i back to zero for further use

    //If the required log is sent store the recieved char into the array
		
	//	ReceivedData[0] = UART_receiveChar(uartNo);

    while (ReceivedData[i] != '*')
    {
			  i++;
       // ReceivedData[i] = UART_receiveChar(uartNo);
			UART_OutString("do2\n",UART7);
			STK_Delay(1000);
       
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
    token = strtok(NULL,delimiter);
    while (token != NULL)
    {
        storedData[i++] = token; //stored data is an array of strings
        token = strtok(NULL,delimiter);
			UART_OutString("do3\n",UART7);
			STK_Delay(1000);
    }

    if (strcmp(storedData[1],"A")==0)
    {

        if (strcmp(storedData[3],"N")==0)
        {
            *LatReturn = atof(storedData[2]);
        }
        else if (strcmp(storedData[3],"S")==0)
        {
            *LatReturn = -atof(storedData[2]);
        }


        if (strcmp(storedData[5],"E")==0)
        {
            *LongReturn = atof(storedData[4]);
        }
        else if (strcmp(storedData[5],"W")==0)
        {
            *LongReturn = -atof(storedData[4]);
        }

        *VelocityReturn = atof(storedData[6]);

        return Valid;
    }
    else if (strcmp(storedData[1],"V")==0)
    {
        return NotValid;
    }

    //return NotValid by default 
    return NotValid;

}

float GPS_ToDegree(float decimal){
    int degree = (int)decimal / 100;
    float minutes = decimal - (float)degree*100;
    return ( degree + (minutes/60) );
}

float GPS_ToRadian(float degree){
    return ( degree * (PI /180) );
}

float GPS_CalcDist(float LatA , float LongA , float LatB , float LongB){
    //Rad Angles
    float RadLatA = GPS_ToRadian( LatA );
    float RadLongA = GPS_ToRadian( LongA );
    float RadLatB = GPS_ToRadian( LatB );
    float RadLongB = GPS_ToRadian( LongB );

    //Difference
    // float LatDiff = RadLatB - RadLatA ; 
    // float LongDiff = RadLongB - RadLongA ; 

    //Distance Calculation (Haversine Formula)
    float  a = pow(sin((RadLatB - RadLatA)/2) , 2) + ( cos(RadLatA) * cos(RadLatB) * pow(sin((RadLongB - RadLongA)/2) , 2) );
    double c = 2 * atan2(sqrt(a) , sqrt(1-a));
    return ( EarthRadius * c );
}
