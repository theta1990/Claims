################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Test/MultiToMulti.cpp \
../Test/OneTOTwoToThree.cpp \
../Test/SerializeWideDependency.cpp \
../Test/ThreeLevelExchangeEager.cpp \
../Test/VerticalExchange.cpp \
../Test/block_stream_iterator_serilaization_test.cpp \
../Test/block_stream_test.cpp \
../Test/iterator_remote_execute.cpp \
../Test/main.cpp \
../Test/test_adaptiveendpoint.cpp \
../Test/test_coordinator.cpp \
../Test/test_iterator.cpp \
../Test/test_iterator_serialization.cpp \
../Test/test_scdong.cpp 

OBJS += \
./Test/MultiToMulti.o \
./Test/OneTOTwoToThree.o \
./Test/SerializeWideDependency.o \
./Test/ThreeLevelExchangeEager.o \
./Test/VerticalExchange.o \
./Test/block_stream_iterator_serilaization_test.o \
./Test/block_stream_test.o \
./Test/iterator_remote_execute.o \
./Test/main.o \
./Test/test_adaptiveendpoint.o \
./Test/test_coordinator.o \
./Test/test_iterator.o \
./Test/test_iterator_serialization.o \
./Test/test_scdong.o 

CPP_DEPS += \
./Test/MultiToMulti.d \
./Test/OneTOTwoToThree.d \
./Test/SerializeWideDependency.d \
./Test/ThreeLevelExchangeEager.d \
./Test/VerticalExchange.d \
./Test/block_stream_iterator_serilaization_test.d \
./Test/block_stream_test.d \
./Test/iterator_remote_execute.d \
./Test/main.d \
./Test/test_adaptiveendpoint.d \
./Test/test_coordinator.d \
./Test/test_iterator.d \
./Test/test_iterator_serialization.d \
./Test/test_scdong.d 


# Each subdirectory must supply rules for building sources it contributes
Test/%.o: ../Test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


