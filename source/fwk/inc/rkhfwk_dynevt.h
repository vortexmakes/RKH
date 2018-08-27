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
 *  \file       rkhfwk_dynevt.h
 *  \brief      Specifies the interface of dynamic event support
 *  \ingroup    fwk
 *  \ingroup    apiEvt
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.04  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHFWK_DYNEVT_H__
#define __RKHFWK_DYNEVT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhitl.h"
#include "rkhfwk_evtpool.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *  \brief
 *	This macro dynamically creates a new event of type \a et with its
 *	signal.
 *
 *	The basic policy is to allocate the event from the first pool that
 *	has a block size big enough to fit the requested event size. RKH
 *	can manage up to three event pools (e.g., small, medium, and large
 *	events, like shirt sizes). It returns a pointer to the event
 *	already cast to the event type (et*). 
 *
 *  \param[in] et		type of event
 *  \param[in] e		event signal
 *  \param[in] sender_	pointer to the actor that request a memory block. It 
 *                      is not necessarily a pointer to an active object. In 
 *                      fact, if RKH_ALLOC_EVT() is called from an interrupt or 
 *                      other context, it can create a unique object just to 
 *                      unambiguously identify the publisher of the event.
 *
 *  \note
 *	The assertions inside rkh_fwk_ae() function guarantee that the
 *	pointer is valid, so you don't need to check the pointer returned
 *	from rkh_fwk_ae(), unlike the value returned from malloc(), which
 *	you should check.
 *
 *  \usage
 *	Here is an example of dynamic event allocation with the macro 
 *	RKH_ALLOC_EVT():
 *
 *	\code
 *	MYEVT_T *mye = RKH_ALLOC_EVT(MYEVT_T, DATA, me);
 *	mye->y = mye->x = 0;
 *	...
 *	\endcode
 *
 *  \ingroup apiEvt
 */
#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
    #define RKH_ALLOC_EVT(et, e, sender_) \
        (et *)rkh_fwk_ae((RKH_ES_T)sizeof(et),(RKH_SIG_T)(e), sender_)
#else
    #define RKH_ALLOC_EVT(et, e, sender_) \
        (void)0
#endif

/**
 *  \brief
 *  Recycle a dynamic event.
 *
 *  This macro implements a simple garbage collector for the dynamic
 *  events.	Only dynamic events are candidates for recycling.
 *  (A dynamic event is one that is allocated from an event pool, which
 *  is determined as non-zero	e->nref attribute.) Next, the function
 *  decrements the reference counter of the event, and recycles the
 *  event only if the counter drops to zero (meaning that no more
 *  references are outstanding for this event). The dynamic event is
 *  recycled by returning it to the pool from which	it was originally
 *  allocated. The pool-of-origin information is stored in the
 *  e->pool member.
 *
 *  \param[in] e		pointer to event to be potentially recycled.
 *  \param[in] sender_  Pointer to the actor that request a memory block. 
 *                      It is not necessarily a pointer to an active 
 *                      object. In fact, if RKH_FWK_GC() is called from 
 *                      an interrupt or other context, it can create a 
 *                      unique object just to unambiguously identify the 
 *                      publisher of the event.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it. Instead, use #RKH_FWK_GC() macro.
 *  \note
 *  The garbage collector must be explicitly invoked at all appropriate
 *  contexts, when an event can become garbage (automatic garbage
 *  collection).
 *  \note
 *  When setting RKH_CFG_FWK_DYN_EVT_EN = 0 the garbage collector has
 *  not effect, thus it's eliminated in compile-time.
 *
 *  \ingroup apiEvt
 */
#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
    #define RKH_FWK_GC(e, sender_)      rkh_fwk_gc(e, sender_)
#else
    #define RKH_FWK_GC(e, sender_)      (void)0
#endif

/**
 *  \brief
 *  Reserve the dynamic event to be recycled.
 *
 *  This is the complement to RKH_FWK_GC(). It increments the reference
 *  count of a dynamic event so the event can be saved by an SMA (AO).
 *  Sometime later the SMA should manually release the event with
 *  RKH_FWK_GC().
 *
 *  \param[in] e		pointer to event to be reserved.
 *
 *  \ingroup apiEvt
 */
#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
    #define RKH_FWK_RSV(e)            rkh_fwk_reserve(e)
#else
    #define RKH_FWK_RSV(e)            (void)0
#endif

/**
 *  \brief
 *	This macro initialize an event \a e with \a es signal and establishes
 *	it as one static event.
 *
 *  \param[in] ev_obj	name of event structure (object).
 *  \param[in] ev_sig	event signal. The RKH takes this value for triggering
 *                      a state transition.
 *
 *	\sa RKH_ROM_STATIC_EVENT() and RKH_STATIC_EVENT() macros.
 *
 *	\usage
 *	\code
 *	typedef struct
 *	{
 *		RKH_EVT_T e;
 *		rui8_t cmd;
 *	} RPC_REQ_T;
 *
 *	typedef struct
 *	{
 *		RPC_REQ_T e;
 *		rkhui8_t txtsz;
 *		EADR_T dst;
 *		EADR_T sc;
 *		char txt[ PDU_SIZEOF_UD_ASCII ];
 *	} REQ_SEND_SMS_T;
 *
 *	...
 *	static REQ_SEND_SMS_T ev_txsm;
 *
 *	...
 *  some_function( ... )
 *  {
 *      RKH_SET_STATIC_EVENT( &ev_txsm, REQ_SEND_SMS );
 *      ev_txsm.e.cmd = RPC_SEND_SMS;
 *		...
 *	}
 *	\endcode
 *
 *  \ingroup apiEvt
 */
#define RKH_SET_STATIC_EVENT(ev_obj, ev_sig) \
    MK_SET_EVT(ev_obj, ev_sig)

/**
 *  \brief
 *	This macro declares and initializes the event structure \a ev_ob with
 *	\a ev_sig signal number and establishes it as one static event.
 *
 *  \param[in] ev_obj	name of event structure (object).
 *  \param[in] ev_sig	event signal. The RKH takes this value for triggering
 *                      a state transition.
 *
 *	\sa RKH_SET_STATIC_EVENT() and RKH_ROM_STATIC_EVENT() macros.
 *
 *	\usage
 *	\code
 *	...
 *	static RKH_STATIC_EVENT( ev_udrej, UPG_DIC_REJ );
 *
 *	void
 *	dm_upgdic_rej( ... )
 *	{
 *		...
 *		rkh_put_fifo( drpc, &ev_udrej );
 *	}
 *	\endcode
 *
 *  \ingroup apiEvt
 */
#define RKH_STATIC_EVENT(ev_obj, ev_sig) \
    MK_EVT(ev_obj, ev_sig)

/**
 *  \brief
 *	This macro declares and initializes the event structure \a ev_ob with
 *	\a ev_sig signal number and establishes it as one static event.
 *
 *  \param[in] ev_obj	name of event structure (object).
 *  \param[in] ev_sig	event signal. The RKH takes this value for triggering
 *                      a state transition.
 *
 *	\sa RKH_SET_STATIC_EVENT() and RKH_STATIC_EVENT() macros.
 *
 *	\warning
 *	The created event object is explicitly placed at ROM.
 *
 *	\usage
 *	\code
 *	...
 *	static RKH_ROM_STATIC_EVENT( ev_timer, RPC_TIMER_RET );
 *
 *	void
 *	offhook( void )
 *	{
 *		...
 *		rkh_put_fifo( qphone, &ev_timer );
 *	}
 *	\endcode
 *
 *  \ingroup apiEvt
 */
#define RKH_ROM_STATIC_EVENT(ev_obj, ev_sig) \
    MK_ROM_EVT(ev_obj, ev_sig)

/**
 *  \brief
 *	Initializes the attibutes of a RKH's event object structure.
 *
 *	\usage
 *	\code
 *	typedef struct
 *	{
 *		RKH_EVT_T e;
 *		rui8_t cmd;
 *	} RPC_REQ_T;
 *
 *  ...
 *	static RKHROM RPC_REQ_T ev_ssreq =
 *	{
 *		RKH_INIT_STATIC_EVT( REQ_SEND_SMS_REQ ),
 *		RPC_SEND_SMS_REQ
 *	};
 *
 *  ...
 *  void
 *  some_function(void)
 *  {
 *      RKH_SMA_POST_FIFO(drpc, RKH_EVT_CAST(&ev_ssreq), 0);
 *      ...
 *  }
 *	\endcode
 *
 *  \ingroup apiEvt
 */
#define RKH_INIT_STATIC_EVT(ev_sig) \
    MK_EVT_STRUCT(ev_sig)

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Initializes the dynamic event manager.
 *
 *  \ingroup apiEvt
 */
void rkh_dynEvt_init(void);

/**
 *  \brief
 *  Registers a new event pool into the event pool list.
 *
 *  Before using dynamic events (or event with arguments) the application
 *  code must register the event pools, which stores the events as a
 *  fixed-sized memory block. Each event pool must be registered with the
 *  RKH framework, by means of the rkh_fwk_registerEvtPool() function.
 *
 *	This function initializes one event pool at a time and must be called
 *  exactly once for each event pool before the pool can be used.
 *
 *  The application code might initialize the event pools by making calls
 *  to the rkh_fwk_registerEvtPool() function. However, for the simplicity of
 *  the internal implementation, the application code initialize event pools
 *  in the ascending order of the event size.
 *
 *  Many RTOSes provide fixed block-size heaps, a.k.a. memory pools that can
 *  be adapted for RKH event pools. In case such support is missing, RKH
 *  provides a native RKH event pool manager implementation. See 
 *  rkhfwk_evtpool.c.
 *
 *  For adapting RKH event pools to any fixed-size memory block service RTOS
 *  provided the application code must provides the implementation of the 
 *  rkhfwk_etpoo.h interface.
 *
 *  The dynamic allocation of events is optional then if the
 *  #RKH_CFGPORT_NATIVE_DYN_EVT_EN is set to 1 and the native fixed-size
 *  memory block facility is enabled (see #RKH_CFG_MP_EN) then RKH will
 *  include its own implementation of dynamic memory management.
 *  When #RKH_CFGPORT_NATIVE_DYN_EVT_EN is enabled RKH also will provide the 
 *  event pool manager implementation based on its native memory pool module.
 *
 *  \param[in] sstart   storage start. Pointer to memory from which memory 
 *                      blocks are allocated.
 *  \param[in] ssize:	storage size. Size of the memory pool storage in bytes.
 *  \param[in] esize	event size. This number determines the size of each 
 *                      memory block in the pool.
 *
 *  \usage
 *	\code
 *	#define SIZEOF_EP0STO				64
 *	#define SIZEOF_EP0_BLOCK			sizeof( TOUT_T )
 *
 *	#define SIZEOF_EP1STO				32
 *	#define SIZEOF_EP1_BLOCK			sizeof( DIAL_T )
 *
 *	#define SIZEOF_EP2STO				32
 *	#define SIZEOF_EP2_BLOCK			sizeof( SETUP_T )
 *
 *	typedef struct
 *	{
 *		RKH_EVT_T evt;                  // base structure
 *		int timerno;					// parameter 'timerno'
 *	} TOUT_T;
 *
 *	typedef struct
 *	{
 *		RKH_EVT_T evt;                  // base structure
 *		char dial[ MAX_SIZE_DIAL ];     // parameter 'dial'
 *		int qty;                        // parameter 'qty'
 *	} DIAL_T;
 *
 *	typedef struct
 *	{
 *		RKH_EVT_T evt;                  // base structure
 *		int volume;                     // parameter 'volume'
 *		int baud_rate;                  // parameter 'baud_rate'
 *		char name[ MAX_SIZE_NAME ];     // parameter 'name'
 *		int iloop;                      // parameter 'iloop'
 *	} SETUP_T;
 *
 *	// declares the storage memory of event pool
 *	static rui8_t	ep0sto[ SIZEOF_EP0STO ],
 *					ep1sto[ SIZEOF_EP1STO ],
 *					ep2sto[ SIZEOF_EP2STO ];
 *  ...
 *  rkh_fwk_registerEvtPool( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
 *  rkh_fwk_registerEvtPool( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
 *  rkh_fwk_registerEvtPool( ep2sto, SIZEOF_EP2STO, SIZEOF_EP2_BLOCK  );
 *  ...
 *	\endcode
 *
 *  \ingroup apiEvt
 */
void rkh_fwk_registerEvtPool(void *sstart, rui32_t ssize, RKH_ES_T esize);

/**
 *  \brief
 *  Allocates an event from the previously created event pool.
 *
 *  \param[in] esize    size of event [in bytes].
 *  \param[in] e        event signal.
 *  \param[in] sender	pointer to the actor that request a memory block. It 
 *                      is not necessarily a pointer to an active object. In 
 *                      fact, if RKH_ALLOC_EVT() is called from an interrupt or 
 *                      other context, it can create a unique object just to 
 *                      unambiguously identify the publisher of the event.
 *
 *  \note
 *  This function is internal to RKH and the user application should not call 
 *  it. Instead, use #RKH_ALLOC_EVT() macro.
 *
 *  \sa rkh_put_fifo(), rkh_put_lifo(), rkh_alloc_event(),
 *  rkh_set_static_event() and rkh_fwk_gc().
 *
 *  \ingroup apiEvt
 */
RKH_EVT_T *rkh_fwk_ae(RKH_ES_T esize, RKH_SIG_T e, const void *const sender);

/**
 *  \brief
 *  Recycle a dynamic event.
 *
 *  \param[in] e        Event signal.
 *  \param[in] sender   Pointer to the actor that request a memory block. 
 *                      It is not necessarily a pointer to an active 
 *                      object. In fact, if RKH_FWK_GC() is called from 
 *                      an interrupt or other context, it can create a 
 *                      unique object just to unambiguously identify the 
 *                      publisher of the event.
 *
 *  \ingroup apiEvt
 */
void rkh_fwk_gc(RKH_EVT_T *e, const void *const sender);

/**
 *  \brief
 *  Reserve the dynamic event to be recycled.
 *
 *  \param[in] e    event signal.
 *
 *  \ingroup apiEvt
 */
void rkh_fwk_reserve(RKH_EVT_T *e);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
