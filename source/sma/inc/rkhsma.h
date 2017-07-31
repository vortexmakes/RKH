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
 *  \file       rkhsma.h
 *  \brief      Specifies the interface of the acive object (SMA state machine 
 *              applications) manager.
 *  \ingroup    apiAO
 *
 *  \addtogroup api
 *  @{
 *  \addtogroup apiAO Active objects
 *  @{@}
 *  @}
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.05  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHSMA_H__
#define __RKHSMA_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhsm.h"
#include "rkhqueue.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#if ((RKH_CFGPORT_NATIVE_EQUEUE_EN == RKH_ENABLED) && \
     (RKH_EN_DOXYGEN == RKH_DISABLED))
    #ifndef RKH_EQ_TYPE
        #define RKH_EQ_TYPE         RKH_QUEUE_T
    #endif
#endif

#define RKH_SMA_NAME(smaName_)      s_##smaName_

/**
 *  \brief
 *  Macro for accessing to state member of state machine structure.
 *
 *  \param[in] me_      Pointer to object of state machine.
 */
#define RKH_SMA_ACCESS_STATE(me_) \
    ((RKH_SM_T *)me_)->state

#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
/**
 *  \brief
 *  Macro for accessing to members of state machine structure.
 *
 *  \param[in] me_      Pointer to object of state machine.
 *  \param[in] member_  Member of state machine structure.
 */
    #define RKH_SMA_ACCESS_CONST(me_, member_) \
        ((RKH_SM_T *)me_)->romrkh->member_
#else
/**
 *  \brief
 *  Macro for accessing to members of state machine structure.
 *
 *  \param[in] me_      Pointer to object of state machine.
 *  \param[in] member_  Member of state machine structure.
 */
    #define RKH_SMA_ACCESS_CONST(me_, member_) \
        ((RKH_SM_T *)me_)->member_
#endif

/**
 *  \brief
 *  This macro declares a opaque pointer to previously created state machine
 *  application (SMA aka active object) to be used as a global object.
 *
 *  This global pointer represent the active object in the application.
 *  These pointers are "opaque" because they cannot access the whole active 
 *  object structure, but only the part inherited from the RKH_SMA_T structure.
 *  The power of an "opaque" pointer is that it allows to completely hide the 
 *  definition of the active object structure and make it inaccessible to the 
 *  rest of the application, thus strengthening the encapsulation concept.
 *
 *  \param[in] me_  pointer to previously created state machine application.
 *
 *	\note
 *  Generally, this macro is used in the SMA's header file.
 *
 *  \sa
 *  RKH_SMA_CREATE().
 *
 *  \usage
 *  \code
 *  //	my.h: state-machine application's header file
 *
 *  RKH_SMA_DCLR(my);
 *  \endcode
 */
#define RKH_SMA_DCLR(me_) \
            RKH_DCLR_PTR_TYPE(RKH_SMA_T, me_)

/**
 *  \brief
 *  This macro declares a typed pointer to previously created state machine
 *  application (SMA aka active object) to be used as a global and public 
 *  object.
 *
 *  \param[in] type_
 *                  Data type of the state machine application. Could be 
 *                  derived from RKH_SMA_T.
 *                  The pointer could be used to publish the internals of the 
 *                  class of the state machine. 
 *  \param[in] me_	pointer to previously created state machine application.
 *
 *	\note
 *  Generally, this macro is used in the SMA's header file.
 *
 *  \sa
 *  RKH_SMA_CREATE(), RKH_SMA_DCLR().
 *
 *  \usage
 *  \code
 *  //	my.h: state-machine application's header file
 *
 *  RKH_SMA_DCLR_TYPE(Blinky, blinky);
 *  \endcode
 */
#define RKH_SMA_DCLR_TYPE(type_, me_) \
            RKH_DCLR_PTR_TYPE(type_, me_)

/**
 *  \brief
 *  Invoke the active object activation function rkh_sma_activate(). 
 *  If RKH_CFG_SMA_VFUNCT_EN is set RKH_ENABLED, this operation is 
 *  polymorphic, where its implementation is defined by the virtual table of 
 *  the active object to activate. 
 *
 *  This macro is the recommended way of invoke the rkh_sma_activate()
 *  function to active an active object, because it allows to
 *  completely hides the platform-specific code.
 *
 *  \param[in] me_	    pointer to previously created state machine
 *                      application.
 *  \param[in] qSto_	base address of the event storage area. A message
 *                      storage area is declared as an array of pointers
 *                      to RKH events.
 *  \param[in] qStoSize size of the storage event area [in number of
 *                      entries].
 *  \param[in] stkSto_	starting address of the stack's memory area.
 *  \param[in] stkSize_ size of stack memory area [in bytes].
 *
 *  \note
 *  In the next releases this macro will be improved, calling a function 
 *  instead of using its own vptr.  
 *
 *	\sa
 *	rkh_sma_activate().
 *
 *  \usage
 *	\code
 *	int
 *	main( int argc, char *argv[] )
 *	{
 *		...
 *		RKH_SMA_ACTIVATE( blinky, qsto, QSTO_SIZE, 0, 0 );
 *		...
 *		return 0;
 *	}
 *	\endcode
 *
 *  \ingroup apiAO
 */
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
#if RKH_CFGPORT_SMA_QSTO_EN == RKH_ENABLED
    #if RKH_CFGPORT_SMA_STK_EN == RKH_ENABLED
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
         ((RKH_SMA_T *)(me_))->vptr->activate(me_, \
                                              (const RKH_EVT_T **)qSto_, \
                                              qStoSize, \
                                              (void *)stkSto_, \
                                              (rui32_t)stkSize_)
    #else
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        ((RKH_SMA_T *)(me_))->vptr->activate(me_, \
                                             (const RKH_EVT_T **)qSto_, \
                                             qStoSize, \
                                             (void *)0, \
                                             (rui32_t)0)
    #endif
#else
    #if RKH_CFGPORT_SMA_STK_EN == RKH_ENABLED
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        ((RKH_SMA_T *)(me_))->vptr->activate(me_, \
                                             (const RKH_EVT_T **)0, \
                                             qStoSize, \
                                             (void *)stkSto_, \
                                             (rui32_t)stkSize_)
    #else
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        ((RKH_SMA_T *)(me_))->vptr->activate(me_, \
                                             (const RKH_EVT_T **)0, \
                                             qStoSize, \
                                             (void *)0, \
                                             (rui32_t)0)
    #endif
#endif
#else
#if RKH_CFGPORT_SMA_QSTO_EN == RKH_ENABLED
    #if RKH_CFGPORT_SMA_STK_EN == RKH_ENABLED
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        rkh_sma_activate(me_, \
                         (const RKH_EVT_T **)qSto_, \
                         qStoSize, \
                         (void *)stkSto_, \
                         (rui32_t)stkSize_)
    #else
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        rkh_sma_activate(me_, \
                         (const RKH_EVT_T **)qSto_, \
                         qStoSize, \
                         (void *)0, \
                         (rui32_t)0)
    #endif
#else
    #if RKH_CFGPORT_SMA_STK_EN == RKH_ENABLED
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        rkh_sma_activate(me_, \
                         (const RKH_EVT_T **)0, \
                         qStoSize, \
                         (void *)stkSto_, \
                         (rui32_t)stkSize_)
    #else
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        rkh_sma_activate(me_, \
                         (const RKH_EVT_T **)0, \
                         qStoSize, \
                         (void *)0, \
                         (rui32_t)0)
    #endif
#endif
#endif

/**
 *  \brief
 *  Declare and allocate a SMA (active object) derived from RKH_SMA_T. Also,
 *  initializes and assigns a state machine to previously declared SMA.
 *
 *  In the UML specification, every state machine has a top state
 *  (the abstract root of every state machine hierarchy), which contains
 *  all the other elements of the entire state machine. RKH provides the
 *  top state using the macro RKH_SMA_CREATE().
 *	Frequently, RKH_SMA_CREATE() is used within state-machine's module
 *	(.c file), thus the structure definition is in fact entirely encapsulated
 *	in its module and is inaccessible to the rest of the application.
 *	However, use RKH_SMA_DEF_PTR() or RKH_SMA_DEF_PTR_TYPE() macros to 
 *	define a opaque pointer or typed pointer to that state machine application 
 *	structure, respectively. Also, use the RKH_SMA_DCLR() macro to declare it 
 *	to be for the rest of application code. 
 *  RKH_SMA_T is not intended to be instantiated directly, but rather
 *  serves as the base structure for derivation of state machines in the
 *  application code.
 *  The following example illustrates how to derive an state machine from
 *  RKH_SMA_T. Please note that the RKH_SMA_T member sm is defined as the
 *  FIRST member of the derived structure.
 *
 *  \param[in] type 	Data type of the SMA. Could be derived from RKH_SMA_T.
 *  \param[in] name		Name of state machine application. Also, it represents 
 *                      the top state of state diagram.
 *  \param[in] prio		State machine application priority. A unique priority
 *                      number must be assigned to each SMA from 0 to
 *                      RKH_LOWEST_PRIO. The lower the number, the higher the
 *                      priority.
 *  \param[in] ppty		State machine properties. The available properties are
 *                      enumerated in RKH_HPPTY_T enumeration in the rkh.h
 *                      file.
 *  \param[in] initialState
 *                      Pointer to initial state. This state could be defined
 *                      either composite or basic (not pseudo-state).
 *  \param[in] initialAction
 *                      Pointer to initialization action (optional). The
 *                      function prototype is defined as RKH_INIT_ACT_T. This
 *                      argument is optional, thus it could be declared as
 *                      NULL.
 *  \param[in] initialEvt
 *                      Pointer to an event that will be passed to state
 *                      machine application when it starts. Could be used to
 *                      pass arguments to the state machine like an argc/argv.
 *                      This argument is optional, thus it could be declared
 *                      as NULL or eliminated in compile-time with
 *                      RKH_CFG_SMA_INIT_EVT_EN = 0.
 *
 *  \sa RKH_SM_CONST_CREATE(), RKH_SM_GET_CONST(), RKH_SM_GET_CONST(),
 *      RKH_SMA_DEF_PTR(), RKH_SMA_DEF_PTR_TYPE()
 *
 *	\usage
 *	\code
 *	...within state-machine application's module
 *
 *	typedef struct
 *	{
 *		RKH_SMA_T ao;	// base structure
 *		rui8_t x;		// private member
 *		rui8_t y;		// private member
 *	} MYSM_T;
 *
 *  //	static instance of SMA object
 *	RKH_SMA_CREATE(MYSM_T, my, 0, HCAL, &S1, my_iaction, &my_ievent);
 *	\endcode
 */
#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SMA_CREATE(type, name, prio, ppty, initialState, \
                           initialAction, initialEvt) \
        RKH_SM_CONST_CREATE(name, prio, ppty, initialState, initialAction, \
                            initialEvt); \
        static type RKH_SMA_NAME(name) = MKSMA(&RKH_SM_CONST_NAME(name), \
                                               initialState)
#else
    #define RKH_SMA_CREATE(type, name, prio, ppty, initialState, \
                           initialAction, initialEvt) \
        static type RKH_SMA_NAME(name) = MKSMA(name, \
                                               prio, \
                                               ppty, \
                                               initialState, \
                                               initialAction, \
                                               initialEvt)
#endif

#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SMA_INIT(me, prio, ppty, initialState, initialAction, \
                         initialEvt)
#else
    #define RKH_SMA_INIT(me, prio, ppty, initialState, initialAction, \
                         initialEvt) \
        MKRT_SM(me, me, prio, ppty, initialState, initialAction, initialEvt)
#endif

#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SMA_GET_OBJ(type, me)
#else
    #define RKH_SMA_GET_OBJ(type, me) \
        (type *)&RKH_SMA_NAME(me)
#endif

/**
 *  \brief
 *  Declare a opaque pointer pointing to an previously created active 
 *  object.
 *
 *  \param[in] me_  Name of state machine application.
 *
 *  \sa RKH_SMA_DCLR()
 */
#define RKH_SMA_DEF_PTR(me_) \
    RKH_SMA_T *const me_ = (RKH_SMA_T *)&RKH_SMA_NAME(me_)

/**
 *  \brief
 *  Declare a pointer of specified type pointing to an previously created 
 *  active object.
 *  
 *  The pointer could be used to hide (opaque) or to publish the internals of 
 *  the class of the active object. 
 *
 *  \param[in] type Data type of the state machine application. Could be 
 *                  derived from RKH_SMA_T.
 *  \param[in] me_  Name of state machine application.
 *
 *  \sa RKH_SMA_DCLR()
 */
#define RKH_SMA_DEF_PTR_TYPE(type, me_) \
    type *const me_ = (type *)&RKH_SMA_NAME(me_)

/**
 *  \brief
 *  Invoke the direct event posting facility rkh_sma_post_fifo().
 *  If RKH_CFG_SMA_VFUNCT_EN is set RKH_ENABLED, this operation is 
 *  polymorphic, where its implementation is defined by the virtual table of 
 *  the target active object. 
 *
 *  This macro is the recommended way of posting events, because it
 *  provides the vital information for software tracing and avoids any
 *  overhead when the tracing is disabled.
 *
 *  \param[in] me_		pointer to previously created state machine
 *                      application.
 *  \param[in] e_		actual event sent to the state machine application.
 *  \param[in] sender_	pointer to the sender object. It is not
 *                      necessarily a pointer to an active object. In
 *                      fact, if RKH_SMA_POST_FIFO() is called from an
 *                      interrupt or other context, it can create a
 *                      unique object just to unambiguously identify the
 *                      publisher of the event.
 *
 *  \note
 *  In the next releases this macro will be improved, calling a function 
 *  instead of using its own vptr.  
 *
 *	\sa
 *	rkh_sma_post_fifo().
 *
 *  \ingroup apiAO
 */
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    #if defined(RKH_USE_TRC_SENDER)
        #define RKH_SMA_POST_FIFO(me_, e_, sender_) \
            ((RKH_SMA_T *)(me_))->vptr->post_fifo((me_), (e_), (sender_))
    #else
        #define RKH_SMA_POST_FIFO(me_, e_, sender_) \
            ((RKH_SMA_T *)(me_))->vptr->post_fifo((me_), (e_))
    #endif
#else
    #if defined(RKH_USE_TRC_SENDER)
        #define RKH_SMA_POST_FIFO(me_, e_, sender_) \
            rkh_sma_post_fifo((me_), (e_), (sender_))
    #else
        #define RKH_SMA_POST_FIFO(me_, e_, sender_) \
            rkh_sma_post_fifo((me_), (e_))
    #endif
#endif

/**
 *  \brief
 *  Invoke the direct event posting facility rkh_sma_post_lifo().
 *  If RKH_CFG_SMA_VFUNCT_EN is set RKH_ENABLED, this operation is 
 *  polymorphic, where its implementation is defined by the virtual table of 
 *  the target active object. 
 *
 *  This macro is the recommended way of posting events, because it
 *  provides the vital information for software tracing and avoids any
 *  overhead when the tracing is disabled.
 *
 *  \param[in] me_	    pointer to previously created state machine
 *                      application.
 *  \param[in] e_		actual event sent to the state machine application.
 *  \param[in] sender_	pointer to the sender object. It is not
 *                      necessarily a pointer to an active object. In
 *                      fact, if RKH_SMA_POST_LIFO() is called from an
 *                      interrupt or other context, it can create a
 *                      unique object just to unambiguously identify the
 *                      publisher of the event.
 *
 *  \note
 *  In the next releases this macro will be improved, calling a function 
 *  instead of using its own vptr.  
 *
 *	\sa
 *	rkh_sma_post_lifo().
 *
 *  \ingroup apiAO
 */
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    #if defined(RKH_USE_TRC_SENDER)
        #define RKH_SMA_POST_LIFO(me_, e_, sender_) \
            ((RKH_SMA_T *)(me_))->vptr->post_lifo((me_), (e_), (sender_))
    #else
        #define RKH_SMA_POST_LIFO(me_, e_, sender_) \
            ((RKH_SMA_T *)(me_))->vptr->post_lifo((me_), (e_))
    #endif
#else
    #if defined(RKH_USE_TRC_SENDER)
        #define RKH_SMA_POST_LIFO(me_, e_, sender_) \
            rkh_sma_post_lifo((me_), (e_), (sender_))
    #else
        #define RKH_SMA_POST_LIFO(me_, e_, sender_) \
            rkh_sma_post_lifo((me_), (e_))
    #endif
#endif

/**
 *  \brief
 *  Declares a opaque pointer to previously created array of state machine
 *  applications SMA (a.k.a Active Object) to be used as a global object.
 *
 *  \param[in] _arr		pointer to previously created array of state machine
 *                      applications. To do that is recommended to use the 
 *                      macro RKH_ARRAY_SMA_CREATE().
 *  \param[in] _num		size of array [in active objects].
 *
 *	\note
 *  Generally, this macro is used in the SMA's header file.
 *
 *  \sa
 *  RKH_SMA_CREATE().
 *
 *  \usage
 *  \code
 *  //	cli.h: state-machine application's header file
 *  #define NUM_CLIENTS			4
 *
 *  typedef struct
 *  {
 *      RKH_SMA_T me;		// base structure
 *      RKH_TMR_T cli_utmr; // usage time
 *      RKH_TMR_T cli_rtmr;	// waiting request time
 *  } CLI_T;				// Active Object derived from RKH_SMA_T structure
 *
 *  RKH_ARRAY_SMA_DCLR( clis, NUM_CLIENTS );
 *  \endcode
 */
#define RKH_ARRAY_SMA_DCLR(_arr, _num) \
    extern RKH_SMA_T * const *_arr[_num]

/**
 *  \brief
 *  Declares a typed pointer to previously created array of state machine
 *  applications SMA (a.k.a Active Object) to be used as a global object.
 *
 *  \param[in] type_	data type of active object.
 *  \param[in] array_	pointer to previously created array of state machine
 *                      applications. To do that is recommended to use the 
 *                      macro RKH_ARRAY_SMA_CREATE_TYPE().
 *  \param[in] num_		size of array [in active objects].
 *
 *	\note
 *  Generally, this macro is used in the SMA's header file.
 *
 *  \sa
 *  RKH_SMA_CREATE().
 *
 *  \usage
 *  \code
 *  //	cli.h: state-machine application's header file
 *  #define NUM_CLIENTS			4
 *
 *  typedef struct
 *  {
 *      RKH_SMA_T me;		// base structure
 *      RKH_TMR_T cli_utmr; // usage time
 *      RKH_TMR_T cli_rtmr;	// waiting request time
 *  } CLI_T;				// Active Object derived from RKH_SMA_T structure
 *
 *  RKH_ARRAY_SMA_DCLR_TYPE(CLI_T, clis, NUM_CLIENTS);
 *  \endcode
 */
#define RKH_ARRAY_SMA_DCLR_TYPE(type_, array_, num_) \
    extern type_ * const * array_[num_]

/**
 *  \brief
 *  Declare and allocate an array of SMAs (a.k.a active objects) derived from
 *  RKH_SMA_T.
 *
 *  \param[in] _arr		name of SMA's array.
 *  \param[in] _num		size of array [in active objects].
 *
 *  \usage
 *  \code
 *	// Defines SMAs (a.k.a Active Objects)
 *
 *	RKH_SMA_CREATE( CLI_T, cli0, 1, HCAL, &cli_idle, cli_init, NULL );
 *	RKH_SMA_CREATE( CLI_T, cli1, 2, HCAL, &cli_idle, cli_init, NULL );
 *	RKH_SMA_CREATE( CLI_T, cli2, 3, HCAL, &cli_idle, cli_init, NULL );
 *	RKH_SMA_CREATE( CLI_T, cli3, 4, HCAL, &cli_idle, cli_init, NULL );
 *
 *	RKH_ARRAY_SMA_CREATE( clis, NUM_CLIENTS )
 *	{
 *		&cli0, &cli1, &cli2, &cli3
 *	};
 *  \endcode
 */
#define RKH_ARRAY_SMA_CREATE(_arr, _num) \
    RKH_SMA_T * const *_arr[_num] =

/**
 *  \brief
 *  Declare and allocate an array of SMAs (a.k.a active objects) derived from
 *  RKH_SMA_T.
 *
 *  \param[in] type_	data type of active object.
 *  \param[in] array_	name of SMA's array.
 *  \param[in] num_		size of array [in active objects].
 *
 *  \usage
 *  \code
 *	// Defines SMAs (a.k.a Active Objects)
 *
 *	RKH_SMA_CREATE(CLI_T, cli0, 1, HCAL, &cli_idle, cli_init, NULL);
 *	RKH_SMA_CREATE(CLI_T, cli1, 2, HCAL, &cli_idle, cli_init, NULL);
 *	RKH_SMA_CREATE(CLI_T, cli2, 3, HCAL, &cli_idle, cli_init, NULL);
 *	RKH_SMA_CREATE(CLI_T, cli3, 4, HCAL, &cli_idle, cli_init, NULL);
 *
 *	RKH_ARRAY_SMA_CREATE(CLI_T, clis, NUM_CLIENTS)
 *	{
 *		&cli0, &cli1, &cli2, &cli3
 *	};
 *  \endcode
 */
#define RKH_ARRAY_SMA_CREATE_TYPE(type_, array_, num_) \
    type_ * const * array_[num_] =

/**
 *  \brief
 *  Retrieves the pointer to active object from a SMA's array.
 *
 *  \param[in] _arr		name of SMA's array.
 *  \param[in] _ix		index (position in the array).
 *
 *  \usage
 *  \code
 *  #define NUM_CLIENTS				4
 *  #define CLI( _clino )			RKH_ARRAY_SMA( clis, _clino )
 *
 *  #define CLI0					CLI(0)
 *  #define CLI1					CLI(1)
 *  #define CLI2					CLI(2)
 *  #define CLI3					CLI(3)
 *
 *  typedef struct
 *  {
 *      RKH_SMA_T me;		// base structure
 *      RKH_TMR_T cli_utmr; // usage time
 *      RKH_TMR_T cli_rtmr;	// waiting request time
 *  } CLI_T;				// Active Object derived from RKH_SMA_T structure
 *
 *  RKH_ARRAY_SMA_DCLR( clis, NUM_CLIENTS );
 *  \endcode
 */
#define RKH_ARRAY_SMA(_arr, _ix)      *_arr[_ix]

#if R_TRC_AO_NAME_EN == RKH_ENABLED
    /**
     *  \brief
     *  This macro retrieves the name of an registered active object.
     *
     *  \param[in] ao		pointer to previously created active object.
     *
     *  \return
     *  Name of active object.
     */
    #define RKH_GET_AO_NAME(ao)       RKH_SMA_ACCESS_CONST(ao, name)
#else
    #define RKH_GET_AO_NAME(ao)       noname
#endif

/**
 *  \brief
 *  Retrieves the address of an registered active object (SMA) according to
 *  its priority.
 *
 *  \param[in] _prio	registered active object (SMA) priority.
 *  \return			    pointer to previously registered active object (SMA).
 */
#define RKH_GET_SMA(_prio) \
    rkh_sptbl[(rui8_t)(_prio)]

/**
 *  \brief
 *  Retrieves the priority number of an registered active object (SMA).
 *
 *  \param[in] _ao		pointer to previously registered active object (SMA).
 */
#define RKH_GET_PRIO(_ao) \
    (rui8_t)(RKH_SMA_ACCESS_CONST(_ao, prio))

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/**
 *  \brief
 *  Defines the data structure into which the collected performance
 *  information for state machine is stored.
 *
 *  This member is optional, thus it could be declared as NULL or eliminated
 *  in compile-time with RKH_EN_SMA_GET_INFO = 0.
 */
typedef struct RKH_SMAI_T
{
    rui16_t ndevt;          /**< # of dispatched events */
    rui16_t exectr;         /**< # of executed transitions */
} RKH_SMAI_T;

/**
 *  \brief
 *  Describes the SMA (active object in UML).
 *
 *	This structure resides in RAM because its members are dinamically updated
 *	by RKH (context of state machine).
 *	The \b RKH_SM_T::romrkh member points to RKH_ROM_T structure, allocated in 
 *	ROM, to reduce the size of RAM consume. The key parameters of a state 
 *	machine are allocated within. Therefore cannot be modified in runtime.
 *
 *  RKH_SMA_T is not intended to be instantiated directly, but rather
 *  serves as the base structure for derivation of active objects in the
 *  application code.
 *  The following example illustrates how to derive an active object from
 *  RKH_SMA_T. Please note that the RKH_SMA_T member ao is defined as the
 *  FIRST member of the derived struct.
 *
 *	Example:
 *	\code
 *	//	...within state-machine's module
 *
 *	typedef struct
 *	{
 *		RKH_SMA_T ao;	// base structure
 *		rui8_t x;		// private member
 *		rui8_t y;		// private member
 *	} MYSM_T;
 *
 *  //	static instance of SMA object
 *	RKH_SMA_CREATE(MYSM_T, my, HCAL, &S1, my_iaction, &my_ievent);
 *	\endcode
 *
 *	\sa
 *	RKH_SMA_T structure definition for more information. Also,
 *	\link RKH_EVT_T single inheritance in C \endlink, and
 *	\link RKH_CREATE_BASIC_STATE another example \endlink.
 *
 *  \ingroup apiAO
 */
struct RKH_SMA_T
{
    /**
     *  \brief
     *  State machine.
     */
    RKH_SM_T sm;

    /**
     *  \brief
     *  Virtual pointer.
     */
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    const RKHSmaVtbl *vptr;
#endif

    /**
     *  \brief
     *  OS-dependent thread of control of the active object.
     *
     *  Frequently, the active object has its own task processing loop that
     *  waits for the signal to be posted, and when it is, loops to remove
     *  and process all events that are currently queued.
     *  The RKH_SMA_POST_FIFO() macro enqueues an event and signals	the OS
     *  that an event has arrived. In this case, \c os_signal holds the OS
     *  object used to signal that an event has been queued.
     *	This data might be used in various ways, depending on the RKH port.
     *  In some ports it's used to store the thread handler.
     *
     *  \note
     *  This member is optional, thus it could be declared as NULL or
     *  eliminated in compile-time with RKH_CFGPORT_SMA_THREAD_EN = 0.
     */
#if RKH_CFGPORT_SMA_THREAD_EN == RKH_ENABLED
    RKH_THREAD_TYPE thread;

    /**
     *  \brief
     *	OS-dependent object used to signal that an event has been queued.
     *
     *  Frequently, the active object has its own task processing loop that
     *  waits for the signal to be posted, and when it is, loops to remove
     *  and process all events that are currently queued.
     *  The RKH_SMA_POST_FIFO() macro enqueues an event and signals	the OS
     *  that an event has arrived. In this case, \c os_signal holds the OS
     *  object used to signal that an event has been queued.
     *  This data might be used in various ways, depending on the RKH port.
     *  In some ports it's used to block the calling thread when the native
     *  RKH queue is empty. In other RKH ports the OS-dependent	data object
     *  might be used differently.
     *
     *  \note
     *  This member is optional, thus it could be eliminated in compile-time
     *  with RKH_CFGPORT_SMA_THREAD_DATA_EN = 0.
     */
#if RKH_CFGPORT_SMA_THREAD_DATA_EN == RKH_ENABLED
    RKH_OSSIGNAL_TYPE os_signal;
#endif
#endif

    /**
     *  \brief
     *  Event queue of the SMA (a.k.a Active Object).
     */
    RKH_EQ_TYPE equeue;

    /**
     *  \brief
     *  The Boolean loop variable determining if the thread routine
     *  of the SMA is running.
     */
    rbool_t running;

    /**
     *  \brief
     *  Performance information. This member is optional, thus it could be
     *  declared as NULL or eliminated in compile-time with
     *  RKH_CFG_SMA_GET_INFO_EN = 0.
     */
#if RKH_CFG_SMA_GET_INFO_EN == RKH_ENABLED
    RKH_SMAI_T sinfo;
#endif
};

/** \copydetails RKHSmaVtbl::activate */
typedef void (*RKHActivate)(RKH_SMA_T *me, 
                         const RKH_EVT_T **qSto, RKH_QUENE_T qSize, 
                         void *stkSto, rui32_t stkSize);

/** \copydetails RKHSmaVtbl::task */
typedef void (*RKHTask)(RKH_SMA_T *me, void *arg);

/** \copydetails RKHSmaVtbl::post_fifo */
#if defined(RKH_USE_TRC_SENDER)
typedef void (*RKHPostFifo)(RKH_SMA_T *me, const RKH_EVT_T *e, 
                         const void *const sender);
#else
typedef void (*RKHPostFifo)(RKH_SMA_T *me, const RKH_EVT_T *e);
#endif

/** \copydetails RKHSmaVtbl::post_lifo */
#if defined(RKH_USE_TRC_SENDER)
typedef void (*RKHPostLifo)(RKH_SMA_T *me, const RKH_EVT_T *e, 
                         const void *const sender);
#else
typedef void (*RKHPostLifo)(RKH_SMA_T *me, const RKH_EVT_T *e);
#endif

/**
 *  \brief
 *  Virtual table for the RKH_SMA_T structure.
 */
struct RKHSmaVtbl
{
    /** Virtual function to activate the active object (thread) */
    /** \sa RKH_SMA_ACTIVATE() */
    RKHActivate activate;

    /** 
     *  \brief
     *  Virtual function to control the execution of the AO (thread task).
     *
     *  Frequently, the active object has its own task processing loop, also 
     *  as known as thread of control, that waits for the signal to be posted,
     *  and when it is, loops to remove and process all events that are 
     *  currently queued.
     */
    RKHTask task;

    /** Virtual function to asynchronously post (FIFO) an event to an AO */
    /** \sa RKH_SMA_POST_FIFO() */
    RKHPostFifo post_fifo;

    /** Virtual function to asynchronously post (LIFO) an event to an AO */
    /** \sa RKH_SMA_POST_LIFO() */
    RKHPostLifo post_lifo;
};

/* -------------------------- External variables --------------------------- */
/** Default virtual table for the RKH_SMA_T structure */
extern const RKHSmaVtbl rkhSmaVtbl;

/**
 *  \brief
 *  Priority arranged table of registered SMA.
 *
 *  Register a state machine application into the framework implies to store
 *  a pointer to the SMA in the priority table. A unique priority number must
 *  be assigned to each SMA from 0 to RKH_LOWEST_PRIO. The lower the number,
 *  the higher the priority.
 */
extern RKH_SMA_T *rkh_sptbl[RKH_CFG_FWK_MAX_SMA];

/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
/**
 *  \brief
 *  Registers a state machine application (SMA) as known as active object into
 *  the framework, which implies to store a pointer to the SMA in the priority
 *  table.
 *
 *  \param[in] me  pointer to previously created state machine application.
 */
void rkh_sma_register(RKH_SMA_T *me);

/**
 *  \brief
 *	Removes the SMA as known as active object from the priority table, and
 *	thus from the framework, by simply replacing the link to the SMA being
 *	deleted with a NULL pointer.
 *
 *  \param[in] me  pointer to previously created state machine application.
 */
void rkh_sma_unregister(RKH_SMA_T *me);

/**
 *  \brief
 *  Initializes the virtual table of the active object instance and calls the 
 *  constructor operation of its base class.
 *
 *  \param[in] me   pointer to previously created state machine application.
 *  \param[in] vtbl pointer to virtual table. Define it as null to use the 
 *                  default virtual table, rkhSmaVtbl.
 *
 *  \note
 *  The initializer assumes that memory has previously been allocated for the 
 *  object (either statically or dynamically).
 */
void rkh_sma_ctor(RKH_SMA_T *me, const RKHSmaVtbl *vtbl);

/**
 *  \brief
 *  Initializes and activates a previously created state machine application
 *  (SMA) as known as active object.
 *
 *  A state machine application (SMA) is declared with the RKH_SMA_T data
 *  type and is defined with the rkh_sma_activate() service.
 *
 *  \param[in] me       pointer to previously created state machine
 *                      application.
 *  \param[in] qSto     base address of the event storage area. A message
 *                      storage area is declared as an array of pointers to
 *                      RKH events.
 *  \param[in] qSize    size of the storage event area [in number of entries].
 *  \param[in] stkSto   starting address of the stack's memory area.
 *  \param[in] stkSize  size of stack memory area [in bytes].
 *
 *	\note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Activates an active object
 *
 *  \ingroup apiPortAO
 */
void rkh_sma_activate(RKH_SMA_T *me, const RKH_EVT_T * *qSto,
                      RKH_QUENE_T qSize, void *stkSto, rui32_t stkSize);

/**
 *  \brief
 *  Terminate a state machine application (SMA) as known as active object.
 *
 *  A state machine application may call this service to terminate itself.
 *  Once terminated, the state machine application must be re-created in
 *  order for it to execute again.
 *
 *  \param[in] me      pointer to previously created state machine
 *                      application.
 *
 *	\note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Terminates an active object
 *
 *  \ingroup apiPortAO
 */
void rkh_sma_terminate(RKH_SMA_T *me);

#if defined(RKH_USE_TRC_SENDER)
/**
 *  \brief
 *  Send an event to a state machine application (SMA) as known as active
 *  object through a queue using the FIFO policy. A message is a pointer
 *  size variable and its use is application specific.
 *
 *  \param[in] me      pointer to previously created state machine
 *                      application.
 *  \param[in] e		actual event sent to the state machine application.
 *  \param[in] sender	pointer to the sender object. It is not necessarily a 
 *                      pointer to an active object. In fact, if 
 *                      RKH_SMA_POST_FIFO() is called from an interrupt or 
 *                      other context, it can create a unique object just to 
 *                      unambiguously identify the publisher of the event.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it. Instead, use RKH_SMA_POST_FIFO() macro.
 *  \note
 *	For memory efficiency and best performance the SMA's event queue,
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *	The assertion inside it guarantee that the pointer is valid, so is not
 *	necessary to check the pointer returned from rkh_sma_post_fifo().
 *	\note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \ingroup apiPortAO
 */
void rkh_sma_post_fifo(RKH_SMA_T *me, const RKH_EVT_T *e,
                       const void *const sender);
#else
void rkh_sma_post_fifo(RKH_SMA_T *me, const RKH_EVT_T *e);
#endif

#if defined(RKH_USE_TRC_SENDER)
/**
 *  \brief
 *  Send an event to a state machine application (SMA) as known as active
 *  object through a queue using the LIFO policy. A message is a pointer
 *  size variable and its use is application specific.
 *
 *  \param[in] me		pointer to previously created state machine 
 *                      application.
 *  \param[in] e		actual event sent to the state machine application.
 *  \param[in] sender	pointer to the sender object. It is not
 *                      necessarily a pointer to an active object. In
 *                      fact, if RKH_SMA_POST_FIFO() is called from an
 *                      interrupt or other context, it can create a
 *                      unique object just to unambiguously identify the
 *                      publisher of the event.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it. Instead, use RKH_SMA_POST_LIFO() macro.
 *  \note
 *	For memory efficiency and best performance the SMA's event queue,
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *	The assertion inside it guarantee that the pointer is valid, so is not
 *	necessary to check the pointer returned from rkh_sma_post_lifo().
 *	\note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \ingroup apiPortAO
 */
void rkh_sma_post_lifo(RKH_SMA_T *me, const RKH_EVT_T *e,
                       const void *const sender);

#else
void rkh_sma_post_lifo(RKH_SMA_T *me, const RKH_EVT_T *e);
#endif

/**
 *  \brief
 *  Get an event from the event queue of an state machine application (SMA)
 *  as known as active object.
 *  The events received are pointer size variables and their use is
 *  application specific.
 *
 *  \param[in] me		pointer to previously created state machine 
 *                      application.
 *
 *	\return     A non-NULL pointer indicates that a event pointer was 
 *	            available, otherwise a NULL pointer.
 *
 *	\note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *	Depending on the underlying OS or kernel, if no event is present at the
 *	queue, the function will block the current thread until an event is
 *	received.
 *
 *  \ingroup apiPortAO
 */
RKH_EVT_T *rkh_sma_get(RKH_SMA_T *me);

/**
 *  \brief
 *	Defer an event to a given separate event queue.
 *
 *  Event deferral comes in very handy when an event arrives in a
 *  particularly inconvenient moment but can be deferred for some later time,
 *  when the system is in a much better position to handle the event. RKH
 *  supports very efficient event deferring and recalling mechanisms.
 *  This function is part of the event deferral mechanism. An SMA
 *  uses this function to defer an event \a e to the event queue \a q.
 *  RKH correctly accounts for another outstanding reference to the event
 *  and will not recycle the event at the end of the RTC step.
 *  Later, the SMA might recall one event at a time from the
 *  event queue by means of rkh_sma_recall() function.
 *
 *  \param[in] q    pointer to previously created queue.
 *  \param[in] e    pointer to event.
 *
 *	\note
 *	For memory efficiency and best performance the deferred event queue,
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *  An SMA can use multiple event queues to defer events of
 *  different kinds.
 *	The assertion inside it guarantee that operation is valid, so is not
 *	necessary to check the value returned from it.
 *
 *  \usage
 *	\code
 *	static RKH_QUEUE_T qurc;
 *	static RKH_EVT_T *qurc_sto[ MAX_SIZEOF_QURC ];
 *
 *	rkh_queue_init( &qurc, qurc_sto, MAX_SIZEOF_QURC, NULL );
 *	...
 *
 *	void
 *	ring( const struct rkh_t *me, RKH_EVT_T *pe )
 *	{
 *		(void)me;                  // argument not used
 *		rkh_sma_defer( &qurc, pe );	// defer event
 *	}
 *	\endcode
 */
void rkh_sma_defer(RKH_QUEUE_T *q, const RKH_EVT_T *e);

/**
 *  \brief
 *  Recall a deferred event from a given event queue.
 *
 *  This function is part of the event deferral support. An SMA
 *  uses this function to recall a deferred event from a given event queue.
 *  Recalling an event means that it is removed from the deferred event
 *  queue \a q and posted (LIFO) to the event queue of the \a me state
 *  machine application.
 *
 *  \note
 *	For memory efficiency and best performance the destination event queue,
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *
 *  \return     The pointer to the recalled event to the caller, or NULL if no
 *              event has been recalled.
 *
 *  \usage
 *	\code
 *	void
 *	exit_rx_manager( const struct rkh_t *me )
 *	{
 *		rkh_sma_recall( me, &qurc );
 *	}
 *	\endcode
 *
 */
RKH_EVT_T *rkh_sma_recall(RKH_SMA_T *me, RKH_QUEUE_T *q);

/**
 *  \brief
 *  Clear performance information for a particular state machine application
 *  (SMA) as known as active object.
 *
 *  \param[in] me  pointer to previously created state machine application.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_SMA_GET_INFO_EN = 0.
 */
void rkh_sma_clear_info(RKH_SMA_T *me);

/**
 *  \brief
 *  Retrieves performance information for a particular state machine
 *  application (SMA) as known as active object.
 *
 *	The user application must allocate an RKH_SMAI_T data structure used to
 *	receive data. The performance information is available during run-time
 *	for each of the RKH services. This can be useful in determining whether
 *	the application is performing properly, as well as helping to optimize the
 *	application.
 *	This information provides a "snapshot" a particular instant in time, i.e.,
 *	when the service is invoked.
 *
 *  \param[in] me  pointer to previously created state machine application.
 *  \param[in] psi  pointer to the buffer into which the performance
 *                  information will be copied by reference.
 *
 *  \note
 *  See RKH_SMAI_T structure for more information. This function is optional, 
 *  thus it could be eliminated in compile-time with 
 *  RKH_CFG_SMA_GET_INFO_EN = 0.
 *
 */
void rkh_sma_get_info(RKH_SMA_T *me, RKH_SMAI_T *psi);

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
