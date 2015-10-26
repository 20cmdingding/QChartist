'
' ===================================================================
' RQPC MASM DEMO:   CountChar.Asm                Nov 2006    Jacques
' -------------------------------------------------------------------
''pre cmd tiny run CountChar.Asm nodone opt con Pencil03.ico Kill nobk
''pre end
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Print "From Masm: Count i: ";CountChar ("iuyuiyiuyiuyiuyiuyiuyiuyiuyiuyiuyiuyiuy", "i")
'
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
' ===================================================================
'
