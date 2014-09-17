################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AppResourceId.cpp \
../src/CreateProfileForm.cpp \
../src/EditProfileForm.cpp \
../src/LocationMapForm.cpp \
../src/ProfileDetailForm.cpp \
../src/ProfileEntry.cpp \
../src/ProfileFormFactory.cpp \
../src/ProfileFrame.cpp \
../src/ProfileListForm.cpp \
../src/SceneRegister.cpp \
../src/UsingmodeProfile.cpp 

OBJS += \
./src/AppResourceId.o \
./src/CreateProfileForm.o \
./src/EditProfileForm.o \
./src/LocationMapForm.o \
./src/ProfileDetailForm.o \
./src/ProfileEntry.o \
./src/ProfileFormFactory.o \
./src/ProfileFrame.o \
./src/ProfileListForm.o \
./src/SceneRegister.o \
./src/UsingmodeProfile.o 

CPP_DEPS += \
./src/AppResourceId.d \
./src/CreateProfileForm.d \
./src/EditProfileForm.d \
./src/LocationMapForm.d \
./src/ProfileDetailForm.d \
./src/ProfileEntry.d \
./src/ProfileFormFactory.d \
./src/ProfileFrame.d \
./src/ProfileListForm.d \
./src/SceneRegister.d \
./src/UsingmodeProfile.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: C++ Compiler'
	clang++.exe -I"pch" -D_DEBUG -I"C:\Users\Ahn\Downloads\UsingmodeProfileApp\inc" -O0 -g3 -Wall -c -fmessage-length=0 -target i386-tizen-linux-gnueabi -gcc-toolchain "E:/tizen-sdk/tools/smart-build-interface/../i386-linux-gnueabi-gcc-4.5/" -ccc-gcc-name i386-linux-gnueabi-g++ -march=i386 -Wno-gnu -fPIE --sysroot="E:/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-emulator-2.2.native" -I"E:/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-emulator-2.2.native/usr/include/libxml2" -I"E:\tizen-sdk\library" -I"E:/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-emulator-2.2.native/usr/include" -I"E:/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-emulator-2.2.native/usr/include/osp" -D_APP_LOG -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


