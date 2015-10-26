;
; -----------------------------------------------------------------------
; -----------------------------------------------------------------------
; RQPC MASM HexToBin and BinToHex Datas Converter Jacques, jan 27th 2007
; -----------------------------------------------------------------------
; -----------------------------------------------------------------------
; In:
; ---
; 1st arg: pointer to the binary datas to convert to hexa
; 2nd arg: size of the binary datas in byte; ex: size of "3F" = 2
; 3rd arg: pointer to a buffer that will receive the Hex data
; 4th arg: 0
;
; Result:
; -------
; 0 = OK NO ERROR
; 1 = ERROR PTRHEX  = 0
; 2 = ERROR PTRBIN  = 0
; 4 = ERROR BINSIZE = 0
; ------------------------------
;
; ''RQEXPORT function BinToHex (ptrBin, binSize, ptrHex)
.code
BinToHex proc ptrBin:dword, binSize:dword, ptrHex:dword, a4:dword
    LOCAL iResult:dword
    pusha
    ;
    ; Check Inputs Validity
    ; --------------------
    .IF ptrBin == 0
        mov ebx, 2
        jz fini_shed
    .ENDIF
    mov esi, ptrBin
    ;
    .IF ptrHex == 0
        mov ebx, 1
        jz fini_shed
    .ENDIF
    mov edi, ptrHex
    ;
    .IF binSize == 0
        mov ebx, 4
        jz fini_shed
    .ENDIF
    mov ecx, binSize
    ;
    mov ebx, 0
    ;
    ; Convert Bin Datas to Hex
    ; ------------------------
    .WHILE ecx > 0
        mov al, [esi]
        mov ah, al
        ; highHex
        ; -------
        shr ah, 4          ; high byte only
        add ah, 48         ; "0"
        .IF ah > 57        ; "9"
            add ah, 7
        .ENDIF
        mov [edi], ah
        inc edi
        ; lowHex
        ; ------
        and al, 0Fh        ; get the low byte only
        add al, 48         ; same as for ah
        .IF ah > 57 
            add al, 7
        .ENDIF
        mov [edi], al
        inc edi
        ; next bin
        inc esi
        dec ecx
    .ENDW
fini_shed:
    ; set result
    ; ----------
    mov iResult, ebx
    popa
    mov eax, iResult
    ret 16
BinToHex endp
;
; -----------------------------------------------------------------------
; -----------------------------------------------------------------------
;
; In:
; ---
; 1st arg: pointer to the hexadecimal data
; 2nd arg: size of the hexadecimal data in byte size of "3F" = 2
; 3rd arg: pointer to a buffer that will receive the binarized hex data
; 4th arg: 0
;
; Result:
; -------
; 0 = OK NO ERROR
; 1 = ERROR PTRHEX  = 0
; 2 = ERROR PTRBIN  = 0
; 3 = ERROR HEXSIZE ODD/UNEVEN
; 4 = ERROR HEXSIZE = 0
; 5 = ERROR AT LEAST ONE NON HEX DIGIT FOUND
; ------------------------------------------
;
; ''RQEXPORT function HexToBin (ptrHex, hexSize, ptrBin)
HexToBin proc ptrHex:dword, hexSize:dword, ptrBin:dword, a4:dword
    LOCAL iResult:dword
    pusha
    ;
    ; Check Inputs Validity
    ; --------------------
    .IF ptrHex == 0       ; ebx = result = 1 =  error ptrhex = 0
        mov ebx, 1
        jz fini__shed
    .ENDIF
    mov esi, ptrHex
    ;
    .IF ptrBin == 0       ; ebx = result = 2 =  error ptrBin = 0
        mov ebx, 2
        jz fini__shed
    .ENDIF
    mov edi, ptrBin
    ;
    mov ebx, 3            ; ebx = result = 3 = error hexSize odd/uneven
    mov ecx, hexSize
    bt ecx, 0
    jc fini__shed
    ;
    .IF hexSize == 0      ; ebx = result = 4 =  error ptrBin = 0
        mov ebx, 4
        jz fini__shed
    .ENDIF
    mov ecx, hexSize
    ;
    mov ebx, 0            ; ebx = 0       all ok no error
    mov edx, 0
    ;
    ; Convert Hex Datas to Bin
    ; ------------------------
    .WHILE ecx > 0
        ;
        ; high_bin   in ah
        ; --------
        mov ah, [esi]
        sub ah, 48          ; "0"
        .IF ah > 9
            sub ah, 7
        .ENDIF
        test ah, 0F0h       ; digit no hex
        setnz dl
        shl ah, 4
        ;
        ; low_bin
        ; -------
        mov al, [esi+1]
        sub al, 48
        .IF al > 9
            sub al, 7
        .ENDIF
        test al, 0F0h       ; digit no hex
        setnz dh
        ;
        ; store bin
        ; ---------
        add ebx, edx        ; one digit no hex
        or al, ah
        mov [edi], al
        inc edi
        add esi, 2
        sub ecx, 2
    .ENDW
    ;
    ; set result in iResult
    ; ---------------------
    .IF ebx != 0
        mov ebx, 5          ; error non hex digit
    .ENDIF
fini__shed:
    mov iResult, ebx
    popa
    mov eax, iResult
    ret 16
HexToBin endp
; -----------------------------------------------------------------------
;
