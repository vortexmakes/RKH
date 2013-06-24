/** 
\page Installation Installation
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
<RKH-root>					- RKH-root directory
  |
  +-demo					- RKH demo applications
  +-doc						- RKH documentation
  \-source					- RKH source files
  | copying.txt				- licence file
  | README					- change log file
  | rkh.chm					- reference manual
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
<RKH-root> 					- RKH-root directory
  |   
  +-demo					- Demo applications
  +-doc						- Documentation
  \-source					- RKH source code files
  | +-include				- Contains platform-independent header files
  | |   rkh.h				- Framework interface 
  | |   rkhassert.h			- Assert definitions
  | |   rkhevt.h			- Event data type and other related macros 
  | |   rkhitl.h			- Internal use only 
  | |   rkhmp.h				- Fixed-size memory block services interface 
  | |   rkhplat.h			- Supported and portable platforms 
  | |   rkhrdy.h			- Native priority management 
  | |   rkhrq.h				- Queue services interface 
  | |   rkhs.h				- Simple and cooperative scheduler interface 
  | |   rkhtim.h			- Timer services interface 
  | |   rkhtrc.h			- Trace facility 
  | |   rkhtype.h			- Defines the data types that uses RKH 
  | |       
  | \-portable				- Contains platform-dependent files
  | |
  | | rkh.c					- State machine engine 
  | | rkhdyn.c				- Dynamic event management, and event framework services 
  | | rkhmp.c				- Fixed-size memory block 
  | | rkhrq.c				- Queue (copy by reference)
  | | rkhs.c				- Simple and cooperative scheduler
  | | rkhsma.c				- State machine application (SMA) registration.
  | | rkhtbl.c				- Binary map tables.
  | | rkhtim.c				- Software timer.
  | | rkhtrc.c				- Platform-independent source code of runtime tracing.
  |
  | copying.txt				- Licence file
  | README					- Change log file
  | rkh.chm					- Reference manual
\endcode
<STRONG> Figure 2 RKH source directory </STRONG>

<HR>
\section portable_dir RKH portable directory

\copydetails rkhplat.h
\copydetails rkhtype.h
See the \ref Porting section for more information. 
The following figure shows the \c \\portable directory.

\anchor portable_dir_fig
\code
	 <RKH-root>	
	   |
	   +-demo
	   +-doc
	   \-source
       | +-include				- RKH platform-independent header files
( 1)   | \-portable				- Platform-specific RKH ports
( 2)   | | +-80x86				- Ports to the 80x86 processor
       | | | | +-linux_st		- Ports to Linux with scheduler emulation
       | | | | | \-gnu			- Ports with the GNU compiler
       | | | | |     rkhport.c	- RKH port to Linux source file
       | | | | |     rkhport.h	- RKH platform-dependent include file
       | | | | |     rkht.h		- RKH platform-dependent include file
       | | | | |           
( 3)   | | | | \-win32_st		- Ports to Win32 with scheduler emulation
( 4)   | | | |   \-vc08 		- Ports with the Visual Studio C++ compiler
( 5)   | | | |       rkhport.c
( 6)   | | | |       rkhport.h
( 7)   | | | |       rkht.h
       | | | |             
       | | +-arm-cortex			- Ports to the ARM Cortex processor
       | | | \-rkhs				- Ports to the native cooperative scheduler
       | | |   +-arm_cm3		- Ports to the ARM Cortex-M3 processor
       | | |   | \-codered		- Ports with the code_red compiler
       | | |   |     rkhport.c
       | | |   |     rkhport.h
       | | |   |     rkht.h
       | | |   |           
       | | |   \-arm_cm4f		- Ports to the ARM Cortex-M3 processor 
       | | |     \-cw_v10		- Ports with the Codewarrior v10 compiler
       | | |         rkhport.c
       | | |         rkhport.h
       | | |         rkht.h
       | | |                   
( 8)   | | +-cfv1				- Ports to the Coldfire V1 processor 
( 9)   | | | \-rkhs				- Ports to the native cooperative scheduler
(10)   | | |   \-cw6_3			- Ports with the Codewarrior v6.3 compiler
(11)   | | |       rkhport.c
(12)   | | |       rkhport.h
(13)   | | |       rkht.h
       | | |               
       | | \-s08				- Ports to the S08 processor 
       | | |  \-rkhs			- Ports to the native cooperative scheduler
       | | |    \-cw6_3			- Ports with the Codewarrior v6.3 compiler
       | | |        rkhport.c
       | | |        rkhport.h
       | | |        rkht.h
	   | | +...					- Ports to other CPUs
	   | |						- RKH platform-independent source code
	   | | rkh.c
	   | | rkhdyn.c
	   | | ...
	   |
	   | copying.txt
	   | README	
	   | rkh.chm	
\endcode
<STRONG> Figure 3 RKH portable directory </STRONG>

\li ( 1) Platform-specific RKH ports. The directory \\portable contains 
platform-dependent 
files to be used by RKH applications. This directory structure is the most 
complicated because of the large number of choices available, such as 
CPU architectures, compilers, operating systems, and compiler options. 
Each of those choices is represented as a separate level of nesting in a 
hierarchical directory tree, so that each dimension in the multi-dimensional 
space of options can be extended independently from the others. Also, the 
directory branch for each port is individually customizable, so each branch 
can represent only choices relevant for a given CPU, operating system, 
compiler, etc.
\li ( 2) Ports to the 80x86 processor. The CPU architecture is placed as the 
first level of nesting within the \\portable directory. Examples of CPU 
architectures could be: 80x86, Coldfire, S08, ARM Cortex, ARM Thumb, 
MSP430, etc. 
Please note that a separate directory is needed whenever the CPU architecture 
is significantly different.
\li ( 3) Ports to Win32 with scheduler emulation. The second level of 
nesting, under the CPU architecture, is the operating system used.
\li ( 4) Ports with the Visual Studio C++ compiler. The next level of 
nesting, under each operating system directory, is the directory for the 
compiler used.
\li ( 5) RKH platform-dependent source file. The platform-specific source 
file is optional and many ports don't require it.
\li ( 6) RKH platform-dependent include file. Frequently, defines the 
interrupt locking method, the critical section management, among other things.
The key point of the design is that all platform-independent RKH source 
files include the same \c rkhplat.h header file as the application source 
files.
\li ( 7) RKH platform-dependent include file. In this file is defined the 
data types that uses RKH. The key point of the design is that all 
platform-independent RKH source files include the same \c rkhtype.h header 
file as the application source files.
\li ( 8) Ports to the Coldfire V1 processor
\li ( 9) using the native simple cooperative scheduler
\li (10) with the Codewarrior v6.3 compiler
\li (11-13) Idem (5-7)

<HR>
\section demo_dir RKH demo applications

The \c \\demo directory contains the application examples that are included in the 
standard RKH distribution. The structure of the \c \\demo is the most complicated 
because of the large number of choices available, such as CPU architectures, 
compilers, operating systems, and compiler options. Each of those choices is 
represented as a separate level of nesting in a hierarchical directory tree, 
so that each dimension in the multi-dimensional space of options can be 
extended independently from the others. Also, the directory branch for each 
RKH port is individually customizable, so each branch can represent only 
choices relevant for a given CPU, operating system, compiler, etc.

Each RKH application must have its own configuration file, called \c rkhcfg.h. 
This file adapts and configures RKH by means of compiler definitions and macros 
allowing to restrict the resources consumed by RKH. Adjusting this definitions 
allows to reduce the ROM and RAM consumption, and to enhance the system 
performance in a substantial manner.

\anchor demo_dir_fig
\code
	 <RKH-root>	
	   |
( 1)   +-demo					- RKH demo applications
( 2)   | +-80x86				- Demos for the x86 processor
       | | +-linux_st			- Demos for Linux with scheduler emulation
       | | |
( 3)   | | +-win32_st			- Demos for Windows with scheduler emulation
( 4)   | | | \-vc08				- Demos for Visual Studio C++
( 5)   | | |   +-ahsm			- Abstract State Machine example for Windows
( 6)   | | |   \-subm			- Submachine example for Windows
( 7)   | | |     \-prj			- IDE-dependent files
       | | |               
       | +-common				- Common files
       | \-cross				- Cross-platform examples
       |   \-blinky				- Blinky example
       |     |  bky.c			- the Blinky active object
       |     |  bky.h			- the Blinky header file
       |     |  bkyact.c		- the Blinky actions
       |     |  bkyact.h		- the Blinky actions header file
       |     |  main.c			- the \c main() function
( 8)   |     |  rkhcfg.h		- RKH configuration file for Blinky demo
       |     |   
       |     \-platform			- Platform-specific RKH BSP
       |       +-80x86			- Examples for the x86 processor
       |       | +-linux_st		- Examples for Linux with scheduler emulation
       |       | | \-gnu
       |       | |     bsp.c	- BSP for the Blinky application
       |       | |     bsp.h	- BSP header file
       |       | |     Makefile - external Makefile for GNU Tool
       |       | |     tcptrc.c - BSP source code for Trazer
       |       | |     tcptrc.h - BSP include file for Trazer
       |       | +-win32_st		- Examples for Win32 with scheduler emulation
       |       |   \-vc08
       |       |     |  bsp.c
       |       |     |  bsp.h
       |       |     |  tcptrc.c
       |       |     |  tcptrc.h
       |       |     |   
       |       |     \-prj
       |       |       |  blinky.ncb
       |       |       |  blinky.sln
       |       |       |  blinky.vcproj
       |       |       |   
       |       |       \---Debug
       |       +-arm-cortex		- Examples for the ARM Cortex processor
       |       |   \-rkhs		- Examples for the native scheduler
       |       |     +-arm_cm3
       |       |     | \-lpcx
       |       |     |     \-codered
       |       |     \-arm_cm4f
       |       |         \-freedom
       |       |           \-cw_v10
       |       +-...
	   +-doc
	   \-source
	   | copying.txt
	   | README	
	   | rkh.chm	
\endcode
<STRONG> Figure 4 Demo application directories </STRONG>

\li ( 1) RKH demo applications. The \c demo\\ directory contains the 
application examples that are included in the standard RKH distribution. 
The structure of the \c demo\\ is the most complicated because of the large 
number of choices available, such as CPU architectures, compilers, operating 
systems, and compiler options. Each of those choices is represented as a 
separate level of nesting in a hierarchical directory tree, so that each 
dimension in the multi-dimensional space of options can be extended 
independently from the others. Also, the directory branch for each RKH port 
is individually customizable, so each branch can represent only choices 
relevant for a given CPU, operating system, compiler, etc.
\li ( 2) Demos for the x86 processor. The CPU architecture is placed as the 
first level of nesting within the \c demo\\ directory. Examples of CPU 
architectures could be: 80x86, Coldfire, S08, ARM Cortex, ARM, MSP430, 
etc. Please note that a separate directory is needed whenever the CPU 
architecture is significantly different.
\li ( 3) Demos for Windows with scheduler emulation. The second level of 
nesting, under the CPU architecture, is the operating system used.
\li ( 4) Demos for Visual Studio C++. The next level of nesting, under each 
operating system directory, is the directory for the compiler used.
\li ( 5-6) Finally, the example application is located in its own directory. 
In this case, abstract hierarchical state machine example. This application 
is very useful to learn and explore the Statechart and UML features.
\li ( 7) The \c ahsm\\prj\\ subdirectory contains the IDE-dependent files, 
like object files, executable, and among others.
\li ( 8) As mentioned above, each of application that use RKH must be defined 
its own configuration file, \c rkhcfg.h.
\li ( 9) This directory provides several examples on how to use RKH, 
designed to experiment with RKH immediately. The simplicity of the code and 
state diagrams means it also serves as a good starter project for people who 
are not yet familiar with RKH. Also, this examples are demostration projects 
considered cross-platform, because of they are able to function on more than 
one computer architecture or operating system. The code of demos are located 
in the \c \<rkh\>\\demo\\cross\\ directory, where \c \<rkh\> stands for the 
installation directory chosed to install the accompanying software. Each 
example contains the platform-independent source code and a  
.. \c \\platform\\ directory. The structure of the .. \c \\platform\\ branch 
closely mirrors the structure of the \c source\\portable\\ directory, which 
contains platform-specific header files and libraries to be used by RKH 
applications.

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
\c rhhport.h, \c rkhport.c, which frequently defines the interrupt 
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
will be stored in ROM, must be defined in \c rkhport.h the RKHROM macro.

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
\c rkhport.h file.
\li (2) Define the macros RKH_SMA_BLOCK(), RKH_SMA_READY(), and 
RKH_SMA_UNREADY() in \c rkhport.h according to underlying OS or RTOS.
\li (3) Define the macros #RKH_OSDATA_TYPE, and #RKH_THREAD_TYPE in 
\c rkhport.h according to underlying OS or RTOS. 
\li (4) Then, implement the platform-specific functions rkh_init(), rkh_enter(), 
rkh_exit(), rkh_sma_activate(), and rkh_sma_terminate(). All these functions 
are placed in \c rkhport.c.

<EM>Example for x86, VC08, and win32 with scheduler emulation</EM>
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
\c rkhcfg.h file.
\li (2) Define the macros #RKH_EQ_TYPE = RKHRQ_T, RKH_SMA_BLOCK(), 
RKH_SMA_READY(), RKH_SMA_UNREADY() in \c rkhport.h. 
\li (3) When using the native shceduler (RKHS) is NOT necessary provides the 
functions rkh_init(), rkh_enter(), rkh_exit(), rkh_sma_activate(), and 
rkh_sma_terminate(). 
\li (4) Also, the macros RKH_EQ_TYPE, RKH_SMA_BLOCK(), 
\li (5) RKH_SMA_READY(), RKH_SMA_UNREADY() are RKH provided. 
In this mode of operation, RKH assumes the use of native priority scheme. 
See \c rkhs.h, \c rkhs.c, and \c rkhrdy.h files for more information.

\n <HR>
\section prio Priority mechanism

<EM>If RKH works in conjunction with a traditional OS/RTOS, RKH provides its own 
priority mechanism?</EM>

\b YES: \n
\li (1) Declare an RKHRG_T variable.
\li (2) Include the \c rkhrdy.h in \c rkhport.h.
\li (3) Then, the RKH port could be use the macros rkh_rdy_is_empty(), 
rkh_rdy_isnot_empty(), rkh_rdy_ins(), rkh_rdy_rem(), and rkh_rdy_findh(). 
Frequently, the macros RKH_SMA_BLOCK(), RKH_SMA_READY(), and 
RKH_SMA_UNREADY() use the macros provided by \c rkhrdy.h.

\b NO: \n
Nothing to do.

\n <HR>
\section eque Event queue

<EM>If RKH works in conjunction with a traditional OS/RTOS, are implemented 
the event queues with a message queue of the underlying OS/RTOS?</EM>

\b YES: \n
\li (1) Define the macro #RKH_EN_NATIVE_EQUEUE = 0 in \c rkhport.h
\li (2) Define the macro #RKH_EQ_TYPE = 0 in \c rkhport.h according to OS/RTOS.
\li (3) Then, implement the platform-specific functions rkh_sma_post_fifo(), 
rkh_sma_post_lifo() y rkh_sma_get(). All these functions are placed in 
\c rkhport.c file.

<EM>Generic example</EM>
\code
void 
rkh_sma_post_fifo( RKHSMA_T *sma, const RKHEVT_T *e )
{
	RKH_SR_ALLOC();
	
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
	RKH_SR_ALLOC();

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
	RKH_SR_ALLOC();

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
\c rkhport.h
\li (2) When using the native event queues is NOT necessary provides neither 
the functions rkh_sma_post_fifo(), rkh_sma_post_lifo() nor rkh_sma_get().
\li (3) Define #RKH_EQ_TYPE = RKHRQ_T in \c rkhport.h.
		
<EM>If the application code uses the RKH native scheduler, are implemented 
the event queues with the native queues RKHRQ_T?</EM>

\b YES: \n
\li (1) Define the macro #RKH_EN_NATIVE_EQUEUE = 1 y #RKH_RQ_EN = 1 in 
\c rkhport.h and \c rkhcfg.h respectively.
\li (2) When using the native event queues is NOT necessary provides neither 
the functions rkh_sma_post_fifo(), rkh_sma_post_lifo() nor rkh_sma_get().
\li (3) Define #RKH_EQ_TYPE = RKHRQ_T in \c rkhport.h.
		
\b NO: \n
\li (1) Define the macro #RKH_EN_NATIVE_EQUEUE = 0 in \c rkhport.h
\li (2) Define the macro #RKH_EQ_TYPE = 0 in \c rkhport.h according to OS/RTOS.
\li (3) Then, implement the platform-specific functions rkh_sma_post_fifo(), 
rkh_sma_post_lifo() y rkh_sma_get(). All these functions are placed in 
\c rkhport.c file.

\n <HR>
\section dyn Dynamic event support

<EM>Is required events with arguments?</EM>

\b NO: \n
\li (1) Define the macros #RKH_EN_DYNAMIC_EVENT = 0 and 
#RKH_EN_NATIVE_DYN_EVENT = 0 in \c rkhport.h.

\b YES: \n

<EM>If RKH works in conjunction with a traditional OS/RTOS, is implemented 
the dynamic memory support with a internal module of the underlying 
OS/RTOS?</EM>

\b YES: \n
\li (1) Define the macro #RKH_EN_DYNAMIC_EVENT = 1 and 
#RKH_EN_NATIVE_DYN_EVENT = 0 in \c rkhport.h
\li (2) Define the macros RKH_DYNE_TYPE, RKH_DYNE_INIT(), 
RKH_DYNE_GET_ESIZE(), RKH_DYNE_GET() y RKH_DYNE_PUT() in \c rkhport.h 
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
#RKH_EN_NATIVE_DYN_EVENT = 0, and #RKH_MP_EN = 1 in \c rkhcfg.h

<EM>If the application code uses the RKH native scheduler, is implemented 
the dynamic memory support with the native fixed-size memory block pool 
RKHMP_T?</EM>

\b YES: \n
\li (1) Define the macro #RKH_EN_DYNAMIC_EVENT = 1 and 
#RKH_EN_NATIVE_DYN_EVENT = 0 in \c rkhcfg.h and \c rkhport.h respectively.

\b NO: \n
\li (1) Define the macro #RKH_EN_DYNAMIC_EVENT = 1,  
#RKH_EN_NATIVE_DYN_EVENT = 0, and #RKH_MP_EN = 1 in \c rkhcfg.h

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
RKH_HK_EN_START, and RKH_HK_EN_EXIT options from the \c rkhcfg.h.\n

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

\copydetails RKH_SR_ALLOC()

\n <HR>
\section trc Trace facility

When using the trace facility must be defined in \c rkhport.h the following 
configurations:

\li #RKH_TRC_SIZEOF_POINTER \copydetails #RKH_TRC_SIZEOF_POINTER 
\li #RKH_TRC_SIZEOF_POINTER \copydetails #RKH_TRC_SIZEOF_FUN_POINTER 

Example:

\code 
#define RKH_TRC_SIZEOF_POINTER			32
#define RKH_TRC_SIZEOF_FUN_POINTER		32
\endcode

A RKH port cannot and should not define all the functions that it calls, 
because this would render the port too inflexible. Therefore, the 
application-specific functions \c rkh_trc_open(), \c rkh_trc_close(), 
\c rkh_trc_flush(), and \c rkh_trc_getts() are application provided typically 
in the board support package (\c bsp.c).

\n
\code void rkh_trc_open( void )\endcode
\copydetails RKH_TRC_OPEN \n

\code void rkh_trc_close( void )\endcode
\copydetails RKH_TRC_CLOSE \n

\code void rkh_trc_flush( void )\endcode
\copydetails RKH_TRC_FLUSH \n

\code void rkh_trc_getts( void )\endcode
\copydetails rkh_trc_getts \n

<HR>
\section rkhp A port file example.

<EM>\c "rkhport.h" for x86, VC08, and win32 with scheduler emulation</EM>
<EM> (\\source\\portable\\80x86\\win32_st\\vc08)</EM>

\code
/*
 *	file: rkhport.h - Visual Studio 2008 port
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 27, 2012
 *
 * 	Copyright (C) 2010 Leandro Francucci. All rights reserved.
 *
 * 	RKH is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 *  RKH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RKH, see copying.txt file.
 *
 * Contact information:
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			lf@vxtsolutions.com.ar
 */

/*
 * 	rkhport.h
 */


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


/**
 *	If the #RKH_EN_SMA_THREAD is set to 1, each SMA (active object) has its own 
 *	thread of execution.
 */

#define RKH_EN_SMA_THREAD 				0

/**
 *	If the #RKH_EN_SMA_THREAD and #RKH_EN_SMA_THREAD_DATA are set to 1, each 
 *	SMA (active object) has its own thread of execution and its own object 
 *	data.
 */

#define RKH_EN_SMA_THREAD_DATA			0

/**
 * 	If the #RKH_EN_NATIVE_SCHEDULER is set to 1 then RKH will include the 
 * 	simple, cooperative, and nonpreemptive scheduler RKHS.
 * 	When #RKH_EN_NATIVE_SCHEDULER is enabled RKH also will automatically 
 * 	define #RKH_EQ_TYPE, RKH_SMA_BLOCK(), RKH_SMA_READY(), RKH_SMA_UNREADY(), 
 * 	and assume the native priority scheme.
 */

#define RKH_EN_NATIVE_SCHEDULER			0

/**
 * 	If the #RKH_EN_NATIVE_EQUEUE is set to 1 and the native event queue is 
 *	enabled (see #RKH_RQ_EN) then RKH will include its own implementation of 
 *	rkh_sma_post_fifo(), rkh_sma_post_lifo(), and rkh_sma_get() functions.
 */

#define RKH_EN_NATIVE_EQUEUE			1

/**
 * 	If the #RKH_EN_NATIVE_DYN_EVENT is set to 1 and the native fixed-size 
 * 	memory block facility is enabled (see #RKH_MP_EN) then RKH will include 
 * 	its own implementation of dynamic memory management.
 * 	When #RKH_EN_NATIVE_DYN_EVENT is enabled RKH also will automatically 
 * 	define RKH_DYNE_TYPE, RKH_DYNE_INIT(), RKH_DYNE_GET_ESIZE(), 
 * 	RKH_DYNE_GET(), and RKH_DYNE_PUT().
 */

#define RKH_EN_NATIVE_DYN_EVENT			1

/**
 *	If the #RKH_EN_REENTRANT is set to 1, the RKH event dispatch allows to be 
 *	invoked from several threads of executions. Enable this only if the 
 *	application is based on a multi-thread architecture.
 */

#define RKH_EN_REENTRANT				0

/**
 * 	Specify the size of void pointer. The valid values [in bits] are 
 * 	16 or 32. Default is 32. See RKH_TRC_SYM() macro.
 */

#define RKH_TRC_SIZEOF_POINTER			32

/**
 * 	Specify the size of function pointer. The valid values [in bits] are 
 * 	16 or 32. Default is 32. See RKH_TUSR_FUN() and RKH_TRC_FUN() macros.
 */

#define RKH_TRC_SIZEOF_FUN_POINTER		32

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
			    rkh_rdy_ins( (rg), ((RKHSMA_T*)(sma))->romrkh->prio ); \
			    (void)SetEvent( sma_is_rdy ); \

#define RKH_SMA_UNREADY( rg, sma ) 							\
			    rkh_rdy_rem( (rg), ((RKHSMA_T*)(sma))->romrkh->prio )

#define RKH_WAIT_FOR_EVENTS() 								\
			    ((void)WaitForSingleObject( sma_is_rdy, (DWORD)INFINITE))


#endif
\endcode

<EM>\c "rkht.h" for x86, VC08, and win32 scheduler emulation</EM>
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

<EM>\c "rkhport.c" for x86, VC08, and win32 with scheduler emulation</EM>
<EM> (\\source\\portable\\80x86\\win32_st\\vc08)</EM>

\code
/*
 *	file: rkhport.c - Visual Studio 2008 port
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 22, 2012
 *
 * 	Copyright (C) 2010 Leandro Francucci. All rights reserved.
 *
 * 	RKH is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 *  RKH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RKH, see copying.txt file.
 *
 * Contact information:
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			lf@vxtsolutions.com.ar
 */

/*
 * 	rkhport.c
 */


#include "rkh.h"


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "Windows 32-bits (single thread)" )


CRITICAL_SECTION csection;		/* Win32 critical section */
HANDLE sma_is_rdy;          	/* Win32 event to signal when SMAs are ready */
RKHRG_T rkhrg;					/* ready group of SMAs */

extern rkhui8_t running;


const 
char *
rkh_get_port_version( void )
{
	return RKH_MODULE_GET_VERSION();
}


const 
char *
rkh_get_port_desc( void )
{
	return RKH_MODULE_GET_DESC();
}


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

    RKH_HK_EXIT();
    CloseHandle( sma_is_rdy );
    DeleteCriticalSection( &csection );	
}


void 
rkh_exit( void )
{
	RKH_TR_FWK_EX();
	running = 0;
}


void 
rkh_sma_activate(	RKHSMA_T *sma, const RKHEVT_T **qs, RKH_RQNE_T qsize, 
						void *stks, rkhui32_t stksize )
{
    ( void )stks;
    ( void )stksize;

	rkh_rq_init( &sma->equeue, (const void **)qs, qsize, sma );
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
		enumeration in the \c rkh.h file.
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
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure: #RKH_SMA_EN_IEVENT, #RKH_SMA_EN_ID. 
See \ref cfg section for more information. 

Prev: \ref qref "Quick reference"

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
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure: #RKH_SMA_EN_HCAL, #RKH_SMA_EN_STATE_ID. 
See \ref cfg section for more information. 

Prev: \ref qref "Quick reference"

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
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure: RKH_SMA_EN_STATE_ID, RKH_SMA_EN_PPRO.
See \ref cfg section for more information. 

Prev: \ref qref "Quick reference"

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
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure: RKH_SMA_EN_HCAL, RKH_SMA_EN_PSEUDOSTATE, RKH_SMA_EN_SUBMACHINE, 
RKH_SMA_EN_STATE_ID.
See \ref cfg section for more information. 

Prev: \ref qref "Quick reference"

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

A conditional pseudostate (also called juncton pseudostate) is defined with 
the RKH_CREATE_COND_STATE() macro and declared with the 
#RKH_DCLR_COND_STATE macro. Frequently, each state machine and its 
states and pseudostates are encapsulated inside a dedicated source file 
(.c file), from which the RKH_CREATE_COND_STATE() macro is used.
We will develop one example of conditional pseudostate 
(aka junction pseudostate) definition to illustrate the use of this macro. We 
will give our junction pseudostate the name \c C1. As will demostrates the 
use of RKH_CREATE_COND_STATE() macro and its arguments is very similar to 
RKH_CREATE_BASIC_STATE() macro.

<b>Defining a conditional pseudostate</b>
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_COND_STATE( 	C1, 
(3)							0 );
\endcode

<b>Declaring a conditional pseudostate</b>
\code
//	my.h: state-machine's header file

...
RKH_DCLR_COND_STATE C1;
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_COND_STATE() macro is used.
\li (2)	\c C1 is the pseudostate name. Represents a conditional pseudostate 
		structure.
\li (3)	\c 0 is the value of pseudostate ID.

\b Customization

Each RKH application must have its own configuration file, called 
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure: RKH_SMA_EN_HCAL, RKH_SMA_EN_STATE_ID, RKH_SMA_EN_PSEUDOSTATE, 
RKH_SMA_EN_CONDITIONAL, RKH_SMA_MAX_TR_SEGS. 
See \ref cfg section for more information. 

Prev: \ref qref "Quick reference"

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
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h shows the general layout of the configuration file.
Use the following macros to reduce the memory taken by state machine 
structure: RKH_SMA_EN_HCAL, RKH_SMA_EN_STATE_ID, RKH_SMA_EN_PSEUDOSTATE, 
RKH_SMA_MAX_TR_SEGS, RKH_EN_SHALLOW_HISTORY. 
See \ref cfg section for more information. 

Prev: \ref qref "Quick reference"

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
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h shows the general layout of the configuration file.
Use the following macros to reduce the memory taken by state machine 
structure: RKH_SMA_EN_HCAL, RKH_SMA_EN_STATE_ID, RKH_SMA_EN_PSEUDOSTATE, 
RKH_SMA_MAX_TR_SEGS, RKH_EN_DEEP_HISTORY. 
See \ref cfg section for more information. 

Prev: \ref qref "Quick reference"

<HR>
\section qref6 Defining a choice pseudostate

\n Prev: \ref qref "Quick reference"

A choice pseudostate is defined with the RKH_CREATE_CHOICE_STATE() macro and 
declared with the #RKH_DCLR_CHOICE_STATE macro. Frequently, each state 
machine and its states and pseudostates are encapsulated inside a dedicated 
source file (.c file), from which the RKH_CREATE_CHOICE_STATE() macro is used.
We will develop one example of choice pseudostate definition to 
illustrate the use of this macro. We will give our choice pseudostate 
the name \c CH. As will demostrates the use of RKH_CREATE_CHOICE_STATE() 
macro and its arguments is very similar to RKH_CREATE_COND_STATE() macro.

<b>Defining a choice pseudostate</b> \n
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_CHOICE_STATE( 	CH, 
(3)								8 );
\endcode

<b>Declaring a choice pseudostate</b>
\code
//	my.h: state-machine's header file

...
RKH_DCLR_CHOICE_STATE	CH;
\endcode

Explanation

\li (1)	Frequently, each state machine and its states are encapsulated 
		inside a dedicated source file (.c file), from which the 
		RKH_CREATE_CHOICE_STATE() macro is used.
\li (2)	\c CH is the pseudostate name. Represents a choice pseudostate 
		structure.
\li (3)	\c 0 is the value of pseudostate ID.

\b Customization

Each RKH application must have its own configuration file, called 
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h shows the general layout of the configuration file.

Use the following macros to reduce the memory taken by state machine 
structure: RKH_SMA_EN_HCAL, RKH_SMA_EN_STATE_ID, RKH_SMA_EN_PSEUDOSTATE, 
RKH_SMA_EN_CHOICE, RKH_SMA_MAX_TR_SEGS. 
See \ref cfg section for more information. 

Prev: \ref qref "Quick reference"

<HR>
\section qref14 Defining entry, exit, and transition actions

\n Prev: \ref qref "Quick reference"

This section summarize the functions and its prototypes used by RKH 
framework. As mentioned before, the framework make use the callbacks, i.e. 
pointer to functions, in most of its data structures by means of 
RKH_SMA_CREATE(), RKH_CREATE_COMP_STATE(), 
RKH_CREATE_BASIC_STATE(), RKH_TRINT(), RKH_TRREG(), RKH_BRANCH(), 
RKH_CREATE_SHALLOW_HISTORY_STATE(), RKH_CREATE_DEEP_HISTORY_STATE(), and 
RKH_CREATE_CHOICE_STATE() macros.
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
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h shows the general layout of the configuration file.
Use the following macros to reduce the memory taken by state machine 
structure: RKH_EN_DYNAMIC_EVENT, RKH_MAX_EPOOL, RKH_SIZEOF_EVENT, 
RKH_SIZEOF_ESIZE, RKH_EN_NATIVE_DYN_EVENT, RKH_DYNE_TYPE, RKH_DYNE_INIT, 
RKH_DYNE_GET_ESIZE, RKH_DYNE_GET, RKH_DYNE_PUT. 
See \ref cfg section for more information. 

Prev: \ref qref "Quick reference"

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
See \ref Usage "Getting started with RKH" section 
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
(2)	static RKH_DCLR_STATIC_EVENT( e_timer, TOUT );

	void
(3)	tlayer_tout( void *t )
	{
		(void)t;
		close_layer();
	}

(4)	rkh_tim_init( 	&tlayer, 
(5)					&e_timer, 
(6)					tlayer_tout );
...
\endcode

Explanation

\li (1)	Declares and allocates the \c tlayer timer. 
\li (1)	Declares and allocates the static event \c e_timer timer with the 
		signal \c TOUT. 
\li (3)	Defines \c tlayer_tout() hook function, which is calls at the 
		\c tlayer expiration.
\li (4)	Initializes the \c tlayer timer. 
\li (5)	Event to be directly posted (using the FIFO policy) into the event 
		queue of the target agreed state machine application at the timer 
		expiration.
\li (6) Registers \c tlayer_tout() hook function.

\subsection qref18_2 Start and stop timers

\code
(1)	#define TPWR_TIME			RKH_TIME_MS( 100 )
(2)	#define TKEY_TIME			RKH_TIME_MS( 100 )
...
(3) static RKHT_T 	tpwr,
(4) 				tkey;

(5)	static RKH_DCLR_STATIC_EVENT( e_tpwr, TPWR );
(6)	static RKH_DCLR_STATIC_EVENT( e_tkey, TKEY );

(7)	rkh_tim_init( &tpwr, e_tpwr, NULL );
(8)	rkh_tim_init( &tkey, e_tkey, NULL );
...
(9) rkh_tim_oneshot( &tpwr, pwr, TPWR_TIME );
(10)rkh_tim_periodic( &tkey, pwr, TKEY_TIME, TKEY_TIME/4 );
...
(11)rkh_tim_stop( &tkey );
...
(12)rkh_tim_restart( &tpwr, TPWR_TIME * 2 );
\endcode

Explanation

\li (1-2)	Defines the number of millisencods for timer expiration using 
			the macro RKH_TIME_MS() that converts the ticks to time. 
\li (3-4)	Declares and allocates the \c tpwr, and \c tkey timers. 
\li (5-6)	Declares and allocates the static events \c e_tpwr, and 
			\c e_tkey. 
\li (7-8)	Initializes the \c tpwr, and \c tkey timers. 
\li (9)	Starts \c tpwr timer as one-shot timer, which posts the signal 
		\c TPWR to 	\c pwr state machine application after TPWR_TICK 
		timer-ticks.
\li (10)Starts \c tkey timer as periodic timer, which posts the signal 
		\c TKEY to \c pwr state machine application after TKEY_TICK 
		timer-ticks initially and then after every TKEY_TICK/4 timer-ticks.
\li (11) Stops \c tkey timer. 
\li (12) Restarts \c tpwr timer with a new number of ticks. 

\subsection qref18_3 Customization

Each RKH application must have its own configuration file, called 
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h shows the general layout of the configuration file.
Use the following macros to reduce the memory taken by state machine 
structure: RKH_TIM_EN, RKH_TIM_SIZEOF_NTIMER, RKH_TIM_EN_HOOK, 
RKH_TIM_EN_GET_INFO.
See \ref cfg section for more information. 

Prev: \ref main_page "Home"

\page dbg Tracing tool
\image html rkh_bunner.jpg

Prev: \ref main_page "Home" \n
Next: \ref cross "Examples"

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
in the \c rkhcfg.h header file. See \ref cfg section for more information 
about that.

<HR>
\section trfn Implementing the trace session support

For using the native trace facility the user should implement several 
functions which are platform and application specific. These function 
prototypes are definied within \c rkh.h file and listed below:

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
...
RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
...
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
	RKH_FILTER_OFF_EVENT( RKH_TG_MP, RKH_TE_MP_INIT );
	RKH_FILTER_OFF_EVENT( RKH_TG_SM, RKH_TE_SM_DCH );
	RKH_FILTER_OFF_EVENT( RKH_TG_FWK, RKH_TE_FWK_OBJ );
	RKH_FILTER_OFF_EVENT( RKH_TG_FWK, RKH_TE_FWK_SIG );
	RKH_FILTER_OFF_EVENT( RKH_TG_TIM, RKH_TE_TIM_START );
	RKH_FILTER_OFF_EVENT( RKH_TG_TIM, RKH_TE_TIM_TOUT );
}
\endcode

<HR>
\section trtbl Trace event table

This section provides a table that lists all the trace events and summarizes 
the data included for each. 

<TABLE	align="center" valign="middle" width=85% cellspacing=2 
		cellpadding=4 border=0>
	<TR bgColor="#c0c0c0">
		<TH colspan=6 align="left"><B> Related with memory pool 
											module (MP)</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Group </I></B></TH>
		<TH><B><I> ID </I></B></TH>
		<TH width=35%><B><I> Trace Event </I></B></TH> 
		<TH width=30%><B><I> Description </I></B></TH> 
		<TH colspan=2><B><I> Parameters </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=6 align="center"> #RKH_TG_MP </TD>
		<TD rowspan=2 align="center"> 0 </TD>
		<TD rowspan=2> #RKH_TE_MP_INIT ( SYM mp, NBLK nblock ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_MP_INIT </TD>
		<TD><I> mp </I></TD>
		<TD><I> Pointer to previously allocated memory pool structure </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nblock </I></TD>
		<TD><I> \copybrief RKHMP_T::nblocks </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 1 </TD>
		<TD rowspan=2> #RKH_TE_MP_GET ( SYM mp, NBLK nfree ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_MP_GET </TD>
		<TD><I> mp </I></TD>
		<TD><I> Pointer to previously allocated memory pool structure </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nfree </I></TD>
		<TD><I> \copybrief RKHMP_T::nfree </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 2 </TD>
		<TD rowspan=2> #RKH_TE_MP_PUT ( SYM mp, NBLK nfree ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_MP_PUT </TD>
		<TD><I> mp </I></TD>
		<TD><I> Pointer to previously allocated memory pool structure </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nfree </I></TD>
		<TD><I> \copybrief RKHMP_T::nfree </I></TD>
	</TR>

	<TR bgColor="#c0c0c0">
		<TH colspan=6 align="left"><B> Related with queue module (RQ)</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Group </I></B></TH>
		<TH><B><I> ID </I></B></TH>
		<TH><B><I> Trace Event </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
		<TH colspan=2><B><I> Parameters </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=12 align="center"> #RKH_TG_RQ </TD>
		<TD rowspan=3 align="center"> 0 </TD>
		<TD rowspan=3> #RKH_TE_RQ_INIT ( SYM q, SYM ao, NE nelem ) </TD>
		<TD rowspan=3> \copybrief RKH_TR_RQ_INIT </TD>
		<TD><I> q </I></TD>
		<TD><I> \copybrief RKHSMA_T::equeue </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nelem </I></TD>
		<TD><I> \copybrief RKHRQ_T::nelems </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 1 </TD>
		<TD rowspan=2> #RKH_TR_RQ_GET ( SYM q, NE nelem ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_RQ_GET </TD>
		<TD><I> q </I></TD>
		<TD><I> \copybrief RKHSMA_T::equeue </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nelem </I></TD>
		<TD><I> \copybrief RKHRQ_T::nelems </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 2 </TD>
		<TD rowspan=2> #RKH_TE_RQ_FIFO ( SYM q, NE nelem ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_RQ_FIFO </TD>
		<TD><I> q </I></TD>
		<TD><I> \copybrief RKHSMA_T::equeue </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nelem </I></TD>
		<TD><I> \copybrief RKHRQ_T::nelems </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 3 </TD>
		<TD rowspan=2> #RKH_TE_RQ_LIFO ( SYM q, NE nelem ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_RQ_LIFO </TD>
		<TD><I> q </I></TD>
		<TD><I> \copybrief RKHSMA_T::equeue </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nelem </I></TD>
		<TD><I> \copybrief RKHRQ_T::nelems </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 4 </TD>
		<TD rowspan=1> #RKH_TE_RQ_FULL ( SYM q ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_RQ_FULL </TD>
		<TD><I> q </I></TD>
		<TD><I> \copybrief RKHSMA_T::equeue </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 5 </TD>
		<TD rowspan=1> #RKH_TE_RQ_DPT ( SYM q ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_RQ_DPT </TD>
		<TD><I> q </I></TD>
		<TD><I> \copybrief RKHSMA_T::equeue </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 6 </TD>
		<TD rowspan=1> #RKH_TE_RQ_GET_LAST ( SYM q ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_RQ_GET_LAST </TD>
		<TD><I> q </I></TD>
		<TD><I> \copybrief RKHSMA_T::equeue </I></TD>
	</TR>

	<TR bgColor="#c0c0c0">
		<TH colspan=6 align="left"><B> Related with State Machine Application 
											(SMA) or Active Object </B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Group </I></B></TH>
		<TH><B><I> ID </I></B></TH>
		<TH><B><I> Trace Event </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
		<TH colspan=2><B><I> Parameters </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=14 align="center"> #RKH_TG_SMA </TD>
		<TD rowspan=1 align="center"> 0 </TD>
		<TD rowspan=1> #RKH_TE_SMA_ACT ( SYM ao ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_SMA_ACT </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 1 </TD>
		<TD rowspan=1> #RKH_TE_SMA_TERM ( SYM q ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_SMA_TERM </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 2 </TD>
		<TD rowspan=2> #RKH_TE_SMA_GET ( SYM sma, SIG sig ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_SMA_GET </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=3 align="center"> 3 </TD>
		<TD rowspan=3> #RKH_TE_SMA_FIFO ( SYM ao, SIG sig, SYM snr ) </TD>
		<TD rowspan=3> \copybrief RKH_TR_SMA_FIFO </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> snr </I></TD>
		<TD><I> Sender object </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=3 align="center"> 4 </TD>
		<TD rowspan=3> #RKH_TE_SMA_LIFO ( SYM ao, SIG sig, SYM snr ) </TD>
		<TD rowspan=3> \copybrief RKH_TR_SMA_LIFO </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> snr </I></TD>
		<TD><I> Sender object </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 5 </TD>
		<TD rowspan=2> #RKH_TE_SMA_REG ( SYM ao, UI8 prio ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_SMA_REG </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> prio </I></TD>
		<TD><I> \copybrief ROMRKH_T::prio </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 6 </TD>
		<TD rowspan=2> #RKH_TE_SMA_UNREG ( SYM ao, UI8 prio ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_SMA_UNREG </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> prio </I></TD>
		<TD><I> \copybrief ROMRKH_T::prio </I></TD>
	</TR>

	<TR bgColor="#c0c0c0">
		<TH colspan=6 align="left"><B> Related with State Machines (SM)</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Group </I></B></TH>
		<TH><B><I> ID </I></B></TH>
		<TH><B><I> Trace Event </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
		<TH colspan=2><B><I> Parameters </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=30 align="center"> #RKH_TG_SM </TD>
		<TD rowspan=2 align="center"> 0 </TD>
		<TD rowspan=2> #RKH_TE_SM_INIT ( SYM ao, SYM ist ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_SM_INIT </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> ist </I></TD>
		<TD><I> \copybrief ROMRKH_T::istate </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 1 </TD>
		<TD rowspan=2> #RKH_TE_SM_CLRH ( SYM ao, SYM h ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_SM_CLRH </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> h </I></TD>
		<TD><I> \copybrief RKHSCMP_T::history </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 2 </TD>
		<TD rowspan=2> #RKH_TE_SM_DCH ( SYM ao, SIG sig ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_SM_DCH </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=3 align="center"> 3 </TD>
		<TD rowspan=3> #RKH_TE_SM_TRN ( SYM ao, SYM sst, SYM tst ) </TD>
		<TD rowspan=3> \copybrief RKH_TR_SM_TRN </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> sst </I></TD>
		<TD><I> Source state of transition </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> tst </I></TD>
		<TD><I> Target state of transition </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 4 </TD>
		<TD rowspan=2> #RKH_TE_SM_STATE ( SYM ao, SYM st ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_SM_STATE </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nxtst </I></TD>
		<TD><I> Next state of transition </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 5 </TD>
		<TD rowspan=2> #RKH_TE_SM_ENSTATE ( SYM ao, SYM st ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_SM_ENSTATE </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> st </I></TD>
		<TD><I> Entry state </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 6 </TD>
		<TD rowspan=2> #RKH_TE_SM_EXSTATE ( SYM ao, SYM st ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_SM_EXSTATE </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> st </I></TD>
		<TD><I> Exited state </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=3 align="center"> 7 </TD>
		<TD rowspan=3> #RKH_TE_SM_NENEX ( SYM ao, UI8 nen, UI8 nex ) </TD>
		<TD rowspan=3> \copybrief RKH_TR_SM_NENEX </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nen </I></TD>
		<TD><I> Number of entry states </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nex </I></TD>
		<TD><I> Number of exited states </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=3 align="center"> 8 </TD>
		<TD rowspan=3> #RKH_TE_SM_NTRNACT ( SYM ao, UI8 nta, UI8 nts ) </TD>
		<TD rowspan=3> \copybrief RKH_TR_SM_NTRNACT </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nta </I></TD>
		<TD><I> Number of executed actions </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nts </I></TD>
		<TD><I> Number of transition segments </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 9 </TD>
		<TD rowspan=2> #RKH_TE_SM_TS_STATE ( SYM ao, SYM st ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_SM_TS_STATE </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> st </I></TD>
		<TD><I> Next state or pseudostate in transition </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 10 </TD>
		<TD rowspan=1> #RKH_TE_SM_EVT_PROC ( SYM ao ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_SM_EVT_PROC </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 11 </TD>
		<TD rowspan=1> #RKH_TE_SM_EVT_NFOUND ( SYM ao ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_SM_EVT_NFOUND </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 12 </TD>
		<TD rowspan=1> #RKH_TE_SM_CND_NFOUND ( SYM ao ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_SM_CND_NFOUND </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 13 </TD>
		<TD rowspan=1> #RKH_TE_SM_GRD_FALSE ( SYM ao ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_SM_GRD_FALSE </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 14 </TD>
		<TD rowspan=1> #RKH_TE_SM_UNKN_STATE ( SYM ao ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_SM_UNKN_STATE </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 15 </TD>
		<TD rowspan=1> #RKH_TE_SM_EX_HLEVEL ( SYM ao ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_SM_EX_HLEVEL </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 16 </TD>
		<TD rowspan=1> #RKH_TE_SM_EX_TSEG ( SYM ao ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_SM_EX_TSEG </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>

	<TR bgColor="#c0c0c0">
		<TH colspan=6 align="left"><B> Related with timer module (TIM)</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Group </I></B></TH>
		<TH><B><I> ID </I></B></TH>
		<TH><B><I> Trace Event </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
		<TH colspan=2><B><I> Parameters </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=8 align="center"> #RKH_TG_TIM </TD>
		<TD rowspan=2 align="center"> 0 </TD>
		<TD rowspan=2> #RKH_TE_TIM_INIT ( SYM t, SIG sig ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_TIM_INIT </TD>
		<TD><I> t </I></TD>
		<TD><I> Pointer to previously allocated timer structure </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=3 align="center"> 1 </TD>
		<TD rowspan=3> #RKH_TE_TIM_START ( SYM t, SYM ao, NTICK ntick ) </TD>
		<TD rowspan=3> \copybrief RKH_TR_TIM_START </TD>
		<TD><I> t </I></TD>
		<TD><I> Pointer to previously allocated timer structure </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHT_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> ntick </I></TD>
		<TD><I> \copybrief RKHT_T::ntick </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 2 </TD>
		<TD rowspan=1> #RKH_TE_TIM_STOP ( SYM t ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_TIM_STOP </TD>
		<TD><I> t </I></TD>
		<TD><I> Pointer to previously allocated timer structure </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 3 </TD>
		<TD rowspan=1> #RKH_TE_TIM_TOUT ( SYM t ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_TIM_TOUT </TD>
		<TD><I> t </I></TD>
		<TD><I> Pointer to previously allocated timer structure </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 4 </TD>
		<TD rowspan=1> #RKH_TR_TIM_REM ( SYM t ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_TIM_REM </TD>
		<TD><I> t </I></TD>
		<TD><I> Pointer to previously allocated timer structure </I></TD>
	</TR>

	<TR bgColor="#c0c0c0">
		<TH colspan=6 align="left"><B> Miscellanueos and related with 
										Framework (FWK)</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Group </I></B></TH>
		<TH><B><I> ID </I></B></TH>
		<TH><B><I> Trace Event </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
		<TH colspan=2><B><I> Parameters </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=39 align="center"> #RKH_TG_FWK </TD>
		<TD rowspan=1 align="center"> 0 </TD>
		<TD rowspan=1> #RKH_TE_FWK_EN () </TD>
		<TD rowspan=1> \copybrief RKH_TR_FWK_EN </TD>
		<TD><I></I></TD>
		<TD><I></I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 1 </TD>
		<TD rowspan=1> #RKH_TE_FWK_EX () </TD>
		<TD rowspan=1> \copybrief RKH_TR_FWK_EX </TD>
		<TD><I></I></TD>
		<TD><I></I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=3 align="center"> 2 </TD>
		<TD rowspan=3> #RKH_TE_FWK_EPREG ( UI8 ep, UI32 ss, ES es ) </TD>
		<TD rowspan=3> \copybrief RKH_TR_FWK_EPREG </TD>
		<TD><I> ep </I></TD>
		<TD><I> Event pool index in the list </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> ss </I></TD>
		<TD><I> Storage size in bytes </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> es </I></TD>
		<TD><I> Event size </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 3 </TD>
		<TD rowspan=2> #RKH_TE_FWK_AE ( ES es, SIG sig ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_AE </TD>
		<TD><I> es </I></TD>
		<TD><I> Event size </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 4 </TD>
		<TD rowspan=1> #RKH_TE_FWK_GC ( SIG sig ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_FWK_GC </TD>
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 5 </TD>
		<TD rowspan=1> #RKH_TE_FWK_GCR ( SIG sig ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_FWK_GCR </TD>
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 6 </TD>
		<TD rowspan=2> #RKH_TE_FWK_DEFER ( SYM q, SIG sig ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_DEFER </TD>
		<TD><I> q </I></TD>
		<TD><I> \copybrief RKHSMA_T::equeue </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 7 </TD>
		<TD rowspan=2> #RKH_TE_FWK_RCALL ( SYM ao, SIG sig ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_RCALL </TD>
		<TD><I> ao </I></TD>
		<TD><I> \copybrief RKHRQ_T::sma </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 8 </TD>
		<TD rowspan=2> #RKH_TE_FWK_OBJ ( SYM obj, STR nm ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_OBJ </TD>
		<TD><I> obj </I></TD>
		<TD><I> Object memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nm </I></TD>
		<TD><I> Name of object </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 9 </TD>
		<TD rowspan=2> #RKH_TE_FWK_SIG ( SIG sig, STR nm ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_SIG </TD>
		<TD><I> sig </I></TD>
		<TD><I> \copybrief RKHEVT_T::e </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nm </I></TD>
		<TD><I> Name of event signal </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 10 </TD>
		<TD rowspan=2> #RKH_TE_FWK_FUN ( SYM func, STR nm ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_FUN </TD>
		<TD><I> func </I></TD>
		<TD><I> Function memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nm </I></TD>
		<TD><I> Name of object </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 11 </TD>
		<TD rowspan=1> #RKH_TE_FWK_EXE_FUN ( SYM func ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_FWK_EXE_FUN </TD>
		<TD><I> func </I></TD>
		<TD><I> Function memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 12 </TD>
		<TD rowspan=2> #RKH_TE_FWK_TUSR ( UI8 usrtrc, STR nm ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_TUSR </TD>
		<TD><I> usrtrc </I></TD>
		<TD><I> User-defined trace event </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nm </I></TD>
		<TD><I> Name of user-defined event </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=1 align="center"> 13 </TD>
		<TD rowspan=1> #RKH_TE_FWK_TCFG ( CFG cfg ) </TD>
		<TD rowspan=1> \copybrief RKH_TR_FWK_TCFG </TD>
		<TD><I> cfg </I></TD>
		<TD><I> Configuration parameters of trace facility </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 14 </TD>
		<TD rowspan=2> #RKH_TE_FWK_ASSERT ( SRT mod, UI16 ln ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_ASSERT </TD>
		<TD><I> mod </I></TD>
		<TD><I> C/C++ module (.c file) </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> ln </I></TD>
		<TD><I> Line number of assertion </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 15 </TD>
		<TD rowspan=2> #RKH_TE_FWK_AO ( SYM obj, STR nm ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_AO </TD>
		<TD><I> obj </I></TD>
		<TD><I> Active object memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nm </I></TD>
		<TD><I> Name of object </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=3 align="center"> 16 </TD>
		<TD rowspan=3> #RKH_TE_FWK_STATE ( SYM ao, SYM obj, STR nm ) </TD>
		<TD rowspan=3> \copybrief RKH_TR_FWK_STATE </TD>
		<TD><I> ao </I></TD>
		<TD><I> Active object memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> obj </I></TD>
		<TD><I> State object memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nm </I></TD>
		<TD><I> Name of object </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=3 align="center"> 17 </TD>
		<TD rowspan=3> #RKH_TE_FWK_PSTATE ( SYM ao, SYM obj, STR nm ) </TD>
		<TD rowspan=3> \copybrief RKH_TR_FWK_PSTATE </TD>
		<TD><I> ao </I></TD>
		<TD><I> Active object memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> obj </I></TD>
		<TD><I> Pseudostate object memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nm </I></TD>
		<TD><I> Name of object </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 18 </TD>
		<TD rowspan=2> #RKH_TE_FWK_TIMER ( SYM obj, STR nm ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_TIMER </TD>
		<TD><I> obj </I></TD>
		<TD><I> Timer object memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nm </I></TD>
		<TD><I> Name of object </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 19 </TD>
		<TD rowspan=2> #RKH_TE_FWK_EPOOL ( SYM obj, STR nm ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_EPOOL </TD>
		<TD><I> obj </I></TD>
		<TD><I> Event pool object memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nm </I></TD>
		<TD><I> Name of object </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD rowspan=2 align="center"> 20 </TD>
		<TD rowspan=2> #RKH_TE_FWK_QUEUE ( SYM obj, STR nm ) </TD>
		<TD rowspan=2> \copybrief RKH_TR_FWK_QUEUE </TD>
		<TD><I> obj </I></TD>
		<TD><I> Queue object memory address </I></TD>
	</TR>
	<TR bgColor="#f0f0f0" align="left" valign="middle" >
		<TD><I> nm </I></TD>
		<TD><I> Name of object </I></TD>
	</TR>
</TABLE>
\n

<HR>
\section trtrazer TRAZER - The fundamental RKH's tracing tool

Trazer is a visualization tool that works in conjuntion with the RKH 
framework built in trace facility. Trazer gives the possibility to display 
selectively the recording of all events of your system, state machines, 
queues, timers, etc. Trazer helps you to faster troubleshooting especially on 
complex problems where a debugger is not sufficient, by providing a simple 
consolidated, human-readable textual output. Given the RKH cross plataform 
portability, trace data may come from 8, 16, or 32-bits platforms. In order 
to that Trazer need to be configured to support this diversity of plataform 
and the wide range of RKH framework configurations. 

Here is the \ref trazer

Prev: \ref main_page "Home" \n
Next: \ref cross "Examples"

\page cross Cross-platform demos
\image html rkh_bunner.jpg

Prev: \ref main_page "Home" \n
Next: \ref Download "Download"

This section provides several examples on how to use RKH, designed to 
experiment with RKH immediately. The simplicity of the code and state 
diagrams means it also serves as a good starter project for people who are 
not yet familiar with RKH. Also, this examples are demostration projects 
considered cross-platform, because of they are able to function on more 
than one computer architecture or operating system. 
The code of demos are located in the \c \<rkh\>\\demo\\cross\\ directory, 
where \c \<rkh\> stands for the installation directory chosed to install 
the accompanying software. Each example contains the platform-independent 
source code and a \c platform\\ directory. The structure of the 
platform\\ branch closely mirrors the structure of the 
\c source\\portable\\ directory, which contains platform-specific header 
files and libraries to be used by RKH applications.


\image html rkh_cross.png "RKH cross-platform architecture"

- (1)	Reactive applications. The user code, which defines the active 
		object, state machines, events, and the RKH configurations.
- (2)	RKH framework. Platform-neutral code.
- (3)	Platform abstraction layer, which encapsulates all the 
		platform-specific code (processor, compiler, and operating system) 
		and cleanly separates it from the platform-neutral code, (1) and (2) 
		layers.
- (4)	Board support package (BSP). Platform-dependent files, which 
		implements RKH support on each platform defined by the (3) layer.
- (5)	RKH port. Implements all the platform-specific code, which is defined 
		by processor, hardware, compiler, and operating system in use.
- (6)	Target hardware.

\n RKH cross-platform examples:

- \subpage cross_blinky

Prev: \ref main_page "Home" \n
Next: \ref Download "Download"

\page cfg Configuration
\image html rkh_bunner.jpg

Prev: \ref main_page "Home" \n
Next: \ref Usage "Getting started with RKH"

Each RKH application must have its own configuration file, called 
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\c rkhcfg.h file shows the general layout of the configuration file.
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

<TABLE	align="center" valign="middle" width=80% cellspacing=2 
		cellpadding=4 border=0>
	<TR bgColor="#c0c0c0">
		<TH colspan=5 align="left"><B> Related with Framework (FWK)</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Option </I></B></TH>
		<TH><B><I> Type </I></B></TH>
		<TH><B><I> Range </I></B></TH> 
		<TH><B><I> Default </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_MAX_SMA </TD>
		<TD> integer </TD>
		<TD> [1..64] </TD>
		<TD> 4 </TD>
		<TD align="left"> \copydetails RKH_MAX_SMA </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_EN_DYNAMIC_EVENT </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_EN_DYNAMIC_EVENT </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_MAX_EPOOL </TD>
		<TD> integer </TD>
		<TD> [0..255] </TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_MAX_EPOOL </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SIZEOF_EVENT </TD>
		<TD> integer </TD>
		<TD> [8,16,32] </TD>
		<TD> 8 </TD>
		<TD align="left"> \copydetails RKH_SIZEOF_EVENT </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SIZEOF_ESIZE </TD>
		<TD> integer </TD>
		<TD> [8,16,32] </TD>
		<TD> 8 </TD>
		<TD align="left"> \copydetails RKH_SIZEOF_ESIZE </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_EN_DEFERRED_EVENT </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_EN_DEFERRED_EVENT </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_ASSERT_EN </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_ASSERT_EN </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_HK_EN_DISPATCH </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_HK_EN_DISPATCH </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_HK_EN_SIGNAL </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_HK_EN_SIGNAL </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_HK_EN_TIMEOUT </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_HK_EN_TIMEOUT </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_HK_EN_START </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_HK_EN_START </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_HK_EN_EXIT </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_HK_EN_EXIT </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_IEVENT </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_IEVENT </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TICK_RATE_HZ </TD>
		<TD> integer </TD>
		<TD> [1..1000] </TD>
		<TD> 100 </TD>
		<TD align="left"> \copydetails RKH_TICK_RATE_HZ </TD>
	</TR>
</TABLE>

Back: \ref cfg "Configuring framework RKH"

<HR>
\section cfg_sm Configuration options related to state machine applications 

<TABLE	align="center" valign="middle" width=80% cellspacing=2 
		cellpadding=4 border=0>
	<TR bgColor="#c0c0c0">
		<TH colspan=5 align="left"><B> Related with State Machine Application
				SMA or Active Object</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Option </I></B></TH>
		<TH><B><I> Type </I></B></TH>
		<TH><B><I> Range </I></B></TH> 
		<TH><B><I> Default </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_ID </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_ID </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_GET_INFO </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_GET_INFO </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_STATE_ID </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_STATE_ID </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_PPRO </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_PPRO </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_HCAL </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_HCAL </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_MAX_HCAL_DEPTH </TD>
		<TD> integer </TD>
		<TD> [1..8] </TD>
		<TD> 4 </TD>
		<TD align="left"> \copydetails RKH_SMA_MAX_HCAL_DEPTH </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_MAX_TRC_SEGS </TD>
		<TD> integer </TD>
		<TD> [1..4] </TD>
		<TD> 4 </TD>
		<TD align="left"> \copydetails RKH_SMA_MAX_TRC_SEGS </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_PSEUDOSTATE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_PSEUDOSTATE </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_DEEP_HISTORY </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_DEEP_HISTORY </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_SHALLOW_HISTORY </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_SHALLOW_HISTORY </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_CHOICE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_CHOICE </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_CONDITIONAL </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_CONDITIONAL </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_SUBMACHINE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_SUBMACHINE </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_TRC_SENDER </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD></TD>
		<TD align="left"> \copydetails RKH_SMA_EN_TRC_SENDER </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_INIT_ARG_SMA </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_INIT_ARG_SMA </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_ENT_ARG_SMA </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_ENT_ARG_SMA </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_EXT_ARG_SMA </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_EXT_ARG_SMA </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_ACT_ARG_SMA </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_ACT_ARG_SMA </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_ACT_ARG_EVT </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_ACT_ARG_EVT </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_GRD_ARG_EVT </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_GRD_ARG_EVT </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_GRD_ARG_SMA </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_GRD_ARG_SMA </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_SMA_EN_PPRO_ARG_SMA </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_SMA_EN_PPRO_ARG_SMA </TD>
	</TR>
</TABLE>

Back: \ref cfg "Configuring framework RKH"

<HR>
\section cfg_tr Configuration options related to trace facility

<TABLE	align="center" valign="middle" width=80% cellspacing=2 
		cellpadding=4 border=0>
	<TR bgColor="#c0c0c0">
		<TH colspan=5 align="left"><B> Related with trace facility (TRC)</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Option </I></B></TH>
		<TH><B><I> Type </I></B></TH>
		<TH><B><I> Range </I></B></TH> 
		<TH><B><I> Default </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_RUNTIME_FILTER </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_RUNTIME_FILTER </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_USER_TRACE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_USER_TRACE </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_ALL </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_ALL </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_MP </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_MP </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_RQ </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_RQ </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SMA </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SMA </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_TIM </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_TIM </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_FWK </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_FWK </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_ASSERT </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_ASSERT </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_INIT </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_INIT </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_DCH </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_DCH </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_CLRH </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_CLRH </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_TRN </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_TRN </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_STATE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_STATE </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_ENSTATE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_ENSTATE </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_EXSTATE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_EXSTATE </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_NENEX </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_NENEX </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_NTRNACT </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_NTRNACT </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_TS_STATE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_TS_STATE </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_SM_PROCESS </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_SM_PROCESS </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_NSEQ </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD></TD>
		<TD align="left"> \copydetails RKH_TRC_EN_NSEQ </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_CHK </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_CHK </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_EN_TSTAMP </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_TRC_EN_TSTAMP </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_SIZEOF_TSTAMP </TD>
		<TD> integer </TD>
		<TD> [8,16,32] </TD>
		<TD> 16 </TD>
		<TD align="left"> \copydetails RKH_TRC_SIZEOF_TSTAMP </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_SIZEOF_STREAM </TD>
		<TD> integer </TD>
		<TD> [8,16,32] </TD>
		<TD> 128 </TD>
		<TD align="left"> \copydetails RKH_TRC_SIZEOF_STREAM </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_SIZEOF_POINTER </TD>
		<TD> integer </TD>
		<TD> [8,16,32] </TD>
		<TD> 32 </TD>
		<TD align="left"> \copydetails RKH_TRC_SIZEOF_POINTER </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TRC_SIZEOF_FUN_POINTER </TD>
		<TD> integer </TD>
		<TD> [8,16,32] </TD>
		<TD> 32 </TD>
		<TD align="left"> \copydetails RKH_TRC_SIZEOF_FUN_POINTER </TD>
	</TR>
</TABLE>

Back: \ref cfg "Configuring framework RKH"

<HR>
\section cfg_q Configuration options related to queue facility

<TABLE	align="center" valign="middle" width=80% cellspacing=2 
		cellpadding=4 border=0>
	<TR bgColor="#c0c0c0">
		<TH colspan=5 align="left"><B> Related with queue module (RQ)</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Option </I></B></TH>
		<TH><B><I> Type </I></B></TH>
		<TH><B><I> Range </I></B></TH> 
		<TH><B><I> Default </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_RQ_EN </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_RQ_EN </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_RQ_SIZEOF_NELEM </TD>
		<TD> integer </TD>
		<TD> [8,16,32] </TD>
		<TD> 8 </TD>
		<TD align="left"> \copydetails RKH_RQ_SIZEOF_NELEM </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_RQ_EN_GET_LWMARK </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_RQ_EN_GET_LWMARK </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_RQ_EN_READ </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_RQ_EN_READ </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_RQ_EN_DEPLETE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_RQ_EN_DEPLETE </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_RQ_EN_IS_FULL </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_RQ_EN_IS_FULL </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_RQ_EN_GET_NELEMS </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_RQ_EN_GET_NELEMS </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_RQ_EN_PUT_LIFO </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_RQ_EN_PUT_LIFO </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_RQ_EN_GET_INFO </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_RQ_EN_GET_INFO </TD>
	</TR>
</TABLE>

Back: \ref cfg "Configuring framework RKH"

<HR>
\section cfg_mp Configuration options related to fixed-sized memory block facility

<TABLE	align="center" valign="middle" width=80% cellspacing=2 
		cellpadding=4 border=0>
	<TR bgColor="#c0c0c0">
		<TH colspan=5 align="left"><B> Related with queue module (RQ)</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Option </I></B></TH>
		<TH><B><I> Type </I></B></TH>
		<TH><B><I> Range </I></B></TH> 
		<TH><B><I> Default </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_MP_EN </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_MP_EN </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_MP_REDUCED </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_MP_REDUCED </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_MP_SIZEOF_BSIZE </TD>
		<TD> integer </TD>
		<TD> [8,16,32] </TD>
		<TD> 8 </TD>
		<TD align="left"> \copydetails RKH_MP_SIZEOF_BSIZE </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_MP_SIZEOF_NBLOCK </TD>
		<TD> integer </TD>
		<TD> [8,16,32] </TD>
		<TD> 8 </TD>
		<TD align="left"> \copydetails RKH_MP_SIZEOF_NBLOCK </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_MP_EN_GET_BSIZE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_MP_EN_GET_BSIZE </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_MP_EN_GET_NFREE </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_MP_EN_GET_NFREE </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_MP_EN_GET_LWM </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_MP_EN_GET_LWM </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_MP_EN_GET_INFO </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_MP_EN_GET_INFO </TD>
	</TR>
</TABLE>

Back: \ref cfg "Configuring framework RKH"

<HR>
\section cfg_t Configuration options related to software timer facility

<TABLE	align="center" valign="middle" width=80% cellspacing=2 
		cellpadding=4 border=0>
	<TR bgColor="#c0c0c0">
		<TH colspan=5 align="left"><B> Related with queue module (RQ)</B></TH>
	</TR>
	<TR bgColor="#c0c0c0">
		<TH><B><I> Option </I></B></TH>
		<TH><B><I> Type </I></B></TH>
		<TH><B><I> Range </I></B></TH> 
		<TH><B><I> Default </I></B></TH> 
		<TH><B><I> Description </I></B></TH> 
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TIM_EN </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 1 </TD>
		<TD align="left"> \copydetails RKH_TIM_EN </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TIM_SIZEOF_NTIMER </TD>
		<TD> integer </TD>
		<TD> [8,16,32] </TD>
		<TD> 8 </TD>
		<TD align="left"> \copydetails RKH_TIM_SIZEOF_NTIMER </TD>
	</TR>
	<TR bgColor="#f0f0f0" align="center" valign="middle" >
		<TD align="left"> #RKH_TIM_EN_HOOK </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TIM_EN_HOOK </TD>
	</TR>
	<TR bgColor="#c8cedc" align="center" valign="middle" >
		<TD align="left"> #RKH_TIM_EN_GET_INFO </TD>
		<TD> boolean </TD>
		<TD></TD>
		<TD> 0 </TD>
		<TD align="left"> \copydetails RKH_TIM_EN_GET_INFO </TD>
	</TR>
</TABLE>

Prev: \ref main_page "Home" \n
Next: \ref Usage "Getting started with RKH"
*/


/**
\page Usage Getting started with RKH
\image html rkh_bunner.jpg

Prev: \ref main_page "Home" \n
Next: \ref dbg "Tracing tool"

\n The goal in this section is to explain how to represent a state machine 
using the RKH framework. To do that is proposed a simple example, which is 
shown in the \ref fig1 "Figure 1". Also, this section summarizes the main 
rules and concepts for making the most out of RKH features.

\image html rkh_framework_3.png "RKH Software Architecture"

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
