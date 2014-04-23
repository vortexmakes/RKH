/*
 *	file: rkhport.c - Visual Studio 2008 port
 *	Last updated for version: 2.3.04
 *	Date of the last update:  Feb 22, 2012
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

/*
 * 	rkhport.c
 */


#include "rkh.h"


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "Windows 32-bits (multi-thread)" )


static CRITICAL_SECTION csection;		/* Win32 critical section object */
static DWORD tick = 10;					/* clock tick in [msec] */
static rkhui8_t running;

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
rkh_init( void )
{
    InitializeCriticalSection( &csection );
}


void 
rkh_enter( void )
{
    RKH_HK_START();						/* start-up callback */
	RKH_TR_FWK_EN();

	SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_HIGHEST );
    running = (rkhui8_t)1;

    while( running )
	{
		Sleep( tick );					/* wait for the tick interval */
		RKH_HOOK_TIMETICK();			/* call tick callback */
    }
    RKH_HK_EXIT();						/* cleanup callback */
	RKH_TRC_CLOSE();					/* cleanup the trace session */
    DeleteCriticalSection( &csection );
}


void 
rkh_exit( void )
{
	RKH_TR_FWK_EX();
	RKH_HK_EXIT();
	running = (rkhui8_t)0;
}


void 
rkh_sma_activate( RKHSMA_T *sma, const RKHEVT_T **qs, RKH_RQNE_T qsize, 
						void *stks, rkhui32_t stksize )
{
    ( void )stks;
    ( void )stksize;
	int priority;
	RKH_SR_ALLOC();

	RKHREQUIRE( (qs != (const RKHEVT_T *)0) && ( stks == (void *)0) );

	rkh_rq_init( &sma->equeue, (const void **)qs, qsize, sma );
	rkh_sma_register( sma );
    rkh_init_hsm( sma );
	sma->thread = CreateThread( NULL, stksize, thread_function, 
														sma, 0, NULL );
	RKHASSERT( sma->thread != (HANDLE)0 );

	/* map priorities RKH -> win32 */
	/* ... */

	SetThreadPriority( sma->thread, priority );
	RKH_TR_SMA_ACT( sma, RKH_GET_PRIO(sma) );
}


void 
rkh_sma_terminate( RKHSMA_T *sma )
{
	RKH_SR_ALLOC();

	rkh_sma_unregister( sma );
	RKH_TR_SMA_TERM( sma, RKH_GET_PRIO(sma) );
}
