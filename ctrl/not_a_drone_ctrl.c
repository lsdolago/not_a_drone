#include <msp430.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void _wait(uint16_t cycles){
	while(cycles > 15) cycles -= 6;
}

void uart_putc(char c);
void uart_puts(char *s);
void uart_puti(int16_t i, int16_t base);

char* itoa(int value, char* result, int base);

int main(void){
	uint8_t c;
	char str[5];
	uint16_t i;

	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	DCOCTL = 0;                               // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
	DCOCTL = CALDCO_1MHZ;

	P1SEL |= BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 104;                            // 1MHz 9600
	UCA0BR1 = 0;                              // 1MHz 9600
	UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	P1SEL |= BIT5 + BIT6 + BIT7;
	P1SEL2 |= BIT5 + BIT6 + BIT7;
	P2DIR |= BIT7;
	P2OUT |= BIT7;

	UCB0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
	UCB0CTL1 |= UCSSEL_2;                     // SMCLK
	UCB0BR0 |= 0x02;                          // /2
	UCB0BR1 = 0;                              //
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	uart_puts("Hello world\n\r");

	__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled

	while(1);
}

void uart_putc(char c){
	while(!(IFG2&UCA0TXIFG));
	UCA0TXBUF = c;
}

void uart_puts(char *s){
	while(*s != '\0'){
		uart_putc(*s++);
	}
}

void uart_puti(int16_t i, int16_t base){
	char str[7];
	itoa(i, str, base);
	uart_puts(str);
}

char* itoa(int value, char* result, int base){
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}
