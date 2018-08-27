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
 *  \file       test_rkhtrc_record_runner.c
 *  \ingroup    test_trace
 *
 *  \brief      Test runner of filter module
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.20.04  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
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
TEST_GROUP_RUNNER(record)
{

	RUN_TEST_CASE(record, InsertRecordHeader);
	RUN_TEST_CASE(record, InsertRecordEnd);
	RUN_TEST_CASE(record, InsertU8Value);
	RUN_TEST_CASE(record, InsertEscapedValues);
	RUN_TEST_CASE(record, InsertU16Value);
	RUN_TEST_CASE(record, InsertU32Value);
	RUN_TEST_CASE(record, InsertString);
	RUN_TEST_CASE(record, InsertObject);
	RUN_TEST_CASE(record, InsertSignal);
	RUN_TEST_CASE(record, InsertState);
	RUN_TEST_CASE(record, InsertRecord);
	RUN_TEST_CASE(record, InsertFwkEpoolRecord);
	RUN_TEST_CASE(record, InsertFwkActorRecord);
	RUN_TEST_CASE(record, InsertSmaActivateRecord);
	RUN_TEST_CASE(record, InsertSmaGetRecord);
	RUN_TEST_CASE(record, InsertSmaPostFifoRecord);
	RUN_TEST_CASE(record, InsertSmaPostLifoRecord);
	RUN_TEST_CASE(record, InsertFwkAeRecord);
	RUN_TEST_CASE(record, InsertFwkGcrRecord);
	RUN_TEST_CASE(record, InsertFwkEpregRecord);
	RUN_TEST_CASE(record, InsertFwkStateRecord);
	RUN_TEST_CASE(record, InsertFwkPseudoStateRecord);
	RUN_TEST_CASE(record, InsertDispatchRecordWithInvalidSignal);
}

/* ------------------------------ End of file ------------------------------ */
