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
 * 	\brief 		BSP for uC/OS-III for Freescale Kinetis K60 and IAR
 */


#include "bsp.h"
#include "rkh.h"
#include "scevt.h"
#include "svr.h"
#include "cli.h"
#include "leds.h"



#define SERIAL_TRACE				1

#define SIZEOF_EP0STO				32
#define SIZEOF_EP0_BLOCK			sizeof( RKH_EVT_T )
#define SIZEOF_EP1STO				16
#define SIZEOF_EP1_BLOCK			sizeof( REQ_EVT_T )


/* This macro is needed only if the module requires to check 	.. */
/* .. expressions that ought to be true as long as the program  .. */
/* .. is running. 												   */

/* RKH_THIS_MODULE */

static rui32_t l_rnd;				/* random seed */
static rui8_t ep0sto[ SIZEOF_EP0STO ],
				ep1sto[ SIZEOF_EP1STO ];
#if defined( RKH_USE_TRC_SENDER )
static rui8_t l_isr_kbd;
#endif

#define BLINK_LED_MASK	0x20;
static int32_t fd_out;

#if defined( RKH_USE_TRC_SENDER )
static rui8_t l_isr_tick;
#endif

static RKH_TS_T bsp_tstamp;

/*
 * 	For serial trace feature.
 */


#if SERIAL_TRACE == 1

	static int32_t utrc;
	#define TRACE_UART_FD	"/dev/serial/uart/1"
	#define TRACE_UART_BAUD	(void *)ciaaBAUDRATE_115200

	/* Trazer Tool COM Port */
	#define SERIAL_TRACE_OPEN()												\
				{															\
					utrc = ciaaPOSIX_open(TRACE_UART_FD, O_WRONLY); 		\
					ciaaPOSIX_ioctl(utrc, 									\
							ciaaPOSIX_IOCTL_SET_BAUDRATE, TRACE_UART_BAUD); \
					ActivateTask( RkhTraceTask );							\
				}

	#define SERIAL_TRACE_CLOSE() 						\
				{										\
					ciaaPOSIX_close( utrc ); 			\
				}

	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ ) 		\
				{										\
				   	ciaaPOSIX_write(utrc, buf_,	len_ );	\
				}
#else
	#define SERIAL_TRACE_OPEN()						(void)0
	#define SERIAL_TRACE_CLOSE()					(void)0
	#define SERIAL_TRACE_SEND( d )					(void)0
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ )	(void)0
#endif


ALARMCALLBACK( TickHandler )
{
	RKH_TIM_TICK( &l_isr_tick );
	++bsp_tstamp;
}



void
bsp_publish( const RKH_EVT_T *e )
{
	rint cn;

	RKH_SMA_POST_FIFO( svr, e, &l_isr_kbd );			/* to server */

	for( cn = 0; cn < NUM_CLIENTS; ++cn )				/* to clients */
		RKH_SMA_POST_FIFO( CLI(cn), e, &l_isr_kbd );
}


void
rkh_hook_timetick( void )
{
//	sequence_interrupt();
//	switch_tick();	
}


void 
rkh_hook_start( void ) 
{
	rkh_fwk_epool_register( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
	rkh_fwk_epool_register( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
}


void 
rkh_hook_exit( void ) 
{
	RKH_TRC_FLUSH();
}


void 
rkh_assert( RKHROM char * const file, int line )
{
	ciaaPOSIX_printf( "RKH_ASSERT: [%d] line from %s "
						"file\n", line, file );
	RKH_TRC_FLUSH();
	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
	rkh_fwk_exit();
}


#if RKH_CFG_TRC_EN == RKH_ENABLED

rui8_t trace_open;


void 
rkh_trc_open( void )
{
	trace_open = (rui8_t)1;
	rkh_trc_init();
	SERIAL_TRACE_OPEN();
	RKH_TRC_SEND_CFG( BSP_TS_RATE_HZ );
	RKH_TR_FWK_OBJ( &l_isr_tick );
}


void 
rkh_trc_close( void )
{
	trace_open = (rui8_t)0;
	SERIAL_TRACE_CLOSE();
}


RKH_TS_T 
rkh_trc_getts( void )
{
	return bsp_tstamp;
}


void 
rkh_trc_flush( void )
{
	rui8_t *blk;
	TRCQTY_T nbytes;
	RKH_SR_ALLOC();

	FOREVER
	{
		nbytes = (TRCQTY_T)1024;

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


rui32_t 
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
bsp_srand( rui32_t seed )
{
    l_rnd = seed;
}


static RGB_COLOR_IDX bsp_led_colors[NUM_CLIENTS + 1] = {
											/* Server paused */
											RGB_WHITE,

											/*
											 * Client1 1-3 according
											 * to clino arg
											 */
											RGB_YELLOW,
											RGB_RED,
											RGB_LIME,
										};

static uint8_t cli_leds[NUM_CLIENTS+1] = { 0, LED1_MASK, LED2_MASK, LED3_MASK };

void 
bsp_cli_wait_req( rui8_t clino, RKH_TNT_T req_time )
{
	(void)clino;
	(void)req_time;
}


void 
bsp_cli_req( rui8_t clino )
{
	set_led( cli_leds[clino], 1 );
}


void 
bsp_cli_using( rui8_t clino, RKH_TNT_T using_time )
{
	(void)using_time;

	//set_cli_sled( clino, CLI_WORKING );
}


void 
bsp_cli_paused( rui8_t clino )
{
	//set_cli_sled( clino, CLI_PAUSED );
}


void 
bsp_cli_resumed( rui8_t clino )
{
	//set_rgb_led( bsp_led_colors[clino] );
}


void 
bsp_cli_done( rui8_t clino )
{
	set_led( cli_leds[clino], 0 );
}


void 
bsp_svr_recall( rui8_t clino )
{
	(void)clino;
}


void 
bsp_svr_paused( const RKH_SMA_T *sma )
{
	(void)sma;
	//set_rgb_led( RGB_WHITE );
}


void 
bsp_svr_start( rui8_t clino )
{
	set_rgb_led( bsp_led_colors[clino] );
}


void 
bsp_svr_end( void )
{
	set_rgb_led( RGB_BLACK );
}


void 
bsp_svr_resume( void )
{
}


void 
bsp_init( int argc, char *argv[] )
{
#if (OS_CFG_STAT_TASK_EN > 0)	
	OS_ERR err;
#endif
	rint cn;

	(void)argc;
	(void)argv;

	bsp_srand( 1234U );

	rkh_fwk_init();
	
	init_leds();

	RKH_FILTER_OFF_SMA( svr );
	for( cn = 0; cn < NUM_CLIENTS; ++cn )
		RKH_FILTER_OFF_SMA( CLI(cn) );

	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_FIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_LIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_DCH );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
	/*RKH_FILTER_OFF_ALL_SIGNALS();*/
	RKH_FILTER_OFF_SIGNAL( REQ );
	RKH_FILTER_OFF_SIGNAL( START );

	RKH_TRC_OPEN();
}
