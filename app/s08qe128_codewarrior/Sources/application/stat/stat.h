/*
 *	stat.h
 *
 *	RKSYS can optionally collect information on the amount of processing time 
 *	that has been used by each task. The stat task can then be used to present 
 *	this information in a tabular format.
 */


#ifndef __STAT_H__
#define __STAT_H__


#include "mytypes.h"
#include "rksys.h"
#include "task.h"


#if RKSYS_TASK_RUNTIME_STATS

DECLARE_TASK( stat );

#endif

#endif
