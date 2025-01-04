################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../myLibrary/fonts.c \
../myLibrary/ssd1306.c 

OBJS += \
./myLibrary/fonts.o \
./myLibrary/ssd1306.o 

C_DEPS += \
./myLibrary/fonts.d \
./myLibrary/ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
myLibrary/%.o myLibrary/%.su myLibrary/%.cyclo: ../myLibrary/%.c myLibrary/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/user/Desktop/stm32Board/encoder_read_using_oled/myLibrary" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-myLibrary

clean-myLibrary:
	-$(RM) ./myLibrary/fonts.cyclo ./myLibrary/fonts.d ./myLibrary/fonts.o ./myLibrary/fonts.su ./myLibrary/ssd1306.cyclo ./myLibrary/ssd1306.d ./myLibrary/ssd1306.o ./myLibrary/ssd1306.su

.PHONY: clean-myLibrary

