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
 *  \file       test_rkhfwk_bittbl.c
 *  \ingroup    test_fwk
 *  \brief      Unit test for bit table of fwk module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_fwk Framework
 *  @{
 *  \brief      Unit test for framework module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.26.04  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhfwk_bittbl.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(bittbl);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* =========================== Bittbl test group =========================== */
TEST_SETUP(bittbl)
{
}

TEST_TEAR_DOWN(bittbl)
{
}

/**
 *  \addtogroup test_bittbl Test cases of bit table group
 *  @{
 *  \name Test cases of bit table group
 *  @{ 
 */
TEST(bittbl, GetBitMask)
{
    rui8_t bitPos = 5, result;
    rui8_t expectedBitMask = (rui8_t)(1 << bitPos);

    result = rkh_bittbl_getBitMask(5);
    TEST_ASSERT_EQUAL_HEX8(expectedBitMask, result);
}

TEST(bittbl, GetLeastSignificantBitPost)
{
    rui8_t result, value;

    value = 0x38;
    result = rkh_bittbl_getLeastBitSetPos(value);
    TEST_ASSERT_EQUAL(3, result);
}

TEST(bittbl, InvalidBitPosition)
{
    rui8_t result;

    result = rkh_bittbl_getBitMask(8);
    TEST_ASSERT_EQUAL_HEX8(RKH_INVALID_BITPOS, result);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
