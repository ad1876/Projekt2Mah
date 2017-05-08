/*
 * CalculateAngle.c
 *
 * Created: 2017-05-08 13:48:07
 *  Author: André Ahlbertz
 */ 

#include "CalculateAngle.h"

#include <stdio.h>
#include <math.h>

int getX_diff(int dest, int pos){					//pos = current x position, dest = destination
	
	int diffx = dest - pos;
	
	return diffx;
}

int getY_diff(int dest, int pos){					//pos = current y position, dest = destination
	
	int diffy = dest - pos;
	
	return diffy;
}


int calculateAngle(int mot, int nar){				//mot = motstående, nar = närliggande
	
	int angle = atan(mot/nar) * (180/M_PI);
	
	char str[20];
	sprintf(str,"Angle: %d\n",angle);
	printf (str);
	
	return angle;
}