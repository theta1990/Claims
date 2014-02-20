################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Catalog/stat/Analyzer.cpp \
../Catalog/stat/AttributeStatistics.cpp \
../Catalog/stat/Estimation.cpp \
../Catalog/stat/StatManager.cpp \
../Catalog/stat/Statistic.cpp \
../Catalog/stat/TableStatistic.cpp 

OBJS += \
./Catalog/stat/Analyzer.o \
./Catalog/stat/AttributeStatistics.o \
./Catalog/stat/Estimation.o \
./Catalog/stat/StatManager.o \
./Catalog/stat/Statistic.o \
./Catalog/stat/TableStatistic.o 

CPP_DEPS += \
./Catalog/stat/Analyzer.d \
./Catalog/stat/AttributeStatistics.d \
./Catalog/stat/Estimation.d \
./Catalog/stat/StatManager.d \
./Catalog/stat/Statistic.d \
./Catalog/stat/TableStatistic.d 


# Each subdirectory must supply rules for building sources it contributes
Catalog/stat/%.o: ../Catalog/stat/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


