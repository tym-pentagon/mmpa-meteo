################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/fonts/terminus-12-bold.c \
../Core/Src/fonts/terminus-12-normal.c \
../Core/Src/fonts/terminus-14-bold.c \
../Core/Src/fonts/terminus-14-normal.c \
../Core/Src/fonts/terminus-16-bold.c \
../Core/Src/fonts/terminus-16-normal.c \
../Core/Src/fonts/terminus-18-bold.c \
../Core/Src/fonts/terminus-18-normal.c \
../Core/Src/fonts/terminus-20-bold.c \
../Core/Src/fonts/terminus-20-normal.c \
../Core/Src/fonts/terminus-22-bold.c \
../Core/Src/fonts/terminus-22-normal.c \
../Core/Src/fonts/terminus-24-bold.c \
../Core/Src/fonts/terminus-24-normal.c \
../Core/Src/fonts/terminus-28-bold.c \
../Core/Src/fonts/terminus-28-normal.c \
../Core/Src/fonts/terminus-32-bold.c \
../Core/Src/fonts/terminus-32-normal.c 

OBJS += \
./Core/Src/fonts/terminus-12-bold.o \
./Core/Src/fonts/terminus-12-normal.o \
./Core/Src/fonts/terminus-14-bold.o \
./Core/Src/fonts/terminus-14-normal.o \
./Core/Src/fonts/terminus-16-bold.o \
./Core/Src/fonts/terminus-16-normal.o \
./Core/Src/fonts/terminus-18-bold.o \
./Core/Src/fonts/terminus-18-normal.o \
./Core/Src/fonts/terminus-20-bold.o \
./Core/Src/fonts/terminus-20-normal.o \
./Core/Src/fonts/terminus-22-bold.o \
./Core/Src/fonts/terminus-22-normal.o \
./Core/Src/fonts/terminus-24-bold.o \
./Core/Src/fonts/terminus-24-normal.o \
./Core/Src/fonts/terminus-28-bold.o \
./Core/Src/fonts/terminus-28-normal.o \
./Core/Src/fonts/terminus-32-bold.o \
./Core/Src/fonts/terminus-32-normal.o 

C_DEPS += \
./Core/Src/fonts/terminus-12-bold.d \
./Core/Src/fonts/terminus-12-normal.d \
./Core/Src/fonts/terminus-14-bold.d \
./Core/Src/fonts/terminus-14-normal.d \
./Core/Src/fonts/terminus-16-bold.d \
./Core/Src/fonts/terminus-16-normal.d \
./Core/Src/fonts/terminus-18-bold.d \
./Core/Src/fonts/terminus-18-normal.d \
./Core/Src/fonts/terminus-20-bold.d \
./Core/Src/fonts/terminus-20-normal.d \
./Core/Src/fonts/terminus-22-bold.d \
./Core/Src/fonts/terminus-22-normal.d \
./Core/Src/fonts/terminus-24-bold.d \
./Core/Src/fonts/terminus-24-normal.d \
./Core/Src/fonts/terminus-28-bold.d \
./Core/Src/fonts/terminus-28-normal.d \
./Core/Src/fonts/terminus-32-bold.d \
./Core/Src/fonts/terminus-32-normal.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/fonts/%.o Core/Src/fonts/%.su Core/Src/fonts/%.cyclo: ../Core/Src/fonts/%.c Core/Src/fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/FATFS/App" -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lcd" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/ssd1306" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/stranky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/lora" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Drivers/bme280" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/widgety" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/obrazky" -I"C:/Users/markus/Desktop/meteostanice/Kod/displej/nove-menu/Core/Src/fonts" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-fonts

clean-Core-2f-Src-2f-fonts:
	-$(RM) ./Core/Src/fonts/terminus-12-bold.cyclo ./Core/Src/fonts/terminus-12-bold.d ./Core/Src/fonts/terminus-12-bold.o ./Core/Src/fonts/terminus-12-bold.su ./Core/Src/fonts/terminus-12-normal.cyclo ./Core/Src/fonts/terminus-12-normal.d ./Core/Src/fonts/terminus-12-normal.o ./Core/Src/fonts/terminus-12-normal.su ./Core/Src/fonts/terminus-14-bold.cyclo ./Core/Src/fonts/terminus-14-bold.d ./Core/Src/fonts/terminus-14-bold.o ./Core/Src/fonts/terminus-14-bold.su ./Core/Src/fonts/terminus-14-normal.cyclo ./Core/Src/fonts/terminus-14-normal.d ./Core/Src/fonts/terminus-14-normal.o ./Core/Src/fonts/terminus-14-normal.su ./Core/Src/fonts/terminus-16-bold.cyclo ./Core/Src/fonts/terminus-16-bold.d ./Core/Src/fonts/terminus-16-bold.o ./Core/Src/fonts/terminus-16-bold.su ./Core/Src/fonts/terminus-16-normal.cyclo ./Core/Src/fonts/terminus-16-normal.d ./Core/Src/fonts/terminus-16-normal.o ./Core/Src/fonts/terminus-16-normal.su ./Core/Src/fonts/terminus-18-bold.cyclo ./Core/Src/fonts/terminus-18-bold.d ./Core/Src/fonts/terminus-18-bold.o ./Core/Src/fonts/terminus-18-bold.su ./Core/Src/fonts/terminus-18-normal.cyclo ./Core/Src/fonts/terminus-18-normal.d ./Core/Src/fonts/terminus-18-normal.o ./Core/Src/fonts/terminus-18-normal.su ./Core/Src/fonts/terminus-20-bold.cyclo ./Core/Src/fonts/terminus-20-bold.d ./Core/Src/fonts/terminus-20-bold.o ./Core/Src/fonts/terminus-20-bold.su ./Core/Src/fonts/terminus-20-normal.cyclo ./Core/Src/fonts/terminus-20-normal.d ./Core/Src/fonts/terminus-20-normal.o ./Core/Src/fonts/terminus-20-normal.su ./Core/Src/fonts/terminus-22-bold.cyclo ./Core/Src/fonts/terminus-22-bold.d ./Core/Src/fonts/terminus-22-bold.o ./Core/Src/fonts/terminus-22-bold.su ./Core/Src/fonts/terminus-22-normal.cyclo ./Core/Src/fonts/terminus-22-normal.d ./Core/Src/fonts/terminus-22-normal.o ./Core/Src/fonts/terminus-22-normal.su ./Core/Src/fonts/terminus-24-bold.cyclo ./Core/Src/fonts/terminus-24-bold.d ./Core/Src/fonts/terminus-24-bold.o ./Core/Src/fonts/terminus-24-bold.su ./Core/Src/fonts/terminus-24-normal.cyclo ./Core/Src/fonts/terminus-24-normal.d ./Core/Src/fonts/terminus-24-normal.o ./Core/Src/fonts/terminus-24-normal.su ./Core/Src/fonts/terminus-28-bold.cyclo ./Core/Src/fonts/terminus-28-bold.d ./Core/Src/fonts/terminus-28-bold.o ./Core/Src/fonts/terminus-28-bold.su ./Core/Src/fonts/terminus-28-normal.cyclo ./Core/Src/fonts/terminus-28-normal.d ./Core/Src/fonts/terminus-28-normal.o ./Core/Src/fonts/terminus-28-normal.su ./Core/Src/fonts/terminus-32-bold.cyclo ./Core/Src/fonts/terminus-32-bold.d ./Core/Src/fonts/terminus-32-bold.o ./Core/Src/fonts/terminus-32-bold.su ./Core/Src/fonts/terminus-32-normal.cyclo ./Core/Src/fonts/terminus-32-normal.d ./Core/Src/fonts/terminus-32-normal.o ./Core/Src/fonts/terminus-32-normal.su

.PHONY: clean-Core-2f-Src-2f-fonts

