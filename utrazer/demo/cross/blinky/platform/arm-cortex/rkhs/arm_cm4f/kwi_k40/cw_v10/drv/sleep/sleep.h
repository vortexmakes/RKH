
/*
 * 			PUBLIC HEADER FOR APPLICATION
 */

/*
 *	sleep.h
 */

#ifndef __SLEEP_H__
#define __SLEEP_H__

#include "rkh.h"

void sleep( unsigned short msec );
void sleep_tick( void );

#define _time_delay(x)	sleep(x/RKH_TICK_RATE_MS)

#endif
