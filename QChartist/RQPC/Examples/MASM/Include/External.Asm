; User Code: External.Asm
; -----------------------
.code
TestAddInt PROTO :DWORD,:DWORD,:DWORD,:DWORD  ; for local invoke
TestSubInt PROTO :DWORD,:DWORD,:DWORD,:DWORD  ; for local invoke
; -------------------------------------------------------------------
; ''RQEXPORT function TestAddInt (iNumber1, iNumber2)
	  TestAddInt proc i1:DWORD, i2:DWORD, i3:DWORD, i4:DWORD
            mov eax, i1
            add eax, i2
            ret
      TestAddInt endp
; -------------------------------------------------------------------
.code      ; !!!!   MANDATORY HERE   !!!!      cause of bugs
; ''INCLUDE TestIncl.Asm
.code
; ''RQEXPORT function TestSubInt (iNumber1, iNumber2)
      TestSubInt proc i1:DWORD, i2:DWORD, i3:DWORD, i4:DWORD
            mov eax, i1
            sub eax, i2
            ret
      TestSubInt endp
; -------------------------------------------------------------------
; USER DATAS
; -------------------------------------------------------------------
.data        ; in Data segment
; ''RQEXPORT data MyString
MyString     db "Masm Exported String in RQ", 0
; ''RQEXPORT data MyBuffer_1
MyBuffer_1   db 1024 dup ('a')
.data?       ; in BSS segment
; ''RQEXPORT data MyBuffer_2
MyBuffer_2   db 32768 dup (?)
; -------------------------------------------------------------------
