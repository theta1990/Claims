################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BlockStreamIterator/ParallelBlockStreamIterator/Test/Buffer.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/Test/TopN_test.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/Test/iterator_test.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/Test/projectionScan.cpp 

OBJS += \
./BlockStreamIterator/ParallelBlockStreamIterator/Test/Buffer.o \
./BlockStreamIterator/ParallelBlockStreamIterator/Test/TopN_test.o \
./BlockStreamIterator/ParallelBlockStreamIterator/Test/iterator_test.o \
./BlockStreamIterator/ParallelBlockStreamIterator/Test/projectionScan.o 

CPP_DEPS += \
./BlockStreamIterator/ParallelBlockStreamIterator/Test/Buffer.d \
./BlockStreamIterator/ParallelBlockStreamIterator/Test/TopN_test.d \
./BlockStreamIterator/ParallelBlockStreamIterator/Test/iterator_test.d \
./BlockStreamIterator/ParallelBlockStreamIterator/Test/projectionScan.d 


# Each subdirectory must supply rules for building sources it contributes
BlockStreamIterator/ParallelBlockStreamIterator/Test/%.o: ../BlockStreamIterator/ParallelBlockStreamIterator/Test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


