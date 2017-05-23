/**
 *  \file       smPseudoTest.c
 *  \ingroup    Test
 *
 *  \brief      State machine to facilitate the test of production code.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */

#include "rkh.h"
#include "smPseudoTest.h"
#include "smPseudoTestAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/*
 *	Defines SMA (active object) 'smPseudoTest'.
 */
RKH_SMA_CREATE(SmPseudoTest, smPseudoTest, 0, HCAL, &smPT_waiting, NULL, NULL);
RKH_SMA_DEF_PTR(smPseudoTest);

/*
 *	Defines states and pseudostates.
 */
RKH_CREATE_BASIC_STATE(smPT_waiting, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(smPT_waiting)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smPT_s0, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(smPT_s0)

    RKH_TRREG(A, NULL, NULL, &smPT_s1),
    RKH_TRREG(B, NULL, NULL, &smPT_s1Hist),
    RKH_TRREG(C, NULL, NULL, &smPT_s12Hist),
    RKH_TRREG(D, NULL, NULL, &smPT_s122),
    RKH_TRREG(E, NULL, NULL, &smPT_s2Hist),

RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smPT_s1);
RKH_CREATE_COMP_REGION_STATE(smPT_s1, NULL, NULL, RKH_ROOT, &smPT_s11, NULL, 
                              RKH_SHISTORY, NULL, NULL, NULL, 
                              RKH_GET_HISTORY_STORAGE(smPT_s1));
RKH_CREATE_TRANS_TABLE(smPT_s1)

    RKH_TRREG(A, NULL, NULL, &smPT_s0),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smPT_s11, NULL, NULL, &smPT_s1, NULL);
RKH_CREATE_TRANS_TABLE(smPT_s11)

    RKH_TRREG(B, NULL, NULL, &smPT_s12),

RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smPT_s12);
RKH_CREATE_COMP_REGION_STATE(smPT_s12, NULL, NULL, &smPT_s1, &smPT_s121, NULL,
                              RKH_DHISTORY, NULL, NULL, NULL, 
                              RKH_GET_HISTORY_STORAGE(smPT_s12));
RKH_CREATE_TRANS_TABLE(smPT_s12)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smPT_s121, NULL, NULL, &smPT_s12, NULL);
RKH_CREATE_TRANS_TABLE(smPT_s121)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smPT_s122, NULL, NULL, &smPT_s12, NULL);
RKH_CREATE_TRANS_TABLE(smPT_s122)
RKH_END_TRANS_TABLE

RKH_CREATE_HISTORY_STORAGE(smPT_s2);
RKH_CREATE_COMP_REGION_STATE(smPT_s2, NULL, NULL, RKH_ROOT, &smPT_s21, NULL, 
                              RKH_SHISTORY, smPT_trueGuard, smPT_trS2History, 
                              &smPT_s22, 
                              RKH_GET_HISTORY_STORAGE(smPT_s2));
RKH_CREATE_TRANS_TABLE(smPT_s2)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smPT_s21, NULL, NULL, &smPT_s2, NULL);
RKH_CREATE_TRANS_TABLE(smPT_s21)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(smPT_s22, NULL, NULL, &smPT_s2, NULL);
RKH_CREATE_TRANS_TABLE(smPT_s22)
RKH_END_TRANS_TABLE

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
