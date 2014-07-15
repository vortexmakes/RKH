/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        BOARD SUPPORT PACKAGE
*
*                                        Freescale Kinetis K60
*                                               on the
*
*                                        Freescale TWR-K60N512
*                                          Evaluation Board
*
* Filename      : bsp_int.c
* Version       : V1.00
* Programmer(s) : JPB
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_INT_MODULE
#include <bsp.h>
#include <bsp_os.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_INT_SRC_NBR                                 120


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

static  CPU_FNCT_VOID  BSP_IntVectTbl[BSP_INT_SRC_NBR];


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_IntHandler      (CPU_DATA  int_id);
static  void  BSP_IntHandlerDummy (void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              BSP_IntClr()
*
* Description : Clear interrupt.
*
* Argument(s) : int_id      Interrupt to clear.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) An interrupt does not need to be cleared within the interrupt controller.
*********************************************************************************************************
*/

void  BSP_IntClr (CPU_DATA  int_id)
{

}


/*
*********************************************************************************************************
*                                              BSP_IntDis()
*
* Description : Disable interrupt.
*
* Argument(s) : int_id      Interrupt to disable.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntDis (CPU_DATA  int_id)
{
    if (int_id < BSP_INT_SRC_NBR) {
        CPU_IntSrcDis(int_id + 16);
    }
}


/*
*********************************************************************************************************
*                                           BSP_IntDisAll()
*
* Description : Disable ALL interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{
    CPU_IntDis();
}


/*
*********************************************************************************************************
*                                               BSP_IntEn()
*
* Description : Enable interrupt.
*
* Argument(s) : int_id      Interrupt to enable.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntEn (CPU_DATA  int_id)
{
    if (int_id < BSP_INT_SRC_NBR) {
        CPU_IntSrcEn(int_id);
    }
}


/*
*********************************************************************************************************
*                                            BSP_IntVectSet()
*
* Description : Assign ISR handler.
*
* Argument(s) : int_id      Interrupt for which vector will be set.
*
*               isr         Handler to assign
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntVectSet (CPU_DATA       int_id,
                      CPU_FNCT_VOID  isr)
{
    CPU_SR_ALLOC();


    if (int_id < BSP_INT_SRC_NBR) {
        CPU_CRITICAL_ENTER();
        BSP_IntVectTbl[int_id] = isr;
        CPU_CRITICAL_EXIT();
    }
}


/*
*********************************************************************************************************
*                                            BSP_IntPrioSet()
*
* Description : Assign ISR priority.
*
* Argument(s) : int_id      Interrupt for which vector will be set.
*
*               prio        Priority to assign
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntPrioSet (CPU_DATA    int_id,
                      CPU_INT08U  prio)
{
    CPU_SR_ALLOC();


    if (int_id < BSP_INT_SRC_NBR) {
        CPU_CRITICAL_ENTER();
        CPU_IntSrcPrioSet(int_id + 16, prio);
        CPU_CRITICAL_EXIT();
    }
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           INTERNAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              BSP_IntInit()
*
* Description : Initialize interrupts:
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntInit (void)
{
    CPU_DATA  int_id;


    for (int_id = 0; int_id < BSP_INT_SRC_NBR; int_id++) {
        BSP_IntVectSet(int_id, BSP_IntHandlerDummy);
    }
}


/*
*********************************************************************************************************
*                                        BSP_IntHandler####()
*
* Description : Handle an interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntHandlerInitialStackPointer     (void)  { BSP_IntHandler(BSP_INT_ID_INITIAL_STACK_POINTER);     }
void  BSP_IntHandlerInitialProgramCounter   (void)  { BSP_IntHandler(BSP_INT_ID_INITIAL_PROGRAM_COUNTER);   }
void  BSP_IntHandlerNMI                     (void)  { BSP_IntHandler(BSP_INT_ID_NMI);                       }
void  BSP_IntHandlerHardFault               (void)  { BSP_IntHandler(BSP_INT_ID_HARD_FAULT);                }
void  BSP_IntHandlerReserved4               (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED4);                 }
void  BSP_IntHandlerBusFault                (void)  { BSP_IntHandler(BSP_INT_ID_BUS_FAULT);                 }
void  BSP_IntHandlerUsageFault              (void)  { BSP_IntHandler(BSP_INT_ID_USAGE_FAULT);               }
void  BSP_IntHandlerReserved7               (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED7);                 }
void  BSP_IntHandlerReserved8               (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED8);                 }
void  BSP_IntHandlerReserved9               (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED9);                 }
void  BSP_IntHandlerReserved10              (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED10);                }
void  BSP_IntHandlerSVCall                  (void)  { BSP_IntHandler(BSP_INT_ID_SVCALL);                    }
void  BSP_IntHandlerDebugMonitor            (void)  { BSP_IntHandler(BSP_INT_ID_DEBUG_MONITOR);             }
void  BSP_IntHandlerReserved13              (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED13);                }
void  BSP_IntHandlerPendableSrvReq          (void)  { BSP_IntHandler(BSP_INT_ID_PENDABLE_SRV_REQ);          }
void  BSP_IntHandlerSysTick                 (void)  { BSP_IntHandler(BSP_INT_ID_SYSTICK);                   }
void  BSP_IntHandlerDMA0                    (void)  { BSP_IntHandler(BSP_INT_ID_DMA0);                      }
void  BSP_IntHandlerDMA1                    (void)  { BSP_IntHandler(BSP_INT_ID_DMA1);                      }
void  BSP_IntHandlerDMA2                    (void)  { BSP_IntHandler(BSP_INT_ID_DMA2);                      }
void  BSP_IntHandlerDMA3                    (void)  { BSP_IntHandler(BSP_INT_ID_DMA3);                      }
void  BSP_IntHandlerDMA4                    (void)  { BSP_IntHandler(BSP_INT_ID_DMA4);                      }
void  BSP_IntHandlerDMA5                    (void)  { BSP_IntHandler(BSP_INT_ID_DMA5);                      }
void  BSP_IntHandlerDMA6                    (void)  { BSP_IntHandler(BSP_INT_ID_DMA6);                      }
void  BSP_IntHandlerDMA7                    (void)  { BSP_IntHandler(BSP_INT_ID_DMA7);                      }
void  BSP_IntHandlerDMA8                    (void)  { BSP_IntHandler(BSP_INT_ID_DMA8);                      }
void  BSP_IntHandlerDMA9                    (void)  { BSP_IntHandler(BSP_INT_ID_DMA9);                      }
void  BSP_IntHandlerDMA10                   (void)  { BSP_IntHandler(BSP_INT_ID_DMA10);                     }
void  BSP_IntHandlerDMA11                   (void)  { BSP_IntHandler(BSP_INT_ID_DMA11);                     }
void  BSP_IntHandlerDMA12                   (void)  { BSP_IntHandler(BSP_INT_ID_DMA12);                     }
void  BSP_IntHandlerDMA13                   (void)  { BSP_IntHandler(BSP_INT_ID_DMA13);                     }
void  BSP_IntHandlerDMA14                   (void)  { BSP_IntHandler(BSP_INT_ID_DMA14);                     }
void  BSP_IntHandlerDMA15                   (void)  { BSP_IntHandler(BSP_INT_ID_DMA15);                     }
void  BSP_IntHandlerDMAError                (void)  { BSP_IntHandler(BSP_INT_ID_DMA_ERROR);                 }
void  BSP_IntHandlerMCM                     (void)  { BSP_IntHandler(BSP_INT_ID_MCM);                       }
void  BSP_IntHandlerFTFL                    (void)  { BSP_IntHandler(BSP_INT_ID_FTFL);                      }
void  BSP_IntHandlerReadCollision           (void)  { BSP_IntHandler(BSP_INT_ID_READ_COLLISION);            }
void  BSP_IntHandlerLVDLVW                  (void)  { BSP_IntHandler(BSP_INT_ID_LVD_LVW);                   }
void  BSP_IntHandlerLLW                     (void)  { BSP_IntHandler(BSP_INT_ID_LLW);                       }
void  BSP_IntHandlerWatchdog                (void)  { BSP_IntHandler(BSP_INT_ID_WATCHDOG);                  }
void  BSP_IntHandlerRNGB                    (void)  { BSP_IntHandler(BSP_INT_ID_RNGB);                      }
void  BSP_IntHandlerI2C0                    (void)  { BSP_IntHandler(BSP_INT_ID_I2C0);                      }
void  BSP_IntHandlerI2C1                    (void)  { BSP_IntHandler(BSP_INT_ID_I2C1);                      }
void  BSP_IntHandlerSPI0                    (void)  { BSP_IntHandler(BSP_INT_ID_SPI0);                      }
void  BSP_IntHandlerSPI1                    (void)  { BSP_IntHandler(BSP_INT_ID_SPI1);                      }
void  BSP_IntHandlerSPI2                    (void)  { BSP_IntHandler(BSP_INT_ID_SPI2);                      }
void  BSP_IntHandlerCAN0ORedMessageBuffer   (void)  { BSP_IntHandler(BSP_INT_ID_CAN0_ORED_MESSAGE_BUFFER);  }
void  BSP_IntHandlerCAN0BusOff              (void)  { BSP_IntHandler(BSP_INT_ID_CAN0_BUS_OFF);              }
void  BSP_IntHandlerCAN0Error               (void)  { BSP_IntHandler(BSP_INT_ID_CAN0_ERROR);                }
void  BSP_IntHandlerCAN0TxWarning           (void)  { BSP_IntHandler(BSP_INT_ID_CAN0_TX_WARNING);           }
void  BSP_IntHandlerCAN0RxWarning           (void)  { BSP_IntHandler(BSP_INT_ID_CAN0_RX_WARNING);           }
void  BSP_IntHandlerCAN0WakeUp              (void)  { BSP_IntHandler(BSP_INT_ID_CAN0_WAKE_UP);              }
void  BSP_IntHandlerCAN0IMEU                (void)  { BSP_IntHandler(BSP_INT_ID_CAN0_IMEU);                 }
void  BSP_IntHandlerCAN0LostRx              (void)  { BSP_IntHandler(BSP_INT_ID_CAN0_LOST_RX);              }
void  BSP_IntHandlerCAN1ORedMessageBuffer   (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_ORED_MESSAGE_BUFFER);  }
void  BSP_IntHandlerCAN1BusOff              (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_BUS_OFF);              }
void  BSP_IntHandlerCAN1Error               (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_ERROR);                }
void  BSP_IntHandlerCAN1TxWarning           (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_TX_WARNING);           }
void  BSP_IntHandlerCAN1RxWarning           (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_RX_WARNING);           }
void  BSP_IntHandlerCAN1WakeUp              (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_WAKE_UP);              }
void  BSP_IntHandlerCAN1IMEU                (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_IMEU);                 }
void  BSP_IntHandlerCAN1LostRx              (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_LOST_RX );             }
void  BSP_IntHandlerUART0RxTx               (void)  { BSP_IntHandler(BSP_INT_ID_UART0_RX_TX);               }
void  BSP_IntHandlerUART0Err                (void)  { BSP_IntHandler(BSP_INT_ID_UART0_ERR);                 }
void  BSP_IntHandlerUART1RxTx               (void)  { BSP_IntHandler(BSP_INT_ID_UART1_RX_TX);               }
void  BSP_IntHandlerUART1Err                (void)  { BSP_IntHandler(BSP_INT_ID_UART1_ERR);                 }
void  BSP_IntHandlerUART2RxTx               (void)  { BSP_IntHandler(BSP_INT_ID_UART2_RX_TX);               }
void  BSP_IntHandlerUART2Err                (void)  { BSP_IntHandler(BSP_INT_ID_UART2_ERR);                 }
void  BSP_IntHandlerUART3RxTx               (void)  { BSP_IntHandler(BSP_INT_ID_UART3_RX_TX);               }
void  BSP_IntHandlerUART3Err                (void)  { BSP_IntHandler(BSP_INT_ID_UART3_ERR);                 }
void  BSP_IntHandlerUART4RxTx               (void)  { BSP_IntHandler(BSP_INT_ID_UART4_RX_TX);               }
void  BSP_IntHandlerUART4Err                (void)  { BSP_IntHandler(BSP_INT_ID_UART4_ERR);                 }
void  BSP_IntHandlerUART5RxTx               (void)  { BSP_IntHandler(BSP_INT_ID_UART5_RX_TX);               }
void  BSP_IntHandlerUART5Err                (void)  { BSP_IntHandler(BSP_INT_ID_UART5_ERR);                 }
void  BSP_IntHandlerADC0                    (void)  { BSP_IntHandler(BSP_INT_ID_ADC0);                      }
void  BSP_IntHandlerADC1                    (void)  { BSP_IntHandler(BSP_INT_ID_ADC1);                      }
void  BSP_IntHandlerHSCMP0                  (void)  { BSP_IntHandler(BSP_INT_ID_HSCMP0);                    }
void  BSP_IntHandlerHSCMP1                  (void)  { BSP_IntHandler(BSP_INT_ID_HSCMP1);                    }
void  BSP_IntHandlerHSCMP2                  (void)  { BSP_IntHandler(BSP_INT_ID_HSCMP2);                    }
void  BSP_IntHandlerFTM0                    (void)  { BSP_IntHandler(BSP_INT_ID_FTM0);                      }
void  BSP_IntHandlerFTM1                    (void)  { BSP_IntHandler(BSP_INT_ID_FTM1);                      }
void  BSP_IntHandlerFTM2                    (void)  { BSP_IntHandler(BSP_INT_ID_FTM2);                      }
void  BSP_IntHandlerCMT                     (void)  { BSP_IntHandler(BSP_INT_ID_CMT);                       }
void  BSP_IntHandlerRTC                     (void)  { BSP_IntHandler(BSP_INT_ID_RTC);                       }
void  BSP_IntHandlerReserved83              (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED83);                }
void  BSP_IntHandlerPIT0                    (void)  { BSP_IntHandler(BSP_INT_ID_PIT0);                      }
void  BSP_IntHandlerPIT1                    (void)  { BSP_IntHandler(BSP_INT_ID_PIT1);                      }
void  BSP_IntHandlerPIT2                    (void)  { BSP_IntHandler(BSP_INT_ID_PIT2);                      }
void  BSP_IntHandlerPIT3                    (void)  { BSP_IntHandler(BSP_INT_ID_PIT3);                      }
void  BSP_IntHandlerPDB0                    (void)  { BSP_IntHandler(BSP_INT_ID_PDB0);                      }
void  BSP_IntHandlerUDB0                    (void)  { BSP_IntHandler(BSP_INT_ID_USB0);                      }
void  BSP_IntHandlerUSBDCD                  (void)  { BSP_IntHandler(BSP_INT_ID_USBDCD);                    }
void  BSP_IntHandlerEnet1588Timer           (void)  { BSP_IntHandler(BSP_INT_ID_ENET_1588_TIMER);           }
void  BSP_IntHandlerEnetTransmit            (void)  { BSP_IntHandler(BSP_INT_ID_ENET_TRANSMIT);             }
void  BSP_IntHandlerEnetReceive             (void)  { BSP_IntHandler(BSP_INT_ID_ENET_RECEIVE);              }
void  BSP_IntHandlerEnetError               (void)  { BSP_IntHandler(BSP_INT_ID_ENET_ERROR);                }
void  BSP_IntHandlerI2S0                    (void)  { BSP_IntHandler(BSP_INT_ID_I2S0);                      }
void  BSP_IntHandlerSDHC                    (void)  { BSP_IntHandler(BSP_INT_ID_SDHC);                      }
void  BSP_IntHandlerDAC0                    (void)  { BSP_IntHandler(BSP_INT_ID_DAC0);                      }
void  BSP_IntHandlerDAC1                    (void)  { BSP_IntHandler(BSP_INT_ID_DAC1);                      }
void  BSP_IntHandlerTSI0                    (void)  { BSP_IntHandler(BSP_INT_ID_TSI0);                      }
void  BSP_IntHandlerMCG                     (void)  { BSP_IntHandler(BSP_INT_ID_MCG);                       }
void  BSP_IntHandlerLPTimer                 (void)  { BSP_IntHandler(BSP_INT_ID_LPTIMER);                   }
void  BSP_IntHandlerReserved102             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED102);               }
void  BSP_IntHandlerPortA                   (void)  { BSP_IntHandler(BSP_INT_ID_PORTA);                     }
void  BSP_IntHandlerPortB                   (void)  { BSP_IntHandler(BSP_INT_ID_PORTB);                     }
void  BSP_IntHandlerPortC                   (void)  { BSP_IntHandler(BSP_INT_ID_PORTC);                     }
void  BSP_IntHandlerPortD                   (void)  { BSP_IntHandler(BSP_INT_ID_PORTD);                     }
void  BSP_IntHandlerPortE                   (void)  { BSP_IntHandler(BSP_INT_ID_PORTE);                     }
void  BSP_IntHandlerReserved108             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED108);               }
void  BSP_IntHandlerReserved109             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED109);               }
void  BSP_IntHandlerReserved110             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED110);               }
void  BSP_IntHandlerReserved111             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED111);               }
void  BSP_IntHandlerReserved112             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED112);               }
void  BSP_IntHandlerReserved113             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED113);               }
void  BSP_IntHandlerReserved114             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED114);               }
void  BSP_IntHandlerReserved115             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED115);               }
void  BSP_IntHandlerReserved116             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED116);               }
void  BSP_IntHandlerReserved117             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED117);               }
void  BSP_IntHandlerReserved118             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED118);               }
void  BSP_IntHandlerReserved119             (void)  { BSP_IntHandler(BSP_INT_ID_RESERVED119);               }


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          BSP_IntHandler()
*
* Description : Central interrupt handler.
*
* Argument(s) : int_id          Interrupt that will be handled.
*
* Return(s)   : none.
*
* Caller(s)   : ISR handlers.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_IntHandler (CPU_DATA  int_id)
{
    CPU_FNCT_VOID  isr;
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();                                       /* Tell the OS that we are starting an ISR            */

    OSIntEnter();

    CPU_CRITICAL_EXIT();

    if (int_id < BSP_INT_SRC_NBR) {
        isr = BSP_IntVectTbl[int_id];
        if (isr != (CPU_FNCT_VOID)0) {
            isr();
        }
    }

    OSIntExit();                                                /* Tell the OS that we are leaving the ISR            */
}


/*
*********************************************************************************************************
*                                        BSP_IntHandlerDummy()
*
* Description : Dummy interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_IntHandlerDummy (void)
{

}
