#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "GPS.h"
#include <math.h>


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
