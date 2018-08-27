/**
 *  \file       main.c
 *  \brief      Example application.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "blinky.h"
#include "bsp.h"


/* ----------------------------- Local macros ------------------------------ */
#define QSTO_SIZE           4

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_EVT_T *qsto[QSTO_SIZE];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
int
main(int argc, char *argv[])
{
    bsp_init(argc, argv);

    RKH_SMA_ACTIVATE(blinky, qsto, QSTO_SIZE, 0, 0);
    rkh_fwk_enter();

    RKH_TRC_CLOSE();
    return 0;
}

/* ------------------------------ End of file ------------------------------ */
