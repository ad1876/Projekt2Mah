/*
 * task_motor.c
 *
 * Created: 2017-05-02 10:15:57
 *  Author: Jounne
 */ 
#include <asf.h>

#include "task_motor.h"
#include "Motor/PID_Controller.h"

extern long sensordistance;

void task_motor(void *pvParameters){
	initMotor2();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
		puts("Task MOTORRRRRRR");
		if(sensordistance<30){
			moveForward1(1500,1500);
			}else{
			pidCompute(0);
			//vTaskDelay(1000);
		}
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}


