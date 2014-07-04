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
 *  File                     : rkh.h
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	fwk
 *
 * 	\brief 		RKH framwwork platform-independent interface.
 *
 * 	\note 		(1) This header file must be included in all modules (*.c 
 * 					files) that use RKH.
 */


#ifndef __RKH_H__
#define __RKH_H__


#include <stdlib.h>
#include "rkhitl.h"
#include "rkhrq.h"
#include "rkhmp.h"
#include "rkhtim.h"
#include "rkhassert.h"
#include "rkhtrc.h"


/**
 *	\brief
 *	This macro appears at the top of each C/C++ source file defining 
 *	the version string for that file (module).
 *
 * 	\param __fname		file (module) name.
 * 	\param __version 	file (module) version.
 */

#define RKH_MODULE_VERSION( __fname, __version )				\
						static RKHROM char *const m_version = #__version;


/**
 *	\brief
 *	Get the module version.
 */

#define RKH_MODULE_GET_VERSION()		\
						((const char*)m_version);


/**
 *	\brief
 *	This macro appears at the top of each C/C++ source file defining 
 *	the description string for that file (module).
 *
 * 	\param __fname		file (module) name.
 * 	\param __desc	 	file (module) description.
 */

#define RKH_MODULE_DESC( __fname, __desc )				\
						static RKHROM char *const m_desc = __desc;


/**
 *	\brief
 *	Get the module description.
 */

#define RKH_MODULE_GET_DESC()		\
						((const char*)m_desc)


#if RKH_EN_NATIVE_DYN_EVENT == RKH_ENABLED && \
	RKH_EN_DOXYGEN == RKH_DISABLED

		#define RKH_DYNE_TYPE			RKH_MP_T

		#define RKH_DYNE_INIT( mp, sstart, ssize, esize ) 	\
    			rkh_mp_init( (mp),sstart,(rui16_t)ssize,(RKH_MPBS_T)esize )

		#define RKH_DYNE_GET_ESIZE( mp )					\
				( (mp)->bsize )

		#define RKH_DYNE_GET( mp, e )						\
				( (e) = (RKH_EVT_T*)rkh_mp_get( (mp) ) )

		#define RKH_DYNE_PUT( mp, e )						\
				( rkh_mp_put( (mp), e ) )
#else
	#define RKH_DYNE_TYPE								rui8_t
	#define RKH_DYNE_INIT( mp, sstart, ssize, esize ) 	(void)0
	#define RKH_DYNE_GET_ESIZE( mp )					(void)0
	#define RKH_DYNE_GET( mp, e )						(void)0
	#define RKH_DYNE_PUT( mp, e )						(void)0
#endif


/**
 * 	\brief
 * 	Priority arranged table of registered SMA.
 *
 * 	Register a state machine application into the framework implies to store 
 * 	a pointer to the SMA in the priority table. A unique priority number must 
 * 	be assigned to each SMA from 0 to RKH_LOWEST_PRIO. The lower the number, 
 * 	the higher the priority. 
 */

extern RKH_SMA_T *rkh_sptbl[ RKH_CFG_MAX_SMA ];


/**
 * 	\brief
 * 	rkh_maptbl[] is a table in ROM, used to equate an index from 0 to 7 to a 
 * 	bit mask.
 */

extern RKHROM rui8_t rkh_maptbl[ 8 ];


/**
 * 	\brief
 * 	rkh_unmaptbl[] is a table in ROM, used to return the bit position of the 
 * 	highest priority bit set - a number between 0 and 7.
 */

extern RKHROM rui8_t rkh_unmaptbl[ 256 ];


/**
 * 	\brief
 * 	String describing the RKH version. 
 */

extern RKHROM char rkh_version[];


/**
 * 	\brief
 * 	Event pool list.
 */

#if RKH_CFG_EN_DYNAMIC_EVENT == RKH_ENABLED
extern RKH_DYNE_TYPE rkh_eplist[ RKH_CFG_MAX_EPOOL ];
#endif


/**
 * 	\brief
 * 	Each condition connector can have one special branch with a guard 
 *	labeled ELSE, which is taken if all the guards on the other 
 *	branches are false.
 *
 * 	A guard function takes the state machine pointer and the event 
 * 	pointer as arguments.
 * 	These arguments are optional, thus they could be eliminated in 
 * 	compile-time by means of RKH_EN_GRD_EVT_ARG and RKH_EN_GRD_HSM_ARG 
 * 	preprocessor directives.
 */

#define ELSE		rkh_else


/**
 * 	\brief
 *	This macro creates a composite state.
 *
 *	\sa
 *	RKH_SCMP_T structure definition for more information.
 *
 * 	\param name		state name. Represents a composite state structure.
 * 	\param en		pointer to state entry action. This argument is 
 *					optional, thus it could be declared as NULL.
 *					The RKH implementation preserves the transition sequence 
 *					imposed by Harel's Statechart and UML. 
 * 	\param ex		pointer to state exit action. This argument is 
 *					optional, thus it could be declared as NULL.
 *					The RKH implementation preserves the transition sequence 
 *					imposed by Harel's Statechart and UML. 
 * 	\param parent	pointer to parent state.
 * 	\param defchild	pointer to default child state or pseudostate.
 * 	\param history	pointer history pseudostate. This argument is 
 *					optional, thus it could be declared as NULL.
 */

#define RKH_CREATE_COMP_STATE( name, en, ex, parent, defchild, history ) \
																		 \
								extern RKHROM RKH_TR_T name##_trtbl[];	 \
																		 \
								RKHROM RKH_SCMP_T name =					 \
								{										 \
									{{MKBASE(RKH_COMPOSITE, name)},		 \
									MKST(en,ex,parent)},				 \
									MKCOMP(name,defchild,history)		 \
								}


/**
 * 	\brief
 *	This macro creates a basic state.
 *
 *	\sa
 *	RKH_SBSC_T structure definition for more information.
 *
 * 	\param name		state name. Represents a basic state structure.
 * 	\param en		pointer to state entry action. This argument is 
 *					optional, thus it could be declared as NULL.
 *					The RKH implementation preserves the transition sequence 
 *					imposed by Harel's Statechart and UML. 
 * 	\param ex		pointer to state exit action. This argument is 
 *					optional, thus it could be declared as NULL.
 *					The RKH implementation preserves the transition sequence 
 *					imposed by Harel's Statechart and UML. 
 * 	\param parent	pointer to parent state.
 * 	\param prepro	pointer to input preprocessor function. This function 
 * 					could be called "Moore" action.
 * 					This argument is optional, thus it could be declared 
 * 					as NULL.
 *					Aditionally, by means of single inheritance in C it 
 *					could be used as state's abstract data. 
 *					Moreover, implementing the single inheritance in C 
 *					is very simply by literally embedding the base type, 
 *					RKH_PPRO_T in this case, as the first member of the 
 *					derived structure. See \a prepro member of RKH_SBSC_T 
 *					structure for more information. Example:
 *  				\code
 *					static RKH_SIG_T
 *					preprocessor( RKH_EVT_T *pe )
 *					{
 *						...
 *					}
 *					typedef struct
 *					{
 *						RKH_PPRO_T prepro; 	// extend the RKH_PPRO_T class
 *						unsigned min:4;
 *						unsigned max:4;
 *						char *buff;
 *					} SDATA_T;
 *					
 *					static const SDATA_T option = { preprocessor,4,8,token1 };
 *					
 *					RKH_CREATE_BASIC_STATE( S111, set_x_1, 
 *											NULL, &S11, preprocessor ); 
 *					RKH_CREATE_BASIC_STATE( S22, set_x_4, 
 *											NULL, &S2, 
 *											(RKH_PPRO_T*)&option ); 
 *					\endcode
 */

#define RKH_CREATE_BASIC_STATE( name, en, ex, parent, prepro )			\
																		\
								extern RKHROM RKH_TR_T name##_trtbl[];	\
																		\
								RKHROM RKH_SBSC_T name =				\
								{										\
									{{MKBASE(RKH_BASIC, name)},			\
									MKST(en,ex,parent)},				\
									MKBASIC(name,prepro)				\
								}

/**
 * 	\brief
 *	This macro creates a conditional pseudostate (a.k.a. junction). 
 *
 * 	The conditional pseudostates are semantic-free vertices that are used to 
 * 	chain together multiple transitions. They are used to construct compound 
 * 	transition paths between states. For example, a junction can be used to 
 * 	converge multiple incoming transitions into a single outgoing transition 
 * 	representing a shared transition path (this is known as a merge).
 * 	Conversely, they can be used to split an incoming transition into multiple 
 * 	outgoing transition segments with different guard conditions. This 
 * 	realizes a static conditional branch. (In the latter case, outgoing 
 * 	transitions whose guard conditions evaluate to false are disabled. A 
 * 	predefined guard denoted "ELSE" may be defined for at most one outgoing 
 * 	transition. This transition is enabled if all the guards labeling the 
 * 	other transitions are false.) Static conditional branches are distinct 
 * 	from dynamic conditional branches that are realized by choice vertices.
 *	
 *	\sa
 *	RKH_SCOND_T structure definition for more information.
 *
 * 	\param name		pseudostate name. Represents a conditional pseudostate 
 * 					structure.
 */

#define RKH_CREATE_COND_STATE( name )									\
																		\
								extern RKHROM RKH_TR_T name##_trtbl[];	\
																		\
								RKHROM RKH_SCOND_T name =				\
								{										\
									{MKBASE(RKH_CONDITIONAL, name)},	\
									name##_trtbl 						\
								}


/**
 * 	\brief
 *	This macro creates a choice pseudostate. 
 *
 * 	Choice pseudostate which, when reached, result in the dynamic evaluation 
 * 	of the guards of its outgoing transitions. This realizes a dynamic 
 * 	conditional branch. It allows splitting of transitions into multiple 
 * 	outgoing paths such that the decision on which path to take may be a 
 * 	function of the results of prior actions performed in the same 
 * 	run-to-completion step. If more than one of the guards evaluates to true, 
 * 	an arbitrary one is selected. If none of the guards evaluates to true, 
 * 	then the model is considered ill-formed. To avoid this, it is recommended 
 * 	to define one outgoing transition with the predefined "ELSE" guard for 
 * 	every choice pseudostate.
 *	Also, branches cannot contain triggers, but in addition to a guard they 
 *	may contain actions. A branch can enter another choice connector, thus 
 *	providing for the nesting of branches.
 *	
 *	\sa
 *	RKH_SCHOICE_T structure definition for more information.
 *
 * 	\param name		pseudostate name. Represents a choice pseudostate 
 * 					structure.
 */

#define RKH_CREATE_CHOICE_STATE( name )									\
																		\
								extern RKHROM RKH_TR_T name##_trtbl[];	\
																		\
								RKHROM RKH_SCHOICE_T name =				\
								{										\
									{MKBASE(RKH_CHOICE, name)},			\
									name##_trtbl 						\
								}


/**
 * 	\brief
 *	This macro creates a deep history pseudostate. 
 *
 *	Deep history applies downwards to all levels of nesting.
 *
 *	\note
 *	At this framework version, it is not recommended to instantiate the 
 *	same history object more than once using this macro, since it uses a 
 *	static memory to store the last visited state (memory of history 
 *	pseudostate).
 *
 *	\sa
 *	RKH_SHIST_T structure definition for more information.
 *
 *	Arguments:
 *
 * 	\param name		pseudostate name. Represents a deep history 
 * 					pseudostate structure.
 * 	\param parent	pointer to parent state.
 */

#define RKH_CREATE_DEEP_HISTORY_STATE( name, parent )					\
																		\
						static RKHROM RKH_ST_T *ram##name;				\
																		\
						RKHROM RKH_SHIST_T name =						\
						{												\
							{MKBASE(RKH_DHISTORY, name)},				\
							(RKHROM struct RKH_ST_T *)parent,&ram##name \
						}


/**
 * 	\brief
 *	This macro creates a shallow history pseudostate. 
 *
 *	Shallow history means that history applies to the current nesting context 
 *	only – states nested more deeply are not affected by the presence of a 
 *	history pseudostates in a higher context.
 *	
 *	\note
 *	At this framework version, it is not recommended to instantiate the 
 *	same history object more than once using this macro, since it uses a 
 *	static memory to store the last visited state (memory of history 
 *	pseudostate).
 *
 *	\sa
 *	RKH_SHIST_T structure definition for more information.
 *
 * 	\param name		pseudostate name. Represents a shallow history 
 * 					pseudostate structure.
 * 	\param parent	pointer to parent state.
 */

#define RKH_CREATE_SHALLOW_HISTORY_STATE( name, parent )				\
																		\
						static RKHROM RKH_ST_T *ram##name;				\
																		\
						RKHROM RKH_SHIST_T name =						\
						{												\
							{MKBASE(RKH_SHISTORY, name)},				\
							(RKHROM struct RKH_ST_T *)parent,&ram##name \
						}


/**
 * 	\brief
 *	This macro creates a submachine state.
 *
 * 	A submachine state is a kind of a state that actually refers to 
 * 	another defined state machine.
 * 	A submachine state is logically equivalent to the insertion of the 
 * 	referenced state machine as a composite state in the place of 
 * 	the submachine state. Consequently, every entrance to a submachine 
 * 	state is equivalent to the corresponding entrance to the inserted 
 * 	(referenced) composite state. In particular, it can be entered 
 * 	thruough its initial pseudostate (as any other composite state), or 
 * 	through one of its entry points. 
 *
 * 	Similary, every exit from a submachine state is equivalent to the 
 * 	corresponding exit from the inserted composite state. It can be exited 
 * 	through one of its exit points. When it is exited through its exit point 
 * 	the effect of the transition targeting the exit point is executed first, 
 * 	followed by the exit behavior of the composite state. 
 *
 * 	The purpose od defining submachine states is to decompose and localize 
 * 	repetitive parts because the same state machine can be referenced from 
 * 	more than one submachine state.
 *
 *	\code
 *	RKH_CREATE_SUBMACHINE_STATE( 	adquire,		// state name
 *									start_adquire, 	// entry action
 *									stop_adquire, 	// exit action
 *									&processing, 	// parent state
 *									&herror );		// referenced submachine
 *	\endcode
 *
 *	\sa
 *	RKH_SSBM_T structure definition for more information.
 *
 * 	\param name		submachine state name. Represents a submachine state 
 * 					structure.
 * 	\param en		pointer to state entry action. This argument is 
 *					optional, thus it could be declared as NULL.
 *					The RKH implementation preserves the transition sequence 
 *					imposed by Harel's Statechart and UML. 
 * 	\param ex		pointer to state exit action. This argument is 
 *					optional, thus it could be declared as NULL.
 *					The RKH implementation preserves the transition sequence 
 *					imposed by Harel's Statechart and UML. 
 * 	\param parent	pointer to parent state.
 * 	\param sbm		pointer to referenced submachine state machine.
 */

#define RKH_CREATE_SUBMACHINE_STATE( name, en, ex, parent, sbm )		\
																		\
							extern RKHROM RKH_EXPCN_T name##_exptbl[];	\
							extern RKHROM RKH_TR_T name##_trtbl[];		\
																		\
							RKHROM RKH_SSBM_T name =						\
							{											\
								{{MKBASE(RKH_SUBMACHINE, name)},		\
								MKST(en,ex,parent)},					\
								MKSBM(name,sbm)							\
							}


/**
 * 	\brief
 *	This macro creates a exit point connection point reference table. 
 *	This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_EX_CNNPNT_TABLE( S2 )
 *		RKH_EX_CNNPNT( EX1S2, &EXPNT1, NULL, &S1 ),
 *		RKH_EX_CNNPNT( EX2S2, &EXPNT2, NULL, &S3 ),
 *	RKH_END_EX_CNNPNT_TABLE
 *	\endcode
 *
 * 	Each exit point connection reference table always begins with the macro 
 * 	RKH_CREATE_EX_CNNPNT_TABLE() and ends with the macro 
 * 	RKH_END_EX_CNNPNT_TABLE().
 *	As noted above, sandwiched between these macros are the exit point 
 *	macros, RKH_EX_CNNPNT().
 *
 *	\note
 *	This macro is not terminated with the semicolon.
 *
 * 	\param name		submachine state name.
 */

#define RKH_CREATE_EX_CNNPNT_TABLE( name )								\
								RKHROM RKH_EXPCN_T name##_exptbl[]={


/**
 * 	\brief
 *	This macro creates an exit point connection point reference.
 *	
 *	Connection point references are sources/targets of transitions implying 
 *	exits out of/entries into the submachine state machine referenced by a 
 *	submachine state.
 * 
 *	An exit point connection point reference as the source of a transition 
 *	implies that the source of the transition is the exit point pseudostate 
 *	as defined in the submachine of the submachine state that has the exit 
 *	point connection point defined.
 *
 *	A connection point reference to an exit point has the same notation as 
 *	an exit point pseudostate.
 *
 * 	\code
 *	// --- exit point pseudostates of SB submachine ---
 *	RKH_CREATE_REF_EXPNT( 	EXPNT1, 
 *							0,		// index of exit point connection table
 *							&SB );
 *	RKH_CREATE_REF_EXPNT( 	EXPNT2, 
 *							1, 		// index of exit point connection table
 *							&SB );
 *							...
 *	// --- exit point connection references of S12 submachine state ---
 *	RKH_CREATE_EX_CNNPNT_TABLE( S12 )
 *		RKH_EX_CNNPNT( EX1S12, &EXPNT1, ... ), // table index = 0 (EXPNT1)
 *		RKH_EX_CNNPNT( EX2S12, &EXPNT2, ... ), // table index = 1 (EXPNT2)
 *	RKH_END_EX_CNNPNT_TABLE
 *	\endcode
 *
 *	\sa
 *	RKH_EXPCN_T structure definition for more information.
 *
 *	\code
 *	\endcode
 *
 * 	\param name		exit point connection point reference name.
 * 	\param expnt	referenced exit point.
 * 	\param act		pointer to transition action function. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param ts		pointer to target state.
 */

#define RKH_EX_CNNPNT( name, expnt, act, ts )		\
								{act, (RKHROM struct RKH_ST_T *)ts}


/**
 * 	\brief
 *	This macro is used to terminate a exit point connection reference 
 *	table. This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_EX_CNNPNT_TABLE( S2 )
 *		RKH_EX_CNNPNT( EX1S2, &EXPNT1, NULL, &S1 ),
 *		RKH_EX_CNNPNT( EX2S2, &EXPNT2, NULL, &S3 ),
 *	RKH_END_EX_CNNPNT_TABLE
 *	\endcode
 *
 * 	Each exit point table always begins with the macro 
 * 	RKH_CREATE_EX_CNNPNT_TABLE() and ends with the macro 
 * 	RKH_END_EX_CNNPNT_TABLE().
 *	As noted above, sandwiched between these macros are the exit point 
 *	macros, RKH_EX_CNNPNT().
 *
 *	\note
 *	This macro is not terminated with the semicolon.
 */

#define RKH_END_EX_CNNPNT_TABLE		};


/**
 * 	\brief
 *	This macro creates an entry point connection point reference.
 *	
 *	Connection point references are sources/targets of transitions implying 
 *	exits out of/entries into the submachine state machine referenced by a 
 *	submachine state.
 * 
 *	An entry point connection point reference as the target of a transition 
 *	implies that the target of the transition is the entry point pseudostate 
 *	as defined in the submachine of the submachine state.
 *
 *	A connection point reference to an entry point has the same notation as 
 *	an entry point pseudostate.
 *
 *	\sa
 *	RKH_SENP_T structure definition for more information.
 *
 *	\code
 *	\endcode
 *
 * 	\param name		entry point connection point reference name.
 * 	\param enpnt	referenced entry point.
 * 	\param subm		pointer to submachine state.
 */

#define RKH_EN_CNNPNT( name, enpnt, subm )						\
																\
							RKHROM RKH_SENP_T name =				\
							{									\
								{MKBASE(RKH_ENPOINT, name)},	\
								MKENP(enpnt,subm)				\
							}


/**
 * 	\brief
 *	This macro creates a submachine state machine, which is to be 
 *	inserted in place of the (submachine) state.
 *
 * 	\code
 * 	RKH_CREATE_REF_SUBMACHINE( 	adquire, 
 * 								&wait, 
 * 								init_adquire );
 * 	\endcode
 *
 *	\sa
 *	RKH_RSM_T structure definition for more information.
 *
 * 	\param name		submachine name. Represents a submachine structure.
 * 	\param defchild	pointer to default child state.
 * 	\param iact		pointer to initialization action (optional). The 
 * 					function prototype is defined as RKH_INIT_ACT_T. This 
 * 					argument is optional, thus it could be declared as 
 * 					NULL.
 */

#define RKH_CREATE_REF_SUBMACHINE( name, defchild, iact )				\
																		\
								static RKHROM RKH_ST_T *rdyp_##name;		\
																		\
								RKHROM RKH_RSM_T name =					\
								{										\
									{MKBASE(RKH_REF_SUBMACHINE, name)},	\
									MKMCH(defchild,iact,name) 			\
								}


/**
 * 	\brief
 *	This macro creates an exit point.
 *
 * 	An exit pseudostate is used to join an internal transition terminating on 
 * 	that exit point to an external transition emanating from that exit point. 
 * 	The main purpose of such entry and exit points is to execute the state 
 * 	entry and exit actions respectively in between the actions that are 
 * 	associated with the joined transitions.
 *
 * 	\code
 * 	RKH_CREATE_REF_EXPNT( 	handled, 
 * 							0, 
 * 							&handle_error );
 * 	\endcode
 *
 *	\sa
 *	RKH_SEXP_T structure definition for more information.
 *
 *	\code
 *	// --- exit point pseudostates of SB submachine ---
 *	RKH_CREATE_REF_EXPNT( 	EXPNT1, 
 *							0,		// index of exit point connection table
 *							&SB );
 *	RKH_CREATE_REF_EXPNT( 	EXPNT2, 
 *							1, 		// index of exit point connection table
 *							&SB );
 *							...
 *	// --- exit point connection references of S12 submachine state ---
 *	RKH_CREATE_EX_CNNPNT_TABLE( S12 )
 *		RKH_EX_CNNPNT( EX1S12, &EXPNT1, ... ), // table index = 0 (EXPNT1)
 *		RKH_EX_CNNPNT( EX2S12, &EXPNT2, ... ), // table index = 1 (EXPNT2)
 *	RKH_END_EX_CNNPNT_TABLE
 *	\endcode
 *
 * 	\param name		entry point name.
 * 	\param ix		index of exit point connection table. Note that each row 
 * 					number matches with the index number of the exit point 
 * 					pseudostate that it represent.
 * 	\param subm		pointer to submachine state machine.
 */

#define RKH_CREATE_REF_EXPNT( name, ix, subm )				\
															\
							RKHROM RKH_SEXP_T name =			\
							{								\
								{MKBASE(RKH_EXPOINT, name)},\
								ix, subm 					\
							}


/**
 * 	\brief
 *	This macro creates a entry point.
 *
 * 	An entry pseudostate is used to join an external transition terminating 
 * 	on that entry point to an internal transition emanating from that entry 
 * 	point.
 * 	The main purpose of such entry and exit points is to execute the state 
 * 	entry and exit actions respectively in between the actions that are 
 * 	associated with the joined transitions.
 *
 * 	\code
 * 	RKH_CREATE_REF_ENPNT( 	show, 
 * 							2, 
 * 							&S2,
 * 							&handle_error );
 * 	\endcode
 *
 *	\sa
 *	RKH_ENPCN_T structure definition for more information.
 *
 *	\code
 *	\endcode
 *
 * 	\param name		entry point name.
 * 	\param act		pointer to transition action function. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param ts		pointer to target state.
 * 	\param subm		pointer to submachine state machine.
 */

#define RKH_CREATE_REF_ENPNT( name, act, ts, subm  )					\
																		\
								RKHROM RKH_ENPCN_T name = 				\
								{										\
									act, (RKHROM struct RKH_ST_T *)ts	\
								}


/**
 * 	\brief
 *	This macro creates a state transition table. This table have the general 
 *	structure shown below:
 *	\code
 *	RKH_CREATE_TRANS_TABLE( state_name )		// transition table begin
 *		RKH_TRxx( ... )							// transition
 *		RKH_TRxx( ... )							// transition
 *		...
 *	RKH_END_TRANS_TABLE							// transition table end
 *	\endcode
 *
 * 	Each transition table always begins with the macro RKH_CREATE_TRANS_TABLE() 
 * 	and ends with the macro RKH_END_TRANS_TABLE().
 *	As noted above, sandwiched between these macros are the transitions macros 
 *	that actually represent behavior of state.
 *
 *	\note
 *	This macro is not terminated with the semicolon.
 *
 * 	\param name		state name.
 */

#define RKH_CREATE_TRANS_TABLE( name )									\
																		\
								RKHROM RKH_TR_T name##_trtbl[]={


/**
 * 	\brief
 *	This macro defines a regular state transition.
 *	The general syntax of an expression labelling a transition in a 
 *	statechart is \e "i[c]/a" where \e i is the input that triggers the 
 *	transition, \e c is a condition that guards the transition from being 
 *	taken unless it is true when \e i occurs, and \e a is an action that 
 *	is carried out if and when the transition is taken. All of these parts 
 *	are optional.
 *
 *	Example:
 *	\code
 *	RKH_TRREG( 	TOUT0, 				// triggering event
 *				is_full, 			// guard function
 *				drop_frame, 		// action function
 *				&WAIT_SYNC )		// next state
 *	\endcode
 *
 *	\sa
 *	RKH_TR_T structure definition for more information.
 *
 * 	\param e		triggering event.
 * 	\param g		pointer to guard function. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param a		pointer to action function. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param t		pointer to target state.
 */

#define RKH_TRREG( e, g, a, t )	{ e, g, a, t }


/**
 * 	\brief
 *	This macro defines an internal state transition.
 *	Internal transitions are simple reactions to events that never lead 
 *	to change of state and consequently never cause execution of exit 
 *	actions, entry actions, or initial transitions.
 *
 *	Example:
 *	\code
 *	RKH_TRINT( 	RCV_DATA, 			// triggering event
 *				is_sync, 			// guard function
 *				store_data ) 		// action function
 *	\endcode
 *
 *	\sa
 *	RKH_TR_T structure definition for more information.
 *
 * 	\param e		triggering event.
 * 	\param g		pointer to guard function.	
 * 	\param a		pointer to action function.
 */

#define RKH_TRINT( e, g, a )	{ e, g, a, NULL }


/**
 * 	\brief
 *	This macro is used to terminate a state transition table.
 *	This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_TRANS_TABLE( state_name )		// transition table begin
 *		RKH_TRxx( ... )							// transition
 *		RKH_TRxx( ... )							// transition
 *		...
 *	RKH_END_TRANS_TABLE							// transition table end
 *	\endcode
 *
 * 	Each transition table always begins with the macro RKH_CREATE_TRANS_TABLE() 
 * 	and ends with the macro RKH_END_TRANS_TABLE().
 *	As noted above, sandwiched between these macros are the transitions macros 
 *	that actually represent behavior of state.
 *
 *	\note
 *	This macro is not terminated with the semicolon.
 */

#define RKH_END_TRANS_TABLE		{ RKH_ANY, NULL, NULL, NULL }};


/**
 *	This macro creates a branch table. This table have the general 
 *	structure shown below:
 *	\code
 *	RKH_CREATE_BRANCH_TABLE( C2 )
 *		RKH_BRANCH( is_power_ok, 	enable_process,	&power		),
 *		RKH_BRANCH( is_switch_off, 	turnoff,		&wait		),
 *		RKH_BRANCH( ELSE, 			abort,			&aborted	),
 *	RKH_END_BRANCH_TABLE
 *	\endcode
 *
 * 	Each branch table always begins with the macro RKH_CREATE_BRANCH_TABLE() 
 * 	and ends with the macro RKH_END_BRANCH_TABLE().
 * 	In RKH branches are defined by the macro RKH_BRANCH().
 *
 *	\sa
 *	This macro is not terminated with the semicolon. 
 *	Use rkh_else() when if all the guards on the other branches are false.
 *
 * 	\param name		conditional pseudostate name.
 */

#define RKH_CREATE_BRANCH_TABLE( name )								\
																	\
								RKH_CREATE_TRANS_TABLE( name )


/**
 * 	\brief
 *	This macro defines a branch in the branch table. 
 *
 *	Each condition connector can have one special branch with a guard 
 *	labeled rkh_else, which is taken if all the guards on the other 
 *	branches are false.
 *	The general syntax of an expression labelling a branch in a statechart is
 *	\e "[c]/a" where \e c is a condition that guards the transition from 
 *	being taken unless it is true, and \e a is an action that is carried out 
 *	if and when the transition is taken. All of these parts are optional. 
 *	
 *	Example:
 *	\code
 *	RKH_CREATE_BRANCH_TABLE( C2 )
 *		RKH_BRANCH( is_power_ok, 	enable_process,	&power		),
 *		RKH_BRANCH( is_switch_off, 	turnoff,		&wait		),
 *		RKH_BRANCH( ELSE, 			abort,			&aborted	),
 *	RKH_END_BRANCH_TABLE
 *	\endcode
 *
 *	\sa
 *	RKH_TR_T structure definition for more information.
 *
 * 	\param g		branch guard function. Branches are labeled with guards 
 * 					that determine which one is to be actually taken. Use 
 * 					ELSE macro when if all the guards on the other branches 
 * 					are false.
 * 	\param a		pointer to transition action. This argument is optional, 
 * 					thus it could be declared as NULL.
 * 	\param t		pointer to target state.
 */

#define RKH_BRANCH( g, a, t )	{ 0, g, a, t }


/*
 * 	This macro is internal to RKH and the user application should 
 * 	not call it.
 */

#define RKH_EBTBL				{ RKH_ANY, NULL, NULL, NULL }


/**
 * 	\brief
 *	This macro is used to terminate a state transition table.
 *	This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_BRANCH_TABLE( C2 )
 *		RKH_BRANCH( is_power_ok, 	enable_process,	&power		),
 *		RKH_BRANCH( is_switch_off, 	turnoff,		&wait		),
 *		RKH_BRANCH( ELSE, 			abort,			&aborted	),
 *	RKH_END_BRANCH_TABLE
 *	\endcode
 *
 * 	Each branch table always begins with the macro RKH_CREATE_BRANCH_TABLE() 
 * 	and ends with the macro RKH_END_BRANCH_TABLE().
 *
 *	\sa
 *	This macro is not terminated with the semicolon. 
 */

#define RKH_END_BRANCH_TABLE	RKH_EBTBL};


/**
 * 	\brief
 *	This macro indicates the root state of a state machine.
 */

#define RKH_ROOT				RKH_NULL


/**
 * 	\brief
 * 	This macro declares a opaque pointer to previously created state machine 
 * 	application (SMA) to be used as a global object. 
 *
 * 	This global pointer represent the state machine in the application. 
 * 	The state machine pointers are "opaque" because they cannot access the 
 * 	whole state machine structure, but only the part inherited from the 
 * 	RKH_SMA_T structure. The power of an "opaque" pointer is that it allows 
 * 	to completely hide the definition of the state machine structure and make 
 * 	it inaccessible to the rest of the application. 
 *	
 *	\note
 * 	Generally, this macro is used in the SMA's header file.
 *
 * 	Example:
 * 	\code
 * 	//	my.h: state-machine application's header file
 * 	
 * 	RKH_SMA_DCLR( my );
 * 	\endcode
 * 	
 * 	\sa
 * 	RKH_SMA_CREATE().
 * 	
 * 	\param sma		pointer to previously created state machine application.
 */

#define RKH_SMA_DCLR( sma )		extern RKH_SMA_T *const sma


/**@{
 *
 * 	\brief
 * 	Declares a previously created state/pseudostate to be used 
 * 	as a global object.  
 *
 * 	\note
 * 	Generally, this macro is used in the state-machine's header file.
 */

#define RKH_DCLR_COMP_STATE		extern RKHROM RKH_SCMP_T
#define RKH_DCLR_BASIC_STATE	extern RKHROM RKH_SBSC_T
#define RKH_DCLR_COND_STATE		extern RKHROM RKH_SCOND_T
#define RKH_DCLR_CHOICE_STATE	extern RKHROM RKH_SCHOICE_T
#define RKH_DCLR_DHIST_STATE	extern RKHROM RKH_SHIST_T 
#define RKH_DCLR_SHIST_STATE	extern RKHROM RKH_SHIST_T
#define RKH_DCLR_SUBM_STATE		extern RKHROM RKH_SSBM_T
#define RKH_DCLR_REF_SUBM		extern RKHROM RKH_RSM_T
#define RKH_DCLR_ENPNT			extern RKHROM RKH_SENP_T
#define RKH_DCLR_REF_EXPNT		extern RKHROM RKH_SEXP_T
#define RKH_DCLR_REF_ENPNT		extern RKHROM RKH_ENPCN_T
/*@}*/


/**
 * 	\brief
 * 	Declares a opaque pointer to previously created array of state machine 
 * 	applications SMA (a.k.a Active Object) to be used as a global object. 
 *
 *	\note
 * 	Generally, this macro is used in the SMA's header file.
 *
 * 	Example:
 * 	\code
 * 	//	cli.h: state-machine application's header file
 * 	#define NUM_CLIENTS			4
 * 	
 * 	typedef struct
 * 	{
 * 		RKH_SMA_T sma;		// base structure
 * 		RKH_TMR_T cli_utmr; // usage time
 * 		RKH_TMR_T cli_rtmr;	// waiting request time
 * 	} CLI_T;				// Active Object derived from RKH_SMA_T structure
 *
 * 	RKH_ARRAY_SMA_DCLR( clis, NUM_CLIENTS );
 * 	\endcode
 * 	
 * 	\sa
 * 	RKH_SMA_CREATE().
 * 	
 * 	\param _arr		pointer to previously created array of state machine 
 * 					applications. To do that is recommended to use the macro 
 * 					RKH_ARRAY_SMA_CREATE().
 * 	\param _num		size of array [in active objects].
 */

#define RKH_ARRAY_SMA_DCLR( _arr, _num )	\
						extern RKH_SMA_T *const *_arr[ _num ]


/**
 * 	\brief
 * 	Declare and allocate an array of SMAs (a.k.a active objects) derived from 
 * 	RKH_SMA_T.
 *
 * 	Example:
 * 	\code
 *	// Defines SMAs (a.k.a Active Objects)
 *
 *	RKH_SMA_CREATE( CLI_T, cli0, 1, HCAL, &cli_idle, cli_init, NULL );
 *	RKH_SMA_CREATE( CLI_T, cli1, 2, HCAL, &cli_idle, cli_init, NULL );
 *	RKH_SMA_CREATE( CLI_T, cli2, 3, HCAL, &cli_idle, cli_init, NULL );
 *	RKH_SMA_CREATE( CLI_T, cli3, 4, HCAL, &cli_idle, cli_init, NULL );
 *
 *	RKH_ARRAY_SMA_CREATE( clis, NUM_CLIENTS ) 
 *	{
 *		&cli0, &cli1, &cli2, &cli3
 *	};
 * 	\endcode
 *
 * 	\param _arr		name of SMA's array.
 * 	\param _num		size of array [in active objects].
 */

#define RKH_ARRAY_SMA_CREATE( _arr, _num )	\
						RKH_SMA_T *const *_arr[ _num ] =

/**
 * 	\brief
 * 	Retrieves the pointer to active object from a SMA's array.
 *
 * 	Example:
 * 	\code
 * 	#define NUM_CLIENTS				4
 * 	#define CLI( _clino )			RKH_ARRAY_SMA( clis, _clino )
 * 	
 * 	#define CLI0					CLI(0)
 * 	#define CLI1					CLI(1)
 * 	#define CLI2					CLI(2)
 * 	#define CLI3					CLI(3)
 *
 * 	typedef struct
 * 	{
 * 		RKH_SMA_T sma;		// base structure
 * 		RKH_TMR_T cli_utmr; // usage time
 * 		RKH_TMR_T cli_rtmr;	// waiting request time
 * 	} CLI_T;				// Active Object derived from RKH_SMA_T structure
 *
 * 	RKH_ARRAY_SMA_DCLR( clis, NUM_CLIENTS );
 * 	\endcode
 *
 * 	\param _arr		name of SMA's array.
 * 	\param _ix		index (position in the array).
 */

#define RKH_ARRAY_SMA( _arr, _ix )		*_arr[_ix]


/**
 * 	\brief
 * 	Declares a previously created SMA to be used as a global object.  
 *
 *	Example:
 *	\code
 *	//	g_my: global pointer to SMA "my".
 *	RKH_DCLR_SM_GLOBAL( MYSM_T, my, g_my );
 *	\endcode
 *
 *	\sa
 *	RKH_SMA_T structure definition for more information. Also, 
 *	\link RKH_EVT_T single inheritance in C \endlink, and 
 *	\link RKH_CREATE_BASIC_STATE another example \endlink.
 *
 * 	\param sma_t		data type of SMA.
 	\param sm			name of previously created SMA.
 * 	\param gob			name of global object.
 *
 * 	\note
 * 	Generally, this macro is used in the state-machine's module.
 */

#define RKH_DCLR_SM_GLOBAL( sma_t, sm, gob )				\
									sma_t * const gob = &s_##sm;


/**
 * 	\brief
 * 	Declares a state transition table.
 *
 * 	\param name			name of state (basic or composite) object.
 */

#define RKH_DECLARE_TR_TBL( name ) \
			extern RKHROM RKH_TR_T name##_trtbl[]


/**
 * 	\brief
 *	Initializes the parameters (attibutes) of a basic state object.
 *	
 *	By means of single inheritance in C it could be used to associate data 
 *	to a basic state. Moreover, implementing the single inheritance in C 
 *	is very simply by literally embedding the base type, RKH_SBSC_T in this 
 *	case, as the first member of the derived structure. The following 
 *	listing shows an example:
 *
 *	\code
 *	(1) typedef struct MENU_ST_T
 *		{
 *	(2)		RKHROM RKH_SBSC_T base;
 *	(3)		const char *title;
 *		} MENU_ST_T;
 *	
 *	...
 *
 *	(4) #define MENU_BASIC_STATE( type_t, name, en, ex, parent, title ) \
 *	(5)				RKH_DECLARE_TR_TBL( name ); \
 *					\
 *	(6)				RKHROM type_t name = \
 *					{ \
 *	(7)					RKH_INIT_BASIC_STATE( name, en, ex, parent, NULL ), \
 *	(8)					title \
 *					}
 *					
 *	(9) MENU_BASIC_STATE( MENU_ST_T, menu_cfg, 	NULL, NULL, RKH_ROOT, 
 *												"Menu 1" );
 *		RKH_CREATE_TRANS_TABLE( menu_cfg )
 *			RKH_TRREG( TIMEOUT, NULL, mc_title, &menu_cfg_resume ),
 *			...
 *		RKH_END_TRANS_TABLE
 *
 * 	...
 *
 *	 
 *	(10) void
 *		 mc_title( const struct RKH_SMA_T *sma )
 *		 {
 *		 	...
 *			lcd_print( "%s\n", ((MENU_ST_T *)(sma->state))->title );
 *		 }
 *	\endcode
 *
 *	(1)  Defines MENU_ST_T as a derived structure from the basic state 
 *		 structure. It could be used to associate data to a basic state 
 *		 objects. \n
 *	(2)	 Implementing the single inheritance in C is very simply by literally 
 *		 embedding the base type, RKH_SBSC_T in this case, as the first 
 *		 member of the derived structure.  \n
 *	(3)  Private members of MENU_ST_T derived structure. \n
 *	(4)  Defines a simple macro to instantiate the derived state object.
 *		 It is not strictly necessary.  \n
 *	(4)	 Declares the transtion table by means of RKH_DECLARE_TR_TBL() macro 
 *		 provided by the framework. \n
 *	(6)  Instantiates the derived state structure. \n
 *	(7)  Initializes the base structure, basic state in this case, using the 
 *		 RKH_INIT_BASIC_STATE() macro provided by the framework. \n
 *	(8)  Initializes the private member of derived state. \n
 *	(9)  Invokes the BLINKY_BASIC_STATE() macro to instantiate the 
 *		 derived state object, menu_cfg. Note that the "Menu 1" string is 
 *		 associated to the state machine context, menu_cfg state in this 
 *		 case. \n
 *	(10) Lastly, on the transtion action mc_title(), or any other action, is 
 *		 used the state data after casting the active object state to 
 *		 derived state object.
 *
 * 	The following listing shows another example for derived state structure, 
 * 	which access to RAM from ROM object (state structure).
 *	
 *	\code
 *	    typedef struct XY_T
 *		{
 *			int x;
 *			int y;
 *		} XY_T;
 *
 *	(1) typedef struct NUM_STATE_T
 *		{
 *	(2)		RKHROM RKH_SBSC_T base;
 *	(3) 	XY_T *p_ram_xy;
 *		} NUM_STATE_T;
 *
 *	(4) #define NUM_BASIC_STATE( name, en, ex, parent, p_xy ) \
 *	   				RKH_DECLARE_TR_TBL( name ); \
 *					\
 *	   				RKHROM NUM_STATE_T name = \
 *					{ \
 *	   					RKH_INIT_BASIC_STATE( name, en, ex, parent, NULL ), \
 *	(5)					p_xy \
 *					}
 *
 *		static XY_T xy;
 *	(6) NUM_BASIC_STATE( num, NULL, NULL, RKH_ROOT, &xy );
 *
 *	    void
 *		num_inc( const struct RKH_SMA_T *sma )
 *		{
 *	(7)		((NUM_STATE_T *)(sma->state))->p_ram_xy++;
 *			...
 *		}
 *	\endcode
 *
 *	(1)  Defines NUM_STATE_T as a derived structure from the basic state 
 *		 structure. \n
 *	(2)	 Implementing the single inheritance in C is very simply by literally 
 *		 embedding the base type, RKH_SBSC_T in this case, as the first 
 *		 member of the derived structure. \n
 *	(3)  Private members of NUM_STATE_T derived structure. It allows to 
 *		 acccess to RAM locations from this object (NUM_STATE_ST) allocated 
 *		 in ROM. \n
 *	(4)  Defines a simple macro to instantiate the derived state object. \n
 *	(5)  Initializes the private member of derived state. \n
 *	(6,7)Invokes the NUM_BASIC_STATE() macro to instantiate the derived 
 *		 state object, num. Note that the variable xy is allocated in RAM 
 *		 but it is access to read and write from ROM object. \n
 *
 *	\sa
 *	See #RKH_CREATE_BASIC_STATE() macro for more information.
 */

#define RKH_INIT_BASIC_STATE( name, en, ex, parent, prepro ) 			\
			{ 															\
				{ 														\
					{MKBASE(RKH_BASIC, name)}, 	/* RKH_BASE_T */ 		\
					MKST(en, ex, parent) 								\
				}, 								/* RKH_ST_T */ 			\
				MKBASIC(name, prepro) 									\
			}									/* RKH_SBSC_T */ 		\


/**
 * 	\brief
 *	Initializes the parameters (attibutes) of a composite state object.
 *	
 *	By means of single inheritance in C it could be used to associate data 
 *	to a basic state. Moreover, implementing the single inheritance in C 
 *	is very simply by literally embedding the base type, RKH_SCMP_T in this 
 *	case, as the first member of the derived structure. 
 *	
 *	\note
 *	See RKH_INIT_BASIC_STATE() and RKH_CREATE_COMP_STATE() macros to more 
 *	information.
 */

#define RKH_INIT_COMPOSITE_STATE( 	name, en, ex, parent, 				\
									defchild, history ) 				\
			{ 															\
				{ 														\
					{MKBASE(RKH_COMPOSITE, name)}, /* RKH_BASE_T */ 	\
					MKST(en, ex, parent) 								\
				}, 								   /* RKH_ST_T */ 		\
				MKCOMP(name, defchild, history) 						\
			}									   /* RKH_SCMP_T */ 		\


/** 	
 * 	\brief
 *  Return codes from rkh_sma_dispatch() function.
 */

typedef enum
{
	/**
	 * 	The arrived event was succesfully processed and HSM 
	 * 	resides in an allowed state.
	 */

	RKH_EVT_PROC,

	/**
	 * 	The arrived event was't founded in the transition table. 
	 */

	RKH_EVT_NFOUND,

	/**
	 * 	The branch function returned a value not founded 
	 * 	in the branch table.
	 */

	RKH_CND_NFOUND,

	/**
	 * 	The transition was cancelled by guard function.
	 */

	RKH_GRD_FALSE,

	/**
	 * 	Unknown state. 
	 */

	RKH_UNKN_STATE,

	/**
	 * 	The transition exceeded the allowed hierarchical level.
	 */

	RKH_EX_HLEVEL,

	/**
	 * 	The transition exceeded the allowed number of segments 
	 * 	within a compound transtion.
	 */

	RKH_EX_TSEG,

	RKH_NUM_CODES
} RKH_RCODE_T;


/** 	
 * 	\brief
 *  State machine properties.
 */

typedef enum
{
	/**
	 * 	Used as state machine property.
	 * 	This macro enables state nesting in a particular state machine.
	 */

	HCAL,


	/**
	 * 	Used as state machine property.
	 * 	This macro disables state nesting in a particular state machine.
	 * 	When FLAT is used in RKH_SMA_CREATE() macro some important features of 
	 * 	RKH are	not included: state nesting, composite state, history 
	 * 	(shallow and deep) pseudostate, entry action, and exit action.
	 */

	FLAT,

	/** Number of state machines properties */
	RKH_NUM_HPPTY
} RKH_HPPTY_T;


/**
 * 	\brief
 * 	This values are retrived by guard functions. 
 *
 * 	A guard is a boolean condition that returns a TRUE or FALSE value that 
 * 	controls whether or not a transition is taken following the receipt of 
 * 	a triggering event.
 */

typedef enum
{
	RKH_GFALSE,	/**< False condition */
	RKH_GTRUE	/**< True condition */
} RKH_GRET_T;


/**
 * 	\brief
 * 	Initializes the RKH framework. 
 *
 * 	A requirement of RKH is that must be called rkh_fwk_init() before call any 
 * 	of its other services. This function initializes all of RKH's variables 
 * 	and data structures.
 *
 * 	\note 
 *	Platform-dependent function. All RKH ports must be define it in the RKH 
 *	port file to a particular platform. However, only the ports to the 
 *	external OS/RTOS usually need some code to bolt the framework to the 
 *	external OS/RTOS.
 *
 *	Example for x86, VC2008, and win32 single thread:
 *	\code
 *	void 
 *	rkh_fwk_init( void )
 *	{
 *		InitializeCriticalSection( &csection );
 *		sma_is_rdy = CreateEvent( NULL, FALSE, FALSE, NULL );
 *	}
 *	\endcode
 */

void rkh_fwk_init( void );


/**
 * 	\brief
 * 	RKH framework is started.
 *
 * 	This entry function turns over control to RKH (and does not return!).
 * 	This function runs the highest priority state machine application (SMA) 
 * 	that is ready to run in run-to-completation model. 
 *
 * 	\note 
 * 	The call to this function does not return. Hence, any code after it will 
 * 	never be executed.
 * 	
 * 	\note 
 *	Platform-dependent function. All RKH ports must be define it in the RKH 
 *	port file to a particular platform. However, only the ports to the 
 *	external OS/RTOS usually need some code to bolt the framework to the 
 *	external OS/RTOS.
 *
 *	Example for x86, VC2008, and win32 single thread:
 *	\code
 *	void 
 *	rkh_fwk_enter( void )
 *	{ 
 *		rui8_t prio;
 *		RKH_SMA_T *sma;
 *		RKH_EVT_T *e;
 *
 *		RKH_HOOK_START();
 *		RKH_TR_FWK_EN();
 *		running = 1;
 *
 *		while( running )
 *		{
 *			RKH_ENTER_CRITICAL( dummy );
 *			if( RKH_RDY_ISNOT_EMPTY( rkhrg ) ) 
 *			{
 *				RKH_RDY_FIND_HIGHEST( rkhrg, prio );
 *				RKH_EXIT_CRITICAL( dummy );
 *				
 *				sma = rkh_sptbl[ prio ];
 *				e = rkh_sma_get( sma );
 *				rkh_sma_dispatch( sma, e );
 *				RKH_GC( e );
 *			}
 *			else
 *				rkh_hook_idle();
 *		}
 *		
 *		rkh_hook_exit();
 *		CloseHandle( sma_is_rdy );
 *		DeleteCriticalSection( &csection );	
 *	}
 *	\endcode
 *	
 *	Here is the basic algorithm for interpreting the listing shown above. 
 *	A pseudocode description of the procedure is:
 *	\code
 *	infinite loop
 *	{
 *		disable interrupts;
 *		if( is_active_object_ready_to_run )
 *		{
 *			find the active object with highest priority;
 *			enable interrupts;
 *			e = get the event from the active object's queue;
 *			dispatch the 'e' event to the active object's state machine;
 *			}
 *		else
 *			execute the idle processing;
 *	}
 *	\endcode
 */

void rkh_fwk_enter( void );


/**
 * 	\brief	
 * 	Exit the RKH framework.
 *
 * 	Function invoked by the application layer to exit the RKH application and 
 * 	return control to the underlying OS/Kernel.
 *
 * 	\note 
 *	This function is strongly platform-dependent. All RKH ports and must be 
 *	defined in the RKH port to a particular platform. 
 *	Some RKH ports might not require implementing this function at all, 
 *	because many embedded applications don't have anything to exit to.
 * 	
 * 	\note 
 *	Platform-dependent function. All RKH ports must be defined in the RKH 
 *	port file to a particular platform. However, only the ports to the 
 *	external OS/RTOS usually need some code to bolt the framework to the 
 *	external OS/RTOS.
 *
 *	Example:
 *	\code
 *	void 
 *	rkh_fwk_exit( void )
 *	{
 *		rkh_hook_exit();
 *		RKH_TR_FWK_EX();
 *	}
 *	\endcode
 */

void rkh_fwk_exit( void );


#if defined( RKH_USE_TRC_SENDER )

	/**
	 * 	\brief
	 * 	Keep tracks and updates the started timers. 
	 *
	 *	Time intervals are measured by periodic timer interrupts. Each timer 
	 *	interrupt is called a timer-tick. The actual time between timer-ticks 
	 *	is specified by the application. 
	 * 	This function must be placed where will be incrementing the system 
	 * 	tick. Normally this function is placed in a timer ISR routine.
	 * 	If one or more timers expires the assigned event is directly posted 
	 * 	into the state machine application (SMA) queue and associated hook 
	 * 	function is executed (if it's used). The expiration events of timers 
	 * 	that expire at the same time are executed in the order they were 
	 * 	started.
	 * 	
	 * 	\note
	 * 	This function is internal to RKH and the user application should 
	 * 	not call it. Instead, use #RKH_TIM_TICK() macro.
	 */

	void rkh_tmr_tick( const void *const sender );

	/**
	 * 	\brief
	 * 	Invoke the system clock tick processing rkh_tmr_tick().
	 *
	 * 	This macro is the recommended way of invoke the clock tick processing, 
	 * 	because it provides the vital information for software tracing and 
	 * 	avoids any overhead when the tracing is disabled.
	 *
	 * 	\param _sender		pointer to the sender object. Typically 
	 * 						RKH_TIM_TICK() will be called from an interrupt, 
	 * 						in which case it would create a unique object 
	 * 						just to unambiguously identify the ISR as the 
	 * 						sender of the time events.
	 *	\sa
	 *	rkh_tmr_tick().
	 */

	#define RKH_TIM_TICK( _sender )		rkh_tmr_tick( _sender )

#else

	void rkh_tmr_tick( void );
	#define RKH_TIM_TICK( dummy_ )		rkh_tmr_tick()

#endif


/**
 * 	\brief
 * 	Initializes and activates a previously created state machine application 
 * 	(SMA) as known as active object.
 *
 * 	A state machine application (SMA) is declared with the RKH_SMA_T data 
 * 	type and is defined with the rkh_sma_activate() service.
 *
 *	Example:
 *	\code
 *	...within state-machine application's module
 *
 *	typedef struct
 *	{
 *		RKH_SMA_T sm;	// base structure
 *		rui8_t x;		// private member
 *		rui8_t y;		// private member
 *	} MYSM_T;
 *
 * 	//	static instance of SMA object
 *	RKH_SMA_CREATE( MYSM_T, my, HCAL, &S1, my_iaction, &my_ievent );
 *
 *	void
 *	main( void )
 *	{
 *		...
 *		rkh_sma_activate( my, 4, qsto, sizeof( RKH_EVT_T* ), (void*)0, 0 );
 *	}
 *	\endcode
 * 	
 *	\note 
 *	Platform-dependent function. All RKH ports must be defined in the RKH 
 *	port file to a particular platform. However, only the ports to the 
 *	external OS/RTOS usually need some code to bolt the framework to the 
 *	external OS/RTOS.
 *	
 *	Example:
 *	\code
 *	void 
 *	rkh_sma_activate(	RKH_SMA_T *sma, const RKH_EVT_T **qs, 
 *						RKH_RQNE_T qsize, void *stks, rui32_t stksize )
 *	{
 *		( void )stks;
 *		( void )stksize;
 *		
 *		rkh_rq_init( &sma->equeue, qs, qsize, sma );
 *		rkh_sma_register( sma );
 *		rkh_sma_init_hsm( sma );
 *		RKH_TR_SMA_ACT( sma );
 *	}
 *	\endcode
 *
 * 	\param sma			pointer to previously created state machine 
 * 						application.
 * 	\param qs			base address of the event storage area. A message 
 * 						storage area is declared as an array of pointers to 
 * 						RKH events.
 * 	\param qsize		size of the storage event area [in number of entries].
 * 	\param stks			starting address of the stack's memory area.
 * 	\param stksize		size of stack memory area [in bytes].
 */

void rkh_sma_activate(	RKH_SMA_T *sma, const RKH_EVT_T **qs, 
						RKH_RQNE_T qsize, void *stks, rui32_t stksize );


/**
 * 	\brief
 * 	Declare and allocate a SMA (active object) derived from RKH_SMA_T. Also, 
 * 	initializes and assigns a state machine to previously declared SMA.
 *
 * 	In the UML specification, every state machine has a top state 
 * 	(the abstract root of every state machine hierarchy), which contains 
 * 	all the other elements of the entire state machine. RKH provides the 
 * 	top state using the macro RKH_SMA_CREATE().
 *	Frequently, RKH_SMA_CREATE() is used within state-machine's module 
 *	(.c file), thus the structure definition is in fact entirely encapsulated 
 *	in its module and is inaccessible to the rest of the application. 
 *	However, use the RKH_SMA_DCLR() macro to declare a "opaque" pointer 
 *	to that state machine application structure to be used in the rest of the 
 *	application but hiding the proper definition.
 * 	RKH_SMA_T is not intended to be instantiated directly, but rather
 * 	serves as the base structure for derivation of state machines in the
 * 	application code.
 * 	The following example illustrates how to derive an state machine from
 * 	RKH_SMA_T. Please note that the RKH_SMA_T member sm is defined as the
 * 	FIRST member of the derived structure.
 *
 *	Example:
 *	\code
 *	...within state-machine application's module
 *
 *	typedef struct
 *	{
 *		RKH_SMA_T sm;	// base structure
 *		rui8_t x;		// private member
 *		rui8_t y;		// private member
 *	} MYSM_T;
 *
 * 	//	static instance of SMA object
 *	RKH_SMA_CREATE( MYSM_T, my, 0, HCAL, &S1, my_iaction, &my_ievent );
 *	\endcode
 *
 * 	\param sma_t		data type of the SMA. Could be derived from RKH_SMA_T.
 * 	\param name			name of state machine application. Also, it 
 * 						represents the top state of state diagram.
 * 	\param prio			state machine application priority. A unique priority 
 * 						number must be assigned to each SMA from 0 to 
 * 						RKH_LOWEST_PRIO. The lower the number, the higher the 
 * 						priority. 
 * 	\param ppty			state machine properties. The available properties are
 * 						enumerated in RKH_HPPTY_T enumeration in the rkh.h 
 * 						file.
 * 	\param ist			pointer to initial state. This state could be defined 
 * 						either composite or basic (not pseudo-state).
 * 	\param iact			pointer to initialization action (optional). The 
 * 						function prototype is defined as RKH_INIT_ACT_T. This 
 * 						argument is optional, thus it could be declared as 
 * 						NULL.
 * 	\param ievt			pointer to an event that will be passed to state 
 * 						machine application when it starts. Could be used to 
 * 						pass arguments to the state machine like an argc/argv.
 * 						This argument is optional, thus it could be declared 
 * 						as NULL or eliminated in compile-time with 
 * 						RKH_CFG_SMA_IEVENT_EN = 0.
 */

#define RKH_SMA_CREATE( sma_t, name, prio, ppty, ist, iact, ievt )			\
																			\
	static RKHROM RKH_ROM_T rs_##name = MKRRKH( name, prio, ppty, ist, 		\
												iact, ievt );				\
	static sma_t s_##name = MKSMA( &rs_##name, ist );						\
	RKH_SMA_T *const name = (RKH_SMA_T *)&s_##name


/**
 * 	\brief
 * 	Terminate a state machine application (SMA) as known as active object.
 *
 * 	A state machine application may call this service to terminate itself. 
 * 	Once terminated, the state machine application must be re-created in 
 * 	order for it to execute again.
 * 	
 *	\note 
 *	Platform-dependent function. All RKH ports must be defined in the RKH 
 *	port file to a particular platform. However, only the ports to the 
 *	external OS/RTOS usually need some code to bolt the framework to the 
 *	external OS/RTOS.
 *
 *	Example:
 *	\code
 *	void 
 *	rkh_sma_terminate( RKH_SMA_T *sma )
 *	{
 *		rkh_sma_unregister( sma );
 *		RKH_TR_SMA_TERM( sma );
 *	}
 *	\endcode
 *
 * 	\param sma			pointer to previously created state machine 
 * 						application.
 */

void rkh_sma_terminate( RKH_SMA_T *sma );


#if defined( RKH_USE_TRC_SENDER )

	/**
	 * 	\brief
	 * 	Send an event to a state machine application (SMA) as known as active 
	 * 	object through a queue using the FIFO policy. A message is a pointer 
	 * 	size variable and its use is application specific. 
	 *
	 * 	\note
	 * 	This function is internal to RKH and the user application should 
	 * 	not call it. Instead, use RKH_SMA_POST_FIFO() macro.
	 * 	\note 
	 *	For memory efficiency and best performance the SMA's event queue, 
	 *	STORE ONLY POINTERS to events, not the whole event objects.
	 *	The assertion inside it guarantee that the pointer is valid, so is not 
	 *	necessary to check the pointer returned from rkh_sma_post_fifo().
	 *	\note 
	 *	Platform-dependent function. All RKH ports must be defined in the RKH 
	 *	port file to a particular platform. However, only the ports to the 
	 *	external OS/RTOS usually need some code to bolt the framework to the 
	 *	external OS/RTOS.
	 *
	 * 	\param sma		pointer to previously created state machine 
	 * 					application.
	 * 	\param e		actual event sent to the state machine application.
	 * 	\param sender	pointer to the sender object. It is not 
	 * 					necessarily a pointer to an active object. In 
	 * 					fact, if RKH_SMA_POST_FIFO() is called from an 
	 * 					interrupt or other context, it can create a 
	 * 					unique object just to unambiguously identify the 
	 * 					publisher of the event.
	 */

	void rkh_sma_post_fifo( RKH_SMA_T *sma, const RKH_EVT_T *e, 
												const void *const sender );

	/**
	 * 	\brief 
	 * 	Invoke the direct event posting facility rkh_sma_post_fifo().
	 *
	 * 	This macro is the recommended way of posting events, because it 
	 * 	provides the vital information for software tracing and avoids any 
	 * 	overhead when the tracing is disabled.
	 *
	 * 	\param _sma			pointer to previously created state machine 
	 * 						application.
	 * 	\param _e			actual event sent to the state machine application.
	 * 	\param _sender		pointer to the sender object. It is not 
	 * 						necessarily a pointer to an active object. In 
	 * 						fact, if RKH_SMA_POST_FIFO() is called from an 
	 * 						interrupt or other context, it can create a 
	 * 						unique object just to unambiguously identify the 
	 * 						publisher of the event.
	 *	\sa
	 *	rkh_sma_post_fifo().
	 */

	#define RKH_SMA_POST_FIFO( _sma, _e, _sender ) \
				rkh_sma_post_fifo( (_sma), (_e), (_sender) )

#else

	void rkh_sma_post_fifo( RKH_SMA_T *sma, const RKH_EVT_T *e );
	#define RKH_SMA_POST_FIFO( _sma, _e, _dummy ) \
				rkh_sma_post_fifo( (_sma), (_e) )

#endif


#if defined( RKH_USE_TRC_SENDER )

	/**
	 * 	\brief
	 * 	Send an event to a state machine application (SMA) as known as active 
	 * 	object through a queue using the LIFO policy. A message is a pointer 
	 * 	size variable and its use is application specific. 
	 *
	 * 	\note
	 * 	This function is internal to RKH and the user application should 
	 * 	not call it. Instead, use RKH_SMA_POST_LIFO() macro.
	 * 	\note
	 *	For memory efficiency and best performance the SMA's event queue, 
	 *	STORE ONLY POINTERS to events, not the whole event objects.
	 *	The assertion inside it guarantee that the pointer is valid, so is not 
	 *	necessary to check the pointer returned from rkh_sma_post_lifo().
	 *	\note 
	 *	Platform-dependent function. All RKH ports must be defined in the RKH 
	 *	port file to a particular platform. However, only the ports to the 
	 *	external OS/RTOS usually need some code to bolt the framework to the 
	 *	external OS/RTOS.
	 *
	 * 	\param sma		pointer to previously created state machine application.
	 * 	\param e		actual event sent to the state machine application.
	 * 	\param sender	pointer to the sender object. It is not 
	 * 					necessarily a pointer to an active object. In 
	 * 					fact, if RKH_SMA_POST_FIFO() is called from an 
	 * 					interrupt or other context, it can create a 
	 * 					unique object just to unambiguously identify the 
	 * 					publisher of the event.
	 */

	void rkh_sma_post_lifo( RKH_SMA_T *sma, const RKH_EVT_T *e, 
												const void *const sender );

	/**
	 * 	\brief 
	 * 	Invoke the direct event posting facility rkh_sma_post_lifo().
	 *
	 * 	This macro is the recommended way of posting events, because it 
	 * 	provides the vital information for software tracing and avoids any 
	 * 	overhead when the tracing is disabled.
	 *
	 * 	\param _sma			pointer to previously created state machine 
	 * 						application.
	 * 	\param _e			actual event sent to the state machine application.
	 * 	\param _sender		pointer to the sender object. It is not 
	 * 						necessarily a pointer to an active object. In 
	 * 						fact, if RKH_SMA_POST_LIFO() is called from an 
	 * 						interrupt or other context, it can create a 
	 * 						unique object just to unambiguously identify the 
	 * 						publisher of the event.
	 *	\sa
	 *	rkh_sma_post_lifo().
	 */

	#define RKH_SMA_POST_LIFO( _sma, _e, _sender ) \
				rkh_sma_post_lifo( (_sma), (_e), (_sender) )

#else

	void rkh_sma_post_lifo( RKH_SMA_T *sma, const RKH_EVT_T *e );
	#define RKH_SMA_POST_LIFO( _sma, _e, _dummy ) \
				rkh_sma_post_lifo( (_sma), (_e) )

#endif


/**
 * 	\brief
 * 	Get an event from the event queue of an state machine application (SMA) 
 * 	as known as active object. 
 * 	The events received are pointer size variables and their use is 
 * 	application specific.
 *
 *	\note 
 *	Platform-dependent function. All RKH ports must be defined in the RKH 
 *	port file to a particular platform. However, only the ports to the 
 *	external OS/RTOS usually need some code to bolt the framework to the 
 *	external OS/RTOS.
 *	Depending on the underlying OS or kernel, if no event is present at the 
 *	queue, the function will block the current thread until an event is 
 *	received.
 *
 *	\return
 * 	A non-NULL pointer indicates that a event pointer was available, 
 * 	otherwise a NULL pointer.
 */

RKH_EVT_T *rkh_sma_get( RKH_SMA_T *sma );


/**
 * 	\brief
 * 	Retrieves performance information for a particular state machine 
 * 	application (SMA) as known as active object. 
 *
 *	The user application must allocate an RKH_SMAI_T data structure used to 
 *	receive data. The performance information is available during run-time 
 *	for each of the RKH services. This can be useful in determining whether 
 *	the application is performing properly, as well as helping to optimize the 
 *	application.
 *	This information provides a "snapshot" a particular instant in time, i.e., 
 *	when the service is invoked.
 *
 * 	\note
 * 	See RKH_SMAI_T structure for more information. This function is 
 * 	optional, thus it could be eliminated in compile-time with 
 * 	RKH_CFG_SMA_GET_INFO_EN = 0.
 *
 * 	\param sma		pointer to previously created state machine application.
 * 	\param psi		pointer to the buffer into which the performance 
 * 					information will be copied by reference.
 */

void rkh_sma_get_info( RKH_SMA_T *sma, RKH_SMAI_T *psi );


/**
 * 	\brief
 * 	Clear performance information for a particular state machine application 
 * 	(SMA) as known as active object.
 *
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_CFG_SMA_GET_INFO_EN = 0.
 *
 * 	\param sma		pointer to previously created state machine application.
 */

void rkh_sma_clear_info( RKH_SMA_T *sma );


/**
 * 	\brief
 * 	Registers a state machine application (SMA) as known as active object into 
 * 	the framework, which implies to store a pointer to the SMA in the priority 
 * 	table.
 *
 * 	\param sma		pointer to previously created state machine application.
 */

void rkh_sma_register( RKH_SMA_T *sma );


/**
 * 	\brief
 *	Removes the SMA as known as active object from the priority table, and 
 *	thus from the framework, by simply replacing the link to the SMA being 
 *	deleted with a NULL pointer.
 * 	
 * 	\param sma		pointer to previously created state machine application.
 */

void rkh_sma_unregister( RKH_SMA_T *sma );


/**
 * 	\brief
 *	Defer an event to a given separate event queue.
 *
 * 	Event deferral comes in very handy when an event arrives in a 
 * 	particularly inconvenient moment but can be deferred for some later time, 
 * 	when the system is in a much better position to handle the event. RKH 
 * 	supports very efficient event deferring and recalling mechanisms.
 * 	This function is part of the event deferral mechanism. An SMA 
 * 	uses this function to defer an event \a e to the event queue \a q. 
 * 	RKH correctly accounts for another outstanding reference to the event 
 * 	and will not recycle the event at the end of the RTC step. 
 * 	Later, the SMA might recall one event at a time from the 
 * 	event queue by means of rkh_fwk_recall() function.
 *	
 *	Example:
 *	\code
 *	static RKH_RQ_T qurc;
 *	static RKH_EVT_T *qurc_sto[ MAX_SIZEOF_QURC ];
 *
 *	rkh_rq_init( &qurc, qurc_sto, MAX_SIZEOF_QURC, NULL );
 *	...
 *
 *	void 
 *	ring( const struct rkh_t *sma, RKH_EVT_T *pe )
 *	{
 *		(void)sma;      			// argument not used
 *		rkh_fwk_defer( &qurc, pe );	// defer event
 *	}
 *	\endcode
 *
 *	\note
 *	For memory efficiency and best performance the deferred event queue, 
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *  An SMA can use multiple event queues to defer events of
 *  different kinds.
 *	The assertion inside it guarantee that operation is valid, so is not 
 *	necessary to check the value returned from it.
 *
 * 	\param q		pointer to previously created queue.
 * 	\param e		pointer to event.
 */

void rkh_fwk_defer( RKH_RQ_T *q, const RKH_EVT_T *e );


/**
 * 	\brief
 * 	Recall a deferred event from a given event queue.
 *
 * 	This function is part of the event deferral support. An SMA 
 * 	uses this function to recall a deferred event from a given event queue. 
 * 	Recalling an event means that it is removed from the deferred event 
 * 	queue \a q and posted (LIFO) to the event queue of the \a sma state 
 * 	machine application.
 *
 *	Example:
 *	\code
 *	void 
 *	exit_rx_manager( const struct rkh_t *sma )
 *	{
 *		rkh_fwk_recall( sma, &qurc );
 *	}
 *	\endcode
 *
 * 	\note
 *	For memory efficiency and best performance the destination event queue, 
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *
 * 	\returns 
 * 	The pointer to the recalled event to the caller, or NULL if no 
 * 	event has been recalled.
 */

RKH_EVT_T *rkh_fwk_recall( RKH_SMA_T *sma, RKH_RQ_T *q );


/**
 * 	\brief
 * 	Registers a new event pool into the event pool list.
 *
 * 	Before using dynamic events (or event with arguments) the application 
 * 	code must register the event pools, which stores the events as a 
 * 	fixed-sized memory block. Each event pool must be registered with the 
 * 	RKH framework, by means of the rkh_fwk_epool_register() function.
 *
 *	This function initializes one event pool at a time and must be called
 * 	exactly once for each event pool before the pool can be used.
 *
 * 	The application code might initialize the event pools by making calls 
 * 	to the rkh_fwk_epool_register() function. However, for the simplicity of 
 * 	the internal implementation, the application code initialize event pools 
 * 	in the ascending order of the event size.
 *
 * 	Many RTOSes provide fixed block-size heaps, a.k.a. memory pools that can
 * 	be adapted for RKH event pools. In case such support is missing, RKH 
 * 	provides a native RKH event pool implementation. The macro 
 * 	#RKH_DYNE_TYPE determines the type of event pool used by a particular 
 * 	RKH port. See structure RKH_MP_T for more information.
 *
 * 	For adapting RKH event pools to any fixed-size memory block service RTOS 
 * 	provided the application code must define RKH_DYNE_TYPE, RKH_DYNE_INIT(), 
 * 	RKH_DYNE_GET_ESIZE(), RKH_DYNE_GET(), and RKH_DYNE_PUT() macros.
 *
 *  The dynamic allocation of events is optional then if the 
 *  #RKH_EN_NATIVE_DYN_EVENT is set to 1 and the native fixed-size 
 * 	memory block facility is enabled (see #RKH_CFG_MP_EN) then RKH will 
 * 	include its own implementation of dynamic memory management.
 * 	When #RKH_EN_NATIVE_DYN_EVENT is enabled RKH also will automatically 
 * 	define RKH_DYNE_TYPE, RKH_DYNE_INIT(), RKH_DYNE_GET_ESIZE(), 
 * 	RKH_DYNE_GET(), and RKH_DYNE_PUT().
 * 
 *	Example:
 *	\code
 *	#define SIZEOF_EP0STO				64
 *	#define SIZEOF_EP0_BLOCK			sizeof( TOUT_T )
 *
 *	#define SIZEOF_EP1STO				32
 *	#define SIZEOF_EP1_BLOCK			sizeof( DIAL_T )
 *
 *	#define SIZEOF_EP2STO				32
 *	#define SIZEOF_EP2_BLOCK			sizeof( SETUP_T )
 *	
 *	typedef struct
 *	{
 *		RKH_EVT_T evt;                  // base structure
 *		int timerno;					// parameter 'timerno'
 *	} TOUT_T;
 *
 *	typedef struct
 *	{
 *		RKH_EVT_T evt;                  // base structure
 *		char dial[ MAX_SIZE_DIAL ];     // parameter 'dial'
 *		int qty;                        // parameter 'qty'
 *	} DIAL_T;
 *		
 *	typedef struct
 *	{
 *		RKH_EVT_T evt;                  // base structure
 *		int volume;                     // parameter 'volume'
 *		int baud_rate;                  // parameter 'baud_rate'
 *		char name[ MAX_SIZE_NAME ];     // parameter 'name'
 *		int iloop;                      // parameter 'iloop'
 *	} SETUP_T;
 *	
 *	// declares the storage memory of event pool
 *	static rui8_t	ep0sto[ SIZEOF_EP0STO ],
 *					ep1sto[ SIZEOF_EP1STO ],
 *					ep2sto[ SIZEOF_EP2STO ];
 *
 * 	...
 * 	rkh_fwk_epool_register( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
 * 	rkh_fwk_epool_register( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
 * 	rkh_fwk_epool_register( ep2sto, SIZEOF_EP2STO, SIZEOF_EP2_BLOCK  );
 * 	...
 *	\endcode
 *
 * 	\param sstart	storage start. Pointer to memory from which memory blocks 
 * 					are allocated.
 * 	\param ssize:	storage size. Size of the memory pool storage in bytes.
 * 	\param esize	event size. This number determines the size of each memory 
 * 					block in the pool.
 */

void rkh_fwk_epool_register( void *sstart, rui32_t ssize, RKH_ES_T esize );


/**
 * 	\brief
 * 	Allocates an event from the previously created event pool. 
 *
 * 	\note
 * 	This function is internal to RKH and the user application should 
 * 	not call it. Instead, use #RKH_ALLOC_EVT() macro.
 *
 * 	\sa rkh_put_fifo(), rkh_put_lifo(), rkh_alloc_event(), 
 * 	rkh_set_static_event() and rkh_gc().
 *
 * 	\param esize	size of event [in bytes].
 * 	\param e		event signal.
 */

RKH_EVT_T *rkh_fwk_ae( RKH_ES_T esize, RKH_SIG_T e );


#if RKH_CFG_EN_DYNAMIC_EVENT == RKH_ENABLED

	/**
	 * 	\brief
	 *	This macro dynamically creates a new event of type \a et with its 
	 *	signal.
	 *
	 *	The basic policy is to allocate the event from the first pool that 
	 *	has a block size big enough to fit the requested event size. RKH 
	 *	can manage up to three event pools (e.g., small, medium, and large 
	 *	events, like shirt sizes). It returns a pointer to the event 
	 *	already cast to the event type (et*). Here is an example of dynamic 
	 *	event allocation with the macro RKH_ALLOC_EVT():
	 *
	 *	\code
	 *	MYEVT_T *mye = RKH_ALLOC_EVT( MYEVT_T, DATA );
	 *	mye->y = mye->x = 0;
	 *	...
	 *	\endcode
	 *
	 * 	\note
	 *	The assertions inside rkh_fwk_ae() function guarantee that the 
	 *	pointer is valid, so you don't need to check the pointer returned 
	 *	from rkh_fwk_ae(), unlike the value returned from malloc(), which 
	 *	you should check.
	 *
	 * 	\param et		type of event.
	 * 	\param e		event signal.
	 */

	#define RKH_ALLOC_EVT( et, e ) \
				(et*)rkh_fwk_ae((RKH_ES_T)sizeof(et),(RKH_SIG_T)(e))
#else
	#define RKH_ALLOC_EVT( et, e ) \
				(void)0
#endif


#if RKH_CFG_EN_DYNAMIC_EVENT == RKH_ENABLED

	/**
	 * 	\brief
	 * 	Recycle a dynamic event.
	 */

	void rkh_gc( RKH_EVT_T *e );

	/**
	 * 	\brief
	 * 	Recycle a dynamic event.
	 *
	 * 	This macro implements a simple garbage collector for the dynamic 
	 * 	events.	Only dynamic events are candidates for recycling. 
	 * 	(A dynamic event is one that is allocated from an event pool, which 
	 * 	is determined as non-zero	e->nref attribute.) Next, the function 
	 * 	decrements the reference counter of the event, and recycles the 
	 * 	event only if the counter drops to zero (meaning that no more 
	 * 	references are outstanding for this event). The dynamic event is 
	 * 	recycled by returning it to the pool from which	it was originally 
	 * 	allocated. The pool-of-origin information is stored in the 
	 * 	e->pool member.
	 * 	
	 * 	\note 
	 * 	This function is internal to RKH and the user application should 
	 * 	not call it. Instead, use #RKH_GC() macro.
	 * 	\note 
	 * 	The garbage collector must be explicitly invoked at all appropriate 
	 * 	contexts, when an event can become garbage (automatic garbage 
	 * 	collection).
	 * 	\note
	 * 	When setting RKH_CFG_EN_DYNAMIC_EVENT = 0 the garbage collector has 
	 * 	not effect, thus it's eliminated in compile-time.
	 *
	 * 	\param e		pointer to event to be potentially recycled.
	 */

	#define RKH_GC( e ) 			rkh_gc( e )
#else
	#define RKH_GC( e )				(void)0
#endif



#if RKH_CFG_EN_DYNAMIC_EVENT == RKH_ENABLED

	/**
	 * 	\brief
	 * 	Reserve the dynamic event to be recycled.
	 */

	void rkh_reserve( RKH_EVT_T *e );

	/**
	 * 	\brief
	 * 	Reserve the dynamic event to be recycled.
	 *
	 * 	This is the complement to RKH_GC(). It increments the reference 
	 * 	count of a dynamic event so the event can be saved by an SMA (AO). 
	 * 	Sometime later the SMA should manually release the event with 
	 * 	RKH_GC().
	 *
	 * 	\param e		pointer to event to be reserved.
	 */

	#define RKH_RSV( e ) 			rkh_reserve( e )
#else
	#define RKH_RSV( e )			(void)0
#endif

	
/**
 * 	\brief
 *	This macro initialize an event \a e with \a es signal and establishes 
 *	it as one static event.
 *
 *	\sa RKH_ROM_STATIC_EVENT() and RKH_STATIC_EVENT() macros.
 *
 *	Example:
 *	\code
 *	typedef struct
 *	{ 
 *		RKH_EVT_T e;
 *		rui8_t cmd;
 *	} RPC_REQ_T;
 *	
 *	typedef struct
 *	{
 *		RPC_REQ_T e;
 *		rkhui8_t txtsz; 
 *		EADR_T dst;
 *		EADR_T sc;
 *		char txt[ PDU_SIZEOF_UD_ASCII ];
 *	} REQ_SEND_SMS_T;
 *	
 *	...
 *	static REQ_SEND_SMS_T ev_txsm;
 *	
 *	...
 * 	some_function( ... )
 * 	{
 * 		RKH_SET_STATIC_EVENT( &ev_txsm, REQ_SEND_SMS );
 * 		ev_txsm.e.cmd = RPC_SEND_SMS;
 *		...
 *	}
 *	\endcode
 *
 * 	\param ev_obj	name of event structure (object).
 * 	\param ev_sig	event signal. The RKH takes this value for triggering 
 * 					a state transition.
 */

#define RKH_SET_STATIC_EVENT( ev_obj, ev_sig )						\
										MK_SET_EVT( ev_obj, ev_sig )

/**
 * 	\brief
 *	This macro declares and initializes the event structure \a ev_ob with 
 *	\a ev_sig signal number and establishes it as one static event. 
 *
 *	\sa RKH_SET_STATIC_EVENT() and RKH_ROM_STATIC_EVENT() macros.
 *
 *	Example:
 *	\code
 *	...
 *	static RKH_STATIC_EVENT( ev_udrej, UPG_DIC_REJ );
 *
 *	void
 *	dm_upgdic_rej( ... )
 *	{
 *		...
 *		rkh_put_fifo( drpc, &ev_udrej );
 *	}
 *	\endcode
 *
 * 	\param ev_obj	name of event structure (object).
 * 	\param ev_sig	event signal. The RKH takes this value for triggering 
 * 					a state transition.
 */

#define RKH_STATIC_EVENT( ev_obj, ev_sig )					\
										MK_EVT( ev_obj, ev_sig )

/**
 * 	\brief
 *	This macro declares and initializes the event structure \a ev_ob with 
 *	\a ev_sig signal number and establishes it as one static event. 
 *
 *	\sa RKH_SET_STATIC_EVENT() and RKH_STATIC_EVENT() macros.
 *
 *	\warning
 *	The created event object is explicitly placed at ROM.
 *
 *	Example:
 *	\code
 *	...
 *	static RKH_ROM_STATIC_EVENT( ev_timer, RPC_TIMER_RET );
 *
 *	void
 *	offhook( void )
 *	{
 *		...
 *		rkh_put_fifo( qphone, &ev_timer );
 *	}
 *	\endcode
 *
 * 	\param ev_obj	name of event structure (object).
 * 	\param ev_sig	event signal. The RKH takes this value for triggering 
 * 					a state transition.
 */

#define RKH_ROM_STATIC_EVENT( ev_obj, ev_sig )				\
										MK_ROM_EVT( ev_obj, ev_sig )

/**
 * 	\brief
 *	Initializes the attibutes of a RKH's event object structure.
 *	
 *	Example:
 *	\code
 *	typedef struct
 *	{
 *		RKH_EVT_T e;
 *		rui8_t cmd;
 *	} RPC_REQ_T;
 *
 *  ...
 *	static RKHROM RPC_REQ_T ev_ssreq =
 *	{
 *		RKH_INIT_STATIC_EVT( REQ_SEND_SMS_REQ ),
 *		RPC_SEND_SMS_REQ
 *	};
 *
 * 	...
 * 	void 
 * 	some_function(void) 
 * 	{ 
 * 		RKH_SMA_POST_FIFO(drpc, RKH_EVT_CAST(&ev_ssreq), 0);
 * 		...
 * 	}
 *	\endcode
 */

#define RKH_INIT_STATIC_EVT( ev_sig )						\
										MK_EVT_STRUCT( ev_sig )


/**
 * 	\brief
 * 	When dispatching an event to a SMA the dispatch hook function will be 
 * 	executed.
 *
 *	\note
 *	The dispatch hook will only get called if RKH_CFG_HOOK_DISPATCH_EN is 
 *	set to 1 within rkhcfg.h file. When this is set the application must 
 *	provide the hook function. 
 *
 * 	\param sma		pointer to previously created state machine application.
 *	\param e		pointer to arrived event.
 */

void rkh_hook_dispatch( RKH_SMA_T *sma, RKH_EVT_T *e );


/**
 * 	\brief
 * 	When the producer of an event directly posts the event to the event queue 
 * 	of the consumer SMA the rkh_hook_signal() will optionally called.
 * 	
 *	\note
 *	The signal hook will only get called if RKH_CFG_HOOK_SIGNAL_EN is set 
 *	to 1 within rkhcfg.h file. When this is set the application must provide 
 *	the hook function. 
 *
 *	\param e		pointer to arrived event.
 */

void rkh_hook_signal( RKH_EVT_T *e );


/**
 * 	\brief
 * 	If a timer expires the rkh_hook_timeout() function is called just before 
 * 	the assigned event is directly posted into the state machine application 
 * 	queue. 
 * 	
 *	\note
 *	The timeout hook will only get called if RKH_CFG_HOOK_TIMEOUT_EN is set 
 *	to 1 within rkhcfg.h file. When this is set the application must provide 
 *	the hook function. 
 *
 *	\param t		pointer to previously allocated timer structure. 
 *					A cast to RKH_TMR_T data type must be internally 
 *					implemented to get the appropiated timer control block.
 */

void rkh_hook_timeout( const void *t );


/**
 * 	\brief
 * 	This hook function is called just before the RKH takes over control of 
 * 	the application.
 *
 *	\note
 *	The start hook will only get called if RKH_CFG_HOOK_START_EN is set to 1 
 *	within rkhcfg.h file. When this is set the application must provide the 
 *	hook function. 
 */

void rkh_hook_start( void );


/**
 * 	\brief
 * 	This hook function is called just before the RKH returns to the 
 * 	underlying OS/RTOS. Usually, the rkh_hook_exit() is useful when executing
 * 	clean-up code upon SMA terminate or framework exit.
 *
 *	\note
 *	The exit hook will only get called if RKH_CFG_HOOK_EXIT_EN is set to 1 
 *	within rkhcfg.h file. When this is set the application must provide the 
 *	hook function. 
 */

void rkh_hook_exit( void );


/**
 * 	\brief
 * 	An idle hook function will only get executed (with interrupts LOCKED) 
 * 	when there are no SMAs of higher priority that are ready to run.
 *
 * 	This makes the idle hook function an ideal place to put the processor 
 * 	into a low power state - providing an automatic power saving whenever 
 * 	there is no processing to be performed.
 *
 * 	\note
 *	The rkh_hook_idle() callback is called with interrupts locked, because the
 *	determination of the idle condition might change by any interrupt posting
 *	an event. This function must internally unlock interrupts, ideally
 *	atomically with putting the CPU to the power-saving mode.
 *
 *	Example:
 *	
 *	\code
 *	void
 *	rkh_hook_idle( void ) 		// NOTE: entered with interrupts DISABLED
 *	{
 *		RKH_ENA_INTERRUPT();	// must at least enable interrupts
 *		...
 *	}
 *	\endcode
 */

void rkh_hook_idle( void );


/**
 * 	\brief
 * 	This function is called by rkh_tmr_tick(), which is assumed to be called 
 * 	from an ISR. rkh_hook_timetick() is called at the very beginning of 
 * 	rkh_tmr_tick(), to give priority to user or port-specific code when the 
 * 	tick interrupt occurs. 
 *
 *	Usually, this hook allows to the application to extend the functionality 
 *	of RKH, giving the port developer the opportunity to add code that will 
 *	be called by rkh_tmr_tick(). Frequently, the rkh_hook_timetick() is 
 *	called from the tick ISR and must not make any blocking calls and must 
 *	execute as quickly as possible.
 *
 *	\note
 *	The time tick hook will only get called if RKH_CFG_HOOK_TIMETICK_EN is 
 *	set to 1 within rkhcfg.h file. When this is set the application must 
 *	provide the hook function. 
 */

void rkh_hook_timetick( void );


/**
 * 	\brief
 * 	Inits a previously created state machine calling its initializing action.
 *
 * 	\param sma		pointer to previously created state machine application.
 */

void rkh_sma_init_hsm( RKH_SMA_T *sma );


/**
 * 	\brief
 *	Executes a state machine in a run-to-completation (RTC) model. 
 *
 *	In this model, before the system handles a new event it can store it 
 *	until the previous event has completed processing. This model is 
 *	called run to completion or RTC. Thus, the system processes events in 
 *	discrete, indivisible RTC steps. An RTC step is the period of time in 
 *	which events are accepted and acted upon. Processing an event always 
 *	completes within a single model step, including exiting the source 
 *	state, executing any associated actions, and entering the target state.
 * 	The RKH implementation preserves the transition sequence imposed by 
 * 	Harel's Statechart and UML. Specifically, the implemented transition 
 * 	sequence is as follows:
 *
 * 	- Execute exit actions of the source state.
 * 	- Execute the transition actions.
 * 	- Execute entry actions of the target state.
 *
 * 	Here now are the details of the main part of this algorithm 
 * 	(rkh_sma_dispatch()), in which an event is processed by the statechart. 
 * 	
 * 	\li	Determine the compound transition (CT) that will fire in response 
 * 		to the event: traverse the states in the active configuration from 
 * 		lowest states in the hierarchy upwards. A CT is enabled if its 
 * 		trigger is the dispatched event, and the guard evaluates to true. 
 * 		Once an enabled transition is found with a given source state stop 
 * 		traversing the states that are higher than this state in the 
 * 		hierarchy. 
 *  \li	Perform the CT that we found should fire. 
 * 		For each transition do:
 * 		-	Update histories of exited states.
 * 		- 	Perform the exit actions of the exited states according to the 
 * 			order states are exited, from low state to high state.
 * 		-	Perform the actions on the CT sequentially according to the 
 * 			order in which they are written on the transition, from the 
 * 			action closest to source state to the action closest to target 
 * 			state.
 * 		-	Perform the entry actions of the entered states according to 
 * 			the order states are entered, from high state to low state.
 * 		-	For lowest level states that were entered, which are not basic 
 * 			states, perform default transitions (recursively) until the 
 * 			statechart reaches basic states.
 * 		-	Update the active configuration.
 *  \li	Wrap up: once a stable configuration is reached, the reaction to the 
 * 		event is completed, control returns to the dispatcher and new events 
 * 		can be dispatched.
 *
 * 	\param sma		pointer to previously created state machine application.
 *	\param e		pointer to arrived event. It's used as state-machine's 
 *					input alphabet.
 *
 *	\return
 *	Result RKH_RCODE_T code.
 */

ruint rkh_sma_dispatch( RKH_SMA_T *sma, RKH_EVT_T *e );


/**
 * 	\brief
 * 	This macro retrieves the state ID of SMA.
 *
 * 	\param sma		pointer to previously created state machine application.
 *
 * 	\return
 * 	Id of current state.
 */

#define RKH_GET_CSTATE_ID( sma )									\
								((RKH_BASE_T*)((sma)->state))->id	


/**
 * 	\brief
 * 	Retrieves the address of an registered active object (SMA) according to 
 * 	its priority.
 *
 * 	\param _prio	registered active object (SMA) priority.
 * 	\return			pointer to previously registered active object (SMA).
 */

#define RKH_GET_SMA( _prio )			\
								rkh_sptbl[(rui8_t)(_prio)]


/**
 * 	\brief
 * 	Retrieves the priority number of an registered active object (SMA).
 *
 * 	\param _ao			pointer to previously registered active object (SMA).
 */

#define RKH_GET_PRIO( _ao )			\
								(rui8_t)((_ao)->romrkh->prio)


/**
 * 	\brief
 * 	Perform cast to pointer to RKH event structure (RKH_EVT_T*).
 */

#define RKH_EVT_CAST( _e )		((RKH_EVT_T*)(_e))


/**
 * 	\brief
 * 	Perform downcast of a reference of a base class to one of its derived 
 * 	classes.
 *
 * 	Example:
 * 	\code
 * 	void 
 * 	svr_start( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
 * 	{
 * 		START_EVT_T *e_start;
 * 		
 * 		e_start = RKH_ALLOC_EVT( START_EVT_T, START );
 * 		e_start->clino = RKH_CAST(REQ_EVT_T, pe)->clino;
 * 		RKH_SMA_POST_FIFO( RKH_GET_SMA( RKH_CAST(REQ_EVT_T, pe)->clino ), 
 *												RKH_EVT_CAST(e_start), sma );
 * 	}
 * 	\endcode
 *
 *	\sa
 *	\link RKH_EVT_T single inheritance in C \endlink, and 
 *	\link RKH_CREATE_BASIC_STATE another example \endlink.
 */

#define RKH_CAST( _type, _obj )		((_type*)(_obj))


/**
 * 	\brief
 * 	Erase the history of a state. It can be a shallow or deep history.
 *
 * 	\param h 		pointer to history pseudostate.
 */

void rkh_fwk_clear_history( RKHROM RKH_SHIST_T *h );



#if RKH_CFG_TRC_EN == RKH_ENABLED

	/**
	 * \brief 
	 * Open the tracing session.
	 */

	void rkh_trc_open( void );

	/**
	 * 	\brief 
	 *	Open the tracing session.
	 *
	 *	This function is application-specific and the user needs to 
	 *	define it. At a minimum, this function must initialize and/or 
	 *	configure the trace stream by calling rkh_trc_init() and 
	 *	RKH_TRC_SEND_CFG() respectively.
	 * 
	 * 	\note
	 * 	This function is internal to RKH and the user application 
	 * 	should not call it. Instead, use #RKH_TRC_OPEN() macro.
	 *
	 *	Example:
	 *
	 *	\code
	 *	#define BSP_SIZEOF_TS		32u
	 *	#define BSP_TS_RATE_HZ		CLOCK_PER_SEC
	 *
	 *	void 
	 *	rkh_trc_open( void )
	 *	{
	 *		rkh_trc_init();
	 *
	 *		FTBIN_OPEN();
	 *		TCP_TRACE_OPEN();
	 *		RKH_TRC_SEND_CFG( BSP_SIZEOF_TS, BSP_TS_RATE_HZ );
	 *
	 *		if(( idle_thread = CreateThread( NULL, 1024, 
	 *				&idle_thread_function, (void *)0, 
	 *				CREATE_SUSPENDED, NULL )) == (HANDLE)0 )
	 *			fprintf( stderr, "Cannot create the thread: [%d] 
	 *													line from %s "
	 *				"file\n", __LINE__, __FILE__ );
	 *	}
	 *	\endcode
	 *
	 * 	\sa \b rkhtrc.h file.
	 */

	#define RKH_TRC_OPEN() 		rkh_trc_open()
#else
	#define RKH_TRC_OPEN()		(void)0
#endif


#if RKH_CFG_TRC_EN == RKH_ENABLED
		
	/**
	 * 	\brief 
	 *	Close the tracing session.
	 */

	void rkh_trc_close( void );

	/**
	 * 	\brief 
	 *	Close the tracing session.
	 *
	 *	This function is application-specific and the user needs to 
	 *	define it. 
	 *
	 * 	\note
	 * 	This function is internal to RKH and the user application 
	 * 	should not call it. Instead, use #RKH_TRC_CLOSE() macro.
	 *
	 *	Example:
	 *
	 *	\code
	 *	void 
	 *	rkh_trc_close( void )
	 *	{
	 *		fclose( fdbg );
	 *	}
	 *	\endcode
	 *
	 * 	\sa \b rkhtrc.h file.
	 */

	#define RKH_TRC_CLOSE() 	rkh_trc_close()
#else
	#define RKH_TRC_CLOSE()		(void)0
#endif


#if RKH_CFG_TRC_EN == RKH_ENABLED

	/**
	 * 	\brief 
	 *	Platform-dependent macro flushing the trace stream.
	 */

	void rkh_trc_flush( void );

	/**
	 * 	\brief 
	 *	Platform-dependent macro flushing the trace stream.
	 *
	 *	This function is application-specific and the user needs to define 
	 *	it. When the RKH trace an event, all the information related to it 
	 *	has to be stored somewhere before it can be retrieved, in order to 
	 *	be analyzed. 
	 * 	This place is a trace stream. Frequently, events traced are stored 
	 * 	in the stream until it is flushed.
	 *
	 * 	\note
	 * 	This function is internal to RKH and the user application should 
	 * 	not call it. Instead, use #RKH_TRC_FLUSH() macro.
	 *
	 *	Example:
	 *	\code
	 * 	void 
	 * 	rkh_trc_flush( void )
	 * 	{
	 * 		rui8_t *blk;
	 * 		TRCQTY_T nbytes;
	 * 		RKH_SR_ALLOC();
	 *
	 * 		FOREVER
	 * 		{
	 * 			nbytes = (TRCQTY_T)1024;
	 * 			
	 * 			RKH_ENTER_CRITICAL_();
	 * 			blk = rkh_trc_get_block( &nbytes );
	 * 			RKH_EXIT_CRITICAL_();
	 *
	 * 			if((blk != (rui8_t *)0))
	 * 			{
	 * 				FTBIN_FLUSH( blk, nbytes );
	 * 				TCP_TRACE_SEND_BLOCK( blk, nbytes );
	 * 			}
	 * 			else
	 * 				break;
	 * 		}
	 * 	}
	 *	\endcode
	 *
	 * 	\sa \b rkhtrc.h file.
	 */

	#define RKH_TRC_FLUSH()		rkh_trc_flush()
#else
	#define RKH_TRC_FLUSH() 	(void)0
#endif


/**
 * 	\brief
 *	Retrieves a timestamp to be placed in a trace event.
 * 
 *	This function is application-specific and the user needs to define it. 
 *	The data returned is defined in compile-time by means of 
 *	RKH_SIZEOF_TSTAMP.
 *
 *	Example:
 *
 *	\code
 *	RKH_TS_T 
 *	rkh_trc_getts( void )
 *	{
 *		return ( RKH_TS_T )clock();
 *	}
 *	\endcode
 *
 * 	\returns
 * 	Timestamp (RKH_TS_T data type).
 *
 * 	\sa \b rkhtrc.h file.
 */

RKH_TS_T rkh_trc_getts( void );


#if RKH_CFG_TRC_EN == RKH_ENABLED

	/**
	 * 	\brief 
	 * 	Send the trace facility configuration to host application software 
	 * 	Trazer.
	 *
	 * 	Trazer is designed to work with all possible target CPU, which 
	 * 	requires a wide range of configurability. For example, for any 
	 * 	given target CPU, Trazer must "know" the size of object pointers, 
	 * 	event size, timestamp size and so on. This configurations could be 
	 * 	provided through "trazer.cfg" file in the host or invoking 
	 * 	RKH_TRC_SEND_CFG() macro from the application-specific 
	 * 	rkh_trc_open() function.
	 *
	 * 	\note
	 *	Frequently, this macro is called from the rkh_trc_open() function, 
	 *	which is provided by user application program, more specifically 
	 *	the board support package (BSP).
	 *
	 * 	\param ts_hz		clocks per second of trace timestamp.
	 *
	 * 	\sa RKH_TRC_OPEN() macro.
	 */

	#define RKH_TRC_SEND_CFG( ts_hz ) \
				RKH_TR_FWK_TCFG( ts_hz )
#else
	#define RKH_TRC_SEND_CFG( ts_hz ) \
				(void)0
#endif


#endif
