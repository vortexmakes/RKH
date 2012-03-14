/*
 * 	rkhtrc.c
 */


#include "rkhassert.h"
#include "rkhtrc.h"
#include "rkh.h"


RKH_THIS_MODULE( 7, rkhtrc );


#if RKH_TRC_EN == 1

static RKH_TRCEVT_T trcstm[ RKH_TRC_MAX_TRACES ];
static RKH_TRCEVT_T *trcin, *trcout;
static rkhui8_t trcqty;
static rkhui8_t trcctrl;


static
HUInt
rkh_remove_trevt( RKHTREVT_T *p )
{
	RKH_SR_CRITICAL_;

	RKH_ENTER_CRITICAL_();
	if( trcqty == 0 )
	{
		RKH_EXIT_CRITICAL_();
		return RKH_TRC_EMPTY;
	}

	*p = *trcout;

	if( ++trcout >= trstm + RKH_TRC_MAX_TRACES )
		trcout = trcsm;

	--trcqty;
	RKH_EXIT_CRITICAL_();
	return RKH_TRC_OK;
}


void
rkh_trc_init( void )
{
	trcin = trcout = trcsm;
	trcqty = 0;
}


void 
rkh_trc_control( HUInt opt )
{
	RKH_SR_CRITICAL_;

	RKH_ENTER_CRITICAL_();
	rkh_trc_enable = opt;
	RKH_EXIT_CRITICAL_();
}


void 
rkh_trc_evt( RKHTREVT_T *ptre )
{
	RKHTRCFG_T *pc;
	RKH_SR_CRITICAL_;
	
	RKH_ENTER_CRITICAL_();
	pc = rkh_trc_getcfg( ptre->smaid );
	if( pc->enable == RKH_TRSTOP )
	{
		RKH_EXIT_CRITICAL_();
		return;
	}

	*trcin = *ptre;

	if( ++trcin >= trcstm + RKH_TRC_MAX_TRACES )
		trcin = trcsm;

	if( ++trcqty >= RKH_TRC_MAX_TRACES )
	{
		trcqty = RKH_TRC_MAX_TRACES;
		trcout = trcin;
	}
	RKH_EXIT_CRITICAL_();
}


HUInt
rkh_trc_get( RKH_TRCEVT_T *ptrce )
{
	return RKH_TRC_EMPTY;
}


void 
rkh_trc_ui8( rkhui8_t d )
{
}


void 
rkh_trc_ui16( rkhui16_t d )
{
}


void 
rkh_trc_ui32( rkhui32_t d )
{
}


#endif
