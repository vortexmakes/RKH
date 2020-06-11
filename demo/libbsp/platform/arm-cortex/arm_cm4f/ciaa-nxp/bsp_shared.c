/* ------------------------------ File header ------------------------------ */
/*  Use file_header.txt file                                                 */

/* -------------------------- Development history -------------------------- */
/*
 *  2020.06.10  CaMa  v1.0.0  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  CaMa  Carlos Mancòn  manconci@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/*
 *  (1) These notes could be referenced by number.
 *      (1.1) Sub-note.
 *  (2) Another note.
 */

/* ----------------------------- Include files ----------------------------- */
/* (1) #include <string.h>                                                   */
/* (2) #include <other system headers>                                       */
/* (3) #include �user header files�                                          */
#include "rkh.h"
#include "bsp.h"
#include "server.h"
#include "client.h"
#include "shared.h"
#include "board.h"

/* ----------------------------- Local macros ------------------------------ */
/* (1) Function macro defines */

/* ------------------------------- Constants ------------------------------- */
/* (1) Macro defines                                                         */
/* (2) Enumerations                                                          */
/* (3) Local const modifier                                                  */
/* (4) Global (extern or non-static external const modifier)                 */

/* ---------------------------- Local data types --------------------------- */
/* (1) typedefs                                                              */

/* ---------------------------- Global variables --------------------------- */
/* (1) Extern declarations of variables defined in other files.              */
/* (2) Non-static external definitions used in this file (and optionally     */
/*     in others if they are declared in those files using extern).          */

/* ---------------------------- Local variables ---------------------------- */
/* (1) Static external definitions used only in this file.                   */ 

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void bsp_init(int argc, char *argv[]);
void bsp_keyParser(int c);
void bsp_timeTick(void);
rui32_t bsp_rand( void );
void bsp_srand( rui32_t seed );
void bsp_cli_req( rui8_t clino );
void bsp_cli_wait_req( rui8_t clino, RKH_TNT_T req_time );
void bsp_cli_using( rui8_t clino, RKH_TNT_T using_time );
void bsp_cli_paused( rui8_t clino );
void bsp_cli_resumed( rui8_t clino );
void bsp_cli_done( rui8_t clino );
void bsp_svr_recall( rui8_t clino );
void bsp_svr_paused(rui32_t ntot, rui32_t *ncr);
void bsp_svr_start( rui8_t clino );
void bsp_svr_end( void );
void bsp_svr_resume( void );
/* ------------------------------ File footer ------------------------------ */
/*  Use file_footer.txt file                                                 */
