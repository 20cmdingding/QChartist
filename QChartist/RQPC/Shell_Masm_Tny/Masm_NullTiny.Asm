;
; ===================================================================
; RAPIDQ  ASM  MASM     byteCode Launcher         nov 2006    Jacques
; + Run Time Linked (RTL) in RapidQ  full   MASM   Functions
; ===================================================================
; Executes a RapidQ Gui or Console bytecode appended to this executable
; The Console will always be Shown.
; 1024 command line arguments possible
; Icon of any size must be set in a resopurce file: rsrc.rc
; Compile me:RqTiny.Asm with
;    \masm32\bin\rc /v rsrc.rc
;    \masm32\bin\cvtres /machine:ix86 rsrc.res
;    \masm32\bin\ml /c /coff RqTiny.asm
;    \masm32\bin\Link /SUBSYSTEM:WINDOWS /OPT:NOREF RqTiny.obj rsrc.obj
; I am not a great window programmer, remarks at erdemaal@yahoo.fr
;
; This code will be modyfied by Rq PreCompiler cmd "Tinrebuild" to Create
; a Console or not, to encrypt bytecode or not and to select which
; version of RapidQ32.Dll to use. Then recompiled to obj, then relinked
; with your selected Icon .Obj file.
; ===================================================================
.386
.model flat,stdcall
option casemap:none
; -------------------------------------------------------------------
include \masm32\include\windows.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib
; ===================================================================
WinMain proto :DWORD,:DWORD,:DWORD,:DWORD
Add__NameAddress proto :dword,:dword
Int__2Str proto :dword,:dword
; ===================================================================
; ---- INITIALIZED VARIABLES ----
; -------------------------------
.data
Class__Name               db "RqTinyJP",0
App__Name                 db "RapidQTiny",0
msgTinyCaption            db "TINY EXE ERROR",0
msgTinyErrorLoadFile      db "CANNOT LOAD .EXE FILE",10,10,"I QUIT !",0
Func__Name                db "RQ_ExecuteMemory",0
; RTL variables
ptr__NameAddress          db "0123456789",0
iLen__NameAddress         db "0123456789",0
sPtr__NameAddress         db "ptrNameAddress",0
sLen__NameAddress         db "lenNameAddress",0
; -----------------------------------------------------
msgCantExecBc           db "CANNOT EXECUTE BYTECODE.  I QUIT !",0
sConsoleTitle           db "RapidQ Console",0
Read__Bytes               dd 1
; ---- NON INITIALIZED VARIABLES ----
; -----------------------------------
.data?
h__Instance               HINSTANCE ?
Command__Line             LPSTR ?
;
RQ_ExecuteMemory          dd ?
exe__Handle               dd ?
exe__Size                 dd ?
exe__Position             dd ?
bc__Position              dd ?
bc__Size                  dd ?
arg__c                    dd ?
arg__v                    dd 1024 dup (?)  ; max 1024 arguments in command line
s__Long                   db 128 dup (?)
ptr__WriteNameAddress     dd ?
len__NameAddress          dd ?
Name__Address             db 32768 dup (?) ; linker
; ===================================================================
.code
; ===================================================================
; ==== user bit =====================================================
; ===================================================================
;
; ==== user code: C:\Tiny_2006\RqPreCompiler\Distribution_01_01_2007_HNY\Masm_Tny_Shell\RQ_Null.Asm 
.code
; -------------------------------------------------------------------
; ''RQEXPORT function AddInt (iNumber1, iNumber2)
	  AddInt proc i1:DWORD, i2:DWORD, i3:DWORD, i4:DWORD
            mov eax, i1
            add eax, i2
            ret
      AddInt endp
; -------------------------------------------------------------------
;
; ==== end user code: C:\Tiny_2006\RqPreCompiler\Distribution_01_01_2007_HNY\Masm_Tny_Shell\RQ_Null.Asm
; ===================================================================
; ==== end of user bit ==============================================
; ===================================================================
.code
; ===================================================================
start:
; ===================================================================
; RTL Function Header
; ===================================================================
mov eax, OFFSET Name__Address
mov ptr__WriteNameAddress, eax
mov [eax], byte ptr ';'
inc ptr__WriteNameAddress
mov len__NameAddress, 1
; ===================================================================
; Auto RTL for Functions and Datas here
; -------------------------------------
.data
    sAddInt db "AddInt",0
.code
invoke Add__NameAddress, ADDR sAddInt, ADDR AddInt
; -------------------------------------------------------------------
; user configured variables  console/encrypt/dllname/msgDllError
; -------------------------
.data
msgErrorRqDll           db "CANNOT RESOLVE RQ_ExecuteMemory in RapidQ32.Dll",10,10,\
                           "RapidQ32.Dll not found probably ?",10,10,"I QUIT !",0
flag__Console           dd 1
flag__Encrypt           dd 0
lib__Name               db "RapidQ32.Dll",0
.code
; ===================================================================
; Set RTL Environment Variable
; ----------------------------
invoke Int__2Str, ADDR ptr__NameAddress, ADDR Name__Address
invoke Int__2Str, ADDR iLen__NameAddress, len__NameAddress
;
invoke SetEnvironmentVariable, ADDR sLen__NameAddress, ADDR iLen__NameAddress
invoke SetEnvironmentVariable, ADDR sPtr__NameAddress, ADDR ptr__NameAddress
; ===================================================================
;
      invoke GetModuleHandle, NULL
      mov    h__Instance, eax
      invoke GetCommandLine
      mov    Command__Line, eax
      invoke WinMain, h__Instance,NULL,Command__Line, SW_SHOWDEFAULT
      invoke ExitProcess, eax
;
WinMain proc hInst:HINSTANCE,hPrevInst:HINSTANCE,CmdLine:LPSTR,CmdShow:DWORD
      LOCAL wc:WNDCLASSEX
      LOCAL msg:MSG
      LOCAL hwnd:HWND
      LOCAL hRQ_Dll:DWORD
      mov   wc.cbSize,SIZEOF WNDCLASSEX
      mov   wc.style, CS_HREDRAW or CS_VREDRAW
      mov   wc.lpfnWndProc, OFFSET Wnd__Proc
      mov   wc.cbClsExtra,NULL
      mov   wc.cbWndExtra,NULL
      push  h__Instance
      pop   wc.hInstance
      mov   wc.hbrBackground,COLOR_WINDOW+1
      mov   wc.lpszMenuName,NULL
      mov   wc.lpszClassName,OFFSET Class__Name
      invoke LoadIcon,NULL,IDI_APPLICATION
      mov   wc.hIcon,eax
      mov   wc.hIconSm,eax
      invoke LoadCursor,NULL,IDC_ARROW
      mov   wc.hCursor,eax
; ===================================================================
; ==== RQ_EXECUTEFILE CODE ==========================================
; ===================================================================
   ; Rewrites CommandLine to fit created argc and argv
      call CL2ArgcArgv
   ; Resolve RQ_ExecuteMemory
   ; -----------------------------------------------------
      ; Load RapidQ32.Dll
      invoke LoadLibrary,ADDR lib__Name
      mov hRQ_Dll, eax
      ; Resolve RQ_ExecuteFile
      invoke GetProcAddress,hRQ_Dll,ADDR Func__Name
      mov RQ_ExecuteMemory, eax
      .IF eax == 0
            invoke MessageBox, 0, ADDR msgErrorRqDll, ADDR msgTinyCaption, 0
            invoke ExitProcess, 0
      .ENDIF
   ; Load a copy of file .exe in memory
      call Load__File
   ; Create or not a Console
      .IF flag__Console != 0
            invoke AllocConsole
      .ENDIF
   ; GetByteCodeLength       bc__Size dd , bc__Position dd
      mov eax, exe__Position
      add eax, exe__Size
      sub eax, 4
      mov edx, [eax]            ; edx = bytecode size
      add edx, 4                ; bytecode size + 4 byte of bcLength (must)
      mov bc__Size, edx
      sub edx, 4
      sub eax, edx              ; eax = bytecode pointer
      mov bc__Position, eax
   ;  Encrypt or not the Bytecode
      .IF flag__Encrypt != 0
            mov esi, bc__Position
            mov edx, bc__Size
            sub edx, 4                ; real bc size
            .WHILE edx > 3            ; (rol eax, 3  until byteleft < 4)
                  mov eax, [esi]
                  rol eax, 3
                  mov [esi], eax
                  sub edx, 4
                  add esi, 4
            .ENDW
      .ENDIF
   ; Call RapidQ32.Dll/RQ_ExecuteMemory
      ; push arg_4 = nbr of arguments in cmdline
      push dword ptr arg__c
      ; push arg_3 = pointer to array of args pointers  
      push (OFFSET arg__v + 4)    ; +4: skip arg0, it will be appended by RQ_ExecuteMemory
      ; push arg_2 = size of bytecode *WITH* the 4 bytes of size
      push bc__Size
      ; push arg_1 = bytecode position
      push bc__Position
      ;
      call RQ_ExecuteMemory
      inc eax
      .IF eax == 0  ; if error while executing bytecode (avoids session hang)
           invoke MessageBox, 0, ADDR msgCantExecBc, ADDR msgTinyCaption, 0
      .ENDIF

      invoke FreeConsole
      invoke FreeLibrary, hRQ_Dll
      invoke ExitProcess, 0
; ===================================================================
; ===================================================================
	  ret
WinMain endp
; ===================================================================
;
; -------------------------------------------------------------------
; ---- WndProc ------------------------------------------------------
; -------------------------------------------------------------------
Wnd__Proc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
      .IF uMsg==WM_DESTROY
            invoke PostQuitMessage,NULL
      .ELSE
            invoke DefWindowProc,hWnd,uMsg,wParam,lParam            
            ret
      .ENDIF
      xor eax,eax
      ret
Wnd__Proc endp
;
; -------------------------------------------------------------------
; ---- CmdLine to argc, arg[v] (replace space sep by 0 separator ...)
; double space separator = end of command line
; tabs are not separators
; -------------------------------------------------------------------
CL2ArgcArgv proc
      push esi
      push edi
      push ecx
;
      mov arg__c, 1
      mov ecx, OFFSET arg__v
      mov esi, Command__Line
      mov [ecx], esi     ; arg[0] = CmdLine[0]
      mov edi, esi
;
LoopInCmdLine:
      mov al, byte ptr [esi]
      ; ---- case     "   >>  copy all chars except  0
      .IF al == '"'        ; Look for next '"' or 0
            inc esi
            mov al, byte ptr [esi]
            .WHILE al != '"'
                  .IF al == 0
                       jmp ZeroFound
                  .ENDIF
                  mov byte ptr [edi], al
                  inc edi
                  inc esi
                  mov al, byte ptr [esi]
            .ENDW
            inc esi
            jmp LoopInCmdLine
      .ENDIF
      ; ---- Case    0   >>  EXIT LOOP
      cmp al, 0
      jz ZeroFound
      ; ---- Case    space  (=cmdline separator)
      .IF al == ' '
            mov byte ptr [edi], 0
            inc arg__c
            add ecx, 4
            inc edi          ; points next Agr[n]
            mov [ecx], edi
            dec edi
      .ELSE
            mov byte ptr [edi], al         
      .ENDIF
      inc edi
      inc esi
jmp LoopInCmdLine
;
ZeroFound:
      mov byte ptr [edi], 0
;
      pop ecx
      pop edi
      pop esi
      ret
CL2ArgcArgv endp
;
; -------------------------------------------------------------------
; ---- Load a copy of Exe in Memory ---------------------------------
; -------------------------------------------------------------------
Load__File proc
            mov exe__Position, 0
            invoke CreateFile,arg__v,GENERIC_READ,FILE_SHARE_READ,0,\
                                       OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,0
            inc eax
            je Error_Load__File
            dec eax
            mov exe__Handle, eax
            invoke GetFileSize,eax,0
            inc eax
            je Error_Load__File
            dec eax
            mov exe__Size, eax
            invoke GetProcessHeap
            mov ebx, exe__Size
            inc ebx                     ; Append a 0 char              
            ; No Need to free heap alloc, it's Freed at Process Close
            invoke HeapAlloc, eax, HEAP_GENERATE_EXCEPTIONS + HEAP_ZERO_MEMORY, ebx 
            ; on alloc error exception is generated
            mov exe__Position, eax
            invoke    ReadFile, exe__Handle, exe__Position, exe__Size, ADDR Read__Bytes,0
            invoke    CloseHandle, exe__Handle
            jmp No_Error
Error_Load__File:
            invoke MessageBox, 0, ADDR msgTinyErrorLoadFile, ADDR msgTinyCaption, 0
            invoke ExitProcess, 0
No_Error:
            mov eax, exe__Position            ; Return the memory block address
            ret
Load__File endp
;
; -------------------------------------------------------------------
; ---- Add__NameAddress ---------------------------------------------
; -------------------------------------------------------------------
Add__NameAddress proc ptrName:DWORD, Address:DWORD
; ---- write name
    pusha
    mov edi, ptr__WriteNameAddress
    mov esi, ptrName
    mov ecx, len__NameAddress
    mov al, [esi]
    .WHILE al != 0
       .IF ecx > 32750
            jmp Buffer__Full
       .ENDIF
       mov [edi], al
       inc edi
       inc ecx
       inc esi
       mov al, [esi]      
    .ENDW
    mov byte ptr [edi], ','
    inc edi 
    mov ptr__WriteNameAddress, edi
    inc ecx
    mov len__NameAddress, ecx
; ---- write address
    invoke Int__2Str, edi, Address
; ----
    add ptr__WriteNameAddress, 10
    mov edi, ptr__WriteNameAddress
    mov byte ptr [edi], ';'
; ----
    inc ptr__WriteNameAddress   
    add len__NameAddress, 11
    jmp EndAddName
; ----
Buffer__Full:
    popa
    jmp @F
          msgBufferNameFull db "NameAddress buffer exceed 32750 bytes ! See RqTiny.Asm",0
    @@:
    invoke MessageBox, 0, ADDR msgBufferNameFull, ADDR msgTinyCaption, 0
    invoke ExitProcess, 0
; ----
EndAddName:
    popa
    ret
Add__NameAddress endp
; -------------------------------------------------------------------
; Integer to String always 10 characters out
; ------------------------------------------
Int__2Str proc ptrStr:dword, nInt:dword
; 
	pusha
; ---- write string address (conversion) 
    mov edx, nInt
    mov ebx, 1000000000     
    mov edi, ptrStr
LoopInt__2Str:
    mov       eax,      edx
    xor       edx,      edx
    div       ebx
    
    add       eax,      48
    mov byte ptr [edi],    al
    inc       edi
    cmp       ebx,      1
        jz  EndInteger2String
            push      edx
                  mov       eax,      ebx
                  xor       edx,      edx
                  mov       ebx,      10
                  div       ebx
                  mov       ebx,      eax
            pop       edx
    jmp       LoopInt__2Str
EndInteger2String:
    popa
    ret
Int__2Str endp
; -------------------------------------------------------------------
end start
; ===================================================================
;
