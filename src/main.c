#include "uart_utils.h"
#include "adc_utils.h"
#include "shift_reg_utils.h"
#include "zoi_protocol.h"
#include <stdio.h>

struct device_value {
  unsigned char pin_num;
  unsigned char old_value;
};

/* **** LEAKAGE SENSORS *** */
struct device_value device_leakage_pins[] = {
  { PC0, 0 },
  { PC1, 0 },
  { PC2, 0 },
  { PC3, 0 },
  { PC4, 0 },
  { PC5, 0 },
// optional digital inputs
  { PB0, 0 },
  { PB1, 0 },
  { PB2, 0 },
};

void LedOn(unsigned char num);
void LedOff(unsigned char num);

int default_optional_digital_pins[3] = { 0, 0, 0 } ;

unsigned char led_mask = 0;

#define DEVICE_LEAKAGE_PINS_COUNT 9

unsigned char getPinState(int num) {
	if(num < 6) {
		return ((PINC & (1 << device_leakage_pins[num].pin_num)) ? 1 : 0);
	} else if(num >= 6) {
		return ((PINB & (1 << device_leakage_pins[num].pin_num)) ? 1 : 0);
	}
}

unsigned char isEvent(int num) {
	if(num < 6) {
		return (getPinState(num) == 0);
	} else if(num >= 6) {
		return (getPinState(num) != default_optional_digital_pins[num-6]);
	}
	return 0;
}

void LedInitShow() {
	int i = 0;
	for(i = 0; i <= 8; i++) {
		LedOn(i);
		_delay_ms(50);
	} 
	for(i = 0; i <= 8; i++) {
		LedOff(i);
		_delay_ms(50);
	}
	ShiftRegisterValue(0);
}

void LedOn(unsigned char num) {
	led_mask |= 1 << num;
	ShiftRegisterValue(led_mask);
}

void LedOff(unsigned char num) {
	led_mask &= ~(1 << num);
	ShiftRegisterValue(led_mask);
}

void SendSensorNewStatus(unsigned char dev_type, unsigned char dev_num, unsigned char value) {
	unsigned char buffer[ZOI_FRAME_SIZE] = { 0x00 };
	FillGetBuffer(dev_type, dev_num, value, buffer);
	send(buffer, ZOI_FRAME_SIZE);
}


void main(void) {
	// DDRC on INPUT	
	DDRC &= (0 << PC0) | (0 << PC1) | (0 << PC2) | (0 << PC3) | (0 << PC4) | (0 << PC5);

	DDRB &= (0 << PB0) | (0 << PB1) | (0 << PB2);
	
	// DDRD on INPUT
	DDRD &= (0 << PD5) | (0 << PD6) | (0 << PD7);
	default_optional_digital_pins[0] = ( PIND & (1 << PD5) ? 1 : 0 );
	default_optional_digital_pins[1] = ( PIND & (1 << PD6) ? 1 : 0 );
	default_optional_digital_pins[2] = ( PIND & (1 << PD7) ? 1 : 0 );

	// Green LED for modules is ON
	DDRB |= ( 1 << PB6 );

	uart0_init();                                                                                             
    shift_reg_init();  
	LedInitShow();
	PORTB |= (1 << PB6);
	
	while(1) {
		int leak_dev_index = 0;
		for(leak_dev_index; leak_dev_index < DEVICE_LEAKAGE_PINS_COUNT; leak_dev_index++) {
			unsigned char old_value = device_leakage_pins[leak_dev_index].old_value;
			
			if(isEvent(leak_dev_index)) {
				if(old_value == 0) {
					SendSensorNewStatus(ZOI_DEV_TYPE_WATER, leak_dev_index+1, 1);
					LedOn(leak_dev_index);
				}
				device_leakage_pins[leak_dev_index].old_value = 1;
			} else {
				if(old_value == 1) {
					SendSensorNewStatus(ZOI_DEV_TYPE_WATER, leak_dev_index+1, 0);
					LedOff(leak_dev_index);
				}
				device_leakage_pins[leak_dev_index].old_value = 0;
			}
			_delay_ms(100);
		}
	}

}
