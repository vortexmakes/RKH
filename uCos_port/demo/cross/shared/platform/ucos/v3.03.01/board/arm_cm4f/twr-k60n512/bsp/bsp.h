/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
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
*                                        BOARD SUPPORT PACKAGE
*
*                                        Freescale Kinetis K60
*                                               on the
*
*                                        Freescale TWR-K60N512
*                                          Evaluation Board
*
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : JPB
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_PRESENT
#define  BSP_PRESENT


/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_MODULE
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include  <stdarg.h>
#include  <stdio.h>

#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_ascii.h>
#include  <lib_def.h>
#include  <lib_mem.h>
#include  <lib_str.h>

#include  <app_cfg.h>


/*
*********************************************************************************************************
*                                           NAME DEFINITIONS
*********************************************************************************************************
*/

#define  BSP_LED_ALL               0
#define  BSP_LED_BLUE              1
#define  BSP_LED_GREEN             2
#define  BSP_LED_YELLOW            3
#define  BSP_LED_ORANGE            4

#define  BSP_PB1                   0
#define  BSP_PB2                   1

#define BSP_CORE_DIV              (1)
#define BSP_BUS_DIV               (2)
#define BSP_FLEXBUS_DIV           (2)
#define BSP_FLASH_DIV             (4)

                                                                /* BSP_CLOCK_MUL from interval 24 - 55                  */
#define BSP_CLOCK_MUL            (48)                           /* BSP_CORE_CLOCK = 96MHz (72-24 = 48 -> Mult. Factor   */

#define REF_CLK                XTAL8
#define CORE_CLK_MHZ           PLL96                            /* 96MHz is only freq tested for a clock input          */


/*
*********************************************************************************************************
*                                          GPIO PIN DEFINITIONS
*********************************************************************************************************
*/

                                                                /* -------------------- GPIOA PINS -------------------- */
#define  BSP_GPIOA_PIN_00                    DEF_BIT_00
#define  BSP_GPIOA_PIN_01                    DEF_BIT_01
#define  BSP_GPIOA_PIN_02                    DEF_BIT_02
#define  BSP_GPIOA_PIN_03                    DEF_BIT_03
#define  BSP_GPIOA_TSI0_CH5                  DEF_BIT_04         /* Electrode 2 @ D16 in the schematics.                 */
#define  BSP_GPIOA_PIN_05                    DEF_BIT_05
#define  BSP_GPIOA_PIN_06                    DEF_BIT_06
#define  BSP_GPIOA_PIN_07                    DEF_BIT_07
#define  BSP_GPIOA_PIN_08                    DEF_BIT_08
#define  BSP_GPIOA_PIN_09                    DEF_BIT_09
#define  BSP_GPIOA_LED_BLUE                  DEF_BIT_10         /* LED Blue   @ D17 in the schematics.                  */
#define  BSP_GPIOA_LED_ORANGE                DEF_BIT_11         /* LED Orange @ D16 in the schematics.                  */
#define  BSP_GPIOA_PIN_12                    DEF_BIT_12
#define  BSP_GPIOA_PIN_13                    DEF_BIT_13
#define  BSP_GPIOA_PIN_14                    DEF_BIT_14
#define  BSP_GPIOA_PIN_15                    DEF_BIT_15
#define  BSP_GPIOA_PIN_16                    DEF_BIT_16
#define  BSP_GPIOA_PIN_17                    DEF_BIT_17
#define  BSP_GPIOA_PIN_18                    DEF_BIT_18
#define  BSP_GPIOA_PIN_19                    DEF_BIT_19         /* Push Button 1 @ SW6 in the schematics.               */
#define  BSP_GPIOA_PIN_20                    DEF_BIT_20
#define  BSP_GPIOA_PIN_21                    DEF_BIT_21
#define  BSP_GPIOA_PIN_22                    DEF_BIT_22
#define  BSP_GPIOA_PIN_23                    DEF_BIT_23
#define  BSP_GPIOA_PIN_24                    DEF_BIT_24
#define  BSP_GPIOA_PIN_25                    DEF_BIT_25
#define  BSP_GPIOA_PIN_26                    DEF_BIT_26
#define  BSP_GPIOA_PIN_27                    DEF_BIT_27
#define  BSP_GPIOA_LED_YELLOW                DEF_BIT_28         /* LED Yellow @ D15 in the schematics.                  */
#define  BSP_GPIOA_LED_GREEN                 DEF_BIT_29         /* LED Green  @ D14 in the schematics.                  */

#define  BSP_GPIO_LEDS                      (BSP_GPIOA_LED_BLUE   | \
                                             BSP_GPIOA_LED_GREEN  | \
                                             BSP_GPIOA_LED_YELLOW | \
                                             BSP_GPIOA_LED_ORANGE)

                                                                /* -------------------- GPIOB PINS -------------------- */
#define  BSP_GPIOB_PIN_00                    DEF_BIT_00
#define  BSP_GPIOB_PIN_01                    DEF_BIT_01
#define  BSP_GPIOB_TSI0_CH7                  DEF_BIT_02         /* TSI0 Channel 7                                       */
#define  BSP_GPIOB_TSI0_CH8                  DEF_BIT_03         /* TSI0 Channel 8                                       */
#define  BSP_GPIOB_PIN_04                    DEF_BIT_04
#define  BSP_GPIOB_PIN_05                    DEF_BIT_05
#define  BSP_GPIOB_PIN_06                    DEF_BIT_06
#define  BSP_GPIOB_PIN_07                    DEF_BIT_07
#define  BSP_GPIOB_PIN_08                    DEF_BIT_08
#define  BSP_GPIOB_PIN_09                    DEF_BIT_09
#define  BSP_GPIOB_PIN_10                    DEF_BIT_10
#define  BSP_GPIOB_PIN_11                    DEF_BIT_11
#define  BSP_GPIOB_PIN_12                    DEF_BIT_12
#define  BSP_GPIOB_PIN_13                    DEF_BIT_13
#define  BSP_GPIOB_PIN_14                    DEF_BIT_14
#define  BSP_GPIOB_PIN_15                    DEF_BIT_15
#define  BSP_GPIOB_TSI0_CH9                  DEF_BIT_16         /* TSI0 Channel 9                                       */
#define  BSP_GPIOB_PIN_17                    DEF_BIT_17
#define  BSP_GPIOB_PIN_18                    DEF_BIT_18
#define  BSP_GPIOB_PIN_19                    DEF_BIT_19
#define  BSP_GPIOB_PIN_20                    DEF_BIT_20
#define  BSP_GPIOB_PIN_21                    DEF_BIT_21
#define  BSP_GPIOB_PIN_22                    DEF_BIT_22
#define  BSP_GPIOB_PIN_23                    DEF_BIT_23

                                                                /* -------------------- GPIOC PINS -------------------- */
#define  BSP_GPIOC_PIN_00                    DEF_BIT_00
#define  BSP_GPIOC_PIN_01                    DEF_BIT_01
#define  BSP_GPIOC_PIN_02                    DEF_BIT_02
#define  BSP_GPIOC_PIN_03                    DEF_BIT_03
#define  BSP_GPIOC_PIN_04                    DEF_BIT_04
#define  BSP_GPIOC_PB1                       DEF_BIT_05
#define  BSP_GPIOC_PIN_06                    DEF_BIT_06
#define  BSP_GPIOC_PIN_07                    DEF_BIT_07
#define  BSP_GPIOC_PIN_08                    DEF_BIT_08
#define  BSP_GPIOC_PIN_09                    DEF_BIT_09
#define  BSP_GPIOC_PIN_10                    DEF_BIT_10
#define  BSP_GPIOC_PIN_11                    DEF_BIT_11
#define  BSP_GPIOC_PIN_12                    DEF_BIT_12
#define  BSP_GPIOC_PB2                       DEF_BIT_13
#define  BSP_GPIOC_PIN_14                    DEF_BIT_14
#define  BSP_GPIOC_PIN_15                    DEF_BIT_15
#define  BSP_GPIOC_PIN_16                    DEF_BIT_16
#define  BSP_GPIOC_PIN_17                    DEF_BIT_17
#define  BSP_GPIOC_PIN_18                    DEF_BIT_18
#define  BSP_GPIOC_PIN_19                    DEF_BIT_19

                                                                /* -------------------- GPIOD PINS -------------------- */
#define  BSP_GPIOD_PIN_00                    DEF_BIT_00
#define  BSP_GPIOD_PIN_01                    DEF_BIT_01
#define  BSP_GPIOD_PIN_02                    DEF_BIT_02
#define  BSP_GPIOD_PIN_03                    DEF_BIT_03
#define  BSP_GPIOD_PIN_04                    DEF_BIT_04
#define  BSP_GPIOD_PIN_05                    DEF_BIT_05
#define  BSP_GPIOD_PIN_06                    DEF_BIT_06
#define  BSP_GPIOD_PIN_07                    DEF_BIT_07
#define  BSP_GPIOD_PIN_08                    DEF_BIT_08
#define  BSP_GPIOD_PIN_09                    DEF_BIT_09
#define  BSP_GPIOD_PIN_10                    DEF_BIT_10
#define  BSP_GPIOD_PIN_11                    DEF_BIT_11
#define  BSP_GPIOD_PIN_12                    DEF_BIT_12
#define  BSP_GPIOD_PIN_13                    DEF_BIT_13
#define  BSP_GPIOD_PIN_14                    DEF_BIT_14
#define  BSP_GPIOD_PIN_15                    DEF_BIT_15

                                                                /* -------------------- GPIOE PINS -------------------- */
#define  BSP_GPIOE_PIN_00                    DEF_BIT_00
#define  BSP_GPIOE_PIN_01                    DEF_BIT_01
#define  BSP_GPIOE_PIN_02                    DEF_BIT_02
#define  BSP_GPIOE_PIN_03                    DEF_BIT_03
#define  BSP_GPIOE_PIN_04                    DEF_BIT_04
#define  BSP_GPIOE_PIN_05                    DEF_BIT_05
#define  BSP_GPIOE_PIN_06                    DEF_BIT_06
#define  BSP_GPIOE_PIN_07                    DEF_BIT_07
#define  BSP_GPIOE_PIN_08                    DEF_BIT_08
#define  BSP_GPIOE_PIN_09                    DEF_BIT_09
#define  BSP_GPIOE_PIN_10                    DEF_BIT_10
#define  BSP_GPIOE_PIN_11                    DEF_BIT_11
#define  BSP_GPIOE_PIN_12                    DEF_BIT_12
#define  BSP_GPIOE_PIN_13                    DEF_BIT_13
#define  BSP_GPIOE_PIN_14                    DEF_BIT_14
#define  BSP_GPIOE_PIN_15                    DEF_BIT_15
#define  BSP_GPIOE_PIN_16                    DEF_BIT_16
#define  BSP_GPIOE_PIN_17                    DEF_BIT_17
#define  BSP_GPIOE_PIN_18                    DEF_BIT_18
#define  BSP_GPIOE_PIN_19                    DEF_BIT_19
#define  BSP_GPIOE_PIN_20                    DEF_BIT_20
#define  BSP_GPIOE_PIN_21                    DEF_BIT_21
#define  BSP_GPIOE_PIN_22                    DEF_BIT_22
#define  BSP_GPIOE_PIN_23                    DEF_BIT_23
#define  BSP_GPIOE_PIN_24                    DEF_BIT_24
#define  BSP_GPIOE_PIN_25                    DEF_BIT_25
#define  BSP_GPIOE_PIN_26                    DEF_BIT_26


/*
*********************************************************************************************************
*                                               INT DEFINES
*********************************************************************************************************
*/

#define  BSP_INT_ID_INITIAL_STACK_POINTER                  0    /* Initial stack pointer                                */
#define  BSP_INT_ID_INITIAL_PROGRAM_COUNTER                1    /* Initial program counter                              */
#define  BSP_INT_ID_NMI                                    2    /* Non-maskable interrupt                               */
#define  BSP_INT_ID_HARD_FAULT                             3    /* Hard fault exception                                 */
#define  BSP_INT_ID_RESERVED4                              4    /* Reserved interrupt 4                                 */
#define  BSP_INT_ID_BUS_FAULT                              5    /* Bus fault exception                                  */
#define  BSP_INT_ID_USAGE_FAULT                            6    /* Usage fault exception                                */
#define  BSP_INT_ID_RESERVED7                              7    /* Reserved interrupt 7                                 */
#define  BSP_INT_ID_RESERVED8                              8    /* Reserved interrupt 8                                 */
#define  BSP_INT_ID_RESERVED9                              9    /* Reserved interrupt 9                                 */
#define  BSP_INT_ID_RESERVED10                            10    /* Reserved interrupt 10                                */
#define  BSP_INT_ID_SVCALL                                11    /* A supervisor call exception                          */
#define  BSP_INT_ID_DEBUG_MONITOR                         12    /* Debug Monitor                                        */
#define  BSP_INT_ID_RESERVED13                            13    /* Reserved interrupt 13                                */
#define  BSP_INT_ID_PENDABLE_SRV_REQ                      14    /* PendSV exception - request for system level service  */
#define  BSP_INT_ID_SYSTICK                               15    /* SysTick Interrupt                                    */
#define  BSP_INT_ID_DMA0                                  16    /* DMA Channel 0 Transfer Complete                      */
#define  BSP_INT_ID_DMA1                                  17    /* DMA Channel 1 Transfer Complete                      */
#define  BSP_INT_ID_DMA2                                  18    /* DMA Channel 2 Transfer Complete                      */
#define  BSP_INT_ID_DMA3                                  19    /* DMA Channel 3 Transfer Complete                      */
#define  BSP_INT_ID_DMA4                                  20    /* DMA Channel 4 Transfer Complete                      */
#define  BSP_INT_ID_DMA5                                  21    /* DMA Channel 5 Transfer Complete                      */
#define  BSP_INT_ID_DMA6                                  22    /* DMA Channel 6 Transfer Complete                      */
#define  BSP_INT_ID_DMA7                                  23    /* DMA Channel 7 Transfer Complete                      */
#define  BSP_INT_ID_DMA8                                  24    /* DMA Channel 8 Transfer Complete                      */
#define  BSP_INT_ID_DMA9                                  25    /* DMA Channel 9 Transfer Complete                      */
#define  BSP_INT_ID_DMA10                                 26    /* DMA Channel 10 Transfer Complete                     */
#define  BSP_INT_ID_DMA11                                 27    /* DMA Channel 11 Transfer Complete                     */
#define  BSP_INT_ID_DMA12                                 28    /* DMA Channel 12 Transfer Complete                     */
#define  BSP_INT_ID_DMA13                                 29    /* DMA Channel 13 Transfer Complete                     */
#define  BSP_INT_ID_DMA14                                 30    /* DMA Channel 14 Transfer Complete                     */
#define  BSP_INT_ID_DMA15                                 31    /* DMA Channel 15 Transfer Complete                     */
#define  BSP_INT_ID_DMA_ERROR                             32    /* DMA Error Interrupt                                  */
#define  BSP_INT_ID_MCM                                   33    /* Normal Interrupt                                     */
#define  BSP_INT_ID_FTFL                                  34    /* FTFL Interrupt                                       */
#define  BSP_INT_ID_READ_COLLISION                        35    /* Read Collision Interrupt                             */
#define  BSP_INT_ID_LVD_LVW                               36    /* Low Voltage Detect, Low Voltage Warning              */
#define  BSP_INT_ID_LLW                                   37    /* Low Leakage Wakeup                                   */
#define  BSP_INT_ID_WATCHDOG                              38    /* WDOG Interrupt                                       */
#define  BSP_INT_ID_RNGB                                  39    /* RNGB Interrupt                                       */
#define  BSP_INT_ID_I2C0                                  40    /* I2C0 interrupt                                       */
#define  BSP_INT_ID_I2C1                                  41    /* I2C1 interrupt                                       */
#define  BSP_INT_ID_SPI0                                  42    /* SPI0 Interrupt                                       */
#define  BSP_INT_ID_SPI1                                  43    /* SPI1 Interrupt                                       */
#define  BSP_INT_ID_SPI2                                  44    /* SPI2 Interrupt                                       */
#define  BSP_INT_ID_CAN0_ORED_MESSAGE_BUFFER              45    /* CAN0 OR'd Message Buffers Interrupt                  */
#define  BSP_INT_ID_CAN0_BUS_OFF                          46    /* CAN0 Bus Off Interrupt                               */
#define  BSP_INT_ID_CAN0_ERROR                            47    /* CAN0 Error Interrupt                                 */
#define  BSP_INT_ID_CAN0_TX_WARNING                       48    /* CAN0 Tx Warning Interrupt                            */
#define  BSP_INT_ID_CAN0_RX_WARNING                       49    /* CAN0 Rx Warning Interrupt                            */
#define  BSP_INT_ID_CAN0_WAKE_UP                          50    /* CAN0 Wake Up Interrupt                               */
#define  BSP_INT_ID_CAN0_IMEU                             51    /* CAN0 Individual Matching Elements Update (IMEU) Int  */
#define  BSP_INT_ID_CAN0_LOST_RX                          52    /* CAN0 Lost Receive Interrupt                          */
#define  BSP_INT_ID_CAN1_ORED_MESSAGE_BUFFER              53    /* CAN1 OR'd Message Buffers Interrupt                  */
#define  BSP_INT_ID_CAN1_BUS_OFF                          54    /* CAN1 Bus Off Interrupt                               */
#define  BSP_INT_ID_CAN1_ERROR                            55    /* CAN1 Error Interrupt                                 */
#define  BSP_INT_ID_CAN1_TX_WARNING                       56    /* CAN1 Tx Warning Interrupt                            */
#define  BSP_INT_ID_CAN1_RX_WARNING                       57    /* CAN1 Rx Warning Interrupt                            */
#define  BSP_INT_ID_CAN1_WAKE_UP                          58    /* CAN1 Wake Up Interrupt                               */
#define  BSP_INT_ID_CAN1_IMEU                             59    /* CAN1 Individual Matching Elements Update (IMEU) Int  */
#define  BSP_INT_ID_CAN1_LOST_RX                          60    /* CAN1 Lost Receive Interrupt                          */
#define  BSP_INT_ID_UART0_RX_TX                           61    /* UART0 Receive/Transmit interrupt                     */
#define  BSP_INT_ID_UART0_ERR                             62    /* UART0 Error interrupt                                */
#define  BSP_INT_ID_UART1_RX_TX                           63    /* UART1 Receive/Transmit interrupt                     */
#define  BSP_INT_ID_UART1_ERR                             64    /* UART1 Error interrupt                                */
#define  BSP_INT_ID_UART2_RX_TX                           65    /* UART2 Receive/Transmit interrupt                     */
#define  BSP_INT_ID_UART2_ERR                             66    /* UART2 Error interrupt                                */
#define  BSP_INT_ID_UART3_RX_TX                           67    /* UART3 Receive/Transmit interrupt                     */
#define  BSP_INT_ID_UART3_ERR                             68    /* UART3 Error interrupt                                */
#define  BSP_INT_ID_UART4_RX_TX                           69    /* UART4 Receive/Transmit interrupt                     */
#define  BSP_INT_ID_UART4_ERR                             70    /* UART4 Error interrupt                                */
#define  BSP_INT_ID_UART5_RX_TX                           71    /* UART5 Receive/Transmit interrupt                     */
#define  BSP_INT_ID_UART5_ERR                             72    /* UART5 Error interrupt                                */
#define  BSP_INT_ID_ADC0                                  73    /* ADC0 interrupt                                       */
#define  BSP_INT_ID_ADC1                                  74    /* ADC1 interrupt                                       */
#define  BSP_INT_ID_HSCMP0                                75    /* HSCMP0 interrupt                                     */
#define  BSP_INT_ID_HSCMP1                                76    /* HSCMP1 interrupt                                     */
#define  BSP_INT_ID_HSCMP2                                77    /* HSCMP2 interrupt                                     */
#define  BSP_INT_ID_FTM0                                  78    /* FTM0 fault, overflow and channels interrupt          */
#define  BSP_INT_ID_FTM1                                  79    /* FTM1 fault, overflow and channels interrupt          */
#define  BSP_INT_ID_FTM2                                  80    /* FTM2 fault, overflow and channels interrupt          */
#define  BSP_INT_ID_CMT                                   81    /* CMT interrupt                                        */
#define  BSP_INT_ID_RTC                                   82    /* RTC interrupt                                        */
#define  BSP_INT_ID_RESERVED83                            83    /* Reserved interrupt 83                                */
#define  BSP_INT_ID_PIT0                                  84    /* PIT timer channel 0 interrupt                        */
#define  BSP_INT_ID_PIT1                                  85    /* PIT timer channel 1 interrupt                        */
#define  BSP_INT_ID_PIT2                                  86    /* PIT timer channel 2 interrupt                        */
#define  BSP_INT_ID_PIT3                                  87    /* PIT timer channel 3 interrupt                        */
#define  BSP_INT_ID_PDB0                                  88    /* PDB0 Interrupt                                       */
#define  BSP_INT_ID_USB0                                  89    /* USB0 interrupt                                       */
#define  BSP_INT_ID_USBDCD                                90    /* USBDCD Interrupt                                     */
#define  BSP_INT_ID_ENET_1588_TIMER                       91    /* Ethernet MAC IEEE 1588 Timer Interrupt               */
#define  BSP_INT_ID_ENET_TRANSMIT                         92    /* Ethernet MAC Transmit Interrupt                      */
#define  BSP_INT_ID_ENET_RECEIVE                          93    /* Ethernet MAC Receive Interrupt                       */
#define  BSP_INT_ID_ENET_ERROR                            94    /* Ethernet MAC Error and miscelaneous Interrupt        */
#define  BSP_INT_ID_I2S0                                  95    /* I2S0 Interrupt                                       */
#define  BSP_INT_ID_SDHC                                  96    /* SDHC Interrupt                                       */
#define  BSP_INT_ID_DAC0                                  97    /* DAC0 interrupt                                       */
#define  BSP_INT_ID_DAC1                                  98    /* DAC1 interrupt                                       */
#define  BSP_INT_ID_TSI0                                  99    /* TSI0 Interrupt                                       */
#define  BSP_INT_ID_MCG                                  100    /* MCG Interrupt                                        */
#define  BSP_INT_ID_LPTIMER                              101    /* LPTimer interrupt                                    */
#define  BSP_INT_ID_RESERVED102                          102    /* Reserved interrupt 102                               */
#define  BSP_INT_ID_PORTA                                103    /* Port A interrupt                                     */
#define  BSP_INT_ID_PORTB                                104    /* Port B interrupt                                     */
#define  BSP_INT_ID_PORTC                                105    /* Port C interrupt                                     */
#define  BSP_INT_ID_PORTD                                106    /* Port D interrupt                                     */
#define  BSP_INT_ID_PORTE                                107    /* Port E interrupt                                     */
#define  BSP_INT_ID_RESERVED108                          108    /* Reserved interrupt 108                               */
#define  BSP_INT_ID_RESERVED109                          109    /* Reserved interrupt 109                               */
#define  BSP_INT_ID_RESERVED110                          110    /* Reserved interrupt 110                               */
#define  BSP_INT_ID_RESERVED111                          111    /* Reserved interrupt 111                               */
#define  BSP_INT_ID_RESERVED112                          112    /* Reserved interrupt 112                               */
#define  BSP_INT_ID_RESERVED113                          113    /* Reserved interrupt 113                               */
#define  BSP_INT_ID_RESERVED114                          114    /* Reserved interrupt 114                               */
#define  BSP_INT_ID_RESERVED115                          115    /* Reserved interrupt 115                               */
#define  BSP_INT_ID_RESERVED116                          116    /* Reserved interrupt 116                               */
#define  BSP_INT_ID_RESERVED117                          117    /* Reserved interrupt 117                               */
#define  BSP_INT_ID_RESERVED118                          118    /* Reserved interrupt 118                               */
#define  BSP_INT_ID_RESERVED119                          119    /* Reserved interrupt 119                               */


/*
*********************************************************************************************************
*                                             PERIPH DEFINES
*********************************************************************************************************
*/

#define  BSP_PERIPH_ID_DMA1                                0
#define  BSP_PERIPH_ID_DMA2                                1
#define  BSP_PERIPH_ID_SRAM                                2
#define  BSP_PERIPH_ID_FLITF                               4
#define  BSP_PERIPH_ID_CRC                                 6
#define  BSP_PERIPH_ID_OTGFS                              12
#define  BSP_PERIPH_ID_ETHMAC                             14
#define  BSP_PERIPH_ID_ETHMACTX                           15

#define  BSP_PERIPH_ID_AFIO                               32
#define  BSP_PERIPH_ID_IOPA                               34
#define  BSP_PERIPH_ID_IOPB                               35
#define  BSP_PERIPH_ID_IOPC                               36
#define  BSP_PERIPH_ID_IOPD                               37
#define  BSP_PERIPH_ID_IOPE                               38
#define  BSP_PERIPH_ID_ADC1                               41
#define  BSP_PERIPH_ID_ADC2                               42
#define  BSP_PERIPH_ID_TIM1                               43
#define  BSP_PERIPH_ID_SPI1                               44
#define  BSP_PERIPH_ID_USART1                             46

#define  BSP_PERIPH_ID_TIM2                               64
#define  BSP_PERIPH_ID_TIM3                               65
#define  BSP_PERIPH_ID_TIM4                               66
#define  BSP_PERIPH_ID_TIM5                               67
#define  BSP_PERIPH_ID_TIM6                               68
#define  BSP_PERIPH_ID_TIM7                               69
#define  BSP_PERIPH_ID_WWDG                               75
#define  BSP_PERIPH_ID_SPI2                               78
#define  BSP_PERIPH_ID_SPI3                               79
#define  BSP_PERIPH_ID_USART2                             81
#define  BSP_PERIPH_ID_USART3                             82
#define  BSP_PERIPH_ID_USART4                             83
#define  BSP_PERIPH_ID_USART5                             84
#define  BSP_PERIPH_ID_I2C1                               85
#define  BSP_PERIPH_ID_I2C2                               86
#define  BSP_PERIPH_ID_CAN1                               89
#define  BSP_PERIPH_ID_CAN2                               90
#define  BSP_PERIPH_ID_BKP                                91
#define  BSP_PERIPH_ID_PWR                                92
#define  BSP_PERIPH_ID_DAC                                93


/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         BSP_Init                    (void);

void         BSP_IntDisAll               (void);

void         BSP_Tick_Init               (void);

CPU_INT32U   BSP_CPU_ClkFreq             (void);


/*
*********************************************************************************************************
*                                           INTERRUPT SERVICES
*********************************************************************************************************
*/

void         BSP_IntInit                 (void);

void         BSP_IntEn                   (CPU_DATA       int_id);

void         BSP_IntDis                  (CPU_DATA       int_id);

void         BSP_IntClr                  (CPU_DATA       int_id);

void         BSP_IntVectSet              (CPU_DATA       int_id,
                                          CPU_FNCT_VOID  isr);

void         BSP_IntPrioSet              (CPU_DATA       int_id,
                                          CPU_INT08U     prio);

void         BSP_IntHandlerInitialStackPointer	 (void);
void         BSP_IntHandlerInitialProgramCounter (void);
void         BSP_IntHandlerNMI				     (void);
void         BSP_IntHandlerHardFault			 (void);
void         BSP_IntHandlerReserved4			 (void);
void         BSP_IntHandlerBusFault			     (void);
void         BSP_IntHandlerUsageFault			 (void);
void         BSP_IntHandlerReserved7			 (void);
void         BSP_IntHandlerReserved8			 (void);
void         BSP_IntHandlerReserved9			 (void);
void         BSP_IntHandlerReserved10			 (void);
void         BSP_IntHandlerSVCall			     (void);
void         BSP_IntHandlerDebugMonitor			 (void);
void         BSP_IntHandlerReserved13			 (void);
void         BSP_IntHandlerPendableSrvReq		 (void);
void         BSP_IntHandlerSysTick			     (void);
void         BSP_IntHandlerDMA0				     (void);
void         BSP_IntHandlerDMA1				     (void);
void         BSP_IntHandlerDMA2				     (void);
void         BSP_IntHandlerDMA3				     (void);
void         BSP_IntHandlerDMA4				     (void);
void         BSP_IntHandlerDMA5				     (void);
void         BSP_IntHandlerDMA6				     (void);
void         BSP_IntHandlerDMA7				     (void);
void         BSP_IntHandlerDMA8				     (void);
void         BSP_IntHandlerDMA9				     (void);
void         BSP_IntHandlerDMA10			     (void);
void         BSP_IntHandlerDMA11			     (void);
void         BSP_IntHandlerDMA12			     (void);
void         BSP_IntHandlerDMA13			     (void);
void         BSP_IntHandlerDMA14			     (void);
void         BSP_IntHandlerDMA15			     (void);
void         BSP_IntHandlerDMAError			     (void);
void         BSP_IntHandlerMCM				     (void);
void         BSP_IntHandlerFTFL				     (void);
void         BSP_IntHandlerReadCollision		 (void);
void         BSP_IntHandlerLVDLVW			     (void);
void         BSP_IntHandlerLLW				     (void);
void         BSP_IntHandlerWatchdog			     (void);
void         BSP_IntHandlerRNGB				     (void);
void         BSP_IntHandlerI2C0				     (void);
void         BSP_IntHandlerI2C1				     (void);
void         BSP_IntHandlerSPI0				     (void);
void         BSP_IntHandlerSPI1				     (void);
void         BSP_IntHandlerSPI2		             (void);
void         BSP_IntHandlerCAN0ORedMessageBuffer (void);
void         BSP_IntHandlerCAN0BusOff			 (void);
void         BSP_IntHandlerCAN0Error			 (void);
void         BSP_IntHandlerCAN0TxWarning		 (void);
void         BSP_IntHandlerCAN0RxWarning		 (void);
void         BSP_IntHandlerCAN0WakeUp			 (void);
void         BSP_IntHandlerCAN0IMEU			     (void);
void         BSP_IntHandlerCAN0LostRx			 (void);
void         BSP_IntHandlerCAN1ORedMessageBuffer (void);
void         BSP_IntHandlerCAN1BusOff			 (void);
void         BSP_IntHandlerCAN1Error			 (void);
void         BSP_IntHandlerCAN1TxWarning		 (void);
void         BSP_IntHandlerCAN1RxWarning		 (void);
void         BSP_IntHandlerCAN1WakeUp			 (void);
void         BSP_IntHandlerCAN1IMEU			     (void);
void         BSP_IntHandlerCAN1LostRx			 (void);
void         BSP_IntHandlerUART0RxTx			 (void);
void         BSP_IntHandlerUART0Err			     (void);
void         BSP_IntHandlerUART1RxTx			 (void);
void         BSP_IntHandlerUART1Err			     (void);
void         BSP_IntHandlerUART2RxTx			 (void);
void         BSP_IntHandlerUART2Err			     (void);
void         BSP_IntHandlerUART3RxTx			 (void);
void         BSP_IntHandlerUART3Err			     (void);
void         BSP_IntHandlerUART4RxTx			 (void);
void         BSP_IntHandlerUART4Err			     (void);
void         BSP_IntHandlerUART5RxTx			 (void);
void         BSP_IntHandlerUART5Err			     (void);
void         BSP_IntHandlerADC0				     (void);
void         BSP_IntHandlerADC1				     (void);
void         BSP_IntHandlerHSCMP0			     (void);
void         BSP_IntHandlerHSCMP1			     (void);
void         BSP_IntHandlerHSCMP2			     (void);
void         BSP_IntHandlerFTM0				     (void);
void         BSP_IntHandlerFTM1				     (void);
void         BSP_IntHandlerFTM2				     (void);
void         BSP_IntHandlerCMT				     (void);
void         BSP_IntHandlerRTC				     (void);
void         BSP_IntHandlerReserved83			 (void);
void         BSP_IntHandlerPIT0				     (void);
void         BSP_IntHandlerPIT1				     (void);
void         BSP_IntHandlerPIT2				     (void);
void         BSP_IntHandlerPIT3				     (void);
void         BSP_IntHandlerPDB0				     (void);
void         BSP_IntHandlerUDB0				     (void);
void         BSP_IntHandlerUSBDCD			     (void);
void         BSP_IntHandlerEnet1588Timer		 (void);
void         BSP_IntHandlerEnetTransmit			 (void);
void         BSP_IntHandlerEnetReceive			 (void);
void         BSP_IntHandlerEnetError			 (void);
void         BSP_IntHandlerI2S0				     (void);
void         BSP_IntHandlerSDHC				     (void);
void         BSP_IntHandlerDAC0				     (void);
void         BSP_IntHandlerDAC1				     (void);
void         BSP_IntHandlerTSI0				     (void);
void         BSP_IntHandlerMCG				     (void);
void         BSP_IntHandlerLPTimer			     (void);
void         BSP_IntHandlerReserved102			 (void);
void         BSP_IntHandlerPortA			     (void);
void         BSP_IntHandlerPortB			     (void);
void         BSP_IntHandlerPortC			     (void);
void         BSP_IntHandlerPortD			     (void);
void         BSP_IntHandlerPortE			     (void);
void         BSP_IntHandlerReserved108			 (void);
void         BSP_IntHandlerReserved109			 (void);
void         BSP_IntHandlerReserved110			 (void);
void         BSP_IntHandlerReserved111			 (void);
void         BSP_IntHandlerReserved112			 (void);
void         BSP_IntHandlerReserved113			 (void);
void         BSP_IntHandlerReserved114			 (void);
void         BSP_IntHandlerReserved115			 (void);
void         BSP_IntHandlerReserved116			 (void);
void         BSP_IntHandlerReserved117			 (void);
void         BSP_IntHandlerReserved118			 (void);
void         BSP_IntHandlerReserved119			 (void);


/*
*********************************************************************************************************
*                                     PERIPHERAL POWER/CLOCK SERVICES
*********************************************************************************************************
*/

CPU_INT32U   BSP_PeriphClkFreqGet        (CPU_DATA       pwr_clk_id);

void         BSP_PeriphEn                (CPU_DATA       pwr_clk_id);

void         BSP_PeriphDis               (CPU_DATA       pwr_clk_id);


/*
*********************************************************************************************************
*                                              LED SERVICES
*********************************************************************************************************
*/

void         BSP_LED_On                  (CPU_INT08U     led);

void         BSP_LED_Off                 (CPU_INT08U     led);

void         BSP_LED_Toggle              (CPU_INT08U     led);


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
