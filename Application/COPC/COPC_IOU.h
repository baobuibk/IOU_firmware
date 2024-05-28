/*
 * COPC_IOU.h
 *
 * Created: 5/21/2024 10:40:38 PM
 *  Author: Admin
 */ 


#ifndef COPC_IOU_H_
#define COPC_IOU_H_
#include "fsp.h"
#include "uart.h"


typedef struct _COPC_SET_TEMP_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		channel;
	uint16_t	setpoint;
}COPC_SET_TEMP_COMMAND_FRAME;

typedef struct _COPC_GET_TEMP_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		channel;
	uint8_t		setpoint;
}COPC_GET_TEMP_COMMAND_FRAME;

typedef struct _COPC_GET_TEMP_SETPOINT_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		channel;

}COPC_GET_TEMP_SETPOINT_COMMAND_FRAME;

typedef struct _COPC_TEC_ENA_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		channel;

}COPC_TEC_ENA_COMMAND_FRAME_;

typedef struct _COPC_TEC_DIS_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		channel;

}COPC_TEC_DIS_COMMAND_FRAME_;

typedef struct _COPC_TEC_ENA_AUTO_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		channel;

}COPC_TEC_ENA_AUTO_COMMAND_FRAME_;

typedef struct _COPC_TEC_DIS_AUTO_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		channel;

}COPC_TEC_DIS_AUTO_COMMAND_FRAME_;


typedef struct _COPC_SET_TEC_OUTPUT_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		channel;
	uint8_t		heat_cool;
	uint16_t	voltage;				//250 mean 2.5V
}SET_TEC_OUTPUT_COMMAND_FRAME;

typedef struct _COPC_IR_SET_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		duty;			//0 to 100

}COPC_IR_SET_COMMAND_FRAME;

typedef struct _COPC_NEO_SET_RGB_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		red;			//0 to 255
	uint8_t		green;			//0 to 255
	uint8_t		blue;			//0 to 255

}COPC_NEO_SET_RGB_COMMAND_FRAME;

typedef struct _COPC_NEO_SET_BRIGHRNESS_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		duty;			//0 to 100

}COPC_NEO_SET_BRIGHRNESS_COMMAND;

typedef struct _COPC_GET_IOU_STATUS_COMMAND_FRAME_
{
	uint8_t		Cmd;
	uint8_t		duty;			

}COPC_GET_IOU_STATUS_COMMAND_FRAME;

typedef struct _IOU_GET_TEMP_RESPONSE_FRAME_
{
	uint8_t			Cmd;
	uint8_t			channel;
	uint16_t		temperature;
}IOU_GET_TEMP_RESPONSE_FRAME;

#endif /* COPC_IOU_H_ */