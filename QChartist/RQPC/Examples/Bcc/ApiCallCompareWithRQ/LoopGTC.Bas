'
' -----------------------------------------------------------------------------
' RQPC BCC DEMO   Test Api Call Speed (GUI)         jan 13th,  2007    Jacques
'
' (I had to add 1.E9 rather than 1E9 ... great mystery ?)
' -----------------------------------------------------------------------------
''pre cmd tiny run opt LoopGTC.Bpp nodone exe nocon DirIcon Kill nobk
DefStr BuildCount = "0.011" ''pre + 0.001 3
DefStr FirstCompiled  = "01-13-2007  21:23:55"
''pre end
'
$RESOURCE FORM_ICO AS "Water.Ico"
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Declare Sub OnClose_frmCallApiSpeedTest
Declare Sub OnClic_AnyMenu (Sender As QMenuItem)
'
Create frmCallApiSpeedTest As QForm
    Center
    Width = 600
    height = 500
    IcoHandle = FORM_ICO
    Caption = "frmCallApiSpeedTest V_" & BuildCount
    AutoScroll = False
    OnClose = OnClose_frmCallApiSpeedTest
    Create rchWin AS QRichEdit
        Align = 5
        Font.Name = "courier"    
        Font.Size = 8
        Font.Color = &H800000
        ReadOnly = True
        WordWrap = False
        ScrollBars = ssBoth
        HideSelection = False 
        PlainText = True
    End Create
End Create
'
Sub GPrint (sText As String)
    rchWin.Addstring (sText)
End Sub
'
' *************************************
frmCallApiSpeedTest.Show
' *************************************
'
Declare Function GetTickCount Lib "kernel32" Alias "GetTickCount" () As Long
'
DefInt N, iCount
DefDbl ins
' -------------------------------------
DefSng sngCppNull, sngCppGTC, sngCppOneCall
iCount = 10000000
'
GPRINT " COMPARE SPEED CALL GetTickCount IN GCC AND RAPIDQ "
GPrint " -------------------------------------------------"
sngCppNull = Timer
LoopNull(iCount)
sngCppNull = Timer - sngCppNull
GPrint ("Cpp Null: " & Str$(sngCppNull) & "      (called " & Str$(iCount) & " Times)")
'
sngCppGTC = Timer
LoopGTC (iCount)
sngCppGTC = Timer - sngCppGTC - sngCppNull
sngCppOneCall = 1.E9 * sngCppGTC/iCount
'
GPrint "Cpp  GTC: " & Str$(sngCppGTC)   & "      (called " & Str$(iCount) & " Times)"
Gprint "One call: " & StrF$(sngCppOneCall, FFNUMBER, 9, 1) & " ns"
'
' -------------------------------------
DefDbl sngRqNull, sngRqGTC, sngRqOneCall
iCount = 100000
'
sngRqNull = Timer
For N = 1 To iCount
Next N
sngRqNull = Timer - sngRqNull
GPrint "\nRQ  Null: " & Str$(sngRqNull) & "      (called " & Str$(iCount) & " Times)"
'
sngRqGTC = Timer
For N = 1 To iCount
    GetTickCount
Next N
sngRqGTC = Timer - sngRqGTC - sngRqNull
sngRqOneCall = 1.E9 * sngRqGTC/iCount
'
GPrint "RQ   GTC: " & Str$(sngRqGTC) & "      (called " & Str$(iCount) & " Times)"
GPrint "One Call: " & StrF$(sngRqOneCall, FFNUMBER, 7, 0) & " ns"
' -------------------------------------
GPrint "\nCpp GetTickCount Call is  " & Strf$(sngRqOneCall/sngCppOneCall, FFNUMBER, 7, 2) _
                                                        & " faster than RapidQ"
' =============================================================================
'
GPRINT "\n COMPARE SPEED CALL CallWindowProc IN GCC AND RAPIDQ "
GPrint   " ---------------------------------------------------"
Declare Function CallWindowProc Lib "user32" Alias "CallWindowProcA" _
        (ByVal lpPrevWndFunc As Long, ByVal hWnd As Long, ByVal Msg As Long, _
                            ByVal wParam As Long, ByVal lParam As Long) As Long

DefSng sngCppCWP, sngCppOneCallCWP
iCount = 10000000
' ---- Cpp ---------------------------
sngCppCWP = Timer
LoopCWP (iCount)
sngCppCWP = Timer - sngCppCWP - sngCppNull
sngCppOneCallCWP = 1.E9 * sngCppCWP/iCount
'
GPrint "Cpp  CWP: " & Str$(sngCppCWP) & "      (called " & Str$(iCount) & " Times)"
Gprint "One call: " & StrF$(sngCppOneCallCWP, FFNUMBER, 9, 1) & " ns"
' ---- RAPIDQ -------------------------
DefDbl sngRqCWP, sngRqOneCallCWP
iCount = 100000
'
sngRqCWP = Timer
For N = 1 To iCount
    CallWindowProc (ptrCWP_Test, 0, 0, 0, 0)
Next N
sngRqCWP = Timer - sngRqCWP - sngRqNull
sngRqOneCallCWP = 1.E9 * sngRqCWP/iCount
'
GPrint "RQ   CWP: " & Str$(sngRqCWP) & "      (called " & Str$(iCount) & " Times)"
GPrint "One Call: " & StrF$(sngRqOneCallCWP, FFNUMBER, 7, 0) & " ns"
'
GPrint "\nCpp CallWindowProc Call is  " & Strf$(sngRqOneCallCWP/sngCppOneCallCWP, FFNUMBER, 7, 2) _
                                                        & " faster than RapidQ"
                                                        
GPRint "\n\n           FINISHED"
'
' *************************************
frmCallApiSpeedTest.Visible = False
frmCallApiSpeedTest.ShowModal
' *************************************
'
Sub OnClose_frmCallApiSpeedTest
    Application.Terminate
End Sub
'
