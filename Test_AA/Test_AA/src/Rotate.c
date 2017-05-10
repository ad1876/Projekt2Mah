/*
 * Rotate.c
 *
 * Created: 2017-05-04 14:35:36
 *  Author: André Ahlbertz
 */
#include <asf.h>
#include <ioport.h>
#include <stdlib.h>
#include <inttypes.h>
#include "Rotate.h"
#include "DelayFunctions.h"
#include "Motorfunctions.h"
#include "CalculateAngle.h"





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

int direction = 0;
int r_count = 0;
int l_count = 0;

uint16_t firstx = 0;
uint16_t firsty = 0;
uint16_t secondx = 0;
uint16_t secondy = 0;

void initRotateMotor(void){
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

	  
    
}

void rotate(int d){					//Minimum d is 4
    double ticks = d * 0.25;

//     char str[20];
//     sprintf(str,"början: %d\n",ticks);
//     printf (str);
	
	
	ioport_set_pin_level(L_RESET,LOW);
	ioport_set_pin_level(R_RESET,LOW);
   
    if(ticks>0){                    //Positivt ticks svänger höger
        while(l_count < (abs(ticks) + direction)){
           
			
            l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
            +ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
            //ioport_set_pin_level(L_RESET,HIGH); 
           
            moveForward(1600,1400);

//             sprintf(str,"åt höger: %d\n",l_count);
//             printf (str);
        }
        moveForward(1500,1500);
		
    }
    else if(ticks<0){                //Negativt ticks svänger vänster
        while(r_count < (abs(ticks) + 360 - direction)){
			
			
            r_count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
            +ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
            //ioport_set_pin_level(R_RESET,HIGH);   
            
            moveForward(1400,1600);
//             sprintf(str,"åt vänster: %d\n",r_count);
//             printf (str);
        }
        moveForward(1500,1500);
		
    }
	l_count = 0;
	r_count = 0;
	
	ioport_set_pin_level(L_RESET,HIGH);
	ioport_set_pin_level(R_RESET,HIGH);	
	
	updateDirection(d);
	
	char str[20];
	sprintf(str,"\nVinkel: %d",d);
	printf (str);
	sprintf(str,"\nTicks: %f",ticks);
	printf (str);
	
}

void updateDirection(int new_rotation){
	direction = direction + new_rotation;
}


void startupMeasure1(uint16_t x1,uint16_t x2){
	firstx = x1;
	firsty = x2;
}

void startupMeasure2(uint16_t x1,uint16_t x2){
	secondx = x1;
	secondy = x2;
	
	int xdiff = getX_diff(secondx,firstx);
	int ydiff = getY_diff(secondy,firsty);
	
	direction = calculateAngle(ydiff,xdiff);
}
