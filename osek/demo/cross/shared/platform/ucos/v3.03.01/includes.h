/*
*********************************************************************************************************
*                                              uC/OS-III
*                                        The Real-Time Kernel
*
*                          (c) Copyright 2004-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/OS-III is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/OS-III in a commercial
*               product you need to contact Micrium to properly license its use in your
*               product.  We provide ALL the source code for your convenience and to
*               help you experience uC/OS-III.  The fact that the source code is provided
*               does NOT mean that you can use it without paying a licensing fee.
*
*               Knowledge of the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                        Freescale Kinetis K60
*                                               on the
*
*                                        Freescale TWR-K60N512
*                                          Evaluation Board
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

#ifndef  INCLUDES_MODULES_PRESENT
#define  INCLUDES_MODULES_PRESENT

/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <math.h>


/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_mem.h>
#include  <lib_str.h>
#include  <lib_ascii.h>
#include  <lib_math.h>


/*
*********************************************************************************************************
*                                              APP / BSP
*********************************************************************************************************
*/

#include  <bsp_twr.h>
#include  <MK60N512VMD100.h>

/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/

#include  <os.h>


/*
*********************************************************************************************************
*                                                SERIAL
*********************************************************************************************************
*/

#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
#include  <bsp_ser.h>
#endif


/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/

#endif
