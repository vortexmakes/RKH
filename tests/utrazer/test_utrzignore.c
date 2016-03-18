/**
 *  \file       test_utrzignore.c
 *  \ingroup    test_utrz
 *  \ingroup    test_utrzignore_group
 *  \brief      Unit test for uTrazer module - Ignore test group
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_utrz
 *  @{
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
#include "unitrazer.h"
#include "rkh.h"
#include "aotest.h"
#include "test_common.h"

/* ----------------------------- Local macros ------------------------------ */
#define utrzOkCheck()   \
        {                       \
            UtrzProcessOut *p;  \
            p = unitrazer_getLastOut();    \
            TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);  \
        }

#define utrzFailCheck()   \
        {                       \
            UtrzProcessOut *p;  \
            p = unitrazer_getLastOut();    \
            TEST_ASSERT_EQUAL(UT_PROC_FAIL, p->status);  \
        }
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */

TEST_GROUP(utrzIgnore);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

TEST_SETUP(utrzIgnore)
{
    /* -------- Setup ---------------
     * Establish the preconditions to the test 
     */
    common_test_setup();
}

TEST_TEAR_DOWN(utrzIgnore)
{
    /* -------- Cleanup -------------
     * Return the system under test to its initial state after the test
     */
    common_tear_down();
}

/**
 *  \addtogroup test_utrzignore_group Ignore test group
 *  @{
 *  \name Test cases of Ignore group
 *  @{ 
 */

TEST(utrzIgnore, sm_trn_Ok)
{	
    sm_trn_ignore();
    sm_evtProc_expect();

    RKH_TR_SM_TRN(aotest, &s21, &s21);

    utrzOkCheck();

    RKH_TR_SM_EVT_PROC(aotest)

    utrzOkCheck();
}

TEST(utrzIgnore, sm_trn_OneArg)
{
	sm_trn_expect(CST(&s21), CST(&s211));
    sm_trn_ignoreArg_sourceState();

    RKH_TR_SM_TRN(aotest, &s211, &s211);

    utrzOkCheck();
}

TEST(utrzIgnore, sm_trn_OneArgBeforeExpect)
{
    UtrzProcessOut *p;

	sm_trn_expect(CST(&s21), CST(&s211));
	sm_evtProc_expect();
    sm_trn_ignoreArg_sourceState();

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_FAIL, p->status);
    TEST_ASSERT_EQUAL_STRING("IgnoreArg called before Expect on event 'TRN'."
                                , p->msg);
	RKH_TR_SM_TRN(aotest, &s21, &s211);
	RKH_TR_SM_EVT_PROC(aotest);
}

TEST(utrzIgnore, sm_exeAct_Ok)
{	
    sm_trn_ignore();
    sm_evtProc_expect();

    RKH_TR_SM_TRN(aotest, &s21, &s21);

    utrzOkCheck();

    RKH_TR_SM_EVT_PROC(aotest)

    utrzOkCheck();
}

TEST(utrzIgnore, sm_exeAct_OneArg)
{
	sm_trn_expect(CST(&s21), CST(&s211));
    sm_trn_ignoreArg_sourceState();

    RKH_TR_SM_TRN(aotest, &s211, &s211);

    utrzOkCheck();
}

TEST(utrzIgnore, sm_exeAct_OneArgBeforeExpect)
{
    UtrzProcessOut *p;

	sm_trn_expect(CST(&s21), CST(&s211));
	sm_evtProc_expect();
    sm_trn_ignoreArg_sourceState();

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_FAIL, p->status);
    TEST_ASSERT_EQUAL_STRING("IgnoreArg called before Expect on event 'TRN'."
                                , p->msg);
	RKH_TR_SM_TRN(aotest, &s21, &s211);
	RKH_TR_SM_EVT_PROC(aotest);
}


TEST(utrzIgnore, ignoreAnEventOfIgnoredGroup)
{
    fwk_ignore();
    sm_evtProc_expect();

    RKH_TR_FWK_AO(aotest);
    RKH_TR_SM_EVT_PROC(aotest);

    utrzOkCheck();
}


TEST(utrzIgnore, ignoreAnOutOfRangeGroup)
{
    unitrazer_ignoreGroup(__LINE__, RKH_TG_NGROUP);

    utrzOkCheck();
}

TEST(utrzIgnore, ignoreAnOutOfRangeEvent)
{
    unitrazer_ignore(__LINE__, RKH_TE_TMR_TOUT);

	utrzOkCheck();
}

TEST(utrzIgnore, verifyFail)
{
	sm_trn_expect(CST(&s21), CST(&s211));

    unitrazer_verify();
	utrzFailCheck();

	unitrazer_cleanup();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
