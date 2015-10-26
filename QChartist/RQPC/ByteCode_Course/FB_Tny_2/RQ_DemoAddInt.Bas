'
' -------------------------------------------------------------------
' RapidQ Code Executing FB Function            Nov 2006,     Jacques
' Link and Execute a Function from the ByteCode Launcher
' -------------------------------------------------------------------
'
''pre cmd tiny opt exe con noKill noRun
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
DefInt ptrAddInt = Val(Environ$("AddInt"))
        '
Declare Function cwp_AddInt Lib "user32" Alias "CallWindowProcA" _
                   (ptrAddInt As Long, i1 As Long, i2 As Long, _
                                    Arg3 As Long, Arg4 As Long) As Long
Function AddInt(i1, i2) As Long
    DefInt iRet = cwp_AddInt(ptrAddInt, i1, i2, 0, 0)
    Result = iRet
End Function
'
DefInt iSum = AddInt (7, 8)  ' that will execute FB code in the Launcher
Print " in RQ: and life from FB ByteCode Launcher: 7 + 8 = ";iSum
' -------------------------------------------------------------------
' Exit Console
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
' -------------------------------------------------------------------
