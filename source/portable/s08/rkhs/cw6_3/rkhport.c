/*
 *	file: rkht.h - Freescale ColdFire V1 MCU's, CodeWarrior port
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Mar 26, 2012
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
 * e-mail:			francuccilea@gmail.com
 */

/*
 * 	rkhport.c
 */


#include "rkh.h"
#include "bsp.h"


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "Freescale S08, CodeWarrior" )


const 
char *
rkh_get_port_version( void )
{
	return RKH_MODULE_GET_VERSION();
}


const 
char *
rkh_get_port_desc( void )
{
	return RKH_MODULE_GET_DESC();
}

static unsigned char ccr_sp_mem[ BSP_MAX_NESTING_CSECT ];
static unsigned int ccr_sp = (unsigned int)ccr_sp_mem;


void 
rkh_enter_critical( void )
{
	asm tpa;			/* transfer CCR to A */
	asm sei;			/* disable interrupts */
	asm ldhx ccr_sp;
	asm sta  ,x;		/* save old interrupt status */
	asm	aix	 #1;
	asm	sthx ccr_sp;

}


void 
rkh_exit_critical( void )
{
	asm ldhx ccr_sp;
	asm	aix	 #-1;
	asm	sthx ccr_sp;
	asm lda  ,x;		/* get old interrupt status */
	asm tap;			/* transfer A to CCR */
}
