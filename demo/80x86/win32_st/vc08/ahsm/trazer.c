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
#include "myevt.h"
#include <stdio.h>


RKH_THIS_MODULE


#define TRAZER_SIZEOF_SIG			RKH_SIZEOF_EVENT
#define TRAZER_SIZEOF_TSTAMP		RKH_TRC_SIZEOF_TSTAMP/8
#define TRAZER_SIZEOF_POINTER		RKH_TRC_SIZEOF_POINTER/8

#define MKTR( id, gn, nm, fmt, fargs )	\
				{ id, gn, nm, fmt, fargs }

#define MKS( sig, name )	\
				{ sig, name }

#define MKO( ix, obj, nm )								\
				objtbl[(ix)].adr = (unsigned long)(obj);	\
				objtbl[(ix)].name = nm

#define EOSIGTBL	\
				{ 0, (const char*)0 }


typedef char *(*HDLR_T)( const struct tre_t *tre );

typedef struct tre_t
{
	unsigned char id;
	const char *group;
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


static char *h_none( const struct tre_t *tre ),
			*h_mpinit( const struct tre_t *tre ),
			*h_rqinit( const struct tre_t *tre ),
			*h_rqelem( const struct tre_t *tre );


static const TRE_T traces[] =
{
	/* --- Memory Pool (MP) ------------------ */
	MKTR(	RKH_TRCE_MP_INIT,	"MP", "INIT", 
			"mp=%s, nblock=%02d",	h_mpinit ),
	MKTR(	 RKH_TRCE_MP_GET, 	"MP", "GET", 
			"mp=%s, nfree=%02d", 	h_none ),
	MKTR( 	RKH_TRCE_MP_PUT, 	"MP", "PUT", 
			"mp=%s, nfree=%02d", 	h_none ),
	
	/* --- Queue (RQ) ------------------------ */
	MKTR( 	RKH_TRCE_RQ_INIT,	"RQ", "INIT", 
			"rq=%s, nelem=%02d, sma=%s",	h_rqinit ),
	MKTR( 	RKH_TRCE_RQ_GET, 	"RQ", "GET", 
			"rq=%s, nused=%02d", 			h_rqelem ),
	MKTR( 	RKH_TRCE_RQ_FIFO,	"RQ", "FIFO", 
			"rq=%s, nused=%02d", 			h_rqelem ),
	MKTR( 	RKH_TRCE_RQ_LIFO,	"RQ", "LIFO", 
			"rq=%s, nused=%02d", 			h_rqelem ),
	MKTR( 	RKH_TRCE_RQ_FULL,	"RQ", "FULL", 
			"rq=%s", 						h_none ),
	MKTR( 	RKH_TRCE_RQ_DPT,	"RQ", "DPT", 
			"rq=%s", 						h_none ),

	/* --- State Machine Application (SMA) --- */
	MKTR( 	RKH_TRCE_SMA_ACT,	"SMA", "ACT", 
			"sma=%s", h_none ),
	MKTR( 	RKH_TRCE_SMA_TERM,	"SMA", "TERM", 
			"sma=%s", h_none ),
	MKTR( 	RKH_TRCE_SMA_GET,	"SMA", "GET", 
			"sma=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_SMA_FIFO,	"SMA", "FIFO", 
			"sma=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_SMA_LIFO,	"SMA", "LIFO", 
			"sma=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_SMA_REG,	"SMA", "REG", 
			"sma=%s, prio=%02d", h_none ),
	MKTR( 	RKH_TRCE_SMA_UNREG,	"SMA", "UNREG", 
			"sma=%s, prio=%02d", h_none ),

	/* --- State machine (SM) ---------------- */
	MKTR( 	RKH_TRCE_SM_INIT,	"SM", "INIT", 
			"sma=%s, istate=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_CLRH,	"SM", "CLRH", 
			"sma=%s, hist=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_DCH,	"SM", "DCH", 
			"sma=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_TRN,	"SM", "TRN", 
			"sma=%s, sstate=%s, tstate=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_STATE,	"SM", "STATE", 
			"sma=%s, state=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_ENSTATE,"SM", "ENSTATE", 
			"sma=%s, state=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_EXSTATE,"SM", "EXSTATE", 
			"sma=%s, state=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_NENEX,	"SM", "NENEX", 
			"sma=%s, nenex=%02d", h_none ),
	MKTR( 	RKH_TRCE_SM_NTRNACT,"SM", "NTRNACT", 
			"sma=%s, ntrnact=%02d", h_none ),
	MKTR( 	RKH_TRCE_SM_CSTATE,	"SM", "CSTATE", 
			"sma=%s, state=%s", h_none ),
	MKTR( 	RKH_TRCE_SM_DCH_RC,	"SM", "DCH_RC", 
			"sma=%s, rcode=%02d", h_none ),

	/* --- Timer (TIM) ----------------------- */
	MKTR( 	RKH_TRCE_TIM_INIT,	"TIM", "INIT", 
			"timer=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_TIM_START,	"TIM", "START", 
			"timer=%s, ntick=%05d, sma=%s", h_none ),
	MKTR( 	RKH_TRCE_TIM_RESTART,"TIM", "RESTART", 
			"timer=%s, ntick=%05d", h_none ),
	MKTR( 	RKH_TRCE_TIM_STOP,	"TIM", "STOP", 
			"timer=%s", h_none ),

	/* --- Framework (RKH) ------------------- */
	MKTR( 	RKH_TRCE_FWK_INIT,	"FWK", "INIT", 
			"", h_none ),
	MKTR( 	RKH_TRCE_FWK_EN,	"FWK", "EN", 
			"", h_none ),
	MKTR( 	RKH_TRCE_FWK_EX,	"FWK", "EX", 
			"", h_none ),
	MKTR( 	RKH_TRCE_FWK_EPREG,	"FWK", "EPREG", 
			"ssize=%05d, esize=%05d", h_none ),
	MKTR( 	RKH_TRCE_FWK_AE,	"FWK", "AE", 
			"esize=%05d, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_FWK_GC,	"FWK", "GC", 
			"sig=%s", h_none ),
	MKTR( 	RKH_TRCE_FWK_GCR,	"FWK", "GCR", 
			"sig=%s", h_none ),
	MKTR( 	RKH_TRCE_FWK_DEFER,	"FWK", "DEFER", 
			"rq=%s, sig=%s", h_none ),
	MKTR( 	RKH_TRCE_FWK_RCALL,	"FWK", "RCALL", 
			"sma=%s, sig=%s", h_none )
};


static const SYMSIG_T sigtbl[] = 			/* signal symbol table */
{
	MKS( ZERO,	"ZERO"	),
	MKS( ONE,	"ONE"	),
	MKS( TWO,	"TWO"	),
	MKS( THREE,	"THREE"	),
	MKS( FOUR,	"FOUR"	),
	MKS( FIVE,	"FIVE"	),
	MKS( SIX,	"SIX"	),
	MKS( TERM,	"TERM"	),

	EOSIGTBL
};


static const char *rctbl[] =				/* dispatch ret code table */
{
	"RKH_OK",
	"RKH_INPUT_NOT_FOUND",
	"RKH_CONDITION_NOT_FOUND",
	"RKH_GUARD_FALSE",
	"RKH_UNKNOWN_STATE",
	"RKH_EXCEED_HCAL_LEVEL",
	"RKH_EXCEED_TRC_SEGS"
};


#if TRAZER_SIZEOF_TSTAMP == 2
	static const char *trheader = "%05d %-3s %-7s : ";
#else
	static const char *trheader = "%010d %-3s %-7s : ";
#endif

static SYMOBJ_T objtbl[ 256 ];		/* object symbol table */
static rkhui8_t *trb;				/* points to trace event buffer */
static char fmt[ 128 ];
extern FILE *fdbg;


static
void
make_symtbl( void )
{
	MKO( 0, my, "my" );
	MKO( 1, &my->equeue, "my_queue" );
	MKO( 2, 0, (const char*)0 );
}


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
	strcpy( fmt, " " );
	return fmt;
}


char *
h_mpinit( const struct tre_t *tre )
{
	unsigned long mpobj;
	unsigned short nblock;

	mpobj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	nblock = (unsigned short)assemble( sizeof( char ) );
	sprintf( fmt, tre->fmt, map_obj( mpobj ), nblock );
	return fmt;
}


char *
h_rqinit( const struct tre_t *tre )
{
	unsigned long rqobj, smaobj;
	unsigned short nelem;

	rqobj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	nelem = (unsigned short)assemble( sizeof( char ) );
	smaobj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	sprintf( fmt, tre->fmt, map_obj( rqobj ), nelem, map_obj( smaobj ) );
	return fmt;
}


char *
h_rqelem( const struct tre_t *tre )
{
	unsigned long rqobj;
	unsigned short nelem;

	rqobj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	nelem = (unsigned short)assemble( sizeof( short ) );
	sprintf( fmt, tre->fmt, map_obj( rqobj ), nelem  );
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
			ts = ( RKHTS_T )assemble( TRAZER_SIZEOF_TSTAMP );
			printf( trheader, ts, ftr->group, ftr->name );
			fprintf( fdbg, trheader, ts, ftr->group, ftr->name );
			printf( "%s\n", (*ftr->fmt_args)( ftr ) );
			fprintf( fdbg, "%s\n", fmt );
		}
		return;
	}
	
	printf( "Unknown trace event = %s (%02d), group = %s\n", 	
										ftr->name, ftr->group, ftr - traces );
	fprintf( fdbg, "Unknown trace event = %s (%02d), group = %s\n",	
										ftr->name, ftr->group, ftr - traces );
}


void
trazer_init( void )
{
	make_symtbl();
}
