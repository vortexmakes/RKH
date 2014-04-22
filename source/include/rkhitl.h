/*
 *	file: rkhitl.h
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
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			lf@vxtsolutions.com.ar
 */

/**
 * 	\file rkhitl.h
 * 	\brief
 * 	RKH engine interface.
 *
 * 	This header file is directly included in RKH interface 
 * 	file, rkh.h.
 */


#ifndef __RKHITL_H__
#define __RKHITL_H__


/**
 * 	Defines standard constants and macros.
 */

#include "rkhdef.h"


/**	
 *  Application specific configuration options.
 */

#include "rkhcfg.h"


/** 
 * 	Specific definitions to the platform being used.
 */

#include "rkhplat.h"
#include "rkhtype.h"


/** 
 * 	Trace facility.
 */

#include "rkhtrc.h"

/**
 * 	Event data type and related macros.
 */

#include "rkhevt.h"


/**	
 * 	\brief
 *	This macro expands to the binary representation of the RKH version.
 *
 *	The version number is composed as 0xABCC, where:
 *	the number A (1-digit) denoted the major revision, the number B (1-digit)
 *	denoted the minor revision, and the number C (2-digit) indicated the 
 *	release number. For example, the code for 2.2.04 is 0x2204.
 *	
 *	Date: 05/03/2013
 */

#define RKH_VERSION_CODE			0x2404U


/**
 * 	\brief
 * 	This macro retrieves a pointer to string describing the RKH version. 
 * 	For example, "2.2.04".
 */

#define RKH_RELEASE					rkh_version


/**
 * 	\brief
 * 	This is the macro used to build an integer version code from the 
 * 	individual numbers that build up a version number. 
 *
 * 	For example, RKH_VERSION(2,2,04) expands to 0x2204. This macro is very 
 * 	useful when needs to compare the current version and a known checkpoint.
 *
 * 	\param a		major revision
 * 	\param b		minor revision
 * 	\param c		release number
 */

#define RKH_VERSION( a, b, c )


/**	
 *	This macro is used to indicate the end of a transition table.
 */

#define RKH_ANY						((RKHE_T)(-1))


/* 	
 *  Verifies port file from rkhport.h included in rkhplat.h.
 */

#ifndef RKHROM
#error "rkhport.h, Missing RKHROM: Qualifier for ROM data storage. \
	See Porting chapter in readme file for more information"
#endif

#define FOREVER						for(;;)


/* 
 * 	Macros for casting 
 */

#define CB( p )						((RKHBASE_T*)(p))
#define CST( p )					((RKHST_T*)(p))
#define CCMP( p )					((RKHSCMP_T*)(p))
#define CBSC( p )					((RKHSBSC_T*)(p))
#define CCD( p )					((RKHSCOND_T*)(p))
#define CCH( p )					((RKHSCHOICE_T*)(p))
#define CH( p )						((RKHSHIST_T*)(p))
#define CSBM( p )					((RKHSSBM_T*)(p))
#define CRSM( p )					((RKHRSM_T*)(p))
#define CM( p )						((RKHROM RKHSMA_T*)(p))
#define CT( p )						((RKHROM RKHTR_T*)(p))
#define CPT( p )					((RKHROM struct rkhscmp_t*)(p))
#define CPP( p )					((RKHPPRO_T)(p))
#define CG( p )						((RKHGUARD_T)(p))
#define CA( p )						((RKHACT_T)(p))
#define CENP( p )					((RKHSENP_T*)(p))
#define CEXP( p )					((RKHSEXP_T*)(p))
#define CENPCN( p )					((RKHENPCN_T*)(p))
#define CEXPCN( p )					((RKHEXPCN_T*)(p))
#define CE( p )						((RKHEVT_T*)(p))
#define CCE( p )					((const RKHEVT_T*)(p))
#define CV( p )						((void*)(p))


/*
 * 	LOOK FOR MISSING #define CONSTANTS ----------------------------------------
 * 
 * 	This section is used to generate ERROR messages at compile time if certain 
 * 	#define constants are MISSING in rkhcfg.h.  This allows you to quickly 
 * 	determine the source of the error.
 * 
 * 	You SHOULD NOT change this section UNLESS you would like to add more 
 * 	comments as to the source of the compile time error.
 */

/*  MEMORY POOL   ---------------------------------------------------------- */

#ifndef	RKH_MP_EN
	#error "RKH_MP_EN                              not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_MP_EN != RKH_DEF_ENABLED) && \
        	(RKH_MP_EN != RKH_DEF_DISABLED))
	#error "RKH_MP_EN                        illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#elif 	(RKH_MP_EN == RKH_DEF_ENABLED)

	#ifndef	RKH_MP_REDUCED
	#error "RKH_MP_REDUCED                         not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_MP_REDUCED != RKH_DEF_ENABLED) && \
    	    	(RKH_MP_REDUCED != RKH_DEF_DISABLED))
	#error "RKH_MP_REDUCED                   illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif
	
	#ifndef	RKH_MP_SIZEOF_BSIZE
	#error "RKH_MP_SIZEOF_BSIZE                    not #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "

	#elif  ((RKH_MP_SIZEOF_BSIZE != 8) && \
    	    (RKH_MP_SIZEOF_BSIZE != 16) && \
        	(RKH_MP_SIZEOF_BSIZE != 32))
	#error  "RKH_MP_SIZEOF_BSIZE             illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "
	#endif

	#ifndef	RKH_MP_SIZEOF_NBLOCK
	#error "RKH_MP_SIZEOF_NBLOCK                   not #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "

	#elif  ((RKH_MP_SIZEOF_NBLOCK != 8) && \
	        (RKH_MP_SIZEOF_NBLOCK != 16) && \
  	      (RKH_MP_SIZEOF_NBLOCK != 32))
	#error  "RKH_MP_SIZEOF_NBLOCK            illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "
	#endif

	#ifndef	RKH_MP_EN_GET_BSIZE
	#error "RKH_MP_EN_GET_BSIZE                    not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_MP_EN_GET_BSIZE != RKH_DEF_ENABLED) && \
    	    	(RKH_MP_EN_GET_BSIZE != RKH_DEF_DISABLED))
	#error "RKH_MP_EN_GET_BSIZE              illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_MP_EN_GET_NFREE
	#error "RKH_MP_EN_GET_NFREE                    not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_MP_EN_GET_NFREE != RKH_DEF_ENABLED) && \
    	    	(RKH_MP_EN_GET_NFREE != RKH_DEF_DISABLED))
	#error "RKH_MP_EN_GET_NFREE              illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_MP_EN_GET_LWM
	#error "RKH_MP_EN_GET_LWM                      not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_MP_EN_GET_LWM != RKH_DEF_ENABLED) && \
    	    	(RKH_MP_EN_GET_LWM != RKH_DEF_DISABLED))
	#error "RKH_MP_EN_GET_LWM                illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_MP_EN_GET_INFO
	#error "RKH_MP_EN_GET_INFO                     not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_MP_EN_GET_INFO != RKH_DEF_ENABLED) && \
    	    	(RKH_MP_EN_GET_INFO != RKH_DEF_DISABLED))
	#error "RKH_MP_EN_GET_INFO               illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

#endif

/*  QUEUE         ---------------------------------------------------------- */

#ifndef	RKH_RQ_EN
	#error "RKH_RQ_EN                              not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_RQ_EN != RKH_DEF_ENABLED) && \
        	(RKH_RQ_EN != RKH_DEF_DISABLED))
	#error "RKH_RQ_EN                        illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_RQ_SIZEOF_NELEM
	#error "RKH_RQ_SIZEOF_NELEM                    not #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "

#elif  ((RKH_RQ_SIZEOF_NELEM != 8) && \
        (RKH_RQ_SIZEOF_NELEM != 16) && \
        (RKH_RQ_SIZEOF_NELEM != 32))
	#error  "RKH_RQ_SIZEOF_NELEM             illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "

#endif


#ifndef	RKH_RQ_EN_GET_LWMARK
	#error "RKH_RQ_EN_GET_LWMARK                   not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_RQ_EN_GET_LWMARK != RKH_DEF_ENABLED) && \
        	(RKH_RQ_EN_GET_LWMARK != RKH_DEF_DISABLED))
	#error "RKH_RQ_EN_GET_LWMARK             illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_RQ_EN_READ
	#error "RKH_RQ_EN_READ                         not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_RQ_EN_READ != RKH_DEF_ENABLED) && \
        	(RKH_RQ_EN_READ != RKH_DEF_DISABLED))
	#error "RKH_RQ_EN_READ                   illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_RQ_EN_DEPLETE
	#error "RKH_RQ_EN_DEPLETE                      not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_RQ_EN_DEPLETE != RKH_DEF_ENABLED) && \
        	(RKH_RQ_EN_DEPLETE != RKH_DEF_DISABLED))
	#error "RKH_RQ_EN_DEPLETE                illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_RQ_EN_IS_FULL
	#error "RKH_RQ_EN_IS_FULL                      not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_RQ_EN_IS_FULL != RKH_DEF_ENABLED) && \
        	(RKH_RQ_EN_IS_FULL != RKH_DEF_DISABLED))
	#error "RKH_RQ_EN_IS_FULL                illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_RQ_EN_GET_NELEMS
	#error "RKH_RQ_EN_GET_NELEMS                   not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_RQ_EN_GET_NELEMS != RKH_DEF_ENABLED) && \
        	(RKH_RQ_EN_GET_NELEMS != RKH_DEF_DISABLED))
	#error "RKH_RQ_EN_GET_NELEMS             illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_RQ_EN_PUT_LIFO
	#error "RKH_RQ_EN_PUT_LIFO                     not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_RQ_EN_PUT_LIFO != RKH_DEF_ENABLED) && \
        	(RKH_RQ_EN_PUT_LIFO != RKH_DEF_DISABLED))
	#error "RKH_RQ_EN_PUT_LIFO               illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_RQ_EN_GET_INFO
	#error "RKH_RQ_EN_GET_INFO                     not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_RQ_EN_GET_INFO != RKH_DEF_ENABLED) && \
        	(RKH_RQ_EN_GET_INFO != RKH_DEF_DISABLED))
	#error "RKH_RQ_EN_GET_INFO               illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif

/*  TIMER         ---------------------------------------------------------- */

#ifndef RKH_TIM_EN
	#error "RKH_TIM_EN                             not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_TIM_EN != RKH_DEF_ENABLED) && \
        	(RKH_TIM_EN != RKH_DEF_DISABLED))
	#error "RKH_TIM_EN                       illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#elif 	(RKH_TIM_EN == RKH_DEF_ENABLED)
	#ifndef RKH_TICK_RATE_HZ
	#error "RKH_TICK_RATE_HZ                       not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "
	#elif (RKH_TICK_RATE_HZ > 0u)
	/**
	 * 	It can be used to convert ticks to milliseconds.
	 * 	This format is more convenient and natural than ticks.
	 * 	This configuration constant is not used by RKH, it is just 
	 * 	a value to allow an application to deal with time when 
	 * 	using timer services. 
	 * 	You can use the global constant RKH_TICK_RATE_HZ (see 
	 * 	rkhcfg.h) to convert time to ticks using the macros like 
	 * 	RKH_TIME_MS(), RKH_TIME_SEC(), and RKH_TIME_MIN().
	 */
	#define RKH_TICK_RATE_MS	\
					((RKH_TNT_T)(1000/RKH_TICK_RATE_HZ))

	/** @{
	 * 	\brief
	 * 	It can be used to convert ticks to time. 
	 *
	 * 	This format is more convenient and natural than ticks. You can use 
	 * 	the global constant RKH_TICK_RATE_HZ (see rkhcfg.h) to convert time to 
	 * 	ticks using the macros like RKH_TIME_MS(), RKH_TIME_SEC(), and 
	 * 	RKH_TIME_MIN().
	 */
	#define RKH_TIME_MS( ms_ )		((ms_)/RKH_TICK_RATE_MS)
	#define RKH_TIME_SEC( s_ )		((s_)*1000u/RKH_TICK_RATE_MS)
	#define RKH_TIME_MIN( m_ )		((m_)*60*1000u/RKH_TICK_RATE_MS)
	/*@}*/

	#else
	#error "RKH_TICK_RATE_HZ                 illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be > 0]                     "
	#endif

	#ifndef	RKH_TIM_SIZEOF_NTIMER
	#error "RKH_TIM_SIZEOF_NTIMER                  not #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "

	#elif  ((RKH_TIM_SIZEOF_NTIMER != 8) && \
    	    (RKH_TIM_SIZEOF_NTIMER != 16) && \
        	(RKH_TIM_SIZEOF_NTIMER != 32))
	#error  "RKH_TIM_SIZEOF_NTIMER           illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "
	#endif

	#ifndef RKH_TIM_EN_HOOK
	#error "RKH_TIM_EN_HOOK                        not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TIM_EN_HOOK != RKH_DEF_ENABLED) && \
    	    	(RKH_TIM_EN_HOOK != RKH_DEF_DISABLED))
	#error "RKH_TIM_EN_HOOK                  illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

	#elif 	(RKH_TIM_EN_HOOK == RKH_DEF_ENABLED)
	#define rkh_mktimer( t, e, th )	\
				rkh_tim_init_( (RKHT_T*)(t), (RKHEVT_T*)(e), (RKH_THK_T)(th) )

	#else
	#define rkh_mktimer( t, e, th )	\
				rkh_tim_init_( (RKHT_T*)(t), (RKHEVT_T*)(e) )
	#endif

	#ifndef	RKH_TIM_EN_GET_INFO
	#error "RKH_TIM_EN_GET_INFO                    not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TIM_EN_GET_INFO != RKH_DEF_ENABLED) && \
    	    	(RKH_TIM_EN_GET_INFO != RKH_DEF_DISABLED))
	#error "RKH_TIM_EN_GET_INFO              illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

#endif

/*  STATE MACHINE APPLICATIONS  -------------------------------------------- */

#ifndef RKH_SMA_EN_ID
	#error "RKH_SMA_EN_ID                          not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_ID != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_ID != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_ID                    illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_GET_INFO
	#error "RKH_SMA_EN_GET_INFO                    not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_GET_INFO != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_GET_INFO != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_GET_INFO              illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_STATE_ID
	#error "RKH_SMA_EN_STATE_ID                    not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_STATE_ID != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_STATE_ID != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_STATE_ID              illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_PPRO
	#error "RKH_SMA_EN_PPRO                        not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_PPRO != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_PPRO != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_PPRO                  illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_HCAL
	#error "RKH_SMA_EN_HCAL                        not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_HCAL != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_HCAL != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_HCAL                  illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_MAX_HCAL_DEPTH
	#error "RKH_SMA_EN_HCAL                        not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be >  0]                    "
	#error "                                [     && <= 8]                    "

#elif	((RKH_SMA_MAX_HCAL_DEPTH == 0) || \
			(RKH_SMA_MAX_HCAL_DEPTH > 8))
	#error "RKH_SMA_MAX_HCAL_DEPTH           illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be >= 0]                    "
	#error  "                               [     && <= 8]                    "

#endif


#ifndef RKH_SMA_MAX_TRC_SEGS
	#error "RKH_SMA_MAX_TRC_SEGS                   not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be >  0]                    "
	#error "                                [     && <= 8]                    "

#elif	((RKH_SMA_MAX_TRC_SEGS == 0) || \
			(RKH_SMA_MAX_TRC_SEGS > 8))
	#error "RKH_SMA_MAX_TRC_SEGS             illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be >= 0]                    "
	#error  "                               [     && <= 8]                    "

#endif


#ifndef RKH_SMA_EN_PSEUDOSTATE
	#error "RKH_SMA_EN_PSEUDOSTATE                 not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_PSEUDOSTATE != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_PSEUDOSTATE != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_PSEUDOSTATE           illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_DEEP_HISTORY
	#error "RKH_SMA_EN_DEEP_HISTORY                not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_DEEP_HISTORY != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_DEEP_HISTORY != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_DEEP_HISTORY          illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_SHALLOW_HISTORY
	#error "RKH_SMA_EN_SHALLOW_HISTORY             not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_SHALLOW_HISTORY != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_SHALLOW_HISTORY != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_SHALLOW_HISTORY       illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_CHOICE
	#error "RKH_SMA_EN_CHOICE                      not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_CHOICE != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_CHOICE != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_CHOICE                illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_CONDITIONAL
	#error "RKH_SMA_EN_CONDITIONAL                 not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_CONDITIONAL != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_CONDITIONAL != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_CONDITIONAL           illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_SUBMACHINE
	#error "RKH_SMA_EN_SUBMACHINE                  not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_SUBMACHINE != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_SUBMACHINE != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_SUBMACHINE            illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_TRC_SENDER
	#error "RKH_SMA_EN_TRC_SENDER                  not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_TRC_SENDER != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_TRC_SENDER != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_TRC_SENDER            illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_INIT_ARG_SMA
	#error "RKH_SMA_EN_INIT_ARG_SMA                not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_INIT_ARG_SMA != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_INIT_ARG_SMA != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_INIT_ARG_SMA          illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_ENT_ARG_SMA
	#error "RKH_SMA_EN_ENT_ARG_SMA                 not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_ENT_ARG_SMA != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_ENT_ARG_SMA != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_ENT_ARG_SMA           illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif

#ifndef RKH_SMA_EN_EXT_ARG_SMA
	#error "RKH_SMA_EN_EXT_ARG_SMA                 not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_EXT_ARG_SMA != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_EXT_ARG_SMA != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_EXT_ARG_SMA           illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_ACT_ARG_SMA
	#error "RKH_SMA_EN_ACT_ARG_SMA                 not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_ACT_ARG_SMA != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_ACT_ARG_SMA != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_ACT_ARG_SMA           illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_ACT_ARG_EVT
	#error "RKH_SMA_EN_ACT_ARG_EVT                 not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_ACT_ARG_EVT != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_ACT_ARG_EVT != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_ACT_ARG_EVT           illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_GRD_ARG_EVT
	#error "RKH_SMA_EN_GRD_ARG_EVT                 not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_GRD_ARG_EVT != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_GRD_ARG_EVT != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_GRD_ARG_EVT           illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_GRD_ARG_SMA
	#error "RKH_SMA_EN_GRD_ARG_SMA                 not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_GRD_ARG_SMA != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_GRD_ARG_SMA != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_GRD_ARG_SMA           illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_SMA_EN_PPRO_ARG_SMA
	#error "RKH_SMA_EN_PPRO_ARG_SMA                not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_PPRO_ARG_SMA != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_PPRO_ARG_SMA != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_PPRO_ARG_SMA          illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif

/*  TRACE         ---------------------------------------------------------- */

#ifndef	RKH_TRC_EN
	#error "RKH_TRC_EN                             not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_TRC_EN != RKH_DEF_ENABLED) && \
        	(RKH_TRC_EN != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN                       illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#elif 	(RKH_TRC_EN == RKH_DEF_ENABLED)

	#ifndef	RKH_TRC_RUNTIME_FILTER
	#error "RKH_TRC_RUNTIME_FILTER                 not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_RUNTIME_FILTER != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_RUNTIME_FILTER != RKH_DEF_DISABLED))
	#error "RKH_TRC_RUNTIME_FILTER           illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif
	
	#ifndef	RKH_TRC_EN_USER_TRACE
	#error "RKH_TRC_EN_USER_TRACE                  not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_USER_TRACE != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_USER_TRACE != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_USER_TRACE            illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_ALL
	#error "RKH_TRC_ALL                            not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_ALL != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_ALL != RKH_DEF_DISABLED))
	#error "RKH_TRC_ALL                      illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_MP
	#error "RKH_TRC_EN_MP                          not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_MP != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_MP != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_MP                    illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_RQ
	#error "RKH_TRC_EN_RQ                          not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_RQ != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_RQ != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_RQ                    illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SMA
	#error "RKH_TRC_EN_SMA                         not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SMA != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SMA != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SMA                   illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_TIM
	#error "RKH_TRC_EN_TIM                         not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_TIM != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_TIM != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_TIM                   illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM
	#error "RKH_TRC_EN_SM                          not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM                    illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_FWK
	#error "RKH_TRC_EN_FWK                         not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_FWK != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_FWK != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_FWK                   illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_ASSERT
	#error "RKH_TRC_EN_ASSERT                      not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_ASSERT != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_ASSERT != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_ASSERT                illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_INIT
	#error "RKH_TRC_EN_SM_INIT                     not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_INIT != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_INIT != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_INIT               illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_DCH
	#error "RKH_TRC_EN_SM_DCH                      not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_DCH != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_DCH != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_DCH                illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_CLRH
	#error "RKH_TRC_EN_SM_CLRH                     not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_CLRH != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_CLRH != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_CLRH               illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_TRN
	#error "RKH_TRC_EN_SM_TRN                      not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_TRN != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_TRN != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_TRN                illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_STATE
	#error "RKH_TRC_EN_SM_STATE                    not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_STATE != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_STATE != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_STATE              illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_ENSTATE
	#error "RKH_TRC_EN_SM_ENSTATE                  not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_ENSTATE != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_ENSTATE != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_ENSTATE            illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_EXSTATE
	#error "RKH_TRC_EN_SM_EXSTATE                  not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_EXSTATE != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_EXSTATE != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_EXSTATE            illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_NENEX
	#error "RKH_TRC_EN_SM_NENEX                    not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_NENEX != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_NENEX != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_NENEX              illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_NTRNACT
	#error "RKH_TRC_EN_SM_NTRNACT                  not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_NTRNACT != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_NTRNACT != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_NTRNACT            illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_TS_STATE
	#error "RKH_TRC_EN_SM_TS_STATE                 not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_TS_STATE != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_TS_STATE != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_TS_STATE           illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_SM_PROCESS
	#error "RKH_TRC_EN_SM_PROCESS                  not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_SM_PROCESS != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_SM_PROCESS != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_SM_PROCESS            illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_NSEQ
	#error "RKH_TRC_EN_NSEQ                        not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_NSEQ != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_NSEQ != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_NSEQ                  illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_CHK
	#error "RKH_TRC_EN_CHK                         not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_CHK != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_CHK != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_CHK                   illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_EN_TSTAMP
	#error "RKH_TRC_EN_TSTAMP                      not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

	#elif 	((RKH_TRC_EN_TSTAMP != RKH_DEF_ENABLED) && \
    	    	(RKH_TRC_EN_TSTAMP != RKH_DEF_DISABLED))
	#error "RKH_TRC_EN_TSTAMP                illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "
	#endif

	#ifndef	RKH_TRC_SIZEOF_TSTAMP
	#error "RKH_TRC_SIZEOF_TSTAMP                  not #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "

	#elif  ((RKH_TRC_SIZEOF_TSTAMP != 8) && \
    	    (RKH_TRC_SIZEOF_TSTAMP != 16) && \
        	(RKH_TRC_SIZEOF_TSTAMP != 32))
	#error  "RKH_TRC_SIZEOF_TSTAMP           illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "
	#endif

	#ifndef	RKH_TRC_SIZEOF_STREAM
	#error "RKH_TRC_SIZEOF_STREAM                  not #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be >     0]                 "
	#error  "                               [     && <= 2048]                 "

	#elif	((RKH_TRC_SIZEOF_STREAM == 0) || (RKH_TRC_SIZEOF_STREAM > 2048))
	#error "RKH_TRC_SIZEOF_STREAM            illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be >    0]                  "
	#error  "                               [     && <= 2048]                 "
	#endif

#endif

/*  FRAMEWORK     ---------------------------------------------------------- */

#ifndef	RKH_MAX_SMA
	#error "RKH_MAX_SMA                            not #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be >=  1]                   "
	#error  "                               [     && <= 64]                   "

#elif ((RKH_MAX_SMA == 0) || (RKH_MAX_SMA > 64))
	#error "RKH_MAX_SMA                      illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be >=  1]                   "
	#error  "                               [     && <= 64]                   "

#endif


#ifndef	RKH_EN_DYNAMIC_EVENT
	#error "RKH_EN_DYNAMIC_EVENT                   not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	(RKH_EN_DYNAMIC_EVENT == RKH_DEF_DISABLED)
	/*
	 *	If the dynamic event support is disabled, RKH not allows to use events 
	 *	with parameters, defer/recall mechanism, allocating and recycling 
	 *	dynamic events, among other features.
	 */
	#undef RKH_EN_NATIVE_DYN_EVENT
	#define RKH_EN_NATIVE_DYN_EVENT			RKH_DEF_DISABLED

#endif


#ifndef	RKH_MAX_EPOOL
	#error "RKH_MAX_EPOOL                          not #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be >    0]                  "
	#error  "                               [     && <  256]                  "

#elif 	(RKH_EN_DYNAMIC_EVENT == RKH_DEF_ENABLED)
	#if ((RKH_MAX_EPOOL == 0) || (RKH_MAX_EPOOL > 255))
	#error "RKH_MAX_EPOOL                    illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be >    0]                  "
	#error  "                               [     && <  256]                  "
	#endif

#endif


#ifndef	RKH_SIZEOF_EVENT
	#error "RKH_SIZEOF_EVENT                       not #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "

#elif  ((RKH_SIZEOF_EVENT != 8) && \
        (RKH_SIZEOF_EVENT != 16) && \
        (RKH_SIZEOF_EVENT != 32))
	#error  "RKH_SIZEOF_EVENT                illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "

#endif


#ifndef	RKH_SIZEOF_ESIZE
	#error "RKH_SIZEOF_ESIZE                       not #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "

#elif  ((RKH_SIZEOF_ESIZE != 8) && \
        (RKH_SIZEOF_ESIZE != 16) && \
        (RKH_SIZEOF_ESIZE != 32))
	#error  "RKH_SIZEOF_ESIZE                illegally #define'd in 'rkhcfg.h'"
	#error  "                               [MUST be  8  ( 8-bit size)]       "
	#error  "                               [     || 16  (16-bit size)]       "
	#error  "                               [     || 32  (32-bit size)]       "

#endif


#ifndef RKH_EN_DEFERRED_EVENT
	#error "RKH_EN_DEFERRED_EVENT                  not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_EN_DEFERRED_EVENT == RKH_DEF_ENABLED) && \
			(RKH_EN_NATIVE_EQUEUE == RKH_DEF_DISABLED))
	#error  "RKH_EN_NATIVE_EQUEUE            illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "

#endif


#ifndef	RKH_ASSERT_EN
	#error "RKH_ASSERT_EN                         not #define'd in 'rkhport.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_ASSERT_EN != RKH_DEF_ENABLED) && \
        	(RKH_ASSERT_EN != RKH_DEF_DISABLED))
	#error "RKH_ASSERT_EN                   illegally #define'd in 'rkhport.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_HK_EN_DISPATCH
	#error "RKH_HK_EN_DISPATCH                     not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_HK_EN_DISPATCH != RKH_DEF_ENABLED) && \
        	(RKH_HK_EN_DISPATCH != RKH_DEF_DISABLED))
	#error "RKH_HK_EN_DISPATCH               illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_HK_EN_SIGNAL
	#error "RKH_HK_EN_SIGNAL                       not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_HK_EN_SIGNAL != RKH_DEF_ENABLED) && \
        	(RKH_HK_EN_SIGNAL != RKH_DEF_DISABLED))
	#error "RKH_HK_EN_SIGNAL                 illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_HK_EN_TIMEOUT
	#error "RKH_HK_EN_TIMEOUT                      not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_HK_EN_TIMEOUT != RKH_DEF_ENABLED) && \
        	(RKH_HK_EN_TIMEOUT != RKH_DEF_DISABLED))
	#error "RKH_HK_EN_TIMEOUT                illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_HK_EN_START
	#error "RKH_HK_EN_START                        not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_HK_EN_START != RKH_DEF_ENABLED) && \
        	(RKH_HK_EN_START != RKH_DEF_DISABLED))
	#error "RKH_HK_EN_START                  illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef RKH_HK_EN_EXIT
	#error "RKH_HK_EN_EXIT                         not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_HK_EN_EXIT != RKH_DEF_ENABLED) && \
        	(RKH_HK_EN_EXIT != RKH_DEF_DISABLED))
	#error "RKH_HK_EN_EXIT                   illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_SMA_EN_IEVENT
	#error "RKH_SMA_EN_IEVENT                      not #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_SMA_EN_IEVENT != RKH_DEF_ENABLED) && \
        	(RKH_SMA_EN_IEVENT != RKH_DEF_DISABLED))
	#error "RKH_SMA_EN_IEVENT                illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif

/*  PORT          ---------------------------------------------------------- */

#ifndef	RKH_EN_SMA_THREAD
	#error "RKH_EN_SMA_THREAD                     not #define'd in 'rkhport.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_EN_SMA_THREAD != RKH_DEF_ENABLED) && \
        	(RKH_EN_SMA_THREAD != RKH_DEF_DISABLED))
	#error "RKH_EN_SMA_THREAD               illegally #define'd in 'rkhport.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_EN_SMA_THREAD_DATA
	#error "RKH_EN_SMA_THREAD_DATA                not #define'd in 'rkhport.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_EN_SMA_THREAD_DATA != RKH_DEF_ENABLED) && \
        	(RKH_EN_SMA_THREAD_DATA != RKH_DEF_DISABLED))
	#error "RKH_EN_SMA_THREAD_DATA          illegally #define'd in 'rkhport.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_EN_NATIVE_SCHEDULER
	#error "RKH_EN_NATIVE_SCHEDULER               not #define'd in 'rkhport.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_EN_NATIVE_SCHEDULER != RKH_DEF_ENABLED) && \
        	(RKH_EN_NATIVE_SCHEDULER != RKH_DEF_DISABLED))
	#error "RKH_EN_NATIVE_SCHEDULER         illegally #define'd in 'rkhport.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_EN_NATIVE_EQUEUE
	#error "RKH_EN_NATIVE_EQUEUE                  not #define'd in 'rkhport.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_EN_NATIVE_EQUEUE != RKH_DEF_ENABLED) && \
        	(RKH_EN_NATIVE_EQUEUE != RKH_DEF_DISABLED))
	#error "RKH_EN_NATIVE_EQUEUE            illegally #define'd in 'rkhport.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#elif	((RKH_EN_NATIVE_EQUEUE == RKH_DEF_ENABLED) && \
        	(RKH_RQ_EN != RKH_DEF_ENABLED))
	#error "RKH_RQ_EN                        illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#endif


#ifndef RKH_EN_NATIVE_DYN_EVENT
	#error "RKH_EN_NATIVE_DYN_EVENT               not #define'd in 'rkhport.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_EN_NATIVE_DYN_EVENT != RKH_DEF_ENABLED) && \
        	(RKH_EN_NATIVE_DYN_EVENT != RKH_DEF_DISABLED))
	#error "RKH_EN_NATIVE_DYN_EVENT         illegally #define'd in 'rkhport.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#elif	(RKH_EN_NATIVE_DYN_EVENT == RKH_DEF_ENABLED)
	#if ((RKH_EN_DYNAMIC_EVENT == RKH_DEF_ENABLED) && \
			(RKH_MP_EN == RKH_DEF_DISABLED))
	#error "RKH_EN_DYNAMIC_EVENT             illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "RKH_MP_EN                        illegally #define'd in 'rkhcfg.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#endif

#endif


#ifndef	RKH_EN_REENTRANT
	#error "RKH_EN_REENTRANT                      not #define'd in 'rkhport.h'"
	#error "                                [MUST be RKH_DEF_ENABLED ]        "
	#error "                                [     || RKH_DEF_DISABLED]        "

#elif 	((RKH_EN_REENTRANT != RKH_DEF_ENABLED) && \
        	(RKH_EN_REENTRANT != RKH_DEF_DISABLED))
	#error "RKH_EN_REENTRANT                illegally #define'd in 'rkhport.h'"
	#error "                                [MUST be  RKH_DEF_ENABLED ]       "
	#error "                                [     ||  RKH_DEF_DISABLED]       "

#endif


#ifndef	RKH_TRC_SIZEOF_POINTER
	#error "RKH_TRC_SIZEOF_POINTER                not #define'd in 'rkhport.h'"
	#error  "                               [MUST be  8  ( 8-bit pointer)]    "
	#error  "                               [     || 16  (16-bit pointer)]    "
	#error  "                               [     || 32  (32-bit pointer)]    "

#elif  ((RKH_TRC_SIZEOF_POINTER != 8) && \
        (RKH_TRC_SIZEOF_POINTER != 16) && \
        (RKH_TRC_SIZEOF_POINTER != 32))
	#error  "RKH_TRC_SIZEOF_POINTER         illegally #define'd in 'rkhport.h'"
	#error  "                               [MUST be  8  ( 8-bit pointer)]    "
	#error  "                               [     || 16  (16-bit pointer)]    "
	#error  "                               [     || 32  (32-bit pointer)]    "

#endif


#ifndef	RKH_TRC_SIZEOF_FUN_POINTER
	#error "RKH_TRC_SIZEOF_FUN_POINTER            not #define'd in 'rkhport.h'"
	#error  "                               [MUST be  8  ( 8-bit pointer)]    "
	#error  "                               [     || 16  (16-bit pointer)]    "
	#error  "                               [     || 32  (32-bit pointer)]    "

#elif  ((RKH_TRC_SIZEOF_FUN_POINTER != 8) && \
        (RKH_TRC_SIZEOF_FUN_POINTER != 16) && \
        (RKH_TRC_SIZEOF_FUN_POINTER != 32))
	#error  "RKH_TRC_SIZEOF_FUN_POINTER     illegally #define'd in 'rkhport.h'"
	#error  "                               [MUST be  8  ( 8-bit pointer)]    "
	#error  "                               [     || 16  (16-bit pointer)]    "
	#error  "                               [     || 32  (32-bit pointer)]    "

#endif


/*
 * 	The following macros and constants are INTERNAL to RKH and 
 * 	the user application should NOT call it.
 */

#define RKH_REGULAR						0x80
#define RKH_PSEUDO						0
#define RKH_TYPE(t,i)					(t|i)

#define RKH_BASIC						RKH_TYPE( RKH_REGULAR, 	0	 )
#define RKH_COMPOSITE					RKH_TYPE( RKH_REGULAR, 	0x01 )	
#define RKH_SUBMACHINE					RKH_TYPE( RKH_REGULAR, 	0x02 )	
#define RKH_REF_SUBMACHINE				RKH_TYPE( RKH_REGULAR, 	0x04 )	

#define RKH_CONDITIONAL					RKH_TYPE( RKH_PSEUDO, 	0x02 )	
#define RKH_CHOICE						RKH_TYPE( RKH_PSEUDO, 	0x04 )	
#define RKH_SHISTORY					RKH_TYPE( RKH_PSEUDO, 	0x08 )	
#define RKH_DHISTORY					RKH_TYPE( RKH_PSEUDO, 	0x10 )	
#define RKH_ENPOINT						RKH_TYPE( RKH_PSEUDO, 	0x20 )	
#define RKH_EXPOINT						RKH_TYPE( RKH_PSEUDO, 	0x40 )	


#if (	RKH_SMA_EN_PSEUDOSTATE == RKH_DEF_DISABLED || \
		(	RKH_SMA_EN_DEEP_HISTORY == RKH_DEF_DISABLED &&  \
			RKH_SMA_EN_SHALLOW_HISTORY == RKH_DEF_DISABLED && \
			RKH_SMA_EN_SUBMACHINE == RKH_DEF_DISABLED && \
			RKH_SMA_EN_CONDITIONAL == RKH_DEF_DISABLED && \
			RKH_SMA_EN_CHOICE == RKH_DEF_DISABLED ))
	#define RKH_DEF_PSEUDOSTATE		RKH_DEF_DISABLED
#else
	#define RKH_DEF_PSEUDOSTATE		RKH_DEF_ENABLED
#endif

#if (	RKH_SMA_EN_HCAL == RKH_DEF_ENABLED && \
		RKH_SMA_EN_PSEUDOSTATE == RKH_DEF_ENABLED && \
			(RKH_SMA_EN_SHALLOW_HISTORY == RKH_DEF_ENABLED || \
				RKH_SMA_EN_DEEP_HISTORY == RKH_DEF_ENABLED))
	#define RKH_HISTORY_ENABLED
#endif

#if (	RKH_SMA_EN_HCAL == RKH_DEF_ENABLED && \
		RKH_SMA_EN_PSEUDOSTATE == RKH_DEF_ENABLED && \
		RKH_SMA_EN_DEEP_HISTORY == RKH_DEF_ENABLED)
	#define RKH_DEEP_ENABLED
#endif

#if (	RKH_SMA_EN_HCAL == RKH_DEF_ENABLED && \
		RKH_SMA_EN_PSEUDOSTATE == RKH_DEF_ENABLED && \
		RKH_SMA_EN_SHALLOW_HISTORY == RKH_DEF_ENABLED)
	#define RKH_SHALLOW_ENABLED
#endif

#if (	RKH_SMA_EN_PSEUDOSTATE == RKH_DEF_ENABLED && \
		RKH_SMA_EN_SUBMACHINE == RKH_DEF_ENABLED)
	#define RKH_SUBMACHINE_ENABLED
#endif

#if (	RKH_SMA_EN_PSEUDOSTATE == RKH_DEF_ENABLED && \
		RKH_SMA_EN_CHOICE == RKH_DEF_ENABLED)
	#define RKH_CHOICE_ENABLED
#endif

#if (	RKH_SMA_EN_PSEUDOSTATE == 1 && \
		(RKH_SMA_EN_CONDITIONAL == 1 || RKH_SMA_EN_CHOICE == 1))
	#define RKH_CHOICE_OR_CONDITIONAL_ENABLED
#endif
	

#if RKH_HK_EN_DISPATCH == RKH_DEF_ENABLED
	#define RKH_HK_DISPATCH( sma, e )	\
							rkh_hk_dispatch( (sma), (RKHEVT_T*)(e) )

#else
	#define RKH_HK_DISPATCH( sma, e )	\
							(void)0
#endif


#if	(RKH_HK_EN_TIMEOUT == RKH_DEF_ENABLED)
	#define RKH_HK_TIMEOUT( t )	\
							rkh_hk_timeout( (t) )
#else
	#define RKH_HK_TIMEOUT( t )	\
							(void)0
#endif


#if	(RKH_HK_EN_SIGNAL == RKH_DEF_ENABLED)
	#define RKH_HK_SIGNAL( e )	\
							rkh_hk_signal( (RKHEVT_T*)(e) )
#else
	#define RKH_HK_SIGNAL( e )	\
							(void)0
#endif


#if	(RKH_HK_EN_START == RKH_DEF_ENABLED)
	#define RKH_HK_START()	\
							rkh_hk_start()
#else
	#define RKH_HK_START()	\
							(void)0
#endif


#if	(RKH_HK_EN_EXIT == RKH_DEF_ENABLED)
	#define RKH_HK_EXIT()	\
							rkh_hk_exit()
#else
	#define RKH_HK_EXIT()	\
							(void)0
#endif


#if (RKH_SMA_EN_ID == RKH_DEF_ENABLED)
	#if (RKH_SMA_EN_IEVENT == RKH_DEF_ENABLED)
		#define MKRRKH(prio,ppty,id,is,ia,ie)				\
				{(prio),(ppty),(id),(RKHROM struct rkhst_t*)is,(ia),(ie)}
	#else
		#define MKRRKH(prio,ppty,id,is,ia,ie)				\
				{(prio),(ppty),(id),(RKHROM struct rkhst_t*)is,(ia)}
	#endif
#else
	#if (RKH_SMA_EN_IEVENT == RKH_DEF_ENABLED)
		#define MKRRKH(prio,ppty,id,is,ia,ie)				\
				{(prio),(ppty),(RKHROM struct rkhst_t*)is,(ia),(ie)}
	#else
		#define MKRRKH(prio,ppty,id,is,ia,ie)				\
				{(prio),(ppty),(RKHROM struct rkhst_t*)is,(ia)}
	#endif
#endif


#define MKSMA( rr, s )					\
						{ {(RKHROM ROMRKH_T*)(rr), \
							 	(RKHROM struct rkhst_t*)(s)} }


#if (RKH_SMA_EN_STATE_ID == RKH_DEF_ENABLED)
	#define MKBASE(t,id)			t,id
#else
	#define MKBASE(t,id)			t
#endif


#if (RKH_SMA_EN_HCAL == RKH_DEF_ENABLED)
	#if (RKH_SMA_EN_PPRO == RKH_DEF_ENABLED)
		#define MKBASIC(n,pp)		n##_trtbl,pp
		#define MKCOMP(n,d,h)		n##_trtbl,NULL,d,h
	#else
		#define MKBASIC(n,pp)		n##_trtbl
		#define MKCOMP(n,d,h)		n##_trtbl,d,h
	#endif
	#define MKST(en,ex,p)			en,ex,(RKHROM struct rkhst_t *)p
	#define MKSBM(n,sbm)			n##_trtbl,n##_exptbl,sbm
	#define MKMCH(d,i,n)			d,i,(RKHROM RKHST_T**)&rdyp_##n
	#define MKENP(e,s)				e,(RKHROM struct rkhst_t *)s
#else
	#if (RKH_SMA_EN_PPRO == RKH_DEF_ENABLED)
		#define MKBASIC(n,pp)		n##_trtbl,pp
		#define MKCOMP(n,d,h)		n##_trtbl,NULL
	#else
		#define MKBASIC(n,pp)		n##_trtbl
		#define MKCOMP(n,d,h)		n##_trtbl
	#endif
	#define MKST(en,ex,p)
	#define MKSBM(n,sbm)			n##_trtbl,n##_exptbl,sbm
	#define MKMCH(d,i,n)			d,i,(RKHROM RKHST_T*)&rdyp_##n
	#define MKENP(e,s)				e,(RKHROM struct rkhst_t *)s
#endif


#define mksevt( evt, es )		\
							((RKHEVT_T*)(evt))->e = (RKHE_T)es;		\
							((RKHEVT_T*)(evt))->nref = 0;
#define mkievt( evt, es )		\
							RKHROM RKHEVT_T evt = { es, 0 }

#ifndef RKH_DIS_INTERRUPT
	#error  "rkhport.h, Must be defined the platform-dependent macro RKH_DIS_INTERRUPT"
#endif

#ifndef RKH_ENA_INTERRUPT
	#error  "rkhport.h, Must be defined the platform-dependent macro RKH_ENA_INTERRUPT"
#endif


#ifndef RKH_EN_DOXYGEN
	#define RKH_EN_DOXYGEN	0
#endif


#if RKH_EN_DOXYGEN == RKH_DEF_ENABLED

	/**
	 *	If the #RKH_EN_SMA_THREAD is set to 1, each SMA (active object) has its own 
	 *	thread of execution.
	 */

	#define RKH_EN_SMA_THREAD 			RKH_DEF_ENABLED

	/**
	 *	If the #RKH_EN_SMA_THREAD and #RKH_EN_SMA_THREAD_DATA are set to 1, each 
	 *	SMA (active object) has its own thread of execution and its own object 
	 *	data.
	 */

	#define RKH_EN_SMA_THREAD_DATA		RKH_DEF_ENABLED

	/**
	 * 	If the #RKH_EN_NATIVE_SCHEDULER is set to 1 then RKH will include the 
	 * 	simple, cooperative, and nonpreemptive scheduler RKHS.
	 * 	When #RKH_EN_NATIVE_SCHEDULER is enabled RKH also will automatically 
	 * 	define #RKH_EQ_TYPE, RKH_SMA_BLOCK(), RKH_SMA_READY(), RKH_SMA_UNREADY(), 
	 * 	and assume the native priority scheme.
	 */

	#define RKH_EN_NATIVE_SCHEDULER		RKH_DEF_ENABLED

	/**
	 * 	If the #RKH_EN_NATIVE_EQUEUE is set to 1 and the native event queue is 
	 *	enabled (see #RKH_RQ_EN) then RKH will include its own implementation of 
	 *	rkh_sma_post_fifo(), rkh_sma_post_lifo(), and rkh_sma_get() functions.
	 */

	#define RKH_EN_NATIVE_EQUEUE		RKH_DEF_ENABLED

	/**
	 * 	If the #RKH_EN_NATIVE_DYN_EVENT is set to 1 and the native fixed-size 
	 * 	memory block facility is enabled (see #RKH_MP_EN) then RKH will include 
	 * 	its own implementation of dynamic memory management.
	 * 	When #RKH_EN_NATIVE_DYN_EVENT is enabled RKH also will automatically 
	 * 	define RKH_DYNE_TYPE, RKH_DYNE_INIT(), RKH_DYNE_GET_ESIZE(), 
	 * 	RKH_DYNE_GET(), and RKH_DYNE_PUT().
	 */

	#define RKH_EN_NATIVE_DYN_EVENT		RKH_DEF_ENABLED

	/**
	 *	If the #RKH_EN_REENTRANT is set to 1, the RKH event dispatch allows to be 
	 *	invoked from several threads of executions. Enable this only if the 
	 *	application is based on a multi-thread architecture.
	 */

	#define RKH_EN_REENTRANT			RKH_DEF_ENABLED

	/**
	 * 	Specify the size of void pointer. The valid values [in bits] are 
	 * 	16 or 32. Default is 32. See RKH_TRC_SYM() macro.
	 */

	#define RKH_TRC_SIZEOF_POINTER		32

	/**
	 * 	Specify the size of function pointer. The valid values [in bits] are 
	 * 	16 or 32. Default is 32. See RKH_TUSR_FUN() and RKH_TRC_FUN() macros.
	 */

	#define RKH_TRC_SIZEOF_FUN_POINTER	32

	/**
	 * 	Defines the data type of the event queue for active objects. 
	 * 	The event queue can be implemented with a message queue of 
	 * 	the RTOS/OS. But it is also possible to use the native RKH 
	 * 	queue RKHRQ_T type if the underlying RTOS/OS does not provide 
	 * 	an adequate queue.
	 *
	 * 	<EM>Example for using the native queue</EM>
	 * 	\code
	 *	// RKH's native queue
	 * 	#define RKH_EQ_TYPE			RKHRQ_T
	 *	// Message queue of ucos/II
	 * 	#define RKH_EQ_TYPE			OS_EVENT
	 *	// Message queue of FreeRTOS
	 * 	#define RKH_EQ_TYPE			xQueueHandle
	 * 	\endcode
	 */

	#define RKH_EQ_TYPE

	/**
	 * 	Frequently, the active object has its own task processing loop that 
	 * 	waits for the signal to be posted, and when it is, loops to remove 
	 * 	and process all events that are currently queued.
	 * 	The RKH_SMA_POST_FIFO() macro enqueues an event and signals	the OS 
	 * 	that an event has arrived. In this case, \c os_signal holds the OS 
	 * 	object used to signal that an event has been queued.
	 * 	The data type RKH_THREAD_TYPE holds the thread handle associated 
	 * 	with the active object.
	 *
	 * 	<EM>Example for using the uCOS/II, FreeRTOS, Linux (Posix) and 
	 * 	Win32</EM>
	 * 	\code
	 *	// For uCOS/II
	 * 	#define RKH_THREAD_TYPE		INT8U
	 *	// For FreeRTOS
	 * 	#define RKH_THREAD_TYPE		xTaskHandle
	 *	// For Linux (Posix)
	 * 	#define RKH_THREAD_TYPE		pthread_t
	 *	// For Win32
	 * 	#define RKH_THREAD_TYPE		void*
	 * 	\endcode
	 */

	#define RKH_THREAD_TYPE

	/**
	 * 	The \c os_signal member of RKHSMA_T is necessary when the underlying 
	 * 	OS does not provide an adequate queue facility, so the native RKH 
	 * 	queue RKHRQ_T must be used. In this case the RKH_OSSIGNAL_TYPE 
	 * 	indicates an operating system specific primitive to efficiently 
	 * 	block the native RKH event queue when the queue is empty.
	 * 	Frequently, the active object has its own task processing loop that 
	 * 	waits for the signal to be posted, and when it is, loops to remove 
	 * 	and process all events that are currently queued.
	 * 	The RKH_SMA_POST_FIFO() macro enqueues an event and signals	the OS 
	 * 	that an event has arrived. In this case, \c os_signal holds the OS 
	 * 	object used to signal that an event has been queued.
	 *
	 * 	<EM>Example for using the Linux (Posix) and Win32</EM>
	 * 	\code
	 *	// For Linux (Posix)
	 * 	#define RKH_OSSIGNAL_TYPE	pthread_cond_t
	 *	// For Win32
	 * 	#define RKH_OSSIGNAL_TYPE	void*
	 * 	\endcode
	 */

	#define RKH_OSSIGNAL_TYPE

	/**@{
	 * 	RKH need to disable interrupts in order to access critical sections 
	 * 	of code, and re-enable interrupts when done. This allows RKH to 
	 * 	protect critical code from being entered simultaneously. To hide the 
	 * 	implementation method chosen by the processor, compiler, etc, RKH 
	 * 	defines two macros to unconditionally disable and enable interrupts: 
	 * 	RKH_DIS_INTERRUPT() and RKH_ENA_INTERRUPT() respectively. Obviously, 
	 * 	they resides in \b rkhport.h file, which the user always need to 
	 * 	provide.
	 *
	 * 	<EM>Example for HCS08 CW6.3 from C:</EM>
	 * 	\code
	 * 	#define RKH_DIS_INTERRUPT()			DisableInterrupts
	 * 	#define RKH_ENA_INTERRUPT()			EnableInterrupts
	 * 	\endcode
	 */

	#define RKH_DIS_INTERRUPT()
	#define RKH_ENA_INTERRUPT()
	/*@}*/


	/**@{
	 * 	\brief
	 * 	RKH need to disable interrupts in order to access critical sections of 
	 * 	code, and re-enable interrupts when done. 
	 *
	 * 	This allows RKH to protect 
	 * 	critical code from being entered simultaneously from either multiple 
	 * 	SMAs or ISRs. Every processor generally provide instructions to 
	 * 	disable/enable interrupts and the C compiler must have a mechanism to 
	 * 	perform these operations directly from C. Some compilers will allows 
	 * 	to insert in-line assembly language statements in the C source code. 
	 * 	This makes it quite easy to insert processor instructions to enable and 
	 * 	disable interrupts. Other compilers will actually contain language 
	 * 	extensions to enable and disable interrupts directly from C. To hide 
	 * 	the implementation method chosen by the compiler manufacturer, RKH 
	 * 	defines two macros to disable and enable interrupts: 
	 * 	RKH_ENTER_CRITICAL() and RKH_EXIT_CRITICAL().
	 *
	 * 	The RKH_ENTER_CRITICAL() macro saves the interrupt disable status onto 
	 * 	the stack and then, disable interrupts. 
	 * 	RKH_EXIT_CRITICAL() would simply be implemented by restoring the 
	 * 	interrupt status from the stack. Using this scheme, if it's called a 
	 * 	RKH service with either interrupts enabled or disabled then, the 
	 * 	status would be preserved across the call. If calls a RKH service with 
	 * 	interrupts disabled, is potentially extending the interrupt latency of 
	 * 	application. The application can use RKH_ENTER_CRITICAL() and 
	 * 	RKH_EXIT_CRITICAL() to also protect critical sections of code. As a 
	 * 	general rule, should always call RKH services with interrupts enabled!.
	 * 	
	 * 	\note
	 * 	These macros are internal to RKH and the user application should 
	 * 	not call it.
	 *
	 * 	<EM>Example for x86, VC2008, and win32 single thread:</EM>
	 * 	\code
	 * 	//#define RKH_CPUSR_TYPE
	 * 	#define RKH_ENTER_CRITICAL( dummy )		EnterCriticalSection(&csection)
	 * 	#define RKH_EXIT_CRITICAL( dummy )		LeaveCriticalSection(&csection)
	 * 	\endcode
	 */

	#define RKH_CPUSR_TYPE
	#define RKH_SR_ALLOC()						RKH_CPUSR_TYPE sr = \
														(RKH_CPUSR_TYPE)0
	#define RKH_ENTER_CRITICAL( dummy )
	#define RKH_EXIT_CRITICAL( dummy )
	/*@}*/


	/**
	 * 	\brief
	 * 	Encapsulates the mechanism of blocking the event queue.
	 *
	 * 	\param sma		pointer to SMA.
	 */

	#define RKH_SMA_BLOCK( sma )

	/**
	 * 	\brief
	 * 	Encapsulates the mechanism of signaling the thread waiting on the 
	 * 	used event queue. Thus, the SMA is inserted in the ready list as 
	 * 	ready-to-dispatch.
	 *
 	 * 	\param rg		ready group.
	 * 	\param sma		pointer to SMA.
	 */

	#define RKH_SMA_READY( rg, sma )

	/**
	 * 	\brief
	 * 	Informs the underlying kernel that the SMA event queue is becoming 
	 * 	empty. Thus, the SMA is removed from the ready list.
	 *
 	 * 	\param rg		ready group.
	 * 	\param sma		pointer to SMA.
	 */

	#define RKH_SMA_UNREADY( rg, sma ) 	


	/**
	 * 	\brief
	 * 	Defines the data type of the fixed-size memory block for 
	 * 	dynamic event support. 
	 *
	 * 	The fixed-size memory block can be implemented with a RTOS/OS 
	 * 	service provided to that. But it's also possible to use the native 
	 * 	RKH fixed-size memory block RKHMP_T type if the underlying RTOS/OS 
	 * 	does not provide an adequate support.
	 */

	#define RKH_DYNE_TYPE

	/**
	 * 	\brief
	 * 	Encapsulates the creation of a event pool. 
	 *
	 * 	Platform-dependent macro. Typically, must be define it in the 
	 * 	specific port file (rkhport.h).
	 *
	 * 	\param mp		pointer to previously allocated memory pool structure.
	 * 	\param sstart	storage start. Pointer to memory from which memory 
	 * 					blocks are allocated.
	 * 	\param ssize:	storage size. Size of the memory pool storage in bytes.
	 * 	\param esize	event size. This number determines the size of each 
	 * 					memory block in the pool.
	 */

	#define RKH_DYNE_INIT( mp, sstart, ssize, esize )

	/**
	 * 	\brief
	 * 	Encapsulates how RKH should obtain the block size of pool.
	 *
	 * 	Platform-dependent macro. Typically, must be define it in the 
	 * 	specific port file (rkhport.h).
	 *
	 * 	\param mp		pointer to previously allocated memory pool structure.
	 */

	#define RKH_DYNE_GET_ESIZE( mp )

	/**
	 * 	\brief
	 *	Encapsulates how RKH should obtain an event \c e from the 
	 *	event pool \c mp.
	 * 
	 * 	Platform-dependent macro. Typically, must be define it in the 
	 * 	specific port file (rkhport.h).
	 *
	 * 	\param mp		pointer to previously allocated memory pool structure.
	 * 	\param e		pointer to a new event or NULL if the pool 
	 * 					runs out of blocks.
	 */

	#define RKH_DYNE_GET( mp, e )

	/**
	 * 	\brief
	 *	Encapsulates how RKH should return an event \c e to the event 
	 *	pool \c mp.
	 *
	 * 	Platform-dependent macro. Typically, must be define it in the 
	 * 	specific port file (rkhport.h).
	 *
	 * 	\param mp		pointer to previously allocated memory pool structure.
	 * 	\param e		pointer to the returned event.
	 */

	#define RKH_DYNE_PUT( mp, e )
#endif


#ifdef RKH_CPUSR_TYPE
	#if RKH_EN_DOXYGEN == RKH_DEF_DISABLED
		#define RKH_SR_ALLOC()				RKH_CPUSR_TYPE sr = \
														(RKH_CPUSR_TYPE)0
		#define RKH_ENTER_CRITICAL_()		RKH_ENTER_CRITICAL( sr )
		#define RKH_EXIT_CRITICAL_()		RKH_EXIT_CRITICAL( sr )
	#endif
#else
	#define RKH_SR_ALLOC()
	#define RKH_ENTER_CRITICAL_()			RKH_ENTER_CRITICAL( dummy )
	#define RKH_EXIT_CRITICAL_()			RKH_EXIT_CRITICAL( dummy )
#endif


/*
 * 	For GNU compatibility.
 */

struct rkh_t;
struct rkhsma_t;


#define CIA( s )	((RKHINIT_T)((s)->romrkh->iaction))

/**
 * 	\brief
 * 	Initialization action.
 *
 * 	Frequently, the state transition originating at the black ball is called 
 * 	the initial transition. Such transition designates the first active state 
 * 	after the state machine object is created. An initial transition can have 
 * 	associated actions, which in the UML notation are enlisted after the 
 * 	forward slash (/). In RKH framework, the application code must trigger 
 * 	the initial transition explicitly by invoking rkh_sma_activate() function.
 */

#if (RKH_SMA_EN_INIT_ARG_SMA == RKH_DEF_ENABLED && \
		RKH_SMA_EN_IEVENT == RKH_DEF_ENABLED)
	typedef void ( *RKHINIT_T )( const void *sma, 
										const struct rkhevt_t *e );
	#define RKH_EXEC_INIT( h )										\
	{																\
		if( CIA( h ) != NULL )										\
			(*CIA( h ))( (h), CIA(h)->romrkh->ievent );				\
	}
#elif (RKH_SMA_EN_INIT_ARG_SMA == RKH_DEF_ENABLED && \
		RKH_SMA_EN_IEVENT == RKH_DEF_DISABLED)
	typedef void ( *RKHINIT_T )( const struct rkhsma_t *sma );
	#define RKH_EXEC_INIT( h )										\
	{																\
		if( CIA( h ) != NULL )										\
			(*CIA( h ))( (h) );										\
	}
#elif (RKH_SMA_EN_INIT_ARG_SMA == RKH_DEF_DISABLED && \
		RKH_SMA_EN_IEVENT == RKH_DEF_ENABLED)
	typedef void ( *RKHINIT_T )( const struct rkhevt_t *e );
	#define RKH_EXEC_INIT( h )										\
	{																\
		if( CIA( h ) != NULL )										\
			(*CIA( h ))( CIA(h)->romrkh->ievent );					\
	}
#else
	typedef void ( *RKHINIT_T )( void );
	#define RKH_EXEC_INIT( h )										\
	{																\
		if( CIA( h ) != NULL )										\
			(*CIA( h ))();											\
	}
#endif


/**
 * 	\brief 
 * 	Defines the data structure into which the collected performance 
 * 	information for state machine is stored.
 * 	
 * 	This member is optional, thus it could be declared as NULL or eliminated 
 * 	in compile-time with RKH_EN_SMA_GET_INFO = 0.
 */

typedef struct rkh_smai_t
{
	rkhui16_t ndevt;			/**< # of dispatched events */
	rkhui16_t exectr;			/**< # of executed transitions */
} RKH_SMAI_T;


/**
 * 	\brief
 * 	Constant parameters of state machine.
 *
 *	The constant key parameters of a state machine are allocated within. 
 *	ROMRKH_T is a ROM base structure of RKH_T.
 *
 *	\sa
 *	RKHSMA_T structure definition for more information. Also, \link RKHEVT_T 
 *	single inheritance in C \endlink, and \link RKH_CREATE_BASIC_STATE 
 *	another example \endlink.
 */

typedef struct romrkh_t
{
	/**
	 * 	\brief
	 * 	SMA (a.k.a Active Object) priority. 
	 *
	 * 	A unique priority number must be assigned to each SMA from 0 to 
	 * 	RKH_LOWEST_PRIO. The lower the number, the higher the priority. 
	 */

	rkhui8_t prio;

	/**
 	 * 	\brief
	 * 	State machine properties. 
	 *
	 * 	The available properties are enumerated in RKH_HPPTY_T enumeration in 
	 * 	the rkh.h file.
	 */

	rkhui8_t ppty;

	/**	
 	 * 	\brief
	 * 	ID of state machine application. 
	 * 	
	 * 	ID of state machine application. This number allows to uniquely 
	 * 	identify a state machine. When a particular application requires 
	 * 	runtime tracing (native tracing features), the option RKH_SMA_EN_ID 
	 * 	must be set to one. 
	 */

#if RKH_SMA_EN_ID == RKH_DEF_ENABLED
	rkhui8_t id;
#endif

	/** 
 	 * 	\brief
	 * 	Points to initial state. 
	 *
	 * 	This state could be defined either composite or basic 
	 * 	(not pseudo-state).
	 */

	RKHROM struct rkhst_t *istate;

	/** 
 	 * 	\brief
	 * 	Points to initializing action (optional). 
	 *
	 * 	The function prototype is defined as RKHINIT_T. This argument is 
	 * 	optional, thus it could be declared as NULL.
	 */

	RKHINIT_T iaction;

	/**
	 * 	\brief
	 *	Pointer to an event that will be passed to state machine application 
	 *	when it starts. Could be used to pass arguments to the state machine 
	 *	like an argc/argv. This argument is optional, thus it could be 
	 *	declared as NULL or eliminated in compile-time with 
	 *	RKH_SMA_EN_IEVENT = 0.
	 */

#if RKH_SMA_EN_IEVENT == RKH_DEF_ENABLED
	const RKHEVT_T *ievent;
#endif
} ROMRKH_T;


/**
 * 	\brief 
 * 	Describes the SMA (active object in UML).
 *
 *	This structure resides in RAM because its members are dinamically updated
 *	by RKH (context of state machine).
 *	The \b #romrkh member points to ROMRKH_T structure, allocated in ROM, 
 *	to reduce the size of RAM consume. The key parameters of a state machine 
 *	are allocated within. Therefore cannot be modified in runtime.
 *
 * 	RKHSMA_T is not intended to be instantiated directly, but rather
 * 	serves as the base structure for derivation of state machines in the
 * 	application code.
 * 	The following example illustrates how to derive an state machine from
 * 	RKH_T. Please note that the RKHSMA_T member sm is defined as the
 * 	FIRST member of the derived struct.
 *
 *	Example:
 *	\code
 *	//	...within state-machine's module
 *
 *	typedef struct
 *	{
 *		RKHSMA_T sm;	// base structure
 *		rkhui8_t x;		// private member
 *		rkhui8_t y;		// private member
 *	} MYSM_T;
 *
 * 	//	static instance of SMA object
 *	RKH_SMA_CREATE( MYSM_T, 0, my, HCAL, &S1, my_iaction, &my_ievent );
 *	\endcode
 *
 *	\sa
 *	RKHSMA_T structure definition for more information. Also, \link RKHEVT_T 
 *	single inheritance in C \endlink, and \link RKH_CREATE_BASIC_STATE 
 *	another example \endlink.
 */

typedef struct rkhsma_t
{
	/**
 	 * 	\brief
	 * 	Points to state machine object.
	 */
	
	RKHROM ROMRKH_T *romrkh;

	/** 
 	 * 	\brief
	 * 	Points to current state (basic state).
	 */

	RKHROM struct rkhst_t *state;

	/**
	 * 	\brief
	 * 	OS-dependent thread of control of the active object.
	 *
	 * 	Frequently, the active object has its own task processing loop that 
	 * 	waits for the signal to be posted, and when it is, loops to remove 
	 * 	and process all events that are currently queued.
	 * 	The RKH_SMA_POST_FIFO() macro enqueues an event and signals	the OS 
	 * 	that an event has arrived. In this case, \c os_signal holds the OS 
	 * 	object used to signal that an event has been queued.
     *	This data might be used in various ways, depending on the RKH port.
     * 	In some ports it's used to store the thread handler.
	 *
	 * 	\note
	 * 	This member is optional, thus it could be declared as NULL or 
	 * 	eliminated in compile-time with RKH_EN_SMA_THREAD = 0.
	 */

#if RKH_EN_SMA_THREAD == RKH_DEF_ENABLED
	RKH_THREAD_TYPE thread;
#endif

	/**
	 * 	\brief
	 *	OS-dependent object used to signal that an event has been queued.
	 *
	 * 	Frequently, the active object has its own task processing loop that 
	 * 	waits for the signal to be posted, and when it is, loops to remove 
	 * 	and process all events that are currently queued.
	 * 	The RKH_SMA_POST_FIFO() macro enqueues an event and signals	the OS 
	 * 	that an event has arrived. In this case, \c os_signal holds the OS 
	 * 	object used to signal that an event has been queued.
	 * 	This data might be used in various ways, depending on the RKH port.
	 * 	In some ports it's used to block the calling thread when the native 
	 * 	RKH queue is empty. In other RKH ports the OS-dependent	data object 
	 * 	might be used differently.
	 * 	
	 * 	\note
	 * 	This member is optional, thus it could be eliminated in compile-time 
	 * 	with RKH_EN_SMA_THREAD_DATA = 0.
	 */

#if (RKH_EN_SMA_THREAD == RKH_DEF_ENABLED && \
		RKH_EN_SMA_THREAD_DATA == RKH_DEF_ENABLED)
	RKH_OSSIGNAL_TYPE os_signal;
#endif

	/**
	 * 	\brief
	 * 	Event queue of the SMA (a.k.a Active Object).
	 */

	RKH_EQ_TYPE equeue;

	/**
	 * 	\brief
	 * 	The Boolean loop variable determining if the thread routine
	 * 	of the SMA is running.
	 */

	rkhui8_t running;

	/** 
 	 * 	\brief
	 * 	Performance information. This member is optional, thus it could be 
	 * 	declared as NULL or eliminated in compile-time with 
	 * 	RKH_SMA_EN_GET_INFO = 0.
	 */

#if RKH_SMA_EN_GET_INFO == RKH_DEF_ENABLED
	RKH_SMAI_T sinfo;
#endif	

} RKHSMA_T;


/**
 * 	\brief
 * 	Entry action.
 *
 * 	The actions that are always executed when a state is entered 
 * 	should be specified as entry actions. UML statecharts provide optional 
 * 	entry and exit actions, which are associated with states rather than 
 * 	transitions, as in a Moore automaton.
 * 	An entry function takes the state machine pointer as argument. 
 * 	This argument is optional, thus it could be eliminated in 
 * 	compile-time by means of RKH_SMA_EN_ENT_ARG_SMA.
 *
 * 	The RKH implementation preserves the transition sequence imposed by 
 * 	Harel's Statechart and UML. Specifically, the implemented transition 
 * 	sequence is as follows:
 *
 * 	- Execute exit actions of the source state.
 * 	- Execute the transition actions.
 * 	- Execute entry actions of the target state.
 * 
 * 	\note
 * 	This callback is referenced from RKH_CREATE_COMP_STATE() and 
 * 	RKH_CREATE_BASIC_STATE() macros.
 * 	\b RKH_SMA_EN_ENT_ARG_SMA macro.
 */


#if RKH_SMA_EN_ENT_ARG_SMA == RKH_DEF_ENABLED
	typedef void ( *RKHENT_T )( const struct rkhsma_t *sma );
	#define RKH_EXEC_ENTRY( s, h )				\
	{											\
		if( (s)->enter != NULL )				\
			(*(s)->enter)( h ); 				\
	}
#else
	typedef void ( *RKHENT_T )( void );
	#define RKH_EXEC_ENTRY( s, h )				\
	{											\
		if( (s)->enter != NULL )				\
			(*(s)->enter)(); 					\
	}
#endif


/**
 * 	\brief
 * 	Exit action.
 *
 * 	The actions that are always execute when a state is exited should be 
 * 	exit actions. UML statecharts provide optional entry and exit actions, 
 * 	which are associated with states rather than transitions, as in a 
 * 	Moore automaton.
 * 	An exit function takes the state machine pointer as argument. 
 * 	This argument is optional, thus it could be eliminated in 
 * 	compile-time by means of RKH_SMA_EN_EXT_ARG_SMA.
 *
 * 	The RKH implementation preserves the transition sequence imposed by 
 * 	Harel's Statechart and UML. Specifically, the implemented transition 
 * 	sequence is as follows:
 *
 * 	- Execute exit actions of the source state.
 * 	- Execute the transition actions.
 * 	- Execute entry actions of the target state.
 *
 * 	\note
 * 	This callback is referenced from RKH_CREATE_COMP_STATE() and 
 * 	RKH_CREATE_BASIC_STATE() macros.
 */

#if RKH_SMA_EN_EXT_ARG_SMA == RKH_DEF_ENABLED
	typedef void ( *RKHEXT_T )( const struct rkhsma_t *sma );
	#define RKH_EXEC_EXIT( s, h )				\
	{											\
		if( (s)->exit != NULL )					\
			(*(s)->exit)( h ); 					\
	}
#else
	typedef void ( *RKHEXT_T )( void );
	#define RKH_EXEC_EXIT( s, h )				\
	{											\
		if( (s)->exit != NULL )					\
			(*(s)->exit)(); 					\
	}
#endif



/**
 * 	\brief
 * 	Event preprocessor.
 *
 * 	Before sending the arrived event to state machine, it can be previously 
 * 	processed using the	event preprocessor function.
 * 	The RKH framework provides optional event preprocessor 
 * 	action, which are associated with states rather than transitions, 
 * 	as in a Moore automaton.
 * 	This action takes the state machine pointer and the event 
 * 	pointer as arguments. 
 * 	This argument is optional, thus it could be eliminated in 
 * 	compile-time by means of RKH_SMA_EN_PPRO_ARG_SMA.
 *
 * 	\note
 * 	This callback is referenced from RKH_CREATE_COMP_STATE() and 
 * 	RKH_CREATE_BASIC_STATE() macros.
 */

#if RKH_SMA_EN_PPRO_ARG_SMA == RKH_DEF_ENABLED
	typedef RKHE_T ( *RKHPPRO_T )( const struct rkhsma_t *sma, RKHEVT_T *pe );
	#define rkh_call_prepro(s,h,e)		(*(s)->prepro)( h, e )
#else
	typedef RKHE_T ( *RKHPPRO_T )( RKHEVT_T *pe );
	#define rkh_call_prepro(s,h,e)		(*(s)->prepro)( e )
#endif


#define CTA( ta )	((RKHACT_T)(ta))

/**
 * 	\brief
 * 	Transition action.
 *
 * 	Transition actions are small atomic behaviors executed at specified points 
 * 	in a state machine. This actions are assumed to take an insignificant 
 * 	amount of time to execute and are noninterruptible. UML statecharts 
 * 	are extended state machines with characteristics of both Mealy and 
 * 	Moore automata. In statecharts, actions generally depend on both 
 * 	the state of the system and the triggering event, as in a Mealy 
 * 	automaton. Additionally, UML statecharts provide optional entry and 
 * 	exit actions, which are associated with states rather than transitions, 
 * 	as in a Moore automaton.
 * 	An action function takes the state machine pointer and the event 
 * 	pointer as arguments. 
 * 	These arguments are optional, thus they could be eliminated in 
 * 	compile-time by means of RKH_SMA_EN_ACT_ARG_EVT and \b 
 * 	RKH_SMA_EN_ACT_ARG_SMA.
 *
 * 	The RKH implementation preserves the transition sequence imposed by 
 * 	Harel's Statechart and UML. Specifically, the implemented transition 
 * 	sequence is as follows:
 *
 * 	- Execute exit actions of the source state.
 * 	- Execute the transition actions.
 * 	- Execute entry actions of the target state.
 *
 * 	\note
 * 	This callback is referenced from RKH_TRREG() and RKH_TRINT()macro. 
 */

#if (RKH_SMA_EN_ACT_ARG_EVT == RKH_DEF_ENABLED && \
		RKH_SMA_EN_ACT_ARG_SMA == RKH_DEF_ENABLED)
	typedef void (*RKHACT_T)( const struct rkhsma_t *sma, RKHEVT_T *pe );
	#define RKH_CALL_ACTION( a,h,e )	(*CTA( a ))( (h), (e) )
#elif (RKH_SMA_EN_ACT_ARG_EVT == RKH_DEF_ENABLED && \
		RKH_SMA_EN_ACT_ARG_SMA == RKH_DEF_DISABLED)
	typedef void (*RKHACT_T)( RKHEVT_T *pe );
	#define RKH_CALL_ACTION( a,h,e )	(*CTA( a ))( (e) )
#elif (RKH_SMA_EN_ACT_ARG_EVT == RKH_DEF_DISABLED && \
		RKH_SMA_EN_ACT_ARG_SMA == RKH_DEF_ENABLED)
	typedef void (*RKHACT_T)( const struct rkhsma_t *sma );
	#define RKH_CALL_ACTION( a,h,e )	(*CTA( a ))( (h) )
#else
	typedef void (*RKHACT_T)( void );
	#define RKH_CALL_ACTION( a,h,e )	(*CTA( a ))()
#endif


/**
 * 	\brief
 * 	Guard.
 *
 *	A guard is a boolean condition that returns a TRUE (RKH_GTRUE) or 
 *	FALSE (RKH_GFALSE) value that controls whether or not a transition 
 *	is taken following the receipt of a triggering event. A transition 
 *	with a guard is only take if the triggering event occurs and the 
 *	guard evaluates to TRUE. As long as the guard evaluated to FALSE, 
 *	the triggering event would be discarded and the transition would 
 *	not be taken.
 *	Each condition connector can have one special branch with a guard 
 *	labeled rkh_else, which is taken if all the guards on the other 
 *	branches are false. 
 * 	A guard function takes the state machine pointer and the event 
 * 	pointer as arguments. 
 * 	These arguments are optional, thus they could be eliminated in 
 * 	compile-time by means of \b RKH_SMA_EN_GRD_ARG_EVT and 
 * 	\b RKH_SMA_EN_GRD_ARG_SMA.
 *
 * 	\note
 * 	This callback is referenced from RKH_BRANCH() macro. 
 */

#if (RKH_SMA_EN_GRD_ARG_EVT == RKH_DEF_ENABLED && \
		RKH_SMA_EN_GRD_ARG_SMA == RKH_DEF_ENABLED)
	typedef HUInt (*RKHGUARD_T)( const struct rkhsma_t *sma, RKHEVT_T *pe );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( h, e )
	HUInt rkh_else( const struct rkhsma_t *sma, RKHEVT_T *pe );
#elif (RKH_SMA_EN_GRD_ARG_EVT == RKH_DEF_ENABLED && \
		RKH_SMA_EN_GRD_ARG_SMA == RKH_DEF_DISABLED)
	typedef HUInt (*RKHGUARD_T)( RKHEVT_T *pe );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( e )
	HUInt rkh_else( RKHEVT_T *pe );
#elif (RKH_SMA_EN_GRD_ARG_EVT == RKH_DEF_DISABLED && \
		RKH_SMA_EN_GRD_ARG_SMA == RKH_DEF_ENABLED)
	typedef HUInt (*RKHGUARD_T)( const struct rkhsma_t *sma );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( h )
	HUInt rkh_else( const struct rkhsma_t *sma );
#else
	typedef HUInt (*RKHGUARD_T)( void );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)()
	HUInt rkh_else( void );
#endif


/**
 * 	\brief 
 * 	Maintains the basic information of a state.
 */

typedef struct rkhbase_t
{
	/**	
 	 * 	\brief
	 * 	State type.
	 *
	 *	Contains the type of a particular state and can have 
	 *	the following values:
	 *
	 *	- \b RKH_COMPOSITE: 	composite state.
	 *	- \b RKH_BASIC: 		basic state.
	 *	- \b RKH_CHOICE: 		choice pseudostate.
	 *	- \b RKH_CONDITIONAL: 	conditional pseudostate.
	 *	- \b RKH_SHISTORY: 		shadow history pseudostate.
	 *	- \b RKH_DHISTORY: 		deep history pseudostate.
	 */

	HUInt type;					

	/**	
 	 * 	\brief
	 *	State ID. 
	 *
	 *	This number isn't internally used by RKH framework.
	 */

#if RKH_SMA_EN_STATE_ID == RKH_DEF_ENABLED
	HUInt id;
#endif
} RKHBASE_T;


/**
 * 	\brief
 * 	Describes the state transition. 
 *
 * 	Transitions represent the response of a state machine to events. 
 * 	Any event that is not explicitly listed as causing an event to occur 
 * 	in a given state is quietly discarded should it occur.
 */

typedef struct rkhtr_t
{
	/** 	
 	 * 	\brief
	 *  Triggering event.
	 */

	RKHE_T event;
	
	/**	
 	 * 	\brief
	 *	Points to guard function.
	 */

	RKHGUARD_T guard;
	
	/** 	
 	 * 	\brief
	 *  Points to transition action.
	 */

	RKHACT_T action;

	/** 	
 	 * 	\brief
	 *  Points to target state.
	 */

	RKHROM void *target;
} RKHTR_T;


/**
 * 	\brief
 * 	Describes the exit point connection. 
 *
 * 	...
 */

typedef struct rkhexpcn_t
{
	/** 	
 	 * 	\brief
	 *  Points to transition action.
	 */

	RKHACT_T action;

	/** 	
 	 * 	\brief
	 *  Points to target state.
	 */

	RKHROM void *target;
} RKHEXPCN_T;


/**
 * 	\brief
 * 	Describes the entry point connection. 
 *
 * 	...
 */

typedef struct rkhenpcn_t
{
	/** 	
 	 * 	\brief
	 *  Points to transition action.
	 */

	RKHACT_T action;

	/** 	
 	 * 	\brief
	 *  Points to target state.
	 */

	RKHROM void *target;
} RKHENPCN_T;


/**
 *	\brief
 * 	Describes the common properties of regular states (basic, composite, 
 * 	and submachine).
 */

typedef struct rkhst_t
{
	/**	
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

#if RKH_SMA_EN_HCAL == RKH_DEF_ENABLED
	/**	
 	 * 	\brief
	 *	Points to entry action.
	 */

	RKHENT_T enter;

	/**	
 	 * 	\brief
	 *	Points to exit action.
	 */

	RKHEXT_T exit;

	/**	
 	 * 	\brief
	 *	Points to state's parent.
	 */

	RKHROM struct rkhst_t *parent;
#endif

} RKHST_T;


/**
 *	\brief
 * 	Describes a basic state.
 */

typedef struct rkhsbsc_t
{
	RKHST_T st;

	/**	
 	 * 	\brief
	 *	Points to state transition table.
	 */

	RKHROM struct rkhtr_t *trtbl;

	/**	
 	 * 	\brief
	 *	Points to event preprocessor.
	 *
	 *	Aditionally, by means of single inheritance in C it could be 
	 *	used as state's abstract data.
	 *	Aditionally, implementing the single inheritance in C is very 
	 *	simply by literally embedding the base type, RKHPPRO_T in 
	 *	this case, as the first member of the derived structure.
	 *	
	 *	This argument is optional, thus it could be declared as NULL.
	 *
	 *	Example:
	 *  
	 *  \code
	 *	static
	 *	RKHE_T
	 *	preprocessor( RKHEVT_T *pe )
	 *	{
	 *		...
	 *	}
	 *  
	 *	typedef struct
	 *	{
	 *		RKHPPRO_T prepro; 	// extend the RKHPPRO_T class
	 *		unsigned min:4;
	 *		unsigned max:4;
	 *		char *buff;
	 *	} SDATA_T;
	 *
	 *	static const SDATA_T option = { preprocessor, 4, 8, token1 };
	 *
	 *	RKH_CREATE_BASIC_STATE( S111, 0, set_x_1, 
	 *					NULL, &S11, preprocessor ); 
	 *	RKH_CREATE_BASIC_STATE( S22, 0, set_x_4, 
	 *					NULL, &S2, (RKHPPRO_T*)&option ); 
	 * \endcode
	 */

#if RKH_SMA_EN_PPRO == RKH_DEF_ENABLED
	RKHPPRO_T prepro;
#endif

} RKHSBSC_T;


/**
 *	\brief
 * 	Describes a composite state.
 */

typedef struct rkhscmp_t
{
	RKHST_T st;

	/**	
 	 * 	\brief
	 *	Points to state transition table.
	 */

	RKHROM struct rkhtr_t *trtbl;

	/**	
 	 * 	\brief
	 *	Points to event preprocessor.
	 *
	 *	Aditionally, by means of single inheritance in C it could be 
	 *	used as state's abstract data.
	 *	Aditionally, implementing the single inheritance in C is very 
	 *	simply by literally embedding the base type, RKHPPRO_T in 
	 *	this case, as the first member of the derived structure.
	 *	
	 *	This argument is optional, thus it could be declared as NULL.
	 *
	 *	Example:
	 *  
	 *  \code
	 *	static
	 *	RKHE_T
	 *	preprocessor( RKHEVT_T *pe )
	 *	{
	 *		...
	 *	}
	 *  
	 *	typedef struct
	 *	{
	 *		RKHPPRO_T prepro; 	// extend the RKHPPRO_T class
	 *		unsigned min:4;
	 *		unsigned max:4;
	 *		char *buff;
	 *	} SDATA_T;
	 *
	 *	static const SDATA_T option = { preprocessor, 4, 8, token1 };
	 *
	 *	RKH_CREATE_BASIC_STATE( S111, 0, set_x_1, 
	 *					NULL, &S11, preprocessor ); 
	 *	RKH_CREATE_BASIC_STATE( S22, 0, set_x_4, 
	 *					NULL, &S2, (RKHPPRO_T*)&option ); 
	 * \endcode
	 */

#if RKH_SMA_EN_PPRO == RKH_DEF_ENABLED
	RKHPPRO_T prepro;
#endif

#if RKH_SMA_EN_HCAL == RKH_DEF_ENABLED
	/**	
 	 * 	\brief
	 *	Points to state's default child.
	 */

	RKHROM void *defchild;

	/**	
 	 * 	\brief
	 *	Points to state's history. 
	 */

	RKHROM struct rkhshist_t *history;
#endif

} RKHSCMP_T;


/**
 *	\brief
 * 	Describes a submachine state.
 *
 * 	A submachine state is a kind of a state that actually refers to 
 * 	another defined state machine.
 * 	A submachine state is logically equivalent to the insertion of the 
 * 	referenced state machine as a composite state in the place of 
 * 	the submachine state. Consequently, every entrance to a submachine 
 * 	state is equivalent to the corresponding entrance to the inserted 
 * 	(referenced) composite state. In particular, it can be entered 
 * 	thruough its initial pseudostate (as any other composite state), or 
 * 	through one of its entry points. 
 *
 * 	Similary, every exit from a submachine state is equivalent to the 
 * 	corresponding exit from the inserted composite state. It can be exited 
 * 	through one of its exit points. When it is exited through its exit point 
 * 	the effect of the transition targeting the exit point is executed first, 
 * 	followed by the exit behavior of the composite state. 
 *
 * 	The entry, exit, and behavior actions and internal transitions are 
 * 	defined as part of the state. Submachine state is a decomposition 
 * 	mechanism that allows factoring of common behaviors and their reuse.
 *
 * 	The purpose od defining submachine states is to decompose and localize 
 * 	repetitive parts because the same state machine can be referenced from 
 * 	more than one submachine state.
 *
 *	The diagram in following figure shows a fragment from a state machine 
 *	diagram in which a submachine state (the \c SB) is referenced.
 *	
 *	\anchor fig_sbm1
 *	\image html sbm1.png "Submachine state"
 *	
 *	In the above example, the transition triggered by event \c TWO will 
 *	terminate on entry point \c ENS12 of the \c SB state machine. 
 *	The \c ONE transition implies taking of the default transition of the 
 *	\c SB and executes the \c act5() action. The transition emanating from 
 *	the \c EX1S12 exit point of the submachine will execute the \c act1() 
 *	behavior in addition to what is executed within the \c SB state machine. 
 *	Idem transition emanating from the \c EX2S12.
 *	This transition must have been triggered within the \c SB state machine. 
 *	Finally, the transition emanating from the edge of the submachine state 
 *	is triggered by event \c THREE.
 *	
 *	The following figure is an example of a state machine \c SB defined with 
 *	two exit points, \c EXPNT1 and \c EXPNT2, and one entry point \c ENPNT.
 *	
 *	\anchor fig_sbm2
 *	\image html sbm2.png "State machine with two exit points and one entry point"
 *	
 *	In the following figure the state machine shown above is referenced twice in 
 *	a submachine state \c S12 and \c S2.
 *	
 *	\anchor fig_sbm3
 *	\image html sbm3.png "Submachine state with usage of exit and entry points"
 */

typedef struct rkhssbm_t
{
	RKHST_T st;

	/**	
 	 * 	\brief
	 *	Points to state transition table.
	 */

	RKHROM struct rkhtr_t *trtbl;

	/**	
 	 * 	\brief
	 *	Points to state transition table.
	 */

	RKHROM struct rkhexpcn_t *exptbl;

	/**	
 	 * 	\brief
	 *	Points to submachine object.
	 */

	RKHROM struct rkhrsm_t *sbm;

} RKHSSBM_T;


/**
 *	\brief
 * 	Describes a (referenced) submachine state machine.
 */

typedef struct rkhrsm_t
{
	/**	
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Points to state's default child.
	 */

	RKHROM void *defchild;

	/** 
 	 * 	\brief
	 * 	Points to initializing action (optional). 
	 *
	 * 	The function prototype is defined as RKHACT_T. This argument is 
	 * 	optional, thus it could be declared as NULL.
	 */

	RKHACT_T iaction;

	/**	
 	 * 	\brief
	 *	Points to RAM memory location which stores
	 *	the dynamic parent.
	 */

	RKHROM struct rkhst_t **dyp;
} RKHRSM_T;


/**
 * 	\brief 
 * 	Describes the entry point pseudostate.
 *
 * 	An entry pseudostate is used to join an external transition terminating 
 * 	on that entry point to an internal transition emanating from that entry 
 * 	point.
 * 	The main purpose of such entry and exit points is to execute the state 
 * 	entry and exit actions respectively in between the actions that are 
 * 	associated with the joined transitions.
 */

typedef struct rkhsenp_t
{
	/**
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Points to entry point connection.
	 */

	RKHROM RKHENPCN_T *enpcn;

	/**	
 	 * 	\brief
	 *	Points to state's parent (submachine state).
	 */

	RKHROM struct rkhst_t *parent;

} RKHSENP_T;


/**
 * 	\brief 
 * 	Describes the exit point pseudostate.
 *
 * 	An exit pseudostate is used to join an internal transition terminating on 
 * 	that exit point to an external transition emanating from that exit point. 
 * 	The main purpose of such entry and exit points is to execute the state 
 * 	entry and exit actions respectively in between the actions that are 
 * 	associated with the joined transitions.
 */

typedef struct rkhsexp_t
{
	/**
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Index of exit point table.
	 */

	rkhui8_t ix;

	/**	
 	 * 	\brief
	 *	Points to state's parent (referenced submachine).
	 */

	RKHROM RKHRSM_T *parent;
} RKHSEXP_T;


/**
 * 	\brief 
 * 	Describes the conditional pseudostate.
 */

typedef struct rkhscond_t
{
	/**
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Points to branch table.
	 */

	RKHROM struct rkhtr_t *trtbl;
} RKHSCOND_T;


/**
 * 	\brief 
 * 	Describes the choice pseudostate.
 */

typedef struct rkhschoice_t
{
	/**
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Points to branch table.
	 */

	RKHROM struct rkhtr_t *trtbl;
} RKHSCHOICE_T;


/**
 * 	\brief 
 * 	Describes the history pseudostate
 *
 * 	It can be either be shallow or deep.
 */

typedef struct rkhshist_t
{
	/**	
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Points to state's parent.
	 */

	RKHROM RKHST_T *parent;

	/**	
 	 * 	\brief
	 *	Points to RAM memory location which stores
	 *	the state's history.
	 */

	RKHROM RKHST_T **target;
} RKHSHIST_T;


#endif
