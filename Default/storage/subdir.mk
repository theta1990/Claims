################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../storage/AllBlockInfo.cpp \
../storage/BlanceMatcher.cpp \
../storage/BlockManager.cpp \
../storage/BlockManagerId.cpp \
../storage/BlockManagerMaster.cpp \
../storage/BlockMessage.cpp \
../storage/BlockStore.cpp \
../storage/ChunkStorage.cpp \
../storage/DiskStore.cpp \
../storage/MemoryStore.cpp \
../storage/PartitionReaderIterator.cpp \
../storage/PartitionStorage.cpp 

OBJS += \
./storage/AllBlockInfo.o \
./storage/BlanceMatcher.o \
./storage/BlockManager.o \
./storage/BlockManagerId.o \
./storage/BlockManagerMaster.o \
./storage/BlockMessage.o \
./storage/BlockStore.o \
./storage/ChunkStorage.o \
./storage/DiskStore.o \
./storage/MemoryStore.o \
./storage/PartitionReaderIterator.o \
./storage/PartitionStorage.o 

CPP_DEPS += \
./storage/AllBlockInfo.d \
./storage/BlanceMatcher.d \
./storage/BlockManager.d \
./storage/BlockManagerId.d \
./storage/BlockManagerMaster.d \
./storage/BlockMessage.d \
./storage/BlockStore.d \
./storage/ChunkStorage.d \
./storage/DiskStore.d \
./storage/MemoryStore.d \
./storage/PartitionReaderIterator.d \
./storage/PartitionStorage.d 


# Each subdirectory must supply rules for building sources it contributes
storage/%.o: ../storage/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


