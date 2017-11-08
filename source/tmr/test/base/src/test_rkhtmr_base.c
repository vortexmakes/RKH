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
 *  \file       test_rkhtmrbase.c
 *  \ingroup    test_tmr
 *  \brief      Unit test for software timer module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_tmr Software timer module
 *  @{
 *  \brief      Unit test for software timer module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.07.11  LeFr  v3.0.01  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhtmr_base.h"
#include "Mock_rkhsma.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(base);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(base)
{
}

TEST_TEAR_DOWN(base)
{
}

/**
 *  \addtogroup test_rkhtimer Software timer test group
 *  @{
 *  \name Test cases of timer group
 *  @{ 
 */
TEST(base, SetBaseTimerToPost)
{
    RKHTmrBase tmrEvt;
    RKH_SMA_T ao;

    ((RKH_EVT_T *)&tmrEvt)->e = 55;
    tmrEvt.ao = &ao;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
