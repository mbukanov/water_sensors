#ifndef SHIFT_REG_UTILS_H
#define SHIFT_REG_UTILS_H

#include <avr/io.h>
#include <util/delay.h>

#define CLK PD3
#define DS PD2
#define E PD4
#define PORT PORTD
#define DDR DDRD

void shift_reg_init() {
	DDR |= (1 << CLK) |(1<<DS) | (1 << E);
}

void ShiftRegisterValue(unsigned char byte) {
    PORT &= ~(1 << E);
    char i = 0;
    for(i = 7; i >= 0; i--) {
        PORT &= ~(1 << CLK);
        _delay_ms(1);
        PORT=((1 << i) & byte) ? PORT | (1<<DS) : PORT & ~(1<<DS);
        PORT |= (1 << CLK);
        _delay_ms(1);
    }
    PORT |= (1 << E);
}

#endif
