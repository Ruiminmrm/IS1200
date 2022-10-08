/* This file written 2021 by Duosi Dai and Ruimin Ma */

#include <stdint.h>
#include <pic32mx.h>

int getsw( void ){
	return ((PORTD >> 8) & 0xf);
	//get swtiches SW4 - SW1 from PORTD (read inputs, write outputs) 
	                            //return bits 11:8 as lsb, 1111 0000 0000 --> 0000 0000 1111
}

int getbtns(void){
	return ((PORTD >> 5) & 0x07) | (((PORTF >> 1) & 0x01)<< 3);
	//get push bottons BTN4,BTN3,BTN2,BTN1; 
}