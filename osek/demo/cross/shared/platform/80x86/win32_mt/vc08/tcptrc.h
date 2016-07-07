/**
 *  \file       tcptrc.h
 *  \ingroup    bsp
 *
 *  \brief      Socket TCP/IP support for 80x86 OS Win32
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
/*
 *  (1) To use the windows socket must be added the "ws2_32.lib"
 *      library in Linker->Input->Additional Dependencies
 *      configuration.
 */

#ifndef __TCPTRC_H__
#define __TCPTRC_H__

/* ----------------------------- Include files ----------------------------- */
#include <winsock.h>

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
int tcp_trace_open(unsigned short port, char *srvip, SOCKET *ps);
void tcp_trace_send(SOCKET s, const char *buf, int len);
void tcp_trace_close(SOCKET s);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
