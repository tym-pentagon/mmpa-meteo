################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SD/SD.c 

OBJS += \
./Drivers/SD/SD.o 

C_DEPS += \
./Drivers/SD/SD.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SD/%.o Drivers/SD/%.su Drivers/SD/%.cyclo: ../Drivers/SD/%.c Drivers/SD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/fonts" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lcd" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/ssd1306" -I../Middlewares/Third_Party/FatFs/src -I../FATFS/App -I../FATFS/Target -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/SD" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SD

clean-Drivers-2f-SD:
	-$(RM) ./Drivers/SD/SD.cyclo ./Drivers/SD/SD.d ./Drivers/SD/SD.o ./Drivers/SD/SD.su

.PHONY: clean-Drivers-2f-SD

