
.code
CWP_Test proto :dword,:dword,:dword,:dword
; ''RQEXPORT function CWP_Test ()
CWP_Test proc i1:dword, i2:dword, i3:dword, i4:dword
    ; do nothing
    ret 16
CWP_Test endp
;
; ''RQEXPORT function LoopGTC (LoopCount)
LoopGTC proc LoopCount:dword, i2:dword, i3:dword, i4:dword
    .WHILE LoopCount > 0
        INVOKE GetTickCount
        dec LoopCount
    .ENDW
    ret 16
LoopGTC endp
;
; ''RQEXPORT function LoopNull (LoopCount)
LoopNull proc LoopCount:dword, i2:dword, i3:dword, i4:dword
    .WHILE LoopCount > 0
        dec LoopCount
    .ENDW
    ret 16
LoopNull endp
;
; ''RQEXPORT function LoopCWP (LoopCount)
LoopCWP proc LoopCount:dword, i2:dword, i3:dword, i4:dword
    .WHILE LoopCount > 0
        INVOKE CallWindowProc, ADDR CWP_Test, 0, 0, 0, 0
        dec LoopCount
    .ENDW
    ret 16
LoopCWP endp
