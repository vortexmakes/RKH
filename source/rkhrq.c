/*
 *	file: rkhrq.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 23, 2012
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
 * 	\file rkhrq.c
 *
 *	\brief
 * 	Implements a queue (by reference) services.
 *
 * 	The queue is a buffer-like object through which state machine applications 
 * 	(SMA) and ISRs send and receive messages to communicate and synchornize 
 * 	with data. It temporarily holds pointer to messages from a sender until 
 * 	the intended receiver is ready to read them.
 */


#include "rkhrq.h"


void 
rkh_rq_init( RKHRQ_T *q, const void **sstart, RKH_RQNE_T ssize, 
													rkhui8_t sched )
{
}


HUInt 
rkh_rq_is_full( RKHRQ_T *q )
{
}


RKH_RQNE_T 
rkh_rq_get_num( RKHRQ_T *q )
{
}


RKH_RQNE_T 
rkh_rq_get_lwm( RKHRQ_T *q )
{
}


HUInt 
rkh_rq_get( RKHRQ_T *q, void *pe )
{
}


void 
rkh_rq_put_fifo( RKHRQ_T *q, const void *pe )
{
}


void 
rkh_rq_put_lifo( RKHRQ_T *q, const void *pe )
{
}


void 
queue_deplete( RKHRQ_T *q )
{
}


HUInt 
rkh_rq_read( RKHRQ_T *q, void *pe )
{
}


void 
rkh_rq_get_info( RKHRQ_T *q, RKH_RQI_T *pqi )
{
}


void 
rkh_rq_clear_info( RKHRQ_T *q )
{
}
