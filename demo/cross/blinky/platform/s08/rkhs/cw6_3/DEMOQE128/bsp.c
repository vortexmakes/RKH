/*
 *	file: bsp.c
 *	Last updated for version: 2.3
 *	Date of the last update:  Mar 12, 2013
 *
 * 	Copyright (C) 2010 Leandro Francucci. All rights reserved.
 *
 * 	RKH is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 *  RKH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RKH, see copying.txt file.
 *
 * Contact information:
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			lf@vxtsolutions.com.ar
 */


#include "bsp.h"
#include "bky.h"
#include "rkh.h"

#include "mcu.h"
#include "gpio.h"
#include "serial.h"


#define SERIAL_TRACE			1


RKH_THIS_MODULE

				
/*
 * 	For serial trace feature.
 */

#if SERIAL_TRACE == 1

	/* Trazer Tool COM Port */
	#define TRC_COM_PORT		COM1	

	#define SERIAL_TRACE_OPEN()		serial_init( TRC_COM_PORT )
	#define SERIAL_TRACE_CLOSE() 	(void)0
	#define SERIAL_TRACE_SEND( d ) 	put_char( TRC_COM_PORT, d )
#else
	#define SERIAL_TRACE_OPEN()		(void)0
	#define SERIAL_TRACE_CLOSE()	(void)0
	#define SERIAL_TRACE_SEND( d )	(void)0
#endif


void 
rkh_hk_start( void ) 
{
}


void 
rkh_hk_exit( void ) 
{
	RKH_TRC_FLUSH();
}


void 
rkh_hk_idle( void )				/* called within critical section */
{
	RKH_ENA_INTERRUPT();
	RKH_TRC_FLUSH();
}


void 
rkh_assert( RKHROM char * const file, int line )
{
	(void)line;

	RKH_TR_FWK_ASSERT( (RKHROM char *)file, __LINE__ );
	rkh_exit();
	reset_now();
}


#if RKH_TRC_EN == 1

void 
rkh_trc_open( void )
{
	rkh_trc_init();
	SERIAL_TRACE_OPEN();
}


void 
rkh_trc_close( void )
{
	SERIAL_TRACE_CLOSE();
}


RKHTS_T 
rkh_trc_getts( void )
{
	return ( RKHTS_T )get_ts();
}


void 
rkh_trc_flush( void )
{
	rkhui8_t *d;

	while( ( d = rkh_trc_get() ) != ( rkhui8_t* )0 )
	{
		SERIAL_TRACE_SEND( *d );		
	}
}
#endif


void 
bsp_init( int argc, char *argv[]  )
{
	(void)argc;
	(void)argv;
	
	mcu_init( RKH_TICK_RATE_MS );

	gpio_init();

	RKH_ENA_INTERRUPT();
}


void 
bsp_led_on( void )
{
	set_iopin( LED1, PIN_LOW );
}


void 
bsp_led_off( void )
{
	set_iopin( LED1, PIN_HIGH );
}

