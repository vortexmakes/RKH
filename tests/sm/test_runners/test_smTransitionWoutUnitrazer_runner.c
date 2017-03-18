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
 *  \file       test_smTransitionWoutUnitrazer_runner.c
 *  \ingroup    test_sm
 *
 *  \brief      Test runner of state machine module without unitrazer facility
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

TEST_GROUP_RUNNER(trnWoutUnitrazer)
{
	RUN_TEST_CASE(trnWoutUnitrazer, firstStateAfterInit);
	RUN_TEST_CASE(trnWoutUnitrazer, simpleToSimpleAtEqualLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, simpleToSimpleFromHighToLowLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, simpleToSimpleFromLowToHighLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, simpleToCompositeAtEqualLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, simpleToCompositeFromHighToLowLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, simpleToCompositeFromLowToHighLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, compositeToSimpleAtEqualLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, compositeToSimpleFromHighToLowLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, compositeToSimpleFromLowToHighLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, compositeToCompositeAtEqualLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, compositeToCompositeFromHighToLowLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, compositeToCompositeFromLowToHighLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, loopSimpleStateOnTop);
	RUN_TEST_CASE(trnWoutUnitrazer, loopNestedSimpleState);
	RUN_TEST_CASE(trnWoutUnitrazer, loopCompositeStateOnTop);
	RUN_TEST_CASE(trnWoutUnitrazer, loopNestedCompositeState);
	RUN_TEST_CASE(trnWoutUnitrazer, internalInSimpleState);
	RUN_TEST_CASE(trnWoutUnitrazer, internalInCompositeState);
	RUN_TEST_CASE(trnWoutUnitrazer, fails_EventNotFound);
	RUN_TEST_CASE(trnWoutUnitrazer, fails_GuardFalseOnInternalTrn);
	RUN_TEST_CASE(trnWoutUnitrazer, fails_GuardFalseOnExternalTrn);
	RUN_TEST_CASE(trnWoutUnitrazer, fails_ExceededHierarchicalLevel);
	RUN_TEST_CASE(trnWoutUnitrazer, multipleEnabledTrn_FiringFirstTrueGuard);
	RUN_TEST_CASE(trnWoutUnitrazer, multipleEnabledTrn_FiringFirstEmptyGuard);
	RUN_TEST_CASE(trnWoutUnitrazer, defaultTrnWithAssociatedEffect);
	RUN_TEST_CASE(trnWoutUnitrazer, generatedCompletionEventBySimpleState);
	RUN_TEST_CASE(trnWoutUnitrazer, generatedCompletionEventByFinalState);
	RUN_TEST_CASE(trnWoutUnitrazer, syncDispatchingToStateMachine);
}

/* ------------------------------ End of file ------------------------------ */
