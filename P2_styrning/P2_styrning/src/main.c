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
void turn(int a);
//int i=0;
//int speed=1500;
int angle=250;
//int d=0;			//0=left, 1=right

int main (void)
{
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	ioport_set_pin_dir(FORWARD,IOPORT_DIR_OUTPUT);
	
	pulseOut(1850);
	delayMicroseconds(1100);
	pulseOut(1850);
	delayMicroseconds(5250);
	
	while(1){		
	//for(int i=800;i<2200;i++){
		
		angle=angle+125;
		turn(angle);
		
		delayMicroseconds(500000);
		
		angle=angle-125;
		turn(angle);		

		delayMicroseconds(500000);
		
		//pulseOut(1850+angle);
		//ioport_set_pin_level(LED,HIGH);
		//delayMicroseconds(1100);		//Delays 1,1 ms for unit 2
		//pulseOut(1850+angle);
		//ioport_set_pin_level(LED,LOW);
		//delayMicroseconds(500000);		//Delays 5,25 ms to signal a new cycle
		
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


void turn(int a){
		if(a>250){						//Turning left
			for(int i=0;i<a-250;i++){
					
				pulseOut(1850-i);
				delayMicroseconds(1100);
				pulseOut(1850+i);
				delayMicroseconds(5250);
					
			}
			
		}
		else if(a<250){					//Turning right
			for(int i=0;i<a;i++){
				
				pulseOut(1850+i);
				delayMicroseconds(1100);
				pulseOut(1850-i);
				delayMicroseconds(5250);
				
			}
			
		}
		else{								//Forward
				pulseOut(1850);
				delayMicroseconds(1100);
				pulseOut(1850);
				delayMicroseconds(5250);			
		}
		angle=250;
}