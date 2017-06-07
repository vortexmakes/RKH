/*
 * 	slog.h
 */

#ifndef __SLOG_H__
#define __SLOG_H__

#include "serdefs.h"

void com1_init( COMSET_T const *p );

void com1_setbd( unsigned short bd );

void com1_sendchar( const unsigned char c );

void com2_init( COMSET_T const *p );

void com2_setbd( unsigned short bd );

void com2_sendchar( const unsigned char c );

#endif
