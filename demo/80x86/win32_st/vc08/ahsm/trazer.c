/*
 *	file: trazer.c
 *	Last updated for version: 2.0
 *	Date of the last update:  Mar 19, 2012
 *
 * 	Copyright (C) 2010 Leandro Francucci. All rights reserved.
 *
 * 	RKH is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 *  RKH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RKH, see copying.txt file.
 *
 * Contact information:
 * RKH web site:	http://
 * e-mail:			francuccilea@gmail.com
 */


#include "rkhtrc.h"
#include "rkh.h"
#include "rkhcfg.h"
#include "my.h"
#include <stdio.h>


RKH_THIS_MODULE


#define TRAZER_SIZEOF_SIG			RKH_SIZEOF_EVENT
#define TRAZER_SIZEOF_TSTAMP		RKH_TRC_SIZEOF_TSTAMP
#define TRAZER_SIZEOF_POINTER		RKH_TRC_SIZEOF_POINTER


#define MKTR( id, nm, fmt, fargs )	\
					{ id, nm, fmt, fargs }


typedef char *(*HDLR_T)( const struct tre_t *tre );

typedef struct tre_t
{
	unsigned char id;
	const char *name;
	const char *fmt;
	HDLR_T fmt_args;
} TRE_T;


typedef struct symobj_t
{
	unsigned long adr;
	const char *name;
} SYMOBJ_T;


typedef struct symsig_t
{
	unsigned char sig;
	const char *name;
} SYMSIG_T;


static char *h_none( const struct tre_t *tre );
static char *h_mpinit( const struct tre_t *tre );


static const TRE_T traces[] =
{
	/* --- Memory Pool (MP) ------------------ */
	MKTR(	RKH_TRCE_MP_INIT,	"MP_INIT", 
			"mp=%s, nblock=%02d",	h_mpinit ),
	MKTR(	 RKH_TRCE_MP_GET, 	"MP_GET", 
			"mp=%s, nfree=%02d", 	h_none ),
	MKTR( 	RKH_TRCE_MP_PUT, 	"MP_PUT", 
			"mp=%s, nfree=%02d", 	h_none ),
	
	/* --- Queue (RQ) ------------------------ */
	MKTR( 	RKH_TRCE_RQ_INIT,	"RQ_INIT", 
			"rq=%s, nelem=%02d, sma=%s", h_none ),
	MKTR( 	RKH_TRCE_RQ_GET, 	"RQ_GET", 
			"rq=%s, nused=%02d", h_none ),
	MKTR( 	RKH_TRCE_RQ_FIFO,	"RQ_FIFO", 
			"rq=%s, nused=%02d", h_none ),
	MKTR( 	RKH_TRCE_RQ_LIFO,	"RQ_LIFO", 
			"rq=%s, nused=%02d", h_none ),
	MKTR( 	RKH_TRCE_RQ_FULL,	"RQ_FULL", 
			"rq=%s", h_none ),
	MKTR( 	RKH_TRCE_RQ_DPT,	"RQ_DPT", 
			"rq=%s", h_none ),

	/* --- State Machine Application (SMA) --- */
	MKTR( 	RKH_TRCE_SMA_ACT,	"SMA_ACT", 
			"sma=%s", h_none ),
	MKTR( 	RKH_TRCE_SMA_TERM,	"SMA_TERM", 
			"sma=%s", h_none ),
	MKTR( 	RKH_TRCE_SMA_GET,	"SMA_GET", 
			"sma=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_SMA_FIFO,	"SMA_FIFO", 
			"sma=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_SMA_LIFO,	"SMA_LIFO", 
			"sma=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_SMA_REG,	"SMA_REG", 
			"sma=%s, prio=%02d", h_none ),
	MKTR( 	RKH_TRCE_SMA_UNREG,	"SMA_UNREG", 
			"sma=%s, prio=%02d", h_none ),

	/* --- State machine (SM) ---------------- */
	MKTR( 	RKH_TRCE_SM_INIT,	"SM_INIT", 
			"sma=%s, istate=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_CLRH,	"SM_CLRH", 
			"sma=%s, hist=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_DCH,	"SM_DCH", 
			"sma=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_TRN,	"SM_TRN", 
			"sma=%s, sstate=%s, tstate=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_STATE,	"SM_STATE", 
			"sma=%s, state=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_ENSTATE,"SM_ENSTATE", 
			"sma=%s, state=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_EXSTATE,"SM_EXSTATE", 
			"sma=%s, state=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_NENEX,	"SM_NENEX", 
			"sma=%s, nenex=%02d", h_none ),
	MKTR( 	RKH_TRCE_SM_NTRNACT,"SM_NTRNACT", 
			"sma=%s, ntrnact=%02d", h_none ),
	MKTR( 	RKH_TRCE_SM_CSTATE,	"SM_CSTATE", 
			"sma=%s, state=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_DCH_RC,	"SM_DCH_RC", 
			"sma=%s, rcode=%02d", h_none ),

	/* --- Timer (TIM) ----------------------- */
	MKTR( 	RKH_TRCE_TIM_INIT,	"TIM_INIT", 
			"timer=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_TIM_START,	"TIM_START", 
			"timer=%s, ntick=%05d, sma=%s", h_none ),
	MKTR( 	RKH_TRCE_TIM_RESTART,"TIM_RESTART", 
			"timer=%s, ntick=%05d", h_none ),
	MKTR( 	RKH_TRCE_TIM_STOP,	"TIM_STOP", 
			"timer=%s", h_none ),

	/* --- Framework (RKH) ------------------- */
	MKTR( 	RKH_TRCE_FWK_INIT,	"FWK_INIT", 
			"", h_none ),
	MKTR( 	RKH_TRCE_FWK_EN,	"FWK_EN", 
			"", h_none ),
	MKTR( 	RKH_TRCE_FWK_EX,	"FWK_EX", 
			"", h_none ),
	MKTR( 	RKH_TRCE_FWK_EPREG,	"FWK_EPREG", 
			"ssize=%05d, esize=%05d", h_none ),
	MKTR( 	RKH_TRCE_FWK_AE,	"FWK_AE", 
			"esize=%05d, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_FWK_GC,	"FWK_GC", 
			"sig=%s", h_none ),
	MKTR( 	RKH_TRCE_FWK_GCR,	"FWK_GCR", 
			"sig=%s", h_none ),
	MKTR( 	RKH_TRCE_FWK_DEFER,	"FWK_DEFER", 
			"rq=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_FWK_RCALL,	"FWK_RCALL", 
			"sma=%s, sig=%s", h_none )
};


static const SYMOBJ_T objtbl[] =			/* object symbol table */
{
	{ (unsigned long)&my, "my" },
	{ 0, (const char*)0 }					/* end of table */
};


static const SYMSIG_T sigtbl[] = 			/* signal symbol table */
{
	{ 0, ( const char* )0 },				/* end of table */
};


static const char *rctbl[] =				/* dispatch retcode table */
{
	"RKH_OK",
	"RKH_INPUT_NOT_FOUND",
	"RKH_CONDITION_NOT_FOUND",
	"RKH_GUARD_FALSE",
	"RKH_UNKNOWN_STATE",
	"RKH_EXCEED_HCAL_LEVEL",
	"RKH_EXCEED_TRC_SEGS"
};


#if TRAZER_SIZEOF_TSTAMP == 16
	static const char *trheader = "%05d %s : ";
#else
	static const char *trheader = "%010d %s : ";
#endif

static rkhui8_t *trb;						/* points to trace event buffer */
static char fmt[ 128 ];
extern FILE *fdbg;


static
const char *
map_obj( unsigned long adr )
{
	const SYMOBJ_T *p;

	for( p = objtbl; p->name != 0; ++p )
		if( p->adr == adr )
			return p->name;
	return ( const char* )0;
}


static
const char *
map_sig( unsigned char sig )
{
	const SYMSIG_T *p;

	for( p = sigtbl; p->name != 0; ++p )
		if( p->sig == sig )
			return p->name;
	return ( const char* )0;
}


static
const
TRE_T *
find_trevt( unsigned char id )
{
	const TRE_T *p;

	for( p = traces; p < traces + RKH_TRCE_USER; ++p )
		if( p->id == id )
			return p;

	return ( TRE_T* )0;
}


static
unsigned long
assemble( int size )
{
	int n, sh;
	unsigned long d;

	for( d = 0, n = size, sh = 0; n; --n, sh += 8  )
		d |= ( unsigned long )( *trb++ << sh );
	return d;
}


char *
h_none( const struct tre_t *tre )
{
	*fmt = ' ';
	return fmt;
}


char *
h_mpinit( const struct tre_t *tre )
{
	unsigned long mpobj;
	unsigned short nblock;

	mpobj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	nblock = (unsigned short)assemble( sizeof( short ) );
	sprintf( fmt, tre->fmt, map_obj( mpobj ), nblock );
	return fmt;
}


void 
trazer_parse( rkhui8_t *tre )
{
	const TRE_T *ftr;			/* received trace event */
	RKHTS_T ts;

	if( ( ftr = find_trevt( tre[ 0 ] ) ) != ( TRE_T* )0 )
	{
		if( ftr->fmt_args != ( HDLR_T )0 )
		{
			trb = tre + 1;		/* from timestamp field */
			ts = ( RKHTS_T )assemble( TRAZER_SIZEOF_TSTAMP/8 );
			printf( trheader, ts, ftr->name );
			fprintf( fdbg, trheader, ts, ftr->name );
			printf( "%s\n", (*ftr->fmt_args)( ftr ) );
			fprintf( fdbg, "%s\n", (*ftr->fmt_args)( ftr ) );
		}
		return;
	}
	
	printf( "Unknown trace event - %s (%02d)\n", 	ftr->name, 
													ftr - traces );
	fprintf( fdbg, "Unknown trace event - %s (%02d)\n",	ftr->name, 
														ftr - traces );
}
