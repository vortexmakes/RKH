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
 *  File                     : bsp.c
 *	Last updated for version : v2.4.04
 *	By                       : DB
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		BSP for LPCXpresso LPC1769 CodeRed
 */

#include "rkh.h"
#include "bsp.h"
#include "blinky.h"
#include "uart.h"
#include "gpio.h"
#include "lpc17xx.h"


#define SERIAL_TRACE			1


RKH_THIS_MODULE

				
/*
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1

	/* Trazer Tool COM Port */
	#define TRC_COM_PORT		COM1	

	#define SERIAL_TRACE_OPEN()		UARTInit(0, 38400)
	#define SERIAL_TRACE_CLOSE() 	(void)0
	#define SERIAL_TRACE_SEND( d ) 	UARTPutc( 0, d )
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ ) 		\
					UARTPutnc( 0,		\
								(char *)(buf_), 		\
								(rui16_t)(len_))
#else
	#define SERIAL_TRACE_OPEN()						(void)0
	#define SERIAL_TRACE_CLOSE()					(void)0
	#define SERIAL_TRACE_SEND( d )					(void)0
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ )	(void)0
#endif

static RKH_TS_T tstamp;

void 
rkh_hook_timetick( void ) 
{
}

void
SysTick_Handler( void )
{
	++tstamp;
	RKH_TIM_TICK(&rkh_tick);
}

void 
rkh_hook_start( void ) 
{
	tstamp = 0;
	systick_init();    
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
	return ( RKH_TS_T )tstamp;
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
	init_led( LED1 );

	rkh_fwk_init();

	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_EXE_ACT );
	RKH_FILTER_OFF_EVENT( RKH_TE_TMR_TOUT );
	RKH_FILTER_OFF_EVENT( RKH_TE_TMR_INIT );
	RKH_FILTER_OFF_EVENT( RKH_TE_TMR_STOP );
	RKH_FILTER_OFF_EVENT( RKH_TE_TMR_START );
	RKH_FILTER_OFF_EVENT( RKH_TE_TMR_REM );
	RKH_FILTER_OFF_SMA( blinky );
	RKH_FILTER_OFF_ALL_SIGNALS();

	RKH_TRC_OPEN();

	RKH_ENA_INTERRUPT();
}


void 
bsp_ledOn( void )
{
	set_led( LED1 );
}


void 
bsp_ledOff( void )
{
	clr_led( LED1 );
}

