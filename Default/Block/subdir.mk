################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Block/Block.cpp \
../Block/BlockContainer.cpp \
../Block/BlockFix.cpp \
../Block/BlockReadable.cpp \
../Block/BlockReadableFix.cpp \
../Block/BlockReadableFixBuffer.cpp \
../Block/BlockStream.cpp \
../Block/BlockStreamBuffer.cpp \
../Block/BlockWritable.cpp \
../Block/BlockWritableFix.cpp \
../Block/BlockWritableFixBuffer.cpp \
../Block/PartitionedBlockBuffer.cpp \
../Block/PartitionedBlockContainer.cpp 

OBJS += \
./Block/Block.o \
./Block/BlockContainer.o \
./Block/BlockFix.o \
./Block/BlockReadable.o \
./Block/BlockReadableFix.o \
./Block/BlockReadableFixBuffer.o \
./Block/BlockStream.o \
./Block/BlockStreamBuffer.o \
./Block/BlockWritable.o \
./Block/BlockWritableFix.o \
./Block/BlockWritableFixBuffer.o \
./Block/PartitionedBlockBuffer.o \
./Block/PartitionedBlockContainer.o 

CPP_DEPS += \
./Block/Block.d \
./Block/BlockContainer.d \
./Block/BlockFix.d \
./Block/BlockReadable.d \
./Block/BlockReadableFix.d \
./Block/BlockReadableFixBuffer.d \
./Block/BlockStream.d \
./Block/BlockStreamBuffer.d \
./Block/BlockWritable.d \
./Block/BlockWritableFix.d \
./Block/BlockWritableFixBuffer.d \
./Block/PartitionedBlockBuffer.d \
./Block/PartitionedBlockContainer.d 


# Each subdirectory must supply rules for building sources it contributes
Block/%.o: ../Block/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


