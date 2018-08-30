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
 *  \file       rkhport.c
 *  \brief      Freescale CFV1 MCU's, CodeWarrior v6.3 port
 *
 *  \ingroup    port
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  DaBa  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhfwk_dynevt.h"

/* ----------------------------- Local macros ------------------------------ */
/* (1) Function macro defines */

/* ------------------------------- Constants ------------------------------- */
RKH_MODULE_NAME(rkhport)
RKH_MODULE_VERSION(rkhport, 1.00)
RKH_MODULE_DESC(rkhport, "Freescale ColdFire V1, CodeWarrior")

#define CFV1_INTERRUPT_MASK	0x2700

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static unsigned short crit_cnt = 0;
static unsigned short sr_mem;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
const
char *
rkhport_get_version(void)
{
    return RKH_MODULE_GET_VERSION();
}

const
char *
rkhport_get_desc(void)
{
    return RKH_MODULE_GET_DESC();
}

void
rkhport_enter_critical(void)
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
rkhport_exit_critical(void)
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

/* ------------------------------ File footer ------------------------------ */
