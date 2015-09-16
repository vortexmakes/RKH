/*
 *	svract.c
 */


#include "rkh.h"
#include "svr.h"
#include "cli.h"
#include "bsp.h"


#define MAX_SIZEOF_QREQ				2*NUM_CLIENTS


static RKH_RQ_T qreq;
static RKH_EVT_T *qreq_sto[ MAX_SIZEOF_QREQ ];


/*
 *	Defines HSM init function
 */

void 
svr_init( const struct RKH_SMA_T *sma )
{
	rint cn;

	(void)sma;
	rkh_rq_init( &qreq, (const void **)qreq_sto, MAX_SIZEOF_QREQ, CSMA(0) );

	RKH_CAST(SVR_T, sma)->ntot = 0;
	for( cn = 0; cn < NUM_CLIENTS; ++cn )
		RKH_CAST(SVR_T, sma)->ncr[ cn ] = 0;
}


/*
 *	Defines state entry functions
 */

void 
svr_pause( const struct RKH_SMA_T *sma )
{
	(void)sma;
	bsp_svr_paused( sma );
}


/*
 *	Defines state exit functions
 */

void 
svr_resume( const struct RKH_SMA_T *sma )
{
	REQ_EVT_T *e;

	if( (e = (REQ_EVT_T *)rkh_fwk_recall( (RKH_SMA_T*)sma, &qreq )) 
			!= (REQ_EVT_T *)0 )
		bsp_svr_recall( e->clino );
	
	bsp_svr_resume();
}


/*
 *	Defines transition action functions
 */

void 
svr_start( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	START_EVT_T *e_start;

	e_start = RKH_ALLOC_EVT( START_EVT_T, START );
	e_start->clino = RKH_CAST(REQ_EVT_T, pe)->clino;
	bsp_svr_start(e_start->clino);
	++RKH_CAST(SVR_T, sma)->ntot;
	++RKH_CAST(SVR_T, sma)->ncr[ CLI_ID(e_start->clino) ];
	RKH_SMA_POST_FIFO( RKH_GET_SMA( RKH_CAST(REQ_EVT_T, pe)->clino ), 
												RKH_EVT_CAST(e_start), sma );
}


void 
svr_end( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	REQ_EVT_T *e;

	(void)pe;
	if( (e = (REQ_EVT_T *)rkh_fwk_recall( (RKH_SMA_T*)sma, &qreq )) 
			!= (REQ_EVT_T *)0 )
		bsp_svr_recall( e->clino );

	bsp_svr_end();
}


void 
svr_defer( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	rkh_fwk_defer( &qreq, pe );
}


void 
svr_terminate( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;

	rkh_fwk_exit();
}
