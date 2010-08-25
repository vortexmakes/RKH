/*
 *	reset.h
 *
 *	Routines for Reset MCU
 *
 */

#ifndef __RESET_H__
#define __RESET_H__

/* 
 * reset_now: If in debugg mode stop the execution,
 *			  resets the MCU in other case.
 */
void reset_now( void );

/*
 * cop_reset_now: Reset MCU trough COP module,
 * 				  to force Bootloader execution.
 */
void cop_reset_now( void );

#endif
