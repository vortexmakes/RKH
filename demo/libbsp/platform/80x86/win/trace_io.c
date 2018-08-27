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
 *  \file       trace_io.c
 *  \brief      Socket TCP/IP support for 80x86 OS win32
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  DaBa  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */
/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

#if RKH_CFG_TRC_EN == 1
#include <stdio.h>
#include <time.h>
#include "getopt.h"
#include "trace_io_cfg.h"
#include "trace_io_tcp.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/*
 *  \brief
 *  This macro represents the number of timestamp clock ticks per second.
 *  Dividing a count of timestamp ticks by this macro yields the number
 *  of seconds.
 */
#define BSP_TS_RATE_HZ              CLOCKS_PER_SEC

#define TRACE_CFG_CONSOLE_OPTIONS   "t:f:p:h"

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static char *opts = (char *)TRACE_CFG_CONSOLE_OPTIONS;
static const char *helpMessage =
{
    "\nOption usage:\n"
    "\t -f File name for binary trace output\n"
    "\t -t ipaddr of TCP trace client\n"
    "\t -p port of TCP trace client\n"
    "\t -h (help)\n"
};

static TRACE_CFG_ST config =
{
    "", TCP_TRC_IP_ADDR_DFT, TCP_TRC_PORT_DFT
};

static FILE *ftbin = NULL;
static SOCKET tsock;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
trace_io_setConfig(int argc, char **argv)
{
    int c;

    while ((c = getopt(argc, argv, opts)) != EOF)
        switch (c)
        {
            case 'f':
                strncpy(config.ftbinName, optarg, FTBIN_NAME_STR_LEN);
                break;

            case 't':
                strncpy(config.tcpIpAddr, optarg, TCP_IPADDR_STR_LEN);
                break;

            case 'p':
                config.tcpPort= (short)atoi(optarg);
                break;

            case '?':
            case 'h':
                printf(helpMessage);
                break;
        }
}

void
rkh_trc_open(void)
{
    rkh_trc_init();

    if (strlen(config.ftbinName) != 0)
    {
        if ((ftbin = fopen(config.ftbinName, "w+b")) == NULL)
        {
            printf("Can't open trace file %s\n", config.ftbinName);
            exit(EXIT_FAILURE);
        }
    }

    if (trace_io_tcp_open(config.tcpPort, config.tcpIpAddr, &tsock) < 0)
    {
        printf("Can't open socket %s:%u\n",
               config.tcpIpAddr, config.tcpPort);
        exit(EXIT_FAILURE);
    }

    RKH_TRC_SEND_CFG(BSP_TS_RATE_HZ);
}

void
rkh_trc_close(void)
{
    if (ftbin != NULL)
    {
        fclose(ftbin);
    }

    trace_io_tcp_close(tsock);
}

RKH_TS_T
rkh_trc_getts(void)
{
    return (RKH_TS_T)clock();
}

void
rkh_trc_flush(void)
{
    rui8_t *blk;
    TRCQTY_T nbytes;
    RKH_SR_ALLOC();

    FOREVER
    {
        nbytes = 128;

        RKH_ENTER_CRITICAL_();
        blk = rkh_trc_get_block(&nbytes);
        RKH_EXIT_CRITICAL_();

        if ((blk != (rui8_t *)0))
        {
            if (ftbin != NULL)
            {
                fwrite(blk, 1, nbytes, ftbin);
            }

            trace_io_tcp_send(tsock, (char *)blk, nbytes);
        }
        else
        {
            break;
        }
    }
}
#endif

/* ------------------------------ File footer ------------------------------ */
