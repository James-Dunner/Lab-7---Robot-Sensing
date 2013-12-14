/*
 * example.c
 *
 *  Created on: Dec 14, 2013
 *      Author: C14James.Dunn
 */

#include <msp430.h>
#include "sensor.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;									// Stop watchdog timer

    P1DIR |= BIT0|BIT6;											// Sets LED1 and LED2 to ouput

    while(1)
    {
    	if(wallLeftDetected() == TRUE)
    	{
    		P1OUT |= BIT0;
    	}
    	else
    	{
    		P1OUT &= ~BIT0;
    	}

    	if(wallFrontDetected() == TRUE)
    	{
    		P1OUT |= BIT6;
    	}
    	else
    	{
    		P1OUT &= ~BIT6;
    	}
    }
