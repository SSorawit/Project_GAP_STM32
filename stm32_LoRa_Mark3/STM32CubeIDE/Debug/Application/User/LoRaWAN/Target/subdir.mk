################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Project\ GAP/stm-32-project/stm32_LoRa_Mark3/LoRaWAN/Target/radio_board_if.c 

OBJS += \
./Application/User/LoRaWAN/Target/radio_board_if.o 

C_DEPS += \
./Application/User/LoRaWAN/Target/radio_board_if.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/LoRaWAN/Target/radio_board_if.o: D:/Project\ GAP/stm-32-project/stm32_LoRa_Mark3/LoRaWAN/Target/radio_board_if.c Application/User/LoRaWAN/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../../Core/Inc -I../../LoRaWAN/App -I../../LoRaWAN/Target -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Utilities/trace/adv_trace" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Utilities/misc" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Utilities/sequencer" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Utilities/timer" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Utilities/lpm/tiny_lpm" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Middlewares/Third_Party/LoRaWAN/LmHandler/Packages" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Middlewares/Third_Party/LoRaWAN/Crypto" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Middlewares/Third_Party/LoRaWAN/Mac/Region" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Middlewares/Third_Party/LoRaWAN/Mac" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Middlewares/Third_Party/LoRaWAN/LmHandler" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Middlewares/Third_Party/LoRaWAN/Utilities" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Middlewares/Third_Party/SubGHz_Phy" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver" -I"C:/Users/sorawit srisun/STM32Cube/Repository/STM32Cube_FW_WL_V1.3.1/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/LoRaWAN/Target/radio_board_if.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User-2f-LoRaWAN-2f-Target

clean-Application-2f-User-2f-LoRaWAN-2f-Target:
	-$(RM) ./Application/User/LoRaWAN/Target/radio_board_if.cyclo ./Application/User/LoRaWAN/Target/radio_board_if.d ./Application/User/LoRaWAN/Target/radio_board_if.o ./Application/User/LoRaWAN/Target/radio_board_if.su

.PHONY: clean-Application-2f-User-2f-LoRaWAN-2f-Target

