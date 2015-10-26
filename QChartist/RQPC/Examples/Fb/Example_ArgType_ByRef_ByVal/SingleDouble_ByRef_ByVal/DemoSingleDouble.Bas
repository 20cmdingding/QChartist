'
' ===================================================================
' RQPC FB DEMO: Single, Double passing, return     Nov 2006, Jacques
' -------------------------------------------------------------------
$Include "DemoSingleDoubleTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated tiny run DemoSingleDouble.Fbb NoDone con Pencil03.ico Kill nobk
DefStr BuildCount    =       "0.012"  ''pre + 0.001 3
''pre end
SetConsoleTitle (Application.ExeName & "   V" & BuildCount)
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
' ===================================================================
Print "\n\nSINGLE + DOUBLE in DOUBLE"
Print     "-------------------------"
' FB DECLARE CODE
' ' ''RQEXPORT function SinglePlusDouble_1:Double (sng1:Single, dbl1:Double)
' Function SinglePlusDouble_1(ByRef sng1 As Single, ByRef dbl1 As Double) As Double
DefSng sng = 333.333
DefDbl dbl = 222.222
Print " in RQ: sng  before call: ";sng
Print " in RQ: dbl  before call: ";dbl
DefDbl iRet = SinglePlusDouble_1 (sng, dbl)
Print " in RQ: Result: SinglePlusDouble_1 (sng, dbl): ";iRet
Print " in RQ:   sng after call: ";sng
Print " in RQ:   dbl after call: ";dbl;"  (cannot be set even passed ByRef)"
'
ShowMessage ("You should notice that Double and Singles have" _
         & "\nbeen passed to an External function very simply" _
       & "\n\n             Wait to continue")
' ===================================================================
Print "\n\nimmediat SINGLE + DOUBLE in DOUBLE"
Print     "----------------------------------"
iRet = SinglePlusDouble_1 (1.111, dbl)
Print " in RQ: Result = SinglePlusDouble_1 (1.111, dbl): ";iRet
'
ShowMessage ("Here the first argument is an immediat value" _
         & "\nImmediat values cannot be used with Arguments" _
         & "\npassed ByRef. It's a RapidQ limitation." _
       & "\n\n             Wait to continue")

' ===================================================================
Print "\n\nSINGLE + DOUBLE in SINGLE"
Print     "-------------------------"
' FB DECLARE CODE
' ''RQEXPORT function SinglePlusDouble_2:Single (sng1:Single:ByRef, dbl1:Double)
'Function SinglePlusDouble_2 (ByRef sng1 As Single, dbl1 As Double ptr) As Single
sng = 333.333
dbl = 222.222
Print " in RQ: sng  before call: ";sng
Print " in RQ: dbl  before call: ";dbl
DefSng iRet2 = SinglePlusDouble_2 (sng, dbl)
Print " in RQ: Result: SinglePlusDouble_2 (sng, dbl): ";iRet2
Print " in RQ:   sng after call: ";sng
Print " in RQ:   dbl after call: ";dbl;"  (cannot be set even passed ByRef)"
'
ShowMessage ("Double and Single have been swapped from precedent" _
         & "\nYou should notice that Double and Singles have" _
         & "\nbeen passed to an External function very simply" _
       & "\n\n             Wait to continue")
' ===================================================================
Print "\n\nSINGLE + DOUBLE in DOUBLE    both passed ByRef"
Print     "-------------------------"
' FB DECLARE CODE
' ''RQEXPORT function SinglePlusDouble_3:Single (sng1:Single:ByRef, dbl1:Double:ByRef)
' Function SinglePlusDouble_3 (ByRef sng1 As Single, ByRef dbl1 As Double) As Single
sng = 333.333
dbl = 222.222
Print " in RQ: sng  before call: ";sng
Print " in RQ: dbl  before call: ";dbl
iRet = SinglePlusDouble_3 (sng, dbl)
Print " in RQ: Result: SinglePlusDouble_3 (sng, dbl): ";iRet
Print " in RQ:   sng after call: ";sng
Print " in RQ:   dbl after call: ";dbl;"  (cannot be set even passed ByRef)"
'
ShowMessage ("Here both Single and Double are passed ByRef" _
         & "\nYou should notice that Double and Singles have" _
         & "\nbeen passed to an External function very simply" _
       & "\n\n             Wait to continue")
' ===================================================================
Print "\n\nimmediat SINGLE + immediat DOUBLE in DOUBLE"
Print     "-------------------------------------------"
' FB DECLARE CODE
' ''RQEXPORT function SinglePlusDouble_4:Single (sng1:Single, dbl1:Double)
' Function SinglePlusDouble_4 (sng1 As Single ptr, dbl1 As Double ptr) As Single
iRet = SinglePlusDouble_4 (1.111, 2.222)
Print " in RQ: Result = SinglePlusDouble_4 (1.111, 2.222): ";iRet
'
ShowMessage ("Here both arguments are immediat values" _
         & "\nImmediat values cannot be used with Arguments" _
         & "\npassed ByRef. It's a RapidQ limitation." _
       & "\n\n             Wait to continue")
' ===================================================================
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
' ===================================================================
'
