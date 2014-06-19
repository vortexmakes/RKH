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
 * 	\brief 		BSP for TWR-K60D100M IAR V6.5
 */


#include "bsp.h"
#include "svr.h"
#include "cli.h"
#include "rkh.h"

#include "cpu.h"
#include "kuart.h"
#include "gpio.h"


#define SERIAL_TRACE			1


RKH_THIS_MODULE

static rkhui32_t l_rnd;			/* random seed */

/*
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1

	static const KUARTPP_ST trz_uart = 
	{
		115200, 0, 1, KUART_HFC_DISABLE, NULL
	};

	/* Trazer Tool COM Port */
	#define TRC_COM_PORT		COM1	

	#define SERIAL_TRACE_OPEN()		kuart_init( UART3_BASE_PTR, &trz_uart )
	#define SERIAL_TRACE_CLOSE() 	(void)0
	#define SERIAL_TRACE_SEND( d ) 	kuart_putchar( UART3_BASE_PTR, d )
#else
	#define SERIAL_TRACE_OPEN()		(void)0
	#define SERIAL_TRACE_CLOSE()	(void)0
	#define SERIAL_TRACE_SEND( d )	(void)0
#endif


void
rkh_hk_timetick( void )
{
}


void 
rkh_hk_start( void ) 
{
}


void 
rkh_hk_exit( void ) 
{
	RKH_TRC_FLUSH();
}


void 
rkh_hk_idle( void )				/* called within critical section */
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
	rkh_exit();
	reset_now();
}


#if RKH_TRC_EN == 1

void 
rkh_trc_open( void )
{
	rkh_trc_init();
	SERIAL_TRACE_OPEN();
}


void 
rkh_trc_close( void )
{
	SERIAL_TRACE_CLOSE();
}


RKHTS_T 
rkh_trc_getts( void )
{
	return ( RKHTS_T )get_ts();
}


void 
rkh_trc_flush( void )
{
	rkhui8_t *d;

	while( ( d = rkh_trc_get() ) != ( rkhui8_t* )0 )
	{
		SERIAL_TRACE_SEND( (char)*d );		
	}
}
#endif

#if 0
void
bsp_switch_evt( rkhui8_t s, rkhui8_t st )
{
	if( st == SW_RELEASED )
		return;

	if(s == SW1_SWITCH )
		bsp_publish( &e_pause );
}
#endif


rkhui32_t 
bsp_rand( void )
{  
	/* 
	 * A very cheap pseudo-random-number generator.
	 * "Super-Duper" Linear Congruential Generator (LCG)
	 * LCG(2^32, 3*7*11*13*23, 0, seed) [MS]
	 */
    l_rnd = l_rnd * (3*7*11*13*23);
    return l_rnd >> 8;
}


void 
bsp_srand( rkhui32_t seed )
{
    l_rnd = seed;
}


void 
bsp_cli_wait_req( rkhui8_t clino, RKH_TNT_T req_time )
{
	(void)clino;
	(void)req_time;
}


void 
bsp_cli_req( rkhui8_t clino )
{
#if 0
	set_cli_sled( clino, CLI_WAITING );
#endif
}


void 
bsp_cli_using( rkhui8_t clino, RKH_TNT_T using_time )
{
#if 0
	(void)using_time;
	
	set_cli_sled( clino, CLI_WORKING );
#endif
}


void 
bsp_cli_paused( rkhui8_t clino )
{
#if 0
	set_cli_sled( clino, CLI_PAUSED );
#endif
}


void 
bsp_cli_resumed( rkhui8_t clino )
{
#if 0
	set_cli_sled( clino, CLI_IDLE );
#endif
}


void 
bsp_cli_done( rkhui8_t clino )
{
#if 0
	set_cli_sled( clino, CLI_IDLE );
#endif
}


void 
bsp_svr_recall( rkhui8_t clino )
{
	(void)clino;
}


void 
bsp_svr_paused( const RKHSMA_T *sma )
{
	(void)sma;
}


void 
bsp_init( int argc, char *argv[]  )
{
	(void)argc;
	(void)argv;
	
	cpu_init();

	systick_init( RKH_TICK_RATE_HZ );
	
	cpu_tstmr_init();

	init_led( LED1 );

	RKH_ENA_INTERRUPT();
}




