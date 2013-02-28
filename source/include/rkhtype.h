/*
 *	file: rkhtype.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 28, 2012
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
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			francuccilea@gmail.com
 */

/**
 * 	\file rkhtype.h
 *	\brief
 *	This file defines the data types that uses RKH.
 *
 * 	The RKH uses a set of integer quantities. That maybe machine or compiler 
 * 	dependent. These types must be defined in \b rkht.h file. The following 
 * 	listing shows the required data type definitions:
 *
 * 	\code
 *  // Denotes a signed integer type with a width of exactly 8 bits
 *  typedef signed char 	rkhi8_t;
 *
 *  // Denotes a signed integer type with a width of exactly 16 bits
 *  typedef signed short 	rkhi16_t;
 *
 *  // Denotes a signed integer type with a width of exactly 32 bits
 *  typedef signed long		rkhi32_t;
 *
 *  // Denotes an unsigned integer type with a width of exactly 8 bits
 *  typedef unsigned char 	rkhui8_t;
 *
 *  // Denotes an unsigned integer type with a width of exactly 16 bits
 *  typedef unsigned short 	rkhui16_t;
 *
 *  // Denotes an unsigned integer type with a width of exactly 32 bits
 *  typedef unsigned long	rkhui32_t;
 *
 *  // Denotes an unsigned integer type that is usually fastest to operate with 
 *  // among all integer types.
 *  typedef unsigned int	HUInt;
 *
 *  // Denotes a signed integer type that is usually fastest to operate with 
 *  // among all integer types.
 *  typedef signed int		HInt;
 *  \endcode
 *
 * 	Next, each \b rkht.h file must be referenced from \b rkhtype.h header 
 * 	file, located in \\include directory.  The next listing shows an example 
 * 	of \b rkhtype.h, where __CFV1CW63__, and __W32STVC08__ are used to 
 *	instruct the C/C++ compiler to include header files from the specific 
 *	RKH port directory. The key point of the design is that all 
 *	platform-independent RKH source files include the same \b rkhtype.h 
 *	header file as the application source files.
 *
 *	\code
 *	#ifdef __CFV1CW63__
 *		#include "..\portable\cfv1\rkhs\cw6_3\rkht.h"
 *	#endif
 *
 *	#ifdef __W32STVC08__
 *		#include "..\portable\80x86\win32_st\vc08\rkht.h"
 *	#endif
 *	...
 *	\endcode
 *
 *	The idea behind conditional compilation is that a \b rkht.h can be 
 *	selectively compiled, depending upon whether a specific value has been 
 *	defined.
 *
 *	\note
 *	The path of platform-dependent file must be relative.
 */


#ifndef __RKHTYPE_H__
#define __RKHTYPE_H__


#ifdef __CFV1CW63__
	#include "..\portable\cfv1\rkhs\cw6_3\rkht.h"
#endif

#ifdef __W32STVC08__
	#include "..\portable\80x86\win32_st\vc08\rkht.h"
#endif

#ifdef __S08CW63__
	#include "..\portable\s08\rkhs\cw6_3\rkht.h"
#endif

#ifdef __LNXGNU__
	#include "../portable/80x86/linux_st/gnu/rkht.h"
#endif


#endif
