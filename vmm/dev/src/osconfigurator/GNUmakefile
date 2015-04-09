TOP?=$(shell cd ../../../;pwd)

include $(TOP)/dev/config.mak

LIBRARY = osconfigurator

GUESTINC = $(TOP)/dev/src/include

SOURCES = \
	executevisitor.cpp \
	hostdomainconfigurator.cpp \
	networkconfigurator.cpp \
	runoncecommandconfigurator.cpp \
	preconfigurator.cpp \
	usersconfigurator.cpp 

HEADERS = $(wildcard *.h)

INCLUDES = \
	$(shell pwd) \
	$(TOP) \
	$(GUESTINC) \
	$(SCXPAL_SRC)/include \
	$(SCXPAL_INTERMEDIATE_DIR)/include

LIBRARIES = \
	fetcher \
	osspecializationreader \
	statusmanager \
	scxcore \
	Util

include $(TOP)/dev/tools/build/rules.mak
