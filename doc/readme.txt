/** \page Installation Installation
\image html rkh_bunner.jpg

Prev: \ref main_page "Home" \n
Next: \ref Porting "Porting"

The RKH project is organized through a hierarchical directory structure
to facilitate its distribution, support and maintenance.
This structure also includes application examples and demos on several
platforms. The following annotated directory tree lists the most important 
directories and files provided in the standard RKH distribution. The 
explanation section immediately following the directory tree explains the 
structure in more detail.

\anchor top_dir
\code
<RKH-root>				- RKH-root directory
+---demo				- RKH demo applications
+---doc					- RKH documentation
+---source				- RKH source files
|   copying.txt			- licence file
|   README				- change log file
\	rkh.chm				- reference manual
\endcode
<STRONG> Figure 1 Top level directories </STRONG>

\n This section includes:

- \ref source_dir
- \ref portable_dir
- \ref demo_dir

<HR>
\section source_dir RKH source files

The following figure shows the \c \\source directory.

\anchor source_dir_fig
\code
(1)  <RKH-root>
(2)  +---demo				- Demo applications
(3)  +---doc				- Documentation
(4)  \---source				- RKH source files
(5)  |   \---include		- Platform-independent header files
(6)  |   |       rkh.h
(7)  |   |       rkhassert.h
(8)  |	 |		 rkhevt.h
(9)  |   |       rkhitl.h
(10) |	 |		 rkhmp.h
(11) |   |       rkhplat.h
(12) |   |       rkhrdy.h
(13) |   |       rkhrq.h
(14) |   |       rkhs.h	
(15) |   |       rkhtim.h
(16) |   |       rkhtrc.h
(17) |   \       rkhtype.h
(18) |   +---portable		- Platform-dependent files
(19) |   |   rkh.c
(20) |   |   rkhdyn.c
(21) |   |   rkhmp.c
(22) |   |   rkhrq.c
(23) |   |   rkhs.c
(24) |   |   rkhsma.c
(25) |   |   rkhtbl.c
(26) |   |   rkhtim.c
(27) |   \   rkhtrc.c
(28) |   copying.txt		- licence file
(29) |   README				- change log file
(30) \	 rkh.chm			- reference manual
\endcode
<STRONG> Figure 2 RKH source directory </STRONG>

\li (1)	RKH-root directory
\li (2)	Demo applications
\li (3)	Documentation
\li (4)	RKH source code files
\li (5)	Contains platform-independent header files
\li (6)	Framework interface
\li (7)	Assert definitions
\li (8)	Event data type and other related macros
\li (9)	Internal use only
\li (10) Fixed-size memory block services interface
\li (11) Supported and portable platforms
\li (12) Native priority management
\li (13) Queue services interface
\li (14) Simple and cooperative scheduler interface
\li (15) Timer services interface
\li (16) Trace facility
\li (17) Defines the data types that uses RKH
\li (18) Contains platform-dependent files.
\li (19) State machine engine
\li (20) Dynamic event management, and event framework services
\li (21) Fixed-size memory block
\li (22) Queue (copy by reference)
\li (23) Simple and cooperative scheduler
\li (24) State machine application (SMA) registration.
\li (25) Binary map tables.
\li (26) Software timer.
\li (27) Platform-independent source code of runtime tracing.
\li (28) Licence file
\li (29) Change log file
\li (30) Reference manual

<HR>
\section portable_dir RKH portable directory

\copydetails rkhplat.h
\copydetails rkhtype.h
See the \ref Porting section for more information. 
The following figure shows the \c \\portable directory.

\anchor portable_dir_fig
\code
	 <RKH-root>	
	 +---demo
	 +---doc
	 \---source
( 1) |   \---portable					- RKH ports
( 2) |   |   \---80x86					- Intel x86
( 3) |   |   | 	\---win32_st			- Win32 Single-thread
( 4) |   |   |  | 	\---vc08			- Microsoft Visual 2008
( 5) |   |   |  | 		|	rkhport.h
( 6) |   |   |  |		|	rkht.h
( 7) |   |   \  \		\ 	rkhport.c
( 8) |   |   \---cfv1					- Freescale Coldfire V1
( 9) |   |   | 	\---rkhs				- Use the native scheduler
(10) |   |   |	|	\---cw6_3			- Codewarrior v6.3
(11) |   |   |  | 	|		rkhport.h
(12) |   |   |  |	|		rkht.h
(13) |   |   \ 	\	\		rkhport.c
	 |   \ 	 +---...					- Others
	 |   |   rkh.c
	 |   |   rkhdyn.c
	 |   |   rkhmp.c
     |   |   rkhrq.c
     |   |   rkhs.c
 	 |   |   rkhsma.c
 	 |   |   rkhtbl.c
	 |   |   rkhtim.c
	 |   \   rkhtrc.c
	 |   copying.txt
	 |   README	
	 \	 rkh.chm	
\endcode
<STRONG> Figure 3 RKH portable directory </STRONG>

\li ( 1) RKH ports. The directory \\portable contains platform-dependent 
files to be used by RKH applications. This directory structure is the most 
complicated because of the large number of choices available, such as 
CPU architectures, compilers, operating systems, and compiler options. 
Each of those choices is represented as a separate level of nesting in a 
hierarchical directory tree, so that each dimension in the multi-dimensional 
space of options can be extended independently from the others. Also, the 
directory branch for each port is individually customizable, so each branch 
can represent only choices relevant for a given CPU, operating system, 
compiler, etc.
\li ( 2) Intel x86. The CPU architecture is placed as the first level of 
nesting within the \\portable directory. Examples of CPU architectures could 
be: 80x86, Coldfire, S08, ARM Cortex, ARM, MSP430, etc. Please note that a 
separate directory is needed whenever the CPU architecture is significantly 
different.
\li ( 3) Win32 Single-thread. The second level of nesting, under the CPU 
architecture, is the operating system used.
\li ( 4) Microsoft Visual 2008. The next level of nesting, under each 
operating system directory, is the directory for the compiler used.
\li ( 5) RKH platform-dependent include file. Frequently, defines the 
interrupt locking method, the critical section management, among other things.
The key point of the design is that all platform-independent RKH source 
files include the same \b rkhplat.h header file as the application source 
files.
\li ( 6) RKH platform-dependent include file. In this file is defined the 
data types that uses RKH.
The key point of the design is that all platform-independent RKH source 
files include the same \b rkhtype.h header file as the application source 
files.
\li ( 7) RKH platform-dependent source file. The platform-specific source 
file is optional and many ports don’t require it.
\li ( 8) Freescale Coldfire V1
\li ( 9) Use the native scheduler
\li (10) Codewarrior v6.3
\li (11-13) Idem (5-7)

<HR>
\section demo_dir RKH demo applications

The \\demo directory contains the application examples that are included in the 
standard RKH distribution. The structure of the \\demo is the most complicated 
because of the large number of choices available, such as CPU architectures, 
compilers, operating systems, and compiler options. Each of those choices is 
represented as a separate level of nesting in a hierarchical directory tree, 
so that each dimension in the multi-dimensional space of options can be 
extended independently from the others. Also, the directory branch for each 
RKH port is individually customizable, so each branch can represent only 
choices relevant for a given CPU, operating system, compiler, etc.

Each RKH application must have its own configuration file, called rkhcfg.h. 
This file adapts and configures RKH by means of compiler definitions and macros 
allowing to restrict the resources consumed by RKH. Adjusting this definitions 
allows to reduce the ROM and RAM consumption, and to enhance the system 
performance in a substantial manner.

\anchor demo_dir_fig
\code
	 <RKH-root>	
( 1) \---demo									- RKH demo applications
( 2) |   |   \---80x86							- Intel x86
( 3) |   |   | 	\---win32_st					- Win32 Single-thread
( 4) |   |   |  | 	\---vc08					- Microsoft Visual 2008
( 5) |   |   |  | 		\---ahsm				- State machine example
( 6) |   |   |  | 			+---prj				- Project files
( 7) |   |   |  |			|		rkhcfg.h	- App source and header files
     |   |   |  |			|		main.c
	 |   |   \  \			\ 		...
	 |   \ 	 +---...							- Others
	 |   |   rkh.c
	 |   |   rkhdyn.c
	 |   |   rkhmp.c
     |   |   rkhrq.c
     |   |   rkhs.c
 	 |   |   rkhsma.c
 	 |   |   rkhtbl.c
	 |   |   rkhtim.c
	 |   \   rkhtrc.c
	 +---doc
	 +---source
	 |   copying.txt
	 |   README	
	 \	 rkh.chm	
\endcode
<STRONG> Figure 4 Demo application directories </STRONG>

\li ( 1) RKH demo applications. The \\demo directory contains the application 
examples that are included in the standard RKH distribution. The structure of 
the \\demo is the most complicated because of the large number of choices 
available, such as CPU architectures, compilers, operating systems, and 
compiler options. Each of those choices is represented as a separate level 
of nesting in a hierarchical directory tree, so that each dimension in the 
multi-dimensional space of options can be extended independently from the 
others. Also, the directory branch for each RKH port is individually 
customizable, so each branch can represent only choices relevant for a 
given CPU, operating system, compiler, etc.
\li ( 2) Intel x86. The CPU architecture is placed as the first level of 
nesting within the \\demo directory. Examples of CPU architectures could 
be: 80x86, Coldfire, S08, ARM Cortex, ARM, MSP430, etc. Please note that a 
separate directory is needed whenever the CPU architecture is significantly 
different.
\li ( 3) Win32 Single-thread. The second level of nesting, under the CPU 
architecture, is the operating system used.
\li ( 4) Microsoft Visual 2008. The next level of nesting, under each 
operating system directory, is the directory for the compiler used.
\li ( 5) Finally, the example application is located in its own directory. 
In this case, abstract hierarchical state machine example. This application 
is very useful to learn and explore the Statechart and UML features.
\li ( 6) The \\ahsm\\prj\ subdirectory contains the IDE-dependent files, 
like object files, executable, and among others.
\li ( 7) As mentioned above, each of application that use RKH must be defined 
its own configuration file, rkhcfg.h.

Prev: \ref main_page "Home" \n
Next: \ref Porting "Porting"

\page Porting Porting
\image html rkh_bunner.jpg

Prev: \ref main_page "Home" \n
Next: \ref cfg "Configuration"


This section describes how to adapt the RKH to various platforms, which
is a process called porting. RKH contains a clearly defined abstraction
layer, which encapsulates all the platform-specific code and cleanly
separates it from platform-neutral code.

Porting RKH implies to create the a few platform-dependent files, 
\b rhhport.h, \b rkhport.c, which frequently defines the interrupt 
locking method, the critical section management, among other things.
The RKH directories and files are described in detail in 
\ref Installation section. The next sections listed below describes 
the aspects to be considered to port RKH:

\n This section includes:

- \ref files
- \ref data
- \ref rom
- \ref blk 
- \ref prio
- \ref eque
- \ref dyn
- \ref hk
- \ref ilock
- \ref crt
- \ref trc
- \ref rkhp

\n <HR>
\section files Platform-dependent files

\copydetails rkhplat.h
Please, see \ref portable_dir section.

\n <HR>
\section data Data types definitions

\copydetails rkhtype.h

\n <HR>
\section rom ROM allocator

For declaring an object that its value will not be changed and that
will be stored in ROM, must be defined in \b rkhport.h the RKHROM macro.

Example:

\code
#define RKHROM			const
\endcode

\n <HR>
\section blk Blocking mechanism

<EM>RKH works in conjunction with a traditional OS/RTOS?</EM>

\b YES: \n
The RKH framework can work with virtually any traditional OS/RTOS. 
Combined with a conventional RTOS, RKH takes full advantage of the 
multitasking capabilities of the RTOS by executing each active object (SMA) 
in a separate task or thread.

\li (1) Define the macros #RKH_EN_NATIVE_SCHEDULER = 0, 
#RKH_EN_SMA_THREAD = 1, and #RKH_EN_SMA_THREAD_DATA, within the 
\b rkhcfg.h file.
\li (2) Define the macros RKH_SMA_BLOCK(), RKH_SMA_READY(), and 
RKH_SMA_UNREADY() in \b rkhport.h according to underlying OS or RTOS.
\li (3) Define the macros #RKH_OSDATA_TYPE, and #RKH_THREAD_TYPE in 
\b rkhport.h according to underlying OS or RTOS. 
\li (4) Then, implement the platform-specific functions rkh_init(), rkh_enter(), 
rkh_exit(), rkh_sma_activate(), and rkh_sma_terminate(). All these functions 
are placed in \b rkhport.c.

<EM>Example for x86, VC2008, and win32 single thread</EM>
\code
#define RKH_EQ_TYPE              		RKHRQ_T
#define RKH_OSDATA_TYPE          		HANDLE
#define RKH_THREAD_TYPE             	HANDLE


#define RKH_SMA_BLOCK( sma ) 								\
				RKHASSERT( ((RKHSMA_T*)(sma))->equeue.qty != 0 )

#define RKH_SMA_READY( rg, sma ) 							\
			    rkh_rdy_ins( (rg), ((RKHSMA_T*)(sma))->romrkh->prio ); 	\
			    (void)SetEvent( sma_is_rdy )

#define RKH_SMA_UNREADY( rg, sma ) 							\
			    rkh_rdy_rem( (rg), ((RKHSMA_T*)(sma))->romrkh->prio )

#define RKH_WAIT_FOR_EVENTS() 								\
			    ((void)WaitForSingleObject( sma_is_rdy, (DWORD)INFINITE))
\endcode
\code
void 
rkh_init( void )
{
	InitializeCriticalSection( &csection );
	sma_is_rdy = CreateEvent( NULL, FALSE, FALSE, NULL );
}

void 
rkh_enter( void )
{
	rkhui8_t prio;
	RKHSMA_T *sma;
	RKHEVT_T *e;

    RKH_HK_START();
	RKH_TR_FWK_EN();
    running = 1;

    while( running )
	{
        RKH_ENTER_CRITICAL( dummy );
        if( rkh_rdy_isnot_empty( rkhrg ) ) 
		{
			rkh_rdy_findh( rkhrg, prio );
            RKH_EXIT_CRITICAL( dummy );

            sma = rkh_sptbl[ prio ];
            e = rkh_sma_get( sma );
            rkh_dispatch( sma, e );
            RKH_GC( e );
        }
        else
            rkh_hk_idle();
    }

    rkh_hk_exit();
    CloseHandle( sma_is_rdy );
    DeleteCriticalSection( &csection );	
}

void 
rkh_exit( void )
{
	rkh_hk_exit();
	RKH_TR_FWK_EX();
}

void 
rkh_sma_activate(	RKHSMA_T *sma, const RKHEVT_T **qs, RKH_RQNE_T qsize, 
						void *stks, rkhui32_t stksize )
{
    ( void )stks;
    ( void )stksize;

	rkh_rq_init( &sma->equeue, qs, qsize, sma );
	rkh_sma_register( sma );
    rkh_init_hsm( sma );
	RKH_TR_SMA_ACT( sma );
}

void 
rkh_sma_terminate( RKHSMA_T *sma )
{
	rkh_sma_unregister( sma );
	RKH_TR_SMA_TERM( sma );
}
\endcode

\b NO: \n
\li (1) Define the macros #RKH_EN_NATIVE_SCHEDULER = 1, 
#RKH_EN_SMA_THREAD = 0, and #RKH_EN_SMA_THREAD_DATA = 0, within the 
\b rkhcfg.h file.
\li (2) Define the macros #RKH_EQ_TYPE = RKHRQ_T, RKH_SMA_BLOCK(), 
RKH_SMA_READY(), RKH_SMA_UNREADY() in \b rkhport.h. 
\li (3) When using the native shceduler (RKHS) is NOT necessary provides the 
functions rkh_init(), rkh_enter(), rkh_exit(), rkh_sma_activate(), and 
rkh_sma_terminate(). 
\li (4) Also, the macros RKH_EQ_TYPE, RKH_SMA_BLOCK(), 
\li (5) RKH_SMA_READY(), RKH_SMA_UNREADY() are RKH provided. 
In this mode of operation, RKH assumes the use of native priority scheme. 
See \b rkhs.h, \b rkhs.c, and \b rkhrdy.h files for more information.

\n <HR>
\section prio Priority mechanism

<EM>If RKH works in conjunction with a traditional OS/RTOS, RKH provides its own 
priority mechanism?</EM>

\b YES: \n
\li (1) Declare an RKHRG_T variable.
\li (2) Include the \b rkhrdy.h in rkhport.h.
\li (3) Then, the RKH port could be use the macros rkh_rdy_is_empty(), 
rkh_rdy_isnot_empty(), rkh_rdy_ins(), rkh_rdy_rem(), and rkh_rdy_findh(). 
Frequently, the macros RKH_SMA_BLOCK(), RKH_SMA_READY(), and 
RKH_SMA_UNREADY() use the macros provided by \b rkhrdy.h.

\b NO: \n
Nothing to do.

\n <HR>
\section eque Event queue

<EM>If RKH works in conjunction with a traditional OS/RTOS, are implemented 
the event queues with a message queue of the underlying OS/RTOS?</EM>

\b YES: \n
\li (1) Define the macro #RKH_EN_NATIVE_EQUEUE = 0 in \b rkhcfg.h
\li (2) Define the macro #RKH_EQ_TYPE = 0 in \b rkhport.h according to OS/RTOS.
\li (3) Then, implement the platform-specific functions rkh_sma_post_fifo(), 
rkh_sma_post_lifo() y rkh_sma_get(). All these functions are placed in 
\b rkhport.c file.

<EM>Generic example</EM>
\code
void 
rkh_sma_post_fifo( RKHSMA_T *sma, const RKHEVT_T *e )
{
	RKH_SR_CRITICAL_;
	
	RKH_HK_SIGNAL( e );
    RKH_ENTER_CRITICAL_();
    if( RCE( e )->pool != 0 ) 
        ++RCE( e )->nref;
    RKH_EXIT_CRITICAL_();

    os_post_fifo_message( &sma->equeue, e );
	RKH_TR_SMA_FIFO( sma, e );
}

void 
rkh_sma_post_lifo( RKHSMA_T *sma, const RKHEVT_T *e )
{
	RKH_SR_CRITICAL_;

	RKH_HK_SIGNAL( e );
    RKH_ENTER_CRITICAL_();
    if( RCE( e )->pool != 0 ) 
        ++RCE( e )->nref;
    RKH_EXIT_CRITICAL_();

    os_post_lifo_message( &sma->equeue, e );
	RKH_TR_SMA_LIFO( sma, e );
}

RKHEVT_T *
rkh_sma_get( RKHSMA_T *sma )
{
	RKHEVT_T *e;
	RKH_SR_CRITICAL_;

    RKH_ENTER_CRITICAL_();
	e = os_get_message( &sma->equeue );
	RKHASSERT( e != ( RKHEVT_T * )0 );
    RKH_EXIT_CRITICAL_();

	RKH_TR_SMA_GET( sma, e );
	return e;
}
\endcode

\b NO: \n
\li (1) Define the macro #RKH_EN_NATIVE_EQUEUE = 1 y #RKH_RQ_EN = 1 in 
\b rkhcfg.h
\li (2) When using the native event queues is NOT necessary provides neither 
the functions rkh_sma_post_fifo(), rkh_sma_post_lifo() nor rkh_sma_get().
\li (3) Define #RKH_EQ_TYPE = RKHRQ_T in \b rkhport.h.
		
<EM>If the application code uses the RKH native scheduler, are implemented 
the event queues with the native queues RKHRQ_T?</EM>

\b YES: \n
\li (1) Define the macro #RKH_EN_NATIVE_EQUEUE = 1 y #RKH_RQ_EN = 1 in 
\b rkhcfg.h
\li (2) When using the native event queues is NOT necessary provides neither 
the functions rkh_sma_post_fifo(), rkh_sma_post_lifo() nor rkh_sma_get().
\li (3) Define #RKH_EQ_TYPE = RKHRQ_T in \b rkhport.h.
		
\b NO: \n
\li (1) Define the macro #RKH_EN_NATIVE_EQUEUE = 0 in \b rkhcfg.h
\li (2) Define the macro #RKH_EQ_TYPE = 0 in \b rkhport.h according to OS/RTOS.
\li (3) Then, implement the platform-specific functions rkh_sma_post_fifo(), 
rkh_sma_post_lifo() y rkh_sma_get(). All these functions are placed in 
\b rkhport.c file.

\n <HR>
\section dyn Dynamic event support

<EM>Is required events with arguments?</EM>

\b NO: \n
\li (1) Define the macros #RKH_EN_DYNAMIC_EVENT = 0 and 
#RKH_EN_NATIVE_DYN_EVENT = 0 in \b rkhcfg.h.

\b YES: \n

<EM>If RKH works in conjunction with a traditional OS/RTOS, is implemented 
the dynamic memory support with a internal module of the underlying 
OS/RTOS?</EM>

\b YES: \n
\li (1) Define the macro #RKH_EN_DYNAMIC_EVENT = 1 and 
#RKH_EN_NATIVE_DYN_EVENT = 0 in \b rkhcfg.h
\li (2) Define the macros RKH_DYNE_TYPE, RKH_DYNE_INIT(), 
RKH_DYNE_GET_ESIZE(), RKH_DYNE_GET() y RKH_DYNE_PUT() in \b rkhport.h 
according to underlying OS/RTOS.

<EM>Generic example</EM>
\code
#define RKH_DYNE_TYPE			RKHMP_T

#define RKH_DYNE_INIT( mp, sstart, ssize, esize ) 	\
			rkh_mp_init( (mp),sstart,(rkhui16_t)ssize,(RKH_MPBS_T)esize )

#define RKH_DYNE_GET_ESIZE( mp )					\
			( (mp)->bsize )

#define RKH_DYNE_GET( mp, e )						\
			( (e) = (RKHEVT_T*)rkh_mp_get( (mp) ) )

#define RKH_DYNE_PUT( mp, e )						\
			( rkh_mp_put( (mp), e ) )
\endcode

\b NO: \n
\li (1) Define the macro #RKH_EN_DYNAMIC_EVENT = 1,  
#RKH_EN_NATIVE_DYN_EVENT = 0, and #RKH_MP_EN = 1 in \b rkhcfg.h

<EM>If the application code uses the RKH native scheduler, is implemented 
the dynamic memory support with the native fixed-size memory block pool 
RKHMP_T?</EM>

\b YES: \n
\li (1) Define the macro #RKH_EN_DYNAMIC_EVENT = 1 and 
#RKH_EN_NATIVE_DYN_EVENT = 0 in \b rkhcfg.h

\b NO: \n
\li (1) Define the macro #RKH_EN_DYNAMIC_EVENT = 1,  
#RKH_EN_NATIVE_DYN_EVENT = 0, and #RKH_MP_EN = 1 in \b rkhcfg.h

\n <HR>
\section hk Hook functions

A RKH port cannot and should not define all the functions that it calls, 
because this would render the port too inflexible. The functions that RKH 
calls but doesn't actually implement are referred to as callback or hook 
functions. All these functions in RKH are easily indentifiable by the 
\b "_hk_" key word used in the function name, rkh_hk_dispatch(), 
rkh_hk_signal(), rkh_hk_timeout(), rkh_hk_start(), rkh_hk_exit(), 
and rkh_hk_idle(). 
Please, see RKH_HK_EN_DISPATCH, RKH_HK_EN_SIGNAL, RKH_HK_EN_TIMEOUT, 
RKH_HK_EN_START, and RKH_HK_EN_EXIT options from the \b rkhcfg.h.\n

\code void rkh_hk_dispatch( RKHSMA_T *sma, RKHEVT_T *e )\endcode
\copydetails RKH_HK_EN_DISPATCH

\code void rkh_hk_signal( RKHEVT_T *e )\endcode
\copydetails RKH_HK_EN_SIGNAL

\code void rkh_hk_timeout( const void *t )\endcode
\copydetails RKH_HK_EN_TIMEOUT

\code void rkh_hk_start( void )\endcode
\copydetails RKH_HK_EN_START

\code void rkh_hk_exit( void )\endcode
\copydetails RKH_HK_EN_EXIT

\code void rkh_hk_idle( void )\endcode
\copydetails rkh_hk_idle

\n <HR>
\section ilock Interrupt locking mechanism

\copydetails RKH_DIS_INTERRUPT()
Please, see \ref Installation section about RKH port directory and files.

\n <HR>
\section crt Critical section

\copydetails RKH_SR_CRITICAL_

\n <HR>
\section trc Trace facility

\copydetails rkhtrc.h

RKH has a set of configuration options related to trace tool 
facility, which an user that require this feature must be properly configure 
in the \b rkhcfg.h header file.

\li Define the macro \b RKH_TRC_EN \copydetails RKH_TRC_EN
\li Define the macro \b RKH_TRC_MAX_EVENTS \copydetails RKH_TRC_MAX_EVENTS
\li Define the macro \b RKH_TRC_RUNTIME_FILTER \copydetails RKH_TRC_RUNTIME_FILTER
\li Define the macro \b RKH_TRC_ALL \copydetails RKH_TRC_ALL
\li Define the macro \b RKH_TRC_EN_MP \copydetails RKH_TRC_EN_MP
\li Define the macro \b RKH_TRC_EN_RQ \copydetails RKH_TRC_EN_RQ
\li Define the macro \b RKH_TRC_EN_SMA \copydetails RKH_TRC_EN_SMA
\li Define the macro \b RKH_TRC_EN_TIM \copydetails RKH_TRC_EN_TIM
\li Define the macro \b RKH_TRC_EN_SM \copydetails RKH_TRC_EN_SM
\li Define the macro \b RKH_TRC_EN_RKH \copydetails RKH_TRC_EN_RKH
\li Define the macro \b RKH_TRC_EN_SM_INIT \copydetails RKH_TRC_EN_SM_INIT
\li Define the macro \b RKH_TRC_EN_SM_DCH \copydetails RKH_TRC_EN_SM_DCH
\li Define the macro \b RKH_TRC_EN_SM_CLRH \copydetails RKH_TRC_EN_SM_CLRH
\li Define the macro \b RKH_TRC_EN_SM_TRN \copydetails RKH_TRC_EN_SM_TRN
\li Define the macro \b RKH_TRC_EN_SM_STATE \copydetails RKH_TRC_EN_SM_STATE
\li Define the macro \b RKH_TRC_EN_SM_ENSTATE \copydetails RKH_TRC_EN_SM_ENSTATE
\li Define the macro \b RKH_TRC_EN_SM_EXSTATE \copydetails RKH_TRC_EN_SM_EXSTATE
\li Define the macro \b RKH_TRC_EN_SM_NENEX \copydetails RKH_TRC_EN_SM_NENEX
\li Define the macro \b RKH_TRC_EN_SM_NTRNACT \copydetails RKH_TRC_EN_SM_NTRNACT
\li Define the macro \b RKH_TRC_EN_SM_CSTATE \copydetails RKH_TRC_EN_SM_CSTATE
\li Define the macro \b RKH_TRC_EN_NSEQ \copydetails RKH_TRC_EN_NSEQ
\li Define the macro \b RKH_TRC_EN_CHK \copydetails RKH_TRC_EN_CHK
\li Define the macro \b RKH_TRC_EN_TSTAMP \copydetails RKH_TRC_EN_TSTAMP
\li Define the macro \b RKH_TRC_SIZEOF_TSTAMP \copydetails RKH_TRC_SIZEOF_TSTAMP
\li Define the macro \b RKH_TRC_SIZEOF_STREAM \copydetails RKH_TRC_SIZEOF_STREAM
\li Define the macro \b RKH_TRC_SIZEOF_POINTER \copydetails RKH_TRC_SIZEOF_POINTER

See \ref cfg section for more information about that.

A RKH port cannot and should not define all the functions 
that it calls, because this would render the port too inflexible. Therefore, 
the application-specific functions rkh_trc_open(), rkh_trc_close(), 
rkh_trc_flush(), and rkh_trc_getts() are application provided.

\code void rkh_trc_open( void )\endcode
\copydetails RKH_TRC_OPEN

\code void rkh_trc_close( void )\endcode
\copydetails RKH_TRC_CLOSE

\code void rkh_trc_flush( void )\endcode
\copydetails RKH_TRC_FLUSH

\code void rkh_trc_getts( void )\endcode
\copydetails rkh_trc_getts

<HR>
\section rkhp A port file example.

<EM>\b "rkhport.h" for x86, VC2008, and win32 single thread</EM>
<EM> (\\source\\portable\\80x86\\win32_st\\vc08)</EM>

\code
#ifndef __RKHPORT_H__
#define __RKHPORT_H__


#include <windows.h>

#include "rkhtype.h"
#include "rkhrq.h"
#include "rkhmp.h"
#include "rkhrdy.h"


extern CRITICAL_SECTION csection;
extern HANDLE sma_is_rdy;
extern RKHRG_T rkhrg;


const char *rkh_get_port_version( void );
const char *rkh_get_port_desc( void );


/*
 * 	Declaring an object RKHROM announces that its value will
 * 	not be changed and it will be stored in ROM.
 */

#define RKHROM			const	


#define RKH_DIS_INTERRUPT()
#define RKH_ENA_INTERRUPT()
//#define RKH_CPUSR_TYPE
#define RKH_ENTER_CRITICAL( dummy )		EnterCriticalSection( &csection )
#define RKH_EXIT_CRITICAL( dummy )		LeaveCriticalSection( &csection )


#define RKH_EQ_TYPE              		RKHRQ_T
#define RKH_OSDATA_TYPE          		HANDLE
#define RKH_THREAD_TYPE             	HANDLE


#define RKH_SMA_BLOCK( sma ) 									\
				RKHASSERT( ((RKHSMA_T*)(sma))->equeue.qty != 0 )

#define RKH_SMA_READY( rg, sma ) 								\
			    rkh_rdy_ins( (rg), ((RKHSMA_T*)(sma))->romrkh->prio ); 	\
			    (void)SetEvent( sma_is_rdy )

#define RKH_SMA_UNREADY( rg, sma ) 								\
			    rkh_rdy_rem( (rg), ((RKHSMA_T*)(sma))->romrkh->prio )

#define RKH_WAIT_FOR_EVENTS() 									\
			    ((void)WaitForSingleObject( sma_is_rdy, (DWORD)INFINITE))


#endif
\endcode

<EM>\b "rkht.h" for x86, VC2008, and win32 single thread</EM>
<EM> (\\source\\portable\\80x86\\win32_st\\vc08)</EM>

\code
#ifndef __RKHT_H__
#define __RKHT_H__


/*
 * 	Portable data types.
 *
 * 	The RKH uses a set of integer quantities. That maybe 
 * 	machine or compiler	dependent.
 *
 * 	Note:
 *
 * 	The 'HUInt' and 'HInt' will normally be the natural size 
 * 	for a particular machine. These types designates an integer 
 * 	type that is usually fastest to operate with among all integer 
 * 	types.
 */

typedef signed char 	rkhi8_t;
typedef signed short 	rkhi16_t;
typedef signed long		rkhi32_t;
typedef unsigned char 	rkhui8_t;
typedef unsigned short 	rkhui16_t;
typedef unsigned long	rkhui32_t;

typedef unsigned int	HUInt;
typedef signed int		HInt;


#endif
\endcode


\page qref Quick reference
\image html rkh_bunner.jpg

Prev: \ref main_page "Home" \n
Next: \ref Installation "Installation"

The main objective of this section is to show and also illustrate the most 
important concepts to apply when dealing with RKH and the event-driven 
applications.

This section includes:

- \ref qref0
- \ref qref1
- \ref qref2
- \ref qrefsb
- \ref qref16
- \ref qref3
- \ref qref17
- \ref qref4
- \ref qref5
- \ref qref6
- \ref qref14
- \ref qref12
- \ref qref7
- \ref qref13
- \ref qref8
- \ref qref9
- \ref qref10
- \ref qref15
- \ref qref18

\n
<HR>
\section qref0 Defining a state machine

\n Prev: \ref qref "Quick reference" \n

A state machine application is defined with the RKH_SMA_CREATE() macro and 
declared with the RKH_SMA_DCLR() macro. Frequently, each state machine is 
encapsulated inside a dedicated source file (.c file), from which the 
RKH_SMA_CREATE() macro is used, thus the structure definition is in fact 
entirely encapsulated in its module and is inaccessible to the rest of the 
application. However, as a general rule, the state machine application must 
be declared inside a header file (.h file) by means of RKH_SMA_DCLR() 
macro. We will develop one example of state machine creation to illustrate 
the use of this macro. Also, we will give our hierarchical state machine the 
name \c my. If you wanted to create a "flat" state machine, you would use the 
#FLAT parameter rather than the #HCAL parameter.

This section includes:

- \ref qref0_1
- \ref qref0_2
- \ref qref0_3


\subsection qref0_1 Defining the state machine application
\n
\code
(1)	//	my.c: state machine application's module

(2) typedef struct
    {
		RKHSMA_T sm;	// base structure
		rkhui8_t x;		// private member
		rkhui8_t y;		// private member
	} MYSM_T;

(3) static RKH_DCLR_STATIC_EVENT( turnon, TURNON );

(4) RKH_SMA_CREATE( 	MYSM_T, 	// state machine application data type
(5) 					3, 			// ID
(6) 					my, 		// name
(7)						2,			// priority number
(8) 					HCAL, 		// hierarchical state machine
(9) 					&S1, 		// initial state
(10) 					my_init, 	// initial action
(11) 					&turnon );	// initial event
\endcode

\subsection qref0_2 Declaring the state machine
\code
//	my.h: state-machine application's header file

RKH_SMA_DCLR( my );
\endcode

Explanation

\li (1)	Frequently, each state machine application is encapsulated inside a 
		dedicated source file (.c file), from which the RKH_SMA_CREATE() 
		macro is used.
\li (2)	The MYSM_T defines the \c my state machine application structure.
		Almost every state machine applications must also store 
		other "extended-state" information. You supply this additional 
		information by means of data members enlisted after the base structure 
		member \c sm. This illustrates how to derive an state machine 
		application from RKHSMA_T. Please note that the RKHSMA_T member 
		\c sm is defined as the FIRST member of the derived struct.
		RKHSMA_T is not intended to be instantiated directly, but rather 
		serves as the base structure for derivation of state machines in the 
		application code.
\li (3)	Declares and initializes the event structure \c turnon with \c TURNON  
		signal and establishes it as one static event. The created event 
		object is explicitly placed in ROM..
\li (4)	As said below, the MYSM_T defines the \c my state machine application 
		structure.
\li (5)	\c 3 is the state machine application ID. This number allows to 
		uniquely identify a state machine application.
\li (6)	\c my is the state machine application. Represents the top state of 
		state diagram. 
\li (7)	\c 2 is the state machine application priority.
\li (8)	the \c my state machine is defined as a hierarchical state machine. 
		The available property options are enumerated in RKH_HPPTY_T 
		enumeration in the \b rkh.h file.
\li (9)	\c S1 is the initial state.
\li (10) \c my_init() function defines the topmost initial transition in 
		the \c my state machine. 
		The function prototype is defined as RKHINIT_T. This argument is 
		(optional), thus it could be declared as NULL. The application code 
		must trigger the initial transition explicitly by invoking 
		rkh_sma_activate() function.
\li (11) \c turnon is a pointer to an event that will be passed to state 
		machine application when it starts. Could be used to pass arguments 
		to the state machine like an argc/argv. This argument is optional, 
		thus it could be declared as NULL or eliminated in compile-time with 
		RKH_SMA_EN_IEVENT = 0.

\subsection qref0_3 Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_SMA_EN_IEVENT: \n
	When RKH_SMA_EN_IEVENT is set to one (1) the RKHSMA_T structure allows to 
	reference a event, which will be passed to state machine application when 
	it starts. Could be used to pass arguments to the state machine like an 
	argc/argv. \n\n
- \b RKH_SMA_EN_ID: \n
	When RKH_SMA_EN_ID is set to one (1) the RKHSMA_T structure includes a 
	ID number that could be used to uniquely identify a state machine 
	application.

\n Prev: \ref qref "Quick reference"

<HR>
\section qref1 Defining a composite state

\n Prev: \ref qref "Quick reference"

A superstate or composite state is defined with the RKH_CREATE_COMP_STATE()
macro and declared with the #RKH_DCLR_COMP_STATE macro. Frequently, each 
state machine and its states (composite and basic) are encapsulated 
inside a dedicated source file (.c file), from which the 
RKH_CREATE_COMP_STATE() macro is used.
We will develop one example of composite state definition to illustrate the 
use of this macro. We will give our composite state the name \c S1. 

This section includes:

- \ref qref1_1
- \ref qref1_2
- \ref qref1_3

\subsection qref1_1 Defining a composite state
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_COMP_STATE( 	S1, 
(3)							0, 
(4)							turn_on, 
(5)							turn_off, 
(6)							&SA, 
(7)							&S11, 
(8)							&H );
\endcode

\subsection qref1_2 Declaring a composite state
\code
//	my.h: state-machine's header file

...
RKH_DCLR_COMP_STATE S1;
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_COMP_STATE() macro is used.
\li (2)	\c S1 is the state name. Represents a composite state structure.
\li (3)	\c 0 is the value of state ID.
\li (4)	\c turn_on() defines the entry action to be executed unconditionally 
		upon the entry to the \c S1 state. This argument is optional, 
		thus it could be declared as NULL. The RKHENT_T defines the function 
		prototype.
\li (5)	\c turn_off() defines the exit action, which is executed upon exit 
		from the \c S1 state. This argument is optional, thus it could be 
		declared as NULL. The RKHEXT_T defines the function prototype.
\li (6)	\c SA is the parent state of \c S1. If a state has no 
		explicit superstate means that it is implicitly nested in 
		the "top" state, and the parent state is defined by means of RKH_ROOT
		macro.  The "top" state is a UML concept that denotes 
		the ultimate root of the state hierarchy in a hierarchical state 
		machine.
\li (7)	\c S11 is the default state of \c S1 state machine. At each level 
		of nesting, a superstate can have a private initial transition that
		designates the active substate after the superstate is entered 
		directly. Here the initial transition of state \c S1 designates the 
		state \c S11 as the initial active substate.
\li (8)	\c H is the history pseudostate. This argument is optional, thus 
		it could be declared as NULL. See RKH_CREATE_SHALLOW_HISTORY_STATE() 
		macro and RKH_CREATE_DEEP_HISTORY_STATE().

\subsection qref1_3 Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_SMA_EN_HCAL: \n
	Enable (1) or disable (0) the state nesting. When RKH_SMA_EN_HCAL is set 
	to one (1) some important features of RKH are not included: state 
	composite state, history (shallow and deep) pseudostate, entry action, 
	and exit action. \n\n
- \b RKH_SMA_EN_STATE_ID: \n
	When RKH_SMA_EN_STATE_ID is set to one (1) the state structure includes an 
	ID number. This number allows to uniquely identify a state.

\n Prev: \ref qref "Quick reference"

<HR>
\section qref2 Defining a basic state

\n Prev: \ref qref "Quick reference"

A basic state (also called substate) is defined with the 
RKH_CREATE_BASIC_STATE() macro and declared with the #RKH_DCLR_BASIC_STATE 
macro. Frequently, each state machine and its states (composite and 
basic) are encapsulated inside a dedicated source file (.c file), from 
which the RKH_CREATE_BASIC_STATE() macro is used.
We will develop one example of basic state definition to illustrate the 
use of this macro. We will give our basic state the name \c S11. 
As will demostrates the use of RKH_CREATE_BASIC_STATE() macro and its
arguments is very similar to RKH_CREATE_COMP_STATE() macro.

<b>Defining a basic state</b>
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_BASIC_STATE( S11, 
(3)							4, 
(4)							start_process, 
(5)							stop_process, 
(6)							&S1, 
(7)							in_keyb );
\endcode

<b>Declaring a basic state</b>
\code
//	my.h: state-machine's header file

...
RKH_DCLR_BASIC_STATE S11;
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_BASIC_STATE() macro is used.
\li (2)	\c S11 is the state name. Represents a substate structure.
\li (3)	\c 4 is the value of state ID.
\li (4)	\c start_process() defines the entry action to be executed unconditionally 
		upon the entry to the \c S11 state. This argument is optional, 
		thus it could be declared as NULL. The RKHENT_T defines the function 
		prototype.
\li (5)	\c stop_process() defines the exit action, which is executed upon exit 
		from the \c S11 state. This argument is optional, thus it could be 
		declared as NULL. The RKHEXT_T defines the function prototype.
\li (6)	\c S1 is the parent state of \c S11. If a state has no 
		explicit superstate means that it is implicitly nested in 
		the "top" state, and the parent state is defined by means of RKH_ROOT
		macro.  The "top" state is a UML concept that denotes 
		the ultimate root of the state hierarchy in a hierarchical state 
		machine.
\li (7)	\c in_keyb() defines the event preprocessor action. Before sending the 
		arrived event to state machine, it can be previously processed using 
		the	event preprocessor function. An action function takes the state 
		machine pointer and the event pointer as arguments. The first 
		parameter is optional in compile-time according to 
		\b RKH_EN_PPRO_HSM_ARG macro.
		Example:
\code
static
RKHE_T
in_keyb( RKHEVT_T *pe )
{
	if( pe->e >= 0 && pe->e <= 9 )
		return DECIMAL;
	if( pe->e == '.' )
		return POINT;
	else
		return pe->e;
}
\endcode

\li (7)	Aditionally, by means of single inheritance in C it could be 
		used to supply additional information to state.
		Implementing the single inheritance in C is very 
		simply by literally embedding the base type, RKHPPRO_T in 
		this case, as the first member of the derived structure.
		This argument is optional, thus it could be declared as NULL.
		Example:
\code
typedef struct
{
	RKHPPRO_T prepro; 	// extend the RKHPPRO_T class
	unsigned min:4;		// addtional information...
	unsigned max:4;
	char *buff;
} SDATA_T;				// this data type will be used in S12 context

static const SDATA_T option = { preprocessor, 4, 8, token };

/* Define S11 state as a substate of S1 */
RKH_CREATE_BASIC_STATE( S11, 4, start_process, start_process, &S1, in_keyb ); 

/* Define S12 state as a substate of S1 */
RKH_CREATE_BASIC_STATE( S12, 5, NULL, NULL, &S1, (RKHPPRO_T*)&option ); 
\endcode

\b Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_SMA_EN_STATE_ID: \n
	When RKH_SMA_EN_STATE_ID is set to one (1) the state structure includes an 
	ID number. This number allows to uniquely identify a state. \n\n
- \b RKH_SMA_EN_PPRO: \n
	When RKH_SMA_EN_PPRO is set to one (1) the state structure includes an 
	reference to preprocessor function. This function could be called "Moore" 
	action. This argument is optional, thus it could be declared as NULL. 
	Aditionally, by means of single inheritance in C it could be used as 
	state's abstract data. Aditionally, implementing the single inheritance 
	in C is very simply by literally embedding the base type, RKHPPRO_T in 
	this case, as the first member of the derived structure. See \a prepro 
	member of RKHSREG_T structure for more information.

\n Prev: \ref qref "Quick reference"

<HR>
\section qrefsb Defining a submachine state

\n Prev: \ref qref "Quick reference"

A submachine state is a kind of a state that actually refers to 
another defined state machine. The diagram in following figure shows a 
fragment from a state machine diagram in which a submachine state 
(the \c SB) is referenced.

\anchor fig_sbm1
\image html sbm1.png "Submachine state"

In the above example, the transition triggered by event \c TWO will 
terminate on entry point \c ENS12 of the \c SB state machine. 
The \c ONE transition implies taking of the default transition of the 
\c SB and executes the \c act5() action. The transition emanating from 
the \c EX1S12 exit point of the submachine will execute the \c act1() 
behavior in addition to what is executed within the \c SB state machine. 
Idem transition emanating from the \c EX2S12.
This transition must have been triggered within the \c SB state machine. 
Finally, the transition emanating from the edge of the submachine state 
is triggered by event \c THREE.

The following figure is an example of a state machine \c SB defined with 
two exit points, \c EXPNT1 and \c EXPNT2, and one entry point \c ENPNT.

\anchor fig_sbm2
\image html sbm2.png "State machine with two exit points and one entry point"

In the following figure the state machine shown above is referenced twice in 
a submachine state \c S12 and \c S2.

\anchor fig_sbm3
\image html sbm3.png "Submachine state with usage of exit and entry points"

This section includes:

- \ref qrefsb_1
- \ref qrefsb_2
- \ref qrefsb_3
- \ref qrefsb_4
- \ref qrefsb_5
- \ref qrefsb_6
- \ref qrefsb_7
- \ref qrefsb_8
- \ref qrefsb_9
- \ref qrefsb_10
- \ref qrefsb_11
- \ref qrefsb_c

\subsection qrefsb_1 Defining a submachine state

A submachine state is defined with the RKH_CREATE_SUBMACHINE_STATE()
macro and declared with the #RKH_DCLR_SUBM_STATE macro. Frequently, each 
state machine and its states (composites, basic, and submachine states) are 
encapsulated inside a dedicated source file (.c file), from which the 
RKH_CREATE_SUBMACHINE_STATE() macro is used.
We will develop one example of submachine state definition to illustrate the 
usage and its related macros. We will give our submachine state the name 
\c S12.

\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_SUBMACHINE_STATE( 	S12, 
(3)									7, 
(4)									NULL, 
(5)									NULL, 
(6)									&S1, 
(7)									&SB );
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_SUBMACHINE_STATE() macro is used.
\li (2)	\c S12 is the state name. Represents a submachine state structure.
\li (3)	\c 7 is the value of state ID.
\li (4)	the entry action is not used.
\li (5)	the exit action is not used.
\li (6)	\c S1 is the parent state of \c S12. If a state has no 
		explicit superstate means that it is implicitly nested in 
		the "top" state, and the parent state is defined by means of RKH_ROOT
		macro.  The "top" state is a UML concept that denotes 
		the ultimate root of the state hierarchy in a hierarchical state 
		machine.
\li (7)	\c SB is the defined submachine state machine, which is referenced by 
		\c S12 submachine state.

On the other hand, in RKH every submachine state is associated with a 
transition table, which is composed of a well-defined set of transitions. 
See \ref qref16 for defining a state transition table.

\code
RKH_CREATE_TRANS_TABLE( S12 )
	RKH_TRINT( TERM, 	NULL, 	terminate ),
	RKH_TRREG( THREE,	NULL, 	NULL, 	&S1 ),
RKH_END_TRANS_TABLE
\endcode

\subsection qrefsb_2 Declaring a submachine state
\code
//	my.h: state-machine's header file

...
RKH_DCLR_SUBM_STATE S12;
\endcode

\subsection qrefsb_3 Defining the exit connection references

Connection point references are sources/targets of transitions implying 
exits out of/entries into the submachine state machine referenced by a 
submachine state.
In RKH every submachine state is associated with a exit point connection 
point reference table, which is composed of a well-defined set of 
exit point connection references. Thus, in RKH each row in a exit point table 
references an exit point pseudostate as defined in the submachine of the 
submachine state that has the exit point connection point defined. 
Note that each row number matches with the index number of the exit point 
pseudostate that it represent.

\code
// --- exit point pseudostates of SB submachine ---
RKH_CREATE_REF_EXPNT( 	EXPNT1, 
						0,			// index of exit point connection table
						&SB );
RKH_CREATE_REF_EXPNT( 	EXPNT2, 
						1, 			// index of exit point connection table
						&SB );
...
// --- exit point connection references of S12 submachine state ---
(1) RKH_CREATE_EX_CNNPNT_TABLE( S12 )
(2) 	RKH_EX_CNNPNT( EX1S12, &EXPNT1, act1, &S13 ), // table index = 0 (EXPNT1)
(3) 	RKH_EX_CNNPNT( EX2S12, &EXPNT2, act2, &S3 ),  // table index = 1 (EXPNT2)
(4) RKH_END_EX_CNNPNT_TABLE
\endcode

Explanation

\li (1)	The RKH_CREATE_EX_CNNPNT_TABLE() macro creates the \c S12's 
		exit point connection reference table. Each exit point connection 
		reference table always begins with the macro 
		RKH_CREATE_EX_CNNPNT_TABLE() and ends with the macro 
		#RKH_END_EX_CNNPNT_TABLE. As noted above, sandwiched between these 
		macros are the exit point macros, RKH_EX_CNNPNT().

\li (2)	The RKH_EX_CNNPNT() macro defines the exit point connection 
		\c EX1S12, where \c EXPNT1 is the referenced exit point pseudostate, 
		\c act1() is the transition action function to be taken, and 
		\c S13 is the transition target state. The place in the table matches 
		with the \c EXPNT1's index field.

\li (3)	Idem (2).

\li (4)	The #RKH_END_EX_CNNPNT_TABLE macro ends exit point connection 
		reference table.

\subsection qrefsb_4 Defining the entry connection references

Connection point references are sources/targets of transitions implying 
exits out of/entries into the submachine state machine referenced by a 
submachine state.

A entry point connection reference is defined with the RKH_EN_CNNPNT() 
macro and declared with the #RKH_DCLR_ENPNT macro. 
Frequently, each state machine and its states and pseudostates are 
encapsulated inside a dedicated source file (.c file), from which the 
RKH_EN_CNNPNT() macro is used.
We will develop one example of entry point connection definition to 
illustrate the use of this macro. We will give our entry connection the 
name \c ENS12.

\code
(1)	//	my.c: state-machine's module

(2)	RKH_EN_CNNPNT( 	ENS12, 
					&ENPNT, 
					&S12 );
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_EN_CNNPNT() macro is used.
\li (2)	The RKH_EN_CNNPNT() macro defines the exit point connection 
		\c ENS12, where \c ENPNT is the referenced entry point pseudostate, 
		and \c S12 is the transition target state.

\subsection qrefsb_5 Declaring entry connection references

\code
//	my.h: state-machine's header file

...
RKH_DCLR_ENPNT ENS12;
\endcode

\subsection qrefsb_6 Defining a submachine

A submachine is defined with the RKH_CREATE_REF_SUBMACHINE() macro and 
declared with the #RKH_DCLR_REF_SUBM macro. Frequently, each 
state machine and its states (composites, basic, and submachine states) are 
encapsulated inside a dedicated source file (.c file), from which the 
RKH_CREATE_REF_SUBMACHINE() macro is used.
We will develop one example of submachine definition to illustrate the 
usage and its related macros. We will give our submachine the name \c SB.

\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_REF_SUBMACHINE( 	SB, 
(3)								0, 
(4)								&SB1, 
(5)								NULL );
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_REF_SUBMACHINE() macro is used.
\li (2)	\c SB is the submachine name. Represents a submachine structure.
\li (3)	\c 0 is the value of submachine ID.
\li (4) \c SB1 is the default state of \c SB submachine. At each level of 
		nesting, a submachine can have a private initial transition that 
		designates the active substate after the submachine is entered 
		directly. Here the initial transition of state \c SB designates 
		the state \c SB1 as the initial active substate. 
\li (5) the initialization action is not used. 

\subsection qrefsb_7 Declaring a submachine

\code
//	my.h: state-machine's header file

...
RKH_DCLR_REF_SUBM SB;
\endcode

\subsection qrefsb_8 Defining the exit point

A exit point pseudostate is defined with the RKH_CREATE_REF_EXPNT() 
macro and declared with the #RKH_DCLR_REF_EXPNT macro. 
Frequently, each state machine and its states and pseudostates are 
encapsulated inside a dedicated source file (.c file), from which the 
RKH_CREATE_REF_EXPNT() macro is used.
We will develop one example of exit point definition to 
illustrate the use of this macro. We will give our exit points the 
name \c EXPNT1 and \c EXPNT2.

\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_REF_EXPNT( 	EXPNT1, 
							0, 
							&SB );
	RKH_CREATE_REF_EXPNT( 	EXPNT2, 
							1, 
							&SB );
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_EN_CNNPNT() macro is used.
\li (2)	The RKH_CREATE_REF_EXPNT() macro defines the exit point \c EXPNT1, 
		where \c 0 is the index of the exit point connection table, and 
		\c SB is the containing submachine. See \ref qrefsb_5 for referencing 
		a submachine exit point from a submachine state.

\subsection qrefsb_9 Declaring a submachine

\code
//	my.h: state-machine's header file

...
RKH_DCLR_REF_EXPNT EXPNT1, EXPNT2;
\endcode

\subsection qrefsb_10 Defining the entry point

A entry point pseudostate is defined with the RKH_CREATE_REF_ENPNT() 
macro and declared with the #RKH_DCLR_REF_ENPNT macro. 
Frequently, each state machine and its states and pseudostates are 
encapsulated inside a dedicated source file (.c file), from which the 
RKH_CREATE_REF_ENPNT() macro is used.
We will develop one example of entry point definition to 
illustrate the use of this macro. We will give our entry point the 
name \c ENPNT.

\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_REF_ENPNT( 	ENPNT, 
							act8,
							&SB1,
							&SB );
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_REF_ENPNT() macro is used.
\li (2)	The RKH_CREATE_REF_ENPNT() macro defines the entry point \c ENPNT, 
		where \c activate() is the transition action to be taken, \c SB1 is 
		the transition target state, and \c SB is the containing submachine.

\subsection qrefsb_11 Declaring a entry point

\code
//	my.h: state-machine's header file

...
RKH_DCLR_REF_ENPNT ENPNT;
\endcode

\subsection qrefsb_c Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_SMA_EN_HCAL: \n \copydetails RKH_SMA_EN_HCAL	
- \b RKH_SMA_EN_PSEUDOSTATE: \n \copydetails RKH_SMA_EN_PSEUDOSTATE
- \b RKH_SMA_EN_SUBMACHINE: \n \copydetails RKH_SMA_EN_SUBMACHINE
- \b RKH_SMA_EN_STATE_ID: \n \copydetails RKH_SMA_EN_STATE_ID

\n Prev: \ref qref "Quick reference"

<HR>
\section qref16 Defining a state transition table

\n Prev: \ref qref "Quick reference"

In RKH every state is associated with a transition table, which is composed 
of a well-defined set of transitions.
The general syntax of an expression labelling a transition in a statechart is
\e "i[c]/a" where \e i is the input that triggers the transition, \e c is a 
condition that guards the transition from being taken unless it is true when 
\e i occurs, and \e a is an action that is carried out if and when the 
transition is taken. All of these parts are optional. 
Thus, in RKH each row in a table represents a transition, which is 
well-defined by an \e event, a \e guard, an \e action, and \e target state 
(or pseudostate). The \ref fig_trtbl "Transition table" figure shows a 
demostrative example of that.

\anchor fig_trtbl
\image html trtbl.jpg "Transition table"

\li (1)	Expressing this transition as said above:\n\n
		<EM>RCV_DATA[ data == SYNC ]/store_data( data )</EM>\n\n
		The \c data \c == \c SYNC expression guards the transition from being 
		taken unless it is true. The \c store_data() function is the action to
		be taken. Note that in RKH the guard condition is evaluated invoking 
		to a function.

\li	(2)	Expressing this transition as said above:\n\n
		<EM>TOUT0/drop_frame()</EM>\n\n
		This transition is not conditioned by a guard.

\li	(3)	Expressing this transition as said above:\n\n
		<EM>DISABLE/disable()</EM>\n\n
		Similar to prior transition.


Now, is time to represent IN_DATA's transition table by means of RKH 
framework:

\code
(1)	RKH_CREATE_TRANS_TABLE( IN_DATA )
(2)		RKH_TRINT( RCV_DATA,	is_sync,	store_data 				),
(3)		RKH_TRREG( TOUT0, 		NULL, 		drop_frame, &WAIT_SYNC	),
		RKH_TRREG( DISABLE, 	NULL, 		disable, 	&IDLE		)
(4)	RKH_END_TRANS_TABLE
\endcode

Explanation

\li (1)	The RKH_CREATE_TRANS_TABLE() macro creates the \c IN_DATA's 
transition table. Each transition table always begins with the macro 
RKH_CREATE_TRANS_TABLE() and ends with the macro RKH_END_TRANS_TABLE().
As noted above, sandwiched between these macros are the transitions macros 
that actually represent behavior of state.

\li (2)	The RKH_TRINT() macro defines a internal transition, where 
\c RCV_DATA is the triggering event, \c is_sync is the guard function, 
and \c store_data() is the action function to be taken.

\li (3)	The RKH_TRREG() macro defines a regular state transition, where 
\c TOUT0 is the triggering event, \c drop_frame() is the action function to 
be taken, and \c WAIT_SYNC is the target state. Note that it is not guarded.

\li (4)	The RKH_END_TRANS_TABLE() macro ends transition table.

As said above, the actions and guards in RKH framework are represented by 
functions. Thus, \c is_sync() could be declared as:

\code
HUInt 
is_sync( RKHEVT_T *pe )
{
	return pe->e == SYNC;
}
\endcode

\n Prev: \ref qref "Quick reference"

<HR>
\section qref3 Defining a conditional pseudostate

\n Prev: \ref qref "Quick reference"

A conditional pseudostate (also called choice pseudostate) is defined with 
the RKH_CREATE_COND_STATE() macro and declared with the 
#RKH_DCLR_COND_STATE macro. Frequently, each state machine and its 
states and pseudostates are encapsulated inside a dedicated source file 
(.c file), from which the RKH_CREATE_COND_STATE() macro is used.
We will develop one example of choice pseudostate definition to 
illustrate the use of this macro. We will give our choice pseudostate 
the name \c C1. As will demostrates the use of RKH_CREATE_COND_STATE() 
macro and its arguments is very similar to RKH_CREATE_BASIC_STATE() macro.

<b>Defining a choice pseudostate</b>
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_COND_STATE( 	C1, 
(3)							0 );
\endcode

<b>Declaring a choice pseudostate</b>
\code
//	my.h: state-machine's header file

...
RKH_DCLR_COND_STATE C1;
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_BASIC_STATE() macro is used.
\li (2)	\c C1 is the pseudostate name. Represents a choice pseudostate 
		structure.
\li (3)	\c 0 is the value of pseudostate ID.

\b Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_SMA_EN_HCAL: \n
	Enable (1) or disable (0) the state nesting. When RKH_SMA_EN_HCAL is set 
	to one (1) some important features of RKH are not included: state 
	composite state, history (shallow and deep) pseudostate, entry action, 
	and exit action. \n\n
- \b RKH_SMA_EN_STATE_ID: \n
	When RKH_SMA_EN_STATE_ID is set to one (1) the state structure includes an 
	ID number. This number allows to uniquely identify a state. \n\n
- \b RKH_SMA_EN_PSEUDOSTATE: \n
	Enable (1) or disable (0) the pseudostates usage.\n\n 
- \b RKH_SMA_EN_CONDITIONAL: \n
	Enable (1) or disable (0) the conditional connector usage. \n\n
- \b RKH_SMA_MAX_TR_SEGS: \n
	Determines the maximum number of linked transition segments. The smaller 
	this number, the lower the static RAM consumption. Typically, the most 
	of hierarchical state machines uses up to 4 transition segments. 
	Currently RKH_SMA_MAX_TR_SEGS cannot exceed 8.

\n Prev: \ref qref "Quick reference"

<HR>
\section qref17 Defining a branch table

\n Prev: \ref qref "Quick reference"

A condition connector has one incoming transition and can have several 
outgoing transition segments called branches. Branches are labeled with 
guards that determine which one is to be actually taken. 
Since the condition connector is an OR connector, only one of the branches 
can be taken. Each condition connector can have one special branch with 
a guard labeled rkh_else, which is taken if all the guards on the other 
branches are false. 
Branches cannot contain triggers, but in addition to a guard they may 
contain actions. A branch can enter another condition connector, thus 
providing for the nesting of branches.
In RKH branches are defined by the macro RKH_BRANCH().
The general syntax of an expression labelling a branch in a statechart is
\e "[c]/a" where \e c is a condition that guards the transition from being 
taken unless it is true, and \e a is an action that is carried out if and 
when the transition is taken. All of these parts are optional. 
Example:

\code
(1)	RKH_CREATE_BRANCH_TABLE( C1 )
(2)		RKH_BRANCH( power_ok, 	enable_process,	&S22	),
(3)		RKH_BRANCH( ELSE, 		abort,			&S4 	),
(4)	RKH_END_BRANCH_TABLE
\endcode

Explanation

\li (1)	The RKH_CREATE_BRANCH_TABLE() macro creates the \c C1's 
branch table. Each table type always begins with the macro 
RKH_CREATE_BRANCH_TABLE() and ends with the macro RKH_END_BRANCH_TABLE().
As noted above, sandwiched between these macros are the segment macros 
that actually comprise the condition connector.

\li (2)	The RKH_BRANCH() macro defines a branch segment, where 
\c power_ok() is the guard function, \c enable_process is the action function 
to be taken, and S22 is the target state.

\li (3)	If all the guards on the other branches are false \c abort() function 
will be invoked, and \c S4 will be the next state.

\li (4)	The RKH_END_BRANCH_TABLE() macro ends branch table.

As said above, the actions and guards in RKH framework are represented by 
functions.

\n Prev: \ref qref "Quick reference"

<HR>
\section qref4 Defining a shallow history pseudostate

\n Prev: \ref qref "Quick reference"

A shallow history pseudostate is defined with the 
RKH_CREATE_SHALLOW_HISTORY_STATE() macro and declared with the 
#RKH_DCLR_SHIST_STATE macro. Frequently, each state machine and its 
states and pseudostates are encapsulated inside a dedicated source file 
(.c file), from which the RKH_CREATE_SHALLOW_HISTORY_STATE() macro is used.
We will develop one example of shallow history pseudostate definition to 
illustrate the use of this macro. We will give our history pseudostate 
the name \c H1. As will demostrates the use of RKH_CREATE_SHALLOW_HISTORY_STATE() 
macro and its arguments is very similar to RKH_CREATE_COND_STATE() macro.

<b>Defining a shallow history pseudostate</b>
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_SHALLOW_HISTORY_STATE(	H1, 
(3)										6,
(4)										&S1 );
\endcode

<b>Declaring a shallow history pseudostate</b>
\code
//	my.h: state-machine's header file

...
RKH_DCLR_DHIST_STATE H1;
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_SHALLOW_HISTORY_STATE() macro is used.
\li (2)	\c H1 is the pseudostate name. Represents a shallow history 
		pseudostate structure.
\li (3)	\c 6 is the value of pseudostate ID.
\li (6)	\c S1 is the parent state of \c H1.

\b Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h shows the general layout of the configuration file.
Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_SMA_EN_HCAL: \n
	Enable (1) or disable (0) the state nesting. When RKH_SMA_EN_HCAL is set 
	to one (1) some important features of RKH are not included: state 
	composite state, history (shallow and deep) pseudostate, entry action, 
	and exit action. \n\n
- \b RKH_SMA_EN_STATE_ID: \n
	When RKH_SMA_EN_STATE_ID is set to one (1) the state structure includes an 
	ID number. This number allows to uniquely identify a state. \n\n
- \b RKH_SMA_EN_PSEUDOSTATE: \n
	Enable (1) or disable (0) the pseudostates usage. \n\n
- \b RKH_SMA_MAX_TR_SEGS: \n
	Determines the maximum number of linked transition segments. The smaller 
	this number, the lower the static RAM consumption. Typically, the most 
	of hierarchical state machines uses up to 4 transition segments. 
	Currently RKH_SMA_MAX_TR_SEGS cannot exceed 8. \n\n
- \b RKH_EN_SHALLOW_HISTORY: \n
	Enable (1) or disable (0) the shallow history usage.

\n Prev: \ref qref "Quick reference"

<HR>
\section qref5 Defining a deep history pseudostate

\n Prev: \ref qref "Quick reference"

A deep history pseudostate is defined with the 
RKH_CREATE_DEEP_HISTORY_STATE() macro and declared with the 
#RKH_DCLR_DHIST_STATE macro. Frequently, each state machine and its 
states and pseudostates are encapsulated inside a dedicated source file 
(.c file), from which the RKH_CREATE_DEEP_HISTORY_STATE() macro is used.
We will develop one example of deep history pseudostate definition to 
illustrate the use of this macro. We will give our history pseudostate 
the name \c H2. As will demostrates the use of 
RKH_CREATE_DEEP_HISTORY_STATE() macro and its arguments is very 
similar to RKH_CREATE_SHALLOW_HISTORY_STATE() macro.

<b>Defining a deep history pseudostate</b> \n
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_DEEP_HISTORY_STATE(	H1, 
(3)									7,
(4)									&S21 );
\endcode

<b>Declaring a shallow history pseudostate</b>
\code
//	my.h: state-machine's header file

...
RKH_DCLR_DHIST_STATE H1;
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_DEEP_HISTORY_STATE() macro is used.
\li (2)	\c H2 is the pseudostate name. Represents a deep history 
		pseudostate structure.
\li (3)	\c 7 is the value of pseudostate ID.
\li (6)	\c S21 is the parent state of \c H2.

\b Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h shows the general layout of the configuration file.
Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_SMA_EN_HCAL: \n
	Enable (1) or disable (0) the state nesting. When RKH_SMA_EN_HCAL is set 
	to one (1) some important features of RKH are not included: state 
	composite state, history (shallow and deep) pseudostate, entry action, 
	and exit action. \n\n
- \b RKH_SMA_EN_STATE_ID: \n
	When RKH_SMA_EN_STATE_ID is set to one (1) the state structure includes an 
	ID number. This number allows to uniquely identify a state. \n\n
- \b RKH_SMA_EN_PSEUDOSTATE: \n
	Enable (1) or disable (0) the pseudostates usage. \n\n
- \b RKH_SMA_MAX_TR_SEGS: \n
	Determines the maximum number of linked transition segments. The smaller 
	this number, the lower the static RAM consumption. Typically, the most 
	of hierarchical state machines uses up to 4 transition segments. 
	Currently RKH_SMA_MAX_TR_SEGS cannot exceed 8. \n\n
- \b RKH_EN_DEEP_HISTORY: \n
	Enable (1) or disable (0) the deep history usage.

\n Prev: \ref qref "Quick reference"

<HR>
\section qref6 Defining a junction pseudostate

\n Prev: \ref qref "Quick reference"

A conditional pseudostate (also called branch pseudostate) is defined with 
the RKH_CREATE_JUNCTION_STATE() macro and declared with the 
#RKH_DCLR_JUNC_STATE macro. Frequently, each state machine and its 
states and pseudostates are encapsulated inside a dedicated source file 
(.c file), from which the RKH_CREATE_JUNCTION_STATE() macro is used.
We will develop one example of junction pseudostate definition to 
illustrate the use of this macro. We will give our junction pseudostate 
the name \c J1. As will demostrates the use of RKH_CREATE_JUNCTION_STATE() 
macro and its arguments is very similar to RKH_CREATE_BASIC_STATE() macro.

<b>Defining a junction pseudostate</b> \n
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_JUNCTION_STATE( 	J1, 
(3)								8, 
(4)								dis_all_modules, 
(6)								&S1 );
\endcode

<b>Declaring a junction pseudostate</b>
\code
//	my.h: state-machine's header file

...
RKH_DCLR_JUNC_STATE J1;
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_JUNCTION_STATE() macro is used.
\li (2)	\c J1 is the pseudostate name. Represents a junction pseudostate 
		structure.
\li (3)	\c 8 is the value of pseudostate ID.
\li (4)	\c dis_all_modules segment action to be taken. This argument is 
		optional, thus it could be declared as NULL.
\li (5)	\c S1 is the target state.

\b Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_SMA_EN_HCAL: \n
	Enable (1) or disable (0) the state nesting. When RKH_SMA_EN_HCAL is set 
	to one (1) some important features of RKH are not included: state 
	composite state, history (shallow and deep) pseudostate, entry action, 
	and exit action. \n\n
- \b RKH_SMA_EN_STATE_ID: \n
	When RKH_SMA_EN_STATE_ID is set to one (1) the state structure includes an 
	ID number. This number allows to uniquely identify a state. \n\n
- \b RKH_SMA_EN_PSEUDOSTATE: \n
	Enable (1) or disable (0) the pseudostates usage. \n\n
- \b RKH_SMA_MAX_TR_SEGS: \n
	Determines the maximum number of linked transition segments. The smaller 
	this number, the lower the static RAM consumption. Typically, the most 
	of hierarchical state machines uses up to 4 transition segments. 
	Currently RKH_SMA_MAX_TR_SEGS cannot exceed 8. \n\n
- \b RKH_EN_JUNCTION: \n
	Enable (1) or disable (0) the junction connector usage.

\n Prev: \ref qref "Quick reference"

<HR>
\section qref14 Defining entry, exit, and transition actions

\n Prev: \ref qref "Quick reference"

This section summarize the functions and its prototypes used by RKH 
framework. As mentioned before, the framework make use the callbacks, i.e. 
pointer to functions, in most of its data structures by means of 
RKH_SMA_CREATE(), RKH_CREATE_COMP_STATE(), 
RKH_CREATE_BASIC_STATE(), RKH_TRINT(), RKH_TRREG(), RKH_BRANCH(), 
RKH_CREATE_SHALLOW_HISTORY_STATE(), RKH_CREATE_DEEP_HISTORY_STATE(), and 
RKH_CREATE_JUNCTION_STATE() macros.
Obviously, the set of available functions and its configurations 
is mandatory to known for properly using the framework. 

<b>Initialization action</b>

\copydetails RKHINIT_T

As said above, the application must explicitly trigger initial transitions 
in all state machines. The following listing shows the use of 
rkh_sma_activate() function, when it's is called the initial action is 
invoked and the state machine start. The rkh_sma_activate() is a 
platform-dependent function. All RKH ports must be defined in the RKH port 
file to a particular platform. However, only the 
ports to the external OS/RTOS usually need some code to bolt the framework to 
the external OS/RTOS.

\code
// start the manager state machine application
rkh_sma_activate( 	manager, 		// state machine application (SMA)
					qmgr, 			// event storage area for manager SMA
					QMGR_SIZE, 		// size of the storage area
					( void * )0, 	// not used
					0 );			// not used
\endcode

The next listing shows an example of the initial action implementation.

\code
void 
manager_init( const struct rkh_t *sma )
{
	dprint( "Init \"manager\" state machine\n" );
	manager_turnon();	
}
\endcode

<b>Exit action</b>

\copydetails RKHEXT_T

The next listing shows an example of the exit action implementation.

\code
void 
idle_exit( const struct rkh_t *sma )
{
	dprint( "Exit from \"IDLE\" state\n" );
	manager_restore();
}
\endcode

<b>Entry action</b>

\copydetails RKHENT_T

The next listing shows an example of the entry action implementation.

\code
void 
wait_process_entry( const struct rkh_t *sma )
{
	dprint( "Entry to \"WAIT_PROCESS\" state\n" );
	manager_deactivate();
}
\endcode

<b>Transition action</b>

\copydetails RKHACT_T

The next listing shows an example of the transition action implementation.

\code
void 
set_config( const struct rkh_t *sma, RKHEVT_T *pe )
{
	MYEVT_T *e;

	(void)sma;		/* argument not used */
	(void)pe;		/* argument not used */

	e = RKH_ALLOC_EVENT( MYEVT_T, SIX );
	e->ts = ( rkhui16_t )rand();
	rkh_tim_oneshot( &my_timer, sma, MY_TICK );
}
\endcode

<b>Event preprocessor</b>

\copydetails RKHPPRO_T

The next listing shows an example of the event preprocessor 
action implementation.

\code
RKHE_T 
preprocess_keys( const struct rkh_t *sma, RKHEVT_T *pe )
{
    if( pe->e >= 0 && pe->e <= 9 )
        return DECIMAL;
    if( pe->e == '.' )
        return POINT;
    else
        return pe->e;
}
\endcode

<b>Guard</b>

\copydetails RKHGUARD_T

The next listing shows an example of the guard function implementation.

\code
HUInt 
is_zero( const struct rkh_t *sma, RKHEVT_T *pe )
{
	return get_water_level( CHANNEL( (( CHEVT_T* )pe)->ch ) ) == 0;
}
\endcode

\n Prev: \ref qref "Quick reference"

<HR>
\section qref12 Using events with parameters

\n Prev: \ref qref "Quick reference"

An event can have associated parameters, allowing the event 
instance to convey not only the occurrence of some interesting 
incident but also quantitative information regarding that occurrence.
Implementing the single inheritance in C is very simply by literally
embedding the base structure, RKHEVT_T in this case, as the first 
member of the derived structure.
For example, the structure MYEVT_T derived from the base structure 
RKHEVT_T by embedding the RKHEVT_T instance as the first member of 
MYEVT_T.
See also, \ref qref7 section for more information.

\code
typedef struct
{
	RKHEVT_T evt;	// base structure
	int x;			// parameter 'x'
	int y;			// parameter 'y'
} MYEVT_T;
\endcode

Such nesting of structures always aligns the data member 'evt' at the 
beginning of every instance of the derived structure. In particular, this 
alignment lets you treat a pointer to the derived MYEVT_T structure as a 
pointer to the RKHEVT_T base structure. Consequently, you can always 
safely pass a pointer to MYEVT_T to any C function that expects a pointer 
to RKHEVT_T. (To be strictly correct in C, you should explicitly cast this 
pointer. In OOP such casting is called upcasting and is always safe.) 
Therefore, all functions designed for the RKHEVT_T structure are 
automatically available to the MYEVT_T structure as well as other 
structures derived from RKHEVT_T.

The RKH takes the \a 'e' member of RKHEVT_T structure for triggering a 
state transition.

See also rkh_sma_put_fifo(), rkh_sma_put_lifo(), RKH_ALLOC_EVENT(), 
RKH_SET_STATIC_EVENT(), and RKH_GC().

\n Prev: \ref qref "Quick reference"

<HR>
\section qref7 Using dynamic and static events

\n Prev: \ref qref "Quick reference"

In RKH as other frameworks, the actual event instances are either constant 
events (or static events) statically allocated at compile time or dynamic events
allocated at runtime from one of the event pools that the framework manages.

This section includes:

- \ref qref7_1
- \ref qref7_2
- \ref qref7_3
- \ref qref7_4
- \ref qref7_5

\subsection qref7_1 Registering the event pool

Before using dynamic events (or event with arguments) the application code 
must register the proper event pools, which stores the events as a 
fixed-sized memory block. 
Each event pool must be registered with the RKH framework, by means of the 
rkh_epool_register() function. This function initializes one event pool at a 
time and must be called exactly once for each event pool before the pool can 
be used.

The application code might initialize the event pools by making calls 
to the rkh_epool_register() function. However, for the simplicity of 
the internal implementation, the application code initialize event pools 
in the ascending order of the event size.

\code
#define SIZEOF_EP0STO				64
#define SIZEOF_EP0_BLOCK			sizeof( TOUT_T )

#define SIZEOF_EP1STO				32
#define SIZEOF_EP1_BLOCK			sizeof( DIAL_T )

#define SIZEOF_EP2STO				32
#define SIZEOF_EP2_BLOCK			sizeof( SETUP_T )

typedef struct
{
	RKHEVT_T evt;                   // base structure
	int timerno;					// parameter 'timerno'
} TOUT_T;

typedef struct
{
	RKHEVT_T evt;                   // base structure
	char dial[ MAX_SIZE_DIAL ];     // parameter 'dial'
	int qty;                        // parameter 'qty'
} DIAL_T;
	
typedef struct
{
	RKHEVT_T evt;                   // base structure
	int volume;                     // parameter 'volume'
	int baud_rate;                  // parameter 'baud_rate'
	char name[ MAX_SIZE_NAME ];     // parameter 'name'
	int iloop;                      // parameter 'iloop'
} SETUP_T;

// declares the storage memory of event pool
static rkhui8_t	ep0sto[ SIZEOF_EP0STO ],
				ep1sto[ SIZEOF_EP1STO ],
				ep2sto[ SIZEOF_EP2STO ];

...
rkh_epool_register( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
rkh_epool_register( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
rkh_epool_register( ep2sto, SIZEOF_EP2STO, SIZEOF_EP2_BLOCK  );
...
\endcode

\subsection qref7_2 Allocating events

\code
(1)	typedef struct
	{
		RKHEVT_T evt;					// base structure
		char dial[ MAX_SIZE_DIAL ];		// parameter 'dial'
		int qty;						// parameter 'qty'
	} DIAL_T;

(2)	typedef struct
	{
		RKHEVT_T evt;					// base structure
		int volume;						// parameter 'volume'
		int baud_rate;					// parameter 'baud_rate'
		char name[ MAX_SIZE_NAME ];		// parameter 'name'
		int iloop;						// parameter 'iloop'
	} SETUP_T;

	typedef struct
	{
		RKHEVT_T evt;
		int timerno;
	} TOUT_T;

(3) static RKH_DCLR_STATIC_EVENT( offh, OFFHOOK );
(4) static TOUT_T tout;

...

(5) RKH_SET_STATIC_EVENT( &tout, TIMEOUT );
(6)	DIAL_T *de = RKH_ALLOC_EVENT( DIAL_T, DIALED );
(7)	SETUP_T *se = RKH_ALLOC_EVENT( SETUP_T, SET_CONFIG );
(8)	se->volume = 0;
	se->baud_rate = DEFAULT_BAUD_RATE;
	se->iloop = 2;
\endcode

Explanation

\li (1-2)	As mentioned before, implementing the single inheritance in C is 
			very simply by literally embedding the base structure, RKHEVT_T 
			in this case, as the first member of the derived structure, 
			\c DIAL_T and \c SETUP_T.
\li (3)		The \c OFFHOOK event never changes, so it can be statically 
			allocated just once. This event is declared as const, which 
			means that it can be placed in ROM. The initializer list for 
			this event consists of the signal \c OFFHOOK followed by zero. 
			This zero informs the RKH framework that this event is 
			<em>static</em> and should never be recycled to an event pool.
\li	(4)		The <c>TIMEOUT( timerno )</c> event is an example of an event with 
			changing parameters. In general, such an event cannot be allocated 
			in ROM like the \c OFFHOOK event because it can change. 
\li (5)		This macro set the event <c>TIMEOUT( timerno )</c> with \c TIMEOUT 
			signal and establishes it as one <em>static event</em>.
\li (6-7) 	The RKH_ALLOC_EVENT() macro dynamically creates a new instances 
			events of type \c DIAL_T and \c SETUP_T with \c DIALED and 
			\c SET_CONFIG signals. These events are represented like this:
			<c>DIALED( dial, qty )</c> and 
			<c> SET_CONFIG( volume, baud_rate, name, iloop )</c>
			This macro returns a pointer to the event already cast to the 
			required event type.
\li (8) 	The \c volume, \c baud_rate, and \c iloop parameters of the event 
			are assigned.

Just one another example that it could be used to easily debug an application 
with static events.

\code
typedef struct
{
	RKHEVT_T evt;
#if SYSEVT_DEBUG == 1
	char *name;
#endif
} SYSEVT_T;

#if SYSEVT_DEBUG == 1
	#define mkse( e, n )		{ { (e), 0, 0 }, (n) }
#else
	#define mkse( e, n )		{ { (e), 0, 0 } }
#endif

static const SYSEVT_T sysevts[] =
{
	mkse( OFFHOOK,	"offhook" ),
	mkse( ONHOOK, 	"onhook" ),
	mkse( POLREV, 	"polarity reversal" ),
	mkse( BTONE,	"billing tone" ),
	...
};
\endcode

\subsection qref7_3 Posting events

The RKH framework supports one type of asynchronous event exchange: the 
simple mechanism of direct event posting supported through the functions
rkh_sma_post_fifo() and rkh_sma_post_lifo(), when the producer of an event 
directly posts the event to the event queue of the consumer SMA 
(active object).

\code
(1) static RKH_DCLR_STATIC_EVENT( eterm, TERM );
...

(2)	rkh_sma_post_fifo( manager, &eterm );
\endcode

\li (1)	Declares and initializes the event \a eterm with \a TERM 
		signal and establishes it as one static event.
\li (2)	The \c eterm event is sent directly to the \c manager SMA.

\code
...
(1) mye = RKH_ALLOC_EVENT( MYEVT_T, kbmap( c ) );
(2) mye->ts = ( rkhui16_t )rand();
(3) rkh_sma_post_fifo( my, ( RKHEVT_T* )mye );
\endcode

\li (1)	Dynamically creates a new event \c mye of type \a MYEVT_T with 
		the signal returned from the kbmap() function.
\li (2) Use the extended members of the event \c mye.
\li (3) The \c mye event is sent directly to the \c my SMA.

\subsection qref7_4 Recycling dynamic events

If the system make use of dynamic events facility after the processing, 
you must not forget to call the RKH garbage collector, because now RKH is 
no longer in charge of event processing and you are solely responsible for 
not leaking the event.
The garbage collector actually recycles the event only when it determines 
that the event is no longer referenced.
The following listing illustrates how and when to invoke RKH_GC() macro 
to recycle "dynamic" events.

\code
	void 
	rkh_enter( void )
    {
		rkhui8_t prio;
		RKHSMA_T *sma;
		RKHEVT_T *e;

		rkh_hk_start();
		RKH_TR_FWK_EN();

		FOREVER
		{
			RKH_DIS_INTERRUPT();
			if( rkh_rdy_isnot_empty( rkhrg ) )
			{
				rkh_rdy_findh( rkhrg, prio );
				sma = rkh_sptbl[ prio ];
				RKH_ENA_INTERRUPT();

(1)				e = rkh_sma_get( sma );
(2)				rkh_dispatch( sma, e );
(3)				RKH_GC( e );
			}
			else 
			//
			// rkh_hk_idle() must be called with interrupts DISABLED because the 
			// determination of the idle condition (no events in the queues) can 
			// change at any time by an interrupt posting events to a queue. The 
			// rkh_hk_idle() MUST enable interrups internally, perhaps at the 
			// same time as putting the CPU into a power-saving mode.
			//			
				rkh_hk_idle();
		}
    }
\endcode

\li (1)	An event \c e is get from the SMA queue with the highest priority.
\li (2)	The event \c e is dispatched to the current SMA.
\li	(2) Thus, the event \c e is passed to the RKH garbage collector for 
		recycling. As described above, the RKH_GC() macro actually recycles 
		the wvent only when it determines that the event is no longer 
		referenced.

\subsection qref7_5 Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h shows the general layout of the configuration file.
Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_EN_DYNAMIC_EVENT: \n \copydetails RKH_EN_DYNAMIC_EVENT
- \b RKH_MAX_EPOOL: \n \copydetails RKH_MAX_EPOOL
- \b RKH_SIZEOF_EVENT: \n \copydetails RKH_SIZEOF_EVENT
- \b RKH_SIZEOF_ESIZE: \n \copydetails RKH_SIZEOF_ESIZE
- \b RKH_EN_NATIVE_DYN_EVENT: \n \copydetails RKH_EN_NATIVE_DYN_EVENT
- \b RKH_DYNE_TYPE: \n \copydetails RKH_DYNE_TYPE
- \b RKH_DYNE_INIT: \n \copydetails RKH_DYNE_INIT
- \b RKH_DYNE_GET_ESIZE: \n \copydetails RKH_DYNE_GET_ESIZE
- \b RKH_DYNE_GET: \n \copydetails RKH_DYNE_GET
- \b RKH_DYNE_PUT: \n \copydetails RKH_DYNE_PUT

\n Prev: \ref qref "Quick reference"

<HR>
\section qref13 Preprocessing events before of dispatch it

\n Prev: \ref qref "Quick reference"

\copydetails RKHPPRO_T

The next listing shows an example of the event preprocessor 
action implementation.

\code
RKHE_T 
preprocess_keys( const struct rkh_t *sma, RKHEVT_T *pe )
{
	printf( "From state machine \"%s\"\n", rkh_get_sm_name( sma ) );
    if( pe->e >= 0 && pe->e <= 9 )
        return DECIMAL;
    if( pe->e == '.' )
        return POINT;
    else
        return pe->e;
}
\endcode

\n Prev: \ref qref "Quick reference"

<HR>
\section qref8 Deferring and recalling events

\n Prev: \ref qref "Quick reference"

Event deferral comes in very handy when an event arrives in a 
particularly inconvenient moment but can be deferred for some later time, 
when the system is in a much better position to handle the event. RKH 
supports very efficient event deferring and recalling mechanisms.
This function is part of the event deferral mechanism. An SMA 
uses this function to defer an event \a e to the event queue \a q. 
RKH correctly accounts for another outstanding reference to the event 
and will not recycle the event at the end of the RTC step. 
Later, the SMA might recall one event at a time from the 
event queue by means of rkh_recall(sma,q) function. 
Recalling an event means that it is removed from the deferred event 
queue \c q and posted (LIFO) to the event queue of the \c sma state 
machine application.

This section includes:

- \ref qref8_1
- \ref qref8_2

\subsection qref8_1 Deferring an event

\code
static RKHRQ_T qurc;
static RKHEVT_T *qurc_sto[ MAX_SIZEOF_QURC ];

(1) rkh_rq_init( &qurc, qurc_sto, MAX_SIZEOF_QURC, NULL );
...

void 
ring( const struct rkh_t *sma, RKHEVT_T *pe )
{
	(void)sma;      				// argument not used
(2)	rkh_defer( &qurc, pe );
}
\endcode

Explanation

\li (1)	Initialize the \c qurc queue to be used as deferred queue. 
\li (1)	Defers the event \c pe to the previously created event queue \c qurc. 

\subsection qref8_2 Recalling an event

\code
void 
exit_rx_manager( const struct rkh_t *sma )
{
(1)	rkh_defer( sma, &qurc );
}
\endcode

Explanation

\li (1)	Removes an event from the deferred event queue \c qurc and posts (LIFO) 
		to the event queue of the \c sma state machine application.

\n Prev: \ref qref "Quick reference"

<HR>
\section qref9 Using assertions

\n Prev: \ref qref "Quick reference"

\copydetails rkhassert.h

\n Prev: \ref qref "Quick reference"

<HR>
\section qref10 Debugging an application based on RKH's state machines

\n Prev: \ref qref "Quick reference"

Please refer to \ref dbg section. 

\n Prev: \ref qref "Quick reference"

<HR>
\section qref15 Initializing a state machine and dispatching events

\n Prev: \ref qref "Quick reference"

The following listing shows an very simple example of the main() function 
implementation and demostrates how to use the RKH API.

\note
See \ref Usage "Representing a state machine: step by step" section 
for more information about this.

\code
	...
	typedef struct
	{
		RKHEVT_T event;
		rkhuint16 ts;
	} MYEVT_T;

	static MYEVT_T mye;
	...

	int
	main( int argc, char *argv[] )
	{
		int c;

(1)		rkh_trc_open();
(2)		rkh_init();

		srand( ( unsigned )time( NULL ) );
(3)  	rkh_init_hsm( my );

(4)		FOREVER
		{
(5)			c = mygetch();
			
			if( c == 'p' )
(6)				rkh_trc_flush();
			else if ( c == ESC )
			{
(7)				rkh_dispatch( my, &term );
				break;
			}
			else
			{
(8)				mye = RKH_ALLOC_EVENT( MYEVT_T, kbmap( c ) );
(9)				mye->ts = ( rkhui16_t )rand();
(10)			rkh_dispatch( my, ( RKHEVT_T* )mye );
			}
		}

(11)	rkh_trc_close();
(12)	rkh_exit();
	}
\endcode

\li (1) Open the trace session.
\li (2) Initialize the framework RKH.
\li (3) Initialize the \c my state machine. 
		RKH invokes the defined init action.
\li (4) This is the event loop of the framework RKH.
\li (5) Gets key pressed from the standard input.
\li (6) Flush the trace stream.
\li (7) Send the \c term event to \c my state machine to terminate. 
		After that, terminates the program.
\li (8) Allocates an event of \c MYEVT_T type (derived from RKHEVT_T) to 
		store the key pressed.
\li (9)	The	event has associated parameters that convey a random number.
\li (10) The \c mye event is dispatched to \c my state machine. Events with 
		parameters, such as the MYEVT_T, require explicit casting from the 
		generic base structure #RKHEVT_T to the specific derived structure 
		MYEVT_T.
\li (11-12) Close the trace session and terminates the program.

<HR>
\section qref18 Using RKH software timers

\n Prev: \ref qref "Quick reference" \n

\copydetails rkhtim.h

This section includes:

- \ref qref18_1
- \ref qref18_2
- \ref qref18_3

\subsection qref18_1 Declaring, and initializing a timer

\code
...
(1) static RKHT_T tlayer;

	void
(2)	tlayer_tout( void *t )
	{
		(void)t;
		close_layer();
	}

(3)	rkh_tim_init( 	&tlayer, 
(4)					TOUT, 
(5)					tlayer_tout );
...
\endcode

Explanation

\li (1)	Declares and allocates the \c tlayer timer. 
\li (2)	Defines \c tlayer_tout() hook function, which is calls at the 
		\c tlayer expiration.
\li (3)	Initializes the \c tlayer timer. 
\li (4)	\c TOUT is the signal of the event to be directly posted (using the 
		FIFO policy) into the event queue of the target agreed state machine 
		application at the timer expiration.
\li (5) Registers \c tlayer_tout() hook function.

\subsection qref18_2 Start and stop timers

\code
(1)	#define TPWR_TICK			100
(2)	#define TKEY_TICK			100
...
(3) static RKHT_T 	tpwr,
(4) 				tkey;

(5)	rkh_tim_init( &tpwr, TPWR, NULL );
(6)	rkh_tim_init( &tkey, TKEY, NULL );
...
(7) rkh_tim_oneshot( &tpwr, pwr, TPWR_TICK );
(8) rkh_tim_periodic( &tkey, pwr, TKEY_TICK, TKEY_TICK/4 );
...
(9) rkh_tim_stop( &tkey );
...
(10)rkh_tim_restart( &tpwr, TPWR_TICK * 2 );
\endcode

Explanation

\li (1-2)	Defines the number of ticks for timer expiration. 
\li (3-4)	Declares and allocates the \c tpwr, and \c tkey timers. 
\li (5-6)	Initializes the \c tpwr, and \c tkey timers. 
\li (7)	Starts \c tpwr timer as one-shot timer, which posts the signal 
		\c TPWR to 	\c pwr state machine application after TPWR_TICK 
		timer-ticks.
\li (8)	Starts \c tkey timer as periodic timer, which posts the signal 
		\c TKEY to \c pwr state machine application after TKEY_TICK 
		timer-ticks initially and then after every TKEY_TICK/4 timer-ticks.
\li (9) Stops \c tkey timer. 
\li (10) Restarts \c tpwr timer with a new number of ticks. 

\subsection qref18_3 Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h shows the general layout of the configuration file.
Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_TIM_EN: \n \copydetails RKH_TIM_EN
- \b RKH_TIM_SIZEOF_NTIMER: \n \copydetails RKH_TIM_SIZEOF_NTIMER
- \b RKH_TIM_EN_HOOK: \n \copydetails RKH_TIM_EN_HOOK
- \b RKH_TIM_EN_RESTART: \n \copydetails RKH_TIM_EN_RESTART
- \b RKH_TIM_EN_GET_INFO: \n \copydetails RKH_TIM_EN_GET_INFO

Prev: \ref main_page "Home"

\page dbg Tracing tool
\image html rkh_bunner.jpg

Prev: \ref main_page "Home" \n
Next: \ref Download "Download"

\copydetails rkhtrc.h

\n This section includes:

- \ref tre
- \ref trcfg
- \ref trfn
- \ref trfil
- \ref trtbl
- \ref trtrazer

<HR>
\section tre Trace event structure
\copydetails RKH_TRC_EVENTS

<HR>
\section trcfg Trace tool configuration

First of all, RKH has a set of configuration options related to trace tool 
facility, which an user that require this feature must be properly configure 
in the \b rkhcfg.h header file.

\li Define the macro \b RKH_TRC_EN \copydetails RKH_TRC_EN
\li Define the macro \b RKH_TRC_MAX_EVENTS \copydetails RKH_TRC_MAX_EVENTS
\li Define the macro \b RKH_TRC_RUNTIME_FILTER \copydetails RKH_TRC_RUNTIME_FILTER
\li Define the macro \b RKH_TRC_ALL \copydetails RKH_TRC_ALL
\li Define the macro \b RKH_TRC_EN_MP \copydetails RKH_TRC_EN_MP
\li Define the macro \b RKH_TRC_EN_RQ \copydetails RKH_TRC_EN_RQ
\li Define the macro \b RKH_TRC_EN_SMA \copydetails RKH_TRC_EN_SMA
\li Define the macro \b RKH_TRC_EN_TIM \copydetails RKH_TRC_EN_TIM
\li Define the macro \b RKH_TRC_EN_SM \copydetails RKH_TRC_EN_SM
\li Define the macro \b RKH_TRC_EN_RKH \copydetails RKH_TRC_EN_RKH
\li Define the macro \b RKH_TRC_EN_SM_INIT \copydetails RKH_TRC_EN_SM_INIT
\li Define the macro \b RKH_TRC_EN_SM_DCH \copydetails RKH_TRC_EN_SM_DCH
\li Define the macro \b RKH_TRC_EN_SM_CLRH \copydetails RKH_TRC_EN_SM_CLRH
\li Define the macro \b RKH_TRC_EN_SM_TRN \copydetails RKH_TRC_EN_SM_TRN
\li Define the macro \b RKH_TRC_EN_SM_STATE \copydetails RKH_TRC_EN_SM_STATE
\li Define the macro \b RKH_TRC_EN_SM_ENSTATE \copydetails RKH_TRC_EN_SM_ENSTATE
\li Define the macro \b RKH_TRC_EN_SM_EXSTATE \copydetails RKH_TRC_EN_SM_EXSTATE
\li Define the macro \b RKH_TRC_EN_SM_NENEX \copydetails RKH_TRC_EN_SM_NENEX
\li Define the macro \b RKH_TRC_EN_SM_NTRNACT \copydetails RKH_TRC_EN_SM_NTRNACT
\li Define the macro \b RKH_TRC_EN_SM_CSTATE \copydetails RKH_TRC_EN_SM_CSTATE
\li Define the macro \b RKH_TRC_EN_NSEQ \copydetails RKH_TRC_EN_NSEQ
\li Define the macro \b RKH_TRC_EN_CHK \copydetails RKH_TRC_EN_CHK
\li Define the macro \b RKH_TRC_EN_TSTAMP \copydetails RKH_TRC_EN_TSTAMP
\li Define the macro \b RKH_TRC_SIZEOF_TSTAMP \copydetails RKH_TRC_SIZEOF_TSTAMP
\li Define the macro \b RKH_TRC_SIZEOF_STREAM \copydetails RKH_TRC_SIZEOF_STREAM
\li Define the macro \b RKH_TRC_SIZEOF_POINTER \copydetails RKH_TRC_SIZEOF_POINTER

See \ref cfg section for more information about that.

<HR>
\section trfn Implementing the trace session support

For using the native trace facility the user should implement several 
functions which are platform and application specific. These function 
prototypes are definied within \b rkh.h file and listed below:

\li \b rkh_trc_open() \copydetails RKH_TRC_OPEN

\li \b rkh_trc_close() \copydetails RKH_TRC_CLOSE

\li \b rkh_trc_flush() \copydetails RKH_TRC_FLUSH

\li \b rkh_trc_getts() \copydetails rkh_trc_getts

<HR>
\section trfil Using runtime trace filters

Also, the streams support runtime filtering. The application can define and 
apply a filter to a trace stream. Basically, the filter establishes which 
event types the stream is accepting (and hence storing) and which are not.
Therefore, trace events corresponding to types which are filtered out 
from the stream will not be stored in the stream. The stream in the 
system can potentially be applied a different filters. This filter can be 
applied, removed or changed at any time. A filter could be applied either 
specific trace event or all events from a specific group.

<EM>Emit or suppress all trace events from a specific group</EM>

The stream is initially created with an empty filter (that is, without 
filtering any event type). If this is not the required behavior, the 
application can build a set of event types, include the appropriate event 
types in it, and apply it as a filter to the stream. After that, the 
stream will reject any event whose type is in the filter set.

Gathering many events generates a lot of data, which requires memory and 
processor time. It also makes the task of interpreting the data more 
difficult. Because the amount of data that the instrumented framework 
generates can be overwhelming, the RKH supports several types of filters 
that can use it to reduce the amount of data to be processed. The available 
groups are enumerated in #RKH_TRC_GROUPS.

Please use RKH_FILTER_ON_GROUP(), or RKH_FILTER_OFF_GROUP() macros to do 
that.

Example:
 	
\code
void
some_function( ... )
{
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
	...
}
\endcode

<EM>Emit or suppress a specific event</EM>

The stream is initially created with an empty filter (that is, without 
filtering any event type). If this is not the required behavior, the 
application can build a set of event types, include the appropriate event 
types in it, and apply it as a filter to the stream. After that, the 
stream will reject any event whose type is in the filter set.

Gathering many events generates a lot of data, which requires memory and 
processor time. It also makes the task of interpreting the data more 
difficult. Because the amount of data that the instrumented framework 
generates can be overwhelming, the RKH supports several types of filters 
that can use it to reduce the amount of data to be processed. The available 
events are enumerated in #RKH_TRC_EVENTS.

Please use RKH_FILTER_ON_EVENT(), or RKH_FILTER_OFF_EVENT() macros to do 
that.

Example:
 	
\code
void
some_function( ... )
{
	RKH_FILTER_OFF_EVENT( RKH_TE_MP_INIT );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_DCH );
	RKH_FILTER_OFF_EVENT( RKH_TE_FWK_OBJ );
	RKH_FILTER_OFF_EVENT( RKH_TE_FWK_SIG );
	RKH_FILTER_OFF_EVENT( RKH_TE_TIM_START );
	RKH_FILTER_OFF_EVENT( RKH_TE_TIM_TOUT );
	...
}
\endcode

<HR>
\section trtbl Trace event table

This section provides a table that lists all the trace events and summarizes 
the data included for each. 

<EM>Memory Pool (MP)</EM>

\li \b RKH_TR_MP_INIT \copydetails RKH_TR_MP_INIT
\li \b RKH_TR_MP_GET \copydetails RKH_TR_MP_GET
\li \b RKH_TR_MP_PUT \copydetails RKH_TR_MP_PUT

<EM>Queue (RQ)</EM>

\li \b RKH_TR_RQ_INIT \copydetails RKH_TR_RQ_INIT
\li \b RKH_TR_RQ_GET \copydetails RKH_TR_RQ_GET
\li \b RKH_TR_RQ_FIFO \copydetails RKH_TR_RQ_FIFO
\li \b RKH_TR_RQ_LIFO \copydetails RKH_TR_RQ_LIFO
\li \b RKH_TR_RQ_FULL \copydetails RKH_TR_RQ_FULL
\li \b RKH_TR_RQ_DEPLETE \copydetails RKH_TR_RQ_DEPLETE
\li \b RKH_TR_RQ_GET_LAST \copydetails RKH_TR_RQ_GET_LAST

<EM>State Machine Application (SMA)</EM>

\li \b RKH_TR_SMA_ACT \copydetails RKH_TR_SMA_ACT
\li \b RKH_TR_SMA_TERM \copydetails RKH_TR_SMA_TERM
\li \b RKH_TR_SMA_GET \copydetails RKH_TR_SMA_GET
\li \b RKH_TR_SMA_FIFO \copydetails RKH_TR_SMA_FIFO
\li \b RKH_TR_SMA_LIFO \copydetails RKH_TR_SMA_LIFO
\li \b RKH_TR_SMA_REG \copydetails RKH_TR_SMA_REG
\li \b RKH_TR_SMA_UNREG \copydetails RKH_TR_SMA_UNREG

<EM>State machine (SM)</EM>

\li \b RKH_TR_SM_INIT \copydetails RKH_TR_SM_INIT
\li \b RKH_TR_SM_DCH \copydetails RKH_TR_SM_DCH
\li \b RKH_TR_SM_CLRH \copydetails RKH_TR_SM_CLRH
\li \b RKH_TR_SM_TRN \copydetails RKH_TR_SM_TRN
\li \b RKH_TR_SM_STATE \copydetails RKH_TR_SM_STATE
\li \b RKH_TR_SM_ENSTATE \copydetails RKH_TR_SM_ENSTATE
\li \b RKH_TR_SM_EXSTATE \copydetails RKH_TR_SM_EXSTATE
\li \b RKH_TR_SM_NENEX \copydetails RKH_TR_SM_NENEX
\li \b RKH_TR_SM_NTRNACT \copydetails RKH_TR_SM_NTRNACT
\li \b RKH_TR_SM_CSTATE \copydetails RKH_TR_SM_CSTATE
\li \b RKH_TR_SM_EVT_PROC \copydetails RKH_TR_SM_EVT_PROC
\li \b RKH_TR_SM_EVT_NFOUND \copydetails RKH_TR_SM_EVT_NFOUND 
\li \b RKH_TR_SM_GRD_FALSE \copydetails RKH_TR_SM_GRD_FALSE 
\li \b RKH_TR_SM_CND_NFOUND \copydetails RKH_TR_SM_CND_NFOUND 
\li \b RKH_TR_SM_UNKN_STATE \copydetails RKH_TR_SM_UNKN_STATE 
\li \b RKH_TR_SM_EX_HLEVEL \copydetails RKH_TR_SM_EX_HLEVEL 
\li \b RKH_TR_SM_EX_TSEG \copydetails RKH_TR_SM_EX_TSEG 

<EM>Timer (TIM)</EM>

\li \b RKH_TR_TIM_INIT \copydetails RKH_TR_TIM_INIT
\li \b RKH_TR_TIM_START \copydetails RKH_TR_TIM_START
\li \b RKH_TR_TIM_RESTART \copydetails RKH_TR_TIM_RESTART
\li \b RKH_TR_TIM_STOP \copydetails RKH_TR_TIM_STOP
\li \b RKH_TR_TIM_TOUT \copydetails RKH_TR_TIM_TOUT
\li \b RKH_TR_TIM_REM \copydetails RKH_TR_TIM_REM

<EM>Framework (RKH)</EM>

\li \b RKH_TR_FWK_EN \copydetails RKH_TR_FWK_EN
\li \b RKH_TR_FWK_EX \copydetails RKH_TR_FWK_EX
\li \b RKH_TR_FWK_EPREG \copydetails RKH_TR_FWK_EPREG
\li \b RKH_TR_FWK_AE \copydetails RKH_TR_FWK_AE
\li \b RKH_TR_FWK_GC \copydetails RKH_TR_FWK_GC
\li \b RKH_TR_FWK_GCR \copydetails RKH_TR_FWK_GCR
\li \b RKH_TR_FWK_DEFER \copydetails RKH_TR_FWK_DEFER
\li \b RKH_TR_FWK_RCALL \copydetails RKH_TR_FWK_RCALL
\li \b RKH_TE_FWK_OBJ \copydetails RKH_TE_FWK_OBJ
\li \b RKH_TE_FWK_SIG \copydetails RKH_TE_FWK_SIG
\li \b RKH_TE_FWK_FUN \copydetails RKH_TE_FWK_FUN
\li \b RKH_TE_FWK_EXE_FUN \copydetails RKH_TE_FWK_EXE_FUN

<EM>Symbol entry table for objects</EM>

\li \b RKH_TR_FWK_OBJ \copydetails RKH_TR_FWK_OBJ

<EM>Symbol entry table for event signals</EM>

\li \b RKH_TR_FWK_SIG \copydetails RKH_TR_FWK_SIG

<HR>
\section trtrazer TRAZER - The fundamental RKH's tracing tool

Trazer is a visualization tool that works in conjuntion with the RKH 
framework built in trace facility. Trazer gives the possibility to display 
selectively the recording of all events of your system, state machines, 
queues, timers, etc.
Trazer helps you to faster troubleshooting especially on complex problems 
where a debugger is not sufficient, by providing a simple consolidated, 
human-readable textual output.

Given the RKH cross plataform portability, trace data may come from 8, 
16, or 32-bits platforms. In order to that Trazer need to be configured 
to support this diversity of plataform and the wide range of RKH framework 
configurations. 

Here is the \ref trazer

\page cfg Configuration
\image html rkh_bunner.jpg

Prev: \ref main_page "Home" \n
Next: \ref Usage "Representing a state machine: step by step"

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\b rkhcfg.h file shows the general layout of the configuration file.
Here is an list of all options with their documentation:

\n This section includes:

- \ref cfg_fw
- \ref cfg_sm
- \ref cfg_tr
- \ref cfg_q
- \ref cfg_mp
- \ref cfg_t

<HR>
\section cfg_fw Configuration options related to framework

\li \b RKH_MAX_SMA \copydetails RKH_MAX_SMA
\li \b RKH_EN_DYNAMIC_EVENT \copydetails RKH_EN_DYNAMIC_EVENT
\li \b RKH_MAX_EPOOL \copydetails RKH_MAX_EPOOL
\li \b RKH_SIZEOF_EVENT \copydetails RKH_SIZEOF_EVENT
\li \b RKH_SIZEOF_ESIZE \copydetails RKH_SIZEOF_ESIZE
\li \b RKH_EN_DEFERRED_EVENT \copydetails RKH_EN_DEFERRED_EVENT
\li \b RKH_ASSERT_EN \copydetails RKH_ASSERT_EN
\li \b RKH_HK_EN_DISPATCH \copydetails RKH_HK_EN_DISPATCH
\li \b RKH_HK_EN_SIGNAL \copydetails RKH_HK_EN_SIGNAL
\li \b RKH_HK_EN_TIMEOUT \copydetails RKH_HK_EN_TIMEOUT
\li \b RKH_HK_EN_START \copydetails RKH_HK_EN_START
\li \b RKH_HK_EN_EXIT \copydetails RKH_HK_EN_EXIT
\li \b RKH_SMA_EN_IEVENT \copydetails RKH_SMA_EN_IEVENT
\li \b RKH_EN_SMA_THREAD \copydetails RKH_EN_SMA_THREAD
\li \b RKH_EN_SMA_THREAD_DATA \copydetails RKH_EN_SMA_THREAD_DATA
\li \b RKH_EN_NATIVE_SCHEDULER \copydetails RKH_EN_NATIVE_SCHEDULER
\li \b RKH_EN_NATIVE_EQUEUE \copydetails RKH_EN_NATIVE_EQUEUE
\li \b RKH_EN_NATIVE_DYN_EVENT \copydetails RKH_EN_NATIVE_DYN_EVENT
\li \b RKH_EN_REENTRANT \copydetails RKH_EN_REENTRANT

<HR>
\section cfg_sm Configuration options related to state machine applications

\li \b RKH_SMA_EN_ID \copydetails RKH_SMA_EN_ID
\li \b RKH_SMA_EN_GET_INFO \copydetails RKH_SMA_EN_GET_INFO	
\li \b RKH_SMA_EN_STATE_ID \copydetails RKH_SMA_EN_STATE_ID	
\li \b RKH_SMA_EN_PPRO \copydetails RKH_SMA_EN_PPRO	
\li \b RKH_SMA_EN_HCAL \copydetails RKH_SMA_EN_HCAL	
\li \b RKH_SMA_MAX_HCAL_DEPTH \copydetails RKH_SMA_MAX_HCAL_DEPTH
\li \b RKH_SMA_MAX_TRC_SEGS \copydetails RKH_SMA_MAX_TRC_SEGS
\li \b RKH_SMA_EN_PSEUDOSTATE \copydetails RKH_SMA_EN_PSEUDOSTATE
\li \b RKH_SMA_EN_DEEP_HISTORY \copydetails RKH_SMA_EN_DEEP_HISTORY	
\li \b RKH_SMA_EN_SHALLOW_HISTORY \copydetails RKH_SMA_EN_SHALLOW_HISTORY
\li \b RKH_SMA_EN_JUNCTION \copydetails RKH_SMA_EN_JUNCTION	
\li \b RKH_SMA_EN_CONDITIONAL \copydetails RKH_SMA_EN_CONDITIONAL
\li \b RKH_SMA_EN_SUBMACHINE \copydetails RKH_SMA_EN_SUBMACHINE
\li \b RKH_SMA_EN_INIT_ARG_SMA \copydetails RKH_SMA_EN_INIT_ARG_SMA
\li \b RKH_SMA_EN_ENT_ARG_SMA \copydetails RKH_SMA_EN_ENT_ARG_SMA
\li \b RKH_SMA_EN_EXT_ARG_SMA \copydetails RKH_SMA_EN_EXT_ARG_SMA
\li \b RKH_SMA_EN_ACT_ARG_SMA \copydetails RKH_SMA_EN_ACT_ARG_SMA
\li \b RKH_SMA_EN_ACT_ARG_EVT \copydetails RKH_SMA_EN_ACT_ARG_EVT
\li \b RKH_SMA_EN_GRD_ARG_EVT \copydetails RKH_SMA_EN_GRD_ARG_EVT
\li \b RKH_SMA_EN_GRD_ARG_SMA \copydetails RKH_SMA_EN_GRD_ARG_SMA
\li \b RKH_SMA_EN_PPRO_ARG_SMA \copydetails RKH_SMA_EN_PPRO_ARG_SMA

<HR>
\section cfg_tr Configuration options related to trace facility

\li \b RKH_TRC_EN \copydetails RKH_TRC_EN
\li \b RKH_TRC_MAX_EVENTS \copydetails RKH_TRC_MAX_EVENTS
\li \b RKH_TRC_RUNTIME_FILTER \copydetails RKH_TRC_RUNTIME_FILTER
\li \b RKH_TRC_ALL \copydetails RKH_TRC_ALL
\li \b RKH_TRC_EN_MP \copydetails RKH_TRC_EN_MP
\li \b RKH_TRC_EN_RQ \copydetails RKH_TRC_EN_RQ
\li \b RKH_TRC_EN_SMA \copydetails RKH_TRC_EN_SMA
\li \b RKH_TRC_EN_TIM \copydetails RKH_TRC_EN_TIM
\li \b RKH_TRC_EN_SM \copydetails RKH_TRC_EN_SM
\li \b RKH_TRC_EN_RKH \copydetails RKH_TRC_EN_RKH
\li \b RKH_TRC_EN_SM_INIT \copydetails RKH_TRC_EN_SM_INIT
\li \b RKH_TRC_EN_SM_DCH \copydetails RKH_TRC_EN_SM_DCH
\li \b RKH_TRC_EN_SM_CLRH \copydetails RKH_TRC_EN_SM_CLRH
\li \b RKH_TRC_EN_SM_TRN \copydetails RKH_TRC_EN_SM_TRN
\li \b RKH_TRC_EN_SM_STATE \copydetails RKH_TRC_EN_SM_STATE
\li \b RKH_TRC_EN_SM_ENSTATE \copydetails RKH_TRC_EN_SM_ENSTATE
\li \b RKH_TRC_EN_SM_EXSTATE \copydetails RKH_TRC_EN_SM_EXSTATE
\li \b RKH_TRC_EN_SM_NENEX \copydetails RKH_TRC_EN_SM_NENEX
\li \b RKH_TRC_EN_SM_NTRNACT \copydetails RKH_TRC_EN_SM_NTRNACT
\li \b RKH_TRC_EN_SM_CSTATE \copydetails RKH_TRC_EN_SM_CSTATE
\li \b RKH_TRC_EN_SM_PROCESS \copydetails RKH_TRC_EN_SM_PROCESS
\li \b RKH_TRC_EN_NSEQ \copydetails RKH_TRC_EN_NSEQ
\li \b RKH_TRC_EN_CHK \copydetails RKH_TRC_EN_CHK
\li \b RKH_TRC_EN_TSTAMP \copydetails RKH_TRC_EN_TSTAMP
\li \b RKH_TRC_SIZEOF_TSTAMP \copydetails RKH_TRC_SIZEOF_TSTAMP
\li \b RKH_TRC_SIZEOF_STREAM \copydetails RKH_TRC_SIZEOF_STREAM
\li \b RKH_TRC_SIZEOF_POINTER \copydetails RKH_TRC_SIZEOF_POINTER

<HR>
\section cfg_q Configuration options related to queue (by reference) facility

\li \b RKH_RQ_EN \copydetails RKH_RQ_EN
\li \b RKH_RQ_SIZEOF_NELEM \copydetails RKH_RQ_SIZEOF_NELEM
\li \b RKH_RQ_EN_GET_LWMARK \copydetails RKH_RQ_EN_GET_LWMARK
\li \b RKH_RQ_EN_READ \copydetails RKH_RQ_EN_READ
\li \b RKH_RQ_EN_DEPLETE \copydetails RKH_RQ_EN_DEPLETE
\li \b RKH_RQ_EN_IS_FULL \copydetails RKH_RQ_EN_IS_FULL
\li \b RKH_RQ_EN_GET_NELEMS \copydetails RKH_RQ_EN_GET_NELEMS
\li \b RKH_RQ_EN_PUT_LIFO \copydetails RKH_RQ_EN_PUT_LIFO
\li \b RKH_RQ_EN_GET_INFO \copydetails RKH_RQ_EN_GET_INFO

<HR>
\section cfg_mp Configuration options related to fixed-sized memory block facility

\li \b RKH_MP_EN \copydetails RKH_MP_EN
\li \b RKH_MP_REDUCED \copydetails RKH_MP_REDUCED
\li \b RKH_MP_SIZEOF_BSIZE \copydetails RKH_MP_SIZEOF_BSIZE
\li \b RKH_MP_SIZEOF_NBLOCK \copydetails RKH_MP_SIZEOF_NBLOCK
\li \b RKH_MP_EN_GET_BSIZE \copydetails RKH_MP_EN_GET_BSIZE
\li \b RKH_MP_EN_GET_NFREE \copydetails RKH_MP_EN_GET_NFREE	
\li \b RKH_MP_EN_GET_LWM \copydetails RKH_MP_EN_GET_LWM	
\li \b RKH_MP_EN_GET_INFO \copydetails RKH_MP_EN_GET_INFO

<HR>
\section cfg_t Configuration options related to software timer facility

\li \b RKH_TIM_EN \copydetails RKH_TIM_EN	
\li \b RKH_TIM_SIZEOF_NTIMER \copydetails RKH_TIM_SIZEOF_NTIMER
\li \b RKH_TIM_EN_HOOK \copydetails RKH_TIM_EN_HOOK
\li \b RKH_TIM_EN_RESTART \copydetails RKH_TIM_EN_RESTART
\li \b RKH_TIM_EN_GET_INFO \copydetails RKH_TIM_EN_GET_INFO

*/


/**
\page Usage Representing a state machine: step by step
\image html rkh_bunner.jpg

Prev: \ref main_page "Home" \n
Next: \ref dbg "Tracing tool"

\n The goal in this section is to explain how to represent a state machine 
using the RKH framework. To do that is proposed a simple example, which is 
shown in the \ref fig1 "Figure 1". Also, this section summarizes the main 
rules and concepts for making the most out of RKH features.
\note
Although the diagram shown in the \ref fig1 "Figure 1" does not have a 
submachine state, was considered appropriate to include in this section a 
detailed explanation of how to deal with this very powerful concept using 
the RKH framework.
The purpose of defining submachine states is to decompose and localize 
repetitive parts because the same state machine can be referenced from 
more than one submachine state.

\n This section includes:

- \subpage basics
- \subpage preparing
- \subpage identify_events
- \subpage identify
- \subpage representing
- \subpage running
- \subpage submachine

\anchor fig1
\image html my.png "Figure 1 - \"my\" state diagram"

*/
