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
 *  \file       rkhtype.h
 *  \brief      Defines the data types that uses RKH.
 *
 *  \ingroup    apiPortMisc
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  Initial version
 *  2019.02.1   Daba  v2.4.05  STM32 Port
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHTYPE_H__
#define __RKHTYPE_H__

/* ----------------------------- Include files ----------------------------- */
#if defined(__NO_OFFICIAL_PORT__)
    #include "rkht.h"
#elif defined(__W32STVC__)
    #include "..\..\portable\80x86\win32_st\vc\rkht.h"
#elif defined(__W32MTVC__)
    #include "..\..\portable\80x86\win32_mt\vc\rkht.h"
#elif defined(__LNXGNU__)
    #include "../../portable/80x86/linux_st/gnu/rkht.h"
#elif defined(__S08CW63__)
    #include "..\..\portable\s08\rkhs\cw6_3\rkht.h"
#elif defined(__CFV1CW63__)
    #include "..\..\portable\cfv1\rkhs\cw6_3\rkht.h"
#elif defined(__ARM_CM0CW10__)
    #include "../../portable/arm-cortex/rkhs/arm_cm0/cw_v10/rkht.h"
#elif defined(__ARM_CM4FCW10__)
    #include "../../portable/arm-cortex/rkhs/arm_cm4f/cw_v10/rkht.h"
#elif defined(__KSDK_KDS__)
    #include "..\..\portable\arm-cortex\rkhs\ksdk\kds\rkht.h"
#elif defined(__KSDK_OS_KDS__)
    #include "..\..\portable\arm-cortex\ksdk_os\ucosiii\kds\rkht.h"
#elif defined(__UCOS_V3_03_01__)
    #include "..\..\portable\ucos\v3.03.01\rkht.h"
#elif defined(__ARM_CM3XPRESSO___)
    #include "../../portable/arm-cortex/rkhs/arm_cm3/codered/rkht.h"
#elif defined(__TEST__)
    #include "../../portable/test/rkht.h"
#elif defined(__CIAANXP__)
    #include "../../portable/arm-cortex/rkhs/arm_cm4f/ciaa_nxp/rkht.h"
#elif defined(__STM32__)
    #include "../../portable/arm-cortex/rkhs/arm_cm4f/stm32/rkht.h"
#elif defined(__PLAT_DEF_BY_BUILD__)
    #include "rkht.h"
#else
    #error "rkhtype.h: Platform definition is not found"
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
