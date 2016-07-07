/*
 *  This file contains porting mechanism pragmas to port HCS08 code to ColdFire V1.
 *  It is included using #include "porting_support.h" in the preprocessor panel.
 */
 
/* Inline Assembly 
#pragma check_asm    strict | report | skip | reset

given a sequence of inline assembly instructions:
    strict    reports an error on every problem encountered
    report    reports a single message for entire sequence and stops codegen
    skip      assume all instructions are illegal, 
              stops codegen whenever an assembly sequence is found, 
              reports a single message per assembly sequence
    reset     returns to the previous stacked state, stack depth is one.
*/
#pragma check_asm  report         /* report only the first illegal instruction per assembly statement/routine */

/* Absolute Definitions
#pragma warn_absolute    on | off | reset

if on a literal index trigger a warning, macros will not. 
The checking for these will be limited to non .h files in an attempt to limit erroneous reports.
*/
#pragma warn_absolute on           /* report definitions with absolute addresses user code */
 
/* Pointer Cast
#pragma warn_any_ptr_int_conv on | off

if on the compiler warns about these accesses.
*/
#pragma warn_any_ptr_int_conv off   /* report casting of absolute addresses to pointers */

