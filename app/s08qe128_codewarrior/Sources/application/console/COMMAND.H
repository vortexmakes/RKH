/*
 *	command.h
 */


#ifndef __COMMAND_H__
#define __COMMAND_H__


#include "mytypes.h"


/*	Maximum arguments to execute a command */

#define MAXARGS				3


/*	Help info for every command. Used by 'help'	command */

#define LONGHELP			0


/*	Abbreviated length for every command */

#define ABBREVIATED			0


/*	Includes 'echo' command */

#define ECHO				1


/*	Includes 'help' command */

#define HELP				0


#if	LONGHELP
#define	MK_CMD_TBL_ENTRY(name,lmin,maxargs,cmd,usage,help)	\
				{ name, lmin, maxargs, cmd, usage, help }
#else
#define	MK_CMD_TBL_ENTRY(name,lmin,maxargs,cmd,usage,help)	\
				{ name, lmin, maxargs, cmd, usage }
#endif


typedef struct cmd_tbl_s
{
	char *name;			/* command name					*/
	MUInt lmin;			/* minimum abbreviated length	*/
	MUInt maxargs;		/* maximum number of arguments	*/
	MInt (*cmd)( const struct cmd_tbl_s *tbl, MUInt argc, char *argv[] );
	char *usage;		/* Usage message	(short)		*/
#if	LONGHELP
	char *help;			/* Help  message	(long)		*/
#endif
} CMD_TABLE;

const CMD_TABLE *find_cmd( const char *cmd );

#endif
