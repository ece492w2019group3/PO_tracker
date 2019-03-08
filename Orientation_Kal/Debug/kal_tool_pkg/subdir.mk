################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kal_tool_pkg/AHRSFilterBase.c \
../kal_tool_pkg/IMUFusionCommon.c \
../kal_tool_pkg/NED.c \
../kal_tool_pkg/conj.c \
../kal_tool_pkg/kal_tool.c \
../kal_tool_pkg/kal_tool_initialize.c \
../kal_tool_pkg/kal_tool_rtwutil.c \
../kal_tool_pkg/kal_tool_terminate.c \
../kal_tool_pkg/mrdivide_helper.c \
../kal_tool_pkg/mtimes.c \
../kal_tool_pkg/norm1.c \
../kal_tool_pkg/normalize.c \
../kal_tool_pkg/quaternioncg.c \
../kal_tool_pkg/rotmat.c \
../kal_tool_pkg/rtGetInf.c \
../kal_tool_pkg/rtGetNaN.c \
../kal_tool_pkg/rt_nonfinite.c \
../kal_tool_pkg/uminus.c 

OBJS += \
./kal_tool_pkg/AHRSFilterBase.o \
./kal_tool_pkg/IMUFusionCommon.o \
./kal_tool_pkg/NED.o \
./kal_tool_pkg/conj.o \
./kal_tool_pkg/kal_tool.o \
./kal_tool_pkg/kal_tool_initialize.o \
./kal_tool_pkg/kal_tool_rtwutil.o \
./kal_tool_pkg/kal_tool_terminate.o \
./kal_tool_pkg/mrdivide_helper.o \
./kal_tool_pkg/mtimes.o \
./kal_tool_pkg/norm1.o \
./kal_tool_pkg/normalize.o \
./kal_tool_pkg/quaternioncg.o \
./kal_tool_pkg/rotmat.o \
./kal_tool_pkg/rtGetInf.o \
./kal_tool_pkg/rtGetNaN.o \
./kal_tool_pkg/rt_nonfinite.o \
./kal_tool_pkg/uminus.o 

C_DEPS += \
./kal_tool_pkg/AHRSFilterBase.d \
./kal_tool_pkg/IMUFusionCommon.d \
./kal_tool_pkg/NED.d \
./kal_tool_pkg/conj.d \
./kal_tool_pkg/kal_tool.d \
./kal_tool_pkg/kal_tool_initialize.d \
./kal_tool_pkg/kal_tool_rtwutil.d \
./kal_tool_pkg/kal_tool_terminate.d \
./kal_tool_pkg/mrdivide_helper.d \
./kal_tool_pkg/mtimes.d \
./kal_tool_pkg/norm1.d \
./kal_tool_pkg/normalize.d \
./kal_tool_pkg/quaternioncg.d \
./kal_tool_pkg/rotmat.d \
./kal_tool_pkg/rtGetInf.d \
./kal_tool_pkg/rtGetNaN.d \
./kal_tool_pkg/rt_nonfinite.d \
./kal_tool_pkg/uminus.d 


# Each subdirectory must supply rules for building sources it contributes
kal_tool_pkg/%.o: ../kal_tool_pkg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


