/**
\page cross_twrk60_ucosiii TWR-K60N512 for K60 processor
\image html rkh_bunner.jpg

Running Shared RKH demo on Freescale <A HREF="http://www.nxp.com/products/
microcontrollers-and-processors/arm-processors/kinetis-cortex-m-mcus/
k-series-performance-m4/k6x-ethernet/kinetis-k60-100-mhz-mixed-signal-
integration-microcontrollers-mcus-based-on-arm-cortex-m4-core:K60_100">
K60D100</A> demostration 
<A HREF="http://www.nxp.com/products/microcontrollers-and-processors/
arm-processors/kinetis-cortex-m-mcus/k-series-performance-m4/k6x-ethernet/
iar-kickstart-kinetis-k60-tower-system-ki:TWR-K60N512">TWR-K60N512</A>.
This is a guide to how to setup the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.
On this demo, multithreading is reach through RKH uCosIII port.

<STRONG>Folder tree</STRONG>

\code
\-frdm-k64f\kds\
    \-board			
       \-arm_cm4f\twr-k60n512\
          +-bsp     - MCU inicialization and Drivers.
          +-prj     - IAR V7_2 "shared" project.
    +-micrium   	- uCosIII kernel source code.
    |  bsp.c		- Board support package source file.
    |  bsp.h		- Board support package header file.
    |  includes.h	- uCosIII includes dependencies.
    |  os_cfg.h		- uCosIII configuration file.
    |  os_cfg_app.h	- Application specific uCosIII configuration file.
    |  cpu_cfg.h	- CPU specific uCosIII configuration file.
    |  readme.txt	- This guide file.
\endcode

<STRONG>Shared demo BSP</STRONG>
	
- The Led's D7 D8 D11 D12 shown which client request is running on server.
- Pressing SW1 button introduce a PAUSE event.
- Tracing info through SDA Virtual COM interface at 115200 8N1.

*/
