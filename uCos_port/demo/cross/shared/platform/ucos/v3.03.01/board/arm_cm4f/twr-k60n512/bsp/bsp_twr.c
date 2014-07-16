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
* Filename      : bsp_twr.c
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

#define  BSP_MODULE
#include  <bsp_twr.h>
#include  <bsp_os.h>
#include  <MK60N512VMD100.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/

#define  BSP_LED_START_BIT  (13 - 1)                            /* LEDs[3:1] are sequentially connected to PTD[15:13].  */


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


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  CPU_INT32U  BSP_CPU_ClkFreq_MHz;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_PLL_Init   (void);
static  void  BSP_LED_Init   (void);


/*
*********************************************************************************************************
*                                             REGISTERS
*********************************************************************************************************
*/

#define  DWT_CR      *(CPU_REG32 *)0xE0001000                   /* Data Watchpoint and Trace (DWT) Control Register     */
#define  DWT_CYCCNT  *(CPU_REG32 *)0xE0001004                   /* Data Watchpoint and Trace (DWT) Cycle Count Register */
#define  DEM_CR      *(CPU_REG32 *)0xE000EDFC
#define  DBGMCU_CR   *(CPU_REG32 *)0xE0042004                   /* ??? Located in the PPB area only in ST           ??? */


/*
*********************************************************************************************************
*                                            REGISTER BITS
*********************************************************************************************************
*/

#define  DBGMCU_CR_TRACE_IOEN_MASK       0x10                   /* ??? Located in the PPB area only in ST           ??? */
#define  DBGMCU_CR_TRACE_MODE_ASYNC      0x00                   /* ??? Located in the PPB area only in ST           ??? */
#define  DBGMCU_CR_TRACE_MODE_SYNC_01    0x40                   /* ??? Located in the PPB area only in ST           ??? */
#define  DBGMCU_CR_TRACE_MODE_SYNC_02    0x80                   /* ??? Located in the PPB area only in ST           ??? */
#define  DBGMCU_CR_TRACE_MODE_SYNC_04    0xC0                   /* ??? Located in the PPB area only in ST           ??? */
#define  DBGMCU_CR_TRACE_MODE_MASK       0xC0                   /* ??? Located in the PPB area only in ST           ??? */

#define  DEM_CR_TRCENA                   (1 << 24)

#define  DWT_CR_CYCCNTENA                (1 <<  0)


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

#if ((CPU_CFG_TS_TMR_EN          != DEF_ENABLED) && \
     (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && \
     (OS_PROBE_HOOKS_EN          == 1))
#error  "CPU_CFG_TS_EN                  illegally #define'd in 'cpu.h'"
#error  "                              [MUST be  DEF_ENABLED] when    "
#error  "                               using uC/Probe COM modules    "
#endif


/*
*********************************************************************************************************
*                                               BSP_Init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
*
*               (2) CPU instruction / data tracing requires the use of the following pins :
*                   (a) (1) Aysynchronous     :  PB[3]
*                       (2) Synchronous 1-bit :  PE[3:2]
*                       (3) Synchronous 2-bit :  PE[4:2]
*                       (4) Synchronous 4-bit :  PE[6:2]
*
*                   (b) The application may wish to adjust the trace bus width depending on I/O
*                       requirements.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    volatile unsigned int dummy = SYST_CSR;
    unsigned int reg  =  SIM_SCGC5;
    
    WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;

    DWT_CR |= (CPU_INT32U)0x00000001;                           /* Enable Cortex-M4's DWT CYCCNT reg.                   */

    BSP_IntInit();                                              /* Initialize Interrupts.                               */

    SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
              |   SIM_SCGC5_PORTB_MASK
              |   SIM_SCGC5_PORTC_MASK
              |   SIM_SCGC5_PORTD_MASK
              |   SIM_SCGC5_PORTE_MASK);


    reg              &= ~SIM_SCGC5_PORTA_MASK;
    reg              |=  1 << SIM_SCGC5_PORTA_SHIFT;
    SIM_SCGC5         = reg;                                    /* Slow slew rate.                                      */

                                                                /* Init System tick times.                              */
                                                                /* Clear pending interrupt.                             */

    SYST_RVR  = (2000000UL);                                    /* Set period.                                          */
    SYST_CSR |=  SysTick_CSR_CLKSOURCE_MASK;                    /* Clock source - System Clock.                         */
    SYST_CSR |=  SysTick_CSR_TICKINT_MASK;                      /* Enable interrupt.                                    */
    SYST_CSR |=  SysTick_CSR_ENABLE_MASK;                       /* Start Sys Timer.                                     */


    BSP_CPU_ClkFreq_MHz = BSP_CPU_ClkFreq() / (CPU_INT32U)1000000;

    BSP_CPU_ClkFreq_MHz = BSP_CPU_ClkFreq_MHz;                  /* Surpress compiler warning BSP_CPU_ClkFreq_MHz    ... */

    BSP_PLL_Init();

                                                                /* ... set and not used.                                */
    BSP_LED_Init();                                             /* Initialize the I/Os for the LED      controls.       */


#ifdef TRACE_EN                                                 /* See project / compiler preprocessor options.         */
    DBGMCU_CR |=  DBGMCU_CR_TRACE_IOEN_MASK;                    /* Enable tracing (see Note #2).                        */
    DBGMCU_CR &= ~DBGMCU_CR_TRACE_MODE_MASK;                    /* Clr trace mode sel bits.                             */
    DBGMCU_CR |=  DBGMCU_CR_TRACE_MODE_SYNC_04;                 /* Cfg trace mode to synch 4-bit.                       */
#endif
}


/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Read CPU registers to determine the CPU clock frequency of the chip.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
  return ((CPU_INT32U)96000000UL);
}


/*
*********************************************************************************************************
*                                            BSP_Tick_Init()
*
* Description : Initialize all the peripherals that required OS Tick services (OS initialized)
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
void BSP_Tick_Init (void)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    
    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
    
#if (OS_VERSION >= 30000u)
    cnts  = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;       /* Determine nbr SysTick increments.                    */
#else
    cnts  = cpu_clk_freq / (CPU_INT32U)OS_TICKS_PER_SEC;        /* Determine nbr SysTick increments.                    */
#endif
    
    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */
}


/*
*********************************************************************************************************
*                                         PLL INITIALIZATION
*
* Description : This function is called to initialize the PLL.
*
* Arguments   : none
*********************************************************************************************************
*/

static  void  BSP_PLL_Init (void)
{
#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
    CPU_SR  cpu_sr;
#endif


    CPU_CRITICAL_ENTER();

    MCG_C2 = 0;                                                 /* Enable external oscillator                           */

    MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);                  /* Select external oscilator and Reference Divider and  */
                                                                /* clear IREFS to start ext osc                         */
                                                                /* CLKS=2, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0      */

    while (MCG_S & MCG_S_IREFST_MASK) {};                       /* Wait for Reference clock Status bit to clear         */

                                                                /* Wait for clock status bits to show clock             */
                                                                /* source is ext ref clk                                */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2) {};

    MCG_C5 = MCG_C5_PRDIV(0x18);                                /* PLL Ref Divider, PLLCLKEN=0, PLLSTEN=0, PRDIV=0x18   */

    MCG_C6 = 0;                                                 /* Ensure MCG_C6 is at the reset default of 0           */

                                                                /* Set System Options Dividers = 0x01130000             */
    SIM_CLKDIV1 =   SIM_CLKDIV1_OUTDIV1(BSP_CORE_DIV - 1)    |  /*     Core/System Clock        Div by: 1               */
                    SIM_CLKDIV1_OUTDIV2(BSP_BUS_DIV - 1)     |  /*     Peripheral Clock         Div by: 2               */
                    SIM_CLKDIV1_OUTDIV3(BSP_FLEXBUS_DIV - 1) |  /*     FlexBus Clock(FB_CLK)    Div by: 2               */
                    SIM_CLKDIV1_OUTDIV4(BSP_FLASH_DIV - 1);     /*     Flash Clock              Div by: 4               */

    MCG_C5 = DEF_BIT_MASK_08(0x18, MCG_C5_PRDIV_SHIFT);         /* PLL Clk Division Factor of: 25                       */
    DEF_BIT_SET_08(MCG_C5, MCG_C5_PLLCLKEN_MASK);               /* PLL Clock Enable                                     */
    
                                                                /* Set the VCO divider and Selects PLL                  */
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(BSP_CLOCK_MUL - 24);
    
    DEF_BIT_SET_32(SIM_SOPT2, SIM_SOPT2_PLLFLLSEL_MASK);        /* Selects MCGPLLCLK Clock for Peripheral Clock         */
    
    while (!(MCG_S & MCG_S_PLLST_MASK)) {};                     /* Wait for PLL status bit to set                       */
    while (!(MCG_S & MCG_S_LOCK_MASK)) {};                      /* Wait for LOCK bit to set                             */

    MCG_C1 &= ~MCG_C1_CLKS_MASK;                                /* Transition into PEE by setting CLKS to 0             */

                                                                /* Wait for clock status bits to update                 */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3) {};

    CPU_CRITICAL_EXIT();
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                              LED FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             BSP_LED_Init()
*
* Description : Initialize the I/O for the LEDs
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

static  void  BSP_LED_Init (void)
{

    PORTA_PCR10 |= PORT_PCR_SRE_MASK                            /* Slow slew rate.                                      */
                |  PORT_PCR_ODE_MASK                            /* Open Drain Enable.                                   */
                |  PORT_PCR_DSE_MASK;                           /* High drive strength.                                 */

    PORTA_PCR10  = (0|PORT_PCR_MUX(1));                         /* Alternative 1 (GPIO).                                */

    PORTA_PCR11 |= PORT_PCR_SRE_MASK                            /* Slow slew rate.                                      */
                |  PORT_PCR_ODE_MASK                            /* Open Drain Enable.                                   */
                |  PORT_PCR_DSE_MASK;                           /* High drive strength.                                 */

    PORTA_PCR11  = (0|PORT_PCR_MUX(1));                         /* Alternative 1 (GPIO).                                */

    PORTA_PCR28 |= PORT_PCR_SRE_MASK                            /* Slow slew rate.                                      */
                |  PORT_PCR_ODE_MASK                            /* Open Drain Enable.                                   */
                |  PORT_PCR_DSE_MASK;                           /* High drive strength.                                 */

    PORTA_PCR28  = (0|PORT_PCR_MUX(1));                         /* Alternative 1 (GPIO).                                */

    PORTA_PCR29 |= PORT_PCR_SRE_MASK                            /* Slow slew rate.                                      */
                |  PORT_PCR_ODE_MASK                            /* Open Drain Enable.                                   */
                |  PORT_PCR_DSE_MASK;                           /* High drive strength.                                 */

    PORTA_PCR29  = (0|PORT_PCR_MUX(1));                         /* Alternative 1 (GPIO).                                */

    GPIOA_POER   = BSP_GPIOA_LED_BLUE
                |  BSP_GPIOA_LED_GREEN
                |  BSP_GPIOA_LED_YELLOW
                |  BSP_GPIOA_LED_ORANGE;

}


/*
*********************************************************************************************************
*                                             BSP_LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turns ON ALL the LEDs
*                       1    turns ON user LED1  on the board
*                       2    turns ON user LED2  on the board
*                       3    turns ON user LED3  on the board
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U led)
{
    switch (led) {
        case BSP_LED_ALL:
             GPIOA_PCOR  = BSP_GPIOA_LED_BLUE
                        |  BSP_GPIOA_LED_GREEN
                        |  BSP_GPIOA_LED_YELLOW
                        |  BSP_GPIOA_LED_ORANGE;
             break;

        case BSP_LED_BLUE:
             GPIOA_PCOR = BSP_GPIOA_LED_BLUE;
             break;

        case BSP_LED_GREEN:
             GPIOA_PCOR = BSP_GPIOA_LED_GREEN;
             break;

        case BSP_LED_YELLOW:
             GPIOA_PCOR = BSP_GPIOA_LED_YELLOW;
             break;

        case BSP_LED_ORANGE:
             GPIOA_PCOR = BSP_GPIOA_LED_ORANGE;
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                              BSP_LED_Off()
*
* Description : Turn OFF any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turns OFF ALL the LEDs
*                       1    turns OFF user LED1  on the board
*                       2    turns OFF user LED2  on the board
*                       3    turns OFF user LED3  on the board
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U led)
{
    switch (led) {
        case BSP_LED_ALL:
             GPIOA_PSOR  =  BSP_GPIOA_LED_BLUE
                        |   BSP_GPIOA_LED_GREEN
                        |   BSP_GPIOA_LED_YELLOW
                        |   BSP_GPIOA_LED_ORANGE;
             break;

        case BSP_LED_BLUE:
             GPIOA_PSOR  = BSP_GPIOA_LED_BLUE;
             break;

        case BSP_LED_GREEN:
             GPIOA_PSOR  = BSP_GPIOA_LED_GREEN;
             break;

        case BSP_LED_YELLOW:
             GPIOA_PSOR  = BSP_GPIOA_LED_YELLOW;
             break;

        case BSP_LED_ORANGE:
             GPIOA_PSOR  = BSP_GPIOA_LED_ORANGE;
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                            BSP_LED_Toggle()
*
* Description : TOGGLE any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    TOGGLE ALL the LEDs
*                       1    TOGGLE user LED1  on the board
*                       2    TOGGLE user LED2  on the board
*                       3    TOGGLE user LED3  on the board
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_INT08U led)
{
    switch (led) {
        case BSP_LED_ALL:
             GPIOA_PTOR  = BSP_GPIOA_LED_BLUE
                        |  BSP_GPIOA_LED_GREEN
                        |  BSP_GPIOA_LED_YELLOW
                        |  BSP_GPIOA_LED_ORANGE;
             break;

        case BSP_LED_BLUE:
             GPIOA_PTOR = BSP_GPIOA_LED_BLUE;
             break;

        case BSP_LED_GREEN:
             GPIOA_PTOR = BSP_GPIOA_LED_GREEN;
             break;

        case BSP_LED_YELLOW:
             GPIOA_PTOR = BSP_GPIOA_LED_YELLOW;
             break;

        case BSP_LED_ORANGE:
             GPIOA_PTOR = BSP_GPIOA_LED_ORANGE;
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                          CPU_TS_TmrInit()
*
* Description : Initialize & start CPU timestamp timer.
*
* Argument(s) : none.
*
* Return(s)   : Number of left-shifts to scale & return timer as (32-bit) 'CPU_TS' data type
*                 (see Note #1a1), if necessary.
*
*               0 (see Note #1a2), otherwise.
*
* Caller(s)   : CPU_TS_Init().
*
* Note(s)     : (1) (a) Timer count values MUST be scaled & returned via (32-bit) 'CPU_TS' data type.
*
*                       (1) If timer used has less bits, left-shift timer values until the most
*                           significant bit of the timer value is shifted into         the most
*                           significant bit of the return timestamp data type.
*                       (2) If timer used has more bits, truncate   timer values' higher-order
*                           bits greater than  the return timestamp data type.
*
*                   (b) Timer SHOULD be an 'up'  counter whose values increase with each time count.
*
*                   (c) When applicable, timer period SHOULD be less than the typical measured time
*                       but MUST be less than the maximum measured time; otherwise, timer resolution
*                       inadequate to measure desired times.
*
*                   See also 'CPU_TS_TmrRd()  Note #1'.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_TmrInit (void)
{
    CPU_INT32U  cpu_clk_freq_hz;


    DEM_CR         |= (CPU_INT32U)DEM_CR_TRCENA;                /* Enable Cortex-M4's DWT CYCCNT reg.                   */
    DWT_CYCCNT      = (CPU_INT32U)0u;
    DWT_CR         |= (CPU_INT32U)DWT_CR_CYCCNTENA;

    cpu_clk_freq_hz = BSP_CPU_ClkFreq();
    CPU_TS_TmrFreqSet(cpu_clk_freq_hz);
}
#endif


/*
*********************************************************************************************************
*                                           CPU_TS_TmrRd()
*
* Description : Get current CPU timestamp timer count value.
*
* Argument(s) : none.
*
* Return(s)   : (32-bit) Timestamp timer count (see Notes #1a & #1b).
*
* Caller(s)   : CPU_TS_Init(),
*               CPU_TS_UpdateHandler(),
*               CPU_IntDisMeasStart(),
*               CPU_IntDisMeasStop().
*
* Note(s)     : (1) (a) Timer count values MUST be returned via (32-bit) 'CPU_TS' data type.
*
*                       (1) If timer used has less bits, left-shift timer values until the most
*                           significant bit of the timer value is shifted into         the most
*                           significant bit of the return timestamp data type.
*                       (2) If timer used has more bits, truncate   timer values' higher-order
*                           bits greater than  the return timestamp data type.
*
*                   (b) Timer SHOULD be an 'up'  counter whose values increase with each time count.
*
*                       (1) If timer is a 'down' counter whose values decrease with each time count,
*                           then the returned timer value MUST be ones-complemented.
*
*                   (c) (1) When applicable, the amount of time measured by CPU timestamps is
*                           calculated by the following equation :
*
*                               Time measured  =  Timer period  *  Number timer counts
*
*                                   where
*
*                                       Timer period            Timer's period in some units of
*                                                                   (fractional) seconds
*                                       Number timer counts     Number of timer counts measured
*                                       Time measured           Amount of time measured, in same
*                                                                   units of (fractional) seconds
*                                                                   as the Timer period
*
*                       (2) Timer period SHOULD be less than the typical measured time but MUST be less
*                           than the maximum measured time; otherwise, timer resolution inadequate to
*                           measure desired times.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS  CPU_TS_TmrRd (void)
{
    return ((CPU_TS)DWT_CYCCNT);
}
#endif





