/*
 *	bkyact.h
 */


#ifndef __BKYACT_H__
#define __BKYACT_H__


#include "rkh.h"


/*
 *	Defines HSM init function
 */

void blinky_init( const struct rkhsma_t *sma );


/*
 *	Defines transition action functions
 */

void blinky_led_on( const struct rkhsma_t *sma, RKHEVT_T *pe );
void blinky_led_off( const struct rkhsma_t *sma, RKHEVT_T *pe );


#endif
