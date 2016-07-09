#include <msp430.h>
#include <stdint.h>
#include "spi.h"

void spi_init(void){
	UCB0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
	UCB0CTL1 |= UCSSEL_2;                     // SMCLK
	UCB0BR0 = 0x02;                          // /2
	UCB0BR1 = 0x00;                              //
	
	P1SEL |= BIT5 + BIT6 + BIT7;
	P1SEL2 |= BIT5 + BIT6 + BIT7;
	P2DIR |= BIT7;
	P2OUT |= BIT7;
	P1DIR |= BIT5 + BIT7;
	
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}
