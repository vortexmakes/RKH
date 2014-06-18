/**
 * 	\file
 * 	\ingroup prt
 * 	\brief Visual Studio 2008 Single-Thread port
 * 	\cond
 *  --------------------------------------------------------------------------
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 28, 2012
 *	By:						  LF
 *  --------------------------------------------------------------------------
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
 *  --------------------------------------------------------------------------
 * 	\endcond
 */


#ifndef __RKHT_H__
#define __RKHT_H__


/*
 * 	Portable data types.
 *
 * 	The RKH uses a set of integer quantities. That maybe 
 * 	machine or compiler	dependent.
 *
 * 	Note:
 *
 * 	The 'HUInt' and 'HInt' will normally be the natural size 
 * 	for a particular machine. These types designates an integer 
 * 	type that is usually fastest to operate with among all integer 
 * 	types.
 */

typedef signed char 	rkhi8_t;
typedef signed short 	rkhi16_t;
typedef signed long		rkhi32_t;
typedef unsigned char 	rkhui8_t;
typedef unsigned short 	rkhui16_t;
typedef unsigned long	rkhui32_t;

typedef unsigned int	HUInt;
typedef signed int		HInt;


#endif
