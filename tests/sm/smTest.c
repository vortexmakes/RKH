/**
 *  \file       smTest.c
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
#include "smTest.h"
#include "smTestAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */

/*
 *	Defines SMA (active object) 'smTest'.
 */
RKH_SMA_CREATE(SmTest, smTest, 0, HCAL, &waiting, smTest_init, NULL);

/*
 *	Defines states and pseudostates.
 */
RKH_CREATE_BASIC_STATE(waiting, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(waiting)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(s0, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(s0)

    RKH_TRREG(A, NULL, NULL, &s1),
    RKH_TRREG(B, NULL, NULL, &s21),
    RKH_TRREG(D, NULL, NULL, &s22),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(s1, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(s1)

    RKH_TRREG(A, NULL, NULL, &s1),

RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE(s2, NULL, NULL, RKH_ROOT, &s21, NULL);
RKH_CREATE_TRANS_TABLE(s2)

    RKH_TRREG(A, NULL, NULL, &s0),
    RKH_TRREG(D, NULL, NULL, &s21),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(s21, NULL, NULL, &s2, NULL);
RKH_CREATE_TRANS_TABLE(s21)

    RKH_TRREG(B, NULL, NULL, &s0),
    RKH_TRREG(C, NULL, NULL, &s2),

RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE(s22, NULL, NULL, &s2, &s221, NULL);
RKH_CREATE_TRANS_TABLE(s22)

    RKH_TRREG(B, NULL, NULL, &s0),
    RKH_TRREG(C, NULL, NULL, &s3),
    RKH_TRREG(D, NULL, NULL, &s22),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(s221, NULL, NULL, &s22, NULL);
RKH_CREATE_TRANS_TABLE(s221)
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE(s3, NULL, NULL, RKH_ROOT, &s31, NULL);
RKH_CREATE_TRANS_TABLE(s3)

    RKH_TRREG(A, NULL, NULL, &s3),
    RKH_TRREG(B, NULL, NULL, &s2),
    RKH_TRREG(C, NULL, NULL, &s22),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(s31, NULL, NULL, &s3, NULL);
RKH_CREATE_TRANS_TABLE(s31)

    RKH_TRREG(D, NULL, NULL, &s31),

RKH_END_TRANS_TABLE

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
