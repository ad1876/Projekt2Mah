/*
* task_KNAPP.c
*
* Created: 2017-04-17 15:50:22
*  Author: Elias Hussein
*/
#include <asf.h>
#include "task_KNAPP.h"

void task_KNAPP(void *pvParameters)
#define Knapp PIO_PD9_IDX
#define BlinkaGreen PIO_PA15_IDX	//Digital Pinne 24
#define BlinkaYellow PIO_PD1_IDX	//Digital Pinne 26
#define BlinkaRed PIO_PD3_IDX		//Digital Pinne 28
{
	xSemaphoreHandle signal_semafor = 0;
	signal_semafor = xSemaphoreCreateMutex();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /*Wait for the next cycle. */
		if(xSemaphoreTake(signal_semafor,100)&& (ioport_get_pin_level(Knapp)==HIGH)){
			puts("Knappen-------------INTRYCKT");
			ioport_set_pin_level(BlinkaGreen,HIGH);
			ioport_set_pin_level(BlinkaRed,LOW);
			xSemaphoreGive(signal_semafor);
		}
		else{
			ioport_set_pin_level(BlinkaGreen,LOW);
			ioport_set_pin_level(BlinkaRed,HIGH);
			puts("Knappen ------------ ej intryckt!");
			xSemaphoreGive(signal_semafor);
		}
		vTaskDelay(500); //vTaskDelay(xTimeIncrement);
	}
	vTaskDelete( NULL );  // För en clean exit av tasken ( Kanske ej behövs)

}