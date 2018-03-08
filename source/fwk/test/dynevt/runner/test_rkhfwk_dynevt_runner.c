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
 *  \file       test_rkhfwk_dynevt_runner.c
 *  \ingroup    test_fwk
 *
 *  \brief      Test runner of dynamic event module
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.04  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
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
TEST_GROUP_RUNNER(dynevt)
{
	RUN_TEST_CASE(dynevt, RegisterOneEventPool);
	RUN_TEST_CASE(dynevt, RegisterMultipleEventPool);
	RUN_TEST_CASE(dynevt, Fails_ExceedsNumberOfAllowedEventPools);
	RUN_TEST_CASE(dynevt, Fails_UnavailablePool);
	RUN_TEST_CASE(dynevt, Fails_TriesAllocateOneEvtWithoutAssignedPool);
	RUN_TEST_CASE(dynevt, AllocateOneEvt);
	RUN_TEST_CASE(dynevt, Fails_UnavailableBlockFromPool);
	RUN_TEST_CASE(dynevt, ReservesOneEvt);
	RUN_TEST_CASE(dynevt, TriesRecycleNotReferencedEvt);
	RUN_TEST_CASE(dynevt, TriesRecycleMultipleReferencedEvt);
	RUN_TEST_CASE(dynevt, RecycleEvt);
	RUN_TEST_CASE(dynevt, Fails_OnRecycleEvtNullPool);
	RUN_TEST_CASE(dynevt, Fails_OnRecycleEvtWrongPool);
}

/* ------------------------------ End of file ------------------------------ */
