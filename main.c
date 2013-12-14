#include <msp430.h>
#include "sensor.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;									// Stop watchdog timer
	
    ADC10CTL0 = ADC10SHT_3|ADC10ON|ADC10IE;
    ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;
    ADC10CTL1 |= ADC10DIV0|ADC10DIV1|ADC10DIV2;

    ADC10AE0 &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
    ADC10AE0 |= BIT4|BIT5;

    P1DIR |= BIT0|BIT6;											// Sets LED1 and LED2 to ouput

    while(1)
    {
    	ADC10CTL0 &= ~ENC;

    	ADC10CTL1 &= ~(INCH0|INCH1|INCH2|INCH3);
    	ADC10CTL1 |= INCH_3;

    	ADC10CTL0 |= ENC + ADC10SC;             				// Sampling and conversion start
        __bis_SR_register(CPUOFF + GIE);        				// LPM0, ADC10_ISR will force exit

        if (ADC10MEM < 0x2FF)
        {
        	P1OUT &= ~BIT0;										// Clear P1.0 LED off
        }
        else
        {
        	P1OUT |= BIT0;                        				// Set P1.0 LED on
        }

        ADC10CTL0 &= ~ENC;										// Clear ENC bit so can modify control bits

    	ADC10CTL1 &= ~(INCH0|INCH1|INCH2|INCH3);
        ADC10CTL1 |= INCH_5;									// Set A5 to receive input

    	ADC10CTL0 |= ENC + ADC10SC;             				// Sampling and conversion start
        __bis_SR_register(CPUOFF + GIE);        				// LPM0, ADC10_ISR will force exit

        if (ADC10MEM < 0x3FE)
        {
        	P1OUT &= ~BIT6;										// Clear P1.6 LED off
        }
        else
        {
        	P1OUT |= BIT6;                        				// Set P1.6 LED on
        }
    }

}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        					// Clear CPUOFF bit from 0(SR)
}
