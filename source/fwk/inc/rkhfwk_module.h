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
 *  \file       rkhfwk_module.h
 *  \brief      Specifies the macros to identify file modules.
 *  \ingroup    fwk
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.17.05  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHFWK_MODULE_H__
#define __RKHFWK_MODULE_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtype.h"
#include "rkhcfg.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *	\brief
 *	This macro appears at the top of each C/C++ source file defining
 *	the version string for that file (module).
 *
 *  \param[in] __fname		file (module) name.
 *  \param[in] __version    file (module) version.
 */
#define RKH_MODULE_VERSION(__fname, __version) \
    static RKHROM char *const m_version = # __version;

/**
 *	\brief
 *	Get the module version.
 */
#define RKH_MODULE_GET_VERSION() \
    ((const char *)m_version);

/**
 *	\brief
 *	This macro appears at the top of each C/C++ source file defining
 *	the description string for that file (module).
 *
 *  \param[in] __fname		file (module) name.
 *  \param[in] __desc	    file (module) description.
 */
#define RKH_MODULE_DESC(__fname, __desc) \
    static RKHROM char *const m_desc = __desc;

/**
 *	\brief
 *	Get the module description.
 */
#define RKH_MODULE_GET_DESC() \
    ((const char *)m_desc)

#if RKH_CFG_FWK_ASSERT_EN == RKH_ENABLED
    /**
     *	\brief
     *	This macro appears at the top of each C/C++ source file defining
     *	a name for that file.
     *
     *  \param[in] __fname		file name where the assertion failed
     *
     *  \ingroup apiAssert
     */
    #define RKH_MODULE_NAME(__fname) \
        static RKHROM char *const m_name = # __fname;

    /**
     *	\brief
     *	This macro appears at the top of each C/C++ source file defining
     *	a name for that file, by means of __FILE__ compiler directive.
     *
     *  \ingroup apiAssert
     */
    #define RKH_THIS_MODULE \
        static RKHROM char *const m_name = __FILE__;

#else
    #define RKH_MODULE_NAME(__fname)
    #define RKH_THIS_MODULE
#endif

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
