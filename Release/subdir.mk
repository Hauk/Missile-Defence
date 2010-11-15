################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MDMain.cpp \
../gameWorld.cpp \
../gui.cpp \
../missile.cpp \
../sensor.cpp \
../statistics.cpp \
../target.cpp 

OBJS += \
./MDMain.o \
./gameWorld.o \
./gui.o \
./missile.o \
./sensor.o \
./statistics.o \
./target.o 

CPP_DEPS += \
./MDMain.d \
./gameWorld.d \
./gui.d \
./missile.d \
./sensor.d \
./statistics.d \
./target.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


