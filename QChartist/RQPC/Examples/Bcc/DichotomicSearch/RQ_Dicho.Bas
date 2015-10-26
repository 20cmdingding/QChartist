'
' -------------------------------------------------------------------
' RQPC BCC EXAMPLE  C++ Dichotomic Search         Jan 2007,   Jacques
' -------------------------------------------------------------------
'
$Include "RQ_DichoTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd tiny run enc noopt exe con kill nobk DichoSearch.Bpp NoDone diricon
DefStr BuildCount = "0.012" ''pre + 0.001 3
DefStr FirstCompiled  = "01-09-2007  20:15:29"
''pre end
SetConsoleTitle (Application.ExeName & "   V" & BuildCount)
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
DefInt Int10K(0 To 10000), N
For N = 0 To 10000
    Int10K(N) = N
Next N
'
DefInt iRet = SearchDicho (VarPtr(Int10K(0)), 10001, 6256)
Print "6256= ";iRet

' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
'
