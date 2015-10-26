
; -------------------------------------------------------------------
.code
; ''RQEXPORT function AddInt(i1, i2)
AddInt proc i1:DWORD, i2:DWORD, i3:DWORD, i4:DWORD
    mov eax, i1
    add eax, i2 
    ret 16
AddInt endp 
; -------------------------------------------------------------------    
; ''RQEXPORT function SubInt (i1, i2)
SubInt proc i1:DWORD, i2:DWORD, i3:DWORD, i4:DWORD
    mov eax, i1
    sub eax, i2 
    ret 16
SubInt endp
; -------------------------------------------------------------------
