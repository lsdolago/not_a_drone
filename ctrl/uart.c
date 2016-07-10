/** LEGAL NOTICE:
 **
 ** Nathan Zimmerman
 ** Hardware_UART
 ** 1/7/12
 **
 ** Based on Nathan Zimmerman's code at http://www.43oh.com/forum/viewtopic.php?f=10&p=15345#p15345
 ** Adapted by Lars Roland
 **/

#include <msp430.h>
#include "uart.h"

void uartInit (void)
{
    BCSCTL1 = CALBC1_1MHZ;            // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ;   
    
    ////////////////USCI setup////////////////
    
    P1SEL = BIT1 + BIT2;            // Set P1.1 to RXD and P1.2 to TXD
    P1SEL2 = BIT1 + BIT2;            //

    UCA0CTL1 |= UCSSEL_2;            // Have USCI use SMCLK AKA 1MHz main CLK
    UCA0BR0 = 104;                  // Baud: 9600, N= CLK/Baud, N= 10^6 / 9600
    UCA0BR1 = 0;                  // Set upper half of baud select to 0 
    UCA0MCTL = UCBRS_1;               // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;             // Start USCI

    IFG2 &= ~UCA0RXIFG;
    IE2 |= UCA0RXIE;
} 

void putc(unsigned char c)
{
	while(!(IFG2&UCA0TXIFG));
    UCA0TXBUF = c; // write c to TX buffer
    //__delay_cycles(10000); //transmission delay
}

void puts (const char *tx_message)
{
	while(*tx_message != '\0'){
		while(!(IFG2&UCA0TXIFG));
		UCA0TXBUF = *tx_message++; // write c to TX buffer
	}
} 

