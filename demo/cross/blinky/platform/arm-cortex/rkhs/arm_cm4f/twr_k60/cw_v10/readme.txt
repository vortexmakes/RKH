/**
\page cross_twr_K60 "Kinetis K60/100Mhz ARM Cortex M-4F processor"

Running Blinky RKH demo on TWR-K60D100M Freescale Cortex M4 demostration board 

This is a guide to how to setup and use the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.

<STRONG>Project organization<\STRONG>

\code

\---cw_v10
    |   
    \---prj	
    |   \---blinky_twr_k60      - Blinky demo CW10 directory.
    +---cm4f                    - CPU inicialization.
    |   bsp.c					- Board support package source file.
    |   bsp.h					- Board support package header file.
    |   gpio.h					- Routines to handle GPIO´s.
    |   readme.txt				- This guide file.
    |   kuart.c					- Routines to handle serial port.
    |   kuart.h					- Serial driver prototipes.

\endcode


<STRONG>Blinky demo BSP<\STRONG>

- Blink state is shown through target board D7 on PA[4].
- Tracing info through UART3_TXD assigned to PC[17] on J8 connector of
  TWR-SER at 115200 8N1.

*/
