/*
 * lib430.h
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
 */
#ifndef LIB430_H
#define LIB430_H
////////////////////////////////////////////////////////////////////////
#define LOW 0
#define OFF 0
#define HIGH 1
#define ON 1

#define INPUTFLOAT 0
#define INPUT 1
#define OUTPUT 2

#define DISABLED -20

#define main() zMain()
////////////////////////////////////////////////////////////////////////
#define wait(seconds) waitMsec((seconds) * 1000) // because floating point math at runtime was huge
////////////////////////////////////////////////////////////////////////
#ifndef __GNUC__
#define  __attribute__(x)  /*NOTHING*/
#endif
////////////////////////////////////////////////////////////////////////
int  __attribute__((const)) pinBit(int);
void analogWrite(int, int);
void waitMsec(int);
void digitalWrite(int, int);
void pinMode(int, int);
int digitalRead(int);
int analogRead(int);
int random(void);
void analogCalibrate(void);
void zMain(void); // so that the user's code may follow our own.
////////////////////////////////////////////////////////////////////////
#endif
