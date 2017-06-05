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
 * 	\brief 		Visual Studio 2008 Single-Thread port (win32)
 */


#include "rkh.h"
#include "rkhfwk_dynevt.h"


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "Windows 32-bits (single thread)" )


CRITICAL_SECTION csection;		/* Win32 critical section */
HANDLE sma_is_rdy;          	/* Win32 event to signal when SMAs are ready */

extern rui8_t running;


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
rkh_sma_block(RKH_SMA_T *const me)
{
    RKH_ASSERT(me->equeue.qty != 0);
    ((void)WaitForSingleObject( sma_is_rdy, (DWORD)INFINITE));
}

void 
rkh_sma_setReady(RKH_SMA_T *const me)
{
    rkh_smaPrio_setReady(RKH_SMA_ACCESS_CONST(me, prio));
    SetEvent( sma_is_rdy );
}

void 
rkh_sma_setUnready(RKH_SMA_T *const me)
{
    rkh_smaPrio_setUnready(RKH_SMA_ACCESS_CONST(me, prio));
}

void 
rkh_fwk_init( void )
{
    InitializeCriticalSection( &csection );
    sma_is_rdy = CreateEvent( NULL, FALSE, FALSE, NULL );	
}


void 
rkh_fwk_enter( void )
{
	rui8_t prio;
	RKH_SMA_T *sma;
	RKH_EVT_T *e;
	RKH_SR_ALLOC();

    RKH_HOOK_START();
	RKH_TR_FWK_EN();
    running = 1;

    while( running )
	{
        RKH_ENTER_CRITICAL( dummy );
        if( rkh_smaPrio_isReady() ) 
		{
			prio = rkh_smaPrio_findHighest();
            RKH_EXIT_CRITICAL( dummy );

            sma = rkh_sptbl[ prio ];
            e = rkh_sma_get( sma );
            rkh_sm_dispatch( (RKH_SM_T *)sma, e );
            RKH_FWK_GC( e, sma );
        }
        else
            rkh_hook_idle();
    }

    RKH_HOOK_EXIT();
    CloseHandle( sma_is_rdy );
    DeleteCriticalSection( &csection );	
}


void 
rkh_fwk_exit( void )
{
	RKH_HOOK_EXIT();
	RKH_TR_FWK_EX();
	running = 0;
}


void 
rkh_sma_activate(	RKH_SMA_T *sma, const RKH_EVT_T **qs, RKH_QUENE_T qsize, 
						void *stks, rui32_t stksize )
{
    ( void )stks;
    ( void )stksize;
	RKH_SR_ALLOC();

	rkh_queue_init( &sma->equeue, (const void **)qs, qsize, sma );
	rkh_sma_register( sma );
    rkh_sm_init( (RKH_SM_T *)sma );
	RKH_TR_SMA_ACT( sma, RKH_GET_PRIO(sma), qsize );
}


void 
rkh_sma_terminate( RKH_SMA_T *sma )
{
	RKH_SR_ALLOC();

	rkh_sma_unregister( sma );
	RKH_TR_SMA_TERM( sma, RKH_GET_PRIO(sma) );
}
