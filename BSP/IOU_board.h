/*
 * PDU_board.h
 *
 * Created: 5/15/2024 11:17:18 AM
 *  Author: Admin
 */ 


#ifndef IOU_BOARD_H_
#define IOU_BOARD_H_

#define F_CPU 8000000UL

#define	IOU_HW_V1_0_0



#ifdef	IOU_HW_V1_0_0

#define LED1_DATA_PORT		PORTF
#define LED1_DIR_PORT		DDRF
#define LED1_PIN			PINF2

#define LED2_DATA_PORT		PORTF
#define LED2_DIR_PORT		DDRF
#define LED2_PIN			PINF3

#define SPI_DDR			DDRB
#define SPI_PORT		PORTB
#define SPI_MISO		PINB3
#define SPI_MOSI		PINB2
#define SPI_SCK			PINB1

#define MCP4921_SS0_PORT	PORTB
#define MCP4921_SS0_DDR		DDRB
#define MCP4921_SS0_PIN		PINB0

#define MCP4921_SS1_PORT	PORTB
#define MCP4921_SS1_DDR		DDRB
#define MCP4921_SS1_PIN		PINB4

#define MCP4921_SS2_PORT	PORTC
#define MCP4921_SS2_DDR		DDRC
#define MCP4921_SS2_PIN		PINC4

#define MCP4921_SS3_PORT	PORTC
#define MCP4921_SS3_DDR		DDRC
#define MCP4921_SS3_PIN		PINC5

#define MCP4921_LDAC_PORT	PORTD
#define MCP4921_LDAC_DDR	DDRD
#define MCP4921_LDAC_PIN	PINC7

#define TEC_SHUTDOWN_TEC0_PORT	PORTB
#define TEC_SHUTDOWN_TEC0_DDR	DDRB
#define TEC_SHUTDOWN_TEC0_PIN	PINB5

#define TEC_SHUTDOWN_TEC1_PORT	PORTE
#define TEC_SHUTDOWN_TEC1_DDR	DDRE
#define TEC_SHUTDOWN_TEC1_PIN	PINE5

#define TEC_SHUTDOWN_TEC2_PORT	PORTE
#define TEC_SHUTDOWN_TEC2_DDR	DDRE
#define TEC_SHUTDOWN_TEC2_PIN	PINE4

#define TEC_SHUTDOWN_TEC3_PORT	PORTE
#define TEC_SHUTDOWN_TEC3_DDR	DDRE
#define TEC_SHUTDOWN_TEC3_PIN	PINE3

#define TPL5010_DONE_PORT		PORTE
#define TPL5010_DONE_DDR		DDRE
#define TPL5010_DONE_PIN		PINE2

#define TPL5010_WAKE_PORT		PORTE
#define TPL5010_WAKE_DDR		DDRE
#define TPL5010_WAKE_PIN		PINE6

#endif

#endif /* PDU_BOARD_H_ */