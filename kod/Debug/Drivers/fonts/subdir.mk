################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/fonts/terminus-12-bold.c \
../Drivers/fonts/terminus-12-normal.c \
../Drivers/fonts/terminus-14-bold.c \
../Drivers/fonts/terminus-14-normal.c \
../Drivers/fonts/terminus-16-bold.c \
../Drivers/fonts/terminus-16-normal.c \
../Drivers/fonts/terminus-18-bold.c \
../Drivers/fonts/terminus-18-normal.c \
../Drivers/fonts/terminus-20-bold.c \
../Drivers/fonts/terminus-20-normal.c \
../Drivers/fonts/terminus-22-bold.c \
../Drivers/fonts/terminus-22-normal.c \
../Drivers/fonts/terminus-24-bold.c \
../Drivers/fonts/terminus-24-normal.c \
../Drivers/fonts/terminus-28-bold.c \
../Drivers/fonts/terminus-28-normal.c \
../Drivers/fonts/terminus-32-bold.c \
../Drivers/fonts/terminus-32-normal.c 

OBJS += \
./Drivers/fonts/terminus-12-bold.o \
./Drivers/fonts/terminus-12-normal.o \
./Drivers/fonts/terminus-14-bold.o \
./Drivers/fonts/terminus-14-normal.o \
./Drivers/fonts/terminus-16-bold.o \
./Drivers/fonts/terminus-16-normal.o \
./Drivers/fonts/terminus-18-bold.o \
./Drivers/fonts/terminus-18-normal.o \
./Drivers/fonts/terminus-20-bold.o \
./Drivers/fonts/terminus-20-normal.o \
./Drivers/fonts/terminus-22-bold.o \
./Drivers/fonts/terminus-22-normal.o \
./Drivers/fonts/terminus-24-bold.o \
./Drivers/fonts/terminus-24-normal.o \
./Drivers/fonts/terminus-28-bold.o \
./Drivers/fonts/terminus-28-normal.o \
./Drivers/fonts/terminus-32-bold.o \
./Drivers/fonts/terminus-32-normal.o 

C_DEPS += \
./Drivers/fonts/terminus-12-bold.d \
./Drivers/fonts/terminus-12-normal.d \
./Drivers/fonts/terminus-14-bold.d \
./Drivers/fonts/terminus-14-normal.d \
./Drivers/fonts/terminus-16-bold.d \
./Drivers/fonts/terminus-16-normal.d \
./Drivers/fonts/terminus-18-bold.d \
./Drivers/fonts/terminus-18-normal.d \
./Drivers/fonts/terminus-20-bold.d \
./Drivers/fonts/terminus-20-normal.d \
./Drivers/fonts/terminus-22-bold.d \
./Drivers/fonts/terminus-22-normal.d \
./Drivers/fonts/terminus-24-bold.d \
./Drivers/fonts/terminus-24-normal.d \
./Drivers/fonts/terminus-28-bold.d \
./Drivers/fonts/terminus-28-normal.d \
./Drivers/fonts/terminus-32-bold.d \
./Drivers/fonts/terminus-32-normal.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/fonts/%.o Drivers/fonts/%.su Drivers/fonts/%.cyclo: ../Drivers/fonts/%.c Drivers/fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/FATFS/App" -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/fonts" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lcd" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/ssd1306" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/stranky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lora" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/obrazky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/bme280" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/widgety" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-fonts

clean-Drivers-2f-fonts:
	-$(RM) ./Drivers/fonts/terminus-12-bold.cyclo ./Drivers/fonts/terminus-12-bold.d ./Drivers/fonts/terminus-12-bold.o ./Drivers/fonts/terminus-12-bold.su ./Drivers/fonts/terminus-12-normal.cyclo ./Drivers/fonts/terminus-12-normal.d ./Drivers/fonts/terminus-12-normal.o ./Drivers/fonts/terminus-12-normal.su ./Drivers/fonts/terminus-14-bold.cyclo ./Drivers/fonts/terminus-14-bold.d ./Drivers/fonts/terminus-14-bold.o ./Drivers/fonts/terminus-14-bold.su ./Drivers/fonts/terminus-14-normal.cyclo ./Drivers/fonts/terminus-14-normal.d ./Drivers/fonts/terminus-14-normal.o ./Drivers/fonts/terminus-14-normal.su ./Drivers/fonts/terminus-16-bold.cyclo ./Drivers/fonts/terminus-16-bold.d ./Drivers/fonts/terminus-16-bold.o ./Drivers/fonts/terminus-16-bold.su ./Drivers/fonts/terminus-16-normal.cyclo ./Drivers/fonts/terminus-16-normal.d ./Drivers/fonts/terminus-16-normal.o ./Drivers/fonts/terminus-16-normal.su ./Drivers/fonts/terminus-18-bold.cyclo ./Drivers/fonts/terminus-18-bold.d ./Drivers/fonts/terminus-18-bold.o ./Drivers/fonts/terminus-18-bold.su ./Drivers/fonts/terminus-18-normal.cyclo ./Drivers/fonts/terminus-18-normal.d ./Drivers/fonts/terminus-18-normal.o ./Drivers/fonts/terminus-18-normal.su ./Drivers/fonts/terminus-20-bold.cyclo ./Drivers/fonts/terminus-20-bold.d ./Drivers/fonts/terminus-20-bold.o ./Drivers/fonts/terminus-20-bold.su ./Drivers/fonts/terminus-20-normal.cyclo ./Drivers/fonts/terminus-20-normal.d ./Drivers/fonts/terminus-20-normal.o ./Drivers/fonts/terminus-20-normal.su ./Drivers/fonts/terminus-22-bold.cyclo ./Drivers/fonts/terminus-22-bold.d ./Drivers/fonts/terminus-22-bold.o ./Drivers/fonts/terminus-22-bold.su ./Drivers/fonts/terminus-22-normal.cyclo ./Drivers/fonts/terminus-22-normal.d ./Drivers/fonts/terminus-22-normal.o ./Drivers/fonts/terminus-22-normal.su ./Drivers/fonts/terminus-24-bold.cyclo ./Drivers/fonts/terminus-24-bold.d ./Drivers/fonts/terminus-24-bold.o ./Drivers/fonts/terminus-24-bold.su ./Drivers/fonts/terminus-24-normal.cyclo ./Drivers/fonts/terminus-24-normal.d ./Drivers/fonts/terminus-24-normal.o ./Drivers/fonts/terminus-24-normal.su ./Drivers/fonts/terminus-28-bold.cyclo ./Drivers/fonts/terminus-28-bold.d ./Drivers/fonts/terminus-28-bold.o ./Drivers/fonts/terminus-28-bold.su ./Drivers/fonts/terminus-28-normal.cyclo ./Drivers/fonts/terminus-28-normal.d ./Drivers/fonts/terminus-28-normal.o ./Drivers/fonts/terminus-28-normal.su ./Drivers/fonts/terminus-32-bold.cyclo ./Drivers/fonts/terminus-32-bold.d ./Drivers/fonts/terminus-32-bold.o ./Drivers/fonts/terminus-32-bold.su ./Drivers/fonts/terminus-32-normal.cyclo ./Drivers/fonts/terminus-32-normal.d ./Drivers/fonts/terminus-32-normal.o ./Drivers/fonts/terminus-32-normal.su

.PHONY: clean-Drivers-2f-fonts

