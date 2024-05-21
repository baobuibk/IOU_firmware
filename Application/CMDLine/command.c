/*
 * command.c
 *
 * Created: 5/19/2024 8:37:53 PM
 *  Author: Admin
 */ 
#include "scheduler.h"
#include "command.h"
#include "uart.h"
#include "temperature.h"
#include <stdlib.h>
#include "cmdline.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct _Command_TaskContextTypedef_
{
	SCH_TASK_HANDLE               taskHandle;
	SCH_TaskPropertyTypedef       taskProperty;
} Command_TaskContextTypedef;


//typedef enum{OK = 0, CMDLINE_BAD_CMD, CMDLINE_TOO_MANY_ARGS, CMDLINE_TOO_FEW_ARGS, CMDLINE_INVALID_ARG} command_error_code_t;
const char * ErrorCode[5] = {"OK\r\n", "CMDLINE_BAD_CMD\r\n", "CMDLINE_TOO_MANY_ARGS\r\n",
"CMDLINE_TOO_FEW_ARGS\r\n", "CMDLINE_INVALID_ARG\r\n" };

static	void	command_task_update(void);
tCmdLineEntry g_psCmdTable[] = { { "set_temp", Cmd_set_temp," : set desired temperature,format: set_temp channel setpoint (250 mean 25 Celcius) " },
								{ "help", Cmd_help," : Display list of commands, format: help" },								
								{"get_temp", Cmd_get_temp , " : Get the current temperature of TEC, format: get_temp NTC channel", },
								{"get_temp_setpoint", Cmd_get_temp_setpoint , " : Get the current temperature setpoint of TEC, format: get_temp_setpoint  channel", },	
								{"tec_ena", Cmd_TEC_enable, " : enable TEC channel, format: tec_ena channel"},
								{"tec_dis", Cmd_TEC_disable, " : disable TEC channel, format: tec_dis channel"}	,						
								{"tec_dis_auto", Cmd_TEC_disable_auto_control, " : disable auto control, format tec_dis_auto channel"},
								{"tec_ena_auto", Cmd_TEC_enable_auto_control, " :  enable auto control,  format: tec_ena_auto channel"},
								{"tec_set_output", Cmd_TEC_set_output, " :  set the output manually,  format: tec_set_output channel heat_cool(0:COOL, 1: HEAT) voltage(150 mean 1.5)"},	
								{0,0,0}
								};

volatile static	ringbuffer_t *p_CommandRingBuffer;
volatile static	char s_commandBuffer[COMMAND_MAX_LENGTH];
static uint8_t	s_commandBufferIndex = 0;


static Command_TaskContextTypedef           s_CommandTaskContext =
{
	SCH_INVALID_TASK_HANDLE,                 // Will be updated by Schedular
	{
		SCH_TASK_SYNC,                      // taskType;
		SCH_TASK_PRIO_0,                    // taskPriority;
		10,                                // taskPeriodInMS;
		command_task_update                // taskFunction;
	}
};

void	command_init(void)
{
	usart0_init();
	
	p_CommandRingBuffer = uart_get_uart0_rx_buffer_address();
	memset((void *)s_commandBuffer, 0, sizeof(s_commandBuffer));
	s_commandBufferIndex = 0;
	usart0_send_string("PDU FIRMWARE V1.0.0 \r\n");
	usart0_send_string(">");
	command_send_splash();
}

static	void	command_task_update(void)
{
	char rxData;
	int8_t	ret_val;
	while (! rbuffer_empty(p_CommandRingBuffer))
	{
		rxData = rbuffer_remove(p_CommandRingBuffer);
		usart0_send_char(rxData);
		if ((rxData == '\r') || (rxData == '\n'))		//got a return or new line
		{
			if (s_commandBufferIndex > 0)		//if we got the CR or LF at the begining, discard	
			{
				s_commandBuffer[s_commandBufferIndex] = 0;
				s_commandBufferIndex++;
				ret_val = CmdLineProcess(s_commandBuffer);		
				s_commandBufferIndex = 0;		
				usart0_send_string(ErrorCode[ret_val]);
				usart0_send_string("> ");
			}	
			else usart0_send_string("\r\n> ");
		}
		else if ((rxData == 8) || (rxData == 127))	
		{
			if (s_commandBufferIndex > 0) s_commandBufferIndex--;
		}
		else
		{
			s_commandBuffer[s_commandBufferIndex] = rxData;
			s_commandBufferIndex ++;
			if (s_commandBufferIndex > COMMAND_MAX_LENGTH) s_commandBufferIndex= 0;
		}
	}	
}


int Cmd_help(int argc, char *argv[]) {
	tCmdLineEntry *pEntry;

	usart0_send_string("\nAvailable commands\r\n");
	usart0_send_string("------------------\r\n");

	// Point at the beginning of the command table.
	pEntry = &g_psCmdTable[0];

	// Enter a loop to read each entry from the command table.  The
	// end of the table has been reached when the command name is NULL.
	while (pEntry->pcCmd) {
		// Print the command name and the brief description.
		usart0_send_string(pEntry->pcCmd);
		usart0_send_string(pEntry->pcHelp);
		usart0_send_string("\r\n");

		// Advance to the next entry in the table.
		pEntry++;

	}
	// Return success.
	return (CMDLINE_OK);
}
//*****************************************************************************
//
// Format: set_temp channel value
//
//*****************************************************************************
int
Cmd_set_temp(int argc, char *argv[]) 
{
	  if (argc < 3) return CMDLINE_TOO_FEW_ARGS;
	  if (argc >3) return CMDLINE_TOO_MANY_ARGS;
	  uint8_t channel = atoi(argv[1]);
	  if (channel > 2)	return CMDLINE_INVALID_ARG;
	  
	uint16_t	_setpoint = atoi(argv[2]);
	temperature_set_point(_setpoint, channel);
	UARTprintf("Channel %d set point is %d \r\n",channel, _setpoint);
	return CMDLINE_OK;
}
//*****************************************************************************
//
// Format: TEC_ena channel 
//
//*****************************************************************************
int
Cmd_TEC_enable(int argc, char *argv[])
{
		  if (argc < 2) return CMDLINE_TOO_FEW_ARGS;
		  if (argc >2) return CMDLINE_TOO_MANY_ARGS;
		  uint8_t channel = atoi(argv[1]);
		  if (channel > 4)	return CMDLINE_INVALID_ARG;
		  temperature_enable_TEC(channel);
		  return CMDLINE_OK;
}
//*****************************************************************************
//
// Format: TEC_dis channel 
//
//*****************************************************************************
int
Cmd_TEC_disable(int argc, char *argv[])
{
		  if (argc < 2) return CMDLINE_TOO_FEW_ARGS;
		  if (argc >2) return CMDLINE_TOO_MANY_ARGS;
		  uint8_t channel = atoi(argv[1]);
		  if (channel > 4)	return CMDLINE_INVALID_ARG;
		  temperature_disable_TEC(channel);
		  return CMDLINE_OK;
}

//*****************************************************************************
//
// Format: TEC_ena_control channel 
//
//*****************************************************************************
int
Cmd_TEC_enable_auto_control(int argc, char *argv[])
{
		  if (argc < 2) return CMDLINE_TOO_FEW_ARGS;
		  if (argc >2) return CMDLINE_TOO_MANY_ARGS;
		  uint8_t channel = atoi(argv[1]);
		  if (channel > 4)	return CMDLINE_INVALID_ARG;
		  temperature_enable_auto_control_TEC(channel);
		  return CMDLINE_OK;
}

//*****************************************************************************
//
// Format: TEC_dis_control channel 
//
//*****************************************************************************
int
Cmd_TEC_disable_auto_control(int argc, char *argv[])
{
		  if (argc < 2) return CMDLINE_TOO_FEW_ARGS;
		  if (argc >2) return CMDLINE_TOO_MANY_ARGS;
		  uint8_t channel = atoi(argv[1]);
		  if (channel > 4)	return CMDLINE_INVALID_ARG;
		  temperature_disable_auto_control_TEC(channel);
		  return CMDLINE_OK;
}

//*****************************************************************************
//
// Format: get_temp NTC	channel
// Get the temperature from NTC
//
//*****************************************************************************

int
Cmd_get_temp(int argc, char *argv[])
{
	  if  (strcmp(argv[1], "NTC"))	return CMDLINE_INVALID_ARG;
	  if (argc < 3) return CMDLINE_TOO_FEW_ARGS;
	  if (argc >3) return CMDLINE_TOO_MANY_ARGS;
	  uint8_t channel = atoi(argv[2]);
		if (channel > 2)	return CMDLINE_INVALID_ARG;
	 UARTprintf("Temperature from NTC channel %d is %d \r\n",channel, temperature_get_NTC(channel));
	 return CMDLINE_OK;
	 
}
//*****************************************************************************
//
// Format: tec_set_output channel heat_cool(0:COOL, 1: HEAT) voltage(150 mean 1.5)
// set the TEC output manually
//
//*****************************************************************************

int
Cmd_TEC_set_output(int argc, char *argv[])
{

	  if (argc < 4) return CMDLINE_TOO_FEW_ARGS;
	  if (argc >4) return CMDLINE_TOO_MANY_ARGS;
	  uint8_t _heatCool = atoi(argv[2]);
	  uint8_t _channel = atoi(argv[1]);
	  uint16_t	_voltage = atoi(argv[3]);
		if (_channel > 4)	return CMDLINE_INVALID_ARG;
	 temperature_set_TEC_output(_channel, _heatCool, _voltage);
	 return CMDLINE_OK;
	 
}



int
Cmd_get_temp_setpoint(int argc, char *argv[])
{

	if (argc < 2) return CMDLINE_TOO_FEW_ARGS;
	if (argc >2) return CMDLINE_TOO_MANY_ARGS;
	uint8_t _channel = atoi(argv[1]);
	uint16_t	_setpoint;
	if (_channel > 2)	return CMDLINE_INVALID_ARG;
	_setpoint = temperature_get_setpoint(_channel);
	UARTprintf("Setpoint channel %d is %d \r\n", _channel, _setpoint);
	return CMDLINE_OK;
	
}
void	command_create_task(void)
{
	SCH_TASK_CreateTask(&s_CommandTaskContext.taskHandle, &s_CommandTaskContext.taskProperty);
}

void	command_send_splash(void)
{
//	    usart0_send_string("                                                                   \r\n");
	    usart0_send_string("\r\n");
//	    usart0_send_string("                                                                   \r\n");
	    usart0_send_string("\r\n");
	    usart0_send_string("...................................................................\r\n");
	    usart0_send_string("\r\n");
	    usart0_send_string("...................................................................\r\n");
	    usart0_send_string("..........                                               ..........\r\n");
	    usart0_send_string("\r\n");
	    usart0_send_string("..........  ____                       _          _      ..........\r\n");
	    usart0_send_string(".......... / ___| _ __   __ _  ___ ___| |    __ _| |__   ..........\r\n");
	    usart0_send_string(".......... \\___ \\| '_ \\ / _` |/ __/ _ \\ |   / _` | '_ \\  ..........\r\n");
	    usart0_send_string("..........  ___) | |_) | (_| | (_|  __/ |__| (_| | |_) | ..........\r\n");
	    usart0_send_string(".......... |____/| .__/ \\__,_|\\___\\___|_____\\__,_|_.__/  ..........\r\n");
	    usart0_send_string("..........       |_|                                     ..........\r\n");
	    usart0_send_string("..........                                               ..........\r\n");
	    usart0_send_string("..........        _____ ____  ____    ____    ___        ..........\r\n");
	    usart0_send_string("..........       | ____|  _ \\/ ___|  |___ \\  / _ \\       ..........\r\n");
	    usart0_send_string("..........       |  _| | |_) \\___ \\    __) || | | |      ..........\r\n");
	    usart0_send_string("..........       | |___|  __/ ___) |  / __/ | |_| |      ..........\r\n");
	    usart0_send_string("..........       |_____|_|   |____/  |_____(_)___/       ..........\r\n");
	    usart0_send_string("..........                                               ..........\r\n");
	    usart0_send_string("..........                                               ..........\r\n");
	    usart0_send_string("...................................................................\r\n");
	    usart0_send_string("...................................................................\r\n");
//	    usart0_send_string("                                                                   \r\n");
		usart0_send_string("> ");
}