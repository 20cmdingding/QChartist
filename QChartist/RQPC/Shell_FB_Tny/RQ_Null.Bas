'
' ===================================================================
' RAPIDQ  byteCode Launcher                       nov 2006    Jacques
' ===================================================================
'
$Include "RQ_NullTiny.Inc"
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Print "\n\n\nFB AddInt: ";AddInt (1, 2)
'
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
' ===================================================================
'
