################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
H:/vortex/rkh/source/fwk/src/rkhfwk_bittbl.c \
H:/vortex/rkh/source/fwk/src/rkhfwk_dynevt.c \
H:/vortex/rkh/source/fwk/src/rkhfwk_evtpool.c \
H:/vortex/rkh/source/fwk/src/rkhfwk_sched.c \
H:/vortex/rkh/source/fwk/src/rkhfwk_version.c \
H:/vortex/rkh/source/mempool/src/rkhmempool.c \
H:/vortex/rkh/source/portable/arm-cortex/rkhs/arm_cm3/codered/rkhport.c \
H:/vortex/rkh/source/queue/src/rkhqueue.c \
H:/vortex/rkh/source/sm/src/rkhsm.c \
H:/vortex/rkh/source/sma/src/rkhsma.c \
H:/vortex/rkh/source/sma/src/rkhsma_prio.c \
H:/vortex/rkh/source/sma/src/rkhsma_sync.c \
H:/vortex/rkh/source/tmr/src/rkhtmr.c \
H:/vortex/rkh/source/trc/src/rkhtrc_filter.c \
H:/vortex/rkh/source/trc/src/rkhtrc_record.c \
H:/vortex/rkh/source/trc/src/rkhtrc_stream.c 

OBJS += \
./src/rkh/rkhfwk_bittbl.o \
./src/rkh/rkhfwk_dynevt.o \
./src/rkh/rkhfwk_evtpool.o \
./src/rkh/rkhfwk_sched.o \
./src/rkh/rkhfwk_version.o \
./src/rkh/rkhmempool.o \
./src/rkh/rkhport.o \
./src/rkh/rkhqueue.o \
./src/rkh/rkhsm.o \
./src/rkh/rkhsma.o \
./src/rkh/rkhsma_prio.o \
./src/rkh/rkhsma_sync.o \
./src/rkh/rkhtmr.o \
./src/rkh/rkhtrc_filter.o \
./src/rkh/rkhtrc_record.o \
./src/rkh/rkhtrc_stream.o 

C_DEPS += \
./src/rkh/rkhfwk_bittbl.d \
./src/rkh/rkhfwk_dynevt.d \
./src/rkh/rkhfwk_evtpool.d \
./src/rkh/rkhfwk_sched.d \
./src/rkh/rkhfwk_version.d \
./src/rkh/rkhmempool.d \
./src/rkh/rkhport.d \
./src/rkh/rkhqueue.d \
./src/rkh/rkhsm.d \
./src/rkh/rkhsma.d \
./src/rkh/rkhsma_prio.d \
./src/rkh/rkhsma_sync.d \
./src/rkh/rkhtmr.d \
./src/rkh/rkhtrc_filter.d \
./src/rkh/rkhtrc_record.d \
./src/rkh/rkhtrc_stream.d 


# Each subdirectory must supply rules for building sources it contributes
src/rkh/rkhfwk_bittbl.o: H:/vortex/rkh/source/fwk/src/rkhfwk_bittbl.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhfwk_dynevt.o: H:/vortex/rkh/source/fwk/src/rkhfwk_dynevt.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhfwk_evtpool.o: H:/vortex/rkh/source/fwk/src/rkhfwk_evtpool.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhfwk_sched.o: H:/vortex/rkh/source/fwk/src/rkhfwk_sched.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhfwk_version.o: H:/vortex/rkh/source/fwk/src/rkhfwk_version.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhmempool.o: H:/vortex/rkh/source/mempool/src/rkhmempool.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhport.o: H:/vortex/rkh/source/portable/arm-cortex/rkhs/arm_cm3/codered/rkhport.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhqueue.o: H:/vortex/rkh/source/queue/src/rkhqueue.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhsm.o: H:/vortex/rkh/source/sm/src/rkhsm.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhsma.o: H:/vortex/rkh/source/sma/src/rkhsma.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhsma_prio.o: H:/vortex/rkh/source/sma/src/rkhsma_prio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhsma_sync.o: H:/vortex/rkh/source/sma/src/rkhsma_sync.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhtmr.o: H:/vortex/rkh/source/tmr/src/rkhtmr.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhtrc_filter.o: H:/vortex/rkh/source/trc/src/rkhtrc_filter.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhtrc_record.o: H:/vortex/rkh/source/trc/src/rkhtrc_record.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rkh/rkhtrc_stream.o: H:/vortex/rkh/source/trc/src/rkhtrc_stream.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3XPRESSO___ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


