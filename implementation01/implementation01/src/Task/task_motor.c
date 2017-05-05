/*,
 * task_motor.c
 *
 * Created: 2017-05-02 10:15:57
 *  Author: Jounne
 */ 
#include <asf.h>

#include "task_motor.h"
#include "Motor/PID_Controller.h"
#include "Motor/Motorfunctions.h"
#include "Motor/Rotate.h"
extern long sensordistance;
int x_pos = 0;
int x_dest = 25;
int b =0 ;		//Börvärde
int u=0;		//Ärvärde


void task_motor(void *pvParameters){
	initMotor2();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{	
		int n=1;
 		b=2;
 		u=2;

		puts("Task MOTORRRRRRR");
// 		if(sensordistance<30 || x_pos>x_dest){
// 			moveForward1(1500,1500);
// 			}else{	
// 		
			if(x_pos<x_dest){
				n=1;
			}else{
				n=0;
			}

			switch (n)
			{
			case 0:
				moveForward1(1500,1500);
				rotate(180);
								
				break;
					
			case 1:
				moveForward1(1650,1650);
				P_regulator(2,3);


				break;
				
			}
			x_pos++;
			
			
		//	stop(10);
			//vTaskDelay(1000);
		/*}*/
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}


