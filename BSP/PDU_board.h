/*
 * PDU_board.h
 *
 * Created: 5/15/2024 11:17:18 AM
 *  Author: Admin
 */ 


#ifndef PDU_BOARD_H_
#define PDU_BOARD_H_

#define F_CPU 1000000UL

#define LED1_DATA_PORT		PORTD
#define LED1_DIR_PORT		DDRD
#define LED1_PIN			PIND7

#define LED2_DATA_PORT		PORTD
#define LED2_DIR_PORT		DDRD
#define LED2_PIN			PIND6

#define TEC1_BUCK_EN_DATA_PORT		PORTA
#define TEC1_BUCK_EN_DIR_PORT		DDRA
#define TEC1_BUCK_EN_PIN			PINA0

#define TEC1_BUCK_EN_DATA_PORT		PORTA
#define TEC1_BUCK_EN_DIR_PORT		DDRA
#define TEC1_BUCK_EN_PIN			PINA0


#endif /* PDU_BOARD_H_ */