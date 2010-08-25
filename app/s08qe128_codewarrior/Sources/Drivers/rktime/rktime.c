/*
 *	rktime.c
 */


#include "rktime.h"


static const RK_TIME_T rktm =
{
	0, 	/* seconds [0,60] */
	0,	/* minutes [0,59] */
	24,	/* hour [0,23] */
	1,	/* day of month [1,31] */
	1,	/* month of year [0,11] */
	9	/* years since [0,99]  */
};


void
rktime_gettod( RK_TIME_T *pts )
{
	*pts = rktm;
}
