################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../To\ Students/Student_Code/AVL.cpp \
../To\ Students/Student_Code/Node.cpp \
../To\ Students/Student_Code/main.cpp 

OBJS += \
./To\ Students/Student_Code/AVL.o \
./To\ Students/Student_Code/Node.o \
./To\ Students/Student_Code/main.o 

CPP_DEPS += \
./To\ Students/Student_Code/AVL.d \
./To\ Students/Student_Code/Node.d \
./To\ Students/Student_Code/main.d 


# Each subdirectory must supply rules for building sources it contributes
To\ Students/Student_Code/AVL.o: ../To\ Students/Student_Code/AVL.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"To Students/Student_Code/AVL.d" -MT"To\ Students/Student_Code/AVL.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

To\ Students/Student_Code/Node.o: ../To\ Students/Student_Code/Node.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"To Students/Student_Code/Node.d" -MT"To\ Students/Student_Code/Node.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

To\ Students/Student_Code/main.o: ../To\ Students/Student_Code/main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"To Students/Student_Code/main.d" -MT"To\ Students/Student_Code/main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


