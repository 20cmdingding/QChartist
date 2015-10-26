' -------------------------------------------------------------------
' RAPIDQ CODE                                   Jan 2007      Jacques
' 
' BUILDS TINY EXECUTABLES FROM BYTECODE 
' -------------------------------------------------------------------
''pre cmd Tiny opt noKill
''pre end
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
If bcFile.Open ("RQ_Null.Bc", fmOpenRead) <> 0 Then
 If tnyFile.Open ("Bcc_NullTiny.Exe", fmOpenRead) <> 0 Then
    exeFile.Open ("RQ_Null.Exe", fmCreate)
       sBc = bcFile.ReadBinStr(bcFile.Size)
       sTny = tnyFile.ReadBinStr(tnyFile.Size)
       exeFile.WriteBinStr (sTny, tnyFile.Size)
       exeFile.WriteBinStr (sbc, bcFile.Size)
    exeFile.Close
    tnyFile.Close
     Else
       Print " *** Error: file ...Tiny.Exe not found "
     End If
    bcFile.Close
Else
 Print " *** Error: file .Bc not found "
End If
' -------------------------------------------------------------
DefStr sExit
Input "\n\n   TINY BUILDER    FINISHED      CR to CONTINUE \n\n", sExit
Application.Terminate
End
'
