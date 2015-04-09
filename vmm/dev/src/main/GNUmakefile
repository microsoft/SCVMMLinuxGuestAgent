TOP?=$(shell cd ../../../;pwd)

RELEASE=1

include $(TOP)/build/Makefile.versionheader
include $(TOP)/dev/config.mak

CXXPROGRAM = scvmmguestagent.bin

GUESTINC = $(TOP)/dev/src/include
FETCHERINC = $(TOP)/dev/src/fetcher
OSCONFIGURATORINC = $(TOP)/dev/src/osconfigurator

SOURCES = \
	main.cpp \
	productdependencies.cpp

HEADERS = \
	$(wildcard *.h)

INCLUDES = \
	$(GUESTINC) \
	$(FETCHERINC) \
	$(OSCONFIGURATORINC) \
	$(SCXPAL_SRC)/include \
	$(SCXPAL_INTERMEDIATE_DIR)/include

LIBRARIES = \
	osconfigurator \
	osspecializationreader \
	fetcher \
	statusmanager \
	argumentmanager \
	commandexecutor \
	Util \
	scxcore

include $(TOP)/dev/tools/build/rules.mak

release:: $(RELTMPBIN) $(TARGET)
	$(CP) $(TARGET) $(RELTMPBIN)

