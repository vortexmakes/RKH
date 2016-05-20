/**
 *  \file       test_utrzignore_runner.c
 *  \ingroup    test_utrzignore_group
 *
 *  \brief      Ignore group runner
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

TEST_GROUP_RUNNER(utrzIgnore)
{
	RUN_TEST_CASE(utrzIgnore, sm_trn_Ok);
	RUN_TEST_CASE(utrzIgnore, sm_trn_OneArg);
	RUN_TEST_CASE(utrzIgnore, sm_trn_OneArgBeforeExpect);
   	RUN_TEST_CASE(utrzIgnore, sm_exeAct_Ok);
	RUN_TEST_CASE(utrzIgnore, sm_exeAct_OneArg);
	RUN_TEST_CASE(utrzIgnore, sm_exeAct_OneArgBeforeExpect);
    RUN_TEST_CASE(utrzIgnore, ignoreAnEventOfIgnoredGroup);
    RUN_TEST_CASE(utrzIgnore, ignoreAnOutOfRangeGroup);
    RUN_TEST_CASE(utrzIgnore, ignoreAnOutOfRangeEvent);
    RUN_TEST_CASE(utrzIgnore, verifyFail);
}

/* ------------------------------ End of file ------------------------------ */
