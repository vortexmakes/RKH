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


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "Freescale Coldfire V1, CodeWarrior" )


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


#define CFV1_INTERRUPT_MASK	0x2700


static unsigned short crit_cnt = 0;
static unsigned short sr_mem;


void 
rkh_enter_critical( void )
{
	asm
	{
		move.w	crit_cnt,d0
		addq.l	#1,d0
		move.w	d0,crit_cnt
		cmpi.w	#1,d0
		bhi.s	end

		save:
		move.w	sr,d0
		move.w	d0,sr_mem
		move.w	#CFV1_INTERRUPT_MASK,d0
		move.w	d0,sr
		end:
	}
}


void 
rkh_exit_critical( void )
{
	asm
	{
		tst.w	crit_cnt
		beq.s	restore
		move.w	crit_cnt,d0
		subq.l	#1,d0
		move.w	d0,crit_cnt
		bne.s	end

		restore: 
		move.w	sr_mem,d0
		move.w	d0,sr
		end:
	}
}


