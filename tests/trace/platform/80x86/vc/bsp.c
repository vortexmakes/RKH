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
 *  \file       bsp.c
 *  \ingroup    Test
 *
 *  \brief      BSP for 80x86 OS win32
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.11.19  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#if RKH_CFG_TRC_EN == RKH_ENABLED
#include <time.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>        /* Win32 API for multithreading */
#endif

#include "bsp.h"
#include "rkh.h"

/* ----------------------------- Local macros ------------------------------ */

#define kbmap(c)            ((c) - '0')

/* ------------------------------- Constants ------------------------------- */

#define BIN_TRACE           0
#define SOCKET_TRACE        1
#define ESC                 0x1B

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */

RKH_THIS_MODULE

#if defined(RKH_USE_TRC_SENDER)
static rui8_t l_isr_kbd;
#endif

#if RKH_CFG_TRC_EN == RKH_ENABLED
static rbool_t running;
static HANDLE idle_thread;
#endif

/*
 *  For binary trace feature.
 */
#if BIN_TRACE == 1
static FILE *ftbin;
#endif

/*
 *  For socket trace feature.
 */
#if SOCKET_TRACE == 1
    #include "tcptrc.h"

    /* Trazer Tool IP Address */
    #define TRC_IP_ADDR                 "127.0.0.1"

    /* Trazer Tool TCP Port Address */
    #define TRC_TCP_PORT                6602

    /* Trace Socket */
    static SOCKET tsock;

    #define TCP_TRACE_OPEN() \
        if (tcp_trace_open(TRC_TCP_PORT, \
                           TRC_IP_ADDR, &tsock) < 0) \
        { \
            printf("Can't open socket %s:%u\n", \
                   TRC_IP_ADDR, TRC_TCP_PORT); \
            exit(EXIT_FAILURE); \
        }
    #define TCP_TRACE_CLOSE() \
        tcp_trace_close(tsock)
    #define TCP_TRACE_SEND(d) \
        tcp_trace_send(tsock, d, (int)1)
    #define TCP_TRACE_SEND_BLOCK(buf_, len_) \
        tcp_trace_send(tsock, (const char *)(buf_), (int)(len_))
#else
    #define TCP_TRACE_OPEN()                    (void)0
    #define TCP_TRACE_CLOSE()                   (void)0
    #define TCP_TRACE_SEND(d)                   (void)0
    #define TCP_TRACE_SEND_BLOCK(buf_, len_)    (void)0
#endif

#if BIN_TRACE == 1
    #define FTBIN_FLUSH(buf_, len_) \
        fwrite((buf_), 1, (len_), ftbin); \
        fflush(ftbin)
    #define FTBIN_CLOSE() \
        fclose(ftbin)
    #define FTBIN_OPEN() \
        if ((ftbin = fopen("../ftbin", "w+b")) == NULL) \
        { \
            perror("Can't open file\n"); \
            exit(EXIT_FAILURE); \
        }
#else
    #define FTBIN_FLUSH(buf_, len_)             (void)0
    #define FTBIN_CLOSE()                       (void)0
    #define FTBIN_OPEN()                        (void)0
#endif

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */

#if RKH_CFG_TRC_EN == RKH_ENABLED
static
DWORD WINAPI
idle_thread_function(LPVOID par)
{
    (void)par;

    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);
    running = (rui8_t)1;

    while (running)
    {
        RKH_TRC_FLUSH();
        Sleep(10);      /* wait for a while */
    }
    return 0;           /* return success */
}
#endif

/* ---------------------------- Global functions --------------------------- */

void
rkh_hook_timetick(void)
{
    if (_kbhit())
    {
        int c = _getch();

        if (c == ESC)
        {
            RKH_SMA_POST_FIFO(svr, &e_term, &l_isr_kbd);
        }
        else if (tolower(c) == 'p')
        {
            bsp_publish(&e_pause);
        }
    }
}

void
rkh_hook_start(void)
{
    rkh_set_tickrate(BSP_TICKS_PER_SEC);

    /*
     *  For avoiding to have multiple threads (idle and main) sending data on
     *  the same socket, i.e. using the send() function, the idle thread is
     *  created to be run only after the initial process has finished.
     *  Without this trick, the streams are interleaving and the trace stream
     *  is corrupted.
     */
    ResumeThread(idle_thread);
}

void
rkh_hook_exit(void)
{
    RKH_TRC_FLUSH();
#if RKH_CFG_TRC_EN == RKH_ENABLED
    running = (rui8_t)0;
#endif
}

void
rkh_assert(RKHROM char * const file, int line)
{
    fprintf(stderr,    "RKH_ASSERT: [%d] line from %s "
            "file\n", line, file);
    RKH_TRC_FLUSH();
    RKH_DIS_INTERRUPT();
    RKH_TR_FWK_ASSERT((RKHROM char *)file, __LINE__);
    __debugbreak();
    rkh_fwk_exit();
}

#if RKH_CFG_TRC_EN == RKH_ENABLED
void
rkh_trc_open(void)
{
    rkh_trc_init();

    FTBIN_OPEN();
    TCP_TRACE_OPEN();
    RKH_TRC_SEND_CFG(BSP_TS_RATE_HZ);

    if ((idle_thread =
             CreateThread(NULL, 1024, &idle_thread_function, (void *)0,
                          CREATE_SUSPENDED, NULL)) == (HANDLE)0)
    {
        fprintf(stderr, "Cannot create the idle thread: [%d] line from %s "
                "file\n", __LINE__, __FILE__);
    }
}

void
rkh_trc_close(void)
{
    FTBIN_CLOSE();
    TCP_TRACE_CLOSE();
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
        nbytes = (TRCQTY_T)1024;

        RKH_ENTER_CRITICAL_();
        blk = rkh_trc_get_block(&nbytes);
        RKH_EXIT_CRITICAL_();

        if ((blk != (rui8_t *)0))
        {
            FTBIN_FLUSH(blk, nbytes);
            TCP_TRACE_SEND_BLOCK(blk, nbytes);
        }
        else
        {
            break;
        }
    }
}
#endif

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    rkh_fwk_init();
    RKH_TRC_OPEN();
}

/* ------------------------------ End of file ------------------------------ */
