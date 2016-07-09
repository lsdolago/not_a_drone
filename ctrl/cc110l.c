#include <msp430.h>
#include <stdint.h>
#include "cc110l_hw.h"
#include "cc110l.h"

static void cc110l_cs_on(void){
	P2OUT &= ~BIT7;
}

static void cc110l_cs_off(void){
	P2OUT |= BIT7;
}

void cc110l_init(void){
	cc110l_cs_off();
	__delay_cycles(30);
	cc110l_cs_on();
	__delay_cycles(30);
	cc110l_cs_off();
	__delay_cycles(45);
	
	cc110l_cs_off();			// /CS enable
	while (!(IFG2&UCB0TXIFG));	// Wait for TXBUF ready
	UCB0TXBUF = CC110L_SRES;	// Send strobe
	// Strobe addr is now being TX'ed
	while (UCB0STAT & UCBUSY);	// Wait for TX to complete
	cc110l_cs_off();			// /CS disable
}

uint8_t cc110l_read_reg(uint8_t addr){
	uint8_t reg;
		
	cc110l_cs_on();        // /CS enable
	while(!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
	UCB0TXBUF = addr | CC110L_READ_SINGLE;// Send address
	while(!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
	UCB0TXBUF = 0;                            // Dummy write so we can read data
	while (UCB0STAT & UCBUSY);                // Wait for TX to complete
	reg = UCB0RXBUF;                            // Read data
	cc110l_cs_off(); // /CS disable
	
	return reg;
}
