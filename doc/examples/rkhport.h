/* --------------------------------- Module -------------------------------- */
#ifndef __RKHPORT_H__
#define __RKHPORT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtype.h"
#include "rkhqueue.h"
#include "rkhmempool.h"
#include "rkhsma_prio.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#define RKH_DIS_INTERRUPT()				    __asm volatile ("cpsid i")
#define RKH_ENA_INTERRUPT()				    __asm volatile ("cpsie i")
#define RKH_ENTER_CRITICAL( dummy )		    rkhport_enter_critical()
#define RKH_EXIT_CRITICAL( dummy )		    rkhport_exit_critical()

/* ------------------------------- Constants ------------------------------- */
#define KERNEL_IRQ_PRIO		                6
#define HIGHEST_IRQ_PRI		                5

#define RKH_CFGPORT_SMA_THREAD_EN 			RKH_DISABLED
#define RKH_CFGPORT_SMA_THREAD_DATA_EN		RKH_DISABLED
#define RKH_CFGPORT_NATIVE_SCHEDULER_EN		RKH_ENABLED
#define RKH_CFGPORT_NATIVE_EQUEUE_EN		RKH_ENABLED
#define RKH_CFGPORT_NATIVE_DYN_EVT_EN		RKH_ENABLED
#define RKH_CFGPORT_REENTRANT_EN			RKH_DISABLED
#define RKH_CFGPORT_TRC_SIZEOF_PTR			32u
#define RKH_CFGPORT_TRC_SIZEOF_FUN_PTR		32u
#define RKH_CFGPORT_TRC_SIZEOF_TSTAMP		32u
#define RKH_CFGPORT_SMA_QSTO_EN				RKH_ENABLED
#define RKH_CFGPORT_SMA_STK_EN				RKH_DISABLED
#define RKHROM								const
#define RKH_EQ_TYPE              		    RKH_QUEUE_T

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
const char *rkhport_get_version(void);
const char *rkhport_get_desc(void);
void rkhport_enter_critical(void);
void rkhport_exit_critical(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif
/* ------------------------------ End of file ------------------------------ */
