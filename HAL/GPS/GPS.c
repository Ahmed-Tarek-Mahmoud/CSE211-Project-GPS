#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "GPS.h"
#include <math.h>

<<<<<<< HEAD
#include "GPS.h"

uint8_t GPS_ReceiveLog(float *LatReturn, float *LongReturn , float *VelocityReturn)
{
    
    char ReqLog [] = "$GPRMC,";
    char ReceivedData [80]; //Array to receive data from gps 

    int8_t i = 0;

    //checks if the recieved log is the required log 

    do { 
        if (UART_GetChar() == ReqLog[i]) 
        {
            i++;
        }
        else 
        {
            i=0;
        }
    }while (i!=7); 

    i=0; //sets i back to zero for further use

    //If the required log is sent store the recieved char into the array

    while (UART_GetChar() != '*')
    {
        ReceivedData[i] = UART_GetChar();
        i++;
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

    while (token != NULL)
    {
        storedData[i++] = token; //stored data is an array of strings
        token = strtok(NULL,delimiter);
    }

    if (strcmp(storedData[1] , "A") == 0)
    {

        if (strcmp(storedData[3] , "N") == 0)
        {
            *LatReturn = stof(storedData[2]);
        }
        else if (strcmp(storedData[3] , "S") == 0)
        {
            *LatReturn = -stof(storedData[2]);
        }


        if (strcmp(storedData[5] , "E") == 0)
        {
            *LongReturn = stof(storedData[4]);
        }
        else if (strcmp(storedData[5] , "W") == 0)
        {
            *LongReturn = -stof(storedData[4]);
        }

        *VelocityReturn = stof(storedData[6]);

        return Valid;
    }
    else if (strcmp(storedData[1] , "V") == 0)
    {
        return NotValid;
    }

    //return NotValid by default 
    return NotValid;

}
=======

float GPS_ToDegree(float decimal){
    int degree = (int)decimal / 100;
    float minutes = decimal - (float)degree*100;
    return ( degree + (minutes/60) );
}

//GPS_ToDegree return value will be param here
float GPS_ToRadian(float degree){
    return ( degree * (PI /180) );
}

float GPS_CalcDist(float LatA , float LongA , float LatB , float LongB){
    //Rad Angles
    float RadLatA = GPS_ToRadian( GPS_ToDegree(LatA) );
    float RadLongA = GPS_ToRadian( GPS_ToDegree(LongA) );
    float RadLatB = GPS_ToRadian( GPS_ToDegree(LatB) );
    float RadLongB = GPS_ToRadian( GPS_ToDegree(LongB) );

    //Difference
    float LatDiff = RadLatB - RadLatA ; 
    float LongDiff = RadLongB - RadLongA ; 

    //Distance Calculation (Haversine Formula)
    float  a = pow(sin(LatDiff/2) , 2) + ( cos(RadLatA) * cos(RadLatB) * pow(sin(LongDiff/2) , 2) );
    double c = 2 * atan2(sqrt(a) , sqrt(1-a));
    return ( EarthRadius * c );
}
>>>>>>> dbe6f7bc79ad4c97d99583ba46c278b7beda9c85
