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
 *  \file       tzlink.c
 *  \ingroup    Test
 *
 *  \brief      RKH trace & Trazer comunication link.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.11.19  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <stdlib.h>
#include <string.h>
#include "rkh.h"
#include "unity.h"
#include "tzlink.h"
#include "unitrazer.h"
#include "tzparse.h"
#include "rkhfwk_sched.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
RKH_THIS_MODULE
static UtrzProcessOut out;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
execTrazerParser(rui8_t *p, TRCQTY_T n)
{
	while (n--)
    {
#ifdef __UNITRAZER_LIB__
		tzparser_exec(*p++);
#endif
    }
}


/* ---------------------------- Global functions --------------------------- */
UtrzProcessOut *
unitrazer_getLastOut(void)
{
#ifdef __UNITRAZER_LIB__
    UTRZ_RESP_T *p;

    p = unitrazer_get_resp();
    out.status = (p->e == RKH_TE_UT_FAIL) ? UT_PROC_FAIL : UT_PROC_SUCCESS;
    out.line = p->line;
    strncpy(out.msg, p->msg, UT_SIZEOF_MSG);
#else
    out.status = UT_PROC_SUCCESS;
    out.line = 0;
    strcpy(out.msg, "");
#endif
    return &out;
}

void
unitrazer_resetOut(void)
{
    out.line = 0;
    out.msg[0] = '\0';
    out.status = UT_PROC_INIT;
}

void
rkh_hook_putTrcEvt(void)
{
#ifdef __UNITRAZER_LIB__
   UTRZ_RESP_T *p;

   RKH_TRC_FLUSH();
   p = unitrazer_get_resp();

   UNITY_TEST_ASSERT(p->e != RKH_TE_UT_FAIL, p->line, p->msg);
#endif
}

#if RKH_CFG_TRC_EN == RKH_ENABLED
void
rkh_trc_open(void)
{
    rkh_trc_init();
    unitrazer_start();
    RKH_TRC_SEND_CFG(1);
}

void
rkh_trc_close(void)
{
}

RKH_TS_T
rkh_trc_getts(void)
{
    return (RKH_TS_T)0;
}

void
rkh_trc_flush(void)
{
    rui8_t *blk;
    TRCQTY_T nbytes;
    RKH_SR_ALLOC();

    FOREVER
    {
        nbytes = (TRCQTY_T)1024;

        RKH_ENTER_CRITICAL_();
        blk = rkh_trc_get_block(&nbytes);
        RKH_EXIT_CRITICAL_();

        if ((blk != (rui8_t *)0))
        {
            while(nbytes--)
            {
#ifdef __UNITRAZER_LIB__
                tzparser_exec(*blk++);
#endif
            }
            break;
        }
        else
        {
            break;
        }
    }
}
#endif

void
tzlink_open(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    RKH_TRC_OPEN();
#ifdef __UNITRAZER_LIB__
    unitrazer_log_start();
#endif
}

/* ------------------------------ End of file ------------------------------ */
