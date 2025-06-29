################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Application\ Code/main.c 

OBJS += \
./Core/Application\ Code/main.o 

C_DEPS += \
./Core/Application\ Code/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Application\ Code/main.o: ../Core/Application\ Code/main.c Core/Application\ Code/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"../Core/Application Code" -I../Core/HCSR04 -I../Core/CAN -I../Core/ODrive -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Application Code/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Application-20-Code

clean-Core-2f-Application-20-Code:
	-$(RM) ./Core/Application\ Code/main.d ./Core/Application\ Code/main.o ./Core/Application\ Code/main.su

.PHONY: clean-Core-2f-Application-20-Code

