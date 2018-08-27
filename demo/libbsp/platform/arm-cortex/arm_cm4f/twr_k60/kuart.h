/*
 * File:		kuart.h
 * Purpose:     Provide common Kinets UART routines
 *
 * Notes:
 */

#ifndef __KUART_H__
#define __KUART_H__


#include "derivative.h"
#include "arm_cm4.h"


typedef void(*KUARTRX_CB)(uint8_t d);


typedef enum
{
	KUART_HFC_DISABLE,
	KUART_HFC_ENABLE
}KUART_HFC_T;


typedef struct
{
	unsigned baud;
	uint8 tx_ffsz;		/* tx fifo size */
	uint8 rx_ffsz;		/* rx fifo size */
	KUART_HFC_T fce;	/* flow control enable */
	KUARTRX_CB rxcb;		/* rx callback function */
} KUARTPP_ST;


void kuart_init( UART_MemMapPtr channel, const KUARTPP_ST* pu );
char kuart_getchar( UART_MemMapPtr channel );
void kuart_putchar( UART_MemMapPtr channel, char ch );
void kuart_putnchar( UART_MemMapPtr channel, char *p, uint16 n );
void kuart_putstr( UART_MemMapPtr channel, char *str );
int kuart_getchar_present( UART_MemMapPtr channel );
void kuart_hflwctrl( UART_MemMapPtr channel, KUART_HFC_T ctrl );

void	kuart0_isr( void ),
		kuart1_isr( void ),
		kuart2_isr( void ),
		kuart3_isr( void ),
		kuart4_isr( void ),
		kuart5_isr( void );

#endif /* __UART_H__ */
