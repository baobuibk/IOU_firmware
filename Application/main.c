/*
 * PDUFirmware.c
 *
 * Created: 5/15/2024 10:28:50 AM
 * Author : Admin
 */ 

#include <avr/io.h>
#include "AD.h"
#include "ntc_10k.h"
#include "status_led.h"
#include "temperature.h"
#include "uart.h"
#include "scheduler.h"
#include "COPC.h"
#include "MCP4921.h"
#include "TEC.h"
#include "command.h"
#include "watchdog.h"
#include <util/delay.h>
int main(void)
{
    /* Replace with your application code */
	status_led_init();
	command_init();
	usart1_init();
	watchdog_init();
	
	SCH_Initialize();
	watchdog_create_timer();
	status_led_create_task();
////	COPC_create_task();
	temperature_init();
	temperature_create_task();
	command_create_task();

	SCH_StartSchedular();
		
//	TEC_init();
//	MCP4921_init();
//	uint16_t	data = 0;
//	init_adc();
	temperature_set_TEC_output(0, 0, 250);	//1.50 V
	temperature_set_TEC_output(1, 0, 250);	//1.50 V
	temperature_set_TEC_output(2, 0, 250);	//1.50 V
	temperature_set_TEC_output(3, 0, 250);	//1.50 V
	
	while (1)
	{
		SCH_HandleScheduledTask();
//	data = adc_read(0);
//	uint16_t temp = ntc_convertToC_10times(data);
//	UARTprintf("ADC value = %d \r\n", temp);
		//		usart1_send_string("Hello\r\n");
		//		usart0_send_string("Hello\r\n");
		//MCP4291_set_output(data, 0, 0, 1, 0);	//enable channel 0
		//data++;
		//if (data ==4096) data = 0;


	}
}

