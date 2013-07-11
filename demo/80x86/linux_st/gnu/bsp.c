/*
 *	file: bsp.c
 *	Last updated for version: 2.3
 *	Date of the last update:  Jan 23, 2013
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
#include "my.h"
#include "rkhdata.h"
#include "rkh.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <termios.h>
#include <sys/time.h>


#define BIN_TRACE					1
#define SOCKET_TRACE				1
#define ESC							0x1B
#define kbmap( c )					( (c) - '0' )

#define SIZEOF_EP0STO				64
#define SIZEOF_EP0_BLOCK			4
#define SIZEOF_EP1STO				32
#define SIZEOF_EP1_BLOCK			8


RKH_THIS_MODULE

static unsigned short tick_msec;			/* clock tick in msec */
rkhui8_t running;
static RKH_DCLR_STATIC_EVENT( eterm, TERM );
static rkhui8_t ep0sto[ SIZEOF_EP0STO ],
				ep1sto[ SIZEOF_EP1STO ];


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
	#define TRC_IP_ADDR					"127.0.0.1"

	/* Trazer Tool TCP Port Address */
	#define TRC_TCP_PORT				6602

	/* Trace Socket */
	static int tsock;

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
				tcp_trace_send( tsock, d )
#else
	#define TCP_TRACE_OPEN()		(void)0
	#define TCP_TRACE_CLOSE()		(void)0
	#define TCP_TRACE_SEND( d )		(void)0
#endif


#if BIN_TRACE == 1
	#define FTBIN_FLUSH( d )				\
				fwrite ( d, 1, 1, ftbin );	\
				fflush( ftbin )
	#define FTBIN_CLOSE() \
				fclose( ftbin )
	#define FTBIN_OPEN() \
				if( ( ftbin = fopen( "ftbin", "w+b" ) ) == NULL ) \
				{ \
					printf( "Can't open file\n" ); \
					exit( EXIT_FAILURE ); \
				}
#else
	#define FTBIN_FLUSH( d )		(void)0
	#define FTBIN_CLOSE()			(void)0
	#define FTBIN_OPEN()			(void)0
#endif


static 
void *
isr_tmr_thread( void *d )	/* thread to emulate timer ISR */
{
	(void)d;

    while( running ) 
	{
		rkh_tim_tick();
        usleep( tick_msec );
    }
	pthread_exit(NULL);
	return NULL;
}

static struct termios orgt;

int 
mygetch( void )
{
	struct termios newt;
	int ch;

	tcgetattr( STDIN_FILENO, &orgt );
	newt = orgt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &orgt );
	return ch;
}


static 
void * 
isr_kbd_thread( void *d )	/* thread to emulate keyboard ISR */
{
	int c;
	MYEVT_T *mye;

	(void)d;
    while( running ) 
	{
		c = mygetch();
		
		if( c == ESC )
			rkh_sma_post_fifo( my, &eterm );
		else
		{
			mye = RKH_ALLOC_EVENT( MYEVT_T, kbmap( c ) );
			mye->ts = ( rkhui16_t )rand();
			rkh_sma_post_fifo( my, RKH_EVT_CAST(mye) );
		}
    }
	return NULL;
}


void 
rkh_hk_start( void ) 
{
	pthread_t thtmr_id, thkbd_id;  /* thread identifiers */
 	pthread_attr_t threadAttr;

	/* set the desired tick rate */
    tick_msec = 1000UL/BSP_TICKS_PER_SEC;
    running = (rkhui8_t)1;

	/* initialize the thread attribute */
	pthread_attr_init(&threadAttr);

	/* Set the stack size of the thread */
	pthread_attr_setstacksize(&threadAttr, 1024);

	/* Create the threads */
	pthread_create(&thtmr_id, &threadAttr, isr_tmr_thread, NULL);
	pthread_create(&thkbd_id, &threadAttr, isr_kbd_thread, NULL);

	/* Destroy the thread attributes */
	pthread_attr_destroy(&threadAttr);
	
	rkh_epool_register( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
	rkh_epool_register( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
}


void 
rkh_hk_exit( void ) 
{
	RKH_TRC_FLUSH();
    running = 0;
	tcsetattr( STDIN_FILENO, TCSANOW, &orgt );
}


void 
rkh_hk_idle( void )				/* called within critical section */
{
    RKH_EXIT_CRITICAL( dummy );
	RKH_TRC_FLUSH();
    RKH_WAIT_FOR_EVENTS();		/* yield the CPU until new event(s) arrive */
}


void 
rkh_assert( RKHROM char * const file, int line )
{
	fprintf( stderr,	"RKHASSERT: [%d] line from %s "
						"file\n", line, file );
	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
	rkh_exit();
}


static
void
print_banner( void )
{
	printf(	"Abstract Hierarchical State Machine (AHSM) example\n\n" );
	printf(	"RKH version      = %s\n", RKH_RELEASE );
	printf(	"Port version     = %s\n", rkh_get_port_version() );
	printf(	"Port description = %s\n\n", rkh_get_port_desc() );
	printf(	"Description: \n\n"
			"The goal of this demo application is to explain how to \n"
			"represent a state machine using the RKH framework. To do \n"
			"that is proposed a simple and abstract example, which is \n"
			"shown in the documentation file Figure 1 section \n"
			"\"Representing a State Machine\". \n\n\n" );

	printf( "1.- Press <numbers> to send events to state machine. \n" );
	printf( "2.- Press ESC to quit \n\n\n" );
}


#if RKH_TRC_EN == 1

void 
rkh_trc_open( void )
{
	rkh_trc_init();

	FTBIN_OPEN();
	TCP_TRACE_OPEN();
 	rkh_trc_config();
}


void 
rkh_trc_close( void )
{
	FTBIN_CLOSE();
	TCP_TRACE_CLOSE();
}


RKHTS_T 
rkh_trc_getts( void )
{
	struct timeval tv;   /* see gettimeofday(2) */
	double t;

	gettimeofday(&tv, NULL);
	t = (double) tv.tv_sec + (double) 1e-6 * tv.tv_usec; 
	return ( RKHTS_T )t;
}


void 
rkh_trc_flush( void )
{
	rkhui8_t *d;

	while( ( d = rkh_trc_get() ) != ( rkhui8_t* )0 )
	{
		FTBIN_FLUSH( d );
		TCP_TRACE_SEND( *d );		
	}
}
#endif


void 
bsp_init( int argc, char *argv[] )
{
	(void)argc;
	(void)argv;

	srand( ( unsigned )time( NULL ) );
	print_banner();
}
