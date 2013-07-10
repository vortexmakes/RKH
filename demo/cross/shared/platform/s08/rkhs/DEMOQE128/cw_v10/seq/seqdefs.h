/*
 * 	seqdefs.h
 */

#ifndef __SEQDEFS_H__
#define __SEQDEFS_H__

/*
 * 	Tones codes
 */

enum
{
	NO_TONE,	

	DIAL_TONE, ERROR_TONE, SUCCESS_TONE, MENU_ENTRY_TONE,
	SETUP_ENTRY_TONE, VOICE_MSG_TONE, RING_TONE, BUSY_TONE, CALL_WAIT_TONE,
	LOCK_TONE, BATTERY_TONE, DATA_MODE_TONE, USB_MODE_TONE,
	SIM_PIN_TONE, NO_SERVICE_TONE,
	WAIT_TONE,

	NUM_TONES
};

/*
 * 	Ring codes
 */

enum
{
	NO_RING,
	NORMAL_RING,	ACCEPT_RING,	LOST_RING,
	NUM_RINGS
};

/*
 * 	Led codes
 */

enum
{
	NO_LIT,
		VOICE = NO_LIT, UNUSED = NO_LIT, NOMSGRCV = NO_LIT,
	LINE_BATT,
		IN_USE = LINE_BATT,	DATA232 = LINE_BATT, SIGNAL_STRENGTH = LINE_BATT,
		MSGRCV = LINE_BATT,     HSPA_MOD = LINE_BATT,
	LINE_BATTCHG,
		DATAUSB = LINE_BATTCHG, NOSRV = LINE_BATTCHG, UNUSED_FD = LINE_BATTCHG,
	LINE_NOBATT,
    IN_USE_FD = LINE_NOBATT,
  NOLINE_BATT, NOLINE_BATTDIS, STATUS_CODE,
  GPRS_MOD, EDGE_MOD, UMTS_MOD,

	NUM_LEDS
};
enum
{
	DATA_MODE2 = NUM_TONES, USB_MODE2, PIN_MODE2,
	NO_SER_MODE2,

	NUM_TOTAL_TONES
};

/*
 * 	Addressed from main rings
 */

enum
{
	LOST_RING2 = NUM_RINGS,
	NUM_TOTAL_RINGS
};

/*
 * 	Addressed by main led sequences
 */

enum
{
	NUM_TOTAL_LEDS = NUM_LEDS
};

/*
 * 	Minor indices
 */

enum
{
	NUM_TONE_CHN 	= 1,
	NUM_RING_CHN 	= 1,
	NUM_LEDS_CHN 	= 9
};
	
/*
 * 	Major indices
 */

typedef enum
{
	MAJOR_TONE, MAJOR_RING, MAJOR_LED,
	NUM_MAJOR
} MAJOR_ENUM;

#define NUM_SEQ_CHANNELS (NUM_TONE_CHN + NUM_RING_CHN +	NUM_LEDS_CHN)

#endif
