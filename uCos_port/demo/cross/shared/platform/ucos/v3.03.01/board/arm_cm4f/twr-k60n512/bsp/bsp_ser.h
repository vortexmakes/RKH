/*
*********************************************************************************************************
*                                     MICRIUM BOARD SUPPORT SUPPORT
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        MICIUM BOARD SUPPORT PACKAGE
*                                         SERIAL (UART) INTERFACE
*
*                                        Freescale Kinetis K60
*                                               on the
*
*                                        Freescale TWR-K60N512
*                                          Evaluation Board
*
* Filename      : bsp_ser.h
* Version       : V1.00
* Programmer(s) : EHS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP_SER present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_SER_PRESENT
#define  BSP_SER_PRESENT

#include <bsp.h>
#include <bsp_os.h>
#include <MK60N512VMD100.h>


/*
*********************************************************************************************************
*                                              EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_SER_MODULE
#define  BSP_SER_EXT
#else
#define  BSP_SER  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

#define  BSP_SER_COMM_UART_NONE                0xFF
#define  BSP_SER_COMM_UART_03                     3


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void        BSP_Ser_ISR_Handler     (void);


/*
*********************************************************************************************************
*                                     INTERRUPT CONTROLLER FUNCTIONS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        BACKWARDS COMPATIBILITY
*********************************************************************************************************
*/

#define  Ser_Init           BSP_Ser_Init
#define  Ser_WrByte         BSP_Ser_WrByte
#define  Ser_WrStr          BSP_Ser_WrStr
#define  Ser_RdByte         BSP_Ser_RdByte
#define  Ser_RdStr          BSP_Ser_RdStr
#define  Ser_Printf         BSP_Ser_Printf


/*
*********************************************************************************************************
*                                             RS-232 SERVICES
*********************************************************************************************************
*/


void         BSP_Ser_Init   (CPU_INT32U  baud_rate);

CPU_INT08U   BSP_Ser_RdByte (void);
void         BSP_Ser_RdStr  (CPU_CHAR    *p_str,
                             CPU_INT16U   len);

void         BSP_Ser_WrByte (CPU_INT08U   c);
void         BSP_Ser_WrStr  (CPU_CHAR     *p_str);

void         BSP_Ser_Printf (CPU_CHAR     *format,
                             ...);


/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#ifndef  BSP_CFG_SER_COMM_SEL
#error  "BSP_CFG_SER_COMM_SEL   not  #define'd in 'app_cfg.h'                     "

#elif   (BSP_CFG_SER_COMM_SEL != BSP_SER_COMM_UART_03)

#error  "BSP_CFG_SER_COMM_SEL  illegally #define'd in 'app_cfg.h'                 "
#error  "                                 [MUST be  BSP_SER_COMM_UART_03]         "
#endif


#endif
