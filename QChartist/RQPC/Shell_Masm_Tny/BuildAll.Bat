rem
rem  ===================================================================
rem  RAPIDQ  byteCode Launcher                       nov 2006    Jacques
rem  ===================================================================
rem 
Echo off
Rem RapidQ Compile TinyBuilder.Bas
"c:\Rapid-Q\rc.exe" -I"c:\Rapid-Q\Includes" -L"c:\Rapid-Q\Libs" TinyBuilder.Bas

Rem RapidQ Compile RQ_Null.Bas to ByteCode
"c:\Rapid-Q\rc.exe" -B -opt -I"c:\Rapid-Q\Includes" -L"c:\Rapid-Q\Libs" RQ_Null.Bas

Rem Compile Icon.Rc to Icon.Res
c:\masm32\bin\rc /v icon.rc

Rem Compile Icon.Res to Icon.Obj
c:\masm32\bin\cvtres /machine:ix86 icon.res

Rem Compile Masm_NullTiny.Asm To Masm_NullTiny.Obj
c:\masm32\bin\ml /c /coff Masm_NullTiny.Asm

Rem Link Masm_NullTiny.Obj and icon.obj to Masm_NullTiny.Exe
c:\masm32\bin\Link /SUBSYSTEM:WINDOWS /OPT:NOREF Masm_NullTiny.Obj icon.obj

Rem Merge Masm_NullTiny.Exe + RQ_Null.Bc
Call TinyBuilder.Exe

Rem Run the final code
Call RQ_Null.Exe

rem  ===================================================================
