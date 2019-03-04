################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../BSP/ARM_Compiler/armv7a_tthelp.s \
../BSP/ARM_Compiler/bsp_cache.s \
../BSP/ARM_Compiler/startup.s 

S_DEPS += \
./BSP/ARM_Compiler/armv7a_tthelp.d \
./BSP/ARM_Compiler/bsp_cache.d \
./BSP/ARM_Compiler/startup.d 

OBJS += \
./BSP/ARM_Compiler/armv7a_tthelp.o \
./BSP/ARM_Compiler/bsp_cache.o \
./BSP/ARM_Compiler/startup.o 


# Each subdirectory must supply rules for building sources it contributes
BSP/ARM_Compiler/armv7a_tthelp.o: ../BSP/ARM_Compiler/armv7a_tthelp.s
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Assembler 5'
	armasm --cpu=Cortex-A9 --no_unaligned_access -g --md --depend_format=unix_escaped --depend="BSP/ARM_Compiler/armv7a_tthelp.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BSP/ARM_Compiler/bsp_cache.o: ../BSP/ARM_Compiler/bsp_cache.s
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Assembler 5'
	armasm --cpu=Cortex-A9 --no_unaligned_access -g --md --depend_format=unix_escaped --depend="BSP/ARM_Compiler/bsp_cache.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BSP/ARM_Compiler/startup.o: ../BSP/ARM_Compiler/startup.s
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Assembler 5'
	armasm --cpu=Cortex-A9 --no_unaligned_access -g --md --depend_format=unix_escaped --depend="BSP/ARM_Compiler/startup.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


