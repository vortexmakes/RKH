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
 *  \file       hook.c
 *  \brief      RKH hooks functions for 80x86 OS win32
 *
 *  \ingroup    bsp
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
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <pthread.h>
#include <sys/time.h>

#define _BSD_SOURCE
#include <unistd.h>

#include "rkh.h"
#include "bsp_common.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define BSP_TICKS_PER_SEC   		100

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static unsigned short tick_msec;
static struct termios orgt;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static int
mygetch(void)
{
    struct termios newt;
    int ch;

    tcgetattr(STDIN_FILENO, &orgt);
    newt = orgt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &orgt);
    return ch;
}

static void *
isr_tmrThread(void *d)
{
    (void)d;

    while (rkhport_fwk_is_running())
    {
        RKH_TIM_TICK(0);
        usleep(tick_msec);
    }
    pthread_exit(NULL);
    return NULL;    
}

static void *
isr_kbdThread(void *d) 
{
    (void)d;

    while (rkhport_fwk_is_running())
    {
        bsp_keyParser(mygetch());
    }
    return NULL;
}

/* ---------------------------- Global functions --------------------------- */
void
rkh_hook_start(void)
{
    pthread_t thtmr_id, thkbd_id;  /* thread identifiers */
    pthread_attr_t threadAttr;

    /* set the desired tick rate */
    tick_msec = 1000UL / BSP_TICKS_PER_SEC;

    /* initialize the thread attribute */
    pthread_attr_init(&threadAttr);

    /* Set the stack size of the thread */
    pthread_attr_setstacksize(&threadAttr, 1024);

    /* Create the threads */
    pthread_create(&thtmr_id, &threadAttr, isr_tmrThread, NULL);
    pthread_create(&thkbd_id, &threadAttr, isr_kbdThread, NULL);

    /* Destroy the thread attributes */
    pthread_attr_destroy(&threadAttr);
}

void
rkh_hook_exit(void)
{
    RKH_TRC_FLUSH();
    tcsetattr(STDIN_FILENO, TCSANOW, &orgt);
}

void
rkh_hook_timetick(void)
{
    bsp_timeTick();
}

void
rkh_hook_idle(void)             /* called within critical section */
{
    RKH_EXIT_CRITICAL(dummy);
    RKH_TRC_FLUSH();
    rkhport_wait_for_events();  /* yield the CPU until new event(s) arrive */
}

/* ------------------------------ File footer ------------------------------ */
