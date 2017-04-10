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
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <ioport.h>
#include "DelayFunctions.h"

#define LED PIO_PB27_IDX
int main (void)
{
	
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	ioport_set_pin_dir(LED,IOPORT_DIR_OUTPUT);
		
	while (1)
	{
		ioport_set_pin_level(LED,HIGH);
		delayMicroseconds(500000);
		ioport_set_pin_level(LED,LOW);	
		delayMicroseconds(500000);
	}
	
}
