/*
 * 	rkhtrc.c
 */


#include "rkhassert.h"
#include "rkhtrc.h"
#include "rkh.h"
#include "rkhrdy.h"


RKH_MODULE_NAME( rkhtrc );


#if RKH_TRC_EN == 1

#if RKH_TRC_RUNTIME_FILTER == 1
rkhui8_t trceftbl[ RKH_TRC_MAX_EVENTS ];	/* trace event filter table */
rkhui8_t trcgfilter;						/* trace group filter table */
#endif

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
	//RKH_SR_CRITICAL_;

	//RKH_ENTER_CRITICAL_();
	trcctrl = opt;
	//RKH_EXIT_CRITICAL_();
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


#if RKH_TRC_RUNTIME_FILTER == 1
HUInt
rkh_trc_ison_( rkhui8_t grp, rkhui8_t e )
{
	return (( trcgfilter & rkh_maptbl[ grp ] ) != 0 ) &&
				(( trceftbl[ e >> 3 ] & rkh_maptbl[ e & 0x07 ]) != 0 );
#if 0
	return (( trcgfilter & (1<<grp) ) != 0 ) &&
				(( trceftbl[ e >> 3 ] & (1 << ( e&0x07 )) ) != 0 );
#endif
}


void 
rkh_trc_filter_group_( rkhui8_t ctrl, rkhui8_t grp )
{
	if( grp == RKH_TRC_ALL_GROUPS )
	{
		trcgfilter = ( ctrl == FILTER_ON ) ? 0xFF : 0;
		return;
	}

	if( ctrl == FILTER_ON )
		trcgfilter |= rkh_maptbl[ grp ];
	else
		trcgfilter &= ~rkh_maptbl[ grp ];
}


void 
rkh_trc_filter_event_( rkhui8_t ctrl, rkhui8_t evt )
{
	rkhui8_t *p, ix;


	if( evt == RKH_TRC_ALL_EVENTS )
	{
		for( p = trceftbl, ix = 0; ix < RKH_TRC_MAX_EVENTS; ++ix, ++p )
			*p = ( ctrl == FILTER_ON ) ? 0xFF : 0;
		return;
	}

	if( ctrl == FILTER_ON )
		trceftbl[ evt>>3 ] |= rkh_maptbl[ evt & 0x07 ];
	else
		trceftbl[ evt>>3 ] &= ~rkh_maptbl[ evt & 0x07 ];
}
#endif

void
rkh_trc_begin( void )
{
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
