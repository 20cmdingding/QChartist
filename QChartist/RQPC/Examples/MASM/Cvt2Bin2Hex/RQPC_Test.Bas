'
' ----------------------------------------------------------------------
' RQPC FB Demo HexToBin BinToHex            Jacques, january 27th, 2007
' ----------------------------------------------------------------------
'
''pre cmd opt tiny con run kill nobk CvtBinHex.Asm nodone diricon
''pre end
$TypeCheck On
$EscapeChars On
$Include "RapidQ.Inc"
'
DefStr sHex = "1234567890ABCDEF"
'
DefStr sBin = Space$(Len(sHex)/2)
'Defint iRet = HexToBin (VarPtr(sHex), Len(sHex), VarPtr(sBin))
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
iRet = BinToHex (VarPtr(sBin), Len(sBin), VarPtr(sReHex))
Print "\niRet BinToHex: ";iRet
'
Print "\nBack to hex: ";sReHex
'
Print "\n\n        ***  Finished  ***"
' ----------------------------------------------------------------------
DefStr sInput:Input sInput:Application.Terminate
' ----------------------------------------------------------------------
'
