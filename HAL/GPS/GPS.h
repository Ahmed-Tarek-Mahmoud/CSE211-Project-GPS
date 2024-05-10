#ifndef GPS_INTERFACE
#define GPS_INTERFACE

#include <stdint.h>
#include <string.h>


/*******************< Macros ********************/
#define NotValid 0 // Not Valid log
#define Valid 1 // Valid log

#define PI 3.14159265358979323846

/*******************< Functions *****************/
/**
 * @brief This function is responsible for receiving the log from the GPS using UART protocol
 *        The only log I am intrested in is the one starting with "$GPRMC".
 *        after recieving the correct log, call the parsing function.
 *        return current lat ,long and velocity in the passed arguments.
*/
uint8_t GPS_ReceiveLog(float *LatReturn, float *LongReturn , float *VelocityReturn,uint8_t uartNo);

/**
 * @brief This function is responsible for parsing the log from the GPS using UART protocol
 *        You are supposed to store the data in a 2D charcter array 12 rows (fields) and 15 columns (String width)
 *        return current lat ,long and velocity in the passed arguments.
*/
uint8_t GPS_LogParsing(char *RecievedSentence,float *LatReturn, float *LongReturn , float *VelocityReturn);


/**
 * @brief This function converts the passed decimal into degree
*/
float GPS_ToDegree(float decimal);


/**
 * @brief This function converts the passed degree into radian
*/
float GPS_ToRadian(float degree);


/**
 * @brief This function calculates the distance using harvesine law (Path on a sphere)
 * 
 * @param LatA  latitude of point A in radians
 * 
 * @param LongA longitude of point A in radians
 * 
 * @param LatB  latitude of point B in radians
 * 
 * @param LatA  latitude of point B in radians
*/
float GPS_CalcDist(float LatA , float LongA , float LatB , float LongB);

#endif
