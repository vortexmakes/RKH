/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhsma.h
 *  \brief      Platform - independent interface for supporting acive objects 
 *              (SMA state machine applications)
 *
 *  \ingroup    apiAO
 *
 *  \addtogroup api
 *  @{
 *  \addtogroup apiAO Active objects
 *  @{@}
 *  @}
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.05  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHSMA_H__
#define __RKHSMA_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhtype.h"
#include "rkhcfg.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
/**
 *  \brief
 *  Registers a state machine application (SMA) as known as active object into
 *  the framework, which implies to store a pointer to the SMA in the priority
 *  table.
 *
 *  \param[in] me  pointer to previously created state machine application.
 */
void rkh_sma_register(RKH_SMA_T *me);

/**
 *  \brief
 *	Removes the SMA as known as active object from the priority table, and
 *	thus from the framework, by simply replacing the link to the SMA being
 *	deleted with a NULL pointer.
 *
 *  \param[in] me  pointer to previously created state machine application.
 */
void rkh_sma_unregister(RKH_SMA_T *me);

/**
 *  \brief
 *  Initializes the virtual table of the active object instance and calls the 
 *  constructor operation of its base class.
 *
 *  \param[in] me   pointer to previously created state machine application.
 *  \param[in] vtbl pointer to virtual table. Define it as null to use the 
 *                  default virtual table, rkhSmaVtbl.
 *
 *  \note
 *  The initializer assumes that memory has previously been allocated for the 
 *  object (either statically or dynamically).
 */
void rkh_sma_ctor(RKH_SMA_T *me, const RKHSmaVtbl *vtbl);

/**
 *  \brief
 *  Initializes and activates a previously created state machine application
 *  (SMA) as known as active object.
 *
 *  A state machine application (SMA) is declared with the RKH_SMA_T data
 *  type and is defined with the rkh_sma_activate() service.
 *
 *  \param[in] me       pointer to previously created state machine
 *                      application.
 *  \param[in] qSto     base address of the event storage area. A message
 *                      storage area is declared as an array of pointers to
 *                      RKH events.
 *  \param[in] qSize    size of the storage event area [in number of entries].
 *  \param[in] stkSto   starting address of the stack's memory area.
 *  \param[in] stkSize  size of stack memory area [in bytes].
 *
 *	\note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Activates an active object
 *
 *  \ingroup apiPortAO
 */
void rkh_sma_activate(RKH_SMA_T *me, const RKH_EVT_T * *qSto,
                      RKH_RQNE_T qSize, void *stkSto, rui32_t stkSize);

/**
 *  \brief
 *  Terminate a state machine application (SMA) as known as active object.
 *
 *  A state machine application may call this service to terminate itself.
 *  Once terminated, the state machine application must be re-created in
 *  order for it to execute again.
 *
 *  \param[in] me      pointer to previously created state machine
 *                      application.
 *
 *	\note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Terminates an active object
 *
 *  \ingroup apiPortAO
 */
void rkh_sma_terminate(RKH_SMA_T *me);

/**
 *  \brief
 *  Clear performance information for a particular state machine application
 *  (SMA) as known as active object.
 *
 *  \param[in] me  pointer to previously created state machine application.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_SMA_GET_INFO_EN = 0.
 */
void rkh_sma_clear_info(RKH_SMA_T *me);

/**
 *  \brief
 *  Retrieves performance information for a particular state machine
 *  application (SMA) as known as active object.
 *
 *	The user application must allocate an RKH_SMAI_T data structure used to
 *	receive data. The performance information is available during run-time
 *	for each of the RKH services. This can be useful in determining whether
 *	the application is performing properly, as well as helping to optimize the
 *	application.
 *	This information provides a "snapshot" a particular instant in time, i.e.,
 *	when the service is invoked.
 *
 *  \param[in] me  pointer to previously created state machine application.
 *  \param[in] psi  pointer to the buffer into which the performance
 *                  information will be copied by reference.
 *
 *  \note
 *  See RKH_SMAI_T structure for more information. This function is optional, 
 *  thus it could be eliminated in compile-time with 
 *  RKH_CFG_SMA_GET_INFO_EN = 0.
 *
 */
void rkh_sma_get_info(RKH_SMA_T *me, RKH_SMAI_T *psi);

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
