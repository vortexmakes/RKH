/*
 *	file: rkhcfg.h
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

/*
 * 	\file rkhcfg.h
 *
 *	\brief
 * 	RKH user configuration.
 */


#ifndef __RKHCFG_H__
#define __RKHCFG_H__


#define RKH_MAX_SMA						8	/* 	CFG01 */ 
#define RKH_LOWEST_PRIO					8	/* 	CFG01 */ 
#define RKH_CRITICAL_METHOD				3	/* 	CFG01 */ 
#define RKH_EN_REENTRANT				0	/* 	CFG01 */
#define RKH_EN_DEFERRED_EVENT			0	/* 	CFG01 */
#define RKH_SIZEOF_EVENT				4	/* 	CFG01 */ 
#define RKH_EN_DYNAMIC_EVENT			1	/* 	CFG01 */ 
#define RKH_ASSERT_EN					1	/* 	CFG01 */

#define RKH_EN_NATIVE_SCHEDULER			1	/* 	CFG01 */ 
#define RKH_EN_NATIVE_POSTFIFO			1	/* 	CFG01 */ 
#define RKH_EN_NATIVE_POSTLIFO			1	/* 	CFG01 */ 
#define RKH_EN_NATIVE_GET				1	/* 	CFG01 */ 

#define RKH_SMA_MAX_HCAL_DEPTH			4	/* 	CFG01 */
#define RKH_SMA_MAX_TR_SEGS				4	/* 	CFG01 */
#define RKH_SMA_EN_HCAL					1	/* 	CFG00 */
#define RKH_SMA_EN_PSEUDOSTATE			1	/* 	CFG01 */
#define RKH_SMA_EN_DEEP_HISTORY			1	/* 	CFG01 */
#define RKH_SMA_EN_SHALLOW_HISTORY		1	/* 	CFG01 */
#define RKH_SMA_EN_JUNCTION				1	/* 	CFG01 */
#define RKH_SMA_EN_CONDITIONAL			1	/* 	CFG01 */
#define RKH_SMA_EN_INIT_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_ENT_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_EXT_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_ACT_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_ACT_ARG_EVT			1	/* 	CFG01 */
#define RKH_SMA_EN_GRD_ARG_EVT			1	/* 	CFG01 */
#define RKH_SMA_EN_GRD_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_PPRO_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_STATE_NAME			1	/* 	CFG01 */
#define RKH_SMA_EN_STATE_ID				1	/* 	CFG01 */
#define RKH_SMA_EN_PPRO					0	/* 	CFG01 */
#define RKH_SMA_EN_NAME					1	/* 	CFG01 */
#define RKH_SMA_EN_IEVENT				1	/* 	CFG01 */
#define RKH_SMA_EN_GET_INFO				0	/* 	CFG01 */

#define RKH_TR_EN						1	/* 	CFG01 */
#define RKH_TR_ALL						0	/* 	CFG01 */
#define RKH_TR_EN_EVENT					1	/* 	CFG01 */
#define RKH_TR_EN_TRN_SRC				0	/* 	CFG01 */
#define RKH_TR_EN_TRN_TGT				0	/* 	CFG01 */
#define RKH_TR_EN_NXT_STATE				1	/* 	CFG01 */
#define RKH_TR_EN_INT_TRAN				0	/* 	CFG01 */
#define RKH_TR_EN_ENTRY					1	/* 	CFG01 */
#define RKH_TR_EN_EXIT					1	/* 	CFG01 */
#define RKH_TR_EN_INIT_HSM				0	/* 	CFG01 */
#define RKH_TR_EN_SGT					0	/* 	CFG01 */
#define RKH_TR_EN_RTN_CODE				0	/* 	CFG01 */
#define RKH_TR_EN_NUM_ENEX				0	/* 	CFG01 */
#define RKH_TR_EN_NUM_ACTSGT			0	/* 	CFG01 */
#define RKH_TR_EN_TIMESTAMP				1	/* 	CFG01 */
#define RKH_TR_SIZEOF_TIMESTAMP			16	/* 	CFG01 */
#define RKH_TR_MAX_NUM_TRACES			16	/* 	CFG01 */
#define RKH_TR_EN_TRACE_STRING			1	/* 	CFG01 */
#define RKH_TR_MAX_TRACE_STRING_SIZE	4	/* 	CFG01 */

#define RKH_RQ_EN						1	/* 	CFG01 */ 
#define RKH_RQ_SIZEOF_NELEM				8	/* 	CFG01 */ 
#define RKH_RQ_EN_GET_LWMARK			1	/* 	CFG01 */ 
#define RKH_RQ_EN_GET_INFO				1	/* 	CFG01 */ 
#define	RKH_RQ_EN_READ					1	/* 	CFG01 */ 
#define	RKH_RQ_EN_DEPLETE				1	/* 	CFG01 */ 

#define RKH_MP_EN						1	/* 	CFG01 */ 
#define RKH_MP_MAX						8	/* 	CFG01 */ 
#define RKH_MP_REDUCED					1	/* 	CFG01 */ 
#define RKH_MP_SIZEOF_BSIZE				4	/* 	CFG01 */ 
#define RKH_MP_SIZEOF_NBLOCK			4	/* 	CFG01 */ 
#define RKH_MP_EN_GET_BSIZE				1	/* 	CFG01 */ 
#define RKH_MP_EN_GET_NFREE				1	/* 	CFG01 */ 
#define RKH_MP_EN_GET_LWM				1	/* 	CFG01 */ 
#define RKH_MP_EN_GET_INFO				1	/* 	CFG01 */ 

#define RKH_TIMER_EN					1	/* 	CFG01 */
#define RKH_TIMER_SIZEOF_NTIMER			1	/* 	CFG01 */
#define RKH_TIMER_EN_HOOK				1	/* 	CFG01 */
#define RKH_TIMER_EN_GET_INFO			1	/* 	CFG01 */
#define RKH_TIMER_EN_RESTART			1	/* 	CFG01 */


#endif
