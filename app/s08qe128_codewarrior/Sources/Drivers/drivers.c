/*
 *	drivers.c
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 26/05/06.
 */

#include "drivers.h"
#include "platform.h"
#include "maintime.h"
#include "serial.h"
#include "cop.h"
#include "mcuinit.h"
#include "rksys.h"


void
drivers_init(void)
{
	MCU_init();
	platform_init();
	rkinit_critical();
	init_main_timer_interrupt();
	serial_init( COM1 ); 	 
	serial_init( COM2 );
	kick_cop_wdog();
}
