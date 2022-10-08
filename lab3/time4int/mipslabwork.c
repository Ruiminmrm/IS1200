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
int timesoutcount = 0; 

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
  
  /
  PR2 = (80000000/256)/10;//set timeperiod 10 timeout/s ----clock frequency/prescaling/10 times per s 
  T2CONSET = 0x0070; //0111 0000 ,set prescaling (bit 6-4 for precaling 1 : 256, Section 14 Timers, p.9)
  TMR2 = 0; // resets the timer 
  T2CONSET = 0x8000;//Sets the bit 15 "ON" to 1 in T2CON , bit 15 in T2CON;
  return;
  
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  
  	int btn = getbtns();// get the value of the button
  	int sw = getsw();//get the value of the switch
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
	
	//Check time-out event flag
	if (IFS(0) & 0x100 )//IFS(0) - Interrupt Flag Status
	{
		IFS(0) = 0; //reset all event flags
		timeoutcount++;
		if(timeoutcount == 10)
		{
			time2string( textstring, mytime );
  			display_string( 3, textstring );
  			display_update();
  			tick( &mytime );
  			display_image(96, icon);
  			timeoutcount = 0;//reset timeoutcount 
		}
	}
	
  }  

}
/*When the time-out event-flag is a "1", how does your code reset it to "0"?

*/

/*What would happen if the time-out event-flag was not reset to "0" by your code? Why?

*/


/*Which device-register (or registers) must be written to define the time between time-out
events? Describe the function of that register (or of those registers).
----
*/

/* If you press BTN3 quickly, does the time update reliably? Why, or why not? If not, would
that be easy to change? If so, how?

*/

