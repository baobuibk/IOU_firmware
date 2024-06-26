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

#define MCP2515_SS0_PORT	PORTB
#define MCP2515_SS0_DDR		DDRB
#define MCP2515_SS0_PIN		PINB0

#define MCP4921_SS0_PORT	PORTB
#define MCP4921_SS0_DDR		DDRB
#define MCP4921_SS0_PIN		PINB4

#define MCP4921_SS1_PORT	PORTD
#define MCP4921_SS1_DDR		DDRD
#define MCP4921_SS1_PIN		PIND6

#define MCP4921_SS2_PORT	PORTC
#define MCP4921_SS2_DDR		DDRC
#define MCP4921_SS2_PIN		PINC4

#define MCP4921_SS3_PORT	PORTC
#define MCP4921_SS3_DDR		DDRC
#define MCP4921_SS3_PIN		PINC5

#define MCP4921_LDAC_PORT	PORTD
#define MCP4921_LDAC_DDR	DDRD
#define MCP4921_LDAC_PIN	PINC7

#define TEC_SHUTDOWN_TEC0_PORT	PORTG
#define TEC_SHUTDOWN_TEC0_DDR	DDRG
#define TEC_SHUTDOWN_TEC0_PIN	PING0

#define TEC_SHUTDOWN_TEC1_PORT	PORTA
#define TEC_SHUTDOWN_TEC1_DDR	DDRA
#define TEC_SHUTDOWN_TEC1_PIN	PINA7

#define TEC_SHUTDOWN_TEC2_PORT	PORTA
#define TEC_SHUTDOWN_TEC2_DDR	DDRA
#define TEC_SHUTDOWN_TEC2_PIN	PINA4

#define TEC_SHUTDOWN_TEC3_PORT	PORTC
#define TEC_SHUTDOWN_TEC3_DDR	DDRC
#define TEC_SHUTDOWN_TEC3_PIN	PINC6

#define TPL5010_DONE_PORT		PORTE
#define TPL5010_DONE_DDR		DDRE
#define TPL5010_DONE_PIN		PINE2

#define TPL5010_WAKE_PORT		PORTE
#define TPL5010_WAKE_DDR		DDRE
#define TPL5010_WAKE_PIN		PINE6

#define	IR_LED_PORT				PORTB
#define	IR_LED_PIN				PINB6
#define IR_LED_DDR				DDRB

#endif

#endif /* PDU_BOARD_H_ */