################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/obrazky/domecek.c \
../Core/Src/obrazky/magnet.c \
../Core/Src/obrazky/oblak.c \
../Core/Src/obrazky/sd_karta.c \
../Core/Src/obrazky/vitr.c 

OBJS += \
./Core/Src/obrazky/domecek.o \
./Core/Src/obrazky/magnet.o \
./Core/Src/obrazky/oblak.o \
./Core/Src/obrazky/sd_karta.o \
./Core/Src/obrazky/vitr.o 

C_DEPS += \
./Core/Src/obrazky/domecek.d \
./Core/Src/obrazky/magnet.d \
./Core/Src/obrazky/oblak.d \
./Core/Src/obrazky/sd_karta.d \
./Core/Src/obrazky/vitr.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/obrazky/%.o Core/Src/obrazky/%.su Core/Src/obrazky/%.cyclo: ../Core/Src/obrazky/%.c Core/Src/obrazky/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/FATFS/App" -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lcd" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/ssd1306" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/stranky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lora" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/bme280" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/widgety" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/obrazky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/fonts" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-obrazky

clean-Core-2f-Src-2f-obrazky:
	-$(RM) ./Core/Src/obrazky/domecek.cyclo ./Core/Src/obrazky/domecek.d ./Core/Src/obrazky/domecek.o ./Core/Src/obrazky/domecek.su ./Core/Src/obrazky/magnet.cyclo ./Core/Src/obrazky/magnet.d ./Core/Src/obrazky/magnet.o ./Core/Src/obrazky/magnet.su ./Core/Src/obrazky/oblak.cyclo ./Core/Src/obrazky/oblak.d ./Core/Src/obrazky/oblak.o ./Core/Src/obrazky/oblak.su ./Core/Src/obrazky/sd_karta.cyclo ./Core/Src/obrazky/sd_karta.d ./Core/Src/obrazky/sd_karta.o ./Core/Src/obrazky/sd_karta.su ./Core/Src/obrazky/vitr.cyclo ./Core/Src/obrazky/vitr.d ./Core/Src/obrazky/vitr.o ./Core/Src/obrazky/vitr.su

.PHONY: clean-Core-2f-Src-2f-obrazky

