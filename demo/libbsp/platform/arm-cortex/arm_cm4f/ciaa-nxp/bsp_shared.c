/* ------------------------------ File header ------------------------------ */
/*  Use file_header.txt file                                                 */

/* -------------------------- Development history -------------------------- */
/*
 *  2020.06.10  CaMa  v1.0.0  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  CaMa  Carlos Mancón  manconci@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/*
 *  (1) These notes could be referenced by number.
 *      (1.1) Sub-note.
 *  (2) Another note.
 */

/* ----------------------------- Include files ----------------------------- */
/* (1) #include <string.h>                                                   */
/* (2) #include <other system headers>                                       */
/* (3) #include �user header files�                                          */
#include "rkh.h"
#include "bsp.h"
#include "server.h"
#include "client.h"
#include "shared.h"
#include "board.h"

/* ----------------------------- Local macros ------------------------------ */
/* (1) Function macro defines */

/* ------------------------------- Constants ------------------------------- */
/* (1) Macro defines                                                         */
/* (2) Enumerations                                                          */
/* (3) Local const modifier                                                  */
/* (4) Global (extern or non-static external const modifier)                 */

/* ---------------------------- Local data types --------------------------- */
/* (1) typedefs                                                              */

/* ---------------------------- Global variables --------------------------- */
/* (1) Extern declarations of variables defined in other files.              */
/* (2) Non-static external definitions used in this file (and optionally     */
/*     in others if they are declared in those files using extern).          */

/* ---------------------------- Local variables ---------------------------- */
/* (1) Static external definitions used only in this file.                   */
static RKH_TS_T tstamp;
static rui32_t l_rnd;				/* random seed */

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */

static
void
print_banner( void )
{
//TODO
#ifdef PRINTF
	PRINTF(	"\"Shared\" example\n\n" );
	PRINTF(	"RKH version      = %s\n", RKH_RELEASE );
	PRINTF(	"Port version     = %s\n", rkhport_get_version() );
	PRINTF(	"Port description = %s\n\n", rkhport_get_desc() );
	PRINTF(	"Description: \n\n" );
	PRINTF(	"This application deals with the shared resource problem \n" );
	PRINTF(	"in active object systems. Showing one of the biggest \n" );
	PRINTF(	"benefit of using active objects: resource encapsulation. \n" );
	PRINTF(	"The encapsulation naturally designates the owner of the \n" );
	PRINTF(	"resource as the ultimate arbiter in resolving any contention \n" );
	PRINTF(	"and potential conflicts for the resource. \n" );
	PRINTF(	"The SHD application is relatively simple and can be tested \n" );
	PRINTF(	"only with a couple of LEDs on your target board. \n" );
	PRINTF(	"Still, SHD contains five (5) concurrent active objects \n" );
	PRINTF(	"that exchange events via direct event posting mechanism. \n" );
	PRINTF(	"The application uses four timers, as well as dynamic  \n" );
	PRINTF(	"and static events. \n" );
	PRINTF(	"On the other hand, this application could be used in either \n" );
	PRINTF(	"preemptive or cooperative enviroment. \n" );
	PRINTF(	"Aditionally, the SHD could be used to verify a new RKH port. \n" );
	PRINTF(	"\n\n\n" );

	PRINTF( "1.- Each Client have your own color, Client 1-4:\n" );
	PRINTF( "	   	RED, GREEN, BLUE, YELLOW\n" );
	PRINTF( "2.- Press SW2 to PAUSE.\n" );
	PRINTF( "3.- Paused state is shown with a WHITE in RGB led\n." );
#endif
}

/* ---------------------------- Global functions --------------------------- */

void
bsp_init(int argc, char *argv[])
{
	rInt cn;

	(void)argc;
	(void)argv;

	SystemCoreClockUpdate();

	Board_Init();

	bsp_srand( 1234U );
	print_banner();
	rkh_fwk_init();

	RKH_FILTER_OFF_SMA( server );
	for( cn = 0; cn < NUM_CLIENTS; ++cn )
		RKH_FILTER_OFF_SMA( CLI(cn) );

	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_FIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SMA_LIFO );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_DCH );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
	/*RKH_FILTER_OFF_ALL_SIGNALS();*/
	RKH_FILTER_OFF_SIGNAL( REQ );
	RKH_FILTER_OFF_SIGNAL( START );

	RKH_TRC_OPEN();
}

void
bsp_keyParser(int c)
{

}

void
bsp_timeTick(void)
{
    ++tstamp;
}

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

void
bsp_srand( rui32_t seed )
{
    l_rnd = seed;
}

void
bsp_cli_req( rui8_t clino )
{
#ifdef PRINTF
	PRINTF( "Client[%d] - Send request to server...\n", CLI_ID(clino) );
#endif
}

void
bsp_cli_wait_req( rui8_t clino, RKH_TNT_T req_time )
{
#ifdef PRINTF
	PRINTF( "Client[%d] - Waiting for send request to server (%d seg)\n",
									CLI_ID(clino), req_time );
#endif
}

void
bsp_cli_using( rui8_t clino, RKH_TNT_T using_time )
{
#ifdef PRINTF
	PRINTF( "Client[%d] - Using server for %d [seg]\n",
									CLI_ID(clino), using_time );
#endif
//TODO	set_rgb_led( bsp_led_colors[clino] );
}

void
bsp_cli_paused( rui8_t clino )
{
#ifdef PRINTF
	PRINTF( "Client[%d] - Paused\n", CLI_ID(clino) );
#endif
//TODO	set_rgb_led( RGB_WHITE );
}

void
bsp_cli_resumed( rui8_t clino )
{
#ifdef PRINTF
	PRINTF( "Client[%d] - Resumed\n", CLI_ID(clino) );
#endif
}

void
bsp_cli_done( rui8_t clino )
{
#ifdef PRINTF
	PRINTF( "Client[%d] - Done\n", CLI_ID(clino) );
#endif
//TODO	set_rgb_led( RGB_BLACK );
}

void
bsp_svr_recall( rui8_t clino )
{
#ifdef PRINTF
	PRINTF( "%s Recall a deferred request from client[%d]\n",
									SVR_NAME, CLI_ID(clino) );
#endif
}

void
bsp_svr_paused(rui32_t ntot, rui32_t *ncr)
{
	rInt cn;
    rui32_t *pNcr;
#ifdef PRINTF
	PRINTF( "Server paused | ");
	PRINTF( "ntot = %d |", ntot );

	for(pNcr = ncr, cn = 0; cn < NUM_CLIENTS; ++cn, ++pNcr )
		PRINTF( " cli%d=%d |", cn, *pNcr );

	PUTCHAR('\n');
#endif
}

void
bsp_svr_start( rui8_t clino )
{
	(void)0;
}

void
bsp_svr_end( void )
{

}

void
bsp_svr_resume( void )
{

}

/* ------------------------------ File footer ------------------------------ */
/*  Use file_footer.txt file                                                 */
