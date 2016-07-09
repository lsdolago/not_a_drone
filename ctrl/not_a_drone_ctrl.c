#include <msp430.h>
#include <stdint.h>
#include "cc110l.h"
#include "spi.h"
#include "uart.h"

int main(void){
	uint8_t c;
	
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	DCOCTL = 0;                               // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
	DCOCTL = CALDCO_1MHZ;

	spi_init();
	uart_init();
	cc110l_init();

	c = cc110l_read_reg(0xf1);
	uart_puts("Hello world\n\r");
	uart_puti(c, 16);
	uart_puts("\n\r");

	__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled

	while(1);
	
	return 0;
}
