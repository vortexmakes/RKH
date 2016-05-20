/*
*********************************************************************************************************
*                                                uC/LIB
*                                        CUSTOM LIBRARY MODULES
*
*                          (c) Copyright 2004-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/LIB is provided in source form to registered licensees ONLY.  It is 
*               illegal to distribute this source code to any third party unless you receive 
*               written permission by an authorized Micrium representative.  Knowledge of 
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest 
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                  CUSTOM LIBRARY CONFIGURATION FILE
*
*                                        Freescale Kinetis K60
*                                               on the
*
*                                        Freescale TWR-K60N512
*                                          Evaluation Board
*
* Filename      : lib_cfg.h
* Version       : V1.35.00
* Programmer(s) : ITJ
*                 DC
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  LIB_CFG_MODULE_PRESENT
#define  LIB_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*                                          uC/LIB CONFIGURATION
*********************************************************************************************************
*/

#define  LIB_MEM_CFG_ARG_CHK_EXT_EN     DEF_DISABLED
                                                        /*   DEF_DISABLED     Argument check DISABLED                   */
                                                        /*   DEF_ENABLED      Argument check ENABLED                    */

#define  LIB_MEM_CFG_OPTIMIZE_ASM_EN    DEF_ENABLED
                                                        /*   DEF_DISABLED     Assembly-optimized function(s) DISABLED   */
                                                        /*   DEF_ENABLED      Assembly-optimized function(s) ENABLED    */

#define  LIB_MEM_CFG_ALLOC_EN           DEF_ENABLED
                                                        /*   DEF_DISABLED     Memory allocation DISABLED                */
                                                        /*   DEF_ENABLED      Memory allocation ENABLED                 */


#define  LIB_MEM_CFG_HEAP_SIZE          2u *  1024u     /* Configure Heap Memory Size                                   */

#define  LIB_STR_CFG_FP_EN              DEF_DISABLED
                                                        /*   DEF_DISABLED     Floating point functions DISABLED         */
                                                        /*   DEF_ENABLED      Floating point functions ENABLED          */

                                                        /* Configure floating point feature(s)' number of ...           */
                                                        /* ... significant digits                                       */
#define  LIB_STR_CFG_FP_MAX_NBR_DIG_SIG         LIB_STR_FP_MAX_NBR_DIG_SIG_DFLT


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                  /* End of lib cfg module include.                               */

