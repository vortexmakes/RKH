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
 *
 * 	Each platform, compiler or processor supported by RKH must have its own 
 * 	platform-dependent file, called rkhport.h by RKH convention. Next, each 
 * 	rkhport.h file must be referenced from rkhplat.h header file, 
 *	located in \\include directory.  The next listing shows an example of 
 *	rkhplat.h, where __CFV1CW63__, and __W32STVC08__ are used to 
 *	instruct the C/C++ compiler to include header files from the specific 
 *	RKH port directory.
 *
 *	\code
 *	#ifdef __CFV1CW63__
 *		#include "..\portable\cfv1\rkhs\cw6_3\rkhport.h"
 *	#endif
 *
 *	#ifdef __W32STVC08__
 *		#include "..\portable\80x86\win32_st\vc08\rkhport.h"
 *	#endif
 *	...
 *	\endcode
 *
 *	The idea behind conditional compilation is that a rkhport.h can be 
 *	selectively compiled, depending upon whether a specific value has been 
 *	defined.
 *
 *	\note
 *	The path of platform-dependent file must be relative.
 */


#ifndef __RKHPLAT_H__
#define __RKHPLAT_H__


#ifdef __CFV1CW63__
	#include "..\portable\cfv1\rkhs\cw6_3\rkhport.h"
#endif

#ifdef __W32STVC08__
	#include "..\portable\80x86\win32_st\vc08\rkhport.h"
#endif

/**
 * 	\brief
 *	If RKHROM has not been defined then	rkhport.h has not yet been 
 *	included - as every rkhport.h provides a RKHROM definition.
 */

#ifndef RKHROM
	#error "rkhplat.h: Missing definition of platform to be used.\
	See Porting chapter in readme file for more information"
#endif


#endif
