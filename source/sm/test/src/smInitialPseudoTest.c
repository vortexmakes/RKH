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
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
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

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
