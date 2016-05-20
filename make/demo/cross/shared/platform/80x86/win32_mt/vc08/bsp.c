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
 * 	\brief 		BSP for 80x86 OS win32
 */


#include "bsp.h"
#include "rkh.h"
#include "scevt.h"
#include "server.h"
#include "client.h"

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define BIN_TRACE					0
#define SOCKET_TRACE				1
#define ESC							0x1B
#define kbmap( c )					( (c) - '0' )

#define SIZEOF_EP0STO				32
#define SIZEOF_EP0_BLOCK			sizeof( RKH_EVT_T )
#define SIZEOF_EP1STO				16
#define SIZEOF_EP1_BLOCK			sizeof( REQ_EVT_T )
#define SVR_NAME					"Server    -"
#define CLI_NAME					"Client"


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
static HANDLE idle_thread;
#endif


/* 
 * 	For binary trace feature.
 */

#if BIN_TRACE == 1
static FILE *ftbin;
#endif


/*
 * 	For socket trace feature.
 */

#if SOCKET_TRACE == 1

	#include "tcptrc.h"

	/* Trazer Tool IP Address */
	/*#define TRC_IP_ADDR					"192.168.1.143"*/
	#define TRC_IP_ADDR					"127.0.0.1"

	/* Trazer Tool TCP Port Address */
	#define TRC_TCP_PORT				6602

	/* Trace Socket */
	static SOCKET tsock;

	#define TCP_TRACE_OPEN() \
				if( tcp_trace_open( TRC_TCP_PORT, \
							TRC_IP_ADDR, &tsock ) < 0 ) \
				{ \
					printf( "Can't open socket %s:%u\n", \
								TRC_IP_ADDR, TRC_TCP_PORT ); \
					exit( EXIT_FAILURE ); \
				}
	#define TCP_TRACE_CLOSE() \
				tcp_trace_close( tsock )
	#define TCP_TRACE_SEND( d ) \
				tcp_trace_send( tsock, d, (int)1 )
	#define TCP_TRACE_SEND_BLOCK( buf_, len_ ) \
				tcp_trace_send( tsock, (const char *)(buf_), (int)(len_) )
#else
	#define TCP_TRACE_OPEN()					(void)0
	#define TCP_TRACE_CLOSE()					(void)0
	#define TCP_TRACE_SEND( d )					(void)0
	#define TCP_TRACE_SEND_BLOCK( buf_, len_ )	(void)0
#endif


#if BIN_TRACE == 1
	#define FTBIN_FLUSH( buf_, len_ ) \
				fwrite ( (buf_), 1, (len_), ftbin ); \
				fflush( ftbin )
	#define FTBIN_CLOSE() \
				fclose( ftbin )
	#define FTBIN_OPEN() \
				if( ( ftbin = fopen( "../ftbin", "w+b" ) ) == NULL ) \
				{ \
					perror( "Can't open file\n" ); \
					exit( EXIT_FAILURE ); \
				}
#else
	#define FTBIN_FLUSH( buf_, len_ )		(void)0
	#define FTBIN_CLOSE()					(void)0
	#define FTBIN_OPEN()					(void)0
#endif


static
void
bsp_publish( const RKH_EVT_T *e )
{
	rint cn;

	RKH_SMA_POST_FIFO( server, e, &l_isr_kbd );			/* to server */

	for( cn = 0; cn < NUM_CLIENTS; ++cn )				/* to clients */
		RKH_SMA_POST_FIFO( CLI(cn), e, &l_isr_kbd );
}


void
rkh_hook_timetick( void )
{
	if( _kbhit() )
	{
		int c = _getch();
		
		if( c == ESC )
			RKH_SMA_POST_FIFO( server, &e_term, &l_isr_kbd );
		else if( tolower(c) == 'p' )
			bsp_publish( &e_pause );
	}
}


void 
rkh_hook_start( void ) 
{
	rkh_set_tickrate( BSP_TICKS_PER_SEC );
	rkh_fwk_epool_register( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
	rkh_fwk_epool_register( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );

	/* 
	 * 	For avoiding to have multiple threads (idle and main) sending data on 
	 * 	the same socket, i.e. using the send() function, the idle thread is 
	 * 	created to be run only after the initial process has finished.
	 * 	Without this trick, the streams are interleaving and the trace stream 
	 * 	is corrupted.
	 */

	ResumeThread( idle_thread );
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
	fprintf( stderr,	"RKH_ASSERT: [%d] line from %s "
						"file\n", line, file );
	RKH_TRC_FLUSH();
	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
	__debugbreak();
	rkh_fwk_exit();
}


static
void
print_banner( void )
{
	printf(	"\"Shared\" example\n\n" );
	printf(	"RKH version      = %s\n", RKH_RELEASE );
	printf(	"Port version     = %s\n", rkh_get_port_version() );
	printf(	"Port description = %s\n\n", rkh_get_port_desc() );
	printf(	"Description: \n\n" );
	printf(	"This application deals with the shared resource problem \n" );
	printf(	"in active object systems. Showing one of the biggest \n" );
	printf(	"benefit of using active objects: resource encapsulation. \n" );
	printf(	"The encapsulation naturally designates the owner of the \n" );
	printf(	"resource as the ultimate arbiter in resolving any contention \n" );
	printf(	"and potential conflicts for the resource. \n" );
	printf(	"The SHD application is relatively simple and can be tested \n" );
	printf(	"only with a couple of LEDs on your target board. \n" );
	printf(	"Still, SHD contains five (5) concurrent active objects \n" );
	printf(	"that exchange events via direct event posting mechanism. \n" );
	printf(	"The application uses four timers, as well as dynamic  \n" );
	printf(	"and static events. \n" );
	printf(	"On the other hand, this application could be used in either \n" );
	printf(	"preemptive or cooperative enviroment. \n" );
	printf(	"Aditionally, the SHD could be used to verify a new RKH port. \n" );
	printf(	"\n\n\n" );

	printf( "1.- Press 'P'/'p' to pause.\n" );
	printf( "2.- Press 'escape' to quit.\n\n\n" );
}


#if RKH_CFG_TRC_EN == RKH_ENABLED

#include <time.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>                        /* Win32 API for multithreading */


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


void 
rkh_trc_open( void )
{
	rkh_trc_init();

	FTBIN_OPEN();
	TCP_TRACE_OPEN();
	RKH_TRC_SEND_CFG( BSP_TS_RATE_HZ );

	if(( idle_thread = CreateThread( NULL, 1024, &idle_thread_function, (void *)0, 
				CREATE_SUSPENDED, NULL )) == (HANDLE)0 )
		fprintf( stderr, "Cannot create the idle thread: [%d] line from %s "
						"file\n", __LINE__, __FILE__ );
}


void 
rkh_trc_close( void )
{
	FTBIN_CLOSE();
	TCP_TRACE_CLOSE();
}


RKH_TS_T 
rkh_trc_getts( void )
{
	return ( RKH_TS_T )clock();
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
			FTBIN_FLUSH( blk, nbytes );
			TCP_TRACE_SEND_BLOCK( blk, nbytes );
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
	printf( "Client[%d] - Waiting for send request to server (%d seg)\n", 
									CLI_ID(clino), req_time );
}


void 
bsp_cli_req( rui8_t clino )
{
	printf( "Client[%d] - Send request to server...\n", CLI_ID(clino) );
}


void 
bsp_cli_using( rui8_t clino, RKH_TNT_T using_time )
{
	printf( "Client[%d] - Using server for %d [seg]\n", 
									CLI_ID(clino), using_time );
}


void 
bsp_cli_paused( rui8_t clino )
{
	printf( "Client[%d] - Paused\n", CLI_ID(clino) );
}


void 
bsp_cli_resumed( rui8_t clino )
{
	printf( "Client[%d] - Resumed\n", CLI_ID(clino) );
}


void 
bsp_cli_done( rui8_t clino )
{
	printf( "Client[%d] - Done\n", CLI_ID(clino) );
}


void 
bsp_svr_recall( rui8_t clino )
{
	printf( "%s Recall a deferred request from client[%d]\n", 
									SVR_NAME, CLI_ID(clino) );
}


void 
bsp_svr_paused(rui32_t ntot, rui32_t *ncr)
{
	rint cn;
    rui32_t *pNcr;

	printf( "Server paused | ");
	printf( "ntot = %d |", ntot );

	for(pNcr = ncr, cn = 0; cn < NUM_CLIENTS; ++cn, ++pNcr )
		printf( " cli%d=%d |", cn, *pNcr );

	putchar('\n');
}


void 
bsp_svr_start( rui8_t clino )
{
	printf( "%s Busy (client[%d])\n", SVR_NAME, CLI_ID(clino) );
}


void 
bsp_svr_end( void )
{
	printf( "%s Released\n", SVR_NAME );
}


void 
bsp_svr_resume( void )
{
	printf( "%s Resumed\n", SVR_NAME );
}


void 
bsp_init( int argc, char *argv[] )
{
	rint cn;

	(void)argc;
	(void)argv;

    bsp_srand( 1234U );
	print_banner();
	rkh_fwk_init();

	RKH_FILTER_OFF_SMA( server );
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
