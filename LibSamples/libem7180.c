/**
 * @brief Library for EM7180 sensor fusion hub
 * @author Michael Burmeister
 * @date Feburary 9, 2021
 * @version 1.0
 * 
*/

#include <math.h>
#include <stdio.h>
#include <propeller.h>
#include "em7180.h"

#define EMCLK 36
#define EMSDA 37

short v[4];
float Q[4];
float A12, A22, A31, A32, A33;
float Yaw, Pitch, Roll;


int main(int argc, char** argv)
{
    int i;
    
    i = Em7180_open(EMCLK, EMSDA);
    
    printf("EM7180: %x\n", i);
    
    i = Em7180_sensors();
    
    printf("Sensors: %x\n", i);
    
    i = Em7180_status();
    
    printf("Status: %x\n", i);
    
    Em7180_loadfw();
    Em7180_setupdefault();
    
    
    while (1)
    {
        i = Em7180_status();
        if ((i & 0x02) != 0)
        {
            printf("Status: %x\n", i);
            if (i & 0x11)
            	printf("Magnetometer failure.\n");
            if (i & 0x12)
            	printf("Accelerometer failure.\n");
            if (i & 0x14)
            	printf("Gyro failure.\n");
            if (i & 0x21)
            	printf("Magnetometer initialization failure.\n");
            if (i & 0x22)
            	printf("Accelerometer initialization failure.\n");
            if (i & 0x24)
            	printf("Gyro initialization failure.\n");
            if (i & 0x30)
            	printf("Math error.\n");
            if (i & 0x80)
            	printf("Invalid sample rate.\n");
            i = 0;
        }
        
        if (i & 0x10)
        	Em7180_readaccelerometer(v);
        if (i & 0x20)
        	Em7180_readgyro(v);
        if (i & 0x08)
        	Em7180_readmagnetometer(v);
        if (i & 0x04) //04
        {
            Em7180_readquaternions(Q);
            //printf("Quat: %f, %f, %f, %f\n", Q[0], Q[1], Q[2], Q[3]);
            //printf("%f %f %f %f\n", Q[0], Q[1], Q[2], Q[3]);
            A12 =   2.0f * (Q[1] * Q[2] + Q[0] * Q[3]);
            A22 =   Q[0] * Q[0] + Q[1] * Q[1] - Q[2] * Q[2] - Q[3] * Q[3];
            A31 =   2.0f * (Q[0] * Q[1] + Q[2] * Q[3]);
            A32 =   2.0f * (Q[1] * Q[3] - Q[0] * Q[2]);
            A33 =   Q[0] * Q[0] - Q[1] * Q[1] - Q[2] * Q[2] + Q[3] * Q[3];
            Pitch = -asinf(A32);
            Roll  = atan2f(A31, A33);
            Yaw   = atan2f(A12, A22);
            Pitch *= 180.0f / PI;
            Yaw   *= 180.0f / PI;
            if (Yaw < 0)
            	Yaw   += 360.0f ;
            Roll  *= 180.0f / PI;
            printf("%3.0f %3.0f %3.0f\n", Yaw, Pitch, Roll);
        }
        
        if (i & 0x40)
        {
            Em7180_readbarometer();
            Em7180_readtemperature();
        }
     
        _waitms(1000);
	}
}
