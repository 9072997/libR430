/*
 * tutorial2-myProgram.c
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
 * This is the C file for a simple tutorial that can be found at
 * http://github.com/9072997/libR430/wiki/Tutorial-2:-Repeater
 * It makes pin 13 match pin 10
 * 
 */

#include <libR430.h>

void main(){
	pinMode(10, OUTPUT); // pin 10 is our LED, which is our output device
	pinMode(13, INPUT); // pin 13 is the button, which is our input device
	
	for(;;){ // this loop will run forever
		digitalWrite(10, digitalRead(13) ); // write, to pin 10, the current value of pin 13
	} // repeat REALLY FAST
}
