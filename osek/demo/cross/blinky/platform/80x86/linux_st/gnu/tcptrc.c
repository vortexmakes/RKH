/**
 *  \file       tcptrc.c
 *  \ingroup    bsp
 *
 *  \brief      Socket TCP/IP support for 80x86 OS linux
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "tcptrc.h"
#include "rkh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
#if RKH_CFG_TRC_EN == 1

int
tcp_trace_open(unsigned short port, char *srv_ip, int *ps)
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
tcp_trace_send(int s, const char *buf, int len)
{
    write(s, buf, len);
}

void
tcp_trace_close(int s)
{
    close(s);
}

#endif

/* ------------------------------ End of file ------------------------------ */

