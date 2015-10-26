'
' -------------------------------------------------------------------
'  ByteCode for Demos                             Nov 2006,  Jacques
' -------------------------------------------------------------------
'
' ''pre cmd Tiny opt nokill nobk
'
SetConsoleTitle (Application.ExeName & "   V" & BuildCount)
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Print "             I am the ByteCode"
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
'
