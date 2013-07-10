/*
 *  seqtbl.c
 *   Tables of sequences
 */

#include "mytypes.h"
#include "seqtbl.h"
#include "seqlog.h"
#include "seqdefs.h"


static const SEQ_T tones_t[] =
{
  /*
   *  Main tones
   */
  { UNIQ|NO_ARG, NO_ARG, 0,  0,  0,   0,  ONE_SHOT  },  /* NO_TONE   */
  { FREQ_A,  NO_ARG, 30,  0, 0,  0, DIAL_TONE  },  /* DIAL_TONE  */
  { UNIQ|FREQ_A, NO_ARG, 1,  1, 8,  0,  ONE_SHOT  },  /* ERROR_TONE  */
  { UNIQ|FREQ_A, NO_ARG, 7,  0, 0,  0,  ONE_SHOT  },  /* SUCCESS_TONE */
  { UNIQ|FREQ_A, NO_ARG, 6,  2, 2,  0,  ONE_SHOT   },  /* MENU_ENTRY_TONE */
  { UNIQ|FREQ_A, NO_ARG, 6,  2, 2,  0,  ONE_SHOT   },  /* SETUP_ENTRY_TONE*/
  { FREQ_A,  NO_ARG, 20,  40, 1,  60, VOICE_MSG_TONE  },  /* VOICE_MSG_TONE */
  { FREQ_A,  NO_ARG, 20,  40, 1,  60, RING_TONE   },  /* RING_TONE  */
  { FREQ_A,  NO_ARG, 3,  3, 1,  6, BUSY_TONE   },  /* BUSY_TONE  */
  { UNIQ|FREQ_A, NO_ARG, 3,  3, 2,  0, ONE_SHOT  },  /* CALL_WAIT_TONE */
  { FREQ_A,  NO_ARG, 3,  3, 1,  6, LOCK_TONE  },  /* LOCK_TONE  */
  { FREQ_A,  NO_ARG, 3,  3, 4,  600,BATTERY_TONE },  /* BATTERY_TONE */
  { FREQ_A,  NO_ARG, 10,  0, 0,  0, DATA_MODE2   },  /* DATA_MODE_TONE */
  { FREQ_A,  NO_ARG, 10,  0, 0,  0, USB_MODE2   },  /* USB_MODE_TONE */
  { FREQ_A,  NO_ARG, 3,  0, 0,  0,  PIN_MODE2   },  /* SIM_PIN_TONE */
  { FREQ_A,  NO_ARG, 3,  0, 0,  0,  NO_SER_MODE2 },  /* NO_SERVICE_TONE */
  { FREQ_A,  NO_ARG, 1,  1, 2,  30, WAIT_TONE  },  /* WAIT_TONE  */

  /*
   *  Addressed from main tones
   */
  { FREQ_B, NO_ARG, 5,  0, 0,  0, DATA_MODE_TONE  },  /* DATA_MODE2  */
  { FREQ_B, NO_ARG, 5,  0, 0,  0, USB_MODE_TONE  },  /* USB_MODE2  */
  { FREQ_B, NO_ARG, 3,  0, 0,  0,  SIM_PIN_TONE  },  /* PIN_MODE2  */
  { FREQ_B, NO_ARG, 3,  0, 0,  0,  NO_SERVICE_TONE }  /* NO_SER_MODE2 */
};

static const SEQ_T rings_t[] =
{
  { UNIQ|NO_ARG, NO_ARG, 0,  0,  0,   0,  ONE_SHOT  },  /* NO_RING   */
  { RING_ON,  NO_ARG, 10,  1, 1,     60, NORMAL_RING  },  /* NORMAL_RING  */
  { UNIQ|RING_ON, NO_ARG, 10,  1, 1,  20, ONE_SHOT  },  /* ACCEPT_RING  */
  { RING_ON,  NO_ARG, 5,  2,  4,    40, LOST_RING2  },  /* LOST_RING  */
  /*
   *  Addressed from main rings
   */
  { RING_ON, NO_ARG,  10,  5, 2,  40, LOST_RING  }  /* LOST_RING2  */
};

static const SEQ_T leds_t[] =
{
  /*  NO_LIT, VOICE,  MSGRCV      */
  { UNIQ|NO_ARG,         NO_ARG, 0,  0, 0,  0,  ONE_SHOT  },
  /* LINE_BATT, IN_USE, DATA232, SIGNAL_STRENGTH, HSPA_MOD       */
  { LED_ON,  NO_ARG, 1,  0, 1,  1,  LINE_BATT  },  
  /* LINE_BATTCHG, DATAUSB, NOSVC */
  { LED_ON,  NO_ARG, 1,  19, 1,  20, LINE_BATTCHG },  
  /* LINE_NOBATT     */
  { LED_ON,  NO_ARG, 1,  1, 3,  40, LINE_NOBATT  },  
  /* NOLINE_BATT     */
  { LED_ON,  NO_ARG, 10,  30, 1,  40, NOLINE_BATT  },  
  /* NOLINE_BATTDIS */
  { LED_ON,  NO_ARG, 3,  7, 1,  10, NOLINE_BATTDIS },  
  /*  STATUS_CODE  */
  { LED_ON,  NO_ARG, 2,  2, 1,  4,  STATUS_CODE  },  

  { LED_ON,  NO_ARG, 1,  1, 1,  40, GPRS_MOD            },
  { LED_ON,  NO_ARG, 1,  1, 2,  40, EDGE_MOD            },
  { LED_ON,  NO_ARG, 1,  1, 3,  40, UMTS_MOD            },
};

const MAJOR_T majors_t[ NUM_MAJOR ] =
{
  { set_hard_tone, tones_t, NUM_TONE_CHN, NUM_TONES },
  { set_hard_ring, rings_t, NUM_RING_CHN, NUM_RINGS },
  { set_hard_leds, leds_t,  NUM_LEDS_CHN, NUM_LEDS }
};


