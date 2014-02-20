################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Client/ClaimsServer.cpp \
../Client/Client.cpp \
../Client/ClientResponse.cpp 

OBJS += \
./Client/ClaimsServer.o \
./Client/Client.o \
./Client/ClientResponse.o 

CPP_DEPS += \
./Client/ClaimsServer.d \
./Client/Client.d \
./Client/ClientResponse.d 


# Each subdirectory must supply rules for building sources it contributes
Client/%.o: ../Client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


