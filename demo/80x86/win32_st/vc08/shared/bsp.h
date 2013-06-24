/*
 *	file: bsp.h
 *	Last updated for version: 2.0
 *	Date of the last update:  Feb 28, 2012
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


#ifndef __BSP_H__
#define __BSP_H__


#include "rkh.h"


#define BSP_TICKS_PER_SEC   		RKH_TICK_RATE_HZ


void bsp_init( int argc, char *argv[] );
rkhui32_t bsp_rand( void );
void bsp_srand( rkhui32_t seed );
void bsp_wait_req( rkhui8_t clino, RKH_TNT_T req_time );
void bsp_req( rkhui8_t clino );
void bsp_using( rkhui8_t clino, RKH_TNT_T using_time );
void bsp_cli_paused( rkhui8_t clino );
void bsp_svr_paused( void );
void bsp_cli_resumed( rkhui8_t clino );
void bsp_cli_done( rkhui8_t clino );
void bsp_req_recalled( rkhui8_t clino );


#endif
