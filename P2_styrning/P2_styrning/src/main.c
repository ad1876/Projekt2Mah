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
#include "conf_board.h"
#include "Motorfunctions.h"

//#define LED PIO_PB27_IDX

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
//definition för omvandling från bool till int
#define TRUE 1 
#define FALSE 0

#define TESTPINOUT11 PIO_PD7_IDX
#define TESPININ12 PIO_PD8_IDX

void pulseOut(int p);
void P_regulator(int b);
void turn(int a);

//int i=0;
//int speed=1500;
int angle=250;
//int d=0;			//0=left, 1=right
static void configure_console(void)
/* Enables feedback through the USB-cable back to terminal within Atmel Studio */
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}
int main (void)
{
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	configure_console();
	initMotor();
	
		pulseOut(1850);
		delayMicroseconds(1100);
		pulseOut(1850);
		delayMicroseconds(5250);
		printf("HEJ");
		ioport_set_pin_level(R_RESET,HIGH);
		ioport_set_pin_level(L_RESET,HIGH);
		ioport_set_pin_dir(TESTPINOUT11,IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(TESPININ12,IOPORT_DIR_INPUT);
		ioport_set_pin_level(TESTPINOUT11,HIGH);
		int counter =0;
	while(1){		
		//P_regulator(0);
		ioport_set_pin_level(TESTPINOUT11,HIGH);
		delayMicroseconds(100);
		ioport_set_pin_level(TESTPINOUT11,LOW);
		delayMicroseconds(100);
		r_count = ioport_get_pin_level(R0)+(ioport_get_pin_level(R1)*2)+(ioport_get_pin_level(R2)*4)+(ioport_get_pin_level(R3)*8);
		char str[20];
		sprintf(str,"räknaren: %d\n",r_count);
		printf (str);
		if(counter == 6´4){
			ioport_set_pin_level(R_RESET,HIGH);
			delayMicroseconds(100);
			counter = 0;
			ioport_set_pin_level(R_RESET,LOW);
		}
		counter++;
		delayMicroseconds(1000);
	}
	/*pulseOut(1500);
	delayMicroseconds(1100);
	pulseOut(1500);*/
}




void turn(int a){
		/*
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
		*/
		pulseOut(1550);
		delayMicroseconds(1100);
		pulseOut(1550);
		delayMicroseconds(5250);
}



