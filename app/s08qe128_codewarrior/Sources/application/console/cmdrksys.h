/*
 * 	cmdrksys.h
 */


#include "mytypes.h"
#include "command.h"


#define CMD_TBL_RKSYS	MK_CMD_TBL_ENTRY(						\
	"rksys",	5,	3,	do_rksys,								\
	"\r\nrksyst\t- suspend/kill/resume the available task\r\n"	\
	"\t- info: show task information\r\n",						\
	"\t- usage: [command] [task id]\r\n"						\
	NULL														\
    ),


MInt do_rksys( const CMD_TABLE *p, MUInt argc, char *argv[] );
