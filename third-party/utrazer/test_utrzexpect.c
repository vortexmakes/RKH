/**
 *  \file       test_utrzexpect.c
 *  \ingroup    test_utrz
 *  \ingroup    test_utrzexpect_group
 *  \brief      Unit test for uTrazer module - Expect test group
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
#include "aotest_act.h"
#include "test_common.h"

/* ----------------------------- Local macros ------------------------------ */
#define str(a)  #a

#define utrzExpect_Ok_check()   \
        {                       \
            UtrzProcessOut *p;  \
            p = unitrazer_getLastOut();    \
            TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);  \
        }

#define utrzExpect_OutOfSequence_check(ex, rc)  \
        {                                       \
            UtrzProcessOut *p;                  \
            p = unitrazer_getLastOut();                \
            TEST_ASSERT_EQUAL(UT_PROC_FAIL, p->status);             \
            TEST_ASSERT_EQUAL_STRING("Out of order Trace event."    \
                    " occurred: '"rc"' expected: '"ex"'.", p->msg); \
        }

#define utrzExpect_WithUnexpectedArg_check( ev, an, e, r )  \
        {                                               \
            UtrzProcessOut *p;                          \
            p = unitrazer_getLastOut();                        \
            TEST_ASSERT_EQUAL(UT_PROC_FAIL, p->status); \
            TEST_ASSERT_EQUAL_STRING("Event '"ev"' occurred with unexpected " \
                             "value for argument '"an"="r"' expected "       \
                             "value='"e"'.", p->msg);                        \
        }

#define utrzExpect_WithUnexpectedArgNoName_check( ev, e, r )  \
        {                                               \
            UtrzProcessOut *p;                          \
            p = unitrazer_getLastOut();                        \
            TEST_ASSERT_EQUAL(UT_PROC_FAIL, p->status); \
            TEST_ASSERT_EQUAL_STRING("Event '"ev"' occurred with unexpected " \
                             "value for argument '"r"' expected "       \
                             "value='"e"'.", p->msg);                        \
        }

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */

TEST_GROUP(utrzExpect);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

TEST_SETUP(utrzExpect)
{
    /* -------- Setup ---------------
     * Establish the preconditions to the test 
     */
    common_test_setup();
}

TEST_TEAR_DOWN(utrzExpect)
{
    /* -------- Cleanup -------------
     * Return the system under test to its initial state after the test
     */
    common_tear_down();
}

/**
 *  \addtogroup test_utrzexpect_group Expect test group
 *  @{
 *  \name Test cases of Expect group
 *  @{ 
 */

TEST(utrzExpect, sm_init_Ok)
{
	sm_init_expect(CST(&s21));

    RKH_TR_SM_INIT(aotest, &s21);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_init_OutOfSequence)
{
	sm_init_expect(CST(&s21));

    RKH_TR_SM_ENSTATE(aotest, CST(&s21));

    utrzExpect_OutOfSequence_check( "INIT", "ENSTATE" );
}

TEST(utrzExpect, sm_init_WithUnexpectedArg)
{
	sm_init_expect(CST(&s21));

    RKH_TR_SM_INIT(aotest, &s211);

    utrzExpect_WithUnexpectedArg_check( "INIT", "ist", str(s21), str(s211) );
}

TEST(utrzExpect, sm_clrh_Ok)
{
	sm_clrh_expect(CST(&s21));

    RKH_TR_SM_CLRH(aotest, &s21);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_clrh_OutOfSequence)
{
	sm_clrh_expect(CST(&s21));

    RKH_TR_SM_ENSTATE(aotest, CST(&s21));

    utrzExpect_OutOfSequence_check( "CLRH", "ENSTATE" );
}

TEST(utrzExpect, sm_clrh_WithUnexpectedArg)
{
	sm_clrh_expect(CST(&s21));

    RKH_TR_SM_CLRH(aotest, &s211);
    
    utrzExpect_WithUnexpectedArg_check( "CLRH", "h", str(s21), str(s211) );
}

TEST(utrzExpect, sm_trn_Ok)
{
	sm_trn_expect(CST(&s21), CST(&s211));
    
    RKH_TR_SM_TRN(aotest, &s21, &s211);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_trn_OutOfSequence)
{
	sm_trn_expect(CST(&s21), CST(&s211));

    RKH_TR_SM_ENSTATE(aotest, CST(&s21));

    utrzExpect_OutOfSequence_check( "TRN", "ENSTATE" );
}

TEST(utrzExpect, sm_trn_WithUnexpectedArg)
{
	sm_trn_expect(CST(&s21), CST(&s211));

    RKH_TR_SM_TRN(aotest, &s21, &s21);

    utrzExpect_WithUnexpectedArg_check( "TRN", "tst", str(s211), str(s21) );

	sm_trn_expect(CST(&s21), CST(&s211));

    RKH_TR_SM_TRN(aotest, &s211, &s211);

    utrzExpect_WithUnexpectedArg_check( "TRN", "sst", str(s21), str(s211) );    
}


TEST(utrzExpect, sm_trn_WithAnyArgs)
{
	sm_trn_expectAnyArgs();

    RKH_TR_SM_TRN(aotest, &s211, &s211);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_state_Ok)
{
	sm_state_expect(CST(&s21));
    
    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_state_OutOfSequence)
{
	sm_state_expect(CST(&s21));

    RKH_TR_SM_ENSTATE(aotest, CST(&s21));

    utrzExpect_OutOfSequence_check( "STATE", "ENSTATE" );
}

TEST(utrzExpect, sm_state_WithUnexpectedArg)
{
	sm_state_expect(CST(&s21));

    RKH_TR_SM_STATE(aotest, &s211);

    utrzExpect_WithUnexpectedArg_check( "STATE", "nxtst", str(s21), str(s211) );
}

TEST(utrzExpect, sm_enstate_Ok)
{
	sm_enstate_expect(CST(&s21));
    
    RKH_TR_SM_ENSTATE(aotest, &s21);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_enstate_OutOfSequence)
{
	sm_enstate_expect(CST(&s21));

    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "ENSTATE", "STATE" );
}

TEST(utrzExpect, sm_enstate_WithUnexpectedArg)
{
	sm_enstate_expect(CST(&s21));

    RKH_TR_SM_ENSTATE(aotest, &s211);

    utrzExpect_WithUnexpectedArg_check( "ENSTATE", "st", str(s21), str(s211) );
}

TEST(utrzExpect, sm_exstate_Ok)
{
	sm_exstate_expect(CST(&s21));
    
    RKH_TR_SM_EXSTATE(aotest, &s21);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_exstate_OutOfSequence)
{
	sm_exstate_expect(CST(&s21));

    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "EXSTATE", "STATE" );
}

TEST(utrzExpect, sm_exstate_WithUnexpectedArg)
{
	sm_exstate_expect(CST(&s21));

    RKH_TR_SM_EXSTATE(aotest, &s211);

    utrzExpect_WithUnexpectedArg_check( "EXSTATE", "st", str(s21), str(s211) );
}

TEST(utrzExpect, sm_nenex_Ok)
{
	sm_nenex_expect(2,3);
    
    RKH_TR_SM_NENEX(aotest, 2, 3);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_nenex_OutOfSequence)
{
	sm_nenex_expect(2,3);

    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "NENEX", "STATE" );
}

TEST(utrzExpect, sm_nenex_WithUnexpectedArg)
{
	sm_nenex_expect(2,3);
    
    RKH_TR_SM_NENEX(aotest, 3, 3);

    utrzExpect_WithUnexpectedArg_check("NENEX", "nen", "2", "3");

	sm_nenex_expect(2,3);
    
    RKH_TR_SM_NENEX(aotest, 2, 2);

    utrzExpect_WithUnexpectedArg_check("NENEX", "nex", "3", "2");    
}

TEST(utrzExpect, sm_ntrnact_Ok)
{
	sm_ntrnact_expect(2,3);
    
    RKH_TR_SM_NTRNACT(aotest, 2, 3);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_ntrnact_OutOfSequence)
{
	sm_ntrnact_expect(2,3);

    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "NTRNACT", "STATE" );
}

TEST(utrzExpect, sm_ntrnact_WithUnexpectedArg)
{
	sm_ntrnact_expect(2,3);
    
    RKH_TR_SM_NTRNACT(aotest, 3, 3);

    utrzExpect_WithUnexpectedArg_check("NTRNACT", "nta", "2", "3");

	sm_ntrnact_expect(2,3);
    
    RKH_TR_SM_NTRNACT(aotest, 2, 2);

    utrzExpect_WithUnexpectedArg_check("NTRNACT", "nts", "3", "2");    
}

TEST(utrzExpect, sm_tsstate_Ok)
{
    sm_tsState_expect(CST(&s21));
    
    RKH_TR_SM_TS_STATE(aotest, &s21);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_tsstate_OutOfSequence)
{
    sm_tsState_expect(CST(&s21));
    
    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "TS_STATE", "STATE" );
}

TEST(utrzExpect, sm_tsstate_WithUnexpectedArg)
{
    sm_tsState_expect(CST(&s21));
    
    RKH_TR_SM_TS_STATE(aotest, &s211);

    utrzExpect_WithUnexpectedArg_check("TS_STATE", "st", str(s21), str(s211) );  
}

TEST(utrzExpect, sm_evtproc_Ok)
{
	sm_evtProc_expect();
    
    RKH_TR_SM_EVT_PROC(aotest);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_evtproc_OutOfSequence)
{
	sm_evtProc_expect();
    
    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "EVT_PROC", "STATE" );
}

TEST(utrzExpect, sm_evtnfound_Ok)
{
    RKH_STATIC_EVENT(e, A);

    sm_evtNotFound_expect(A);
    
    RKH_TR_SM_EVT_NFOUND(aotest, (&e));

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_evtnfound_OutOfSequence)
{
    sm_evtNotFound_expect(A);
    
    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "EVT_NFOUND", "STATE" );
}

TEST(utrzExpect, sm_evtnfound_WithUnexpectedArg)
{
    RKH_STATIC_EVENT(ev, B);

    sm_evtNotFound_expect(A);
    
    RKH_TR_SM_EVT_NFOUND(aotest, (&ev));

    utrzExpect_WithUnexpectedArg_check("EVT_NFOUND", "sig", str(A), str(B));
}

TEST(utrzExpect, sm_grdfalse_Ok)
{
	sm_grdFalse_expect();
    
    RKH_TR_SM_GRD_FALSE(aotest);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_grdfalse_OutOfSequence)
{
    sm_grdFalse_expect();
    
    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "GRD_FALSE", "STATE" );
}

TEST(utrzExpect, sm_cndnfound_Ok)
{
	sm_cndNotFound_expect();
    
    RKH_TR_SM_CND_NFOUND(aotest);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_cndnfound_OutOfSequence)
{
	sm_cndNotFound_expect();
    
    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "CND_NFOUND", "STATE" );
}

TEST(utrzExpect, sm_unkstate_Ok)
{
	sm_unknState_expect();
    
    RKH_TR_SM_UNKN_STATE(aotest);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_unkstate_OutOfSequence)
{
	sm_unknState_expect();
    
    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "UNKN_STATE", "STATE" );
}

TEST(utrzExpect, sm_exhlevel_Ok)
{
	sm_exHLevel_expect();
    
    RKH_TR_SM_EX_HLEVEL(aotest);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_exhlevel_OutOfSequence)
{
	sm_exHLevel_expect();
    
    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "EX_HLEVEL", "STATE" );
}

TEST(utrzExpect, sm_extseg_Ok)
{
	sm_exTSeg_expect();
    
    RKH_TR_SM_EX_TSEG(aotest);

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_extseg_OutOfSequence)
{
    sm_exTSeg_expect();
    
    RKH_TR_SM_STATE(aotest, &s21);

    utrzExpect_OutOfSequence_check( "EX_TSEG", "STATE" );
}

TEST(utrzExpect, sm_exeAct_Ok)
{
	sm_exeAct_expect(RKH_SUBTE_SM_EXE_ACT_EN,
                        CST(&s21), foo_set2zero );

    RKH_TR_SM_EXE_ACT( RKH_SUBTE_SM_EXE_ACT_EN, aotest, &s21, foo_set2zero );

    utrzExpect_Ok_check();
}

TEST(utrzExpect, sm_exeAct_OutOfSequence)
{
   	sm_exeAct_expect(RKH_SUBTE_SM_EXE_ACT_EN,
                        CST(&s21), foo_set2zero );

    RKH_TR_SM_ENSTATE(aotest, CST(&s21));

    utrzExpect_OutOfSequence_check( "EXE_ACT", "ENSTATE" );
}

TEST(utrzExpect, sm_exeAct_WithUnexpectedArg)
{
    sm_exeAct_expect(RKH_SUBTE_SM_EXE_ACT_EN,
                        CST(&s21), foo_set2zero );

    RKH_TR_SM_EXE_ACT( RKH_SUBTE_SM_EXE_ACT_EN, aotest, &s211, foo_set2zero );

    utrzExpect_WithUnexpectedArg_check("EXE_ACT", "st", str(s21), str(s211));

    sm_exeAct_expect(RKH_SUBTE_SM_EXE_ACT_EN,
                        CST(&s21), foo_set2zero );

    RKH_TR_SM_EXE_ACT( RKH_SUBTE_SM_EXE_ACT_EN, aotest, &s21, foo_set2one );

    utrzExpect_WithUnexpectedArg_check("EXE_ACT", "fn", 
                                        str(foo_set2zero), str(foo_set2one));    

    sm_exeAct_expect(RKH_SUBTE_SM_EXE_ACT_EN,
                        CST(&s21), foo_set2zero );

    RKH_TR_SM_EXE_ACT( RKH_SUBTE_SM_EXE_ACT_EX, aotest, &s21, foo_set2one );

    utrzExpect_WithUnexpectedArgNoName_check("EXE_ACT", "Entry", "Exit");    
}

TEST(utrzExpect, sm_exeAct_WithAnyArgs)
{
	sm_exeAct_expectAnyArgs();

    RKH_TR_SM_EXE_ACT( RKH_SUBTE_SM_EXE_ACT_INI, aotest, &s211, foo_set2one );

    utrzExpect_Ok_check();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
