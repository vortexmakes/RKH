/**
 *  \file       client.h
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
#ifndef __CLIENT_H__
#define __CLIENT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "scevt.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#define CLI(clino_)     RKH_ARRAY_SMA(clis, clino_)
#define CLI0            CLI(0)
#define CLI1            CLI(1)
#define CLI2            CLI(2)
#define CLI3            CLI(3)
#define CLI_STK_SIZE    (512 / sizeof(RKH_THREAD_STK_TYPE))

/* -------------------------------- Constants ------------------------------ */
/* ================================ Signals ================================ */
/* ======================== Declares active object ========================= */
enum
{
    CLI_PRIO_0 = 1, CLI_PRIO_1, CLI_PRIO_2, CLI_PRIO_3,
    MAX_CLI_PRIO,
    NUM_CLIENTS = MAX_CLI_PRIO - 1,
};

RKH_ARRAY_SMA_DCLR(clis, NUM_CLIENTS);

/* =================== Declares states and pseudostates ==================== */
RKH_DCLR_BASIC_STATE client_idle, client_waiting, client_using, client_paused;

/* ------------------------------- Data types ------------------------------ */
typedef struct Client Client;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* ============================ Initial action ============================= */
void client_init(Client *const me);

/* ============================ Effect actions ============================= */
void client_req(Client *const me, RKH_EVT_T *pe);
void client_start(Client *const me, RKH_EVT_T *pe);
void client_end(Client *const me, RKH_EVT_T *pe);

/* ============================= Entry actions ============================= */
void client_delay_req(Client *const me);
void client_pause(Client *const me);

/* ============================= Exit actions ============================== */
void client_resume(Client *const me);

/* ================================ Guards ================================= */

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
