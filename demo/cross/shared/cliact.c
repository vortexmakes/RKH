/*
 *	cliact.c
 */


#include "rkh.h"
#include "cli.h"
#include "svr.h"
#include "bsp.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define CLI_REQ_TIME		\
			(RKH_TNT_T)RKH_TIME_SEC( (bsp_rand() % 5) + 2 )
#define CLI_USING_TIME		\
			(RKH_TNT_T)RKH_TIME_SEC( (bsp_rand() % 5) + 1 )


static RKH_ROM_STATIC_EVENT( e_touse, TOUT_USING );
static RKH_ROM_STATIC_EVENT( e_toreq, TOUT_REQ );
static RKH_ROM_STATIC_EVENT( e_done, DONE );


/*
 *	Defines HSM init function
 */

void
cli_init( const struct RKH_SMA_T *sma )
{
	RKH_TMR_INIT( &RKH_CAST(CLI_T, sma)->cli_utmr, &e_touse, NULL );
	RKH_TMR_INIT( &RKH_CAST(CLI_T, sma)->cli_rtmr, &e_toreq, NULL );
}


/*
 *	Defines state entry functions
 */

void 
cli_pause( const struct RKH_SMA_T *sma )
{
	rkh_tmr_stop( &RKH_CAST(CLI_T, sma)->cli_rtmr );
	bsp_cli_paused( RKH_GET_PRIO(sma) );
}


void 
cli_delay_req( const struct RKH_SMA_T *sma )
{
	RKH_TNT_T time;

	time = CLI_REQ_TIME;
	RKH_TMR_ONESHOT( &RKH_CAST(CLI_T, sma)->cli_rtmr, sma, time );
	bsp_cli_wait_req( RKH_GET_PRIO(sma), time/BSP_TICKS_PER_SEC );
}


/*
 *	Defines state exit functions
 */

void 
cli_resume( const struct RKH_SMA_T *sma )
{
	bsp_cli_resumed( RKH_GET_PRIO(sma) );
}


/*
 *	Defines transition action functions
 */

void 
cli_req( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	REQ_EVT_T *e_req;

	(void)pe;
	e_req = RKH_ALLOC_EVT( REQ_EVT_T, REQ );
	e_req->clino = RKH_GET_PRIO(sma);
	RKH_SMA_POST_FIFO( svr, RKH_EVT_CAST(e_req), sma );
	bsp_cli_req( e_req->clino );
}


void 
cli_start( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	RKH_TNT_T time;

	(void)pe;
	time = CLI_USING_TIME;
	RKH_TMR_ONESHOT( &RKH_CAST(CLI_T, sma)->cli_utmr, sma, time );
	bsp_cli_using( RKH_CAST(START_EVT_T, pe)->clino, time/BSP_TICKS_PER_SEC );
}


void 
cli_end( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)pe;
	(void)sma;

	RKH_SMA_POST_FIFO( svr, &e_done, sma );
	bsp_cli_done( RKH_GET_PRIO(sma) );
}
