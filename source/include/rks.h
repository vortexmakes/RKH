/*
 *	file: rks.h
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
 * 	\file rks.h
 *	\brief
 *	Platform-independent interface to the RKS scheduler.
 */


#ifndef __RKS_H__
#define __RKS_H__


#include "rkhitl.h"
#include "rkh.h"
#include "rkhassert.h"


/**
 *	Defines the event queue type for the RKS scheduler.
 */

#define RKH_EQ_TYPE					RKHQ_T


/**
 * 	Defines event queue support.
 */

#define SMA_EQ_WAIT( sma ) 								\
    Q_ASSERT((me_)->eQueue.frontEvt != (QEvent *)0)

#if RKH_MAX_SMA <= 8
    #define SMA_EQ_EVENT( sma ) 						\
        QPSet8_insert(&QF_readySet_, (me_)->prio)

    #define SMA_EQ_IS_EMPTY( sma ) 						\
        QPSet8_remove(&QF_readySet_, (me_)->prio)
#else
    #define SMA_EQ_EVENT( sma ) 						\
        QPSet64_insert(&QF_readySet_, (me_)->prio)

    #define SMA_EQ_IS_EMPTY_( sma ) 					\
        QPSet64_remove(&QF_readySet_, (me_)->prio)
#endif


/**
 *	Defines the event pool type for the RKS scheduler.
 */

#define RKH_EP_TYPE              	RKHMP_T


/**
 * 	Defines event pool support.
 */

#define RKH_EP_INIT(p_, poolSto_, poolSize_, evtSize_) 	\
    QMPool_init(&(p_), (poolSto_), (poolSize_), (QMPoolSize)(evtSize_))
#define RKH_EP_GET_ESIZE(p_)    	((p_).blockSize)
#define RKH_EP_GET(p_, e_)       	((e_) = (QEvent *)QMPool_get(&(p_)))
#define RKH_EP_PUT(p_, e_)       	(QMPool_put(&(p_), (e_)))
                                         

/** 
 * 	RKH ready group of state machine applications.
 */

#if RKH_MAX_SMA <= 8
    extern RKH_RG8_T rkh_rdygrp;	
#else
    extern RKH_RG64_T rkh_rdygrp;
#endif


#endif
