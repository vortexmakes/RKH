/*
************************************************************************************************************************
*                                                     uC/OS-III
*                                                The Real-Time Kernel
*
*                                  (c) Copyright 2009-2013; Micrium, Inc.; Weston, FL
*                          All rights reserved.  Protected by international copyright laws.
*
*                                                  APPLICATION HOOKS
*
* File    : OS_APP_HOOKS.H
* By      : JJL
* Version : V3.01.2
*
* LICENSING TERMS:
* ---------------
*               uC/OS-III is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
************************************************************************************************************************
*/

#ifndef  OS_APP_HOOKS_H
#define  OS_APP_HOOKS_H


#ifdef   OS_APP_HOOKS_H_GLOBALS
#define  OS_APP_HOOKS_H_EXT
#else
#define  OS_APP_HOOKS_H_EXT  extern
#endif

/*
************************************************************************************************************************
*                                                 INCLUDE HEADER FILES
************************************************************************************************************************
*/

#include <os.h>

/*
************************************************************************************************************************
*                                                 FUNCTION PROTOTYPES
************************************************************************************************************************
*/

void  App_OS_SetAllHooks   (void);
void  App_OS_ClrAllHooks   (void);


                                                                /* ---------------------- HOOKS --------------------- */
void  App_OS_TaskCreateHook(OS_TCB  *p_tcb);
void  App_OS_TaskDelHook   (OS_TCB  *p_tcb);
void  App_OS_TaskReturnHook(OS_TCB  *p_tcb);

void  App_OS_IdleTaskHook  (void);
void  App_OS_InitHook      (void);
void  App_OS_StatTaskHook  (void);
void  App_OS_TaskSwHook    (void);
void  App_OS_TimeTickHook  (void);

#endif
