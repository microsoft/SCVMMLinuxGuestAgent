TOP?=$(shell cd ../../../;pwd)

include $(TOP)/dev/config.mak

BINSCRIPTS = addme \
	     copyenv \
	     copykeys \
	     copytfspw \
	     createsshkeys \
	     nfsmount \
	     unmount \
	     pbcmd \
	     pushtfspw 


TMPDIR := $(shell echo "/tmp/env".`date +%s`)

env.tar:
	@echo -n "Building ~/env.tar..."
	@rm -rf $(TMPDIR)
	@mkdir -p $(TMPDIR)/bin
	@cp $(TOP)/dev/tools/bin/arch $(TMPDIR)/bin
	@cp $(BINSCRIPTS) $(TMPDIR)/bin
	@-cp ~/.bashrc_local $(TMPDIR)
	@-cp ~/.wincred $(TMPDIR)
	@`if [ -f ~/.pbuild ]; then cp ~/.pbuild $(TMPDIR)/.pbuild; else cp DOT_pbuild $(TMPDIR)/.pbuild; fi`
	@(cd $(TMPDIR); chmod 644 .pbuild)
	@cp DOT_bashrc $(TMPDIR)/.bashrc
	@cp DOT_bash_profile $(TMPDIR)/.bash_profile
	@cp DOT_bash_functions $(TMPDIR)/.bash_functions
	@(cd $(TMPDIR); chmod 644 .bash*)
	@(cd $(TMPDIR)/bin; chmod 755 *)
	@(cd $(TMPDIR); chmod 644 .pbuild .bashrc .bash_functions)
	@(cd $(TMPDIR); tar cf ~/env.tar .)
	@(rm -rf $(TMPDIR))
	@echo "done."
