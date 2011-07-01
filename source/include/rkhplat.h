/*
 *	file: rkhplat.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 28, 2010
 *
 * 	Copyright (C) 2010 Leandro Francucci. All rights reserved.
 *
 * 	RKH is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 *  RKH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RKH, see copying.txt file.
 *
 * Contact information:
 * RKH web site:	http://
 * e-mail:			francuccilea@gmail.com
 */

/**
 * 	\file rkhplat.h
 *	\brief
 *	RKH platform-dependent interface.
 */


#ifndef __RKHPLAT_H__
#define __RKHPLAT_H__


#ifdef __CWS08__
	#include "..\portable\cws08\rkhport.h"
#endif

#ifdef __VC__
	#include "..\portable\vc08\rkhport.h"
#endif

#ifdef __VCRKSYS__
	#include "..\portable\vc08rksys\rkhport.h"
#endif

#ifdef __LNXGCC__
   	#include "lnxgcc/rkhport.h"
#endif

#ifdef __CWS08RKSYS__
	#include "..\portable\cws08rksys\rkhport.h"
#endif


/*
 *	If rkhrom has not been defined then	rkhport.h has not yet been 
 *	included - as every rkhport.h provides a rkhrom definition.
 */

#ifndef rkhrom
	#error "rkhplat.h: Missing definition of platform to be used.\
	See Porting chapter in readme file for more information"
#endif


#endif
