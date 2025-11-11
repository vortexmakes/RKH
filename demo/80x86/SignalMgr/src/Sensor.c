/**
 *  \file   Sensor.c
 *  \brief  Sensor implementation.
 */

/* -------------------------- Development history -------------------------- */
/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "Sensor.h"
#include <stdlib.h>
#include <time.h>

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static double
randomRange(double min, double max)
{
    return min + (double)rand() / RAND_MAX * (max - min);
}

/* ---------------------------- Global functions --------------------------- */

void
Sensor_init(void)
{
    srand(time(NULL));
}

double
Sensor_get(void)
{
    return randomRange(0.9, 5);
}

double
Sensor_process(double value)
{
    return value / randomRange(1, 3);
}
