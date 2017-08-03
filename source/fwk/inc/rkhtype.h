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
 *  \file       rkhtype.h
 *  \brief      Defines the data types that uses RKH.
 *
 *  \ingroup    apiPortMisc
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHTYPE_H__
#define __RKHTYPE_H__

/* ----------------------------- Include files ----------------------------- */
#ifdef __W32STVC__
    #include "..\..\portable\80x86\win32_st\vc\rkht.h"
#endif

#ifdef __W32MTVC__
    #include "..\..\portable\80x86\win32_mt\vc\rkht.h"
#endif

#ifdef __LNXGNU__
    #include "../../portable/80x86/linux_st/gnu/rkht.h"
#endif

#ifdef __S08CW63__
    #include "..\..\portable\s08\rkhs\cw6_3\rkht.h"
#endif

#ifdef __CFV1CW63__
    #include "..\..\portable\cfv1\rkhs\cw6_3\rkht.h"
#endif

#ifdef __ARM_CM0CW10__
    #include "../../portable/arm-cortex/rkhs/arm_cm0/cw_v10/rkht.h"
#endif

#ifdef __ARM_CM4FCW10__
    #include "../../portable/arm-cortex/rkhs/arm_cm4f/cw_v10/rkht.h"
#endif

#ifdef __KSDK_KDS__
    #include "..\..\portable\arm-cortex\rkhs\ksdk\kds\rkht.h"
#endif

#ifdef __KSDK_OS_KDS__
    #include "..\..\portable\arm-cortex\ksdk_os\ucosiii\kds\rkht.h"
#endif

#ifdef __UCOS_V3_03_01__
    #include "..\..\portable\ucos\v3.03.01\rkht.h"
#endif

#ifdef __ARM_CM3XPRESSO___
    #include "../../portable/arm-cortex/rkhs/arm_cm3/codered/rkht.h"
#endif

#ifdef __TEST__
    #include "../../portable/test/rkht.h"
#endif

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
