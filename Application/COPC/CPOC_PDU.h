/*
 * CPOC_PDU.h
 *
 * Created: 5/22/2024 2:43:48 PM
 *  Author: Admin
 */ 


#ifndef CPOC_PDU_H_
#define CPOC_PDU_H_
#include <stdint.h>


typedef struct _PDU_SINGLE_POWER_CONTROL_FRAME_
{
	uint8_t Cmd;              /* The command class */
	uint8_t PowerSource : 7;                   /* power source */
	uint8_t Status		:1;						/* 1: ON, 0: OFF */
} PDU_SINGLE_POWER_CONTROL_FRAME;

typedef struct _PDU_SINGLE_POWER_STATUS_REQUEST_FRAME_
{
	uint8_t Cmd;              /* The command class */
	uint8_t PowerSource;                   /* power source */

} PDU_SINGLE_POWER_STATUS_REQUEST_FRAME;

typedef struct _PDU_SINGLE_POWER_STATUS_REPORT_FRAME_
{
	uint8_t		Cmd;								/* The command class */
	uint8_t		PowerSource : 7;                   /* power source */
	uint8_t		Status		:1;						/* 1: ON, 0: OFF */
	uint16_t	Current_Val;
}	PDU_SINGLE_POWER_STATUS_REPORT_FRAME;



#endif /* CPOC_PDU_H_ */