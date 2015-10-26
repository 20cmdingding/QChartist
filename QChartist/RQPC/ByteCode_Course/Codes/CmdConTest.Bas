'
' -------------------------------------------------------------------
' ByteCode Test: Read Console Command Line      Nov 2006,     Jacques
' -------------------------------------------------------------------
'
' CONSOLE CODE READING THE COMMAND LINE ARGUMENTS RECEIVED
'
' ''pre cmd Tiny opt noKIll nobk
SetConsoleTitle (Application.ExeName & " CONSDOLE READING RECIEVED COMMAND LINE ARGUMENTS")
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"

Print (" - ENUMERATES THE COMMAND LINE ARGUMENTS -\n"_
      &"   =====================================\n")
'
DefInt N = 0

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
