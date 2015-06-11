/*
 * telybrd.c
 * BSP extension for tely project
 */

#include "board.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"

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
