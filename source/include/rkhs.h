/*
 *	file: rkhs.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 22, 2012
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
 * 	\file rkhs.h
 *	\brief
 *	Platform-independent interface to the RKS scheduler.
 */


#ifndef __RKHS_H__
#define __RKHS_H__


#include "rkhcfg.h"
#include "rkh.h"
#include "rkhevt.h"


#if RKH_EN_NATIVE_SCHEDULER == 1

#define RKH_EQ_TYPE				RKHQ_T


#define RKH_SMA_BLOCK( sma ) 						\
			    RKHASSERT( (sma)->eq.qty != 0 )

#define RKH_SMA_READY( sma ) 						\
			    rkh_rdyins( (sma)->romrkh->prio )

#define RKH_SMA_UNREADY( sma ) 						\
			    rkh_rdyrem( (sma)->romrkh->prio )


#define RKH_DYNE_TYPE			RKHMP_T

#define RKH_DYNE_INIT( mp, sstart, ssize, esize ) 			\
    			rkh_mp_init( (mp), sstart, ssize, esize )

#define RKH_DYNE_GET_ESIZE( mp )	\
				( (mp)->bsize )

#define RKH_DYNE_GET( mp, e )								\
				( (e) = (RKHEVT_T*)rkh_mp_get( (mp) ) )

#define RKH_DYNE_PUT( mp, e )				\
				( rkh_mp_put( (mp), e ) )


extern RKHRG_T rkhrg;


#endif
#endif
