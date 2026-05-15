################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lora/lora.c 

OBJS += \
./Drivers/lora/lora.o 

C_DEPS += \
./Drivers/lora/lora.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lora/%.o Drivers/lora/%.su Drivers/lora/%.cyclo: ../Drivers/lora/%.c Drivers/lora/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/FATFS/App" -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lcd" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/ssd1306" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/stranky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lora" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/bme280" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/widgety" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/obrazky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/fonts" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lora

clean-Drivers-2f-lora:
	-$(RM) ./Drivers/lora/lora.cyclo ./Drivers/lora/lora.d ./Drivers/lora/lora.o ./Drivers/lora/lora.su

.PHONY: clean-Drivers-2f-lora

