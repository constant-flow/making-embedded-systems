##########################################################################################################################
# File automatically-generated by STM32forVSCode
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = audio-locator


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/al_display.c \
Core/Src/al_led.c \
Core/Src/al_state.c \
Core/Src/console.c \
Core/Src/consoleCommands.c \
Core/Src/consoleIo.c \
Core/Src/crc.c \
Core/Src/dma2d.c \
Core/Src/dsihost.c \
Core/Src/fmc.c \
Core/Src/gpio.c \
Core/Src/i2c.c \
Core/Src/ltdc.c \
Core/Src/main.c \
Core/Src/quadspi.c \
Core/Src/sai.c \
Core/Src/sdio.c \
Core/Src/stm32f4xx_hal_msp.c \
Core/Src/stm32f4xx_hal_timebase_tim.c \
Core/Src/stm32f4xx_it.c \
Core/Src/system_stm32f4xx.c \
Core/Src/tim.c \
Core/Src/usart.c \
Drivers/BSP/Components/otm8009a/otm8009a.c \
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.c \
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.c \
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dsi.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c \
FATFS/App/fatfs.c \
FATFS/Target/bsp_driver_sd.c \
FATFS/Target/fatfs_platform.c \
FATFS/Target/sd_diskio.c \
LIBJPEG/App/libjpeg.c \
LIBJPEG/Target/jdata_conf.c \
Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Src/usbh_cdc.c \
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c \
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c \
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c \
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c \
Middlewares/Third_Party/FatFs/src/diskio.c \
Middlewares/Third_Party/FatFs/src/ff.c \
Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
Middlewares/Third_Party/FatFs/src/option/syscall.c \
Middlewares/Third_Party/LibJPEG/source/jaricom.c \
Middlewares/Third_Party/LibJPEG/source/jcapimin.c \
Middlewares/Third_Party/LibJPEG/source/jcapistd.c \
Middlewares/Third_Party/LibJPEG/source/jcarith.c \
Middlewares/Third_Party/LibJPEG/source/jccoefct.c \
Middlewares/Third_Party/LibJPEG/source/jccolor.c \
Middlewares/Third_Party/LibJPEG/source/jcdctmgr.c \
Middlewares/Third_Party/LibJPEG/source/jchuff.c \
Middlewares/Third_Party/LibJPEG/source/jcinit.c \
Middlewares/Third_Party/LibJPEG/source/jcmainct.c \
Middlewares/Third_Party/LibJPEG/source/jcmarker.c \
Middlewares/Third_Party/LibJPEG/source/jcmaster.c \
Middlewares/Third_Party/LibJPEG/source/jcomapi.c \
Middlewares/Third_Party/LibJPEG/source/jcparam.c \
Middlewares/Third_Party/LibJPEG/source/jcprepct.c \
Middlewares/Third_Party/LibJPEG/source/jcsample.c \
Middlewares/Third_Party/LibJPEG/source/jctrans.c \
Middlewares/Third_Party/LibJPEG/source/jdapimin.c \
Middlewares/Third_Party/LibJPEG/source/jdapistd.c \
Middlewares/Third_Party/LibJPEG/source/jdarith.c \
Middlewares/Third_Party/LibJPEG/source/jdatadst.c \
Middlewares/Third_Party/LibJPEG/source/jdatasrc.c \
Middlewares/Third_Party/LibJPEG/source/jdcoefct.c \
Middlewares/Third_Party/LibJPEG/source/jdcolor.c \
Middlewares/Third_Party/LibJPEG/source/jddctmgr.c \
Middlewares/Third_Party/LibJPEG/source/jdhuff.c \
Middlewares/Third_Party/LibJPEG/source/jdinput.c \
Middlewares/Third_Party/LibJPEG/source/jdmainct.c \
Middlewares/Third_Party/LibJPEG/source/jdmarker.c \
Middlewares/Third_Party/LibJPEG/source/jdmaster.c \
Middlewares/Third_Party/LibJPEG/source/jdmerge.c \
Middlewares/Third_Party/LibJPEG/source/jdpostct.c \
Middlewares/Third_Party/LibJPEG/source/jdsample.c \
Middlewares/Third_Party/LibJPEG/source/jdtrans.c \
Middlewares/Third_Party/LibJPEG/source/jerror.c \
Middlewares/Third_Party/LibJPEG/source/jfdctflt.c \
Middlewares/Third_Party/LibJPEG/source/jfdctfst.c \
Middlewares/Third_Party/LibJPEG/source/jfdctint.c \
Middlewares/Third_Party/LibJPEG/source/jidctflt.c \
Middlewares/Third_Party/LibJPEG/source/jidctfst.c \
Middlewares/Third_Party/LibJPEG/source/jidctint.c \
Middlewares/Third_Party/LibJPEG/source/jmemmgr.c \
Middlewares/Third_Party/LibJPEG/source/jmemnobs.c \
Middlewares/Third_Party/LibJPEG/source/jquant1.c \
Middlewares/Third_Party/LibJPEG/source/jquant2.c \
Middlewares/Third_Party/LibJPEG/source/jutils.c \
PDM2PCM/App/pdm2pcm.c \
USB_HOST/App/usb_host.c \
USB_HOST/Target/usbh_conf.c \
USB_HOST/Target/usbh_platform.c


CPP_SOURCES = \


# ASM sources
ASM_SOURCES =  \
startup_stm32f469xx.s



#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
POSTFIX = "
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
GCC_PATH="/usr/local/bin
ifdef GCC_PATH
CXX = $(GCC_PATH)/$(PREFIX)g++$(POSTFIX)
CC = $(GCC_PATH)/$(PREFIX)gcc$(POSTFIX)
AS = $(GCC_PATH)/$(PREFIX)gcc$(POSTFIX) -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy$(POSTFIX)
SZ = $(GCC_PATH)/$(PREFIX)size$(POSTFIX)
else
CXX = $(PREFIX)g++
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DSTM32F469xx \
-DUSE_HAL_DRIVER \
-DUSE_STM32469I_DISCO_REVB


# CXX defines
CXX_DEFS =  \
-DSTM32F469xx \
-DUSE_HAL_DRIVER \
-DUSE_STM32469I_DISCO_REVB


# AS includes
AS_INCLUDES = \

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/BSP/Components/otm8009a \
-IDrivers/BSP/STM32469I-Discovery \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IFATFS/App \
-IFATFS/Target \
-ILIBJPEG/App \
-ILIBJPEG/Target \
-IMiddlewares/ST/STM32_Audio/Addons/PDM/Inc \
-IMiddlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc \
-IMiddlewares/ST/STM32_USB_Host_Library/Core/Inc \
-IMiddlewares/Third_Party/FatFs/src \
-IMiddlewares/Third_Party/LibJPEG/include \
-IPDM2PCM/App \
-IUSB_HOST/App \
-IUSB_HOST/Target \
-IUtilities/Fonts



# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CXXFLAGS = $(MCU) $(CXX_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -feliminate-unused-debug-types

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Add additional flags
CFLAGS += 
ASFLAGS += 
CXXFLAGS += 

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F469NIHx_FLASH.ld

# libraries
LIBS = -l:libPDMFilter_CM4_GCC_wc32.a 
LIBDIR = \
-LMiddlewares/ST/STM32_Audio/Addons/PDM/Lib


# Additional LD Flags from config file
ADDITIONALLDFLAGS = -specs=nano.specs -specs=rdimon.specs 

LDFLAGS = $(MCU) $(ADDITIONALLDFLAGS) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of cpp program objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

# list of C objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.cpp STM32Make.make | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cxx STM32Make.make | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cxx=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.c STM32Make.make | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s STM32Make.make | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) STM32Make.make
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

#######################################
# flash
#######################################
flash: $(BUILD_DIR)/$(TARGET).elf
	"/Users/de119876/.espressif/tools/openocd-esp32/v0.11.0-esp32-20211220/openocd-esp32/bin/openocd" -f ./openocd.cfg -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

#######################################
# erase
#######################################
erase: $(BUILD_DIR)/$(TARGET).elf
	"/Users/de119876/.espressif/tools/openocd-esp32/v0.11.0-esp32-20211220/openocd-esp32/bin/openocd" -f ./openocd.cfg -c "init; reset halt; stm32f4x mass_erase 0; exit"

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
	
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***