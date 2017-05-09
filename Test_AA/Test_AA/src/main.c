/**
 * main.c
 *
 * Created: 2017-05-08 09:48:07 
 * Author: André Ahlbertz
 *
 */



#include <asf.h>
#include <ioport.h>
#include <stdio.h>
#include <time.h>

#include "DelayFunctions.h"
#include "CalculateAngle.h"
#include "Regulator.h"
#include "Motorfunctions.h"
#include "Rotate.h"
#include "Drive.h"




int x_diff = 0;
int y_diff = 0;
int angle = 0;

static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};
	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	printf("Konsolen reado\n");
	printf("===============\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
}

int main (void)
{
	
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	initRegulator();
	initMotor();
	initRotateMotor();
	configure_console();
	initDrive();
	
	char str[20];
	sprintf(str,"Main while");
	printf (str);
	
	
	while(1){
		
// 		rotate(180);
// 		delayMicroseconds(500000);
		
// 		char str[20];
// 		sprintf(str,"Main while");
// 		printf (str);
		
// 		clock_t start, end;
// 		double cpu_time_used;
// 		
// 		start = clock();
		
		
		testStuff();
		
		moveForward(1500,1500);
		
// 		end = clock();
// 		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
// 		
// 		printf("testStuff() took %f seconds to execute \n", cpu_time_used);
		
// 		x_diff = getX_diff(200,400);
// 		y_diff = getY_diff(200,100);
// 		angle = calculateAngle(x_diff,y_diff);
// 		rotate(angle);
// 		
 		delayMicroseconds(500000);

		

	}
	
	
	
		
		
	

}

