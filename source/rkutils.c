/*
 * 	rkutils.c
 */


#include "mytypes.h"
#include "rksys.h"
#include <stdarg.h>
#include <stdio.h>


#if RKSYS_PRINT_FORMAT

static char pfs[ RKSYS_PRINT_FORMAT_SIZE ];


void
print_format( uchar out, char *fmt, ... )
{
	va_list args;

	va_start( args, fmt );
	vsprintf( pfs, fmt, args );
	rkput_string( out, pfs );
	va_end( args );
}

#endif

#if RKSYS_TIME_MEASURE == 1 && RKSYS_RUNTIME_COUNTER == 1

static RTCOUNTER_T start_time, end_time;


void
rkstart_time_measure( void )
{
	start_time = rkget_exec_time();
}


void
rkend_time_measure( void )
{
	end_time = rkget_exec_time();
}


RTCOUNTER_T
rkget_time_measure( void )
{
	return end_time - start_time;
}

#endif
