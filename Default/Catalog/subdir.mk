################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Catalog/Catalog.cpp \
../Catalog/Partitioner.cpp \
../Catalog/ProjectionBinding.cpp \
../Catalog/ProjectionBinding_test.cpp \
../Catalog/table.cpp 

OBJS += \
./Catalog/Catalog.o \
./Catalog/Partitioner.o \
./Catalog/ProjectionBinding.o \
./Catalog/ProjectionBinding_test.o \
./Catalog/table.o 

CPP_DEPS += \
./Catalog/Catalog.d \
./Catalog/Partitioner.d \
./Catalog/ProjectionBinding.d \
./Catalog/ProjectionBinding_test.d \
./Catalog/table.d 


# Each subdirectory must supply rules for building sources it contributes
Catalog/%.o: ../Catalog/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


