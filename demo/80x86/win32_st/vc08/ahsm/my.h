/*
 *	my.h
 */


#ifndef __MY_H__
#define __MY_H__


#include "rkh.h"


typedef struct
{
	RKHEVT_T event;
	rkhui16_t ts;
} MYEVT_T;


typedef struct
{
	RKHSMA_T sma;	/* base structure */
	rkhui8_t x;		/* private member */
	rkhui8_t y;		/* private member */
} MYSM_T;			/* SMA derived from RKHSMA_T structure */


/*
 *	Declare HSM.
 */

RKH_SMA_DCLR( my );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_COMP_STATE		S1,S3,S11;
RKH_DCLR_BASIC_STATE	S2,S31,S32,S111,S112,S12;
RKH_DCLR_COND_STATE		C1,C2;
RKH_DCLR_JUNC_STATE		J;
RKH_DCLR_DHIST_STATE	DH;
RKH_DCLR_SHIST_STATE	H;


#endif
