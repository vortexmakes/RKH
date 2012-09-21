/*
 *	file: rkhport.c - Visual Studio 2008 port
 *	Last updated for version: 1.0.00
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
 * RKH web site:	http://
 * e-mail:			francuccilea@gmail.com
 */

/*
 * 	rkhport.c
 */


#include "rkh.h"


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "Windows 32-bits (single thread)" )


CRITICAL_SECTION csection;		/* Win32 critical section */
HANDLE sma_is_rdy;          	/* Win32 event to signal when SMAs are ready */
RKHRG_T rkhrg;					/* ready group of SMAs */

extern rkhui8_t running;


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
    sma_is_rdy = CreateEvent( NULL, FALSE, FALSE, NULL );	
}


void 
rkh_enter( void )
{
	rkhui8_t prio;
	RKHSMA_T *sma;
	RKHEVT_T *e;

    RKH_HK_START();
	RKH_TRCR_RKH_EN();
    running = 1;

    while( running )
	{
        RKH_ENTER_CRITICAL( dummy );
        if( rkh_rdy_isnot_empty( rkhrg ) ) 
		{
			rkh_rdy_findh( rkhrg, prio );
            RKH_EXIT_CRITICAL( dummy );

            sma = rkh_sptbl[ prio ];
            e = rkh_sma_get( sma );
            rkh_dispatch( sma, e );
            RKH_GC( e );
        }
        else
            rkh_hk_idle();
    }

    RKH_HK_EXIT();
    CloseHandle( sma_is_rdy );
    DeleteCriticalSection( &csection );	
}


void 
rkh_exit( void )
{
	RKH_TRCR_RKH_EX();
	running = 0;
}


void 
rkh_sma_activate(	RKHSMA_T *sma, const RKHEVT_T **qs, RKH_RQNE_T qsize, 
						void *stks, rkhui32_t stksize )
{
    ( void )stks;
    ( void )stksize;

	rkh_rq_init( &sma->equeue, qs, qsize, sma );
	rkh_sma_register( sma );
    rkh_init_hsm( sma );
	RKH_TRCR_SMA_ACT( sma );
}


void 
rkh_sma_terminate( RKHSMA_T *sma )
{
	rkh_sma_unregister( sma );
	RKH_TRCR_SMA_TERM( sma );
}
