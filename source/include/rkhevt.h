/*
 *	file: rkhevt.h
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
 * e-mail:			lf@vxtsolutions.com.ar
 */

/**
 * 	\file rkhevt.h
 *
 *	\brief
 * 	Event data type and other related macros.
 *
 * 	This header file must be included in all modules (*.c files) that use RKH.
 */


#ifndef __RKHEVT_H__
#define __RKHEVT_H__


#include "rkhtype.h"
#include "rkhcfg.h"


#define RCE( e )			(( RKHEVT_T*)(e))


/** 
 * 	Defines the size of event. The valid values [in bits] are 
 * 	8, 16 or 32. Default is 8. This type is configurable via the 
 * 	preprocessor switch RKH_SIZEOF_EVENT.
 */

#if RKH_SIZEOF_EVENT == 8
	typedef rkhui8_t RKHE_T;
#elif RKH_SIZEOF_EVENT == 16
	typedef rkhui16_t RKHE_T;
#elif RKH_SIZEOF_EVENT == 32
	typedef rkhui32_t RKHE_T;
#else
	typedef rkhui8_t RKHE_T;
#endif


/** 
 * 	Defines the data type of event size. The valid values [in bits] are 
 * 	8, 16 or 32. Default is 8. This type is configurable via the 
 * 	preprocessor switch RKH_SIZEOF_ESIZE.
 */

#if RKH_SIZEOF_ESIZE == 8
	typedef rkhui8_t RKHES_T;
#elif RKH_SIZEOF_ESIZE == 16
	typedef rkhui16_t RKHES_T;
#elif RKH_SIZEOF_ESIZE == 32
	typedef rkhui32_t RKHES_T;
#else
	typedef rkhui8_t RKHES_T;
#endif


/**	
 * 	\brief 
 * 	Represents events without parameters.
 * 	
 * 	An event can have associated parameters, allowing the event 
 * 	instance to convey not only the occurrence of some interesting 
 * 	incident but also quantitative information regarding that occurrence.
 *	Implementing the single inheritance in C is very simply by literally
 *	embedding the base structure, RKHEVT_T in this case, as the first 
 *	member of the derived structure.
 * 	For example, the structure MYEVT_T derived from the base structure 
 * 	RKHEVT_T by embedding the RKHEVT_T instance as the first member of 
 *	MYEVT_T.
 *
 * 	\code
 * 	typedef struct
 * 	{
 * 		RKHEVT_T evt;	// base structure
 *		int x;			// parameter 'x'
 *		int y;			// parameter 'y'
 * 	} MYEVT_T;
 * 	\endcode
 *
 *	Such nesting of structures always aligns the data member 'evt' at the 
 *	beginning of every instance of the derived structure. In particular, this 
 *	alignment lets you treat a pointer to the derived MYEVT_T structure as a 
 *	pointer to the RKHEVT_T base structure. Consequently, you can always 
 *	safely pass a pointer to MYEVT_T to any C function that expects a pointer 
 *	to RKHEVT_T. (To be strictly correct in C, you should explicitly cast this 
 *	pointer. In OOP such casting is called upcasting and is always safe.) 
 *	Therefore, all functions designed for the RKHEVT_T structure are 
 *	automatically available to the MYEVT_T structure as well as other 
 *	structures derived from RKHEVT_T.
 *
 * 	\note
 * 	The RKH takes the \a 'e' member of RKHEVT_T structure for triggering a 
 * 	state transition.
 *
 * 	\sa rkh_put_fifo(), rkh_put_lifo(), rkh_alloc_event(), 
 * 	rkh_set_static_event() and rkh_gc().
 */

typedef struct
{
	/**
	 *	Signal of the event instance.
	 */

	RKHE_T e;

	/**
	 * 	Attributes of dynamic event (0 for static event).
	 */

	rkhui8_t nref;
	rkhui8_t pool;
} RKHEVT_T;


#endif
