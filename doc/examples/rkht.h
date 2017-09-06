/* ------------------------------- Data types ------------------------------ */
/*
 * 	The RKH uses a set of integer quantities. That maybe machine or 
 * 	compiler dependent.
 */

typedef signed char 	ri8_t;      /* Denotes a signed integer type with a */
                                    /* width of exactly 8 bits */
typedef signed short 	ri16_t;     /* Denotes a signed integer type with a */
                                    /* width of exactly 16 bits */
typedef signed long		ri32_t;     /* Denotes a signed integer type with a */
                                    /* width of exactly 32 bits */
typedef unsigned char 	rui8_t;     /* Denotes a unsigned integer type with */
                                    /* a width of exactly 8 bits */
typedef unsigned short 	rui16_t;    /* Denotes a unsigned integer type with */
                                    /* a width of exactly 16 bits */
typedef unsigned long	rui32_t;    /* Denotes a unsigned integer type with */
                                    /* a width of exactly 32 bits */

/*
 * 	The 'ruint' and 'rInt' will normally be the natural size for a 
 * 	particular machine. These types designates an integer type that is 
 * 	usually fastest to operate with among all integer types.
 */
typedef unsigned int	ruint;
typedef signed int		rInt;

/*
 * 	Boolean data type and constants.
 *
 * 	\note
 * 	The true (RKH_TRUE) and false (RKH_FALSE) values as defined as macro 
 * 	definitions in \c rkhdef.h file.
 */
typedef unsigned int	rbool_t;
