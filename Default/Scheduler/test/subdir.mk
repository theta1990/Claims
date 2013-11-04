################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Scheduler/test/QueryDagTest.cpp \
../Scheduler/test/SchedulerTest.cpp 

OBJS += \
./Scheduler/test/QueryDagTest.o \
./Scheduler/test/SchedulerTest.o 

CPP_DEPS += \
./Scheduler/test/QueryDagTest.d \
./Scheduler/test/SchedulerTest.d 


# Each subdirectory must supply rules for building sources it contributes
Scheduler/test/%.o: ../Scheduler/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


