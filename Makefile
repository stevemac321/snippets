
TARGETNAME := MakeStdPeriph.elf
#TARGETTYPE can be APP, STATIC or SHARED
TARGETTYPE := APP

to_lowercase = $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$1))))))))))))))))))))))))))

CONFIG ?= DEBUG

CONFIGURATION_FLAGS_FILE := $(call to_lowercase,$(CONFIG)).mak

include $(CONFIGURATION_FLAGS_FILE)

#LINKER_SCRIPT defined inside the configuration file (e.g. debug.mak) should override any linker scripts defined in shared .mak files
CONFIGURATION_LINKER_SCRIPT := $(LINKER_SCRIPT)

include $(ADDITIONAL_MAKE_FILES)

ifneq ($(CONFIGURATION_LINKER_SCRIPT),)
LINKER_SCRIPT := $(CONFIGURATION_LINKER_SCRIPT)
endif

ifneq ($(LINKER_SCRIPT),)
LDFLAGS += -T$(LINKER_SCRIPT)
endif

ifeq ($(BINARYDIR),)
error:
	$(error Invalid configuration, please check your inputs)
endif

SOURCEFILES := $(BSP_ROOT)/STM32F4xxxx/StartupFiles/startup_stm32f401xe.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/misc.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cec.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dfsdm.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dsi.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash_ramfunc.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmpi2c.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_lptim.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_qspi.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spdifrx.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c LEDBlink.c system_stm32f4xx.c algo.c heap.c array.c functor.c specializations.c static_tree.c
EXTERNAL_LIBS := 
EXTERNAL_LIBS_COPIED := $(foreach lib, $(EXTERNAL_LIBS),$(BINARYDIR)/$(notdir $(lib)))

CFLAGS += $(COMMONFLAGS)
CXXFLAGS += $(COMMONFLAGS)
ASFLAGS += $(COMMONFLAGS)
LDFLAGS += $(COMMONFLAGS)

CFLAGS += $(addprefix -I,$(INCLUDE_DIRS))
CXXFLAGS += $(addprefix -I,$(INCLUDE_DIRS))

CFLAGS += $(addprefix -D,$(PREPROCESSOR_MACROS))
CXXFLAGS += $(addprefix -D,$(PREPROCESSOR_MACROS))
ASFLAGS += $(addprefix -D,$(PREPROCESSOR_MACROS))

CXXFLAGS += $(addprefix -framework ,$(MACOS_FRAMEWORKS))
CFLAGS += $(addprefix -framework ,$(MACOS_FRAMEWORKS))
LDFLAGS += $(addprefix -framework ,$(MACOS_FRAMEWORKS))

LDFLAGS += $(addprefix -L,$(LIBRARY_DIRS))

ifeq ($(GENERATE_MAP_FILE),1)
LDFLAGS += -Wl,-Map=$(BINARYDIR)/$(basename $(TARGETNAME)).map
endif

LIBRARY_LDFLAGS = $(addprefix -l,$(LIBRARY_NAMES))

ifeq ($(IS_LINUX_PROJECT),1)
	RPATH_PREFIX := -Wl,--rpath='$$ORIGIN/../
	LIBRARY_LDFLAGS += $(EXTERNAL_LIBS)
	LIBRARY_LDFLAGS += -Wl,--rpath='$$ORIGIN'
	LIBRARY_LDFLAGS += $(addsuffix ',$(addprefix $(RPATH_PREFIX),$(dir $(EXTERNAL_LIBS))))
	
	ifeq ($(TARGETTYPE),SHARED)
		CFLAGS += -fPIC
		CXXFLAGS += -fPIC
		ASFLAGS += -fPIC
		LIBRARY_LDFLAGS += -Wl,-soname,$(TARGETNAME)
	endif
	
	ifneq ($(LINUX_PACKAGES),)
		PACKAGE_CFLAGS := $(foreach pkg,$(LINUX_PACKAGES),$(shell pkg-config --cflags $(pkg)))
		PACKAGE_LDFLAGS := $(foreach pkg,$(LINUX_PACKAGES),$(shell pkg-config --libs $(pkg)))
		CFLAGS += $(PACKAGE_CFLAGS)
		CXXFLAGS += $(PACKAGE_CFLAGS)
		LIBRARY_LDFLAGS += $(PACKAGE_LDFLAGS)
	endif	
else
	LIBRARY_LDFLAGS += $(EXTERNAL_LIBS)
endif

LIBRARY_LDFLAGS += $(ADDITIONAL_LINKER_INPUTS)

all_make_files := $(firstword $(MAKEFILE_LIST)) $(CONFIGURATION_FLAGS_FILE) $(ADDITIONAL_MAKE_FILES)

ifeq ($(STARTUPFILES),)
	all_source_files := $(SOURCEFILES)
else
	all_source_files := $(STARTUPFILES) $(filter-out $(STARTUPFILES),$(SOURCEFILES))
endif

source_obj1 := $(all_source_files:.cpp=.o)
source_obj2 := $(source_obj1:.c=.o)
source_obj3 := $(source_obj2:.s=.o)
source_obj4 := $(source_obj3:.S=.o)
source_obj5 := $(source_obj4:.cc=.o)
source_objs := $(source_obj5:.cxx=.o)

all_objs := $(addprefix $(BINARYDIR)/, $(notdir $(source_objs)))

PRIMARY_OUTPUTS :=

ifeq ($(GENERATE_BIN_FILE),1)
PRIMARY_OUTPUTS += $(BINARYDIR)/$(basename $(TARGETNAME)).bin
endif

ifeq ($(GENERATE_IHEX_FILE),1)
PRIMARY_OUTPUTS += $(BINARYDIR)/$(basename $(TARGETNAME)).ihex
endif

ifeq ($(PRIMARY_OUTPUTS),)
PRIMARY_OUTPUTS := $(BINARYDIR)/$(TARGETNAME)
endif

all: $(PRIMARY_OUTPUTS)

$(BINARYDIR)/$(basename $(TARGETNAME)).bin: $(BINARYDIR)/$(TARGETNAME)
	$(OBJCOPY) -O binary $< $@

$(BINARYDIR)/$(basename $(TARGETNAME)).ihex: $(BINARYDIR)/$(TARGETNAME)
	$(OBJCOPY) -O ihex $< $@
	
ifneq ($(LINKER_SCRIPT),)
$(BINARYDIR)/$(TARGETNAME): $(LINKER_SCRIPT)
endif

ifeq ($(TARGETTYPE),APP)
$(BINARYDIR)/$(TARGETNAME): $(all_objs) $(EXTERNAL_LIBS)
	$(LD) -o $@ $(LDFLAGS) $(START_GROUP) $(all_objs) $(LIBRARY_LDFLAGS) $(END_GROUP)
endif

ifeq ($(TARGETTYPE),SHARED)
$(BINARYDIR)/$(TARGETNAME): $(all_objs) $(EXTERNAL_LIBS)
	$(LD) -shared -o $@ $(LDFLAGS) $(START_GROUP) $(all_objs) $(LIBRARY_LDFLAGS) $(END_GROUP)
endif
	
ifeq ($(TARGETTYPE),STATIC)
$(BINARYDIR)/$(TARGETNAME): $(all_objs)
	$(AR) -r $@ $^
endif

-include $(all_objs:.o=.dep)

clean:
ifeq ($(USE_DEL_TO_CLEAN),1)
	cmd /C del /S /Q $(BINARYDIR)
else
	rm -rf $(BINARYDIR)
endif

$(BINARYDIR):
	mkdir $(BINARYDIR)

#VisualGDB: FileSpecificTemplates		#<--- VisualGDB will use the following lines to define rules for source files in subdirectories
$(BINARYDIR)/%.o : %.cpp $(all_make_files) |$(BINARYDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)

$(BINARYDIR)/%.o : %.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)

$(BINARYDIR)/%.o : %.S $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) $(ASFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)

$(BINARYDIR)/%.o : %.s $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) $(ASFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)

$(BINARYDIR)/%.o : %.cc $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)

$(BINARYDIR)/%.o : %.cxx $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)

#VisualGDB: GeneratedRules				#<--- All lines below are auto-generated. Remove this line to suppress auto-generation of file rules.


$(BINARYDIR)/startup_stm32f401xe.o : $(BSP_ROOT)/STM32F4xxxx/StartupFiles/startup_stm32f401xe.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/misc.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/misc.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_adc.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_can.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_cec.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cec.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_crc.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_cryp.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_cryp_aes.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_cryp_des.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_cryp_tdes.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_dac.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_dbgmcu.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_dcmi.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_dfsdm.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dfsdm.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_dma.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_dma2d.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_dsi.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dsi.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_exti.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_flash.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_flash_ramfunc.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash_ramfunc.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_fmpi2c.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmpi2c.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_gpio.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_hash.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_hash_md5.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_hash_sha1.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_i2c.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_iwdg.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_lptim.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_lptim.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_ltdc.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_pwr.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_qspi.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_qspi.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_rcc.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_rng.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_rtc.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_sai.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_sdio.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_spdifrx.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spdifrx.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_spi.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_syscfg.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_tim.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_usart.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)


$(BINARYDIR)/stm32f4xx_wwdg.o : $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c $(all_make_files) |$(BINARYDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)

