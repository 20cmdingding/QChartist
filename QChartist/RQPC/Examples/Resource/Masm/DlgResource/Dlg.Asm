; #########################################################################
; Adapted from an MASM Example
; #########################################################################

        ;=============
        ; Local macros
        ;=============
  
        szText MACRO Name, Text:VARARG
          LOCAL lbl
            jmp lbl
              Name db Text,0
            lbl:
          ENDM
          
        ;=================
        ; Local prototypes
        ;=================
        dlgProc PROTO :DWORD,:DWORD,:DWORD,:DWORD
        
    .data
        dlgname       db "TESTWIN",0
    .code
; #########################################################################
.code
; ''RQEXPORT function ShowDialog ()
ShowDialog proc i1:dword, i2:dword, i3:dword, i4:dword
        LOCAL hInstance
        invoke GetModuleHandle, NULL
        mov hInstance, eax
        
        ; -------------------------------------------
        ; Call the dialog box stored in resource file
        ; -------------------------------------------
        invoke DialogBoxParam,hInstance,ADDR dlgname,0,ADDR dlgProc,0

        ret 16
ShowDialog endp
; #########################################################################
dlgProc proc hWin   :DWORD,
             uMsg   :DWORD,
             wParam :DWORD,
             lParam :DWORD

      .if uMsg == WM_INITDIALOG
        szText dlgTitle,"Demo dialog box"
        invoke SendMessage,hWin,WM_SETTEXT,0,ADDR dlgTitle

      .elseif uMsg == WM_CLOSE
        invoke EndDialog,hWin,0

      .endif

    xor eax, eax
    ret

dlgProc endp
; ########################################################################

