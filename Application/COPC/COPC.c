/*
 * COPC.c
 *
 * Created: 5/18/2024 6:29:56 AM
 *  Author: Admin
 */ 
#include "scheduler.h"
#include "COPC.h"
#include "fsp.h"

static	void COPC_task_update(void);
volatile static	ringbuffer_t *p_COPCBuffer;
static	fsp_packet_t	s_COPC_RxFspPacket;
static	fsp_packet_t	s_COPC_TxFspPacket;

typedef struct COPC_TaskContextTypedef
{
	SCH_TASK_HANDLE               taskHandle;
	SCH_TaskPropertyTypedef       taskProperty;
} COPC_TaskContextTypedef;

static COPC_TaskContextTypedef           s_COPC_task_context =
{
	SCH_INVALID_TASK_HANDLE,                 // Will be updated by Schedular
	{
		SCH_TASK_SYNC,                      // taskType;
		SCH_TASK_PRIO_0,                    // taskPriority;
		10,                                // taskPeriodInMS, call the task to check buffer every 10ms
										//with baudrate of 9600, buffer size can be less than 10 bytes
		COPC_task_update                // taskFunction;
	}
};

void COPC_process_command(fsp_packet_t	*s_COPC_FspPacket);


void	COPC_init(void)
{	
	usart1_init();
	fsp_init(PDU_ADDRESS);
	p_COPCBuffer = uart_get_uart1_rx_buffer_address();

}

static void COPC_task_update(void)
{
	char rxData;
	while (! rbuffer_empty(p_COPCBuffer))
	{

		rxData = rbuffer_remove(p_COPCBuffer);
		switch ( fsp_decode(rxData,&s_COPC_RxFspPacket))
		{
			//process command
            case FSP_PKT_NOT_READY:
				break;
            case FSP_PKT_READY:
				COPC_process_command(&s_COPC_RxFspPacket);	            
	            break;
            case FSP_PKT_INVALID:
				
	            break;
            case FSP_PKT_WRONG_ADR:

	            break;
            case FSP_PKT_ERROR:

	            break;
            default:

	           break;
			
		}
	}
}

void	COPC_create_task(void)
{
	COPC_init();
	SCH_TASK_CreateTask(&s_COPC_task_context.taskHandle, &s_COPC_task_context.taskProperty);
}

void COPC_process_command(fsp_packet_t	*s_COPC_FspPacket)
{
	COPC_Sfp_Payload_t	*s_pCOPC_Sfp_Payload = &(s_COPC_FspPacket->payload);
	switch (s_pCOPC_Sfp_Payload->commonFrame.Cmd)
		{
			case	FSP_CMD_PDU_SINGLE_POWER_CONTROL:
				{
							
				}
		}
}

