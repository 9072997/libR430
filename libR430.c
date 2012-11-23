/*
 * libR430.c
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

#include <msp430g2231.h>
#include <libR430.h>
////////////////////////////////////////////////////////////////////////
#undef main
////////////////////////////////////////////////////////////////////////
int zWait=12; // so our wait function can account for changes in frequency
unsigned char zInteruptCounter=0; // counts from 0 to 4 (datatype is for optimization)
int zRandom=1; // store random state
unsigned char zAnalogWrite[2][8]={{127, 127, 127, 127, 127, 127, 127, 127}, {127, 127, 127, 127, 127, 127, 127, 127}}; // holds values as [port][pin] (chars to save RAM)
int zAnalogRead[8]={0, 0, 0, 0, 0, 0, 0, 0}; // holds offsets
const char zBit[8]={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
const unsigned char zSpeed[16]={1, 2, 2, 3, 4, 6, 8, 12, 16, 23, 34, 43, 58, 78, 113, 152}; // MHz*10 values by RSELx values from datasheet
////////////////////////////////////////////////////////////////////////
void wait10Milliseconds(long milliseconds){ // macros will replace wait(x) with waitMsec(x*100)
	milliseconds*=zWait; // compensate for frequency
	while (milliseconds--){
		__delay_cycles(998); // wait .1 msec the extra 2 are for loop overhead 
	}
}
////////////////////////////////////////////////////////////////////////
void zDigitalWrite(int pin, int value){
	int bit;
	bit=zBit[pin%10];
	switch(value){
		case HIGH:
			switch(pin/10){
				case 1:
					P1OUT |= bit;
					break;
				case 2:
					P2OUT |= bit;
			}
			break;
		case LOW:
			switch(pin/10){
				case 1:
					P1OUT &= ~bit;
					break;
				case 2:
					P2OUT &= ~bit;
			}
	}
}
////////////////////////////////////////////////////////////////////////
void analogWrite(int pin, int value){
	switch(pin/10){
		case 1:
			zAnalogWrite[0][pin % 10]=value/20;
			break;
		case 2:
			zAnalogWrite[1][pin % 10]=value/20;
	}
	
	if(value==DISABLED){ // if we are disableing the pin
		zDigitalWrite(pin, LOW); // also set it to low
	}
}
////////////////////////////////////////////////////////////////////////
void digitalWrite(int pin, int value){ // mask for dw function that disables aw
	analogWrite(pin, DISABLED); // disable analog write
	zDigitalWrite(pin, value);
}
////////////////////////////////////////////////////////////////////////
void pinMode(int pin, int mode){
	int bit;
	analogWrite(pin, DISABLED); // disable analog write
	bit=zBit[pin%10]; // to avoid redundancy
	switch(mode){
		case INPUTFLOAT:
			switch(pin/10){
				case 1:
					P1REN &= ~bit; // disable pull
					P1DIR &= ~bit; // set input
					break;
				case 2:
					P2REN &= ~bit; // disable pull
					P2DIR &= ~bit; // set input
			}
			break;
		case INPUT:
			switch(pin/10){
				case 1:
					P1REN |= bit; // enable pull
					P1DIR &= ~bit; // set input
					break;
				case 2:
					P2REN |= bit; // enable pull
					P2DIR &= ~bit; // set input
			}
			zDigitalWrite(pin, HIGH); // pull up
			break;
		case OUTPUT:
			zDigitalWrite(pin, LOW); // set LOW
			switch(pin/10){
				case 1:
					P1REN &= ~bit; // disable pull just in case
					P1DIR |= bit; // set output
					break;
				case 2:
					P2REN &= ~bit; // disable pull just in case
					P2DIR |= bit; // set output
			}
	}
}
////////////////////////////////////////////////////////////////////////
int digitalRead(int pin){
	int bit;
	bit=zBit[pin%10];
	switch(pin/10){
		case 1:
			if(P1IN & bit){ // read 1 bit from P1IN
				return HIGH;
			}else{
				return LOW;
			}
		case 2:
			if(P2IN & bit){ // read 1 bit from P2IN
				return HIGH;
			}else{
				return LOW;
			}
		default:
			return LOW; // no pin 30, sorry
	}
}
////////////////////////////////////////////////////////////////////////
int analogRead(int pin){
	if(pin <= 17){ // aparently the ADC does bad things of the pin numer is wrong
		pin-=10; // not my function so adjust pin number
		
		ADC10CTL0 &= ~ENC;
		ADC10CTL1 = pin << 12;
		ADC10CTL0 = ADC10ON + ENC + ADC10SHT_0;

		ADC10CTL0 |= ADC10SC;
		while(ADC10CTL1 & ADC10BUSY); // wait until analog read is done
		return ADC10MEM/10+zAnalogRead[pin]; // divide by 10 so we have (roughly) a percentage
	}else{ // pin does not support analog read, so output 100% for LOW or 0% for LOW
		return digitalRead(pin);
	}
}
////////////////////////////////////////////////////////////////////////
int random(void){
	zRandom = (zRandom * 32719 + 3) % 32749;
	return zRandom % 101;
}
////////////////////////////////////////////////////////////////////////
void analogCalibrate(void){ // adition calibrate port 1 analogRead values
	int i, n, sum;
	for(i=0; i<8; i++){ // loop from 0 to 7 inclusive 
		sum=0; // used for averageing
		for(n=0; n<10; n++){ // average 10 consecutive reads
			wait(.1); // so we do not overload the analog sensor
			sum+=analogRead(i+10);
		}
		
		zAnalogRead[i]-=sum/10; // adjust calibration values so 0 is normal
	}
}
////////////////////////////////////////////////////////////////////////
void setSpeed(int speed){
	switch(speed){
		case CAL1MHZ:
			BCSCTL1 = CALBC1_1MHZ; // set to calibrated 1mhz
			DCOCTL = CALDCO_1MHZ;
			break;
		default:
			if(speed>=0 && speed<=15){ //sanity check
				BCSCTL1 &= ~(0x0F);
				BCSCTL1 |= speed; // value is RSELx
				
				zWait=zSpeed[speed]; // so our wait function can compensate
			}
			break;
	}
}
////////////////////////////////////////////////////////////////////////
void main(void){
	WDTCTL=WDTPW + WDTHOLD; // Stop watchdog timer
	
	setSpeed(13); // ~8MHz
	
	P2SEL &= 0x3F; // gpio insted of xin/xout
	
	CCTL0=CCIE;
	CCR0=8192; // counts per interupt
	TACTL=TASSEL_2 + MC_1; // Set the timer A to SMCLCK, Continuous
	
	__enable_interrupt(); // Clear the timer and enable timer interrupt
	
	analogCalibrate(); // This takes 8 seconds
	
	pinMode(26, INPUT);
	while(digitalRead(26)==LOW){ // wait to pull the pin
		random(); // so we get a random initial value
		wait(0.2);
	}
	
	zMain(); // exicute user code
	for(;;); // stop after user's code is done
}
////////////////////////////////////////////////////////////////////////
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A(void){ // Timer A0 interrupt service routine
	int port, bit;
	zInteruptCounter=(zInteruptCounter + 1) % 5; // 0 to 4
	for(port=0; port<2; port++){ // loop through ports [0] and [1] (1 and 2)
		for(bit=0; bit<8; bit++){ // loop through pins 0 to 7
			if(zAnalogWrite[port][bit]!=DISABLED/20){ // if analog write is enabled
				int pin;
				
				switch(port){
					case 0:pin= 10 + bit; break; // get human readible pin numbers for digitalWrite
					case 1:pin= 20 + bit;
				}
				
				if(zAnalogWrite[port][bit]>zInteruptCounter){ // turn on and off at the right times
					zDigitalWrite(pin, HIGH);
				}else{
					zDigitalWrite(pin, LOW);
				}
			}
		}
	}
}
