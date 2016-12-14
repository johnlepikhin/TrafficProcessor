################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/ProcessorsCollection.cpp \
../src/core/utils.cpp 

OBJS += \
./src/core/ProcessorsCollection.o \
./src/core/utils.o 

CPP_DEPS += \
./src/core/ProcessorsCollection.d \
./src/core/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../cpp-sparse-ropes/src -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


