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
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhtrc_record.h
 *  \brief      Defines the trace records.
 *  \ingroup    apiTrc
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.15  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHTRC_RECORD_H__
#define __RKHTRC_RECORD_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtrc_stream.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#if RKH_CFG_TRC_EN == RKH_ENABLED
    /* --- Memory Pool (MP) ------------------------------------------------ */
    #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || \
        RKH_CFG_TRC_MP_EN == RKH_ENABLED
        /**
         *  \addtogroup trc
         *  @{
         *  \addtogroup traceMP Traces of memory pool services
         *  @{
         *  \brief      Macros for tracing the memory pool execution
         */

        /**
         *  \brief
         *  \copybrief rkh_memPool_init
         *
         *  \description    Initialize a memory block pool
         *  \trcGroup       RKH_TG_MP
         *  \trcEvent       RKH_TE_MP_INIT
         *
         *  \param[in] memPool_     Memory pool
         *  \param[in] nBlocks_     Total number of blocks in bytes
         *  \param[in] blockSize_   Maximum block size in bytes
         */
        #define RKH_TR_MP_INIT(memPool_, nBlocks_, blockSize_) \
            RKH_TRC_BEGIN_WOAOSIG(RKH_TE_MP_INIT) \
                RKH_TRC_SYM(memPool_); \
                RKH_TRC_NBLK(nBlocks_); \
                RKH_TRC_BSIZE(blockSize_); \
            RKH_TRC_END()

        /**
         *  \brief
         *  \copybrief rkh_memPool_get
         *
         *  \description    Get a block from the pool
         *  \trcGroup       RKH_TG_MP
         *  \trcEvent       RKH_TE_MP_GET
         *
         *  \param[in] memPool_     Memory pool
         *  \param[in] nFree_       Number of free blocks remaining
         *  \param[in] nMin_        Minimum number of free blocks ever in 
         *                          this pool, i.e. holds the lowest 
         *                          number of free blocks ever present in 
         *                          the pool.
         */
        #define RKH_TR_MP_GET(memPool_, nFree_, nMin_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_MP_GET) \
                RKH_TRC_SYM(memPool_); \
                RKH_TRC_NBLK(nFree_); \
                RKH_TRC_MP_NMIN(nMin_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  \copybrief rkh_memPool_put
         *
         *  \description    Put the block to the pool
         *  \trcGroup       RKH_TG_MP
         *  \trcEvent       RKH_TE_MP_PUT
         *
         *  \param[in] memPool_     Memory pool
         *  \param[in] nFree_       Number of free blocks remaining
         */
        #define RKH_TR_MP_PUT(memPool_, nFree_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_MP_PUT) \
                RKH_TRC_SYM(memPool_); \
                RKH_TRC_NBLK(nFree_); \
            RKH_TRC_END_NOCRIT()

        /** @} doxygen end group definition */
        /** @} doxygen end group definition */
    #else
        #define RKH_TR_MP_INIT(memPool_, nBlocks_, blockSize_)  (void)0
        #define RKH_TR_MP_GET(memPool_, nFree_, nMin_)          (void)0
        #define RKH_TR_MP_PUT(memPool_, nFree_)                 (void)0
    #endif

    /* --- Queue (QUE) ------------------------------------------------------ */
    #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || RKH_CFG_TRC_QUE_EN == RKH_ENABLED
        /**
         *  \addtogroup trc
         *  @{
         *  \addtogroup traceQ Traces of event queue services
         *  @{
         *  \brief      Macros for tracing the event queue execution
         */

        /**
         *  \brief
         *	\copybrief rkh_queue_init
         *
         *  \description    Initialize a event queue
         *  \trcGroup       RKH_TG_QUE
         *  \trcEvent       RKH_TE_QUE_INIT
         *
         *  \param[in] queue_   Event queue
         *  \param[in] actObj_  Associated active object that receives the 
         *                      equeued events.
         *  \param[in] nElem_   Storage size [in the units of void pointers]
         */
        #define RKH_TR_QUE_INIT(queue_, actObj_, nElem_) \
            RKH_TRC_BEGIN_WOAOSIG(RKH_TE_QUE_INIT) \
                RKH_TRC_SYM(queue_); \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_NE(nElem_); \
            RKH_TRC_END()

        /**
         *  \brief
         *  \copybrief rkh_queue_get
         *
         *  \description    Get and remove an element from a queue
         *  \trcGroup       RKH_TG_QUE
         *  \trcEvent       RKH_TE_QUE_GET
         *
         *  \param[in] queue_   Event queue
         *  \param[in] nElem_   Number of elements currently in the queue
         */
        #define RKH_TR_QUE_GET(queue_, nElem_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_QUE_GET) \
                RKH_TRC_SYM(queue_); \
                RKH_TRC_NE(nElem_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  \copybrief rkh_queue_put_fifo
         *
         *  \description    Puts an element on a queue in a FIFO manner
         *  \trcGroup       RKH_TG_QUE
         *  \trcEvent       RKH_TE_QUE_FIFO
         *
         *  \param[in] queue_   Event queue
         *  \param[in] nElem_   Number of elements currently in the queue
         *  \param[in] nMin_    Minimum number of free elements ever in 
         *                      this queue
         */
        #define RKH_TR_QUE_FIFO(queue_, nElem_, nMin_) \
            RKH_TRC_BEGIN_WOAOSIG(RKH_TE_QUE_FIFO) \
                RKH_TRC_SYM(queue_); \
                RKH_TRC_NE(nElem_); \
                RKH_TRC_QUE_NMIN(nMin_); \
            RKH_TRC_END()

        /**
         *  \brief
         *  \copybrief rkh_queue_put_lifo
         *
         *  \description    Puts an element on a queue in a LIFO manner
         *  \trcGroup       RKH_TG_QUE
         *  \trcEvent       RKH_TE_QUE_LIFO
         *
         *  \param[in] queue_   Event queue
         *  \param[in] nElem_   Number of elements currently in the queue
         *  \param[in] nMin_    Minimum number of free elements ever in 
         *                      this queue
         */
        #define RKH_TR_QUE_LIFO(queue_, nElem_, nMin_) \
            RKH_TRC_BEGIN_WOAOSIG(RKH_TE_QUE_LIFO) \
                RKH_TRC_SYM(queue_); \
                RKH_TRC_NE(nElem_); \
                RKH_TRC_QUE_NMIN(nMin_); \
            RKH_TRC_END()

        /**
         *  \brief
         *  Queue is full.
         *
         *  \description    Queue is full
         *  \trcGroup       RKH_TG_QUE
         *  \trcEvent       RKH_TE_QUE_FULL
         *
         *  \param[in] queue_   Event queue
         */
        #define RKH_TR_QUE_FULL(queue_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_QUE_FULL) \
                RKH_TRC_SYM(queue_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  \copybrief rkh_queue_deplete
         *
         *  \description    Depletes a queue
         *  \trcGroup       RKH_TG_QUE
         *  \trcEvent       RKH_TE_QUE_DPT
         *
         *  \param[in] queue_   Event queue
         */
        #define RKH_TR_QUE_DPT(queue_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_QUE_DPT) \
                RKH_TRC_SYM(queue_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  Get the last element from the queue
         *
         *  \description    Get the last element from the queue
         *  \trcGroup       RKH_TG_QUE
         *  \trcEvent       RKH_TE_QUE_GET_LAST
         *
         *  \param[in] queue_   Event queue
         */
        #define RKH_TR_QUE_GET_LAST(queue_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_QUE_GET_LAST)  \
                RKH_TRC_SYM(queue_); \
            RKH_TRC_END_NOCRIT()

        /** @} doxygen end group definition */
        /** @} doxygen end group definition */
    #else
        #define RKH_TR_QUE_INIT(queue_, actObj_, nElem_)     (void)0
        #define RKH_TR_QUE_GET(queue_, nElem_)               (void)0
        #define RKH_TR_QUE_FIFO(queue_, nElem_, nMin_)       (void)0
        #define RKH_TR_QUE_LIFO(queue_, nElem_, nMin_)       (void)0
        #define RKH_TR_QUE_FULL(queue_)                      (void)0
        #define RKH_TR_QUE_DPT(queue_)                       (void)0
        #define RKH_TR_QUE_GET_LAST(queue_)                  (void)0
    #endif

    /* --- State Machine Application (SMA) --------------------------------- */
    #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || \
        RKH_CFG_TRC_SMA_EN == RKH_ENABLED
        /**
         *  \addtogroup trc
         *  @{
         *  \addtogroup traceAO Traces of active objects
         *  @{
         *  \brief      Macros for tracing the active object execution
         */
        /**
         *  \brief
         *  \copybrief rkh_sma_activate
         *
         *  \description    Activate an active object
         *  \trcGroup       RKH_TG_SMA
         *  \trcEvent       RKH_TE_SMA_ACT
         *
         *  \param[in] actObj_          Active object
         *  \param[in] actObjPrio_      Active object priority
         *  \param[in] actObjQueSize_   Size of active object queue
         */
        #define RKH_TR_SMA_ACT(actObj_, actObjPrio_, actObjQueSize_) \
            RKH_TRC_BEGIN_WOSIG(RKH_TE_SMA_ACT, \
                                RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_UI8(actObjPrio_); \
                RKH_TRC_UI8(actObjQueSize_); \
            RKH_TRC_END()

        /**
         *  \brief
         *  \copybrief rkh_sma_terminate
         *
         *  \description    Terminate an active object
         *  \trcGroup       RKH_TG_SMA
         *  \trcEvent       RKH_TE_SMA_TERM
         *
         *  \param[in] actObj_   Active object
         *  \param[in] actObjPrio_    Active object priority
         */
        #define RKH_TR_SMA_TERM(actObj_, actObjPrio_) \
            RKH_TRC_BEGIN_WOSIG(RKH_TE_SMA_TERM, \
                                RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_UI8(actObjPrio_); \
            RKH_TRC_END()

        /**
         *  \brief
         *  Get an event from the active object's queue.
         *
         *  \description    
         *  \trcGroup       RKH_TG_SMA
         *  \trcEvent       RKH_TE_SMA_GET
         *
         *  \param[in] actObj_      Get an event from the active object 
         *                          queue
         *  \param[in] evt_         Event signal
         *  \param[in] poolID_      Pool ID (for dynamic events) 
         *  \param[in] refCntr_     Reference count (for dynamic events)
         *  \param[in] nElem_       Number of elements currently in the 
         *                          queue
         *  \param[in] nMin_        Minimum number of free elements ever 
         *                          in this queue
         */
        #define RKH_TR_SMA_GET(actObj_, evt_, poolID_, refCntr_, \
                               nElem_, nMin_) \
            RKH_TRC_BEGIN(RKH_TE_SMA_GET, \
                          RKH_SMA_ACCESS_CONST(actObj_, prio), (evt_)->e) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SIG((evt_)->e); \
                RKH_TRC_UI8(poolID_); \
                RKH_TRC_UI8(refCntr_); \
                RKH_TRC_NE(nElem_); \
                RKH_TRC_QUE_NMIN(nMin_); \
            RKH_TRC_END()

        /**
         *  \brief
         *  \copybrief rkh_sma_post_fifo
         *
         *  \description    Send a event to SMA's queue in a FIFO manner
         *  \trcGroup       RKH_TG_SMA
         *  \trcEvent       RKH_TE_SMA_FIFO
         *
         *  \param[in] actObj_  Active object
         *  \param[in] evt_     Event signal
         *  \param[in] sender_  Event sender
         *  \param[in] poolID_  Pool ID (for dynamic events) 
         *  \param[in] refCntr_ Reference count (for dynamic events)
         *  \param[in] nElem_   Number of elements currently in the 
         *                      queue
         *  \param[in] nMin_    Minimum number of free elements ever 
         *                      in this queue
         */
        #define RKH_TR_SMA_FIFO(actObj_, evt_, sender_, poolID_, refCntr_, \
                                nElem_, nMin_) \
            RKH_TRC_BEGIN_NOCRIT(RKH_TE_SMA_FIFO, \
                                 RKH_SMA_ACCESS_CONST(actObj_, prio), \
                                 (evt_)->e) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SIG((evt_)->e); \
                RKH_TRC_SNDR(sender_); \
                RKH_TRC_UI8(poolID_); \
                RKH_TRC_UI8(refCntr_); \
                RKH_TRC_NE(nElem_); \
                RKH_TRC_QUE_NMIN(nMin_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  \copybrief rkh_sma_post_lifo
         *
         *  \description    Send a event to SMA's queue in a LIFO manner
         *  \trcGroup       RKH_TG_SMA
         *  \trcEvent       RKH_TE_SMA_LIFO
         *
         *  \param[in] actObj_  Active object
         *  \param[in] evt_     Event signal
         *  \param[in] sender_  Event sender
         *  \param[in] poolID_  Pool ID (for dynamic events) 
         *  \param[in] refCntr_ Reference count (for dynamic events)
         *  \param[in] nElem_   Number of elements currently in the 
         *                      queue
         *  \param[in] nMin_    Minimum number of free elements ever 
         *                      in this queue
         */
        #define RKH_TR_SMA_LIFO(actObj_, evt_, sender_, poolID_, refCntr_, \
                                nElem_, nMin_) \
            RKH_TRC_BEGIN_NOCRIT(RKH_TE_SMA_LIFO, \
                                 RKH_SMA_ACCESS_CONST(actObj_, prio), \
                                 (evt_)->e) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SIG((evt_)->e); \
                RKH_TRC_SNDR(sender_); \
                RKH_TRC_UI8(poolID_); \
                RKH_TRC_UI8(refCntr_); \
                RKH_TRC_NE(nElem_); \
                RKH_TRC_QUE_NMIN(nMin_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  \copybrief rkh_sma_register
         *
         *  \description    Register an active object
         *  \trcGroup       RKH_TG_SMA
         *  \trcEvent       RKH_TE_SMA_REG
         *
         *  \param[in] actObj_      Active object
         *  \param[in] actObjPrio_  Active object priority
         */
        #define RKH_TR_SMA_REG(actObj_, actObjPrio_) \
            RKH_TRC_BEGIN_WOSIG_NOCRIT(RKH_TE_SMA_REG, \
                                       RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_UI8(actObjPrio_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  \copybrief rkh_sma_unregister
         *
         *  \description    Unregister an active object
         *  \trcGroup       RKH_TG_SMA
         *  \trcEvent       RKH_TE_SMA_UNREG
         *
         *  \param[in] actObj_      Active object
         *  \param[in] actObjPrio_  Active object priority
         */
        #define RKH_TR_SMA_UNREG(actObj_, actObjPrio_) \
            RKH_TRC_BEGIN_WOSIG_NOCRIT(RKH_TE_SMA_UNREG, \
                                       RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_UI8(actObjPrio_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  \copybrief rkh_sma_defer
         *
         *  \description    Defer an event
         *  \trcGroup       RKH_TG_SMA
         *  \trcEvent       RKH_TE_SMA_DEFER
         *
         *  \param[in] queue_    Target queue to store deferred event
         *  \param[in] evt_   Event
         */
        #define RKH_TR_SMA_DEFER(queue_, evt_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_SMA_DEFER) \
                RKH_TRC_SYM(queue_); \
                RKH_TRC_SIG((evt_)->e); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  \copybrief rkh_sma_recall
         *
         *  \description    Recall an event
         *  \trcGroup       RKH_TG_SMA
         *  \trcEvent       RKH_TE_SMA_RCALL
         *
         *  \param[in] actObj_   Active object
         *  \param[in] evt_   Event
         */
        #define RKH_TR_SMA_RCALL(actObj_, evt_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_SMA_RCALL) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SIG((evt_)->e); \
            RKH_TRC_END_NOCRIT()

        /** @} doxygen end group definition */
        /** @} doxygen end group definition */
    #else
        #define RKH_TR_SMA_ACT(actObj_, actObjPrio_, actObjQueSize_) \
            (void)0
        #define RKH_TR_SMA_TERM(actObj_, actObjPrio_) \
            (void)0
        #define RKH_TR_SMA_GET(actObj_, evt_, poolID_, refCntr_, nElem_, \
                               nMin_) \
            (void)0
        #define RKH_TR_SMA_FIFO(actObj_, evt_, sender_, poolID_, \
                                refCntr_, nElem_, nMin_) \
            (void)0
        #define RKH_TR_SMA_LIFO(actObj_, evt_, sender_, poolID_, \
                                refCntr_, nElem_, nMin_) \
            (void)0
        #define RKH_TR_SMA_REG(actObj_, actObjPrio_) \
            (void)0
        #define RKH_TR_SMA_UNREG(actObj_, actObjPrio_) \
            (void)0
        #define RKH_TR_SMA_DEFER(queue_, evt_) \
            (void)0
        #define RKH_TR_SMA_RCALL(actObj_, evt_) \
            (void)0
    #endif

    /* --- State machine (SM) ---------------------------------------------- */
    #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || \
        RKH_CFG_TRC_SM_EN == RKH_ENABLED
        /**
         *  \addtogroup trc
         *  @{
         *  \addtogroup traceSM Traces of state machine
         *  @{
         *  \brief      Macros for tracing the state machine execution
         */
        /**
         *  \brief
         *  \copybrief rkh_sm_init
         *
         *  \description    Initialize a state machine
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_INIT
         *
         *  \param[in] actObj_      Active object
         *  \param[in] initState_   Initial state of state machine
         */
        #if RKH_CFG_TRC_SM_INIT_EN == RKH_ENABLED
            #define RKH_TR_SM_INIT(actObj_, initState_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_INIT, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SYM(initState_); \
                RKH_TRC_END()
        #else
            #define RKH_TR_SM_INIT(actObj_, initState_)     (void)0
        #endif

        /**
         *  \brief
         *	\copybrief rkh_sm_clear_history
         *
         *  Desc    = clear history pseudostate\n
         *  Group   = RKH_TG_SM\n
         *  Id      = RKH_TE_SM_CLRH\n
         *  Args	= actObj_, history pseudostate\n
         *
         *  \description    Clear a history pseudostate
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_CLRH
         *
         *  \param[in] actObj_      Active object
         *  \param[in] history_     History pseudostate
         */
        #if RKH_CFG_TRC_SM_CLRH_EN == RKH_ENABLED
            #define RKH_TR_SM_CLRH(actObj_, history_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_CLRH, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SYM(history_); \
                RKH_TRC_END()
        #else
            #define RKH_TR_SM_CLRH(actObj_, history_)       (void)0
        #endif

        /**
         *  \brief
         *  \copybrief rkh_sm_dispatch
         *
         *  \description    Dispatch an event to a state machine
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_DCH
         *
         *  \param[in] actObj_  Active object
         *  \param[in] evt_     Dispatched event
         *  \param[in] state_   Current state
         */
        #if RKH_CFG_TRC_SM_DCH_EN == RKH_ENABLED
            #define RKH_TR_SM_DCH(actObj_, evt_, state_) \
                RKH_TRC_BEGIN(RKH_TE_SM_DCH, \
                              RKH_SMA_ACCESS_CONST(actObj_, prio), \
                              (evt_)->e) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SIG((evt_)->e); \
                RKH_TRC_SYM(state_); \
                RKH_TRC_END()
        #else
            #define RKH_TR_SM_DCH(actObj_, evt_, state_)   (void)0
        #endif

        /**
         *  \brief
         *	Source and target state of the transition. The target could be
         *	either basic state, composite state or pseudostate.
         *
         *  \description    Source and target state of transition
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_TRN
         *
         *  \param[in] actObj_          Active object
         *  \param[in] sourceState_     Source state
         *  \param[in] targetState_     Target state
         */
        #if RKH_CFG_TRC_SM_TRN_EN == RKH_ENABLED
            #define RKH_TR_SM_TRN(actObj_, sourceState_, targetState_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_TRN, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SYM(sourceState_); \
                RKH_TRC_SYM(targetState_); \
                RKH_TRC_END()
        #else
            #define RKH_TR_SM_TRN(actObj_, sourceState_, targetState_)           (void)0
        #endif

        /**
         *  \brief
         *	Legal, stable and final state of transition.
         *
         *  \description    Main target state of transition
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_STATE
         *
         *  \param[in] actObj_  Active object
         *  \param[in] state_   Target state of transition
         */
        #if RKH_CFG_TRC_SM_STATE_EN == RKH_ENABLED
            #define RKH_TR_SM_STATE(actObj_, state_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_STATE, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SYM(state_); \
                RKH_TRC_END()
        #else
            #define RKH_TR_SM_STATE(actObj_, state_)        (void)0
        #endif

        /**
         *  \brief
         *  Entered state.
         *
         *  \description    Entry state
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_ENSTATE
         *
         *  \param[in] actObj_  Active object
         *  \param[in] state_   Entry state
         */
        #if RKH_CFG_TRC_SM_ENSTATE_EN == RKH_ENABLED
            #define RKH_TR_SM_ENSTATE(actObj_, state_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_ENSTATE, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SYM(state_); \
                RKH_TRC_END()
        #else
            #define RKH_TR_SM_ENSTATE(actObj_, state_)      (void)0
        #endif

        /**
         *  \brief
         *  Exited state.
         *
         *  \description    Exit state
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_EXSTATE
         *
         *  \param[in] actObj_  Active object
         *  \param[in] state_   Exit state
         */
        #if RKH_CFG_TRC_SM_EXSTATE_EN == RKH_ENABLED
            #define RKH_TR_SM_EXSTATE(actObj_, state_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_EXSTATE, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SYM(state_); \
                RKH_TRC_END()
        #else
            #define RKH_TR_SM_EXSTATE(actObj_, state_)      (void)0
        #endif

        /**
         *  \brief
         *	Number of entry and exit states in transition.
         *
         *  \description    Number of entry and exit states in transition
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_NENEX
         *
         *  \param[in] actObj_      Active object
         *  \param[in] nEnState_    Number of entry states  
         *  \param[in] nExState_    Number of exit states
         */
        #if RKH_CFG_TRC_SM_NENEX_EN == RKH_ENABLED
            #define RKH_TR_SM_NENEX(actObj_, nEnState_, nExState_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_NENEX, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_UI8(nEnState_); \
                RKH_TRC_UI8(nExState_); \
        RKH_TRC_END()
        #else
            #define RKH_TR_SM_NENEX(actObj_, nEnState_, nExState_) \
                (void)nEnState_
        #endif

        /**
         *  \brief
         *	Number of executed actions and segments of the transition.
         *
         *  \description    Number of executed actions in transition
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_NTRNACT
         *
         *  \param[in] actObj_  Active object
         *  \param[in] nta      Number of executed effect action 
         *  \param[in] nts      Number of transition segments
         */
        #if RKH_CFG_TRC_SM_NTRNACT_EN == RKH_ENABLED
            #define RKH_TR_SM_NTRNACT(actObj_, nta, nts) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_NTRNACT, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_UI8(nta); \
                RKH_TRC_UI8(nts); \
                RKH_TRC_END()
        #else
            #define RKH_TR_SM_NTRNACT(actObj_, nta, nts)    (void)0
        #endif

        /**
         *  \brief
         *	Destination state or pseudostate of a transition segment.
         *
         *  \description    Next vertex in a compound transition
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_TS_STATE
         *
         *  \param[in] actObj_  Active object
         *  \param[in] state_   Target state of transition segment
         */
        #if RKH_CFG_TRC_SM_TS_STATE_EN == RKH_ENABLED
            #define RKH_TR_SM_TS_STATE(actObj_, state_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_TS_STATE, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SYM(state_); \
                RKH_TRC_END()
        #else
            #define RKH_TR_SM_TS_STATE(actObj_, state_)     (void)0
        #endif

        #if RKH_CFG_TRC_SM_PROCESS_EN == RKH_ENABLED

        /**
         *  \brief
         *	The arrived event was succesfully processed and HSM resides in 
         *	an allowed state
         *
         *  \description    The ocurred event was succesfully processed and 
         *                  the state machine resides in a stable state
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_EVT_PROC
         *
         *  \param[in] actObj_   Active object
         */
        #define RKH_TR_SM_EVT_PROC(actObj_) \
            RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_EVT_PROC, \
                                RKH_SMA_ACCESS_CONST(actObj_, prio)) \
            RKH_TRC_SYM(actObj_); \
            RKH_TRC_END()

        /**
         *  \brief
         *	The arrived event was't founded in the transition table.
         *
         *  \description    the arrived event was't founded in the 
         *                  transition table
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_EVT_NFOUND
         *
         *  \param[in] actObj_   Active object
         *  \param[in] evt_   Dispatched event 
         */
        #define RKH_TR_SM_EVT_NFOUND(actObj_, evt_) \
            RKH_TRC_BEGIN(RKH_TE_SM_EVT_NFOUND, \
                          RKH_SMA_ACCESS_CONST(actObj_, prio), \
                          (evt_)->e) \
            RKH_TRC_SYM(actObj_); \
            RKH_TRC_SIG((evt_)->e); \
            RKH_TRC_END()

        /**
         *  \brief
         *	The transition was cancelled by guard function.
         *
         *  \description    The transition was cancelled by a guard 
         *                  function 
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_GRD_FALSE
         *
         *  \param[in] actObj_   Active object
         */
        #define RKH_TR_SM_GRD_FALSE(actObj_) \
            RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_GRD_FALSE, \
                                RKH_SMA_ACCESS_CONST(actObj_, prio)) \
            RKH_TRC_SYM(actObj_); \
            RKH_TRC_END()

        /**
         *  \brief
         *	The branch function returned a value not founded in the branch
         *	table.
         *
         *  \description    The branch function returned a value not founded
         *                  in the branch table
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_CND_NFOUND
         *
         *  \param[in] actObj_   Active object
         */
        #define RKH_TR_SM_CND_NFOUND(actObj_) \
            RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_CND_NFOUND, \
                                RKH_SMA_ACCESS_CONST(actObj_, prio)) \
            RKH_TRC_SYM(actObj_); \
            RKH_TRC_END()

        /**
         *  \brief
         *	Unknown state.
         *
         *  \description    Unknown state
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_UNKN_STATE
         *
         *  \param[in] actObj_   Active object
         */

        #define RKH_TR_SM_UNKN_STATE(actObj_) \
            RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_UNKN_STATE, \
                                RKH_SMA_ACCESS_CONST(actObj_, prio)) \
            RKH_TRC_SYM(actObj_); \
            RKH_TRC_END()

        /**
         *  \brief
         *	The transition exceeded the allowed hierarchical level.
         *
         *  \description    The transition exceeded the allowed hierarchical
         *                  level
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_EX_HLEVEL
         *
         *  \param[in] actObj_   Active object
         */
        #define RKH_TR_SM_EX_HLEVEL(actObj_) \
            RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_EX_HLEVEL, \
                                RKH_SMA_ACCESS_CONST(actObj_, prio)) \
            RKH_TRC_SYM(actObj_); \
            RKH_TRC_END()

        /**
         *  \brief
         *	The transition exceeded the allowed number of segments within a
         *	compound transtion.
         *
         *  \description    The transition exceeded the allowed number of
         *                  segments within a compound transtion
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_EX_TSEG
         *
         *  \param[in] actObj_   Active object
         */
        #define RKH_TR_SM_EX_TSEG(actObj_) \
            RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_EX_TSEG, \
                                RKH_SMA_ACCESS_CONST(actObj_, prio)) \
            RKH_TRC_SYM(actObj_); \
            RKH_TRC_END()
        #else
            #define RKH_TR_SM_EVT_PROC(actObj_)             (void)0
            #define RKH_TR_SM_EVT_NFOUND(actObj_, evt_)     (void)0
            #define RKH_TR_SM_CND_NFOUND(actObj_)           (void)0
            #define RKH_TR_SM_GRD_FALSE(actObj_)            (void)0
            #define RKH_TR_SM_UNKN_STATE(actObj_)           (void)0
            #define RKH_TR_SM_EX_HLEVEL(actObj_)            (void)0
            #define RKH_TR_SM_EX_TSEG(actObj_)              (void)0
        #endif

        /**
         *  \brief
         *	Executes a behavior (action) of state machine, it could be an 
         *	entry, exit, effect, init, preprocessor or guard.
         *
         *  \description    Executed behavior of state machine
         *  \trcGroup       RKH_TG_SM
         *  \trcEvent       RKH_TE_SM_EXE_ACT
         *
         *  \param[in] actionType_  Action type
         *  \param[in] actObj_      Active object
         *  \param[in] state_       State
         *  \param[in] action_      Action
         */
        #if RKH_CFG_TRC_SM_EXE_ACT_EN == RKH_ENABLED
            #define RKH_TR_SM_EXE_ACT(actionType_, actObj_, state_, action_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_EXE_ACT, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_UI8(actionType_); \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SYM(state_); \
                RKH_TRC_FUN(action_); \
                RKH_TRC_END()
        #else
            #define RKH_TR_SM_EXE_ACT(actionType_, actObj_, state_, action_)     (void)0
        #endif

        /** @} doxygen end group definition */
        /** @} doxygen end group definition */
    #else
        #define RKH_TR_SM_INIT(actObj_, initState_)     (void)0
        #define RKH_TR_SM_CLRH(actObj_, history_)       (void)0
        #define RKH_TR_SM_DCH(actObj_, evt_, state_)   (void)0
        #define RKH_TR_SM_TRN(actObj_, sourceState_, targetState_) \
            (void)0
        #define RKH_TR_SM_STATE(actObj_, state_)        (void)0
        #define RKH_TR_SM_ENSTATE(actObj_, state_)      (void)0
        #define RKH_TR_SM_EXSTATE(actObj_, state_)      (void)0
        #define RKH_TR_SM_NENEX(actObj_, nEnState_, nExState_) \
            (void)0
        #define RKH_TR_SM_NTRNACT(actObj_, nta, nts)    (void)0
        #define RKH_TR_SM_TS_STATE(aaost)               (void)0
        #define RKH_TR_SM_EVT_PROC(actObj_)             (void)0
        #define RKH_TR_SM_EVT_NFOUND(actObj_, evt_)     (void)0
        #define RKH_TR_SM_GRD_FALSE(actObj_)            (void)0
        #define RKH_TR_SM_CND_NFOUND(actObj_)           (void)0
        #define RKH_TR_SM_UNKN_STATE(actObj_)           (void)0
        #define RKH_TR_SM_EX_HLEVEL(actObj_)            (void)0
        #define RKH_TR_SM_EX_TSEG(actObj_)              (void)0
        #define RKH_TR_SM_EXE_ACT(actionType_, actObj_, state_, action_) \
            (void)0
    #endif

    /* --- Timer (TIM) ----------------------------------------------------- */
    #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || \
        RKH_CFG_TRC_TMR_EN == RKH_ENABLED
        /**
         *  \addtogroup trc
         *  @{
         *  \addtogroup traceTMR Traces of timer services
         *  @{
         *  \brief      Macros for tracing the timer execution
         */
        /**
         *  \brief
         *  \copybrief RKH_TMR_INIT
         *
         *  \description    Initialize a timer
         *  \trcGroup       RKH_TG_TMR
         *  \trcEvent       RKH_TE_TMR_INIT
         *
         *  \param[in] timer_    Timer
         *  \param[in] signal_  Event to enqueued 
         */
        #define RKH_TR_TMR_INIT(timer_, signal_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_TMR_INIT) \
                RKH_TRC_SYM(timer_); \
                RKH_TRC_SIG(signal_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  \copybrief rkh_tmr_start
         *
         *  \description    Start a timer
         *  \trcGroup       RKH_TG_TMR
         *  \trcEvent       RKH_TE_TMR_START
         *
         *  \param[in] timer_    Timer
         *  \param[in] actObj_   Active object target
         *  \param[in] nTicks_   Load in ticks
         *  \param[in] period_  Period in ticks
         */
        #define RKH_TR_TMR_START(timer_, actObj_, nTicks_, period_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_TMR_START) \
                RKH_TRC_SYM(timer_); \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_NTICK(nTicks_); \
                RKH_TRC_NTICK(period_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  \copybrief rkh_tmr_stop
         *
         *  \description    Stop a timer
         *  \trcGroup       RKH_TG_TMR
         *  \trcEvent       RKH_TE_TMR_STOP
         *
         *  \param[in] timer_    Timer
         *  \param[in] nTicks_   Load in ticks
         *  \param[in] period_  Period in ticks
         */
        #define RKH_TR_TMR_STOP(timer_, nTicks_, period_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_TMR_STOP) \
                RKH_TRC_SYM(timer_); \
                RKH_TRC_NTICK(nTicks_); \
                RKH_TRC_NTICK(period_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  Timer expired.
         *
         *  \description    Timer has expired
         *  \trcGroup       RKH_TG_TMR
         *  \trcEvent       RKH_TE_TMR_TOUT
         *
         *  \param[in] timer_    Timer
         *  \param[in] signal_  Event to enqueued 
         *  \param[in] actObj_   Active object target
         */
        #define RKH_TR_TMR_TOUT(timer_, signal_, actObj_) \
            RKH_TRC_BEGIN_NOCRIT(RKH_TE_TMR_TOUT, \
                                 RKH_SMA_ACCESS_CONST(actObj_, prio), \
                                 signal_) \
                RKH_TRC_SYM(timer_); \
                RKH_TRC_SIG(signal_); \
                RKH_TRC_SYM(actObj_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *	Removes timer from the active timer list.
         *
         *  \description    Remove timer from the active timer list
         *  \trcGroup       RKH_TG_TMR
         *  \trcEvent       RKH_TE_TMR_REM
         *
         *  \param[in] timer_    Timer
         */
        #define RKH_TR_TMR_REM(timer_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_TMR_REM) \
                RKH_TRC_SYM(timer_); \
            RKH_TRC_END_NOCRIT()

        /** @} doxygen end group definition */
        /** @} doxygen end group definition */
    #else
        #define RKH_TR_TMR_INIT(timer_, signal_)                    (void)0
        #define RKH_TR_TMR_START(timer_, actObj_, nTicks_, period_) (void)0
        #define RKH_TR_TMR_STOP(timer_, nTicks_, period_)           (void)0
        #define RKH_TR_TMR_TOUT(timer_, signal_, actObj_)           (void)0
        #define RKH_TR_TMR_REM(timer_)                              (void)0
    #endif

    /* --- Framework (RKH) ------------------------------------------------- */
    #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || \
        RKH_CFG_TRC_FWK_EN == RKH_ENABLED
        /**
         *  \addtogroup trc
         *  @{
         *  \addtogroup traceFWK Traces of miscellaneous framework
         *  @{
         *  \brief Macros for tracing the framework execution
         */
        /**
         *  \brief
         *  \copybrief rkh_fwk_init
         *
         *  \description    Initialize the RKH framework
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_EN
         */
        #define RKH_TR_FWK_EN() \
            RKH_TRC_BEGIN_WOAOSIG(RKH_TE_FWK_EN) \
            RKH_TRC_END()

        /**
         *  \brief
         *  \copybrief rkh_fwk_exit
         *
         *  \description    Terminate the RKH framework
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_EX
         */
        #define RKH_TR_FWK_EX() \
            RKH_TRC_BEGIN_WOAOSIG(RKH_TE_FWK_EX) \
            RKH_TRC_END()

        /**
         *  \brief
         *  \copybrief rkh_fwk_registerEvtPool
         *
         *  \description    Register an event pool
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_EPREG
         *
         *  \param[in] evtPool_     Event pool id
         *  \param[in] storageSize_ Storage size
         *  \param[in] evtSize_     Event size
         *  \param[in] poolSize_    Total number of blocks
         */
        #define RKH_TR_FWK_EPREG(evtPool_, storageSize_, evtSize_, \
                                 poolSize_) \
            RKH_TRC_BEGIN_WOAOSIG(RKH_TE_FWK_EPREG) \
                RKH_TRC_UI8(evtPool_); \
                RKH_TRC_UI32(storageSize_); \
                RKH_TRC_ES(evtSize_); \
                RKH_TRC_NBLK(poolSize_); \
            RKH_TRC_END()

        /**
         *  \brief
         *  \copybrief rkh_fwk_ae
         *
         *  \description    Allocate an event from pool
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_AE
         *
         *  \param[in] evtSize_ Event size
         *  \param[in] evt_     Pointer to event object
         *  \param[in] nUsed_   Current number of memory blocks used 
         *  \param[in] nMin_    Lowest number of free blocks ever present 
         *  \param[in] sender_  Pointer to the actor that request a memory
         *                      block. It is not necessarily a pointer to
         *                      an active object. In fact, if 
         *                      RKH_ALLOC_EVT() is called from an 
         *                      interrupt or other context, it can create 
         *                      a unique object just to unambiguously 
         *                      identify the publisher of the event.
         */
        #define RKH_TR_FWK_AE(evtSize_, evt_, nUsed_, nMin_, sender_) \
            RKH_TRC_BEGIN_WOAOSIG(RKH_TE_FWK_AE) \
                RKH_TRC_ES(evtSize_); \
                RKH_TRC_SIG((evt_)->e); \
                RKH_TRC_UI8((evt_)->pool - 1); \
                RKH_TRC_UI8((evt_)->nref); \
                RKH_TRC_NBLK(nUsed_); \
                RKH_TRC_MP_NMIN(nMin_); \
                RKH_TRC_SYM(sender_); \
            RKH_TRC_END()

        /**
         *  \brief
         *  Attempt to recycle an event.
         *
         *  \description    Attempt to recycle an event
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_GC
         *
         *  \param[in] evt_   Event
         *  \param[in] poolID_  Event pool id
         *  \param[in] refCnt_   Reference count
         */
        #define RKH_TR_FWK_GC(evt_, poolID_, refCnt_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_FWK_GC) \
                RKH_TRC_SIG((evt_)->e); \
                RKH_TRC_UI8(poolID_); \
                RKH_TRC_UI8(refCnt_); \
            RKH_TRC_END_NOCRIT()

        /**
         *  \brief
         *  Effective recycling event.
         *
         *  \description    Effective recycling of event
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_GCR
         *
         *  \param[in] evt_     Pointer to event object
         *  \param[in] nUsed_   Current number of memory blocks used 
         *  \param[in] nMin_    Lowest number of free blocks ever present 
         *  \param[in] sender_  Pointer to the actor that request a memory
         *                      block. It is not necessarily a pointer to
         *                      an active object. In fact, if 
         *                      RKH_ALLOC_EVT() is called from an 
         *                      interrupt or other context, it can create 
         *                      a unique object just to unambiguously 
         *                      identify the publisher of the event.
         */
        #define RKH_TR_FWK_GCR(evt_, nUsed_, nMin_, sender_) \
            RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_FWK_GCR) \
                RKH_TRC_SIG((evt_)->e); \
                RKH_TRC_UI8((evt_)->pool - 1); \
                RKH_TRC_UI8((evt_)->nref); \
                RKH_TRC_NBLK(nUsed_); \
                RKH_TRC_MP_NMIN(nMin_); \
                RKH_TRC_SYM(sender_); \
            RKH_TRC_END_NOCRIT()

        /* --- Symbol entry table for objects -------------------------- */

        /**
         *  \brief
         *	Entry symbol table for memory object.
         *
         *  \description    Entry symbol table for memory object
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_OBJ
         *
         *  \param[in] obj_  Object address
         *
         *  e.g.\n
         *  Associates the address of the object, in memory
         *  with its symbolic name.
         *
         *  \code
         *  ...
         *  static int g_status;
         *  static RKH_TMR_T tdll;
         *
         *  RKH_TR_FWK_OBJ(&g_status);
         *  RKH_TR_FWK_OBJ(&tdll);
         *  \endcode
         */
        #define RKH_TR_FWK_OBJ(obj_) \
            do \
            { \
                static RKHROM char __o_n[] = # obj_; \
                rkh_trc_obj(RKH_TE_FWK_OBJ, (rui8_t *)obj_, \
                            __o_n); \
            } \
            while (0)

        /* --- Symbol entry table for objects with name ---------------- */

        /**
         *  \brief
         *	Entry symbol table for memory object. Very similar to
         *	RKH_TR_FWK_OBJ() but the name of object must be explicitely
         *	defined.
         *
         *  \description    Entry symbol table for memory object
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_OBJ
         *
         *  \param[in] obj_  Object address
         *  \param[in] name_  Name of object
         *
         *	\note
         *	This macro uses the same trace event that RKH_TR_FWK_OBJ().
         *	Use when the object name is very long and the Trazer's view is
         *	unclear.
         *
         *  e.g.\n
         *  Associates the address of the object, in memory with a name.
         *
         *  \code
         *  ...
         *  RKH_TR_FWK_OBJ_NAME(&RKH_CAST(CLI_T, sma)->cli_utmr, "cliutmr");
         *  \endcode
         */
        #define RKH_TR_FWK_OBJ_NAME(obj_, name_) \
            do \
            { \
                rkh_trc_obj(RKH_TE_FWK_OBJ, (rui8_t *)obj_, name_); \
            } \
            while (0)

        /* --- Symbol entry table for event signals -------------------- */

        /**
         *  \brief
         *	Entry symbol table for event signal.
         *
         *  \description    Entry symbol table for signal
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_SIG
         *
         *  \param[in] stateObj_  Signal
         *
         *  e.g.\n
         *  Associates the numerical value of the event signal to the
         *  symbolic name of the signal.
         *
         *  \code
         *  // in the dedicated application header file resides the signal
         *  // enumeration
         *
         *  enum
         *  {
         *      ...
         *      PWR_FAIL,
         *      PRESS_ENTER,
         *      ...
         *  };
         *
         *  // frequently, the macro RKH_TR_FWK_SIG() is used in the
         *  // \b main.c file.
         *
         *  RKH_TR_FWK_SIG(PWR_FAIL);
         *  RKH_TR_FWK_SIG(PRESS_ENTER);
         *  \endcode
         */
        #define RKH_TR_FWK_SIG(stateObj_) \
            do \
            { \
                static RKHROM char __s_n[] = # stateObj_; \
                rkh_trc_sig(stateObj_, __s_n); \
            } \
            while (0)

        /* --- Symbol entry table for functions ------------------------ */

        /**
         *  \brief
         *	Entry symbol table for function object.
         *
         *  \description    Entry symbol table for function
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_FUN
         *
         *  \param[in] function_  Function address
         *
         *  e.g.\n
         *  Associates the address of the function in memory
         *  with its symbolic name.
         *
         *  \code
         *  // frequently, the macro RKH_TR_FWK_FUN() is used in the
         *  // \b main.c file.
         *
         *  RKH_TR_FWK_FUN(my_init);
         *  RKH_TR_FWK_FUN(set_x_1);
         *  RKH_TR_FWK_FUN(set_x_2);
         *  RKH_TR_FWK_FUN(set_x_3);
         *  RKH_TR_FWK_FUN(set_y_0);
         *  RKH_TR_FWK_FUN(dummy_exit);
         *  ...
         *  \endcode
         */
        #define RKH_TR_FWK_FUN(function_) \
            do \
            { \
                static RKHROM char __f_n[] = #function_; \
                rkh_trc_obj(RKH_TE_FWK_FUN, (rui8_t *)function_, \
                            __f_n); \
            } \
            while (0)

        /**
         *  \brief
         *  The function was executed.
         *
         *  \description    Executed function
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_EXE_FUN
         *
         *  \param[in] function_   Function address
         *
         *  Example:
         *
         *  \code
         *  void
         *  my_init(const void *sma)
         *  {
         *      CMY(sma)->x = CMY(sma)->y = 0;
         *      RKH_TR_FWK_EXE_FUN(my_init);
         *  }
         *  \endcode
         */
        #define RKH_TR_FWK_EXE_FUN(function_) \
            RKH_TRC_BEGIN_WOFIL(RKH_TE_FWK_EXE_FUN) \
                RKH_TRC_FUN(function_); \
            RKH_TRC_END_WOFIL()

        /**
         *  \brief
         *  The function was synchronously executed. It is not explicitely
         *  used by the RKH, instead it's frequently placed on application
         *  source code.
         *
         *  \description    Function was synchronously executed
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_SYNC_EVT
         *
         *  \param[in] function_   Function address
         *  \param[in] senderObj_  Sender object
         *  \param[in] receiverObj_  Receiver object
         *
         *  Example:
         *
         *  \code
         *  void
         *  Gas_setCommandedFlow(Gas *me, unsigned int p_commandedFlow)
         *  {
         *      (void)pe;
         *      Valve_setAperture(me->itsValve, 0);
         *      RKH_TR_FWK_SYNC_EVT(Valve_setAperture, &itsGas, 
         *                          me->itsValve);
         *  }
         *  \endcode
         */
        #define RKH_TR_FWK_SYNC_EVT(function_, senderObj_, receiverObj_) \
            RKH_TRC_BEGIN_WOFIL(RKH_TE_FWK_SYNC_EVT) \
                RKH_TRC_FUN(function_); \
                RKH_TRC_SNDR(senderObj_); \
                RKH_TRC_SNDR(receiverObj_); \
            RKH_TRC_END_WOFIL()

        /* --- Symbol entry table for user user-defined trace events --- */

        /**
         *  \brief
         *	Entry symbol table for user-defined trace events.
         *
         *  \description    Entry symbol table for user-defined trace events
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_TUSR
         *
         *  \param[in] __e  User trace event ID
         *
         *  e.g.\n
         *  Associates the numerical value of the user-defined trace event 
         *  to the symbolic name of that.
         *
         *  \code
         *  ...
         *  // frequently, the macro RKH_TR_FWK_TUSR() is used in the
         *  // \b main.c file.
         *
         *	enum // define the user trace events
         *	{
         *		LOWPWR_USRT = RKH_TE_USER,
         *		DISCONNECTED_USRT,
         *		...
         *	};
         *
         *  void
         *  main(void)
         *  {
         *      RKH_TR_FWK_TUSR(LOWPWR_USRT);
         *      RKH_TR_FWK_TUSR(DISCONNECTED_USRT);
         *      ...
         *  }
         *  \endcode
         */
        #define RKH_TR_FWK_TUSR(__e) \
            do \
            { \
                static RKHROM char __e_n[] = # __e; \
                RKH_TRC_BEGIN_WOFIL(RKH_TE_FWK_TUSR) \
                    RKH_TRC_TE_ID(EXTE(__e, RKH_TG_USR)); \
                    RKH_TRC_STR(__e_n); \
                    RKH_TRC_END_WOFIL() \
                RKH_TRC_FLUSH(); \
            } \
            while (0)

        /* --- Trace configuration ------------------------------------- */

        /**
         *  \brief
         *	Send trace configuration to Trazer.
         *
         *  \description    Send trace configuration table to Trazer
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_TCFG
         *
         *  \param[in] timeStamp_    Trace timestamp in Hz [ticks per 
         *                          second]
         *
         *  \note
         *  The following table shows the format of RKH_TE_FWK_TCFG 
         *  arguments.
         *  The first column means ["byte index", "bit index":"# of 
         *  bits"] in the data stream.
         *
         *  [byte_index:size in bits] \n
         *  [ 0, 0:16] - RKH_VERSION_CODE \n
         *  [ 2, 0: 1] - RKH_CFG_SMA_TRC_SNDR_EN \n
         *  [ 2, 1: 1] - RKH_CFG_TRC_RTFIL_EN \n
         *  [ 2, 2: 1] - RKH_CFG_TRC_USER_TRACE_EN \n
         *  [ 2, 3: 1] - RKH_CFG_TRC_ALL_EN \n
         *  [ 2, 4: 1] - RKH_CFG_TRC_MP_EN \n
         *  [ 2, 5: 1] - RKH_CFG_TRC_QUE_EN \n
         *  [ 2, 6: 1] - RKH_CFG_TRC_SMA_EN \n
         *  [ 2, 7: 1] - RKH_CFG_TRC_TMR_EN \n
         *  [ 3, 8: 1] - RKH_CFG_TRC_SM_EN \n
         *  [ 3, 9: 1] - RKH_CFG_TRC_FWK_EN \n
         *  [ 3,10: 1] - RKH_CFG_TRC_ASSERT_EN \n
         *  [ 3,11: 1] - RKH_CFG_QUE_GET_LWMARK_EN \n
         *  [ 3,12: 1] - RKH_CFG_MP_GET_LWM_EN \n
         *  [ 3,13: 1] - RKH_CFG_TRC_RTFIL_SMA_EN \n
         *  [ 3,14: 1] - RKH_CFG_TRC_RTFIL_SIGNAL_EN \n
         *  [ 3,15: 1] - RKH_CFG_TRC_NSEQ_EN \n
         *  [ 4,16: 1] - RKH_CFG_TRC_TSTAMP_EN \n
         *  [ 4,17: 1] - RKH_CFG_TRC_CHK_EN \n
         *  [ 4,18:14] - 0 (Reserved) \n
         *  [ 6, 0: 4] - RKH_CFG_FWK_SIZEOF_EVT \n
         *  [ 6, 4: 4] - RKH_CFGPORT_TRC_SIZEOF_TSTAMP \n
         *  [ 7, 0: 4] - RKH_CFGPORT_TRC_SIZEOF_PTR \n
         *  [ 7, 4: 4] - RKH_CFG_TMR_SIZEOF_NTIMER \n
         *  [ 8, 0: 4] - RKH_CFG_MP_SIZEOF_NBLOCK \n
         *  [ 8, 4: 4] - RKH_CFG_QUE_SIZEOF_NELEM \n
         *  [ 9, 0: 4] - RKH_CFG_FWK_SIZEOF_EVT_SIZE \n
         *  [ 9, 4: 4] - 0 (Reserved) \n
         *  [10, 0: 4] - RKH_CFG_MP_SIZEOF_BSIZE \n
         *  [10, 4: 4] - RKH_CFG_FWK_MAX_EVT_POOL \n
         *  [11, 0:16] - Timestamp HZ (ticks per second)
         */
        #define RKH_TR_FWK_TCFG(timeStamp_) \
            RKH_TRC_BEGIN_DFT(RKH_TE_FWK_TCFG) \
                RKH_TRC_UI16((rui16_t)RKH_VERSION_CODE); \
                RKH_TRC_UI32( \
                    (rui32_t)( \
                        ((rui32_t)RKH_CFG_SMA_TRC_SNDR_EN) | \
                        ((rui32_t)RKH_CFG_TRC_RTFIL_EN << 1) | \
                        ((rui32_t)RKH_CFG_TRC_USER_TRACE_EN << 2) | \
                        ((rui32_t)RKH_CFG_TRC_ALL_EN << 3) | \
                        ((rui32_t)RKH_CFG_TRC_MP_EN << 4) | \
                        ((rui32_t)RKH_CFG_TRC_QUE_EN << 5) | \
                        ((rui32_t)RKH_CFG_TRC_SMA_EN << 6) | \
                        ((rui32_t)RKH_CFG_TRC_TMR_EN << 7) | \
                        ((rui32_t)RKH_CFG_TRC_SM_EN << 8) | \
                        ((rui32_t)RKH_CFG_TRC_FWK_EN << 9) | \
                        ((rui32_t)RKH_CFG_TRC_ASSERT_EN << 10) | \
                        ((rui32_t)RKH_CFG_QUE_GET_LWMARK_EN << 11) | \
                        ((rui32_t)RKH_CFG_MP_GET_LWM_EN << 12) | \
                        ((rui32_t)RKH_CFG_TRC_RTFIL_SMA_EN << 13) | \
                        ((rui32_t)RKH_CFG_TRC_RTFIL_SIGNAL_EN << 14) | \
                        ((rui32_t)RKH_CFG_TRC_NSEQ_EN << 15) | \
                        ((rui32_t)RKH_CFG_TRC_TSTAMP_EN << 16) | \
                        ((rui32_t)RKH_CFG_TRC_CHK_EN << 17))); \
                RKH_TRC_UI8( \
                    (rui8_t)((RKH_CFG_FWK_SIZEOF_EVT / 8 << 4) | \
                             RKH_CFGPORT_TRC_SIZEOF_TSTAMP / 8)); \
                RKH_TRC_UI8( \
                    (rui8_t)((RKH_CFGPORT_TRC_SIZEOF_PTR / 8 << 4) | \
                             RKH_CFG_TMR_SIZEOF_NTIMER / 8)); \
                RKH_TRC_UI8( \
                    (rui8_t)((RKH_CFG_MP_SIZEOF_NBLOCK / 8 << 4) | \
                             RKH_CFG_QUE_SIZEOF_NELEM / 8)); \
                RKH_TRC_UI8( \
                    (rui8_t)(RKH_CFG_FWK_SIZEOF_EVT_SIZE / 8)); \
                RKH_TRC_UI8( \
                    (rui8_t)((RKH_CFG_MP_SIZEOF_BSIZE / 8 << 4) | \
                             RKH_CFG_FWK_MAX_EVT_POOL)); \
                RKH_TRC_UI16( \
                    (rui16_t)(timeStamp_)); \
            RKH_TRC_END_DFT() \
            RKH_TRC_FLUSH()

        /* --- Assertion ----------------------------------------------- */

        /**
         *  \brief
         *	Assertion expression was evaluated to false.
         *
         *  \description    Assertion expression was evaluated to false
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_EXE_ASSERT
         *
         *  \param[in] mod_ Module name (*.c)
         *  \param[in] ln_  Line of code
         */
        #if RKH_CFG_TRC_ASSERT_EN == RKH_ENABLED
            #define RKH_TR_FWK_ASSERT(mod_, ln_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_FWK_ASSERT) \
                    RKH_TRC_STR((RKHROM char *)mod_); \
                    RKH_TRC_UI16((rui16_t)ln_); \
                    RKH_TRC_END_NOCRIT() \
                RKH_TRC_FLUSH()
        #else
            #define RKH_TR_FWK_ASSERT(mod_, ln_)      (void)0
        #endif

        /* --- Symbol entry table for active objects ------------------- */

        /**
         *  \brief
         *	Entry symbol table for active object.
         *
         *  \description    Entry symbol table for active object
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_OBJ
         *
         *  \param[in] actObj_ Active object address
         *
         *  e.g.\n
         *  Associates the address of the active object, in memory
         *  with its symbolic name.
         *
         *  \code
         *  ...
         *  typedef struct
         *  {
         *      RKH_SMA_T actObj_;
         *      rui8_t x;
         *      rui8_t y;
         *  } AO_T;
         *
         *  RKH_SMA_CREATE(AO_T, actObj_, 0, HCAL, &S1, ao_init, NULL);
         *  RKH_TR_FWK_OBJ(&actObj_);
         *  \endcode
         */
        #define RKH_TR_FWK_AO(actObj_) \
            do \
            { \
                rkh_trc_ao((struct RKH_SMA_T *)actObj_); \
            } \
            while (0)

        /* --- Symbol entry table for state objects -------------------- */

        /**
         *  \brief
         *	Entry symbol table for state object.
         *
         *  \description    Entry symbol table for state object
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_OBJ
         *
         *  \param[in] actObj_ Active object address
         *  \param[in] stateObj_ State object address
         *
         *  e.g.\n
         *  Associates the address of the state object, in memory
         *  with its symbolic name.
         *
         *  \code
         *  ...
         *  RKH_CREATE_COMP_STATE(S1, en, ex, RKH_ROOT, &S11);
         *  RKH_CREATE_TRANS_TABLE(S1)
         *      RKH_TRINT(SIX,     NULL,       show_data),
         *      RKH_TRREG(TWO,     NULL,       set_y_2,	&S2),
         *  RKH_END_TRANS_TABLE
         *
         *  ...
         *  RKH_TR_FWK_STATE(my, &S1);
         *  \endcode
         */
        #define RKH_TR_FWK_STATE(actObj_, stateObj_) \
            do \
            { \
                rkh_trc_state((struct RKH_SMA_T *)actObj_, \
                              (rui8_t *)stateObj_); \
            } \
            while (0)

        /* --- Symbol entry table for pseudostate objects -------------- */

        /**
         *  \brief
         *	Entry symbol table for pseudostate object.
         *
         *  \description    Entry symbol table for pseudostate object
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_OBJ
         *
         *  \param[in] actObj_     Active object address
         *  \param[in] pseudoStObj_    Pseudostate object address
         *
         *  e.g.\n
         *  Associates the address of the pseudostate object, in memory
         *  with its symbolic name.
         *
         *  \code
         *  ...
         *  RKH_CREATE_COND_STATE(C1, 12);
         *  RKH_CREATE_BRANCH_TABLE(C1)
         *      RKH_BRANCH(y_1,    NULL,           &H),
         *      RKH_BRANCH(y_2,    dummy_act,      &DH),
         *      RKH_BRANCH(y_0,    NULL,           &S1),
         *  RKH_END_BRANCH_TABLE
         *
         *  ...
         *  RKH_TR_FWK_PSTATE(my, &C1);
         *  \endcode
         */
        #define RKH_TR_FWK_PSTATE(actObj_, pseudoStObj_) \
            do \
            { \
                rkh_trc_state((struct RKH_SMA_T *)actObj_, \
                              (rui8_t *)pseudoStObj_); \
            } \
            while (0)

        /* --- Symbol entry table for timer objects -------------------- */

        /**
         *  \brief
         *	Entry symbol table for timer object.
         *
         *  \description    Entry symbol table for timer object
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_OBJ
         *
         *  \param[in] timerObj_ Timer object address
         *
         *  e.g.\n
         *  Associates the address of the timer object, in memory
         *  with its symbolic name.
         *
         *  \code
         *  ...
         *  static RKH_TMR_T bky_tmr;
         *
         *  RKH_TR_FWK_TIMER(&bky_tmr);
         *  \endcode
         */
        #define RKH_TR_FWK_TIMER(timerObj_) \
            do \
            { \
                static RKHROM char __to_n[] = # timerObj_; \
                rkh_trc_obj(RKH_TE_FWK_TIMER, (rui8_t *)timerObj_, \
                            __to_n); \
            } \
            while (0)

        /* --- Symbol entry table for event pool objects --------------- */

        /**
         *  \brief
         *	Entry symbol table for event pool object.
         *
         *  \description    Entry symbol table for event pool object
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_OBJ
         *
         *  \param[in] poolId_   Event pool ID (index of event pool list)
         *  \param[in] poolName_ String terminated in '\\0'.
         *
         *  e.g.\n
         *  Associates the ID of the event pool, with a symbolic name.
         *
         *  \code
         *	...
         *	rkh_fwk_registerEvtPool(ep0_sto,	SIZEOF_EP0STO,
         *						    SIZEOF_EP0_BLOCK);
         *	rkh_fwk_registerEvtPool(ep1_sto, SIZEOF_EP1STO,
         *						    SIZEOF_EP1_BLOCK);
         *	rkh_fwk_registerEvtPool(ep2_sto, SIZEOF_EP2STO,
         *						    SIZEOF_EP2_BLOCK);
         *
         *  RKH_TR_FWK_EPOOL(0, "ep0");
         *  RKH_TR_FWK_EPOOL(1, "ep1");
         *  RKH_TR_FWK_EPOOL(2, "ep2");
         *	...
         *  \endcode
         */
        #define RKH_TR_FWK_EPOOL(poolId_, poolName_) \
            RKH_TRC_BEGIN_WOFIL(RKH_TE_FWK_EPOOL) \
                RKH_TRC_UI8(poolId_); \
                RKH_TRC_STR(poolName_); \
            RKH_TRC_END_WOFIL() \
            RKH_TRC_FLUSH();

        /* --- Symbol entry table for queue objects -------------------- */

        /**
         *  \brief
         *	Entry symbol table for queue object.
         *
         *  \description    Entry symbol table for queue object
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_OBJ
         *
         *  \param[in] queueObj_ Queue object address
         *
         *  e.g.\n
         *  Associates the address of the queue object, in memory
         *  with its symbolic name.
         *
         *  \code
         *  ...
         *  #define QSTO_SIZE			4
         *  static RKH_EVT_T *qsto[QSTO_SIZE];
         *
         *  ...
         *  RKH_TR_FWK_QUEUE(&blinky->equeue);
         *  rkh_sma_activate(blinky, (const RKH_EVT_T **)qsto,
         *                   QSTO_SIZE, CV(0), 0);
         *	...
         *  \endcode
         */
        #define RKH_TR_FWK_QUEUE(queueObj_) \
            do \
            { \
                static RKHROM char __qo_n[] = #queueObj_; \
                rkh_trc_obj(RKH_TE_FWK_QUEUE, (rui8_t *)queueObj_, \
                            __qo_n); \
            } \
            while (0)

        /**
         *  \brief
         *	Entry symbol table for actor object.
         *
         *  \description    Entry symbol table for actor object
         *  \trcGroup       RKH_TG_FWK
         *  \trcEvent       RKH_TE_FWK_ACTOR
         *
         *  \param[in] actorObj_    Actor object address. Generally, it's 
         *                          used for active object and ISR, i.e. 
         *                          event producers.
         *  \param[in] nm_          String terminated in '\\0'
         *
         *  e.g.\n
         *  Associates the address of an actor object, in memory
         *  with its symbolic name.
         *
         *  \code
         *  RKH_TR_FWK_ACTOR(blinky, RKH_GET_AO_NAME(blinky));
         *  ...
         *  static int buttonManager;
         *
         *  RKH_TR_FWK_ACTOR(&buttonManager, "buttonManager");
         *  \endcode
         */
        #define RKH_TR_FWK_ACTOR(actorObj_, nm_) \
            do \
            { \
                rkh_trc_obj(RKH_TE_FWK_ACTOR, (rui8_t *)actorObj_, nm_); \
            } \
            while (0)

        /** @} doxygen end group definition */
        /** @} doxygen end group definition */
    #else
        #define RKH_TR_FWK_EN()                                     (void)0
        #define RKH_TR_FWK_EX()                                     (void)0
        #define RKH_TR_FWK_EPREG(evtPool_, storageSize_, evtSize_, \
                                 poolSize_)                         (void)0
        #define RKH_TR_FWK_AE(evtSize_, evt_, nUsed_, nMin_, sndr_) (void)0
        #define RKH_TR_FWK_GC(evt_, poolID_, refCnt_)               (void)0
        #define RKH_TR_FWK_GCR(evt_, nUsed_, nMin_, sndr_)          (void)0
        #define RKH_TR_FWK_OBJ(obj_)                                (void)0
        #define RKH_TR_FWK_OBJ_NAME(obj_, name_)                    (void)0
        #define RKH_TR_FWK_SIG(stateObj_)                           (void)0
        #define RKH_TR_FWK_FUN(stateObj_)                           (void)0
        #define RKH_TR_FWK_EXE_FUN(function_)                       (void)0
        #define RKH_TR_FWK_SYNC_EVT(function_, senderObj_, \
                                    receiverObj_)                   (void)0
        #define RKH_TR_FWK_TUSR(__e)                                (void)0
        #define RKH_TR_FWK_TCFG(timeStamp_)                         (void)0
        #define RKH_TR_FWK_ASSERT(mod_, ln_)                        (void)0
        #define RKH_TR_FWK_AO(actObj_)                              (void)0
        #define RKH_TR_FWK_STATE(actObj_, stateObj_)                (void)0
        #define RKH_TR_FWK_PSTATE(actObj_, pseudoStObj_)            (void)0
        #define RKH_TR_FWK_TIMER(timerObj_)                         (void)0
        #define RKH_TR_FWK_EPOOL(evtPoolObj_)                       (void)0
        #define RKH_TR_FWK_QUEUE(queueObj_)                         (void)0
        #define RKH_TR_FWK_ACTOR(actObj_, nm_)                      (void)0
    #endif
#else
    /* --- Memory Pool (MP) -------------------------------------------- */
    #define RKH_TR_MP_INIT(mp, nb, bs)                (void)0
    #define RKH_TR_MP_GET(mp, nfree, nmin)            (void)0
    #define RKH_TR_MP_PUT(mp, nfree)                  (void)0

    /* --- Queue (QUE) -------------------------------------------------- */
    #define RKH_TR_QUE_INIT(q, ao, nelem)              (void)0
    #define RKH_TR_QUE_GET(q, nelem)                   (void)0
    #define RKH_TR_QUE_FIFO(q, nelem, nmin)            (void)0
    #define RKH_TR_QUE_LIFO(q, nelem, nmin)            (void)0
    #define RKH_TR_QUE_FULL(q)                         (void)0
    #define RKH_TR_QUE_DPT(q)                          (void)0
    #define RKH_TR_QUE_GET_LAST(q)                     (void)0

    /* --- State Machine Application (SMA) ----------------------------- */
    #define RKH_TR_SMA_ACT(ao, p, s)                  (void)0
    #define RKH_TR_SMA_TERM(ao, p)                    (void)0
    #define RKH_TR_SMA_GET(ao, ev, pid, rc, ne, nm)   (void)0
    #define RKH_TR_SMA_FIFO(ao, ev, snr, pid, rc, ne, \
                            nm)                       (void)0
    #define RKH_TR_SMA_LIFO(ao, ev, snr, pid, rc, ne, \
                            nm)                       (void)0
    #define RKH_TR_SMA_REG(ao, actObjPrio_)           (void)0
    #define RKH_TR_SMA_UNREG(ao, actObjPrio_)         (void)0
    #define RKH_TR_SMA_DEFER(queue_, evt_)            (void)0
    #define RKH_TR_SMA_RCALL(actObj_, evt_)           (void)0

    /* --- State machine (SM) ------------------------------------------ */
    #define RKH_TR_SM_INIT(ao, ist)                   (void)0
    #define RKH_TR_SM_CLRH(ao, h)                     (void)0
    #define RKH_TR_SM_DCH(ao, ev, st)                 (void)0
    #define RKH_TR_SM_TRN(ao, sst, tst)               (void)0
    #define RKH_TR_SM_STATE(ao, st)                   (void)0
    #define RKH_TR_SM_ENSTATE(ao, st)                 (void)0
    #define RKH_TR_SM_EXSTATE(ao, st)                 (void)0
    #define RKH_TR_SM_NENEX(ao, nen, nex)             (void)0
    #define RKH_TR_SM_NTRNACT(ao, nta, nts)           (void)0
    #define RKH_TR_SM_TS_STATE(ao, st)                (void)0
    #define RKH_TR_SM_EVT_PROC(ao)                    (void)0
    #define RKH_TR_SM_EVT_NFOUND(ao, ev)              (void)0
    #define RKH_TR_SM_GRD_FALSE(ao)                   (void)0
    #define RKH_TR_SM_CND_NFOUND(ao)                  (void)0
    #define RKH_TR_SM_UNKN_STATE(ao)                  (void)0
    #define RKH_TR_SM_EX_HLEVEL(ao)                   (void)0
    #define RKH_TR_SM_EX_TSEG(ao)                     (void)0
    #define RKH_TR_SM_EXE_ACT(act_t, ao, st, act)     (void)0

    /* --- Timer (TIM) ------------------------------------------------- */
    #define RKH_TR_TMR_INIT(t, sig)                   (void)0
    #define RKH_TR_TMR_START(t, ao, nt, per)          (void)0
    #define RKH_TR_TMR_STOP(t, nt, per)               (void)0
    #define RKH_TR_TMR_TOUT(t, sig, ao)               (void)0
    #define RKH_TR_TMR_REM(t)                         (void)0

    /* --- Framework (RKH) --------------------------------------------- */
    #define RKH_TR_FWK_EN()                           (void)0
    #define RKH_TR_FWK_EX()                           (void)0
    #define RKH_TR_FWK_EPREG(ep, ss, es, poolSize_)   (void)0
    #define RKH_TR_FWK_AE(es, ev, nUsed_, nMin_, \
                          sndr_)                      (void)0
    #define RKH_TR_FWK_GC(ev, pid, rc)                (void)0
    #define RKH_TR_FWK_GCR(ev, nUsed_, nMin_, sndr_)  (void)0
    #define RKH_TR_FWK_OBJ(__o)                       (void)0
    #define RKH_TR_FWK_OBJ_NAME(__o, __n)             (void)0
    #define RKH_TR_FWK_SIG(__s)                       (void)0
    #define RKH_TR_FWK_FUN(__f)                       (void)0
    #define RKH_TR_FWK_EXE_FUN(__f)                   (void)0
    #define RKH_TR_FWK_SYNC_EVT(fn, snr, rcr)         (void)0
    #define RKH_TR_FWK_TUSR(__e)                      (void)0
    #define RKH_TR_FWK_TCFG(ts_hz)                    (void)0
    #define RKH_TR_FWK_ASSERT(mod_, ln_)              (void)0
    #define RKH_TR_FWK_AO(__ao)                       (void)0
    #define RKH_TR_FWK_STATE(__ao, __so)              (void)0
    #define RKH_TR_FWK_PSTATE(__ao, __pso)            (void)0
    #define RKH_TR_FWK_TIMER(__to)                    (void)0
    #define RKH_TR_FWK_EPOOL(__epo)                   (void)0
    #define RKH_TR_FWK_QUEUE(__qo)                    (void)0
    #define RKH_TR_FWK_ACTOR(actObj_, nm_)            (void)0
#endif

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Initializes the RKH's trace record service.
 *
 *  \note
 *  rkh_trc_init() is NOT protected with a critical section.
 */
void rkh_trc_init(void);

/**
 *  \brief
 *  Store the trace record header in the stream.
 *
 *	- Trace event ID [n-bytes]. The number of bytes that it uses is specified 
 *	by the size of RKH_TE_ID_T data type.
 *
 *	- Sequence number [1-byte]. If the RKH_CFG_TRC_NSEQ_EN is set to 1 then
 *	RKH will add to the trace record an incremental number (1-byte), used
 *	like a sequence number.
 *
 *	- Timestamp [1, 2 or 4 bytes]. If the RKH_CFG_TRC_TSTAMP_EN is set to 1
 *	then RKH will add to the trace record a timestamp field. It's
 *	configurable by means of RKH_CFGPORT_TRC_SIZEOF_TSTAMP.
 *
 *	\param[in] eid		trace event ID. The available events are
 *                      enumerated in RKH_TE_<group>_<event> definitions.
 *
 *  \note
 *	This function should be called indirectly through the macro
 *	RKH_TRC_BEGIN.
 */
void rkh_trc_begin(RKH_TE_ID_T eid);

/**
 *  \brief
 *  Terminate the recorded trace event.
 *
 *	This function inserts a the flag byte, which delimits the frame.
 *	The flag is the 0x7E.
 *
 *  \note
 *	This function should be called indirectly through the macro
 *	RKH_TRC_END.
 */
void rkh_trc_end(void);

/**
 *  \brief
 *  Clear to zero the trace record checksum.
 *
 *  \note
 *	This function should be called indirectly through the macro
 *	RKH_TRC_BEGIN_DFT().
 */
void rkh_trc_clear_chk(void);

/**
 *  \brief
 *  Store a 8-bit data into the current trace event buffer without format
 *  information.
 *
 *  \param[in] d		data
 */
void rkh_trc_u8(rui8_t d);

/**
 *  \brief
 *  Store a 16-bit data into the current trace event buffer without format
 *  information.
 *
 *  \param[in] d		data
 */
void rkh_trc_u16(rui16_t d);

/**
 *  \brief
 *  Store a 32-bit data into the current trace event buffer without format
 *  information.
 *
 *  \param[in] d		data
 */
void rkh_trc_u32(rui32_t d);

/**
 *  \brief
 *  Store a string terminated in '\\0' into the current trace event buffer
 *  without format information.
 *
 *  \param[in] s		pointer to string treminated in '\\0'
 */
void rkh_trc_str(const char *s);

/**
 *  \brief
 *  Output object symbol record.
 *
 *  \param[in] tre		trace event ID. The available events are enumerated in
 *                      RKH_TE_<group>_<event> definitions.
 *  \param[in] obj		address of the object in memory.
 *  \param[in] obj_name	string terminated in '\\0'.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it.
 */
void rkh_trc_obj(RKH_TE_ID_T tre, rui8_t *obj, const char *obj_name);

/**
 *  \brief
 *  Output signal symbol record.
 *
 *  \param[in] sig		signal number.
 *  \param[in] sig_name	string terminated in '\\0'.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it.
 */
void rkh_trc_sig(RKH_SIG_T sig, const char *sig_name);

/**
 *  \brief
 *  Output active object (AO) symbol record.
 *
 *  \param[in] ao		address of active object symbol.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it.
 */
void rkh_trc_ao(void *ao);

/**
 *  \brief
 *  Output state symbol record.
 *
 *  \param[in] ao		address of active object symbol.
 *  \param[in] state	address of state symbol.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it.
 */
void rkh_trc_state(void *ao, rui8_t *state);

/**
 *  \brief
 *  Store a 8-bit data into the current trace event buffer with format
 *  information.
 *
 *  \param[in] fmt		format information
 *  \param[in] d		data
 */
void rkh_trc_fmt_u8(rui8_t fmt, rui8_t d);

/**
 *  \brief
 *  Store a 16-bit data into the current trace event buffer with format
 *  information.
 *
 *  \param[in] fmt		format information
 *  \param[in] d		data
 */
void rkh_trc_fmt_u16(rui8_t fmt, rui16_t d);

/**
 *  \brief
 *  Store a 32-bit data into the current trace event buffer with format
 *  information.
 *
 *  \param[in] fmt		format information
 *  \param[in] d		data
 */
void rkh_trc_fmt_u32(rui8_t fmt, rui32_t d);

/**
 *  \brief
 *  Store a string terminated in '\\0' into the current trace event buffer
 *  with format information.
 *
 *  \param[in] s		pointer to string terminated in '\\0'
 */
void rkh_trc_fmt_str(const char *s);

/**
 *  \brief
 *  Output memory block of up to 255-bytes with format information.
 *
 *  \param[in] mem		pointer to memory block.
 *  \param[in] size		size of memory block.
 */
void rkh_trc_fmt_mem(rui8_t const *mem, rui8_t size);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
