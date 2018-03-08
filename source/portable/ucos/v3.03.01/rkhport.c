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
 *  \brief      uC/OS-III for Freescale Kinetis K60 and IAR
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
#include "os_cfg_app.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
RKH_MODULE_NAME(rkhport)
RKH_MODULE_VERSION(rkhport, 1.00)
RKH_MODULE_DESC(rkhport, "uC/OS-III for Freescale Kinetis K60 and IAR")

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
void
thread_function(void *arg)
{
    OS_ERR err;
    RKH_SR_ALLOC();

    while (((RKH_SMA_T *)arg)->running != (rbool_t)0)
    {
        RKH_EVT_T *e = rkh_sma_get((RKH_SMA_T *)arg);
        rkh_sm_dispatch((RKH_SM_T *)arg, e);
        RKH_FWK_GC(e, arg);
    }

    rkh_sma_unregister((RKH_SMA_T *)arg);
    RKH_TR_SMA_TERM((RKH_SMA_T *)arg, RKH_GET_PRIO((RKH_SMA_T *)arg));
    OSTaskDel((OS_TCB *)0, &err);  /* deletes the currently running task */
}

/* ---------------------------- Global functions --------------------------- */
const
char *
rkh_get_port_version(void)
{
    return RKH_MODULE_GET_VERSION();
}

const
char *
rkh_get_port_desc(void)
{
    return RKH_MODULE_GET_DESC();
}

void
rkh_sma_block(RKH_SMA_T *const me)
{
    (void)me;
}

void
rkh_sma_setReady(RKH_SMA_T *const me)
{
    (void)me;
}

void
rkh_sma_setUnready(RKH_SMA_T *const me)
{
    (void)me;
}

void
rkh_fwk_init(void)
{
    OS_ERR err;

    OSInit(&err);

    RKH_ASSERT(err == OS_ERR_NONE);
}

void
rkh_fwk_enter(void)
{
    OS_ERR err;
    RKH_SR_ALLOC();

    RKH_HOOK_START();   /* RKH start-up callback */
    RKH_TR_FWK_EN();

    OSStart(&err);      /* uC/OS-III start the multitasking */
    RKH_TRC_CLOSE();    /* cleanup the trace session */
                        /* NEVER supposed to come back to this point */
    RKH_ASSERT(err == OS_ERR_NONE);
}

void
rkh_fwk_exit(void)
{
    RKH_SR_ALLOC();
    RKH_TR_FWK_EX();
    RKH_HOOK_EXIT();    /* RKH cleanup callback */
}

void
rkh_sma_terminate(RKH_SMA_T *sma)
{
    OS_ERR err;

    sma->running = (rbool_t)0;
    OSQDel(&sma->equeue, OS_OPT_DEL_ALWAYS, &err);
    RKH_ASSERT(err == OS_ERR_NONE);
}

void
rkh_sma_activate(RKH_SMA_T *sma, const RKH_EVT_T **qs, RKH_RQNE_T qsize,
                 void *stks, rui32_t stksize)
{
    OS_ERR err;
    OS_PRIO prio;

    RKH_REQUIRE(qs == (const RKH_EVT_T **)0);
    OSQCreate(&sma->equeue,                 /* event message queue object */
              "uc_queue",                   /* name */
              (OS_MSG_QTY)qsize,            /* max. size of message queue */
              &err);                        /* received error code */

    RKH_ASSERT(err == OS_ERR_NONE);
    rkh_sma_register(sma);
    rkh_sm_init((RKH_SM_T *)sma);

    /* Map RKH priority to uC/OS-III priority. */
    /* In both systems the lower the number the higher the priority. */
    /* In uC/OS-III the priorities 0, 1, OS_CFG_PRIO_MAX-2 and ... */
    /* ... OS_CFG_PRIO_MAX-3 are reserved. */
    /* See uC/OS-III API reference manual for more information. */

    if ((RKH_GET_PRIO(sma) + 2) >= (OS_CFG_PRIO_MAX - 2))
    {
        RKH_ASSERT(err == OS_ERR_NONE);
    }
    prio = RKH_GET_PRIO(sma) + 2;

    OSTaskCreate(&sma->thread,              /* task object */
                 "uc_task",                 /* name */
                 thread_function,           /* function */
                 sma,                       /* function argument */
                 prio,                      /* priority */
                 (CPU_STK *)stks,           /* stack base (low memory) */
                 (CPU_STK_SIZE)(stksize - 1),       /* stack limit */
                 stksize / sizeof(CPU_STK_SIZE),    /* stack size */
                 (OS_MSG_QTY)0,             /* queue size */
                 (OS_TICK)0,                /* time quanta in round-robin */
                 (void *)0,                 /* TCB extension */
                 OS_OPT_TASK_STK_CLR,       /* options */
                 &err);                     /* received error code */

    RKH_ASSERT(err == OS_ERR_NONE);
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
    OS_ERR err;
    RKH_SR_ALLOC();

    RKH_HOOK_SIGNAL(e);
    RKH_ENTER_CRITICAL_();

    RKH_INC_REF(e);
    OSQPost(&sma->equeue,                   /* event queue object */
            (void *)e,                      /* actual event posted */
            sizeof(RKH_EVT_T *),            /* size of event */
                                            /* type of POST performed */
            OS_OPT_POST_FIFO + OS_OPT_POST_NO_SCHED,
            &err);                          /* received error code */
    RKH_ALLEGE(err == OS_ERR_NONE);
    RKH_TR_SMA_FIFO(sma, e, sender, e->pool, e->nref,
                    &sma->equeue.MsgQ.NbrEntries,
                    &sma->equeue.MsgQ.NbrEntriesSize -
                    &sma->equeue.MsgQ.NbrEntriesMax);

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
    OS_ERR err;
    RKH_SR_ALLOC();

    RKH_HOOK_SIGNAL(e);
    RKH_ENTER_CRITICAL_();

    RKH_INC_REF(e);
    OSQPost(&sma->equeue,                   /* event queue object */
            (void *)e,                      /* actual event posted */
            sizeof(RKH_EVT_T *),            /* size of event */
                                            /* type of POST performed */
            OS_OPT_POST_LIFO + OS_OPT_POST_NO_SCHED,
            &err);                          /* received error code */
    RKH_ALLEGE(err == OS_ERR_NONE);
    RKH_TR_SMA_LIFO(sma, e, sender, e->pool, e->nref,
                    &sma->equeue.MsgQ.NbrEntries,
                    &sma->equeue.MsgQ.NbrEntriesSize -
                    &sma->equeue.MsgQ.NbrEntriesMax);

    RKH_EXIT_CRITICAL_();
}

RKH_EVT_T *
rkh_sma_get(RKH_SMA_T *sma)
{
    OS_ERR err;
    OS_MSG_SIZE ev_size;
    RKH_EVT_T *e;
    RKH_SR_ALLOC();

    e = OSQPend(&sma->equeue,               /* event queue object */
                (OS_TICK)0,                 /* wait forever for a event */
                OS_OPT_PEND_BLOCKING,       /* blocking system call */
                &ev_size,                   /* received event size */
                (CPU_TS *)0,                /* no time-stamp */
                &err);                      /* received error code */
    RKH_ASSERT(err == OS_ERR_NONE);
    /* To get the number of message currently in the queue and its */
    /* minimum number of free elements is not a reliable manner in uC/OS */
    /* Because the variables are obtained outside critical section could be */
    /* a race condition */
    RKH_TR_SMA_GET(sma, e, e->pool, e->nref,
                   &sma->equeue.MsgQ.NbrEntries,
                   &sma->equeue.MsgQ.NbrEntriesSize -
                   &sma->equeue.MsgQ.NbrEntriesMax);
    return e;
}

/* ------------------------------ End of file ------------------------------ */
