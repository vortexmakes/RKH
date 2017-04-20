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
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       test_trace_runner.c
 *  \ingroup    test_trace
 *
 *  \brief      Test runner of trace module
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.11.11  LeFr  v2.4.05  ---
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

TEST_GROUP_RUNNER(trace_filter)
{
	RUN_TEST_CASE(trace_filter, getBitIndex0);
	RUN_TEST_CASE(trace_filter, getBitIndexX);
	RUN_TEST_CASE(trace_filter, setBitIndex0);
	RUN_TEST_CASE(trace_filter, resetBitIndex0);
	RUN_TEST_CASE(trace_filter, setBitIndexX);
	RUN_TEST_CASE(trace_filter, resetBitIndexX);
}

TEST_GROUP_RUNNER(trace)
{
	RUN_TEST_CASE(trace, filEventsAreOnAfterInit);
	RUN_TEST_CASE(trace, turnOffOneFilEvent);
	RUN_TEST_CASE(trace, turnOnOneFilEvent);
	RUN_TEST_CASE(trace, turnOffMultipleFilEvent);
	RUN_TEST_CASE(trace, allOffFilEvent);
	RUN_TEST_CASE(trace, allOnFilEvent);
	RUN_TEST_CASE(trace, isOnOffFilEvent);
    RUN_TEST_CASE(trace, setAllEventsFromOneGroup);
	RUN_TEST_CASE(trace, upperAndLowerBoundsFilEvent);
	RUN_TEST_CASE(trace, outOfBoundsProducesRuntimeError);

	RUN_TEST_CASE(trace, turnOffOneGroup);
	RUN_TEST_CASE(trace, turnOnOneGroup);
	RUN_TEST_CASE(trace, allOnOffGroup);
    RUN_TEST_CASE(trace, turnOnOffMultipleGroups);
    RUN_TEST_CASE(trace, turnOffOneGroupChangedItsEventFilters);

	RUN_TEST_CASE(trace, turnOffOneSymFil);
	RUN_TEST_CASE(trace, turnOnOneSymFil);
	RUN_TEST_CASE(trace, turnOnOffMultipleSymFil);
	RUN_TEST_CASE(trace, allOffOnSymFil);
	RUN_TEST_CASE(trace, isOnOffSymFil);
	RUN_TEST_CASE(trace, upperAndLowerBoundsSymFil);
	RUN_TEST_CASE(trace, Fails_outOfBoundsProducesRuntimeErrorInSetSymFil);
	RUN_TEST_CASE(trace, Fails_outOfBoundsProducesRuntimeErrorInGetSymFil);
}

TEST_GROUP_RUNNER(trace_stream)
{
	RUN_TEST_CASE(trace_stream, FlagAfterInit);
	RUN_TEST_CASE(trace_stream, NotFullAfterInit);
	RUN_TEST_CASE(trace_stream, NotEmptyThenEmpty);
	RUN_TEST_CASE(trace_stream, GetPutOneValue);
	RUN_TEST_CASE(trace_stream, GetPutAFew);
	RUN_TEST_CASE(trace_stream, IsFull);
	RUN_TEST_CASE(trace_stream, EmptyToFullToEmpty);
	RUN_TEST_CASE(trace_stream, WrapAround);
	RUN_TEST_CASE(trace_stream, GetFromEmptyReturnsNull);
	RUN_TEST_CASE(trace_stream, GetContinuousBlock);
}

TEST_GROUP_RUNNER(trace_args)
{
	RUN_TEST_CASE(trace_args, InsertRecordHeader);
	RUN_TEST_CASE(trace_args, InsertRecordEnd);
	RUN_TEST_CASE(trace_args, InsertU8Value);
	RUN_TEST_CASE(trace_args, InsertEscapedValues);
	RUN_TEST_CASE(trace_args, InsertU16Value);
	RUN_TEST_CASE(trace_args, InsertU32Value);
	RUN_TEST_CASE(trace_args, InsertString);
	RUN_TEST_CASE(trace_args, InsertObject);
	RUN_TEST_CASE(trace_args, InsertSignal);
	RUN_TEST_CASE(trace_args, InsertState);
	RUN_TEST_CASE(trace_args, InsertRecord);
	RUN_TEST_CASE(trace_args, InsertFwkEpoolRecord);
	RUN_TEST_CASE(trace_args, InsertFwkActorRecord);
	RUN_TEST_CASE(trace_args, InsertSmaActivateRecord);
	RUN_TEST_CASE(trace_args, InsertSmaGetRecord);
	RUN_TEST_CASE(trace_args, InsertSmaPostFifoRecord);
	RUN_TEST_CASE(trace_args, InsertSmaPostLifoRecord);
	RUN_TEST_CASE(trace_args, InsertFwkAeRecord);
	RUN_TEST_CASE(trace_args, InsertFwkGcrRecord);
	RUN_TEST_CASE(trace_args, InsertFwkEpregRecord);
	RUN_TEST_CASE(trace_args, InsertFwkStateRecord);
	RUN_TEST_CASE(trace_args, InsertFwkPseudoStateRecord);
	RUN_TEST_CASE(trace_args, InsertDispatchRecordWithInvalidSignal);
}

/* ------------------------------ End of file ------------------------------ */
