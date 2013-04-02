#Program build mode : debug/release
BUILD_MODE := debug
#BUILD_MODE := release

TARGET := GtkmmSample

#LOCAL_ASFLAGS
#LOCAL_CPPFLAGS
LOCAL_CFLAGS = `pkg-config gtkmm-2.4 --cflags`
LOCAL_LDFLAGS = `pkg-config gtkmm-2.4 --libs`

#add java support
#LOCAL_CFLAGS += -I/usr/lib/jvm/java-6-sun-1.6.0.26/include -I/usr/lib/jvm/java-6-sun-1.6.0.26/include/ linux 
#LOCAL_LDFLAGS += -L/usr/lib/jvm/java-6-sun/jre/lib/amd64/server -ljvm
#LOCAL_CFLAGS += -I/opt/jdk1.6.0_31/include -I/opt/jdk1.6.0_31/include/linux
#LOCAL_LDFLAGS += -L/opt/jdk1.6.0_31/jre/lib/i386/client -ljvm

#LOCAL_INCLUDES = 
#EXTRA_LIBS_DIR = 
RES_DIR = res

###############################################################################
##               Variable
###############################################################################
MKDIR := mkdir -p
RM := rm -fr
CP := cp -f

LOCAL_CC ?= gcc
LOCAL_CXX ?= g++
LOCAL_PATH := .

SRC_ROOT ?= src
CPP_EXT ?= cpp

#LOCAL_CPPFLAGS += -DPACKAGE=\""$(TARGET)"\" -DLOCALDIR=\""./local"\"

ifeq ($(BUILD_MODE),debug)
  LOCAL_CFLAGS += -g 
  LOCAL_CPPFLAGS += -Wall -DDEBUG
else
  ifeq ($(BUILD_MODE),release)
    LOCAL_CFLAGS += -O2 -DG_DISABLE_CHECKS -DG_DISABLE_ASSERT
  else
    $(error "BUILD_MODE error !(debug/release)")
  endif
endif

LOCAL_INCLUDES += $(EXTRA_LIBS_DIR) 
ifneq ($(RES_DIR),)
	LOCAL_CPPFLAGS +=-DRES_DIR=\""$(RES_DIR)"\"
	LOCAL_INCLUDES += $(RES_DIR)
endif

OUT_ROOT = $(BUILD_MODE)
intermediates := $(OUT_ROOT)

###############################################################################
##               Definition
###############################################################################
define all-files-under
$(patsubst ./%,%, \
  $(shell cd $(LOCAL_PATH) ; \
          find $(1) -name $(2) -and -not -name ".*") \
 )
endef

## Convert "path/to/libXXX.so" to "-lXXX".
## Any "path/to/libXXX.a" elements pass through unchanged.
define normalize-libraries
$(foreach so,$(filter %.so,$(1)),-l$(patsubst lib%.so,%,$(notdir $(so))))\
$(filter-out %.so,$(1))
endef

define normalize-target-libraries
$(call normalize-libraries,$(1))
endef

## Commands for munging the dependency files GCC generates
define transform-d-to-p
	@cp $(@:%.o=%.d) $(@:%.o=%.P); \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
        -e '/^$$/ d' -e 's/$$/ :/' < $(@:%.o=%.d) >> $(@:%.o=%.P); \
	rm -f $(@:%.o=%.d)
endef

# $(1): extra flags
define transform-host-c-or-s-to-o-no-deps
@$(MKDIR) $(dir $@)
$(LOCAL_CC) $(addprefix -I , $(LOCAL_INCLUDES)) $(LOCAL_CPPFLAGS) $(LOCAL_CFLAGS) -c $(1) -MD -o $@ $<
endef

define transform-files
@$(MKDIR) $(dir $@)
@$(CP) $< $@
endef

define transform-host-c-to-o
$(call transform-host-c-or-s-to-o-no-deps,)
$(transform-d-to-p)
endef

define transform-host-s-to-o
$(call transform-host-c-or-s-to-o-no-deps, $(LOCAL_ASFLAGS))
$(transform-d-to-p)
endef

## Commands for running gcc to compile a host C++ file
define transform-host-cpp-to-o
@$(MKDIR) $(dir $@)
$(LOCAL_CXX) $(addprefix -I , $(LOCAL_INCLUDES)) $(LOCAL_CPPFLAGS) $(LOCAL_CFLAGS) -c -MD -o $@ $<
$(transform-d-to-p)
endef

define transform-o-to-executable
@$(MKDIR) $(dir $@)
$(LOCAL_CXX) $(all_objects) -o $@ $(libs_path) $(call normalize-target-libraries,$(all_libraries)) $(LOCAL_LDFLAGS)
endef

## all objects
asm_sources := $(call all-files-under,$(SRC_ROOT),*.s)
asm_objects := $(addprefix $(intermediates)/,$(asm_sources_s:.s=.o))

c_sources := $(call all-files-under,$(SRC_ROOT),*.c)
c_objects := $(addprefix $(intermediates)/,$(c_sources:.c=.o))

cpp_sources := $(call all-files-under,$(SRC_ROOT),*.$(CPP_EXT))
cpp_objects := $(addprefix $(intermediates)/,$(cpp_sources:%.$(CPP_EXT)=%.o))

tmp_all_objects := $(asm_objects) $(c_objects) $(cpp_objects)
all_objects := $(strip $(tmp_all_objects))

## all libraries
ifneq ($(strip $(EXTRA_LIBS_DIR)),)
libs_path = $(addprefix -L, $(EXTRA_LIBS_DIR))
static_libs_sources := $(call all-files-under,$(EXTRA_LIBS_DIR),*.a)
static_libs_objs := $(addprefix $(intermediates)/, $(static_libs_sources))

dynamic_libs_sources := $(call all-files-under,$(EXTRA_LIBS_DIR),*.so)
dynamic_libs_objs := $(addprefix $(intermediates)/, $(dynamic_libs_sources))

all_libraries := $(static_libs_objs) $(dynamic_libs_objs)
endif

## all res
ifneq ($(strip $(RES_DIR)),)
res_sources := $(call all-files-under,$(RES_DIR),*.*)
res_objs := $(addprefix $(intermediates)/, $(res_sources))
all_resources := $(res_objs)
endif
###############################################################################
##               Rules
###############################################################################

linked_module :=$(intermediates)/$(TARGET)

.PHONY : all
all: $(linked_module)

$(linked_module): $(all_objects) $(all_libraries) $(all_resources)
	$(transform-o-to-executable)

ifneq ($(strip $(asm_objects)),)
$(asm_objects): $(intermediates)/%.o: $(LOCAL_PATH)/%.s
	$(transform-host-s-to-o)
-include $(asm_objects:%.o=%.P)
endif

ifneq ($(strip $(c_objects)),)
$(c_objects): $(intermediates)/%.o: $(LOCAL_PATH)/%.c 
	$(transform-host-c-to-o)
-include $(c_objects:%.o=%.P)
endif

ifneq ($(strip $(cpp_objects)),)
$(cpp_objects): $(intermediates)/%.o: $(LOCAL_PATH)/%.$(CPP_EXT)
	$(transform-host-cpp-to-o)
-include $(cpp_objects:%.o=%.P)
endif


ifneq ($(strip $(static_libs_objs)),)
$(static_libs_objs): $(intermediates)/%.a: $(LOCAL_PATH)/%.a
	$(transform-files)
endif

ifneq ($(strip $(dynamic_libs_objs)),)
$(dynamic_libs_objs): $(intermediates)/%.so: $(LOCAL_PATH)/%.so
	$(transform-files)
endif

ifneq ($(strip $(all_resources)),)
$(all_resources): $(intermediates)/%: $(LOCAL_PATH)/%
	$(transform-files)
endif

.PHONY : clean run
clean:
	@$(RM) $(OUT_ROOT)

run:
	@$(linked_module) 
