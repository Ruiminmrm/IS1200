/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  //TRISE address 0xbf886100
  int volatile *trise = (int volatile *) 0xbf886100;
  //clears bits 7:0, set them as output pins, 1111 1111 0000 0000
  *trise = *trise & 0xff00;
  //intialize port D; bits 11:5 set them as input pins ,0000 1111 1110 0000 ;  
  //TRISD works as the mask of inputs
  TRISD = TRISD & 0x0fe0;
  return;
  
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  	int btn = getbtns();
  	int sw = getsw();
  	if(btn & 0x1)// button 001 
	{
  		mytime = (sw << 4)|(mytime & 0xff0f);//16:53 ---> 16:43 ----> ff0f or mask the bits 7:4 
	}
	if(btn & 0x2)// button 010
	{
		mytime = (sw << 8)|(mytime & 0xf0ff);//16:53 ---> 14:53 ----> f0ff or mask the bits 11:8
	}
	if(btn & 0x4)// button 100
	{
		mytime = (sw << 16)|(mytime & 0x0fff);//16:53 ---> 46:53 ----> 0fff or mask 
	}
	delay( 1000 );
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    display_image(96, icon);
}
/*Test pressing BTN3 and BTN2 at the same time. What happens? Why?
--------------------------------
*/

/* Three device-registers for input/output control are TRISE, TRISESET, and TRISECLR.
Their functions are related. How? What are the differences?
----TRISX is a register which controlls the port. TRISX determine whetheer the pin of the port id an input or an output,
    When the given bit of the TRISX register is 0, the pin is an output. 
	When the given bit of the TRISX register is 1, the pin is an input.
----TRISXSET register reads the TRISX base register and set any bits specified as '1'. then write the value back to the TRISX base register.
----TRISXCLR register reads the TRISX base register and set any bits specified as '0'. then write the valur back to the TRISX base register.
*/

/*In the generated assembly code, in which MIPS register will the return values from
functions getbtns and getsw be placed in. You should be able to answer this question
without debugging the generated assembly code.
----
*/

/*In this exercise, we explained which bits that should be used in Port D and Port E. How can
you find this information in the PIC32 and ChipKIT manuals? Be prepared to demonstrate
how to find this information in the manuals.
Advice: check the lecture slides from lecture 5 for ideas.
----PIC32MX3XX/4XX Family Data Sheet P.72. PORT D
----PIC32MX3XX/4XX Family Data Sheet P.73. PORT E
*/
