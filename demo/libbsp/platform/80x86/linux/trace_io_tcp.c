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
 *  \brief      Socket TCP/IP support for 80x86 OS Linux
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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

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
trace_io_tcp_open(unsigned short port, char *srv_ip, int *ps)
{
    int s;
    struct sockaddr_in serv_addr;

    /* --- INITIALIZATION ----------------------------------- */
    *ps = 0;

    /* ------------------------------------------------------ */

    /* ---- create SOCKET-------------------------------------- */
    s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); /* Create socket */
    if (s < 0)
    {
        printf("socket opening error\n");
        return -1; /* Couldn't create the socket */
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr.s_addr = inet_addr(srv_ip);  /* Normal Address */

    serv_addr.sin_port = htons(port);
    /* ------------------------------------------------------ */

    /* ---- try CONNECT ----------------------------------------- */
    if (connect(s,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        printf("ERROR connecting \n");
        return -1;
    }

    *ps = s;
    return 0;
}

void
trace_io_tcp_send(int s, char c)
{
    write(s, &c, 1);
}

void
trace_io_tcp_close(int s)
{
    close(s);
}

/* ------------------------------ File footer ------------------------------ */

/* ------------------------------ End of file ------------------------------ */
