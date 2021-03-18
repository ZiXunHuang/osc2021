#include "gpio.h"
#include "aux.h"
#include "utils.h"

void uart_init() {
    register unsigned int r = *GPFSEL1;

    *AUX_ENABLE |= 1;   /* Enable mini uart */
    *AUX_MU_CNTL = 0;   /* Disable tx rx */
    *AUX_MU_LCR = 3;    /* 8-bit mode */
    *AUX_MU_MCR = 0;
    *AUX_MU_IER = 0;    /* Disable interrupts */
    *AUX_MU_IIR = 6;    /* No fifo */
    *AUX_MU_BAUD = 270; /*Set baud rate */

    /* Change GPIO 14 15 to alternate function -> P92 */
    r &= ~((7 << 12)|(7 << 15)); /* Reset GPIO 14, 15 */
    r |= (2 << 12)|(2 << 15);    /* Set ALT5 */
    *GPFSEL1 = r;

    /* Disable GPIO pull up/down -> P101 */
    *GPPUD = 0; /* Set control signal to disable */
    delay(150);
    /* Clock the control signal into the GPIO pads */
    *GPPUDCLK0 = (1 << 14)|(1 << 15);
    delay(150);
    *GPPUDCLK0 = 0; /* Remove the clock */
    *AUX_MU_CNTL = 3; /* Enable tx rx */
}

__attribute__((section(".text.io"))) char uart_getc() {
    char c;
    while (!(*AUX_MU_LSR & 0x01)) {}
    c = (char)(*AUX_MU_IO);
    return c;
}

__attribute__((section(".text.io"))) void uart_putc(char c) {
    while (!(*AUX_MU_LSR & 0x20)) {}
    *AUX_MU_IO = c;
}

__attribute__((section(".text.io"))) void print(const char *s) {
    while (*s) {
        if (*s == '\n') {
            uart_putc('\r');
        }
        uart_putc(*s++);
    }
}

__attribute__((section(".text.io"))) void print_int(unsigned long long num) {
    if (!num) {
        uart_putc('0');
        return ;
    }
    unsigned int buffer[15];
    int count = 0;
    while (num) {
        buffer[count++] = num%10;
        num/=10;
    }
    for (int i = count-1; i >= 0; i--) {
				switch (buffer[i]) {
					case 0:
							uart_putc('0');
							break;
					case 1:
							uart_putc('1');
							break;
					case 2:
							uart_putc('2');
							break;
					case 3:
							uart_putc('3');
							break;
					case 4:
							uart_putc('4');
							break;
					case 5:
							uart_putc('5');
							break;
					case 6:
							uart_putc('6');
							break;
					case 7:
							uart_putc('7');
							break;
					case 8:
							uart_putc('8');
							break;
					case 9:
							uart_putc('9');
							break;
				}
		}
}