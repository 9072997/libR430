/*
 * digitalWrite-ledBlinker.c
 * Copyright (C) 2012  Jon Penn
 *  
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
 * 
 * 
 * This is a demo of the digitalWrite function. It is an abstraction so
 * the programer need not use bit manipulation to write to pins. This
 * demo uses the red and green leds on the launchpad on pins 10 and 16.
 * 
 * the syntax is: digitalWrite(int pin, int value)
 * pin: the pin with the port as the first decimil digit and the bit as
 * 		second digit.
 * value: HIGH for vcc or LOW for gnd. ON and OFF also work.
 * 
 */

#include <libR430.h>

void main(){
	pinMode(10, OUTPUT); // set pin 10 (red led) as output so we can use digitalWrite on it
	pinMode(16, OUTPUT); // set pin 16 (green led) as output so we can use digitalWrite on it

	for(;;){ // foreaver
		
		digitalWrite(10, HIGH); // make pin 10 HIGH (turn on red led)
		digitalWrite(16, LOW); // make pin 16 LOW (turn off green led)
		
		wait(1); // wait 1 second between steps so humans can see
		
		digitalWrite(10, LOW); // make pin 10 LOW (turn off red led)
		digitalWrite(16, HIGH); // make pin 16 HIGH (turn on green led)
		
		wait(1); // wait 1 second between steps so humans can see
		
	} // and repete
}
