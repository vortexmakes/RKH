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

#define MKO( obj, nm )									\
				++i;									\
				objtbl[i].adr = (unsigned long)(obj);	\
				objtbl[i].name = nm

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
			*h_2u16( const struct tre_t *tre ),
			*h_u16u8( const struct tre_t *tre ),
			*h_evt( const struct tre_t *tre ),
			*h_1sym( const struct tre_t *tre ),
			*h_2sym( const struct tre_t *tre ),
			*h_3sym( const struct tre_t *tre ),
			*h_symrc( const struct tre_t *tre ),
			*h_symu8( const struct tre_t *tre ),
			*h_sym2u8( const struct tre_t *tre ),
			*h_symevt( const struct tre_t *tre ),
			*h_2symu8( const struct tre_t *tre ),
			*h_symu16( const struct tre_t *tre ),
			*h_2symu16( const struct tre_t *tre );


static const TRE_T traces[] =
{
	/* --- Memory Pool (MP) ------------------ */
	MKTR(	RKH_TRCE_MP_INIT,	"MP", "INIT", 
			"mp=%s, nblock=%02d",			h_symu8 ),
	MKTR(	 RKH_TRCE_MP_GET, 	"MP", "GET", 
			"mp=%s, nfree=%02d", 			h_symu8 ),
	MKTR( 	RKH_TRCE_MP_PUT, 	"MP", "PUT", 
			"mp=%s, nfree=%02d", 			h_symu8 ),
	
	/* --- Queue (RQ) ------------------------ */
	MKTR( 	RKH_TRCE_RQ_INIT,	"RQ", "INIT", 
			"rq=%s, sma=%s, nelem=%02d",	h_2symu8 ),
	MKTR( 	RKH_TRCE_RQ_GET, 	"RQ", "GET", 
			"rq=%s, nused=%02d", 			h_symu8 ),
	MKTR( 	RKH_TRCE_RQ_FIFO,	"RQ", "POST_FIFO", 
			"rq=%s, nused=%02d", 			h_symu8 ),
	MKTR( 	RKH_TRCE_RQ_LIFO,	"RQ", "POST_LIFO", 
			"rq=%s, nused=%02d", 			h_symu8 ),
	MKTR( 	RKH_TRCE_RQ_FULL,	"RQ", "FULL", 
			"rq=%s", 						h_1sym ),
	MKTR( 	RKH_TRCE_RQ_DPT,	"RQ", "DEPLETE", 
			"rq=%s", 						h_1sym ),

	/* --- State Machine Application (SMA) --- */
	MKTR( 	RKH_TRCE_SMA_ACT,	"SMA", "ACTIVATE", 
			"sma=%s", 						h_1sym ),
	MKTR( 	RKH_TRCE_SMA_TERM,	"SMA", "TERMINATE", 
			"sma=%s", 						h_1sym ),
	MKTR( 	RKH_TRCE_SMA_GET,	"SMA", "GET_EVENT", 
			"sma=%s, sig=%s", 				h_symevt ),
	MKTR( 	RKH_TRCE_SMA_FIFO,	"SMA", "POST_FIFO", 
			"sma=%s, sig=%s", 				h_symevt ),
	MKTR( 	RKH_TRCE_SMA_LIFO,	"SMA", "POST_LIFO", 
			"sma=%s, sig=%s", 				h_symevt ),
	MKTR( 	RKH_TRCE_SMA_REG,	"SMA", "REGISTER", 
			"sma=%s, prio=%02d", 			h_symu8 ),
	MKTR( 	RKH_TRCE_SMA_UNREG,	"SMA", "UNREGISTER", 
			"sma=%s, prio=%02d", 			h_symu8 ),

	/* --- State machine (SM) ---------------- */
	MKTR( 	RKH_TRCE_SM_INIT,	"SM", "INIT", 
			"sma=%s, istate=%s", 			h_2sym ),
	MKTR( 	RKH_TRCE_SM_CLRH,	"SM", "CLEAR_HIST", 
			"sma=%s, hist=%s", 				h_2sym ),
	MKTR( 	RKH_TRCE_SM_DCH,	"SM", "DISPATCH", 
			"sma=%s, sig=%s", 				h_symevt ),
	MKTR( 	RKH_TRCE_SM_TRN,	"SM", "TRANSITION", 
			"sma=%s, sstate=%s, tstate=%s", h_3sym ),
	MKTR( 	RKH_TRCE_SM_STATE,	"SM", "STATE", 
			"sma=%s, state=%s", 			h_2sym ),
	MKTR( 	RKH_TRCE_SM_ENSTATE,"SM", "ENSTATE", 
			"sma=%s, state=%s", 			h_2sym ),
	MKTR( 	RKH_TRCE_SM_EXSTATE,"SM", "EXSTATE", 
			"sma=%s, state=%s", 			h_2sym ),
	MKTR( 	RKH_TRCE_SM_NENEX,	"SM", "NUM_EN_EX", 
			"sma=%s, nentry=%02d, nexit=%02d",	h_sym2u8 ),
	MKTR( 	RKH_TRCE_SM_NTRNACT,"SM", "NUM_TRN_ACT", 
			"sma=%s, ntrnaction=%02d", 		h_symu8 ),
	MKTR( 	RKH_TRCE_SM_CSTATE,	"SM", "COMP_STATE", 
			"sma=%s, state=%s", 			h_2sym ),
	MKTR( 	RKH_TRCE_SM_DCH_RC,	"SM", "DISPATCH_RC", 
			"sma=%s, retcode=%s", 			h_symrc ),

	/* --- Timer (TIM) ----------------------- */
	MKTR( 	RKH_TRCE_TIM_INIT,	"TIM", "INIT", 
			"timer=%s, sig=%s", 			h_symevt ),
	MKTR( 	RKH_TRCE_TIM_START,	"TIM", "START", 
			"timer=%s, ntick=%05d, sma=%s", h_2symu16 ),
	MKTR( 	RKH_TRCE_TIM_RESTART,"TIM", "RESTART", 
			"timer=%s, ntick=%05d", 		h_symu16 ),
	MKTR( 	RKH_TRCE_TIM_STOP,	"TIM", "STOP", 
			"timer=%s", 					h_1sym ),

	/* --- Framework (RKH) ------------------- */
	MKTR( 	RKH_TRCE_RKH_INIT,	"RKH", "INIT", 
			"", 							h_none ),
	MKTR( 	RKH_TRCE_RKH_EN,	"RKH", "ENTER", 
			"", 							h_none ),
	MKTR( 	RKH_TRCE_RKH_EX,	"RKH", "EXIT", 
			"", 							h_none ),
	MKTR( 	RKH_TRCE_RKH_EPREG,	"RKH", "EPOOL_REG", 
			"ssize=%05d, esize=%05d", 		h_2u16 ),
	MKTR( 	RKH_TRCE_RKH_AE,	"RKH", "ALLOC_EVT", 
			"esize=%05d, sig=%s", 			h_u16u8 ),
	MKTR( 	RKH_TRCE_RKH_GC,	"RKH", "GC", 
			"sig=%s", 						h_evt ),
	MKTR( 	RKH_TRCE_RKH_GCR,	"RKH", "GCR", 
			"sig=%s", 						h_evt ),
	MKTR( 	RKH_TRCE_RKH_DEFER,	"RKH", "DEFER", 
			"rq=%s, sig=%s", 				h_symevt ),
	MKTR( 	RKH_TRCE_RKH_RCALL,	"RKH", "RECALL", 
			"sma=%s, sig=%s", 				h_symevt )
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
	static const char *trheader = "%05d %-4s| %-12s : ";
#else
	static const char *trheader = "%010d %-4s| %-12s : ";
#endif

static SYMOBJ_T objtbl[ 128 ];		/* object symbol table */
static rkhui8_t *trb;				/* points to trace event buffer */
static char fmt[ 128 ];
extern FILE *fdbg;


static
void
make_symtbl( void )
{
	int i = -1;

	MKO( my, 			"my"		);
	MKO( &my->equeue,	"my_queue"	);
	MKO( &S1, 			"S1"		);
	MKO( &S11, 			"S11"		);
	MKO( &S111, 		"S111"		);
	MKO( &S112, 		"S112"		);
	MKO( &S12, 			"S12"		);
	MKO( &S2, 			"S2"		);
	MKO( &S3, 			"S3" 		);
	MKO( &S31, 			"S31" 		);
	MKO( &S32, 			"S32"		);

	MKO( 0, 			(const char*)0 );
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
h_1sym( const struct tre_t *tre )
{
	unsigned long obj;

	obj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	sprintf( fmt, tre->fmt, map_obj( obj ) );
	return fmt;
}


char *
h_2sym( const struct tre_t *tre )
{
	unsigned long obj1, obj2;

	obj1 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	obj2 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	sprintf( fmt, tre->fmt, map_obj( obj1 ), map_obj( obj2 ) );
	return fmt;
}


char *
h_3sym( const struct tre_t *tre )
{
	unsigned long obj1, obj2, obj3;

	obj1 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	obj2 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	obj3 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	sprintf( fmt, tre->fmt, map_obj( obj1 ), map_obj( obj2 ), 
												map_obj( obj3 ) );
	return fmt;
}


char *
h_symrc( const struct tre_t *tre )
{
	unsigned long obj;
	unsigned char u8;

	obj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	u8 = (unsigned char)assemble( sizeof( char ) );
	sprintf( fmt, tre->fmt, map_obj( obj ), rctbl[ u8 ] );
	return fmt;
}


char *
h_symu8( const struct tre_t *tre )
{
	unsigned long obj;
	unsigned char u8;

	obj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	u8 = (unsigned char)assemble( sizeof( char ) );
	sprintf( fmt, tre->fmt, map_obj( obj ), u8 );
	return fmt;
}


char *
h_sym2u8( const struct tre_t *tre )
{
	unsigned long obj;
	unsigned char u8_1, u8_2;

	obj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	u8_1 = (unsigned char)assemble( sizeof( char ) );
	u8_2 = (unsigned char)assemble( sizeof( char ) );
	sprintf( fmt, tre->fmt, map_obj( obj ), u8_1, u8_2 );
	return fmt;
}


char *
h_evt( const struct tre_t *tre )
{
	unsigned char u8;

	u8 = (unsigned char)assemble( sizeof( char ) );
	sprintf( fmt, tre->fmt, map_sig( u8 ) );
	return fmt;
}


char *
h_symevt( const struct tre_t *tre )
{
	unsigned long obj;
	unsigned char u8;

	obj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	u8 = (unsigned char)assemble( sizeof( char ) );
	sprintf( fmt, tre->fmt, map_obj( obj ), map_sig( u8 ) );
	return fmt;
}


char *
h_2symu8( const struct tre_t *tre )
{
	unsigned long obj1, obj2;
	unsigned char u8;

	obj1 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	obj2 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	u8 = (unsigned char )assemble( sizeof( char ) );
	sprintf( fmt, tre->fmt, map_obj( obj1 ), map_obj( obj2 ), u8 );
	return fmt;
}


char *
h_symu16( const struct tre_t *tre )
{
	unsigned long obj;
	unsigned short u16;

	obj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	u16 = (unsigned short)assemble( sizeof( short ) );
	sprintf( fmt, tre->fmt, map_obj( obj ), u16  );
	return fmt;
}


char *
h_2symu16( const struct tre_t *tre )
{
	unsigned long obj;
	unsigned short u16_1, u16_2;

	obj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	u16_1 = (unsigned short)assemble( sizeof( short ) );
	u16_2 = (unsigned short)assemble( sizeof( short ) );
	sprintf( fmt, tre->fmt, map_obj( obj ), u16_1, u16_2  );
	return fmt;
}


char *
h_2u16( const struct tre_t *tre )
{
	unsigned short u16_1, u16_2;

	u16_1 = (unsigned short)assemble( sizeof( short ) );
	u16_2 = (unsigned short)assemble( sizeof( short ) );
	sprintf( fmt, tre->fmt, u16_1, u16_2  );
	return fmt;
}


char *
h_u16u8( const struct tre_t *tre )
{
	unsigned short u16;
	unsigned char u8;

	u16 = (unsigned short)assemble( sizeof( short ) );
	u8 = (unsigned char)assemble( sizeof( char ) );
	sprintf( fmt, tre->fmt, u16, u8 );
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
