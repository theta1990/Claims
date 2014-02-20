################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LogicalQueryPlan/Test/Aggregation_test.cpp \
../LogicalQueryPlan/Test/ResultCollect_test.cpp \
../LogicalQueryPlan/Test/getOptimalQueryPlan.cpp \
../LogicalQueryPlan/Test/query_optmization_based_on_statisitic_test.cpp \
../LogicalQueryPlan/Test/testGenerateIteratorTree.cpp \
../LogicalQueryPlan/Test/testGetDataflow.cpp 

OBJS += \
./LogicalQueryPlan/Test/Aggregation_test.o \
./LogicalQueryPlan/Test/ResultCollect_test.o \
./LogicalQueryPlan/Test/getOptimalQueryPlan.o \
./LogicalQueryPlan/Test/query_optmization_based_on_statisitic_test.o \
./LogicalQueryPlan/Test/testGenerateIteratorTree.o \
./LogicalQueryPlan/Test/testGetDataflow.o 

CPP_DEPS += \
./LogicalQueryPlan/Test/Aggregation_test.d \
./LogicalQueryPlan/Test/ResultCollect_test.d \
./LogicalQueryPlan/Test/getOptimalQueryPlan.d \
./LogicalQueryPlan/Test/query_optmization_based_on_statisitic_test.d \
./LogicalQueryPlan/Test/testGenerateIteratorTree.d \
./LogicalQueryPlan/Test/testGetDataflow.d 


# Each subdirectory must supply rules for building sources it contributes
LogicalQueryPlan/Test/%.o: ../LogicalQueryPlan/Test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


