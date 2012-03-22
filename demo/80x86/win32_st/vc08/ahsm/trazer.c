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
#include "rkhtim.h"
#include <stdio.h>


RKH_THIS_MODULE


#define TRAZER_EN 			(RKH_TRC_EN == 1 && ( RKH_TRC_ALL == 1 || 		\
							RKH_TRC_EN_MP == 1 || RKH_TRC_EN_RQ == 1 || 	\
							RKH_TRC_EN_SMA == 1 || RKH_TRC_EN_TIM == 1 || 	\
							RKH_TRC_EN_SM == 1 || RKH_TRC_EN_RKH == 1 ))


/*
 * 	Application dependent macros and typedefs
 */

#define TRAZER_SIZEOF_SIG			RKH_SIZEOF_EVENT/8
#define TRAZER_SIZEOF_TSTAMP		RKH_TRC_SIZEOF_TSTAMP/8
#define TRAZER_SIZEOF_POINTER		RKH_TRC_SIZEOF_POINTER/8
#define TRAZER_SIZEOF_NTIMER		RKH_TIM_SIZEOF_NTIMER/8
#define TRAZER_SIZEOF_NBLOCK		RKH_MP_SIZEOF_NBLOCK/8
#define TRAZER_SIZEOF_NELEM			RKH_RQ_SIZEOF_NELEM/8
#define TRAZER_SIZEOF_ESIZE			RKH_SIZEOF_ESIZE/8


#if TRAZER_SIZEOF_SIG == 1
	typedef unsigned char TRZE_T;
#elif TRAZER_SIZEOF_SIG == 2
	typedef unsigned short TRZE_T;
#elif TRAZER_SIZEOF_SIG == 4
	typedef unsigned long TRZE_T;
#else
	typedef unsigned char TRZE_T;
#endif


#if TRAZER_SIZEOF_TSTAMP == 1
	typedef unsigned char TRZTS_T;
#elif TRAZER_SIZEOF_TSTAMP == 2
	typedef unsigned short TRZTS_T;
#elif TRAZER_SIZEOF_TSTAMP == 4
	typedef unsigned long TRZTS_T;
#else
	typedef unsigned char TRZTS_T;
#endif


#if TRAZER_SIZEOF_NBLOCK == 1
	typedef unsigned char TRZNB_T;
#elif TRAZER_SIZEOF_NBLOCK == 2
	typedef unsigned short TRZNB_T;
#elif TRAZER_SIZEOF_NBLOCK == 4
	typedef unsigned long TRZNB_T;
#else
	typedef unsigned char TRZNB_T;
#endif


#if TRAZER_SIZEOF_NELEM == 1
	typedef unsigned char TRZNE_T;
#elif TRAZER_SIZEOF_NELEM == 2
	typedef unsigned short TRZNE_T;
#elif TRAZER_SIZEOF_NELEM == 4
	typedef unsigned long TRZNE_T;
#else
	typedef unsigned char TRZNE_T;
#endif


#if TRAZER_SIZEOF_NTIMER == 1
	typedef unsigned char TRZNT_T;
#elif TRAZER_SIZEOF_NTIMER == 2
	typedef unsigned short TRZNT_T;
#elif TRAZER_SIZEOF_NTIMER == 4
	typedef unsigned long TRZNT_T;
#else
	typedef unsigned char TRZNT_T;
#endif


#if TRAZER_SIZEOF_ESIZE == 1
	typedef unsigned char TRZES_T;
#elif TRAZER_SIZEOF_ESIZE == 2
	typedef unsigned short TRZES_T;
#elif TRAZER_SIZEOF_ESIZE == 4
	typedef unsigned long TRZES_T;
#else
	typedef unsigned char TRZES_T;
#endif


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
	TRZE_T sig;
	const char *name;
} SYMSIG_T;


static char *h_none( const struct tre_t *tre ),
			*h_epreg( const struct tre_t *tre ),
			*h_ae( const struct tre_t *tre ),
			*h_evt( const struct tre_t *tre ),
			*h_1sym( const struct tre_t *tre ),
			*h_2sym( const struct tre_t *tre ),
			*h_3sym( const struct tre_t *tre ),
			*h_symrc( const struct tre_t *tre ),
			*h_symu8( const struct tre_t *tre ),
			*h_sym2u8( const struct tre_t *tre ),
			*h_symevt( const struct tre_t *tre ),
			*h_symnblk( const struct tre_t *tre ),
			*h_2symnused( const struct tre_t *tre ),
			*h_symnused( const struct tre_t *tre ),
			*h_2symntick( const struct tre_t *tre ),
			*h_symntick( const struct tre_t *tre );


static const TRE_T traces[] =
{
	/* --- Memory Pool (MP) ------------------ */
	MKTR(	RKH_TRCE_MP_INIT,	"MP", "INIT", 
			"mp=%s, nblock=%d",				h_symnblk ),
	MKTR(	 RKH_TRCE_MP_GET, 	"MP", "GET", 
			"mp=%s, nfree=%d", 				h_symnblk ),
	MKTR( 	RKH_TRCE_MP_PUT, 	"MP", "PUT", 
			"mp=%s, nfree=%d", 				h_symnblk ),
	
	/* --- Queue (RQ) ------------------------ */
	MKTR( 	RKH_TRCE_RQ_INIT,	"RQ", "INIT", 
			"rq=%s, sma=%s, nelem=%d",		h_2symnused ),
	MKTR( 	RKH_TRCE_RQ_GET, 	"RQ", "GET", 
			"rq=%s, nused=%d", 				h_symnused ),
	MKTR( 	RKH_TRCE_RQ_FIFO,	"RQ", "POST_FIFO", 
			"rq=%s, nused=%d", 				h_symnused ),
	MKTR( 	RKH_TRCE_RQ_LIFO,	"RQ", "POST_LIFO", 
			"rq=%s, nused=%d", 				h_symnused ),
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
			"sma=%s, prio=%d", 				h_symu8 ),
	MKTR( 	RKH_TRCE_SMA_UNREG,	"SMA", "UNREGISTER", 
			"sma=%s, prio=%d", 				h_symu8 ),

	/* --- State machine (SM) ---------------- */
	MKTR( 	RKH_TRCE_SM_INIT,	"SM", "INIT", 
			"sma=%s, istate=%s", 			h_2sym ),
	MKTR( 	RKH_TRCE_SM_CLRH,	"SM", "CLEAR_HIST", 
			"sma=%s, hist=%s", 				h_2sym ),
	MKTR( 	RKH_TRCE_SM_DCH,	"SM", "DISPATCH", 
			"sma=%s, sig=%s", 				h_symevt ),
	MKTR( 	RKH_TRCE_SM_TRN,	"SM", "TRANSITION", 
			"sma=%s, sstate=%s, tstate=%s", h_3sym ),
	MKTR( 	RKH_TRCE_SM_STATE,	"SM", "CURRENT_STATE", 
			"sma=%s, state=%s", 			h_2sym ),
	MKTR( 	RKH_TRCE_SM_ENSTATE,"SM", "ENTRY_STATE", 
			"sma=%s, state=%s", 			h_2sym ),
	MKTR( 	RKH_TRCE_SM_EXSTATE,"SM", "EXIT_STATE", 
			"sma=%s, state=%s", 			h_2sym ),
	MKTR( 	RKH_TRCE_SM_NENEX,	"SM", "NUM_EN_EX", 
			"sma=%s, nentry=%d, nexit=%d",	h_sym2u8 ),
	MKTR( 	RKH_TRCE_SM_NTRNACT,"SM", "NUM_TRN_ACT", 
			"sma=%s, ntrnaction=%d", 		h_symu8 ),
	MKTR( 	RKH_TRCE_SM_CSTATE,	"SM", "COMP_STATE", 
			"sma=%s, state=%s", 			h_2sym ),
	MKTR( 	RKH_TRCE_SM_DCH_RC,	"SM", "DISPATCH_RCODE", 
			"sma=%s, retcode=%s", 			h_symrc ),

	/* --- Timer (TIM) ----------------------- */
	MKTR( 	RKH_TRCE_TIM_INIT,	"TIM", "INIT", 
			"timer=%s, sig=%s", 			h_symevt ),
	MKTR( 	RKH_TRCE_TIM_START,	"TIM", "START", 
			"timer=%s, sma=%s, ntick=%d", 	h_2symntick ),
	MKTR( 	RKH_TRCE_TIM_RESTART,"TIM", "RESTART", 
			"timer=%s, ntick=%5d", 			h_symntick ),
	MKTR( 	RKH_TRCE_TIM_STOP,	"TIM", "STOP", 
			"timer=%s", 					h_1sym ),
	MKTR( 	RKH_TRCE_TIM_TOUT,	"TIM", "TIMEOUT", 
			"timer=%s", 					h_1sym ),

	/* --- Framework (RKH) ------------------- */
	MKTR( 	RKH_TRCE_RKH_INIT,	"RKH", "INIT", 
			"", 							h_none ),
	MKTR( 	RKH_TRCE_RKH_EN,	"RKH", "ENTER", 
			"", 							h_none ),
	MKTR( 	RKH_TRCE_RKH_EX,	"RKH", "EXIT", 
			"", 							h_none ),
	MKTR( 	RKH_TRCE_RKH_EPREG,	"RKH", "EPOOL_REG", 
			"epix =%d, ssize=%d, esize=%d",	h_epreg ),
	MKTR( 	RKH_TRCE_RKH_AE,	"RKH", "ALLOC_EVENT", 
			"esize=%d, sig=%s", 			h_ae ),
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
	MKS( SEVEN,	"SEVEN"	),
	MKS( EIGHT,	"EIGHT"	),
	MKS( NINE,	"NINE"	),
	MKS( TOUT,	"TOUT"	),
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
	static const char *trheader = "%5d %-4s| %-15s : ";
#else
	static const char *trheader = "%10d %-4s| %-15s : ";
#endif


static SYMOBJ_T objtbl[ 128 ];		/* object symbol table */
static rkhui8_t *trb;				/* points to trace event buffer */
static char fmt[ 128 ];
extern FILE *fdbg;

extern RKHT_T my_timer;

static
void
make_symtbl( void )
{
	int i = -1;

	MKO( my, 			"my"		);
	MKO( &my->equeue,	"my_queue"	);
	MKO( &my_timer, 	"my_timer"	);
	MKO( &rkheplist[0], "ep0"		);
	MKO( &rkheplist[1], "ep1"		);
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
map_sig( TRZE_T sig )
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
h_symnblk( const struct tre_t *tre )
{
	unsigned long obj;
	TRZNB_T nblock;

	obj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	nblock = (TRZNB_T)assemble( sizeof( TRZNB_T ) );
	sprintf( fmt, tre->fmt, map_obj( obj ), nblock );
	return fmt;
}


char *
h_2symnused( const struct tre_t *tre )
{
	unsigned long obj1, obj2;
	TRZNE_T nelem;

	obj1 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	obj2 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	nelem = (TRZNE_T)assemble( sizeof( TRZNE_T ) );
	sprintf( fmt, tre->fmt, map_obj( obj1 ), map_obj( obj2 ), nelem );
	return fmt;
}


char *
h_symnused( const struct tre_t *tre )
{
	unsigned long obj;
	TRZNE_T nelem;

	obj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	nelem = (TRZNE_T)assemble( sizeof( TRZNE_T ) );
	sprintf( fmt, tre->fmt, map_obj( obj ), nelem );
	return fmt;
}


char *
h_2symntick( const struct tre_t *tre )
{
	unsigned long obj1, obj2;
	TRZNT_T ntick;

	obj1 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	obj2 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	ntick = (TRZNT_T)assemble( sizeof( TRZNT_T ) );
	sprintf( fmt, tre->fmt, map_obj( obj1 ), map_obj( obj2 ), ntick );
	return fmt;
}


char *
h_symntick( const struct tre_t *tre )
{
	unsigned long obj1;
	TRZNT_T ntick;

	obj1 = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	ntick = (TRZNT_T)assemble( sizeof( TRZNT_T ) );
	sprintf( fmt, tre->fmt, map_obj( obj1 ), ntick );
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
	TRZE_T e;

	e = (TRZE_T)assemble( sizeof( TRZE_T ) );
	sprintf( fmt, tre->fmt, map_sig( e ) );
	return fmt;
}


char *
h_symevt( const struct tre_t *tre )
{
	unsigned long obj;
	TRZE_T e;

	obj = (unsigned long)assemble( TRAZER_SIZEOF_POINTER );
	e = (TRZE_T)assemble( sizeof( TRZE_T ) );
	sprintf( fmt, tre->fmt, map_obj( obj ), map_sig( e ) );
	return fmt;
}


char *
h_epreg( const struct tre_t *tre )
{
	unsigned long u32;
	TRZES_T esize;
	unsigned char u8;

	u8 = (unsigned char)assemble( sizeof( char ) );
	u32 = (unsigned long)assemble( sizeof( long ) );
	esize = (TRZES_T)assemble( sizeof( TRZES_T ) );
	sprintf( fmt, tre->fmt, u8, u32, esize  );
	return fmt;
}


char *
h_ae( const struct tre_t *tre )
{
	TRZES_T esize;
	TRZE_T e;

	esize = (TRZES_T)assemble( sizeof( TRZES_T ) );
	e = (TRZE_T)assemble( sizeof( TRZE_T ) );
	sprintf( fmt, tre->fmt, esize, map_sig( e ) );
	return fmt;
}


void 
trazer_parse( rkhui8_t *tre )
{
#if RKH_TRC_EN == 1 
	const TRE_T *ftr;			/* received trace event */
	TRZTS_T ts;

	if( ( ftr = find_trevt( tre[ 0 ] ) ) != ( TRE_T* )0 )
	{
		if( ftr->fmt_args != ( HDLR_T )0 )
		{
			trb = tre + 1;		/* from timestamp field */
			ts = ( TRZTS_T )assemble( TRAZER_SIZEOF_TSTAMP );
			printf( trheader, ts, ftr->group, ftr->name );
			fprintf( fdbg, trheader, ts, ftr->group, ftr->name );
			printf( "%s\n", (*ftr->fmt_args)( ftr ) );
			fprintf( fdbg, "%s\n", fmt );
		}
		return;
	}
	
	printf( "Unknown trace event = %s (%d), group = %s\n", 	
										ftr->name, ftr->group, ftr - traces );
	fprintf( fdbg, "Unknown trace event = %s (%d), group = %s\n",	
										ftr->name, ftr->group, ftr - traces );
#else
	( void )tre;
#endif
}


void
trazer_init( void )
{
#if TRAZER_EN == 1 
	printf( "---- RKH trace log session ----\n\n" );
	printf( "Date = "__DATE__ __TIME__"\n" );
	printf( "Configurations = \n\n" );
	printf( "   TRAZER_SIZEOF_SIG     = %d\n", TRAZER_SIZEOF_SIG );
	printf( "   TRAZER_SIZEOF_TSTAMP  = %d\n", TRAZER_SIZEOF_TSTAMP );
	printf( "   TRAZER_SIZEOF_POINTER = %d\n", TRAZER_SIZEOF_POINTER );
	printf( "   TRAZER_SIZEOF_NTIMER  = %d\n", TRAZER_SIZEOF_NTIMER );
	printf( "   TRAZER_SIZEOF_NBLOCK  = %d\n", TRAZER_SIZEOF_NBLOCK );
	printf( "   TRAZER_SIZEOF_NELEM   = %d\n", TRAZER_SIZEOF_NELEM );
	printf( "   TRAZER_SIZEOF_ESIZE   = %d\n", TRAZER_SIZEOF_ESIZE );
	printf( "   RKH_TRC_ALL           = %d\n", RKH_TRC_ALL );
	printf( "   RKH_TRC_EN_MP         = %d\n", RKH_TRC_EN_MP );
	printf( "   RKH_TRC_EN_RQ         = %d\n", RKH_TRC_EN_RQ );
	printf( "   RKH_TRC_EN_SMA        = %d\n", RKH_TRC_EN_SMA );
	printf( "   RKH_TRC_EN_TIM        = %d\n", RKH_TRC_EN_TIM );
	printf( "   RKH_TRC_EN_SM         = %d\n", RKH_TRC_EN_SM );
	printf( "   RKH_TRC_EN_RKH        = %d\n", RKH_TRC_EN_RKH );
	printf( "\n---- BEGIN TRACE SESSION ----\n\n" );

	fprintf( fdbg, "---- RKH trace log session ----\n" );
	fprintf( fdbg, "date : "__DATE__ __TIME__"\n" );
	fprintf( fdbg, "Configurations = \n\n" );
	fprintf( fdbg, "   TRAZER_SIZEOF_SIG     = %d\n", TRAZER_SIZEOF_SIG );
	fprintf( fdbg, "   TRAZER_SIZEOF_TSTAMP  = %d\n", TRAZER_SIZEOF_TSTAMP );
	fprintf( fdbg, "   TRAZER_SIZEOF_POINTER = %d\n", TRAZER_SIZEOF_POINTER );
	fprintf( fdbg, "   TRAZER_SIZEOF_NTIMER  = %d\n", TRAZER_SIZEOF_NTIMER );
	fprintf( fdbg, "   TRAZER_SIZEOF_NBLOCK  = %d\n", TRAZER_SIZEOF_NBLOCK );
	fprintf( fdbg, "   TRAZER_SIZEOF_NELEM   = %d\n", TRAZER_SIZEOF_NELEM );
	fprintf( fdbg, "   TRAZER_SIZEOF_ESIZE   = %d\n", TRAZER_SIZEOF_ESIZE );
	fprintf( fdbg, "   RKH_TRC_ALL        	 = %d\n", RKH_TRC_ALL );
	fprintf( fdbg, "   RKH_TRC_EN_MP         = %d\n", RKH_TRC_EN_MP );
	fprintf( fdbg, "   RKH_TRC_EN_RQ         = %d\n", RKH_TRC_EN_RQ );
	fprintf( fdbg, "   RKH_TRC_EN_SMA        = %d\n", RKH_TRC_EN_SMA );
	fprintf( fdbg, "   RKH_TRC_EN_TIM        = %d\n", RKH_TRC_EN_TIM );
	fprintf( fdbg, "   RKH_TRC_EN_SM         = %d\n", RKH_TRC_EN_SM );
	fprintf( fdbg, "   RKH_TRC_EN_RKH        = %d\n", RKH_TRC_EN_RKH );
	fprintf( fdbg, "\n---- BEGIN TRACE SESSION ----\n\n" );

	make_symtbl();
#endif
}
