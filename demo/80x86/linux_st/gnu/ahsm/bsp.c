/**
 *  \file       bsp.c
 *  \brief      BSP for 80x86 OS Linux
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.12.06  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Darío Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */


#include "bsp.h"
#include "my.h"
#include "rkh.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <termios.h>
#include <sys/time.h>

/* ----------------------------- Local macros ------------------------------ */
#define BIN_TRACE				    0
#define SOCKET_TRACE				1
#define ESC							0x1B
#define kbmap( c )					( (c) - '0' )

/* ------------------------------- Constants ------------------------------- */
#define SIZEOF_EP0STO				64
#define SIZEOF_EP0_BLOCK			4
#define SIZEOF_EP1STO				32
#define SIZEOF_EP1_BLOCK			8

RKH_THIS_MODULE

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
rui8_t running;

/* ---------------------------- Local variables ---------------------------- */
static struct termios orgt;
static unsigned short tick_msec;			/* clock tick in msec */
static RKH_ROM_STATIC_EVENT( eterm, TERM );
static rui8_t ep0sto[ SIZEOF_EP0STO ],
				ep1sto[ SIZEOF_EP1STO ];
#if BIN_TRACE == 1      /* For binary trace feature */
static FILE *ftbin;
#endif

#if SOCKET_TRACE == 1    /* For socket trace feature */
	#include "tcptrc.h"

	/* Trazer Tool IP Address */
	#define TRC_IP_ADDR					"127.0.0.1"

	/* Trazer Tool TCP Port Address */
	#define TRC_TCP_PORT				6602

	/* Trace Socket */
	static int tsock;

	#define TCP_TRACE_OPEN() \
				if( tcp_trace_open( TRC_TCP_PORT, \
							TRC_IP_ADDR, &tsock ) < 0 ) \
				{ \
					printf( "Can't open socket %s:%u\n", \
								TRC_IP_ADDR, TRC_TCP_PORT ); \
					exit( EXIT_FAILURE ); \
				}
	#define TCP_TRACE_CLOSE() \
				tcp_trace_close( tsock )
	#define TCP_TRACE_SEND( d ) \
				tcp_trace_send( tsock, d )
#else
	#define TCP_TRACE_OPEN()		(void)0
	#define TCP_TRACE_CLOSE()		(void)0
	#define TCP_TRACE_SEND( d )		(void)0
#endif


#if BIN_TRACE == 1
	#define FTBIN_FLUSH( d )				\
				fwrite ( d, 1, 1, ftbin );	\
				fflush( ftbin )
	#define FTBIN_CLOSE() \
				fclose( ftbin )
	#define FTBIN_OPEN() \
				if( ( ftbin = fopen( "ftbin", "w+b" ) ) == NULL ) \
				{ \
					printf( "Can't open file\n" ); \
					exit( EXIT_FAILURE ); \
				}
#else
	#define FTBIN_FLUSH( d )		(void)0
	#define FTBIN_CLOSE()			(void)0
	#define FTBIN_OPEN()			(void)0
#endif

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void *
isr_tmr_thread( void *d )	/* thread to emulate timer ISR */
{
	(void)d;

    while( running ) 
	{
		RKH_TIM_TICK( 0 );
        usleep( tick_msec );
    }
	pthread_exit(NULL);
	return NULL;
}

static int 
mygetch( void )
{
	struct termios newt;
	int ch;

	tcgetattr( STDIN_FILENO, &orgt );
	newt = orgt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &orgt );
	return ch;
}

static void * 
isr_kbd_thread( void *d )	/* thread to emulate keyboard ISR */
{
	int c;
	MyEvt *mye;

	(void)d;
    while( running ) 
	{
		c = mygetch();
		
		if( c == ESC )
			RKH_SMA_POST_FIFO( my, &eterm, 0 );
		else
		{
			mye = RKH_ALLOC_EVT( MyEvt, kbmap( c ), 0 );
			mye->ts = ( rui16_t )rand();
			RKH_SMA_POST_FIFO( my, RKH_EVT_CAST(mye), 0 );
		}
    }
	return NULL;
}

static
void
print_banner( void )
{
	printf(	"Abstract Hierarchical State Machine (AHSM) example\n\n" );
	printf(	"RKH version      = %s\n", RKH_RELEASE );
	printf(	"Port version     = %s\n", rkh_get_port_version() );
	printf(	"Port description = %s\n\n", rkh_get_port_desc() );
	printf(	"Description: \n\n"
			"The goal of this demo application is to explain how to \n"
			"represent a state machine using the RKH framework. To do \n"
			"that is proposed a simple and abstract example, which is \n"
			"shown in the documentation file Figure 1 section \n"
			"\"Representing a State Machine\". \n\n\n" );

	printf( "1.- Press <numbers> to send events to state machine. \n" );
	printf( "2.- Press ESC to quit \n\n\n" );
}

/* ---------------------------- Global functions --------------------------- */
void 
rkh_hook_start( void ) 
{
	pthread_t thtmr_id, thkbd_id;  /* thread identifiers */
 	pthread_attr_t threadAttr;

	/* set the desired tick rate */
    tick_msec = 1000UL/BSP_TICKS_PER_SEC;
    running = (rui8_t)1;

	/* initialize the thread attribute */
	pthread_attr_init(&threadAttr);

	/* Set the stack size of the thread */
	pthread_attr_setstacksize(&threadAttr, 1024);

	/* Create the threads */
	pthread_create(&thtmr_id, &threadAttr, isr_tmr_thread, NULL);
	pthread_create(&thkbd_id, &threadAttr, isr_kbd_thread, NULL);

	/* Destroy the thread attributes */
	pthread_attr_destroy(&threadAttr);
	
	rkh_fwk_epool_register( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
	rkh_fwk_epool_register( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
}

void 
rkh_hook_exit( void ) 
{
	RKH_TRC_FLUSH();
    running = 0;
	tcsetattr( STDIN_FILENO, TCSANOW, &orgt );
}

void 
rkh_hook_idle( void )				/* called within critical section */
{
    RKH_EXIT_CRITICAL( dummy );
	RKH_TRC_FLUSH();
    RKH_WAIT_FOR_EVENTS();		/* yield the CPU until new event(s) arrive */
}

void 
rkh_hook_timetick( void ) 
{
}

void 
rkh_assert( RKHROM char * const file, int line )
{
	fprintf( stderr,	"RKH_ASSERT: [%d] line from %s "
						"file\n", line, file );
	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
	rkh_fwk_exit();
}

#if RKH_CFG_TRC_EN == 1
void 
rkh_trc_open( void )
{
	rkh_trc_init();

	FTBIN_OPEN();
	TCP_TRACE_OPEN();
	RKH_TRC_SEND_CFG( BSP_TS_RATE_HZ );
}

void 
rkh_trc_close( void )
{
	FTBIN_CLOSE();
	TCP_TRACE_CLOSE();
}

RKH_TS_T 
rkh_trc_getts( void )
{
	struct timeval tv;   /* see gettimeofday(2) */
	double t;

	gettimeofday(&tv, NULL);
	t = (double) tv.tv_sec + (double) 1e-6 * tv.tv_usec; 
	return ( RKH_TS_T )t;
}

void 
rkh_trc_flush( void )
{
	rui8_t *d;

	while( ( d = rkh_trc_get() ) != ( rui8_t* )0 )
	{
		FTBIN_FLUSH( d );
		TCP_TRACE_SEND( *d );		
	}
}
#endif

void 
bsp_init( int argc, char *argv[] )
{
	(void)argc;
	(void)argv;

	srand( ( unsigned )time( NULL ) );
	print_banner();
    rkh_fwk_init();

    /* set trace filters */
    RKH_FILTER_ON_GROUP(RKH_TRC_ALL_GROUPS);
    RKH_FILTER_ON_EVENT(RKH_TRC_ALL_EVENTS);
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_SM);
    RKH_FILTER_OFF_SMA(my);

    RKH_TRC_OPEN();
}

/* ------------------------------ End of file ------------------------------ */
