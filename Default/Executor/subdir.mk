################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Executor/Coordinator.cpp \
../Executor/ExchangeTracker.cpp \
../Executor/IteratorExecutorMaster.cpp \
../Executor/IteratorExecutorSlave.cpp 

OBJS += \
./Executor/Coordinator.o \
./Executor/ExchangeTracker.o \
./Executor/IteratorExecutorMaster.o \
./Executor/IteratorExecutorSlave.o 

CPP_DEPS += \
./Executor/Coordinator.d \
./Executor/ExchangeTracker.d \
./Executor/IteratorExecutorMaster.d \
./Executor/IteratorExecutorSlave.d 


# Each subdirectory must supply rules for building sources it contributes
Executor/%.o: ../Executor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


