# This Makefile is for the par.exe extension to perl.
#
# It was generated automatically by MakeMaker version
# 6.98 (Revision: 69800) from the contents of
# Makefile.PL. Don't edit this file, edit Makefile.PL instead.
#
#       ANY CHANGES MADE HERE WILL BE LOST!
#
#   MakeMaker ARGV: (q[INSTALLDIRS=site])
#

#   MakeMaker Parameters:

#     BUILD_REQUIRES => {  }
#     CONFIGURE_REQUIRES => {  }
#     EXE_FILES => [q[parl.exe], q[parldyn.exe]]
#     MAN1PODS => {  }
#     NAME => q[par.exe]
#     NO_META => q[1]
#     PL_FILES => {  }
#     PM => { Dynamic.pm=>q[$(INST_LIBDIR)\PAR\StrippedPARL\Dynamic.pm], Static.pm=>q[$(INST_LIBDIR)\PAR\StrippedPARL\Static.pm] }
#     PREREQ_PM => {  }
#     SKIP => [q[static], q[static_lib], q[dynamic], q[dynamic_lib], q[test]]
#     TEST_REQUIRES => {  }
#     macro => { FIXIN=>q[$(NOOP)] }

# --- MakeMaker post_initialize section:


# --- MakeMaker const_config section:

# These definitions are from config.sh (via c:/Perl/lib/Config.pm).
# They may have been overridden via Makefile.PL or on the command line.
AR = c:\perl\site\bin\ar.exe
CC = c:\perl\site\bin\gcc.exe
CCCDLFLAGS =  
CCDLFLAGS =  
DLEXT = dll
DLSRC = dl_win32.xs
EXE_EXT = .exe
FULL_AR = 
LD = c:\perl\site\bin\g++.exe
LDDLFLAGS = -mdll -s -static-libgcc -static-libstdc++ -L"C:\Perl\lib\CORE" -L"C:\MinGW\i686-w64-mingw32\lib"
LDFLAGS = -s -static-libgcc -static-libstdc++ -L"C:\Perl\lib\CORE" -L"C:\MinGW\i686-w64-mingw32\lib"
LIBC = 
LIB_EXT = .a
OBJ_EXT = .o
OSNAME = MSWin32
OSVERS = 5.2
RANLIB = ranlib
SITELIBEXP = C:\Perl\site\lib
SITEARCHEXP = C:\Perl\site\lib
SO = dll
VENDORARCHEXP = 
VENDORLIBEXP = 


# --- MakeMaker constants section:

# Get dmake to read long commands like PM_TO_BLIB
MAXLINELENGTH = 800000

AR_STATIC_ARGS = cr
DIRFILESEP = \\
DFSEP = $(DIRFILESEP)
NAME = par.exe
NAME_SYM = par_exe
VERSION = 
VERSION_MACRO = VERSION
VERSION_SYM = 
DEFINE_VERSION = -D$(VERSION_MACRO)=\"$(VERSION)\"
XS_VERSION = 
XS_VERSION_MACRO = XS_VERSION
XS_DEFINE_VERSION = -D$(XS_VERSION_MACRO)=\"$(XS_VERSION)\"
INST_ARCHLIB = ..\blib\arch
INST_SCRIPT = ..\blib\script
INST_BIN = ..\blib\bin
INST_LIB = ..\blib\lib
INST_MAN1DIR = ..\blib\man1
INST_MAN3DIR = ..\blib\man3
INST_HTMLDIR = ..\blib\html
MAN1EXT = 1
MAN3EXT = 3
INSTALLDIRS = site
DESTDIR = 
PREFIX = $(SITEPREFIX)
PERLPREFIX = C:\Perl
SITEPREFIX = C:\Perl\site
VENDORPREFIX = 
INSTALLPRIVLIB = C:\Perl\lib
DESTINSTALLPRIVLIB = $(DESTDIR)$(INSTALLPRIVLIB)
INSTALLSITELIB = C:\Perl\site\lib
DESTINSTALLSITELIB = $(DESTDIR)$(INSTALLSITELIB)
INSTALLVENDORLIB = 
DESTINSTALLVENDORLIB = $(DESTDIR)$(INSTALLVENDORLIB)
INSTALLARCHLIB = C:\Perl\lib
DESTINSTALLARCHLIB = $(DESTDIR)$(INSTALLARCHLIB)
INSTALLSITEARCH = C:\Perl\site\lib
DESTINSTALLSITEARCH = $(DESTDIR)$(INSTALLSITEARCH)
INSTALLVENDORARCH = 
DESTINSTALLVENDORARCH = $(DESTDIR)$(INSTALLVENDORARCH)
INSTALLBIN = C:\Perl\bin
DESTINSTALLBIN = $(DESTDIR)$(INSTALLBIN)
INSTALLSITEBIN = C:\Perl\site\bin
DESTINSTALLSITEBIN = $(DESTDIR)$(INSTALLSITEBIN)
INSTALLVENDORBIN = 
DESTINSTALLVENDORBIN = $(DESTDIR)$(INSTALLVENDORBIN)
INSTALLSCRIPT = C:\Perl\bin
DESTINSTALLSCRIPT = $(DESTDIR)$(INSTALLSCRIPT)
INSTALLSITESCRIPT = C:\Perl\site\bin
DESTINSTALLSITESCRIPT = $(DESTDIR)$(INSTALLSITESCRIPT)
INSTALLVENDORSCRIPT = 
DESTINSTALLVENDORSCRIPT = $(DESTDIR)$(INSTALLVENDORSCRIPT)
INSTALLMAN1DIR = C:\Perl\man\man1
DESTINSTALLMAN1DIR = $(DESTDIR)$(INSTALLMAN1DIR)
INSTALLSITEMAN1DIR = $(INSTALLMAN1DIR)
DESTINSTALLSITEMAN1DIR = $(DESTDIR)$(INSTALLSITEMAN1DIR)
INSTALLVENDORMAN1DIR = 
DESTINSTALLVENDORMAN1DIR = $(DESTDIR)$(INSTALLVENDORMAN1DIR)
INSTALLMAN3DIR = C:\Perl\man\man3
DESTINSTALLMAN3DIR = $(DESTDIR)$(INSTALLMAN3DIR)
INSTALLSITEMAN3DIR = $(INSTALLMAN3DIR)
DESTINSTALLSITEMAN3DIR = $(DESTDIR)$(INSTALLSITEMAN3DIR)
INSTALLVENDORMAN3DIR = 
DESTINSTALLVENDORMAN3DIR = $(DESTDIR)$(INSTALLVENDORMAN3DIR)
INSTALLHTMLDIR = C:\Perl\html
DESTINSTALLHTMLDIR = $(DESTDIR)$(INSTALLHTMLDIR)
INSTALLSITEHTMLDIR = C:\Perl\html
DESTINSTALLSITEHTMLDIR = $(DESTDIR)$(INSTALLSITEHTMLDIR)
INSTALLVENDORHTMLDIR = C:\Perl\html
DESTINSTALLVENDORHTMLDIR = $(DESTDIR)$(INSTALLVENDORHTMLDIR)
PERL_LIB = C:\Perl\lib
PERL_ARCHLIB = C:\Perl\lib
LIBPERL_A = libperl.a
FIRST_MAKEFILE = Makefile
MAKEFILE_OLD = Makefile.old
MAKE_APERL_FILE = Makefile.aperl
PERLMAINCC = $(CC)
PERL_INC = C:\Perl\lib\CORE
PERL = C:\perl\bin\perl.exe
FULLPERL = C:\perl\bin\perl.exe
ABSPERL = $(PERL)
PERLRUN = $(PERL)
FULLPERLRUN = $(FULLPERL)
ABSPERLRUN = $(ABSPERL)
PERLRUNINST = $(PERLRUN) "-I$(INST_ARCHLIB)" "-I$(INST_LIB)"
FULLPERLRUNINST = $(FULLPERLRUN) "-I$(INST_ARCHLIB)" "-I$(INST_LIB)"
ABSPERLRUNINST = $(ABSPERLRUN) "-I$(INST_ARCHLIB)" "-I$(INST_LIB)"
PERL_CORE = 0
PERM_DIR = 755
PERM_RW = 644
PERM_RWX = 755

MAKEMAKER   = c:/Perl/lib/ExtUtils/MakeMaker.pm
MM_VERSION  = 6.98
MM_REVISION = 69800

# FULLEXT = Pathname for extension directory (eg Foo/Bar/Oracle).
# BASEEXT = Basename part of FULLEXT. May be just equal FULLEXT. (eg Oracle)
# PARENT_NAME = NAME without BASEEXT and no trailing :: (eg Foo::Bar)
# DLBASE  = Basename part of dynamic library. May be just equal BASEEXT.
MAKE = c:\perl\site\bin\dmake.exe
FULLEXT = par.exe
BASEEXT = exe
PARENT_NAME = 
DLBASE = $(BASEEXT)
VERSION_FROM = 
OBJECT = $(BASEEXT)$(OBJ_EXT)
LDFROM = $(OBJECT)
LINKTYPE = dynamic
BOOTDEP = 

# Handy lists of source code files:
XS_FILES = 
C_FILES  = boot.c \
	env.c \
	internals.c \
	main.c \
	mktmpdir.c \
	perlxsi.c \
	usernamefrompwuid.c \
	utils.c
O_FILES  = boot.o \
	env.o \
	internals.o \
	main.o \
	mktmpdir.o \
	perlxsi.o \
	usernamefrompwuid.o \
	utils.o
H_FILES  = mktmpdir.h \
	usernamefrompwuid.h
MAN1PODS = 
MAN3PODS = Dynamic.pm \
	Static.pm

# Where is the Config information that we are using/depend on
CONFIGDEP = $(PERL_ARCHLIB)$(DFSEP)Config.pm $(PERL_INC)$(DFSEP)config.h

# Where to build things
INST_LIBDIR      = $(INST_LIB)
INST_ARCHLIBDIR  = $(INST_ARCHLIB)

INST_AUTODIR     = $(INST_LIB)\auto\$(FULLEXT)
INST_ARCHAUTODIR = $(INST_ARCHLIB)\auto\$(FULLEXT)

INST_STATIC      = $(INST_ARCHAUTODIR)\$(BASEEXT)$(LIB_EXT)
INST_DYNAMIC     = $(INST_ARCHAUTODIR)\$(DLBASE).$(DLEXT)
INST_BOOT        = $(INST_ARCHAUTODIR)\$(BASEEXT).bs

# Extra linker info
EXPORT_LIST        = $(BASEEXT).def
PERL_ARCHIVE       = $(PERL_INC)\libperl520.a
PERL_ARCHIVE_AFTER = 


TO_INST_PM = Dynamic.pm \
	Static.pm

PM_TO_BLIB = Dynamic.pm \
	$(INST_LIBDIR)\PAR\StrippedPARL\Dynamic.pm \
	Static.pm \
	$(INST_LIBDIR)\PAR\StrippedPARL\Static.pm


# --- MakeMaker platform_constants section:
MM_Win32_VERSION = 6.98


# --- MakeMaker tool_autosplit section:
# Usage: $(AUTOSPLITFILE) FileToSplit AutoDirToSplitInto
AUTOSPLITFILE = $(ABSPERLRUN)  -e "use AutoSplit;  autosplit($$$$ARGV[0], $$$$ARGV[1], 0, 1, 1)" --



# --- MakeMaker tool_xsubpp section:

XSUBPPDIR = C:\Perl\lib\ExtUtils
XSUBPP = $(XSUBPPDIR)$(DFSEP)xsubpp
XSUBPPRUN = $(PERLRUN) $(XSUBPP)
XSPROTOARG = 
XSUBPPDEPS = C:\Perl\lib\ExtUtils\typemap $(XSUBPP)
XSUBPPARGS = -typemap C:\Perl\lib\ExtUtils\typemap
XSUBPP_EXTRA_ARGS =


# --- MakeMaker tools_other section:
CHMOD = $(ABSPERLRUN) -MExtUtils::Command -e chmod --
CP = $(ABSPERLRUN) -MExtUtils::Command -e cp --
MV = $(ABSPERLRUN) -MExtUtils::Command -e mv --
NOOP = rem
NOECHO = @
RM_F = $(ABSPERLRUN) -MExtUtils::Command -e rm_f --
RM_RF = $(ABSPERLRUN) -MExtUtils::Command -e rm_rf --
TEST_F = $(ABSPERLRUN) -MExtUtils::Command -e test_f --
TOUCH = $(ABSPERLRUN) -MExtUtils::Command -e touch --
UMASK_NULL = umask 0
DEV_NULL = > NUL
MKPATH = $(ABSPERLRUN) -MExtUtils::Command -e mkpath --
EQUALIZE_TIMESTAMP = $(ABSPERLRUN) -MExtUtils::Command -e eqtime --
FALSE = $(ABSPERLRUN)  -e "exit 1" --
TRUE = $(ABSPERLRUN)  -e "exit 0" --
ECHO = $(ABSPERLRUN) -l -e "print qq{{@ARGV}}" --
ECHO_N = $(ABSPERLRUN)  -e "print qq{{@ARGV}}" --
UNINST = 0
VERBINST = 0
MOD_INSTALL = $(ABSPERLRUN) -MExtUtils::Install -e "install([ from_to => {{@ARGV}}, verbose => '$(VERBINST)', uninstall_shadows => '$(UNINST)', dir_mode => '$(PERM_DIR)' ]);" --
DOC_INSTALL = $(ABSPERLRUN) -MExtUtils::Command::MM -e perllocal_install --
UNINSTALL = $(ABSPERLRUN) -MExtUtils::Command::MM -e uninstall --
WARN_IF_OLD_PACKLIST = $(ABSPERLRUN) -MExtUtils::Command::MM -e warn_if_old_packlist --
MACROSTART = 
MACROEND = 
USEMAKEFILE = -f
FIXIN = pl2bat.bat
CP_NONEMPTY = $(ABSPERLRUN) -MExtUtils::Command::MM -e cp_nonempty --


# --- MakeMaker makemakerdflt section:
makemakerdflt : all
	$(NOECHO) $(NOOP)


# --- MakeMaker dist section skipped.

# --- MakeMaker macro section:
FIXIN = $(NOOP)


# --- MakeMaker depend section:


# --- MakeMaker cflags section:

CCFLAGS = -s -O2 -DWIN32 -DPERL_TEXTMODE_SCRIPTS -DUSE_SITECUSTOMIZE -DPERL_IMPLICIT_CONTEXT -DPERL_IMPLICIT_SYS -DUSE_PERLIO -fwrapv -fno-strict-aliasing -mms-bitfields
OPTIMIZE = -s -O2
PERLTYPE = 


# --- MakeMaker const_loadlibs section:

# par.exe might depend on some other libraries:
# See ExtUtils::Liblist for details
#
LDLOADLIBS = -lmoldname -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -lnetapi32 -luuid -lws2_32 -lmpr -lwinmm -lversion -lodbc32 -lodbccp32 -lcomctl32


# --- MakeMaker const_cccmd section:
CCCMD = $(CC) -c $(PASTHRU_INC) $(INC) \
	$(CCFLAGS) $(OPTIMIZE) \
	$(PERLTYPE) $(MPOLLUTE) $(DEFINE_VERSION) \
	$(XS_DEFINE_VERSION)

# --- MakeMaker post_constants section:


# --- MakeMaker pasthru section:
PASTHRU = 

# --- MakeMaker special_targets section:
.SUFFIXES : .xs .c .C .cpp .i .s .cxx .cc $(OBJ_EXT)

.PHONY: all config static dynamic test linkext manifest blibdirs clean realclean disttest distdir

.USESHELL :


# --- MakeMaker c_o section:

.c.i:
	gcc -E -c $(PASTHRU_INC) $(INC) \
	$(CCFLAGS) $(OPTIMIZE) \
	$(PERLTYPE) $(MPOLLUTE) $(DEFINE_VERSION) \
	$(XS_DEFINE_VERSION) $(CCCDLFLAGS) "-I$(PERL_INC)" $(PASTHRU_DEFINE) $(DEFINE) $*.c > $*.i

.c.s:
	$(CCCMD) -S $(CCCDLFLAGS) "-I$(PERL_INC)" $(PASTHRU_DEFINE) $(DEFINE) $*.c

.c$(OBJ_EXT):
	$(CCCMD) $(CCCDLFLAGS) "-I$(PERL_INC)" $(PASTHRU_DEFINE) $(DEFINE) $*.c

.cpp$(OBJ_EXT):
	$(CCCMD) $(CCCDLFLAGS) "-I$(PERL_INC)" $(PASTHRU_DEFINE) $(DEFINE) $*.cpp

.cxx$(OBJ_EXT):
	$(CCCMD) $(CCCDLFLAGS) "-I$(PERL_INC)" $(PASTHRU_DEFINE) $(DEFINE) $*.cxx

.cc$(OBJ_EXT):
	$(CCCMD) $(CCCDLFLAGS) "-I$(PERL_INC)" $(PASTHRU_DEFINE) $(DEFINE) $*.cc


# --- MakeMaker xs_c section:

.xs.c:
	$(XSUBPPRUN) $(XSPROTOARG) $(XSUBPPARGS) $(XSUBPP_EXTRA_ARGS) $*.xs > $*.xsc && $(MV) $*.xsc $*.c


# --- MakeMaker xs_o section:


# --- MakeMaker top_targets section:
all :: pure_all htmlifypods
	$(NOECHO) $(NOOP)


pure_all :: config pm_to_blib subdirs linkext
	$(NOECHO) $(NOOP)

subdirs :: $(MYEXTLIB)
	$(NOECHO) $(NOOP)

config :: $(FIRST_MAKEFILE) blibdirs
	$(NOECHO) $(NOOP)

$(O_FILES): $(H_FILES)

help :
	perldoc ExtUtils::MakeMaker


# --- MakeMaker blibdirs section:
blibdirs : $(INST_LIBDIR)$(DFSEP).exists $(INST_ARCHLIB)$(DFSEP).exists $(INST_AUTODIR)$(DFSEP).exists $(INST_ARCHAUTODIR)$(DFSEP).exists $(INST_BIN)$(DFSEP).exists $(INST_SCRIPT)$(DFSEP).exists $(INST_MAN1DIR)$(DFSEP).exists $(INST_MAN3DIR)$(DFSEP).exists
	$(NOECHO) $(NOOP)

# Backwards compat with 6.18 through 6.25
blibdirs.ts : blibdirs
	$(NOECHO) $(NOOP)

$(INST_LIBDIR)$(DFSEP).exists :: Makefile.PL
	$(NOECHO) $(MKPATH) $(INST_LIBDIR)
	$(NOECHO) $(CHMOD) $(PERM_DIR) $(INST_LIBDIR)
	$(NOECHO) $(TOUCH) $(INST_LIBDIR)$(DFSEP).exists

$(INST_ARCHLIB)$(DFSEP).exists :: Makefile.PL
	$(NOECHO) $(MKPATH) $(INST_ARCHLIB)
	$(NOECHO) $(CHMOD) $(PERM_DIR) $(INST_ARCHLIB)
	$(NOECHO) $(TOUCH) $(INST_ARCHLIB)$(DFSEP).exists

$(INST_AUTODIR)$(DFSEP).exists :: Makefile.PL
	$(NOECHO) $(MKPATH) $(INST_AUTODIR)
	$(NOECHO) $(CHMOD) $(PERM_DIR) $(INST_AUTODIR)
	$(NOECHO) $(TOUCH) $(INST_AUTODIR)$(DFSEP).exists

$(INST_ARCHAUTODIR)$(DFSEP).exists :: Makefile.PL
	$(NOECHO) $(MKPATH) $(INST_ARCHAUTODIR)
	$(NOECHO) $(CHMOD) $(PERM_DIR) $(INST_ARCHAUTODIR)
	$(NOECHO) $(TOUCH) $(INST_ARCHAUTODIR)$(DFSEP).exists

$(INST_BIN)$(DFSEP).exists :: Makefile.PL
	$(NOECHO) $(MKPATH) $(INST_BIN)
	$(NOECHO) $(CHMOD) $(PERM_DIR) $(INST_BIN)
	$(NOECHO) $(TOUCH) $(INST_BIN)$(DFSEP).exists

$(INST_SCRIPT)$(DFSEP).exists :: Makefile.PL
	$(NOECHO) $(MKPATH) $(INST_SCRIPT)
	$(NOECHO) $(CHMOD) $(PERM_DIR) $(INST_SCRIPT)
	$(NOECHO) $(TOUCH) $(INST_SCRIPT)$(DFSEP).exists

$(INST_MAN1DIR)$(DFSEP).exists :: Makefile.PL
	$(NOECHO) $(MKPATH) $(INST_MAN1DIR)
	$(NOECHO) $(CHMOD) $(PERM_DIR) $(INST_MAN1DIR)
	$(NOECHO) $(TOUCH) $(INST_MAN1DIR)$(DFSEP).exists

$(INST_MAN3DIR)$(DFSEP).exists :: Makefile.PL
	$(NOECHO) $(MKPATH) $(INST_MAN3DIR)
	$(NOECHO) $(CHMOD) $(PERM_DIR) $(INST_MAN3DIR)
	$(NOECHO) $(TOUCH) $(INST_MAN3DIR)$(DFSEP).exists



# --- MakeMaker linkext section:

linkext :: $(LINKTYPE)
	$(NOECHO) $(NOOP)


# --- MakeMaker dlsyms section:


# --- MakeMaker dynamic_bs section:
BOOTSTRAP = $(BASEEXT).bs

# As Mkbootstrap might not write a file (if none is required)
# we use touch to prevent make continually trying to remake it.
# The DynaLoader only reads a non-empty file.
$(BOOTSTRAP) : $(FIRST_MAKEFILE) $(BOOTDEP) $(INST_ARCHAUTODIR)$(DFSEP).exists
	$(NOECHO) $(ECHO) "Running Mkbootstrap for $(NAME) ($(BSLOADLIBS))"
	$(NOECHO) $(PERLRUN) \
		"-MExtUtils::Mkbootstrap" \
		-e "Mkbootstrap('$(BASEEXT)','$(BSLOADLIBS)');"
	$(NOECHO) $(TOUCH) $@
	$(CHMOD) $(PERM_RW) $@


# --- MakeMaker dynamic section skipped.

# --- MakeMaker dynamic_lib section skipped.

# --- MakeMaker static section skipped.

# --- MakeMaker static_lib section skipped.

# --- MakeMaker manifypods section:

POD2MAN_EXE = $(PERLRUN) "-MExtUtils::Command::MM" -e pod2man "--"
POD2MAN = $(POD2MAN_EXE)


manifypods : pure_all  \
	Dynamic.pm \
	Static.pm
	$(NOECHO) $(POD2MAN) --section=3 --perm_rw=$(PERM_RW) \
	  Dynamic.pm $(INST_MAN3DIR)\Dynamic.$(MAN3EXT) \
	  Static.pm $(INST_MAN3DIR)\Static.$(MAN3EXT) 




# --- MakeMaker htmlifypods section:

POD2HTML_EXE = $(PERLRUN) "-MActivePerl::DocTools" -e "UpdateHTML_blib(installdirs => "$(INSTALLDIRS)")"
POD2HTML = $(POD2HTML_EXE)


htmlifypods :  \
	Static.pm \
	Dynamic.pm
	$(NOECHO) $(POD2HTML)



# --- MakeMaker processPL section:


# --- MakeMaker installbin section:

EXE_FILES = parl.exe parldyn.exe

pure_all :: $(INST_SCRIPT)\parl.exe $(INST_SCRIPT)\parldyn.exe
	$(NOECHO) $(NOOP)

realclean ::
	$(RM_F) \
	  $(INST_SCRIPT)\parl.exe $(INST_SCRIPT)\parldyn.exe 

$(INST_SCRIPT)\parl.exe : parl.exe $(FIRST_MAKEFILE) $(INST_SCRIPT)$(DFSEP).exists $(INST_BIN)$(DFSEP).exists
	$(NOECHO) $(RM_F) $(INST_SCRIPT)\parl.exe
	$(CP) parl.exe $(INST_SCRIPT)\parl.exe
	$(FIXIN) $(INST_SCRIPT)\parl.exe
	-$(NOECHO) $(CHMOD) $(PERM_RWX) $(INST_SCRIPT)\parl.exe

$(INST_SCRIPT)\parldyn.exe : parldyn.exe $(FIRST_MAKEFILE) $(INST_SCRIPT)$(DFSEP).exists $(INST_BIN)$(DFSEP).exists
	$(NOECHO) $(RM_F) $(INST_SCRIPT)\parldyn.exe
	$(CP) parldyn.exe $(INST_SCRIPT)\parldyn.exe
	$(FIXIN) $(INST_SCRIPT)\parldyn.exe
	-$(NOECHO) $(CHMOD) $(PERM_RWX) $(INST_SCRIPT)\parldyn.exe



# --- MakeMaker subdirs section:

# none

# --- MakeMaker clean_subdirs section:
clean_subdirs :
	$(NOECHO) $(NOOP)


# --- MakeMaker clean section:

# Delete temporary files but do not touch installed files. We don't delete
# the Makefile here so a later make realclean still has a makefile to use.

clean :: clean_subdirs
	- $(RM_F) \
	  $(BASEEXT).bso $(BASEEXT).def \
	  $(BASEEXT).exp $(BASEEXT).x \
	  $(BOOTSTRAP) $(INST_ARCHAUTODIR)\extralibs.all \
	  $(INST_ARCHAUTODIR)\extralibs.ld $(MAKE_APERL_FILE) \
	  *$(LIB_EXT) *$(OBJ_EXT) \
	  *perl.core MYMETA.json \
	  MYMETA.yml blibdirs.ts \
	  core core.*perl.*.? \
	  core.[0-9] core.[0-9][0-9] \
	  core.[0-9][0-9][0-9] core.[0-9][0-9][0-9][0-9] \
	  core.[0-9][0-9][0-9][0-9][0-9] lib$(BASEEXT).def \
	  mon.out perl \
	  perl$(EXE_EXT) perl.exe \
	  perlmain.c pm_to_blib \
	  pm_to_blib.ts so_locations \
	  tmon.out 
	- $(RM_RF) \
	  blib dll.base \
	  dll.exp 
	  $(NOECHO) $(RM_F) $(MAKEFILE_OLD)
	- $(MV) $(FIRST_MAKEFILE) $(MAKEFILE_OLD) $(DEV_NULL)


# --- MakeMaker realclean_subdirs section:
realclean_subdirs :
	$(NOECHO) $(NOOP)


# --- MakeMaker realclean section:
# Delete temporary files (via clean) and also delete dist files
realclean purge ::  clean realclean_subdirs
	- $(RM_F) \
	  $(MAKEFILE_OLD) $(OBJECT) \
	  $(FIRST_MAKEFILE) 
	- $(RM_RF) \
	  $(DISTVNAME) 


# --- MakeMaker metafile section:
metafile :
	$(NOECHO) $(NOOP)


# --- MakeMaker signature section:
signature :
	cpansign -s


# --- MakeMaker dist_basics section skipped.

# --- MakeMaker dist_core section skipped.

# --- MakeMaker distdir section skipped.

# --- MakeMaker dist_test section skipped.

# --- MakeMaker dist_ci section skipped.

# --- MakeMaker distmeta section:
distmeta : create_distdir metafile
	$(NOECHO) cd $(DISTVNAME) && $(ABSPERLRUN) -MExtUtils::Manifest=maniadd -e "exit unless -e q{{META.yml}};\
eval {{ maniadd({{q{{META.yml}} => q{{Module YAML meta-data (added by MakeMaker)}}}}) }}\
    or print \"Could not add META.yml to MANIFEST: $$$${{'^@'}}\n\"" --
	$(NOECHO) cd $(DISTVNAME) && $(ABSPERLRUN) -MExtUtils::Manifest=maniadd -e "exit unless -f q{{META.json}};\
eval {{ maniadd({{q{{META.json}} => q{{Module JSON meta-data (added by MakeMaker)}}}}) }}\
    or print \"Could not add META.json to MANIFEST: $$$${{'^@'}}\n\"" --



# --- MakeMaker distsignature section:
distsignature : create_distdir
	$(NOECHO) cd $(DISTVNAME) && $(ABSPERLRUN) -MExtUtils::Manifest=maniadd -e "eval {{ maniadd({{q{{SIGNATURE}} => q{{Public-key signature (added by MakeMaker)}}}}) }}\
    or print \"Could not add SIGNATURE to MANIFEST: $$$${{'^@'}}\n\"" --
	$(NOECHO) cd $(DISTVNAME) && $(TOUCH) SIGNATURE
	cd $(DISTVNAME) && cpansign -s



# --- MakeMaker install section skipped.

# --- MakeMaker force section:
# Phony target to force checking subdirectories.
FORCE :
	$(NOECHO) $(NOOP)


# --- MakeMaker perldepend section:
PERL_HDRS = \
        $(PERL_INC)/BuildInfo.h            \
        $(PERL_INC)/EXTERN.h            \
        $(PERL_INC)/INTERN.h            \
        $(PERL_INC)/PerlEz.h            \
        $(PERL_INC)/XSUB.h            \
        $(PERL_INC)/av.h            \
        $(PERL_INC)/bitcount.h            \
        $(PERL_INC)/charclass_invlists.h            \
        $(PERL_INC)/config.h            \
        $(PERL_INC)/cop.h            \
        $(PERL_INC)/cv.h            \
        $(PERL_INC)/dirent.h            \
        $(PERL_INC)/dosish.h            \
        $(PERL_INC)/embed.h            \
        $(PERL_INC)/embedvar.h            \
        $(PERL_INC)/fakesdio.h            \
        $(PERL_INC)/feature.h            \
        $(PERL_INC)/form.h            \
        $(PERL_INC)/git_version.h            \
        $(PERL_INC)/gv.h            \
        $(PERL_INC)/handy.h            \
        $(PERL_INC)/hv.h            \
        $(PERL_INC)/hv_func.h            \
        $(PERL_INC)/inline.h            \
        $(PERL_INC)/intrpvar.h            \
        $(PERL_INC)/iperlsys.h            \
        $(PERL_INC)/keywords.h            \
        $(PERL_INC)/l1_char_class_tab.h            \
        $(PERL_INC)/malloc_ctl.h            \
        $(PERL_INC)/metaconfig.h            \
        $(PERL_INC)/mg.h            \
        $(PERL_INC)/mg_data.h            \
        $(PERL_INC)/mg_raw.h            \
        $(PERL_INC)/mg_vtable.h            \
        $(PERL_INC)/mydtrace.h            \
        $(PERL_INC)/netdb.h            \
        $(PERL_INC)/nostdio.h            \
        $(PERL_INC)/op.h            \
        $(PERL_INC)/op_reg_common.h            \
        $(PERL_INC)/opcode.h            \
        $(PERL_INC)/opnames.h            \
        $(PERL_INC)/overload.h            \
        $(PERL_INC)/pad.h            \
        $(PERL_INC)/parser.h            \
        $(PERL_INC)/patchlevel.h            \
        $(PERL_INC)/perl.h            \
        $(PERL_INC)/perlapi.h            \
        $(PERL_INC)/perlhost.h            \
        $(PERL_INC)/perlio.h            \
        $(PERL_INC)/perliol.h            \
        $(PERL_INC)/perlsdio.h            \
        $(PERL_INC)/perlvars.h            \
        $(PERL_INC)/perly.h            \
        $(PERL_INC)/pp.h            \
        $(PERL_INC)/pp_proto.h            \
        $(PERL_INC)/proto.h            \
        $(PERL_INC)/reentr.h            \
        $(PERL_INC)/regcharclass.h            \
        $(PERL_INC)/regcomp.h            \
        $(PERL_INC)/regexp.h            \
        $(PERL_INC)/regnodes.h            \
        $(PERL_INC)/scope.h            \
        $(PERL_INC)/sv.h            \
        $(PERL_INC)/thread.h            \
        $(PERL_INC)/time64.h            \
        $(PERL_INC)/time64_config.h            \
        $(PERL_INC)/uconfig.h            \
        $(PERL_INC)/unicode_constants.h            \
        $(PERL_INC)/unixish.h            \
        $(PERL_INC)/utf8.h            \
        $(PERL_INC)/utfebcdic.h            \
        $(PERL_INC)/util.h            \
        $(PERL_INC)/uudmap.h            \
        $(PERL_INC)/vdir.h            \
        $(PERL_INC)/vmem.h            \
        $(PERL_INC)/vutil.h            \
        $(PERL_INC)/warnings.h            \
        $(PERL_INC)/win32.h            \
        $(PERL_INC)/win32iop-o.h            \
        $(PERL_INC)/win32iop.h            \
        $(PERL_INC)/win32thread.h            \
        $(PERL_INC)/wince.h            

$(OBJECT) : $(PERL_HDRS)


# --- MakeMaker makefile section:

$(OBJECT) : $(FIRST_MAKEFILE)

# We take a very conservative approach here, but it's worth it.
# We move Makefile to Makefile.old here to avoid gnu make looping.
$(FIRST_MAKEFILE) : Makefile.PL $(CONFIGDEP)
	$(NOECHO) $(ECHO) "Makefile out-of-date with respect to $?"
	$(NOECHO) $(ECHO) "Cleaning current config before rebuilding Makefile..."
	-$(NOECHO) $(RM_F) $(MAKEFILE_OLD)
	-$(NOECHO) $(MV)   $(FIRST_MAKEFILE) $(MAKEFILE_OLD)
	- $(MAKE) $(USEMAKEFILE) $(MAKEFILE_OLD) clean $(DEV_NULL)
	$(PERLRUN) Makefile.PL "INSTALLDIRS=site"
	$(NOECHO) $(ECHO) "==> Your Makefile has been rebuilt. <=="
	$(NOECHO) $(ECHO) "==> Please rerun the $(MAKE) command.  <=="
	$(FALSE)



# --- MakeMaker staticmake section:

# --- MakeMaker makeaperl section ---
MAP_TARGET    = ..\perl
FULLPERL      = C:\perl\bin\perl.exe


# --- MakeMaker test section skipped.

# --- MakeMaker ppd section:
# Creates a PPD (Perl Package Description) for a binary distribution.
ppd :
	$(NOECHO) $(ECHO) "<SOFTPKG NAME=\"$(DISTNAME)\" VERSION=\"$(VERSION)\">" > $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "    <ABSTRACT></ABSTRACT>" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "    <AUTHOR></AUTHOR>" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "    <IMPLEMENTATION>" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "        <ARCHITECTURE NAME=\"MSWin32-x86-multi-thread-64int-5.20\" />" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "        <CODEBASE HREF=\"\" />" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "    </IMPLEMENTATION>" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) ^</SOFTPKG^> >> $(DISTNAME).ppd


# --- MakeMaker pm_to_blib section:

pm_to_blib : $(FIRST_MAKEFILE) $(TO_INST_PM)
	$(NOECHO) $(ABSPERLRUN) -MExtUtils::Install -e "pm_to_blib({{@ARGV}}, '$(INST_LIB)\auto', q[$(PM_FILTER)], '$(PERM_DIR)')" -- \
	  Dynamic.pm $(INST_LIBDIR)\PAR\StrippedPARL\Dynamic.pm \
	  Static.pm $(INST_LIBDIR)\PAR\StrippedPARL\Static.pm 
	$(NOECHO) $(TOUCH) pm_to_blib


# --- MakeMaker selfdocument section:


# --- MakeMaker postamble section:
LD=c:\perl\site\bin\g++.exe
CC=c:\perl\site\bin\gcc.exe
CFLAGS=  -s -O2 -DWIN32 -DPERL_TEXTMODE_SCRIPTS -DUSE_SITECUSTOMIZE -DPERL_IMPLICIT_CONTEXT -DPERL_IMPLICIT_SYS -DUSE_PERLIO -fwrapv -fno-strict-aliasing -mms-bitfields  -I"C:\Perl\lib\CORE"  -DPARL_EXE=\"parl.exe\"
OPTIMIZE=-s -O2
LDFLAGS=-s -static-libgcc -static-libstdc++ -L"C:\Perl\lib\CORE" -L"C:\MinGW\i686-w64-mingw32\lib"
PERL_LDFLAGS=-s   -s -static-libgcc -static-libstdc++ -L"C:\Perl\lib\CORE" -L"C:\MinGW\i686-w64-mingw32\lib"  C:\Perl\lib\CORE\libperl520.a 
STATIC_LDFLAGS=-s   -s -static-libgcc -static-libstdc++ -L"C:\Perl\lib\CORE" -L"C:\MinGW\i686-w64-mingw32\lib"  C:\Perl\lib\CORE\libperl520.a 

OBJECTS=main.o ppresource.coff
MKTMP_STUFF=mktmpdir.c mktmpdir.h utils.c sha1.c

.c.o:
	$(CC) -c $(CFLAGS) $(OPTIMIZE) $<

pure_all:: parl.exe Static.pm

main.o: main.c my_par_pl.c perlxsi.c internals.c $(MKTMP_STUFF)

sha1.c:
	$(PERLRUN) sha1.c.PL

ppresource.coff:
	windres -i winres/pp.rc -o ppresource.coff --input-format=rc --output-format=coff --target=pe-i386


clean::
	-$(RM_F) boot_embedded_files.c my_par_pl.c
	-$(RM_F) main.o boot.o ppresource.coff
	-$(RM_F) sha1.c
	-$(RM_F) *.opt *.pdb perlxsi.c
	-$(RM_F) usernamefrompwuid.h
	-$(RM_F) par.exe boot.exe parl.exe parldyn.exe Dynamic.pm Static.pm

par.exe: $(OBJECTS)
	$(LD) $(OBJECTS) $(PERL_LDFLAGS) -o par.exe
	-$(NOOP)

my_par_pl.c: ..\script\par.pl
	$(PERLRUN) par_pl2c.pl my_par_pl < ..\script\par.pl > $@ 

parl.exe: boot.exe
	$(PERLRUN) -Mblib=.. run_with_inc.pl boot.exe -q -B -O$@

Static.pm: Static.in boot.exe
	$(PERLRUN) encode_append.pl Static.in boot.exe Static.pm


.DEFAULT:
	-$(NOOP)

.SUFFIXES: .o

# dummy targets to satisfy ExtUtils::MakeMaker
dynamic::
static::
test::

pure_all:: parldyn.exe Dynamic.pm

parldyn.exe: par.exe
	$(PERLRUN) -Mblib=.. run_with_inc.pl par.exe -q -B -O$@

boot.o: $(MKTMP_STUFF) boot_embedded_files.c

boot.exe: boot.o
	$(LD) boot.o -static-libgcc -s   -s -static-libgcc -static-libstdc++ -L"C:\Perl\lib\CORE" -L"C:\MinGW\i686-w64-mingw32\lib"  C:\Perl\lib\CORE\libperl520.a  ppresource.coff -o boot.exe
	-$(NOOP)

boot_embedded_files.c: par.exe
	$(PERLRUN) file2c.pl -c 30000 "par.exe" "C:\Perl\bin\perl520.dll" "C:\Program Files (x86)\GNU\GnuPG\pub\libgcc_s_sjlj-1.dll" "C:\Program Files (x86)\GNU\GnuPG\pub\libstdc++-6.dll" > $@

Dynamic.pm: Dynamic.in par.exe
	$(PERLRUN) encode_append.pl Dynamic.in par.exe Dynamic.pm


# End.
