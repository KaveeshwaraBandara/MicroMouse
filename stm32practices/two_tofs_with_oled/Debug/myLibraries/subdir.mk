################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../myLibraries/VL53L0X.c \
../myLibraries/fonts.c \
../myLibraries/ssd1306.c 

OBJS += \
./myLibraries/VL53L0X.o \
./myLibraries/fonts.o \
./myLibraries/ssd1306.o 

C_DEPS += \
./myLibraries/VL53L0X.d \
./myLibraries/fonts.d \
./myLibraries/ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
myLibraries/%.o myLibraries/%.su myLibraries/%.cyclo: ../myLibraries/%.c myLibraries/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/user/Desktop/stm32Board/two_tofs_with_oled/myLibraries" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-myLibraries

clean-myLibraries:
	-$(RM) ./myLibraries/VL53L0X.cyclo ./myLibraries/VL53L0X.d ./myLibraries/VL53L0X.o ./myLibraries/VL53L0X.su ./myLibraries/fonts.cyclo ./myLibraries/fonts.d ./myLibraries/fonts.o ./myLibraries/fonts.su ./myLibraries/ssd1306.cyclo ./myLibraries/ssd1306.d ./myLibraries/ssd1306.o ./myLibraries/ssd1306.su

.PHONY: clean-myLibraries

