'
' -------------------------------------------------------------------
'  ByteCode File Launcher                      Nov 2006,     Jacques
' -------------------------------------------------------------------
''pre cmd Tiny opt nokill
'
SetConsoleTitle (Application.ExeName & "   V" & BuildCount)
$ESCAPECHARS ON
'
' ---- Rapidq Bytecode Laucher Code
Declare Function RQ_ExecuteFile Lib "RapidQ32.Dll" Alias "RQ_ExecuteFile" _
             (Filename As String, Commands As Long, Count As Long) As Long
    RQ_ExecuteFile("ByteCode.Bc", 0, 0)
' ----
' EXIT CONSOLE
DefStr sExit
Input "\n\n                   CR to QUIT \n\n", sExit
Application.Terminate
' -------------------------------------------------------------------
'

