/*
 *	file: unitrzlib.h
 */

#ifndef __UNITRZLIB_H__
#define __UNITRZLIB_H__


#ifdef __cplusplus
extern "C"{
#endif

typedef struct utrz_resp_t
{
    RKH_TE_ID_T e;
    rui32_t line;
    char msg[1024];
}UTRZ_RESP_T;


void unitrazer_init(void);
void tzparser_init(void);

void tzparser_exec( rui8_t d );

void start_log( const char *fname );

UTRZ_RESP_T * unitrazer_get_resp( void );

#ifdef __cplusplus
}
#endif

#endif

