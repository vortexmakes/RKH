/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*                                      Application-Defined Task Hooks
*
*                                 (c) Copyright 2013; Micrium; Weston, FL
*                                           All Rights Reserved
*
* File    : APP_HOOKS.C
* By      : Fabiano Kovalski
*         : Eric Shufro
*********************************************************************************************************
*/

#include  <includes.h>

/*
*********************************************************************************************************
*                                          App_TaskCreateHook()
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

#if (OS_APP_HOOKS_EN > 0)
void  App_TaskCreateHook (OS_TCB *ptcb)
{
#if (uC_PROBE_OS_PLUGIN > 0) && (OS_PROBE_HOOKS_EN > 0)
    OSProbe_TaskCreateHook(ptcb);
#else
    (void)ptcb;
#endif
}

/*
*********************************************************************************************************
*                                           App_TaskDelHook()
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void  App_TaskDelHook (OS_TCB *ptcb)
{
    (void)ptcb;
}

/*
*********************************************************************************************************
*                                             App_TaskIdleHook()
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/

void  App_TaskIdleHook (void)
{

}

/*
*********************************************************************************************************
*                                   App_TaskStatHook()
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your
*              application to add functionality to the statistics task.
*
* Returns    : none
*********************************************************************************************************
*/

void  App_TaskStatHook (void)
{
}

/*
*********************************************************************************************************
*                                           App_TaskSwHook()
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

#if OS_TASK_SW_HOOK_EN > 0
void  App_TaskSwHook (void)
{
#if (uC_PROBE_OS_PLUGIN > 0) && (OS_PROBE_HOOKS_EN > 0)
    OSProbe_TaskSwHook();
#endif
}
#endif

/*
*********************************************************************************************************
*                                           App_TCBInitHook()
*
* Description: This function is called by OS_TCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 204
void  App_TCBInitHook (OS_TCB *ptcb)
{
    (void)ptcb;
}
#endif

/*
*********************************************************************************************************
*                                               App_TimeTickHook()
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_TIME_TICK_HOOK_EN > 0
void  App_TimeTickHook (void)
{
#if (uC_PROBE_OS_PLUGIN > 0) && (OS_PROBE_HOOKS_EN > 0)
    OSProbe_TickHook();
#endif
}
#endif


/*$PAGE*/
/*
************************************************************************************************************************
*                                             APPLICATION TASK RETURN HOOK
*
* Description: This function is called if a task accidentally returns.  In other words, a task should either be an
*              infinite loop or delete itself when done.
*
* Arguments  : p_tcb     is a pointer to the OS_TCB of the task that is returning.
*
* Note(s)    : none
************************************************************************************************************************
*/

void  App_TaskReturnHook (OS_TCB  *p_tcb)
{
   (void)&p_tcb;
}


#endif                                                                  /* End of OS_APP_HOOKS_EN                                   */
