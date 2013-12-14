/*
 * robot_motion.c
 *
 *  Created on: Dec 9, 2013
 *      Author: C14James.Dunn
 */

#include "sensor.h"
#include <msp430.h>

#define LEFT_THRESHOLD	0x2FF
#define RIGHT_THRESHOLD 0x3FE
#define FRONT_THRESHOLD	0x2FF
#define TRUE	1
#define FALSE	0

unsigned int getLeftSensor(void)
{
	ADC10CTL0 = ~ENC;												// Disabled to write to registers
	ADC10CTL0 = ADC10SHT_3|ADC10ON|ADC10IE;

	ADC10CTL1 &= ~(INCH0|INCH1|INCH2|INCH3);						// Select input channel
	ADC10CTL1 |= INCH_3;

	ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;
	ADC10CTL1 |= ADC10DIV0|ADC10DIV1|ADC10DIV2;						// Divides clock to slow down sampling rate

	ADC10AE0 &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	ADC10AE0 |= BIT3;

	ADC10CTL0 |= ENC + ADC10SC;             						// Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        						// LPM0, ADC10_ISR will force exit

    return ADC10MEM;
}

unsigned int getFrontSensor(void)
{
	ADC10CTL0 = ~ENC;												// Disabled to write to registers
	ADC10CTL0 = ADC10SHT_3|ADC10ON|ADC10IE;

	ADC10CTL1 &= ~(INCH0|INCH1|INCH2|INCH3);						// Select input channel
	ADC10CTL1 |= INCH_4;

	ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;
	ADC10CTL1 |= ADC10DIV0|ADC10DIV1|ADC10DIV2;						// Divides clock to slow down sampling rate

	ADC10AE0 &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	ADC10AE0 |= BIT4;

	ADC10CTL0 |= ENC + ADC10SC;             						// Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        						// LPM0, ADC10_ISR will force exit

    return ADC10MEM;
}

unsigned int getRightSensor(void)
{
	ADC10CTL0 = ~ENC;												// Disabled to write to registers
	ADC10CTL0 = ADC10SHT_3|ADC10ON|ADC10IE;

	ADC10CTL1 &= ~(INCH0|INCH1|INCH2|INCH3);						// Select input channel
	ADC10CTL1 |= INCH_5;

	ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;
	ADC10CTL1 |= ADC10DIV0|ADC10DIV1|ADC10DIV2;						// Divides clock to slow down sampling rate

	ADC10AE0 &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	ADC10AE0 |= BIT5;

	ADC10CTL0 |= ENC + ADC10SC;             						// Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        						// LPM0, ADC10_ISR will force exit

    return ADC10MEM;
}

char wallFrontDetected(void)
{
	if(getFrontSensor() >= FRONT_THRESHOLD)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

char wallLeftDetected(void)
{
	if(getLeftSensor() >= LEFT_THRESHOLD)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

char wallRightDetected(void)
{
	if(getRightSensor() >= RIGHT_THRESHOLD)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        					// Clear CPUOFF bit from 0(SR)
}
