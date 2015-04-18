/*
 * libR430.c
 * Copyright (C) 2012  Jon Penn
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "libR430.h"
#undef main

struct zAnalogVal {
	uint8_t val;
	bool isEnabled;
};
volatile struct zAnalogVal zAnalogVals[20];
bool zMode = PULSE;

void zDigitalWrite(uint8_t pin, bool isHigh) { // bad form, I know
	if(isHigh) {
		switch(pin) {
			//   PP      X V    76543210
			case  3: PORTD |= 0b00001000; break;
			case  4: PORTD |= 0b00010000; break;
			case  5: PORTD |= 0b00100000; break;
			case  6: PORTD |= 0b01000000; break;
			case  8: PORTB |= 0b00000001; break;
			case  9: PORTB |= 0b00000010; break;
			case 10: PORTB |= 0b00000100; break;
			case 11: PORTB |= 0b00001000; break;
			case 12: PORTB |= 0b00010000; break;
			case 13: PORTB |= 0b00100000; break;
			case 14: PORTC |= 0b00000001; break;
			case 15: PORTC |= 0b00000010; break;
			case 16: PORTC |= 0b00000100; break;
			case 17: PORTC |= 0b00001000; break;
			case 18: PORTC |= 0b00010000; break;
			case 19: PORTC |= 0b00100000; break;
		}
		} else {
		switch(pin) {
			//   PP      X V    76543210
			case  3: PORTD &= 0b11110111; break;
			case  4: PORTD &= 0b11101111; break;
			case  5: PORTD &= 0b11011111; break;
			case  6: PORTD &= 0b10111111; break;
			case  8: PORTB &= 0b11111110; break;
			case  9: PORTB &= 0b11111101; break;
			case 10: PORTB &= 0b11111011; break;
			case 11: PORTB &= 0b11110111; break;
			case 12: PORTB &= 0b11101111; break;
			case 13: PORTB &= 0b11011111; break;
			case 14: PORTC &= 0b11111110; break;
			case 15: PORTC &= 0b11111101; break;
			case 16: PORTC &= 0b11111011; break;
			case 17: PORTC &= 0b11110111; break;
			case 18: PORTC &= 0b11101111; break;
			case 19: PORTC &= 0b11011111; break;
		}
	}
}

void digitalWrite(uint8_t pin, bool isHigh) {
	zAnalogVals[pin].isEnabled = false;
	zDigitalWrite(pin, isHigh);
}

void pinMode(uint8_t pin, bool isOutput) { // bad form, I know
	if(isOutput) {
		switch(pin) {
			//   PP     X V    76543210
			case  3: DDRD |= 0b00001000; break;
			case  4: DDRD |= 0b00010000; break;
			case  5: DDRD |= 0b00100000; break;
			case  6: DDRD |= 0b01000000; break;
			case  8: DDRB |= 0b00000001; break;
			case  9: DDRB |= 0b00000010; break;
			case 10: DDRB |= 0b00000100; break;
			case 11: DDRB |= 0b00001000; break;
			case 12: DDRB |= 0b00010000; break;
			case 13: DDRB |= 0b00100000; break;
			case 14: DDRC |= 0b00000001; break;
			case 15: DDRC |= 0b00000010; break;
			case 16: DDRC |= 0b00000100; break;
			case 17: DDRC |= 0b00001000; break;
			case 18: DDRC |= 0b00010000; break;
			case 19: DDRC |= 0b00100000; break;
		}
	} else {
		zAnalogVals[pin].isEnabled = false;
		switch(pin) {
			//   PP     X V    76543210
			case  3: DDRD &= 0b11110111; break;
			case  4: DDRD &= 0b11101111; break;
			case  5: DDRD &= 0b11011111; break;
			case  6: DDRD &= 0b10111111; break;
			case  8: DDRB &= 0b11111110; break;
			case  9: DDRB &= 0b11111101; break;
			case 10: DDRB &= 0b11111011; break;
			case 11: DDRB &= 0b11110111; break;
			case 12: DDRB &= 0b11101111; break;
			case 13: DDRB &= 0b11011111; break;
			case 14: DDRC &= 0b11111110; break;
			case 15: DDRC &= 0b11111101; break;
			case 16: DDRC &= 0b11111011; break;
			case 17: DDRC &= 0b11110111; break;
			case 18: DDRC &= 0b11101111; break;
			case 19: DDRC &= 0b11011111; break;
		}
	}
}

bool digitalRead(uint8_t pin) { // bad form, I know
	switch(pin) {
		//   PP            X     76543210
		case  3: return (PIND & 0b00001000) == 0 ? LOW : HIGH;
		case  4: return (PIND & 0b00010000) == 0 ? LOW : HIGH;
		case  5: return (PIND & 0b00100000) == 0 ? LOW : HIGH;
		case  6: return (PIND & 0b01000000) == 0 ? LOW : HIGH;
		case  8: return (PINB & 0b00000001) == 0 ? LOW : HIGH;
		case  9: return (PINB & 0b00000010) == 0 ? LOW : HIGH;
		case 10: return (PINB & 0b00000100) == 0 ? LOW : HIGH;
		case 11: return (PINB & 0b00001000) == 0 ? LOW : HIGH;
		case 12: return (PINB & 0b00010000) == 0 ? LOW : HIGH;
		case 13: return (PINB & 0b00100000) == 0 ? LOW : HIGH;
		case 14: return (PINC & 0b00000001) == 0 ? LOW : HIGH;
		case 15: return (PINC & 0b00000010) == 0 ? LOW : HIGH;
		case 16: return (PINC & 0b00000100) == 0 ? LOW : HIGH;
		case 17: return (PINC & 0b00001000) == 0 ? LOW : HIGH;
		case 18: return (PINC & 0b00010000) == 0 ? LOW : HIGH;
		case 19: return (PINC & 0b00100000) == 0 ? LOW : HIGH;
		default: return LOW;
	}
}
void analogMode(bool mode) {
	zMode = mode;
}
void analogWrite(uint8_t pin, uint8_t val) {
	zAnalogVals[pin].isEnabled = true;
	zAnalogVals[pin].val = val;
}
uint8_t sendPulse(uint8_t trigger, uint8_t echo) {
	unsigned int delay = 0;
	pinMode(trigger, OUTPUT);
	pinMode(echo, INPUT);
	for(int i=0; i<10; i++) {
		unsigned int pulseWidth = 0;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { // we use alot of timeing, so we have to disable interupts
			digitalWrite(trigger, HIGH);
			_delay_us(10);
			digitalWrite(trigger, LOW);
			while(digitalRead(echo) == LOW); // wait until echo is high
			while(digitalRead(echo) == HIGH && pulseWidth <= 2000){
				pulseWidth++;
			} // count delay untill pin comes back high
		}
		delay += pulseWidth;
		wait(0.01); // wait for lingering echos to die off
	}
	return delay/200; //average
}
ISR(TIMER1_OVF_vect) {
	if(zMode) { // is pulse
		for(uint8_t pin=0; pin<20; pin++) {
			if(zAnalogVals[pin].isEnabled) {
				zDigitalWrite(pin, HIGH);
				_delay_loop_2((zAnalogVals[pin].val+10) * 100);
				zDigitalWrite(pin, LOW);
			}
		}
	}
}
uint8_t zInteruptCounter = 0;
ISR(TIMER0_OVF_vect) {
	if(!zMode) { // percent mode
		 zInteruptCounter=(zInteruptCounter + 5) % 100;
		 for(uint8_t pin=0; pin<20; pin++) {
			 if(zAnalogVals[pin].isEnabled) { // if analog write is enabled
				 if(zAnalogVals[pin].val>zInteruptCounter) { // turn on and off at the right times
						zDigitalWrite(pin, HIGH);
					} else {
						zDigitalWrite(pin, LOW);
				 }
			 }
		 }
	 }
}
int main(void) {
	
	for(uint8_t pin=0; pin<20; pin++) { // init
		zAnalogVals[pin].isEnabled = false;
	}
	
	// Turn on timer with no prescaler on the clock for fastest
	// triggering of the interrupt service routine.
	TCCR1B |= _BV(CS11); // cs10
	TIMSK1 |= _BV(TOIE1);

	// setup timer 0 for percent mode (prescale 64)
    // Setting the 64 prescaler
    TCCR0B |= _BV(CS01) | _BV(CS00);
    // Initialize Timer0
    TCNT0 = 0;
    // Initialize the overflow interrupt for TIMER0
    TIMSK0 |= _BV(TOIE0);
	
	// Turn interrupts on.
	sei();
	
	
	
	zMain(); // user code
	for(;;); // do nothing
}
