/**
 * @brief Base 64 encoder/decoder library
 * @author Michael Burmeister
 * @date March 13, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "Base64.h"

char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

int Base64_Encode(uint8_t *from, char *to, int len)
{
    int position;
    int v, r, t;

        position = 0;
    r = 0;
    v = 0;
    t = 0;
    for (int i=0;i<len;i++)
    {
        if (position == 0)
        {
            r = from[i] &0x03;
            v = from[i] >> 2;
        }
        if (position == 1)
        {
            r = r << 4;
            v = r | (from[i] >> 4);
            r = from[i] & 0x0f;
        }
        if (position == 2)
        {
            r = r << 2;
            v = r | (from[i] >> 6);
            r = from[i] & 0x3f;
    	}
    	to[t++] = base64[v];
        if (position == 2)
        	to[t++] = base64[r];
        position++;
        if (position > 2)
        	position = 0;
    }
    if (position > 0)
    {
        if (position == 1)
        {
            r = r << 4;
            to[t++] = base64[r];
            to[t++] = base64[64];
            to[t++] = base64[64];
        }
        if (position == 2)
        {
            r = r << 2;
            to[t++] = base64[r];
            to[t++] = base64[64];
        }
	}
	to[t++] = 0;
    return t;
}

int Base64_Decode(char *from, uint8_t *to)
{
    int position;
    int v, r, t;
    
    position = 0;
    r = 0;
    t = 0;
    v = (char*)strchr(base64, from[0]) - base64;
    for (int i=1;i<strlen(from);i++)
    {
        if (position == 0)
        {
            r = (char*)strchr(base64, from[i]) - base64;
            to[t++] = (v << 2) | (r >> 4);
            r = r & 0x0f;
        }
        if (position == 1)
        {
            v = (char*)strchr(base64, from[i]) - base64;
            if (v > 63)
            {
                to[t++] = r << 4;
                break;
   			}
   			to[t++] = (r << 4) | (v >> 2);
   			r = v & 0x03;
     	}
        if (position == 2)
        {
            v = (char*)strchr(base64, from[i]) - base64;
            if (v > 63)
            {
                to[t++] = r << 6;
                break;
            }
            to[t++] = (r << 6) | v;
            i++;
            v = (char*)strchr(base64, from[i]) - base64;
        }
        position++;
        if (position > 2)
        	position = 0;
    }
    to[t++] = 0;
	return t;
}