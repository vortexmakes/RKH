/*
 *	scevt.h
 *	
 *	\brief
 *	Server-Client (SC) event definitions.
 */


#ifndef __SCEVT_H__
#define __SCEVT_H__


#include "rkh.h"


/**
 * 	Signals
 */

typedef enum sc_sigs_t
{
	REQ,		/* client request */
	START,		/* use server */
	DONE,		/* release server  */
	TOUT_REQ,	/* timer expired */
	TOUT_USING,	/* timer expired */
	PAUSE,		/* press the key 'p' on the keyboard */
	TERM		/* press the key escape on the keyboard */
} SC_SIGS_T;


typedef struct
{
	RKH_EVT_T e;		/** base structure */
	rui8_t clino; 		/** client number (ID) */
} REQ_EVT_T;


typedef struct
{
	RKH_EVT_T e;		/** base structure */
	rui8_t clino; 		/** client number (ID) */
} START_EVT_T;


#endif
