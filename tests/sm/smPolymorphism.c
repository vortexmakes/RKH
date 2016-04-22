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
 *  \file       smPolymorphism.c
 *  \brief      Helper functions and object defines to facilitate the test of
 *              production code.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.12.15  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "smPolymorphism.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
typedef struct Singleton Singleton;
struct Singleton
{
    RKH_SMA_T base;
    int foo;
};

struct Multiple
{
    RKH_SMA_T base;
    MultipleVtbl vtbl;
    int foobar;
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
RKH_SMA_CREATE(Singleton, singleton, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR(singleton);

RKH_SMA_CREATE(Multiple, multA, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(Multiple, multA);

RKH_SMA_CREATE(Multiple, multB, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(Multiple, multB);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
Singleton_activate(RKH_SMA_T *me, const RKH_EVT_T **qSto, RKH_RQNE_T qSize,
                void *stkSto, rui32_t stkSize)
{
    int var = 0;

    if (me->vptr->task != (void(*)(RKH_SMA_T *, void *))0)
        me->vptr->task(me, &var);
}

static void
Singleton_task(RKH_SMA_T *me, void *arg)
{
    RKH_DOWNCAST(Singleton, me)->foo = *((int *)arg);
}

static void
Multiple_toggle(Multiple *me)
{
    me->foobar = (int)((me->foobar & 1u) == 0);
}

/* ---------------------------- Global functions --------------------------- */
void
Singleton_ctor(int foo)
{
    static const RKHSmaVtbl vtbl =
    {
        Singleton_activate,
        Singleton_task,
        rkh_sma_post_fifo,
        rkh_sma_post_lifo
    };

    singleton->vptr = &vtbl;
    RKH_DOWNCAST(Singleton, singleton)->foo = foo;
}

int
Singleton_getFoo(void)
{
    return RKH_DOWNCAST(Singleton, singleton)->foo;
}

void
Multiple_ctor(Multiple *const me, int foobar, RKHPostFifo postFifo)
{
    RKH_UPCAST(RKH_SMA_T, me)->vptr = &me->vtbl.super;
    *((RKHSmaVtbl *)(RKH_UPCAST(RKH_SMA_T, me)->vptr)) = rkhSmaVtbl;
    ((RKHSmaVtbl *)(RKH_UPCAST(RKH_SMA_T, me)->vptr))->post_fifo = postFifo;
    ((MultipleVtbl *)(RKH_UPCAST(RKH_SMA_T, me)->vptr))->toggle = 
                                                            Multiple_toggle;
    me->foobar = foobar;
}

int
Multiple_getFoobar(Multiple *const me)
{
    return me->foobar;
}

void
Multiple_postFifoA(RKH_SMA_T *me, const RKH_EVT_T *e, const void *const sender)
{
    RKH_DOWNCAST(Multiple, me)->foobar = 0;
}

void
Multiple_postFifoB(RKH_SMA_T *me, const RKH_EVT_T *e, const void *const sender)
{
    RKH_DOWNCAST(Multiple, me)->foobar += 4;
}

/* ------------------------------ End of file ------------------------------ */
