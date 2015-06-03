/*
 * telybrd.c
 * BSP extension for tely project
 */

#include "board.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"
#include "fsl_clock_manager.h"

/* The UART to use for RKH trace . */

static uart_user_config_t trc_uart =
{
	TELYBRD_RKHTRC_UART_BAUD, 
	kUart8BitsPerChar, kUartParityDisabled, kUartOneStopBit
};

static uart_state_t trc_uart_state;

uint8_t rx_data;

void
trc_rx_callback( uint32_t instance, void * uartState )
{
	UART_DRV_SendData( BOARD_DEBUG_UART_INSTANCE, &rx_data, 1 );
}

void
rkhtrc_uart_init( void )
{
    configure_uart_pins(TELYBRD_RKHTRC_UART_INSTANCE);	
	UART_DRV_Init(	TELYBRD_RKHTRC_UART_INSTANCE, &trc_uart_state, &trc_uart );

	UART_DRV_InstallRxCallback( TELYBRD_RKHTRC_UART_INSTANCE, trc_rx_callback, &rx_data, NULL, 1 );
	UART_DRV_ReceiveData( TELYBRD_RKHTRC_UART_INSTANCE, &rx_data, 1 );
}


void
rkhtrc_uart_deinit( void )
{
	UART_DRV_Deinit( TELYBRD_RKHTRC_UART_INSTANCE );
}


void
rkhtrc_send_block( rui8_t *buf, TRCQTY_T len )
{
	static uint32_t txrem;

	UART_DRV_SendData( TELYBRD_RKHTRC_UART_INSTANCE, buf, len );

	while
		( UART_DRV_GetTransmitStatus( TELYBRD_RKHTRC_UART_INSTANCE, &txrem) ==
		  kStatus_UART_TxBusy);

}


/* LPTMR0 config for RKH trace time stamp */

lptmr_state_t tstamp_state;

lptmr_user_config_t lptmr_tstamp =
{
		/* use LPTMR in Time Counter mode */	
		.timerMode = kLptmrTimerModeTimeCounter, 
		/* use LPTMR in Time Counter mode */		
		.freeRunningEnable    = false, 
		/* bypass prescaler */
		.prescalerEnable      = false, 
		/* use 1kHz Low Power Clock */		
		.prescalerClockSource = kClockLptmrSrcLpoClk, 
		/* not use interrupts */		
		.isInterruptEnabled   = false
};

#if 0
void
rkhtrc_lptmr_init( void )
{
    /* Initialize LPTMR */
	LPTMR_DRV_Init(TSTAMP_LPTMR_INSTANCE, &tstamp_state, &lptmr_tstamp);

    /* Set the timer period for 1 second */
    LPTMR_DRV_SetTimerPeriodUs(TSTAMP_LPTMR_INSTANCE,1000000);

	/* Start counting */
    LPTMR_DRV_Start(TSTAMP_LPTMR_INSTANCE);
}


uint32_t 
rkhtrc_lptmr_read( void )
{
	return LPTMR_DRV_GetCurrentTimeUs(TSTAMP_LPTMR_INSTANCE);
}
#endif



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

    /* Initialize LPTMR */
	LPTMR_DRV_Init(TSTAMP_LPTMR_INSTANCE, &tstamp_state, &lptmr_tstamp);

    /* Set the timer period for 1 second */
    LPTMR_DRV_SetTimerPeriodUs(TSTAMP_LPTMR_INSTANCE,1000000);

	/* Start counting */
    LPTMR_DRV_Start(TSTAMP_LPTMR_INSTANCE);

    cpu_clk_freq_hz = CLOCK_SYS_GetCoreClockFreq();
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
//	return LPTMR_DRV_GetCurrentTimeUs(TSTAMP_LPTMR_INSTANCE);
	return 0;
}
#endif

