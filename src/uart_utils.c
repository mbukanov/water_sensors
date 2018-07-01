#include "uart_utils.h"
#include <util/delay.h>

void uart0_init() {
/* atmega328p 
	UBRR0H = (unsigned char)(BAUD_PRESCALE >> 8);
	UBRR0L = (unsigned char)(BAUD_PRESCALE);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) ;
	UCSR0C = (1 << USBS0) | (3 << UCSZ00) ;
*/
	UBRRL = (unsigned char)(BAUD_PRESCALE);
	UBRRH = (unsigned char)(BAUD_PRESCALE >> 8);
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1) ;
}

void send(unsigned char * bytes, int len) {
	int i = 0;
	for(i = 0; i < len; i++) {
		while ((UCSRA & (1 << UDRE)) == 0) {};
		UDR = bytes[i];
	}
}


void send_byte(unsigned char byte) {
	while(!(UCSRA & (1<<UDRE)));
	UDR = byte;
}
