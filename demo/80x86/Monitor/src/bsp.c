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
#include "events.h"
#include "rkhevt.h"
#include "rkhitl.h"
#include "signals.h"
#include "rkh.h"
#include "rkhfwk_dynevt.h"
#include "rkhtrc_define.h"
#include "rkhtrc_filter.h"
#include "trace_io_cfg.h"
#include "Monitor.h"
#include <stdio.h>

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define KEY_ESC 0x1B
#define KEY_A   0x61
#define KEY_S   0x73
#define KEY_D   0x64

static const PushedButton evPushButton =
{
    .evt = RKH_INIT_STATIC_EVT(sigPushedButton),
    .which = KEY_A
};

static const Simulator evSimulator =
{
    {RKH_INIT_STATIC_EVT(sigSimulator), KEY_A},
    .additional = 0xdead
};

static const ADC evADC =
{
    .evt = RKH_INIT_STATIC_EVT(sigADC),
    .channel = 2,
    .value = 16
};

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
printBanner(void)
{
    printf("Monitor: a non-reactive Active Object\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkhport_get_version());
    printf("Port description = %s\n\n", rkhport_get_desc());
    printf("Description:\n");
    printf("This example demonstrates how to implement a non-reactive \n");
    printf("active object\n\n");
    printf("Press the following keys to stimulate this example:\n");
    printf("- 'a' to generate a PushedButton event\n");
    printf("- 's' to generate a Simulator event\n");
    printf("- 'd' to generate an ADC event\n");
    printf("- ESC to quit ");
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
    RKH_FILTER_OFF_SMA(monitor);
    RKH_FILTER_OFF_ALL_SIGNALS();
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_DCH);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_FIFO);

    RKH_TRC_OPEN();
}

void
bsp_keyParser(int c)
{
    switch (c)
    {
        case KEY_A:
            RKH_SMA_POST_FIFO(monitor, RKH_CAST_EVT(&evPushButton), m_name);
            break;
        case KEY_S:
            RKH_SMA_POST_FIFO(monitor, RKH_CAST_EVT(&evSimulator), m_name);
            break;
        case KEY_D:
            RKH_SMA_POST_FIFO(monitor, RKH_CAST_EVT(&evADC), m_name);
            break;
        case KEY_ESC:
            rkhport_fwk_stop();
            break;
        default:
            break;
    }
}

void
bsp_timeTick(void)
{
}

/* ------------------------------ File footer ------------------------------ */
