################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../myLibrary/VL53L0X.c \
../myLibrary/blink.c 

OBJS += \
./myLibrary/VL53L0X.o \
./myLibrary/blink.o 

C_DEPS += \
./myLibrary/VL53L0X.d \
./myLibrary/blink.d 


# Each subdirectory must supply rules for building sources it contributes
myLibrary/%.o myLibrary/%.su myLibrary/%.cyclo: ../myLibrary/%.c myLibrary/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/user/Desktop/stm32Board/exled/myLibrary" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-myLibrary

clean-myLibrary:
	-$(RM) ./myLibrary/VL53L0X.cyclo ./myLibrary/VL53L0X.d ./myLibrary/VL53L0X.o ./myLibrary/VL53L0X.su ./myLibrary/blink.cyclo ./myLibrary/blink.d ./myLibrary/blink.o ./myLibrary/blink.su

.PHONY: clean-myLibrary

