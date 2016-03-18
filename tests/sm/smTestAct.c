/**
 *  \file       smTestAct.c
 *  \ingroup    Test
 *
 *  \brief      Production code.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.11.11  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */

#include <stdio.h>
#include "rkh.h"
#include "bsp.h"
#include "smTest.h"
#include "smTestAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

/* Defines HSM init function */
void
smTest_init(SmTest *const me)
{
    me->foo = 0;
}

/*
 * Defines transition action functions
 */
void
foo_set2zero(SmTest *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->foo = 0;
}

void
foo_set2one(SmTest *const me, RKH_EVT_T *pe)
{
    (void)pe;

    me->foo = 1;
}

/*
 * Defines guards functions
 */
rbool_t
foo_isn_zero(SmTest*const me, RKH_EVT_T *pe)
{
    return me->foo != 0;
}

rbool_t
foo_is_zero(SmTest *const me, RKH_EVT_T *pe)
{
    return me->foo == 0;
}

/* ------------------------------ End of file ------------------------------ */
