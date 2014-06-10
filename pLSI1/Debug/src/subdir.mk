################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Docs.cpp \
../src/Factors.cpp \
../src/main.cpp \
../src/main1.cpp \
../src/pLSI.cpp 

OBJS += \
./src/Docs.o \
./src/Factors.o \
./src/main.o \
./src/main1.o \
./src/pLSI.o 

CPP_DEPS += \
./src/Docs.d \
./src/Factors.d \
./src/main.d \
./src/main1.d \
./src/pLSI.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


