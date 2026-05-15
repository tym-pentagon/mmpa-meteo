################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/stranky/atmosfera.c \
../Core/Src/stranky/hlavni_menu.c 

OBJS += \
./Core/Src/stranky/atmosfera.o \
./Core/Src/stranky/hlavni_menu.o 

C_DEPS += \
./Core/Src/stranky/atmosfera.d \
./Core/Src/stranky/hlavni_menu.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/stranky/%.o Core/Src/stranky/%.su Core/Src/stranky/%.cyclo: ../Core/Src/stranky/%.c Core/Src/stranky/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/FATFS/App" -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lcd" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/ssd1306" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/stranky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lora" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/bme280" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/widgety" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/obrazky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/fonts" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-stranky

clean-Core-2f-Src-2f-stranky:
	-$(RM) ./Core/Src/stranky/atmosfera.cyclo ./Core/Src/stranky/atmosfera.d ./Core/Src/stranky/atmosfera.o ./Core/Src/stranky/atmosfera.su ./Core/Src/stranky/hlavni_menu.cyclo ./Core/Src/stranky/hlavni_menu.d ./Core/Src/stranky/hlavni_menu.o ./Core/Src/stranky/hlavni_menu.su

.PHONY: clean-Core-2f-Src-2f-stranky

