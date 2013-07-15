/*
 *	cliact.h
 */


#ifndef __CLIACT_H__
#define __CLIACT_H__


#include "rkh.h"


/*
 *	Defines HSM init function
 */

void cli_init( const struct rkhsma_t *sma );


/*
 *	Defines state entry functions
 */

void cli_delay_req( const struct rkhsma_t *sma );
void cli_pause( const struct rkhsma_t *sma );


/*
 *	Defines state exit functions
 */

void cli_resume( const struct rkhsma_t *sma );


/*
 *	Defines transition action functions
 */

void cli_req( const struct rkhsma_t *sma, RKHEVT_T *pe );
void cli_start( const struct rkhsma_t *sma, RKHEVT_T *pe );
void cli_end( const struct rkhsma_t *sma, RKHEVT_T *pe );


#endif
