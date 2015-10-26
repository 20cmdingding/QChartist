' -------------------------------------------------------------------
' RAPIDQ CODE                     Nov 2006                  Jacques
' 
' BUILDS TINY EXECUTABLES FROM BYTECODE 
' CmdConTest.Exe = FB_Tny.Exe + CmdConTest.Bc
' -------------------------------------------------------------------
''pre cmd Tiny opt noKill
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
''
' ----- RAPIDQ BC to EXE BUILDER -----
Dim bcFile As QFileStream
Dim tnyFile As QFileStream
Dim exeFile As QFileStream
DefStr sBc, sTny, sExe
' ----------------------------
' Creates CmdConTest.Exe
If bcFile.Open ("RQ_DemoAddInt.bc", fmOpenRead) <> 0 Then
 If tnyFile.Open ("FB_Tny.Exe", fmOpenRead) <> 0 Then
    exeFile.Open ("RQ_DemoAddInt.Bas.Exe", fmCreate)
       sBc = bcFile.ReadBinStr(bcFile.Size)
'       ENCRYPT(ptrENCRYPT, VarPtr(sBC), Len(sBC), 0, 0)
       sTny = tnyFile.ReadBinStr(tnyFile.Size)
       exeFile.WriteBinStr (sTny, tnyFile.Size)
       exeFile.WriteBinStr (sbc, bcFile.Size)
    exeFile.Close
    tnyFile.Close
     Else
       Print " *** Error: file .Jp not found "
     End If
    bcFile.Close
Else
 Print " *** Error: file .Bc not found "
End If
' -------------------------------------------------------------
DefStr sExit
Input "\n\n       FINISHED      CR to QUIT \n\n", sExit
Application.Terminate
End
'
