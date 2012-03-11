/*
 * 	rkhtrace.c
 */


#include "rkhassert.h"
#include "rkhtrace.h"
#include "rkh.h"


RKH_THIS_MODULE( 7, rkhtrace );


#if RKH_TR_EN == 1

static RKHTRCFG_T trcfgs[ RKH_MAX_SMA ];
static RKHTREVT_T trstream[ RKH_TR_MAX_NUM_TRACES ];
static RKHTREVT_T *trin, *trout;

#if RKH_TR_MAX_NUM_TRACES > 255
static rkhui16_t trqty;
#else
static rkhui8_t trqty;
#endif


#if 0
static
HUInt
rkh_is_trenabled( HUInt trix )
{
	RKHTRCFG_T *p;

	p = rkh_trace_getcfg( trix );
	return p->enable;
}


static
HUInt
rkh_insert_trevt( RKHTREVT_T *p )
{
	RKH_SR_CRITICAL_;

	RKH_ENTER_CRITICAL_();
	*trin = *p;

	if( ++trin >= trstream + RKH_TR_MAX_NUM_TRACES )
		trin = trstream;

	if( ++trqty >= RKH_TR_MAX_NUM_TRACES )
	{
		trqty = RKH_TR_MAX_NUM_TRACES;
		trout = trin;
	}
	RKH_EXIT_CRITICAL_();

	return RKH_TROK;
}
#endif


static
HUInt
rkh_remove_trevt( RKHTREVT_T *p )
{
	RKH_SR_CRITICAL_;

	RKH_ENTER_CRITICAL_();
	if( trqty == 0 )
	{
		RKH_EXIT_CRITICAL_();
		return RKH_TREMPTY;
	}

	*p = *trout;

	if( ++trout >= trstream + RKH_TR_MAX_NUM_TRACES )
		trout = trstream;

	--trqty;
	RKH_EXIT_CRITICAL_();
	return RKH_TROK;
}


RKHTRCFG_T *
rkh_trace_getcfg( HUInt trix )
{
	return &trcfgs[ trix ];
}


void
rkh_trace_init( void )
{
	trin = trout = trstream;
	trqty = 0;
}


void
rkh_trace_config( HUInt trix, HUInt log, HUInt print )
{
	RKHTRCFG_T *p;

	p = rkh_trace_getcfg( trix );

	p->log = log;
	p->print = print;
}


void 
rkh_trace_control( HUInt trix, HUInt opt )
{
	RKHTRCFG_T *p;

	p = rkh_trace_getcfg( trix );
	p->enable = opt;
}


void 
rkh_trace_evt( RKHTREVT_T *ptre )
{
	RKHTRCFG_T *pc;
	RKH_SR_CRITICAL_;
	
	RKH_ENTER_CRITICAL_();
	pc = rkh_trace_getcfg( ptre->smaid );
	if( pc->enable == RKH_TRSTOP )
	{
		RKH_EXIT_CRITICAL_();
		return;
	}

	*trin = *ptre;

	if( ++trin >= trstream + RKH_TR_MAX_NUM_TRACES )
		trin = trstream;

	if( ++trqty >= RKH_TR_MAX_NUM_TRACES )
	{
		trqty = RKH_TR_MAX_NUM_TRACES;
		trout = trin;
	}
	RKH_EXIT_CRITICAL_();
}


HUInt
rkh_trace_getnext( RKHTREVT_T *p )
{
	return rkh_remove_trevt( p );
}


rkhui16_t
rkh_trace_getqty( void )
{
	return trqty;
}


#endif
