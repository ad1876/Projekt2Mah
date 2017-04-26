/*
 * Motorfunctions.c
 *
 * Created: 2017-04-26 09:32:47
 *  Author: Jounne
 */ 

#include <asf.h>
#include <ioport.h>
#include <inttypes.h>
#include "DelayFunctions.h"
#include "Motorfunctions.h"
#define FORWARD PIO_PC4_IDX
//högra räknare
#define R0 PIO_PA15_IDX
#define R1 PIO_PD1_IDX
#define R2 PIO_PD3_IDX
#define R3 PIO_PD9_IDX
#define R4 PIO_PD10_IDX
#define R5 PIO_PC2_IDX
#define R_RESET PIO_PB26_IDX
//vänstra räknaren
#define L0 PIO_PD0_IDX
#define L1 PIO_PD2_IDX
#define L2 PIO_PD6_IDX
#define L3 PIO_PA7_IDX
#define L4 PIO_PC1_IDX
#define L5 PIO_PC3_IDX
#define L_RESET PIO_PA14_IDX

int r_count=0;
int counter = 0;
int l_count=0;
int Kp = 5;
int angle=250;
void initMotor(){
		ioport_set_pin_dir(FORWARD,IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(R_RESET,IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(L_RESET,IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(R0,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(R1,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(R2,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(R3,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(R4,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(R5,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(L0,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(L1,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(L2,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(L3,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(L4,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(L5,IOPORT_DIR_INPUT);
		//ioport_set_pin_dir(TESTPIN,IOPORT_DIR_OUTPUT);
}


void P_regulator(int b)
{
	r_count = ioport_get_pin_level(R0)+(ioport_get_pin_level(R1)*2)+(ioport_get_pin_level(R2)*4)+(ioport_get_pin_level(R3)*8);
	+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;   
	//r_count = ioport_get_pin_level(R0);
	ioport_set_pin_level(R_RESET,HIGH);	                                                          //hämta input värde frå pinnarna
	l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
	+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
	ioport_set_pin_level(L_RESET,HIGH);	
	/*
	if(counter == 64){
		ioport_set_pin_level(R_RESET,HIGH);
		ioport_set_pin_level(L_RESET,HIGH);
		delayMicroseconds(100);
		counter = 0;
		ioport_set_pin_level(R_RESET,LOW);
		ioport_set_pin_level(L_RESET,LOW);
	}
	counter++;
	*/
	char str[20];
	sprintf(str,"högerhjul: %d\n",r_count);
	printf (str);
	//int e = b-(r_count - l_count); //räkna felvärde
	//angle = (Kp*e)+250; //adderar medelvärde för att köra fram, funktionen för p-regulator
	//printf (" Felvarde:%d\n",e);
	sprintf(str,"Vänsterhjul: %d\n",l_count);
	printf (str);
	moveForward();
//	turn(angle); // anropar turn med den nya vinkeln
	ioport_set_pin_level(R_RESET,LOW);
	ioport_set_pin_level(L_RESET,LOW);
	//delayMicroseconds(10000);
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
		
		pulseOut(1550);
		delayMicroseconds(1100);
		pulseOut(1550);
		delayMicroseconds(5250);
}

void moveForward(){
	pulseOut(1600);
	delayMicroseconds(1100);
	pulseOut(1400);
	delayMicroseconds(5250);
}