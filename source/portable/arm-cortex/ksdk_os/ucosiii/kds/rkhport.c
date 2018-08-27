/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhport.c
 *	\brief      uC/OS-III for Freescale KSDK and KDS
 *
 *  \ingroup    port
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhfwk_dynevt.h"
#include "os.h"
#include "fsl_os_abstraction.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
RKH_MODULE_NAME(rkhport)
RKH_MODULE_VERSION(rkhport, 1.00)
RKH_MODULE_DESC(rkhport, "uC/OS-III for Freescale KSDK and KDS")

#if (OSCfg_TickRate_Hz > OS_CFG_TICK_RATE_HZ)
#error "RKH_CFG_FWK_TICK_RATE_HZ in 'rkhcfg.h' must be <= to OS tick"
#error "defined by RKH_CFG_FWK_TICK_RATE_HZ in 'os_cfg_app.h'       "
#endif

#define RKH_TICKS_RATE          (OSCfg_TickRate_Hz / RKH_CFG_FWK_TICK_RATE_HZ)

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static rui16_t tick_cnt;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
void
idle_thread_function(void)
{
#if RKH_CFG_TRC_EN == 1
    RKH_TRC_FLUSH();
#endif
}

static
void
thread_function(void *arg)
{
    osa_status_t status;
    RKH_SR_ALLOC();

    while (((RKH_SMA_T *)arg)->running != (rbool_t)0)
    {
        RKH_EVT_T *e = rkh_sma_get((RKH_SMA_T *)arg);
        rkh_sm_dispatch((RKH_SM_T *)arg, e);
        RKH_FWK_GC(e, arg);
    }

    rkh_sma_unregister((RKH_SMA_T *)arg);
    RKH_TR_SMA_TERM((RKH_SMA_T *)arg, RKH_GET_PRIO((RKH_SMA_T *)arg));
    /* deletes the currently running task */
    status = OSA_TaskDestroy(&(((RKH_SMA_T *)arg)->thread));
    RKH_ENSURE(status == kStatus_OSA_Success);
}

static
void
rkh_isr_tick(void)
{
    if (tick_cnt && (--tick_cnt == (rui16_t)0))
    {
        tick_cnt = RKH_TICKS_RATE;
        RKH_TIM_TICK((const void *)(rkh_isr_tick));
    }
}

/* Include required OSA_MsgQPutLifo() implementation based on RTOS selection */
#if defined (FSL_RTOS_MQX)
    #define OSA_MsgQPutLifo(h, pm)      (void)0

#elif defined (FSL_RTOS_FREE_RTOS)
    #define OSA_MsgQPutLifo(h, pm)      (void)0

#elif defined (FSL_RTOS_UCOSII)
    #define OSA_MsgQPutLifo(h, pm)      (void)0

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
            handler->size * sizeof(int32_t),
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
    #define OSA_MsgQPutLifo(h, pm)      (void)0
#endif

/* ---------------------------- Global functions --------------------------- */
const char *
rkhport_get_version(void)
{
    return RKH_MODULE_GET_VERSION();
}

const char *
rkhport_get_desc(void)
{
    return RKH_MODULE_GET_DESC();
}

void
rkh_fwk_init(void)
{
    osa_status_t status;

    tick_cnt = RKH_TICKS_RATE;

    status = OSA_Init();

    OS_AppTimeTickHookPtr = rkh_isr_tick;
    OS_AppIdleTaskHookPtr = idle_thread_function;

    RKH_ENSURE(status == kStatus_OSA_Success);
}

void
rkh_fwk_enter(void)
{
    osa_status_t status;
    RKH_SR_ALLOC();

    RKH_HOOK_START();                               /* RKH start-up callback */
    RKH_TR_FWK_EN();
    RKH_TR_FWK_OBJ(&rkh_isr_tick);

    status = OSA_Start();                /* uC/OS-III start the multitasking */
    RKH_TRC_CLOSE();                            /* cleanup the trace session */
    /* NEVER supposed to come back to this point */
    RKH_ENSURE(status == kStatus_OSA_Success);
}

void
rkh_fwk_exit(void)
{
    RKH_SR_ALLOC();
    RKH_TR_FWK_EX();
    RKH_HOOK_EXIT();                                 /* RKH cleanup callback */
}

void
rkh_sma_terminate(RKH_SMA_T *sma)
{
    osa_status_t status;

    sma->running = (rbool_t)0;
    status = OSA_MsgQDestroy(&sma->equeue);
    RKH_ENSURE(status == kStatus_OSA_Success);
}

void
rkh_sma_activate(RKH_SMA_T *sma, const RKH_EVT_T **qs, RKH_QUENE_T qsize,
                 void *stks, rui32_t stksize)
{
    msg_queue_handler_t qh;
    osa_status_t status;
    task_handler_t th;

    RKH_REQUIRE(qs != (const RKH_EVT_T **)0);

    sma->equeue.msgs = (void *)qs;
    qh = OSA_MsgQCreate(&sma->equeue,          /* event message queue object */
                        (uint16_t)qsize,       /* max. size of message queue */
                        /* allocate pointers */
                        (uint16_t)(sizeof(RKH_EVT_T *) / sizeof(uint32_t)));
    RKH_ENSURE(qh != (msg_queue_handler_t)0);

    rkh_sma_register(sma);
    rkh_sm_init((RKH_SM_T *)sma);

    th = &sma->thread;
    status = OSA_TaskCreate(thread_function,                     /* function */
                            "uc_task",                               /* name */
                            (uint16_t)stksize,                 /* stack size */
                            (task_stack_t *)stks, /* stack base (low memory) */
                            (uint16_t)RKH_GET_PRIO(sma),         /* priority */
                            sma,                        /* function argument */
                            false,                /* usage of float register */
                            &th);    /* task object */

    RKH_ENSURE(status == kStatus_OSA_Success);
    sma->running = (rbool_t)1;
}

#if defined(RKH_USE_TRC_SENDER)
void
rkh_sma_post_fifo(RKH_SMA_T *sma, const RKH_EVT_T *e,
                  const void *const sender)
#else
void
rkh_sma_post_fifo(RKH_SMA_T *sma, const RKH_EVT_T *e)
#endif
{
    osa_status_t status;
    RKH_SR_ALLOC();

    RKH_HOOK_SIGNAL(e);
    RKH_ENTER_CRITICAL_();

    RKH_INC_REF(e);
    status = OSA_MsgQPut(&sma->equeue,                 /* event queue object */
                         (void *)&e);                 /* actual event posted */
    RKH_ALLEGE(status == kStatus_OSA_Success);
    RKH_TR_SMA_FIFO(sma, e, sender, e->pool, e->nref, 
                        &sma->equeue.queue.MsgQ.NbrEntries, 0);

    RKH_EXIT_CRITICAL_();
}

#if (RKH_CFG_QUE_PUT_LIFO_EN == RKH_ENABLED) && \
    (defined(RKH_USE_TRC_SENDER))
void
rkh_sma_post_lifo(RKH_SMA_T *sma, const RKH_EVT_T *e,
                  const void *const sender)
#else
void
rkh_sma_post_lifo(RKH_SMA_T *sma, const RKH_EVT_T *e)
#endif
{
    osa_status_t status;
    RKH_SR_ALLOC();

    RKH_HOOK_SIGNAL(e);
    RKH_ENTER_CRITICAL_();

    RKH_INC_REF(e);
    status = OSA_MsgQPutLifo(&sma->equeue,             /* event queue object */
                             (void *)&e);              /* actual event posted */
    RKH_ALLEGE(status == kStatus_OSA_Success);
    RKH_TR_SMA_LIFO(sma, e, sender, e->pool, e->nref, 
                        &sma->equeue.queue.MsgQ.NbrEntries, 0);

    RKH_EXIT_CRITICAL_();
}

RKH_EVT_T *
rkh_sma_get(RKH_SMA_T *sma)
{
    osa_status_t status;
    RKH_EVT_T *e;
    RKH_SR_ALLOC();

    status = OSA_MsgQGet(&sma->equeue,                 /* event queue object */
                         &e,                       /* received event message */
                         OSA_WAIT_FOREVER);             /* wait indefinitely */
    RKH_ENSURE(status == kStatus_OSA_Success);
    /* To get the number of message currently in the queue and its */
    /* minimum number of free elements is not a reliable manner in OSA */
    /* Because the variables are obtained outside critical section could be */
    /* a race condition */
    /* Morever, OSA abstraction layer not implements the water mark in */
    /* the queue */
    RKH_TR_SMA_GET(sma, e, e->pool, e->nref,
                        &sma->equeue.queue.MsgQ.NbrEntries, 0);
    return e;
}

/* ------------------------------ End of file ------------------------------ */
