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

TEST_GROUP_RUNNER(utrzIgnore)
{
   /* RKH_TE_SM_INIT */
   /* RKH_TE_SM_CLRH */    
   /* RKH_TE_SM_TRN */
	RUN_TEST_CASE(utrzIgnore, sm_trn_Ok);
	RUN_TEST_CASE(utrzIgnore, sm_trn_OneArg);
	RUN_TEST_CASE(utrzIgnore, sm_trn_OneArgBeforeExpect);

    /* RKH_TE_SM_STATE */
    /* RKH_TE_SM_ENSTATE */
    /* RKH_TE_SM_EXSTATE */
    /* RKH_TE_SM_NENEX */
    /* RKH_TE_SM_NTRNACT */
    /* RKH_TE_SM_TS_STATE */
    /* RKH_TE_SM_EVT_PROC */
    /* RKH_TE_SM_EVT_NFOUND */
    /* RKH_TE_SM_GRD_FALSE */
    /* RKH_TE_SM_CND_NFOUND */
    /* RKH_TE_SM_UNKN_STATE */
    /* RKH_TE_SM_EX_HLEVEL */
    /* RKH_TE_SM_EX_TSEG */    
    /* RKH_TE_SM_EXE_ACT */
   	RUN_TEST_CASE(utrzIgnore, sm_exeAct_Ok);
	RUN_TEST_CASE(utrzIgnore, sm_exeAct_OneArg);
	RUN_TEST_CASE(utrzIgnore, sm_exeAct_OneArgBeforeExpect);

    
    RUN_TEST_CASE(utrzIgnore, ignoreAnEventOfIgnoredGroup);
    RUN_TEST_CASE(utrzIgnore, ignoreAnOutOfRangeGroup);
    RUN_TEST_CASE(utrzIgnore, ignoreAnOutOfRangeEvent);

    RUN_TEST_CASE(utrzIgnore, verifyFail);

}

/* ------------------------------ End of file ------------------------------ */
