/*
 *	file: bsp.c
 *	Last updated for version: 2.0
 *	Date of the last update:  Feb 28, 2012
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
 * RKH web site:	http://
 * e-mail:			francuccilea@gmail.com
 */


#include "bsp.h"
#include "my.h"
#include "rkhdata.h"
#include "rkh.h"

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define tostring( expr )			#expr
#define ESC							0x1B
#define kbmap( c )					( c - '0' )


RKH_THIS_FILE;

static char fmt[ 64 ];
static MYEVT_T mye;
FILE *fdbg;
static DWORD tick_msec = 10;		/* clock tick in msec (argument for Sleep()) */
static rkhui8_t running;


static const char *tremap[] =
{
	tostring( RKHTR_EVENT 		),
	tostring( RKHTR_TRN_SRC		),
	tostring( RKHTR_TRN_TGT		),
	tostring( RKHTR_NXT_STATE	),
	tostring( RKHTR_INT_TRAN	),
	tostring( RKHTR_ENTRY		),
	tostring( RKHTR_EXIT		),
	tostring( RKHTR_INIT_HSM	),
	tostring( RKHTR_SGT_TGT		),
	tostring( RKHTR_RTN_CODE	),
	tostring( RKHTR_NUM_ENEX	),
	tostring( RKHTR_NUM_ACTSGT	)
};


static const char *smmap[] =
{
	tostring( MY )
};


static const char *rcmap[] =
{
	tostring( RKH_OK 						),
	tostring( RKH_INPUT_NOT_FOUND			),
	tostring( RKH_CONDITIONAL_NOT_FOUND		),
	tostring( RKH_CONDITION_NOT_FOUND		),
	tostring( RKH_GUARD_FALSE				),
	tostring( RKH_UNKNOWN_STATE				),
	tostring( RKH_EXCEED_HCAL_LEVEL			),
	tostring( RKH_EXCEED_TR_SEGS 			)
};


static 
DWORD WINAPI 
isr_tmr_thread( LPVOID par )			/* Win32 thread to emulate timer ISR */
{
    ( void )par;
    while( running ) 
	{
		rkh_time_tick();
        Sleep( tick_msec );
    }
    return 0;
}


static 
DWORD WINAPI 
isr_kbd_thread( LPVOID par )			/* Win32 thread to emulate keyboard ISR */
{
	int c;

    ( void )par;
    while( running ) 
	{
		c = _getch();
		
		if( c == 'p' )
			rkh_trace_flush();
		else if ( c == ESC )
			break;
		else if ( c == 'r' )
			rkh_init_hsm( my );
		else
		{
			RKH_SET_STATIC_EVENT( &mye, kbmap( c ) );
			mye.ts = ( rkhui16_t )rand();
			rkh_sma_post_fifo( my, ( RKHEVT_T* )&mye );
		}
    }
    return 0;
}


void 
rkh_hk_start( void ) 
{
    DWORD thtmr_id, thkbd_id;
    HANDLE hth_tmr, hth_kbd;

	/* set the desired tick rate */
    tick_msec = 1000UL / BSP_TICKS_PER_SEC;
    running = (rkhui8_t)1;
	
	/* create the ISR timer thread */
    hth_tmr = CreateThread( NULL, 1024, &isr_tmr_thread, 0, 0, &thtmr_id );
    RKHASSERT( hth_tmr != (HANDLE)0 );
    SetThreadPriority( hth_tmr, THREAD_PRIORITY_TIME_CRITICAL );

	/* create the ISR keyboard thread */
    hth_kbd = CreateThread( NULL, 1024, &isr_kbd_thread, 0, 0, &thkbd_id );
    RKHASSERT( hth_kbd != (HANDLE)0 );
    SetThreadPriority( hth_kbd, THREAD_PRIORITY_NORMAL );
}


void 
rkh_hk_exit( void ) 
{
    running = (rkhui8_t)0;
}


void 
rkh_hk_idle( void )					/* called within critical section */
{
    RKH_EXIT_CRITICAL( dummy );
#if 0
    if( _kbhit() )					/* any key pressed? */
        if( _getch() == 0x1B )		/* see if the ESC key pressed */
            QF_PUBLISH(Q_NEW(QEvent, TERMINATE_SIG), (void *)0);
#endif

    RKH_WAIT_FOR_EVENTS();        /* yield the CPU until new event(s) arrive */
}


void 
rkh_assert( RKHROM char * const file, HUInt fnum, int line )
{
	fprintf( stderr,	"RKHASSERT: [%d] line from %s "
						"file (#%02d)", line, file, fnum );
	__debugbreak();
	rkh_exit();
}


static
char *
format_trevt_args( RKHTREVT_T *ptre )
{
	switch( ptre->id )
	{
		case RKHTR_INIT_HSM:
			sprintf( fmt, "is = %s [%d]", ptre->sb, ptre->num );
			break;
		case RKHTR_INT_TRAN:
			sprintf( fmt, "" );
			break;
		case RKHTR_SGT_TGT:
		case RKHTR_TRN_SRC:
		case RKHTR_TRN_TGT:
		case RKHTR_NXT_STATE:
		case RKHTR_ENTRY:
		case RKHTR_EXIT:
			sprintf( fmt, "%s [%d]", ptre->sb, ptre->num );
			break;
		case RKHTR_RTN_CODE:
			sprintf( fmt, "%s", rcmap[ ptre->num ] );
			break;
		case RKHTR_NUM_ENEX:
		case RKHTR_NUM_ACTSGT:
			sprintf( fmt, "%d - %d", ( ( ptre->num ) >> 4 ) & 0x0F, 
										( ptre->num & 0x0F  ) );
			break;
		case RKHTR_EVENT:
			sprintf( fmt, "%d", ptre->num );
			break;
		default:
			return NULL;
	}
	return fmt;
}


static
void
print_banner( void )
{
	printf(	"Abstract Hierarchical State Machine (ahsm) example\n"
    		"RKH v%s\n\n", RKH_RELEASE );
	printf(	"Description: \n\n"
			"The goal of this demo application is to explain how to \n"
			"represent a state machine using the RKH framework. To do \n"
			"that is proposed a simple and abstract example, which is \n"
			"shown in the documentation file Figure 1 section \n"
			"\"Representing a State Machine\". \n\n\n" );

	printf( "1.- Press <numbers> to send events to state machine. \n" );
	printf( "2.- Press 'p' to see related information about transitions, \n" );
	printf( "    state changes, and so on.\n" );
	printf( "3.- Press 'r' to reset state machine.\n" );
	printf( "4.- Press ESC to quit \n\n\n" );
}


void 
rkh_trace_open( void )
{
	RKHTRCFG_T *pcfg;

	rkh_trace_init();
	rkh_trace_config( MY, RKH_TR_EN_LOG, RKH_TR_EN_PRINT );
	rkh_trace_control( MY, RKH_TRSTART );

	if( ( fdbg = fopen( "../mylog.txt", "w+" ) ) == NULL )
	{
		perror( "Can't open file\n" );
		exit( EXIT_FAILURE );
	}

	fprintf( fdbg, "---- RKH trace log session - "__DATE__" - "__TIME__" ----\n\n" );
	
	pcfg = rkh_trace_getcfg( MY );
	if( pcfg->print == RKH_TR_EN_PRINT )
		printf( "---- RKH trace log session - "__DATE__" - "__TIME__" ----\n\n" );
}


void 
rkh_trace_close( void )
{
	fclose( fdbg );
}


RKHTS_T 
rkh_trace_getts( void )
{
	return ( RKHTS_T )clock();
}


void 
rkh_trace_flush( void )
{
	RKHTREVT_T te;
	RKHTRCFG_T *pcfg;

	while( rkh_trace_getnext( &te ) != RKH_TREMPTY )
	{
		pcfg = rkh_trace_getcfg( te.smaid );

		if( pcfg->log == RKH_TR_EN_LOG )
			fprintf( fdbg, "%05d [ %-16s ] - %s : %s\n",
													rkh_trace_getts(),
													tremap[ te.id ],
													smmap[ te.smaid ],
													format_trevt_args( &te ) );
		if( pcfg->print == RKH_TR_EN_PRINT )
			printf( "%05d [ %-16s ] - %s : %s\n",
													rkh_trace_getts(),
													tremap[ te.id ],
													smmap[ te.smaid ],
													format_trevt_args( &te ) );
	}
}


void 
bsp_init( int argc, char *argv[] )
{
	srand( ( unsigned )time( NULL ) );
	print_banner();
}
