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
 *  \file       rkh.h
 *  \brief      RKH framwwork platform - independent interface.
 *
 *  \ingroup    apiSM
 *  \ingroup    apiAO
 *
 *  \addtogroup api
 *  @{
 *      \addtogroup apiSM State machines
 *      @{@}
 *      \addtogroup apiAO Active objects
 *      @{@}
 *      \addtogroup apiPort Port
 *      @{
 *          \addtogroup apiPortMisc Miscellaneous
 *          @{@}
 *          \addtogroup apiPortAO Active objects
 *          @{
 *          \brief Related to underlying OS/RTOS
 *          @}
 *      @}
 *      \addtogroup apiBSP BSP
 *      @{
 *          \addtogroup apiBSPHook Hooks
 *          @{
 *          \brief The hook functions allows to bsp/port developer to extend
 *                 the functionality of the framework.
 *
 *                 A RKH port cannot and should not define all the functions 
 *                 that it calls, because this would render the port too 
 *                 inflexible. The functions that RKH calls but doesn't 
 *                 actually implement are referred to as callback or hook 
 *                 functions. All these functions in RKH are easily 
 *                 indentifiable by the \b "_hook_" key word used in the 
 *                 function name, rkh_hook_dispatch(), rkh_hook_signal(), 
 *                 rkh_hook_timeout(), rkh_hook_start(), rkh_hook_exit(), and 
 *                 rkh_hook_idle(). 
 *                 Please, see RKH_CFG_HOOK_DISPATCH_EN, 
 *                 RKH_CFG_HOOK_SIGNAL_EN, RKH_CFG_HOOK_TIMEOUT_EN, 
 *                 RKH_CFG_HOOK_START_EN, and RKH_CFG_HOOK_EXIT_EN options 
 *                 from the \c rkhcfg.h.\n
 *          @}
 *          \addtogroup apiBSPTrc Trace
 *          @{
 *          \brief Related to manage a trace session with Trazer application.
*           See the \ref dbg section for more information. 
 *          @}
 *      @}
 *  @}
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/*
 *  (1) This header file must be included in all modules (*.c) that use RKH.
 */

/* --------------------------------- Module -------------------------------- */
#ifndef __RKH_H__
#define __RKH_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhitl.h"
#include "rkhrq.h"
#include "rkhmp.h"
#include "rkhtim.h"
#include "rkhassert.h"
#include "rkhtrc.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *	\brief
 *	This macro appears at the top of each C/C++ source file defining
 *	the version string for that file (module).
 *
 *  \param[in] __fname		file (module) name.
 *  \param[in] __version    file (module) version.
 */
#define RKH_MODULE_VERSION(__fname, __version) \
    static RKHROM char *const m_version = # __version;

/**
 *	\brief
 *	Get the module version.
 */
#define RKH_MODULE_GET_VERSION() \
    ((const char *)m_version);

/**
 *	\brief
 *	This macro appears at the top of each C/C++ source file defining
 *	the description string for that file (module).
 *
 *  \param[in] __fname		file (module) name.
 *  \param[in] __desc	    file (module) description.
 */
#define RKH_MODULE_DESC(__fname, __desc) \
    static RKHROM char *const m_desc = __desc;

/**
 *	\brief
 *	Get the module description.
 */
#define RKH_MODULE_GET_DESC() \
    ((const char *)m_desc)

#if RKH_CFGPORT_NATIVE_DYN_EVT_EN == RKH_ENABLED && \
    RKH_EN_DOXYGEN == RKH_DISABLED
    #define RKH_DYNE_TYPE           RKH_MP_T
    #define RKH_DYNE_INIT(mp, sstart, ssize, esize) \
        rkh_mp_init((mp),sstart,(rui16_t)ssize,(RKH_MPBS_T)esize)
    #define RKH_DYNE_GET_ESIZE(mp)  ((mp)->bsize)
    #define RKH_DYNE_GET(mp, e)     ((e) = (RKH_EVT_T *)rkh_mp_get((mp)))
    #define RKH_DYNE_PUT(mp, e)     (rkh_mp_put((mp), e))
    #define RKH_DYNE_GET_NUSED(mp)  ((mp)->nblocks - (mp)->nfree)
    #define RKH_DYNE_GET_NMIN(mp)   ((mp)->nmin)
    #define RKH_DYNE_GET_PSIZE(mp)  ((mp)->nblocks)
#else
    #define RKH_DYNE_TYPE           rui8_t
    #define RKH_DYNE_INIT(mp, sstart, ssize, esize)   (void)0
    #define RKH_DYNE_GET_ESIZE(mp)  (void)0
    #define RKH_DYNE_GET(mp, e)     (void)0
    #define RKH_DYNE_PUT(mp, e)     (void)0
    #define RKH_DYNE_GET_NBLOCK(mp) (void)0
    #define RKH_DYNE_GET_NUSED(mp)  (void)0
    #define RKH_DYNE_GET_NMIN(mp)   (void)0
    #define RKH_DYNE_GET_PSIZE(mp)  (void)0
#endif

/**
 *  \brief
 *  Convert a pointer to a base-class. 
 *
 *  In other words, upcasting allows us to treat a derived type as though 
 *  it were its base type.
 *
 *  \ingroup apiAO
 */
#define RKH_UPCAST(BaseType_, me_)          ((BaseType_ *)me_)

/**
 *  \brief
 *  Converts a base-class pointer to a derived-class pointer.
 *
 *  \ingroup apiAO
 */
#define RKH_DOWNCAST(DerivedType_, me_)     ((DerivedType_ *)me_)

/* -------------------------------- Constants ------------------------------ */
#ifndef NULL
#define NULL    (void *)0
#endif

/* ------------------------------- Data types ------------------------------ */
/**
 *  \brief
 *  Return codes from rkh_sm_dispatch() function.
 *
 *  \ingroup apiSM
 */
typedef enum RKH_RCODE_T
{
    /**
     *  The arrived event was succesfully processed and HSM
     *  resides in an allowed state.
     */
    RKH_EVT_PROC,

    /**
     *  The arrived event was't founded in the transition table.
     */
    RKH_EVT_NFOUND,

    /**
     *  The branch function returned a value not founded
     *  in the branch table.
     */
    RKH_CND_NFOUND,

    /**
     *  The transition was cancelled by guard function.
     */
    RKH_GRD_FALSE,

    /**
     *  Unknown state.
     */
    RKH_UNKN_STATE,

    /**
     *  The transition exceeded the allowed hierarchical level.
     */
    RKH_EX_HLEVEL,

    /**
     *  The transition exceeded the allowed number of segments
     *  within a compound transtion.
     */
    RKH_EX_TSEG,
    RKH_NUM_CODES
} RKH_RCODE_T;

/**
 *  \brief
 *  State machine properties.
 *
 *  \ingroup apiSM
 */
typedef enum
{
    /**
     *  Used as state machine property.
     *  This macro enables state nesting in a particular state machine.
     */
    HCAL,

    /**
     *  Used as state machine property.
     *  This macro disables state nesting in a particular state machine.
     *  When FLAT is used in RKH_SMA_CREATE() macro some important features of
     *  RKH are	not included: state nesting, composite state, history
     *  (shallow and deep) pseudostate, entry action, and exit action.
     */
    FLAT,

    /** Number of state machines properties */
    RKH_NUM_HPPTY
} RKH_HPPTY_T;

/* -------------------------- External variables --------------------------- */
/**
 *  \brief
 *  Priority arranged table of registered SMA.
 *
 *  Register a state machine application into the framework implies to store
 *  a pointer to the SMA in the priority table. A unique priority number must
 *  be assigned to each SMA from 0 to RKH_LOWEST_PRIO. The lower the number,
 *  the higher the priority.
 */
extern RKH_SMA_T *rkh_sptbl[RKH_CFG_FWK_MAX_SMA];

/**
 *  \brief
 *  rkh_maptbl[] is a table in ROM, used to equate an index from 0 to 7 to a
 *  bit mask.
 */
extern RKHROM rui8_t rkh_maptbl[8];

/**
 *  \brief
 *  rkh_unmaptbl[] is a table in ROM, used to return the bit position of the
 *  highest priority bit set - a number between 0 and 7.
 */
extern RKHROM rui8_t rkh_unmaptbl[256];

/**
 *  \brief
 *  String describing the RKH version.
 */
extern RKHROM char rkh_version[];

/**
 *  \brief
 *  String representing the name of undefined object name.
 */
extern RKHROM char noname[];

/**
 *  \brief
 *  Event pool list.
 */
#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
extern RKH_DYNE_TYPE rkh_eplist[RKH_CFG_FWK_MAX_EVT_POOL];
#endif

/**
 *  \brief
 *  Each condition connector can have one special branch with a guard
 *	labeled ELSE, which is taken if all the guards on the other
 *	branches are false.
 *
 *  A guard function takes the state machine pointer and the event
 *  pointer as arguments.
 *  These arguments are optional, thus they could be eliminated in
 *  compile-time by means of RKH_EN_GRD_EVT_ARG and RKH_EN_GRD_HSM_ARG
 *  preprocessor directives.
 */
#define ELSE        rkh_else

/**
 *  \brief
 *	This macro creates a composite state with a single region, including its 
 *	own initial pseudostate, history (shallow and deep type) pseudostate, as 
 *	well as its own final state.
 *
 *	The names of history pseudostate and final state are internally conformed 
 *	as "<nameOfCompositeState>Hist" and "<nameOfCompositeState>Final" 
 *	respectively. Thus, use these names as target vertex in a transition. 
 *
 *	Shallow history means that history applies to the current nesting context
 *	only – states nested more deeply are not affected by the presence of a
 *	history pseudostates in a higher context.
 *	Deep history applies downwards to all levels of nesting.
 *
 *  \param[in] name     state name. Represents a composite state structure.
 *  \param[in] en       pointer to state entry action. This argument is
 *                      optional, thus it could be declared as NULL.
 *                      The RKH implementation preserves the transition sequence
 *                      imposed by Harel's Statechart and UML.
 *  \param[in] ex	    pointer to state exit action. This argument is
 *                      optional, thus it could be declared as NULL.
 *                      The RKH implementation preserves the transition sequence
 *                      imposed by Harel's Statechart and UML.
 *  \param[in] parent	pointer to parent state.
 *  \param[in] defchild	pointer to default child state or pseudostate.
 *  \param[in] initialTrn
 *                      pointer to initial transition action of the composite 
 *                      state's region. This argument is optional, thus it 
 *                      could be declared as NULL. The RKH implementation 
 *                      preserves the transition sequence imposed by UML.
 *  \param[in] kindOfHistory 
 *                      Kind of history pseudostate. It could be defined
 *                      either shallow history (RKH_SHISTORY), deep history 
 *                      (RKH_DHISTORY) or without history (RKH_NO_HISTORY).
 *                      When it is defined as RKH_NO_HISTORY each of 
 *                      parameters related to history default transition are 
 *                      ignored.
 *  \param[in] hDftTrnGuard	
 *                      pointer to guard function. This argument is
 *					    optional, thus it could be declared as NULL.
 *  \param[in] hDftTrnAction
 *                      pointer to action function. This argument is
 *					    optional, thus it could be declared as NULL.
 *  \param[in] hDftTarget
 *                      pointer to target state. If a default history 
 *                      Transition is defined (the target parameter is not 
 *                      NULL) originating from the History Pseudostate, it 
 *                      will be taken. Otherwise, default State entry is 
 *                      applied. 
 *  \param[in] hRamMem
 *                      pointer to a RAM location which maintains the last 
 *                      visited state of this region. If composite state don't 
 *                      include the history pseudostate then this parameter 
 *                      should be passed as NULL.
 *                      Please, use RKH_CREATE_HISTORY_STORAGE() macro to 
 *                      create the history RAM location.
 *
 *	\sa
 *	RKH_SCMP_T structure definition for more information.
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_COMP_REGION_STATE(name, en, ex, parent, defchild, \
                                     initialTrn, \
                                     kindOfHistory, hDftTrnGuard, \
                                     hDftTrnAction, hDftTarget, hRamMem) \
                                                                         \
    MKFINAL_INCOMP(name); \
    MKHIST_INCOMP(name, kindOfHistory, hDftTrnGuard, hDftTrnAction, \
                  hDftTarget, hRamMem); \
                                        \
    extern RKHROM RKH_TR_T name##_trtbl[]; \
    RKHROM RKH_SCMP_T name = \
    { \
        {MKBASE(RKH_COMPOSITE, name), MKST(en, ex, parent)}, \
        MKCOMP(name, defchild, initialTrn, &name##Hist) \
    }

/**
 *  \brief
 *	This macro creates a composite state.
 *
 *  \param[in] name     state name. Represents a composite state structure.
 *  \param[in] en       pointer to state entry action. This argument is
 *                      optional, thus it could be declared as NULL.
 *                      The RKH implementation preserves the transition sequence
 *                      imposed by Harel's Statechart and UML.
 *  \param[in] ex	    pointer to state exit action. This argument is
 *                      optional, thus it could be declared as NULL.
 *                      The RKH implementation preserves the transition sequence
 *                      imposed by Harel's Statechart and UML.
 *  \param[in] parent	pointer to parent state.
 *  \param[in] defchild	pointer to default child state or pseudostate.
 * 	\param[in] history	pointer history pseudostate. This argument is 
 *                      optional, thus it could be declared as NULL.
 *
 *	\sa
 *	RKH_SCMP_T structure definition for more information.
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_COMP_STATE(name, en, ex, parent, defchild, history) \
                                                                       \
    extern RKHROM RKH_TR_T name##_trtbl[]; \
    RKHROM RKH_SCMP_T name = \
    { \
        {MKBASE(RKH_COMPOSITE, name), MKST(en, ex, parent)}, \
        MKCOMP(name, defchild, NULL, history) \
    }

/**
 *  \brief
 *  This macro creates a final state.
 *
 *  \param[in] name     state name. Represents a composite state structure.
 *  \param[in] parent	pointer to parent state.
 *
 *	\sa
 *	RKH_FINAL_T structure definition for more information.
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_FINAL_STATE(name, parent) \
                                             \
    static RKHROM RKH_TR_T name##_trtbl[] = \
        RKH_TRREG(RKH_ANY, NULL, NULL, NULL); \
    RKHROM RKH_FINAL_T name = \
    { \
        {MKBASE(RKH_FINAL, name), MKST(NULL, NULL, parent)}, \
        MKFINAL(name) \
    }

/**
 *  \brief
 *	This macro creates a basic state.
 *
 *  \param[in] name	state name. Represents a basic state structure.
 *  \param[in] en	pointer to state entry action. This argument is
 *					optional, thus it could be declared as NULL.
 *					The RKH implementation preserves the transition sequence
 *					imposed by Harel's Statechart and UML.
 *  \param[in] ex	pointer to state exit action. This argument is
 *					optional, thus it could be declared as NULL.
 *					The RKH implementation preserves the transition sequence
 *					imposed by Harel's Statechart and UML.
 *  \param[in] parent	pointer to parent state.
 *  \param[in] prepro	pointer to input preprocessor function. This function
 *                  could be called "Moore" action.
 *                  This argument is optional, thus it could be declared
 *                  as NULL.
 *					Aditionally, by means of single inheritance in C it
 *					could be used as state's abstract data.
 *					Moreover, implementing the single inheritance in C
 *					is very simply by literally embedding the base type,
 *					RKH_PPRO_T in this case, as the first member of the
 *					derived structure. See \a prepro member of RKH_SBSC_T
 *					structure for more information. 
 *					\usage
 *                  \code
 *					static RKH_SIG_T
 *					preprocessor( RKH_EVT_T *pe )
 *					{
 *						...
 *					}
 *
 *					typedef struct
 *					{
 *						RKH_PPRO_T prepro;  // extend the RKH_PPRO_T class
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
 *
 *	\sa
 *	RKH_SBSC_T structure definition for more information.
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_BASIC_STATE(name, en, ex, parent, prepro) \
                                                             \
    extern RKHROM RKH_TR_T name##_trtbl[]; \
                                             \
    RKHROM RKH_SBSC_T name = \
    { \
        {MKBASE(RKH_BASIC, name), MKST(en,ex,parent)}, \
        MKBASIC(name,prepro)  \
    }

/**
 *  \brief
 *	This macro creates a conditional pseudostate (a.k.a. junction).
 *
 *  The conditional pseudostates are semantic-free vertices that are used to
 *  chain together multiple transitions. They are used to construct compound
 *  transition paths between states. For example, a junction can be used to
 *  converge multiple incoming transitions into a single outgoing transition
 *  representing a shared transition path (this is known as a merge).
 *  Conversely, they can be used to split an incoming transition into multiple
 *  outgoing transition segments with different guard conditions. This
 *  realizes a static conditional branch. (In the latter case, outgoing
 *  transitions whose guard conditions evaluate to false are disabled. A
 *  predefined guard denoted "ELSE" may be defined for at most one outgoing
 *  transition. This transition is enabled if all the guards labeling the
 *  other transitions are false.) Static conditional branches are distinct
 *  from dynamic conditional branches that are realized by choice vertices.
 *
 *  \param[in] name     pseudostate name. Represents a conditional pseudostate
 *                      structure.
 *
 *	\sa
 *	RKH_SCOND_T structure definition for more information.
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_COND_STATE(name) \
                                    \
    extern RKHROM RKH_TR_T name##_trtbl[]; \
                                             \
    RKHROM RKH_SCOND_T name = \
    { \
        MKBASE(RKH_CONDITIONAL, name), \
        name##_trtbl \
    }

/**
 *  \brief
 *	This macro creates a choice pseudostate.
 *
 *  Choice pseudostate which, when reached, result in the dynamic evaluation
 *  of the guards of its outgoing transitions. This realizes a dynamic
 *  conditional branch. It allows splitting of transitions into multiple
 *  outgoing paths such that the decision on which path to take may be a
 *  function of the results of prior actions performed in the same
 *  run-to-completion step. If more than one of the guards evaluates to true,
 *  an arbitrary one is selected. If none of the guards evaluates to true,
 *  then the model is considered ill-formed. To avoid this, it is recommended
 *  to define one outgoing transition with the predefined "ELSE" guard for
 *  every choice pseudostate.
 *	Also, branches cannot contain triggers, but in addition to a guard they
 *	may contain actions. A branch can enter another choice connector, thus
 *	providing for the nesting of branches.
 *
 *  \param[in] name		pseudostate name. Represents a choice pseudostate
 *                      structure.
 *
 *	\sa
 *	RKH_SCHOICE_T structure definition for more information.
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_CHOICE_STATE(name) \
                                      \
    extern RKHROM RKH_TR_T name##_trtbl[]; \
                                           \
    RKHROM RKH_SCHOICE_T name = \
    { \
        MKBASE(RKH_CHOICE, name), \
        name##_trtbl \
    }

/**
 * 	\deprecated 
 * 	This macro creates a deep history pseudostate. Instead use: 
 *	RKH_CREATE_COMP_REGION_STATE() macro.
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
 * 	\param[in] name		pseudostate name. Represents a deep history 
 *                      pseudostate structure.
 * 	\param[in] parent	pointer to parent state.
 *  \param[in] dftTrnGuard	
 *                      pointer to guard function. This argument is
 *			   	        optional, thus it could be declared as NULL.
 *  \param[in] dftTrnAction
 *                      pointer to action function. This argument is
 *			   	        optional, thus it could be declared as NULL.
 *  \param[in] dftTarget
 *                      pointer to target state. If a default history 
 *                      Transition is defined (the target parameter is not 
 *                      NULL) originating from the History Pseudostate, it 
 *                      will be taken. Otherwise, default State entry is 
 *                      applied. 
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_DEEP_HISTORY_STATE(name, parent, dftTrnGuard, \
                                      dftTrnAction, dftTarget) \
                                                               \
    static RKHROM RKH_ST_T *ram##name; \
    MKHISTORY(name, parent, RKH_DHISTORY, dftTrnGuard, dftTrnAction, \
              dftTarget, &ram##name)

/**
 * 	\deprecated 
 *	This macro creates a shallow history pseudostate. Instead use: 
 *	RKH_CREATE_COMP_REGION_STATE() macro.
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
 * 	\param[in] name     pseudostate name. Represents a shallow history 
 *                      pseudostate structure.
 * 	\param[in] parent   pointer to parent state.
 *  \param[in] dftTrnGuard	
 *                      pointer to guard function. This argument is
 *					    optional, thus it could be declared as NULL.
 *  \param[in] dftTrnAction
 *                      pointer to action function. This argument is
 *					    optional, thus it could be declared as NULL.
 *  \param[in] dftTarget
 *                      pointer to target state. If a default history 
 *                      Transition is defined (the target parameter is not 
 *                      NULL) originating from the History Pseudostate, it 
 *                      will be taken. Otherwise, default State entry is 
 *                      applied. 
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_SHALLOW_HISTORY_STATE(name, parent, dftTrnGuard, \
                                         dftTrnAction, dftTarget) \
                                                                  \
    static RKHROM RKH_ST_T *ram##name; \
    MKHISTORY(name, parent, RKH_SHISTORY, dftTrnGuard, dftTrnAction, \
              dftTarget, &ram##name)

/**
 *  \brief
 *	This macro creates a submachine state.
 *
 *  A submachine state is a kind of a state that actually refers to
 *  another defined state machine.
 *  A submachine state is logically equivalent to the insertion of the
 *  referenced state machine as a composite state in the place of
 *  the submachine state. Consequently, every entrance to a submachine
 *  state is equivalent to the corresponding entrance to the inserted
 *  (referenced) composite state. In particular, it can be entered
 *  thruough its initial pseudostate (as any other composite state), or
 *  through one of its entry points.
 *
 *  Similary, every exit from a submachine state is equivalent to the
 *  corresponding exit from the inserted composite state. It can be exited
 *  through one of its exit points. When it is exited through its exit point
 *  the effect of the transition targeting the exit point is executed first,
 *  followed by the exit behavior of the composite state.
 *
 *  The purpose od defining submachine states is to decompose and localize
 *  repetitive parts because the same state machine can be referenced from
 *  more than one submachine state.
 *
 *  \param[in] name     submachine state name. Represents a submachine state
 *                      structure.
 *  \param[in] en		pointer to state entry action. This argument is
 *                      optional, thus it could be declared as NULL.
 *                      The RKH implementation preserves the transition sequence
 *                      imposed by Harel's Statechart and UML.
 *  \param[in] ex       pointer to state exit action. This argument is
 *                      optional, thus it could be declared as NULL.
 *                      The RKH implementation preserves the transition sequence
 *                      imposed by Harel's Statechart and UML.
 *  \param[in] parent	pointer to parent state.
 *  \param[in] sbm		pointer to referenced submachine state machine.
 *
 *	\sa
 *	RKH_SSBM_T structure definition for more information.
 *
 *	\code
 *	RKH_CREATE_SUBMACHINE_STATE(    adquire,		// state name
 *									start_adquire,  // entry action
 *									stop_adquire,   // exit action
 *									&processing,    // parent state
 *									&herror );		// referenced submachine
 *	\endcode
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_SUBMACHINE_STATE(name, en, ex, parent, sbm) \
                                                               \
    extern RKHROM RKH_EXPCN_T name##_exptbl[]; \
    extern RKHROM RKH_TR_T name##_trtbl[]; \
                                             \
    RKHROM RKH_SSBM_T name = \
    { \
        {MKBASE(RKH_SUBMACHINE, name), MKST(en,ex,parent)}, \
        MKSBM(name,sbm) \
    }

/**
 *  \brief
 *	This macro creates a exit point connection point reference table.
 *
 *  \param[in] name		submachine state name
 *
 *	\note
 *	This macro is not terminated with the semicolon.
 *
 *	\usage
 *	This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_EX_CNNPNT_TABLE( S2 )
 *		RKH_EX_CNNPNT( EX1S2, &EXPNT1, NULL, &S1 ),
 *		RKH_EX_CNNPNT( EX2S2, &EXPNT2, NULL, &S3 ),
 *	RKH_END_EX_CNNPNT_TABLE
 *	\endcode
 *  Each exit point connection reference table always begins with the macro
 *  RKH_CREATE_EX_CNNPNT_TABLE() and ends with the macro
 *  RKH_END_EX_CNNPNT_TABLE().
 *	As noted above, sandwiched between these macros are the exit point
 *	macros, RKH_EX_CNNPNT().
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_EX_CNNPNT_TABLE(name) \
    RKHROM RKH_EXPCN_T name##_exptbl[]= \
    {

/**
 *  \brief
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
 *  \param[in] name     exit point connection point reference name.
 *  \param[in] expnt	referenced exit point.
 *  \param[in] act		pointer to transition action function. This argument is
 *					    optional, thus it could be declared as NULL.
 *  \param[in] ts		pointer to target state.
 *
 *	\sa
 *	RKH_EXPCN_T structure definition for more information.
 *
 *  \usage
 *  \code
 *	// --- exit point pseudostates of SB submachine ---
 *	RKH_CREATE_REF_EXPNT(   EXPNT1,
 *							0,		// index of exit point connection table
 *							&SB );
 *	RKH_CREATE_REF_EXPNT(   EXPNT2,
 *							1,      // index of exit point connection table
 *							&SB );
 *							...
 *	// --- exit point connection references of S12 submachine state ---
 *	RKH_CREATE_EX_CNNPNT_TABLE( S12 )
 *		RKH_EX_CNNPNT( EX1S12, &EXPNT1, ... ), // table index = 0 (EXPNT1)
 *		RKH_EX_CNNPNT( EX2S12, &EXPNT2, ... ), // table index = 1 (EXPNT2)
 *	RKH_END_EX_CNNPNT_TABLE
 *	\endcode
 */
#define RKH_EX_CNNPNT(name, expnt, act, ts) \
    {(RKH_TRN_ACT_T)act, (RKHROM struct RKH_ST_T *)ts}

/**
 *  \brief
 *	This macro is used to terminate a exit point connection reference table.
 *
 *	\note
 *	This macro is not terminated with the semicolon.
 *
 *	\usage
 *	This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_EX_CNNPNT_TABLE( S2 )
 *		RKH_EX_CNNPNT( EX1S2, &EXPNT1, NULL, &S1 ),
 *		RKH_EX_CNNPNT( EX2S2, &EXPNT2, NULL, &S3 ),
 *	RKH_END_EX_CNNPNT_TABLE
 *	\endcode
 *  Each exit point table always begins with the macro
 *  RKH_CREATE_EX_CNNPNT_TABLE() and ends with the macro
 *  RKH_END_EX_CNNPNT_TABLE().
 *	As noted above, sandwiched between these macros are the exit point
 *	macros, RKH_EX_CNNPNT().
 */
#define RKH_END_EX_CNNPNT_TABLE     };

/**
 *  \brief
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
 *  \param[in] name		entry point connection point reference name.
 *  \param[in] enpnt	referenced entry point.
 *  \param[in] subm		pointer to submachine state.
 *
 *	\sa
 *	RKH_SENP_T structure definition for more information.
 */
#define RKH_EN_CNNPNT(name, enpnt, subm) \
                                         \
    RKHROM RKH_SENP_T name = \
    { \
        MKBASE(RKH_ENPOINT, name), \
        MKENP(enpnt,subm) \
    }

/**
 *  \brief
 *	This macro creates a submachine state machine, which is to be
 *	inserted in place of the (submachine) state.
 *
 *  \param[in] name		submachine name. Represents a submachine structure.
 *  \param[in] defchild	pointer to default child state.
 *  \param[in] iact		pointer to initialization action (optional). The
 *                      function prototype is defined as RKH_INIT_ACT_T. This
 *                      argument is optional, thus it could be declared as
 *                      NULL.
 *
 *	\sa
 *	RKH_RSM_T structure definition for more information.
 *
 *  \code
 *  RKH_CREATE_REF_SUBMACHINE(  adquire,
 *                              &wait,
 *                              init_adquire );
 *  \endcode
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_REF_SUBMACHINE(name, defchild, iact) \
                                                        \
    static RKHROM RKH_ST_T * rdyp_##name; \
                                            \
    RKHROM RKH_RSM_T name = \
    { \
        MKBASE(RKH_REF_SUBMACHINE, name), \
        MKMCH(defchild,iact,name) \
    }

/**
 *  \brief
 *	This macro creates an exit point.
 *
 *  An exit pseudostate is used to join an internal transition terminating on
 *  that exit point to an external transition emanating from that exit point.
 *  The main purpose of such entry and exit points is to execute the state
 *  entry and exit actions respectively in between the actions that are
 *  associated with the joined transitions.
 *
 *  \param[in] name		entry point name.
 *  \param[in] ix		index of exit point connection table. Note that each 
 *                      row number matches with the index number of the exit 
 *                      point pseudostate that it represent.
 *  \param[in] subm		pointer to submachine state machine.
 *
 *  \code
 *  RKH_CREATE_REF_EXPNT(handled,
 *                       0,
 *                       &handle_error);
 *  \endcode
 *
 *	\sa
 *	RKH_SEXP_T structure definition for more information.
 *
 *  \usage
 *	\code
 *	// --- exit point pseudostates of SB submachine ---
 *	RKH_CREATE_REF_EXPNT(   EXPNT1,
 *							0,		// index of exit point connection table
 *							&SB );
 *	RKH_CREATE_REF_EXPNT(   EXPNT2,
 *							1,      // index of exit point connection table
 *							&SB );
 *							...
 *	// --- exit point connection references of S12 submachine state ---
 *	RKH_CREATE_EX_CNNPNT_TABLE( S12 )
 *		RKH_EX_CNNPNT( EX1S12, &EXPNT1, ... ), // table index = 0 (EXPNT1)
 *		RKH_EX_CNNPNT( EX2S12, &EXPNT2, ... ), // table index = 1 (EXPNT2)
 *	RKH_END_EX_CNNPNT_TABLE
 *	\endcode
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_REF_EXPNT(name, ix, subm) \
                                             \
    RKHROM RKH_SEXP_T name = \
    { \
        MKBASE(RKH_EXPOINT, name), \
        ix, subm \
    }

/**
 *  \brief
 *	This macro creates a entry point.
 *
 *  An entry pseudostate is used to join an external transition terminating
 *  on that entry point to an internal transition emanating from that entry
 *  point.
 *  The main purpose of such entry and exit points is to execute the state
 *  entry and exit actions respectively in between the actions that are
 *  associated with the joined transitions.
 *
 *  \param[in] name     entry point name.
 *  \param[in] act		pointer to transition action function. This argument is
 *					    optional, thus it could be declared as NULL.
 *  \param[in] ts		pointer to target state.
 *  \param[in] subm		pointer to submachine state machine.
 *
 *	\sa
 *	RKH_ENPCN_T structure definition for more information.
 *
 *  \code
 *  RKH_CREATE_REF_ENPNT(   show,
 *                          2,
 *                          &S2,
 *                          &handle_error );
 *  \endcode
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_REF_ENPNT(name, act, ts, subm) \
                                                  \
    RKHROM RKH_ENPCN_T name = \
    { \
        (RKH_TRN_ACT_T)act, (RKHROM struct RKH_ST_T *)ts \
    }

/**
 *  \brief
 *	This macro creates a state transition table. 
 *  
 *  \param[in] name		state name.
 *
 *	\note
 *	This macro is not terminated with the semicolon.
 *  
 *  \usage
 *  This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_TRANS_TABLE( state_name )		// transition table begin
 *		RKH_TRxx( ... )							// transition
 *		RKH_TRxx( ... )							// transition
 *		...
 *	RKH_END_TRANS_TABLE							// transition table end
 *	\endcode
 *  Each transition table always begins with the macro RKH_CREATE_TRANS_TABLE()
 *  and ends with the macro RKH_END_TRANS_TABLE().
 *	As noted above, sandwiched between these macros are the transitions macros
 *	that actually represent behavior of state.
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_TRANS_TABLE(name) \
                                     \
    RKHROM RKH_TR_T name##_trtbl[]= \
    {

/**
 *  \brief
 *	This macro defines a regular state transition.
 *
 *	The general syntax of an expression labelling a transition in a
 *	statechart is \e "i[c]/a" where \e i is the input that triggers the
 *	transition, \e c is a condition that guards the transition from being
 *	taken unless it is true when \e i occurs, and \e a is an action that
 *	is carried out if and when the transition is taken. All of these parts
 *	are optional.
 *
 *  \param[in] evt_	    triggering event.
 *  \param[in] guard_	pointer to guard function. This argument is
 *					    optional, thus it could be declared as NULL.
 *  \param[in] effect_	pointer to action function. This argument is
 *					    optional, thus it could be declared as NULL.
 *  \param[in] target_	pointer to target state.
 *
 *	\sa
 *	RKH_TR_T structure definition for more information.
 *
 *  \usage
 *	\code
 *	RKH_TRREG(  TOUT0,              // triggering event
 *				is_full,            // guard function
 *				drop_frame,         // action function
 *				&WAIT_SYNC )		// next state
 *	\endcode
 */
#define RKH_TRREG(evt_, guard_, effect_, target_) \
            MKTRN(evt_, guard_, effect_, target_)

/**
 *  \brief
 *	This macro defines an internal state transition.
 *	Internal transitions are simple reactions to events that never lead
 *	to change of state and consequently never cause execution of exit
 *	actions, entry actions, or initial transitions.
 *
 *  \param[in] e    triggering event.
 *  \param[in] g	pointer to guard function.
 *  \param[in] a	pointer to action function.
 *
 *	\sa
 *	RKH_TR_T structure definition for more information.
 *
 *  \usage
 *	\code
 *	RKH_TRINT(  RCV_DATA,           // triggering event
 *				is_sync,            // guard function
 *				store_data )        // action function
 *	\endcode
 */
#define RKH_TRINT(e, g, a)    {e, (RKH_GUARD_T)g, (RKH_TRN_ACT_T)a, NULL}

/**
 *  \brief
 *	This macro defines a completion transition.
 *
 *  A special kind of transition is a completion transition, which has an 
 *  implicit trigger. The event that enables this trigger is called a 
 *  completion event and it signifies that all behaviors associated with the 
 *  source state of the completion transition have completed execution. 
 *  In case of simple states, a completion event is generated when the 
 *  associated entry behavior have completed executing. If no such behaviors 
 *  are defined, the completion event is generated upon entry into the state. 
 *  For composite state, a completion event is generated under the following 
 *  circumstances:
 *  - All internal activities (e.g., entry behavior) have completed execution, 
 *  and
 *  - its region have reached a finalState.
 *
 *  \param[in] guard_	pointer to guard function. This argument is
 *					    optional, thus it could be declared as NULL.
 *  \param[in] effect_	pointer to effect function. This argument is
 *					    optional, thus it could be declared as NULL.
 *  \param[in] target_	pointer to target vertex (state or pseudostate).
 *
 *	\sa
 *	RKH_TR_T structure definition for more information.
 *
 *  \usage
 *	\code
 *	RKH_TRCOMPLETION(isFull,        // guard function
 *				     dropFrame,     // effect function
 *				     &waitSync),    // next state
 *	\endcode
 */
#define RKH_TRCOMPLETION(guard_, effect_, target_) \
    {RKH_COMPLETION_EVENT, \
     (RKH_GUARD_T)guard_, (RKH_TRN_ACT_T)effect_, target_}

/**
 *  \brief
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
 *  Each transition table always begins with the macro RKH_CREATE_TRANS_TABLE()
 *  and ends with the macro RKH_END_TRANS_TABLE().
 *	As noted above, sandwiched between these macros are the transitions macros
 *	that actually represent behavior of state.
 *
 *	\note
 *	This macro is not terminated with the semicolon.
 */
#define RKH_END_TRANS_TABLE     {RKH_ANY, NULL, NULL, NULL}};

/**
 *	This macro creates a branch table. 
 *
 *  \param[in] name		conditional pseudostate name.
 *
 *	\sa
 *	This macro is not terminated with the semicolon.
 *	Use rkh_else() when if all the guards on the other branches are false.
 *
 *  \usage
 *	This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_BRANCH_TABLE( C2 )
 *		RKH_BRANCH( is_power_ok,    enable_process,	&power		),
 *		RKH_BRANCH( is_switch_off,  turnoff,		&wait		),
 *		RKH_BRANCH( ELSE,           abort,			&aborted	),
 *	RKH_END_BRANCH_TABLE
 *	\endcode
 *  Each branch table always begins with the macro RKH_CREATE_BRANCH_TABLE()
 *  and ends with the macro RKH_END_BRANCH_TABLE().
 *  In RKH branches are defined by the macro RKH_BRANCH().
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_BRANCH_TABLE(name) \
                                      \
    RKH_CREATE_TRANS_TABLE(name)

/**
 *  \brief
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
 *  \param[in] guard_	branch guard function. Branches are labeled with guards
 *                      that determine which one is to be actually taken. Use
 *                      ELSE macro when if all the guards on the other branches
 *                      are false.
 *  \param[in] effect_	pointer to transition action. This argument is 
 *                      optional, thus it could be declared as NULL.
 *  \param[in] target_	pointer to target state.
 *
 *	\sa
 *	RKH_TR_T structure definition for more information.
 *
 *  \usage
 *	\code
 *	RKH_CREATE_BRANCH_TABLE( C2 )
 *		RKH_BRANCH( is_power_ok,    enable_process,	&power		),
 *		RKH_BRANCH( is_switch_off,  turnoff,		&wait		),
 *		RKH_BRANCH( ELSE,           abort,			&aborted	),
 *	RKH_END_BRANCH_TABLE
 *	\endcode
 */
#define RKH_BRANCH(guard_, effect_, target_) \
            MKTRN(0, guard_, effect_, target_)

/**
 *  \brief
 *  Define a RAM storage to mantain the last visited state of a composite 
 *  state (history pseudostate).
 *
 *  Frequently, it's used before of RKH_CREATE_COMP_REGION_STATE() macro to 
 *  define the dynamic storage of a history pseudostate.
 *
 *  \param[in] compStateName    pointer to the composite state that contains 
 *                              this history pseudostate.
 *
 *  \ingroup apiSM
 */
#define RKH_CREATE_HISTORY_STORAGE(compStateName) \
    static RKHROM RKH_ST_T *ramHist_##compStateName

/**
 *  \brief
 *  Return the history storage address of a composite state. 
 *
 *  Frequently, it's used in the hRamMem parameter of 
 *  RKH_CREATE_COMP_REGION_STATE() macro to define the dynamic storage of a 
 *  history pseudostate.
 *
 *  \param[in] compStateName    pointer to the composite state that contains 
 *                              this history pseudostate.
 */
#define RKH_GET_HISTORY_STORAGE(compStateName) \
    &ramHist_##compStateName

/*
 *  This macro is internal to RKH and the user application should
 *  not call it.
 */
#define RKH_EBTBL               {RKH_ANY, NULL, NULL, NULL}

/**
 *  \brief
 *	This macro is used to terminate a state transition table.
 *	This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_BRANCH_TABLE( C2 )
 *		RKH_BRANCH( is_power_ok,    enable_process,	&power		),
 *		RKH_BRANCH( is_switch_off,  turnoff,		&wait		),
 *		RKH_BRANCH( ELSE,           abort,			&aborted	),
 *	RKH_END_BRANCH_TABLE
 *	\endcode
 *
 *  Each branch table always begins with the macro RKH_CREATE_BRANCH_TABLE()
 *  and ends with the macro RKH_END_BRANCH_TABLE().
 *
 *	\sa
 *	This macro is not terminated with the semicolon.
 */
#define RKH_END_BRANCH_TABLE    RKH_EBTBL};

/**
 *  \brief
 *	This macro indicates the root state of a state machine.
 */
#define RKH_ROOT                RKH_NULL

/**
 *  \brief
 *  This macro declares a opaque pointer to previously created state machine
 *  application (SMA aka active object) to be used as a global object.
 *
 *  This global pointer represent the active object in the application.
 *  These pointers are "opaque" because they cannot access the whole active 
 *  object structure, but only the part inherited from the RKH_SMA_T structure.
 *  The power of an "opaque" pointer is that it allows to completely hide the 
 *  definition of the active object structure and make it inaccessible to the 
 *  rest of the application, thus strengthening the encapsulation concept.
 *
 *  \param[in] me_  pointer to previously created state machine application.
 *
 *	\note
 *  Generally, this macro is used in the SMA's header file.
 *
 *  \sa
 *  RKH_SMA_CREATE().
 *
 *  \usage
 *  \code
 *  //	my.h: state-machine application's header file
 *
 *  RKH_SMA_DCLR(my);
 *  \endcode
 */
#define RKH_SMA_DCLR(me_) \
            RKH_DCLR_PTR_TYPE(RKH_SMA_T, me_)

/**
 *  \brief
 *  This macro declares a typed pointer to previously created state machine
 *  application (SMA aka active object) to be used as a global and public 
 *  object.
 *
 *  \param[in] type_
 *                  Data type of the state machine application. Could be 
 *                  derived from RKH_SMA_T.
 *                  The pointer could be used to publish the internals of the 
 *                  class of the state machine. 
 *  \param[in] me_	pointer to previously created state machine application.
 *
 *	\note
 *  Generally, this macro is used in the SMA's header file.
 *
 *  \sa
 *  RKH_SMA_CREATE(), RKH_SMA_DCLR().
 *
 *  \usage
 *  \code
 *  //	my.h: state-machine application's header file
 *
 *  RKH_SMA_DCLR_TYPE(Blinky, blinky);
 *  \endcode
 */
#define RKH_SMA_DCLR_TYPE(type_, me_) \
            RKH_DCLR_PTR_TYPE(type_, me_)

/**
 *  \brief
 *  This macro declares an opaque pointer to previously created state machine
 *  to be used as a global object.
 *
 *  This global pointer represent the state machine in the application.
 *  The state machine pointers are "opaque" because they cannot access the
 *  whole state machine structure, but only the part inherited from the
 *  RKH_SM_T structure. The power of an "opaque" pointer is that it allows
 *  to completely hide the definition of the state machine structure and make
 *  it inaccessible to the rest of the application.
 *
 *  \param[in] me_	Pointer to previously created state machine.
 *
 *	\note
 *  Generally, this macro is used in the SMA's header file.
 *
 *  \sa
 *  RKH_SMA_CREATE(), RKH_SM_CREATE().
 *
 *  \usage
 *  \code
 *  // ColorRegion.h: state machine's header file
 *
 *  RKH_SM_DCLR_TYPE(ColorRegion, color);
 *  \endcode
 */
#define RKH_SM_DCLR(me_) \
            RKH_DCLR_PTR_TYPE(RKH_SM_T, me_)

/**
 *  \brief
 *  This macro declares a typed pointer to previously created state machine
 *  to be used as a global and public object.
 *
 *  \param[in] type_
 *                  Data type of the state machine, derived from RKH_SM_T. 
 *  \param[in] me_	Pointer to previously created state machine.
 *
 *	\note
 *  Generally, this macro is used in the SMA's header file.
 *
 *  \sa
 *  RKH_SMA_CREATE(), RKH_SM_CREATE().
 *
 *  \usage
 *  \code
 *  // ColorRegion.h: state machine's header file
 *
 *  RKH_SM_DCLR_TYPE(ColorRegion, color);
 *  \endcode
 */
#define RKH_SM_DCLR_TYPE(type_, me_) \
            RKH_DCLR_PTR_TYPE(type_, me_)

/**@{
 *
 *  \brief
 *  Declares a previously created state/pseudostate to be used
 *  as a global object.
 *
 *  \note
 *  Generally, this macro is used in the state-machine's header file.
 */
#define RKH_DCLR_COMP_STATE     extern RKHROM RKH_SCMP_T
#define RKH_DCLR_BASIC_STATE    extern RKHROM RKH_SBSC_T
#define RKH_DCLR_FINAL_STATE    extern RKHROM RKH_FINAL_T
#define RKH_DCLR_COND_STATE     extern RKHROM RKH_SCOND_T
#define RKH_DCLR_CHOICE_STATE   extern RKHROM RKH_SCHOICE_T
#define RKH_DCLR_DHIST_STATE    extern RKHROM RKH_SHIST_T
#define RKH_DCLR_SHIST_STATE    extern RKHROM RKH_SHIST_T
#define RKH_DCLR_SUBM_STATE     extern RKHROM RKH_SSBM_T
#define RKH_DCLR_REF_SUBM       extern RKHROM RKH_RSM_T
#define RKH_DCLR_ENPNT          extern RKHROM RKH_SENP_T
#define RKH_DCLR_REF_EXPNT      extern RKHROM RKH_SEXP_T
#define RKH_DCLR_REF_ENPNT      extern RKHROM RKH_ENPCN_T
/**@}*/

/**
 *  \brief
 *  Declares a opaque pointer to previously created array of state machine
 *  applications SMA (a.k.a Active Object) to be used as a global object.
 *
 *  \param[in] _arr		pointer to previously created array of state machine
 *                      applications. To do that is recommended to use the 
 *                      macro RKH_ARRAY_SMA_CREATE().
 *  \param[in] _num		size of array [in active objects].
 *
 *	\note
 *  Generally, this macro is used in the SMA's header file.
 *
 *  \sa
 *  RKH_SMA_CREATE().
 *
 *  \usage
 *  \code
 *  //	cli.h: state-machine application's header file
 *  #define NUM_CLIENTS			4
 *
 *  typedef struct
 *  {
 *      RKH_SMA_T me;		// base structure
 *      RKH_TMR_T cli_utmr; // usage time
 *      RKH_TMR_T cli_rtmr;	// waiting request time
 *  } CLI_T;				// Active Object derived from RKH_SMA_T structure
 *
 *  RKH_ARRAY_SMA_DCLR( clis, NUM_CLIENTS );
 *  \endcode
 */
#define RKH_ARRAY_SMA_DCLR(_arr, _num) \
    extern RKH_SMA_T * const *_arr[_num]

/**
 *  \brief
 *  Declares a typed pointer to previously created array of state machine
 *  applications SMA (a.k.a Active Object) to be used as a global object.
 *
 *  \param[in] type_	data type of active object.
 *  \param[in] array_	pointer to previously created array of state machine
 *                      applications. To do that is recommended to use the 
 *                      macro RKH_ARRAY_SMA_CREATE_TYPE().
 *  \param[in] num_		size of array [in active objects].
 *
 *	\note
 *  Generally, this macro is used in the SMA's header file.
 *
 *  \sa
 *  RKH_SMA_CREATE().
 *
 *  \usage
 *  \code
 *  //	cli.h: state-machine application's header file
 *  #define NUM_CLIENTS			4
 *
 *  typedef struct
 *  {
 *      RKH_SMA_T me;		// base structure
 *      RKH_TMR_T cli_utmr; // usage time
 *      RKH_TMR_T cli_rtmr;	// waiting request time
 *  } CLI_T;				// Active Object derived from RKH_SMA_T structure
 *
 *  RKH_ARRAY_SMA_DCLR_TYPE(CLI_T, clis, NUM_CLIENTS);
 *  \endcode
 */
#define RKH_ARRAY_SMA_DCLR_TYPE(type_, array_, num_) \
    extern type_ * const * array_[num_]

/**
 *  \brief
 *  Declare and allocate an array of SMAs (a.k.a active objects) derived from
 *  RKH_SMA_T.
 *
 *  \param[in] _arr		name of SMA's array.
 *  \param[in] _num		size of array [in active objects].
 *
 *  \usage
 *  \code
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
 *  \endcode
 */
#define RKH_ARRAY_SMA_CREATE(_arr, _num) \
    RKH_SMA_T * const *_arr[_num] =

/**
 *  \brief
 *  Declare and allocate an array of SMAs (a.k.a active objects) derived from
 *  RKH_SMA_T.
 *
 *  \param[in] type_	data type of active object.
 *  \param[in] array_	name of SMA's array.
 *  \param[in] num_		size of array [in active objects].
 *
 *  \usage
 *  \code
 *	// Defines SMAs (a.k.a Active Objects)
 *
 *	RKH_SMA_CREATE(CLI_T, cli0, 1, HCAL, &cli_idle, cli_init, NULL);
 *	RKH_SMA_CREATE(CLI_T, cli1, 2, HCAL, &cli_idle, cli_init, NULL);
 *	RKH_SMA_CREATE(CLI_T, cli2, 3, HCAL, &cli_idle, cli_init, NULL);
 *	RKH_SMA_CREATE(CLI_T, cli3, 4, HCAL, &cli_idle, cli_init, NULL);
 *
 *	RKH_ARRAY_SMA_CREATE(CLI_T, clis, NUM_CLIENTS)
 *	{
 *		&cli0, &cli1, &cli2, &cli3
 *	};
 *  \endcode
 */
#define RKH_ARRAY_SMA_CREATE_TYPE(type_, array_, num_) \
    type_ * const * array_[num_] =

/**
 *  \brief
 *  Retrieves the pointer to active object from a SMA's array.
 *
 *  \param[in] _arr		name of SMA's array.
 *  \param[in] _ix		index (position in the array).
 *
 *  \usage
 *  \code
 *  #define NUM_CLIENTS				4
 *  #define CLI( _clino )			RKH_ARRAY_SMA( clis, _clino )
 *
 *  #define CLI0					CLI(0)
 *  #define CLI1					CLI(1)
 *  #define CLI2					CLI(2)
 *  #define CLI3					CLI(3)
 *
 *  typedef struct
 *  {
 *      RKH_SMA_T me;		// base structure
 *      RKH_TMR_T cli_utmr; // usage time
 *      RKH_TMR_T cli_rtmr;	// waiting request time
 *  } CLI_T;				// Active Object derived from RKH_SMA_T structure
 *
 *  RKH_ARRAY_SMA_DCLR( clis, NUM_CLIENTS );
 *  \endcode
 */
#define RKH_ARRAY_SMA(_arr, _ix)      *_arr[_ix]

/**
 *  \brief
 *  Declares a previously created SMA to be used as a global object.
 *
 *  \param[in] sma_t		data type of SMA.
 *  \param[in] sm			name of previously created SMA.
 *  \param[in] gob			name of global object.
 *
 *  \note
 *  Generally, this macro is used in the state-machine's module.
 *
 *	\sa
 *	RKH_SMA_T structure definition for more information. Also,
 *	\link RKH_EVT_T single inheritance in C \endlink, and
 *	\link RKH_CREATE_BASIC_STATE another example \endlink.
 *
 *  \usage
 *	\code
 *	//	g_my: global pointer to SMA "my".
 *	RKH_DCLR_SM_GLOBAL( MYSM_T, my, g_my );
 *	\endcode
 */
#define RKH_DCLR_SM_GLOBAL(sma_t, sm, gob) \
    sma_t * const gob = &s_##sm;

/**
 *  \brief
 *  Declares a state transition table.
 *
 *  \param[in] name			name of state (basic or composite) object.
 */
#define RKH_DECLARE_TR_TBL(name) \
    extern RKHROM RKH_TR_T name##_trtbl[]

/**
 *  \brief
 *	Initializes the parameters (attibutes) of a basic state object.
 *
 *	By means of single inheritance in C it could be used to associate data
 *	to a basic state. Moreover, implementing the single inheritance in C
 *	is very simply by literally embedding the base type, RKH_SBSC_T in this
 *	case, as the first member of the derived structure. The following
 *	listing shows an example:
 *
 *	\sa
 *	See #RKH_CREATE_BASIC_STATE() macro for more information.
 *
 *  \usage
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
 *	(9) MENU_BASIC_STATE( MENU_ST_T, menu_cfg,  NULL, NULL, RKH_ROOT,
 *												"Menu 1" );
 *		RKH_CREATE_TRANS_TABLE( menu_cfg )
 *			RKH_TRREG( TIMEOUT, NULL, mc_title, &menu_cfg_resume ),
 *			...
 *		RKH_END_TRANS_TABLE
 *
 *  ...
 *
 *
 *	(10) void
 *		 mc_title( const struct RKH_SMA_T *me )
 *		 {
 *		    ...
 *			lcd_print("%s\n", 
 *			          ((MENU_ST_T *)(((RKH_SM_T *)me)->state))->title);
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
 *  The following listing shows another example for derived state structure,
 *  which access to RAM from ROM object (state structure).
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
 *	(3)     XY_T *p_ram_xy;
 *		} NUM_STATE_T;
 *
 *	(4) #define NUM_BASIC_STATE( name, en, ex, parent, p_xy ) \
 *	                RKH_DECLARE_TR_TBL( name ); \
 *					\
 *	                RKHROM NUM_STATE_T name = \
 *					{ \
 *	                    RKH_INIT_BASIC_STATE( name, en, ex, parent, NULL ), \
 *	(5)					p_xy \
 *					}
 *
 *		static XY_T xy;
 *	(6) NUM_BASIC_STATE( num, NULL, NULL, RKH_ROOT, &xy );
 *
 *	    void
 *		num_inc( const struct RKH_SMA_T *me )
 *		{
 *	(7)		((NUM_STATE_T *)(((RKH_SM_T *)me)->state))->p_ram_xy++;
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
 */
#define RKH_INIT_BASIC_STATE(name, en, ex, parent, prepro) \
    { \
        { \
            MKBASE(RKH_BASIC, name),    /* RKH_BASE_T */ \
            MKST(en, ex, parent) \
        },                              /* RKH_ST_T */ \
        MKBASIC(name, prepro) \
    } /* RKH_SBSC_T */ \


/**
 *  \brief
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
#define RKH_INIT_COMPOSITE_STATE(name, en, ex, parent, \
                                 defchild, history) \
    { \
        { \
            MKBASE(RKH_COMPOSITE, name),    /* RKH_BASE_T */ \
            MKST(en, ex, parent) \
        },                                  /* RKH_ST_T */ \
        MKCOMP(name, defchild, history) \
    }                                       /* RKH_SCMP_T */ \

/**
 *  \brief
 *  This values are retrived by guard functions.
 *
 *  A guard is a boolean condition that returns a true or false value that
 *  controls whether or not a transition is taken following the receipt of
 *  a triggering event.
 */
#define RKH_GFALSE      RKH_FALSE   /**< False condition */
#define RKH_GTRUE       RKH_TRUE    /**< True condition */

#if defined(RKH_USE_TRC_SENDER)
/**
 *  \brief
 *  Invoke the system clock tick processing rkh_tmr_tick().
 *
 *  This macro is the recommended way of invoke the clock tick processing,
 *  because it provides the vital information for software tracing and
 *  avoids any overhead when the tracing is disabled.
 *
 *  \param[in] _sender	pointer to the sender object. Typically
 *                      RKH_TIM_TICK() will be called from an interrupt,
 *                      in which case it would create a unique object
 *                      just to unambiguously identify the ISR as the
 *                      sender of the time events.
 *	\sa
 *	rkh_tmr_tick().
 *
 *	\ingroup apiBSPHook
 */
    #define RKH_TIM_TICK(_sender)     rkh_tmr_tick(_sender)
#else
    #define RKH_TIM_TICK(dummy_)      rkh_tmr_tick()
#endif

/**
 *  \brief
 *  Invoke the active object activation function rkh_sma_activate(). 
 *  If RKH_CFG_SMA_VFUNCT_EN is set RKH_ENABLED, this operation is 
 *  polymorphic, where its implementation is defined by the virtual table of 
 *  the active object to activate. 
 *
 *  This macro is the recommended way of invoke the rkh_sma_activate()
 *  function to active an active object, because it allows to
 *  completely hides the platform-specific code.
 *
 *  \param[in] me_	    pointer to previously created state machine
 *                      application.
 *  \param[in] qSto_	base address of the event storage area. A message
 *                      storage area is declared as an array of pointers
 *                      to RKH events.
 *  \param[in] qStoSize size of the storage event area [in number of
 *                      entries].
 *  \param[in] stkSto_	starting address of the stack's memory area.
 *  \param[in] stkSize_ size of stack memory area [in bytes].
 *
 *  \note
 *  In the next releases this macro will be improved, calling a function 
 *  instead of using its own vptr.  
 *
 *	\sa
 *	rkh_sma_activate().
 *
 *  \usage
 *	\code
 *	int
 *	main( int argc, char *argv[] )
 *	{
 *		...
 *		RKH_SMA_ACTIVATE( blinky, qsto, QSTO_SIZE, 0, 0 );
 *		...
 *		return 0;
 *	}
 *	\endcode
 *
 *  \ingroup apiAO
 */
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
#if RKH_CFGPORT_SMA_QSTO_EN == RKH_ENABLED
    #if RKH_CFGPORT_SMA_STK_EN == RKH_ENABLED
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
         ((RKH_SMA_T *)(me_))->vptr->activate(me_, \
                                              (const RKH_EVT_T **)qSto_, \
                                              qStoSize, \
                                              (void *)stkSto_, \
                                              (rui32_t)stkSize_)
    #else
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        ((RKH_SMA_T *)(me_))->vptr->activate(me_, \
                                             (const RKH_EVT_T **)qSto_, \
                                             qStoSize, \
                                             (void *)0, \
                                             (rui32_t)0)
    #endif
#else
    #if RKH_CFGPORT_SMA_STK_EN == RKH_ENABLED
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        ((RKH_SMA_T *)(me_))->vptr->activate(me_, \
                                             (const RKH_EVT_T **)0, \
                                             qStoSize, \
                                             (void *)stkSto_, \
                                             (rui32_t)stkSize_)
    #else
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        ((RKH_SMA_T *)(me_))->vptr->activate(me_, \
                                             (const RKH_EVT_T **)0, \
                                             qStoSize, \
                                             (void *)0, \
                                             (rui32_t)0)
    #endif
#endif
#else
#if RKH_CFGPORT_SMA_QSTO_EN == RKH_ENABLED
    #if RKH_CFGPORT_SMA_STK_EN == RKH_ENABLED
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        rkh_sma_activate(me_, \
                         (const RKH_EVT_T **)qSto_, \
                         qStoSize, \
                         (void *)stkSto_, \
                         (rui32_t)stkSize_)
    #else
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        rkh_sma_activate(me_, \
                         (const RKH_EVT_T **)qSto_, \
                         qStoSize, \
                         (void *)0, \
                         (rui32_t)0)
    #endif
#else
    #if RKH_CFGPORT_SMA_STK_EN == RKH_ENABLED
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        rkh_sma_activate(me_, \
                         (const RKH_EVT_T **)0, \
                         qStoSize, \
                         (void *)stkSto_, \
                         (rui32_t)stkSize_)
    #else
    #define RKH_SMA_ACTIVATE(me_, qSto_, qStoSize, stkSto_, stkSize_) \
        rkh_sma_activate(me_, \
                         (const RKH_EVT_T **)0, \
                         qStoSize, \
                         (void *)0, \
                         (rui32_t)0)
    #endif
#endif
#endif


/**
 *  \brief
 *  Use it to allocate a state machine regardless of an active object.
 *
 *  \param[in] type 	Data type of the SMA. Could be derived from RKH_SMA_T.
 *  \param[in] name		Name of state machine application. Also, it represents 
 *                      the top state of state diagram.
 *  \param[in] prio		State machine application priority. A unique priority
 *                      number must be assigned to each SMA from 0 to
 *                      RKH_LOWEST_PRIO. The lower the number, the higher the
 *                      priority.
 *  \param[in] ppty		State machine properties. The available properties are
 *                      enumerated in RKH_HPPTY_T enumeration in the rkh.h
 *                      file.
 *  \param[in] initialState
 *                      Pointer to initial state. This state could be defined
 *                      either composite or basic (not pseudo-state).
 *  \param[in] initialAction
 *                      Pointer to initialization action (optional). The
 *                      function prototype is defined as RKH_INIT_ACT_T. This
 *                      argument is optional, thus it could be declared as
 *                      NULL.
 *  \param[in] initialEvt
 *                      Pointer to an event that will be passed to state
 *                      machine application when it starts. Could be used to
 *                      pass arguments to the state machine like an argc/argv.
 *                      This argument is optional, thus it could be declared
 *                      as NULL or eliminated in compile-time with
 *                      RKH_CFG_SMA_INIT_EVT_EN = 0.
 *
 *  \sa RKH_SM_CONST_CREATE, RKH_SM_GET_CONST, RKH_SM_GET_CONST
 */
#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SM_CREATE(type, name, prio, ppty, initialState, \
                          initialAction, initialEvt) \
        RKH_SM_CONST_CREATE(name, prio, ppty, initialState, initialAction, \
                            initialEvt); \
        static type s_##name = {MKSM(&RKH_SM_CONST_NAME(name), initialState)}
#else
    #define RKH_SM_CREATE(type, name, prio, ppty, initialState, \
                          initialAction, initialEvt) \
        static type RKH_SMA_NAME(name) = {MKSM(name, prio, ppty, initialState, \
                                               initialAction, initialEvt)}
#endif

/**
 *  \brief
 *  Initialize (at runtime) a previously created state machine object.
 *
 *  \param[in] me_		Name of state machine. Also, it represents the top 
 *                      state of state diagram.
 *  \param[in] nameSMConst_  
 *                      Describe it 
 *  \param[in] prio_	State machine application priority. A unique priority
 *                      number must be assigned to each SMA from 0 to
 *                      RKH_LOWEST_PRIO. The lower the number, the higher the
 *                      priority.
 *  \param[in] ppty_	State machine properties. The available properties are
 *                      enumerated in RKH_HPPTY_T enumeration in the rkh.h
 *                      file.
 *  \param[in] initialState_ 
 *                      Pointer to initial state. This state could be defined
 *                      either composite or basic (not pseudo-state).
 *  \param[in] initialAction_ 
 *                      Pointer to initialization action (optional). The
 *                      function prototype is defined as RKH_INIT_ACT_T. This
 *                      argument is optional, thus it could be declared as
 *                      NULL.
 *  \param[in] initialEvt_ 
 *                      Pointer to an event that will be passed to state
 *                      machine application when it starts. Could be used to
 *                      pass arguments to the state machine like an argc/argv.
 *                      This argument is optional, thus it could be declared
 *                      as NULL or eliminated in compile-time with
 *                      RKH_CFG_SMA_INIT_EVT_EN = 0.
 */
#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SM_INIT(me_, nameSMConst_, prio_, ppty_, initialState_, \
                        initialAction_, initialEvt_) \
        ((RKH_SM_T *)me_)->romrkh = \
            (RKHROM RKH_ROM_T *)(RKH_SM_GET_CONST_OBJ(nameSMConst_)); \
        ((RKH_SM_T *)me_)->state = \
            (RKHROM struct RKH_ST_T *) \
                ((RKH_SM_GET_CONST_OBJ(nameSMConst_))->istate)
#else
    #define RKH_SM_INIT(sm, name, prio, ppty, initialState, \
                        initialAction, initialEvt) \
        MKRT_SM(sm, name, prio, ppty, initialState, initialAction, initialEvt)
#endif

/**
 *  \brief
 *  Declare and allocate a SMA (active object) derived from RKH_SMA_T. Also,
 *  initializes and assigns a state machine to previously declared SMA.
 *
 *  In the UML specification, every state machine has a top state
 *  (the abstract root of every state machine hierarchy), which contains
 *  all the other elements of the entire state machine. RKH provides the
 *  top state using the macro RKH_SMA_CREATE().
 *	Frequently, RKH_SMA_CREATE() is used within state-machine's module
 *	(.c file), thus the structure definition is in fact entirely encapsulated
 *	in its module and is inaccessible to the rest of the application.
 *	However, use RKH_SMA_DEF_PTR() or RKH_SMA_DEF_PTR_TYPE() macros to 
 *	define a opaque pointer or typed pointer to that state machine application 
 *	structure, respectively. Also, use the RKH_SMA_DCLR() macro to declare it 
 *	to be for the rest of application code. 
 *  RKH_SMA_T is not intended to be instantiated directly, but rather
 *  serves as the base structure for derivation of state machines in the
 *  application code.
 *  The following example illustrates how to derive an state machine from
 *  RKH_SMA_T. Please note that the RKH_SMA_T member sm is defined as the
 *  FIRST member of the derived structure.
 *
 *  \param[in] type 	Data type of the SMA. Could be derived from RKH_SMA_T.
 *  \param[in] name		Name of state machine application. Also, it represents 
 *                      the top state of state diagram.
 *  \param[in] prio		State machine application priority. A unique priority
 *                      number must be assigned to each SMA from 0 to
 *                      RKH_LOWEST_PRIO. The lower the number, the higher the
 *                      priority.
 *  \param[in] ppty		State machine properties. The available properties are
 *                      enumerated in RKH_HPPTY_T enumeration in the rkh.h
 *                      file.
 *  \param[in] initialState
 *                      Pointer to initial state. This state could be defined
 *                      either composite or basic (not pseudo-state).
 *  \param[in] initialAction
 *                      Pointer to initialization action (optional). The
 *                      function prototype is defined as RKH_INIT_ACT_T. This
 *                      argument is optional, thus it could be declared as
 *                      NULL.
 *  \param[in] initialEvt
 *                      Pointer to an event that will be passed to state
 *                      machine application when it starts. Could be used to
 *                      pass arguments to the state machine like an argc/argv.
 *                      This argument is optional, thus it could be declared
 *                      as NULL or eliminated in compile-time with
 *                      RKH_CFG_SMA_INIT_EVT_EN = 0.
 *
 *  \sa RKH_SM_CONST_CREATE(), RKH_SM_GET_CONST(), RKH_SM_GET_CONST(),
 *      RKH_SMA_DEF_PTR(), RKH_SMA_DEF_PTR_TYPE()
 *
 *	\usage
 *	\code
 *	...within state-machine application's module
 *
 *	typedef struct
 *	{
 *		RKH_SMA_T ao;	// base structure
 *		rui8_t x;		// private member
 *		rui8_t y;		// private member
 *	} MYSM_T;
 *
 *  //	static instance of SMA object
 *	RKH_SMA_CREATE(MYSM_T, my, 0, HCAL, &S1, my_iaction, &my_ievent);
 *	\endcode
 */
#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SMA_CREATE(type, name, prio, ppty, initialState, \
                           initialAction, initialEvt) \
        RKH_SM_CONST_CREATE(name, prio, ppty, initialState, initialAction, \
                            initialEvt); \
        static type RKH_SMA_NAME(name) = MKSMA(&RKH_SM_CONST_NAME(name), \
                                               initialState)
#else
    #define RKH_SMA_CREATE(type, name, prio, ppty, initialState, \
                           initialAction, initialEvt) \
        static type RKH_SMA_NAME(name) = MKSMA(name, \
                                               prio, \
                                               ppty, \
                                               initialState, \
                                               initialAction, \
                                               initialEvt)
#endif

/**
 *  \brief
 *  Allocates and then initializes the constant part (in ROM) of the state 
 *  machine.
 *
 *  \param[in] name		Name of state machine application. Also, it represents 
 *                      the top state of state diagram.
 *  \param[in] prio		State machine application priority. A unique priority
 *                      number must be assigned to each SMA from 0 to
 *                      RKH_LOWEST_PRIO. The lower the number, the higher the
 *                      priority.
 *  \param[in] ppty		State machine properties. The available properties are
 *                      enumerated in RKH_HPPTY_T enumeration in the rkh.h
 *                      file.
 *  \param[in] initialState
 *                      Pointer to initial state. This state could be defined
 *                      either composite or basic (not pseudo-state).
 *  \param[in] initialAction
 *                      Pointer to initialization action (optional). The
 *                      function prototype is defined as RKH_INIT_ACT_T. This
 *                      argument is optional, thus it could be declared as
 *                      NULL.
 *  \param[in] initialEvt
 *                      Pointer to an event that will be passed to state
 *                      machine application when it starts. Could be used to
 *                      pass arguments to the state machine like an argc/argv.
 *                      This argument is optional, thus it could be declared
 *                      as NULL or eliminated in compile-time with
 *                      RKH_CFG_SMA_INIT_EVT_EN = 0.
 */
#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SM_CONST_CREATE(name, prio, ppty, initialState, \
                                initialAction, initialEvt) \
       static RKHROM RKH_ROM_T RKH_SM_CONST_NAME(name) = \
                                                MKRRKH(name, \
                                                       prio, \
                                                       ppty, \
                                                       initialState, \
                                                       initialAction, \
                                                       initialEvt)
#else
    #define RKH_SM_CONST_CREATE(name, prio, ppty, initialState, \
                                initialAction, initialEvt)
#endif

/**
 *  \brief
 *  Return the address of the constant part from a previously created and 
 *  initializated state machine.
 *
 *  \param[in] sm   Name of state machine.
 */
#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SM_GET_CONST(sm) \
        ((RKH_SM_T *)sm)->romrkh
#else
    #define RKH_SM_GET_CONST(sm) \
        ((RKH_SM_T *)sm)
#endif

/**
 *  \brief
 *  Return the address of the constant part of a state machine.
 *
 *  \param[in] sm   Name of state machine.
 */
#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SM_GET_CONST_OBJ(sm) \
        &RKH_SM_CONST_NAME(sm)
#else
    #define RKH_SM_GET_CONST_OBJ(sm) \
        ((RKH_SM_T *)sm)
#endif

#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SMA_INIT(me, prio, ppty, initialState, initialAction, \
                         initialEvt)
#else
    #define RKH_SMA_INIT(me, prio, ppty, initialState, initialAction, \
                         initialEvt) \
        MKRT_SM(me, me, prio, ppty, initialState, initialAction, initialEvt)
#endif

#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SMA_GET_OBJ(type, me)
#else
    #define RKH_SMA_GET_OBJ(type, me) \
        (type *)&RKH_SMA_NAME(me)
#endif

#if RKH_CFG_SMA_SM_CONST_EN == RKH_ENABLED
    #define RKH_SM_GET_OBJ(type, sm)
#else
    #define RKH_SM_GET_OBJ(type, sm) \
        (type *)&RKH_SM_NAME(sm)
#endif

/**
 *  \brief
 *  Declare an opaque pointer pointing to a previously created state 
 *  machine.
 *
 *  \param[in] sm   Name of state machine.
 *
 *  \sa RKH_SMA_DCLR()
 */
#define RKH_SM_DEF_PTR(sm) \
    RKH_SM_T *const sm = (RKH_SM_T *)&RKH_SM_NAME(sm)

/**
 *  \brief
 *  Declare a pointer of specified type pointing to a previously created 
 *  state machine.
 *  
 *  The pointer could be used to hide (opaque) or to publish the internals of 
 *  the class of the state machine. 
 *
 *  \param[in] type Data type of the state machine. Could be derived from 
 *                  RKH_SM_T.
 *  \param[in] sm   Name of state machine.
 *
 *  \sa RKH_SMA_DCLR()
 */
#define RKH_SM_DEF_PTR_TYPE(type, sm) \
    type *const sm = (type *)&RKH_SM_NAME(sm)

/**
 *  \brief
 *  Declare a opaque pointer pointing to an previously created active 
 *  object.
 *
 *  \param[in] me_  Name of state machine application.
 *
 *  \sa RKH_SMA_DCLR()
 */
#define RKH_SMA_DEF_PTR(me_) \
    RKH_SMA_T *const me_ = (RKH_SMA_T *)&RKH_SMA_NAME(me_)

/**
 *  \brief
 *  Declare a pointer of specified type pointing to an previously created 
 *  active object.
 *  
 *  The pointer could be used to hide (opaque) or to publish the internals of 
 *  the class of the active object. 
 *
 *  \param[in] type Data type of the state machine application. Could be 
 *                  derived from RKH_SMA_T.
 *  \param[in] me_  Name of state machine application.
 *
 *  \sa RKH_SMA_DCLR()
 */
#define RKH_SMA_DEF_PTR_TYPE(type, me_) \
    type *const me_ = (type *)&RKH_SMA_NAME(me_)

/**
 *  \brief
 *  Invoke the direct event posting facility rkh_sma_post_fifo().
 *  If RKH_CFG_SMA_VFUNCT_EN is set RKH_ENABLED, this operation is 
 *  polymorphic, where its implementation is defined by the virtual table of 
 *  the target active object. 
 *
 *  This macro is the recommended way of posting events, because it
 *  provides the vital information for software tracing and avoids any
 *  overhead when the tracing is disabled.
 *
 *  \param[in] me_		pointer to previously created state machine
 *                      application.
 *  \param[in] e_		actual event sent to the state machine application.
 *  \param[in] sender_	pointer to the sender object. It is not
 *                      necessarily a pointer to an active object. In
 *                      fact, if RKH_SMA_POST_FIFO() is called from an
 *                      interrupt or other context, it can create a
 *                      unique object just to unambiguously identify the
 *                      publisher of the event.
 *
 *  \note
 *  In the next releases this macro will be improved, calling a function 
 *  instead of using its own vptr.  
 *
 *	\sa
 *	rkh_sma_post_fifo().
 *
 *  \ingroup apiAO
 */
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    #if defined(RKH_USE_TRC_SENDER)
        #define RKH_SMA_POST_FIFO(me_, e_, sender_) \
            ((RKH_SMA_T *)(me_))->vptr->post_fifo((me_), (e_), (sender_))
    #else
        #define RKH_SMA_POST_FIFO(me_, e_, sender_) \
            ((RKH_SMA_T *)(me_))->vptr->post_fifo((me_), (e_))
    #endif
#else
    #if defined(RKH_USE_TRC_SENDER)
        #define RKH_SMA_POST_FIFO(me_, e_, sender_) \
            rkh_sma_post_fifo((me_), (e_), (sender_))
    #else
        #define RKH_SMA_POST_FIFO(me_, e_, sender_) \
            rkh_sma_post_fifo((me_), (e_))
    #endif
#endif

/**
 *  \brief
 *  Invoke the direct event posting facility rkh_sma_post_lifo().
 *  If RKH_CFG_SMA_VFUNCT_EN is set RKH_ENABLED, this operation is 
 *  polymorphic, where its implementation is defined by the virtual table of 
 *  the target active object. 
 *
 *  This macro is the recommended way of posting events, because it
 *  provides the vital information for software tracing and avoids any
 *  overhead when the tracing is disabled.
 *
 *  \param[in] me_	    pointer to previously created state machine
 *                      application.
 *  \param[in] e_		actual event sent to the state machine application.
 *  \param[in] sender_	pointer to the sender object. It is not
 *                      necessarily a pointer to an active object. In
 *                      fact, if RKH_SMA_POST_LIFO() is called from an
 *                      interrupt or other context, it can create a
 *                      unique object just to unambiguously identify the
 *                      publisher of the event.
 *
 *  \note
 *  In the next releases this macro will be improved, calling a function 
 *  instead of using its own vptr.  
 *
 *	\sa
 *	rkh_sma_post_lifo().
 *
 *  \ingroup apiAO
 */
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    #if defined(RKH_USE_TRC_SENDER)
        #define RKH_SMA_POST_LIFO(me_, e_, sender_) \
            ((RKH_SMA_T *)(me_))->vptr->post_lifo((me_), (e_), (sender_))
    #else
        #define RKH_SMA_POST_LIFO(me_, e_, sender_) \
            ((RKH_SMA_T *)(me_))->vptr->post_lifo((me_), (e_))
    #endif
#else
    #if defined(RKH_USE_TRC_SENDER)
        #define RKH_SMA_POST_LIFO(me_, e_, sender_) \
            rkh_sma_post_lifo((me_), (e_), (sender_))
    #else
        #define RKH_SMA_POST_LIFO(me_, e_, sender_) \
            rkh_sma_post_lifo((me_), (e_))
    #endif
#endif

/**
 *  \brief
 *	This macro dynamically creates a new event of type \a et with its
 *	signal.
 *
 *	The basic policy is to allocate the event from the first pool that
 *	has a block size big enough to fit the requested event size. RKH
 *	can manage up to three event pools (e.g., small, medium, and large
 *	events, like shirt sizes). It returns a pointer to the event
 *	already cast to the event type (et*). 
 *
 *  \param[in] et		type of event
 *  \param[in] e		event signal
 *  \param[in] sender_	pointer to the actor that request a memory block. It is not 
 *                      necessarily a pointer to an active object. In fact, if 
 *                      RKH_ALLOC_EVT() is called from an interrupt or 
 *                      other context, it can create a unique object just to 
 *                      unambiguously identify the publisher of the event.
 *
 *  \note
 *	The assertions inside rkh_fwk_ae() function guarantee that the
 *	pointer is valid, so you don't need to check the pointer returned
 *	from rkh_fwk_ae(), unlike the value returned from malloc(), which
 *	you should check.
 *
 *  \usage
 *	Here is an example of dynamic event allocation with the macro 
 *	RKH_ALLOC_EVT():
 *
 *	\code
 *	MYEVT_T *mye = RKH_ALLOC_EVT(MYEVT_T, DATA, me);
 *	mye->y = mye->x = 0;
 *	...
 *	\endcode
 *
 *  \ingroup apiEvt
 */
#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
    #define RKH_ALLOC_EVT(et, e, sender_) \
        (et *)rkh_fwk_ae((RKH_ES_T)sizeof(et),(RKH_SIG_T)(e), sender_)
#else
    #define RKH_ALLOC_EVT(et, e, sender_) \
        (void)0
#endif

/**
 *  \brief
 *  Recycle a dynamic event.
 *
 *  This macro implements a simple garbage collector for the dynamic
 *  events.	Only dynamic events are candidates for recycling.
 *  (A dynamic event is one that is allocated from an event pool, which
 *  is determined as non-zero	e->nref attribute.) Next, the function
 *  decrements the reference counter of the event, and recycles the
 *  event only if the counter drops to zero (meaning that no more
 *  references are outstanding for this event). The dynamic event is
 *  recycled by returning it to the pool from which	it was originally
 *  allocated. The pool-of-origin information is stored in the
 *  e->pool member.
 *
 *  \param[in] e		pointer to event to be potentially recycled.
 *  \param[in] sender_  Pointer to the actor that request a memory block. 
 *                      It is not necessarily a pointer to an active 
 *                      object. In fact, if RKH_FWK_GC() is called from 
 *                      an interrupt or other context, it can create a 
 *                      unique object just to unambiguously identify the 
 *                      publisher of the event.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it. Instead, use #RKH_FWK_GC() macro.
 *  \note
 *  The garbage collector must be explicitly invoked at all appropriate
 *  contexts, when an event can become garbage (automatic garbage
 *  collection).
 *  \note
 *  When setting RKH_CFG_FWK_DYN_EVT_EN = 0 the garbage collector has
 *  not effect, thus it's eliminated in compile-time.
 *
 *  \ingroup apiEvt
 */
#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
    #define RKH_FWK_GC(e, sender_)      rkh_fwk_gc(e, sender_)
#else
    #define RKH_FWK_GC(e, sender_)      (void)0
#endif

/**
 *  \brief
 *  Reserve the dynamic event to be recycled.
 *
 *  This is the complement to RKH_FWK_GC(). It increments the reference
 *  count of a dynamic event so the event can be saved by an SMA (AO).
 *  Sometime later the SMA should manually release the event with
 *  RKH_FWK_GC().
 *
 *  \param[in] e		pointer to event to be reserved.
 *
 *  \ingroup apiEvt
 */
#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
    #define RKH_FWK_RSV(e)            rkh_fwk_reserve(e)
#else
    #define RKH_FWK_RSV(e)            (void)0
#endif

/**
 *  \brief
 *	This macro initialize an event \a e with \a es signal and establishes
 *	it as one static event.
 *
 *  \param[in] ev_obj	name of event structure (object).
 *  \param[in] ev_sig	event signal. The RKH takes this value for triggering
 *                      a state transition.
 *
 *	\sa RKH_ROM_STATIC_EVENT() and RKH_STATIC_EVENT() macros.
 *
 *	\usage
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
 *  some_function( ... )
 *  {
 *      RKH_SET_STATIC_EVENT( &ev_txsm, REQ_SEND_SMS );
 *      ev_txsm.e.cmd = RPC_SEND_SMS;
 *		...
 *	}
 *	\endcode
 *
 *  \ingroup apiEvt
 */
#define RKH_SET_STATIC_EVENT(ev_obj, ev_sig) \
    MK_SET_EVT(ev_obj, ev_sig)

/**
 *  \brief
 *	This macro declares and initializes the event structure \a ev_ob with
 *	\a ev_sig signal number and establishes it as one static event.
 *
 *  \param[in] ev_obj	name of event structure (object).
 *  \param[in] ev_sig	event signal. The RKH takes this value for triggering
 *                      a state transition.
 *
 *	\sa RKH_SET_STATIC_EVENT() and RKH_ROM_STATIC_EVENT() macros.
 *
 *	\usage
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
 *  \ingroup apiEvt
 */
#define RKH_STATIC_EVENT(ev_obj, ev_sig) \
    MK_EVT(ev_obj, ev_sig)

/**
 *  \brief
 *	This macro declares and initializes the event structure \a ev_ob with
 *	\a ev_sig signal number and establishes it as one static event.
 *
 *  \param[in] ev_obj	name of event structure (object).
 *  \param[in] ev_sig	event signal. The RKH takes this value for triggering
 *                      a state transition.
 *
 *	\sa RKH_SET_STATIC_EVENT() and RKH_STATIC_EVENT() macros.
 *
 *	\warning
 *	The created event object is explicitly placed at ROM.
 *
 *	\usage
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
 *  \ingroup apiEvt
 */
#define RKH_ROM_STATIC_EVENT(ev_obj, ev_sig) \
    MK_ROM_EVT(ev_obj, ev_sig)

/**
 *  \brief
 *	Initializes the attibutes of a RKH's event object structure.
 *
 *	\usage
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
 *  ...
 *  void
 *  some_function(void)
 *  {
 *      RKH_SMA_POST_FIFO(drpc, RKH_EVT_CAST(&ev_ssreq), 0);
 *      ...
 *  }
 *	\endcode
 *
 *  \ingroup apiEvt
 */
#define RKH_INIT_STATIC_EVT(ev_sig) \
    MK_EVT_STRUCT(ev_sig)

/**
 *  \brief
 *  This macro retrieves the state ID of SMA.
 *
 *  \param[in] me	pointer to previously created state machine application.
 *
 *  \return
 *  Id of current state.
 */
#define RKH_GET_CSTATE_ID(me) \
    ((RKH_BASE_T *)(((RKH_SM_T *)me)->state))->id

#if R_TRC_AO_NAME_EN == RKH_ENABLED
    /**
     *  \brief
     *  This macro retrieves the name of an registered active object.
     *
     *  \param[in] ao		pointer to previously created active object.
     *
     *  \return
     *  Name of active object.
     */
    #define RKH_GET_AO_NAME(ao)       RKH_SMA_ACCESS_CONST(ao, name)

    /**
     *  \brief
     *  This macro retrieves the name of a vertex.
     *
     *  \param[in] vx		pointer to previously created vertex object.
     *
     *  \return
     *  Name of vertex object.
     */
    #define RKH_GET_VERTEX_NAME(vx) \
        ((struct RKH_BASE_T *)(vx))->name
#else
    #define RKH_GET_AO_NAME(ao)           noname
    #define RKH_GET_VERTEX_NAME(vx)       noname
#endif

/**
 *  \brief
 *  Retrieves the address of an registered active object (SMA) according to
 *  its priority.
 *
 *  \param[in] _prio	registered active object (SMA) priority.
 *  \return			    pointer to previously registered active object (SMA).
 */
#define RKH_GET_SMA(_prio) \
    rkh_sptbl[(rui8_t)(_prio)]

/**
 *  \brief
 *  Retrieves the priority number of an registered active object (SMA).
 *
 *  \param[in] _ao		pointer to previously registered active object (SMA).
 */
#define RKH_GET_PRIO(_ao) \
    (rui8_t)(RKH_SMA_ACCESS_CONST(_ao, prio))

/**
 *  \brief
 *  Perform cast to pointer to RKH event structure (RKH_EVT_T*).
 *
 *  \ingroup apiEvt
 */
#define RKH_EVT_CAST(_e)      ((RKH_EVT_T *)(_e))

/**
 *  \brief
 *  Perform downcast of a reference of a base class to one of its derived
 *  classes.
 *
 *	\sa
 *	\link RKH_EVT_T single inheritance in C \endlink, and
 *	\link RKH_CREATE_BASIC_STATE another example \endlink.
 *
 *  \usage
 *  \code
 *  void
 *  svr_start( const struct RKH_SMA_T *me, RKH_EVT_T *pe )
 *  {
 *      START_EVT_T *e_start;
 *
 *      e_start = RKH_ALLOC_EVT( START_EVT_T, START, me );
 *      e_start->clino = RKH_CAST(REQ_EVT_T, pe)->clino;
 *      RKH_SMA_POST_FIFO( RKH_GET_SMA( RKH_CAST(REQ_EVT_T, pe)->clino ),
 *												RKH_EVT_CAST(e_start), me );
 *  }
 *  \endcode
 */
#define RKH_CAST(_type, _obj)     ((_type *)(_obj))

/**
 *  \brief
 *	Open the tracing session.
 *
 *	This function is application-specific and the user needs to
 *	define it. At a minimum, this function must initialize and/or
 *	configure the trace stream by calling rkh_trc_init() and
 *	RKH_TRC_SEND_CFG() respectively.
 *
 *  \note
 *  This function is internal to RKH and the user application
 *  should not call it. Instead, use #RKH_TRC_OPEN() macro.
 *
 *  \sa \b rkhtrc.h file.
 *
 *	\usage
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
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
    #define RKH_TRC_OPEN()      rkh_trc_open()
#else
    #define RKH_TRC_OPEN()      (void)0
#endif

/**
 *  \brief
 *	Close the tracing session.
 *
 *	This function is application-specific and the user needs to
 *	define it.
 *
 *  \note
 *  This function is internal to RKH and the user application
 *  should not call it. Instead, use #RKH_TRC_CLOSE() macro.
 *
 *  \sa \b rkhtrc.h file.
 *
 *	\usage
 *
 *	\code
 *	void
 *	rkh_trc_close( void )
 *	{
 *		fclose( fdbg );
 *	}
 *	\endcode
 *
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
    #define RKH_TRC_CLOSE()     rkh_trc_close()
#else
    #define RKH_TRC_CLOSE()     (void)0
#endif

/**
 *  \brief
 *	Platform-dependent macro flushing the trace stream.
 *
 *	This function is application-specific and the user needs to define
 *	it. When the RKH trace an event, all the information related to it
 *	has to be stored somewhere before it can be retrieved, in order to
 *	be analyzed.
 *  This place is a trace stream. Frequently, events traced are stored
 *  in the stream until it is flushed.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it. Instead, use #RKH_TRC_FLUSH() macro.
 *
 *  \sa \b rkhtrc.h file.
 *
 *	\usage
 *	\code
 *  void
 *  rkh_trc_flush( void )
 *  {
 *      rui8_t *blk;
 *      TRCQTY_T nbytes;
 *      RKH_SR_ALLOC();
 *
 *      FOREVER
 *      {
 *          nbytes = (TRCQTY_T)1024;
 *
 *          RKH_ENTER_CRITICAL_();
 *          blk = rkh_trc_get_block( &nbytes );
 *          RKH_EXIT_CRITICAL_();
 *
 *          if((blk != (rui8_t *)0))
 *          {
 *              FTBIN_FLUSH( blk, nbytes );
 *              TCP_TRACE_SEND_BLOCK( blk, nbytes );
 *          }
 *          else
 *              break;
 *      }
 *  }
 *	\endcode
 *
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
    #define RKH_TRC_FLUSH()     rkh_trc_flush()
#else
    #define RKH_TRC_FLUSH()     (void)0
#endif

/**
 *  \brief
 *  Send the trace facility configuration to host application software
 *  Trazer.
 *
 *  Trazer is designed to work with all possible target CPU, which
 *  requires a wide range of configurability. For example, for any
 *  given target CPU, Trazer must "know" the size of object pointers,
 *  event size, timestamp size and so on. This configurations could be
 *  provided through "trazer.cfg" file in the host or invoking
 *  RKH_TRC_SEND_CFG() macro from the application-specific
 *  rkh_trc_open() function.
 *
 *  \param[in] ts_hz		clocks per second of trace timestamp.
 *
 *  \note
 *	Frequently, this macro is called from the rkh_trc_open() function,
 *	which is provided by user application program, more specifically
 *	the board support package (BSP).
 *
 *  \sa RKH_TRC_OPEN() macro.
 *
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
    #define RKH_TRC_SEND_CFG(ts_hz) \
        RKH_TR_FWK_TCFG(ts_hz)
#else
    #define RKH_TRC_SEND_CFG(ts_hz)     (void)0
#endif

/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Initializes the RKH framework.
 *
 *  A requirement of RKH is that must be called rkh_fwk_init() before call any
 *  of its other services. This function initializes all of RKH's variables
 *  and data structures.
 *
 *  \note
 *	Platform-dependent function. All RKH ports must be define it in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Initializes the RKH framework
 *
 *  \ingroup apiPortMisc
 */
void rkh_fwk_init(void);

/**
 *  \brief
 *  RKH framework is started.
 *
 *  This entry function turns over control to RKH (and does not return!).
 *  This function runs the highest priority state machine application (SMA)
 *  that is ready to run in run-to-completation model.
 *
 *  \note
 *  The call to this function does not return. Hence, any code after it will
 *  never be executed.
 *
 *  \note
 *	Platform-dependent function. All RKH ports must be define it in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Run RKH framework
 *
 *	Here is the basic algorithm for interpreting the listing shown above.
 *	A pseudocode description of the procedure is:
 *  \include pseudo_cooperative_emulator.c
 *
 *  \ingroup apiPortMisc
 */
void rkh_fwk_enter(void);

/**
 *  \brief
 *  Exit the RKH framework.
 *
 *  Function invoked by the application layer to exit the RKH application and
 *  return control to the underlying OS/Kernel.
 *
 *  \note
 *	This function is strongly platform-dependent. All RKH ports and must be
 *	defined in the RKH port to a particular platform.
 *	Some RKH ports might not require implementing this function at all,
 *	because many embedded applications don't have anything to exit to.
 *
 *  \note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Exit the RKH framework
 *
 *  \ingroup apiPortMisc
 */
void rkh_fwk_exit(void);

/**
 *  \brief
 *  Terminate a state machine application (SMA) as known as active object.
 *
 *  A state machine application may call this service to terminate itself.
 *  Once terminated, the state machine application must be re-created in
 *  order for it to execute again.
 *
 *  \param[in] me      pointer to previously created state machine
 *                      application.
 *
 *	\note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Terminates an active object
 *
 *  \ingroup apiPortAO
 */
void rkh_sma_terminate(RKH_SMA_T *me);

#if defined(RKH_USE_TRC_SENDER)
/**
 *  \brief
 *  Keep tracks and updates the started timers.
 *
 *	Time intervals are measured by periodic timer interrupts. Each timer
 *	interrupt is called a timer-tick. The actual time between timer-ticks
 *	is specified by the application.
 *  This function must be placed where will be incrementing the system
 *  tick. Normally this function is placed in a timer ISR routine.
 *  If one or more timers expires the assigned event is directly posted
 *  into the state machine application (SMA) queue and associated hook
 *  function is executed (if it's used). The expiration events of timers
 *  that expire at the same time are executed in the order they were
 *  started.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it. Instead, use #RKH_TIM_TICK() macro.
 */
void rkh_tmr_tick(const void *const sender);
#else
void rkh_tmr_tick(void);
#endif

/**
 *  \brief
 *  Initializes and activates a previously created state machine application
 *  (SMA) as known as active object.
 *
 *  A state machine application (SMA) is declared with the RKH_SMA_T data
 *  type and is defined with the rkh_sma_activate() service.
 *
 *  \param[in] me       pointer to previously created state machine
 *                      application.
 *  \param[in] qSto     base address of the event storage area. A message
 *                      storage area is declared as an array of pointers to
 *                      RKH events.
 *  \param[in] qSize    size of the storage event area [in number of entries].
 *  \param[in] stkSto   starting address of the stack's memory area.
 *  \param[in] stkSize  size of stack memory area [in bytes].
 *
 *	\note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Activates an active object
 *
 *  \ingroup apiPortAO
 */
void rkh_sma_activate(RKH_SMA_T *me, const RKH_EVT_T * *qSto,
                      RKH_RQNE_T qSize, void *stkSto, rui32_t stkSize);

#if defined(RKH_USE_TRC_SENDER)
/**
 *  \brief
 *  Send an event to a state machine application (SMA) as known as active
 *  object through a queue using the FIFO policy. A message is a pointer
 *  size variable and its use is application specific.
 *
 *  \param[in] me      pointer to previously created state machine
 *                      application.
 *  \param[in] e		actual event sent to the state machine application.
 *  \param[in] sender	pointer to the sender object. It is not necessarily a 
 *                      pointer to an active object. In fact, if 
 *                      RKH_SMA_POST_FIFO() is called from an interrupt or 
 *                      other context, it can create a unique object just to 
 *                      unambiguously identify the publisher of the event.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it. Instead, use RKH_SMA_POST_FIFO() macro.
 *  \note
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
 *  \ingroup apiPortAO
 */
void rkh_sma_post_fifo(RKH_SMA_T *me, const RKH_EVT_T *e,
                       const void *const sender);
#else
void rkh_sma_post_fifo(RKH_SMA_T *me, const RKH_EVT_T *e);
#endif

#if defined(RKH_USE_TRC_SENDER)
/**
 *  \brief
 *  Send an event to a state machine application (SMA) as known as active
 *  object through a queue using the LIFO policy. A message is a pointer
 *  size variable and its use is application specific.
 *
 *  \param[in] me		pointer to previously created state machine 
 *                      application.
 *  \param[in] e		actual event sent to the state machine application.
 *  \param[in] sender	pointer to the sender object. It is not
 *                      necessarily a pointer to an active object. In
 *                      fact, if RKH_SMA_POST_FIFO() is called from an
 *                      interrupt or other context, it can create a
 *                      unique object just to unambiguously identify the
 *                      publisher of the event.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it. Instead, use RKH_SMA_POST_LIFO() macro.
 *  \note
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
 *  \ingroup apiPortAO
 */
void rkh_sma_post_lifo(RKH_SMA_T *me, const RKH_EVT_T *e,
                       const void *const sender);

#else
void rkh_sma_post_lifo(RKH_SMA_T *me, const RKH_EVT_T *e);
#endif

/**
 *  \brief
 *  Get an event from the event queue of an state machine application (SMA)
 *  as known as active object.
 *  The events received are pointer size variables and their use is
 *  application specific.
 *
 *  \param[in] me		pointer to previously created state machine 
 *                      application.
 *
 *	\return     A non-NULL pointer indicates that a event pointer was 
 *	            available, otherwise a NULL pointer.
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
 *  \ingroup apiPortAO
 */
RKH_EVT_T *rkh_sma_get(RKH_SMA_T *me);

/**
 *  \brief
 *  Retrieves performance information for a particular state machine
 *  application (SMA) as known as active object.
 *
 *	The user application must allocate an RKH_SMAI_T data structure used to
 *	receive data. The performance information is available during run-time
 *	for each of the RKH services. This can be useful in determining whether
 *	the application is performing properly, as well as helping to optimize the
 *	application.
 *	This information provides a "snapshot" a particular instant in time, i.e.,
 *	when the service is invoked.
 *
 *  \param[in] me  pointer to previously created state machine application.
 *  \param[in] psi  pointer to the buffer into which the performance
 *                  information will be copied by reference.
 *
 *  \note
 *  See RKH_SMAI_T structure for more information. This function is optional, 
 *  thus it could be eliminated in compile-time with 
 *  RKH_CFG_SMA_GET_INFO_EN = 0.
 *
 */
void rkh_sma_get_info(RKH_SMA_T *me, RKH_SMAI_T *psi);

/**
 *  \brief
 *  Clear performance information for a particular state machine application
 *  (SMA) as known as active object.
 *
 *  \param[in] me  pointer to previously created state machine application.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_SMA_GET_INFO_EN = 0.
 */
void rkh_sma_clear_info(RKH_SMA_T *me);

/**
 *  \brief
 *  Registers a state machine application (SMA) as known as active object into
 *  the framework, which implies to store a pointer to the SMA in the priority
 *  table.
 *
 *  \param[in] me  pointer to previously created state machine application.
 */
void rkh_sma_register(RKH_SMA_T *me);

/**
 *  \brief
 *	Removes the SMA as known as active object from the priority table, and
 *	thus from the framework, by simply replacing the link to the SMA being
 *	deleted with a NULL pointer.
 *
 *  \param[in] me  pointer to previously created state machine application.
 */
void rkh_sma_unregister(RKH_SMA_T *me);

/**
 *  \brief
 *  Initializes the virtual table of the active object instance and calls the 
 *  constructor operation of its base class.
 *
 *  \param[in] me   pointer to previously created state machine application.
 *  \param[in] vtbl pointer to virtual table. Define it as null to use the 
 *                  default virtual table, rkhSmaVtbl.
 *
 *  \note
 *  The initializer assumes that memory has previously been allocated for the 
 *  object (either statically or dynamically).
 */
void rkh_sma_ctor(RKH_SMA_T *me, const RKHSmaVtbl *vtbl);

/**
 *  \brief
 *	Defer an event to a given separate event queue.
 *
 *  Event deferral comes in very handy when an event arrives in a
 *  particularly inconvenient moment but can be deferred for some later time,
 *  when the system is in a much better position to handle the event. RKH
 *  supports very efficient event deferring and recalling mechanisms.
 *  This function is part of the event deferral mechanism. An SMA
 *  uses this function to defer an event \a e to the event queue \a q.
 *  RKH correctly accounts for another outstanding reference to the event
 *  and will not recycle the event at the end of the RTC step.
 *  Later, the SMA might recall one event at a time from the
 *  event queue by means of rkh_fwk_recall() function.
 *
 *  \param[in] q    pointer to previously created queue.
 *  \param[in] e    pointer to event.
 *
 *	\note
 *	For memory efficiency and best performance the deferred event queue,
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *  An SMA can use multiple event queues to defer events of
 *  different kinds.
 *	The assertion inside it guarantee that operation is valid, so is not
 *	necessary to check the value returned from it.
 *
 *  \usage
 *	\code
 *	static RKH_RQ_T qurc;
 *	static RKH_EVT_T *qurc_sto[ MAX_SIZEOF_QURC ];
 *
 *	rkh_rq_init( &qurc, qurc_sto, MAX_SIZEOF_QURC, NULL );
 *	...
 *
 *	void
 *	ring( const struct rkh_t *me, RKH_EVT_T *pe )
 *	{
 *		(void)me;                  // argument not used
 *		rkh_fwk_defer( &qurc, pe );	// defer event
 *	}
 *	\endcode
 */
void rkh_fwk_defer(RKH_RQ_T *q, const RKH_EVT_T *e);

/**
 *  \brief
 *  Recall a deferred event from a given event queue.
 *
 *  This function is part of the event deferral support. An SMA
 *  uses this function to recall a deferred event from a given event queue.
 *  Recalling an event means that it is removed from the deferred event
 *  queue \a q and posted (LIFO) to the event queue of the \a me state
 *  machine application.
 *
 *  \note
 *	For memory efficiency and best performance the destination event queue,
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *
 *  \return     The pointer to the recalled event to the caller, or NULL if no
 *              event has been recalled.
 *
 *  \usage
 *	\code
 *	void
 *	exit_rx_manager( const struct rkh_t *me )
 *	{
 *		rkh_fwk_recall( me, &qurc );
 *	}
 *	\endcode
 *
 */
RKH_EVT_T *rkh_fwk_recall(RKH_SMA_T *me, RKH_RQ_T *q);

/**
 *  \brief
 *  Registers a new event pool into the event pool list.
 *
 *  Before using dynamic events (or event with arguments) the application
 *  code must register the event pools, which stores the events as a
 *  fixed-sized memory block. Each event pool must be registered with the
 *  RKH framework, by means of the rkh_fwk_epool_register() function.
 *
 *	This function initializes one event pool at a time and must be called
 *  exactly once for each event pool before the pool can be used.
 *
 *  The application code might initialize the event pools by making calls
 *  to the rkh_fwk_epool_register() function. However, for the simplicity of
 *  the internal implementation, the application code initialize event pools
 *  in the ascending order of the event size.
 *
 *  Many RTOSes provide fixed block-size heaps, a.k.a. memory pools that can
 *  be adapted for RKH event pools. In case such support is missing, RKH
 *  provides a native RKH event pool implementation. The macro
 *  #RKH_DYNE_TYPE determines the type of event pool used by a particular
 *  RKH port. See structure RKH_MP_T for more information.
 *
 *  For adapting RKH event pools to any fixed-size memory block service RTOS
 *  provided the application code must define RKH_DYNE_TYPE, RKH_DYNE_INIT(),
 *  RKH_DYNE_GET_ESIZE(), RKH_DYNE_GET(), RKH_DYNE_PUT(), RKH_DYNE_GET_NUSED(),
 *  RKH_DYNE_GET_NMIN(), and RKH_DYNE_GET_PSIZE() macros.
 *
 *  The dynamic allocation of events is optional then if the
 *  #RKH_CFGPORT_NATIVE_DYN_EVT_EN is set to 1 and the native fixed-size
 *  memory block facility is enabled (see #RKH_CFG_MP_EN) then RKH will
 *  include its own implementation of dynamic memory management.
 *  When #RKH_CFGPORT_NATIVE_DYN_EVT_EN is enabled RKH also will
 *  automatically define RKH_DYNE_TYPE, RKH_DYNE_INIT(),
 *  RKH_DYNE_GET_ESIZE(), RKH_DYNE_GET(), RKH_DYNE_PUT(), RKH_DYNE_GET_NUSED(),
 *  RKH_DYNE_GET_NMIN(), and RKH_DYNE_GET_PSIZE() macros.
 *
 *  \param[in] sstart   storage start. Pointer to memory from which memory 
 *                      blocks are allocated.
 *  \param[in] ssize:	storage size. Size of the memory pool storage in bytes.
 *  \param[in] esize	event size. This number determines the size of each 
 *                      memory block in the pool.
 *
 *  \usage
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
 *  ...
 *  rkh_fwk_epool_register( ep0sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
 *  rkh_fwk_epool_register( ep1sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
 *  rkh_fwk_epool_register( ep2sto, SIZEOF_EP2STO, SIZEOF_EP2_BLOCK  );
 *  ...
 *	\endcode
 */
void rkh_fwk_epool_register(void *sstart, rui32_t ssize, RKH_ES_T esize);

/**
 *  \brief
 *  Allocates an event from the previously created event pool.
 *
 *  \param[in] esize    size of event [in bytes].
 *  \param[in] e        event signal.
 *  \param[in] sender	pointer to the actor that request a memory block. It is not 
 *                      necessarily a pointer to an active object. In fact, if 
 *                      RKH_ALLOC_EVT() is called from an interrupt or 
 *                      other context, it can create a unique object just to 
 *                      unambiguously identify the publisher of the event.
 *
 *  \note
 *  This function is internal to RKH and the user application should not call 
 *  it. Instead, use #RKH_ALLOC_EVT() macro.
 *
 *  \sa rkh_put_fifo(), rkh_put_lifo(), rkh_alloc_event(),
 *  rkh_set_static_event() and rkh_fwk_gc().
 */

RKH_EVT_T *rkh_fwk_ae(RKH_ES_T esize, RKH_SIG_T e, const void *const sender);

/**
 *  \brief
 *  Recycle a dynamic event.
 *
 *  \param[in] e        Event signal.
 *  \param[in] sender   Pointer to the actor that request a memory block. 
 *                      It is not necessarily a pointer to an active 
 *                      object. In fact, if RKH_FWK_GC() is called from 
 *                      an interrupt or other context, it can create a 
 *                      unique object just to unambiguously identify the 
 *                      publisher of the event.
 */
#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
void rkh_fwk_gc(RKH_EVT_T *e, const void *const sender);
#endif

/**
 *  \brief
 *  Reserve the dynamic event to be recycled.
 *
 *  \param[in] e    event signal.
 */
#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
void rkh_fwk_reserve(RKH_EVT_T *e);
#endif

/**
 *  \brief
 *  When dispatching an event to a SMA the dispatch hook function will be
 *  executed.
 *
 *  \param[in] me  pointer to previously created state machine application.
 *	\param[in] e    pointer to arrived event.
 *
 *	\note
 *	The dispatch hook will only get called if RKH_CFG_HOOK_DISPATCH_EN is
 *	set to 1 within rkhcfg.h file. When this is set the application must
 *	provide the hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_dispatch(RKH_SMA_T *me, RKH_EVT_T *e);

/**
 *  \brief
 *  When the producer of an event directly posts the event to the event queue
 *  of the consumer SMA the rkh_hook_signal() will optionally called.
 *
 *	\param[in] e    pointer to arrived event.
 *
 *	\note
 *	The signal hook will only get called if RKH_CFG_HOOK_SIGNAL_EN is set
 *	to 1 within rkhcfg.h file. When this is set the application must provide
 *	the hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_signal(RKH_EVT_T *e);

/**
 *  \brief
 *  If a timer expires the rkh_hook_timeout() function is called just before
 *  the assigned event is directly posted into the state machine application
 *  queue.
 *
 *	\param[in] t    pointer to previously allocated timer structure.
 *					A cast to RKH_TMR_T data type must be internally
 *					implemented to get the appropiated timer control block.
 *
 *	\note
 *	The timeout hook will only get called if RKH_CFG_HOOK_TIMEOUT_EN is set
 *	to 1 within rkhcfg.h file. When this is set the application must provide
 *	the hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_timeout(const void *t);

/**
 *  \brief
 *  This hook function is called just before the RKH takes over control of
 *  the application.
 *
 *	\note
 *	The start hook will only get called if RKH_CFG_HOOK_START_EN is set to 1
 *	within rkhcfg.h file. When this is set the application must provide the
 *	hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_start(void);

/**
 *  \brief
 *  This hook function is called just before the RKH returns to the
 *  underlying OS/RTOS. Usually, the rkh_hook_exit() is useful when executing
 *  clean-up code upon SMA terminate or framework exit.
 *
 *	\note
 *	The exit hook will only get called if RKH_CFG_HOOK_EXIT_EN is set to 1
 *	within rkhcfg.h file. When this is set the application must provide the
 *	hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_exit(void);

/**
 *  \brief
 *  An idle hook function will only get executed (with interrupts LOCKED)
 *  when there are no SMAs of higher priority that are ready to run.
 *
 *  This makes the idle hook function an ideal place to put the processor
 *  into a low power state - providing an automatic power saving whenever
 *  there is no processing to be performed.
 *
 *  \note
 *	The rkh_hook_idle() callback is called with interrupts locked, because the
 *	determination of the idle condition might change by any interrupt posting
 *	an event. This function must internally unlock interrupts, ideally
 *	atomically with putting the CPU to the power-saving mode.
 *
 *  \usage
 *	\code
 *	void
 *	rkh_hook_idle( void )       // NOTE: entered with interrupts DISABLED
 *	{
 *		RKH_ENA_INTERRUPT();	// must at least enable interrupts
 *		...
 *	}
 *	\endcode
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_idle(void);

/**
 *  \brief
 *  This function is called by rkh_tmr_tick(), which is assumed to be called
 *  from an ISR. rkh_hook_timetick() is called at the very beginning of
 *  rkh_tmr_tick(), to give priority to user or port-specific code when the
 *  tick interrupt occurs.
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
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_timetick(void);

/**
 *  \brief
 *  This function is called from rkh_trc_end() function, at the end of that, 
 *  to allow to the application to extend the functionality of RKH, giving 
 *  the port developer the opportunity to add code that will be called when 
 *  is put a trace event into the stream buffer.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_putTrcEvt(void);

/**
 *  \brief
 *  Inits a previously created state machine calling its initializing action.
 *
 *  \param[in] me  pointer to previously created state machine.
 *
 *  \ingroup apiSM
 */
void rkh_sm_init(RKH_SM_T *me);

/**
 *  \brief
 *	Executes a state machine in a run-to-completation (RTC) model.
 *
 *	In this model, before the system handles a new event it can store it
 *	until the previous event has completed processing. This model is
 *	called run to completion or RTC. Thus, the system processes events in
 *	discrete, indivisible RTC steps. An RTC step is the period of time in
 *	which events are accepted and acted upon. Processing an event always
 *	completes within a single model step, including exiting the source
 *	state, executing any associated actions, and entering the target state.
 *  The RKH implementation preserves the transition sequence imposed by
 *  Harel's Statechart and UML. Specifically, the implemented transition
 *  sequence is as follows:
 *
 *  - Execute exit actions of the source state.
 *  - Execute the transition actions.
 *  - Execute entry actions of the target state.
 *
 *  Here now are the details of the main part of this algorithm
 *  (rkh_sm_dispatch()), in which an event is processed by the statechart.
 *
 *  \li	Determine the compound transition (CT) that will fire in response
 *      to the event: traverse the states in the active configuration from
 *      lowest states in the hierarchy upwards. A CT is enabled if its
 *      trigger is the dispatched event, and the guard evaluates to true.
 *      Once an enabled transition is found with a given source state stop
 *      traversing the states that are higher than this state in the
 *      hierarchy.
 *  \li	Perform the CT that we found should fire.
 *      For each transition do:
 *      -	Update histories of exited states.
 *      -   Perform the exit actions of the exited states according to the
 *          order states are exited, from low state to high state.
 *      -	Perform the actions on the CT sequentially according to the
 *          order in which they are written on the transition, from the
 *          action closest to source state to the action closest to target
 *          state.
 *      -	Perform the entry actions of the entered states according to
 *          the order states are entered, from high state to low state.
 *      -	For lowest level states that were entered, which are not basic
 *          states, perform default transitions (recursively) until the
 *          statechart reaches basic states.
 *      -	Update the active configuration.
 *  \li	Wrap up: once a stable configuration is reached, the reaction to the
 *      event is completed, control returns to the dispatcher and new events
 *      can be dispatched.
 *
 *  \param[in] me   pointer to previously created state machine application.
 *	\param[in] e	pointer to arrived event. It's used as state-machine's
 *					input alphabet.
 *
 *	\return         Result #RKH_RCODE_T code.
 *
 *  \ingroup apiSM
 */
ruint rkh_sm_dispatch(RKH_SM_T *me, RKH_EVT_T *e);

/**
 *  \brief
 *  Initializes the attributes of the state machine instance.
 *
 *  \param[in] me  pointer to previously created state machine.
 *
 *  \note
 *  The initializer assumes that memory has previously been allocated for the 
 *  object (either statically or dynamically).
 *
 *  \ingroup apiSM
 */
void rkh_sm_ctor(RKH_SM_T *me);

/**
 *  \brief
 *  Erase the history of a state. It can be a shallow or deep history.
 *
 *  \param[in] h    pointer to history pseudostate.
 *
 *  \ingroup apiSM
 */
#if defined(RKH_HISTORY_ENABLED)
void rkh_sm_clear_history(RKHROM RKH_SHIST_T *h);
#else
#define rkh_sm_clear_history(h)          (void)0
#endif

/**
 *  \brief
 *  Open the tracing session.
 *
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
void rkh_trc_open(void);
#endif

/**
 *  \brief
 *	Close the tracing session.
 *
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
void rkh_trc_close(void);
#endif

/**
 *  \brief
 *	Platform-dependent macro flushing the trace stream.
 *
 *	\ingroup apiBSPTrc
 */
#if RKH_CFG_TRC_EN == RKH_ENABLED
void rkh_trc_flush(void);
#endif

/**
 *  \brief
 *	Retrieves a timestamp to be placed in a trace event.
 *
 *	This function is application-specific and the user needs to define it.
 *	The data returned is defined in compile-time by means of
 *	RKH_SIZEOF_TSTAMP.
 *
 *  \return     Timestamp (RKH_TS_T data type).
 *
 *  \sa \b rkhtrc.h file.
 *
 *  \usage
 *	\code
 *	RKH_TS_T
 *	rkh_trc_getts( void )
 *	{
 *		return ( RKH_TS_T )clock();
 *	}
 *	\endcode
 *
 *	\ingroup apiBSPTrc
 */
RKH_TS_T rkh_trc_getts(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
