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
 *  \file       bsp.c
 *  \brief      BSP for 80x86 OS Linux
 */

/* -------------------------- Development history -------------------------- */
/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 *  CaMa  Carlos Mancón      manconci@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "bsp.h"
#include "rkh.h"
#include "trace_io_cfg.h"
#include "SignalMgr.h"
#include <stdio.h>

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define ESC  0x1B

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
printBanner(void)
{
    printf("SignalMgr: set of periodic Active Objects\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkhport_get_version());
    printf("Port description = %s\n\n", rkhport_get_desc());
    printf("Description:\n");
    printf("The following examples demonstrates how to \n");
    printf("implement different kinds of special Active Objects:\n"
           "- variant1: periodic non-reactive using synchronous state machine\n"
           "- variant2: periodic reactive\n"
           "- variant3: periodic reactive using orthogonal regions\n"
           "- variant4: periodic non-reactive\n\n");
    printf("Press ESC to quit ");
}

/* ---------------------------- Global functions --------------------------- */
void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    printBanner();

    trace_io_setConfig(argc, argv);

    rkh_fwk_init();

    RKH_FILTER_ON_GROUP(RKH_TRC_ALL_GROUPS);
    RKH_FILTER_ON_EVENT(RKH_TRC_ALL_EVENTS);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_SMA(signalMgr);
    RKH_FILTER_OFF_ALL_SIGNALS();
    RKH_FILTER_OFF_EVENT(USRT_ACTOUT);

    RKH_TRC_OPEN();
    RKH_TR_FWK_TUSR(USRT_ACTOUT);
}

void
bsp_keyParser(int c)
{
    if (c == ESC)
    {
        rkhport_fwk_stop();
    }
}

void
bsp_timeTick(void)
{
}

/* ------------------------------ File footer ------------------------------ */
