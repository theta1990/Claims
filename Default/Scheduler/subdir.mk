################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Scheduler/Dataflow.cpp \
../Scheduler/ExecuteTask.cpp \
../Scheduler/OperateNode.cpp \
../Scheduler/Scheduler.cpp \
../Scheduler/master.cpp \
../Scheduler/resources.cpp 

OBJS += \
./Scheduler/Dataflow.o \
./Scheduler/ExecuteTask.o \
./Scheduler/OperateNode.o \
./Scheduler/Scheduler.o \
./Scheduler/master.o \
./Scheduler/resources.o 

CPP_DEPS += \
./Scheduler/Dataflow.d \
./Scheduler/ExecuteTask.d \
./Scheduler/OperateNode.d \
./Scheduler/Scheduler.d \
./Scheduler/master.d \
./Scheduler/resources.d 


# Each subdirectory must supply rules for building sources it contributes
Scheduler/%.o: ../Scheduler/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


