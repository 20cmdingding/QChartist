# This Makefile is for the Win32::Exe extension to perl.
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

#     ABSTRACT => q[Manipulate Win32 executable files]
#     AUTHOR => [q[Audrey Tang <cpan@audreyt.org>]]
#     BUILD_REQUIRES => { Test::More=>q[0], File::Copy=>q[0] }
#     CONFIGURE_REQUIRES => {  }
#     EXE_FILES => [q[script/exe_update.pl]]
#     LICENSE => q[perl]
#     MIN_PERL_VERSION => q[5.006000]
#     NAME => q[Win32::Exe]
#     NORECURS => q[0]
#     PREREQ_PM => { Parse::Binary=>q[0.11], File::Copy=>q[0], Test::More=>q[0], XML::Simple=>q[2.18], XML::Parser=>q[2.36] }
#     TEST_REQUIRES => {  }
#     VERSION_FROM => q[lib/Win32/Exe.pm]

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
NAME = Win32::Exe
NAME_SYM = Win32_Exe
VERSION = 0.17
VERSION_MACRO = VERSION
VERSION_SYM = 0_17
DEFINE_VERSION = -D$(VERSION_MACRO)=\"$(VERSION)\"
XS_VERSION = 0.17
XS_VERSION_MACRO = XS_VERSION
XS_DEFINE_VERSION = -D$(XS_VERSION_MACRO)=\"$(XS_VERSION)\"
INST_ARCHLIB = blib\arch
INST_SCRIPT = blib\script
INST_BIN = blib\bin
INST_LIB = blib\lib
INST_MAN1DIR = blib\man1
INST_MAN3DIR = blib\man3
INST_HTMLDIR = blib\html
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
FULLEXT = Win32\Exe
BASEEXT = Exe
PARENT_NAME = Win32
DLBASE = $(BASEEXT)
VERSION_FROM = lib/Win32/Exe.pm
OBJECT = 
LDFROM = $(OBJECT)
LINKTYPE = dynamic
BOOTDEP = 

# Handy lists of source code files:
XS_FILES = 
C_FILES  = 
O_FILES  = 
H_FILES  = 
MAN1PODS = script/exe_update.pl
MAN3PODS = lib/Win32/Exe.pm \
	lib/Win32/Exe/Manifest.pm \
	lib/Win32/Exe/Manifest/Parser.pm

# Where is the Config information that we are using/depend on
CONFIGDEP = $(PERL_ARCHLIB)$(DFSEP)Config.pm $(PERL_INC)$(DFSEP)config.h

# Where to build things
INST_LIBDIR      = $(INST_LIB)\Win32
INST_ARCHLIBDIR  = $(INST_ARCHLIB)\Win32

INST_AUTODIR     = $(INST_LIB)\auto\$(FULLEXT)
INST_ARCHAUTODIR = $(INST_ARCHLIB)\auto\$(FULLEXT)

INST_STATIC      = 
INST_DYNAMIC     = 
INST_BOOT        = 

# Extra linker info
EXPORT_LIST        = $(BASEEXT).def
PERL_ARCHIVE       = $(PERL_INC)\libperl520.a
PERL_ARCHIVE_AFTER = 


TO_INST_PM = lib/Win32/Exe.pm \
	lib/Win32/Exe/Base.pm \
	lib/Win32/Exe/DataDirectory.pm \
	lib/Win32/Exe/DebugDirectory.pm \
	lib/Win32/Exe/DebugTable.pm \
	lib/Win32/Exe/IconFile.pm \
	lib/Win32/Exe/InsertResourceSection.pm \
	lib/Win32/Exe/Manifest.pm \
	lib/Win32/Exe/Manifest/Parser.pm \
	lib/Win32/Exe/PE.pm \
	lib/Win32/Exe/PE/Header.pm \
	lib/Win32/Exe/PE/Header/PE32.pm \
	lib/Win32/Exe/PE/Header/PE32Plus.pm \
	lib/Win32/Exe/Resource.pm \
	lib/Win32/Exe/Resource/GroupIcon.pm \
	lib/Win32/Exe/Resource/Icon.pm \
	lib/Win32/Exe/Resource/Manifest.pm \
	lib/Win32/Exe/Resource/Version.pm \
	lib/Win32/Exe/ResourceData.pm \
	lib/Win32/Exe/ResourceEntry.pm \
	lib/Win32/Exe/ResourceEntry/Id.pm \
	lib/Win32/Exe/ResourceEntry/Name.pm \
	lib/Win32/Exe/ResourceTable.pm \
	lib/Win32/Exe/Section.pm \
	lib/Win32/Exe/Section/Code.pm \
	lib/Win32/Exe/Section/Data.pm \
	lib/Win32/Exe/Section/Debug.pm \
	lib/Win32/Exe/Section/Exports.pm \
	lib/Win32/Exe/Section/Imports.pm \
	lib/Win32/Exe/Section/Resources.pm

PM_TO_BLIB = lib/Win32/Exe.pm \
	blib\lib\Win32\Exe.pm \
	lib/Win32/Exe/Base.pm \
	blib\lib\Win32\Exe\Base.pm \
	lib/Win32/Exe/DataDirectory.pm \
	blib\lib\Win32\Exe\DataDirectory.pm \
	lib/Win32/Exe/DebugDirectory.pm \
	blib\lib\Win32\Exe\DebugDirectory.pm \
	lib/Win32/Exe/DebugTable.pm \
	blib\lib\Win32\Exe\DebugTable.pm \
	lib/Win32/Exe/IconFile.pm \
	blib\lib\Win32\Exe\IconFile.pm \
	lib/Win32/Exe/InsertResourceSection.pm \
	blib\lib\Win32\Exe\InsertResourceSection.pm \
	lib/Win32/Exe/Manifest.pm \
	blib\lib\Win32\Exe\Manifest.pm \
	lib/Win32/Exe/Manifest/Parser.pm \
	blib\lib\Win32\Exe\Manifest\Parser.pm \
	lib/Win32/Exe/PE.pm \
	blib\lib\Win32\Exe\PE.pm \
	lib/Win32/Exe/PE/Header.pm \
	blib\lib\Win32\Exe\PE\Header.pm \
	lib/Win32/Exe/PE/Header/PE32.pm \
	blib\lib\Win32\Exe\PE\Header\PE32.pm \
	lib/Win32/Exe/PE/Header/PE32Plus.pm \
	blib\lib\Win32\Exe\PE\Header\PE32Plus.pm \
	lib/Win32/Exe/Resource.pm \
	blib\lib\Win32\Exe\Resource.pm \
	lib/Win32/Exe/Resource/GroupIcon.pm \
	blib\lib\Win32\Exe\Resource\GroupIcon.pm \
	lib/Win32/Exe/Resource/Icon.pm \
	blib\lib\Win32\Exe\Resource\Icon.pm \
	lib/Win32/Exe/Resource/Manifest.pm \
	blib\lib\Win32\Exe\Resource\Manifest.pm \
	lib/Win32/Exe/Resource/Version.pm \
	blib\lib\Win32\Exe\Resource\Version.pm \
	lib/Win32/Exe/ResourceData.pm \
	blib\lib\Win32\Exe\ResourceData.pm \
	lib/Win32/Exe/ResourceEntry.pm \
	blib\lib\Win32\Exe\ResourceEntry.pm \
	lib/Win32/Exe/ResourceEntry/Id.pm \
	blib\lib\Win32\Exe\ResourceEntry\Id.pm \
	lib/Win32/Exe/ResourceEntry/Name.pm \
	blib\lib\Win32\Exe\ResourceEntry\Name.pm \
	lib/Win32/Exe/ResourceTable.pm \
	blib\lib\Win32\Exe\ResourceTable.pm \
	lib/Win32/Exe/Section.pm \
	blib\lib\Win32\Exe\Section.pm \
	lib/Win32/Exe/Section/Code.pm \
	blib\lib\Win32\Exe\Section\Code.pm \
	lib/Win32/Exe/Section/Data.pm \
	blib\lib\Win32\Exe\Section\Data.pm \
	lib/Win32/Exe/Section/Debug.pm \
	blib\lib\Win32\Exe\Section\Debug.pm \
	lib/Win32/Exe/Section/Exports.pm \
	blib\lib\Win32\Exe\Section\Exports.pm \
	lib/Win32/Exe/Section/Imports.pm \
	blib\lib\Win32\Exe\Section\Imports.pm \
	lib/Win32/Exe/Section/Resources.pm \
	blib\lib\Win32\Exe\Section\Resources.pm


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


# --- MakeMaker dist section:
TAR = tar
TARFLAGS = cvf
ZIP = zip
ZIPFLAGS = -r
COMPRESS = gzip --best
SUFFIX = .gz
SHAR = shar
PREOP = $(NOECHO) $(NOOP)
POSTOP = $(NOECHO) $(NOOP)
TO_UNIX = $(NOECHO) $(NOOP)
CI = ci -u
RCS_LABEL = rcs -Nv$(VERSION_SYM): -q
DIST_CP = best
DIST_DEFAULT = tardist
DISTNAME = Win32-Exe
DISTVNAME = Win32-Exe-0.17


# --- MakeMaker macro section:


# --- MakeMaker depend section:


# --- MakeMaker cflags section:

CCFLAGS = -s -O2 -DWIN32 -DPERL_TEXTMODE_SCRIPTS -DUSE_SITECUSTOMIZE -DPERL_IMPLICIT_CONTEXT -DPERL_IMPLICIT_SYS -DUSE_PERLIO -fwrapv -fno-strict-aliasing -mms-bitfields
OPTIMIZE = -s -O2
PERLTYPE = 


# --- MakeMaker const_loadlibs section:

# Win32::Exe might depend on some other libraries:
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

Exe.def: Makefile.PL
	$(PERLRUN) -MExtUtils::Mksymlists \
     -e "Mksymlists('NAME'=>\"Win32::Exe\", 'DLBASE' => '$(BASEEXT)', 'DL_FUNCS' => {  }, 'FUNCLIST' => [], 'IMPORTS' => {  }, 'DL_VARS' => []);"


# --- MakeMaker dynamic_bs section:

BOOTSTRAP =


# --- MakeMaker dynamic section:

dynamic :: $(FIRST_MAKEFILE) $(BOOTSTRAP) $(INST_DYNAMIC)
	$(NOECHO) $(NOOP)


# --- MakeMaker dynamic_lib section:


# --- MakeMaker static section:

## $(INST_PM) has been moved to the all: target.
## It remains here for awhile to allow for old usage: "make static"
static :: $(FIRST_MAKEFILE) $(INST_STATIC)
	$(NOECHO) $(NOOP)


# --- MakeMaker static_lib section:


# --- MakeMaker manifypods section:

POD2MAN_EXE = $(PERLRUN) "-MExtUtils::Command::MM" -e pod2man "--"
POD2MAN = $(POD2MAN_EXE)


manifypods : pure_all  \
	lib/Win32/Exe.pm \
	lib/Win32/Exe/Manifest.pm \
	lib/Win32/Exe/Manifest/Parser.pm \
	script/exe_update.pl
	$(NOECHO) $(POD2MAN) --section=1 --perm_rw=$(PERM_RW) \
	  script/exe_update.pl $(INST_MAN1DIR)\exe_update.pl.$(MAN1EXT) 
	$(NOECHO) $(POD2MAN) --section=3 --perm_rw=$(PERM_RW) \
	  lib/Win32/Exe.pm $(INST_MAN3DIR)\Win32.Exe.$(MAN3EXT) \
	  lib/Win32/Exe/Manifest.pm $(INST_MAN3DIR)\Win32.Exe.Manifest.$(MAN3EXT) \
	  lib/Win32/Exe/Manifest/Parser.pm $(INST_MAN3DIR)\Win32.Exe.Manifest.Parser.$(MAN3EXT) 




# --- MakeMaker htmlifypods section:

POD2HTML_EXE = $(PERLRUN) "-MActivePerl::DocTools" -e "UpdateHTML_blib(installdirs => "$(INSTALLDIRS)")"
POD2HTML = $(POD2HTML_EXE)


htmlifypods :  \
	script/exe_update.pl \
	lib/Win32/Exe/Manifest/Parser.pm \
	lib/Win32/Exe.pm \
	lib/Win32/Exe/Manifest.pm
	$(NOECHO) $(POD2HTML)



# --- MakeMaker processPL section:


# --- MakeMaker installbin section:

EXE_FILES = script/exe_update.pl

pure_all :: $(INST_SCRIPT)\exe_update.pl
	$(NOECHO) $(NOOP)

realclean ::
	$(RM_F) \
	  $(INST_SCRIPT)\exe_update.pl 

$(INST_SCRIPT)\exe_update.pl : script/exe_update.pl $(FIRST_MAKEFILE) $(INST_SCRIPT)$(DFSEP).exists $(INST_BIN)$(DFSEP).exists
	$(NOECHO) $(RM_F) $(INST_SCRIPT)\exe_update.pl
	$(CP) script/exe_update.pl $(INST_SCRIPT)\exe_update.pl
	$(FIXIN) $(INST_SCRIPT)\exe_update.pl
	-$(NOECHO) $(CHMOD) $(PERM_RWX) $(INST_SCRIPT)\exe_update.pl



# --- MakeMaker subdirs section:

# The default clean, realclean and test targets in this Makefile
# have automatically been given entries for each subdir.


subdirs ::
	$(NOECHO) cd insert && $(MAKE) $(USEMAKEFILE) $(FIRST_MAKEFILE) all $(PASTHRU)


# --- MakeMaker clean_subdirs section:
clean_subdirs :
	$(ABSPERLRUN)  -e "exit 0 unless chdir 'insert';  system '$(MAKE) clean' if -f '$(FIRST_MAKEFILE)';" --


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
	- $(ABSPERLRUN)  -e "chdir 'insert';  system '$(MAKE) $(USEMAKEFILE) $(MAKEFILE_OLD) realclean' if -f '$(MAKEFILE_OLD)';" --
	- $(ABSPERLRUN)  -e "chdir 'insert';  system '$(MAKE) $(USEMAKEFILE) $(FIRST_MAKEFILE) realclean' if -f '$(FIRST_MAKEFILE)';" --


# --- MakeMaker realclean section:
# Delete temporary files (via clean) and also delete dist files
realclean purge ::  clean realclean_subdirs
	- $(RM_F) \
	  $(MAKEFILE_OLD) $(FIRST_MAKEFILE) 
	- $(RM_RF) \
	  $(DISTVNAME) 


# --- MakeMaker metafile section:
metafile : create_distdir
	$(NOECHO) $(ECHO) Generating META.yml
	$(NOECHO) $(ECHO) --- > META_new.yml
	$(NOECHO) $(ECHO) "abstract: 'Manipulate Win32 executable files'" >> META_new.yml
	$(NOECHO) $(ECHO) author: >> META_new.yml
	$(NOECHO) $(ECHO) "  - 'Audrey Tang <cpan@audreyt.org>'" >> META_new.yml
	$(NOECHO) $(ECHO) build_requires: >> META_new.yml
	$(NOECHO) $(ECHO) "  File::Copy: '0'" >> META_new.yml
	$(NOECHO) $(ECHO) "  Test::More: '0'" >> META_new.yml
	$(NOECHO) $(ECHO) configure_requires: >> META_new.yml
	$(NOECHO) $(ECHO) "  ExtUtils::MakeMaker: '0'" >> META_new.yml
	$(NOECHO) $(ECHO) "dynamic_config: 1" >> META_new.yml
	$(NOECHO) $(ECHO) "generated_by: 'ExtUtils::MakeMaker version 6.98, CPAN::Meta::Converter version 2.150001'" >> META_new.yml
	$(NOECHO) $(ECHO) "license: perl" >> META_new.yml
	$(NOECHO) $(ECHO) meta-spec: >> META_new.yml
	$(NOECHO) $(ECHO) "  url: http://module-build.sourceforge.net/META-spec-v1.4.html" >> META_new.yml
	$(NOECHO) $(ECHO) "  version: '1.4'" >> META_new.yml
	$(NOECHO) $(ECHO) "name: Win32-Exe" >> META_new.yml
	$(NOECHO) $(ECHO) no_index: >> META_new.yml
	$(NOECHO) $(ECHO) "  directory:" >> META_new.yml
	$(NOECHO) $(ECHO) "    - t" >> META_new.yml
	$(NOECHO) $(ECHO) "    - inc" >> META_new.yml
	$(NOECHO) $(ECHO) requires: >> META_new.yml
	$(NOECHO) $(ECHO) "  Parse::Binary: '0.11'" >> META_new.yml
	$(NOECHO) $(ECHO) "  XML::Parser: '2.36'" >> META_new.yml
	$(NOECHO) $(ECHO) "  XML::Simple: '2.18'" >> META_new.yml
	$(NOECHO) $(ECHO) "  perl: '5.006000'" >> META_new.yml
	$(NOECHO) $(ECHO) "version: '0.17'" >> META_new.yml
	-$(NOECHO) $(MV) META_new.yml $(DISTVNAME)/META.yml
	$(NOECHO) $(ECHO) Generating META.json
	$(NOECHO) $(ECHO) {{ > META_new.json
	$(NOECHO) $(ECHO) "   \"abstract\" : \"Manipulate Win32 executable files\"," >> META_new.json
	$(NOECHO) $(ECHO) "   \"author\" : [" >> META_new.json
	$(NOECHO) $(ECHO) "      \"Audrey Tang ^<cpan^@audreyt.org^>\"" >> META_new.json
	$(NOECHO) $(ECHO) "   ]," >> META_new.json
	$(NOECHO) $(ECHO) "   \"dynamic_config\" : 1," >> META_new.json
	$(NOECHO) $(ECHO) "   \"generated_by\" : \"ExtUtils::MakeMaker version 6.98, CPAN::Meta::Converter version 2.150001\"," >> META_new.json
	$(NOECHO) $(ECHO) "   \"license\" : [" >> META_new.json
	$(NOECHO) $(ECHO) "      \"perl_5\"" >> META_new.json
	$(NOECHO) $(ECHO) "   ]," >> META_new.json
	$(NOECHO) $(ECHO) "   \"meta-spec\" : {{" >> META_new.json
	$(NOECHO) $(ECHO) "      \"url\" : \"http://search.cpan.org/perldoc?CPAN::Meta::Spec\"," >> META_new.json
	$(NOECHO) $(ECHO) "      \"version\" : \"2\"" >> META_new.json
	$(NOECHO) $(ECHO) "   }}," >> META_new.json
	$(NOECHO) $(ECHO) "   \"name\" : \"Win32-Exe\"," >> META_new.json
	$(NOECHO) $(ECHO) "   \"no_index\" : {{" >> META_new.json
	$(NOECHO) $(ECHO) "      \"directory\" : [" >> META_new.json
	$(NOECHO) $(ECHO) "         \"t\"," >> META_new.json
	$(NOECHO) $(ECHO) "         \"inc\"" >> META_new.json
	$(NOECHO) $(ECHO) "      ]" >> META_new.json
	$(NOECHO) $(ECHO) "   }}," >> META_new.json
	$(NOECHO) $(ECHO) "   \"prereqs\" : {{" >> META_new.json
	$(NOECHO) $(ECHO) "      \"build\" : {{" >> META_new.json
	$(NOECHO) $(ECHO) "         \"requires\" : {{" >> META_new.json
	$(NOECHO) $(ECHO) "            \"File::Copy\" : \"0\"," >> META_new.json
	$(NOECHO) $(ECHO) "            \"Test::More\" : \"0\"" >> META_new.json
	$(NOECHO) $(ECHO) "         }}" >> META_new.json
	$(NOECHO) $(ECHO) "      }}," >> META_new.json
	$(NOECHO) $(ECHO) "      \"configure\" : {{" >> META_new.json
	$(NOECHO) $(ECHO) "         \"requires\" : {{" >> META_new.json
	$(NOECHO) $(ECHO) "            \"ExtUtils::MakeMaker\" : \"0\"" >> META_new.json
	$(NOECHO) $(ECHO) "         }}" >> META_new.json
	$(NOECHO) $(ECHO) "      }}," >> META_new.json
	$(NOECHO) $(ECHO) "      \"runtime\" : {{" >> META_new.json
	$(NOECHO) $(ECHO) "         \"requires\" : {{" >> META_new.json
	$(NOECHO) $(ECHO) "            \"Parse::Binary\" : \"0.11\"," >> META_new.json
	$(NOECHO) $(ECHO) "            \"XML::Parser\" : \"2.36\"," >> META_new.json
	$(NOECHO) $(ECHO) "            \"XML::Simple\" : \"2.18\"," >> META_new.json
	$(NOECHO) $(ECHO) "            \"perl\" : \"5.006000\"" >> META_new.json
	$(NOECHO) $(ECHO) "         }}" >> META_new.json
	$(NOECHO) $(ECHO) "      }}" >> META_new.json
	$(NOECHO) $(ECHO) "   }}," >> META_new.json
	$(NOECHO) $(ECHO) "   \"release_status\" : \"stable\"," >> META_new.json
	$(NOECHO) $(ECHO) "   \"version\" : \"0.17\"" >> META_new.json
	$(NOECHO) $(ECHO) }} >> META_new.json
	-$(NOECHO) $(MV) META_new.json $(DISTVNAME)/META.json


# --- MakeMaker signature section:
signature :
	cpansign -s


# --- MakeMaker dist_basics section:
distclean :: realclean distcheck
	$(NOECHO) $(NOOP)

distcheck :
	$(PERLRUN) "-MExtUtils::Manifest=fullcheck" -e fullcheck

skipcheck :
	$(PERLRUN) "-MExtUtils::Manifest=skipcheck" -e skipcheck

manifest :
	$(PERLRUN) "-MExtUtils::Manifest=mkmanifest" -e mkmanifest

veryclean : realclean
	$(RM_F) *~ */*~ *.orig */*.orig *.bak */*.bak *.old */*.old



# --- MakeMaker dist_core section:

dist : $(DIST_DEFAULT) $(FIRST_MAKEFILE)
	$(NOECHO) $(ABSPERLRUN) -l -e "print 'Warning: Makefile possibly out of date with $(VERSION_FROM)'\
    if -e '$(VERSION_FROM)' and -M '$(VERSION_FROM)' < -M '$(FIRST_MAKEFILE)';" --

tardist : $(DISTVNAME).tar$(SUFFIX)
	$(NOECHO) $(NOOP)

uutardist : $(DISTVNAME).tar$(SUFFIX)
	uuencode $(DISTVNAME).tar$(SUFFIX) $(DISTVNAME).tar$(SUFFIX) > $(DISTVNAME).tar$(SUFFIX)_uu
	$(NOECHO) $(ECHO) 'Created $(DISTVNAME).tar$(SUFFIX)_uu'

$(DISTVNAME).tar$(SUFFIX) : distdir
	$(PREOP)
	$(TO_UNIX)
	$(TAR) $(TARFLAGS) $(DISTVNAME).tar $(DISTVNAME)
	$(RM_RF) $(DISTVNAME)
	$(COMPRESS) $(DISTVNAME).tar
	$(NOECHO) $(ECHO) 'Created $(DISTVNAME).tar$(SUFFIX)'
	$(POSTOP)

zipdist : $(DISTVNAME).zip
	$(NOECHO) $(NOOP)

$(DISTVNAME).zip : distdir
	$(PREOP)
	$(ZIP) $(ZIPFLAGS) $(DISTVNAME).zip $(DISTVNAME)
	$(RM_RF) $(DISTVNAME)
	$(NOECHO) $(ECHO) 'Created $(DISTVNAME).zip'
	$(POSTOP)

shdist : distdir
	$(PREOP)
	$(SHAR) $(DISTVNAME) > $(DISTVNAME).shar
	$(RM_RF) $(DISTVNAME)
	$(NOECHO) $(ECHO) 'Created $(DISTVNAME).shar'
	$(POSTOP)


# --- MakeMaker distdir section:
create_distdir :
	$(RM_RF) $(DISTVNAME)
	$(PERLRUN) "-MExtUtils::Manifest=manicopy,maniread" \
		-e "manicopy(maniread(),'$(DISTVNAME)', '$(DIST_CP)');"

distdir : create_distdir distmeta 
	$(NOECHO) $(NOOP)



# --- MakeMaker dist_test section:
disttest : distdir
	cd $(DISTVNAME) && $(ABSPERLRUN) Makefile.PL "INSTALLDIRS=site"
	cd $(DISTVNAME) && $(MAKE) $(PASTHRU)
	cd $(DISTVNAME) && $(MAKE) test $(PASTHRU)



# --- MakeMaker dist_ci section:

ci :
	$(PERLRUN) "-MExtUtils::Manifest=maniread" \
	  -e "@all = keys %{ maniread() };" \
	  -e "print(qq{Executing $(CI) @all\n}); system(qq{$(CI) @all});" \
	  -e "print(qq{Executing $(RCS_LABEL) ...\n}); system(qq{$(RCS_LABEL) @all});"


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



# --- MakeMaker install section:

install :: pure_install doc_install doc_update
	$(NOECHO) $(NOOP)

install_perl :: pure_perl_install doc_perl_install
	$(NOECHO) $(NOOP)

install_site :: pure_site_install doc_site_install
	$(NOECHO) $(NOOP)

install_vendor :: pure_vendor_install doc_vendor_install
	$(NOECHO) $(NOOP)

pure_install :: pure_$(INSTALLDIRS)_install
	$(NOECHO) $(NOOP)

doc_install :: doc_$(INSTALLDIRS)_install
	$(NOECHO) $(NOOP)

doc_update ::
	$(NOECHO) $(PERLRUN) "-MActivePerl::DocTools" -e ActivePerl::DocTools::WriteTOC

pure__install : pure_site_install
	$(NOECHO) $(ECHO) INSTALLDIRS not defined, defaulting to INSTALLDIRS=site

doc__install : doc_site_install
	$(NOECHO) $(ECHO) INSTALLDIRS not defined, defaulting to INSTALLDIRS=site

pure_perl_install :: all
	$(NOECHO) $(MOD_INSTALL) \
		read $(PERL_ARCHLIB)\auto\$(FULLEXT)\.packlist \
		write $(DESTINSTALLARCHLIB)\auto\$(FULLEXT)\.packlist \
		$(INST_LIB) $(DESTINSTALLPRIVLIB) \
		$(INST_ARCHLIB) $(DESTINSTALLARCHLIB) \
		$(INST_BIN) $(DESTINSTALLBIN) \
		$(INST_SCRIPT) $(DESTINSTALLSCRIPT) \
		$(INST_MAN1DIR) $(DESTINSTALLMAN1DIR) \
		$(INST_MAN3DIR) $(DESTINSTALLMAN3DIR) \
		$(INST_HTMLDIR) $(DESTINSTALLHTMLDIR)
	$(NOECHO) $(WARN_IF_OLD_PACKLIST) \
		$(SITEARCHEXP)\auto\$(FULLEXT)


pure_site_install :: all
	$(NOECHO) $(MOD_INSTALL) \
		read $(SITEARCHEXP)\auto\$(FULLEXT)\.packlist \
		write $(DESTINSTALLSITEARCH)\auto\$(FULLEXT)\.packlist \
		$(INST_LIB) $(DESTINSTALLSITELIB) \
		$(INST_ARCHLIB) $(DESTINSTALLSITEARCH) \
		$(INST_BIN) $(DESTINSTALLSITEBIN) \
		$(INST_SCRIPT) $(DESTINSTALLSITESCRIPT) \
		$(INST_MAN1DIR) $(DESTINSTALLSITEMAN1DIR) \
		$(INST_MAN3DIR) $(DESTINSTALLSITEMAN3DIR) \
		$(INST_HTMLDIR) $(DESTINSTALLSITEHTMLDIR)
	$(NOECHO) $(WARN_IF_OLD_PACKLIST) \
		$(PERL_ARCHLIB)\auto\$(FULLEXT)

pure_vendor_install :: all
	$(NOECHO) $(MOD_INSTALL) \
		read $(VENDORARCHEXP)\auto\$(FULLEXT)\.packlist \
		write $(DESTINSTALLVENDORARCH)\auto\$(FULLEXT)\.packlist \
		$(INST_LIB) $(DESTINSTALLVENDORLIB) \
		$(INST_ARCHLIB) $(DESTINSTALLVENDORARCH) \
		$(INST_BIN) $(DESTINSTALLVENDORBIN) \
		$(INST_SCRIPT) $(DESTINSTALLVENDORSCRIPT) \
		$(INST_MAN1DIR) $(DESTINSTALLVENDORMAN1DIR) \
		$(INST_MAN3DIR) $(DESTINSTALLVENDORMAN3DIR) \
		$(INST_HTMLDIR) $(DESTINSTALLVENDORHTMLDIR)


doc_perl_install :: all
	$(NOECHO) $(ECHO) Appending installation info to $(DESTINSTALLARCHLIB)/perllocal.pod
	-$(NOECHO) $(MKPATH) $(DESTINSTALLARCHLIB)
	-$(NOECHO) $(DOC_INSTALL) \
		"Module" "$(NAME)" \
		"installed into" "$(INSTALLPRIVLIB)" \
		LINKTYPE "$(LINKTYPE)" \
		VERSION "$(VERSION)" \
		EXE_FILES "$(EXE_FILES)" \
		>> $(DESTINSTALLARCHLIB)\perllocal.pod

doc_site_install :: all
	$(NOECHO) $(ECHO) Appending installation info to $(DESTINSTALLARCHLIB)/perllocal.pod
	-$(NOECHO) $(MKPATH) $(DESTINSTALLARCHLIB)
	-$(NOECHO) $(DOC_INSTALL) \
		"Module" "$(NAME)" \
		"installed into" "$(INSTALLSITELIB)" \
		LINKTYPE "$(LINKTYPE)" \
		VERSION "$(VERSION)" \
		EXE_FILES "$(EXE_FILES)" \
		>> $(DESTINSTALLARCHLIB)\perllocal.pod

doc_vendor_install :: all
	$(NOECHO) $(ECHO) Appending installation info to $(DESTINSTALLARCHLIB)/perllocal.pod
	-$(NOECHO) $(MKPATH) $(DESTINSTALLARCHLIB)
	-$(NOECHO) $(DOC_INSTALL) \
		"Module" "$(NAME)" \
		"installed into" "$(INSTALLVENDORLIB)" \
		LINKTYPE "$(LINKTYPE)" \
		VERSION "$(VERSION)" \
		EXE_FILES "$(EXE_FILES)" \
		>> $(DESTINSTALLARCHLIB)\perllocal.pod


uninstall :: uninstall_from_$(INSTALLDIRS)dirs doc_update
	$(NOECHO) $(NOOP)

uninstall_from_perldirs ::
	$(NOECHO) $(UNINSTALL) $(PERL_ARCHLIB)\auto\$(FULLEXT)\.packlist

uninstall_from_sitedirs ::
	$(NOECHO) $(UNINSTALL) $(SITEARCHEXP)\auto\$(FULLEXT)\.packlist

uninstall_from_vendordirs ::
	$(NOECHO) $(UNINSTALL) $(VENDORARCHEXP)\auto\$(FULLEXT)\.packlist


# --- MakeMaker force section:
# Phony target to force checking subdirectories.
FORCE :
	$(NOECHO) $(NOOP)


# --- MakeMaker perldepend section:


# --- MakeMaker makefile section:
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
MAP_TARGET    = perl
FULLPERL      = C:\perl\bin\perl.exe

$(MAP_TARGET) :: static $(MAKE_APERL_FILE)
	$(MAKE) $(USEMAKEFILE) $(MAKE_APERL_FILE) $@

$(MAKE_APERL_FILE) : $(FIRST_MAKEFILE) pm_to_blib
	$(NOECHO) $(ECHO) Writing \"$(MAKE_APERL_FILE)\" for this $(MAP_TARGET)
	$(NOECHO) $(PERLRUNINST) \
		Makefile.PL DIR=insert \
		MAKEFILE=$(MAKE_APERL_FILE) LINKTYPE=static \
		MAKEAPERL=1 NORECURS=1 CCCDLFLAGS= \
		INSTALLDIRS=site


# --- MakeMaker test section:

TEST_VERBOSE=0
TEST_TYPE=test_$(LINKTYPE)
TEST_FILE = test.pl
TEST_FILES = t/*.t
TESTDB_SW = -d

testdb :: testdb_$(LINKTYPE)

test :: $(TEST_TYPE) subdirs-test

subdirs-test ::
	$(NOECHO) $(NOOP)

subdirs-test ::
	$(NOECHO) cd insert && $(MAKE) test $(PASTHRU)


test_dynamic :: pure_all
	$(FULLPERLRUN) "-MExtUtils::Command::MM" "-MTest::Harness" "-e" "undef *Test::Harness::Switches; test_harness($(TEST_VERBOSE), '$(INST_LIB)', '$(INST_ARCHLIB)')" $(TEST_FILES)

testdb_dynamic :: pure_all
	$(FULLPERLRUN) $(TESTDB_SW) "-I$(INST_LIB)" "-I$(INST_ARCHLIB)" $(TEST_FILE)

test_ : test_dynamic

test_static :: pure_all $(MAP_TARGET)
	./$(MAP_TARGET) "-MExtUtils::Command::MM" "-MTest::Harness" "-e" "undef *Test::Harness::Switches; test_harness($(TEST_VERBOSE), '$(INST_LIB)', '$(INST_ARCHLIB)')" $(TEST_FILES)

testdb_static :: pure_all $(MAP_TARGET)
	./$(MAP_TARGET) $(TESTDB_SW) "-I$(INST_LIB)" "-I$(INST_ARCHLIB)" $(TEST_FILE)



# --- MakeMaker ppd section:
# Creates a PPD (Perl Package Description) for a binary distribution.
ppd :
	$(NOECHO) $(ECHO) "<SOFTPKG NAME=\"$(DISTNAME)\" VERSION=\"$(VERSION)\">" > $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "    <ABSTRACT>Manipulate Win32 executable files</ABSTRACT>" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "    <AUTHOR>Audrey Tang &lt;cpan@audreyt.org&gt;</AUTHOR>" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "    <IMPLEMENTATION>" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "        <PERLCORE VERSION=\"5,006000,0,0\" />" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "        <REQUIRE VERSION=\"0.11\" NAME=\"Parse::Binary\" />" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "        <REQUIRE NAME=\"XML::Parser\" VERSION=\"2.36\" />" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "        <REQUIRE VERSION=\"2.18\" NAME=\"XML::Simple\" />" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "        <ARCHITECTURE NAME=\"MSWin32-x86-multi-thread-64int-5.20\" />" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "        <CODEBASE HREF=\"\" />" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) "    </IMPLEMENTATION>" >> $(DISTNAME).ppd
	$(NOECHO) $(ECHO) ^</SOFTPKG^> >> $(DISTNAME).ppd


# --- MakeMaker pm_to_blib section:

pm_to_blib : $(FIRST_MAKEFILE) $(TO_INST_PM)
	$(NOECHO) $(ABSPERLRUN) -MExtUtils::Install -e "pm_to_blib({{@ARGV}}, '$(INST_LIB)\auto', q[$(PM_FILTER)], '$(PERM_DIR)')" -- \
	  lib/Win32/Exe.pm blib\lib\Win32\Exe.pm \
	  lib/Win32/Exe/Base.pm blib\lib\Win32\Exe\Base.pm \
	  lib/Win32/Exe/DataDirectory.pm blib\lib\Win32\Exe\DataDirectory.pm \
	  lib/Win32/Exe/DebugDirectory.pm blib\lib\Win32\Exe\DebugDirectory.pm \
	  lib/Win32/Exe/DebugTable.pm blib\lib\Win32\Exe\DebugTable.pm \
	  lib/Win32/Exe/IconFile.pm blib\lib\Win32\Exe\IconFile.pm \
	  lib/Win32/Exe/InsertResourceSection.pm blib\lib\Win32\Exe\InsertResourceSection.pm \
	  lib/Win32/Exe/Manifest.pm blib\lib\Win32\Exe\Manifest.pm \
	  lib/Win32/Exe/Manifest/Parser.pm blib\lib\Win32\Exe\Manifest\Parser.pm \
	  lib/Win32/Exe/PE.pm blib\lib\Win32\Exe\PE.pm \
	  lib/Win32/Exe/PE/Header.pm blib\lib\Win32\Exe\PE\Header.pm \
	  lib/Win32/Exe/PE/Header/PE32.pm blib\lib\Win32\Exe\PE\Header\PE32.pm \
	  lib/Win32/Exe/PE/Header/PE32Plus.pm blib\lib\Win32\Exe\PE\Header\PE32Plus.pm \
	  lib/Win32/Exe/Resource.pm blib\lib\Win32\Exe\Resource.pm \
	  lib/Win32/Exe/Resource/GroupIcon.pm blib\lib\Win32\Exe\Resource\GroupIcon.pm \
	  lib/Win32/Exe/Resource/Icon.pm blib\lib\Win32\Exe\Resource\Icon.pm \
	  lib/Win32/Exe/Resource/Manifest.pm blib\lib\Win32\Exe\Resource\Manifest.pm \
	  lib/Win32/Exe/Resource/Version.pm blib\lib\Win32\Exe\Resource\Version.pm \
	  lib/Win32/Exe/ResourceData.pm blib\lib\Win32\Exe\ResourceData.pm 
	$(NOECHO) $(ABSPERLRUN) -MExtUtils::Install -e "pm_to_blib({{@ARGV}}, '$(INST_LIB)\auto', q[$(PM_FILTER)], '$(PERM_DIR)')" -- \
	  lib/Win32/Exe/ResourceEntry.pm blib\lib\Win32\Exe\ResourceEntry.pm \
	  lib/Win32/Exe/ResourceEntry/Id.pm blib\lib\Win32\Exe\ResourceEntry\Id.pm \
	  lib/Win32/Exe/ResourceEntry/Name.pm blib\lib\Win32\Exe\ResourceEntry\Name.pm \
	  lib/Win32/Exe/ResourceTable.pm blib\lib\Win32\Exe\ResourceTable.pm \
	  lib/Win32/Exe/Section.pm blib\lib\Win32\Exe\Section.pm \
	  lib/Win32/Exe/Section/Code.pm blib\lib\Win32\Exe\Section\Code.pm \
	  lib/Win32/Exe/Section/Data.pm blib\lib\Win32\Exe\Section\Data.pm \
	  lib/Win32/Exe/Section/Debug.pm blib\lib\Win32\Exe\Section\Debug.pm \
	  lib/Win32/Exe/Section/Exports.pm blib\lib\Win32\Exe\Section\Exports.pm \
	  lib/Win32/Exe/Section/Imports.pm blib\lib\Win32\Exe\Section\Imports.pm \
	  lib/Win32/Exe/Section/Resources.pm blib\lib\Win32\Exe\Section\Resources.pm 
	$(NOECHO) $(TOUCH) pm_to_blib


# --- MakeMaker selfdocument section:


# --- MakeMaker postamble section:


# End.
