/*
 * temperature.c
 *
 * Created: 5/20/2024 6:03:07 AM
 *  Author: Admin
 */ 

#include "scheduler.h"
#include "IOU_board.h"
#include "ntc_10k.h"
#include "temperature.h"
#include "MCP4921.h"
#include "TEC.h"
#include "uart.h"

const	uint16_t Kp = 2;
#define	DAC_at_2_5		3103

static	void	temperature_task_update(void);
typedef struct _Temperature_TaskContextTypedef_
{
	SCH_TASK_HANDLE               taskHandle;
	SCH_TaskPropertyTypedef       taskProperty;
} Temperature_TaskContextTypedef;

typedef	struct _Temperature_CurrentStateTypedef_
{
	uint16_t					channel_temperature[2];
	uint16_t					channel_temperature_setpoint[2];
	uint16_t				DAC_channel_Val[4];
	uint8_t					channel_enabled[4];
	uint8_t					channel_auto_control[4];
}Temperature_CurrentStateTypedef;

static Temperature_TaskContextTypedef           s_temperature_task_context =
{
	SCH_INVALID_TASK_HANDLE,                 // Will be updated by Schedular
	{
		SCH_TASK_SYNC,                      // taskType;
		SCH_TASK_PRIO_0,                    // taskPriority;
		1000,                                // taskPeriodInMS;
		temperature_task_update                // taskFunction;
	}
};

static	Temperature_CurrentStateTypedef	s_Temperature_CurrentState = 
{

	{
	250,
	250
	},
	{
	250,
	250
	},			//set point is 25.0
	{DAC_at_2_5,
	DAC_at_2_5,
	DAC_at_2_5,
	DAC_at_2_5},
	{0,
	0,
	0,
	0},
	{0,
	0,
	0,
	0}
	};

void	temperature_init(void)
{
	uint8_t	idx;
	init_adc();
	TEC_init();
	MCP4921_init();
	SPI_Init();

	for(idx =0; idx < 4; idx ++)	TEC_shutdown(idx);
	uint16_t	data = DAC_at_2_5;
	MCP4291_set_output(data, 0, 0, 1, 0);	//enable channel 0
//	TEC_enable(0);
//	s_Temperature_CurrentState.channel_enabled[0] = 1;
}

void	temperature_enable_channel(uint8_t channel)
{
	TEC_enable(channel);
	s_Temperature_CurrentState.channel_enabled[channel] = 1;
}

void	temperature_disable_channel(uint8_t channel)
{
	TEC_shutdown(channel);
	s_Temperature_CurrentState.channel_enabled[channel] = 0;
}

static	void	temperature_task_update(void)
{
	uint16_t		_channel0_temperature = get_temperature(0);
	uint16_t		_channel1_temperature = get_temperature(1);
	
//_channel0_temperature = 230;		//230 mean 23.0
	

	uint16_t		_temperature_setpoint_channel0 = s_Temperature_CurrentState.channel_temperature_setpoint[0];
	uint16_t		_temperature_setpoint_channel1 = s_Temperature_CurrentState.channel_temperature_setpoint[1];
	int16_t		_DAC_channel0_Val;
	int16_t		_DAC_channel1_Val;
		s_Temperature_CurrentState.channel_temperature[0] = _channel0_temperature;
		s_Temperature_CurrentState.channel_temperature[1] = _channel1_temperature;
//		UARTprintf("current temp = %d and set point = %d \r\n", _channel0_temperature, _temperature_setpoint );
		if ((s_Temperature_CurrentState.channel_enabled[0]) && (s_Temperature_CurrentState.channel_auto_control[0]))
		{
			if (_channel0_temperature > _temperature_setpoint_channel0)	//provide higher V+ voltage to make closer to 2.5V
			{
//				UARTprintf("Increase DAC \r\n"); 
				_DAC_channel0_Val = s_Temperature_CurrentState.DAC_channel_Val[0] + Kp*(_channel0_temperature - _temperature_setpoint_channel0);
			}
			else 
			{
//				UARTprintf("Decrease DAC \r\n"); 
				_DAC_channel0_Val = s_Temperature_CurrentState.DAC_channel_Val[0] - Kp*(_temperature_setpoint_channel0 - _channel0_temperature);	
			}
			if (_DAC_channel0_Val < 0)	_DAC_channel0_Val = 0;
			if (_DAC_channel0_Val > 0x0FFFFF)	_DAC_channel0_Val = 0x0FFF;
			MCP4291_set_output(_DAC_channel0_Val, 0, 0, 1, 0);
			s_Temperature_CurrentState.DAC_channel_Val[0] = _DAC_channel0_Val;
//			dummy = _channel0_temperature;
//			UARTprintf("temperature channel 0 is %d Celcius \r\n", dummy); 
			
		}
		if ((s_Temperature_CurrentState.channel_enabled[1]) && s_Temperature_CurrentState.channel_auto_control[1])
		{
			if (_channel1_temperature > _temperature_setpoint_channel1)			//provide higher V+ voltage to make closer to 2.5V
			{
				_DAC_channel1_Val = s_Temperature_CurrentState.DAC_channel_Val[1] + Kp*(_channel1_temperature - _temperature_setpoint_channel1);
			}
			else _DAC_channel1_Val = s_Temperature_CurrentState.DAC_channel_Val[1] - Kp*(_channel1_temperature - _temperature_setpoint_channel1);
			if (_DAC_channel1_Val < 0)			_DAC_channel1_Val = 0;
			if (_DAC_channel1_Val > 0x0FFFFF)	_DAC_channel1_Val = 0x0FFF;	
			MCP4291_set_output(_DAC_channel1_Val, 0, 0, 1, 1);	
			s_Temperature_CurrentState.DAC_channel_Val[1] = _DAC_channel1_Val;
		}
		
}

void	temperature_create_task(void)
{
	SCH_TASK_CreateTask(&s_temperature_task_context .taskHandle, &s_temperature_task_context .taskProperty);
}

void	temperature_set_point(uint16_t	setpoint, uint8_t channel)
{
	s_Temperature_CurrentState.channel_temperature_setpoint[channel] = setpoint;
}

uint16_t	temperature_get_NTC(uint8_t	channel)
{
	return s_Temperature_CurrentState.channel_temperature[channel];
}

void	temperature_enable_TEC(uint8_t	channel)
{
	TEC_enable(channel);
	s_Temperature_CurrentState.channel_enabled[channel] = 1;
}

void	temperature_disable_TEC(uint8_t	channel)
{
	TEC_shutdown(channel);
	s_Temperature_CurrentState.channel_enabled[channel] = 0;
}

void	temperature_enable_auto_control_TEC(uint8_t	channel)
{
	s_Temperature_CurrentState.channel_auto_control[channel] = 1;
}

void	temperature_disable_auto_control_TEC(uint8_t	channel)
{
	s_Temperature_CurrentState.channel_auto_control[channel] = 0;
}
// set the output of the TEC manually
//@param	channel: 0-3
//@param	HeatCool: 1 HEAT, 0 COOL
//@voltage	Real Voltage multiply with 100
void    temperature_set_TEC_output(uint8_t channel, uint8_t HeatCool, uint16_t	voltage)
{
	uint32_t	_delta = ((uint32_t)voltage * 4096) / 759;
	uint32_t	_adcVal ;
	if (HeatCool == 1)		//want HEAT
	{
		_adcVal = 1551 - _delta;
	}
	else 
	{
		_adcVal = 1551 + _delta;
	}
	_adcVal = _adcVal >> 1;
	s_Temperature_CurrentState.DAC_channel_Val[channel] = _adcVal;
	MCP4291_set_output((uint16_t)_adcVal, 0, 1, 1, channel);
}

uint16_t	temperature_get_setpoint(uint8_t	channel)
{
	return s_Temperature_CurrentState.channel_temperature_setpoint[channel];
}