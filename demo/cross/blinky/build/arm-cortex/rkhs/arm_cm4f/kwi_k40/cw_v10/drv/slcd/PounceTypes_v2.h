/**------------------------------------------------------------------------------------    
  \n 2010 Pounce Embedded  (Copyright)
  \n Pounce Embedded Intellectual Property
       
  \file     	          PounceTypes      
  \author     	          Diego Perez
  \mail		          diego.perez@pounceconsulting.com 
  \version   	          1.0.1
  \date                   03-Noviembre-2010
  \project		  Generico
   
  \description	    Header file used to redefine the variable types and several standard macros
                            used in the majority of programs.
                            Warning: this file should (must) not contain compiler-native macros, if needed, 
                            they should (must) be added in a separate file.
---------------------------------------------------------------------------------------*/
#ifndef _POUNCE_TYPES_H_
#define _POUNCE_TYPES_H_	
    
    /**--------------------------------------
    \brief Redefinition of types
    ---------------------------------------*/
    typedef unsigned char  U08;
    typedef unsigned short U16;
    typedef unsigned long  U32;
    typedef unsigned long long U64;
        
    typedef signed char  S08;
    typedef signed short S16;
    typedef signed long  S32;
    typedef signed long long S64;
        
    typedef unsigned char BOOL;
    
    typedef char * STRING;
    
    /**--------------------------------------
    \brief Bits handling
    ---------------------------------------*/
    typedef union
    {
        U08 u8Flags;
        struct
        {
            U08 _b0  :1;
            U08 _b1  :1;
            U08 _b2  :1;
            U08 _b3  :1;
            U08 _b4  :1;
            U08 _b5  :1;
            U08 _b6  :1;
            U08 _b7  :1;
        }_sBits;
    }_uFlags;
        
    /**--------------------------------------
    \brief Bytes handling
    ---------------------------------------*/
    typedef union
    {
        U32 u32Long;
        U16 u16Short[2];
        U08 u8Byte[4];
    }_uBytes;

    /**--------------------------------------
    \brief State  machine
    ---------------------------------------*/        
    typedef struct 
    {
    	  U08 u8PrevState;
    	  U08 u8NextState;
    	  U08 u8ActualState;
    	  U08 u8ErrorState;
    }_sSM;
            
    /**--------------------------------------
    \brief Manipulation of bits
    ---------------------------------------*/  
    #define SET_BIT(var, bit)                 (var) |= (1<<(bit))
    #define CLEAR_BIT(var, bit)               (var) &= ~(1<<(bit))
    #define QUERY_BIT(var, bit)               (var) & (1<<(bit))
    #define TOGGLE_BIT(var, bit)              (var) ^= (1<<(bit))
    
    /**--------------------------------------
    \brief Pin values
    ---------------------------------------*/       
    #define OUTPUT	(1)
    #define INTPUT	(0)
    
    /**--------------------------------------
    \brief Standard macros
    ---------------------------------------*/      
    #define WAIT()        _asm wait
    #define _NOP          asm(NOP)
    #define _BGND         asm(BGND)
    
    /**--------------------------------------
    \brief Error values
    ---------------------------------------*/      
    #define ERRORx   (1)                      /* R60287: ERROR is defined in MQX file fio.h
                                                         and is used in sprintf()  */
    #define NoERROR (0)	
    
    /**--------------------------------------
    \brief Boolean values
    ---------------------------------------*/  
    #ifndef TRUE
        #define TRUE  (1)
    #endif

    #ifndef FALSE
        #define FALSE (0)
 	  #endif
    
    /**--------------------------------------
    \brief Function pointer
    ---------------------------------------*/        
    typedef void (* pFunc_t) (void);

#endif /** _POUNCE_TYPES_H_ */
