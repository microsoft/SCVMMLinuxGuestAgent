TOP?=$(shell cd ../../../;pwd)

include $(TOP)/dev/config.mak

LIBRARY = statusmanager

GUESTINC = $(TOP)/dev/src/include

SOURCES = \
	statusmessagestrings.cpp \
	statusmessage.cpp

INCLUDES = \
	$(TOP) \
	$(GUESTINC) \
	$(SCXPAL_SRC)/include \
	$(SCXPAL_INTERMEDIATE_DIR)/include

LIBRARIES = \
	Util \
	scxcore

include $(TOP)/dev/tools/build/rules.mak