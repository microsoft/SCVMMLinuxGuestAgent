TOP?=$(shell cd ../../../;pwd)

include $(TOP)/dev/config.mak

LIBRARY = fetcher

GUESTINC = $(TOP)/dev/src/include

SOURCES := isofetcher.cpp

HEADERS := \
	$(GUESTINC)

INCLUDES = \
	$(shell pwd) \
        $(GUESTINC) \
	$(SCXPAL_SRC)/include \
	$(SCXPAL_INTERMEDIATE_DIR)/include

LIBRARIES=\
	argumentmanager \
	osspecializationreader \
	scxcore \
	Util

include $(TOP)/dev/tools/build/rules.mak

