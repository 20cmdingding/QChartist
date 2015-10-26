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
' ' ''RQEXPORT function BinToHex (ptrBin, binSize, ptrHex)
Declare Function cwp_BinToHex Lib "user32" Alias "CallWindowProcA" _
                   (ptrBinToHex As Long, ptrBin As Long, binSize As Long, ptrHex As Long, Arg4 As Long) As Long
DefInt ptrBinToHex = GetFuncPtr ("BinToHex")
Function BinToHex(ptrBin, binSize, ptrHex) As Long
    DefInt iRet = cwp_BinToHex(ptrBinToHex, ptrBin, binSize, ptrHex, 0)
    Result = iRet
End Function
' ------------------------------------------------
' ' ''RQEXPORT function HexToBin (ptrHex, hexSize, ptrBin)
Declare Function cwp_HexToBin Lib "user32" Alias "CallWindowProcA" _
                   (ptrHexToBin As Long, ptrHex As Long, hexSize As Long, ptrBin As Long, Arg4 As Long) As Long
DefInt ptrHexToBin = GetFuncPtr ("HexToBin")
Function HexToBin(ptrHex, hexSize, ptrBin) As Long
    DefInt iRet = cwp_HexToBin(ptrHexToBin, ptrHex, hexSize, ptrBin, 0)
    Result = iRet
End Function
' --------------------------------------------------------------------
