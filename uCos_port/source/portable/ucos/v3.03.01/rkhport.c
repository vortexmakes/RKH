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
 * 	\brief 		uC/OS-III for Freescale Kinetis K60 and IAR
 */


#include "rkh.h"


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "uC/OS-III for Freescale Kinetis K60 and IAR" )


static rui8_t running;

static
void
thread_function( void *arg )
{
	OS_ERR err;
	RKH_SR_ALLOC();

	while(((RKH_SMA_T *)arg)->running != (rbool_t)0)
	{
		RKH_EVT_T *e = rkh_sma_get((RKH_SMA_T *)arg);
        rkh_sma_dispatch((RKH_SMA_T *)arg, e);
        RKH_FWK_GC(e);
	}

	rkh_sma_unregister((RKH_SMA_T *)arg);
	RKH_TR_SMA_TERM((RKH_SMA_T *)arg, RKH_GET_PRIO((RKH_SMA_T *)arg));
	OSTaskDel((OS_TCB *)0, &err ); /* deletes the currently running task */
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
}


void 
rkh_fwk_enter( void )
{
 
}


void 
rkh_fwk_exit( void )
{
}


void 
rkh_sma_terminate( RKH_SMA_T *sma )
{
	OS_ERR err;

	sma->running = (rbool_t)0;
#if 0
	OSQDel(sma->queue, OS_OPT_DEL_ALWAYS, &err );

    RKH_ASSERT(err == OS_ERR_NONE);
#endif	
}


void
rkh_sma_activate( RKH_SMA_T *sma, const RKH_EVT_T **qs, RKH_RQNE_T qsize,
                  void *stks, rui32_t stksize )
{
    OS_ERR err;
    OS_PRIO prio;
    RKH_SR_ALLOC();

    RKH_REQUIRE(qs != (const RKH_EVT_T **)0); /* ??? */
#if 0
	OSQCreate( 	&sma->queue,				/* event message queue object */
				"uc_queue",					/* name */
				(OS_MSG_QTY)qsize,			/* max. size of message queue */
				&err );						/* received error code */

    RKH_ASSERT(err == OS_ERR_NONE);
#endif	
    rkh_sma_register( sma );
    rkh_sma_init_hsm( sma );

    /* Map RKH priority to uC/OS-III priority. */
	/* In both systems the lower the number the higher the priority. */
	/* In uC/OS-III the priorities 0, 1, OS_CFG_PRIO_MAX-2 and ... */
	/* ... OS_CFG_PRIO_MAX-2 are reserved. */
	/* See uC/OS-III API reference manual for more information. */

    switch( RKH_GET_PRIO( sma ) )
    {
        case 0:
        case 1:
            prio = RKH_GET_PRIO(sma) + 1;
            break;
        case OS_CFG_PRIO_MAX - 2:
        case OS_CFG_PRIO_MAX - 1:
            prio = OS_CFG_PRIO_MAX - 3;
            break;
        default:
            prio = RKH_GET_PRIO(sma);
            break;
    }

    OSTaskCreate(	sma->thread,			/* task object */
                  	"uc_task", 				/* name */
					thread_function,		/* function */
					sma, 					/* function argument */
					prio, 					/* priority */
					(CPU_STK *)stks, 		/* stack base (low memory) */
					(CPU_STK_SIZE)(stksize - 1),	/* stack limit */
					stksize/sizeof(CPU_STK_SIZE), 	/* stack size */
					(OS_MSG_QTY)0, 			/* queue size */
					(OS_TICK)0, 			/* time quanta in round-robin */
					(void *)0, 				/* TCB extension */
					OS_OPT_TASK_STK_CLR, 	/* options */
					&err );					/* received error code */

    RKH_ASSERT(err == OS_ERR_NONE);
	sma->running = (rbool_t)1;
}
