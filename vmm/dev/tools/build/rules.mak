##==============================================================================
##
## Phony targets.
##
##==============================================================================

.PHONY: gen all clean depend memcheck cachegrind proj release subdirs

##==============================================================================
##
## OpenSSL
##
##==============================================================================

OPENSSL_CFLAGS=$(shell $(PKGCONFIG) --cflags openssl)
OPENSSL_LIBS=$(shell $(PKGCONFIG) --libs openssl)
OPENSSL_LIBDIR=$(shell $(PKGCONFIG) --variable=libdir openssl)

##==============================================================================
##
## OBJDIRPATH -- resolve directory where objects will go.
##
##==============================================================================

OBJDIRPATH=$(OBJDIR)$(subst $(ROOT),,$(CURDIR))

ifeq ($(subst $(ROOT),,$(CURDIR)), $(ROOT))
  $(error "current directory seems to be a symbolic link")
endif

##==============================================================================
##
## Obtain build flags with 'buildtool'.
##
##==============================================================================

BUILDTOOL=$(ROOT)/tools/bin/buildtool

CC=$(shell $(BUILDTOOL) cc)

CXX=$(shell $(BUILDTOOL) cxx)

__OPTS=

ifeq ($(ENABLE_DEBUG),1)
  __OPTS += --debug
endif

ifeq ($(ENABLE_WERROR),1)
  __OPTS += --errwarn
endif

__OPTS += --pic

ifeq ($(NORTTI), 1)
  __OPTS += --nortti
endif

CFLAGS=$(shell $(BUILDTOOL) cflags $(__OPTS))

CXXFLAGS=$(shell $(BUILDTOOL) cxxflags $(__OPTS))

ifdef DISABLE_LIBPATH
  LIBPATHFLAGS=$(shell $(BUILDTOOL) libpath)
else
  LIBPATHFLAGS=$(shell $(BUILDTOOL) libpath $(CONFIG_LIBDIR))
endif

CSHLIBFLAGS=$(shell $(BUILDTOOL) cshlibflags)
CSHLIBFLAGS+=$(shell $(BUILDTOOL) syslibs)
CSHLIBFLAGS+=$(LIBPATHFLAGS)

CXXSHLIBFLAGS=$(shell $(BUILDTOOL) cxxshlibflags)
CXXSHLIBFLAGS+=$(shell $(BUILDTOOL) syslibs)
CXXSHLIBFLAGS+=$(LIBPATHFLAGS)

CPROGFLAGS=$(shell $(BUILDTOOL) cprogflags)
CPROGFLAGS+=$(shell $(BUILDTOOL) syslibs)
CPROGFLAGS+=$(LIBPATHFLAGS)

CXXPROGFLAGS=$(shell $(BUILDTOOL) cxxprogflags)
CXXPROGFLAGS+=$(shell $(BUILDTOOL) syslibs)
CXXPROGFLAGS+=$(LIBPATHFLAGS)

##==============================================================================
##
## OBJECTS:
##
##==============================================================================

__TMP = $(SOURCES:.c=.o)
__TMP2 = $(__TMP:.s=.o)
OBJECTS = $(__TMP2:.cpp=.o)
__OBJECTS = $(addprefix $(OBJDIRPATH)/,$(OBJECTS))

##==============================================================================
##
## LIBRARY target
##
##==============================================================================

ifdef LIBRARY

FOUND = 1

    $(shell mkdir -p $(OBJDIRPATH))

ifndef TOP
    $(error "Please define TOP variable")
endif

ifndef SOURCES
    $(error "Please define SOURCES variable")
endif


TARGET = $(LIBDIR)/lib$(LIBRARY).a

# The subdirs target is used in those folders where there is a one makefile 
# for a directory hierarchy.  The target extracts the directory names, and creates
# the output directories where the .o files will be placed.
$(TARGET): subdirs $(__OBJECTS)
	mkdir -p $(LIBDIR)
	ar r $(TARGET) $(__OBJECTS)

SUBDIRS = $(dir $(SOURCES))

subdirs:
	@for i in $(SUBDIRS); do if [ ! -d $(OBJDIRPATH)/$$i ]; then mkdir $(OBJDIRPATH)/$$i; fi done

endif

##==============================================================================
##
## CSHLIBRARY target
##
##==============================================================================

ifdef CSHLIBRARY

FOUND = 1

    $(shell mkdir -p $(OBJDIRPATH))

ifndef TOP
    $(error "Please define TOP variable")
endif

ifndef SOURCES
    $(error "Please define SOURCES variable")
endif

TARGET = $(LIBDIR)/$(shell $(BUILDTOOL) shlibname $(CSHLIBRARY))

__LIBRARIES = $(addprefix -l,$(LIBRARIES))
__LIBRARIES += $(addprefix -l,$(SYSLIBRARIES))

ifndef DISABLE_LIBPATH
LIBNAMEOPT=$(shell $(BUILDTOOL) libname $(CONFIG_LIBDIR)/$(shell $(BUILDTOOL) shlibname $(CSHLIBRARY)))
endif

$(TARGET): $(__OBJECTS)
	mkdir -p $(LIBDIR)
	$(CC) -o $(TARGET) $(__OBJECTS) $(ICONVLIB_LINK) -L$(LIBDIR) $(__LIBRARIES) $(CSHLIBFLAGS) $(LIBNAMEOPT)
	@ echo

chklib:
	$(BINDIR)/chklib $(TARGET)

endif

##==============================================================================
##
## CXXSHLIBRARY target
##
##==============================================================================

ifdef CXXSHLIBRARY

FOUND = 1

    $(shell mkdir -p $(OBJDIRPATH))

ifndef TOP
    $(error "Please define TOP variable")
endif

ifndef SOURCES
    $(error "Please define SOURCES variable")
endif

TARGET = $(LIBDIR)/$(shell $(BUILDTOOL) shlibname $(CXXSHLIBRARY))

__LIBRARIES = $(addprefix -l,$(LIBRARIES))
__LIBRARIES += $(addprefix -l,$(SYSLIBRARIES))

ifndef DISABLE_LIBPATH
LIBNAMEOPT=$(shell $(BUILDTOOL) libname $(CONFIG_LIBDIR)/$(shell $(BUILDTOOL) shlibname $(CXXSHLIBRARY)))
endif

$(TARGET): $(__OBJECTS)
	mkdir -p $(LIBDIR)
	$(CXX) -o $(TARGET) $(__OBJECTS) $(ICONVLIB_LINK) -L$(LIBDIR) $(__LIBRARIES) $(CXXSHLIBFLAGS) $(LIBNAMEOPT)
	@ echo

chklib:
	$(BINDIR)/chklib $(TARGET)

endif


##==============================================================================
##
## CPROGRAM target
##
##==============================================================================

ifdef CPROGRAM

FOUND = 1

    $(shell mkdir -p $(OBJDIRPATH))

ifndef TOP
    $(error "Please define TOP variable")
endif

ifndef SOURCES
    $(error "Please define SOURCES variable")
endif

TARGET = $(BINDIR)/$(CPROGRAM)

__LIBRARIES = $(addprefix -l,$(LIBRARIES))
__LIBRARIES += $(addprefix -l,$(SYSLIBRARIES))
__DEPS=$(wildcard $(addprefix $(LIBDIR)/lib,$(addsuffix .*,$(LIBRARIES))))

$(TARGET): $(__OBJECTS) $(__DEPS)
	mkdir -p $(BINDIR)
	$(CC) -o $(TARGET) $(__OBJECTS) $(ICONVLIB_LINK) -L$(LIBDIR) $(__LIBRARIES) $(CPROGFLAGS)
	@ echo

proj:
	$(ROOT)/mak/MakeProgramProject.sh \
            --guid=$(GUID) \
            --top=$(TOP) \
            --project=$(CPROGRAM) \
            --sources="$(subst /,\,$(SOURCES))" \
            --headers="$(subst /,\,$(HEADERS))" \
            --includes="$(INCLUDES)" \
            --defines="$(DEFINES)" \
            --libraries="$(LIBRARIES)"
endif

##==============================================================================
##
## CXXPROGRAM target
##
##==============================================================================

ifdef CXXPROGRAM

FOUND = 1

    $(shell mkdir -p $(OBJDIRPATH))

ifndef TOP
    $(error "Please define TOP variable")
endif

ifndef SOURCES
    $(error "Please define SOURCES variable")
endif

TARGET = $(BINDIR)/$(CXXPROGRAM)

__LIBRARIES = $(addprefix -l,$(LIBRARIES))
__LIBRARIES += $(addprefix -l,$(SYSLIBRARIES))

__LIBDIRS=-L$(LIBDIR) -L$(SCXPAL_TARGET_DIR)

__DEPS=$(wildcard $(addprefix $(LIBDIR)/lib,$(addsuffix .*,$(LIBRARIES))))


all: $(TARGET) $(EXTRA_RULE)

$(TARGET): $(__OBJECTS)  $(__DEPS)
	mkdir -p $(BINDIR)
	$(CXX) -o $(TARGET) $(__OBJECTS) $(ICONVLIB_LINK) $(__LIBDIRS) $(__LIBRARIES) $(CXXPROGFLAGS)
	@ echo

proj:
	$(ROOT)/mak/MakeProgramProject.sh \
            --guid=$(GUID) \
            --top=$(TOP) \
            --project=$(CXXPROGRAM) \
            --sources="$(subst /,\,$(SOURCES))" \
            --headers="$(subst /,\,$(HEADERS))" \
            --includes="$(INCLUDES)" \
            --defines="$(DEFINES)" \
            --libraries="$(LIBRARIES)"

endif

##==============================================================================
##
## DIRECTORIES target
##
##==============================================================================

ifdef DIRECTORIES

FOUND = 1

# define a newline macro
define NL


endef

all: $(PREREQ_TARGET)
	@ $(foreach i, $(DIRECTORIES), $(MAKE) -C $i $(NL) )

# Changed to :: so that additional clean:: target could be in individual makefile.
clean::
	@ $(foreach i, $(DIRECTORIES), $(MAKE) -C $i clean $(NL) )

depend:
	@ $(foreach i, $(DIRECTORIES), $(MAKE) -C $i depend $(NL) )

release::
	@ $(foreach i, $(DIRECTORIES), $(MAKE) -C $i release $(NL) )

endif

##==============================================================================
##
## For Makefiles which have only a release target
##
##==============================================================================

# Define this variable if your makefile only includes a release target.

ifdef RELEASE

FOUND = 1

$(RELTMP): 
	@mkdir -p $@

$(RELTMPETC):
	@mkdir -p $@

$(RELTMPBIN):
	@mkdir -p $@

$(RELEASEDIR):
	@mkdir -p $@

endif

##==============================================================================
##
## Check that one of the targets above was defined
##
##==============================================================================

ifndef FOUND

TARGETS = \
    LIBRARY \
    LIBDIR \
    CSHLIBRARY \
    CXXSHLIBRARY \
    CPROGRAM \
    CXXPROGRAM \
    DIRECTORIES \
	RELEASE

$(error "Please define one of the following targets: $(TARGETS)")

endif

##==============================================================================
##
## AUTOCHECKOUT -- checkout files from TFS automatically when they have
## compiler errors or warnings.
##
##==============================================================================

ifdef AUTOCHECKOUT
  ifndef SUPPRESS_CCTOOL
    CWRAP=$(BINDIR)/cctool --cctool-exec tf co {} --
    CXXWRAP=$(CWRAP)
  endif
endif

##==============================================================================
##
## STDERRX - exit whenever a command writes anything to standard error.
## to standard error.
##
##==============================================================================

ifdef STDERRX
  ifndef SUPPRESS_STDERRX
    CWRAP=$(BINDIR)/stderrx
    CXXWRAP=$(CWRAP)
  endif
endif

##==============================================================================
##
## USECCACHE
##
##==============================================================================

ifdef USECCACHE
    CWRAP=ccache
    CXXWRAP=$(CWRAP)
endif

##==============================================================================
##
## Object file targets
##
##==============================================================================

__INCLUDES = -I$(INCDIR) $(addprefix -I,$(INCLUDES))

__DEFINES = $(addprefix -D,$(DEFINES))

compilec = \
    $(CWRAP) $(CC) -c -o $@ $(CFLAGS) $(__INCLUDES) $(__DEFINES) $(1) $(2)

compilecxx = \
    $(CXXWRAP) $(CXX) -c -o $@ $(CXXFLAGS) $(__INCLUDES) $(__DEFINES) $(1) $(2)

compiles = \
    $(CC) -c -o $@ $(CFLAGS) $(__INCLUDES) $(__DEFINES) $(1) $(2)

$(OBJDIRPATH)/%.o: %.c
	$(call compilec,$<)
	@ echo

$(OBJDIRPATH)/%.o: %.cpp
	$(call compilecxx,$<)
	@ echo

$(OBJDIRPATH)/%.o: %.s
	$(call compiles,$<)
	@ echo

##==============================================================================
##
## clean target
##
##==============================================================================

ifndef DIRECTORIES
# Changed to :: so that additional clean:: target could be in individual makefile.
clean::
	rm -rf $(TARGET) $(__OBJECTS) $(OBJDIRPATH)/depend.mak $(CLEANFILES)
endif

##==============================================================================
##
## depend target
##
##==============================================================================

MKDEP=$(BINDIR)/mkdep

ifndef DIRECTORIES
ifdef SOURCES
depend: $(BINDIR)/mkdep
	$(MKDEP) --objdir $(OBJDIRPATH) $(__INCLUDES) $(SOURCES) > $(OBJDIRPATH)/depend.mak
endif
endif

# Only build if we are not in the mkdep source directory.
ifndef MAKEDEPSRCDIR
$(BINDIR)/mkdep:
	$(MAKE) -C $(ROOT)/dev/tools/mkdep
endif

##==============================================================================
##
## memcheck target
##
##==============================================================================

MEMCHECK=valgrind --tool=memcheck --leak-check=full --error-exitcode=1 --gen-suppressions=all --track-fds=yes

ifdef MEMCHECK_SUPPRESS
  __MEMCHECK_SUPPRESS = --suppressions=$(MEMCHECK_SUPPRESS)
endif

memcheck:
	$(MEMCHECK) $(__MEMCHECK_SUPPRESS) $(TARGET) $(MEMCHECK_ARGS)

##==============================================================================
##
## errfiles - print a list of files that have errors (or warnings).
##
##==============================================================================

errfiles:
	@ ( $(MAKE) -i 2>&1 | $(BINDIR)/errfiles )

coerrfiles:
	@ ( $(MAKE) -i 2>&1 | $(BINDIR)/errfiles > ERRORFILES; tf co `cat ERRORFILES`; rm -f ERRORFILES )

##==============================================================================
##
## cachegrind target
##
##==============================================================================

CACHEGRIND=valgrind --tool=cachegrind

cachegrind:
	$(CACHEGRIND) --cachegrind-out-file=callgrind.out $(TARGET) $(ARGUMENTS) $(MEMCHECK_ARGS)
	cg_annotate --auto=yes callgrind.out > cg_annotate.out
	rm -f callgrind.out
	@ echo "Created cg_annotate.out"

##==============================================================================
##
## cogen target:
##
##==============================================================================

STATIKGEN=`grep -r -l '@''migen@' .`

cogen:
	tf co $(STATIKGEN)

##==============================================================================
##
## Include depend.mak
##
##==============================================================================

-include $(OBJDIRPATH)/depend.mak

