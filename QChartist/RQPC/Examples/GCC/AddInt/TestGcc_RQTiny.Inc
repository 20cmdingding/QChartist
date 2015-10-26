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
' // ''RQEXPORT function TestAddInt (i1, i2)
Declare Function cwp_TestAddInt Lib "user32" Alias "CallWindowProcA" _
                   (ptrTestAddInt As Long, i1 As Long, i2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrTestAddInt = GetFuncPtr ("TestAddInt")
Function TestAddInt(i1, i2) As Long
    DefInt iRet = cwp_TestAddInt(ptrTestAddInt, i1, i2, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function TestSubInt (i1, i2)
Declare Function cwp_TestSubInt Lib "user32" Alias "CallWindowProcA" _
                   (ptrTestSubInt As Long, i1 As Long, i2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrTestSubInt = GetFuncPtr ("TestSubInt")
Function TestSubInt(i1, i2) As Long
    DefInt iRet = cwp_TestSubInt(ptrTestSubInt, i1, i2, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT data MyString
DefInt ptrMyString = GetFuncPtr ("MyString")
' // ''RQEXPORT data MyBuffer_1
DefInt ptrMyBuffer_1 = GetFuncPtr ("MyBuffer_1")
' // ''RQEXPORT data MyBuffer_2
DefInt ptrMyBuffer_2 = GetFuncPtr ("MyBuffer_2")
' --------------------------------------------------------------------
