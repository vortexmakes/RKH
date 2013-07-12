/*
 *  seqtbl.c
 *   Tables of sequences
 */

#include "mytypes.h"
#include "seqtbl.h"
#include "seqlog.h"
#include "seqdefs.h"



static const SEQ_T leds_t[] =
{
  /* CLI_IDLE */
  { UNIQ|NO_ARG,	NO_ARG, 0,  0, 0,  0,	ONE_SHOT  },
  /* CLI_WORKING */
  { LED_ON,  		NO_ARG, 1,  0, 1,  1,	CLI_WORKING  },  
  /* CLI_WAITING */
  { LED_ON,			NO_ARG, 2,  2, 1,  4,	CLI_WAITING },
  /* CLI_PAUSED */
  { LED_ON,			NO_ARG, 6,  4, 3,  40,	CLI_PAUSED }
};

const MAJOR_T majors_t[ NUM_MAJOR ] =
{
  { set_hard_leds, leds_t,  NUM_LEDS_CHN, NUM_LEDS }
};


