TOP?=$(shell cd ../../;pwd)

include $(TOP)/dev/config.mak

RELEASE=1

DIRECTORIES = config

include $(TOP)/dev/tools/build/rules.mak

release:: $(RELTMPBIN)
	$(CP) -f  ./bin/arch $(RELTMPBIN)

clean::
	rm -rf $(SCRIPTRELDIR)
