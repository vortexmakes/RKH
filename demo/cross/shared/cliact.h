/*
 *	cliact.h
 */


#ifndef __CLIACT_H__
#define __CLIACT_H__


#include "rkh.h"


/*
 *	Defines HSM init function
 */

void cli_init( const struct RKH_SMA_T *sma );


/*
 *	Defines state entry functions
 */

void cli_delay_req( const struct RKH_SMA_T *sma );
void cli_pause( const struct RKH_SMA_T *sma );


/*
 *	Defines state exit functions
 */

void cli_resume( const struct RKH_SMA_T *sma );


/*
 *	Defines transition action functions
 */

void cli_req( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void cli_start( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void cli_end( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );


#endif
