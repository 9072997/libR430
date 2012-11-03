/*
 * robot-folowLight.c
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
 * This is what your code for the 2012 robot compitition might look like
 * 
 * This program assumes your motors and sensors are set up as below
 * pin 11: left light sensor
 * pin 12: right light sensor
 * pin 13: left motor
 * pin 14: right motor
 * 
 */

#include <lib430.h>

void greenFlag(){
	int i; // this is used as a counter in the for loops
	
	pinMode(11, INPUT); // we get information IN from pin 11 because it has a light sensor atached
	pinMode(12, INPUT); // pin 12 also
	
	pinMode(13, OUTPUT); // pin 13 is connected to a motor which is an OUTPUT device
	pinMode(14, OUTPUT); // pin 14 also
	
	for(;;){ // this loop will run VERY fast because we don't have a wait
		
		if(analogRead(11)>analogRead(12)){ // if there is more light on the left
			// turn to the left
			digitalWrite(13, LOW); // turn off the left motor
			digitalWrite(14, HIGH);  // turn on the right motor
		}else{ // otherwise (more light on the right)
			// turn to the right
			digitalWrite(13, HIGH); // turn on the left motor
			digitalWrite(14, LOW);  // turn off the right motor
		}
		
	} // and repete
}
