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
 *  \file       bsp_ahsm.c
 *  \brief      BSP for 80x86 OS win32
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <stdio.h>

#include "my.h"
#include "bsp.h"
#include "rkh.h"
#include "trace_io_cfg.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define ESC                         0x1B
#define kbmap(c)                    ((c) - '0')

#define SIZEOF_EP0STO               64
#define SIZEOF_EP0_BLOCK            4
#define SIZEOF_EP1STO               32
#define SIZEOF_EP1_BLOCK            8

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT(evTerm, TERM);

static rui8_t ep0sto[SIZEOF_EP0STO],
              ep1sto[SIZEOF_EP1STO];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
printBanner(void)
{
    printf("Abstract Hierarchical State Machine (AHSM) example\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkhport_get_version());
    printf("Port description = %s\n\n", rkhport_get_desc());
    printf("Description: \n\n"
           "The goal of this demo application is to explain how to \n"
           "represent a state machine using the RKH framework. To do \n"
           "that is proposed a simple and abstract example, which is \n"
           "shown in the documentation file Figure 1 section \n"
           "\"Representing a State Machine\". \n\n\n");

    printf("1.- Press <numbers> to send events to state machine. \n");
    printf("2.- Press ESC to quit \n\n\n");

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
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_SM);
    RKH_FILTER_OFF_SMA(my);

    RKH_TRC_OPEN();

    rkh_fwk_registerEvtPool( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
	rkh_fwk_registerEvtPool( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
}

void
bsp_keyParser(int c)
{
    MyEvt *mye;

    if (c == ESC)
    {
        RKH_SMA_POST_FIFO(my, &evTerm, 0);
    }
    else
    {
        mye = RKH_ALLOC_EVT(MyEvt, kbmap(c), 0);
        mye->ts = (rui16_t)rand();
        RKH_SMA_POST_FIFO(my, RKH_EVT_CAST(mye), 0);
    }
}

void
bsp_timeTick(void)
{
}

/* ------------------------------ File footer ------------------------------ */
