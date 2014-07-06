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
 *  File                     : rkhassert.h
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 * 	\endcond
 *
 * 	\file
 * 	\ingroup 	assert
 *
 *	\brief 		Assert definitions.
 */


#ifndef __RKHASSERT_H__
#define __RKHASSERT_H__


#include "rkhcfg.h"


#if RKH_CFG_FWK_ASSERT_EN == RKH_ENABLED

    /** 
	 *	\brief
	 *	Callback invoked in case the condition passed to RKH_ASSERT(),
	 * 	RKH_REQUIRE(), RKH_ENSURE(), RKH_ERROR(), or RKH_ALLEGE() evaluates 
	 * 	to FALSE.
	 *
	 * 	If the expression evaluates to FALSE (0), the function rkh_assert() 
	 * 	will be invoked, typically halting the program in some way and 
	 * 	storing or reporting the error code.
	 * 	Once the rkh_assert() callback has stored or reported the error, it 
	 * 	must decide on the system's next action. One option is:
	 *		
	 *	-# disable general interrupt
	 *	-# stores or send detected error (could be use a trace facility)
	 *	-# trigger a software reset
	 *
	 *	The policy chooses will be largely determined by the nature of 
	 *	product. 
	 *	If the system is running with a source level debugger, place a 
	 *	breakpoint within. Another option is to trigger a software reset and 
	 *	attempt to run the system again.
	 *
	 * 	Also a unique identifier that can be reported from the field, easing 
	 * 	the investigation of the problem. Therefore, the error code could be
	 * 	composed of the software version number, file number (.c file), 
	 * 	line number of assertion, and other information. A number is easier 
	 * 	to fill in on a report form and easier to store in NVRAM.
	 *
 	 *	The following listing shows a illustrative example for Visual Studio 
     *	C++ 2008 IDE:
	 *
	 *	\code
	 *	void 
	 *	rkh_assert( RKHROM char * const file, int line )
	 *	{
	 *		printf( "RKH_ASSERT: [%d] line from %s file\n", line, file );
	 *
	 *		RKH_DIS_INTERRUPT();
	 *		RKH_TR_FWK_ASSERT( (RKHROM char *)file, line );
	 *		__debugbreak();
	 *	}
	 *	
	 *	\note
	 *	The rkh_assert() callback will only get called if 
	 *	RKH_CFG_FWK_ASSERT_EN is set to 1 within rkhcfg.h file. When this 
	 *	is set the application must provide the callback function. 
	 * 
	 * 	\param file			file name where the assertion failed
	 * 	\param line 		line number at which the assertion failed
     */

	void rkh_assert( const char *const file, int line );


	/**
	 *	\brief
	 *	This macro appears at the top of each C/C++ source file defining 
	 *	a name for that file.
	 *
	 * 	\param __fname		file name where the assertion failed
	 */
	
	#define RKH_MODULE_NAME( __fname )						\
					static RKHROM char *const m_name = #__fname;


	/**
	 *	\brief
	 *	This macro appears at the top of each C/C++ source file defining 
	 *	a name for that file, by means of __FILE__ compiler directive.
	 */
	
	#define RKH_THIS_MODULE									\
					static RKHROM char *const m_name = __FILE__;


	/**
	 * 	\brief 
	 * 	The RKH_ASSERT() macro is used to check expressions that ought to 
	 * 	be true as long as the program is running correctly. 
	 *
 	 *	The assertions (\c RKH_ASSERT() macro) are used to check expressions 
	 *	that ought to be true as long as the program is running correctly. It 
	 *	is a convenient way to insert sanity checks.
	 *	A number of philosophies can be employed when deciding where to use an 
	 *	\c RKH_ASSERT() macro. Broadly speaking, the assertions only serve the 
	 *	purposes of catching bugs and helping documentation. Helping to 
	 *	document the code means that the statements inside the assertion tell 
	 *	the reader something he might not already know.
	 *	
	 *	\note 
	 *	The preprocessor switch RKH_CFG_FWK_ASSERT_EN disables checking 
	 *	assertions.
	 * 	In particular macros RKH_ASSERT(), RKH_REQUIRE(), RKH_ENSURE(),
	 * 	RKH_INVARIANT(), and RKH_ERROR() do NOT evaluate the test condition
	 * 	passed as the argument to these macros. One notable exception is the
	 * 	macro RKH_ALLEGE(), that still evaluates the test condition, but does
	 * 	not report assertion failures when the switch 
	 * 	RKH_CFG_FWK_ASSERT_EN is defined.
	 *
	 *	Example of use:
	 *	\code
	 *	...
	 *	some_function( const char *p, int size )
	 *	{
	 *		RKH_ASSERT( 	p != ( const char* )0 &&
	 *					size > 0  &&
	 *					size < MAX_SIZE );
	 *		...
	 *	}
	 *	\endcode
	 *
	 * 	\param exp		expression to be checked.
	 * 	
	 * 	\sa RKH_ALLEGE(), RKH_REQUIRE(), RKH_ENSURE(), RKH_ERROR() and 
	 * 	RKH_INVARIANT() macros.
	 */

	#define RKH_ASSERT( exp )					\
		if( ( exp ) )							\
		{}										\
		else									\
		{										\
			rkh_assert( m_name, __LINE__ );		\
		}

    /** 
 	 * 	\brief 
	 * 	General purpose assertion that ALWAYS evaluates the \a exp
	 * 	argument and calls the RKH_ASSERT() macro if the \a exp	evaluates 
	 * 	to FALSE.
	 *
	 * 	\note The \a exp argument IS always evaluated even when assertions 
	 * 	are disabled with the RKH_CFG_FWK_ASSERT_EN. 
	 * 	When the RKH_CFG_ASSERT_EN is set to one (1), the RKH_ASSERT() 
	 * 	macro is NOT called, even if the \a exp evaluates to FALSE.
     */

	#define RKH_ALLEGE( exp )			RKH_ASSERT( exp )

    
	/** 
	 * 	\brief
	 * 	Assertion that always calls the rkh_assert() callback if
	 * 	ever executed.
	 *
	 * 	\note 
	 * 	Can be disabled with the RKH_CFG_FWK_ASSERT_EN switch.
	 */

    #define RKH_ERROR() 							\
										rkh_assert(m_name,__LINE__)

#else
	#define RKH_MODULE_NAME( __fname )
	#define RKH_THIS_MODULE
	#define RKH_ASSERT( exp )			((void)0)
	#define RKH_ALLEGE( exp )			((void)(exp))
	#define RKH_ERROR()					((void)0)
#endif


/**
 * 	\brief
 *	This macro checks the precondition. 
 *
 *	This macro is equivalent to RKH_ASSERT() macro, except the name provides 
 *	a better documentation of the intention of this assertion.
 */

#define RKH_REQUIRE( exp )				RKH_ASSERT( exp )


/**
 * 	\brief
 *	This macro checks the postcondition. 
 *
 *	This macro is equivalent to RKH_ASSERT() macro, except the name provides 
 *	a better documentation of the intention of this assertion.
 */

#define RKH_ENSURE( exp )				RKH_ASSERT( exp )


/**
 * 	\brief
 *	This macro is used to check a loop invariant. 
 *
 *	This macro is equivalent to RKH_ASSERT() macro, except the name provides 
 *	a better documentation of the intention of this assertion.
 */

#define RKH_INVARIANT( exp )			RKH_ASSERT( exp )


#endif
