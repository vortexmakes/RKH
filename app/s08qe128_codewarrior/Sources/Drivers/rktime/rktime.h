/*
 *	rktime.h
 */


#ifndef __RKTIME_H__
#define __RKTIME_H__


#include "mytypes.h"


typedef struct
{
	uchar tm_sec;		/* seconds [0,60] */
	uchar tm_min;   	/* minutes [0,59] */
	uchar tm_hour;  	/* hour [0,23] */
	uchar tm_mday;  	/* day of month [1,31] */
	uchar tm_mon;  		/* month of year [0,11] */
	uchar tm_year; 		/* years since [0,99]  */
#if 0
	uchar tm_wday;  	/* day of week [0,6] (Sunday =0) */
	ushort tm_yday;  	/* day of year [0,365] */
	uchar tm_isdst; 	/* daylight savings flag */
#endif
} RK_TIME_T;


void rktime_gettod( RK_TIME_T *pts );


#endif
