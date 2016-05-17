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
 *  \file       test_smTransition_runner.c
 *  \ingroup    test_sm
 *
 *  \brief      Test runner of state machine module
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

#include "unity_fixture.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

TEST_GROUP_RUNNER(transition)
{
	RUN_TEST_CASE(transition, firstStateAfterInit);
	RUN_TEST_CASE(transition, simpleToSimpleAtEqualLevel);
	RUN_TEST_CASE(transition, simpleToSimpleFromHighToLowLevel);
	RUN_TEST_CASE(transition, simpleToSimpleFromLowToHighLevel);
	RUN_TEST_CASE(transition, simpleToCompositeAtEqualLevel);
	RUN_TEST_CASE(transition, simpleToCompositeFromHighToLowLevel);
	RUN_TEST_CASE(transition, simpleToCompositeFromLowToHighLevel);
	RUN_TEST_CASE(transition, compositeToSimpleAtEqualLevel);
	RUN_TEST_CASE(transition, compositeToSimpleFromHighToLowLevel);
	RUN_TEST_CASE(transition, compositeToSimpleFromLowToHighLevel);
	RUN_TEST_CASE(transition, compositeToCompositeAtEqualLevel);
	RUN_TEST_CASE(transition, compositeToCompositeFromHighToLowLevel);
	RUN_TEST_CASE(transition, compositeToCompositeFromLowToHighLevel);
	RUN_TEST_CASE(transition, loopSimpleStateOnTop);
	RUN_TEST_CASE(transition, loopNestedSimpleState);
	RUN_TEST_CASE(transition, loopCompositeStateOnTop);
	RUN_TEST_CASE(transition, loopNestedCompositeState);
	RUN_TEST_CASE(transition, internalInSimpleState);
	RUN_TEST_CASE(transition, internalInCompositeState);
	RUN_TEST_CASE(transition, fails_EventNotFound);
	RUN_TEST_CASE(transition, fails_GuardFalse);
	RUN_TEST_CASE(transition, fails_ExceededHierarchicalLevel);
	RUN_TEST_CASE(transition, multipleEnabledTrn_FiringFirstTrueGuard);
	RUN_TEST_CASE(transition, multipleEnabledTrn_FiringFirstEmptyGuard);
	RUN_TEST_CASE(transition, defaultTrnWithAssociatedEffect);
	RUN_TEST_CASE(transition, generatedCompletionEventBySimpleState);
	RUN_TEST_CASE(transition, generatedCompletionEventByFinalState);
	RUN_TEST_CASE(transition, syncDispatchingToStateMachine);
}

/* ------------------------------ End of file ------------------------------ */
