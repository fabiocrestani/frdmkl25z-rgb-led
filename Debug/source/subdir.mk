################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/leds.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/timer.c \
../source/tpm_pwm_twochannel.c \
../source/ws2812b.c 

OBJS += \
./source/leds.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/timer.o \
./source/tpm_pwm_twochannel.o \
./source/ws2812b.o 

C_DEPS += \
./source/leds.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/timer.d \
./source/tpm_pwm_twochannel.d \
./source/ws2812b.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DDEBUG -DFRDM_KL25Z -DFREEDOM -D__MCUXPRESSO -D__USE_CMSIS -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


