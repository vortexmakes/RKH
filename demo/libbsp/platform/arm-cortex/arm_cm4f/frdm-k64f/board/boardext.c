/*
 * boardext.c
 * board.c BSP extension 
 */

#include "board.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"
#include "fsl_clock_manager.h"


/* The UART to use for RKH trace. */

static uart_user_config_t trc_uart = {	BRD_RKHTRC_UART_BAUD,
										kUart8BitsPerChar,
										kUartParityDisabled, 
										kUartOneStopBit
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
    configure_uart_pins(BRD_RKHTRC_UART_INSTANCE);	
	UART_DRV_Init(	BRD_RKHTRC_UART_INSTANCE, &trc_uart_state, &trc_uart );

	UART_DRV_InstallRxCallback( BRD_RKHTRC_UART_INSTANCE, trc_rx_callback, 
								&rx_data, NULL, 1 );
	UART_DRV_ReceiveData( BRD_RKHTRC_UART_INSTANCE, &rx_data, 1 );
}


void
rkhtrc_uart_deinit( void )
{
	UART_DRV_Deinit( BRD_RKHTRC_UART_INSTANCE );
}


void
rkhtrc_send_block( rui8_t *buf, TRCQTY_T len )
{
	static uint32_t txrem;

	UART_DRV_SendData( BRD_RKHTRC_UART_INSTANCE, buf, len );

	while ( UART_DRV_GetTransmitStatus( BRD_RKHTRC_UART_INSTANCE, &txrem) ==
		  kStatus_UART_TxBusy);

}


/* LPTMR0 config for uCos and RKH trace time stamp */

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)

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


#ifdef FSL_RTOS_UCOSIII

/* LPTMR0 config for uCos and RKH trace time stamp */

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


CPU_TS  CPU_TS_TmrRd (void)
{
	return LPTMR_DRV_GetCurrentTimeUs(TSTAMP_LPTMR_INSTANCE);
}

#endif

#endif

/* RGB Led control */

typedef struct
{
	uint32_t r;
	uint32_t g;
	uint32_t b;
} RGB_COLOR_ST;


static RGB_COLOR_ST rgb_colors[] = {	{ 0, 0, 0 },	
										{ 1, 1, 1 },
										{ 1, 0, 0 },
										{ 0, 1, 0 },
										{ 0, 0, 1 },
										{ 1, 1, 0 },
										{ 0, 1, 1 },
										{ 1, 0, 1 }	};

void
set_rgb_led( RGB_COLOR_IDX idx )
{
	(rgb_colors[idx].r == 1) ? GPIO_DRV_ClearPinOutput( BOARD_GPIO_LED_RED ) :
							GPIO_DRV_SetPinOutput( BOARD_GPIO_LED_RED );
	(rgb_colors[idx].g == 1) ? GPIO_DRV_ClearPinOutput( BOARD_GPIO_LED_GREEN ) :
							GPIO_DRV_SetPinOutput( BOARD_GPIO_LED_GREEN );	
	(rgb_colors[idx].b == 1) ? GPIO_DRV_ClearPinOutput( BOARD_GPIO_LED_BLUE ) :
							GPIO_DRV_SetPinOutput( BOARD_GPIO_LED_BLUE );
}


/* board low level initialization */

void
board_init( void )
{
	hardware_init();
	CPU_Init();

	GPIO_DRV_Init( switchPins, ledPins );
}
