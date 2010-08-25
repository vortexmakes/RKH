/*
 * 	console.c
 */


#include "mytypes.h"
#include "conser.h"
#include "command.h"
#include "console.h"
#include "contick.h"
#include "rkutils.h"
#include "rksys.h"
#include <stdlib.h>
#include <string.h>


#if CON_CONFIG_CMD_TOUT
#define set_abort_shell()		(abort_shell = 1)
#else 
#define set_abort_shell()
#endif


#if CON_CONFIG_CMD_TOUT
#define clear_abort_shell()		(abort_shell = 0)
#else 
#define clear_abort_shell()
#endif


#if CON_CONFIG_CMD_TOUT
#define is_abort_shell()		(abort_shell != 0)
#else 
#define is_abort_shell()
#endif


/*	Define the size of console buffer */

#define CBSIZE    				32


/*	Length of prompt string */

#define	PROMPT_LEN				sizeof( prompt )


/*	Prompt string */

static const char prompt[] = ">";


/* 	Used to expand TABs */

static const char tab_seq[] = "        ";


/*	Erase sequence */

#if CON_DELETE_CHAR

static const char erase_seq[] = "\b \b";

#endif


/*	Used to store the command's arguments */

static char *argv[ MAXARGS + 1 ];


/*	Used to maintain the input char from attached serial channel */

static char console_buffer[ CBSIZE ];


/*	Console buffer index */

static MUInt n;


/*	Output column counter */

static MUInt col;


/*	Pointer to console buffer */

static char *p;


/*	
 *	If CON_CONFIG_CMD_TOUT is defined and command timer elapsed,
 *	command shell is aborted.
 */

#if CON_CONFIG_CMD_TOUT 

static MUInt abort_shell;

#endif

/*
 * 	Return codes for 'process_in_char' function.
 *	They are negative numbers.
 */

enum
{
	CTRL_C = 1, PARSING
};


/*
 * 	print_prompt:
 *
 * 	Print prompt string on console and initialize
 * 	for next command entry.
 */

static
void
print_prompt( void )
{
	n = 0;
	p = console_buffer;
	if( prompt != NULL )
	{
		conser_puts( prompt );
		col = PROMPT_LEN;
		return;
	}
	col = 0;
}


/*
 * 	delete_char:
 * 	
 * 	Delete one character of console. Check '\t' character.
 */

#if CON_DELETE_CHAR
static 
char * 
delete_char( char *buffer, char *p, MUInt *colp, MUInt *np )
{
	char *s;

	if( *np == 0 ) 
	{
		conser_putc( '\a' );
		return p;
	}

	if( *( --p ) == '\t' )
   	{					
		while( *colp > PROMPT_LEN )		/* delete whole line on console */
		{
			conser_puts( erase_seq );
			--( *colp );
		}
		for( s = buffer; s < p; ++s )	/* retype whole line on console */
			if( *s == '\t' )
		   	{
				conser_puts( tab_seq + ( ( *colp ) & 07 ) );
				*colp += 8 - ( ( *colp ) & 07 );
			} 
			else
		   	{
				++( *colp );
				conser_putc( *s );
			}
	} 
	else
   	{
		conser_puts( erase_seq );
		--( *colp );
	}
	--( *np );
	return p;
}
#endif

/*
 * 	process_in_char:
 *
 * 	Every received character from attached
 * 	serial channel is parsed on-line.
 *
 * 	Returns:
 *
 * 	-CTRL_C		- received ^C
 * 	-PARSING	- continue
 * 	>= 0		- received '\r' or '\n'
 */

static
MInt
process_in_char( char c )
{
	MUInt column;

	switch( c )
	{
		//case '\r':
		case '\n':									/* Enter */
			*p = '\0';
			conser_puts( "\r\n" );
			return (MInt)(p - console_buffer);
		case 0x03:									/* ^C - abort */
		   	return -CTRL_C;	
		case 0x15:									/* ^U - erase line	*/
#if CON_DELETE_CHAR
			while( col > PROMPT_LEN ) 
			{
				conser_puts( erase_seq );
				--col;
			}
			p = console_buffer;
			n = 0;
#endif
			return -PARSING;
		case 0x17:									/* ^W - erase word 	*/
#if CON_DELETE_CHAR
			p = delete_char( console_buffer, p, &col, &n );
			while( n > 0 && *p != ' ' ) 
				p = delete_char( console_buffer, p, &col, &n );
#endif
			return -PARSING;
		case 0x08:									/* ^H  - backspace	*/
		case 0x7F:									/* DEL - backspace	*/
#if CON_DELETE_CHAR
			p = delete_char( console_buffer, p, &col, &n );
#endif
			return -PARSING;
		default:		
			/* Must be a normal character then */
			if( n < CBSIZE - 2 )
			{
				if( c == '\t' ) 					/* Expand TABs */
				{
					column = col & 7;
					conser_puts( tab_seq + column );
					col += 8 - column;
				}
				else  								/* Echo input	*/
				{
					++col;
					conser_putc( c );
				}
				*p++ = c;
				++n;
			}
			else									/* Buffer full */
				conser_putc('\a');
			return -PARSING;
	}
}


/*
 * 	parse_line:
 *
 * 	Parse the received line. Store and prepare all args
 * 	into argv parameter. Then return the actual number of args.
 * 	Skip any white space (' ' or '\t'). The character '\0' is
 * 	the end of line.
 */

static
MUInt
parse_line( char *line, char *argv[] )
{
	MUInt nargs;
	char **pargv;

	for( pargv = argv, nargs = 0; nargs < MAXARGS; ++pargv )
	{
		/* Skip any white space */

		while( *line == ' ' || *line == '\t' )
			++line;

		/* End of line, no more args */

		if( *line == '\0' )
		{
			pargv = NULL;
			return nargs;
		}

		/* Begin of argument string	*/

		++nargs;
		*pargv = line;

		/* Find end of string */

		while( *line && *line != ' ' && *line != '\t' )
			++line;

		/* End of line, no more args */

		if( *line == '\0' )
		{
			pargv = NULL;
			return nargs;
		}

		/* Terminate current arg */

		*line++ = '\0';
	}
#if CON_PRINT_FORMATS
	conser_printf( (COM2, "** Too many args (max. %d) **\r\n", MAXARGS) );
#else
	conser_puts( "** Too many args **\n" );
#endif
	return nargs;
}


/*
 * 	run_command:
 *
 * 	Get and find the actual command. If found it, then
 *	get all arguments and pass it to properly callback 
 *	function.
 *
 * 	Returns:
 *	
 *	0,1	- command executed.
 *	-1 	- not executed ( unrecognized or too many args )
 *  If cmd is NULL or "" or longer than CBSIZE-1 it is 
 *  considered unrecognized.
 */

static
MInt
run_command( char *cmd )
{
	const CMD_TABLE *cmdtp;
	char *str = cmd;
	MUInt argc;

	/* Empty command */

	if( !cmd || !*cmd )
		return -1;

	if( strlen( cmd ) >= CBSIZE )
	{
		conser_puts( "## Command too long!\n" );
		return -1;
	}

	/* Extract arguments */

	argc = parse_line( str, argv );

	/* Look up command in command table */

	if( ( cmdtp = find_cmd( *argv ) ) == NULL )
	{
#if CON_PRINT_FORMATS
		conser_printf( (COM2, "Unknown command '%s' - try 'help'\r\n", *argv) );
#else
		conser_puts( "Unknown command - try 'help'\n\r" );
#endif
		return -1;	/* Give up after bad command */
	}

	/* Found - Check max args */

	if( argc > cmdtp->maxargs )
	{
#if CON_PRINT_FORMATS
		conser_printf( (COM2, "Usage:\n%s\r\n", cmdtp->usage) );
#endif
		return -1;
	}

	/* OK - Call function to do the command */

	if( ( cmdtp->cmd )( cmdtp, argc, argv ) != 0 )
		return -1;

	/* Print prompt */

	print_prompt();

	return 0;
}


/*
 * 	do_console:
 *
 * 	Check if key already pressed and
 * 	and send it to command shell process.
 *
 * 	Returns:
 *
 * 	0 - successfully
 *	1 - abort command shell
 */

static
MUInt
do_console( char c )
{
	MInt r;

	if( ( r = process_in_char( c ) ) >= 0 && 
			run_command( console_buffer ) < 0 )
	{
		print_prompt();
		return 0;
	}
	return r == -CTRL_C;
}


MUInt
command_shell( char c )
{
#if CON_CONFIG_CMD_TOUT
	if( is_abort_shell() && is_cmd_timeout() )
		return CON_ABORT_SHELL;
	clear_abort_shell();
#endif
	return do_console( c ) ? CON_ABORT_SHELL : CON_CONTINUE;
}


void
init_command_shell( void )
{
	conser_init();
	set_abort_shell();
#if CON_CONFIG_CMD_TOUT
	set_cmd_timeout( CON_CONFIG_CMD_TIME );
#endif
	print_prompt();
}


#if CON_EXAMPLE

#define forever			for(;;)

void
main( void )
{
	init_command_shell();

	forever
	{
		if( command_shell() == CON_ABORT_SHELL )
			return;
	}
}

#endif
