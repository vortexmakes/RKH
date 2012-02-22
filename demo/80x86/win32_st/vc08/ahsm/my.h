/*
 *	my.h
 */


#ifndef __MY_H__
#define __MY_H__


#include "rkh.h"


typedef struct
{
	RKHEVT_T event;
	rkhuint16 ts;
} MYEVT_T;


typedef struct
{
	rkhuint8 x;
	rkhuint8 y;
} MYHDATA_T;


/*
 *	Declare HSM.
 */

RKH_DCLR_HSM( my );


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
