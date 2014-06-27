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
svr_init( const struct rkhsma_t *sma )
{
	HInt cn;

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
svr_pause( const struct rkhsma_t *sma )
{
	(void)sma;
	bsp_svr_paused( sma );
}


/*
 *	Defines state exit functions
 */

void 
svr_resume( const struct rkhsma_t *sma )
{
	REQ_EVT_T *e;

	if( (e = (REQ_EVT_T *)rkh_recall( (RKH_SMA_T*)sma, &qreq )) 
			!= (REQ_EVT_T *)0 )
		bsp_svr_recall( e->clino );
}


/*
 *	Defines transition action functions
 */

void 
svr_start( const struct rkhsma_t *sma, RKH_EVT_T *pe )
{
	START_EVT_T *e_start;

	e_start = RKH_ALLOC_EVENT( START_EVT_T, START );
	e_start->clino = RKH_CAST(REQ_EVT_T, pe)->clino;
	RKH_SMA_POST_FIFO( RKH_GET_SMA( RKH_CAST(REQ_EVT_T, pe)->clino ), 
												RKH_EVT_CAST(e_start), sma );
	++RKH_CAST(SVR_T, sma)->ntot;
	++RKH_CAST(SVR_T, sma)->ncr[ CLI_ID(e_start->clino) ];
}


void 
svr_end( const struct rkhsma_t *sma, RKH_EVT_T *pe )
{
	REQ_EVT_T *e;

	(void)pe;
	if( (e = (REQ_EVT_T *)rkh_recall( (RKH_SMA_T*)sma, &qreq )) 
			!= (REQ_EVT_T *)0 )
		bsp_svr_recall( e->clino );
}


void 
svr_defer( const struct rkhsma_t *sma, RKH_EVT_T *pe )
{
	(void)sma;
	rkh_defer( &qreq, pe );
}


void 
svr_terminate( const struct rkhsma_t *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;

	rkh_exit();
}
