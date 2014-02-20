################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Parsetree/parsetree2logicalplan.cpp \
../Parsetree/runparsetree.cpp \
../Parsetree/sql.tab.cpp \
../Parsetree/wc2tb.cpp 

C_SRCS += \
../Parsetree/lex.yy.c 

OBJS += \
./Parsetree/lex.yy.o \
./Parsetree/parsetree2logicalplan.o \
./Parsetree/runparsetree.o \
./Parsetree/sql.tab.o \
./Parsetree/wc2tb.o 

C_DEPS += \
./Parsetree/lex.yy.d 

CPP_DEPS += \
./Parsetree/parsetree2logicalplan.d \
./Parsetree/runparsetree.d \
./Parsetree/sql.tab.d \
./Parsetree/wc2tb.d 


# Each subdirectory must supply rules for building sources it contributes
Parsetree/%.o: ../Parsetree/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	g++ -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Parsetree/%.o: ../Parsetree/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


