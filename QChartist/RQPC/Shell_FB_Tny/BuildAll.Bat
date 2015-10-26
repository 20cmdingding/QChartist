
rem  ===================================================================
rem  RAPIDQ  byteCode Launcher                       nov 2006    Jacques
rem  ===================================================================

Echo off
Rem RapidQ Compile TinyBuilder.Bas
"c:\Rapid-Q\rc.exe" -I"c:\Rapid-Q\Includes" -L"c:\Rapid-Q\Libs" TinyBuilder.Bas

Rem RapidQ Compile RQ_Null.Bas to ByteCode
"c:\Rapid-Q\rc.exe" -B -opt -I"c:\Rapid-Q\Includes" -L"c:\Rapid-Q\Libs" RQ_Null.Bas

Rem FreeBasic Compile FB_NullTiny.Bas (The bytecode Launcher) with AddInt(i1, i2) 
c:\freebasic\fbc.exe -v -s gui -i c:\freebasic\inc -p c:\freebasic\lib FB_NullTiny.Bas Icon.Rc

Rem Merge FB_NullTiny.Exe + RQ_Null.Bc
Call TinyBuilder.Exe

Rem Run the final code
Call RQ_Null.Exe

rem  ===================================================================
