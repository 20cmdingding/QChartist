; ''RQEXPORT function CountChar (CountInString:String, CharToCount:STring)
.code
CountChar proc ptrStr:dword, ptrChar:dword, i3:dword, i4:dword
		LOCAL Count:dword
		mov Count, 0
		mov esi, ptrChar
		mov al, [esi]
		mov esi, ptrStr
		mov ah, [esi]
		.WHILE ah != 0
			.IF al == ah
				Inc Count
			.ENDIF
			Inc esi
			mov ah, [esi]
        .ENDW
		mov eax, Count
        ret 16
CountChar endp
