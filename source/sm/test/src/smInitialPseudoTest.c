/**
 *  \file       smInitialPseudoTest.c
 *  \ingroup    Test
 *
 *  \brief      State machine to facilitate the test of production code.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.02.16  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "smInitialPseudoTest.h"
#include "smInitialPseudoTestAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ......................... Declares active object ........................ */
RKH_SMA_CREATE(SmInitialPseudoTest, smInitialPseudoTest, 0, HCAL, 
               &smIPT_s0, smIPT_init, NULL);
RKH_SMA_DEF_PTR(smInitialPseudoTest);

/* ................... Declares states and pseudostates .................... */
RKH_CREATE_BASIC_STATE(smIPT_s0, smIPT_nS0, smIPT_xS0, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s0)
    RKH_TRREG(A, NULL, NULL, &smIPT_s1),
    RKH_TRREG(D, NULL, NULL, &smIPT_s2),
    RKH_TRREG(B, NULL, NULL, &smIPT_s3),
    RKH_TRREG(C, NULL, NULL, &smIPT_s4),
    RKH_TRREG(E, NULL, NULL, &smIPT_s5),
    RKH_TRREG(F, NULL, NULL, &smIPT_s6),
RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smIPT_s1);
RKH_CREATE_COMP_REGION_STATE(smIPT_s1, smIPT_nS1, smIPT_xS1, RKH_ROOT, 
                             &smIPT_s1Hist, 
                             NULL, RKH_SHISTORY, NULL, smIPT_tr1, &smIPT_s11, 
                             RKH_GET_HISTORY_STORAGE(smIPT_s1));
RKH_CREATE_TRANS_TABLE(smIPT_s1)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s11, smIPT_nS11, smIPT_xS11, &smIPT_s1, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s11)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s12, smIPT_nS12, smIPT_xS12, &smIPT_s1, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s12)
RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smIPT_s2);
RKH_CREATE_COMP_REGION_STATE(smIPT_s2, smIPT_nS2, smIPT_xS2, RKH_ROOT, 
                             &smIPT_s2Hist, 
                             NULL, RKH_SHISTORY, NULL, NULL, &smIPT_s21, 
                             RKH_GET_HISTORY_STORAGE(smIPT_s2));
RKH_CREATE_TRANS_TABLE(smIPT_s2)
RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smIPT_s21);
RKH_CREATE_COMP_REGION_STATE(smIPT_s21, smIPT_nS21, smIPT_xS21, &smIPT_s2, 
                             &smIPT_s211, 
                             NULL, RKH_NO_HISTORY, NULL, NULL, 
                             NULL, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s21)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s211, smIPT_nS211, smIPT_xS211, &smIPT_s21, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s211)
RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smIPT_s3);
RKH_CREATE_COMP_REGION_STATE(smIPT_s3, smIPT_nS3, smIPT_xS3, RKH_ROOT, 
                             &smIPT_s3Hist, 
                             NULL, RKH_DHISTORY, NULL, NULL, &smIPT_s31, 
                             RKH_GET_HISTORY_STORAGE(smIPT_s3));
RKH_CREATE_TRANS_TABLE(smIPT_s3)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s31, smIPT_nS31, smIPT_xS31, &smIPT_s3, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s31)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s32, smIPT_nS32, smIPT_xS32, &smIPT_s3, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s32)
RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smIPT_s33);
RKH_CREATE_COMP_REGION_STATE(smIPT_s33, smIPT_nS33, smIPT_xS33, &smIPT_s3, 
                             &smIPT_s331, 
                             NULL, RKH_NO_HISTORY, NULL, NULL, 
                             NULL, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s33)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s331, smIPT_nS331, smIPT_xS331, &smIPT_s33, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s331)
RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smIPT_s4);
RKH_CREATE_COMP_REGION_STATE(smIPT_s4, smIPT_nS4, smIPT_xS4, RKH_ROOT, 
                             &smIPT_s4Hist, 
                             NULL, RKH_SHISTORY, NULL, NULL, &smIPT_s411, 
                             RKH_GET_HISTORY_STORAGE(smIPT_s4));
RKH_CREATE_TRANS_TABLE(smIPT_s4)
RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smIPT_s41);
RKH_CREATE_COMP_REGION_STATE(smIPT_s41, smIPT_nS41, smIPT_xS41, &smIPT_s4, 
                             &smIPT_s411, 
                             NULL, RKH_NO_HISTORY, NULL, NULL, 
                             NULL, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s41)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s411, smIPT_nS411, smIPT_xS411, &smIPT_s41, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s411)
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_REGION_STATE(smIPT_s5, smIPT_nS5, smIPT_xS5, RKH_ROOT, 
                             &smIPT_choice1, smIPT_tr2, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s5)
RKH_END_TRANS_TABLE

RKH_CREATE_CHOICE_STATE(smIPT_choice1);
RKH_CREATE_BRANCH_TABLE(smIPT_choice1)
    RKH_BRANCH(smIPT_isC1,  NULL,	&smIPT_s52),
    RKH_BRANCH(smIPT_isC2,  NULL,	&smIPT_s511),
    RKH_BRANCH(smIPT_isC3,  NULL,	&smIPT_s512),
	RKH_BRANCH(ELSE,        NULL,   &smIPT_s51),
RKH_END_BRANCH_TABLE

RKH_CREATE_COMP_REGION_STATE(smIPT_s51, smIPT_nS51, smIPT_xS51, &smIPT_s5, 
                             &smIPT_s511, NULL, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s51)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s511, smIPT_nS511, smIPT_xS511, &smIPT_s51, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s511)
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_REGION_STATE(smIPT_s512, smIPT_nS512, smIPT_xS512, &smIPT_s51, 
                             &smIPT_s5121, NULL, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s512)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s5121, smIPT_nS5121, smIPT_xS5121, &smIPT_s512, 
                       NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s5121)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s52, smIPT_nS52, smIPT_xS52, &smIPT_s5, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s52)
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_REGION_STATE(smIPT_s6, smIPT_nS6, smIPT_xS6, RKH_ROOT, 
                             &smIPT_junction1, smIPT_tr3, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s6)
RKH_END_TRANS_TABLE

RKH_CREATE_COND_STATE(smIPT_junction1);
RKH_CREATE_BRANCH_TABLE(smIPT_junction1)
    RKH_BRANCH(smIPT_isC1,  NULL,	&smIPT_s62),
    RKH_BRANCH(smIPT_isC2,  NULL,	&smIPT_s611),
    RKH_BRANCH(smIPT_isC3,  NULL,	&smIPT_s612),
	RKH_BRANCH(ELSE,        NULL,   &smIPT_s61),
RKH_END_BRANCH_TABLE

RKH_CREATE_COMP_REGION_STATE(smIPT_s61, smIPT_nS61, smIPT_xS61, &smIPT_s6, 
                             &smIPT_s611, NULL, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s61)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s611, smIPT_nS611, smIPT_xS611, &smIPT_s61, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s611)
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_REGION_STATE(smIPT_s612, smIPT_nS612, smIPT_xS612, &smIPT_s61, 
                             &smIPT_s6121, NULL, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s612)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s6121, smIPT_nS6121, smIPT_xS6121, &smIPT_s612, 
                       NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s6121)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s62, smIPT_nS62, smIPT_xS62, &smIPT_s6, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s62)
RKH_END_TRANS_TABLE

/* ........................ Declares state machine ......................... */
RKH_SM_CREATE(SmInitialPseudoTest, smInitial0, 0, HCAL, 
              &smI0_s0, smIPT_init, NULL);
RKH_SM_DEF_PTR(smInitial0);

/* ................... Declares states and pseudostates .................... */
RKH_CREATE_BASIC_STATE(smI0_s0, smI0_nS0, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(smI0_s0)
RKH_END_TRANS_TABLE

/* ........................ Declares state machine ......................... */
RKH_SM_CREATE(SmInitialPseudoTest, smInitial1, 0, HCAL, 
              &smI1_s0, smIPT_init, NULL);
RKH_SM_DEF_PTR(smInitial1);

/* ................... Declares states and pseudostates .................... */
RKH_CREATE_COMP_REGION_STATE(smI1_s0, smI1_nS0, NULL, RKH_ROOT, 
                             &smI1_s01, smIPT_init, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smI1_s0)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smI1_s01, smI1_nS01, NULL, &smI1_s0, NULL);
RKH_CREATE_TRANS_TABLE(smI1_s01)
RKH_END_TRANS_TABLE

/* ........................ Declares state machine ......................... */
RKH_SM_CREATE(SmInitialPseudoTest, smInitial2, 0, HCAL, 
              &smI2_s01, smIPT_init, NULL);
RKH_SM_DEF_PTR(smInitial2);

/* ................... Declares states and pseudostates .................... */
RKH_CREATE_COMP_REGION_STATE(smI2_s0, smI2_nS0, NULL, RKH_ROOT, 
                             &smI2_s01, smIPT_init, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smI2_s0)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smI2_s01, smI2_nS01, NULL, &smI2_s0, NULL);
RKH_CREATE_TRANS_TABLE(smI2_s01)
RKH_END_TRANS_TABLE

/* ........................ Declares state machine ......................... */
RKH_SM_CREATE(SmInitialPseudoTest, smInitial3, 0, HCAL, 
              &smI3_s01, smIPT_init, NULL);
RKH_SM_DEF_PTR(smInitial3);

/* ................... Declares states and pseudostates .................... */
RKH_CREATE_COMP_REGION_STATE(smI3_s0, smI3_nS0, NULL, RKH_ROOT, 
                             &smI3_s01, smIPT_init, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smI3_s0)
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_REGION_STATE(smI3_s01, smI3_nS01, NULL, &smI3_s0, 
                             &smI3_s011, smIPT_init, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smI3_s01)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smI3_s011, smI3_nS011, NULL, &smI3_s01, NULL);
RKH_CREATE_TRANS_TABLE(smI3_s011)
RKH_END_TRANS_TABLE

/* ........................ Declares state machine ......................... */
RKH_SM_CREATE(SmInitialPseudoTest, smInitial4, 0, HCAL, 
              &smI4_junction1, smIPT_init, NULL);
RKH_SM_DEF_PTR(smInitial4);

/* ................... Declares states and pseudostates .................... */
RKH_CREATE_COND_STATE(smI4_junction1);
RKH_CREATE_BRANCH_TABLE(smI4_junction1)
    RKH_BRANCH(smIPT_isC1,  smIPT_tr1,	&smI4_s0),
    RKH_BRANCH(smIPT_isC2,  smIPT_tr2,	&smI4_s1),
	RKH_BRANCH(ELSE,        NULL,       &smI4_s0),
RKH_END_BRANCH_TABLE

RKH_CREATE_BASIC_STATE(smI4_s0, smI4_nS0, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(smI4_s0)
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_REGION_STATE(smI4_s1, smI4_nS1, NULL, RKH_ROOT, 
                             &smI4_s11, smIPT_init, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smI4_s1)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smI4_s11, smI4_nS11, NULL, &smI4_s1, NULL);
RKH_CREATE_TRANS_TABLE(smI4_s11)
RKH_END_TRANS_TABLE

/* ........................ Declares state machine ......................... */
RKH_SM_CREATE(SmInitialPseudoTest, smInitial5, 0, HCAL, 
              &smI5_branch1, smIPT_init, NULL);
RKH_SM_DEF_PTR(smInitial5);

/* ................... Declares states and pseudostates .................... */
RKH_CREATE_CHOICE_STATE(smI5_branch1);
RKH_CREATE_BRANCH_TABLE(smI5_branch1)
    RKH_BRANCH(smIPT_isC1,  smIPT_tr1,	&smI5_s0),
    RKH_BRANCH(smIPT_isC2,  smIPT_tr2,	&smI5_s1),
	RKH_BRANCH(ELSE,        NULL,       &smI5_s1),
RKH_END_BRANCH_TABLE

RKH_CREATE_BASIC_STATE(smI5_s0, smI5_nS0, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(smI5_s0)
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_REGION_STATE(smI5_s1, smI5_nS1, NULL, RKH_ROOT, 
                             &smI5_s11, smIPT_init, 
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(smI5_s1)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smI5_s11, smI5_nS11, NULL, &smI5_s1, NULL);
RKH_CREATE_TRANS_TABLE(smI5_s11)
RKH_END_TRANS_TABLE

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
