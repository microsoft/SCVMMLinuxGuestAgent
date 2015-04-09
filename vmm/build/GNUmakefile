#.PHONY: all configure clean build release
.PHONY: all configure clean release

buildtype=release

TOP?=$(shell cd ..; pwd)

BUILDDIR:=$(TOP)/dev

all: configure build release

TARGET:=$(TOP)/target

ifeq ($(buildtype), debug)
	CONFIGOPTS=--enable-debug
endif


#ejm
PAL_LIBS: $(SCXPAL_TARGET_DIR)/libutil.a

$(SCXPAL_TARGET_DIR)/libutil.a:
	cd $(SCXPAL_DIR)/build && $(MAKE) libutil.a


configure:
	(cd $(BUILDDIR); ./configure $(CONFIGOPTS))

build: $(PAL_LIBS) 
	(cd $(BUILDDIR); $(MAKE) all)

clean:
	(cd $(BUILDDIR); $(MAKE) clean)

release:
	(cd $(BUILDDIR); $(MAKE) release RELEASEDIR=$(TARGET))


include $(TOP)/build/Makefile.versionheader
