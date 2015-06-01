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
 * 	\brief 		uC/OS-III for Freescale KSDK and KDS
 */


#include "rkh.h"
#include "fsl_os_abstraction.h"


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "uC/OS-III for Freescale KSDK and KDS" )


static
void
thread_function( void *arg )
{
	osa_status_t status;
	RKH_SR_ALLOC();

	while(((RKH_SMA_T *)arg)->running != (rbool_t)0)
	{
		RKH_EVT_T *e = rkh_sma_get((RKH_SMA_T *)arg);
        rkh_sma_dispatch((RKH_SMA_T *)arg, e);
        RKH_FWK_GC(e);
	}

	rkh_sma_unregister((RKH_SMA_T *)arg);
	RKH_TR_SMA_TERM((RKH_SMA_T *)arg, RKH_GET_PRIO((RKH_SMA_T *)arg));
                                       /* deletes the currently running task */
	status = OSA_TaskDestroy((task_handler_t)&sma->thread);
	RKH_ENSURE(status == kStatus_OSA_Success);
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


/* Include required OSA_MsgQPutLifo() implementation based on RTOS selection */
#if defined (FSL_RTOS_MQX)
	#define OSA_MsgQPutLifo(h, pm)		(void)0

#elif defined (FSL_RTOS_FREE_RTOS)
	#define OSA_MsgQPutLifo(h, pm)		(void)0

#elif defined (FSL_RTOS_UCOSII)
	#define OSA_MsgQPutLifo(h, pm)		(void)0

#elif defined (FSL_RTOS_UCOSIII)
	static
	osa_status_t 
	OSA_MsgQPutLifo(msg_queue_handler_t handler, void* pMessage)
	{
		OS_ERR err;
		void *localMsg;
		int32_t  *from_ptr, *to_ptr;
		uint32_t msg_size = handler->size;

		/* In this case, the message is saved into internal memory */
		localMsg = OSMemGet(&(handler->mem), &err);
		if (!localMsg)
		{
			return kStatus_OSA_Error;
		}

		/* Copy msg to localMsg. */
		from_ptr = (int32_t*)pMessage;
		to_ptr   = (int32_t*)localMsg;
		while (msg_size--)
		{
			*to_ptr++ = *from_ptr++;
		}

		OSQPost(&(handler->queue),
				localMsg,
				handler->size*sizeof(int32_t),
				OS_OPT_POST_LIFO,
				&err);

		if (OS_ERR_NONE != err)
		{
			OSMemPut(&(handler->mem), localMsg, &err);
			return kStatus_OSA_Error;
		}

		return kStatus_OSA_Success;
	}

#else
	#define OSA_MsgQPutLifo(h, pm)		(void)0
#endif


void 
rkh_fwk_init( void )
{
	osa_status_t status;

	status = OSA_Init();
	RKH_ENSURE(status == kStatus_OSA_Success);
}


void 
rkh_fwk_enter( void )
{
	osa_status_t status;
    RKH_SR_ALLOC();

    RKH_HOOK_START();	                            /* RKH start-up callback */
	RKH_TR_FWK_EN();

	status = OSA_Start();	             /* uC/OS-III start the multitasking */
	RKH_TRC_CLOSE();		                    /* cleanup the trace session */
 							    /* NEVER supposed to come back to this point */
	RKH_ENSURE(status == kStatus_OSA_Success);
}


void 
rkh_fwk_exit( void )
{
    RKH_SR_ALLOC();
	RKH_TR_FWK_EX();
    RKH_HOOK_EXIT();	                             /* RKH cleanup callback */
}


void 
rkh_sma_terminate( RKH_SMA_T *sma )
{
	osa_status_t status;

	sma->running = (rbool_t)0;
	status = OSA_MsgQDestroy(&sma->equeue);
	RKH_ENSURE(status == kStatus_OSA_Success);
}


void
rkh_sma_activate( RKH_SMA_T *sma, const RKH_EVT_T **qs, RKH_RQNE_T qsize,
                  void *stks, rui32_t stksize )
{
	msg_queue_handler_t qh;
	osa_status_t status;

	RKH_REQUIRE(qs != (const RKH_EVT_T **)0);

	qh = OSA_MsgQCreate(&sma->equeue,		   /* event message queue object */
						(uint16_t)qs,		   /* max. size of message queue */
						(uint16_t)1);		            /* allocate pointers */
    RKH_ENSURE(qh != (msg_queue_handler_t)0);

    rkh_sma_register( sma );
    rkh_sma_init_hsm( sma );

	status = OSA_TaskCreate(thread_function,                     /* function */
							"uc_task",			                     /* name */
							(uint16_t)stksize,	               /* stack size */
							(task_stack_t *)stks, /* stack base (low memory) */
							(uint16_t)RKH_GET_PRIO(sma),         /* priority */
							sma,                        /* function argument */
							false,                /* usage of float register */
							(task_handler_t)&sma->thread);    /* task object */

    RKH_ENSURE(status == kStatus_OSA_Success);
	sma->running = (rbool_t)1;
}


#if defined(RKH_USE_TRC_SENDER)
void 
rkh_sma_post_fifo( 	RKH_SMA_T *sma, const RKH_EVT_T *e, 
					const void *const sender )
#else
void 
rkh_sma_post_fifo(	RKH_SMA_T *sma, const RKH_EVT_T *e )
#endif
{
	osa_status_t status;
	RKH_SR_ALLOC();

	RKH_HOOK_SIGNAL( e );
	RKH_ENTER_CRITICAL_();

	RKH_INC_REF( e );
	status = OSA_MsgQPut(&sma->equeue,	               /* event queue object */
						 (void *)e);                  /* actual event posted */
    RKH_ALLEGE(status == kStatus_OSA_Success);
	RKH_TR_SMA_FIFO( sma, e, sender, e->pool, e->nref );

	RKH_EXIT_CRITICAL_();
}


#if (RKH_CFG_RQ_PUT_LIFO_EN == RKH_ENABLED) && \
	(defined(RKH_USE_TRC_SENDER))
void 
rkh_sma_post_lifo( 	RKH_SMA_T *sma, const RKH_EVT_T *e, 
					const void *const sender )
#else
void 
rkh_sma_post_lifo( 	RKH_SMA_T *sma, const RKH_EVT_T *e )
#endif
{
	osa_status_t status;
	RKH_SR_ALLOC();

	RKH_HOOK_SIGNAL( e );
	RKH_ENTER_CRITICAL_();

	RKH_INC_REF( e );
	status = OSA_MsgQPutLifo(&sma->equeue,             /* event queue object */
						     (void *)e);              /* actual event posted */
    RKH_ALLEGE(status == kStatus_OSA_Success);
	RKH_TR_SMA_LIFO( sma, e, sender, e->pool, e->nref );

	RKH_EXIT_CRITICAL_();
}



RKH_EVT_T *
rkh_sma_get( RKH_SMA_T *sma )
{
	osa_status_t status;
	RKH_EVT_T *e;
	RKH_SR_ALLOC();

	status = OSA_MsgQGet(&sma->equeue,				   /* event queue object */
						 e, 					   /* received event message */
						 OSA_WAIT_FOREVER);			    /* wait indefinitely */
    RKH_ENSURE(status == kStatus_OSA_Success);
	RKH_TR_SMA_GET( sma, e, e->pool, e->nref );
	return e;
}
