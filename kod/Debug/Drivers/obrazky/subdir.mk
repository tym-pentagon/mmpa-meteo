################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/obrazky/domecek.c \
../Drivers/obrazky/magnet.c \
../Drivers/obrazky/oblak.c \
../Drivers/obrazky/sd_karta.c \
../Drivers/obrazky/vitr.c 

OBJS += \
./Drivers/obrazky/domecek.o \
./Drivers/obrazky/magnet.o \
./Drivers/obrazky/oblak.o \
./Drivers/obrazky/sd_karta.o \
./Drivers/obrazky/vitr.o 

C_DEPS += \
./Drivers/obrazky/domecek.d \
./Drivers/obrazky/magnet.d \
./Drivers/obrazky/oblak.d \
./Drivers/obrazky/sd_karta.d \
./Drivers/obrazky/vitr.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/obrazky/%.o Drivers/obrazky/%.su Drivers/obrazky/%.cyclo: ../Drivers/obrazky/%.c Drivers/obrazky/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/FATFS/App" -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/fonts" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lcd" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/ssd1306" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/stranky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lora" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/obrazky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/bme280" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/widgety" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-obrazky

clean-Drivers-2f-obrazky:
	-$(RM) ./Drivers/obrazky/domecek.cyclo ./Drivers/obrazky/domecek.d ./Drivers/obrazky/domecek.o ./Drivers/obrazky/domecek.su ./Drivers/obrazky/magnet.cyclo ./Drivers/obrazky/magnet.d ./Drivers/obrazky/magnet.o ./Drivers/obrazky/magnet.su ./Drivers/obrazky/oblak.cyclo ./Drivers/obrazky/oblak.d ./Drivers/obrazky/oblak.o ./Drivers/obrazky/oblak.su ./Drivers/obrazky/sd_karta.cyclo ./Drivers/obrazky/sd_karta.d ./Drivers/obrazky/sd_karta.o ./Drivers/obrazky/sd_karta.su ./Drivers/obrazky/vitr.cyclo ./Drivers/obrazky/vitr.d ./Drivers/obrazky/vitr.o ./Drivers/obrazky/vitr.su

.PHONY: clean-Drivers-2f-obrazky

