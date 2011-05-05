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
|   chglog.txt			- Change log file
\	copying.txt			- licence file
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
|   |       rkh.h		- Internal use only
|   |       rkhtrace.h	- Trace facility
|   |       rkhplat.h	- Supported and portable platforms
|   |       rkhsm.h		- Framework interface
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
|   chglog.txt			- Change log file
\	copying.txt			- licence file
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

- \c rkh.c: platform-independent source code of RKH. This file 
requires inclusion of only one platform-specific header file named 
\c rkhport.h. It's indirectly included by \c rkh.h file and it's 
described in detail in section \ref Porting.

- \c rkhtrace.c: platform-independent source code of runtime debugging.

Next, each \c rkhport.h must be referenced from \c rkhplat.h header file,
located in \c \\include directory. The idea behind conditional 
compilation is that a \c rkhport.h can be selectively compiled, depending 
upon whether a specific value has been defined. The next listing shows 
the \c rkhplat.h file according to \c \\portable directory from
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
Aditionallity, should be created the RKH configuration file \c rkhcfg.h 
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
|		main.c			- main source code
|		my.c			- application source file
|		myact.c			- application source file
|		my.h			- application include file
|		myact.h			- application include file
|		myevt.h			- application include file
|		rkhcfg.h		- RKH configuration file
|		rkhdata.h		- application include file
|                   
+---doc					- RKH documentation
|                   
+---source				- RKH source files
|   chglog.txt			- Change log file
\	copying.txt			- licence file
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
rkh.h		- Internal use only
rkhtrace.h	- Trace facility
rkhplat.h	- Supported and portable platform
rkhsm.h		- Framework interface
\endcode

Required include files extracted from \c \\portable\\\<platform\> directory:

\code
rkhport.h	- RKH platform-dependent include file
\endcode

The \c rkhport.h must be referenced from \c rkhplat.h file as shown below:

\code
#include "rkhport.h"
\endcode

\n \b Application

Next, should be created the configuration file \c rkhcfg.h to be included 
within the application directory. See \ref cfg section for more information. 
This file is mandatory and it's used by RKH.


\page Porting Porting

This section describes how to adapt the RKH to various platforms, which
is a process called porting. RKH contains a clearly defined abstraction
layer, which encapsulates all the platform-specific code and cleanly
separates it from platform-neutral code.

Porting RKH implies to create the platform-dependent file, called 
\c rhhport.h. In this file must be defined the data types 
that uses RKH.
The RKH directories and files are described in detail in 
\ref Installation section. The next sections listed below describes 
the aspects to be considered:

- \ref data
- \ref rom
- \ref files
- \ref rkhp

<HR>
\section data Data types definitions

The RKH uses a set of integer quantities. That maybe machine or compiler
dependent. These types must be defined in \c rkhport.h file as shown 
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

The \c HUInt and \c HInt will normally be the natural size 
for a particular machine. These types designates an integer 
type that is usually fastest to operate with among all integer 
types.

<HR>
\section rom ROM allocator

For declaring an object that its value will not be changed and that
will be stored in ROM, must be defined in \c rkhport.h the 
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
\section files Platform-dependent files

The header file \c rkhport.h adapts and configures RKH. This
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

Next, each \c rkhport.h must be referenced from \c rkhplat.h header file,
located in \c \\include directory. The idea behind conditional 
compilation is that a \c rkhport.h can be selectively compiled, depending 
upon whether a specific value has been defined. The next listing shows 
the \c rkhplat.h file according to \c \\portable directory from
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
\endcode


\page Usage Representing a state-machine

\n
As stated above, RKH is a generic, flexible, modular, highly portable, 
ANSI-C compliant, and open-source development tool for implementing 
hierarchical state-machines based on modern state-machine concepts. This 
modern techniques are used to give an abstract description of the dynamic 
behavior of a system in a substantial manner.

<STRONG> The key features of the RKH framework: </STRONG>

- State-machines representation is based on state-tables.
- Representing a state-machine with RKH is intuitive, and easy.
- Reflects the state-diagram without obfuscation.
- The RKH application are highly maintainable.
- Easy to integrate with any event queuing and dispatching mechanism.
- Useful in embedded systems.
- The most of the RKH implementation is independent of any particular 
CPU, operating system, or compiler.
- Flexible and user-configurable code generation.
- Very small footprint.
- Support hierarchically nested states, and flat state-machine.
- Support conditional, junction, and history pseudostates.
- Support compound transitions with guards.


The RKH not implements neither entire UML specs. nor entire Statechart specs. 
Instead, the RKH intention is to support just enough basic concepts of that 
powerful tools to facilitate the reactive-system modeling holding a solid, 
and efficient implementation. Broadly speaking, the RKH implementation has 
been designed from the ground up to be used in 8-bits platforms but can be 
easily adapted to 16 or 32-bits platforms.

The goal in this section is to explain how to represent a state-machine 
using the RKH framework. To do that is proposed a simple example, which is 
shown in the \ref fig1 "Figure 1".

\n
\anchor fig1
\image html my.jpg "Figure 1 - \"my\" State diagram"

\n This section summarizes the main rules and concepts for making the most
out of RKH features.

- \ref rep0
- \ref rep1
- \ref rep2
- \ref rep3

<HR>
\section rep0 Preparing the application files

The sample code for the example presented above port to x86 is located 
in the directory \\demo\\vc08\\. The directory contains the Visual C++ 2008
project files to build the application. See \ref Installation section 
about RKH files.

Th header file is located in the application directory:

- \b "rkhcfg.h":	this file adapts and configures RKH. See \ref cfg section. 
					In the \\demo directory there are other rkhcfg.h files
					already in existence and it's suggested that these 
					are used as a reference. See the application 
					\ref rkhcfg_h file.
					Note that this header file is located in the application 
					directory.

- \b "my.c": 		contains the implementation of the "my" state-machine, 
					which illustrates all aspects of implementing 
					state-machines with RKH. Please correlate this 
					implementation with the "my" state diagram in 
					\ref fig1 "Figure 1".
					In this file are specifically declared the 
					state-machine, also its 
					states and pseudostates. See the \ref my_c file.
					Note that this source file is located in the application 
					directory.

- \b "myact.c": 	this source file declares each of entry, exit, 
					transition, and guard actions to be executed.
					Note that the \c rkhcfg.h file defines the function
					prototype of actions. See \ref cfg section about of 
					available options and \ref myact_c file.
					Also, note that this source file is located in the 
					application 

- \b "my.h": 		this header file contains the definitions of objet 
					structures (state-machine, states, and pseudostates) and
					other facilities shared among the components of the
					application. See the \ref my_h file.
					Note that this header file is located in the application 
					directory.

- \b "myact.h":		this header file defines the actions to be executed.
					Note that the \c rkhcfg.h file defines the function
					prototype of actions. See \ref cfg section about of 
					available options and \ref myact_c file.
					See the \ref myact_h file.
					Note that this header file is located in the application 
					directory.

- \b "myevt.h":		because events are explicitly shared 
					among most of the application components, it's convenient 
					to declare them in the separate header file "myevt.h".
					See the \ref myevt_h file.
					Note that this header file is located in the application 
					directory.

- \b "main.c": 		this file contains the main() function along with 
					an example for using the RKH trace facility.
					See the \ref main_c file.
					Note that this source file is located in the 
					application 

<HR>
\section rep1 Identify and classify states and pseudostates

The \ref fig2 "Figure 2" shows the states and pseudostates from the diagram
presented above, sorted by state nesting level.

\n
\anchor fig2
\image html sttbl.jpg "Figure 2 - State nesting"

<HR>
\section rep2 Representing the state-machine

Now, this section explains how to implement the "my" state-machine 
using the RKH framework, which is shown in \ref fig1 "Figure 1".

-# \ref rep_sm
-# \ref rep_cs
-# \ref rep_bs
-# \ref rep_cjh
-# \ref rep_st
-# \ref rep_def
-# \ref rep_act
-# \ref rep_inc

\n
\subsection rep_sm Declaring the state-machine (top-state)

\n
The object structure of "my" state-machine is declared by means of 
RKH_CREATE_HSM() macro, which is explained in \c rkhsm.h file.
According to "my" state diagram:
\n
\n
\code
RKH_CREATE_HSM( my, 0, HCAL, &S1, my_init, &mydata );
\endcode
\n
where:
\n
	- \e \b name =	"my". State-machine (top-state) name. Represents the 
					state-machine structure.
	- \e \b id =	"0". The value of state-machine ID. The user application 
					defines the available ids in \c rkhdata.h file. 
	- \e \b ppty =	"HCAL". Enables the state nesting. 
	- \e \b is =	"S1". Pointer to regular initial state. This state could 
					be defined either composite or basic.
	- \e \b ia =	"my_init". Pointer to initialization action. The function 
					prototype is defined as #RKHINIT_T. This argument is 
					optional, thus it could be declared as NULL.
	- \e \b hd =	"mydata". Pointer to state-machine's abstract data. This 
					argument is optional, thus it could be declared as NULL.
\n
\n
\subsection rep_cs Declaring the composite states
\n
The RKH_CREATE_COMP_STATE() macro, which is defined in the \c rkhsm.h file,
is used for creating the composite states.

According to "my" state diagram the declaration of composite state "S1" looks
as follow:

\code
RKH_CREATE_COMP_STATE( S1, 0, set_y_0, dummy_exit, RKH_ROOT, &S11, &DH );
\endcode
\n
where:
\n
	- \e \b name =	"S1". State name. Represents the composite state structure.
	- \e \b id =	"0". The value of state ID.
	- \e \b en =	"set_y_0". Pointer to state entry action. This argument is 
					optional, thus it could be declared as NULL.
	- \e \b ex =	"dummy_exit". Pointer to state exit action. This argument 
					is optional, thus it could be declared as NULL.
	- \e \b parent =	"RKH_ROOT". Pointer to parent state. 
	- \e \b defchild =	"S11". Pointer to default child state or pseudostate. 
	- \e \b history =	"DH". Pointer to history pseudostate. This argument 
						is optional, thus it could be declared as NULL.

In like manner, the rest composite states are declared as shown below:
\n
\code
RKH_CREATE_COMP_STATE( S11, 0, NULL, NULL, 	&S1, 		&S111,	&H );
RKH_CREATE_COMP_STATE( S3, 	0, NULL, NULL,  RKH_ROOT, 	&S31,  	NULL );
\endcode
\n
\subsection rep_bs Declaring the basic states
\n
The RKH_CREATE_BASIC_STATE() macro, which is defined in the \c rkhsm.h file,
is used for creating the basic states.

According to "my" state diagram the declaration of basic state "S12" looks
as follow:

\code
RKH_CREATE_BASIC_STATE( S12, 	0, set_x_3, NULL, &S1, NULL );
\endcode
\n
where:
\n
	- \e \b name =	"S12". State name. Represents the basic state structure.
	- \e \b id =	"0". The value of state ID.
	- \e \b en =	"set_x_3". Pointer to state entry action. This argument is 
					optional, thus it could be declared as NULL.
	- \e \b ex =	"NULL". Pointer to state exit action. This argument is 
					optional, thus it could be declared as NULL.
	- \e \b parent =	"S1". Pointer to parent state. 
	- \e \b prepro =	"NULL". Pointer to input preprocessor function. This 
						argument is optional, thus it could be declared as NULL.

In like manner, the rest basic states are declared as shown below:
\n
\code
RKH_CREATE_BASIC_STATE( S111, 	0, set_x_1, NULL, &S11, NULL );
RKH_CREATE_BASIC_STATE( S112,	0, set_x_2, NULL, &S11, NULL );
RKH_CREATE_BASIC_STATE( S31, 	0, NULL, 	NULL, &S3, 	NULL );
RKH_CREATE_BASIC_STATE( S32, 	0, NULL, 	NULL, &S3, 	NULL );
\endcode
\n
\subsection rep_cjh Declaring the pseudostates
\n
The conditional, junction, shallow history, and deep history pseudostates 
are created using RKH_CREATE_COND_STATE(), RKH_CREATE_JUNCTION_STATE(), 
RKH_CREATE_SHALLOW_HISTORY_STATE(), and RKH_CREATE_DEEP_HISTORY_STATE() 
macros respectively, which are explained in \c rkhsm.h file.

\n According to "my" state diagram the declaration of conditional 
pseudostate "C1" looks as follow:
\n
\code
RKH_CREATE_COND_STATE( C1, 0 );
RKH_CREATE_COND_STATE( C2, 0 );
\endcode
\n
where:
\n
	- \e \b name =	"C1"/"C2". Pseudostate name. Represents the conditional 
					pseudostate structure.
	- \e \b id =	"0"/"0". The value of state ID.

\n According to "my" state diagram the declaration of juction pseudostate
"J" looks as follow:
\n
\code
RKH_CREATE_JUNCTION_STATE( J, 0, NULL, &S3 );
\endcode
\n
where:
\n
	- \e \b name =	"J". Pseudostate name. Represents the junction
					pseudostate structure.
	- \e \b id =	"0". The value of state ID.
	- \e \b action =	"NULL". Pointer to transition action. This argument is 
					optional, thus it could be declared as NULL.
	- \e \b target =	"S3". Pointer to target state.

\n According to "my" state diagram the declaration of shallow history 
pseudostate "H" looks as follow:
\n
\code
RKH_CREATE_SHALLOW_HISTORY_STATE( H, 0, &S11 );
\endcode
\n
where:
\n
	- \e \b name =	"H". Pseudostate name. Represents the shallow history 
					pseudostate structure.
	- \e \b id =	"0". The value of state ID.
	- \e \b parent =	"S11". Pointer to parent state.

\n According to "my" state diagram the declaration of deep history 
pseudostate "DH" looks as follow:
\n
\code
RKH_CREATE_DEEP_HISTORY_STATE( DH, 0, &S1 );
\endcode
\n
where:
\n
	- \e \b name =	"DH". Pseudostate name. Represents the deep history 
					pseudostate structure.
	- \e \b id =	"0". The value of state ID.
	- \e \b parent =	"S1". Pointer to parent state.

\n
\subsection rep_st Declaring transition and branch tables

\n
The basic and composite states requires a state transition table.
The #RKH_CREATE_TRANS_TABLE() macro creates a state transition table. Use the 
#RKH_END_TRANS_TABLE macro to terminate it.
Similarly, the condiotional pseudostates requires a branch table. 
This #RKH_CREATE_BRANCH_TABLE macro creates a branch table. Use the 
#RKH_END_BRANCH_TABLE macro to terminate it.

\n According to "my" state diagram the state transition table of state "S2"
looks as follow:

\code
(1)	RKH_CREATE_TRANS_TABLE( S2 )

(2)		RKH_TRREG( ONE, 	x_equal_1, 	dummy_act, 	&S1 ),
		RKH_TRREG( TWO, 	NULL, 		NULL, 		&S2 ),
		RKH_TRREG( THREE, 	NULL, 		NULL, 		&C2 ),
(3)		RKH_TRINT( FOUR, 	NULL, 		dummy_act ),
		RKH_TRINT( SIX, 	NULL, 		show_data ),

(4)	RKH_END_TRANS_TABLE	
\endcode

\li (1) Declares the state transition table of state "S2".

\li (2) Declares a regular transition using RKH_TRREG() macro. Where:
	- \e \b event =	"ONE". Triggering event. 
	- \e \b guard = "x_equal_1". Pointer to guard function. This argument is 
					optional, thus it could be declared as NULL.
	- \e \b action = "dummy_act". Pointer to action function. This argument is 
					optional, thus it could be declared as NULL.
	- \e \b target \b state = "S1". Pointer to target state.

\li (3) Declares an internal transition using RKH_TRINT() macro. Where:
	- \e \b event =	"FOUR". Triggering event. 
	- \e \b guard = "NULL". Pointer to guard function. This argument is 
					optional, thus it could be declared as NULL.
	- \e \b action = "dummy_act". Pointer to action function. This argument is 
					optional, thus it could be declared as NULL.

\li (4) Terminates the transition table.

\n According to "my" state diagram the branch table of "C2"
looks as follow:

\code
(1)	RKH_CREATE_BRANCH_TABLE( C2 )
(2)		RKH_BRANCH( x1, 		dummy_act, 	&S3 ),
		RKH_BRANCH( x2_or_x3, 	NULL, 		&S32 ),
(3)	RKH_END_BRANCH_TABLE

\endcode

\li (1) Declares the branch table of state of "C2".

\li (2) Declares a branch. Where:
	- \e \b guard =	"x1". branch guard. 
	- \e \b action = "NULL". Pointer to action function. This argument is 
					optional, thus it could be declared as NULL.
	- \e \b target \b state = "S3". Pointer to target state.

\li (3) Terminates the branch table.

\n In like manner, the rest tables are declared as shown below:
\n
\code
/*
 *	Defines states and pseudostates.
 */

RKH_CREATE_BASIC_STATE( S2, 0, NULL, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( S2 )

	RKH_TRREG( ONE, 	x_equal_1, 	dummy_act, 	&S1 ),
	RKH_TRREG( TWO, 	NULL, 		NULL, 		&S2 ),
	RKH_TRREG( THREE, 	NULL, 		NULL, 		&C2 ),
	RKH_TRINT( FOUR, 	NULL, 		dummy_act ),
	RKH_TRINT( SIX, 	NULL, 		show_data ),

RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE( S1, 0, set_y_0, dummy_exit,  RKH_ROOT, &S11, &DH );
RKH_CREATE_TRANS_TABLE( S1 )

	RKH_TRREG( THREE, 	NULL, 		NULL, 		&S3 ),
	RKH_TRREG( FIVE, 	NULL, 		NULL, 		&S12 ),
	RKH_TRINT( SIX, 	NULL, 		show_data ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S12, 0, set_x_3, NULL, &S1, NULL );
RKH_CREATE_TRANS_TABLE( S12 )

	RKH_TRREG( ONE, 	NULL, 		NULL, 		&J ),
	RKH_TRREG( FOUR, 	NULL, 		set_y_1, 	&S2 ),

RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE( S11, 0, NULL, NULL, &S1, &S111, &H );
RKH_CREATE_TRANS_TABLE( S11 )

	RKH_TRREG( TWO, 	NULL, 		NULL, 		&S112 ),
	RKH_TRREG( FOUR, 	NULL, 		NULL, 		&S12 ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S111, 0, set_x_1, NULL, &S11, NULL );
RKH_CREATE_TRANS_TABLE( S111 )

	RKH_TRREG( ONE, 	NULL, 		NULL, 		&S112 ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S112, 0, set_x_2, NULL, &S11, NULL );
RKH_CREATE_TRANS_TABLE( S112 )

	RKH_TRREG( ONE, 	NULL, 		NULL, 		&S111 ),
	RKH_TRREG( TWO, 	NULL, 		NULL, 		&S11 ),
	RKH_TRREG( THREE, 	NULL, 		NULL, 		&J ),

RKH_END_TRANS_TABLE

RKH_CREATE_SHALLOW_HISTORY_STATE( H, 0, &S11 );
RKH_CREATE_DEEP_HISTORY_STATE( DH, 0, &S1 );

RKH_CREATE_COMP_STATE( S3, 0, NULL, NULL,  RKH_ROOT, &S31,  NULL );
RKH_CREATE_TRANS_TABLE( S3 )

	RKH_TRREG( TWO, 	NULL, 		NULL, 		&C1 ),
	RKH_TRREG( THREE, 	NULL, 		NULL, 		&S3 ),
	RKH_TRINT( SIX, 	NULL, 		show_data ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S31, 0, NULL, NULL, &S3, NULL );
RKH_CREATE_TRANS_TABLE( S31 )

	RKH_TRREG( ONE, 	NULL, 		NULL, 		&S32 ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S32, 0, NULL, NULL, &S3, NULL );
RKH_CREATE_TRANS_TABLE( S32 )

	RKH_TRREG( ONE, 	NULL, 		NULL, 		&S31 ),

RKH_END_TRANS_TABLE


RKH_CREATE_JUNCTION_STATE( J, 0, NULL, &S3 );

RKH_CREATE_COND_STATE( C1, 0 );
RKH_CREATE_BRANCH_TABLE( C1 )

	RKH_BRANCH( y1, 	NULL, 		&H ),
	RKH_BRANCH( y2, 	dummy_act, 	&DH ),

RKH_END_BRANCH_TABLE

RKH_CREATE_COND_STATE( C2, 0 );
RKH_CREATE_BRANCH_TABLE( C2 )

	RKH_BRANCH( x1, 		dummy_act, 	&S3 ),
	RKH_BRANCH( x2_or_x3, 	NULL, 		&S32 ),
	RKH_BRANCH( ELSE, 		NULL, 		&S2 ),

RKH_END_BRANCH_TABLE
\endcode


\subsection rep_inc Including files

The following listing shows a fragment of "my.c" source file, which 
illustatres some aspects of implementing state-machines with RKH.

\code
(1) #include "rkhsm.h"


/*	Includes file of event definitions. */

(2) #include "myevt.h"


/* Includes file of HSM definitions. */

(3) #include "my.h"


/* Includes file of action/guard definitions. */

(4) #include "myact.h"


/* Defines HSM's data. */

(5) static MYHDATA_T mydata;

/* ... */
\endcode

\li (1) Every application C-file that uses RKH must include the rkhsm.h 
		header file. This header file contains the specific adaptation 
		of RKH to the given processor and compiler, also includes the
		RKH interface to implement state-machines. The port file is located
		in the application directory.

\li (2) The "myevt.h" header file contains the declarations of triggering 
		events shared among the components of the
		application. This header file is located in the application 
		directory.

\li (3) The "my.h" header file contains the definitions of objet 
		structures (state-machine, states, and pseudostates) and
		other facilities shared among the components of the application. 

\li (4) This header file defines the actions to be executed.

\li (5) The "my" state-machine maintains its own data in the structure 
		MYDATA_T, which is defined in the "my.h" header file.

\n
\subsection rep_def Defining the state-machine

The following listing shows the "my.h" header file, which 
illustatres some important aspects of implementing state-machines with RKH.

\code
#ifndef __MY_H__
#define __MY_H__


(1)	#include "rkhsm.h"


/*	Defines the event structure. */

(2)	typedef struct
	{
(3)		RKHEVT_T event;
(4)		rkhuint16 ts;
	} MYEVT_T;


/*	Defines the state-machine data */

(5)	typedef struct
	{
		rkhuint8 x;
		rkhuint8 y;
	} MYHDATA_T;


/*	Defines the state-machine. */

(6)	RKH_DCLR_HSM( my );


/*	Defines states and pseudostates. */

(7)	RKH_DCLR_COMP_STATE		S1,S3,S11;
	RKH_DCLR_BASIC_STATE	S2,S31,S32,S111,S112,S12;
	RKH_DCLR_COND_STATE		C1,C2;
	RKH_DCLR_JUNC_STATE		J;
	RKH_DCLR_DHIST_STATE	DH;
	RKH_DCLR_SHIST_STATE	H;


#endif
\endcode

\li (1) RKH interfaces.

\li (2-4) The MYEVT_T structure declares an event with the parameter "ts".
		Such nesting of structures always aligns the data member 
		#RKHEVT_T at the beginning of every instance of the derived 
		structure. In particular, this alignment lets treat a pointer to 
		the derived MYEVT_T structure as a pointer to the #RKHEVT_T 
		base structure. Consequently, can always safely pass a pointer 
		to MYEVT_T to any C function that expects a pointer to #RKHEVT_T.

\li (5) The MYHDATA_T defines the state-machine data. 

\li (6) Defines the state-machine as a global object.

\li (7) Defines the states and pseudostates using the corresponding macos
		listed above:
		\n
		\n
		- #RKH_DCLR_COMP_STATE: composite state.
		- #RKH_DCLR_BASIC_STATE: basic state.
		- #RKH_DCLR_COND_STATE: conditional pseudostate.
		- #RKH_DCLR_JUNC_STATE: junction pseudostate.
		- #RKH_DCLR_DHIST_STATE: deep history pseudostate.
		- #RKH_DCLR_SHIST_STATE: shallow history pseudostate.

\n
\subsection rep_act Declaring and defining actions

\n The following enlists the action to be automatically executed by RKH. The
function prototypes are explicitly defined in \c rkh.h file.

- \b Initiallization \b action (#RKHINIT_T): 
	the state transition originating at the black ball is called the 
	initial transition.	An initial transition can have associated 
	actions, which RKH invokes to execute the topmost initial transition.

- \b Transition \b action (#RKHACT_T): 		
	enlists any actions associated with the transition.

- \b Entry \b action (#RKHENT_T): 			
	this action is executed upon entry to a state.

- \b Exit \b action (#RKHEXT_T): 			
	this action is executed upon exit from a state.

- \b Guard \b action (#RKHGUARD_T):
	contains the guard conditions attached to transitions.

- \b Preprocessor \b action (#RKHPPRO_T): 	
	this action is executed before sending occured event to state-machine.

Aditionally, the preprocessor options listed in \c rkhcfg.h allows 
to customize the prototypes of each action. See \ref cfg section for 
more information about that.
The used actions in the "my" state-machine implementation are shown in
\ref myact_c file.

\n According to "my" state diagram the initial action looks as follow:
\n
\code
void 
my_init( const struct rkh_t *ph )
{
	pd = rkh_get_data( ph );
	pd->x = pd->y = 0;
}
\endcode

\n According to "my" state diagram the transition actions looks as follow:
\n
\code
void
set_y_2( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );
	pd->y = 2;
	printf( "action: "__FUNCTION__"()\n" );
	printf( "event.ts = %05d\n", (( MYEVT_T* )pe )->ts );
	printf( "data.x = %02d - data.y = %02d\n", pd->x, pd->y );
}


void
set_y_1( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );
	pd->y = 1;
	printf( "action: "__FUNCTION__"()\n" );
	printf( "event.ts = %05d\n", (( MYEVT_T* )pe )->ts );
	printf( "data.x = %02d - data.y = %02d\n", pd->x, pd->y );
}


void
dummy_act( const struct rkh_t *ph, RKHEVT_T *pe )
{
}


void
show_data( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );
	printf( "data.x = %02d - data.y = %02d\n", pd->x, pd->y );
}
\endcode

\n According to "my" state diagram the entry actions looks as follow:
\n
\code
void
set_x_1( const struct rkh_t *ph )
{
	pd = rkh_get_data( ph );
	pd->x = 1;
}


void
set_x_2( const struct rkh_t *ph )
{
	pd = rkh_get_data( ph );
	pd->x = 2;
}


void
set_x_3( const struct rkh_t *ph )
{
	pd = rkh_get_data( ph );
	pd->x = 3;
}


void
set_y_0( const struct rkh_t *ph )
{
	pd = rkh_get_data( ph );
	pd->y = 0;
}
\endcode

\n According to "my" state diagram the exit actions looks as follow:
\n
\code
void
dummy_exit( const struct rkh_t *ph )
{
}
\endcode

\n According to "my" state diagram the guards looks as follow:
\n
\code
HUInt
x_equal_1( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );

	return pd->x == 1 ? RKH_GTRUE : RKH_GFALSE;
}
\endcode

\n According to "my" state diagram the branch selection functions looks 
as follow:
\n
\code
HUInt
y1( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );
	return pd->y == 1 ? RKH_GTRUE : RKH_GFALSE;
}


HUInt
y2( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );
	return pd->y == 2 ? RKH_GTRUE : RKH_GFALSE;
}


HUInt
x1( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );
	return pd->x == 1 ? RKH_GTRUE : RKH_GFALSE;
}


HUInt
x2_or_x3( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );
	return pd->x == 2 || pd->x == 3 ? RKH_GTRUE : RKH_GFALSE;
}
\endcode

\n After declaring each actions in "myact.c" it must be defined in 
\ref myact_h file.

<HR>

\section rep3 Running

The following listing shows the main() function implementation. This function
is included in the \ref main_c file, it's located in the application 
directory.

\code
	void
	main( void )
	{
		int c;

(1)		rkh_trace_open();
(2)		rkh_init_hsm( &my );
		srand( ( unsigned )time( NULL ) );

		forever
		{
(3)			c = mygetch();
		
			if( c == 'p' )
(4)				rkh_trace_flush();
			else if ( c == ESC )
(5)				break;
			else if ( c == 'r' )
				rkh_init_hsm( &my );
			else
			{
(6)				mye.event.evt = kbmap( c );
(7)				mye.ts = ( rkhuint16 )rand();
(8)				rkh_engine( &my, ( RKHEVT_T *)&mye );
			}
		}

(9)		rkh_trace_close();
	}
\endcode

\li (1) Initialize the RKH trace module.

\li (2) Initialize the "my" state-machine. RKH invokes the my_init() function.

\li (3) Gets key pressed from the standard input.

\li (4) Flushs the trace stream to the desired host.

\li (5) Terminates the program.

\li (6) The	event generated by pressing a key on the keyboard is stored 
		in the "event.evt" member of MYEVT_T structure.

\li (7)	The	event has associated parameters that convey a random number.

\li (8)	Events with parameters, such as the MYEVT_T, require explicit 
		casting from the generic base structure #RKHEVT_T to the specific 
		derived structure MYEVT_T.

\li (9)	Terminates the program and close debug session.


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
these events are common for all the state-machine applications and never 
change (they are always traced). 
The trace events are associated with a integer value and are explicity 
listed and defined (enumerated) as shown below in this section.
	
The standard defines that the trace system has to store some information 
or each trace event (also named arguments) being generated, including, 
t least, the following:

- the trace event identifier (\c #RKHTR_EVENTS enumerated list),
- instrumented application (state-machine),
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

- The option \c RKH_TRACE must be set to one (1), it should be defined in 
the specific application configuration file named \c rkhcfg.h. 

- The trace events of interest must be defined in the \c rkhcfg.h file. See
\c #RKHTR_EVENTS enumeration and \ref trcfg section.

- The rkh_trace_open(), rkh_trace_close(), rkh_trace_flush(), and 
rkh_trace_getts() are platform-dependent functions, therefore the user
application must implement it. 
This functions are invoked through the rkh_tropen(), rkh_trclose(), 
rkh_trflush(), and rkh_trgetts() macros. 

- The RKH_EN_TIMESTAMP, RKH_SIZEOF_TIMESTAMP, RKH_MAX_NUM_TRACES, 
RKH_EN_TRACE_STRING, and RKH_MAX_TRACE_STRING_SIZE preprocessor options 
configures the \c #RKHTREVT_T trace event structure and should be defined 
in the \c rkhcfg.h file.

- See \c rkhtrace.h header file for more information.

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
\n \n Records the initialization process of state-machine.

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
\c rkhcfg.h. This file adapts and configures RKH by means of compiler
definitions and macros allowing to restrict the resources consumed by RKH.
Adjusting this definitions allows to reduce the ROM and RAM consumption,
and to enhance the system performance in a substantial manner. The 
\ref rkhcfg_h shows the general layout of the \c rkhcfg.h header file.

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

-	\b RKH_SIZEOF_EVENT
	\n \n Determines the size [in bits] of the RKH event representation 
	#RKHE_T. Valid values: 8, 16 or 32. Default 8.

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
	state-machines. When RKH_EN_INIT_HSM_ARG is set to one (1) this
	function adds as argument a pointer to state-machine structure 
	RKH_T. See #RKHINIT_T structure definition.

-	\b RKH_EN_ENT_HSM_ARG
	\n \n Determines the function prototype of the state entry. 
	When RKH_EN_ENT_HSM_ARG is set to one (1) this function adds as 
	argument a pointer to state-machine structure RKH_T. See 
	#RKHENT_T structure definition.

-	\b RKH_EN_EXT_HSM_ARG
	\n \n Determines the function prototype of the state exit. 
	When RKH_EN_EXT_HSM_ARG is set to one (1) this function adds as 
	argument a pointer to state-machine structure RKH_T. See 
	#RKHEXT_T structure definition.

-	\b RKH_EN_ACT_HSM_ARG
	\n \n Determines the function prototype of the transition action. 
	When RKH_EN_ACT_HSM_ARG is set to one (1) this function adds as 
	argument a pointer to state-machine structure RKH_T. See 
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
	argument a pointer to state-machine structure RKH_T. See 
	#RKHGUARD_T structure definition.

-	\b RKH_EN_STATE_NAME
	\n \n When RKH_EN_STATE_NAME is set to one (1) the state structure 
	includes its own name as a null-terminated string. When a particular 
	application requires runtime debugging, this option must be enabled. 
	See #RKHBASE_T structure definition.

-	\b RKH_EN_HSM_NAME	
	\n \n When RKH_EN_HSM_NAME is set to one (1) the state-machine
	structure RKH_T includes its own name as a null-terminated string. 
	When a particular application requires runtime debugging, this option 
	must be enabled.

-	\b RKH_EN_HSM_DATA
	\n \n When RKH_EN_HSM_DATA is set to one (1) the state-machine structure
	 RKH_T allows to reference a data object, which maintains additional 
	 information.

-	\b RKH_EN_PPRO	
	\n \n When RKH_EN_PPRO is set to one (1) either basic or composite states
	can use a function to preprocessing the ocurred events.

-	\b RKH_EN_GET_INFO	
	\n \n When RKH_EN_GET_INFO is set to one (1) the state-machine structure
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
	\n \n If it's enabled (1) records the initialization process of state-machine.

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


*/
