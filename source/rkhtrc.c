/*
 * 	rkhtrc.c
 */


#include "rkhassert.h"
#include "rkhtrc.h"
#include "rkh.h"


RKH_MODULE_NAME( rkhtrc );


#if RKH_TRC_EN == 1

static RKH_TRCE_T trcstm[ RKH_TRC_MAX_TRACES ];
static RKH_TRCE_T *trcin, *trcout, *trcend;
static rkhui8_t trcqty;
static rkhui8_t trcctrl;
static rkhui8_t *trcb;


void
rkh_trc_init( void )
{
	trcin = trcout = trcstm;
	trcqty = 0;
	trcend = &trcstm[ RKH_TRC_MAX_TRACES ];
	trcctrl = RKH_TRC_START;
}


void 
rkh_trc_control( HUInt opt )
{
	RKH_SR_CRITICAL_;

	RKH_ENTER_CRITICAL_();
	trcctrl = opt;
	RKH_EXIT_CRITICAL_();
}


rkhui8_t *
rkh_trc_get_nextbuf( void )
{
	rkhui8_t *tre = ( rkhui8_t* )0;
	RKH_SR_CRITICAL_;
	
	RKH_ENTER_CRITICAL_();

	tre = ( rkhui8_t* )trcin++;
	++trcqty;

	if( trcin == trcend )
		trcin = trcstm;

	if( trcqty >= RKH_TRC_MAX_TRACES )
	{
		trcqty = RKH_TRC_MAX_TRACES;
		trcout = trcin;
	}
	RKH_EXIT_CRITICAL_();
	return tre;
}


rkhui8_t *
rkh_trc_get_oldest( void )
{
	rkhui8_t *tre = ( rkhui8_t* )0;
	RKH_SR_CRITICAL_;

	RKH_ENTER_CRITICAL_();

	if( trcqty == 0 )
	{
		RKH_EXIT_CRITICAL_();
		return tre;
	}

	tre = ( rkhui8_t* )trcout++;
	--trcqty;

	if( trcout >= trcend )
		trcout = trcstm;

	RKH_EXIT_CRITICAL_();
	return tre;
}


void
rkh_trc_begin( void )
{
	RKH_SR_CRITICAL_;

	RKH_ENTER_CRITICAL_();
	trcb = rkh_trc_get_nextbuf();
}


void 
rkh_trc_ui8( rkhui8_t d )
{
	*trcb++ = d;
}


void 
rkh_trc_ui16( rkhui16_t d )
{
	*trcb++ = (rkhui8_t)d;
	d >>= 8;
	*trcb++ = (rkhui8_t)d;
}


void 
rkh_trc_ui32( rkhui32_t d )
{
	*trcb++ = (rkhui8_t)d;
	d >>= 8;
	*trcb++ = (rkhui8_t)d;
	d >>= 8;
	*trcb++ = (rkhui8_t)d;
	d >>= 8;
	*trcb++ = (rkhui8_t)d;
}


#endif
