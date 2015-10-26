
rem ===================================================================
rem RAPIDQ  byteCode Launcher                       nov 2006    Jacques
rem ===================================================================

Echo off
Rem RapidQ Compile TinyBuilder.Bas
"c:\Rapid-Q\rc.exe" -I"c:\Rapid-Q\Includes" -L"c:\Rapid-Q\Libs" TinyBuilder.Bas

Rem RapidQ Compile RQ_Null.Bas to ByteCode
"c:\Rapid-Q\rc.exe" -B -opt -I"c:\Rapid-Q\Includes" -L"c:\Rapid-Q\Libs" RQ_Null.Bas

Rem compile icon.rc to .o (object)
c:\MinGw\Bin\windres -i icon.rc -o icon.o

Rem GCC Compile Gcc_NullTiny.Cpp (The bytecode Launcher) with AddInt(i1, i2) 
c:\MinGw\Bin\g++ -O -s -o Gcc_NullTiny.Exe Gcc_NullTiny.cpp icon.o -mwindows

Rem Merge Gcc_NullTiny.Exe + RQ_Null.Bc
Call TinyBuilder.Exe

Rem Run the final code
Call RQ_Null.Exe
rem ===================================================================
