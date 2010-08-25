/*
 * qdata.h
 */


#ifndef __QDATA_H__
#define __QDATA_H__


#include "rksys.h"


/*
 *	When a queue is first created, it is assigned an associated unique 
 *	descriptor. It is defined as number of index on queue structure array.
 *	Therefore, the following defined numbers identifies a particular created
 *	queue and are prefectly linked to queue structure array.
 */

enum
{
#if RKSYS_SIGNAL == 1
	SIGNAL_QUEUE,
#endif
	BUTTON_QUEUE,
	SHELL_QUEUE
};


#endif
