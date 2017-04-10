/**
 * \file
 *
 * \brief Empty user application template
 *
 */

//Styrning


#include <asf.h>
#include <ioport.h>
#include "DelayFunctions.h"


//#define LED PIO_PB27_IDX
#define FORWARD PIO_PB26_IDX

void pulseOut(int p);
int i=0;


int main (void)
{
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	ioport_set_pin_dir(FORWARD,IOPORT_DIR_OUTPUT);
	
	while(i<2000){		
	//for(int i=800;i<2200;i++){
		i++;
		pulseOut(1000);
		//ioport_set_pin_level(LED,HIGH);
		delayMicroseconds(1100);		//Delays 1,1 ms for unit 2
		pulseOut(2000);
		//ioport_set_pin_level(LED,LOW);
		delayMicroseconds(50000);		//Delays 5,25 ms to signal a new cycle
	}
	pulseOut(1500);
	delayMicroseconds(1100);
	pulseOut(1500);
}

void pulseOut(int p){					//Gives signal out for "p" microseconds   
	ioport_set_pin_level(FORWARD,HIGH);
	delayMicroseconds(p);
	ioport_set_pin_level(FORWARD,LOW);
}