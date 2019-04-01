################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := clean

# All of the sources participating in the build are defined here
-include sources.mk
-include uCOS-II/Source/subdir.mk
-include uCOS-II/Ports/subdir.mk
-include uC-LIBS/subdir.mk
-include uC-CPU/Cache/subdir.mk
-include uC-CPU/ARM-Cortex-A/subdir.mk
-include uC-CPU/subdir.mk
-include HWLIBS/subdir.mk
-include BSP/OS/subdir.mk
-include BSP/ARM_Compiler/subdir.mk
-include BSP/subdir.mk
-include APP/i2c_driver/subdir.mk
-include APP/command_controller/subdir.mk
-include APP/UART/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(SX_UPPER_DEPS)),)
-include $(SX_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: IMU_Positional_Tracking.axf

# Tool invocations
IMU_Positional_Tracking.axf: $(OBJS) C:/Users/mhoule/Documents/PO_tracker/IMUInterfacing/software/IMU_Positional_Tracking/BSP/ARM_COMPILER/scatter.scat $(USER_OBJS) $(LIBS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker 5'
	armlink --cpu=Cortex-A9 --entry=Start --scatter=""C:/Users/mhoule/Documents/PO_tracker/IMUInterfacing/software/IMU_Positional_Tracking/BSP/ARM_COMPILER/scatter.scat"" --info=sizes -o "IMU_Positional_Tracking.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS) $(S_DEPS) $(C_DEPS) $(CC_DEPS) $(SX_DEPS) $(ASM_UPPER_DEPS) $(C++_DEPS) $(EXECUTABLES) $(CXX_DEPS) $(OBJS) $(SX_UPPER_DEPS) $(ASM_DEPS) $(S_UPPER_DEPS) $(CPP_DEPS) IMU_Positional_Tracking.axf 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
