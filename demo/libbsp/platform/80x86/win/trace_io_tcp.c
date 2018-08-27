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
 *  \file       trace_io_tcp.c
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
#include <stdio.h>
#include "trace_io_tcp.h"
#include "rkh.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
int
trace_io_tcp_open(unsigned short port, char *srv_ip, SOCKET *ps)
{
    WORD wVersionRequested;
    WSADATA wsaData;
    SOCKADDR_IN target; /* Socket address information */
    SOCKET s;
    int err;

    /* --- INITIALIZATION ----------------------------------- */
    wVersionRequested = MAKEWORD(1, 1);
    err = WSAStartup(wVersionRequested, &wsaData);
    *ps = INVALID_SOCKET;

    if (err != 0)
    {
        printf("WSAStartup error %ld", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    /* ------------------------------------------------------ */

    /* ---- build address structure to bind to socket.-------- */
    target.sin_family = AF_INET; /* address family Internet */
    target.sin_port = htons(port);   /* Port to connect on */
    target.sin_addr.s_addr = inet_addr (srv_ip); /* Server IP */
    /* ------------------------------------------------------ */

    /* ---- create SOCKET-------------------------------------- */
    s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        printf("socket error %ld", WSAGetLastError());
        WSACleanup();
        return -1; /* Couldn't create the socket */
    }
    /* ------------------------------------------------------ */

    /* ---- try CONNECT ----------------------------------------- */
    if (connect(s, (SOCKADDR*)&target, sizeof(target)) == SOCKET_ERROR)
    {
        printf("connect error %ld", WSAGetLastError());
        WSACleanup();
        return -1; /* Couldn't connect */
    }
    *ps = s;
    return 0;
}

void
trace_io_tcp_send(SOCKET s, const char *buf, int len)
{
    send(s, buf, len, 0);
}

int
trace_io_tcp_recv(SOCKET s, char *buf, int len)
{
    return recv(s, buf, len, 0);
}

void
trace_io_tcp_close(SOCKET s)
{
    closesocket(s);
    WSACleanup();
}

/* ------------------------------ File footer ------------------------------ */

/* ------------------------------ End of file ------------------------------ */
