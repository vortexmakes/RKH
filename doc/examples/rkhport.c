/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "lpc17xx.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
RKH_MODULE_NAME(rkhport)
RKH_MODULE_VERSION(rkhport, 1.00)
RKH_MODULE_DESC(rkhport, "ARM Cortex-M, LPCXpresso")

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static ruint critical_nesting;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
const char *
rkhport_get_version(void)
{
    return RKH_MODULE_GET_VERSION();
}

const char *
rkhport_get_desc(void)
{
    return RKH_MODULE_GET_DESC();
}

void
rkhport_enter_critical(void)
{
    __asm volatile
    (
        "	mov r0, %0 \n"
        "	msr basepri, r0	\n"
        ::"i" (((HIGHEST_IRQ_PRI << (8 - __NVIC_PRIO_BITS)) & 0xFF)) : "r0"
    );

    critical_nesting++;
}

void
rkhport_exit_critical(void)
{
    critical_nesting--;

    if (critical_nesting != 0)
    {
        return;
    }

    __asm volatile
    (
        "	mov r0, #0 \n"
        "	msr basepri, r0 \n"
        ::: "r0"
    );
}

/* ------------------------------ File footer ------------------------------ */
