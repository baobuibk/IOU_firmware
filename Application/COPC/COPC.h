/*
 * COPC.h
 *
 * Created: 5/18/2024 6:04:17 AM
 *  Author: Admin
 */ 


#ifndef COPC_H_
#define COPC_H_

#include "fsp.h"
#include "uart.h"
#define		PDU_ADDRESS	2
// Addresses
#define FSP_ADR_COPC	                1       /**< COPC module address. */
#define FSP_ADR_PMU                     2       /**< PMU module address. */
#define FSP_ADR_PDU                     3       /**< PDU module address. */
#define FSP_ADR_CAM	                    4       /**< CAM module address. */
#define FSP_ADR_IOU	`	                5       /**< IOU module address. */


typedef struct _COMMON_FRAME_
{
	uint8_t Cmd;	
}COMMON_FRAME;


// Union to encapsulate all frame types

typedef union _COPC_Sfp_Payload_ {
	COMMON_FRAME							commonFrame;
} COPC_Sfp_Payload_t;
void	COPC_init(void);
void	COPC_create_task(void);

#endif /* COPC_H_ */