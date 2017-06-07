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
*
*                                            STARTUP CODE
*
*                                        Freescale Kinetis K60
*                                               on the
*
*                                        Freescale TWR-K60N512
*                                          Evaluation Board
*
* Filename      : cstartup.c
* Version       : V1.00
* Programmer(s) : JM
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

typedef  union {
    CPU_FNCT_VOID   Fnct;
    void           *Ptr;
} APP_INTVECT_ELEM;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#pragma language=extended
#pragma segment="CSTACK"

static  void  App_NMI_ISR         (void);

static  void  App_Fault_ISR       (void);

static  void  App_BusFault_ISR    (void);

static  void  App_UsageFault_ISR  (void);

static  void  App_Spurious_ISR    (void);

extern  void  __iar_program_start (void);

static void program_start( void );

/*
*********************************************************************************************************
*                                  EXCEPTION / INTERRUPT VECTOR TABLE
*
* Note(s) : (1) The Cortex-M4 may have up to 256 external interrupts, which are the final entries in the
*               vector table.  The K60N512 has 48 external interrupt vectors.
*********************************************************************************************************
*/

__root  const  APP_INTVECT_ELEM  __vector_table[] @ ".intvec" = {
    { .Ptr = (void *)__sfe( "CSTACK" )},                        /* 000 Initial stack pointer.                           */
    program_start,                                        /* 001 Initial program counter.                         */
    App_NMI_ISR,                                                /* 002 Non-maskable interrupt.                          */
    App_Fault_ISR,                                              /* 003 Hard fault exception.                            */
    BSP_IntHandlerReserved4,                                    /* 004 Reserved interrupt 4.                            */
    App_BusFault_ISR,                                           /* 005 Bus fault exception.                             */
    App_UsageFault_ISR,                                         /* 006 Usage fault exception.                           */
    App_Spurious_ISR,                                           /* 007 Reserved interrupt 7.                            */
    App_Spurious_ISR,                                           /* 008 Reserved interrupt 8.                            */
    App_Spurious_ISR,                                           /* 009 Reserved interrupt 9.                            */
    App_Spurious_ISR,                                           /* 010 Reserved interrupt 10.                           */
    App_Spurious_ISR,                                           /* 011 A supervisor call exception.                     */
    App_Spurious_ISR,                                           /* 012 Debug Monitor.                                   */
    App_Spurious_ISR,                                           /* 013 Reserved interrupt 13.                           */
    OS_CPU_PendSVHandler,                                       /* 014 PendSV exception.                                */
    OS_CPU_SysTickHandler,                                      /* 015 SysTick Interrupt.                               */

    BSP_IntHandlerDMA0,                                         /* 016 DMA Channel  0 Transfer Complete.                */
    BSP_IntHandlerDMA1,                                         /* 017 DMA Channel  1 Transfer Complete.                */
    BSP_IntHandlerDMA2,                                         /* 018 DMA Channel  2 Transfer Complete.                */
    BSP_IntHandlerDMA3,                                         /* 019 DMA Channel  3 Transfer Complete.                */
    BSP_IntHandlerDMA4,                                         /* 020 DMA Channel  4 Transfer Complete.                */
    BSP_IntHandlerDMA5,                                         /* 021 DMA Channel  5 Transfer Complete.                */
    BSP_IntHandlerDMA6,                                         /* 022 DMA Channel  6 Transfer Complete.                */
    BSP_IntHandlerDMA7,                                         /* 023 DMA Channel  7 Transfer Complete.                */
    BSP_IntHandlerDMA8,                                         /* 024 DMA Channel  8 Transfer Complete.                */
    BSP_IntHandlerDMA9,                                         /* 025 DMA Channel  9 Transfer Complete.                */
    BSP_IntHandlerDMA10,                                        /* 026 DMA Channel 10 Transfer Complete.                */
    BSP_IntHandlerDMA11,                                        /* 027 DMA Channel 11 Transfer Complete.                */
    BSP_IntHandlerDMA12,                                        /* 028 DMA Channel 12 Transfer Complete.                */
    BSP_IntHandlerDMA13,                                        /* 029 DMA Channel 13 Transfer Complete.                */
    BSP_IntHandlerDMA14,                                        /* 030 DMA Channel 14 Transfer Complete.                */
    BSP_IntHandlerDMA15,                                        /* 031 DMA Channel 15 Transfer Complete.                */
    BSP_IntHandlerDMAError,                                     /* 032 DMA Error Interrupt.                             */

    BSP_IntHandlerMCM,                                          /* 033 Normal Interrupt.                                */
    BSP_IntHandlerFTFL,                                         /* 034 FTFL Interrupt.                                  */
    BSP_IntHandlerReadCollision,                                /* 035 Read Collision Interrupt.                        */
    BSP_IntHandlerLVDLVW,                                       /* 036 Low Voltage Detect, Low Voltage Warning.         */
    BSP_IntHandlerLLW,                                          /* 037 Low Leakage Wakeup.                              */
    BSP_IntHandlerWatchdog,                                     /* 038 WDOG Interrupt.                                  */
    BSP_IntHandlerRNGB,                                         /* 039 RNGB Interrupt.                                  */

    BSP_IntHandlerI2C0,                                         /* 040 I2C0 interrupt.                                  */
    BSP_IntHandlerI2C1,                                         /* 041 I2C1 interrupt.                                  */
    BSP_IntHandlerSPI0,                                         /* 042 SPI0 Interrupt.                                  */
    BSP_IntHandlerSPI1,                                         /* 043 SPI1 Interrupt.                                  */
    BSP_IntHandlerSPI2,                                         /* 044 SPI2 Interrupt.                                  */

    BSP_IntHandlerCAN0ORedMessageBuffer,                        /* 045 CAN0 OR'd Message Buffers Interrupt.             */
    BSP_IntHandlerCAN0BusOff,                                   /* 046 CAN0 Bus Off Interrupt.                          */
    BSP_IntHandlerCAN0Error,                                    /* 047 CAN0 Error Interrupt.                            */
    BSP_IntHandlerCAN0TxWarning,                                /* 048 CAN0 Tx Warning Interrupt.                       */
    BSP_IntHandlerCAN0RxWarning,                                /* 049 CAN0 Rx Warning Interrupt.                       */
    BSP_IntHandlerCAN0WakeUp,                                   /* 050 CAN0 Wake Up Interrupt.                          */
    BSP_IntHandlerCAN0IMEU,                                     /* 051 CAN0 Individual Matching Elements Update (IMEU). */
    BSP_IntHandlerCAN0LostRx,                                   /* 052 CAN0 Lost Receive Interrupt.                     */
    BSP_IntHandlerCAN1ORedMessageBuffer,                        /* 053 CAN1 OR'd Message Buffers Interrupt.             */
    BSP_IntHandlerCAN1BusOff,                                   /* 054 CAN1 Bus Off Interrupt.                          */
    BSP_IntHandlerCAN1Error,                                    /* 055 CAN1 Error Interrupt.                            */
    BSP_IntHandlerCAN1TxWarning,                                /* 056 CAN1 Tx Warning Interrupt.                       */
    BSP_IntHandlerCAN1RxWarning,                                /* 057 CAN1 Rx Warning Interrupt.                       */
    BSP_IntHandlerCAN1WakeUp,                                   /* 058 CAN1 Wake Up Interrupt.                          */
    BSP_IntHandlerCAN1IMEU,                                     /* 059 CAN1 Individual Matching Elements Update (IMEU). */
    BSP_IntHandlerCAN1LostRx,                                   /* 060 CAN1 Lost Receive Interrupt.                     */

    BSP_IntHandlerUART0RxTx,                                    /* 061 UART0 Receive/Transmit interrupt.                */
    BSP_IntHandlerUART0Err,                                     /* 062 UART0 Error interrupt.                           */
    BSP_IntHandlerUART1RxTx,                                    /* 063 UART1 Receive/Transmit interrupt.                */
    BSP_IntHandlerUART1Err,                                     /* 064 UART1 Error interrupt.                           */
    BSP_IntHandlerUART2RxTx,                                    /* 065 UART2 Receive/Transmit interrupt.                */
    BSP_IntHandlerUART2Err,                                     /* 066 UART2 Error interrupt.                           */
    BSP_IntHandlerUART3RxTx,                                    /* 067 UART3 Receive/Transmit interrupt.                */
    BSP_IntHandlerUART3Err,                                     /* 068 UART3 Error interrupt.                           */
    BSP_IntHandlerUART4RxTx,                                    /* 069 UART4 Receive/Transmit interrupt.                */
    BSP_IntHandlerUART4Err,                                     /* 070 UART4 Error interrupt.                           */
    BSP_IntHandlerUART5RxTx,                                    /* 071 UART5 Receive/Transmit interrupt.                */
    BSP_IntHandlerUART5Err,                                     /* 072 UART5 Error interrupt.                           */

    BSP_IntHandlerADC0,                                         /* 073 ADC0 interrupt.                                  */
    BSP_IntHandlerADC1,                                         /* 074 ADC1 interrupt.                                  */
    BSP_IntHandlerHSCMP0,                                       /* 075 HSCMP0 interrupt.                                */
    BSP_IntHandlerHSCMP1,                                       /* 076 HSCMP1 interrupt.                                */
    BSP_IntHandlerHSCMP2,                                       /* 077 HSCMP2 interrupt.                                */
    BSP_IntHandlerFTM0,                                         /* 078 FTM0 fault, overflow and channels interrupt.     */
    BSP_IntHandlerFTM1,                                         /* 079 FTM1 fault, overflow and channels interrupt.     */
    BSP_IntHandlerFTM2,                                         /* 080 FTM2 fault, overflow and channels interrupt.     */
    BSP_IntHandlerCMT,                                          /* 081 CMT interrupt.                                   */
    BSP_IntHandlerRTC,                                          /* 082 RTC interrupt.                                   */
    BSP_IntHandlerReserved83,                                   /* 083 Reserved interrupt 83.                           */
    BSP_IntHandlerPIT0,                                         /* 084 PIT timer channel 0 interrupt.                   */
    BSP_IntHandlerPIT1,                                         /* 085 PIT timer channel 1 interrupt.                   */
    BSP_IntHandlerPIT2,                                         /* 086 PIT timer channel 2 interrupt.                   */
    BSP_IntHandlerPIT3,                                         /* 087 PIT timer channel 3 interrupt.                   */
    BSP_IntHandlerPDB0,                                         /* 088 PDB0 Interrupt.                                  */
    BSP_IntHandlerUDB0,                                         /* 089 USB0 interrupt.                                  */
    BSP_IntHandlerUSBDCD,                                       /* 090 USBDCD Interrupt.                                */
    BSP_IntHandlerEnet1588Timer,                                /* 091 Ethernet MAC IEEE 1588 Timer Interrupt.          */
    BSP_IntHandlerEnetTransmit,                                 /* 092 Ethernet MAC Transmit Interrupt.                 */
    BSP_IntHandlerEnetReceive,                                  /* 093 Ethernet MAC Receive Interrupt.                  */
    BSP_IntHandlerEnetError,                                    /* 094 Ethernet MAC Error and miscelaneous Interrupt.   */
    BSP_IntHandlerI2S0,                                         /* 095 I2S0 Interrupt.                                  */
    BSP_IntHandlerSDHC,                                         /* 096 SDHC Interrupt.                                  */
    BSP_IntHandlerDAC0,                                         /* 097 DAC0 interrupt.                                  */
    BSP_IntHandlerDAC1,                                         /* 098 DAC1 interrupt.                                  */
    BSP_IntHandlerTSI0,                                         /* 099 TSI0 Interrupt.                                  */
    BSP_IntHandlerMCG,                                          /* 100 MCG Interrupt.                                   */
    BSP_IntHandlerLPTimer,                                      /* 101 LPTimer interrupt.                               */
    BSP_IntHandlerReserved102,                                  /* 102 Reserved interrupt 102.                          */

    BSP_IntHandlerPortA,                                        /* 103 Port A interrupt.                                */
    BSP_IntHandlerPortB,                                        /* 104 Port B interrupt.                                */
    BSP_IntHandlerPortC,                                        /* 105 Port C interrupt.                                */
    BSP_IntHandlerPortD,                                        /* 106 Port D interrupt.                                */
    BSP_IntHandlerPortE,                                        /* 107 Port E interrupt.                                */

    BSP_IntHandlerReserved108,                                  /* 108 Reserved interrupt 108.                          */
    BSP_IntHandlerReserved109,                                  /* 109 Reserved interrupt 109.                          */
    BSP_IntHandlerReserved110,                                  /* 110 Reserved interrupt 110.                          */
    BSP_IntHandlerReserved111,                                  /* 111 Reserved interrupt 111.                          */
    BSP_IntHandlerReserved112,                                  /* 112 Reserved interrupt 112.                          */
    BSP_IntHandlerReserved113,                                  /* 113 Reserved interrupt 113.                          */
    BSP_IntHandlerReserved114,                                  /* 114 Reserved interrupt 114.                          */
    BSP_IntHandlerReserved115,                                  /* 115 Reserved interrupt 115.                          */
    BSP_IntHandlerReserved116,                                  /* 116 Reserved interrupt 116.                          */
    BSP_IntHandlerReserved117,                                  /* 117 Reserved interrupt 117.                          */
    BSP_IntHandlerReserved118,                                  /* 118 Reserved interrupt 118.                          */
    BSP_IntHandlerReserved119                                   /* 119 Reserved interrupt 119.                          */
};


/********************************************************************/
/*
* Watchdog timer disable routine
*
* Parameters:
* none
*/
void wdog_disable(void)
{
    /* First unlock the watchdog so that we can write to registers */
    /* NOTE: DO NOT SINGLE STEP THROUGH THIS FUNCTION!!! */
    /* There are timing requirements for the execution of the unlock. If
     * you single step through the code you will cause the CPU to reset.
     */
 
    /* This sequence must execute within 20 clock cycles, so disable
         * interrupts will keep the code atomic and ensure the timing.
         */
   
    /* Write 0xC520 to the unlock register */
    WDOG_UNLOCK = 0xC520;
   
    /* Followed by 0xD928 to complete the unlock */
    WDOG_UNLOCK = 0xD928;
   
    /* Clear the WDOGEN bit to disable the watchdog */
    WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
}
 

static void program_start( void )
{
    wdog_disable();
    __iar_program_start();
}

/*
*********************************************************************************************************
*                                            App_NMI_ISR()
*
* Description : Handle Non-Maskable Interrupt (NMI).
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : This is an ISR.
*
* Note(s)     : (1) Since the NMI is not being used, this serves merely as a catch for a spurious
*                   exception.
*********************************************************************************************************
*/

static  void  App_NMI_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}


/*
*********************************************************************************************************
*                                             App_Fault_ISR()
*
* Description : Handle hard fault.
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_Fault_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}


/*
*********************************************************************************************************
*                                           App_BusFault_ISR()
*
* Description : Handle bus fault.
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_BusFault_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}


/*
*********************************************************************************************************
*                                          App_UsageFault_ISR()
*
* Description : Handle usage fault.
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_UsageFault_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}


/*
*********************************************************************************************************
*                                           App_Spurious_ISR()
*
* Description : Handle spurious interrupt.
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_Spurious_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}
