/*
 *	svract.h
 */


#ifndef __SVRACT_H__
#define __SVRACT_H__


#include "rkh.h"


/*
 *	Defines HSM init function
 */

void svr_init( const struct rkhsma_t *sma );


/*
 *	Defines state entry functions
 */

void svr_pause( const struct rkhsma_t *sma );


/*
 *	Defines state exit functions
 */

void svr_resume( const struct rkhsma_t *sma );


/*
 *	Defines transition action functions
 */

void svr_start( const struct rkhsma_t *sma, RKHEVT_T *pe );
void svr_end( const struct rkhsma_t *sma, RKHEVT_T *pe );
void svr_defer( const struct rkhsma_t *sma, RKHEVT_T *pe );
void svr_terminate( const struct rkhsma_t *sma, RKHEVT_T *pe );


#endif
