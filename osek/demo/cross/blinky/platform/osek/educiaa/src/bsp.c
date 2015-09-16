/**
 * \cond
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 * 	          State-machine framework for reactive embedded systems            
 * 	        
 * 	                    Copyright (C) 2010 Leandro Francucci.
 * 	        All rights reserved. Protected by international copyright laws.
 *
 *
 * 	RKH is free software: you can redistribute it and/or modify it under the 
 * 	terms of the GNU General Public License as published by the Free Software 
 * 	Foundation, either version 3 of the License, or (at your option) any 
 * 	later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY 
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along 
 *  with RKH, see copying.txt file.
 *
 * 	Contact information:
 * 	RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * 	e-mail:			francuccilea@gmail.com
 *
 *  --------------------------------------------------------------------------
 *  File                     : bsp.c
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		BSP for 80x86 OS win32
 */

#include "bsp.h"
#include "bky.h"
#include "rkh.h"

#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */

#define SERIAL_TRACE				1


RKH_THIS_MODULE

#if defined( RKH_USE_TRC_SENDER )
static rui8_t l_isr_tick;
#endif

static RKH_ROM_STATIC_EVENT( ev_term, TERMINATE );

#define BLINK_LED_MASK	0x20;
static int32_t fd_out;

static RKH_TS_T bsp_tstamp;

/* 
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1

	static int32_t utrc;
	#define TRACE_UART_FD	"/dev/serial/uart/1"
	#define TRACE_UART_BAUD	(void *)ciaaBAUDRATE_115200

	/* Trazer Tool COM Port */
	#define SERIAL_TRACE_OPEN()												\
				{															\
					utrc = ciaaPOSIX_open(TRACE_UART_FD, O_WRONLY); 		\
					ciaaPOSIX_ioctl(utrc, 									\
							ciaaPOSIX_IOCTL_SET_BAUDRATE, TRACE_UART_BAUD); \
					ActivateTask( RkhTraceTask );							\
				}

	#define SERIAL_TRACE_CLOSE() 						\
				{										\
					ciaaPOSIX_close( utrc ); 			\
				}

	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ ) 		\
				{										\
				   	ciaaPOSIX_write(utrc, buf_,	len_ );	\
				}
#else
	#define SERIAL_TRACE_OPEN()						(void)0
	#define SERIAL_TRACE_CLOSE()					(void)0
	#define SERIAL_TRACE_SEND( d )					(void)0
	#define SERIAL_TRACE_SEND_BLOCK( buf_, len_ )	(void)0
#endif


ALARMCALLBACK( TickHandler )
{
	RKH_TIM_TICK( &l_isr_tick );
	++bsp_tstamp;
}


void 
rkh_hook_start( void ) 
{
}


void 
rkh_hook_exit( void ) 
{
	RKH_TRC_FLUSH();
}


void 
rkh_assert( RKHROM char * const file, int line )
{
	ciaaPOSIX_printf( "RKH_ASSERT: [%d] line from %s "
						"file\n", line, file );
	RKH_DIS_INTERRUPT();
	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
/*	__debugbreak();*/
	rkh_fwk_exit();
}


static
void
print_banner( void )
{
	ciaaPOSIX_printf( "Blinky: a very simple state machine example.\n\n" );
	ciaaPOSIX_printf( "RKH version      = %s\n", RKH_RELEASE );
	ciaaPOSIX_printf( "Port version     = %s\n", rkh_get_port_version() );
	ciaaPOSIX_printf( "Port description = %s\n\n", rkh_get_port_desc() );
	ciaaPOSIX_printf( "Description: \n\n"
	 	"The goal of this demo application is to explain how to \n"
		"represent a \"flat\" state machine and how to use the timer \n"
		"services using the RKH framework. To do that is proposed a \n"
		"very simple demo that use one state machine and one timer, \n"
		"which is shown and explained in the reference manual section \n"
		"\"Examples\". "
		"This is the 'hello world' of RKH programming!.\n\n\n" );

	ciaaPOSIX_printf( "1.- Press ESC to quit \n\n\n" );
}


#if RKH_CFG_TRC_EN == 1

rui8_t trace_open;

void 
rkh_trc_open( void )
{
	trace_open = (rui8_t)1;
	rkh_trc_init();
	SERIAL_TRACE_OPEN()
	RKH_TRC_SEND_CFG( BSP_TS_RATE_HZ );
	RKH_TR_FWK_OBJ( &l_isr_tick );
}


void 
rkh_trc_close( void )
{
	trace_open = (rui8_t)0;
	SERIAL_TRACE_CLOSE();
}


RKH_TS_T 
rkh_trc_getts( void )
{
	return bsp_tstamp;
}


void 
rkh_trc_flush( void )
{
	rui8_t *blk;
	TRCQTY_T nbytes;
	RKH_SR_ALLOC();

	FOREVER
	{
		nbytes = 128;

		RKH_ENTER_CRITICAL_();
		blk = rkh_trc_get_block( &nbytes );
		RKH_EXIT_CRITICAL_();

		if((blk != (rui8_t *)0))
		{
			SERIAL_TRACE_SEND_BLOCK( blk, nbytes );
		}
		else
			break;
	}
}
#endif


void 
bsp_init( int argc, char *argv[] )
{
	(void)argc;
	(void)argv;

	rkh_fwk_init();

	fd_out = ciaaPOSIX_open("/dev/dio/out/0", O_RDWR);
	print_banner();

	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
	RKH_FILTER_OFF_EVENT( RKH_TE_TMR_TOUT );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
	RKH_FILTER_OFF_SMA( blinky );
	RKH_FILTER_OFF_ALL_SIGNALS();

	RKH_TRC_OPEN();
}


void 
bsp_led_on( void )
{
   uint8_t outputs;	

   /* write blinking message */
   ciaaPOSIX_printf("LED ON\n");
	
   /* set output on */
   ciaaPOSIX_read(fd_out, &outputs, 1);
   outputs |= BLINK_LED_MASK;
   ciaaPOSIX_write(fd_out, &outputs, 1);
}


void 
bsp_led_off( void )
{
   uint8_t outputs;	

   /* write blinking message */
   ciaaPOSIX_printf("LED OFF\n");
	
   /* set output off */
   ciaaPOSIX_read(fd_out, &outputs, 1);
   outputs &= ~BLINK_LED_MASK;
   ciaaPOSIX_write(fd_out, &outputs, 1);
}
