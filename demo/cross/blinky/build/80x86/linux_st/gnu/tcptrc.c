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
 *  File                     : tcptrc.c
 *	Last updated for version : v2.4.04
 *	By                       : JC
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		Socket TCP/IP support for 80x86 OS linux
 */


#include "tcptrc.h"
#include "rkh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#if RKH_CFG_TRC_EN == 1

int
tcp_trace_open( unsigned short port, char *srv_ip, int *ps )
{
	int s;
	struct sockaddr_in serv_addr;


	/* --- INITIALIZATION ----------------------------------- */
	*ps = 0;

	/* ------------------------------------------------------ */
	
	/* ---- create SOCKET-------------------------------------- */
	s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); /* Create socket */
	if( s < 0 )
	{
		printf("socket opening error\n" );
		return -1; /* Couldn't create the socket */
	}  


	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

	serv_addr.sin_addr.s_addr = inet_addr(srv_ip);  /* Normal Address */

    serv_addr.sin_port = htons(port);
	/* ------------------------------------------------------ */

	/* ---- try CONNECT ----------------------------------------- */
	if (connect(s,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
		printf("ERROR connecting \n");
		return -1;
	}
		
	*ps = s;
	return 0;
}


void
tcp_trace_send( int s, const char *buf, int len )
{
    write( s, buf, len );
}


void
tcp_trace_close( int s )
{
	close( s );
}

#endif
