#include "adc_utils.h"

void adc_init() {
	ADMUX=(1<<REFS0)|(1<<REFS1);
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); 
}

unsigned char getADC(int pin) {
	set_adc_pin(pin);
	
    unsigned char v;                                                              
    ADCSRA|=(1<<ADSC);
//    while ((ADCSRA & _BV(ADIF))==0x00);
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA|=(1<<ADIF);
//	v=ADCH;
    return(ADC);
}

void set_adc_pin(uint8_t num) {
	num = num & 0b00000111;
	ADMUX |= num;
	/*
	ADCSRA=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);
	switch(num) {
		case 0:	
			ADMUX=(1<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
			break;
		case 1:
			ADMUX=(1<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(1<<MUX0);
			break;
		case 2:
			ADMUX=(1<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(0<<MUX0);
			break;
		case 3:
			ADMUX=(1<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0);
			break;
		case 4:
			ADMUX=(1<<REFS1)|(1<<REFS0)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(0<<MUX0);
			break;
		case 5:
			ADMUX=(1<<REFS1)|(1<<REFS0)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(1<<MUX0);
			break;
		default:
			ADMUX=(1<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
			break;
	}
	*/
}
