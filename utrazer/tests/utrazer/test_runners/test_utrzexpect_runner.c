/**
 *  \file       test_utrzexpect.c
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

TEST_GROUP_RUNNER(utrzExpect)
{
    /* RKH_TE_SM_INIT */
	RUN_TEST_CASE(utrzExpect, sm_init_Ok);
	RUN_TEST_CASE(utrzExpect, sm_init_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_init_WithUnexpectedArg);    
    /* RKH_TE_SM_CLRH */
	RUN_TEST_CASE(utrzExpect, sm_clrh_Ok);
	RUN_TEST_CASE(utrzExpect, sm_clrh_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_clrh_WithUnexpectedArg);    
    /* RKH_TE_SM_TRN */
	RUN_TEST_CASE(utrzExpect, sm_trn_Ok);
	RUN_TEST_CASE(utrzExpect, sm_trn_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_trn_WithUnexpectedArg);
	RUN_TEST_CASE(utrzExpect, sm_trn_WithAnyArgs);
    /* RKH_TE_SM_STATE */
   	RUN_TEST_CASE(utrzExpect, sm_state_Ok);
	RUN_TEST_CASE(utrzExpect, sm_state_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_state_WithUnexpectedArg);
    /* RKH_TE_SM_ENSTATE */
	RUN_TEST_CASE(utrzExpect, sm_enstate_Ok);
	RUN_TEST_CASE(utrzExpect, sm_enstate_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_enstate_WithUnexpectedArg);    
    /* RKH_TE_SM_EXSTATE */
	RUN_TEST_CASE(utrzExpect, sm_exstate_Ok);
	RUN_TEST_CASE(utrzExpect, sm_exstate_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_exstate_WithUnexpectedArg);    
    /* RKH_TE_SM_NENEX */
	RUN_TEST_CASE(utrzExpect, sm_nenex_Ok);
	RUN_TEST_CASE(utrzExpect, sm_nenex_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_nenex_WithUnexpectedArg);    
    /* RKH_TE_SM_NTRNACT */
	RUN_TEST_CASE(utrzExpect, sm_ntrnact_Ok);
	RUN_TEST_CASE(utrzExpect, sm_ntrnact_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_ntrnact_WithUnexpectedArg);    
    /* RKH_TE_SM_TS_STATE */
	RUN_TEST_CASE(utrzExpect, sm_tsstate_Ok);
	RUN_TEST_CASE(utrzExpect, sm_tsstate_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_tsstate_WithUnexpectedArg);    
    /* RKH_TE_SM_EVT_PROC */
	RUN_TEST_CASE(utrzExpect, sm_evtproc_Ok);
	RUN_TEST_CASE(utrzExpect, sm_evtproc_OutOfSequence);
    /* RKH_TE_SM_EVT_NFOUND */
	RUN_TEST_CASE(utrzExpect, sm_evtnfound_Ok);
	RUN_TEST_CASE(utrzExpect, sm_evtnfound_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_evtnfound_WithUnexpectedArg);    
    /* RKH_TE_SM_GRD_FALSE */
	RUN_TEST_CASE(utrzExpect, sm_grdfalse_Ok);
	RUN_TEST_CASE(utrzExpect, sm_grdfalse_OutOfSequence);
    /* RKH_TE_SM_CND_NFOUND */
	RUN_TEST_CASE(utrzExpect, sm_cndnfound_Ok);
	RUN_TEST_CASE(utrzExpect, sm_cndnfound_OutOfSequence);
    /* RKH_TE_SM_UNKN_STATE */
	RUN_TEST_CASE(utrzExpect, sm_unkstate_Ok);
	RUN_TEST_CASE(utrzExpect, sm_unkstate_OutOfSequence);
    /* RKH_TE_SM_EX_HLEVEL */
	RUN_TEST_CASE(utrzExpect, sm_exhlevel_Ok);
	RUN_TEST_CASE(utrzExpect, sm_exhlevel_OutOfSequence);
    /* RKH_TE_SM_EX_TSEG */    
   	RUN_TEST_CASE(utrzExpect, sm_extseg_Ok);
	RUN_TEST_CASE(utrzExpect, sm_extseg_OutOfSequence);
    /* RKH_TE_SM_EXE_ACT */
   	RUN_TEST_CASE(utrzExpect, sm_exeAct_Ok);
	RUN_TEST_CASE(utrzExpect, sm_exeAct_OutOfSequence);
	RUN_TEST_CASE(utrzExpect, sm_exeAct_WithUnexpectedArg);
    RUN_TEST_CASE(utrzExpect, sm_exeAct_WithAnyArgs);
}

/* ------------------------------ End of file ------------------------------ */
