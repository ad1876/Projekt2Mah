/*
*Main filen för projektet.
*Author: Elias Hussein
*/

//	Inkluderar bibiloteken.
#include <asf.h>
#include <stdio.h>
#include "task.h"
#include <ioport.h>
#include "FreeRTOSConfig.h"
#include "delay.h"
#include "conf_board.h"
#include "task_LED.h"
#include "task_BLINKA.h"
#include "task_VinkelGivare.h"
#include "task_KNAPP.h"

//För att hålla reda vad de mappade pinnarna motsvarar i SAM3x pin namn.
//https://www.arduino.cc/en/Hacking/PinMappingSAM3X

//	Definierar pinnar som jag använder.
#define LED PIO_PB27_IDX			//Digital Pinne 13 / Amber LED "L"
#define BlinkaGreen PIO_PA15_IDX	//Digital Pinne 24
#define BlinkaYellow PIO_PD1_IDX	//Digital Pinne 26
#define BlinkaRed PIO_PD3_IDX		//Digital Pinne 28
#define Knapp PIO_PD9_IDX			//Digital Pinne 30

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

int main (void)
{
	// Initialisera Due kortet */
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	configure_console();
	
	// Sätter direction för pinnar, Utgångar / Ingångar.
	ioport_set_pin_dir(BlinkaGreen,IOPORT_DIR_OUTPUT);	//Utgång
	ioport_set_pin_dir(BlinkaYellow,IOPORT_DIR_OUTPUT);	//Utgång
	ioport_set_pin_dir(BlinkaRed,IOPORT_DIR_OUTPUT);	//Utgång
	ioport_set_pin_dir(LED,IOPORT_DIR_OUTPUT);			//Utgång
	ioport_set_pin_dir(Knapp,IOPORT_DIR_INPUT);			//Ingång
	
	//Skapar tasken nedan.
	//Task med högst prioritet
	xTaskCreate(task_KNAPP, (const signed char * const) "KNAPP", TASK_KNAPP_STACK_SIZE, NULL, TASK_KNAPP_STACK_PRIORITY, xTaskHandle);
	
	//Task med näst högst prioritet
	if (xTaskCreate(task_VinkelGivare, (const signed char * const) "VINKELGIVARE", TASK_VINKELGIVARE_STACK_SIZE, NULL, TASK_VINKELGIVARE_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed the VinkelGivare Task\r\n");
	}
	//Task med näst lägst prioritet
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
