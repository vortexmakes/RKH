/*
 * boardext.h
 * board.h BSP extension
 */

#ifndef __BOARDEXT_H__
#define __BOARDEXT_H__

#include "rkh.h"


/* The UART to use for RKH trace . */

#include "fsl_uart_driver.h"

#ifndef BRD_TRACE_UART_INSTANCE
    #define BRD_RKHTRC_UART_INSTANCE	0
    #define BRD_RKHTRC_UART_BASEADDR	UART0
#endif
#ifndef BRD_RKHTRC_UART_BAUD
    #define BRD_RKHTRC_UART_BAUD		115200
#endif


void rkhtrc_uart_init( void );
void rkhtrc_uart_deinit( void );
void rkhtrc_send_block( rui8_t *buf, TRCQTY_T len );


/* LPTMR config for RKH trace time stamp */

#include "fsl_lptmr_driver.h"

#define TSTAMP_LPTMR_INSTANCE     0U

void rkhtrc_lptmr_init(void );
uint32_t rkhtrc_lptmr_read( void );


/* RGB Led control */

typedef enum
{
	RGB_BLACK,
	RGB_WHITE,
	RGB_RED,
	RGB_LIME,
	RGB_BLUE,
	RGB_YELLOW,
	RGB_CYAN,
	RGB_MAGENTA
} RGB_COLOR_IDX;

void set_rgb_led( RGB_COLOR_IDX idx );


/* board low level initilization */

void board_init( void );

#endif

