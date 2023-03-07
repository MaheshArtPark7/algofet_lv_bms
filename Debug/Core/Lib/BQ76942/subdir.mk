################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/BQ76942/bq76942.c 

OBJS += \
./Core/Lib/BQ76942/bq76942.o 

C_DEPS += \
./Core/Lib/BQ76942/bq76942.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/BQ76942/%.o Core/Lib/BQ76942/%.su: ../Core/Lib/BQ76942/%.c Core/Lib/BQ76942/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Core/Inc/App -I../Core/CodeGen/can/source -I../Core/Lib/BQ76942 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-BQ76942

clean-Core-2f-Lib-2f-BQ76942:
	-$(RM) ./Core/Lib/BQ76942/bq76942.d ./Core/Lib/BQ76942/bq76942.o ./Core/Lib/BQ76942/bq76942.su

.PHONY: clean-Core-2f-Lib-2f-BQ76942

