/*
 *	conser.h
 *
 * 	This module presents a several routines used by
 * 	command shell's modules. These routines are platform dependent.
 */


#ifndef __CONSER_H__
#define __CONSER_H__

#include "mytypes.h"
#include "console.h"
#include "rkutils.h"
#include "rksys.h"
#include "serial.h"


#if CON_PRINT_FORMATS && RKSYS_PRINT_FORMAT

	#if CON_MSDOS_PLATFORM
	#include <stdio.h>
	#include <conio.h>
	#endif
	#define conser_printf(x)			print_format##x
#else
	#define conser_printf
#endif


/*
 * 	conser_init:
 *
 * 	Attachs a serial channel to command shell.
 */

void conser_init( void );


/*
 * 	conser_putc:
 *
 * 	Writes a character to the attached serial channel.
 */

void conser_putc( const char c );


/*
 * 	conser_puts:
 *
 * 	Writes the string pointed by 's' to attached serial channel.
 */

void conser_puts( const char *s );


#endif
