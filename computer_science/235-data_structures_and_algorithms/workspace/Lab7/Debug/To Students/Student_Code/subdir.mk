################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../To\ Students/Student_Code/Factory.cpp 

OBJS += \
./To\ Students/Student_Code/Factory.o 

CPP_DEPS += \
./To\ Students/Student_Code/Factory.d 


# Each subdirectory must supply rules for building sources it contributes
To\ Students/Student_Code/Factory.o: ../To\ Students/Student_Code/Factory.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"To Students/Student_Code/Factory.d" -MT"To\ Students/Student_Code/Factory.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


