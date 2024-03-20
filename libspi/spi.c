/**
 * @brief SPI Driver
 * @author Michael Burmeister
 * @date March 22, 2022
 * @version 1.0
 * 
*/

#include "spi.h"
#include <stdio.h>
#include <stdlib.h>
#include <propeller.h>


spi_t *Spi_Init(char mosi, char miso, char clk, char order, char wait)
{
    spi_t *x = malloc(sizeof(spi_t));
    x->mosi = mosi;
    x->miso = miso;
    x->clk = clk;
    x->order = order;
    if (wait == 0)
        wait = 2;
    x->wait = wait;

    _pinl(clk);
    _dirl(miso);
    _dirh(mosi);

    return x;
}

int Spi_In(spi_t *spi, char bits)
{
    int i;
    unsigned data = 0;
    int wt = spi->wait;
    int bt = bits;
    int clk = spi->clk;
    int pin = spi->miso;

    i = 32 - bits;

    if (spi->order == 0)
    {
        __asm volatile {
            drvl clk
        l1  testp pin wc
            rcl data, #1
            drvh clk
            drvl clk
            waitx wt
            djnz bt, #l1
        }
    }
    if (spi->order == 1)
    {
        __asm volatile {
            drvl clk
        l2  testp pin wc
            rcr data, #1
            drvh clk
            drvl clk
            waitx wt
            djnz bt, #l2
            shr data, i
        }
    }

    return data;
}

void Spi_Out(spi_t *spi, char bits, unsigned int data)
{
    int i;
    int wt = spi->wait;
    int bt = bits;
    int clk = spi->clk;
    int pin = spi->mosi;

    i = 32 - bits;

    if (spi->order == 0)
    {
        __asm volatile {
            drvl clk
            shl data, i
        l3  rcl data, #1 wc
            if_c drvh pin
            if_nc drvl pin
            waitx wt
            drvh clk
            waitx wt
            drvl clk
            djnz bt, #l3
        }
    }
    if (spi->order == 1)
    {
        __asm volatile {
            drvl clk
        l4  rcr data, #1 wc
            if_c drvh pin
            if_nc drvl pin
            drvh clk
            waitx wt
            drvl clk
            waitx wt
            djnz bt, #l4
        }
    }
}
