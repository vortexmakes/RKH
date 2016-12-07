/**
 *  \file       tcptrc.h
 *  \brief      Socket TCP/IP support for 80x86 OS win32
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Darío Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/*
 *  \note 
 *  To use the windows socket must be added the "ws2_32.lib" library in 
 *  Linker->Input->Additional Dependencies configuration.
 */

/* --------------------------------- Module -------------------------------- */
#ifndef __TCPTRC_H__
#define __TCPTRC_H__


/* ----------------------------- Include files ----------------------------- */
/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
int tcp_trace_open( unsigned short port, char *srvip, int *ps );
void tcp_trace_send( int s, char c );
void tcp_trace_close( int s );

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
