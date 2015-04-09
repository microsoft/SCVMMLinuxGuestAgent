TOP?=$(shell cd ../../..;pwd)

include $(TOP)/dev/config.mak

RELEASE=1

include $(TOP)/dev/tools/build/rules.mak
include $(TOP)/build/Makefile.versionheader

all: $(OUTPUTDIR)/etc
	@cat scvmm.conf | sed "s@<SCVMM_HOME>@$(OUTPUTDIR)@" > $(OUTPUTDIR)/etc/scvmm.conf
	@chmod 644 $(OUTPUTDIR)/etc/scvmm.conf

release: $(RELTMPETC)
	@ $(foreach i, $(DIRECTORIES), $(MAKE) -C $i release $(NL) )
	$(CP) scvmm.conf $(RELTMPETC)
	@chmod 644 $(RELTMPETC)/scvmm.conf
	@echo $(VMM_VER) > $(RELTMPETC)/version
	@chmod 644 $(RELTMPETC)/version

