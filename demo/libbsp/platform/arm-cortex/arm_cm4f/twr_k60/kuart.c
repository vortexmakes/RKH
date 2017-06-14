/*
 * File:        kuart.c
 * Purpose:     Provide common Kinetis UART routines
 *
 * Notes:       
 *              
 */

#include "bsp.h"
#include "kuart.h"


typedef
struct
{
	UART_MemMapPtr mma; /* uart memory map address*/
	uint8_t num;
	uint8_t prio;
	KUARTRX_CB rxcb;
}KUART_IRQ_ST;


enum
{
	KUART0,
	KUART1,
	KUART2,
	KUART3,
	KUART4,
	KUART5
};


static KUART_IRQ_ST kuart_channels[] =
{
	{ UART0_BASE_PTR, IRQ_NUMBER( INT_UART0_RX_TX ), BSP_UART_IRQ_PRIO, NULL },
	{ UART1_BASE_PTR, IRQ_NUMBER( INT_UART1_RX_TX ), BSP_UART_IRQ_PRIO, NULL },
	{ UART2_BASE_PTR, IRQ_NUMBER( INT_UART2_RX_TX ), BSP_UART_IRQ_PRIO, NULL },
	{ UART3_BASE_PTR, IRQ_NUMBER( INT_UART3_RX_TX ), BSP_UART_IRQ_PRIO, NULL },
	{ UART4_BASE_PTR, IRQ_NUMBER( INT_UART4_RX_TX ), BSP_UART_IRQ_PRIO, NULL },
	{ UART5_BASE_PTR, IRQ_NUMBER( INT_UART5_RX_TX ), BSP_UART_IRQ_PRIO, NULL },
	{ NULL}
};


static
KUART_IRQ_ST *
find_channtbl( UART_MemMapPtr channel )
{
	KUART_IRQ_ST *pc;

	for( pc = &kuart_channels[0]; pc->mma != NULL; ++pc )
	{
		if( pc->mma == channel )
			return pc;
	}
	return NULL;
}


/*
 * Initialize the UART for 8N1 operation, interrupts disabled, and
 * no hardware flow-control
 *
 * NOTE: Since the UARTs are pinned out in multiple locations on most
 *       Kinetis devices, this driver does not enable UART pin functions.
 *       The desired pins should be enabled before calling this init function.
 *
 * Parameters:
 *  channel      UART channel to initialize
 *  sysclk      UART module Clock in kHz(used to calculate baud)
 *  baud        UART baud rate
 */

void 
kuart_init ( UART_MemMapPtr channel, const KUARTPP_ST* pu )
{
    register uint16 sbr, brfa;
    uint8 temp;
	uint8_t txsize, rxsize, shiftval;	
	uint32_t  pFIFO; 	
	KUART_IRQ_ST *pc;
	int sysclk;

	if( (pc = find_channtbl( channel )) == NULL )
		return;

		/* Enable the clock to the selected UART */    
    if(channel == UART0_BASE_PTR)
	{
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
		sysclk = (int)(mcu_coreclk_hz/1000);
	}
    else if (channel == UART1_BASE_PTR)
	{
		SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
		sysclk = (int)(mcu_coreclk_hz/1000);
	}
    else if (channel == UART2_BASE_PTR)
	{
    	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
		sysclk = (int)(mcu_busclk_hz/1000);
	}
    else if(channel == UART3_BASE_PTR)
	{
		SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
		sysclk = (int)(mcu_busclk_hz/1000);
	}
   	else if(channel == UART4_BASE_PTR)
	{
    	SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;
		sysclk = (int)(mcu_busclk_hz/1000);
	}
	else
	{
    	SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;
		sysclk = (int)(mcu_busclk_hz/1000);
	}


    /* 
	 * Make sure that the transmitter and receiver are disabled while we 
     * change settings.
     */
    UART_C2_REG(channel) &= ~(UART_C2_TE_MASK
				| UART_C2_RE_MASK );

    /* Configure the UART for 8-bit mode, no parity */
	/* We need all default settings, so entire register is cleared */
    UART_C1_REG(channel) = 0;	
    
    /* Calculate baud settings */
    sbr = (uint16)((sysclk*1000)/(pu->baud * 16));
        
    /* Save off the current value of the UARTx_BDH except for the SBR field */
    temp = UART_BDH_REG(channel) & ~(UART_BDH_SBR(0x1F));
    
    UART_BDH_REG(channel) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
    UART_BDL_REG(channel) = (uint8)(sbr & UART_BDL_SBR_MASK);
    
    /* 
	 * Determine if a fractional divider is needed 
	 * to get closer to the baud rate
	 */
    brfa = (uint16)(((sysclk*32000)/(pu->baud * 16)) - (sbr * 32));
    
    /*
	 * Save off the current value of the UARTx_C4 register except 
	 * for the BRFA field
	 */
    temp = UART_C4_REG(channel) & ~(UART_C4_BRFA(0x1F));
    
    UART_C4_REG(channel) = temp |  UART_C4_BRFA(brfa);    

	UART_C5_REG(channel) = 0; /* use interrupt not dma. */

	/* set watermark in the almost full TX buffer */
	if( ( ( UART_PFIFO_REG(channel) & UART_PFIFO_TXFIFOSIZE_MASK ) 
			>> UART_PFIFO_TXFIFOSIZE_SHIFT ) == 0 )
	{
		/* 1 dataword in D */
		UART_TWFIFO_REG(channel) = UART_TWFIFO_TXWATER(0);
	}
	else
	{
		pFIFO=UART_PFIFO_REG(channel) & UART_PFIFO_TXFIFOSIZE_MASK;
		shiftval=(uint8_t)(((pFIFO) >> UART_PFIFO_TXFIFOSIZE_SHIFT) + 1);
		txsize = 1 << shiftval;
		/* 
		 * watermark for TX buffer generates interrupts 
		 * below & equal to watermark
		 */
		txsize -= 1;
		UART_TWFIFO_REG(channel) = UART_TWFIFO_TXWATER( pu->tx_ffsz < txsize ?
			   											pu->tx_ffsz : txsize );
	}

	/* set watermark in the almost full RX buffer */
	if( ( ( UART_PFIFO_REG(channel) & UART_PFIFO_RXFIFOSIZE_MASK) 
			>> UART_PFIFO_RXFIFOSIZE_SHIFT ) == 0 )
	{
		/* rx buffer is 1 byte */
		UART_RWFIFO_REG(channel) = UART_RWFIFO_RXWATER(1);
	}
	else
	{
		pFIFO=UART_PFIFO_REG(channel) & UART_PFIFO_RXFIFOSIZE_MASK;
		shiftval=(uint8_t)(((pFIFO) >> UART_PFIFO_RXFIFOSIZE_SHIFT) + 1);
		rxsize = 1 << shiftval;
		/* 
		 * watermark for RX buffer generates interrupts
		 * below & equal to watermark
		 */
		rxsize -= 1;
		UART_RWFIFO_REG(channel) = UART_RWFIFO_RXWATER( pu->rx_ffsz < rxsize ?
			   											pu->rx_ffsz : rxsize );
	}

   	/* flush buffers */
	UART_CFIFO_REG(channel) |= (UART_CFIFO_RXFLUSH_MASK|UART_CFIFO_TXFLUSH_MASK);

	/* enable fifo */
	UART_PFIFO_REG(channel) |= UART_PFIFO_RXFE_MASK; 
	UART_PFIFO_REG(channel) |= UART_PFIFO_TXFE_MASK;

	/* clear isr flags */
	temp=UART_S1_REG(channel);

	/* see page 73 of the manual */
	if( pu->rxcb != NULL )
	{
		enable_irq( pc->num );
		set_irq_priority( pc->num, pc->prio );
		UART_C2_REG(channel) |= UART_C2_RIE_MASK;	/* enable rx irq */
		pc->rxcb = pu->rxcb;
	}
	else
	{
		disable_irq( pc->num );
		UART_C2_REG(channel) &= ~UART_C2_RIE_MASK;	/* disable rx irq */
	}

	/* Configure hardware flow ctrl */
	if( pu->fce == KUART_HFC_ENABLE )
	{
		UART_MODEM_REG( channel ) |= UART_MODEM_TXCTSE_MASK;
		UART_MODEM_REG( channel ) |= UART_MODEM_RXRTSE_MASK; 
	}

    /* Enable receiver and transmitter */
	UART_C2_REG(channel) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );
}


static
void
kuart_isr( KUART_IRQ_ST *p )
{
	uint32_t reg;
	KUARTRX_CB rx_cb;

	reg = UART_S1_REG(p->mma);
	
#ifdef __KUART_XMIT_INTERRUPT__		
	/*
	 * UART transmition IRQ drived is not yet implemented
	 */

	/*
	 * this clears the interrupt so now we have to see which one is:
	 */
	if( reg & UART_S1_TDRE_MASK )
	{
		/* disable interrupts */
		UART_C2_REG(p->mma) &= ~(UART_C2_TIE_MASK);
		/* uart_isr_tx(); */
		/* tx complete isr. */
	}
	if( reg & UART_S1_TC_MASK )
	{
	}
#endif	

   	/* Receive Data Register Full Flag */
	if( reg & UART_S1_RDRF_MASK )
		if( (rx_cb = p->rxcb) != NULL )
			rx_cb( UART_D_REG(p->mma) );
}


/*
 * Interrupt vector functions
 */

void kuart0_isr( void ){	kuart_isr( &kuart_channels[KUART0] ); }
void kuart1_isr( void ){	kuart_isr( &kuart_channels[KUART1] ); }
void kuart2_isr( void ){	kuart_isr( &kuart_channels[KUART2] ); }
void kuart3_isr( void ){	kuart_isr( &kuart_channels[KUART3] ); }
void kuart4_isr( void ){	kuart_isr( &kuart_channels[KUART4] ); }
void kuart5_isr( void ){	kuart_isr( &kuart_channels[KUART5] ); }


/*
 * Wait for a character to be received on the specified UART
 *
 * Parameters:
 *  channel      UART channel to read from
 *
 * Return Values:
 *  the received character
 */

char kuart_getchar (UART_MemMapPtr channel)
{
    /* Wait until character has been received */
    while (!(UART_S1_REG(channel) & UART_S1_RDRF_MASK))
    	;
    
    /* Return the 8-bit data from the receiver */
    return (char)UART_D_REG(channel);
}


/*
 * Wait for space in the UART Tx FIFO and then send a character
 *
 * Parameters:
 *  channel      UART channel to send to
 *  ch			 character to send
 */ 

void
kuart_putchar (UART_MemMapPtr channel, char ch)
{
	char i = 0;

	/* Wait until space is available in the FIFO */
    while(!(UART_S1_REG(channel) & UART_S1_TDRE_MASK))
		++i;
    
    /* Send the character */
    UART_D_REG(channel) = (uint8)ch;
}


/*
 * Wait for space in the UART Tx FIFO and then send a character
 *
 * Parameters:
 *  channel      UART channel to send to
 *  *p			 pointer to data buffer
 *  n			 char quantity to send
 */ 

void
kuart_putnchar (UART_MemMapPtr channel, char *p, uint16 n )
{
	while( n-- )
		kuart_putchar( channel, *p++ );
}


void
kuart_putstr( UART_MemMapPtr channel, char *str )
{
	while( *str != '\0' )
		kuart_putchar( channel, *str++ );
	
	/* flush buffer */
	UART_CFIFO_REG(channel) |= UART_CFIFO_TXFLUSH_MASK; 
}


/*
 * Check to see if a character has been received
 *
 * Parameters:
 *  channel      UART channel to check for a character
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */

int
kuart_getchar_present (UART_MemMapPtr channel)
{
    return (int)(UART_S1_REG(channel) & UART_S1_RDRF_MASK);
}
    

void
kuart_hflwctrl( UART_MemMapPtr channel, KUART_HFC_T ctrl )
{
	if( ctrl == KUART_HFC_ENABLE )
	{
		UART_MODEM_REG( channel ) |= UART_MODEM_TXCTSE_MASK;
		UART_MODEM_REG( channel ) |= UART_MODEM_RXRTSE_MASK; 
	}
	else
	{
		UART_MODEM_REG( channel ) &= ~UART_MODEM_TXCTSE_MASK;
		UART_MODEM_REG( channel ) &= ~UART_MODEM_RXRTSE_MASK; 
	}
}

