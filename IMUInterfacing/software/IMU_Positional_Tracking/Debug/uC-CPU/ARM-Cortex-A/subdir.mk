################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../uC-CPU/ARM-Cortex-A/cpu_a.s 

S_DEPS += \
./uC-CPU/ARM-Cortex-A/cpu_a.d 

OBJS += \
./uC-CPU/ARM-Cortex-A/cpu_a.o 


# Each subdirectory must supply rules for building sources it contributes
uC-CPU/ARM-Cortex-A/cpu_a.o: ../uC-CPU/ARM-Cortex-A/cpu_a.s
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Assembler 5'
	armasm --cpu=Cortex-A9 --no_unaligned_access -g --md --depend_format=unix_escaped --depend="uC-CPU/ARM-Cortex-A/cpu_a.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


