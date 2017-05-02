/*
 * Navi.c
 *
 * Created: 2017-05-02 08:34:30
 *  Author: Jounne
 */ 

#include <asf.h>
#include <inttypes.h>
#include "Navi.h"

int startposition[2] = {0,0};
int endposition[2] = {12,5};
int middleposition[2];
int currentposition[2];
int road1[2],road2[2];


/*
uint16_t test = 0x0004000300020001;
typedef struct allpositions{
	int16_t xxpos1,
	int16_t yypos1,
	int16_t xxpos2,
	int16_t yypos2
	};
*/

void calculate_rut(){
	middleposition[0] = startposition[0];
	middleposition[1] = endposition [1];
	road1[0] = middleposition[0] - startposition[0];
	road1[1] = middleposition[1] - startposition[1];
	print_values(road1[0],road1[1]);
}


void print_values(int xPosition,int yPosition){
	char *xpos[10];
	char *ypos[10];
	sprintf(xpos,"X: %d\n",xPosition);
	sprintf(ypos,"Y: %d\n",yPosition);
	printf(xpos);
	printf(ypos);
}

void getCurrentPosition(){
	//something here
}
