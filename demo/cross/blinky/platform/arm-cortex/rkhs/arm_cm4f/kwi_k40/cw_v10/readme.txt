/**
\page cross_kwi_K40 "Kinetis K40/100Mhz ARM Cortex M-4F processor"

Running Blinky RKH demo on KWIKSTIK-K40 Freescale Cortex M4 demostration board 

This is a guide to how to setup and use the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.

<STRONG>Project organization<\STRONG>

\code

\---cw_v10
    |   
    \---prj	
    |   \---blinky_twr_k40      - Blinky demo CW10 directory.
    +---cm4f                    - CPU inicialization.
    \---drv
        \---kuart               - Kinetis UART driver. 
        \---slcd                - SLCD driver from KWISTIK-DEMO
        \---sleep               - miliseconds time delay.

\endcode


<STRONG>Blinky demo BSP<\STRONG>

- Blink state is shown through target board LCD, texts ON/OFF are
  shown according to the blink state on/off.
- Tracing info through UART5_TXD assigned to PTE.8 available on TWR header A.44
  compatible with TWR-SER board at 115200 8N1.

*/
