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
 * 	Contact information:
 * 	RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * 	e-mail:			francuccilea@gmail.com
 *
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
 * 	\brief 		Socket TCP/IP support for 80x86 OS win32
 *
 * 	\note	    (1) To use the windows socket must be added the "ws2_32.lib" 
 * 					library in Linker->Input->Additional Dependencies 
 * 					configuration.
 */


#ifndef __TCPTRC_H__
#define __TCPTRC_H__


#include <winsock.h>
	

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

int tcp_trace_open( unsigned short port, char *srvip, SOCKET *ps );


/**
 * 	\brief
 *	---.
 * 
 *	---.
 *
 * 	\param s 			---.
 * 	\param c 			---.
 * 	\param len 			---.
 */

void tcp_trace_send( SOCKET s, const char *buf, int len );


/**
 * 	\brief
 *	---.
 * 
 *	---.
 *
 * 	\param s	 		---.
 */

void tcp_trace_close( SOCKET s );


#endif
