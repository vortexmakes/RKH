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
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       test_rkhfwk_evtpool_runner.c
 *  \ingroup    test_fwk
 *
 *  \brief      Test runner of event pool module
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.09  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_GROUP_RUNNER(evtpool)
{
	RUN_TEST_CASE(evtpool, AfterInitAllEvtPoolAvailable);
	RUN_TEST_CASE(evtpool, GetOneEvtPool);
	RUN_TEST_CASE(evtpool, GetMultipleEvtPool);
	RUN_TEST_CASE(evtpool, Fails_ExceedsMaxAvailableEvtPool);
	RUN_TEST_CASE(evtpool, GetBlockSize);
	RUN_TEST_CASE(evtpool, Fails_GetBlockSizeInvalidInstance);
	RUN_TEST_CASE(evtpool, GetBlock);
	RUN_TEST_CASE(evtpool, Fails_GetBlockInvalidInstance);
	RUN_TEST_CASE(evtpool, PutBlock);
	RUN_TEST_CASE(evtpool, Fails_PutBlockInvalidInstance);
	RUN_TEST_CASE(evtpool, GetNumUsed);
	RUN_TEST_CASE(evtpool, Fails_GetNumUsedInvalidInstance);
	RUN_TEST_CASE(evtpool, GetNumMin);
	RUN_TEST_CASE(evtpool, Fails_GetNumMinInvalidInstance);
	RUN_TEST_CASE(evtpool, GetNumBlock);
	RUN_TEST_CASE(evtpool, Fails_GetNumBlockInvalidInstance);
}

/* ------------------------------ End of file ------------------------------ */
