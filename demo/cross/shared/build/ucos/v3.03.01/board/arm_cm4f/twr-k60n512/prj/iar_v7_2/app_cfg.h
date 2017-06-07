/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                              (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      APPLICATION CONFIGURATION
*
*                                        Freescale Kinetis K60
*                                               on the
*
*                                        Freescale TWR-K60N512
*                                          Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

#ifndef  APP_CFG_MODULE_PRESENT
#define  APP_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  APP_CFG_SERIAL_EN                          DEF_DISABLED


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                    2u


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_STK_SIZE                128u


/*
*********************************************************************************************************
*                                          SERIAL CONFIGURATION
*********************************************************************************************************
*/

#define  BSP_CFG_SER_COMM_SEL                       BSP_SER_COMM_UART_03


/*
*********************************************************************************************************
*                                       TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/
#if 0
#define  TRACE_LEVEL_OFF                            0
#define  TRACE_LEVEL_INFO                           1
#define  TRACE_LEVEL_DBG                            2
#endif 

#define  APP_CFG_TRACE_LEVEL                        TRACE_LEVEL_DBG
#define  APP_CFG_TRACE                              BSP_Ser_Printf

#define  BSP_CFG_TRACE_LEVEL                        TRACE_LEVEL_OFF
#define  BSP_CFG_TRACE                              BSP_Ser_Printf               

#define  APP_TRACE_INFO(x)               ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG)   ? (void)(APP_CFG_TRACE x) : (void)0)

#define  BSP_TRACE_INFO(x)               ((BSP_CFG_TRACE_LEVEL  >= TRACE_LEVEL_INFO) ? (void)(BSP_CFG_TRACE x) : (void)0)
#define  BSP_TRACE_DBG(x)                ((BSP_CFG_TRACE_LEVEL  >= TRACE_LEVEL_DBG)  ? (void)(BSP_CFG_TRACE x) : (void)0)

#endif
