/*
 * temperature.h
 *
 * Created: 5/20/2024 6:02:47 AM
 *  Author: Admin
 */ 


#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

void	temperature_init(void);
void	temperature_create_task(void);
void	temperature_set_point(uint16_t	setpoint, uint8_t channel);
uint16_t	temperature_get_NTC(uint8_t	channel);
void	temperature_enable_auto_control_TEC(uint8_t	channel);
void	temperature_disable_auto_control_TEC(uint8_t	channel);
void	temperature_enable_TEC(uint8_t	channel);
void	temperature_disable_TEC(uint8_t	channel);
void	temperature_enable_channel(uint8_t channel);
void	temperature_disable_channel(uint8_t channel);
void    temperature_set_TEC_output(uint8_t channel, uint8_t HeatCool, uint16_t	voltage);
uint16_t	temperature_get_setpoint(uint8_t	channel);
#endif /* TEMPERATURE_H_ */