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
#include "rkhsma.h"
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
    MultipleVtbl vtbl;  /* Since every instance of Multiple sets in runtime */
                        /* its own virtual functions, every instance must */
                        /* store into RAM its virtual table. */ 
    int foobar;
};

struct Command
{
    RKH_SMA_T base;
    int bar;
};

struct CallControl
{
    RKH_SMA_T base;
    int foo;
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
RKH_SMA_CREATE(Singleton, singleton, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR(singleton);

RKH_SMA_CREATE(Multiple, multA, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(Multiple, multA);
RKH_SMA_CREATE(Multiple, multB, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(Multiple, multB);

RKH_SMA_CREATE(Command, cmdSignal, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(Command, cmdSignal);
RKH_SMA_CREATE(Command, cmdRegister, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(Command, cmdRegister);

RKH_SMA_CREATE(CallControl, theCallControl, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR_TYPE(CallControl, theCallControl);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
Singleton_activate(RKH_SMA_T *me, const RKH_EVT_T **qSto, RKH_QUENE_T qSize,
                   void *stkSto, rui32_t stkSize)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    int var = 0;

    (void)qSto;
    (void)qSize;
    (void)stkSto;
    (void)stkSize;
    if (me->vptr->task != (void (*)(RKH_SMA_T *, void *)) 0)
    {
        me->vptr->task(me, &var);
    }
#else
    (void)me;
    (void)qSto;
    (void)qSize;
    (void)stkSto;
    (void)stkSize;
#endif
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
/*
 * Initializes the object attributes.
 *
 * Singleton objects (with a multiplicity of one) are instantiated only once
 * throughout the life of the system.
 * Because there can be only one instance of a singleton, its operations do
 * not include a context pointer as their first argument.
 */
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

    rkh_sma_ctor(RKH_UPCAST(RKH_SMA_T, singleton), &vtbl);
    RKH_DOWNCAST(Singleton, singleton)->foo = foo;
}

int
Singleton_getFoo(void)
{
    return RKH_DOWNCAST(Singleton, singleton)->foo;
}

/*
 *  Initializes the object attributes.
 *
 *  In this case, the constructor only initializes the object, neither
 *  allocates memory for it nor returns a pointer to the object initialized.
 *  The initializer assumes that memory has previously been allocated for the
 *  object (either statically or dynamically).
 *
 *  Because each operation associated with an object is implemented as a
 *  global function in C, it must be provided with a context in the form of a
 *  pointer to the object on which it should operate. In C++, this context is
 *  provided in the form of an implied this pointer as the first argument.
 *  In C, however, the this pointer is not available. Therefore, in RKH, the
 *  first argument to operations is generally a pointer to the object
 *  associated with the operation. This context pointer is conventionally
 *  called me, as shown below.
 *
 *  Because there is only one instance of a singleton object, the context
 *  pointer is not needed for singleton operations.
 *
 *  The naming convention used to name operations is to prefix each (public)
 *  operation with the name of the object type on which it should operate.
 *  Thus, the public operation names have the format
 *  <object_type>_<operation_name>(), and private operation names have the
 *  format <operation_name>().
 *
 *  \note
 *  The first argument is a constant pointer to the object being initialized.
 *  The const keyword defines a constant pointer in ANSI C. Passing a constant
 *  pointer as an argument allows the operation to change the value of the
 *  object that the pointer addresses, but not the address that the argument
 *  me contains.
 */
void
Multiple_ctor(Multiple *const me, int foobar, RKHPostFifo postFifo)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    /* Link vptr to its own virtual table */
    rkh_sma_ctor(RKH_UPCAST(RKH_SMA_T, me), &me->vtbl.base);

    /* Initialize the virtual table */
    *((RKHSmaVtbl *)(RKH_UPCAST(RKH_SMA_T, me)->vptr)) = rkhSmaVtbl;

    /* Overrides the post_fifo() virtual operation */
    ((RKHSmaVtbl *)(RKH_UPCAST(RKH_SMA_T, me)->vptr))->post_fifo = postFifo;

    /* Set the toggle() virtual operation */
    ((MultipleVtbl *)(RKH_UPCAST(RKH_SMA_T, me)->vptr))->toggle =
        Multiple_toggle;

    /* Initialize the attributes of AO instance */
    me->foobar = foobar;
#endif
}

int
Multiple_getFoobar(Multiple *const me)
{
    return me->foobar;
}

void
Multiple_postFifoA(RKH_SMA_T *me, const RKH_EVT_T *e, const void *const sender)
{
    (void)e;
    (void)sender;

    RKH_DOWNCAST(Multiple, me)->foobar = 0;
}

void
Multiple_postFifoB(RKH_SMA_T *me, const RKH_EVT_T *e, const void *const sender)
{
    (void)e;
    (void)sender;

    RKH_DOWNCAST(Multiple, me)->foobar += 4;
}

static const RKHSmaVtbl commandVtbl =
{
    rkh_sma_activate,
    Command_task,
    Command_postFifo,
    Command_postLifo
};

void
Command_task(RKH_SMA_T *me, void *arg)
{
    (void)me;
    (void)arg;
}

void
Command_postFifo(RKH_SMA_T *me, const RKH_EVT_T *e, const void *const sender)
{
    (void)me;
    (void)e;
    (void)sender;
}

void
Command_postLifo(RKH_SMA_T *me, const RKH_EVT_T *e, const void *const sender)
{
    (void)me;
    (void)e;
    (void)sender;
}

void
Command_ctor(Command *const me, int bar)
{
    rkh_sma_ctor(RKH_UPCAST(RKH_SMA_T, me), &commandVtbl);
    me->bar = bar;
}

void
CallControl_activate(RKH_SMA_T *me, const RKH_EVT_T **qSto, RKH_QUENE_T qSize,
                     void *stkSto, rui32_t stkSize)
{
    (void)me;
    (void)qSto;
    (void)qSize;
    (void)stkSto;
    (void)stkSize;
}

void
CallControl_task(RKH_SMA_T *me, void *arg)
{
    (void)me;
    (void)arg;
}

void
CallControl_ctorA(int foo)
{
    static const RKHSmaVtbl vtbl =
    {
        CallControl_activate,
        CallControl_task,
        rkh_sma_post_fifo,
        rkh_sma_post_lifo
    };

    rkh_sma_ctor(&theCallControl->base, &vtbl);
    theCallControl->foo = foo;
}

void
CallControl_ctorB(int foo)
{
    rkh_sma_ctor(&theCallControl->base, (const RKHSmaVtbl *)0);
    theCallControl->foo = foo;
}

int
CallControl_getFoo(void)
{
    return theCallControl->foo;
}

/* ------------------------------ End of file ------------------------------ */
