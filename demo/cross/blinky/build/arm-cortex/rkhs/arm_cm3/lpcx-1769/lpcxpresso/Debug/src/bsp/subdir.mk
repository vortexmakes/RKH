################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
H:/vortex/rkh/demo/libbsp/platform/arm-cortex/arm_cm3/lpc17xx/bsp_blinky.c \
H:/vortex/rkh/demo/libbsp/platform/arm-cortex/arm_cm3/lpc17xx/uart.c 

OBJS += \
./src/bsp/bsp_blinky.o \
./src/bsp/uart.o 

C_DEPS += \
./src/bsp/bsp_blinky.d \
./src/bsp/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/bsp_blinky.o: H:/vortex/rkh/demo/libbsp/platform/arm-cortex/arm_cm3/lpc17xx/bsp_blinky.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3CRED__ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/uart.o: H:/vortex/rkh/demo/libbsp/platform/arm-cortex/arm_cm3/lpc17xx/uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__ARM_CM3CRED__ -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/common" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../libbsp/platform/arm-cortex/arm_cm3/lpc17xx" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sma/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/tmr/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/trc/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/mempool/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/fwk/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/queue/inc" -I"H:/vortex/rkh/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso../../../../../../../../../../source/sm/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


