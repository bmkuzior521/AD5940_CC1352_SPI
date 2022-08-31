################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs1030/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gcc-9.2.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DDeviceFamily_CC13X2 -I"C:/Users/bkuzi/workspace_v10/spimaster_CC1352R1_LAUNCHXL_tirtos_gcc" -I"C:/Users/bkuzi/workspace_v10/spimaster_CC1352R1_LAUNCHXL_tirtos_gcc/Debug" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_6_20_00_29/source" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_6_20_00_29/source/ti/posix/gcc" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_6_20_00_29/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include/newlib-nano" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_6_20_00_29/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include" -I"C:/ti/ccs1030/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/arm-none-eabi/include" -O3 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/bkuzi/workspace_v10/spimaster_CC1352R1_LAUNCHXL_tirtos_gcc/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-2132875919: ../spimaster.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1_13_0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc13xx_cc26xx_sdk_6_20_00_29/.metadata/product.json" --script "C:/Users/bkuzi/workspace_v10/spimaster_CC1352R1_LAUNCHXL_tirtos_gcc/spimaster.syscfg" -o "syscfg" --compiler gcc
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_devices_config.c: build-2132875919 ../spimaster.syscfg
syscfg/ti_drivers_config.c: build-2132875919
syscfg/ti_drivers_config.h: build-2132875919
syscfg/ti_utils_build_linker.cmd.genlibs: build-2132875919
syscfg/syscfg_c.rov.xs: build-2132875919
syscfg/ti_utils_runtime_model.gv: build-2132875919
syscfg/ti_utils_runtime_Makefile: build-2132875919
syscfg/: build-2132875919

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs1030/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gcc-9.2.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DDeviceFamily_CC13X2 -I"C:/Users/bkuzi/workspace_v10/spimaster_CC1352R1_LAUNCHXL_tirtos_gcc" -I"C:/Users/bkuzi/workspace_v10/spimaster_CC1352R1_LAUNCHXL_tirtos_gcc/Debug" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_6_20_00_29/source" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_6_20_00_29/source/ti/posix/gcc" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_6_20_00_29/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include/newlib-nano" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_6_20_00_29/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include" -I"C:/ti/ccs1030/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/arm-none-eabi/include" -O3 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"syscfg/$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/bkuzi/workspace_v10/spimaster_CC1352R1_LAUNCHXL_tirtos_gcc/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


