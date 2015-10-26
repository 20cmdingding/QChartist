'
' ----------------------------------------------------------------------
' RQPC FB Demo HexToBin BinToHex            Jacques, january 27th, 2007
' ----------------------------------------------------------------------
'
$Include "RQPC_TestTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated opt tiny con run kill nobk CvtBinHex.Fbb NoDone diricon
''pre end
$TypeCheck On
$EscapeChars On
$Include "RapidQ.Inc"
'
DefStr sHex = "1234567890ABCDEF"
'
DefStr sBin = Space$(Len(sHex)/2)
Defint iRet = HexToBin (VarPtr(sHex), Len(sHex), VarPtr(sBin))
'
Print "\niRet HexToBin: ";iRet
Print "\n";sHex;"  to Bin:"
DefInt N, i
For N = 1 To Len(sBin)
    i = Asc(sBin[N])
    Print Right$(Hex$((i shr 4) and &HF), 1);" ";Right$(Hex$(i and &HF), 1)
Next N
'
DefStr sReHex = Space$(Len(sBin) * 2)
BinToHex (VarPtr(sBin), Len(sBin), VarPtr(sReHex))
'
Print "\nBack to hex: ";sReHex
'
Print "\n\n        ***  Finished  ***"
' ----------------------------------------------------------------------
DefStr sInput:Input sInput:Application.Terminate
' ----------------------------------------------------------------------
'
