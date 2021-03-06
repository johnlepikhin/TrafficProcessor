################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/levels/ChunkEtherNet.cpp \
../src/levels/ChunkEtherNet802LLC.cpp \
../src/levels/ChunkEtherNetDIX.cpp \
../src/levels/ChunkEtherNetRAW.cpp \
../src/levels/ChunkEtherNetSNAP.cpp \
../src/levels/ChunkHTTP.cpp \
../src/levels/ChunkIPv4.cpp \
../src/levels/ChunkIPv6.cpp \
../src/levels/ChunkSSL.cpp \
../src/levels/ChunkTCP.cpp \
../src/levels/ChunkUDP.cpp \
../src/levels/PacketIPVariant.cpp \
../src/levels/PacketIPv4.cpp \
../src/levels/PacketMySQL.cpp \
../src/levels/ParserChunkSSL.cpp \
../src/levels/ParserEtherNet.cpp \
../src/levels/ParserEtherNet802LLC.cpp \
../src/levels/ParserEtherNetDIX.cpp \
../src/levels/ParserEtherNetRAW.cpp \
../src/levels/ParserEtherNetSNAP.cpp \
../src/levels/ParserHTTP.cpp \
../src/levels/ParserIPv4.cpp \
../src/levels/ParserIPv6.cpp \
../src/levels/ParserPacketIPv4.cpp \
../src/levels/ParserPacketMySQL.cpp \
../src/levels/ParserSessionTCP.cpp \
../src/levels/ParserTCP.cpp \
../src/levels/ParserUDP.cpp \
../src/levels/SessionTCP.cpp 

OBJS += \
./src/levels/ChunkEtherNet.o \
./src/levels/ChunkEtherNet802LLC.o \
./src/levels/ChunkEtherNetDIX.o \
./src/levels/ChunkEtherNetRAW.o \
./src/levels/ChunkEtherNetSNAP.o \
./src/levels/ChunkHTTP.o \
./src/levels/ChunkIPv4.o \
./src/levels/ChunkIPv6.o \
./src/levels/ChunkSSL.o \
./src/levels/ChunkTCP.o \
./src/levels/ChunkUDP.o \
./src/levels/PacketIPVariant.o \
./src/levels/PacketIPv4.o \
./src/levels/PacketMySQL.o \
./src/levels/ParserChunkSSL.o \
./src/levels/ParserEtherNet.o \
./src/levels/ParserEtherNet802LLC.o \
./src/levels/ParserEtherNetDIX.o \
./src/levels/ParserEtherNetRAW.o \
./src/levels/ParserEtherNetSNAP.o \
./src/levels/ParserHTTP.o \
./src/levels/ParserIPv4.o \
./src/levels/ParserIPv6.o \
./src/levels/ParserPacketIPv4.o \
./src/levels/ParserPacketMySQL.o \
./src/levels/ParserSessionTCP.o \
./src/levels/ParserTCP.o \
./src/levels/ParserUDP.o \
./src/levels/SessionTCP.o 

CPP_DEPS += \
./src/levels/ChunkEtherNet.d \
./src/levels/ChunkEtherNet802LLC.d \
./src/levels/ChunkEtherNetDIX.d \
./src/levels/ChunkEtherNetRAW.d \
./src/levels/ChunkEtherNetSNAP.d \
./src/levels/ChunkHTTP.d \
./src/levels/ChunkIPv4.d \
./src/levels/ChunkIPv6.d \
./src/levels/ChunkSSL.d \
./src/levels/ChunkTCP.d \
./src/levels/ChunkUDP.d \
./src/levels/PacketIPVariant.d \
./src/levels/PacketIPv4.d \
./src/levels/PacketMySQL.d \
./src/levels/ParserChunkSSL.d \
./src/levels/ParserEtherNet.d \
./src/levels/ParserEtherNet802LLC.d \
./src/levels/ParserEtherNetDIX.d \
./src/levels/ParserEtherNetRAW.d \
./src/levels/ParserEtherNetSNAP.d \
./src/levels/ParserHTTP.d \
./src/levels/ParserIPv4.d \
./src/levels/ParserIPv6.d \
./src/levels/ParserPacketIPv4.d \
./src/levels/ParserPacketMySQL.d \
./src/levels/ParserSessionTCP.d \
./src/levels/ParserTCP.d \
./src/levels/ParserUDP.d \
./src/levels/SessionTCP.d 


# Each subdirectory must supply rules for building sources it contributes
src/levels/%.o: ../src/levels/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../cpp-quilt-strings/src -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


