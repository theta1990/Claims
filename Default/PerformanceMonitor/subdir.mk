################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PerformanceMonitor/BlockStreamPerformanceMonitorTop.cpp \
../PerformanceMonitor/BlockStreamPerformanceTest.cpp \
../PerformanceMonitor/PerformanceIteratorTop.cpp 

OBJS += \
./PerformanceMonitor/BlockStreamPerformanceMonitorTop.o \
./PerformanceMonitor/BlockStreamPerformanceTest.o \
./PerformanceMonitor/PerformanceIteratorTop.o 

CPP_DEPS += \
./PerformanceMonitor/BlockStreamPerformanceMonitorTop.d \
./PerformanceMonitor/BlockStreamPerformanceTest.d \
./PerformanceMonitor/PerformanceIteratorTop.d 


# Each subdirectory must supply rules for building sources it contributes
PerformanceMonitor/%.o: ../PerformanceMonitor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


