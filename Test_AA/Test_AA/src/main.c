
#include <asf.h>
#include <ioport.h>
#include <stdio.h>

#include "DelayFunctions.h"
#include "CalculateAngle.h"
#include "Regulator.h"
#include "Motorfunctions.h"
#include "Rotate.h"
#include "Drive.h"

int OB1x= 20;
int OB1y = 30;
int OB2x = 30;
int OB2y = 30;
int OB3x = 40;
int OB3y = 50;

uint8_t c_counter = 0;
char rx[16];

/*Tillåter feedback till terminafönstret */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};
	
	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	printf("Konsolen reado\n");
	printf("===============\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	printf("Whilesatsen");
}


// static void configure_console(void)
// /* Enables feedback through the USB-cable back to terminal within Atmel Studio */
// /* Note that  the baudrate, parity and other parameters must be set in conf/conf_uart_serial.h */
// {
// 	const usart_serial_options_t uart_serial_options = {
// 		.baudrate = CONF_UART_BAUDRATE,
// 		.paritytype = CONF_UART_PARITY,
// 		.charlength = CONF_UART_CHAR_LENGTH,
// 		.stopbits = CONF_UART_STOP_BITS
// 	};
// 
// 	/* Configure console UART. */
// 	sysclk_enable_peripheral_clock(BOARD_USART1_BASE);
// 	usart_serial_init(CONF_UART, &uart_serial_options);
// }

// void USART1_Handler() {
// 	CONF_UART->US_CR |= (1 << US_CR_RSTRX);
// 	rx[c_counter++] = CONF_UART->US_RHR & US_RHR_RXCHR_Msk;
// 	if (c_counter > 15)
// 	{
// 		c_counter = 0;
// 		/*x1 = (rx[0] << 8) | (rx[1] << 0);
// 		y1 = (rx[2] << 8) | (rx[3] << 0);
// 		x2 = (rx[4] << 8) | (rx[5] << 0);
// 		y2 = (rx[6] << 8) | (rx[7] << 0);*/
// 	}
// 	
// }

// void stringToInt(uint16_t *p_variable, char *p_string) {
// 			*p_variable = (*p_string++ - '0') * 1000;
// 			*p_variable = *p_variable + (*p_string++ - '0') * 100;
// 			*p_variable = *p_variable + (*p_string++ - '0') * 10;
// 			*p_variable = *p_variable + (*p_string - '0');
// }


int main (void)
{
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	initRegulator();
	initMotor();
	initRotateMotor();
	configure_console();
	initDrive();
	
// 	char str1[4];
// 	char str2[4];
// 	char str3[4];
// 	char str4[4];
	uint16_t x1 = 0;
	uint16_t y1 = 0;
// 	uint16_t x2 = 0;
// 	uint16_t x3 = 0; //irrelevant
// 	uint16_t x4 = 0; //irrelevant
	

	while(1){
		
// 		str1[0] = rx[0];
// 		str1[1] = rx[1];
// 		str1[2] = rx[2];
// 		str1[3] = rx[3];
// 		
// 		str2[0] = rx[4];
// 		str2[1] = rx[5];
// 		str2[2] = rx[6];
// 		str2[3] = rx[7];
// 		
// 		str3[0] = rx[8];
// 		str3[1] = rx[9];
// 		str3[2] = rx[10];
// 		str3[3] = rx[11];
// 		
// 		str4[0] = rx[12];
// 		str4[1] = rx[13];
// 		str4[2] = rx[14];
// 		str4[3] = rx[15];
// 		
// 		stringToInt(&x1, str1);
// 		stringToInt(&x2, str2);
// 		stringToInt(&x3, str3);
// 		stringToInt(&x4, str4);
// 			

startupMeasure1(0,0);
moveForward(1650,1650);
delayMicroseconds(1000000);
moveForward(1500,1500);
startupMeasure2(20,20);

		int casen=0;
		switch (casen)
		{
		case 0:
			rotate(calculateAngle(getY_diff(OB1x,x1),getX_diff(OB1y,y1)));
		case 1:
			driveTo(calculateDistance(getY_diff(OB1x,x1),getX_diff(OB1y,y1)));
			break;
		case 2:
			rotate(calculateAngle(getY_diff(OB2x,OB1x),getX_diff(OB2y,OB1y)));
		case 3:
			driveTo(calculateDistance(getY_diff(OB2x,OB1x),getX_diff(OB2y,OB1y)));
			break;
		case 4:
			rotate(calculateAngle(getY_diff(OB3x,OB2x),getX_diff(OB3y,OB2y)));
		case 5:
			driveTo(calculateDistance(getY_diff(OB3x,OB2x),getX_diff(OB3y,OB2y)));		
			break;
		default:
			moveForward(1500,1500);	
			break;
		}
		casen++;
	}
}