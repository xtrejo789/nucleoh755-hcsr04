################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/HCSR04/hcsr04.c 

OBJS += \
./Core/HCSR04/hcsr04.o 

C_DEPS += \
./Core/HCSR04/hcsr04.d 


# Each subdirectory must supply rules for building sources it contributes
Core/HCSR04/hcsr04.o: ../Core/HCSR04/hcsr04.c Core/HCSR04/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"../Core/Application Code" -I../Core/HCSR04 -I../Core/CAN -I../Core/ODrive -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-HCSR04

clean-Core-2f-HCSR04:
	-$(RM) ./Core/HCSR04/hcsr04.d ./Core/HCSR04/hcsr04.o ./Core/HCSR04/hcsr04.su

.PHONY: clean-Core-2f-HCSR04

