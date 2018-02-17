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
    RKH_TRREG(B, NULL, NULL, &smIPT_s12),
RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smIPT_s1);
RKH_CREATE_COMP_REGION_STATE(smIPT_s1, smIPT_nS1, smIPT_xS1, RKH_ROOT, 
                             &smIPT_s1Hist, 
                             NULL, RKH_SHISTORY, NULL, smIPT_tr1, &smIPT_s11, 
                             RKH_GET_HISTORY_STORAGE(smIPT_s1));
RKH_CREATE_TRANS_TABLE(smIPT_s1)
    RKH_TRREG(C, NULL, NULL, &smIPT_s0),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s11, smIPT_nS11, smIPT_xS11, &smIPT_s1, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s11)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smIPT_s12, smIPT_nS12, smIPT_xS12, &smIPT_s1, NULL);
RKH_CREATE_TRANS_TABLE(smIPT_s12)
RKH_END_TRANS_TABLE

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
