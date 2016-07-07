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
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhport.c
 *  \ingroup    prt
 *
 *  \brief      Freescale S08 MCU's, CodeWarrior v6.3 port
 *
 *  Long description and purpose of this file.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "bsp.h"

RKH_MODULE_NAME(rkhport)
RKH_MODULE_VERSION(rkhport, 1.00)
RKH_MODULE_DESC(rkhport, "Freescale S08, CodeWarrior")

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static unsigned char ccr_sp_mem[BSP_MAX_NESTING_CSECT];
static unsigned int ccr_sp = (unsigned int)ccr_sp_mem;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
const
char *
rkh_get_port_version(void)
{
    return RKH_MODULE_GET_VERSION();
}

const
char *
rkh_get_port_desc(void)
{
    return RKH_MODULE_GET_DESC();
}

void
rkh_enter_critical(void)
{
    asm tpa;            /* transfer CCR to A */
    asm sei;            /* disable interrupts */
    asm ldhx ccr_sp;
    asm sta,x;          /* save old interrupt status */
    asm aix  #1;
    asm sthx ccr_sp;
}

void
rkh_exit_critical(void)
{
    asm ldhx ccr_sp;
    asm aix  #- 1;
    asm sthx ccr_sp;
    asm lda,x;          /* get old interrupt status */
    asm tap;            /* transfer A to CCR */
}

/* ------------------------------ End of file ------------------------------ */
