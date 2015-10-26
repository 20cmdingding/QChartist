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
' ' ''RQEXPORT function ReplaceCharByRef (InString:String:ByRef, ToReplace:String, ReplaceBy:String)
Declare Function cwp_ReplaceCharByRef Lib "user32" Alias "CallWindowProcA" _
                   (ptrReplaceCharByRef As Long, InString As Long, ToReplace As Long, ReplaceBy As Long, Arg4 As Long) As Long
DefInt ptrReplaceCharByRef = GetFuncPtr ("ReplaceCharByRef")
Function ReplaceCharByRef(ByRef InString As String, ToReplace As String, ReplaceBy As String) As Long
    Dim _InString As String:_InString = InString
    Dim _ToReplace As String:_ToReplace = Mid$(ToReplace, 1)
    Dim _ReplaceBy As String:_ReplaceBy = Mid$(ReplaceBy, 1)
    DefInt iRet = cwp_ReplaceCharByRef(ptrReplaceCharByRef, VarPtr(_InString), VarPtr(_ToReplace), VarPtr(_ReplaceBy), 0)
    Result = iRet
End Function
' ------------------------------------------------
' ' ''RQEXPORT function ReplaceCharByVal (InString:String, ToReplace:String, ReplaceBy:String)
Declare Function cwp_ReplaceCharByVal Lib "user32" Alias "CallWindowProcA" _
                   (ptrReplaceCharByVal As Long, InString As Long, ToReplace As Long, ReplaceBy As Long, Arg4 As Long) As Long
DefInt ptrReplaceCharByVal = GetFuncPtr ("ReplaceCharByVal")
Function ReplaceCharByVal(InString As String, ToReplace As String, ReplaceBy As String) As Long
    Dim _InString As String:_InString = Mid$(InString, 1)
    Dim _ToReplace As String:_ToReplace = Mid$(ToReplace, 1)
    Dim _ReplaceBy As String:_ReplaceBy = Mid$(ReplaceBy, 1)
    DefInt iRet = cwp_ReplaceCharByVal(ptrReplaceCharByVal, VarPtr(_InString), VarPtr(_ToReplace), VarPtr(_ReplaceBy), 0)
    Result = iRet
End Function
' ------------------------------------------------
' ' ''RQEXPORT function ReplaceCharAsString:String (InString:String, ToReplace:String, ReplaceBy:String)
Declare Function cwp_ReplaceCharAsString Lib "user32" Alias "CallWindowProcA" _
                   (ptrReplaceCharAsString As Long, InString As Long, ToReplace As Long, ReplaceBy As Long, Arg4 As Long) As Long
DefInt ptrReplaceCharAsString = GetFuncPtr ("ReplaceCharAsString")
Function ReplaceCharAsString(InString As String, ToReplace As String, ReplaceBy As String) As String
    Dim _InString As String:_InString = Mid$(InString, 1)
    Dim _ToReplace As String:_ToReplace = Mid$(ToReplace, 1)
    Dim _ReplaceBy As String:_ReplaceBy = Mid$(ReplaceBy, 1)
    DefInt iRet = cwp_ReplaceCharAsString(ptrReplaceCharAsString, VarPtr(_InString), VarPtr(_ToReplace), VarPtr(_ReplaceBy), 0)
    DefStr sRet = Space$(RTL_lstrlen(iRet))
    MemCpy (VarPtr(sRet), iRet, Len(sRet))
    Result = sRet
End Function
' ------------------------------------------------
' ' ''RQEXPORT function SinglePlusDouble_1:Double (sng1:Single, dbl1:Double:ByRef)
Declare Function cwp_SinglePlusDouble_1 Lib "user32" Alias "CallWindowProcA" _
                   (ptrSinglePlusDouble_1 As Long, sng1 As Long, dbl1 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrSinglePlusDouble_1 = GetFuncPtr ("SinglePlusDouble_1")
Function SinglePlusDouble_1(sng1 As Single, ByRef dbl1 As Double) As Double
    Dim _sng1 As Single:_sng1 = 1 * sng1
    Dim _dbl1 As Double:_dbl1 = dbl1
    DefInt iRet = cwp_SinglePlusDouble_1(ptrSinglePlusDouble_1, VarPtr(_sng1), VarPtr(_dbl1), 0, 0)
    DefDbl dblRet
    MemCpy (VarPtr(dblRet), iRet, 8)
    Result = dblRet
End Function
' ------------------------------------------------
' ' ''RQEXPORT function SinglePlusDouble_2:Single (sng1:Single:ByRef, dbl1:Double)
Declare Function cwp_SinglePlusDouble_2 Lib "user32" Alias "CallWindowProcA" _
                   (ptrSinglePlusDouble_2 As Long, sng1 As Long, dbl1 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrSinglePlusDouble_2 = GetFuncPtr ("SinglePlusDouble_2")
Function SinglePlusDouble_2(ByRef sng1 As Single, dbl1 As Double) As Single
    Dim _sng1 As Single:_sng1 = sng1
    Dim _dbl1 As Double:_dbl1 = 1 * dbl1
    DefInt iRet = cwp_SinglePlusDouble_2(ptrSinglePlusDouble_2, VarPtr(_sng1), VarPtr(_dbl1), 0, 0)
    DefLng sngRet
    MemCpy (VarPtr(sngRet), iRet, 4)
    Result = sngRet
End Function
' ------------------------------------------------
' ' ''RQEXPORT function SinglePlusDouble_3:Single (sng1:Single:ByRef, dbl1:Double:ByRef)
Declare Function cwp_SinglePlusDouble_3 Lib "user32" Alias "CallWindowProcA" _
                   (ptrSinglePlusDouble_3 As Long, sng1 As Long, dbl1 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrSinglePlusDouble_3 = GetFuncPtr ("SinglePlusDouble_3")
Function SinglePlusDouble_3(ByRef sng1 As Single, ByRef dbl1 As Double) As Single
    Dim _sng1 As Single:_sng1 = sng1
    Dim _dbl1 As Double:_dbl1 = dbl1
    DefInt iRet = cwp_SinglePlusDouble_3(ptrSinglePlusDouble_3, VarPtr(_sng1), VarPtr(_dbl1), 0, 0)
    DefLng sngRet
    MemCpy (VarPtr(sngRet), iRet, 4)
    Result = sngRet
End Function
' ------------------------------------------------
' ' ''RQEXPORT function SinglePlusDouble_4:Double (sng1:Single, dbl1:Double)
Declare Function cwp_SinglePlusDouble_4 Lib "user32" Alias "CallWindowProcA" _
                   (ptrSinglePlusDouble_4 As Long, sng1 As Long, dbl1 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrSinglePlusDouble_4 = GetFuncPtr ("SinglePlusDouble_4")
Function SinglePlusDouble_4(sng1 As Single, dbl1 As Double) As Double
    Dim _sng1 As Single:_sng1 = 1 * sng1
    Dim _dbl1 As Double:_dbl1 = 1 * dbl1
    DefInt iRet = cwp_SinglePlusDouble_4(ptrSinglePlusDouble_4, VarPtr(_sng1), VarPtr(_dbl1), 0, 0)
    DefDbl dblRet
    MemCpy (VarPtr(dblRet), iRet, 8)
    Result = dblRet
End Function
' --------------------------------------------------------------------
