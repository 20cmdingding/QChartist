'
' -------------------------------------------------------------------
'  ByteCode in Memory Launcher Accept Cmd Line     Nov 2006,  Jacques
' -------------------------------------------------------------------
'
''pre cmd Tiny opt nokill
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Declare Function RQ_ExecuteMemory LIB "RAPIDQCC.Dll" _
            ALIAS "RQ_ExecuteMemory" (Memory As Long, _
            MemorySize As Long, Commands As Long, _
                                      Count As Long) As Long
Dim bcFile As QFileStream
DefInt bcSize
DefStr sByteCode

' CmdConTest.Bas >> displays received command line arguments
bcFile.Open("CmdConTest.Bc", fmOpenRead)
    bcSize = bcFile.Size
    sByteCode = bcFile.ReadBinStr(bcSize)
bcFile.Close

' Maximum 10 Command Line Arguments
DefInt ptrCmd(10), ArgCount = 0
DefStr Cmd(10)
While Command$(ArgCount) <> ""
    Cmd(ArgCount) = Command$(ArgCount)
        ptrCmd(ArgCount) = VarPtr(Cmd(ArgCount))
    Inc ArgCount
Wend
'
' The first Argument is dropped, it is the same as the second
RQ_ExecuteMemory(VARPTR(sByteCode), bcSize, VarPtr(ptrCmd(1)), ArgCount - 1)
'
' -------------------------------------------------------------
' EXIT CONSOLE
' ------------
DefStr sExit
Input "\n\n                    CR to QUIT \n\n", sExit
Application.Terminate
' -------------------------------------------------------------------
'
