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
void analogMode(bool isPulse);
bool digitalRead(uint8_t pin);
uint8_t sendPulse(uint8_t triggerPin, uint8_t echoPin);

#endif
#define main() zMain() // so user code is not main
