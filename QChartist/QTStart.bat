echo off
cls
echo Compiling QTGen.bas
echo.
del QTGen.exe
rqpc\rqpc QTGen.bas noconsole
echo.
echo Compiling QTGuard.bas
echo.
del QTGuard.exe
rqpc\rqpc QTGuard.bas noconsole
echo.
echo Compiling sendmail.bas
echo.
del sendmail.exe
rqpc\rqpc sendmail.bas noconsole
echo.
echo Compiling sendmail2.bas
echo.
del sendmail2.exe
rc sendmail2.bas
echo.
echo Compiling QTIndex.bas
echo.
del QTIndex.exe
rqpc\rqpc QTIndex.bas
echo.
echo Indexing indicators
echo.
QTIndex.exe
echo.
echo Compiling update.bas
echo.
del update.exe
rc update.bas
echo.
echo Compiling QChartist.bas please wait...
echo.
del QChartist.exe
rqpc\rqpc QChartist.bas