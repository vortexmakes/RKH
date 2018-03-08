/**
 * \cond
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 * 	          State-machine framework for reactive embedded systems            
 * 	        
 * 	                    Copyright (C) 2010 Leandro Francucci.
 * 	        All rights reserved. Protected by international copyright laws.
 *
 *
 * 	RKH is free software: you can redistribute it and/or modify it under the 
 * 	terms of the GNU General Public License as published by the Free Software 
 * 	Foundation, either version 3 of the License, or (at your option) any 
 * 	later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY 
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along 
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  --------------------------------------------------------------------------
 *  File                     : bsp.h
 *	Last updated for version : v2.4.04
 *	By                       : DB
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		BSP for FRDM-KL25z CW10
 */


#ifndef __BSP_H__
#define __BSP_H__


#include "rkh.h"
#include "cpu.h"


#define BSP_KERNEL_IRQ_PRIO		6
#define BSP_UART_IRQ_PRIO		7
#define BSP_HIGHEST_IRQ_PRI		5

#define BSP_TICKS_PER_SEC   	RKH_CFG_FWK_TICK_RATE_HZ

/**
 * 	\brief
 * 	This macro represents the number of timestamp clock ticks per second. 
 * 	Dividing a count of timestamp ticks by this macro yields the number 
 * 	of seconds.
 */

#define BSP_TS_RATE_HZ		   	MCU_TS_RATE_HZ

void bsp_init( int argc, char *argv[] );
void bsp_led_on( void );
void bsp_led_off( void );

#ifdef RKH_DEBUG
#define reset_now()		__asm volatile	("	bkpt 0x00FF\n" )
#else					
#define reset_now()		cpu_reset()
#endif


#define get_ts()		cpu_tstmr_read()


#endif
