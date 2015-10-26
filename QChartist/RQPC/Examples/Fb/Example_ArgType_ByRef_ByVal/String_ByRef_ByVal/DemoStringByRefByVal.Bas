'
' ===================================================================
' RQPC FB DEMO: String ByRef ByVal with FB       Nov 2006    Jacques
' -------------------------------------------------------------------
$Include "DemoStringByRefByValTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated tiny run DemoStringByRefByVal.Fbb noDone con Pencil03.ico Kill noBK
DefStr BuildCount    =       "0.011"  ''pre + 0.001 3
''pre end
SetConsoleTitle (Application.ExeName & "   V" & BuildCount)
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
DefStr s1
DefInt iCount
' ===================================================================
Print "STRING PASSED BYREF"
Print "-------------------"
' FB DECLARE CODE
' ''RQEXPORT function ReplaceCharByRef (InString:string:byref, ToReplace:String, ReplaceBy:String)
' Function ReplaceCharByRef (ptrStr As byte ptr, ptrTo As byte ptr, ptrBy As byte ptr) As Long
s1 = "iuyuiyiuyiuyiuyiuyiuyiuyiuyiuyiuyiuyiuyoiuoiuoiu"
Print " in RQ: ByRef Before: ";s1
iCount = ReplaceCharByRef (s1, "i", "X")
Print " in RQ: ByRef After: ";s1
Print " in RQ: ";iCount;"  \"i\"  replaced by \"X\""
'
ShowMessage ("You should notice that the Source String" _
         & "\nhas been modified thanks to ByRef in the" _
         & "\n''RQEXPORT declaration in the FB code." _
       & "\n\n           Wait to continue")
' ===================================================================
Print "\n\nSTRING PASSED BYVAL"
Print     "-------------------"
' FB DECLARE CODE
' ''RQEXPORT function ReplaceCharByVal (InString:string, ToReplace:String, ReplaceBy:String)
' FB Function ReplaceCharByVal (ptrStr As byte ptr, ptrTo As byte ptr, ptrBy As byte ptr) As Long
s1 = "iuyuiyiuyiuyiuyiuyiuyiuyiuyiuyiuyiuyiuyoiuoiuoiu"
Print " in RQ: Before: ";s1
iCount = ReplaceCharByVal (s1, "i", "Z")
Print " in RQ:  After: ";s1
Print " in RQ: ";iCount;"  \"i\"  replaced by \"Z\""

ShowMessage ("You should notice that the source string" _
         & "\nhas  *NOT*  been modified: no ByRef (= ByVal)" _
         & "\nin the ''RQEXPORT declaration in the FB code." _
       & "\n\n             Wait to continue")


' ===================================================================
Print "\n\nSTRING PASSED BYVAL  result returned in string"
Print     "-------------------"
' FB DECLARE CODE
' ''RQEXPORT function ReplaceCharAsString:String (InString:String, ToReplace:String, ReplaceBy:String)
' Function ReplaceCharAsString (ptrStr As byte ptr, ptrTo As byte ptr, ptrBy As byte ptr) As Long
s1 = "iuyuiyiuyiuyiuyiuyiuyiuyiuyiuyiuyiuyiuyoiuoiuoiu"
Print " in RQ:   s1 Before: ";s1
DefStr sOut = ReplaceCharAsString (s1, "i", "Z")
Print " in RQ:   s1  After: ";s1
Print " in RQ:  Out String: ";sOut

ShowMessage ("You should notice that the source string" _
         & "\nhas  *NOT*  been modified: no ByRef (= ByVal)" _
         & "\nin the ''RQEXPORT declaration in the FB code." _
       & "\n\n             Wait to continue")

' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
' ===================================================================
'
