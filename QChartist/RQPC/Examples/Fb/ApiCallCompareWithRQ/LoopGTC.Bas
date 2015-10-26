'
' -----------------------------------------------------------------------------
' RQPC FreeBasic DEMO   Test Api Call Speed (GUI)    jan 13th,  2007   Jacques
'
' (I had to add 1.E9 rather than 1E9 ... great mystery ?)
' -----------------------------------------------------------------------------
$Include "LoopGTCTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated tiny run opt LoopGTC.Fbb nodone exe nocon DirIcon Kill nobk
DefStr BuildCount = "0.014" ''pre + 0.001 3
DefStr FirstCompiled  = "01-13-2007  19:23:55"
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
DefSng sngFbbNull, sngFbbGTC, sngFbbOneCall
iCount = 10000000
'
GPRINT " COMPARE SPEED CALL GetTickCount IN FREEBASIC AND RAPIDQ "
GPrint " -------------------------------------------------------"
sngFbbNull = Timer
LoopNull(iCount)
sngFbbNull = Timer - sngFbbNull
GPrint ("Fbb Null: " & Str$(sngFbbNull) & "      (called " & Str$(iCount) & " Times)")
'
sngFbbGTC = Timer
LoopGTC (iCount)
sngFbbGTC = Timer - sngFbbGTC - sngFbbNull
sngFbbOneCall = 1.E9 * sngFbbGTC/iCount
'
GPrint "Fbb  GTC: " & Str$(sngFbbGTC)   & "      (called " & Str$(iCount) & " Times)"
Gprint "One call: " & StrF$(sngFbbOneCall, FFNUMBER, 9, 1) & " ns"
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
GPrint "\nFbb GetTickCount Call is  " & Strf$(sngRqOneCall/sngFbbOneCall, FFNUMBER, 7, 2) _
                                                        & " faster than RapidQ"
' =============================================================================
'
GPRINT "\n COMPARE SPEED CALL CallWindowProc IN FREEBASIC AND RAPIDQ "
GPrint   " ---------------------------------------------------------"
Declare Function CallWindowProc Lib "user32" Alias "CallWindowProcA" _
        (ByVal lpPrevWndFunc As Long, ByVal hWnd As Long, ByVal Msg As Long, _
                            ByVal wParam As Long, ByVal lParam As Long) As Long
'
DefSng sngFbbCWP, sngFbbOneCallCWP
iCount = 10000000
' ---- Fbb ---------------------------
sngFbbCWP = Timer
LoopCWP (iCount)
sngFbbCWP = Timer - sngFbbCWP - sngFbbNull
sngFbbOneCallCWP = 1.E9 * sngFbbCWP/iCount
'
GPrint "Fbb  CWP: " & Str$(sngFbbCWP) & "      (called " & Str$(iCount) & " Times)"
Gprint "One call: " & StrF$(sngFbbOneCallCWP, FFNUMBER, 9, 1) & " ns"

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
GPrint "\nFbb CallWindowProc Call is  " & Strf$(sngRqOneCallCWP/sngFbbOneCallCWP, FFNUMBER, 7, 2) _
                                                        & " faster than RapidQ"
'                                                        
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
