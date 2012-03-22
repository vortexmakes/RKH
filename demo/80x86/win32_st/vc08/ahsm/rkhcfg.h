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
#define RKH_MAX_EPOOL					4	/* 	CFG01 */ 
#define RKH_LOWEST_PRIO					8	/* 	CFG01 */ 
#define RKH_EN_REENTRANT				0	/* 	CFG01 */
#define RKH_EN_DEFERRED_EVENT			0	/* 	CFG01 */
#define RKH_SIZEOF_EVENT				8	/* 	CFG01 */ 
#define RKH_EN_DYNAMIC_EVENT			1	/* 	CFG01 */ 
#define RKH_ASSERT_EN					1	/* 	CFG01 */
#define RKH_SIZEOF_ESIZE				16	/* 	CFG01 */
#define RKH_HK_EN_DISPATCH				1	/* 	CFG01 */
#define RKH_HK_EN_SIGNAL				1	/* 	CFG01 */
#define RKH_HK_EN_TIMEOUT				1	/* 	CFG01 */
#define RKH_HK_EN_START					1	/* 	CFG01 */
#define RKH_HK_EN_EXIT					1	/* 	CFG01 */

#define RKH_EN_NATIVE_SCHEDULER			0	/* 	CFG01 */ 
#define RKH_EN_NATIVE_EQUEUE			1	/* 	CFG01 */ 

#define RKH_SMA_EN_HCAL					1	/* 	CFG00 */
#define RKH_SMA_MAX_HCAL_DEPTH			4	/* 	CFG01 */
#define RKH_SMA_MAX_TRC_SEGS			4	/* 	CFG01 */
#define RKH_SMA_EN_PSEUDOSTATE			1	/* 	CFG01 */
#define RKH_SMA_EN_DEEP_HISTORY			1	/* 	CFG01 */
#define RKH_SMA_EN_SHALLOW_HISTORY		1	/* 	CFG01 */
#define RKH_SMA_EN_JUNCTION				1	/* 	CFG01 */
#define RKH_SMA_EN_CONDITIONAL			1	/* 	CFG01 */
#define RKH_SMA_EN_INIT_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_INIT_ARG_IE			0	/* 	CFG01 */
#define RKH_SMA_EN_ENT_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_EXT_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_ACT_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_ACT_ARG_EVT			1	/* 	CFG01 */
#define RKH_SMA_EN_GRD_ARG_EVT			1	/* 	CFG01 */
#define RKH_SMA_EN_GRD_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_PPRO_ARG_SMA			1	/* 	CFG01 */
#define RKH_SMA_EN_STATE_ID				1	/* 	CFG01 */
#define RKH_SMA_EN_PPRO					0	/* 	CFG01 */
#define RKH_SMA_EN_ID					1	/* 	CFG01 */
#define RKH_SMA_EN_IEVENT				1	/* 	CFG01 */
#define RKH_SMA_EN_GET_INFO				0	/* 	CFG01 */

#define RKH_TRC_EN						1	/* 	CFG01 */
#define RKH_TRC_MAX_EVENTS				16	/* 	CFG01 */
#define RKH_TRC_RUNTIME_FILTER			1	/* 	CFG01 */
#define RKH_TRC_ALL						1	/* 	CFG01 */
#define RKH_TRC_EN_MP					0	/* 	CFG01 */
#define RKH_TRC_EN_RQ					0	/* 	CFG01 */
#define RKH_TRC_EN_SMA					0	/* 	CFG01 */
#define RKH_TRC_EN_TIM					0	/* 	CFG01 */
#define RKH_TRC_EN_SM					0	/* 	CFG01 */
#define RKH_TRC_EN_RKH					0	/* 	CFG01 */
#define RKH_TRC_EN_SM_INIT				1	/* 	CFG01 */
#define RKH_TRC_EN_SM_DCH				1	/* 	CFG01 */
#define RKH_TRC_EN_SM_CLRH				1	/* 	CFG01 */
#define RKH_TRC_EN_SM_TRN				1	/* 	CFG01 */
#define RKH_TRC_EN_SM_STATE				1	/* 	CFG01 */
#define RKH_TRC_EN_SM_ENSTATE			1	/* 	CFG01 */
#define RKH_TRC_EN_SM_EXSTATE			1	/* 	CFG01 */
#define RKH_TRC_EN_SM_NENEX				1	/* 	CFG01 */
#define RKH_TRC_EN_SM_NTRNACT			1	/* 	CFG01 */
#define RKH_TRC_EN_SM_CSTATE			1	/* 	CFG01 */
#define RKH_TRC_EN_SM_DCH_RC			1	/* 	CFG01 */
#define RKH_TRC_EN_TSTAMP				1	/* 	CFG01 */
#define RKH_TRC_SIZEOF_TSTAMP			32	/* 	CFG01 */
#define RKH_TRC_MAX_TRACES				16	/* 	CFG01 */
#define RKH_TRC_SIZEOF_EVENT			17	/* 	CFG01 */
#define RKH_TRC_SIZEOF_POINTER			32	/* 	CFG01 */

#define RKH_RQ_EN						1	/* 	CFG01 */ 
#define RKH_RQ_SIZEOF_NELEM				8	/* 	CFG01 */ 
#define RKH_RQ_EN_GET_LWMARK			1	/* 	CFG01 */ 
#define RKH_RQ_EN_GET_INFO				0	/* 	CFG01 */ 
#define	RKH_RQ_EN_READ					1	/* 	CFG01 */ 
#define	RKH_RQ_EN_DEPLETE				1	/* 	CFG01 */ 
#define	RKH_RQ_EN_IS_FULL				1	/* 	CFG01 */ 
#define	RKH_RQ_EN_GET_NELEMS			1	/* 	CFG01 */ 
#define	RKH_RQ_EN_PUT_LIFO				1	/* 	CFG01 */ 

#define RKH_MP_EN						1	/* 	CFG01 */ 
#define RKH_MP_MAX						8	/* 	CFG01 */ 
#define RKH_MP_REDUCED					0	/* 	CFG01 */ 
#define RKH_MP_SIZEOF_BSIZE				8	/* 	CFG01 */ 
#define RKH_MP_SIZEOF_NBLOCK			8	/* 	CFG01 */ 
#define RKH_MP_EN_GET_BSIZE				1	/* 	CFG01 */ 
#define RKH_MP_EN_GET_NFREE				1	/* 	CFG01 */ 
#define RKH_MP_EN_GET_LWM				1	/* 	CFG01 */ 
#define RKH_MP_EN_GET_INFO				0	/* 	CFG01 */ 

#define RKH_TIM_EN						1	/* 	CFG01 */
#define RKH_TIM_EN_HOOK					1	/* 	CFG01 */
#define RKH_TIM_EN_GET_INFO				0	/* 	CFG01 */
#define RKH_TIM_EN_RESTART				1	/* 	CFG01 */
#define RKH_TIM_SIZEOF_NTIMER			16	/* 	CFG01 */


#endif
