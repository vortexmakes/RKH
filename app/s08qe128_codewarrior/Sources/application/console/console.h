/*
 * 	console.h
 */


#ifndef __CONSOLE_H__
#define __CONSOLE_H__


#define CON_EXAMPLE					0
#define CON_MSDOS_PLATFORM			0
#define CON_PRINT_FORMATS			1
#define CON_DELETE_CHAR				0
#define CON_CONFIG_CMD_TOUT			0
#define CON_CONFIG_CMD_TOUT_MIN 	1
#define CON_CONFIG_CMD_TIME			3 /* seconds */


enum
{
	CON_CONTINUE, CON_ABORT_SHELL
};


/*
 * 	init_command_shell:
 *
 * 	Initialize this module.
 */

void init_command_shell( void );


/*
 * 	command_shell:
 *
 * 	Entry point to use the command shell. Each received 
 * 	character from attached serial channel is parsed on-line.
 * 	If CON_CONFIG_CMD_TOUT is defined and command timer elapsed,
 *	returns timeout and command shell is aborted.
 */

MUInt command_shell( char c );


#endif
