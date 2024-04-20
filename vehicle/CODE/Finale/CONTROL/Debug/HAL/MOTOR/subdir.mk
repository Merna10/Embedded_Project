################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/MOTOR/ac_dc_motor.c \
../HAL/MOTOR/dc_motor.c 

OBJS += \
./HAL/MOTOR/ac_dc_motor.o \
./HAL/MOTOR/dc_motor.o 

C_DEPS += \
./HAL/MOTOR/ac_dc_motor.d \
./HAL/MOTOR/dc_motor.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/MOTOR/%.o: ../HAL/MOTOR/%.c HAL/MOTOR/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


