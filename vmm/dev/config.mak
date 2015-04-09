TOP?=$(shell cd ..;pwd)

OUTPUTDIR=$(TOP)/dev/output/$(shell $(TOP)/dev/tools/bin/buildtool hostname)

-include $(OUTPUTDIR)/config.mak

ifndef CONFIG_MAK
$(error "Please use ./configure script to configure for this platform")
endif

ifndef SCXPAL_DIR
$(error "Please use ./configure script to configure for this platform")
endif

-include $(SCXPAL_DIR)/build/config.mak
