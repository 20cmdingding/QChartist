------------------------------------------------------------
GCC COMPILER BUNDLE FOR 32 BIT WINDOWS
------------------------------------------------------------

The archives contain a single top level directory - 'mingw32'
Download one of the archives (7-zip is recommended) and 
extract to a path on your system with NO SPACES.

Once extracted, to use place '<extractedpath>\mingw32\bin'
on your path.

You may do this by adding the path to the start of your
PATH environment variable, or more commonly you may create
batch files that set up your environment. For example:

mydevenv.bat >>

set PATH=C:\extractedpath\mingw32\bin;%PATH%
cmd /K

<<

The compiler bundle includes c, c++ and fortran compilers.

make.exe has been renamed with the aliases gmake and 
mingw32-make to avoid conflict with msys make if you use 
that enviroment.

The 'dmake' make utility is included for use with Perl.

------------------------------------------------------------
USE WITH PERL
------------------------------------------------------------

For use with Perl you may also choose to add the path to
Perl allowing you to set up environments for several
different Perl installations.

mydevenv.bat >>

set MPERLPATH=C:\myperl
set PATH=%MPERLPATH%\site\bin;%MPERLPATH%\bin;%PATH%
set PATH=C:\extractedpath\mingw32\bin;%PATH%
cmd /K

<<

For use with ActivePerl, you may wish to rely on ActivePerl
itself passing out the correct configuration options during
module compilation which all recent versions of ActivePerl
should do. ActivePerl passes link library options that 
include '-lmsvcrt'. It appears this is the wrong thing to do
with some gcc versions but the issue only manifests itself
compiling particular xs modules. You may therefore choose to 
use the bundled configuration module in 
..\mingw64\perllib\Config_MinGWFP.pm.
You can place this module in your $PERL\site\lib and then 
set up your environment bat as:

mydevenv.bat >>

set MPERLPATH=C:\myperl
set PATH=%MPERLPATH%\site\bin;%MPERLPATH%\bin;%PATH%
set PATH=C:\extractedpath\mingw32\bin;%PATH%
set PERL5OPT=-MConfig_MinGWFP
cmd /K

<<

------------------------------------------------------------
COMPILING YOUR OWN PERL
------------------------------------------------------------

Compiling your own Perl is quite straightforward.

Download the source for Perl 5.12.x or Perl 5.14.x.

Edit the file ..\win32\makefile.mk

The text below shows the edits you might choose to make which
can easily applied by hand. (Edits are the same for Perl 5.12)

=======================================================================
--- perl-5.14.2/win32/makefile.mk 2011-06-17 01:06:09.000000000 +0100
+++ perl-5.14.2/win32/makefile.mk 2011-10-15 19:04:39.931400000 +0100
@@ -23,12 +23,12 @@
 # newly built perl.
 #
 INST_DRV   *= c:
-INST_TOP   *= $(INST_DRV)\perl
+INST_TOP   *= $(INST_DRV)\myperl
 
 #
 # Uncomment if you want to build a 32-bit Perl using a 32-bit compiler
 # on a 64-bit version of Windows.
-#WIN64     *= undef
#WIN64  *= undef
 
 #
 # Comment this out if you DON'T want your perl installation to be versioned.
@@ -58,7 +58,7 @@
 # before anything else.  This script can then be set up, for example,
 # to add additional entries to @INC.
 #
-#USE_SITECUST  *= define
+USE_SITECUST   *= define
 
 #
 # uncomment to enable multiple interpreters.  This is need for fork()
@@ -194,7 +194,7 @@
 .IF "$(CCTYPE)" == "BORLAND"
 CCHOME     *= C:\Borland\BCC55
 .ELIF "$(CCTYPE)" == "GCC"
-CCHOME     *= C:\MinGW
+CCHOME     *= C:\extractedpath\mingw32
 .ELSE
 CCHOME     *= $(MSVCDIR)
 .ENDIF
@@ -210,8 +210,8 @@
 # unsure about the correct name.)
 # Without these corrections, the op/taint.t test script will fail.
 #
-#GCC_4XX       *= define
-#GCCHELPERDLL  *= $(CCHOME)\bin\libgcc_s_sjlj-1.dll
+GCC_4XX        *= define
+GCCHELPERDLL   *= $(CCHOME)\bin\libgcc_s_sjlj-1.dll
 #GCCHELPERDLL  *= $(CCHOME)\bin\libgcc_s_dw2-1.dll
 #GCCHELPERDLL  *= $(CCHOME)\bin\libgcc_s_1.dll
 
@@ -230,8 +230,8 @@
 CCINCDIR *= $(CCHOME)\mingw\include
 CCLIBDIR *= $(CCHOME)\mingw\lib
 .ELSE
-CCINCDIR *= $(CCHOME)\include
-CCLIBDIR *= $(CCHOME)\lib
+CCINCDIR *= $(CCHOME)\i686-w64-mingw32\include
+CCLIBDIR *= $(CCHOME)\i686-w64-mingw32\lib
 .ENDIF
 
 #

=======================================================================

Once you have make your edits to makefile.mk, you can change to the
..\win32 directory of the Perl source and run

dmake

Once Perl has compiled, BEFORE you run the tests you must copy
libstdc++-6.dll to the ..\t directory of the Perl source in which you
are building. Then.

dmake test

You can then

dmake install

So that your Perl installation can run even when your compiler bin is 
not on your path, copy two dlls from ..\mingw32\bin to your <perl>\bin
so that they are side by side with perl.exe

libgcc_s_sjlj-1.dll
libstdc++-6.dll























