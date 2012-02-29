/*
 *	file: rkhmp.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 27, 2012
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
 * 	\file rkhmp.c
 *
 * 	\brief
 * 	Implements a pool of fixed-size memory blocks.
 *
 * 	Since memory block pools consist of fixed-size blocks, there are 
 * 	never any fragmentation problems. Of course, fragmentation causes 
 * 	behavior that is inherently un-deterministic. In addition, the time
 * 	required to allocate and free a fixed-size memory is comparable to 
 * 	that of simple linked-list manipulation.
 * 	Lack of flexibility is the main drawback of fixed-size memory pools. 
 * 	The block size of a pool must be large enough to handle the worst 
 * 	case memory requirements of its users. Of course, memory may be wasted 
 * 	if many different size memory requests are made to the same pool. 
 * 	A possible solution is to make several different memory block pools 
 * 	that contain different sized memory blocks.
 */


#include "rkhmp.h"


void 
rkh_mp_init( RKHMP_T *mp, void *sstart, rkhui16_t ssize, 
												RKH_MPBS_T bsize )
{
}


void *
rkh_mp_get( RKHMP_T *mp )
{
}


void 
rkh_mp_put( RKHMP_T *mp, void *blk )
{
}


RKH_MPBS_T 
rkh_mp_get_blksize( RKHMP_T *mp )
{
}


RKH_MPNB_T 
rkh_mp_get_nfree( RKHMP_T *mp )
{
}


RKH_MPNB_T 
rkh_mp_get_low_wmark( RKHMP_T *mp )
{
}


void 
rkh_mp_get_info( RKHMP_T *mp, RKH_MPI_T *mpi )
{
}


void 
rkh_mp_clear_info( RKHMP_T *mp )
{
}
