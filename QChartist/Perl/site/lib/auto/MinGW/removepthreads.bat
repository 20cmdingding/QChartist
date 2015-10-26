@echo off
echo.
echo MinGW For Perl Environment
echo.

set ROOTPATH=%~dp0
rem %ROOTPATH% ends with a trailing backslash
echo Removing pthreads-win32 from %ROOTPATH% ....
echo.
echo.

rem echo removing %ROOTPATH%bin\pthreadGC2-w32.dll
rem del /F %ROOTPATH%bin\pthreadGC2-w32.dll

echo removing %ROOTPATH%i686-w64-mingw32\include\pthread.h
del /F %ROOTPATH%i686-w64-mingw32\include\pthread.h

echo removing %ROOTPATH%i686-w64-mingw32\include\pthreads_win32_config.h
del /F %ROOTPATH%i686-w64-mingw32\include\pthreads_win32_config.h

echo removing %ROOTPATH%i686-w64-mingw32\include\sched.h
del /F %ROOTPATH%i686-w64-mingw32\include\sched.h

echo removing %ROOTPATH%i686-w64-mingw32\include\semaphore.h
del /F %ROOTPATH%i686-w64-mingw32\include\semaphore.h

echo removing %ROOTPATH%i686-w64-mingw32\lib\libpthread.a
del /F %ROOTPATH%i686-w64-mingw32\lib\libpthread.a

echo removing %ROOTPATH%share\doc\pthreads-win32
rmdir /S /Q %ROOTPATH%share\doc\pthreads-win32

echo.
echo.
echo Removal of pthreads-win32 is complete.
echo run installpthreads.bat to reinstall files
echo.

pause
