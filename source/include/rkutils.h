/*
 * 	rkutils.h
 */


#ifndef __RKUTILS_H__
#define __RKUTILS_H__


#include "mytypes.h"
#include "rksys.h"
#include <stdarg.h>


void print_format( uchar out, char *fmt, ... );


/*
 * 	rkstart_time_measure:
 *
 * 	Stores the starting time of measurement.
 * 	Note: it is not a reentrant function.
 */

void rkstart_time_measure( void );


/*
 * 	rkend_time_measure:
 *
 * 	Stores the end time of measurement.
 * 	Note: it is not a reentrant function.
 */

void rkend_time_measure( void );


/*
 * 	rkget_time_measure:
 *
 * 	Returns the measurement of execution time.
 */

RTCOUNTER_T rkget_time_measure( void );


#endif
