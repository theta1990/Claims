################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../try/Epoll.cpp \
../try/IteratorTreeSerialization.cpp \
../try/Socket.cpp \
../try/SocketSender.cpp \
../try/data_generator.cpp \
../try/select.cpp 

OBJS += \
./try/Epoll.o \
./try/IteratorTreeSerialization.o \
./try/Socket.o \
./try/SocketSender.o \
./try/data_generator.o \
./try/select.o 

CPP_DEPS += \
./try/Epoll.d \
./try/IteratorTreeSerialization.d \
./try/Socket.d \
./try/SocketSender.d \
./try/data_generator.d \
./try/select.d 


# Each subdirectory must supply rules for building sources it contributes
try/%.o: ../try/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/imdb/tools/Theron-5.01.01/Include -I/home/NewHadoop/hadoop/hadoop-1.0.3/src/c++/libhdfs -I/home/imdb/supports/boost_1_53_0 -O0 -g -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


