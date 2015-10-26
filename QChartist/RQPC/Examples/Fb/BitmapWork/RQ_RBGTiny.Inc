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
' ' ''RQEXPORT function BitmapWork (fileBMP:String, ptrResult, Method)
Declare Function cwp_BitmapWork Lib "user32" Alias "CallWindowProcA" _
                   (ptrBitmapWork As Long, fileBMP As Long, ptrResult As Long, Method As Long, Arg4 As Long) As Long
DefInt ptrBitmapWork = GetFuncPtr ("BitmapWork")
Function BitmapWork(fileBMP As String, ptrResult, Method) As Long
    Dim _fileBMP As String:_fileBMP = Mid$(fileBMP, 1)
    DefInt iRet = cwp_BitmapWork(ptrBitmapWork, VarPtr(_fileBMP), ptrResult, Method, 0)
    Result = iRet
End Function
' --------------------------------------------------------------------
