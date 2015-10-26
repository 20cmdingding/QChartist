'
''AUTO_PRE --------------------------------
''pre cmd DirIcon
DefStr sFirstCompiled = "04-07-2007  23:39:28"
''pre end
''END_AUTO_PRE ----------------------------
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"

Print (" - ENUMERATES THE COMMAND LINE ARGUMENTS -\n"_
      &"   =====================================\n")
'
DefInt N = 0
'
While Command$(N) <> ""
    Print ("Cmds(" & Str$(N) & ") = " & Command$(N))
    N++
Wend
'
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n    ***  FINISHED  ***     CR to QUIT \n\n", sExit
Application.Terminate
End
'
