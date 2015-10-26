'
' -----------------------------------------------------------------------------
' RQPC  MASM  DIALOG  RESOURCE  DEMO               February 5th, 2007  Jacques
' -----------------------------------------------------------------------------
'
''pre cmd tiny run enc noopt exe con nobk Dlg.Asm Rsrc.Rc nodone DirIcon
DefStr BuildCount = "0.005" ''pre + 0.001 3
''pre end
SetConsoleTitle (Application.ExeName & "   V" & BuildCount)
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
ShowDialog
'
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
' -----------------------------------------------------------------------------
'
