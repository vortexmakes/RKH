/*
 * telybrd.h
 * board.h BSP extension for tely project
 */

#ifndef __TELYBRD_H__
#define __TELYBRD_H__

#include "rkh.h"

/* The UART to use for RKH trace . */

#include "fsl_uart_driver.h"

#ifndef TELYBRD_TRACE_UART_INSTANCE
    #define TELYBRD_RKHTRC_UART_INSTANCE	0
    #define TELYBRD_RKHTRC_UART_BASEADDR	UART0
#endif
#ifndef TELYBRD_RKHTRC_UART_BAUD
    #define TELYBRD_RKHTRC_UART_BAUD		115200
#endif


void rkhtrc_uart_init( void );
void rkhtrc_uart_deinit( void );
void rkhtrc_send_block( rui8_t *buf, TRCQTY_T len );


/* LPTMR config for RKH trace time stamp */

#include "fsl_lptmr_driver.h"

#define TSTAMP_LPTMR_INSTANCE     0U

void rkhtrc_lptmr_init(void );
uint32_t rkhtrc_lptmr_read( void );

#endif

