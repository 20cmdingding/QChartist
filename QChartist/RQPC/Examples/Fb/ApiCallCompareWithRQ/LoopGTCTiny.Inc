' -------------------------------------------------------------------
' Rapidq side RunTime Linker Code                 Nov 2006,  Jacques
' -------------------------------------------------------------------
' Common Part
' -----------
Declare Function RTL_lstrlen Lib "kernel32" Alias "lstrlenA" (lpString As Long) As Long
'
DefInt ptrNameAddress = Val(Environ$("ptrNameAddress"))
DefInt lenNameAddress = Val(Environ$("lenNameAddress"))
'
DefStr sNameAddress = Space$(lenNameAddress)
memcpy (VarPtr(sNameAddress), ptrNameAddress, lenNameAddress)
'
Function GetFuncPtr (sName As String) As Long
    DefInt i0, i1, i2
    DefStr sPtr
    i0 = Instr (sNameAddress, ";" & sName & ",")
    If i0 = 0 Then Result = 0:Exit Function
    i1 = Instr(i0, sNameAddress, ",")
    i2 = Instr(i1, sNameAddress, ";")
    sPtr = Mid$(sNameAddress, i1 + 1, i2 - i1 - 1)
    Result = Val(sPtr)
End Function
' --------------------------------------------------------------------
' User Code Part
' --------------
' ------------------------------------------------
' ' ''RQEXPORT function CWP_Test ()
Declare Function cwp_CWP_Test Lib "user32" Alias "CallWindowProcA" _
                   (ptrCWP_Test As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrCWP_Test = GetFuncPtr ("CWP_Test")
Function CWP_Test() As Long
    DefInt iRet = cwp_CWP_Test(ptrCWP_Test, 0, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' ' ''RQEXPORT function LoopGTC (LoopCount)
Declare Function cwp_LoopGTC Lib "user32" Alias "CallWindowProcA" _
                   (ptrLoopGTC As Long, LoopCount As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrLoopGTC = GetFuncPtr ("LoopGTC")
Function LoopGTC(LoopCount) As Long
    DefInt iRet = cwp_LoopGTC(ptrLoopGTC, LoopCount, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' ' ''RQEXPORT function LoopNull (LoopCount)
Declare Function cwp_LoopNull Lib "user32" Alias "CallWindowProcA" _
                   (ptrLoopNull As Long, LoopCount As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrLoopNull = GetFuncPtr ("LoopNull")
Function LoopNull(LoopCount) As Long
    DefInt iRet = cwp_LoopNull(ptrLoopNull, LoopCount, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' ' ''RQEXPORT function LoopCWP (LoopCount)
Declare Function cwp_LoopCWP Lib "user32" Alias "CallWindowProcA" _
                   (ptrLoopCWP As Long, LoopCount As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrLoopCWP = GetFuncPtr ("LoopCWP")
Function LoopCWP(LoopCount) As Long
    DefInt iRet = cwp_LoopCWP(ptrLoopCWP, LoopCount, 0, 0, 0)
    Result = iRet
End Function
' --------------------------------------------------------------------
