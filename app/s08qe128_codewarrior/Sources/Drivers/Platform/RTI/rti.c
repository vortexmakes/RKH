/*
 *	rti.c
 *		Routines handle RTI service
 *
 *	Programmer: Darío S. Baliña.
 */
#include "mytypes.h"
#include "sleep.h"
#include "watchdog.h"
#include "rti.h"
#include "ioports.h"
#include "enaint.h"
#include "reset.h"
#include "maintime.h"
#include "cop.h"
#include "stack.h"
#include "rksys.h"

#define _reset_mcu() {asm bgnd;}

static MUInt enable_maintime = 1;

/*
 *	rti_handler: RTI Interrupt Service Routine.
 */
void
interrupt 24 
rti_handler( void )
{
	RTCSC_RTIF = 1;

	rktrace_interrupt_in( 24 );

	kick_cop_wdog();
	kick_watchdog();

	if( enable_maintime )
		main_timer_interrupt();

	rktrace_interrupt_out( 24 );
}

void
init_timer_hardware( unsigned short irq_time )
{
	enable_maintime = 1;
}

void
rti_ctrl( MUInt ctrl )
{
	enable_maintime = ctrl;	
}
