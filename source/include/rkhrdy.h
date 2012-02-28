/*
 *	file: rkhrdy.h
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
 * 	\file rkhrdy.h
 *
 * 	\brief
 * 	Native priority management.
 *
 * 	Each SMA is assigned a unique priority level between 0 and 
 * 	RKH_LOWEST_PRIO. Each SMA that is ready to run is placed in a ready list 
 * 	consisting of two variables, rkh_rdygrp and rkh_rdytbl[]. SMA priorities 
 * 	are grouped (8 SMA per group) in rkh_rdygrp. Each bit in rkh_rdygrp is 
 * 	used to indicate whenever any SMA in a group is ready to run. When a task 
 * 	is ready to run it also sets its corresponding bit in the ready table, 
 * 	rkh_rdytbl[]. The size of rkh_rdytbl[] depends on RKH_LOWEST_PRIO 
 * 	(see rkhcfg.h). This allows to reduce the amount of RAM needed by RKH when 
 * 	your application requires few SMA priorities. 
 *
 * 	SMA's priority = | 0 | 0 | Y | Y | Y | X | X | X |
 *
 * 	Y's:	bit position in rkh_rdygrp and 
 * 			index into rkh_rdytbl[RKH_LOWEST_PRIO / 8 + 1]
 * 	X's:	bit position in rkh_rdytbl[RKH_LOWEST_PRIO / 8 + 1]
 *
 * 	The lower 3 bits (X's) of the SMA's priority are used to determine the 
 * 	bit position in rkh_rdytbl[], while the next three most significant bits 
 * 	(Y's) are used to determine the index into rkh_rdytbl[]. Note that 
 * 	rkh_maptbl[] is a table in ROM, used to equate an index from 0 to 7 to a 
 * 	bit mask.
 *
 * 	To determine which priority (and thus which SMA) will run next, the 
 * 	scheduler determines the lowest priority number that has its bit set in 
 * 	rkh_rdytbl[]. The relationship between rkh_rdygrp and rkh_rdytbl[] is 
 * 	given by the following rules:
 *
 * 	Bit 0 in rkh_rdygrp is 1 when any bit in rkh_rdytbl[0] is 1.
 * 	Bit 1 in rkh_rdygrp is 1 when any bit in rkh_rdytbl[1] is 1.
 * 	Bit 2 in rkh_rdygrp is 1 when any bit in rkh_rdytbl[2] is 1.
 * 	Bit 3 in rkh_rdygrp is 1 when any bit in rkh_rdytbl[3] is 1.
 * 	Bit 4 in rkh_rdygrp is 1 when any bit in rkh_rdytbl[4] is 1.
 * 	Bit 5 in rkh_rdygrp is 1 when any bit in rkh_rdytbl[5] is 1.
 * 	Bit 6 in rkh_rdygrp is 1 when any bit in rkh_rdytbl[6] is 1.
 * 	Bit 7 in rkh_rdygrp is 1 when any bit in rkh_rdytbl[7] is 1.
 * 	
 * 	[JL]
 */


#ifndef __RKHRDY_H__
#define __RKHRDY_H__

/*
static RKHROM rkh_maptbl[] = 
{
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};
*/


/**
 * 	\brief
 * 	Making a task ready-to-run.
 */

#define rkh_setrdy( prio )											\
				rkh_rdygrp |= rkh_maptbl[(prio) >> 3];				\
				rkh_rdytbl[(prio) >> 3] |= rkh_maptbl[(prio) & 0x07]

	/*
	OSRdyGrp |= OSMapTbl[prio >> 3];
	OSRdyTbl[prio >> 3] |= OSMapTbl[prio & 0x07];
	*/

/*
 * A task is removed from the ready list by reversing the process. The following code is executed in this case
if ((OSRdyTbl[prio >> 3] &= ~OSMapTbl[prio & 0x07]) == 0)
OSRdyGrp &= ~OSMapTbl[prio >> 3];
 * 
 */

/*
This code clears the ready bit of the task in OSRdyTbl[] and clears the bit in OSRdyGrp only if all tasks in a group
are not ready to run, i.e. all bits in OSRdyTbl[prio >> 3] are 0. Another table lookup is performed, rather than
scanning through the table starting with OSRdyTbl[0] to find the highest priority task ready to run.
OSUnMapTbl[256] is a priority resolution table (see OS_CORE.C). Eight bits are used to represent when tasks are
ready in a group. The least significant bit has the highest priority. Using this byte to index the table returns the bit
position of the highest priority bit set, a number between 0 and 7.
 * 
Determining the priority of the highest priority task
ready to run is accomplished with the following section of code:

y = OSUnMapTbl[OSRdyGrp];
x = OSUnMapTbl[OSRdyTbl[y]];
prio = (y << 3) + x;
 * 
 */


#endif
