/*
 * Motorfunctions.c
 *
 * Created: 2017-04-26 09:32:47
 *  Author: Jounne
 */ 

#include <asf.h>
#include <ioport.h>

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