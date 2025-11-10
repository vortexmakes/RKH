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
#include "PulseCounterMgr.h"
#include <stdint.h>
#include <stdio.h>

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define KEY_ESC 0x1B
#define KEY_A   0x61
#define KEY_S   0x73
#define KEY_0   0x30
#define KEY_1   0x31
#define KEY_2   0x32
#define KEY_3   0x33
#define KEY_4   0x34
#define KEY_5   0x35
#define KEY_6   0x36
#define KEY_7   0x37
#define KEY_8   0x38
#define KEY_9   0x39

typedef enum Order Order;
enum Order
{
    WAIT_ORDER, WAIT_ID
};

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */

/* Disclaimer: tt is not recommended to use a single instance to allocate an
 * event with varible arguments. However, this is a simple and demonstrative
 * example for educational purposes. In a professional project, use instances
 * allocated dinamically instead.
 */
static StatusEvt evStatus;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
printBanner(void)
{
    printf("Parameterized: a parameterized reactive Active Object\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkhport_get_version());
    printf("Port description = %s\n\n", rkhport_get_desc());
    printf("Description:\n");
    printf("This example demonstrates how to implement a parameterized \n");
    printf("reactive Active Object\n\n");
    printf("Press the following keys to stimulate this example:\n");
    printf("- 'a<pulse-counter-id>' to generate an evActive(id) event\n");
    printf("- 's<pulse-counter-id>' to generate an evInactive(id) event\n");
    printf("- ESC to quit\n\n");
}

static bool
isOrder(int c)
{
    return (c == KEY_A) || (c == KEY_S);
}

static bool
isId(int c)
{
    return (c >= KEY_0) && (c <= KEY_9);
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
    RKH_FILTER_OFF_SMA(pulseCounterMgr);
    RKH_FILTER_OFF_ALL_SIGNALS();
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_DCH);
    RKH_FILTER_OFF_EVENT(RKH_TE_SMA_FIFO);

    RKH_TRC_OPEN();
    RKH_SET_STATIC_EVENT(&evStatus, sigActive);
}

void
bsp_keyParser(int c)
{
    static Order state = WAIT_ORDER;
    static int lastOrder;

    switch (state)
    {
        case WAIT_ORDER:
            if (isOrder(c) == true)
            {
                lastOrder = c;
                state = WAIT_ID;
                printf("%s", (c == KEY_A) ? "a" : "s");
            }
            else if (c == KEY_ESC)
            {
                rkhport_fwk_stop();
            }
            break;
        case WAIT_ID:
            if (isOrder(c) == true)
            {
                lastOrder = c;
                printf("%d", c);
            }
            else if (isId(c) == true)
            {
                evStatus.id = c - '0';
                evStatus.evt.e =
                    (lastOrder == KEY_A) ? sigActive : sigInactive;
                RKH_SMA_POST_FIFO(pulseCounterMgr,
                        RKH_CAST_EVT(&evStatus),
                        m_name);
                state = WAIT_ORDER;
                int id = c - '0';
                if (lastOrder == KEY_A)
                {
                    printf("%d -> evActive(%d)\n", id, id);
                }
                else
                {
                    printf("%d -> evInactive(%d)\n", id, id);
                }
            }
            else if (c == KEY_ESC)
            {
                rkhport_fwk_stop();
            }
            else
            {
                state = WAIT_ORDER;
            }
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
