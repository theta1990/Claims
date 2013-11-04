################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BlockStreamIterator/BlockStreamExchangeBase.cpp \
../BlockStreamIterator/BlockStreamExchangeLowerBase.cpp \
../BlockStreamIterator/BlockStreamFilter.cpp \
../BlockStreamIterator/BlockStreamIteratorBase.cpp \
../BlockStreamIterator/BlockStreamRandomMemAccess.cpp \
../BlockStreamIterator/BlockStreamSingleColumnScan.cpp 

OBJS += \
./BlockStreamIterator/BlockStreamExchangeBase.o \
./BlockStreamIterator/BlockStreamExchangeLowerBase.o \
./BlockStreamIterator/BlockStreamFilter.o \
./BlockStreamIterator/BlockStreamIteratorBase.o \
./BlockStreamIterator/BlockStreamRandomMemAccess.o \
./BlockStreamIterator/BlockStreamSingleColumnScan.o 

CPP_DEPS += \
./BlockStreamIterator/BlockStreamExchangeBase.d \
./BlockStreamIterator/BlockStreamExchangeLowerBase.d \
./BlockStreamIterator/BlockStreamFilter.d \
./BlockStreamIterator/BlockStreamIteratorBase.d \
./BlockStreamIterator/BlockStreamRandomMemAccess.d \
./BlockStreamIterator/BlockStreamSingleColumnScan.d 


# Each subdirectory must supply rules for building sources it contributes
BlockStreamIterator/%.o: ../BlockStreamIterator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


