/*
 *	myact.h
 */


#ifndef __MYACT_H__
#define __MYACT_H__


#include "rkh.h"

RKH_DCLR_COMP_STATE		S1,S3,S11;
RKH_DCLR_BASIC_STATE	S2,S31,S32,S111,S112,S12;
RKH_DCLR_COND_STATE		C1,C2;
RKH_DCLR_CHOICE_STATE	CH;
RKH_DCLR_DHIST_STATE	DH;
RKH_DCLR_SHIST_STATE	H;

typedef struct MYSM_T MYSM_T;
struct MYSM_T
{
    RKH_SMA_T sma;  /* base structure */
    rui8_t x;       /* private member */
    rui8_t y;       /* private member */
};                  /* SMA derived from RKH_SMA_T structure */

/*
 *	Defines HSM init function
 */

void my_init( const struct RKH_SMA_T *me );


/*
 *	Defines state entry functions
 */

void set_x_1( const struct RKH_SMA_T *me );
void set_x_2( const struct RKH_SMA_T *me );
void set_x_3( const struct RKH_SMA_T *me );
void set_y_0( const struct RKH_SMA_T *me );


/*
 *	Defines state exit functions
 */

void dummy_exit( const struct RKH_SMA_T *me );


/*
 *	Defines state preprocessor functions
 */



/*
 *	Defines transition action functions
 */

void set_x1( const struct RKH_SMA_T *me, RKH_EVT_T *pe );
void set_y_2( const struct RKH_SMA_T *me, RKH_EVT_T *pe );
void set_y_1( const struct RKH_SMA_T *me, RKH_EVT_T *pe );
void dummy_act( const struct RKH_SMA_T *me, RKH_EVT_T *pe );
void show_data( const struct RKH_SMA_T *me, RKH_EVT_T *pe );
void terminate( const struct RKH_SMA_T *me, RKH_EVT_T *pe );


/*
 *	Defines branch's guards
 */

rbool_t y_0( const struct RKH_SMA_T *me, RKH_EVT_T *pe );
rbool_t y_1( const struct RKH_SMA_T *me, RKH_EVT_T *pe );
rbool_t y_2( const struct RKH_SMA_T *me, RKH_EVT_T *pe );
rbool_t x1( const struct RKH_SMA_T *me, RKH_EVT_T *pe );
rbool_t x2_or_x3( const struct RKH_SMA_T *me, RKH_EVT_T *pe );


/*
 *	Defines guard functions
 */


#endif
