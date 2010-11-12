/*
 *	myact.h
 */


#ifndef __MYACT_H__
#define __MYACT_H__


#include "rkhsm.h"


/*
 *	Defines HSM init function
 */

void my_init( const struct rkh_t *ph );


/*
 *	Defines state entry functions
 */

void set_x_1( const struct rkh_t *ph );
void set_x_2( const struct rkh_t *ph );
void set_x_3( const struct rkh_t *ph );
void set_y_0( const struct rkh_t *ph );


/*
 *	Defines state exit functions
 */

void dummy_exit( const struct rkh_t *ph );


/*
 *	Defines state preprocessor functions
 */



/*
 *	Defines transition action functions
 */

void set_y_2( const struct rkh_t *ph, RKHEVT_T *pe );
void set_y_1( const struct rkh_t *ph, RKHEVT_T *pe );
void dummy_act( const struct rkh_t *ph, RKHEVT_T *pe );


/*
 *	Defines branch functions
 */

RKHE_T get_y( const struct rkh_t *ph, RKHEVT_T *pe );
RKHE_T get_x( const struct rkh_t *ph, RKHEVT_T *pe );


/*
 *	Defines guard functions
 */

HUInt x_equal_1( const struct rkh_t *ph, RKHEVT_T *pe );


#endif
