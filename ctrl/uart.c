#include <msp430.h>
#include <stdint.h>
#include "uart.h"

static void xtoa(int value, char* result, int base){
	// check that the base if valid
	if (base < 2 || base > 36){
		*result = '\0';
	}

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"
			[35 + (tmp_value - value * base)];
	} while(value);

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
}

void uart_init(void){
	P1SEL |= BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 0x68;                            // 1MHz 9600
	UCA0BR1 = 0x00;                              // 1MHz 9600
	UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
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

void uart_puti(int16_t i, uint16_t base){
	char str[7];
	xtoa(i, str, base);
	uart_puts(str);
}
