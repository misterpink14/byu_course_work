################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Lab8\ To\ Students/Student_Code/Factory.cpp 

OBJS += \
./Lab8\ To\ Students/Student_Code/Factory.o 

CPP_DEPS += \
./Lab8\ To\ Students/Student_Code/Factory.d 


# Each subdirectory must supply rules for building sources it contributes
Lab8\ To\ Students/Student_Code/Factory.o: ../Lab8\ To\ Students/Student_Code/Factory.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Lab8 To Students/Student_Code/Factory.d" -MT"Lab8\ To\ Students/Student_Code/Factory.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


