TOP?=$(shell cd ../../../../;pwd)

include $(TOP)/dev/config.mak

LIBRARY = commandexecutor

GUESTINC = $(TOP)/dev/src/include

SOURCES := commandexecutor.cpp

HEADERS := $(GUESTINC)

INCLUDES = $(TOP) \
        $(GUESTINC) \
	$(SCXPAL_SRC)/include \
	$(SCXPAL_INTERMEDIATE_DIR)/include

LIBRARIES=\
	scxcore \
	Util

include $(TOP)/dev/tools/build/rules.mak

