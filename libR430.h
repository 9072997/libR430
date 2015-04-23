/*
 * libR430.h
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

#ifndef LIBR430_H
#define LIBR430_H
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/atomic.h>

#define wait(seconds) _delay_ms(seconds * 995) // estimate of lost time
#define HIGH true
#define LOW false
#define OUTPUT true
#define INPUT false
#define PULSE true
#define PERCENT false
#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19
void zMain(void);

void digitalWrite(uint8_t pin, bool val);
void pinMode(uint8_t pin, bool mode);
void analogWrite(uint8_t pin, uint8_t val);
void motorWrite(uint8_t pin1, uint8_t pin2, uint8_t val);
void analogMode(bool isPulse);
bool digitalRead(uint8_t pin);
uint8_t sendPulse(uint8_t triggerPin, uint8_t echoPin);

#endif
#define main() zMain() // so user code is not main
