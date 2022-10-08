#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
int getsw(void)){
	//get swtiches SW4 - SW1 from PORTD (read inputs, write outputs) 
	//return bits 11:8 as lsb, 1111 0000 0000 --> 0000 0000 1111
	return (PORTD & 0x0f00) >> 8;
}
int getbtns(void)
{
	//get push bottons BTN4,BTN3,BTN2; 
	//return bits 7:5 as lsb, 1110 0000-->0000 0111
	return(PORTD & 0x00e0) >> 5;
}
