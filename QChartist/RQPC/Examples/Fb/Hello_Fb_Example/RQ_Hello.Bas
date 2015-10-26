'
' -------------------------------------------------------------------
' RQPC FB EXAMPLE: ''INCLUDE                      nov 2006   Jacques
' -------------------------------------------------------------------
$Include "RQ_HelloTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated run enc noopt exe con Hello.Fbb NoDone DirIcon kill
''pre end
SetConsoleTitle (Application.ExeName & "   V" & BuildCount)
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
' Call FB Hello
Hello
'
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
'
