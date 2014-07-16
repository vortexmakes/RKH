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
 *	By                       : LF
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

#include <bsp_twr.h>
#include <bsp_ser.h>
#include <os.h>
#include <lib_math.h>
#include <lib_math.h>


#define SERIAL_TRACE				0

#define SIZEOF_EP0STO				32
#define SIZEOF_EP0_BLOCK			sizeof( RKH_EVT_T )
#define SIZEOF_EP1STO				16
#define SIZEOF_EP1_BLOCK			sizeof( REQ_EVT_T )


RKH_THIS_MODULE

static rui32_t l_rnd;			/* random seed */
static RKH_ROM_STATIC_EVENT( e_term, TERM );
static RKH_ROM_STATIC_EVENT( e_pause, PAUSE );
static rui8_t ep0sto[ SIZEOF_EP0STO ],
				ep1sto[ SIZEOF_EP1STO ];
#if defined( RKH_USE_TRC_SENDER )
static rui8_t l_isr_kbd;
#endif

#if RKH_CFG_TRC_EN == RKH_ENABLED
static rbool_t running;
//static HANDLE idle_thread;
#endif


/*
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1
	static const KUARTPP_ST trz_uart = 
	{
		115200, 0, 1, KUART_HFC_DISABLE, NULL
	};

	/* Trazer Tool COM Port */
	#define SERIAL_TRACE_OPEN()		kuart_init( UART3_BASE_PTR, &trz_uart )
	#define SERIAL_TRACE_CLOSE() 	(void)0
	#define SERIAL_TRACE_SEND( d ) 	kuart_putchar( UART3_BASE_PTR, d )
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ ) 		\
					kuart_putnchar( UART3_BASE_PTR, 	\
								(char *)(buf_), 		\
								(rui16_t)(len_))
#else
	#define SERIAL_TRACE_OPEN()						(void)0
	#define SERIAL_TRACE_CLOSE()					(void)0
	#define SERIAL_TRACE_SEND( d )					(void)0
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ )	(void)0
#endif


static
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
#if 0
	if( _kbhit() )
	{
		int c = _getch();
		
		if( c == ESC )
			RKH_SMA_POST_FIFO( svr, &e_term, &l_isr_kbd );
		else if( tolower(c) == 'p' )
			bsp_publish( &e_pause );
	}
#endif
}


void 
rkh_hook_start( void ) 
{
	OS_ERR err;

	rkh_set_tickrate( BSP_TICKS_PER_SEC );
	rkh_fwk_epool_register( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
	rkh_fwk_epool_register( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );

	/* Start multitasking (i.e. give control to uC/OS-III).  */
    OSStart(&err);  
}


void 
rkh_hook_exit( void ) 
{
	RKH_TRC_FLUSH();
#if RKH_CFG_TRC_EN == RKH_ENABLED
	running = (rui8_t)0;
#endif
}


void 
rkh_assert( RKHROM char * const file, int line )
{
	RKH_TRC_FLUSH();
	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
	rkh_fwk_exit();
	/*** perform reset ??? ***/
}


#if RKH_CFG_TRC_EN == RKH_ENABLED


/** Idle task hook to flush trace */
#if 0
static 
DWORD WINAPI 
idle_thread_function( LPVOID par )
{
    (void)par;

    SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_IDLE );
    running = (rui8_t)1;

    while( running )
	{
		RKH_TRC_FLUSH();
        Sleep(10);                                      /* wait for a while */
    }
    return 0;                                             /* return success */
}
#endif


void 
rkh_trc_open( void )
{
	rkh_trc_init();

	SERIAL_TRACE_OPEN();
	RKH_TRC_SEND_CFG( BSP_TS_RATE_HZ );

	/** flush must be done in idle task */
#if 0
	if(( idle_thread = CreateThread( NULL, 1024, &idle_thread_function, (void *)0, 
				CREATE_SUSPENDED, NULL )) == (HANDLE)0 )
		fprintf( stderr, "Cannot create the idle thread: [%d] line from %s "
						"file\n", __LINE__, __FILE__ );
#endif
}


void 
rkh_trc_close( void )
{
	SERIAL_TRACE_CLOSE();
}


RKH_TS_T 
rkh_trc_getts( void )
{
  return 0;
//	return ( RKH_TS_T )clock();
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
//	printf( "Client[%d] - Waiting for send request to server (%d seg)\n", 
//									CLI_ID(clino), req_time );
}


void 
bsp_cli_req( rui8_t clino )
{
//	printf( "Client[%d] - Send request to server...\n", CLI_ID(clino) );
}


void 
bsp_cli_using( rui8_t clino, RKH_TNT_T using_time )
{
//	printf( "Client[%d] - Using server for %d [seg]\n", 
//									CLI_ID(clino), using_time );
}


void 
bsp_cli_paused( rui8_t clino )
{
//	printf( "Client[%d] - Paused\n", CLI_ID(clino) );
}


void 
bsp_cli_resumed( rui8_t clino )
{
//	printf( "Client[%d] - Resumed\n", CLI_ID(clino) );
}


void 
bsp_cli_done( rui8_t clino )
{
//	printf( "Client[%d] - Done\n", CLI_ID(clino) );
}


void 
bsp_svr_recall( rui8_t clino )
{
//	printf( "%s Recall a deferred request from client[%d]\n", 
//									SVR_NAME, CLI_ID(clino) );
}


void 
bsp_svr_paused( const RKH_SMA_T *sma )
{
/*	rint cn;
	SVR_T *ao;

	ao = RKH_CAST(SVR_T, sma);
	printf( "%s Paused | ", SVR_NAME );
	printf( "ntot = %d |", ao->ntot );

	for( cn = 0; cn < NUM_CLIENTS; ++cn )
		printf( " cli%d=%d |", cn, ao->ncr[ cn ] );

	putchar('\n');*/
}


void
ucos_init( void )
{
	OS_ERR err;
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
	CPU_ERR cpu_err;
#endif

	CPU_Init();
	Mem_Init();			/* Initialize the Memory Management Module */
	Math_Init();		/* Initialize the Mathematical Module */	

#if (CPU_CFG_NAME_EN == DEF_ENABLED)
	CPU_NameSet((CPU_CHAR *)"MK60N512ZVMD10",
                (CPU_ERR  *)&cpu_err);
#endif
	
	BSP_IntDisAll();   
	
	OSInit(&err);		/* Initialize "uC/OS-III, The Real-Time Kernel" */
	
	BSP_Init();         /* Start BSP and tick initialization */

	BSP_Tick_Init();    /* Start Tick Initialization */

#if (OS_CFG_STAT_TASK_EN > 0)
    OSStatTaskCPUUsageInit(&err);
#endif
    
#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
    BSP_Ser_Init(115200);
#endif	

    BSP_LED_Off(BSP_LED_ALL);
}


void 
bsp_init( int argc, char *argv[] )
{
	rint cn;

	(void)argc;
	(void)argv;

	ucos_init();

	bsp_srand( 1234U );

	rkh_fwk_init();

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
