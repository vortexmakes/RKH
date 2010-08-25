/*
 *	platform.c
 *
 *	Routines for Platform Initialization.
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 26/05/06.
 */

#include "derivative.h"

#include "platform.h"
#include "ioports.h"

void
platform_init(void)
{
	ports_init();
}

void
acknowledge_irqs( void )
{
#ifdef __GB60___
	SRTISC |= 0x40;
#endif
	SCI1S1 = SCI1S1;
	SCI2S1 = SCI2S1;
}

