;
.code
AddInt PROTO :DWORD,:DWORD,:DWORD,:DWORD  ; for local invoke
SubInt PROTO :DWORD,:DWORD,:DWORD,:DWORD  ; for local invoke
; -------------------------------------------------------------------
; ''RQEXPORT function AddInt (iNumber1, iNumber2)
	  AddInt proc i1:DWORD, i2:DWORD, i3:DWORD, i4:DWORD
            mov eax, i1
            add eax, i2
            ret
      AddInt endp
; -------------------------------------------------------------------
; ''RQEXPORT function SubInt (iNumber1, iNumber2)
      SubInt proc i1:DWORD, i2:DWORD, i3:DWORD, i4:DWORD
            mov eax, i1
            sub eax, i2
            ret
      SubInt endp
; -------------------------------------------------------------------
; USER DATAS
; -------------------------------------------------------------------
.data        ; in Data segment
; ''RQEXPORT data xMyString
xMyString     db "Masm Exported String in RQ", 0
; ''RQEXPORT data xMyBuffer_1
xMyBuffer_1   db 1024 dup ('a')
.data?       ; in BSS segment
; ''RQEXPORT data xMyBuffer_2
xMyBuffer_2   db 32768 dup (?)
; -------------------------------------------------------------------
