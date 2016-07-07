/**
 *  \file       test_utrzsm.c
 *  \ingroup    test_utrz
 *  \ingroup    test_utrzsm_group
 *  \brief      Unit test for uTrazer module - State machine test group
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_utrz UTrazer
 *  @{
 *  \brief      Unit test for uTrazer module
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
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */

TEST_GROUP(utrzsm);

/* ---------------------------- Local variables ---------------------------- */

static RKH_ROM_STATIC_EVENT( eA, A );
static RKH_ROM_STATIC_EVENT( eB, B );
static RKH_ROM_STATIC_EVENT( eC, C );
static RKH_ROM_STATIC_EVENT( eD, D );
static RKH_ROM_STATIC_EVENT( eE, E );
static RKH_ROM_STATIC_EVENT( eF, F );
static RKH_ROM_STATIC_EVENT( eG, G );
static RKH_ROM_STATIC_EVENT( eH, H );
static RKH_ROM_STATIC_EVENT( eI, I );
static RKH_ROM_STATIC_EVENT( eTerm, TERMINATE );

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

TEST_SETUP(utrzsm)
{
    /* -------- Setup ---------------
     * Establish the preconditions to the test 
     */
    common_test_setup();
}

TEST_TEAR_DOWN(utrzsm)
{
    /* -------- Cleanup -------------
     * Return the system under test to its initial state after the test
     */
    common_tear_down();
}

/**
 *  \addtogroup test_utrzsm_group State machine test group
 *  @{
 *  \name Test cases of State machine test group
 *  @{ 
 */

TEST(utrzsm, expectEventOk)
{
    UtrzProcessOut *p;

    /* -------- Expectations --------
     * Record the trace event expectations to be met
     */
	sm_trn_expect(CST(&s21), CST(&s211));

    /* -------- Exercise ------------ 
     * Do something to the system 
     */

    /* Each recorded trace event is checked to see that it matches */
    /* the expected trace event exactly. If calls are out of order or */
    /* parameters are wrong, the test immediately fails. */
    RKH_TR_SM_TRN(aotest, &s21, &s211);

    /* -------- Verify --------------
     * Check the expected outcome 
     */
    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(utrzsm, expectEventOutOfSequence)
{
    UtrzProcessOut *p;

	sm_trn_expect(CST(&s21), CST(&s211));

    RKH_TR_SM_ENSTATE(aotest, CST(&s21));

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_FAIL, p->status);
    TEST_ASSERT_EQUAL_STRING("Out of order Trace event. occurred: 'ENSTATE' "
                             "expected: 'TRN'.", p->msg);
}

TEST(utrzsm, expectEventWithUnexpectedArg)
{
    UtrzProcessOut *p;

	sm_trn_expect(CST(&s21), CST(&s211));

    RKH_TR_SM_TRN(aotest, &s21, &s21);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_FAIL, p->status);
    TEST_ASSERT_EQUAL_STRING("Event 'TRN' occurred with unexpected "
                             "value for argument 'tst=s21' expected "
                             "value='s211'.", p->msg);
}

TEST(utrzsm, ignoreEvt)
{	
    UtrzProcessOut *p;

    sm_trn_ignore();
    sm_evtProc_expect();

    RKH_TR_SM_TRN(aotest, &s21, &s21);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);

    RKH_TR_SM_EVT_PROC(aotest)

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(utrzsm, ignoreOneArg)
{
    UtrzProcessOut *p;

	sm_trn_expect(CST(&s21), CST(&s211));
    sm_trn_ignoreArg_sourceState();

    RKH_TR_SM_TRN(aotest, &s211, &s211);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(utrzsm, ignoreOneArgBeforeExpect)
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

TEST(utrzsm, eventMoreThanExpect)
{
    UtrzProcessOut *p;

	sm_trn_expect(CST(&s21), CST(&s211));

    RKH_TR_SM_TRN(aotest, &s21, &s211);        

    RKH_TR_SM_ENSTATE(aotest, CST(&s21));

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_FAIL, p->status);
    TEST_ASSERT_EQUAL_STRING("Event 'ENSTATE' occurred more times than"
                             " expected.", p->msg);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
