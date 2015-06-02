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
 * 	\brief 		BSP for TWR-K60D100M CWV10
 */


#include "bsp.h"
#include "svr.h"
#include "cli.h"
#include "scevt.h"
#include "rkh.h"

#define SERIAL_TRACE			1

#define SIZEOF_EP0STO				32
#define SIZEOF_EP0_BLOCK			sizeof( RKH_EVT_T )
#define SIZEOF_EP1STO				16
#define SIZEOF_EP1_BLOCK			sizeof( REQ_EVT_T )


/* This macro is needed only if the module requires to check 	.. */
/* .. expressions that ought to be true as long as the program  .. */
/* .. is running. 												   */

RKH_THIS_MODULE


static rui16_t tick_cnt;
static rui32_t l_rnd;				/* random seed */
static rui8_t ep0sto[ SIZEOF_EP0STO ],
				ep1sto[ SIZEOF_EP1STO ];
#if defined( RKH_USE_TRC_SENDER )
static rui8_t l_isr_kbd;
#endif


/*
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1
	#define SERIAL_TRACE_OPEN()		rkhtrc_uart_init()
	#define SERIAL_TRACE_CLOSE() 	rkhtrc_uart_deinit()
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ )	\
									rkhtrc_send_block( buf_, len_ )
#else
	#define SERIAL_TRACE_OPEN()						(void)0
	#define SERIAL_TRACE_CLOSE()					(void)0
	#define SERIAL_TRACE_SEND( d )					(void)0
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ )	(void)0
#endif


static
void
bsp_isr_tick( void )
{
	if(tick_cnt && (--tick_cnt == (rui16_t)0))
	{
		tick_cnt = BSP_TICKS_RATE;
		RKH_TIM_TICK((const void *)(bsp_isr_tick));
	}
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
	(void)line;

	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
	rkh_fwk_exit();
	reset_now();
}


#if RKH_CFG_TRC_EN == 1


static 
void
idle_thread_function( void )
{
	RKH_TRC_FLUSH();
}


void 
rkh_trc_open( void )
{
	rkh_trc_init();
	SERIAL_TRACE_OPEN();
	RKH_TRC_SEND_CFG( BSP_TS_RATE_HZ );
	RKH_TR_FWK_OBJ( &bsp_isr_tick );
}


void 
rkh_trc_close( void )
{
	SERIAL_TRACE_CLOSE();
}


RKH_TS_T 
rkh_trc_getts( void )
{
	return ( RKH_TS_T )rkhtrc_lptmr_read();
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


void 
bsp_cli_wait_req( rui8_t clino, RKH_TNT_T req_time )
{
	(void)clino;
	(void)req_time;
}


void 
bsp_cli_req( rui8_t clino )
{
//	set_cli_sled( clino, CLI_WAITING );
}


void 
bsp_cli_using( rui8_t clino, RKH_TNT_T using_time )
{
	(void)using_time;

//	set_cli_sled( clino, CLI_WORKING );
}


void 
bsp_cli_paused( rui8_t clino )
{
//	set_cli_sled( clino, CLI_PAUSED );
}


void 
bsp_cli_resumed( rui8_t clino )
{
//	set_cli_sled( clino, CLI_IDLE );
}


void 
bsp_cli_done( rui8_t clino )
{
//	set_cli_sled( clino, CLI_IDLE );
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
}


#include "fsl_debug_console.h"

void 
bsp_init( int argc, char *argv[]  )
{
#if (OS_CFG_STAT_TASK_EN > 0)
	OS_ERR err;
#endif
	rint cn;

	(void)argc;
	(void)argv;

    hardware_init();

//    GPIO_DRV_Init( switchPins, ledPins );

    rkhtrc_lptmr_init();

#if (OS_CFG_STAT_TASK_EN > 0)
    OSStatTaskCPUUsageInit(&err);
#endif
	
	rkh_fwk_init();

	tick_cnt = BSP_TICKS_RATE;
	OS_AppTimeTickHookPtr = bsp_isr_tick;
	OS_AppIdleTaskHookPtr = idle_thread_function;

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


void 
bsp_led_on( void )
{
	GPIO_DRV_SetPinOutput( BOARD_GPIO_LED_RED );
}


void 
bsp_led_off( void )
{
	GPIO_DRV_ClearPinOutput( BOARD_GPIO_LED_RED );
}




