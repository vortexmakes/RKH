/*
 *	watchdog.c
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 26/05/06.
 */
#include "mytypes.h"
#include "watchdog.h"
#include "reset.h"
#include "rksys.h"
#include "ioports.h"
#include "rti.h"
#include "cop.h"

#define BWATCHDOG_TICK	(WATCHDOG_TICK/WATCHDOG_BASE)

static short watchdog_tick = BWATCHDOG_TICK;

/*
 *	kick_watchdog: Kicks The Watchdog Counter
 */
void
kick_watchdog( void )
{
	enter_critical();
	if( watchdog_tick <= 0 )
		rktrace_usr_wd();

	kick_cop_wdog();
	watchdog_tick = BWATCHDOG_TICK;
	exit_critical();
}

/*
 *	check_watchdog: Checks The Watchdog Counter, if reach to 0 reset.
 */
void
check_watchdog( void )
{
	if( (watchdog_tick !=0) && (--watchdog_tick <= 0) )
		rktrace_usr_wd();
}




