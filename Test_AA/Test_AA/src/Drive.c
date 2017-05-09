/*
 * Drive.c
 *
 * Created: 2017-05-08 16:52:33
 *  Author: André Ahlbertz
 */ 

#include <asf.h>
#include <ioport.h>
#include <stdlib.h>
#include <inttypes.h>
#include "Regulator.h"
#include "Motorfunctions.h"
#include "DelayFunctions.h"
#include "Drive.h"

#define R0 PIO_PA15_IDX
#define R1 PIO_PD1_IDX
#define R2 PIO_PD3_IDX
#define R3 PIO_PD9_IDX
#define R4 PIO_PD10_IDX
#define R5 PIO_PC2_IDX
#define R_RESET PIO_PB26_IDX




#define X1 300
#define Y1 300
#define X2 300
#define Y2 300
#define X3 300
#define Y3 300
#define XBOX 300
#define YBOX 300


void initDrive(void){
	ioport_set_pin_dir(R_RESET,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(R0,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R1,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R2,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R3,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R4,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R5,IOPORT_DIR_INPUT);
}


void testStuff(void){
	
	int count =0;
	int newcount = 0;
	
	
	
	
	
	ioport_set_pin_level(R_RESET,LOW);
	
	while(newcount < 360){
		moveForward(1600,1600);
		
		count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
		+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
		
		newcount = newcount + count;
		
		count = 0;
	}
	
	newcount = 0;
	ioport_set_pin_level(R_RESET,HIGH);
	
		
}

// void driveTo(int x, int y){
// 	
// 	
// 	while(){
// 		
// 		
// 		P_regulator()
// 	}
// 		
// 	
// }