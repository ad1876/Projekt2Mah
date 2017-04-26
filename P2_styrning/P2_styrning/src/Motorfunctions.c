/*
 * Motorfunctions.c
 *
 * Created: 2017-04-26 09:32:47
 *  Author: Jounne
 */ 

#include <asf.h>
#include <ioport.h>
#include <inttypes.h>

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
int l_count=0;
int Kp = 5;

void initMotor(){
		ioport_set_pin_dir(FORWARD,IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(R_RESET,IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(L_RESET,IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(R0,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(R1,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(R2,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(R3,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(L0,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(L1,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(L2,IOPORT_DIR_INPUT);
		ioport_set_pin_dir(L3,IOPORT_DIR_INPUT);
		//ioport_set_pin_dir(TESTPIN,IOPORT_DIR_OUTPUT);
}


void P_regulator(int b)
{
	//r_count = ioport_get_pin_level(R0)+(ioport_get_pin_level(R1)*2)+(ioport_get_pin_level(R2)*4)+(ioport_get_pin_level(R3)*8);
	r_count = ioport_get_pin_level(R0);
	ioport_set_pin_level(R_RESET,LOW);
	//+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;                                                             //hämta input värde frå pinnarna
	l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8;
	ioport_set_pin_level(L_RESET,LOW);
	//+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
	char str[20];
	sprintf(str,"räknaren: %d\n",r_count);
	printf (str);
	
	int e = b-(r_count - l_count); //räkna felvärde
	angle = (Kp*e)+250; //adderar medelvärde för att köra fram, funktionen för p-regulator
	//printf (" Felvarde:%d\n",e);
	turn(angle); // anropar turn med den nya vinkeln
	ioport_set_pin_level(R_RESET,HIGH);
	ioport_set_pin_level(L_RESET,HIGH);
	//delayMicroseconds(10000);
}

void pulseOut(int p){					//Gives signal out for "p" microseconds
	ioport_set_pin_level(FORWARD,HIGH);
	delayMicroseconds(p);
	ioport_set_pin_level(FORWARD,LOW);
}