/*
 *	myact.h
 */


#ifndef __MYACT_H__
#define __MYACT_H__


#include "rkh.h"


/*
 *	Defines HSM init function
 */

void my_init( const struct rkhsma_t *sma );


/*
 *	Defines state entry functions
 */

void set_x_1( const struct rkhsma_t *sma );
void set_x_2( const struct rkhsma_t *sma );
void set_x_3( const struct rkhsma_t *sma );
void set_y_0( const struct rkhsma_t *sma );


/*
 *	Defines state exit functions
 */

void dummy_exit( const struct rkhsma_t *sma );


/*
 *	Defines state preprocessor functions
 */



/*
 *	Defines transition action functions
 */

void set_y_2( const struct rkhsma_t *sma, RKHEVT_T *pe );
void set_y_1( const struct rkhsma_t *sma, RKHEVT_T *pe );
void dummy_act( const struct rkhsma_t *sma, RKHEVT_T *pe );
void show_data( const struct rkhsma_t *sma, RKHEVT_T *pe );


/*
 *	Defines branch's guards
 */

HUInt y1( const struct rkhsma_t *sma, RKHEVT_T *pe );
HUInt y2( const struct rkhsma_t *sma, RKHEVT_T *pe );
HUInt x1( const struct rkhsma_t *sma, RKHEVT_T *pe );
HUInt x2_or_x3( const struct rkhsma_t *sma, RKHEVT_T *pe );


/*
 *	Defines guard functions
 */

HUInt x_equal_1( const struct rkhsma_t *sma, RKHEVT_T *pe );


#endif
