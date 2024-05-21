/*
 * command.h
 *
 * Created: 5/19/2024 8:38:57 PM
 *  Author: Admin
 */ 


#ifndef COMMAND_H_
#define COMMAND_H_

#include "cmdline.h"
#include <stdint.h>
#include <stdbool.h>
#include	<string.h>

#define	COMMAND_MAX_LENGTH	128

void	command_init(void);
void	command_send_splash(void);
int
Cmd_help(int argc, char *argv[]);

int Cmd_set_temp(int argc, char *argv[]);
void	command_create_task(void);

int
Cmd_get_temp(int argc, char *argv[]);
int
Cmd_TEC_enable(int argc, char *argv[]);
int
Cmd_TEC_disable(int argc, char *argv[]);
int
Cmd_TEC_enable_auto_control(int argc, char *argv[]);
int
Cmd_TEC_disable_auto_control(int argc, char *argv[]);

int
Cmd_TEC_set_output(int argc, char *argv[]);

int
Cmd_get_temp_setpoint(int argc, char *argv[]);
#endif /* COMMAND_H_ */