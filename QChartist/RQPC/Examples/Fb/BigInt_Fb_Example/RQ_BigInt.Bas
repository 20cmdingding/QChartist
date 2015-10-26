'
' -------------------------------------------------------------------
' RQPC FB EXAMPLE: BIGINT  from Fb             Nov 2006,     Jacques
' -------------------------------------------------------------------
'
$Include "RQ_BigIntTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated tiny run opt con BigInt.Fbb NoDone Icon_2686.Ico kill nobk
DefStr BuildCount = "0.011" ''pre + 0.001 3
DefStr FirstCompiled  = "12-26-2006  19:18:50"
''pre end
SetConsoleTitle (Application.ExeName & "   V" & BuildCount)
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
' Call FB BigInt code
DoBigInt
'
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
' -------------------------------------------------------------------
'
