/*
 * Interrupt_Handler.c
 *
 * Created: 2017-04-24 09:50:32
 *  Author: Elias Hussein
 */ 
#include <asf.h>
#include "task_KNAPP.h"
#include "Interrupt_Handler.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"

/*
void ToggleLedISR()
#define Knapp PIO_PA15_IDX			//Digital Pinne 24

// Set an interrupt handler for the provided pins.
//The provided handler will be called with the triggering pin as its parameter as soon as an interrupt is detected.
{
	//int status;
	static portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	if(xHigherPriorityTaskWoken == pdTRUE) {
	//	portYIELD_FROM_ISR();
	}
}


void ToggleLedTask(void *pvParameters) {
		xSemaphoreHandle xSemaphore;
		xSemaphore = vSemaphoreCreateBinary(void);
	while(1) {
		xSemaphoreTake(xSemaphore, portMAX_DELAY);
	}
}
// Interrupt handler för vald pinne, dvs knappen just nu...
// Handler kommer kallas vid trigging av pinnen som dess parameter så fort ett interrupt sker
void hanldler(){
	puts("FÅR JAG ETT INTERRUPT DÅ?!!!!");
	// pio_set_input(PIOA, Knapp, PIO_PULLUP);
	pio_handler_set(PIOA, ID_PIOA, Knapp, PIO_IT_RISE_EDGE, task_KNAPP);
	NVIC_EnableIRQ(PIOA_IRQn);
	pio_enable_interrupt(PIOA, Knapp);

}
*/