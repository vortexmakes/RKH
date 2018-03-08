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
 *  Contact information:
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  --------------------------------------------------------------------------
 *  File                     : rkhcfg.h
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 *
 * 	\brief 		RKH user configuration
 */


#ifndef __RKHCFG_H__
#define __RKHCFG_H__


/**
 * 	Defines standard constants and macros.
 */

#include "rkhdef.h"


/* --- Configuration options related to framework ------------------------- */

/**
 *	Specify the maximum number of state machine applications (SMA) to be used 
 *	by the application (can be a number in the range [1..64]).
 */

#define RKH_CFG_FWK_MAX_SMA				8u

/**
 *	If the dynamic event support (see #RKH_CFG_FWK_DYN_EVT_EN) is set to 
 *	1, RKH allows to use event with parameters, defer/recall, allocating 
 *	and recycling dynamic events, among other features.
 */

#define RKH_CFG_FWK_DYN_EVT_EN			RKH_ENABLED

/**
 *	If the dynamic event support is enabled (see #RKH_CFG_FWK_DYN_EVT_EN) 
 *	then the #RKH_CFG_FWK_MAX_EVT_POOL can be used to specify the maximum 
 *	number of fixed-size memory block pools to be used by the application 
 *	(can be a number in the range [0..256]).
 *	Note that a value of 0 will completely suppress the memory pool services.
 */

#define RKH_CFG_FWK_MAX_EVT_POOL		4u

/**
 * 	Specify the size of the event signal. The valid values [in bits] are 
 * 	8, 16 or 32. Default is 8. The higher the signal size, the higher the 
 * 	event structure size and therefore more memory consumption.
 * 	See #RKH_SIG_T data type.
 */

#define RKH_CFG_FWK_SIZEOF_EVT			8u

/**
 *	Specify the maximum number of event signals to be used by the 
 *	application.
 */

#define RKH_CFG_FWK_MAX_SIGNALS			16u

/**
 * 	Specify the data type of event size. The valid values [in bits] are 
 * 	8, 16 or 32. Default is 8. See #RKH_ES_T, rkh_fwk_epool_register(), and 
 *	RKH_ALLOC_EVT(). Use a 8 value if the bigger event size is minor to 
 *	256 bytes.
 */

#define RKH_CFG_FWK_SIZEOF_EVT_SIZE		16u

/**
 *	If the #RKH_CFG_FWK_DEFER_EVT_EN is set to 1 and the dynamic event 
 *	support is enabled (see #RKH_CFG_FWK_DYN_EVT_EN), RKH enables the 
 *	defer and recall event features.
 */

#define RKH_CFG_FWK_DEFER_EVT_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_FWK_ASSERT_EN is set to 0 the checking assertions are 
 *	disabled.
 * 	In particular macros RKH_ASSERT(), RKH_REQUIRE(), RKH_ENSURE(),
 * 	RKH_INVARIANT(), and RKH_ERROR() do NOT evaluate the test condition
 * 	passed as the argument to these macros. One notable exception is the
 * 	macro RKH_ALLEGE(), that still evaluates the test condition, but does
 * 	not report assertion failures when the #RKH_CFG_FWK_ASSERT_EN is enabled.
 */

#define RKH_CFG_FWK_ASSERT_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_HOOK_DISPATCH_EN is set to 1, RKH will invoke the 
 *	dispatch hook function rkh_hook_dispatch() when dispatching an event to 
 *	a SMA. When this is set the application must provide the hook function. 
 */

#define RKH_CFG_HOOK_DISPATCH_EN		RKH_DISABLED

/**
 *	If the #RKH_CFG_HOOK_SIGNAL_EN is set to 1, RKH will invoke the signal 
 *	hook function rkh_hook_signal() when the producer of an event directly 
 *	posts the event to the event queue of the consumer SMA.
 *	When this is set the application must provide the hook function. 
 */

#define RKH_CFG_HOOK_SIGNAL_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_HOOK_TIMEOUT_EN is set to 1, RKH will invoke the timeout 
 *	hook function rkh_hook_timeout() when a timer expires just before the 
 *	assigned event is directly posted into the state machine application 
 *	queue.
 *	When this is set the application must provide the hook function. 
 */

#define RKH_CFG_HOOK_TIMEOUT_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_HOOK_START_EN is set to 1, RKH will invoke the start 
 *	hook function rkh_hook_start() just before the RKH takes over control of 
 * 	the application.
 *	When this is set the application must provide the hook function. 
 */

#define RKH_CFG_HOOK_START_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_HOOK_EXIT_EN is set to 1, RKH will invoke the exit 
 *	hook function just before it returns to the underlying OS/RTOS. Usually, 
 *	the rkh_hook_exit() is useful when executing clean-up code upon SMA 
 *	terminate or framework exit.
 *	When this is set the application must provide the hook function. 
 */

#define RKH_CFG_HOOK_EXIT_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_HOOK_TIMETICK_EN is set to 1, RKH will invoke the time 
 *	tick hook function from rkh_tmr_tick(), at the very beginning of that, 
 *	to give priority to user or port-specific code when the tick interrupt 
 *	occurs. 
 *	Usually, the rkh_hook_timetick() allows to the application to extend the 
 *	functionality of RKH, giving the port developer the opportunity to add 
 *	code that will be called by rkh_tmr_tick(). Frequently, the 
 *	rkh_hook_timetick() is called from the tick ISR and must not make any 
 *	blocking calls and must execute as quickly as possible.
 *	When this is set the application must provide the hook function. 
 */

#define RKH_CFG_HOOK_TIMETICK_EN		RKH_DISABLED

/**
 *  If the #RKH_CFG_HOOK_PUT_TRCEVT_EN is set to 1, RKH will invoke the
 *  rkh_hook_putTrcEvt() function from rkh_trc_end() function, at the end of
 *  that, to allow to the application to extend the functionality of RKH, 
 *  giving the port developer the opportunity to add code that will be called 
 *  when is put a trace event into the stream buffer.
 *  When this is set the application must provide the hook function.
 */

#define RKH_CFG_HOOK_PUT_TRCEVT_EN        RKH_DISABLED

/**
 * 	Specify the frequency of the framework tick interrupt (number of ticks 
 * 	in one second). It's the rate at which the rkh_tmr_tick() function is 
 * 	invoked. This configuration constant is not used by RKH, it is just a 
 * 	value to allow an application to deal with time when using timer 
 * 	services, converting ticks to time. See RKH_TICK_RATE_MS constant.
 */

#define RKH_CFG_FWK_TICK_RATE_HZ		100u


/* --- Configuration options related to state machine applications -------- */

/**
 *	If the #RKH_CFG_SMA_GET_INFO_EN is set to 1 then RKH will include the 
 *	rkh_clear_info() and rkh_get_info() functions.
 */

#define RKH_CFG_SMA_GET_INFO_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_SMA_PPRO_EN is set to 1 then RKH allows to reference a 
 *	event preprocessor to any basic state. Aditionally, by means of single 
 *	inheritance in C it could be used as state's abstract data. 
 *	Moreover, implementing the single inheritance in C is very simply by 
 *	literally embedding the base type, #RKH_PPRO_T in this case, as the first 
 *	member of the derived structure. See \a prepro member of #RKH_ST_T 
 *	structure for more information.
 */

#define RKH_CFG_SMA_PPRO_EN				RKH_DISABLED

/**
 *	If the #RKH_CFG_SMA_HCAL_EN is set to 1, the RKH allows state nesting. 
 *	When #RKH_CFG_SMA_HCAL_EN is set to 0 some important features of RKH are 
 *	not included: state nesting, composite state, history (shallow and deep) 
 *	pseudostate, entry action, and exit action.
 */

#define RKH_CFG_SMA_HCAL_EN				RKH_ENABLED

/**
 * 	Specify the maximum number of hierarchical levels. The smaller this 
 * 	number, the lower the RAM consumption. Typically, the most of 
 * 	hierarchical state machines uses up to 4 levels. Currently 
 * 	#RKH_CFG_SMA_MAX_HCAL_DEPTH cannot exceed 8.
 */

#define RKH_CFG_SMA_MAX_HCAL_DEPTH		4u

/**
 *	Specify the maximum number of linked transition segments. The smaller 
 *	this number, the lower the RAM consumption. Typically, the most of 
 *	hierarchical state machines uses up to 4 transition segments. 
 *	Currently #RKH_CFG_SMA_MAX_TRC_SEGS cannot exceed 8.
 */

#define RKH_CFG_SMA_MAX_TRC_SEGS		4u

/**
 *	If the #RKH_CFG_SMA_PSEUDOSTATE_EN is set to 1, the RKH allows 
 *	pseudostates usage.
 */

#define RKH_CFG_SMA_PSEUDOSTATE_EN		RKH_DISABLED

/**
 *	If the #RKH_CFG_SMA_DEEP_HIST_EN and #RKH_CFG_SMA_PSEUDOSTATE_EN are 
 *	set to 1, the RKH allows deep history pseudostate usage.
 */

#define RKH_CFG_SMA_DEEP_HIST_EN		RKH_DISABLED

/**
 *	If the #RKH_CFG_SMA_SHALLOW_HIST_EN and #RKH_CFG_SMA_PSEUDOSTATE_EN 
 *	are set to 1, the RKH allows shallow history pseudostate usage.
 */

#define RKH_CFG_SMA_SHALLOW_HIST_EN		RKH_DISABLED

/**
 *	If the #RKH_CFG_SMA_CHOICE_EN and #RKH_CFG_SMA_PSEUDOSTATE_EN are set to 
 *	1, the RKH allows choice pseudostate usage.
 */

#define RKH_CFG_SMA_CHOICE_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_SMA_CONDITIONAL_EN and #RKH_CFG_SMA_PSEUDOSTATE_EN are 
 *	set to 1, the RKH allows branch (or conditional) pseudostate usage.
 */

#define RKH_CFG_SMA_CONDITIONAL_EN		RKH_DISABLED

/**
 *	If the #RKH_CFG_SMA_SUBMACHINE_EN and #RKH_CFG_SMA_PSEUDOSTATE_EN are 
 *	set to 1, the RKH allows submachine state (and exit/entry points) usage.
 */

#define RKH_CFG_SMA_SUBMACHINE_EN		RKH_DISABLED

/**
 *	If the #RKH_CFG_SMA_TRC_SNDR_EN and #RKH_CFG_TRC_EN are set to 1, 
 *	when posting an event the RKH inserts a pointer to the sender object.
 */

#define RKH_CFG_SMA_TRC_SNDR_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_SMA_INIT_EVT_EN is set to 1 then an initial event could 
 *	be be passed to state machine application when it starts, like an 
 *	argc/argv. Also, the #RKH_CFG_SMA_INIT_EVT_EN changes the initial action 
 *	prototype.
 */

#define RKH_CFG_SMA_INIT_EVT_EN			RKH_DISABLED


/* --- Configuration options related to SMA action featues ---------------- */

/**
 *	If the #RKH_CFG_SMA_ENT_ARG_SMA_EN is set to 1 then the entry action 
 *	prototype will add as argument a pointer to state machine structure 
 *	#RKH_SMA_T. See #RKH_ENT_ACT_T definition.
 */

#define RKH_CFG_SMA_ENT_ARG_SMA_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_SMA_ENT_ARG_STATE_EN is set to 1 then the entry action 
 *	prototype will add as argument a pointer to "this" state structure 
 *	#RKH_ST_T. See #RKH_ENT_ACT_T definition.
 */

#define RKH_CFG_SMA_ENT_ARG_STATE_EN	RKH_DISABLED

/**
 *	If the #RKH_CFG_SMA_EXT_ARG_SMA_EN is set to 1 then the exit action 
 *	prototype will add as argument a pointer to state machine structure 
 *	#RKH_SMA_T. See #RKH_EXT_ACT_T definition.
 */

#define RKH_CFG_SMA_EXT_ARG_SMA_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_SMA_EXT_ARG_STATE_EN is set to 1 then the exit action 
 *	prototype will add as argument a pointer to "this" state structure 
 *	#RKH_ST_T. See #RKH_EXT_ACT_T definition.
 */

#define RKH_CFG_SMA_EXT_ARG_STATE_EN	RKH_DISABLED

/**
 *	If the #RKH_CFG_SMA_ACT_ARG_SMA_EN is set to 1 then the transition action 
 *	prototype will add as argument a pointer to state machine structure 
 *	#RKH_SMA_T. See #RKH_TRN_ACT_T definition.
 */

#define RKH_CFG_SMA_ACT_ARG_SMA_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_SMA_ACT_ARG_EVT_EN is set to 1 then the transition action 
 *	prototype will add as argument a pointer to ocurred event. 
 *	See RKH_TRN_ACT_T definition.
 */

#define RKH_CFG_SMA_ACT_ARG_EVT_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_SMA_GRD_ARG_EVT_EN is set to 1 then the transition guard  
 *	prototype will add as argument a pointer to ocurred event. 
 *	See RKH_GUARD_T definition.
 */

#define RKH_CFG_SMA_GRD_ARG_EVT_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_SMA_GRD_ARG_SMA_EN is set to 1 then the transition guard  
 *	prototype will add as argument a pointer to state machine structure 
 *	RKH_SMA_T. See RKH_GUARD_T definition.
 */

#define RKH_CFG_SMA_GRD_ARG_SMA_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_SMA_PPRO_ARG_SMA_EN is set to 1 then the event preprocessor  
 *	(Moore function like entry and exit actions) prototype will add as 
 *	argument a pointer to state machine structure 
 *	RKH_SMA_T. See RKH_PPRO_T definition.
 */

#define RKH_CFG_SMA_PPRO_ARG_SMA_EN		RKH_ENABLED	

/** 
 *  \brief
 *  If RKH_CFG_SMA_SM_CONST_EN is set to RKH_ENABLED then much of the state 
 *  machine object is allocated in ROM. This approach does have as key benefit 
 *  the little RAM consuming as compared when RKH_CFG_SMA_SM_CONST_EN is set 
 *  to RKH_DISABLED.
 *  Nevertheless, the primary drawback of this approach is the obfuscated API 
 *  to use it.
 *  In constrast, if RKH_CFG_SMA_SM_CONST_EN is set to RKH_ENABLED then the 
 *  whole state machine object is allocated in RAM, including its own
 *  constant part. However, the API to use it is very simple, intuitive,
 *  and flexible, allowing easily the dynamic memory allocation
*/
#define RKH_CFG_SMA_SM_CONST_EN         RKH_ENABLED

/** 
 *  \brief
 *  If RKH_CFG_SMA_RT_CTOR_EN is set to RKH_ENABLED then is allowed the use 
 *  of run-time constructors of RKH_SM_T and RKH_SMA_T classes, rkh_sm_ctor() 
 *  and rkh_sma_ctor() respectively.
 *
 *  \type       Boolean
 *  \range      
 *  \default    RKH_DISABLED
 */
#define RKH_CFG_SMA_RT_CTOR_EN          RKH_DISABLED

/** 
 *  \brief
 *  If RKH_CFG_SMA_VFUNCT_EN is set to RKH_ENABLED, the active objects are 
 *  defined as polymorphics, since it incorporates a virtual table of 
 *  functions. See the default virtual table rkhSmaVtbl to known the 
 *  available polymorphic operations. 
 *
 *  \type       Boolean
 *  \range      
 *  \default    RKH_DISABLED
 */
#define RKH_CFG_SMA_VFUNCT_EN           RKH_DISABLED

/* --- Configuration options related to trace facility -------------------- */

/**
 *	If the #RKH_CFG_TRC_EN is set to 1 then RKH will include the trace 
 *	facility.
 */

#define RKH_CFG_TRC_EN					RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_RTFIL_EN is set to 1 then RKH will include 
 *	the runtime trace filter facility.
 * 	When #RKH_CFG_TRC_RTFIL_EN is enabled RKH also will 
 * 	automatically define RKH_FILTER_ON_GROUP(), RKH_FILTER_OFF_GROUP(), 
 * 	RKH_FILTER_ON_EVENT(), RKH_FILTER_OFF_EVENT(), 
 * 	RKH_FILTER_ON_GROUP_ALL_EVENTS(), RKH_FILTER_OFF_GROUP_ALL_EVENTS(), 
 * 	RKH_FILTER_ON_SMA(), and RKH_FILTER_OFF_SMA() macros.
 */

#define RKH_CFG_TRC_RTFIL_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_RTFIL_EN and #RKH_CFG_TRC_RTFIL_SMA_EN are 
 *	set to 1, the RKH allows the usage of runtime trace filter for state 
 *	machine applications (active objects).
 */

#define RKH_CFG_TRC_RTFIL_SMA_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_RTFIL_EN and #RKH_CFG_TRC_RTFIL_SIGNAL_EN 
 *	are set to 1, the RKH allows the usage of runtime trace filter for 
 *	signals (events).
 */

#define RKH_CFG_TRC_RTFIL_SIGNAL_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_USER_TRACE_EN is set to 1 then RKH will allow to 
 *	build and generate tracing information from the application-level code. 
 *	This trace records are application-specific.
 */

#define RKH_CFG_TRC_USER_TRACE_EN		RKH_DISABLED

/**
 *	If the #RKH_CFG_TRC_ALL_EN is set to 1 then RKH will include all its own 
 *	trace records.
 */

#define RKH_CFG_TRC_ALL_EN				RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_MP_EN is set to 1 then RKH will include all trace 
 *	records related to the native fixed-size memory blocks.
 */

#define RKH_CFG_TRC_MP_EN				RKH_DISABLED

/**
 *	If the #RKH_CFG_TRC_QUE_EN is set to 1 then RKH will include all trace 
 *	records related to the native queues.
 */

#define RKH_CFG_TRC_QUE_EN				RKH_DISABLED

/**
 *	If the #RKH_CFG_TRC_SMA_EN is set to 1 then RKH will include all trace 
 *	records related to the state machine applications.
 */

#define RKH_CFG_TRC_SMA_EN				RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_TMR_EN is set to 1 then RKH will include all trace 
 *	records related to the native software timer.
 */

#define RKH_CFG_TRC_TMR_EN				RKH_DISABLED

/**
 *	If the #RKH_CFG_TRC_SM_EN is set to 1 then RKH will include all trace 
 *	records related to the state machine (hierarchical and "flat").
 */

#define RKH_CFG_TRC_SM_EN				RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_FWK_EN is set to 1 then RKH will include all trace 
 *	records related to the nativenative  event framework.
 */

#define RKH_CFG_TRC_FWK_EN				RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_ASSERT_EN and #RKH_CFG_TRC_FWK_EN are set to 1 then 
 *	RKH will include the "assertion" trace record.
 */

#define RKH_CFG_TRC_ASSERT_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_INIT_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "init state machine" trace record.
 */

#define RKH_CFG_TRC_SM_INIT_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_DCH_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "start a state machine" trace record.
 */

#define RKH_CFG_TRC_SM_DCH_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_CLRH_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "dispatch an event to state machine" trace record.
 */

#define RKH_CFG_TRC_SM_CLRH_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_CLRH_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "clear the history pseudostate" trace record.
 */

#define RKH_CFG_TRC_SM_TRN_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_STATE_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "final state of transition" trace record.
 */

#define RKH_CFG_TRC_SM_STATE_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_CLRH_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "entry state" trace record.
 */

#define RKH_CFG_TRC_SM_ENSTATE_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_CLRH_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "exit state" trace record.
 */

#define RKH_CFG_TRC_SM_EXSTATE_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_CLRH_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "number of entry and exit states in transition" 
 *	trace record.
 */

#define RKH_CFG_TRC_SM_NENEX_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_CLRH_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "number of executed actions in transition" trace 
 *	record.
 */

#define RKH_CFG_TRC_SM_NTRNACT_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_CLRH_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "state or pseudostate in a compound transition" 
 *	trace record.
 */

#define RKH_CFG_TRC_SM_TS_STATE_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_CLRH_EN and #RKH_CFG_TRC_SM_EN are set to 1 then 
 *	RKH will include the "returned code from dispatch function" trace record.
 */

#define RKH_CFG_TRC_SM_PROCESS_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_SM_EXE_ACT_EN and #RKH_CFG_TRC_SM_EN are set to 1 
 *	then RKH will include the "executed behavior of state machine" trace 
 *	record.
 */

#define RKH_CFG_TRC_SM_EXE_ACT_EN		RKH_DISABLED

/**
 *	If the #RKH_CFG_TRC_NSEQ_EN is set to 1 then RKH will add to the trace 
 *	record an incremental number (1-byte), used like a sequence number.
 *	See RKH_TRC_NSEQ() and RKH_TRC_HDR() macros.
 */

#define RKH_CFG_TRC_NSEQ_EN				RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_CHK_EN is set to 1 then RKH will add to the trace 
 *	record a checksum (1-byte). See RKH_TRC_CHK() macro.
 */

#define RKH_CFG_TRC_CHK_EN				RKH_ENABLED

/**
 *	If the #RKH_CFG_TRC_TSTAMP_EN is set to 1 then RKH will add to the trace 
 *	record a timestamp field. It's configurable by means of 
 *	#RKH_CFGPORT_TRC_SIZEOF_TSTAMP.
 */

#define RKH_CFG_TRC_TSTAMP_EN			RKH_ENABLED

/**
 *	Specify the maximum number of trace events in the stream. The smaller 
 *	this number, the lower the RAM consumption.
 */

#define RKH_CFG_TRC_SIZEOF_STREAM		512u


/* --- Configuration options related to queue (by reference) facility ----- */

/**
 *	If the #RKH_CFG_QUE_EN is set to 1 then RKH will include the native queue 
 *	facility.
 */

#define RKH_CFG_QUE_EN					RKH_ENABLED

/**
 * 	Specify the maximum number of elements that any queue can contain. 
 * 	The valid values [in bits] are 8, 16 or 32. Default is 8. 
 *	See #RKH_QUENE_T type.
 */

#define RKH_CFG_QUE_SIZEOF_NELEM			8u

/**
 *	If the #RKH_CFG_QUE_GET_LWMARK_EN is set to 1 then RKH allows to known the 
 * 	minimum number of free elements ever in the queue (low-watermark ). 
 * 	This provides valuable empirical data for proper sizing of the queue.
 * 	See rkh_queue_get_lwm() function.
 */

#define RKH_CFG_QUE_GET_LWMARK_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_QUE_GET_INFO_EN is set to 1 then RKH allows to collect and 
 *	retrives performance information for a particular queue.
 *	See rkh_queue_get_info() and rkh_queue_clear_info() functions.
 */

#define RKH_CFG_QUE_GET_INFO_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_QUE_READ_EN is set to 1 then RKH will include the 
 *	rkh_queue_read() function that allows read an element from a queue without 
 *	remove it. See rkh_queue_read() function.
 */

#define	RKH_CFG_QUE_READ_EN				RKH_DISABLED

/**
 *	If the #RKH_CFG_QUE_DEPLETE_EN is set to 1 then RKH will include the 
 *	rkh_queue_deplete() function that empties the contents of the queue and 
 *	eliminates all stored elements.
 *	See rkh_queue_deplete() function.
 */

#define	RKH_CFG_QUE_DEPLETE_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_QUE_IS_FULL_EN is set to 1 then RKH will include the 
 *	rkh_queue_is_full() function that allows to known if a queue is full.
 *	See rkh_queue_is_full() function.
 */

#define	RKH_CFG_QUE_IS_FULL_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_QUE_GET_NELEMS_EN is set to 1 then RKH will include the 
 *	rkh_queue_get_num() function that returns the number of elements currently 
 *	in the queue.
 *	See rkh_queue_get_num() function.
 */

#define	RKH_CFG_QUE_GET_NELEMS_EN		RKH_ENABLED

/**
 *	If the #RKH_CFG_QUE_PUT_LIFO_EN is set to 1 then RKH will include the 
 *	rkh_queue_put_lifo() function that puts an element on a queue in a LIFO 
 *	manner.
 *	See rkh_queue_put_lifo() function.
 */

#define	RKH_CFG_QUE_PUT_LIFO_EN			RKH_ENABLED


/* --- Configuration options related to fixed-sized memory block facility - */

/**
 *	If the #RKH_CFG_MP_EN is set to 1 then RKH will include the native 
 *	fixed-size memory block management.
 */

#define RKH_CFG_MP_EN					RKH_ENABLED

/**
 *	If the #RKH_CFG_MP_EN is set to 1 then RKH will include the native 
 *	fixed-size memory block management.
 */

#define RKH_CFG_MP_REDUCED_EN			RKH_DISABLED

/**
 * 	Specify the size of memory block size. The valid values [in bits] are 
 * 	8, 16 or 32. Default is 8. See #RKH_MPBS_T type.
 */

#define RKH_CFG_MP_SIZEOF_BSIZE			8u

/**
 * 	Specify size of number of memory block size. The valid values [in bits] 
 * 	are 8, 16 or 32. Default is 8. See #RKH_MPNB_T type.
 */

#define RKH_CFG_MP_SIZEOF_NBLOCK		8u

/**
 *	If the #RKH_CFG_MP_GET_BSIZE_EN is set to 1 then RKH will include the 
 *	rkh_memPool_get_bsize() function that returns the size of memory block in 
 *	bytes. See rkh_memPool_get_bsize() function.
 */

#define RKH_CFG_MP_GET_BSIZE_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_MP_GET_NFREE_EN is set to 1 then RKH will include the 
 *	rkh_memPool_get_nfree() function that returns the current number of free 
 *	memory blocks in the pool.
 *	See rkh_memPool_get_nfree() function.
 */

#define RKH_CFG_MP_GET_NFREE_EN			RKH_DISABLED

/**
 *	If the #RKH_CFG_MP_GET_LWM_EN is set to 1 then RKH will include the 
 *	rkh_memPool_get_low_wmark() function that returns the lowest number of free 
 *	blocks ever present in the pool. This number provides valuable empirical 
 *	data for proper sizing of the memory pool.
 *	See rkh_memPool_get_low_wmark() function.
 */

#define RKH_CFG_MP_GET_LWM_EN			RKH_ENABLED

/**
 *	If the #RKH_CFG_MP_GET_INFO_EN is set to 1 then RKH will include the 
 *	rkh_memPool_get_info() function that retrieves performance information for 
 *	a particular memory pool. See rkh_memPool_get_info() function.
 */

#define RKH_CFG_MP_GET_INFO_EN			RKH_DISABLED


/* --- Configuration options related to software timer facility ----------- */

/**
 *	If the #RKH_CFG_QUE_EN is set to 1 then RKH will include the native software 
 *	timer facility.
 */

#define RKH_CFG_TMR_EN					RKH_ENABLED

/**
 * 	Specify the dynamic range of the time delays measured in clock ticks 
 * 	(maximum number of ticks). The valid values [in bits] are 8, 16 or 32. 
 * 	Default is 8.
 */

#define RKH_CFG_TMR_SIZEOF_NTIMER		16u

/**
 *	If the #RKH_CFG_TMR_HOOK_EN is set to 1 then RKH will invoke a hook 
 *	function when a timer expires. When this is set the application must 
 *	provide the hook function. 
 */

#define RKH_CFG_TMR_HOOK_EN				RKH_DISABLED

/** 
 *	If the #RKH_CFG_TMR_GET_INFO_EN is set to 1 then RKH will include the 
 *	rkh_tmr_get_info() function that retrieves performance information for 
 *	a particular software timer. See rkh_tmr_get_info() function.
 */

#define RKH_CFG_TMR_GET_INFO_EN			RKH_DISABLED


#endif
