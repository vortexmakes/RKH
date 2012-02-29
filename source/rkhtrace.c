/*
 * 	rkhtrace.c
 */


#include "rkh.h"
#include "rkhtrace.h"


RKH_THIS_MODULE( 7, rkhtrace );


#if RKH_TRACE == 1


static RKHTRCFG_T trcfgs[ RKH_NUM_STATE_MACHINES ];
static RKHTREVT_T trstream[ RKH_MAX_NUM_TRACES ];
static RKHTREVT_T *trin, *trout;

#if RKH_MAX_NUM_TRACES > 255
static rkhui16_t trqty;
#else
static rkhui8_t trqty;
#endif


static
HUInt
rkh_is_trenabled( HUInt trix )
{
	RKHTRCFG_T *p;

	p = rkh_trgetcfg( trix );
	return p->enable;
}


static
HUInt
rkh_insert_trevt( RKHTREVT_T *p )
{
	*trin = *p;

	if( ++trin >= trstream + RKH_MAX_NUM_TRACES )
		trin = trstream;

	if( ++trqty >= RKH_MAX_NUM_TRACES )
	{
		trqty = RKH_MAX_NUM_TRACES;
		trout = trin;
	}

	return RKH_TROK;
}


static
HUInt
rkh_remove_trevt( RKHTREVT_T *p )
{
	if( trqty == 0 )
		return RKH_TREMPTY;

	*p = *trout;

	if( ++trout >= trstream + RKH_MAX_NUM_TRACES )
		trout = trstream;

	--trqty;

	return RKH_TROK;
}


RKHTRCFG_T *
rkh_trgetcfg( HUInt trix )
{
	return &trcfgs[ trix ];
}


void
rkh_trinit( void )
{
	trin = trout = trstream;
	trqty = 0;
}


void
rkh_trconfig( HUInt trix, HUInt log, HUInt print )
{
	RKHTRCFG_T *p;

	p = rkh_trgetcfg( trix );

	p->log = log;
	p->print = print;
}


void 
rkh_trcontrol( HUInt trix, HUInt opt )
{
	RKHTRCFG_T *p;

	p = rkh_trgetcfg( trix );
	p->enable = opt;
}


void 
rkh_trevt( RKHTREVT_T *ptre )
{
	if( rkh_is_trenabled( ptre->smix ) == RKH_TRSTOP )
		return;

	rkh_insert_trevt( ptre );
}


HUInt
rkh_trgetnext( RKHTREVT_T *p )
{
	return rkh_remove_trevt( p );
}


rkhui16_t
rkh_trgetqty( void )
{
	return trqty;
}


#endif
