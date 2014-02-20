################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../iterator/AggregationIterator.cpp \
../iterator/CombinedIterator.cpp \
../iterator/ExchangeBase.cpp \
../iterator/ExchangeIterator.cpp \
../iterator/ExchangeIteratorEager.cpp \
../iterator/ExchangeIteratorEagerLower.cpp \
../iterator/ExchangeIteratorLower.cpp \
../iterator/ExchangeIteratorLowerWithWideDependency.cpp \
../iterator/ExchangeIteratorWithWideDependency.cpp \
../iterator/FilterIterator.cpp \
../iterator/JoinIterator.cpp \
../iterator/PrintIterator.cpp \
../iterator/RandomDiskAccessIterator.cpp \
../iterator/RandomMemAccessIterator.cpp \
../iterator/RowScanIterator.cpp \
../iterator/SequencialDiskAccessIterator.cpp \
../iterator/SingleColumnScanIterator.cpp \
../iterator/SingleColumnScanIteratorFix.cpp 

OBJS += \
./iterator/AggregationIterator.o \
./iterator/CombinedIterator.o \
./iterator/ExchangeBase.o \
./iterator/ExchangeIterator.o \
./iterator/ExchangeIteratorEager.o \
./iterator/ExchangeIteratorEagerLower.o \
./iterator/ExchangeIteratorLower.o \
./iterator/ExchangeIteratorLowerWithWideDependency.o \
./iterator/ExchangeIteratorWithWideDependency.o \
./iterator/FilterIterator.o \
./iterator/JoinIterator.o \
./iterator/PrintIterator.o \
./iterator/RandomDiskAccessIterator.o \
./iterator/RandomMemAccessIterator.o \
./iterator/RowScanIterator.o \
./iterator/SequencialDiskAccessIterator.o \
./iterator/SingleColumnScanIterator.o \
./iterator/SingleColumnScanIteratorFix.o 

CPP_DEPS += \
./iterator/AggregationIterator.d \
./iterator/CombinedIterator.d \
./iterator/ExchangeBase.d \
./iterator/ExchangeIterator.d \
./iterator/ExchangeIteratorEager.d \
./iterator/ExchangeIteratorEagerLower.d \
./iterator/ExchangeIteratorLower.d \
./iterator/ExchangeIteratorLowerWithWideDependency.d \
./iterator/ExchangeIteratorWithWideDependency.d \
./iterator/FilterIterator.d \
./iterator/JoinIterator.d \
./iterator/PrintIterator.d \
./iterator/RandomDiskAccessIterator.d \
./iterator/RandomMemAccessIterator.d \
./iterator/RowScanIterator.d \
./iterator/SequencialDiskAccessIterator.d \
./iterator/SingleColumnScanIterator.d \
./iterator/SingleColumnScanIteratorFix.d 


# Each subdirectory must supply rules for building sources it contributes
iterator/%.o: ../iterator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


