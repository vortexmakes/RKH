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
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       getopt.c
 *  \brief      
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <stdio.h>
#include <string.h>

#include "getopt.h"

/* ----------------------------- Local macros ------------------------------ */
#define ERR(s, c)	if(opterr)  \
                        fprintf( stderr, "%s: %s -- %c\n", argv[0], s, c )

/* ------------------------------- Constants ------------------------------- */
enum
{
	ILLEGAL_OPTION, NO_ARGUMENT,
	NUM_MSGS
};

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
int	optind = 1;
static int	optopt;
int	opterr = 1;
char *optarg;
static const char * messages[ NUM_MSGS ] =
{
	"illegal option", 
	"option requires an argument"
};

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
int
getopt( int argc, char **argv, char *opts )
{
	static int sp = 1;
	register int c;
	register char *cp;

	if(sp == 1)
	{
		if(optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0')
			return(EOF);
		else if( strcmp(argv[optind], "--" ) == 0)
		{
			optind++;
			return(EOF);
		}
	}
	optopt = c = argv[optind][sp];
	if( c == ':' || ( cp = strchr(opts, c) ) == NULL )
	{
		ERR( messages[ ILLEGAL_OPTION ], c);
		if(argv[optind][++sp] == '\0')
		{
			optind++;
			sp = 1;
		}
		return('?');
	}
	if( *++cp == ':' )
	{
		if( argv[optind][sp+1] != '\0' )
			optarg = &argv[optind++][sp+1];
		else if(++optind >= argc)
		{
			ERR( messages[ NO_ARGUMENT ], c);
			sp = 1;
			return('?');
		} else
			optarg = argv[optind++];
		sp = 1;
	} else
	{
		if(argv[optind][++sp] == '\0')
		{
			sp = 1;
			optind++;
		}
		optarg = NULL;
	}
	return(c);
}

char *
get_next( char **argv )
{
	return argv[optind++];
}

/* ------------------------------ File footer ------------------------------ */
