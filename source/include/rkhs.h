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
 *  File                     : rkhs.h
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	sch
 *
 *	\brief 		Platform-independent interface to the RKS scheduler.
 */


#ifndef __RKHS_H__
#define __RKHS_H__


#include "rkhcfg.h"
#include "rkhrdy.h"
#include "rkhevt.h"


#if RKH_EN_NATIVE_SCHEDULER == 1 && \
	RKH_EN_DOXYGEN == 0

	#define RKH_EQ_TYPE				RKHRQ_T

	#define RKH_SMA_BLOCK( sma ) 							\
					RKHASSERT( ((RKHSMA_T*)(sma))->equeue.qty != 0 )

	#define RKH_SMA_READY( rg, sma ) 						\
					rkh_rdy_ins( (rg), ((RKHSMA_T*)(sma))->romrkh->prio )

	#define RKH_SMA_UNREADY( rg, sma ) 						\
					rkh_rdy_rem( (rg), ((RKHSMA_T*)(sma))->romrkh->prio )

	extern RKHRG_T rkhrg;

#endif


#endif
