'
' ===================================================================
' RAPIDQ  byteCode Launcher                       Jan 2007    Jacques
' ===================================================================
'
''pre cmd norun noenc opt
$Include "RQ_NullTiny.Inc"
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Print "\n\n\nBig math again:\n\nBcc AddInt(1, 2): ";AddInt (1, 2)
'
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
' ===================================================================
'
