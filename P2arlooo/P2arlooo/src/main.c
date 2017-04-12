/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "task_VinkelGivare.h"
#include <stdio.h>
#include "task.h"
#include <ioport.h>
#include "FreeRTOSConfig.h"
#include "delay.h"
#include "task_LED.h"


#define LED PIO_PB27_IDX
int main (void)
{
	////uint32_t baud_rate = 115200;
	// Initialise the Due board */
	sysclk_init();
	// Minimal main function that starts with a call to board_init()
	board_init();
	ioport_init();
	delayInit();
	ioport_set_pin_dir(LED,IOPORT_DIR_OUTPUT);
	 
	 	if (xTaskCreate(task_VinkelGivare, (const signed char * const) "VinkelGivare", TASK_VINKELGIVARE_STACK_SIZE, NULL, TASK_VINKELGIVARE_STACK_PRIORITY, NULL) != pdPASS) {
		 	printf("Failed the VinkelGivare Task\r\n");
	 	}
		 
		if (xTaskCreate(task_LED, (const signed char * const) "LED", TASK_LED_STACK_SIZE, NULL, TASK_LED_STACK_PRIORITY, NULL) != pdPASS) {
				 	printf("Failed the LED Task\r\n");
		} 
	 
		void tasken(void *p){
			while(1)
			{
				puts("HEJJJJ");
				printf("HELLO,");
			}
		}
		xTaskCreate(tasken, (signed char*) "tasken", 1024, NULL, 2, NULL);
		
		vTaskStartScheduler();
}
