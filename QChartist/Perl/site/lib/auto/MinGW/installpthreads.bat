@echo off
echo.
echo MinGW For Perl Environment
echo.

set ROOTPATH=%~dp0
rem %ROOTPATH% ends with a trailing backslash
echo Installing pthreads-win32 in %ROOTPATH% ....
echo.
echo.
xcopy %ROOTPATH%pthreads-win32  %ROOTPATH% /E /Y /R /F
echo.
echo.
echo Installation of pthreads-win32 is complete.
echo run removepthreads.bat to remove installed files
echo.

pause
