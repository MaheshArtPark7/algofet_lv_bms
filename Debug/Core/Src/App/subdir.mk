################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/App/app_adc.c \
../Core/Src/App/app_afe.c \
../Core/Src/App/app_can.c \
../Core/Src/App/app_fuel_gauge.c \
../Core/Src/App/app_gpio.c \
../Core/Src/App/app_sys_init.c \
../Core/Src/App/app_task_1000hz.c \
../Core/Src/App/app_task_100hz.c \
../Core/Src/App/app_task_10hz.c \
../Core/Src/App/app_task_1hz.c 

OBJS += \
./Core/Src/App/app_adc.o \
./Core/Src/App/app_afe.o \
./Core/Src/App/app_can.o \
./Core/Src/App/app_fuel_gauge.o \
./Core/Src/App/app_gpio.o \
./Core/Src/App/app_sys_init.o \
./Core/Src/App/app_task_1000hz.o \
./Core/Src/App/app_task_100hz.o \
./Core/Src/App/app_task_10hz.o \
./Core/Src/App/app_task_1hz.o 

C_DEPS += \
./Core/Src/App/app_adc.d \
./Core/Src/App/app_afe.d \
./Core/Src/App/app_can.d \
./Core/Src/App/app_fuel_gauge.d \
./Core/Src/App/app_gpio.d \
./Core/Src/App/app_sys_init.d \
./Core/Src/App/app_task_1000hz.d \
./Core/Src/App/app_task_100hz.d \
./Core/Src/App/app_task_10hz.d \
./Core/Src/App/app_task_1hz.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/App/%.o Core/Src/App/%.su: ../Core/Src/App/%.c Core/Src/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Core/Inc/App -I../Core/Lib/BQ76952 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-App

clean-Core-2f-Src-2f-App:
	-$(RM) ./Core/Src/App/app_adc.d ./Core/Src/App/app_adc.o ./Core/Src/App/app_adc.su ./Core/Src/App/app_afe.d ./Core/Src/App/app_afe.o ./Core/Src/App/app_afe.su ./Core/Src/App/app_can.d ./Core/Src/App/app_can.o ./Core/Src/App/app_can.su ./Core/Src/App/app_fuel_gauge.d ./Core/Src/App/app_fuel_gauge.o ./Core/Src/App/app_fuel_gauge.su ./Core/Src/App/app_gpio.d ./Core/Src/App/app_gpio.o ./Core/Src/App/app_gpio.su ./Core/Src/App/app_sys_init.d ./Core/Src/App/app_sys_init.o ./Core/Src/App/app_sys_init.su ./Core/Src/App/app_task_1000hz.d ./Core/Src/App/app_task_1000hz.o ./Core/Src/App/app_task_1000hz.su ./Core/Src/App/app_task_100hz.d ./Core/Src/App/app_task_100hz.o ./Core/Src/App/app_task_100hz.su ./Core/Src/App/app_task_10hz.d ./Core/Src/App/app_task_10hz.o ./Core/Src/App/app_task_10hz.su ./Core/Src/App/app_task_1hz.d ./Core/Src/App/app_task_1hz.o ./Core/Src/App/app_task_1hz.su

.PHONY: clean-Core-2f-Src-2f-App

