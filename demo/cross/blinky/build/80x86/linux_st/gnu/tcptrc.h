/**
 * \cond
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 * 	          State-machine framework for reactive embedded systems            
 * 	        
 * 	                    Copyright (C) 2010 Leandro Francucci.
 * 	        All rights reserved. Protected by international copyright laws.
 *
 *
 * 	RKH is free software: you can redistribute it and/or modify it under the 
 * 	terms of the GNU General Public License as published by the Free Software 
 * 	Foundation, either version 3 of the License, or (at your option) any 
 * 	later version.
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
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  --------------------------------------------------------------------------
 *  File                     : tcptrc.h
 *	Last updated for version : v2.4.04
 *	By                       : DB
 *	                           LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		Socket TCP/IP support for 80x86 OS linux
 */


#ifndef __TCPTRC_H__
#define __TCPTRC_H__


/**
 * 	\brief
 *	---.
 * 
 *	---.
 *
 * 	\param port 		---.
 * 	\param srvip 		---.
 * 	\param ps 			---.
 *
 * 	\returns
 * 	---.
 */

int tcp_trace_open( unsigned short port, char *srvip, int *ps );


/**
 * 	\brief
 *	---.
 * 
 *	---.
 *
 * 	\param s 			---.
 * 	\param c 			---.
 */

void tcp_trace_send( int s, const char *buf, int len );


/**
 * 	\brief
 *	---.
 * 
 *	---.
 *
 * 	\param s	 		---.
 */

void tcp_trace_close( int s );


#endif
