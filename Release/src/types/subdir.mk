################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/types/Chunk.cpp \
../src/types/IPv4Addr.cpp \
../src/types/IPv6Addr.cpp \
../src/types/MAC.cpp \
../src/types/PhantomQuilt.cpp 

OBJS += \
./src/types/Chunk.o \
./src/types/IPv4Addr.o \
./src/types/IPv6Addr.o \
./src/types/MAC.o \
./src/types/PhantomQuilt.o 

CPP_DEPS += \
./src/types/Chunk.d \
./src/types/IPv4Addr.d \
./src/types/IPv6Addr.d \
./src/types/MAC.d \
./src/types/PhantomQuilt.d 


# Each subdirectory must supply rules for building sources it contributes
src/types/%.o: ../src/types/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../cpp-quilt-strings/src -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


