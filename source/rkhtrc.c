/*
 * 	rkhtrc.c
 */


#include "rkhassert.h"
#include "rkhtrc.h"
#include "rkh.h"
#include "rkhrdy.h"


RKH_MODULE_NAME( rkhtrc )


#if RKH_TRC_EN == 1

#define GETGRP( e )		(rkhui8_t)(((e) & 0xE0) >> 5)
#define GETEVT( e )		(rkhui8_t)((e) & 0x1F)

#if RKH_TRC_RUNTIME_FILTER == 1
/* trace event filter table */
rkhui8_t trceftbl[ RKH_TRC_MAX_EVENTS_IN_BYTES ];

/* trace group filter table */
rkhui8_t trcgfilter;

/* trace points associated with the SMA (AO */
rkhui8_t trcsmaftbl[ RKH_TRC_MAX_SMA ];
#endif

static RKH_TE_T trcstm[ RKH_TRC_SIZEOF_STREAM ];
static RKH_TE_T *trcin, *trcout, *trcend;
static HUInt trcctrl;
static rkhui8_t chk;
static rkhui8_t nseq;
#if RKH_TRC_SIZEOF_STREAM < 255
static rkhui8_t trcqty;
#else
static rkhui16_t trcqty;
#endif


/* From group to event table */
static RKHROM rkhui8_t trcgmtbl[] =
{
	/*	<offset>	| <range> [in bytes] */
	/*                1 byte -> 8 events */
	(	(0 << 4) 	| 1		),	/* RKH_MP_START */
	(	(1 << 4) 	| 1		),	/* RKH_RQ_START */
	(	(2 << 4) 	| 1		),	/* RKH_SMA_START */
	(	(3 << 4) 	| 3		),	/* RKH_SM_START */
	(	(6 << 4) 	| 1		),	/* RKH_TIM_START */
	(	(7 << 4) 	| 2		),	/* RKH_FWK_START */
	(	(9 << 4) 	| 1		)	/* RKH_USR_START */
};


void
rkh_trc_init( void )
{
	trcin = trcout = trcstm;
	trcqty = 0;
	nseq = 0;
	trcend = &trcstm[ RKH_TRC_SIZEOF_STREAM ];
	trcctrl = RKH_TRC_START;
	RKH_TRC_U8_RAW( RKH_FLG );
}


void 
rkh_trc_control( HUInt opt )
{
	/* RKH_SR_CRITICAL_;*/

	/* RKH_ENTER_CRITICAL_(); */
	trcctrl = opt;
	/* RKH_EXIT_CRITICAL_(); */
}


void
rkh_trc_put( rkhui8_t b )
{
	*trcin++ = b;
	++trcqty;

	if( trcin == trcend )
		trcin = trcstm;

	if( trcqty >= RKH_TRC_SIZEOF_STREAM )
	{
		trcqty = RKH_TRC_SIZEOF_STREAM;
		trcout = trcin;
	}
}


rkhui8_t *
rkh_trc_get( void )
{
	rkhui8_t *tre = ( rkhui8_t* )0;

	if( trcqty == 0 )
		return tre;

	tre = trcout++;
	--trcqty;

	if( trcout >= trcend )
		trcout = trcstm;

	return tre;
}


#if RKH_TRC_RUNTIME_FILTER == 1
HUInt
rkh_trc_isoff_( rkhui8_t e )
{
	rkhui8_t evt, grp;

	evt = GETEVT( e );
	grp = GETGRP( e );
	return 	(( trcgfilter & rkh_maptbl[ grp ] ) == 0 ) &&
			(( trceftbl[ evt >> 3 ] & rkh_maptbl[ evt & 0x07 ]) == 0 );
#if 0
	return (( trcgfilter & (1<<grp) ) != 0 ) &&
				(( trceftbl[ e >> 3 ] & (1 << ( e&0x07 )) ) != 0 );
#endif
}


void 
rkh_trc_filter_group_( rkhui8_t ctrl, rkhui8_t grp, rkhui8_t mode )
{
	rkhui8_t *p, ix, c, offset, range;

	if( grp == RKH_TRC_ALL_GROUPS )
	{
		trcgfilter = (rkhui8_t)((ctrl == FILTER_ON) ? 0xFF : 0);
		return;
	}

	if( ctrl == FILTER_ON )
		trcgfilter |= rkh_maptbl[ grp ];
	else
		trcgfilter &= ~rkh_maptbl[ grp ];

	if( mode == ECHANGE )
	{
		offset = trcgmtbl[ grp ] >> 4;
		range = trcgmtbl[ grp ] & 0x0F;
		for( 	p = &trceftbl[ offset ], 
				ix = 0, 
				c = (rkhui8_t)((ctrl == FILTER_ON) ? 0xFF : 0); 
				ix < range; ++ix, ++p )
			*p = c;
	}
}


void 
rkh_trc_filter_event_( rkhui8_t ctrl, rkhui8_t evt )
{
	rkhui8_t *p, ix, c;

	if( evt == RKH_TRC_ALL_EVENTS )
	{
		for( 	p = trceftbl, 
				ix = 0, 
				c = (rkhui8_t)((ctrl == FILTER_ON) ? 0xFF : 0); 
				ix < RKH_TRC_MAX_EVENTS_IN_BYTES; ++ix, ++p )
			*p = c;
		return;
	}

	if( ctrl == FILTER_ON )
		trceftbl[ evt>>3 ] |= rkh_maptbl[ evt & 0x07 ];
	else
	{
		trceftbl[ evt>>3 ] &= ~rkh_maptbl[ evt & 0x07 ];
		trcgfilter &= ~rkh_maptbl[ GETGRP( evt ) ];
	}
}


HUInt
rkh_trc_sma_isoff_( rkhui8_t prio )
{
	if( prio == RKH_MAX_SMA )
		return 1;
	return (( trcsmaftbl[ prio >> 3 ] & rkh_maptbl[ prio & 0x07 ]) == 0 );
}


void 
rkh_trc_filter_sma_( rkhui8_t ctrl, rkhui8_t prio )
{
	rkhui8_t x, y;

	/* index into trcsmaftbl[ #RKH_TRC_MAX_SMA ] table */
	y = (rkhui8_t)(prio >> 3);
	/* bit position in trcsmaftbl[ Y's ] */
	x = (rkhui8_t)(prio & 0x07);

	if( ctrl == FILTER_ON )
		trcsmaftbl[ y ] |= rkh_maptbl[ x ];
	else
		trcsmaftbl[ y ] &= ~rkh_maptbl[ x ];
}
#endif


void
rkh_trc_begin( rkhui8_t eid )
{
	RKH_TRC_HDR( eid );
}


void
rkh_trc_end( void )
{
	RKH_TRC_CHK();
	RKH_TRC_FLG();
}


void 
rkh_trc_u8( rkhui8_t d )
{
	chk = (rkhui8_t)( chk + d );
	if( d == RKH_FLG || d == RKH_ESC )
	{
		rkh_trc_put( RKH_ESC );
		rkh_trc_put( (rkhui8_t)(d ^ RKH_XOR) );
	}
	else
		rkh_trc_put( d );
}


void 
rkh_trc_u16( rkhui16_t d )
{
	rkh_trc_u8( (rkhui8_t)d );
	d >>= 8;
	rkh_trc_u8( (rkhui8_t)d );
}


void 
rkh_trc_u32( rkhui32_t d )
{
	rkh_trc_u8( (rkhui8_t)d );
	d >>= 8;
	rkh_trc_u8( (rkhui8_t)d );
	d >>= 8;
	rkh_trc_u8( (rkhui8_t)d );
	d >>= 8;
	rkh_trc_u8( (rkhui8_t)d );
}


void 
rkh_trc_str( const char *s )
{
	while( *s != '\0' )
		rkh_trc_u8( (rkhui8_t)*s++ );
	rkh_trc_u8( '\0' );
}


void 
rkh_trc_fmt_u8( rkhui8_t fmt, rkhui8_t d )
{
	rkh_trc_u8( fmt );
	rkh_trc_u8( d );
}


void 
rkh_trc_fmt_u16( rkhui8_t fmt, rkhui16_t d )
{
	rkh_trc_u8( fmt );
	rkh_trc_u16( d );
}


void 
rkh_trc_fmt_u32( rkhui8_t fmt, rkhui32_t d )
{
	rkh_trc_u8( fmt );
	rkh_trc_u32( d );
}


void 
rkh_trc_fmt_str( const char *s )
{
	rkh_trc_u8( (rkhui8_t)RKH_STR_T );
	while( *s != '\0' )
		RKH_TRC_U8_RAW( (rkhui8_t)*s++ );
	rkh_trc_u8( '\0' );
}


void 
rkh_trc_fmt_mem( const rkhui8_t *mem, rkhui8_t size )
{
	rkh_trc_u8( (rkhui8_t)RKH_MEM_T );
    while( size != 0 )
	{
		rkh_trc_u8( (rkhui8_t)*mem++ );
        --size;
    }	
}


#endif
