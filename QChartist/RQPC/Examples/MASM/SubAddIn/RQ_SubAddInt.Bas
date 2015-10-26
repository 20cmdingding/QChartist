'
' -------------------------------------------------------------------
' RQPC MASM DEMO: SubInt, AddInt                  nov 2006   Jacques
' -------------------------------------------------------------------
'
''pre cmd Tiny Con opt run Kill noKb SubAddInt.Asm NoDone Icon1.Ico
DefStr BuildCount     =       "0.009"  ''pre + 0.001 3
DefStr FirstCompiled  =  "12-18-2006  21:38:37"
''pre end
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Declare Sub OnClose_frmRTL_Test

Create frmRTL_Test As QForm
    Center
    Width = 600
    height = 150
    Caption = "Run Time Link Test V" &  BuildCount
    AutoScroll = False
    OnClose = OnClose_frmRTL_Test
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
' *************************************
frmRTL_Test.Show
' *************************************
'
rchWin.Addstring  "Call AddInt (111111, 222222) = " & Str$(AddInt (111111, 222222))
rchWin.Addstring  "Call AddInt (ptrAddInt, 111111, 333333, 0, 0) = " & Str$(cwp_AddInt (ptrAddInt, 111111, 333333, 0, 0))
'
rchWin.Addstring  "Call cwp_SubInt (222222, 111111) = " & Str$(SubInt (222222, 111111))
rchWin.Addstring  "Call cwp_SubInt (ptrSubInt, 333333, 111111, 0, 0) = " & Str$(cwp_SubInt (ptrSubInt, 333333, 111111, 0, 0))
'
Print "Great math once again :)"
' *************************************
frmRTL_Test.Visible = False
frmRTL_Test.ShowModal
' *************************************
'
Sub OnClose_frmRTL_Test
    Application.Terminate
End Sub
'
