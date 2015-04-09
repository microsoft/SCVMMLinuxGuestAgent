TOP?=$(shell cd ..;pwd)

include $(TOP)/dev/config.mak
RELEASE=1

##==============================================================================
##
## rules targets:
##
##==============================================================================

DIRECTORIES = \
	pal \
	src \
	scripts \
	tools



CMARCH := $(shell $(TOP)/dev/tools/bin/arch -a)

include $(TOP)/dev/tools/build/rules.mak
include $(TOP)/build/Makefile.versionheader

##==============================================================================
##
## distclean:
##
##==============================================================================

distclean:
	rm -rf $(OUTPUTDIR)

release:: $(RELEASEDIR) $(RELTMP)
	  echo $(CMARCH) > $(RELTMP)/etc/buildarch
	  (cd $(RELTMP); tar cvf $(RELEASEDIR)/scvmmguestagent.$(VMM_VER).$(CMARCH).tar bin etc )
	  @ rm -rf $(RELTMP)

clean::
	rm -rf $(RELEASEDIR)
	rm -rf $(RELTMP)
	rm -f $(TOP)/dev/src/include/vmmbuildversion.h

tar:
	echo "Making tar"
	(cd $(RELTMP); tar cvf $(RELEASEDIR)/scvmmguestagent-$(CMARCH).tar bin etc )
