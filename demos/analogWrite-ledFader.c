/*
 * analogWrite-ledFader.c
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
 * This is a demo of the analogWrite function. It does software pwm.
 * This demo uses the red and green leds on the launchpad on pins 10 and
 * 16.
 * 
 * the syntax is: analogWrite(int pin, int value)
 * pin: the pin with the port as the first decimil digit and the bit as
 * 		second digit.
 * value: a percentage (0 to 100 inclusive) or DISABLED. NOTE: this
 * 		function has a resolution of 5 (seps at 20% intervals).
 * 
 */

#include <lib430.h>

void greenFlag(){
	int i; // this is used as a counter in the for loops
	
	setPinMode(10, OUTPUT); // set pin 10 (red led) as output so we can use analogWrite on it
	setPinMode(16, OUTPUT); // set pin 16 (green led) as output so we can use analogWrite on it
	
	for(;;){ // foreaver. i will be {0, 20, 40, 60, 80, 100, 80, 60, 40, 20} over one loop
		
		for(i=0; i<100; i+=20){ // i will be {0, 20, 40, 60, 80} over this loop (remember the analogWrite function only changes as 20% intervals)
			analogWrite(10, i); // i will be {0, 20, 40, 60, 80}
			analogWrite(16, 100-i); // 100-i will be {100, 80, 60, 40, 20} ("opisite" of the red led)
			wait(1); // wait 1 second between steps so humans can see
		}
		// i is 100 here
		for(;i>=0; i-=20){ // i will be {100, 80, 60, 40, 20} over this loop
			analogWrite(10, i); // i will be {100, 80, 60, 40, 20}
			analogWrite(16, 100-i); // 100-i will be {0, 20, 40, 60, 80} ("opisite" of the red led)
			wait(1); // wait 1 second between steps so humans can see
		}
		
	} // and repete
}
