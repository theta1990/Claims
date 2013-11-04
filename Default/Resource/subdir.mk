################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Resource/NodeTracker.cpp \
../Resource/ResourceInfo.cpp \
../Resource/ResourceManagerMaster.cpp \
../Resource/ResourceManagerSlave.cpp 

OBJS += \
./Resource/NodeTracker.o \
./Resource/ResourceInfo.o \
./Resource/ResourceManagerMaster.o \
./Resource/ResourceManagerSlave.o 

CPP_DEPS += \
./Resource/NodeTracker.d \
./Resource/ResourceInfo.d \
./Resource/ResourceManagerMaster.d \
./Resource/ResourceManagerSlave.d 


# Each subdirectory must supply rules for building sources it contributes
Resource/%.o: ../Resource/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


