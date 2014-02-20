################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LogicalQueryPlan/Aggregation.cpp \
../LogicalQueryPlan/Buffer.cpp \
../LogicalQueryPlan/DataflowPartition.cpp \
../LogicalQueryPlan/DataflowPartitionDescriptor.cpp \
../LogicalQueryPlan/EqualJoin.cpp \
../LogicalQueryPlan/Filter.cpp \
../LogicalQueryPlan/LogicalOperator.cpp \
../LogicalQueryPlan/LogicalQueryPlanRoot.cpp \
../LogicalQueryPlan/Requirement.cpp \
../LogicalQueryPlan/Scan.cpp 

OBJS += \
./LogicalQueryPlan/Aggregation.o \
./LogicalQueryPlan/Buffer.o \
./LogicalQueryPlan/DataflowPartition.o \
./LogicalQueryPlan/DataflowPartitionDescriptor.o \
./LogicalQueryPlan/EqualJoin.o \
./LogicalQueryPlan/Filter.o \
./LogicalQueryPlan/LogicalOperator.o \
./LogicalQueryPlan/LogicalQueryPlanRoot.o \
./LogicalQueryPlan/Requirement.o \
./LogicalQueryPlan/Scan.o 

CPP_DEPS += \
./LogicalQueryPlan/Aggregation.d \
./LogicalQueryPlan/Buffer.d \
./LogicalQueryPlan/DataflowPartition.d \
./LogicalQueryPlan/DataflowPartitionDescriptor.d \
./LogicalQueryPlan/EqualJoin.d \
./LogicalQueryPlan/Filter.d \
./LogicalQueryPlan/LogicalOperator.d \
./LogicalQueryPlan/LogicalQueryPlanRoot.d \
./LogicalQueryPlan/Requirement.d \
./LogicalQueryPlan/Scan.d 


# Each subdirectory must supply rules for building sources it contributes
LogicalQueryPlan/%.o: ../LogicalQueryPlan/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


