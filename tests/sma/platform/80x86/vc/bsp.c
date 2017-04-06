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
 *  \file       bsp.c
 *  \ingroup    Test
 *
 *  \brief      BSP for 80x86 OS win32
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.11.19  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <conio.h>

#if RKH_CFG_TRC_EN == RKH_ENABLED
#include <time.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>        /* Win32 API for multithreading */
#endif

#include "unity.h"
#include "bsp.h"
#include "rkh.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
RKH_THIS_MODULE
rui8_t running;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
unitrazer_resetOut(void)
{
}

void
rkh_hook_idle(void)             /* called within critical section */
{
    RKH_EXIT_CRITICAL(dummy);
}

#if RKH_CFG_TRC_EN == RKH_ENABLED
void
rkh_trc_open(void)
{
    rkh_trc_init();
}

void
rkh_trc_close(void)
{
}

RKH_TS_T
rkh_trc_getts(void)
{
    return (RKH_TS_T)0x01234567;
}

void
rkh_trc_flush(void)
{
}
#endif

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    rkh_fwk_init();
}

/* ------------------------------ End of file ------------------------------ */
