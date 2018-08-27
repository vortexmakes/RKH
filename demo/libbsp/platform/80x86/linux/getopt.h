/*
 * Newsgroups: mod.std.unix
 * Subject: public domain AT&T getopt source
 * Date: 3 Nov 85 19:34:15 GMT

 * Here's something you've all been waiting for:  the AT&T public domain
 * source for getopt(3).  It is the code which was given out at the 1985
 * UNIFORUM conference in Dallas.  I obtained it by electronic mail
 * directly from AT&T.  The people there assure me that it is indeed
 * in the public domain.
 */

/*LINTLIBRARY*/

/**
 *  \file       getopt.h
 *  \brief
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Module -------------------------------- */
#ifndef __GETOPT_H__
#define __GETOPT_H__

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
extern int optind;
extern char *optarg;

/* -------------------------- Function prototypes -------------------------- */
int getopt(int argc, char **argv, char *opts);
char * get_next(char **argv);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */
