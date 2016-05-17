/**
 *  \file       server.h
 *  \brief      Example application
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __SERVER_H__
#define __SERVER_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "client.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#define CLI_ID(cp_)     ((cp_) - RKH_GET_PRIO(CLI(0)))
#define SVR_STK_SIZE    (512 / sizeof(RKH_THREAD_STK_TYPE))

/* -------------------------------- Constants ------------------------------ */

/* ================================ Signals ================================ */
/* ======================== Declares active object ========================= */
RKH_SMA_DCLR(server);

/* =================== Declares states and pseudostates ==================== */
RKH_DCLR_BASIC_STATE server_idle, server_busy, server_paused;

/* ------------------------------- Data types ------------------------------ */
typedef struct Server Server;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */

/* ============================ Initial action ============================= */
void server_init(Server *const me);

/* ============================ Effect actions ============================= */
void server_start(Server *const me, RKH_EVT_T *pe);
void server_end(Server *const me, RKH_EVT_T *pe);
void server_defer(Server *const me, RKH_EVT_T *pe);
void server_terminate(Server *const me, RKH_EVT_T *pe);

/* ============================= Entry actions ============================= */
void server_pause(Server *const me);

/* ============================= Exit actions ============================== */
void server_resume(Server *const me);

/* ================================ Guards ================================= */

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
