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
 *  terms of the GNU General Public License as published by the Recycle Software
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
 *  \file       test_rkhfwk_pubsub.c
 *  \ingroup    test_fwk
 *  \brief      Unit test for publishing/subscribing mechanism of fwk module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_fwk Framework
 *  @{
 *  \brief      Unit test for framework module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.08.06  LeFr  v3.1.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhfwk_pubsub.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(pubsub);

/* ---------------------------- Local variables ---------------------------- */
static rui8_t *stoStart;
static rui16_t stoSize;
static RKH_ES_T evtSize;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(pubsub)
{
}

TEST_TEAR_DOWN(pubsub)
{
}

/**
 *  \addtogroup test_pubsub Test cases of publishing/subscribing group
 *  @{
 *  \name Test cases of publishing/subscribing group
 *  @{ 
 */
TEST(pubsub, AfterInitAllChannelsAreAvailable)
{
    rkh_pubsub_init();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
