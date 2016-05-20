/**
 *  \file       test_utrzsm_runner.c
 *  \ingroup    test_utrzsm_group
 *
 *  \brief      State machine group runner
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

#include "unity_fixture.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

TEST_GROUP_RUNNER(utrzsm)
{
	RUN_TEST_CASE(utrzsm, expectEventOk);
	RUN_TEST_CASE(utrzsm, expectEventOutOfSequence);
	RUN_TEST_CASE(utrzsm, expectEventWithUnexpectedArg);
	RUN_TEST_CASE(utrzsm, ignoreEvt);
	RUN_TEST_CASE(utrzsm, ignoreOneArg);
	RUN_TEST_CASE(utrzsm, ignoreOneArgBeforeExpect);
	RUN_TEST_CASE(utrzsm, eventMoreThanExpect);
}

/* ------------------------------ End of file ------------------------------ */
