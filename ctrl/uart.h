#include <stdint.h>

void uart_init(void);
void uart_putc(char c);
void uart_puts(char *s);
void uart_puti(int16_t i, uint16_t base);
