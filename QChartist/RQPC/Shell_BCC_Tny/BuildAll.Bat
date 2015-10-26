
rem ===================================================================
rem RAPIDQ  byteCode Launcher                       jan 2007    Jacques
rem ===================================================================

Echo off
Rem RapidQ Compile TinyBuilder.Bas
"c:\Rapid-Q\rc.exe" -I"c:\Rapid-Q\Includes" -L"c:\Rapid-Q\Libs" TinyBuilder.Bas

Rem RapidQ Compile RQ_Null.Bas to ByteCode
"c:\Rapid-Q\rc.exe" -B -opt -I"c:\Rapid-Q\Includes" -L"c:\Rapid-Q\Libs" RQ_Null.Bas

Rem Set in Path for Borland
SET PATH=%PATH%;"C:\Borland\Bcc55\BIN\"

Rem compile icon.rc to .Res
brc32 -32 -r Icon.rc

Rem BCC Compile Bcc_NullTiny.Cpp (The bytecode Launcher) with AddInt(i1, i2) 
Rem -c = compile only , -tW = gui
Bcc32 -Ic:\Borland\Bcc55\Include -Lc:\Borland\Bcc55\Lib -c -tW Bcc_NullTiny.Cpp

Rem ILINK32 (not an easy one :)
ilink32 /aa /Lc:\Borland\Bcc55\Lib c0w32 Bcc_nulltiny.obj,Bcc_nulltiny.exe,,import32 cw32,,Icon.Res

Rem Merge Bcc_NullTiny.Exe + RQ_Null.Bc
Call TinyBuilder.Exe

Rem Run the final code
Call RQ_Null.Exe

rem ===================================================================
