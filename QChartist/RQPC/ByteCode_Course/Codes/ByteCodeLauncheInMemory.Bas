'
' -------------------------------------------------------------------
'  ByteCode in Memory Launcher                  Nov 2006,     Jacques
' -------------------------------------------------------------------
'
''pre cmd Tiny opt nokill
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
' ---- RAPIDQ BYTECODE IN MEMORY LAUNCHER
Declare Function RQ_ExecuteMemory LIB "RAPIDQCC.Dll" _
            ALIAS "RQ_ExecuteMemory" (Memory As Long, _
            MemorySize As Long, Commands As Long, _
                                      Count As Long) As Long
Dim bcFile As QFileStream
DefInt bcSize
DefStr sByteCode

bcFile.Open("ByteCode.Bc", fmOpenRead)
    bcSize = bcFile.Size
    sByteCode = bcFile.ReadBinStr(bcSize)
bcFile.Close
RQ_ExecuteMemory(VARPTR(sByteCode), bcSize, 0, 0)
'
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
'
