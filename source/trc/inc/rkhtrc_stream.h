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
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhtrc_stream.h
 *  \brief      Specifies the trace stream manager (circular buffer).
 *  \ingroup    apiTrc
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.15  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHTRC_STREAM_H__
#define __RKHTRC_STREAM_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtrc_out.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Initializes the RKH's trace stream.
 *
 *  \note
 *  rkh_trcStream_init() is NOT protected with a critical section.
 */
void rkh_trcStream_init(void);

/**
 *  \brief
 *	Retrieves a pointer to oldest stored byte in the trace stream.
 *	Frequently, this function is used by the called trace analyzer.
 *
 *  \note
 *  The data is stored in a single ring buffer, called trace stream. In this
 *	manner the recorder always holds the most recent history.
 *  rkh_trc_get() is NOT protected with a critical section.
 *
 *  \returns
 *  A pointer to the oldest stored byte if trace stream was not empty,
 *  otherwise NULL pointer.
 */
rui8_t *rkh_trc_get(void);

/**
 *  \brief
 *  Retrieves a pointer to a contiguous block of data from the trace stream.
 *
 *  The function returns the pointer to the beginning of the block, and writes
 *  the number of bytes in the block to the location pointed to by \a nget.
 *  The argument \a nget is also used as input to provide the maximum size
 *  of the data block that the caller can accept.
 *	Frequently, this function is used by the called trace analyzer.
 *
 *  \param[in] nget	when this function is invoked \a nget is used as an input
 *                  to provide the maximum size of the data block to be
 *                  retrieved. Also, it is used as an output retrieving the
 *                  size of block.
 *
 *  \returns
 *  The pointer to the beginning of the block, and writes the number of bytes
 *  in the block to the location pointed to by \a nget. If this number
 *  differs from the \a nget parameter, the end-of-stream was reached. If
 *  the trace stream is empty, the function returns NULL and the content
 *  pointed by \a nget is set to zero.
 *
 *  \note
 *  The data is stored in a single ring buffer, called trace stream. In this
 *	manner the recorder always holds the most recent history.
 *  rkh_trc_get_block() is NOT protected with a critical section.
 */
rui8_t *rkh_trc_get_block(TRCQTY_T *nget);

/**
 *  \brief
 *  Put a data byte into the trace stream.
 *
 *  \param[in] b	data to be written in the trace stream.
 *
 *  \note
 *  The data is stored in a single ring buffer, called trace stream. In this
 *	manner the recorder always holds the most recent history.
 *  rkh_trc_put() is NOT protected with a critical section.
 */
void rkh_trc_put(rui8_t b);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
