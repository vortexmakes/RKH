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
 *  \file       rkhtrc_stream.c
 *  \brief      Trace stream implementation
 *  \ingroup    aptTrc
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.21.04  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhtrc_stream.h"
#include "rkhfwk_bittbl.h"
#include "rkhassert.h"

/* ----------------------------- Local macros ------------------------------ */
/*
 * This macro is needed only if the module requires to check expressions 
 * that ought to be true as long as the program  is running.
 */
RKH_MODULE_NAME(rkhtrc_stream)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static rui8_t trcstm[RKH_CFG_TRC_SIZEOF_STREAM];
static rui8_t *trcin, *trcout, *trcend;
static TRCQTY_T trcqty;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void 
rkh_trcStream_init(void)
{
    trcin = trcout = trcstm;
    trcqty = 0;
    trcend = &trcstm[RKH_CFG_TRC_SIZEOF_STREAM];
    RKH_TRC_U8_RAW(RKH_FLG);
}

rui8_t *
rkh_trc_get(void)
{
    rui8_t *trByte = (rui8_t *)0;

    if (trcqty == 0)
    {
        return trByte;
    }

    trByte = trcout++;
    --trcqty;

    if (trcout >= trcend)
    {
        trcout = trcstm;
    }

    return trByte;
}

rui8_t *
rkh_trc_get_block(TRCQTY_T *nget)
{
    rui8_t *trByte = (rui8_t *)0;
    TRCQTY_T n;

    if (trcqty == (TRCQTY_T)0)
    {
        *nget = (TRCQTY_T)0;
        return trByte;
    }

    trByte = trcout;

    /* Calculates the number of bytes to be retrieved */
    n = (TRCQTY_T)(trcend - trcout);    /* bytes until the end */
    if (n > trcqty)
    {
        n = trcqty;
    }
    if (n > *nget)
    {
        n = *nget;
    }

    *nget = n;
    trcout += n;
    trcqty -= n;

    if (trcout >= trcend)
    {
        trcout = trcstm;
    }

    return trByte;
}

void 
rkh_trc_put(rui8_t b)
{
    *trcin++ = b;
    ++trcqty;

    if (trcin == trcend)
    {
        trcin = trcstm;
    }

    if (trcqty >= RKH_CFG_TRC_SIZEOF_STREAM)
    {
        trcqty = RKH_CFG_TRC_SIZEOF_STREAM;
        trcout = trcin;
    }
}

/* ------------------------------ End of file ------------------------------ */
