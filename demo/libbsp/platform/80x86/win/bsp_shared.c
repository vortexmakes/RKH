/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       bsp_shared.c
 *  \brief      BSP for 80x86 OS win32
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <stdio.h>

#include "shared.h"
#include "server.h"
#include "client.h"
#include "bsp.h"
#include "rkh.h"
#include "trace_io_cfg.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
#define kbmap( c )					( (c) - '0' )

/* ------------------------------- Constants ------------------------------- */
#define ESC							0x1B

#define SIZEOF_EP0STO				32
#define SIZEOF_EP0_BLOCK			sizeof( RKH_EVT_T )
#define SIZEOF_EP1STO				16
#define SIZEOF_EP1_BLOCK			sizeof( ReqEvt )
#define SVR_NAME					"Server    -"
#define CLI_NAME					"Client"

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static rui32_t l_rnd;			/* random seed */
static DWORD tick_msec;			/* clock tick in msec */

static RKH_ROM_STATIC_EVENT( e_term, TERM );
static RKH_ROM_STATIC_EVENT( e_pause, PAUSE );

static rui8_t ep0sto[ SIZEOF_EP0STO ],
				ep1sto[ SIZEOF_EP1STO ];

#if defined( RKH_USE_TRC_SENDER )
static rui8_t l_isr_kbd;
static rui8_t l_isr_tick;
#endif

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
void
publish( const RKH_EVT_T *e )
{
	rInt cn;

	RKH_SMA_POST_FIFO( server, e, &l_isr_kbd );			/* to server */

	for( cn = 0; cn < NUM_CLIENTS; ++cn )				/* to clients */
		RKH_SMA_POST_FIFO( CLI(cn), e, &l_isr_kbd );
}

static
void
printBanner( void )
{
	printf(	"\"Shared\" example\n\n" );
	printf(	"RKH version      = %s\n", RKH_RELEASE );
	printf(	"Port version     = %s\n", rkhport_get_version() );
	printf(	"Port description = %s\n\n", rkhport_get_desc() );
	printf(	"Description: \n\n" );
	printf(	"This application deals with the shared resource problem \n" );
	printf(	"in active object systems. Showing one of the biggest \n" );
	printf(	"benefit of using active objects: resource encapsulation. \n" );
	printf(	"The encapsulation naturally designates the owner of the \n" );
	printf(	"resource as the ultimate arbiter in resolving any contention \n" );
	printf(	"and potential conflicts for the resource. \n" );
	printf(	"The SHD application is relatively simple and can be tested \n" );
	printf(	"only with a couple of LEDs on your target board. \n" );
	printf(	"Still, SHD contains five (5) concurrent active objects \n" );
	printf(	"that exchange events via direct event posting mechanism. \n" );
	printf(	"The application uses four timers, as well as dynamic  \n" );
	printf(	"and static events. \n" );
	printf(	"On the other hand, this application could be used in either \n" );
	printf(	"preemptive or cooperative enviroment. \n" );
	printf(	"Aditionally, the SHD could be used to verify a new RKH port. \n" );
	printf(	"\n\n\n" );

	printf( "1.- Press 'P'/'p' to pause.\n" );
	printf( "2.- Press 'escape' to quit.\n\n\n" );
}

/* ---------------------------- Global functions --------------------------- */
rui32_t 
bsp_rand( void )
{  
	/* 
	 * A very cheap pseudo-random-number generator.
	 * "Super-Duper" Linear Congruential Generator (LCG)
	 * LCG(2^32, 3*7*11*13*23, 0, seed) [MS]
	 */
    l_rnd = l_rnd * (3*7*11*13*23);
    return l_rnd >> 8;
}

/* ------------------------------ File footer ------------------------------ */


void 
bsp_srand( rui32_t seed )
{
    l_rnd = seed;
}


void 
bsp_cli_wait_req( rui8_t clino, RKH_TNT_T req_time )
{
	printf( "Client[%d] - Waiting for send request to server (%d seg)\n", 
									CLI_ID(clino), req_time );
}


void 
bsp_cli_req( rui8_t clino )
{
	printf( "Client[%d] - Send request to server...\n", CLI_ID(clino) );
}


void 
bsp_cli_using( rui8_t clino, RKH_TNT_T using_time )
{
	printf( "Client[%d] - Using server for %d [seg]\n", 
									CLI_ID(clino), using_time );
}


void 
bsp_cli_paused( rui8_t clino )
{
	printf( "Client[%d] - Paused\n", CLI_ID(clino) );
}


void 
bsp_cli_resumed( rui8_t clino )
{
	printf( "Client[%d] - Resumed\n", CLI_ID(clino) );
}


void 
bsp_cli_done( rui8_t clino )
{
	printf( "Client[%d] - Done\n", CLI_ID(clino) );
}


void 
bsp_svr_recall( rui8_t clino )
{
	printf( "%s Recall a deferred request from client[%d]\n", 
									SVR_NAME, CLI_ID(clino) );
}


void 
bsp_svr_paused(rui32_t ntot, rui32_t *ncr)
{
	rInt cn;
    rui32_t *pNcr;

	printf( "Server paused | ");
	printf( "ntot = %d |", ntot );

	for(pNcr = ncr, cn = 0; cn < NUM_CLIENTS; ++cn, ++pNcr )
		printf( " cli%d=%d |", cn, *pNcr );

	putchar('\n');
}


void 
bsp_svr_start( rui8_t clino )
{
	printf( "%s Busy (client[%d])\n", SVR_NAME, CLI_ID(clino) );
}


void 
bsp_svr_end( void )
{
	printf( "%s Released\n", SVR_NAME );
}


void 
bsp_svr_resume( void )
{
	printf( "%s Resumed\n", SVR_NAME );
}


void 
bsp_init( int argc, char *argv[] )
{
	rInt cn;

	(void)argc;
	(void)argv;

    bsp_srand( 1234U );
	printBanner();

    trace_io_setConfig(argc, argv);

	rkh_fwk_init();

	RKH_FILTER_OFF_SMA( server );
	for( cn = 0; cn < NUM_CLIENTS; ++cn )
		RKH_FILTER_OFF_SMA( CLI(cn) );

	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_FIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_LIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_DCH );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
	RKH_FILTER_OFF_ALL_SIGNALS();

	RKH_TRC_OPEN();

#if defined( RKH_USE_TRC_SENDER )
	RKH_TR_FWK_OBJ( &l_isr_kbd );
	RKH_TR_FWK_OBJ( &l_isr_tick );
#endif

    rkh_fwk_registerEvtPool( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
	rkh_fwk_registerEvtPool( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
}


void
bsp_keyParser(int c)
{
    if( c == ESC )
		RKH_SMA_POST_FIFO( server, &e_term, &l_isr_kbd );
	else if( tolower(c) == 'p' )
		publish( &e_pause );
}

void
bsp_timeTick( void )
{
}



