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
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhsma.h"
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

typedef struct Composite Composite;
struct Composite
{
    RKH_SMA_T ao;
    int foo;
    RKH_SM_T itsReactivePart;
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

RKH_SM_CREATE(PublicStateMachine, publicStateMachine, 4, HCAL, NULL, NULL, 
              NULL);
RKH_SM_DEF_PTR_TYPE(PublicStateMachine, publicStateMachine);

RKH_SMA_CREATE(Composite, composite, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR(composite);
RKH_SM_CONST_CREATE(region, 1, HCAL, NULL, NULL, NULL);

RKH_SMA_CREATE(PublicComposite, publicComposite, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(PublicComposite, publicComposite);
RKH_SM_CONST_CREATE(publicRegion, 1, HCAL, NULL, NULL, NULL);

RKH_SMA_CREATE(PublicCompositeA, publicCompositeA, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(PublicCompositeA, publicCompositeA);
RKH_SM_CONST_CREATE(publicRegionA, 1, HCAL, NULL, NULL, NULL);

RKH_SM_CONST_CREATE(publicSingleDyn, 1, HCAL, NULL, NULL, NULL);

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

void
Composite_ctor(int foo)
{
    ((Composite *)composite)->foo = foo;
    RKH_SM_INIT(&((Composite *)composite)->itsReactivePart, region, 
                1, HCAL, NULL, NULL, NULL);
}

int
Composite_getFoo(void)
{
    return ((Composite *)composite)->foo;
}

RKH_SM_T *
Composite_getItsReactivePart(void)
{
    return &((Composite *)composite)->itsReactivePart;
}

void
PublicComposite_ctor(PublicComposite *const me, int foo)
{
    me->foo = foo;
    RKH_SM_INIT(&me->itsReactivePart, publicRegion,
                1, HCAL, NULL, NULL, NULL);
}

void
PublicCompositeA_ctor(PublicCompositeA *const me, int actObjFoo, int partFoo)
{
    me->foo = actObjFoo;
    RKH_SM_INIT(&me->itsReactivePart, publicRegionA,
                1, HCAL, NULL, NULL, NULL);
    me->itsReactivePart.foo = partFoo;
}

PublicSingle *
PublicSingle_dynCtor(int foo)
{
    PublicSingle *me = (PublicSingle *)malloc(sizeof(PublicSingle));

    if (me != (PublicSingle *)0)
    {
        /* Initialize its own state machine object */
        RKH_SM_INIT(me, publicSingleDyn,
                    1, HCAL, NULL, NULL, NULL);
        me->foo = foo;
    }
    return me;
}

void 
PublicSingle_dynDtor(PublicSingle *const me)
{
    if (me != (PublicSingle *)0)
        free(me);
}

/* ------------------------------ End of file ------------------------------ */
