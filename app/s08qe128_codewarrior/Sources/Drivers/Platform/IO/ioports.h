/*
 *	ioports.h
 *	
 *	Routines for PORTS initialization.
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 26/05/06.
 */

#ifndef __IOPORTS_H__
#define __IOPORTS_H__

#include "derivative.h"


/* DATA_REGISTERS */

/* PORT A Data Register */

#define PSHBUTT0	PTAD_PTAD2		/* input */
#define PSHBUTT1	PTAD_PTAD3		/* input */

/* PORT B Data Register */

#define SPI_CLK		PTBD_PTBD2		/* output */
#define SPI_MOSI	PTBD_PTBD3		/* output */
#define SPI_MISO	PTBD_PTBD4		/* output */

/* PORT C Data Register */

#define LED0		PTCD_PTCD0		/* output */
#define LED1		PTCD_PTCD1		/* output */
#define LED2		PTCD_PTCD2		/* output */
#define LED3		PTCD_PTCD3		/* output */
#define LED4		PTCD_PTCD4		/* output */
#define LED5		PTCD_PTCD5		/* output */
#define COM_ENABLE	PTCD_PTCD5		/* output */

/* PORT D Data Register */

#define WIZNET_RST	PTDD_PTDD0		/* input */
#define SPI_CS		PTDD_PTDD1		/* input */
#define PSHBUTT2	PTDD_PTDD2		/* input */
#define PSHBUTT3	PTDD_PTDD3		/* input */

/* PORT E Data Register */

#define LED6		PTED_PTED6		/* output */
#define LED7		PTED_PTED7		/* output */

/* DATA DIRECTION REGISTERS */

/* PORT A Data Direction Register */

#define D_PSHBUTT0	PTADD_PTADD2	/* input */
#define D_PSHBUTT1	PTADD_PTADD3	/* input */

/* PORT B Data Direction Register */

#define D_SPI_CLK	PTBDD_PTBDD2	/* output */
#define D_SPI_MOSI	PTBDD_PTBDD3	/* output */
#define D_SPI_MISO	PTBDD_PTBDD4	/* output */

/* PORT C Data Direction Register */

#define D_LED0		PTCDD_PTCDD0	/* SCI2 TX output */
#define D_LED1		PTCDD_PTCDD1	/* SCI2 RX input */
#define D_LED2		PTCDD_PTCDD2	/* output */
#define D_LED3		PTCDD_PTCDD3	/* output */
#define D_LED4		PTCDD_PTCDD4	/* output */
#define D_LED5		PTCDD_PTCDD5	/* output */
#define D_COM_ENABLE PTCDD_PTCDD5	/* output */

/* PORT D Data Direction Register */

#define D_WIZNET_RST PTDDD_PTDDD0	/* input */
#define D_SPI_CS	PTDDD_PTDDD1	/* input */
#define D_PSHBUTT2	PTDDD_PTDDD2	/* input */
#define D_PSHBUTT3	PTDDD_PTDDD3	/* input */

/* PORT E Data Direction Register */

#define D_LED6		PTEDD_PTEDD6	/* output */
#define D_LED7		PTEDD_PTEDD7	/* output */

/* PULL UP REGISTERS */

/* PORT A PullUp Enable Register */

#define P_PSHBUTT0	PTAPE_PTAPE2	/* input */
#define P_PSHBUTT1	PTAPE_PTAPE3	/* input */

/* PORT B PullUp Enable Register */

#if 0
#define P_BATT_LVL		PTBPE_PTBPE0	/* A/D input */
#endif

/* PORT C PullUp Enable Register */

#if 0
#define P_KEYS			PTCPE_PTCPE7	/* input */
#endif

/* PORT D PullUp Enable Register */

#define P_PSHBUTT2	PTDPE_PTDPE2	/* input */
#define P_PSHBUTT3	PTDPE_PTDPE3	/* input */

#if 0
#define P_VAL1PWR		PTDPE_PTDPE7	/* output */
#endif

/* PORT E PullUp Enable Register */

#if 0
#define P_SPI_CS_M		PTEPE_PTEPE6	/* output */
#endif

/* PORT F PullUp Enable Register */

#if 0
#define P_CHRG_CTRL0	PTFPE_PTFPE7	/* output */
#endif

/* PORT G PullUp Enable Register */

#if 0
#define P_CIM_ID3		PTGPE_PTGPE7	/* input */
#endif

void ports_init(void);
void loging_led( void );


#endif






