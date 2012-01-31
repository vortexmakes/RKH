/** \page Installation Installation

The RKH project is organized through a hierarchical directory structure
to facilitate its distribution, support and maintenance.
This structure also includes application examples and demos on several
platforms.

There are several ways of using RKH, one of them is to use the directory 
structure as is and the other is to extract the necessary files for 
including in a particular application.

- \ref using_dir
- \ref using_file

<HR>
\section using_dir Using directory structure

This section describes how to use the RKH directory structure shown in
\ref top_dir "Figure 1 Top level directories".
	
\anchor top_dir
\n
<STRONG> Figure 1 Top level directories </STRONG>
\code
<RKH-root>				- RKH-root directory
|
+---demo				- RKH demo applications
+---doc					- RKH documentation
+---source				- RKH source files
|   copying.txt			- licence file
|   README				- change log file
\	rkh.chm				- reference manual
\endcode

\n <STRONG> RKH source files </STRONG>

The \ref src_dir "Figure 2 RKH source directory" shows the \c \\source 
directory.

\anchor src_dir
\n
<STRONG> Figure 2 RKH source directory </STRONG>
\code
<RKH-root>				- RKH-root directory
|
+---demo				- RKH demo applications
+---doc					- RKH documentation
\---source				- RKH source files
|   |   
|   \---include			- RKH platform-independent include files
|   |       rkh.h		- Framework interface
|   |       rkhassert.h	- Assert definitions
|   |       rkhitl.h	- Internal use only
|   |       rkhplat.h	- Supported and portable platforms
|   |       rkhtrace.h	- Trace facility
|   |       
|   \---portable		- RKH ports
|   |   \---cws08		- Codewarrior for Freescale S08
|   |       rkhport.h	- RKH platform-dependent include file
|   |   \---lnxgcc		- Linux GCC
|   |       rkhport.h	- RKH platform-dependent include file
|   |   \---vc08		- Visual C++ 2008
|   |       rkhport.h	- RKH platform-dependent include file
|   |					
|   |   rkh.c			- RKH platform-independent source code.
|   \   rkhtrace.c		- RKH trace facility source code.
|
|   copying.txt			- licence file
|   README				- change log file
\	rkh.chm				- reference manual
\endcode

- \c \\include: contains platform-independent header files.

- \c \\portable: contains platform-independent header files to be
used by RKH applications. Each platform-dependent file should be 
placed in a directory that represents the platform to be used. 
Each platform directory should be placed within \c \\portable directory, 
i.e.: \c \\portable\\\<platform\>\\rkhport.h. The 
\ref src_dir "Figure 2 RKH source directory" shows three RKH port 
directories: \c \\portable\\cw08 (Codewarrior for Freescale S08), 
\c \\portable\\lnxgcc (Linux GCC), and \c \\portable\\vc08 (Visual C++ 2008).

- \b rkh.c: platform-independent source code of RKH. This file 
requires inclusion of only one platform-specific header file named 
\b rkhport.h. It's indirectly included by \b rkh.h file and it's 
described in detail in section \ref Porting.

- \c rkhtrace.c: platform-independent source code of runtime debugging.

Next, each \b rkhport.h must be referenced from \b rkhplat.h header file,
located in \c \\include directory. The idea behind conditional 
compilation is that a \b rkhport.h can be selectively compiled, depending 
upon whether a specific value has been defined. The next listing shows 
the \b rkhplat.h file according to \c \\portable directory from
\ref src_dir "Figure 2 RKH source directory", where \c ___CWS08__, 
\c ___LNXGCC__, and \c __VC__ are used to instruct the C/C++ compiler 
to include header files from the specific RKH port directory.

\code
#if __CWS08__
	#include "..\portable\cw08\rkhport.h"
#elif __VC__
	#include "..\portable\vc08\rkhport.h"
#elif __LNXGCC__
   	#include "lnxgcc/rkhport.h"	
#else
	#error "rkhplat.h: Missing platform definition."
#endif
\endcode

The path of platform-dependent file must be relative. 

\n \b Demo \b application

Then, should be created a directory within \c \\demo with the name of 
application that will make use of RKH. For example: \c \\demo\\vc08, as
shown in \ref demo_dir "Figure 3 Demo application directories". 
This directory includes the files needed by the application. 
Aditionallity, should be created the RKH configuration file \b rkhcfg.h 
to be included within the application directory. See \ref cfg section. 
This file is mandatory and it's used by RKH.

\anchor demo_dir
\n
<STRONG> Figure 3 Demo application directories </STRONG>
\code
<root>					- RKH-root directory
|
\---demo				- RKH demo applications
|   +---common			- Common source code
|   +---cw08			- Application demo for Codewarrior Freescale S08 platform
|   +---lnxgcc			- Application demo for Linux GCC platform
|   \---vc08			- Application demo for VC08 platform
|	    +---prj			- IDE files.
|		main.c			- main source code
|		my.c			- application source file
|		my.h			- application include file
|		myact.c			- application source file
|		myact.h			- application include file
|		myevt.h			- application include file
|		mylog.txt		- log file
|		rkhcfg.h		- RKH configuration file
|		rkhdata.h		- application include file
|                   
+---doc					- RKH documentation
|                   
+---source				- RKH source files
|   copying.txt			- licence file
|   README				- change log file
\	rkh.chm				- reference manual
\endcode

<HR>
\section using_file Using files

Here proposes to extract from RKH directory structure, detailed	above, 
those files required by RKH to use it in a particular application. 
Therefore, the proposed structure is no longer necessary.

Required source files extracted from \c \\source directory:

\code
rkh.c		- RKH platform-independent source code
rkhtrace.c	- RKH trace tool
\endcode

Required include files extracted from \c \\include directory:

\code
rkh.h		- Framework interface
rkhassert.h	- Assert definitions
rkhitl.h	- Internal use only
rkhplat.h	- Supported and portable platforms
rkhtrace.h	- Trace facility
\endcode

Required include files extracted from \c \\portable\\\<platform\> directory:

\code
rkhport.h	- RKH platform-dependent include file
\endcode

The \c rkhport.h must be referenced from \b rkhplat.h file as shown below:

\code
#include "rkhport.h"
\endcode

\n \b Application

Next, should be created the configuration file \b rkhcfg.h to be included 
within the application directory. See \ref cfg section for more information. 
This file is mandatory and it's used by RKH.


\page Porting Porting

This section describes how to adapt the RKH to various platforms, which
is a process called porting. RKH contains a clearly defined abstraction
layer, which encapsulates all the platform-specific code and cleanly
separates it from platform-neutral code.

Porting RKH implies to create the platform-dependent file, called 
\b rhhport.h. In this file must be defined the data types 
that uses RKH.
The RKH directories and files are described in detail in 
\ref Installation section. The next sections listed below describes 
the aspects to be considered:

- \ref data
- \ref rom
- \ref crt
- \ref dyn
- \ref trc
- \ref files
- \ref rkhp

<HR>
\section data Data types definitions

The RKH uses a set of integer quantities. That maybe machine or compiler
dependent. These types must be defined in \b rkhport.h file as shown 
in \ref rkhp.

- \b rkhint8
	\n \n Denotes a signed integer type with a width of exactly 8 bits.

- \b rkhint16
	\n \n Denotes a signed integer type with a width of exactly 16 bits.

- \b rkhint32
	\n \n Denotes a signed integer type with a width of exactly 32 bits.

- \b rkhuint8
	\n \n Denotes an unsigned integer type with a width of exactly 8 bits.

- \b rkhuint16
	\n \n Denotes an unsigned integer type with a width of exactly 16 bits.

- \b rkhuint32
	\n \n Denotes an unsigned integer type with a width of exactly 32 bits.

- \b HUInt
	\n \n Denotes an unsigned integer type that is usually fastest to operate 
with among all integer types.

- \b HInt
	\n \n Denotes a signed integer type that is usually fastest to operate 
with among all integer types.

\note

The \c HUInt and \c HInt will normally be the Platform-dependentnatural size 
for a particular machine. These types designates an integer 
type that is usually fastest to operate with among all integer 
types.

<HR>
\section rom ROM allocator

For declaring an object that its value will not be changed and that
will be stored in ROM, must be defined in \b rkhport.h the 
\c rkhrom macro, as shown in \ref rkhp.

\code
#define rkhrom
\endcode

The following listing shows an example of such definitions for a
x86 platform and Visual C++ 2008.

\code
typedef signed char 	rkhint8;
typedef signed short 	rkhint16;
typedef signed long		rkhint32;
typedef unsigned char 	rkhuint8;
typedef unsigned short 	rkhuint16;
typedef unsigned long	rkhuint32;

typedef unsigned int	HUInt;
typedef signed int		HInt;

#define rkhrom			const	
\endcode

<HR>
\section crt Critical section

RKH needs to disable interrupts in order to access critical sections of code 
and to reenable interrupts when done. To hide the actual implementation 
method available for a particular processor, compiler, an OS, RKH defines 
the following two macros to disable and enable interrupts 
rkh_enter_critical() and define rkh_exit_critical() respectively. These 
macros are always together to wrap critical sections of code.

\code
#define rkh_enter_critical()
#define rkh_exit_critical()
\endcode

<HR>
\section trc Trace facility

Defines trace facility support. This definitions are required only when the 
user application is used trace facility (of course, RKH_TRACE == 1).
\n See \ref dbg section for more information.

\code
#define rkh_tropen							rkh_trace_open
#define rkh_trclose							rkh_trace_close
#define rkh_trflush							rkh_trace_flush
#define rkh_trgetts							rkh_trace_getts
\endcode

<HR>
\section dyn Dynamic event support

Defines dynamic event support. This definitions are required only when the 
user application is used dynamic event (of course, RKH_EN_DYNAMIC_EVENT == 1).
\n See \ref qref7 section for more information.

\code
#include "rkmpool.h"
#include "queue.h"


#define RKH_DYNE_NUM_POOLS			RKSYS_MPOOL_NUM_POOLS

#define rkh_dyne_init( mpd, pm, ps, bs )							\
				rk_mpool_init( (mpd), (pm), (rkint16)(ps),			\
												(RK_MPBS_T)(bs) )

#define rkh_dyne_event_size( mpd )									\
																	\
				( RK_MPBS_T )rk_mpool_get_blksize( (mpd) )

#define rkh_dyne_get( mpd, e )										\
																	\
				((e) = ( RKHEVT_T* )rk_mpool_get( (mpd) ))

#define rkh_dyne_put( mpd, e )										\
																	\
				rk_mpool_put( (mpd), (e) )

#define rkh_post_fifo( qd, e )										\
				queue_insert( (QD_T)(qd), &(e) )

#define rkh_post_lifo( qd, e )										\
				queue_insert_lifo( (QD_T)(qd), &(e) )

#define rkh_get( qd, e )											\
				queue_remove( (QD_T)(qd), &(e) )
\endcode

<HR>
\section files Platform-dependent files

The header file \b rkhport.h adapts and configures RKH. This
file has already discussed in \ref Installation section. However,
this section includes here again the explanation of this important file.

The \\portable directory contains platform-independent header files to be
used by RKH applications. Each platform-dependent file should be 
placed in a directory that represents the platform to be used, called port
directory. 
Each port directory should be placed within \c \\portable, 
i.e.: \c \\portable\\\<platform\>\\rkhport.h. The 
\ref src_dir "Figure 2 RKH source directory" shows three RKH port 
directories: \c \\portable\\cw08 (Codewarrior for Freescale S08), 
\c \\portable\\lnxgcc (Linux GCC), and \c \\portable\\vc08 (Visual C++ 2008).

Next, each \b rkhport.h must be referenced from \b rkhplat.h header file,
located in \c \\include directory. The idea behind conditional 
compilation is that a \b rkhport.h can be selectively compiled, depending 
upon whether a specific value has been defined. The next listing shows 
the \b rkhplat.h file according to \c \\portable directory from
\ref src_dir "Figure 2 RKH source directory", where \c ___CWS08__,
\c ___LNXGCC__, and \c __VC__ are used to instruct the C/C++ compiler to 
include header files from the specific RKH port directory.

\code
#if __CWS08__
	#include "..\portable\cw08\rkhport.h"
#elif __VC__
	#include "..\portable\vc08\rkhport.h"
#elif __LNXGCC__
   	#include "lnxgcc/rkhport.h"	
#else
	#error "rkhplat.h: Missing platform definition."
#endif
\endcode

The path of platform-dependent file must be relative.

<HR>
\section rkhp "rkhport.h" A port file example

\code
#include "rkhcfg.h"


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

typedef signed char 	rkhint8;
typedef signed short 	rkhint16;
typedef signed long		rkhint32;
typedef unsigned char 	rkhuint8;
typedef unsigned short 	rkhuint16;
typedef unsigned long	rkhuint32;

typedef unsigned int	HUInt;
typedef signed int		HInt;


/*
 * 	Declaring an object rkhrom announces that its value will
 * 	not be changed and it will be stored in ROM.
 */

#define rkhrom			const	


/*
 * 	RKH needs to disable interrupts in order to access critical
 * 	sections of code and to reenable interrupts when done.
 * 	
 * 	To hide the actual implementation method available for a
 * 	particular processor, compiler, an OS, RKH defines the 
 * 	following two macros to disable and enable interrupts 
 * 	rkh_enter_critical() and define rkh_exit_critical() respectively.
 * 	
 * 	These macros are always together to wrap critical sections of
 * 	code.
 */

#define rkh_enter_critical()
#define rkh_exit_critical()


/*
 *	Defines trace facility support.
 *
 *	This definitions are required only when the user application
 *	is used trace facility (of course, RKH_TRACE == 1).
 */

#define rkh_tropen							rkh_trace_open
#define rkh_trclose							rkh_trace_close
#define rkh_trflush							rkh_trace_flush
#define rkh_trgetts							rkh_trace_getts


/*
 *	Defines dynamic event support.
 *
 *	This definitions are required only when the user application
 *	is used dynamic event (of course, RKH_EN_DYNAMIC_EVENT == 1).
 */

#include "rkmpool.h"
#include "queue.h"


#define RKH_DYNE_NUM_POOLS			RKSYS_MPOOL_NUM_POOLS

#define rkh_dyne_init( mpd, pm, ps, bs )							\
				rk_mpool_init( (mpd), (pm), (rkint16)(ps),			\
												(RK_MPBS_T)(bs) )

#define rkh_dyne_event_size( mpd )									\
																	\
				( RK_MPBS_T )rk_mpool_get_blksize( (mpd) )

#define rkh_dyne_get( mpd, e )										\
																	\
				((e) = ( RKHEVT_T* )rk_mpool_get( (mpd) ))

#define rkh_dyne_put( mpd, e )										\
																	\
				rk_mpool_put( (mpd), (e) )

#define rkh_post_fifo( qd, e )										\
				queue_insert( (QD_T)(qd), &(e) )

#define rkh_post_lifo( qd, e )										\
				queue_insert_lifo( (QD_T)(qd), &(e) )

#define rkh_get( qd, e )											\
				queue_remove( (QD_T)(qd), &(e) )
\endcode


\page qref Quick reference

\n
- \ref qref0
- \ref qref1
- \ref qref2
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

\n
<HR>
\section qref0 Defining a state machine

A state machine is defined with the RKH_CREATE_HSM() macro and declared with
the RKH_DCLR_HSM() macro. Frequently, each state machine is encapsulated
inside a dedicated source file (.c file), from which the RKH_CREATE_HSM() 
macro is used, thus the structure definition is in fact entirely encapsulated 
in its module and is inaccessible to the rest of the application. However, as
a general rule, the state machine must be declared inside a header file 
(.h file) by means of RKH_DCLR_HSM() macro.
We will develop one example of state machine creation to illustrate the use 
of this macro. We will give our hierarchical state machine the name \c my. 
If you wanted to create a "flat" state machine, you would use the #FLAT 
parameter rather than the #HCAL parameter.

<b>Defining the state machine</b>
\n
\code
(1)	//	my.c: state-machine's module

	typedef struct
	{
		rkhuint8 argv_channel;
		rkhuint16 argv_timer;
		rkhuint32 argv_density;
	} MYDATA_T;

(2)	static MYDATA_T mydata;


(3) RKH_CREATE_HSM( 	RKH_T, 		// state machine data type
(4) 					my, 		// state machine name
(5) 					0, 			// ID
(6) 					HCAL, 		// hierarchical state machine
(7) 					&S1, 		// initial state
(8) 					my_init, 	// initial action function
(9) 					&mydata );	// associated data
\endcode

<b>Declaring the state machine</b>
\n
\code
//	my.h: state-machine's header file

RKH_DCLR_HSM( my );
\endcode

Explanation

\li (1)	Frequently, each state machine is encapsulated inside a dedicated 
		source file (.c file), from which the RKH_CREATE_HSM() macro is used.
\li (2)	In this example, \c mydata structure is used like an argc/argv. 
\li (3)	The RKH_T defines the \c my state machine structure.
		On the other hand, almost every state machine must also store other 
		"extended-state" information. You supply this additional information 
		by means of data members enlisted after the base structure member
		\c sm. The following example illustrates how to derive an 
		state machine from RKH_T. 
		Please note that the RKH_T member \c sm is defined as the FIRST 
		member of the derived struct.
		RKH_T is not intended to be instantiated directly, but rather serves 
		as the base structure for derivation of state machines in the 
		application code.
\code
typedef struct
{
	RKH_T sm;		// base structure
	rkhuint8 x;		// private member
	rkhuint8 y;		// private member
} MYSM_T;

//	static instance of state machine object
RKH_CREATE_HSM( MYSM_T, my, 0, HCAL, &S1, my_init, &mydata );
\endcode

\li (4)	\c my is the state machine. Represents the top state of state diagram. 
\li (5)	\c 0 is the state machine descriptor. This number allows to uniquely 
		identify a state machine.
\li (6)	the \c my state machine is defined as a hierarchical state machine. 
		The available property options are enumerated in RKH_HPPTY_T 
		enumeration in the \b rkh.h file.
\li (7)	\c S1 is the initial state.
\li (8)	the \c my_init() function defines the topmost initial transition in 
		the \c my state machine. 
		The function prototype is defined as RKHINIT_T. This argument is 
		(optional), thus it could be declared as NULL. The application code 
		must trigger the initial transition explicitly by invoking 
		rkh_init_hsm() function.
\li (9) \c mydata is used like a argc/argv. This argument is optional, thus 
		it could be declared as NULL or eliminated with RKH_EN_HSM_DATA 
		option. Could be used to pass arguments to the state machine like 
		an argc/argv.

\b Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\ref rkhcfg_h shows the general layout of the \b rkhcfg.h header file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_EN_HSM_NAME:	When RKH_EN_HSM_NAME is set to one (1) the state 
						machine structure RKH_T includes its own name as a 
						null-terminated string. When a particular application 
						requires runtime debugging (native tracing features), 
						this option must be enabled.
- \b RKH_EN_HSM_DATA:	When RKH_EN_HSM_DATA is set to one (1) the state 
						machine structure RKH_T allows to reference a data 
						object, which maintains additional information.
- \b RKH_EN_HSM_ID:		When RKH_EN_HSM_ID is set to one (1) the state machine
						structure RKH_T includes a ID number that could be
						used to uniquely identify a state machine, also called
						state machine descriptor. When a particular application 
						requires runtime debugging (native tracing features), 
						this option must be enabled.

<HR>
\section qref1 Defining a superstate

A superstate or composite state is defined with the RKH_CREATE_COMP_STATE()
macro and declared with the RKH_DCLR_COMP_STATE() macro. Frequently, each 
state machine and its states (superstates and substates) are encapsulated 
inside a dedicated source file (.c file), from which the 
RKH_CREATE_COMP_STATE() macro is used.
We will develop one example of composite state definition to illustrate the 
use of this macro. We will give our composite state the name \c S1. 

<b>Defining a composite state</b>
\n
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

<b>Declaring a composite state</b>
\n
\code
//	my.h: state-machine's header file

RKH_DCLR_COMP_STATE( S1 );
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

\b Customization

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\ref rkhcfg_h shows the general layout of the \b rkhcfg.h header file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_EN_HCAL:	Enable (1) or disable (0) the state nesting.
					When RKH_EN_HCAL is set to zero (0) some important 
					features of RKH are	not included: state nesting, 
					composite state, history (shallow and deep)
					pseudostate, entry action, and exit action.
- \b RKH_EN_STATE_NAME:	When RKH_EN_STATE_NAME is set to one (1) the state 
					structure includes its own name as a null-terminated 
					string. When a particular application requires runtime 
					debugging, this option must be enabled. 
					See #RKHBASE_T structure definition.
- \b RKH_EN_STATE_ID:
					When RKH_EN_STATE_ID is set to one (1) the state structure 
					includes an ID number (also called descriptor). 
					This number allows to uniquely identify a state. 
					When a particular application requires runtime debugging 
					(native tracing features), this option must be enabled. 

<HR>
\section qref2 Defining a basic state

A basic state (also called substate) is defined with the 
RKH_CREATE_BASIC_STATE() macro and declared with the RKH_DCLR_BASIC_STATE() 
macro. Frequently, each state machine and its states (superstates and 
substates) are encapsulated inside a dedicated source file (.c file), from 
which the RKH_CREATE_BASIC_STATE() macro is used.
We will develop one example of basic state definition to illustrate the 
use of this macro. We will give our basic state the name \c S11. 
As will demostrates the use of RKH_CREATE_BASIC_STATE() macro and its
arguments is very similar to RKH_CREATE_COMP_STATE() macro.

<b>Defining a basic state</b>
\n
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
\n
\code
//	my.h: state-machine's header file

RKH_DCLR_BASIC_STATE( S11 );
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
\ref rkhcfg_h shows the general layout of the \b rkhcfg.h header file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_EN_STATE_NAME:	When RKH_EN_STATE_NAME is set to one (1) the state 
					structure includes its own name as a null-terminated 
					string. When a particular application requires runtime 
					debugging, this option must be enabled. 
					See #RKHBASE_T structure definition.
- \b RKH_EN_STATE_ID:
					When RKH_EN_STATE_ID is set to one (1) the state structure 
					includes an ID number (also called descriptor). 
					This number allows to uniquely identify a state. 
					When a particular application requires runtime debugging 
					(native tracing features), this option must be enabled. 

<HR>
\section qref16 Defining a state transition table

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

<HR>
\section qref3 Defining a conditional pseudostate

A conditional pseudostate (also called choice pseudostate) is defined with 
the RKH_CREATE_COND_STATE() macro and declared with the 
RKH_DCLR_COND_STATE() macro. Frequently, each state machine and its 
states and pseudostates are encapsulated inside a dedicated source file 
(.c file), from which the RKH_CREATE_COND_STATE() macro is used.
We will develop one example of choice pseudostate definition to 
illustrate the use of this macro. We will give our choice pseudostate 
the name \c C1. As will demostrates the use of RKH_CREATE_COND_STATE() 
macro and its arguments is very similar to RKH_CREATE_BASIC_STATE() macro.

<b>Defining a choice pseudostate</b>
\n
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_COND_STATE( 	C1, 
(3)							0 );
\endcode

<b>Declaring a choice pseudostate</b>
\n
\code
//	my.h: state-machine's header file

RKH_DCLR_COND_STATE( C1 );
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
\ref rkhcfg_h shows the general layout of the \b rkhcfg.h header file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_EN_HCAL:	Enable (1) or disable (0) the state nesting.
					When RKH_EN_HCAL is set to zero (0) some important 
					features of RKH are	not included: state nesting, 
					composite state, history (shallow and deep)
					pseudostate, entry action, and exit action.
- \b RKH_EN_STATE_NAME:	When RKH_EN_STATE_NAME is set to one (1) the state 
					structure includes its own name as a null-terminated 
					string. When a particular application requires runtime 
					debugging, this option must be enabled. 
					See #RKHBASE_T structure definition.
- \b RKH_EN_STATE_ID:
					When RKH_EN_STATE_ID is set to one (1) the state structure 
					includes an ID number (also called descriptor). 
					This number allows to uniquely identify a state. 
					When a particular application requires runtime debugging 
					(native tracing features), this option must be enabled. 
- \b RKH_EN_PSEUDOSTATE: Enable (1) or disable (0) the pseudostates usage.
- \b RKH_EN_CONDITIONAL: Enable (1) or disable (0) the conditional connector 
					usage.
- \b RKH_MAX_TR_SEGS: Determines the maximum number of linked transition 
					segments. The smaller this number, the lower the static 
					RAM consumption. Typically, the most of hierarchical 
					state machines uses up to 4 transition segments. 
					Currently RKH_MAX_TR_SEGS cannot exceed 8.

<HR>
\section qref17 Defining a branch table

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

<HR>
\section qref4 Defining a shallow history pseudostate

A shallow history pseudostate is defined with the 
RKH_CREATE_SHALLOW_HISTORY_STATE() macro and declared with the 
RKH_DCLR_SHIST_STATE() macro. Frequently, each state machine and its 
states and pseudostates are encapsulated inside a dedicated source file 
(.c file), from which the RKH_CREATE_SHALLOW_HISTORY_STATE() macro is used.
We will develop one example of shallow history pseudostate definition to 
illustrate the use of this macro. We will give our history pseudostate 
the name \c H1. As will demostrates the use of RKH_CREATE_SHALLOW_HISTORY_STATE() 
macro and its arguments is very similar to RKH_CREATE_COND_STATE() macro.

<b>Defining a shallow history pseudostate</b>
\n
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_SHALLOW_HISTORY_STATE(	H1, 
(3)										6,
(4)										&S1 );
\endcode

<b>Declaring a shallow history pseudostate</b>
\n
\code
//	my.h: state-machine's header file

RKH_DCLR_DHIST_STATE( H1 );
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
\ref rkhcfg_h shows the general layout of the \b rkhcfg.h header file.
Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_EN_HCAL:	Enable (1) or disable (0) the state nesting.
					When RKH_EN_HCAL is set to zero (0) some important 
					features of RKH are	not included: state nesting, 
					composite state, history (shallow and deep)
					pseudostate, entry action, and exit action.
- \b RKH_EN_STATE_NAME:	When RKH_EN_STATE_NAME is set to one (1) the state 
					structure includes its own name as a null-terminated 
					string. When a particular application requires runtime 
					debugging, this option must be enabled. 
					See #RKHBASE_T structure definition.
- \b RKH_EN_STATE_ID: When RKH_EN_STATE_ID is set to one (1) the state 
					structure includes an ID number (also called descriptor). 
					This number allows to uniquely identify a state. 
					When a particular application requires runtime debugging 
					(native tracing features), this option must be enabled. 
- \b RKH_EN_PSEUDOSTATE: Enable (1) or disable (0) the pseudostates usage.
- \b RKH_EN_SHALLOW_HISTORY: Enable (1) or disable (0) the shallow history 
					usage.
- \b RKH_MAX_TR_SEGS: Determines the maximum number of linked transition 
					segments. The smaller this number, the lower the static 
					RAM consumption. Typically, the most of hierarchical 
					state machines uses up to 4 transition segments. 
					Currently RKH_MAX_TR_SEGS cannot exceed 8.

<HR>
\section qref5 Defining a deep history pseudostate

A deep history pseudostate is defined with the 
RKH_CREATE_DEEP_HISTORY_STATE() macro and declared with the 
RKH_DCLR_DHIST_STATE() macro. Frequently, each state machine and its 
states and pseudostates are encapsulated inside a dedicated source file 
(.c file), from which the RKH_CREATE_DEEP_HISTORY_STATE() macro is used.
We will develop one example of deep history pseudostate definition to 
illustrate the use of this macro. We will give our history pseudostate 
the name \c H2. As will demostrates the use of 
RKH_CREATE_DEEP_HISTORY_STATE() macro and its arguments is very 
similar to RKH_CREATE_SHALLOW_HISTORY_STATE() macro.

<b>Defining a deep history pseudostate</b>
\n
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_DEEP_HISTORY_STATE(	H1, 
(3)									7,
(4)									&S21 );
\endcode

<b>Declaring a shallow history pseudostate</b>
\n
\code
//	my.h: state-machine's header file

RKH_DCLR_DHIST_STATE( H1 );
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
\ref rkhcfg_h shows the general layout of the \b rkhcfg.h header file.
Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_EN_HCAL:	Enable (1) or disable (0) the state nesting.
					When RKH_EN_HCAL is set to zero (0) some important 
					features of RKH are	not included: state nesting, 
					composite state, history (shallow and deep)
					pseudostate, entry action, and exit action.
- \b RKH_EN_STATE_NAME:	When RKH_EN_STATE_NAME is set to one (1) the state 
					structure includes its own name as a null-terminated 
					string. When a particular application requires runtime 
					debugging, this option must be enabled. 
					See #RKHBASE_T structure definition.
- \b RKH_EN_STATE_ID: When RKH_EN_STATE_ID is set to one (1) the state 
					structure includes an ID number (also called descriptor). 
					This number allows to uniquely identify a state. 
					When a particular application requires runtime debugging 
					(native tracing features), this option must be enabled. 
- \b RKH_EN_PSEUDOSTATE: Enable (1) or disable (0) the pseudostates usage.
- \b RKH_EN_DEEP_HISTORY: Enable (1) or disable (0) the deep history 
					usage.
- \b RKH_MAX_TR_SEGS: Determines the maximum number of linked transition 
					segments. The smaller this number, the lower the static 
					RAM consumption. Typically, the most of hierarchical 
					state machines uses up to 4 transition segments. 
					Currently RKH_MAX_TR_SEGS cannot exceed 8.

<HR>
\section qref6 Defining a junction pseudostate

A conditional pseudostate (also called branch pseudostate) is defined with 
the RKH_CREATE_JUNCTION_STATE() macro and declared with the 
RKH_DCLR_JUNC_STATE() macro. Frequently, each state machine and its 
states and pseudostates are encapsulated inside a dedicated source file 
(.c file), from which the RKH_CREATE_JUNCTION_STATE() macro is used.
We will develop one example of junction pseudostate definition to 
illustrate the use of this macro. We will give our junction pseudostate 
the name \c J1. As will demostrates the use of RKH_CREATE_JUNCTION_STATE() 
macro and its arguments is very similar to RKH_CREATE_BASIC_STATE() macro.

<b>Defining a junction pseudostate</b>
\n
\code
(1)	//	my.c: state-machine's module

(2)	RKH_CREATE_JUNCTION_STATE( 	J1, 
(3)								8, 
(4)								dis_all_modules, 
(6)								&S1 );
\endcode

<b>Declaring a junction pseudostate</b>
\n
\code
//	my.h: state-machine's header file

RKH_DCLR_JUNC_STATE( J1 );
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
\ref rkhcfg_h shows the general layout of the \b rkhcfg.h header file.

Use the following macros to reduce the memory taken by state machine 
structure. See \ref cfg section for more information. 

- \b RKH_EN_HCAL:	Enable (1) or disable (0) the state nesting.
					When RKH_EN_HCAL is set to zero (0) some important 
					features of RKH are	not included: state nesting, 
					composite state, history (shallow and deep)
					pseudostate, entry action, and exit action.
- \b RKH_EN_STATE_NAME:	When RKH_EN_STATE_NAME is set to one (1) the state 
					structure includes its own name as a null-terminated 
					string. When a particular application requires runtime 
					debugging, this option must be enabled. 
					See #RKHBASE_T structure definition.
- \b RKH_EN_STATE_ID:
					When RKH_EN_STATE_ID is set to one (1) the state structure 
					includes an ID number (also called descriptor). 
					This number allows to uniquely identify a state. 
					When a particular application requires runtime debugging 
					(native tracing features), this option must be enabled. 
- \b RKH_EN_PSEUDOSTATE: Enable (1) or disable (0) the pseudostates usage.
- \b RKH_EN_JUNCTION: Enable (1) or disable (0) the junction connector usage.
- \b RKH_MAX_TR_SEGS: Determines the maximum number of linked transition 
					segments. The smaller this number, the lower the static 
					RAM consumption. Typically, the most of hierarchical 
					state machines uses up to 4 transition segments. 
					Currently RKH_MAX_TR_SEGS cannot exceed 8.

<HR>
\section qref14 Actions

This section summarize the functions and its prototypes used by RKH 
framework. As mentioned before, the framework make use the callbacks, i.e. 
pointer to functions, in most of its data structures by means of 
RKH_CREATE_HSM(), RKH_CREATE_COMP_STATE(), 
RKH_CREATE_BASIC_STATE(), RKH_TRINT(), RKH_TRREG(), RKH_BRANCH(), 
RKH_CREATE_SHALLOW_HISTORY_STATE(), RKH_CREATE_DEEP_HISTORY_STATE(), and 
RKH_CREATE_JUNCTION_STATE() macros.
Obviously, the set of available functions and its configurations 
is mandatory to known for properly using the framework. 

<b>Initialization action</b>

\copydetails RKHINIT_T

As said above, the application must explicitly trigger initial transitions 
in all state machines.

\code
rkh_init_hsm( manager );		// calls manager's initial action
rkh_init_hsm( gps );			// calls gps's initial action
\endcode

The next listing shows an example of the initial action implementation.

\code
void 
manager_init( const struct rkh_t *ph )
{
	printf( "Init \"%s\" state machine ", rkh_get_sm_name( ph ) );
	printf( "with initial state %s\n", rkh_get_cstate_name( ph ) );
}
\endcode

<b>Exit action</b>

\copydetails RKHEXT_T

The next listing shows an example of the exit action implementation.

\code
void 
idle_exit( const struct rkh_t *ph )
{
	printf( "Exit from "IDLE" state\n" );
}
\endcode

<b>Entry action</b>

\copydetails RKHENT_T

The next listing shows an example of the entry action implementation.

\code
void 
wait_process_entry( const struct rkh_t *ph )
{
	printf( "Entry to "WAIT_PROCESS" state\n" );
}
\endcode

<b>Transition action</b>

\copydetails RKHACT_T

The next listing shows an example of the transition action implementation.

\code
void 
set_config( const struct rkh_t *ph, RKHEVT_T *pe )
{
	printf( "From state machine \"%s\" ", rkh_get_sm_name( ph ) );
	printf( "- %s -\n", __FUNCTION__ );
	printf( "data = %02d\n", pe->e );
}
\endcode

<b>Event preprocessor</b>

\copydetails RKHPPRO_T

The next listing shows an example of the event preprocessor 
action implementation.

\code
RKHE_T 
preprocess_keys( const struct rkh_t *ph, RKHEVT_T *pe )
{
	printf( "From state machine \"%s\"\n", rkh_get_sm_name( ph ) );
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
is_zero( const struct rkh_t *ph, RKHEVT_T *pe )
{
	return get_water_level( CHANNEL( (( CHEVT_T* )pe)->ch ) ) == 0;
}
\endcode

<HR>
\section qref12 Using events with parameters

An event can have associated parameters, allowing the event 
instance to convey not only the occurrence of some interesting 
incident but also quantitative information regarding that occurrence.
Implementing the single inheritance in C is very simply by literally
embedding the base structure, RKHEVT_T in this case, as the first 
member of the derived structure.
For example, the structure MYEVT_T derived from the base structure 
RKHEVT_T by embedding the RKHEVT_T instance as the first member of 
MYEVT_T.

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

See also rkh_put_fifo(), rkh_put_lifo(), rkh_alloc_event(), 
rkh_set_static_event(), and rkh_gc().

<HR>
\section qref7 Using dynamic and static events

In RKH as other frameworks, the actual event instances are either constant 
events (or static events) statically allocated at compile time or dynamic events
allocated at runtime from one of the event pools that the framework manages.

<b>Allocating events</b>

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

(3) static const RKHEVT_T offh = { OFFHOOK, 0 };
(4) static TOUT_T tout;

...

(5) rkh_set_static_event( &tout, TIMEOUT );
(6)	DIAL_T *de = rkh_alloc_event( DIAL_T, DIALED );
(7)	SETUP_T *se = rkh_alloc_event( SETUP_T, SET_CONFIG );
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
\li (6-7) 	The rkh_alloc_event() macro dynamically creates a new instances 
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
#define mkse( e, n )		{ { (e), 0 }, (n) }
#else
#define mkse( e, n )		{ { (e), 0 } }
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

<b>Posting events</b>

The RKH framework supports one type of asynchronous event exchange: the 
simple mechanism of direct event posting supported through the functions
rkh_put_fifo() and rkh_put_lifo(), when the producer of an event directly 
posts the event to the event queue of the consumer active object.

\code
(1)	rkh_put_fifo( QUEUE_MGR, ( RKHEVT_T* )de );
\endcode

\li (1)	The dynamic event is posted directly to the \c QUEUE_MGR queue.

\code
(1)	rkh_put_fifo( QUEUE_COMM, ( RKHEVT_T* )&tout );
\endcode

\li (1)	The static events are posted directly to the \c QUEUE_COMM queue.

<b>Recycling dynamic events</b>

If the system make use of dynamic events facility after the processing, 
you must not forget to call the RKH garbage collector, because now RKH is 
no longer in charge of event processing and you are solely responsible for 
not leaking the event.
The garbage collector actually recycles the event only when it determines 
that the event is no longer referenced.

\code
	void
    main( void )
    {
		...

        forever
        {
			...
(1)			rkh_engine( manager, &e );
(2)			rkh_gc( &e );
        }
    }
\endcode

\li (1)	The event \c e is dispatched to the state machine \c manager for 
		processing.
\li	(2) The event \c e is passed to the RKH garbage collector for recycling. 
		As described above, the rkh_gc() function actually recycles the 
		event only when it determines that the event is no longer referenced.

<HR>
\section qref13 Preprocessing events before of dispatch it

\copydetails RKHPPRO_T

The next listing shows an example of the event preprocessor 
action implementation.

\code
RKHE_T 
preprocess_keys( const struct rkh_t *ph, RKHEVT_T *pe )
{
	printf( "From state machine \"%s\"\n", rkh_get_sm_name( ph ) );
    if( pe->e >= 0 && pe->e <= 9 )
        return DECIMAL;
    if( pe->e == '.' )
        return POINT;
    else
        return pe->e;
}
\endcode

<HR>
\section qref8 Deferring and recalling events

Event deferral comes in very handy when an event arrives in a 
particularly inconvenient moment but can be deferred for some later time, 
when the system is in a much better position to handle the event. RKH 
supports very efficient event deferring and recalling mechanisms.
RKH provides a simple function call to defer an event to a given separate 
event queue, rkh_defer(). Also, offers another simple function to recall 
a deferred event, rkh_recall().

An active object uses <c>rkh_defer( qd, evt )</c> to defer an event \a evt to 
the event queue \a qd. RKH correctly accounts for another outstanding 
reference to the event and will not recycle the event at the end of the 
RTC step. 
\note
For memory efficiency and best performance the deferred event queue, 
STORE ONLY POINTERS to events, not the whole event objects.
An active object can use multiple event queues to defer events of
different kinds.
The assertion inside it guarantee that operation is valid, so is not 
necessary to check the value returned from it.

Later, the active object might recall one event at a time from the 
event queue by means of <c>rkh_recall( qdd, qds )</c> function. Recalling an 
event means that it is removed from the deferred event queue \a qds 
and posted (LIFO) to the event queue of the active object \a qdd.
\note
For memory efficiency and best performance the destination event queue, 
STORE ONLY POINTERS to events, not the whole event objects.
The pointer to the recalled event to the caller, or NULL if no 
event has been recalled.

<HR>
\section qref9 Using assertions

\copydetails rkhassert.h

<HR>
\section qref10 Debugging an application based on RKH's state machines

Please refer to \ref dbg section. 

<HR>
\section qref15 Initializing a state machine and dispatching events

The following listing shows an example of the main() function 
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
	main( void )
	{
		int c;

(1)		rkh_init_hsm( my );
		srand( ( unsigned )time( NULL ) );

		print_banner();
(2)		rkh_trace_open();

(3)		forever
		{
(4)			c = mygetch();
			
			if( c == 'p' )
(5)				rkh_trace_flush();
			else if ( c == ESC )
(6)				break;
			else if ( c == 'r' )
(7)				rkh_init_hsm( my );
			else
			{
(8)				rkh_set_static_event( &mye, kbmap( c ) );
(9)				mye.ts = ( rkhuint16 )rand();
(10)			rkh_engine( my, ( RKHEVT_T* )&mye );
			}
		}

(11)	rkh_trace_close();
	}
\endcode

\li (1) Initialize the "my" state machine. RKH invokes the init action.
\li (2) Initialize and open the RKH debug session.
\li (3) This is the event loop of the RKH framework.
\li (4) Gets key pressed from the standard input.
\li (5) Flushs the trace stream to the desired host.
\li (6) Terminates the program.
\li (7) Reinitialize the state machine.
\li (8) The	event generated by pressing a key on the keyboard is stored 
		in the signal member of MYEVT_T structure.
\li (9)	The	event has associated parameters that convey a random number.
\li (10)	The \c mye event is dispatched to "my" state machine by means of 
		rkh_engine() function. Events with parameters, such as the MYEVT_T, 
		require explicit casting from the generic base structure #RKHEVT_T 
		to the specific derived structure MYEVT_T.
\li (11)	Terminates the program and close debug session.

\page dbg Debugging tool

When a program needs to be traced, it has to generate some information 
each time it reaches a "significant step" (certain instruction in the 
program's source code). In the standard terminology, this step is called 
a trace point, and the tracing information which is generated at that 
point is called a trace event. A program containing one or more of this 
trace points is named instrumented application.

There is one class of trace events: RKH trace events, which are generated 
by the RKH source code. The \c #RKHTREVT_T structure describes the RKH trace 
event.

The definition of events and the mapping between these and their 
corresponding names is hard-coded in the RKH implementation. Therefore, 
these events are common for all the state machine applications and never 
change (they are always traced). 
The trace events are associated with a integer value and are explicity 
listed and defined (enumerated) as shown below in this section.
	
The standard defines that the trace system has to store some information 
or each trace event (also named arguments) being generated, including, 
t least, the following:

- the trace event identifier (\c #RKHTR_EVENTS enumerated list),
- instrumented application (state machine),
- a timestamp (optional),
- any extra data that the system wants to associate with the event 
(optional).

When the RKH reachs a trace point, all the information related to 
it has to be stored somewhere before it can be retrieved, in order to 
be analyzed. This place is named trace stream.

Each trace points cannot be changed but RKH allows enable/disable it
in compile-time by means of C/C++ preprocessor. The \ref cfg section
shows how to make that.

- \ref trusing
- \ref trcfg
- \ref trexample

<HR>
\section trusing Using tracing tool

- The option \b RKH_TRACE must be set to one (1), it should be defined in 
the specific application configuration file named \b rkhcfg.h. 

- The trace events of interest must be defined in the \b rkhcfg.h file. See
\b #RKHTR_EVENTS enumeration and \ref trcfg section.

- The rkh_trace_open(), rkh_trace_close(), rkh_trace_flush(), and 
rkh_trace_getts() are platform-dependent functions, therefore the user
application must implement it. These function prototypes are definied
within \b rkhtrace.h file.
This functions are invoked through the rkh_tropen(), rkh_trclose(), 
rkh_trflush(), and rkh_trgetts() macros. 

- The RKH_EN_TIMESTAMP, RKH_SIZEOF_TIMESTAMP, RKH_MAX_NUM_TRACES, 
RKH_EN_TRACE_STRING, and RKH_MAX_TRACE_STRING_SIZE preprocessor options 
configures the \c #RKHTREVT_T trace event structure and should be defined 
in the \b rkhcfg.h file.

- See \b rkhtrace.h header file for more information.

<HR>
\section trcfg Trace tool configuration

The \ref cfg section shows the trace event configuration options. However,
are listed again to be described in detail. 

- \b RKH_EN_EVENT
\n \n Records the ocurred event in decimal format. See \c #RKHE_T typedef.

- \b RKH_EN_TRN_SRC
\n \n Records the identification number and string name of the transition 
source state. 

- \b RKH_EN_TRN_TGT
\n \n Records the identification number and string name of the transition 
target state.

- \b RKH_EN_NXT_STATE
\n \n Records the identification number and string name of the next state.

- \b RKH_EN_INT_TRAN
\n \n Records an internal transition.

- \b RKH_EN_ENTRY
\n \n Records the identification number and string name of the entered state.

- \b RKH_EN_EXIT
\n \n Records the identification number and string name of the exited state.

- \b RKH_EN_INIT_HSM
\n \n Records the initialization process of state machine.

- \b RKH_EN_SGT_TGT
\n \n Records the identification number and string name of the transition segment
target state.

- \b RKH_EN_RTN_CODE
\n \n Records the code returned by rkh_engine() functionm in decimal format.
See \c #RKH_RCODE_T enumeration.

- \b RKH_EN_NUM_ENEX
\n \n Records the number of entered and exited states.

- \b RKH_EN_NUM_ACTSGT
\n \n Records the number of transition actions and transition segments.

<HR>
\section trexample Example use

The following listing shows an implementation example of rkh_trace_open(), 
rkh_trace_close(), rkh_trace_flush(), and rkh_trace_getts() functions:

\code
void 
rkh_trace_open( void )
{
	rkh_trinit();
	rkh_trconfig( MY, RKH_TRLOG, RKH_TRPRINT );
	rkh_trcontrol( MY, RKH_TRSTART );

	if( ( fdbg = fopen( "../mylog.txt", "w+" ) ) == NULL )
	{
		perror( "Can't open file\n" );
		exit( EXIT_FAILURE );
	}

	fprintf( fdbg, "---- RKH trace log session - "__DATE__" - "__TIME__" ----\n\n" );
}


void 
rkh_trace_close( void )
{
	fclose( fdbg );
}


void 
rkh_trace_flush( void )
{
	RKHTREVT_T te;
	RKHTRCFG_T *pcfg;

	while( rkh_trgetnext( &te ) != RKH_TREMPTY )
	{
		pcfg = rkh_trgetcfg( te.smix );

		if( pcfg->log == RKH_TRLOG )
			fprintf( fdbg, "%05d [ %-16s ] - %s : %s\n",
													rkh_trgetts(),
													tremap[ te.id ],
													smmap[ te.smix ],
													format_trevt_args( &te ) );
		if( pcfg->print == RKH_TRPRINT )
			printf( "%05d [ %-16s ] - %s : %s\n",
													rkh_trgetts(),
													tremap[ te.id ],
													smmap[ te.smix ],
													format_trevt_args( &te ) );
	}
}


RKHTS_T 
rkh_trace_getts( void )
{
	return ( RKHTS_T )clock();
}
\endcode

According to example shown above the following shows a fragment of 
output generated:

\code
---- RKH trace log session - Jun 10 2010 - 11:00:42 ----

00097 [ RKHTR_INIT_HSM   ] - MY : is = S1 [0]
00097 [ RKHTR_ENTRY      ] - MY : S1 [0]
00097 [ RKHTR_ENTRY      ] - MY : S11 [0]
00097 [ RKHTR_ENTRY      ] - MY : S111 [0]
00098 [ RKHTR_EVENT      ] - MY : 15
00098 [ RKHTR_TRN_SRC    ] - MY : S111 [0]
00098 [ RKHTR_INT_TRAN   ] - MY : 
00098 [ RKHTR_NUM_ACTSGT ] - MY : 0 - 0
00098 [ RKHTR_RTN_CODE   ] - MY : RKH_OK
00099 [ RKHTR_EVENT      ] - MY : 5
00099 [ RKHTR_TRN_SRC    ] - MY : S111 [0]
00099 [ RKHTR_TRN_TGT    ] - MY : C11 [0]
00100 [ RKHTR_SGT_TGT    ] - MY : C11 [0]
00102 [ RKHTR_SGT_TGT    ] - MY : S21 [0]
00102 [ RKHTR_NUM_ENEX   ] - MY : 2 - 3
00104 [ RKHTR_EXIT       ] - MY : S111 [0]
00104 [ RKHTR_EXIT       ] - MY : S11 [0]
00104 [ RKHTR_EXIT       ] - MY : S1 [0]
00104 [ RKHTR_NUM_ACTSGT ] - MY : 2 - 2
00104 [ RKHTR_ENTRY      ] - MY : S2 [0]
00104 [ RKHTR_ENTRY      ] - MY : S21 [0]
00104 [ RKHTR_NXT_STATE  ] - MY : S21 [0]
00105 [ RKHTR_RTN_CODE   ] - MY : RKH_OK
\endcode


\page cfg Configuration

Each RKH application must have its own configuration file, called 
\b rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\ref rkhcfg_h shows the general layout of the \b rkhcfg.h header file.

Available options:

- 	\b RKH_EN_HCAL
	\n \n Enable (1) or disable (0) the state nesting.
	When RKH_EN_HCAL is set to zero (0) some important features of RKH are
	not included: state nesting, composite state, history (shallow and deep)
	pseudostate, entry action, and exit action.

- 	\b RKH_MAX_HCAL_DEPTH
	\n \n Determines the maximum number of hierarchical levels. The smaller
	this number, the lower the static RAM consumption. Typically, the most 
	of hierarchical state machines uses up to 4 levels.	Currently 
	RKH_MAX_HCAL_DEPTH cannot exceed 8. 

- 	\b RKH_MAX_TR_SEGS
	\n \n Determines the maximum number of linked transition segments. 
	The smaller this number, the lower the static RAM consumption. 
	Typically, the most of hierarchical state machines uses 
	up to 4 transition segments. Currently RKH_MAX_TR_SEGS cannot 
	exceed 8. 

-	\b RKH_NUM_STATE_MACHINES
	\n \n Number of used state machines.

-	\b RKH_SIZEOF_EVENT
	\n \n Determines the size [in bits] of the RKH event representation 
	#RKHE_T. Valid values: 8, 16 or 32. Default 8.

-	\b RKH_EN_DYNAMIC_EVENT
	\n \n Enable (1) or Disable (0) dynamic event support.

-	\b RKH_EN_DEFERRED_EVENT
	\n \n Enable (1) or Disable (0) deferred event support. 
	For using this feature the dynamic event support must be set to one.

-	\b RKH_EN_PSEUDOSTATE
	\n \n Enable (1) or disable (0) the pseudostates usage.

-	\b RKH_EN_DEEP_HISTORY
	\n \n Enable (1) or disable (0) the deep history usage.

-	\b RKH_EN_SHALLOW_HISTORY
	\n \n Enable (1) or disable (0) the shallow history usage.

-	\b RKH_EN_JUNCTION
	\n \n Enable (1) or disable (0) the junction connector usage.

-	\b RKH_EN_CONDITIONAL
	\n \n Enable (1) or disable (0) the conditional connector usage.

-	\b RKH_EN_INIT_HSM_ARG
	\n \n Determines the initialization function prototype of the
	state machines. When RKH_EN_INIT_HSM_ARG is set to one (1) this
	function adds as argument a pointer to state machine structure 
	RKH_T. See #RKHINIT_T structure definition.

-	\b RKH_EN_ENT_HSM_ARG
	\n \n Determines the function prototype of the state entry. 
	When RKH_EN_ENT_HSM_ARG is set to one (1) this function adds as 
	argument a pointer to state machine structure RKH_T. See 
	#RKHENT_T structure definition.

-	\b RKH_EN_EXT_HSM_ARG
	\n \n Determines the function prototype of the state exit. 
	When RKH_EN_EXT_HSM_ARG is set to one (1) this function adds as 
	argument a pointer to state machine structure RKH_T. See 
	#RKHEXT_T structure definition.

-	\b RKH_EN_ACT_HSM_ARG
	\n \n Determines the function prototype of the transition action. 
	When RKH_EN_ACT_HSM_ARG is set to one (1) this function adds as 
	argument a pointer to state machine structure RKH_T. See 
	#RKHACT_T structure definition.

-	\b RKH_EN_ACT_EVT_ARG
	\n \n Determines the function prototype of the transition action. 
	When RKH_EN_ACT_HSM_ARG is set to one (1) this function adds as 
	argument a pointer to ocurred event. See #RKHACT_T 
	structure definition.

-	\b RKH_EN_GRD_EVT_ARG
	\n \n Determines the function prototype of the transition guard.
	When RKH_EN_GRD_EVT_ARG is set to one (1) this function adds as 
	argument a pointer to ocurred event. See #RKHGUARD_T structure 
	definition.

-	\b RKH_EN_GRD_HSM_ARG
	\n \n Determines the function prototype of the transition guard.
	When RKH_EN_GRD_HSM_ARG is set to one (1) this function adds as 
	argument a pointer to state machine structure RKH_T. See 
	#RKHGUARD_T structure definition.

-	\b RKH_EN_PPRO_HSM_ARG
	\n \n Determines the function prototype of the event preprocessor.
	When RKH_EN_PPRO_HSM_ARG is set to one (1) this function adds as 
	argument a pointer to state machine structure RKH_T. See 
	#RKHPPRO_T structure definition.

-	\b RKH_EN_STATE_NAME
	\n \n When RKH_EN_STATE_NAME is set to one (1) the state structure 
	includes its own name as a null-terminated string. When a particular 
	application requires runtime debugging, this option must be enabled. 
	See #RKHBASE_T structure definition.

-	\b RKH_EN_STATE_ID	
	\n \n When RKH_EN_STATE_ID is set to one (1) the state structure 
	includes an ID number (also called descriptor). 
	This number allows to uniquely identify a state. When a particular 
	application requires runtime debugging (native tracing features), 
	this option must be enabled. 

-	\b RKH_EN_HSM_NAME	
	\n \n When RKH_EN_HSM_NAME is set to one (1) the state machine
	structure RKH_T includes its own name as a null-terminated string. 
	When a particular application requires runtime debugging, this option 
	must be enabled.

-	\b RKH_EN_HSM_ID	
	\n \n When RKH_EN_HSM_ID is set to one (1) the state machine
	structure RKH_T includes an ID number (also called descriptor). 
	This number allows to uniquely identify a state. When a particular 
	application requires runtime debugging (native tracing features), 
	this option must be enabled. 

-	\b RKH_EN_HSM_DATA
	\n \n When RKH_EN_HSM_DATA is set to one (1) the state machine structure
	 RKH_T allows to reference a data object, which maintains additional 
	 information.

-	\b RKH_EN_PPRO	
	\n \n When RKH_EN_PPRO is set to one (1) either basic or composite states
	can use a function to preprocessing the ocurred events.

-	\b RKH_EN_GET_INFO	
	\n \n When RKH_EN_GET_INFO is set to one (1) the state machine structure
	 RKH_T includes additional performance information by means of 
	 RKH_INFO_T structure.

-	\b RKH_EN_REENTRANT
	\n \n Not yet implemented.

-	\b RKH_TRACE
	\n \n Enable (1) or disable (0) the trace mode. It's described in detail
	in \ref dbg section.

-	\b RKH_TRACE_ALL
	\n \n Enable (1) or disable (0) all trace points.

-	\b RKH_EN_EVENT
	\n \n If it's enabled (1) records the triggering event.

-	\b RKH_EN_TRN_SRC
	\n \n If it's enabled (1) records the source state of transition.

-	\b RKH_EN_TRN_TGT
	\n \n If it's enabled (1) records the target state of transition.

-	\b RKH_EN_NXT_STATE
	\n \n If it's enabled (1) records the next state of transition.

-	\b RKH_EN_INT_TRAN
	\n \n If it's enabled (1) records the internal transition.

-	\b RKH_EN_ENTRY
	\n \n If it's enabled (1) records the entered state.

-	\b RKH_EN_EXIT
	\n \n If it's enabled (1) records the exited state.

-	\b RKH_EN_INIT_HSM
	\n \n If it's enabled (1) records the initialization process of state machine.

-	\b RKH_EN_SGT_TGT
	\n \n If it's enabled (1) records the target state of transition segment.

-	\b RKH_EN_RTN_CODE
	\n \n If it's enabled (1) records the code returned by rkh_engine() function.

-	\b RKH_EN_NUM_ENEX
	\n \n If it's enabled (1) records the number of entered and exited states.

-	\b RKH_EN_NUM_ACTSGT
	\n \n If it's enabled (1) records the number of transition actions and transition
	segments.

-	\b RKH_EN_TIMESTAMP
	\n \n When RKH_EN_TIMESTAMP is set to one (1) the trace event structure 
	RKHTREVT_T allows include a timestamp.

- 	\b RKH_SIZEOF_TIMESTAMP
	\n \n Determines the size [in bits] of the trace timestamp representation. 
	Valid values: 8, 16 or 32. Default 8.

- 	\b RKH_MAX_NUM_TRACES
	\n \n Determines the maximum number of trace events in the stream. The smaller
	this number, the lower the static RAM consumption.

- 	\b RKH_EN_TRACE_STRING
	\n \n When RKH_EN_TRACE_STRING is set to one (1) the trace event
	structure RKHTREVT_T adds as argument an array of chars to allocate a 
	null-terminated string.

- 	\b RKH_MAX_TRACE_STRING_SIZE
	\n \n Determines the size [in bytes] of the trace string argument.

-	\b RKH_ASSERT
	\n \n Enable (1) or Disable (0) assert support.

*/


/**
\page Usage Representing a state machine: step by step

\n The goal in this section is to explain how to represent a state machine 
using the RKH framework. To do that is proposed a simple example, which is 
shown in the \ref fig1 "Figure 1". Also, this section summarizes the main 
rules and concepts for making the most out of RKH features.

- \subpage basics
- \subpage preparing
- \subpage identify
- \subpage representing
- \subpage running

\anchor fig1
\image html my.png "Figure 1 - \"my\" state diagram"

*/
