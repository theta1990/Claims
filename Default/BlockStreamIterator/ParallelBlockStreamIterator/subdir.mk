################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamAggregationIterator.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamCombinedIterator.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamExchangeBroadcast.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamExchangeLowerBroadcast.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamExpander.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamJoinIterator.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamBroadcastExchange.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamBroadcastExchangeLower.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchange.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeEpoll.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeLower.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeLowerEfficient.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeLowerMaterialized.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeMaterialized.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamFilter.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamRandomDiskAccess.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamRandomMemAccess.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamSingleColumnScan.cpp \
../BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamSingleColumnScanDisk.cpp 

OBJS += \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamAggregationIterator.o \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamCombinedIterator.o \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamExchangeBroadcast.o \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamExchangeLowerBroadcast.o \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamExpander.o \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamJoinIterator.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamBroadcastExchange.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamBroadcastExchangeLower.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchange.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeEpoll.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeLower.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeLowerEfficient.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeLowerMaterialized.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeMaterialized.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamFilter.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamRandomDiskAccess.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamRandomMemAccess.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamSingleColumnScan.o \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamSingleColumnScanDisk.o 

CPP_DEPS += \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamAggregationIterator.d \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamCombinedIterator.d \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamExchangeBroadcast.d \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamExchangeLowerBroadcast.d \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamExpander.d \
./BlockStreamIterator/ParallelBlockStreamIterator/BlockStreamJoinIterator.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamBroadcastExchange.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamBroadcastExchangeLower.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchange.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeEpoll.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeLower.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeLowerEfficient.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeLowerMaterialized.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamExchangeMaterialized.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamFilter.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamRandomDiskAccess.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamRandomMemAccess.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamSingleColumnScan.d \
./BlockStreamIterator/ParallelBlockStreamIterator/ExpandableBlockStreamSingleColumnScanDisk.d 


# Each subdirectory must supply rules for building sources it contributes
BlockStreamIterator/ParallelBlockStreamIterator/%.o: ../BlockStreamIterator/ParallelBlockStreamIterator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


