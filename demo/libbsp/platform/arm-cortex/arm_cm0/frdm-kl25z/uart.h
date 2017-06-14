/*
 * File:		uart.h
 * Purpose:     Provide common ColdFire uart routines for polled serial IO
 *
 * Notes:
 */

#ifndef __uart_H__
#define __uart_H__

#include "stdio.h"
/********************************************************************/


void uart_init (UART_MemMapPtr uartch, int sysclk, int baud);
char uart_getchar (UART_MemMapPtr channel);
void uart_putchar (UART_MemMapPtr channel, char ch);
void uart_putnchar (UART_MemMapPtr channel, char *p, uint16 n );
int uart_getchar_present (UART_MemMapPtr channel);
void uart0_init (UART0_MemMapPtr uartch, int sysclk, int baud);
char uart0_getchar (UART0_MemMapPtr channel);
void uart0_putchar (UART0_MemMapPtr channel, char ch);
void uart0_putnchar (UART0_MemMapPtr channel, char *p, uint16 n );
int uart0_getchar_present (UART0_MemMapPtr channel);

/********************************************************************/

#endif /* __uart_H__ */
