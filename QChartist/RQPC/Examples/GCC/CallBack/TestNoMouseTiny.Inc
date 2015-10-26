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
' // ''RQEXPORT function CB_RichEdit_Top ()
Declare Function cwp_CB_RichEdit_Top Lib "user32" Alias "CallWindowProcA" _
                   (ptrCB_RichEdit_Top As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrCB_RichEdit_Top = GetFuncPtr ("CB_RichEdit_Top")
Function CB_RichEdit_Top() As Long
    DefInt iRet = cwp_CB_RichEdit_Top(ptrCB_RichEdit_Top, 0, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function CB_RichEdit_Bottom ()
Declare Function cwp_CB_RichEdit_Bottom Lib "user32" Alias "CallWindowProcA" _
                   (ptrCB_RichEdit_Bottom As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrCB_RichEdit_Bottom = GetFuncPtr ("CB_RichEdit_Bottom")
Function CB_RichEdit_Bottom() As Long
    DefInt iRet = cwp_CB_RichEdit_Bottom(ptrCB_RichEdit_Bottom, 0, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function SubClassTop (hRichEditTop)
Declare Function cwp_SubClassTop Lib "user32" Alias "CallWindowProcA" _
                   (ptrSubClassTop As Long, hRichEditTop As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrSubClassTop = GetFuncPtr ("SubClassTop")
Function SubClassTop(hRichEditTop) As Long
    DefInt iRet = cwp_SubClassTop(ptrSubClassTop, hRichEditTop, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function SubClassBottom (hRichEditBottom)
Declare Function cwp_SubClassBottom Lib "user32" Alias "CallWindowProcA" _
                   (ptrSubClassBottom As Long, hRichEditBottom As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrSubClassBottom = GetFuncPtr ("SubClassBottom")
Function SubClassBottom(hRichEditBottom) As Long
    DefInt iRet = cwp_SubClassBottom(ptrSubClassBottom, hRichEditBottom, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function InitSubClass ()
Declare Function cwp_InitSubClass Lib "user32" Alias "CallWindowProcA" _
                   (ptrInitSubClass As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrInitSubClass = GetFuncPtr ("InitSubClass")
Function InitSubClass() As Long
    DefInt iRet = cwp_InitSubClass(ptrInitSubClass, 0, 0, 0, 0)
    Result = iRet
End Function
' --------------------------------------------------------------------
