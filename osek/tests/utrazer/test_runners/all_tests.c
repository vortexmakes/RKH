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
 *  \file       all_tests.c
 *  \ingroup    test_utrz
 *
 *  \brief      Test runner of uTrazer module
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

#include "rkh.h"
#include "unity_fixture.h"
#include "unitrazer.h"
#include "bsp.h"
#include "aotest.h"


/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */

static 
void 
runAllTests(void)
{
	RUN_TEST_GROUP(utrzsm);
	RUN_TEST_GROUP(utrzexeact);
	RUN_TEST_GROUP(utrzExpect);
	RUN_TEST_GROUP(utrzIgnore);
}

/* ---------------------------- Global functions --------------------------- */

int
main(int argc, char *argv[])
{
	bsp_init(argc, argv);
	UnityMain(argc, argv, runAllTests);
    RKH_TRC_CLOSE();
	getchar();
	return EXIT_SUCCESS;
}

/* ------------------------------ End of file ------------------------------ */
