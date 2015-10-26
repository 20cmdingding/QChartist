'
' -------------------------------------------------------------------
' FB ByteCode Launcher                              Nov 2006, Jacques
' -------------------------------------------------------------------
' ===================================================================
' Executes a RapidQ Gui or Console bytecode appended to this executable
' The Console will always be Shown.
' 1024 command line arguments possible
' Icon of any size must be set in a resource file: Icon.rc
' Compile me:FbRqTiny.Bas with
' c:\freebasic\fbc.exe -v -s gui -i c:\freebasic\inc 
'                            -p c:\freebasic\lib FbRqTiny.Bas Icon.Rc
'
' I am not a great window programmer, remarks at erdemaal@yahoo.fr
' ===================================================================
'
option explicit
option byval
#include once "windows.bi"
' ----------------------------
Dim Shared As String sRQ32DllName
' ----------------------------
Dim Shared w__Msg as MSG
Dim Shared w__cls as WNDCLASS
Dim Shared h__Wnd as HWND
' ----------------------------
Dim Shared Arg__v (0 To 1024) As Integer
Dim Shared Cmd__s (0 To 1024) As String
Dim Shared buf__Exe() As Byte
Dim Shared As Long Arg__c = 0, ptr__Argv, len__Exe, len__BC, ptr__BufExe, ptr__BC, i__Ret
Dim Shared As Integer hRq32DLL, ptrRQ_ExecuteMemory
' Shared because use less space in .exe  ???
' ----------------------------
sRQ32DllName            = "RapidQ32.Dll"
AllocConsole   ' will always show a console (same code for Gui and Console
'
declare function        WinMain     ( hInstance as HINSTANCE, _
                                      hPrevInstance as HINSTANCE, _
                                      szCmdLine as string, _
                                      iCmdShow as integer ) as integer

end WinMain( GetModuleHandle( null ), null, Command( ), 0)
' ---------------------------
function Wnd__Proc ( hWnd as HWND, _
                     wMsg as UINT, _
                     wParam as WPARAM, _
                     lParam as LPARAM ) as LRESULT
    function = 0

    select case( wMsg )
        case WM_CREATE
            exit function

        case WM_DESTROY
            PostQuitMessage( 0 )
            exit function
    end select

    function = DefWindowProc( hWnd, wMsg, wParam, lParam )

end function
' ---------------------------
function WinMain ( hInstance as HINSTANCE, _
                   hPrevInstance as HINSTANCE, _
                   szCmdLine as string, _
                   iCmdShow as integer ) as integer
    function = 0
    with w__cls
        .style         = CS_HREDRAW or CS_VREDRAW
        .lpfnWndProc   = @Wnd__Proc
        .cbClsExtra    = 0
        .cbWndExtra    = 0
        .hInstance     = hInstance
        .hIcon         = LoadIcon( NULL, IDI_APPLICATION )
        .hCursor       = LoadCursor( NULL, IDC_ARROW )
        .hbrBackground = GetStockObject( WHITE_BRUSH )
        .lpszMenuName  = NULL
        .lpszClassName = @"FbTinyJp"
    end with
'
' -------------------------------------------------------------------
' ByteCode 'Stuff'
' -------------------------------------------------------------------
' Command Line to Argc, Argv[]
' ----------------------------
While Command$(Arg__c) <> ""
    Cmd__s(Arg__c) = Command$(Arg__c)
    Arg__v(Arg__c) = StrPtr(Cmd__s(Arg__c))
    Arg__c = Arg__c + 1
Wend
ptr__Argv = @Arg__v(1)
'
' Load File in Buffer
' -------------------
open Command$(0) for binary as #1
    len__Exe = Lof(1)
    Redim buf__Exe (len__Exe + 16) As Byte
    ptr__BufExe = @buf__Exe(0)
    get #1, 0, buf__Exe(0), len__Exe
close #1
'
' Get ByteCode Length and Pointer
' ------------------------------
Asm
    ' Length
    mov esi, [ptr__BufExe]
    add esi, [len__Exe]
    sub esi, 4
    mov eax, [esi]
    mov [len__BC], eax
    ' Pointer
    mov esi, [ptr__BufExe]
    add esi, [len__Exe]
    sub esi, 4
    sub esi, [len__BC]
    mov [ptr__BC], esi
End Asm
'
' Execute ByteCode
' ----------------
If len__BC <> 0 Then
    hRq32Dll = LoadLibrary (sRQ32DllName)
    If hRq32Dll <> 0 Then
        ptrRQ_ExecuteMemory = GetProcAddress(hRq32Dll, "RQ_ExecuteMemory" )
        Asm
            push dword ptr [Arg__c]
            push dword ptr [ptr__Argv]
            mov eax, [len__BC]
            add eax, 4
            push eax
            push dword ptr [ptr__BC]
            Call dword ptr [ptrRQ_ExecuteMemory]
        End Asm
        dylibfree hRq32Dll
    Else
        MessageBox (0, "Cannot find DLL: " & sRQ32DllName & "\n\n   I QUIT", "ERROR FB RAPIDQ Tiny", 0)
    End If    
Else
    MessageBox (0,"No ByteCode Appended ! I Quit", "FB RapidQ Tiny Launcher", 0)
End If
FreeConsole
ExitProcess (0)
' -------------------------------------------------------------------
' -------------------------------------------------------------------
end function
'--------------------------------------------------------------------
'
