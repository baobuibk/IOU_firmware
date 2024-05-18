/*
 * PDUFirmware.c
 *
 * Created: 5/15/2024 10:28:50 AM
 * Author : Admin
 */ 

#include <avr/io.h>
#include "status_led.h"
#include "uart.h"
#include "scheduler.h"
#include "COPC.h"

int main(void)
{
    /* Replace with your application code */
	status_led_init();
	usart0_init();
	usart1_init();
	SCH_Initialize();
	status_led_create_task();
	COPC_create_task();
	SCH_StartSchedular();
	uint8_t	data = 10;
    while (1) 
    {
		SCH_HandleScheduledTask();
//		UARTprintf("Hello %x  \r\n", data);
//		usart1_send_string("Hello\r\n");
//		usart0_send_string("Hello\r\n");
    }
}

