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

#define TESTPIN PIO_PD7_IDX

void pulseOut(int p);
void P_regulator(int b);
void turn(int a);
int r_count=0;
int l_count=0;
int Kp = 5;
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
		ioport_set_pin_level(R_RESET,LOW);
		ioport_set_pin_level(L_RESET,LOW);
		
		char str1[15];
		int test = ioport_get_pin_level(R_RESET);
		sprintf(str1,"TESTPINOUT %d",test);
		printf(str1);
	while(1){		
		P_regulator(0);
	}
	/*pulseOut(1500);
	delayMicroseconds(1100);
	pulseOut(1500);*/
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

void P_regulator(int b)
{	
	r_count = ioport_get_pin_level(R0)+(ioport_get_pin_level(R1)*2)+(ioport_get_pin_level(R2)*4)+(ioport_get_pin_level(R3)*8);
	ioport_set_pin_level(R_RESET,HIGH);
	//+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;                                                             //hämta input värde frå pinnarna
	l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8;
	ioport_set_pin_level(L_RESET,HIGH);
	//+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
	char str[20];
	sprintf(str,"räknaren: %d\n",r_count);
	printf (str);
	
	int e = b-(r_count - l_count); //räkna felvärde
	angle = (Kp*e)+250; //adderar medelvärde för att köra fram, funktionen för p-regulator
	printf (" Felvarde:%d\n",e);
	//turn(angle); // anropar turn med den nya vinkeln 
	ioport_set_pin_level(R_RESET,LOW);
	ioport_set_pin_level(L_RESET,LOW);
	delayMicroseconds(1000);
}

