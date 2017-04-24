/*
*Main file of the project-.
*Author: Elias Hussein
*/

//	Inkluderar bibiloteken.
#include <asf.h>
#include <stdio.h>
#include "task.h"
#include <ioport.h>
#include "FreeRTOSConfig.h"
#include "delay.h"
#include "task_LED.h"
#include "task_BLINKA.h"
#include "task_VinkelGivare.h"
#include "conf_board.h"



//	Definierar pinnar som jag använder.
#define LED PIO_PB27_IDX
#define Blinkared PIO_PB26_IDX
#define Blinkayellow PIO_PA14_IDX

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
	
	printf("Console ready\n");
	printf("=============\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
}

int main (void)
{
	// Initialisera Due kortet */
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	configure_console();
	
	// Sätter direction för pinnar, Utgångar / Ingångar.
	ioport_set_pin_dir(Blinkared,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(Blinkayellow,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LED,IOPORT_DIR_OUTPUT);
	
	
	
	//Skapar tasken nedan.
	//Task med högst prioritet
	if (xTaskCreate(task_VinkelGivare, (const signed char * const) "VinkelGivare", TASK_VINKELGIVARE_STACK_SIZE, NULL, TASK_VINKELGIVARE_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed the VinkelGivare Task\r\n");
	}
	
	//Task med näst högst prioritet
	if (xTaskCreate(task_LED, (const signed char * const) "LED", TASK_LED_STACK_SIZE, NULL, TASK_LED_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed the LED Task\r\n");
	}
	
	//Task med lägst prioritet
	if (xTaskCreate(task_BLINKA, (const signed char * const) "BLINKA", TASK_BLINKA_STACK_SIZE, NULL, TASK_BLINKA_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed the BLINKA Task\r\n");
	}
	
	//Ser till att köra tasken.
	vTaskStartScheduler();
}
