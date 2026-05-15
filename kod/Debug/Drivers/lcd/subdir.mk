################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lcd/ili9486.c \
../Drivers/lcd/lcd_io_gpio8.c \
../Drivers/lcd/stm32_adafruit_lcd.c 

OBJS += \
./Drivers/lcd/ili9486.o \
./Drivers/lcd/lcd_io_gpio8.o \
./Drivers/lcd/stm32_adafruit_lcd.o 

C_DEPS += \
./Drivers/lcd/ili9486.d \
./Drivers/lcd/lcd_io_gpio8.d \
./Drivers/lcd/stm32_adafruit_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lcd/%.o Drivers/lcd/%.su Drivers/lcd/%.cyclo: ../Drivers/lcd/%.c Drivers/lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/FATFS/App" -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lcd" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/ssd1306" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/stranky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lora" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/bme280" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/widgety" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/obrazky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/fonts" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lcd

clean-Drivers-2f-lcd:
	-$(RM) ./Drivers/lcd/ili9486.cyclo ./Drivers/lcd/ili9486.d ./Drivers/lcd/ili9486.o ./Drivers/lcd/ili9486.su ./Drivers/lcd/lcd_io_gpio8.cyclo ./Drivers/lcd/lcd_io_gpio8.d ./Drivers/lcd/lcd_io_gpio8.o ./Drivers/lcd/lcd_io_gpio8.su ./Drivers/lcd/stm32_adafruit_lcd.cyclo ./Drivers/lcd/stm32_adafruit_lcd.d ./Drivers/lcd/stm32_adafruit_lcd.o ./Drivers/lcd/stm32_adafruit_lcd.su

.PHONY: clean-Drivers-2f-lcd

