################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mylib/fonts.c \
../mylib/ssd1306.c 

OBJS += \
./mylib/fonts.o \
./mylib/ssd1306.o 

C_DEPS += \
./mylib/fonts.d \
./mylib/ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
mylib/%.o mylib/%.su mylib/%.cyclo: ../mylib/%.c mylib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/user/Desktop/stm32Board/twomotorcontrol/myLibrary" -I"C:/Users/user/Desktop/stm32Board/twomotorcontrol/mylib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-mylib

clean-mylib:
	-$(RM) ./mylib/fonts.cyclo ./mylib/fonts.d ./mylib/fonts.o ./mylib/fonts.su ./mylib/ssd1306.cyclo ./mylib/ssd1306.d ./mylib/ssd1306.o ./mylib/ssd1306.su

.PHONY: clean-mylib

