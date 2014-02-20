################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Catalog/Catalog.cpp \
../Catalog/Column.cpp \
../Catalog/Partitioner.cpp \
../Catalog/ProjectionBinding.cpp \
../Catalog/table.cpp 

OBJS += \
./Catalog/Catalog.o \
./Catalog/Column.o \
./Catalog/Partitioner.o \
./Catalog/ProjectionBinding.o \
./Catalog/table.o 

CPP_DEPS += \
./Catalog/Catalog.d \
./Catalog/Column.d \
./Catalog/Partitioner.d \
./Catalog/ProjectionBinding.d \
./Catalog/table.d 


# Each subdirectory must supply rules for building sources it contributes
Catalog/%.o: ../Catalog/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


