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
 *  \file       rkhsma_prio.c
 *  \brief      Native priority mechanism for active object scheduling
 *  \ingroup    sma
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.15  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhsma_prio.h"
#include "rkhassert.h"
#include "rkhfwk_module.h"
#include "rkhfwk_rdygrp.h"

RKH_MODULE_NAME(rkhsma_prio)

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKHRdyGrp readyGroup;  /* ready group of active objects */

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void 
rkh_smaPrio_init(void)
{
    rkh_rdygrp_init(&readyGroup);
}

rbool_t 
rkh_smaPrio_isNotReady(void)
{
    return rkh_rdygrp_isReady(&readyGroup) == 0;
}

rbool_t 
rkh_smaPrio_isReady(void)
{
    return rkh_rdygrp_isReady(&readyGroup);
}

void 
rkh_smaPrio_setReady(rui8_t prio)
{
    RKH_REQUIRE(prio < RKH_CFG_FWK_MAX_SMA);
    rkh_rdygrp_setReady(&readyGroup, prio);
}

void 
rkh_smaPrio_setUnready(rui8_t prio)
{
    RKH_REQUIRE(prio < RKH_CFG_FWK_MAX_SMA);
    rkh_rdygrp_setUnready(&readyGroup, prio);
}

rui8_t 
rkh_smaPrio_findHighest(void)
{
    return rkh_rdygrp_findHighest(&readyGroup);
}

/* ------------------------------ End of file ------------------------------ */
