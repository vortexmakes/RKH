/*
 *	file: bsp.c
 *	Last updated for version: 2.3
 *	Date of the last update:  Jul 11, 2013
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


#include "bsp.h"
#include "rkh.h"
#include "scevt.h"
#include "svr.h"
#include "cli.h"

#include "mcu.h"
#include "gpio.h"
#include "serial.h"
#include "sequence.h"
#include "genled.h"
#include "switch.h"


#define SERIAL_TRACE				1

#define SIZEOF_EP0STO				32
#define SIZEOF_EP0_BLOCK			sizeof( RKHEVT_T )
#define SIZEOF_EP1STO				16
#define SIZEOF_EP1_BLOCK			sizeof( REQ_EVT_T )
#define SVR_NAME					"Server    -"
#define CLI_NAME					"Client"


RKH_THIS_MODULE


static rkhui32_t l_rnd;			/* random seed */

static RKH_DCLR_STATIC_EVENT( e_term, TERM );
static RKH_DCLR_STATIC_EVENT( e_pause, PAUSE );

static rkhui8_t ep0sto[ SIZEOF_EP0STO ],
				ep1sto[ SIZEOF_EP1STO ];

#if defined( RKH_USE_TRC_SENDER )
static rkhui8_t l_isr_kbd;
interrupt VectorNumber_Vrtc void l_isr_tick( void );
#endif

/*
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1

	/* Trazer Tool COM Port */
	#define TRC_COM_PORT		COM1	

	#define SERIAL_TRACE_OPEN()		serial_init( TRC_COM_PORT )
	#define SERIAL_TRACE_CLOSE() 	(void)0
	#define SERIAL_TRACE_SEND( d ) 	put_char( TRC_COM_PORT, d )
#else
	#define SERIAL_TRACE_OPEN()		(void)0
	#define SERIAL_TRACE_CLOSE()	(void)0
	#define SERIAL_TRACE_SEND( d )	(void)0
#endif


static
void
bsp_publish( const RKHEVT_T *e )
{
	HInt cn;

	RKH_SMA_POST_FIFO( svr, e, &l_isr_kbd );			/* to server */

	for( cn = 0; cn < NUM_CLIENTS; ++cn )				/* to clients */
		RKH_SMA_POST_FIFO( CLI(cn), e, &l_isr_kbd );
}

#if 0
static 
DWORD WINAPI 
isr_tmr_thread( LPVOID par )	/* Win32 thread to emulate timer ISR */
{
    ( void )par;
    while( running ) 
	{
		RKH_TIM_TICK( &l_isr_tick );
        Sleep( tick_msec );
    }
    return 0;
}


static 
DWORD WINAPI 
isr_kbd_thread( LPVOID par )	/* Win32 thread to emulate keyboard ISR */
{
	int c;

    ( void )par;
    while( running ) 
	{
		c = _getch();
		
		if( c == ESC )
			RKH_SMA_POST_FIFO( svr, &e_term, &l_isr_kbd );
		else if( tolower(c) == 'p' )
			bsp_publish( &e_pause );
    }
    return 0;
}
#endif


void 
rkh_hk_start( void ) 
{
	rkh_epool_register( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
	rkh_epool_register( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
}


void 
rkh_hk_exit( void ) 
{
	RKH_TRC_FLUSH();
}


void 
rkh_hk_idle( void )				/* called within critical section */
{
//    RKH_EXIT_CRITICAL( dummy );
	RKH_ENA_INTERRUPT();
	RKH_TRC_FLUSH();
}


void 
rkh_assert( RKHROM char * const file, int line )
{
	RKH_TRC_FLUSH();
	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, line );
	rkh_exit();
	reset_now();
}


#if RKH_TRC_EN == 1

void 
rkh_trc_open( void )
{
	rkh_trc_init();

	SERIAL_TRACE_OPEN();
 	rkh_trc_config();
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
		SERIAL_TRACE_SEND( *d );		
	}
}
#endif


void
bsp_switch_evt( rkhui8_t s, rkhui8_t st )
{
	if( st == SW_RELEASED )
		return;

	if(s == SW1_SWITCH )
		bsp_publish( &e_pause );
}


rkhui32_t 
bsp_rand( void )
{  
	/* 
	 * A very cheap pseudo-random-number generator.
	 * "Super-Duper" Linear Congruential Generator (LCG)
	 * LCG(2^32, 3*7*11*13*23, 0, seed) [MS]
	 */
    l_rnd = (rkhui32_t)(l_rnd * (3*7*11*13*23));
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
	set_cli_sled( clino, CLI_WAITING );
}


void 
bsp_cli_using( rkhui8_t clino, RKH_TNT_T using_time )
{
	(void)using_time;
	
	set_cli_sled( clino, CLI_WORKING );
}


void 
bsp_cli_paused( rkhui8_t clino )
{
	set_cli_sled( clino, CLI_PAUSED );
}


void 
bsp_cli_resumed( rkhui8_t clino )
{
	set_cli_sled( clino, CLI_IDLE );
}


void 
bsp_cli_done( rkhui8_t clino )
{
	set_cli_sled( clino, CLI_IDLE );
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
bsp_init( int argc, char *argv[] )
{
	HInt cn;

	(void)argc;
	(void)argv;

	mcu_init( RKH_TICK_RATE_MS );
	gpio_init();
	init_seqs();
    bsp_srand( 1234U );
    
	RKH_ENA_INTERRUPT();
	
	rkh_init();

	/* set trace filters */
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );

	RKH_FILTER_OFF_SMA( svr );
	for( cn = 0; cn < NUM_CLIENTS; ++cn )
		RKH_FILTER_OFF_SMA( CLI(cn) );

	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_FIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );

	RKH_TRC_OPEN();

//#if defined( RKH_USE_TRC_SENDER )
	RKH_TR_FWK_OBJ( &l_isr_kbd );
	RKH_TR_FWK_OBJ( &l_isr_tick );
//#endif

}
