/*
 *	reset.c
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 10/03/08.
 */
#include "mytypes.h"
#include "reset.h"
#include "lowint.h"

#define _reset_mcu() {asm bgnd;}

/* 
 * reset_now: If in debugg mode stop the execution,
 *				 resets the MCU in other case.
 */
void
reset_now( void )
{
	_reset_mcu();
}

/*
 * cop_reset_now: Reset MCU trough COP module,
 * 				  to force Bootloader execution.
 */
void
cop_reset_now( void )
{
	rkdisable_interrupt();
	for(;;);
}


