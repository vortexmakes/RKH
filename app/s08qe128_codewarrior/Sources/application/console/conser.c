/*
 *	conser.c
 */


#include "mytypes.h"
#include "console.h"
#include "rkutils.h"
#include "qdata.h"
#include "queue.h"
#include "task.h"
#include "serial.h"

#if CON_MSDOS_PLATFORM
#include <stdio.h>
#include <conio.h>
#endif


void
conser_init( void )
{
	dclrscr();
}


void
conser_putc( const char c )
{
	put_char( COM2, c );
}


void
conser_puts( const char *s )
{
	while( *s )
		put_char( COM2, *s++ );
}
