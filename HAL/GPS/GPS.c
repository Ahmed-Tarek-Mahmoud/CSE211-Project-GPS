#include <stdint.h>

#include "tm4c123gh6pm.h"

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