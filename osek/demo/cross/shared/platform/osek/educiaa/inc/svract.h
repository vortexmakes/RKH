/*
 *	svract.h
 */


#ifndef __SVRACT_H__
#define __SVRACT_H__


#include "rkh.h"


/*
 *	Defines HSM init function
 */

void svr_init( const struct RKH_SMA_T *sma );


/*
 *	Defines state entry functions
 */

void svr_pause( const struct RKH_SMA_T *sma );


/*
 *	Defines state exit functions
 */

void svr_resume( const struct RKH_SMA_T *sma );


/*
 *	Defines transition action functions
 */

void svr_start( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void svr_end( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void svr_defer( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void svr_terminate( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );


#endif
