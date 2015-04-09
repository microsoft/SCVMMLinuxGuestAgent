TOP?=$(shell cd ../../;pwd)

include $(TOP)/dev/config.mak

.PHONY: all clean test

INTERMEDIATE_DIR=$(OUTPUTDIR)/lib


# define a newline macro
define NL


endef

SOFTLINK=ln -sf

SCXPAL_LINKS = \
	libscxcore.a \
	libUtil.a

LINKS = \
	$(SCXPAL_LINKS)

all: 
	$(MAKE) -C $(SCXPAL_DIR)/build all BUILD_TYPE='$(BUILD_TYPE)' ULINUX='$(ULINUX)'
	@$(foreach i, $(LINKS), $(RM) $(OUTPUTDIR)/lib/$i $(NL) )
	@$(foreach i, $(SCXPAL_LINKS), $(SOFTLINK) $(SCXPAL_TARGET_DIR)/$i $(OUTPUTDIR)/lib/$i $(NL) )
	@$(SOFTLINK) $(SHAREDBASE64LIBDIR)/libbase64.a  $(INTERMEDIATE_DIR)/libbase64.a 

clean: 
	$(MAKE) -C $(SCXPAL_DIR)/build clean BUILD_TYPE='$(BUILD_TYPE)' ULINUX='$(ULINUX)'
	@$(foreach i, $(LINKS), $(RM) $(OUTPUTDIR)/lib/$i $(NL) )

release:
