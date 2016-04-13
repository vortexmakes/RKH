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
 *  \file       smInstance.c
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
#include "smInstance.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
typedef struct Single Single;
struct Single
{
    RKH_SMA_T ao;
    int foo;
};

struct Opaque
{
    RKH_SMA_T ao;
    int foo;
};

typedef struct StateMachine StateMachine;
struct StateMachine
{
    RKH_SM_T sm;
    int foo;
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
RKH_SMA_CREATE(Single, single, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR(single);

RKH_SMA_CREATE(PublicSingle, publicSingle, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(PublicSingle, publicSingle);

RKH_SMA_CREATE(Opaque, opaque, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(Opaque, opaque);

RKH_SMA_CREATE(PublicSingle, single0, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(PublicSingle, single0);
RKH_SMA_CREATE(Single, single1, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(PublicSingle, single1);
RKH_SMA_CREATE(Single, single2, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(PublicSingle, single2);
RKH_SMA_CREATE(Single, single3, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(PublicSingle, single3);

RKH_ARRAY_SMA_CREATE_TYPE(PublicSingle, arrayOfSingles, 4)
{
    &single0, &single1, &single2, &single3
};

RKH_SM_CREATE(StateMachine, stateMachine, 4, HCAL, NULL, NULL, NULL);
RKH_SM_DEF_PTR(stateMachine);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

void
Single_ctor(int foo)
{
    ((Single *)single)->foo = foo;
}

int
Single_getFoo(void)
{
    return ((Single *)single)->foo;
}

void
PublicSingle_ctor(int foo)
{
    publicSingle->foo = foo;
}

void
Opaque_ctor(Opaque *const me, int foo)
{
    me->foo = foo;
}

int
Opaque_getFoo(Opaque *const me)
{
    return me->foo;
}

void
MultiplePublicSingle_ctor(PublicSingle *const me, int foo)
{
    me->foo = foo;
}

/* ------------------------------ End of file ------------------------------ */
