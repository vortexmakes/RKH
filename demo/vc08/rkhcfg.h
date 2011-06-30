/*
 * 	rkhcfg.h
 */


#ifndef __RKHCFG_H__
#define __RKHCFG_H__


#define RKH_EN_HCAL					1	/* 	Enable (1) or Disable (0) state nesting */
#define RKH_MAX_HCAL_DEPTH			4	/* 	Max. number of hierarchical levels */
#define RKH_MAX_TR_SEGS				4	/* 	Max. number of transition segments */
#define RKH_NUM_STATE_MACHINES		1	/*	Number of defined state machines */		
#define RKH_SIZEOF_EVENT			8	/* 	Defines the size of event [in bits]: 8, 16 or 32 */
#define RKH_EN_DYNAMIC_EVENT		0	/*	Enable (1) or Disable (0) dynamic event support. */
#define RKH_EN_DEFERRED_EVENT		1	/* 	Enable (1) or Disable (0) deferred event support. For using this feature the dynamic event support must be set to one. */

#define RKH_EN_PSEUDOSTATE			1	/* 	Enable (1) or Disable (0) pseudostates */
#define RKH_EN_DEEP_HISTORY			1	/* 	Include deep history */
#define RKH_EN_SHALLOW_HISTORY		1	/* 	Include shallow history */
#define RKH_EN_JUNCTION				1	/* 	Include junction */
#define RKH_EN_CONDITIONAL			1	/* 	Include conditional */

#define RKH_EN_INIT_HSM_ARG			1	/* 	Enable (1) or Disable (0) HSM arg */
#define RKH_EN_ENT_HSM_ARG			1	/* 	Enable (1) or Disable (0) HSM arg */
#define RKH_EN_EXT_HSM_ARG			1	/* 	Enable (1) or Disable (0) HSM arg */
#define RKH_EN_ACT_HSM_ARG			1	/* 	Enable (1) or Disable (0) HSM arg */
#define RKH_EN_ACT_EVT_ARG			1	/* 	Enable (1) or Disable (0) event arg */
#define RKH_EN_GRD_EVT_ARG			1	/* 	Enable (1) or Disable (0) event arg */
#define RKH_EN_GRD_HSM_ARG			1	/* 	Enable (1) or Disable (0) HSM arg */
#define RKH_EN_PPRO_HSM_ARG			1	/* 	Enable (1) or Disable (0) HSM arg */

#define RKH_EN_STATE_NAME			1	/* 	Include state name */
#define RKH_EN_HSM_NAME				1	/* 	Include HSM name */
#define RKH_EN_HSM_DATA				1	/*	Include HSM data */
#define RKH_EN_PPRO					0	/* 	Include input preprocessor function */
#define RKH_EN_GET_INFO				0	/* 	Include get information function */
#define RKH_EN_REENTRANT			0	/* 	Enable (1) or Disable (0) HSM re-entrancy */

#define RKH_TRACE					1	/* 	Enable (1) or Disable (0) trace mode */
#define RKH_TRACE_ALL				0	/* 	Include all trace points */

										/* 	Enable (1) or Disable (0) trace points: */
#define RKH_EN_EVENT				1	/*	triggering event */
#define RKH_EN_TRN_SRC				0	/*	transition source state */
#define RKH_EN_TRN_TGT				0	/*	transition target state */
#define RKH_EN_NXT_STATE			1	/*	next state */
#define RKH_EN_INT_TRAN				0	/*	internal transition */
#define RKH_EN_ENTRY				1	/*	entry state */
#define RKH_EN_EXIT					1	/*	exit state */
#define RKH_EN_INIT_HSM				0	/*	initializing state-machine */
#define RKH_EN_SGT					0	/*	target state of transition segment */
#define RKH_EN_RTN_CODE				0	/*	code returned by rkh_engine() function */
#define RKH_EN_NUM_ENEX				0	/*	number of enter and exited states */
#define RKH_EN_NUM_ACTSGT			0	/*	number of transition actions to be executed and number of transition segments */

#define RKH_EN_TIMESTAMP			1	/*	Enable (1) or Disable (0) trace timestamp */
#define RKH_SIZEOF_TIMESTAMP		16	/* 	Defines the size of timestamp [in bits]: 8, 16 or 32 */
#define RKH_MAX_NUM_TRACES			16	/*	Max. number of trace events in the stream */
#define RKH_EN_TRACE_STRING			1	/*	Enable (1) or Disable (0) the string argument of trace event */
#define RKH_MAX_TRACE_STRING_SIZE	4	/*	Defines the size of string argument of trace event */

#define RKH_ASSERT					1	/* 	Enable (1) or Disable (0) assert support. */
#define rkh_assert( event )			printf( "RKHASSERT = [%02d] from %s()", 	\
														event, __FUNCTION__ );	\
									__debugbreak();


#endif
