/*
*Main filen för projektet.
*Author: Elias Hussein
*/

//	Inkluderar bibiloteken.
#include <asf.h>
#include <stdio.h>
#include "task.h"
#include <ioport.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "delay.h"
#include "conf_board.h"
#include "task_LED.h"
#include "task_BLINKA.h"
#include "task_VinkelGivare.h"
#include "task_KNAPP.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Motorfunctions.h"
//För att hålla reda vad de mappade pinnarna motsvarar i SAM3x pin namn.
//https://www.arduino.cc/en/Hacking/PinMappingSAM3X

//	Definierar pinnar som jag använder.
#define LED PIO_PB27_IDX			//Digital Pinne 13 / Amber LED "L"
#define BlinkaGreen PIO_PD9_IDX		//Digital Pinne 30
#define BlinkaYellow PIO_PD1_IDX	//Digital Pinne 26
#define BlinkaRed PIO_PD3_IDX		//Digital Pinne 28
#define Knapp PIO_PA15_IDX			//Digital Pinne 24
#define LED1 PIO_PC22_IDX
#define LED3 PIO_PC29_IDX  //pin10
#define k1 PIO_PC28_IDX 
	float a = 7;
	float b = 8;
	float c = 5;
	float d = 6;
	float distance;
/*Tillåter feedback till terminafönstret */
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

knapp_handler();
int main (void)
{
	// Initialisera Due kortet */
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	configure_console();
	float getDistance(float x1,float x2,float y1,float y2);
	float updateOdometry(float x_before, float y_before);
	int state;
	// Sätter direction för pinnar, Utgångar / Ingångar.
	ioport_set_pin_dir(BlinkaGreen,IOPORT_DIR_OUTPUT);	//Utgång
	ioport_set_pin_dir(BlinkaYellow,IOPORT_DIR_OUTPUT);	//Utgång
	ioport_set_pin_dir(BlinkaRed,IOPORT_DIR_OUTPUT);	//Utgång
	ioport_set_pin_dir(LED,IOPORT_DIR_OUTPUT);			//Utgång
	ioport_set_pin_dir(Knapp,IOPORT_DIR_INPUT);			//Ingång
	ioport_set_pin_dir(k1,IOPORT_DIR_INPUT);			//Ingång
	ioport_set_pin_dir(LED1,IOPORT_DIR_OUTPUT);		
	ioport_set_pin_level(LED1,LOW);
	moveForward(1850,1850);
	//Skapar tasken nedan.
	//Task med högst prioritet
	float di = getDistance(a,b,c,d);
	char str[20];
	sprintf(str,"distans: %f\n",di);
	printf("hej");
	printf (str);
	float odo = updateOdometry(a,b);
	sprintf(str,"odometry: %f\n",odo);
	printf(str);
	
	printf ("hello its me");
	bool knapp;
	knapp = ioport_get_pin_level(k1);
	if (knapp==true)
	{
		//pushButton1(instance);
		//ioport_set_pin_level(LED3,knapp)
		
		int state = 0;
	}
	if(knapp==2)
	{
		int state = 1;
	}
	switch(state){
		case 0:
		ioport_set_pin_level(LED1,HIGH);
		delayMicroseconds(100000);
		char str[20];
		sprintf(str,"case1: %f\n");
		printf (str);
		case 1:
		//P_regulator(2,2);
		break;
	}
	xTaskCreate(task_KNAPP, (const signed char * const) "KNAPP", TASK_KNAPP_STACK_SIZE, NULL, TASK_KNAPP_STACK_PRIORITY, NULL);
	
	//Task med näst högst prioritet
// 	if (xTaskCreate(task_VinkelGivare, (const signed char * const) "VINKELGIVARE", TASK_VINKELGIVARE_STACK_SIZE, NULL, TASK_VINKELGIVARE_STACK_PRIORITY, NULL) != pdPASS) {
// 		printf("Failed the VinkelGivare Task\r\n");
// 	}
	//Task med näst lägst prioritet
// 	if (xTaskCreate(task_LED, (const signed char * const) "LED", TASK_LED_STACK_SIZE, NULL, TASK_LED_STACK_PRIORITY, NULL) != pdPASS) {
// 		printf("Failed the LED Task\r\n");
// 	}
	//Task med lägst prioritet
// 	if (xTaskCreate(task_BLINKA, (const signed char * const) "BLINKA", TASK_BLINKA_STACK_SIZE, NULL, TASK_BLINKA_STACK_PRIORITY, NULL) != pdPASS) {
// 		printf("Failed the BLINKA Task\r\n");
// 	}
	//Ser till att köra tasken.
	vTaskStartScheduler();
	
	
}



float getDistance(float x1,float x2,float y1,float y2){
	
	distance =  sqrt((x1-y1)*(x1-y1)+(x2-y2)*(x2-y2));
	return distance;
}

float updateOdometry(float x_before, float y_before){
float anglepos;
	float sr = distance * (a-x_before);
	float sl = distance * (b-y_before);
	x_before = a;
	y_before = b;
	float distansdtraveled = (sl+sr)/2;
	float anglechange = 2*(sr-sl)/2;
	anglepos += anglechange;
	float xChange = distansdtraveled*cos(anglepos);
	float yChange = distansdtraveled*sin(anglepos);
	a +=xChange;
	b +=yChange;
	
	
}