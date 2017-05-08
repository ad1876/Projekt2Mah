/**
 * main.c
 *
 * Created: 2017-05-08 09:48:07 
 * Author: André Ahlbertz
 *
 */


 
#include <asf.h>
#include <ioport.h>

#include "CalculateAngle.h"
#include "DelayFunctions.h"
#include "Regulator.h"
#include "Motorfunctions.h"
#include "Rotate.h"

int n = 0;
int x_diff = 0;
int y_diff = 0;
int angle = 0;

int main (void)
{
	
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	initRegulator();
	initMotor();
	initRotateMotor();
	
	
	
	
	while(n=0){
		x_diff = getX_diff(100,200);
		y_diff = getY_diff(100,200);
		angle = calculateAngle(x_diff,y_diff);
		
		rotate(angle);
		n=1;
	}
	
	
	
		
		
	

}

