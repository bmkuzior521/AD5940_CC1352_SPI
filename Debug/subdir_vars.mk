################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../spimaster.syscfg 

LDS_SRCS += \
../cc13x2_cc26x2_tirtos.lds 

C_SRCS += \
../AD5940_SPI.c \
../ADICUP3029Port.c \
../BIOZ-2Wire.c \
../ad5940.c \
../main_tirtos.c \
../spimaster.c \
./syscfg/ti_devices_config.c \
./syscfg/ti_drivers_config.c 

GEN_FILES += \
./syscfg/ti_devices_config.c \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./AD5940_SPI.d \
./ADICUP3029Port.d \
./BIOZ-2Wire.d \
./ad5940.d \
./main_tirtos.d \
./spimaster.d \
./syscfg/ti_devices_config.d \
./syscfg/ti_drivers_config.d 

OBJS += \
./AD5940_SPI.o \
./ADICUP3029Port.o \
./BIOZ-2Wire.o \
./ad5940.o \
./main_tirtos.o \
./spimaster.o \
./syscfg/ti_devices_config.o \
./syscfg/ti_drivers_config.o 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/ti_utils_build_linker.cmd.genlibs \
./syscfg/syscfg_c.rov.xs \
./syscfg/ti_utils_runtime_model.gv \
./syscfg/ti_utils_runtime_Makefile 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"AD5940_SPI.o" \
"ADICUP3029Port.o" \
"BIOZ-2Wire.o" \
"ad5940.o" \
"main_tirtos.o" \
"spimaster.o" \
"syscfg\ti_devices_config.o" \
"syscfg\ti_drivers_config.o" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\ti_utils_build_linker.cmd.genlibs" \
"syscfg\syscfg_c.rov.xs" \
"syscfg\ti_utils_runtime_model.gv" \
"syscfg\ti_utils_runtime_Makefile" 

C_DEPS__QUOTED += \
"AD5940_SPI.d" \
"ADICUP3029Port.d" \
"BIOZ-2Wire.d" \
"ad5940.d" \
"main_tirtos.d" \
"spimaster.d" \
"syscfg\ti_devices_config.d" \
"syscfg\ti_drivers_config.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_devices_config.c" \
"syscfg\ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../AD5940_SPI.c" \
"../ADICUP3029Port.c" \
"../BIOZ-2Wire.c" \
"../ad5940.c" \
"../main_tirtos.c" \
"../spimaster.c" \
"./syscfg/ti_devices_config.c" \
"./syscfg/ti_drivers_config.c" 

SYSCFG_SRCS__QUOTED += \
"../spimaster.syscfg" 


