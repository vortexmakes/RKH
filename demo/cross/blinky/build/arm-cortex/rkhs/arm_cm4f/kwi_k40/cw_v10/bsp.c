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
 * 	Contact information:
 * 	RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * 	e-mail:			francuccilea@gmail.com
 *
 *  --------------------------------------------------------------------------
 *  File                     : bsp.c
 *	Last updated for version : v2.4.04
 *	By                       : DB
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		BSP for KWIKSTIK-K40 CW10
 */


#include "bsp.h"
#include "bky.h"
#include "rkh.h"

#include "cpu.h"
#include "kuart.h"
#include "Driver_SLCD.h"


#define SERIAL_TRACE			1


RKH_THIS_MODULE

/*
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1

	static const KUARTPP_ST trz_uart = 
	{
		115200, 0, 1, KUART_HFC_DISABLE, NULL
	};

	/* Trazer Tool COM Port */
	#define SERIAL_TRACE_OPEN()		kuart_init( UART5_BASE_PTR, &trz_uart )
	#define SERIAL_TRACE_CLOSE() 	(void)0
	#define SERIAL_TRACE_SEND( d ) 	kuart_putchar( UART5_BASE_PTR, d )
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ ) 		\
					kuart_putnchar( UART5_BASE_PTR,		\
								(char *)(buf_), 		\
								(rui16_t)(len_))

#else

	#define SERIAL_TRACE_OPEN()						(void)0
	#define SERIAL_TRACE_CLOSE()					(void)0
	#define SERIAL_TRACE_SEND( d )					(void)0
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ )	(void)0

#endif


void 
rkh_hook_timetick( void ) 
{
}


void 
rkh_hook_start( void ) 
{
}


void 
rkh_hook_exit( void ) 
{
	RKH_TRC_FLUSH();
}


void 
rkh_hook_idle( void )				/* called within critical section */
{
	RKH_ENA_INTERRUPT();
	RKH_TRC_FLUSH();
}


void 
rkh_assert( RKHROM char * const file, int line )
{
	(void)line;

	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
	rkh_fwk_exit();
	reset_now();
}


#if RKH_CFG_TRC_EN == 1

void 
rkh_trc_open( void )
{
	rkh_trc_init();
	SERIAL_TRACE_OPEN();
	RKH_TRC_SEND_CFG( BSP_TS_RATE_HZ );
}


void 
rkh_trc_close( void )
{
	SERIAL_TRACE_CLOSE();
}


RKH_TS_T 
rkh_trc_getts( void )
{
	return ( RKH_TS_T )get_ts();
}


void 
rkh_trc_flush( void )
{
	rui8_t *blk;
	TRCQTY_T nbytes;
	RKH_SR_ALLOC();

	FOREVER
	{
		nbytes = 128;

		RKH_ENTER_CRITICAL_();
		blk = rkh_trc_get_block( &nbytes );
		RKH_EXIT_CRITICAL_();

		if((blk != (rui8_t *)0))
		{
			SERIAL_TRACE_SEND_BLOCK( blk, nbytes );
		}
		else
			break;
	}	
}
#endif


void 
bsp_init( int argc, char *argv[]  )
{
	(void)argc;
	(void)argv;
	
	cpu_init();
	systick_init( RKH_CFG_FWK_TICK_RATE_HZ );
	cpu_tstmr_init();
	_SLCDModule_Init();
	_SLCDModule_TurnOnFreescaleSign();
	_SLCDModule_PrintScrolling( "RKH" );

	rkh_fwk_init();
	
	RKH_ENA_INTERRUPT();
	
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
	RKH_FILTER_OFF_EVENT( RKH_TE_TMR_TOUT );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
	RKH_FILTER_OFF_SMA( blinky );
	RKH_FILTER_OFF_ALL_SIGNALS();

	RKH_TRC_OPEN();
}


void 
bsp_led_on( void )
{
	_SLCDModule_PrintString("  ON ", 0);
}


void 
bsp_led_off( void )
{
	_SLCDModule_PrintString("  OFF", 0);
}




