/*
 * 	seqdefs.h
 */

#ifndef __SEQDEFS_H__
#define __SEQDEFS_H__


/*
 * 	Led codes
 */

enum
{
	NO_LIT,
		CLI_IDLE = NO_LIT,

	CLI_WORKING, 
		SRV_WORKING = CLI_WORKING,

	CLI_WAITING,
	
	CLI_PAUSED,
		SRV_PAUSED = CLI_PAUSED,

	NUM_LEDS
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
	NUM_LEDS_CHN 	= 4
};
	
/*
 * 	Major indices
 */

typedef enum
{
	MAJOR_LED,
	NUM_MAJOR
} MAJOR_ENUM;

#define NUM_SEQ_CHANNELS (NUM_LEDS_CHN)

#endif
