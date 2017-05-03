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
#include <FreeRTOSConfig.h>

#include "Configs/DelayFunctions.h"
#include "Sensor/soundSensor.h"
#include "Motor/PID_Controller.h"
#include "Task/task_soundsensor.h"
#include "Task/task_blink.h"
#include "Task/task_motor.h"

static void configure_console(void)
/* Enables feedback through the USB-cable back to terminal within Atmel Studio */
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

int main (void)
{
	//alla inits
	board_init();
	sysclk_init();
	init_sensor();
	delayInit();
	initMotor2();
	ioport_init();
	configure_console();
	
	xTaskCreate(task_motor,(const signed char* const) "Motor",TASK_MOTOR_STACK_SIZE,NULL,TASK_MOTOR_PRIORITY,NULL);
	xTaskCreate(task_soundsensor,(const signed char* const) "Soundsensor",TASK_SOUNDSENSOR_STACK_SIZE,NULL,TASK_SOUNDSENSOR_STACK_PRIORITY,NULL);
	//xTaskCreate(task_blink,(const signed char* const) "BlINK",TASK_BLINK_STACK_SIZE,NULL,TASK_BLINK_PRIORITY,NULL);
	vTaskStartScheduler();
	
	
	while(1){
		
		};
	
}
