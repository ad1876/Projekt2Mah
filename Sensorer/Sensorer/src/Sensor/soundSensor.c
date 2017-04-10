/*
 * soundSensor.c
 *
 * Created: 2017-04-10 12:41:08
 *  Author: Jounne
 */ 


#include "soundSensor.h"
#include <ioport.h>
#include <delay.h>
#include <time.h>

//DigitalPin 22
//#define TriggerPin IOPORT_CREATE_PIN(PORTB,26)
//DigitalPin 23
//#define EchoPin IOPORT_CREATE_PIN(PORTA,14)


void init_sensor(){
	ioport_init();
	
	//ioport_set_pin_dir(TriggerPin,IOPORT_DIR_OUTPUT);
	//ioport_set_pin_dir(EchoPin,IOPORT_DIR_INPUT);
}

int readSensorValue(){
	/*
	long duration,distance;
	ioport_set_pin_level(TriggerPin,LOW);
	delay_ms(2);
	ioport_set_pin_level(TriggerPin,HIGH);
	delay_ms(10);
	ioport_set_pin_level(TriggerPin,LOW);
	duration = pulsein();
	*/
	return NULL;
}

int pulsein(){
	/*
	int state = 1;
	int flag = 0,clocktime;
	while(state){
		if(ioport_get_pin_level(EchoPin) && !flag){
			
			flag = 1;
		}
	}
	*/
	return NULL;
}