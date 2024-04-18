################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../i2c-lcd/Src/i2c-lcd.c 

OBJS += \
./i2c-lcd/Src/i2c-lcd.o 

C_DEPS += \
./i2c-lcd/Src/i2c-lcd.d 


# Each subdirectory must supply rules for building sources it contributes
i2c-lcd/Src/%.o i2c-lcd/Src/%.su i2c-lcd/Src/%.cyclo: ../i2c-lcd/Src/%.c i2c-lcd/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/1-) MY SOFTWARE FILES AND PROJECTS/PROJECTS/UDEMY/ARM COURSE/STM32CubeIDE/072_I2C_2x16_LCD_HAL/i2c-lcd/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-i2c-2d-lcd-2f-Src

clean-i2c-2d-lcd-2f-Src:
	-$(RM) ./i2c-lcd/Src/i2c-lcd.cyclo ./i2c-lcd/Src/i2c-lcd.d ./i2c-lcd/Src/i2c-lcd.o ./i2c-lcd/Src/i2c-lcd.su

.PHONY: clean-i2c-2d-lcd-2f-Src

