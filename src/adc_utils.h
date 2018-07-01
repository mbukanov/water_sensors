#ifndef ADC_UTILS
#define ADC_UTILS

#include <avr/io.h>
#include <util/delay.h>

unsigned char getADC(int pin);
void set_adc_pin(uint8_t num);


#endif
