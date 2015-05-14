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
 *  File                     : rkhport.c
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		Visual Studio 2008 Multithread port (win32)
 */


#include "rkh.h"


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "Windows 32-bits (multi-thread)" )


static CRITICAL_SECTION csection;		/* Win32 critical section object */
static DWORD tick_msec = 10u;			/* clock tick in [msec] */
static rui8_t running;
#if defined( RKH_USE_TRC_SENDER )
static rui8_t l_isr_tick;
#endif

static DWORD WINAPI thread_function( LPVOID arg );


void
rkh_enter_critical( void )
{
	EnterCriticalSection( &csection );
}


void
rkh_exit_critical( void )
{
	LeaveCriticalSection( &csection );
}


void 
rkh_set_tickrate( rui32_t tick_rate_hz )
{
	tick_msec = 1000UL/tick_rate_hz;
}


const 
char *
rkh_get_port_version( void )
{
	return RKH_MODULE_GET_VERSION();
}


const 
char *
rkh_get_port_desc( void )
{
	return RKH_MODULE_GET_DESC();
}


void 
rkh_fwk_init( void )
{
    InitializeCriticalSection( &csection );
}


void 
rkh_fwk_enter( void )
{
    RKH_HOOK_START();						/* start-up callback */
	RKH_TR_FWK_EN();

	SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_HIGHEST );
    running = (rui8_t)1;
	RKH_TR_FWK_OBJ( &l_isr_tick );

    while( running )
	{
		Sleep( tick_msec );				/* wait for the tick interval */
		RKH_TIM_TICK( &l_isr_tick );	/* tick handler */
    }
    RKH_HOOK_EXIT();						/* cleanup callback */
	RKH_TRC_CLOSE();					/* cleanup the trace session */
    DeleteCriticalSection( &csection );
}


void 
rkh_fwk_exit( void )
{
	RKH_TR_FWK_EX();
	RKH_HOOK_EXIT();
	running = (rui8_t)0;
}


void 
rkh_sma_activate( RKH_SMA_T *sma, const RKH_EVT_T **qs, RKH_RQNE_T qsize, 
						void *stks, rui32_t stksize )
{
	int priority;

    ( void )stks;
    ( void )stksize;
	RKH_SR_ALLOC();

	RKH_REQUIRE( (qs != (const RKH_EVT_T **)0) && ( stks == (void *)0) );

	rkh_rq_init( &sma->equeue, (const void **)qs, qsize, sma );
	rkh_sma_register( sma );
	sma->os_signal = CreateEvent( NULL, FALSE, FALSE, NULL );
    rkh_sma_init_hsm( sma );
	sma->thread = CreateThread( NULL, stksize, thread_function, 
														sma, 0, NULL );
	RKH_ASSERT( sma->thread != (HANDLE)0 );

	/* map RKH priority to win32 priority */
	switch( RKH_GET_PRIO( sma ) )
	{
		case 0:
			priority = THREAD_PRIORITY_HIGHEST;
			break;
		case 1:
			priority = THREAD_PRIORITY_ABOVE_NORMAL;
			break;
		case RKH_LOWEST_PRIO:
			priority = THREAD_PRIORITY_IDLE;
			break;
		case RKH_LOWEST_PRIO - 1:
			priority = THREAD_PRIORITY_LOWEST;
			break;
		case RKH_LOWEST_PRIO - 2:
			priority = THREAD_PRIORITY_BELOW_NORMAL;
			break;
		default:
			priority = THREAD_PRIORITY_NORMAL;
			break;
	}

	SetThreadPriority( sma->thread, priority );
	RKH_TR_SMA_ACT( sma, RKH_GET_PRIO(sma) );
}


void 
rkh_sma_terminate( RKH_SMA_T *sma )
{
	sma->thread = (HANDLE)0;
}


static
DWORD
WINAPI 
thread_function( LPVOID arg )
{
	RKH_SR_ALLOC();

	do
	{
		RKH_EVT_T *e = rkh_sma_get( (RKH_SMA_T *)arg );
        rkh_sma_dispatch( (RKH_SMA_T *)arg, e );
        RKH_FWK_GC( e );
	}
	while( ((RKH_SMA_T *)arg)->thread != (HANDLE)0 );

	rkh_sma_unregister( (RKH_SMA_T *)arg );
	RKH_TR_SMA_TERM( (RKH_SMA_T *)arg, 
			RKH_GET_PRIO( (RKH_SMA_T *)arg ));
	CloseHandle( ((RKH_SMA_T *)arg)->os_signal );
	return 0;
}
