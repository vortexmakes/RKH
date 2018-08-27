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
 *  \file       rkhtrc_out.h
 *  \brief      Specifies the interface to get out the trace records from the 
 *              instrumented application.
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
#ifndef __RKHTRC_OUT_H__
#define __RKHTRC_OUT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtrc_define.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *  \brief
 *	Open the tracing session.
 *
 *	This function is application-specific and the user needs to
 *	define it. At a minimum, this function must initialize and/or
 *	configure the trace stream by calling rkh_trc_init() and
 *	RKH_TRC_SEND_CFG() respectively.
 *
 *  \note
 *  This function is internal to RKH and the user application
 *  should not call it. Instead, use #RKH_TRC_OPEN() macro.
 *
 *  \sa \b rkhtrc.h file.
 *
 *	\usage
 *
 *	\code
 *	#define BSP_SIZEOF_TS		32u
 *	#define BSP_TS_RATE_HZ		CLOCK_PER_SEC
 *
 *	void
 *	rkh_trc_open( void )
 *	{
 *		rkh_trc_init();
 *
 *		FTBIN_OPEN();
 *		TCP_TRACE_OPEN();
 *		RKH_TRC_SEND_CFG( BSP_SIZEOF_TS, BSP_TS_RATE_HZ );
 *
 *		if(( idle_thread = CreateThread( NULL, 1024,
 *				&idle_thread_function, (void *)0,
 *				CREATE_SUSPENDED, NULL )) == (HANDLE)0 )
 *			fprintf( stderr, "Cannot create the thread: [%d]
 *													line from %s "
 *				"file\n", __LINE__, __FILE__ );
 *	}
 *	\endcode
 *
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
    #define RKH_TRC_OPEN()      rkh_trc_open()
#else
    #define RKH_TRC_OPEN()      (void)0
#endif

/**
 *  \brief
 *	Close the tracing session.
 *
 *	This function is application-specific and the user needs to
 *	define it.
 *
 *  \note
 *  This function is internal to RKH and the user application
 *  should not call it. Instead, use #RKH_TRC_CLOSE() macro.
 *
 *  \sa \b rkhtrc.h file.
 *
 *	\usage
 *
 *	\code
 *	void
 *	rkh_trc_close( void )
 *	{
 *		fclose( fdbg );
 *	}
 *	\endcode
 *
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
    #define RKH_TRC_CLOSE()     rkh_trc_close()
#else
    #define RKH_TRC_CLOSE()     (void)0
#endif

/**
 *  \brief
 *	Platform-dependent macro flushing the trace stream.
 *
 *	This function is application-specific and the user needs to define
 *	it. When the RKH trace an event, all the information related to it
 *	has to be stored somewhere before it can be retrieved, in order to
 *	be analyzed.
 *  This place is a trace stream. Frequently, events traced are stored
 *  in the stream until it is flushed.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it. Instead, use #RKH_TRC_FLUSH() macro.
 *
 *  \sa \b rkhtrc.h file.
 *
 *	\usage
 *	\code
 *  void
 *  rkh_trc_flush( void )
 *  {
 *      rui8_t *blk;
 *      TRCQTY_T nbytes;
 *      RKH_SR_ALLOC();
 *
 *      FOREVER
 *      {
 *          nbytes = (TRCQTY_T)1024;
 *
 *          RKH_ENTER_CRITICAL_();
 *          blk = rkh_trc_get_block( &nbytes );
 *          RKH_EXIT_CRITICAL_();
 *
 *          if((blk != (rui8_t *)0))
 *          {
 *              FTBIN_FLUSH( blk, nbytes );
 *              TCP_TRACE_SEND_BLOCK( blk, nbytes );
 *          }
 *          else
 *              break;
 *      }
 *  }
 *	\endcode
 *
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
    #define RKH_TRC_FLUSH()     rkh_trc_flush()
#else
    #define RKH_TRC_FLUSH()     (void)0
#endif

/**
 *  \brief
 *  Send the trace facility configuration to host application software
 *  Trazer.
 *
 *  Trazer is designed to work with all possible target CPU, which
 *  requires a wide range of configurability. For example, for any
 *  given target CPU, Trazer must "know" the size of object pointers,
 *  event size, timestamp size and so on. This configurations could be
 *  provided through "trazer.cfg" file in the host or invoking
 *  RKH_TRC_SEND_CFG() macro from the application-specific
 *  rkh_trc_open() function.
 *
 *  \param[in] ts_hz		clocks per second of trace timestamp.
 *
 *  \note
 *	Frequently, this macro is called from the rkh_trc_open() function,
 *	which is provided by user application program, more specifically
 *	the board support package (BSP).
 *
 *  \sa RKH_TRC_OPEN() macro.
 *
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
    #define RKH_TRC_SEND_CFG(ts_hz) \
        RKH_TR_FWK_TCFG(ts_hz)
#else
    #define RKH_TRC_SEND_CFG(ts_hz)     (void)0
#endif

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Open the tracing session.
 *
 *	\ingroup apiBSPTrc
 */
void rkh_trc_open(void);

/**
 *  \brief
 *	Close the tracing session.
 *
 *	\ingroup apiBSPTrc
 */
void rkh_trc_close(void);

/**
 *  \brief
 *	Platform-dependent macro flushing the trace stream.
 *
 *	\ingroup apiBSPTrc
 */
void rkh_trc_flush(void);

/**
 *  \brief
 *	Retrieves a timestamp to be placed in a trace event.
 *
 *	This function is application-specific and the user needs to define it.
 *	The data returned is defined in compile-time by means of
 *	RKH_SIZEOF_TSTAMP.
 *
 *  \return     Timestamp (RKH_TS_T data type).
 *
 *  \sa \b rkhtrc.h file.
 *
 *  \usage
 *	\code
 *	RKH_TS_T
 *	rkh_trc_getts( void )
 *	{
 *		return ( RKH_TS_T )clock();
 *	}
 *	\endcode
 *
 *	\ingroup apiBSPTrc
 */
RKH_TS_T rkh_trc_getts(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
