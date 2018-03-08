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
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       test_smInitialPseudostate.c
 *  \ingroup    test_sm
 *  \brief      Unit test for state machine module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_sm State Machine
 *  @{
 *  \brief      Unit test for state machine module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.02.16  LeFr  v1.0.00  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "unitrazer.h"
#include "rkhfwk_dynevt.h"
#include "common.h"
#include "smInitialPseudoTest.h"
#include "Mock_smInitialPseudoTestAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
static RKH_STATIC_EVENT(evA, A);
static RKH_STATIC_EVENT(evB, B);
static RKH_STATIC_EVENT(evC, C);
static RKH_STATIC_EVENT(evD, D);
static RKH_STATIC_EVENT(evE, E);
static RKH_STATIC_EVENT(evF, F);
extern const RKH_EVT_T evCreation;

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(InitPseudostate);

/* ---------------------------- Local variables ---------------------------- */
static const RKH_ST_T *targetStates[16], *exitStates[16], *entryStates[16];
int GlobalExpectCount;
int GlobalVerifyOrder;
char *GlobalOrderError;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
loadStateMachineSymbols(void)
{
    RKH_TR_FWK_AO(smInitialPseudoTest);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s0);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s1);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s11);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s12);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s2);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s21);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s211);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s3);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s31);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s32);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s33);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s331);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s4);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s41);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s411);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s5);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s51);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s511);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s52);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s6);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s61);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s62);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s1Hist);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s2Hist);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s3Hist);
    RKH_TR_FWK_SIG(A);
    RKH_TR_FWK_SIG(B);
    RKH_TR_FWK_SIG(C);
    RKH_TR_FWK_SIG(D);
}

static void
setRKHTraceFilters(void)
{
    RKH_FILTER_OFF_ALL_SIGNALS();
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_SM);
    RKH_FILTER_OFF_SMA(smInitialPseudoTest);
    RKH_FILTER_OFF_EVENT(RKH_TE_FWK_ASSERT);
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(InitPseudostate)
{
    sm_init();
    sm_ntrnact_ignore();
    rkh_sm_clear_history(&smIPT_s1Hist);

    loadStateMachineSymbols();
    setRKHTraceFilters();
    Mock_smInitialPseudoTestAct_Init();
}

TEST_TEAR_DOWN(InitPseudostate)
{
    sm_verify(); /* Makes sure there are no unused expectations, if */
                 /* there are, this function causes the test to fail. */
    sm_cleanup();
    Mock_smInitialPseudoTestAct_Verify();
    Mock_smInitialPseudoTestAct_Destroy();
}

/**
 *  \addtogroup test_smInitialPseudostate Initial pseudostate test group
 *  @{
 *  \name Test cases of InitPseudostate group
 *  @{ 
 */

TEST(InitPseudostate, firstStateAfterInit)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    trnStepExpect(me, &smIPT_s0, NULL, NULL, NULL, &evCreation);

    rkh_sm_init((RKH_SM_T *)me);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToEmptyShHistoryToSimpleState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;
    TargetEntrySt tgEnSt[4] =   {{&smIPT_s1,     &smIPT_s1   },
                                 {&smIPT_s1Hist, NULL        },
                                 {&smIPT_s11,    &smIPT_s11  },
                                 {NULL,          NULL        }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(smInitialPseudoTest);
    smIPT_xS0_Expect(smInitialPseudoTest);
    smIPT_nS1_Expect(smInitialPseudoTest);
    smIPT_tr1_Expect(smInitialPseudoTest, &evA);
    smIPT_nS11_Expect(smInitialPseudoTest);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evA);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evA);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToLoadedShHistory)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;
    TargetEntrySt tgEnSt[4] =   {{&smIPT_s1,     &smIPT_s1   },
                                 {&smIPT_s1Hist, NULL        },
                                 {&smIPT_s12,    &smIPT_s12  },
                                 {NULL,          NULL        }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS1_Expect(me);
    smIPT_nS12_Expect(me);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evA);

    rkh_sm_init((RKH_SM_T *)me);
    setHistory(&smIPT_s1Hist, RKH_STATE_CAST(&smIPT_s12));
    rkh_sm_dispatch((RKH_SM_T *)me, &evA);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToEmptyShHistoryToCmpState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;
    TargetEntrySt tgEnSt[5] =   {{&smIPT_s2,     &smIPT_s2      },
                                 {&smIPT_s2Hist, NULL           },
                                 {&smIPT_s21,    &smIPT_s21     },
                                 {&smIPT_s211,   &smIPT_s211    },
                                 {NULL,          NULL           }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(smInitialPseudoTest);
    smIPT_xS0_Expect(smInitialPseudoTest);
    smIPT_nS2_Expect(smInitialPseudoTest);
    smIPT_nS21_Expect(smInitialPseudoTest);
    smIPT_nS211_Expect(smInitialPseudoTest);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evD);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evD);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToEmptyDeepHistoryToSimpleState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;
    TargetEntrySt tgEnSt[4] =   {{&smIPT_s3,     &smIPT_s3   },
                                 {&smIPT_s3Hist, NULL        },
                                 {&smIPT_s31,    &smIPT_s31  },
                                 {NULL,          NULL        }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS3_Expect(me);
    smIPT_nS31_Expect(me);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evB);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToLoadedDeepHistory)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;
    TargetEntrySt tgEnSt[4] =   {{&smIPT_s3,     &smIPT_s3   },
                                 {&smIPT_s3Hist, NULL        },
                                 {&smIPT_s32,    &smIPT_s32  },
                                 {NULL,          NULL        }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS3_Expect(me);
    smIPT_nS32_Expect(me);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evB);

    rkh_sm_init((RKH_SM_T *)me);
    setHistory(&smIPT_s3Hist, RKH_STATE_CAST(&smIPT_s32));
    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToLoadedDeepHistoryToNestedState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;
    TargetEntrySt tgEnSt[5] =   {{&smIPT_s3,     &smIPT_s3   },
                                 {&smIPT_s3Hist, NULL        },
                                 {&smIPT_s331,   &smIPT_s33  },
                                 {NULL,          &smIPT_s331 },
                                 {NULL,          NULL        }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS3_Expect(me);
    smIPT_nS33_Expect(me);
    smIPT_nS331_Expect(me);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evB);

    rkh_sm_init((RKH_SM_T *)me);
    setHistory(&smIPT_s3Hist, RKH_STATE_CAST(&smIPT_s331));
    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToEmptyShHistoryToNestedSimpleState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;
    TargetEntrySt tgEnSt[5] =   {{&smIPT_s4,     &smIPT_s4   },
                                 {&smIPT_s4Hist, NULL        },
                                 {&smIPT_s411,   &smIPT_s41  },
                                 {NULL,          &smIPT_s411 },
                                 {NULL,          NULL        }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(smInitialPseudoTest);
    smIPT_xS0_Expect(smInitialPseudoTest);
    smIPT_nS4_Expect(smInitialPseudoTest);
    smIPT_nS41_Expect(smInitialPseudoTest);
    smIPT_nS411_Expect(smInitialPseudoTest);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evC);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToBranchToSimpleState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = RKH_CAST(SmInitialPseudoTest, 
                                       smInitialPseudoTest);
    TargetEntrySt tgEnSt[4] =   {{&smIPT_s5,      &smIPT_s5  },
                                 {&smIPT_choice1, NULL       },
                                 {&smIPT_s52,    &smIPT_s52  },
                                 {NULL,          NULL        }};

    //stateList_create(targetStates, 3, &smIPT_s5, &smIPT_choice1, &smIPT_s52);
    stateList_create(exitStates, 1, &smIPT_s0);
    //stateList_create(entryStates, 2, &smIPT_s5, &smIPT_s52);

    /* Expect call actions */
    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS5_Expect(me);
    smIPT_tr2_Expect(me, &evE);
    smIPT_isC1_ExpectAndReturn(me, &evE, RKH_TRUE);
    smIPT_nS52_Expect(me);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evE);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)me, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToBranchToCmpState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = RKH_CAST(SmInitialPseudoTest, 
                                       smInitialPseudoTest);
    TargetEntrySt tgEnSt[5] =   {{&smIPT_s5,      &smIPT_s5   },
                                 {&smIPT_choice1, NULL        },
                                 {&smIPT_s51,     &smIPT_s51  },
                                 {&smIPT_s511,    &smIPT_s511 },
                                 {NULL,           NULL        }};

    //stateList_create(targetStates, 4, &smIPT_s5, &smIPT_choice1, &smIPT_s51, 
    //                 &smIPT_s511);
    stateList_create(exitStates, 1, &smIPT_s0);
    //stateList_create(entryStates, 3, &smIPT_s5, &smIPT_s51, &smIPT_s511);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS5_Expect(me);
    smIPT_tr2_Expect(me, &evE);
    smIPT_isC1_ExpectAndReturn(me, &evE, RKH_FALSE);
    smIPT_isC2_ExpectAndReturn(me, &evE, RKH_FALSE);
    smIPT_isC3_ExpectAndReturn(me, &evE, RKH_FALSE);
    smIPT_nS51_Expect(me);
    smIPT_nS511_Expect(me);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evE);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)me, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToBranchToNestedSimpleState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = RKH_CAST(SmInitialPseudoTest, 
                                       smInitialPseudoTest);
    TargetEntrySt tgEnSt[5] =   {{&smIPT_s5,      &smIPT_s5   },
                                 {&smIPT_choice1, NULL        },
                                 {&smIPT_s511,    &smIPT_s51  },
                                 {NULL,           &smIPT_s511 },
                                 {NULL,           NULL        }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS5_Expect(me);
    smIPT_tr2_Expect(me, &evE);
    smIPT_isC1_ExpectAndReturn(me, &evE, RKH_FALSE);
    smIPT_isC2_ExpectAndReturn(me, &evE, RKH_TRUE);
    smIPT_nS51_Expect(me);
    smIPT_nS511_Expect(me);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evE);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)me, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToBranchToNestedCmpState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = RKH_CAST(SmInitialPseudoTest, 
                                       smInitialPseudoTest);
    TargetEntrySt tgEnSt[6] =   {{&smIPT_s5,      &smIPT_s5    },
                                 {&smIPT_choice1, NULL         },
                                 {&smIPT_s512,    &smIPT_s51   },
                                 {NULL,           &smIPT_s512  },
                                 {&smIPT_s5121,   &smIPT_s5121 },
                                 {NULL,           NULL         }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS5_Expect(me);
    smIPT_tr2_Expect(me, &evE);
    smIPT_isC1_ExpectAndReturn(me, &evE, RKH_FALSE);
    smIPT_isC2_ExpectAndReturn(me, &evE, RKH_FALSE);
    smIPT_isC3_ExpectAndReturn(me, &evE, RKH_TRUE);
    smIPT_nS51_Expect(me);
    smIPT_nS512_Expect(me);
    smIPT_nS5121_Expect(me);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evE);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)me, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToJunctionToSimpleState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = RKH_CAST(SmInitialPseudoTest, 
                                       smInitialPseudoTest);
    TargetEntrySt tgEnSt[4] =   {{&smIPT_s6,        &smIPT_s6   },
                                 {&smIPT_junction1, NULL        },
                                 {&smIPT_s62,       &smIPT_s62  },
                                 {NULL,             NULL        }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS6_Expect(me);
    smIPT_isC1_ExpectAndReturn(me, &evF, RKH_TRUE);
    smIPT_tr3_Expect(me, &evF);
    smIPT_nS62_Expect(me);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evF);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)me, &evF);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToJunctionToCmpState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = RKH_CAST(SmInitialPseudoTest, 
                                       smInitialPseudoTest);
    TargetEntrySt tgEnSt[5] =   {{&smIPT_s6,        &smIPT_s6   },
                                 {&smIPT_junction1, NULL        },
                                 {&smIPT_s61,       &smIPT_s61  },
                                 {&smIPT_s611,      &smIPT_s611 },
                                 {NULL,             NULL        }};

    stateList_create(exitStates, 1, &smIPT_s0);

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS6_Expect(me);
    smIPT_isC1_ExpectAndReturn(me, &evF, RKH_FALSE);
    smIPT_isC2_ExpectAndReturn(me, &evF, RKH_FALSE);
    smIPT_isC3_ExpectAndReturn(me, &evF, RKH_FALSE);
    smIPT_tr3_Expect(me, &evF);
    smIPT_nS61_Expect(me);
    smIPT_nS611_Expect(me);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, tgEnSt, exitStates, &evF);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)me, &evF);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, SMInitialToSimpleState)
{
    UtrzProcessOut *p;
    RKH_SM_T *me = smInitial0;

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smI0_nS0_Expect(me);
    trnStepExpect(me, &smI0_s0, NULL, NULL, NULL, NULL, &evCreation);

    rkh_sm_init(me);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, SMInitialToCmpState)
{
    UtrzProcessOut *p;
    RKH_SM_T *me = smInitial1;

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smI1_nS0_Expect(me);
    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smI1_nS01_Expect(me);
    sm_init_expect(RKH_STATE_CAST(&smI1_s0));
    sm_trn_expect(RKH_STATE_CAST(&smI1_s0), RKH_STATE_CAST(&smI1_s0));
    sm_tsState_expect(RKH_STATE_CAST(&smI1_s0));
    sm_enstate_expect(RKH_STATE_CAST(&smI1_s0));
    sm_tsState_expect(RKH_STATE_CAST(&smI1_s01));
    sm_enstate_expect(RKH_STATE_CAST(&smI1_s01));
    sm_nenex_expect(2, 0);
    sm_state_expect(RKH_STATE_CAST(&smI1_s01));
    sm_evtProc_expect();

    rkh_sm_init(me);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, SMInitialToNestedSimpleState)
{
    UtrzProcessOut *p;
    RKH_SM_T *me = smInitial2;

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smI2_nS0_Expect(me);
    smI2_nS01_Expect(me);
    sm_init_expect(RKH_STATE_CAST(&smI2_s01));
    sm_trn_expect(RKH_STATE_CAST(&smI2_s01), RKH_STATE_CAST(&smI2_s01));
    sm_tsState_expect(RKH_STATE_CAST(&smI2_s01));
    sm_enstate_expect(RKH_STATE_CAST(&smI2_s0));
    sm_enstate_expect(RKH_STATE_CAST(&smI2_s01));
    sm_nenex_expect(2, 0);
    sm_state_expect(RKH_STATE_CAST(&smI2_s01));
    sm_evtProc_expect();

    rkh_sm_init(me);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, SMInitialToNestedCmpState)
{
    UtrzProcessOut *p;
    RKH_SM_T *me = smInitial3;

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smI3_nS0_Expect(me);
    smI3_nS01_Expect(me);
    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smI3_nS011_Expect(me);
    sm_init_expect(RKH_STATE_CAST(&smI3_s01));
    sm_trn_expect(RKH_STATE_CAST(&smI3_s01), RKH_STATE_CAST(&smI3_s01));
    sm_tsState_expect(RKH_STATE_CAST(&smI3_s01));
    sm_enstate_expect(RKH_STATE_CAST(&smI3_s0));
    sm_enstate_expect(RKH_STATE_CAST(&smI3_s01));
    sm_tsState_expect(RKH_STATE_CAST(&smI3_s011));
    sm_enstate_expect(RKH_STATE_CAST(&smI3_s011));
    sm_nenex_expect(3, 0);
    sm_state_expect(RKH_STATE_CAST(&smI3_s011));
    sm_evtProc_expect();

    rkh_sm_init(me);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, SMInitialToJunctionToSimpleState)
{
    UtrzProcessOut *p;
    RKH_SM_T *me = smInitial4;

    smIPT_isC1_ExpectAndReturn(me, &evCreation, RKH_TRUE);
    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_tr1_Expect(me, &evCreation);
    smI4_nS0_Expect(me);
    sm_init_expect(RKH_STATE_CAST(&smI4_junction1));
    sm_trn_expect(RKH_STATE_CAST(&smI4_junction1), 
                  RKH_STATE_CAST(&smI4_junction1));
    sm_tsState_expect(RKH_STATE_CAST(&smI4_junction1));
    sm_tsState_expect(RKH_STATE_CAST(&smI4_s0));
    sm_enstate_expect(RKH_STATE_CAST(&smI4_s0));
    sm_nenex_expect(1, 0);
    sm_state_expect(RKH_STATE_CAST(&smI4_s0));
    sm_evtProc_expect();

    rkh_sm_init(me);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, SMInitialToJunctionToCmpState)
{
    UtrzProcessOut *p;
    RKH_SM_T *me = smInitial4;

    smIPT_isC1_ExpectAndReturn(me, &evCreation, RKH_FALSE);
    smIPT_isC2_ExpectAndReturn(me, &evCreation, RKH_TRUE);
    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_tr2_Expect(me, &evCreation);
    smI4_nS1_Expect(me);
    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smI4_nS11_Expect(me);
    sm_init_expect(RKH_STATE_CAST(&smI4_junction1));
    sm_trn_expect(RKH_STATE_CAST(&smI4_junction1), 
                  RKH_STATE_CAST(&smI4_junction1));
    sm_tsState_expect(RKH_STATE_CAST(&smI4_junction1));
    sm_tsState_expect(RKH_STATE_CAST(&smI4_s1));
    sm_enstate_expect(RKH_STATE_CAST(&smI4_s1));
    sm_tsState_expect(RKH_STATE_CAST(&smI4_s11));
    sm_enstate_expect(RKH_STATE_CAST(&smI4_s11));
    sm_nenex_expect(2, 0);
    sm_state_expect(RKH_STATE_CAST(&smI4_s11));
    sm_evtProc_expect();

    rkh_sm_init(me);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, SMInitialToBranchToSimpleState)
{
    UtrzProcessOut *p;
    RKH_SM_T *me = smInitial5;

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_isC1_ExpectAndReturn(me, &evCreation, RKH_TRUE);
    smIPT_tr1_Expect(me, &evCreation);
    smI5_nS0_Expect(me);
    sm_init_expect(RKH_STATE_CAST(&smI5_branch1));
    sm_trn_expect(RKH_STATE_CAST(&smI5_branch1), 
                  RKH_STATE_CAST(&smI5_branch1));
    sm_tsState_expect(RKH_STATE_CAST(&smI5_branch1));
    sm_tsState_expect(RKH_STATE_CAST(&smI5_s0));
    sm_enstate_expect(RKH_STATE_CAST(&smI5_s0));
    sm_nenex_expect(1, 0);
    sm_state_expect(RKH_STATE_CAST(&smI5_s0));
    sm_evtProc_expect();

    rkh_sm_init(me);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, SMInitialToBranchToCmpState)
{
    UtrzProcessOut *p;
    RKH_SM_T *me = smInitial5;

    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smIPT_isC1_ExpectAndReturn(me, &evCreation, RKH_FALSE);
    smIPT_isC2_ExpectAndReturn(me, &evCreation, RKH_TRUE);
    smIPT_tr2_Expect(me, &evCreation);
    smI5_nS1_Expect(me);
    smIPT_init_Expect(me, (RKH_EVT_T *)&evCreation);
    smI5_nS11_Expect(me);
    sm_init_expect(RKH_STATE_CAST(&smI5_branch1));
    sm_trn_expect(RKH_STATE_CAST(&smI5_branch1), 
                  RKH_STATE_CAST(&smI5_branch1));
    sm_tsState_expect(RKH_STATE_CAST(&smI5_branch1));
    sm_tsState_expect(RKH_STATE_CAST(&smI5_s1));
    sm_enstate_expect(RKH_STATE_CAST(&smI5_s1));
    sm_tsState_expect(RKH_STATE_CAST(&smI5_s11));
    sm_enstate_expect(RKH_STATE_CAST(&smI5_s11));
    sm_nenex_expect(2, 0);
    sm_state_expect(RKH_STATE_CAST(&smI5_s11));
    sm_evtProc_expect();

    rkh_sm_init(me);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
