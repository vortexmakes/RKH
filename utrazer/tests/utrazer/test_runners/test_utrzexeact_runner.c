/**
 *  \file       test_utrzexeact.c
 *  \ingroup    Test
 *
 *  \brief      ...
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

TEST_GROUP_RUNNER(utrzexeact)
{
	RUN_TEST_CASE(utrzexeact, expectEventOk);
	RUN_TEST_CASE(utrzexeact, expectEventOutOfSequence);
	RUN_TEST_CASE(utrzexeact, expectEventWithUnexpectedArg);
	RUN_TEST_CASE(utrzexeact, ignoreEvt);
	RUN_TEST_CASE(utrzexeact, ignoreOneArg);
	RUN_TEST_CASE(utrzexeact, ignoreOneArgBeforeExpect);
}

/* ------------------------------ End of file ------------------------------ */
