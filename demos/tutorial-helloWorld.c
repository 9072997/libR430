/*
 * tutorial-helloWorld.c
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
 * http://github.com/9072997/libR430/wiki/Getting-Started
 * It turnes on the red LED on the launchpad.
 * 
 */

#include <libR430.h>

void main(){
	pinMode(10, OUTPUT); // set pin 10 to OUTPUT
	digitalWrite(10, HIGH); // make pin 10 HIGH (turn on the pin)
}
