/*
 *	file: rkht.h - ARM Cortex-M4F MCU's, Eclipse CW10 port
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 06, 2013
 *
 * 	Copyright (C) 2010 Leandro Francucci. All rights reserved.
 *
 * 	RKH is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 *  RKH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RKH, see copying.txt file.
 *
 * Contact information:
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			lf@vxtsolutions.com.ar
 */

/*
 * 	rkhport.c
 */


#include "rkh.h"
#include "bsp.h"


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "ARM Cortex-M4F, Eclipse CW10" )


#define cortex_m4_enter_critical()	\
			__asm volatile			\
			(						\
				"	mov r0, %0								\n"	\
				"	msr basepri, r0							\n"	\
				::"i"(((BSP_HIGHEST_IRQ_PRI<<(8 - ARM_INTERRUPT_LEVEL_BITS))&0xFF)):"r0" \
			)

#define cortex_m4_exit_critical()		\
			__asm volatile			\
			(						\
				"	mov r0, #0					\n"	\
				"	msr basepri, r0				\n"	\
				:::"r0"								\
			)


static HUInt critical_nesting;


const 
char *
rkh_get_port_version( void )
{
	return RKH_MODULE_GET_VERSION();
}


const 
char *
rkh_get_port_desc( void )
{
	return RKH_MODULE_GET_DESC();
}


void
rkh_enter_critical( void )
{
	cortex_m4_enter_critical();

	critical_nesting++;
}


void
rkh_exit_critical( void )
{
	critical_nesting--;

	if( critical_nesting != 0 )
		return;

	cortex_m4_exit_critical();
}
