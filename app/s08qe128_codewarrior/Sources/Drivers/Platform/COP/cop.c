/*
 *	cop.c
 *
 *	Routines for COP Module.
 *
 */

#include "derivative.h"
#include "cop.h"

#define _kick_cop_wdog() __RESET_WATCHDOG()

/*
 *	kick_cop: Feeds the COP watchdog
 */
void
kick_cop_wdog( void )
{
	_kick_cop_wdog();
}

