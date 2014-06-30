/*
 *	myact.h
 */


#ifndef __MYACT_H__
#define __MYACT_H__


#include "rkh.h"


/*
 *	Defines HSM init function
 */

/* ... */

/*
 *	Defines state entry functions
 */

/* ... */


/*
 *	Defines state exit functions
 */

/* ... */


/*
 *	Defines state preprocessor functions
 */

/* ... */


/*
 *	Defines transition action functions
 */

void act1( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act2( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act3( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act4( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act5( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act6( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act7( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act8( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void terminate( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );


/*
 *	Defines branch's guards
 */

/* ... */

/*
 *	Defines guard functions
 */

/* ... */


#endif
