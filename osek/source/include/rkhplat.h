/**
 * \cond
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 * 	          State-machine framework for reactive embedded systems            
 * 	        
 * 	                    Copyright (C) 2010 Leandro Francucci.
 * 	        All rights reserved. Protected by international copyright laws.
 *
 *
 * 	RKH is free software: you can redistribute it and/or modify it under the 
 * 	terms of the GNU General Public License as published by the Free Software 
 * 	Foundation, either version 3 of the License, or (at your option) any 
 * 	later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY 
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along 
 *  with RKH, see copying.txt file.
 *
 * 	Contact information:
 * 	RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * 	e-mail:			francuccilea@gmail.com
 *
 *  --------------------------------------------------------------------------
 *  File                     : rkhplat.h
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *	\brief 		RKH platform-dependent interface.
 */


#ifndef __RKHPLAT_H__
#define __RKHPLAT_H__


#ifdef __CFV1CW63__
	#include "..\portable\cfv1\rkhs\cw6_3\rkhport.h"
#endif

#ifdef __W32STVC08__
	#include "..\portable\80x86\win32_st\vc08\rkhport.h"
#endif

#ifdef __S08CW63__
	#include "..\portable\s08\rkhs\cw6_3\rkhport.h"
#endif

#ifdef __LNXGNU__
	#include "../portable/80x86/linux_st/gnu/rkhport.h"
#endif

#ifdef __ARM_CM3CRED__
	#include "../portable/arm-cortex/rkhs/arm_cm3/codered/rkhport.h"
#endif

#ifdef __ARM_CM4FCW10__
	#include "../portable/arm-cortex/rkhs/arm_cm4f/cw_v10/rkhport.h"
#endif

#ifdef __ARM_CM4FIAR7_2__
	#include "../portable/arm-cortex/rkhs/arm_cm4f/iar_v7_2/rkhport.h"
#endif

#ifdef __ARM_CM0CW10__
	#include "../portable/arm-cortex/rkhs/arm_cm0/cw_v10/rkhport.h"
#endif

#ifdef __W32MTVC08__
	#include "..\portable\80x86\win32_mt\vc08\rkhport.h"
#endif

#ifdef __UCOS_V3_03_01__ 
	#include "..\portable\ucos\v3.03.01\rkhport.h"
#endif

#ifdef __KSDK_KDS__
	#include "..\portable\arm-cortex\rkhs\ksdk\kds\rkhport.h"
#endif

#ifdef __KSDK_OS_KDS__
	#include "..\portable\arm-cortex\ksdk_os\ucosiii\kds\rkhport.h"
#endif

#ifdef __CIAA_OSEK__
	#include "..\portable\osek\ciaa\rkhport.h"
#endif


/**
 * 	\brief
 *	If RKHROM has not been defined then	\b rkhport.h has not yet been 
 *	included - as every \b rkhport.h provides a RKHROM definition.
 */

#ifndef RKHROM
	#error "rkhplat.h: Missing definition of platform to be used.\
	See Porting chapter in readme file for more information"
#endif


#endif
