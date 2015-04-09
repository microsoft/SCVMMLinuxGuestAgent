TOP?=$(shell cd ../../;pwd)

include $(TOP)/dev/config.mak

RELEASE=1

include $(TOP)/dev/tools/build/rules.mak

# The install scripts get copied directly to the release directory
# instead of the staging folder because it is not shipped in the tar
# file.

release:: $(RELTMP) $(RELTMPBIN) $(RELEASEDIR)
	$(CP) -f cfgroot $(RELTMPBIN)
	$(CP) -f cfgdynnetadapter $(RELTMPBIN)
	$(CP) -f cfghostdomain $(RELTMPBIN)
	$(CP) -f cfgnetadapter $(RELTMPBIN)
	$(CP) -f cfgpost $(RELTMPBIN)
	$(CP) -f cfgpre $(RELTMPBIN)
	$(CP) -f cfgtimezone $(RELTMPBIN)
	$(CP) -f tztable $(RELTMPBIN)
	$(CP) -f utilities $(RELTMPBIN)
	$(CP) -f scvmmguestagent $(RELTMPBIN)
	$(CP) -f install $(RELEASEDIR)
	@chmod 755 $(RELTMPBIN)/cfg* $(RELTMPBIN)/utilities $(RELTMPBIN)/scvmmguestagent $(RELEASEDIR)/install
