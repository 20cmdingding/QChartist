'
' -------------------------------------------------------------------
' RQPC  DEMO  EXAMPLE      BCC AddInt            Jan 2007,   Jacques
' -------------------------------------------------------------------
'
''pre cmd tiny opt enc run Kill Test.Bpp NoDone nocon diricon 
DefStr BuildCount     =       "0.003"  ''pre + 0.001 3
DefStr FirstCompiled  =  "03-08-2007  21:22:18"
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
    height = 200
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

rchWin.AddString "ptrNameAddress: " & Str$(ptrNameAddress)
rchWin.AddString "lenNameAddress: " & Str$(lenNameAddress)
rchWin.AddString "RTL string: " & sNameAddress
rchWin.AddString " ptrTestAddInt: " & Str$(ptrTestAddInt)
'
' Call Gcc Function
' -----------------
rchWin.Addstring  "Call TestAddInt (111111, 222222) = " & Str$(TestAddInt (111111, 222222))
rchWin.Addstring  ("Call cwp_TestAddInt (ptrTestAddInt, 111111, 222222) = " _
                              & Str$(cwp_TestAddInt (ptrTestAddInt, 111111, 222222, 0, 0)))
'
rchWin.Addstring  "Call TestSubInt (222222, 111111) = " & Str$(TestSubInt (222222, 111111))
rchWin.Addstring  ("Call cwp_TestSubInt (ptrTestSubInt, 111111, 222222) = " _
                              & Str$(cwp_TestSubInt (ptrTestSubInt, 111111, 222222, 0, 0)))
' Show Gcc Exported Datas
' -----------------------
DefStr sTmp0 = Space$(50)
memcpy (VarPtr(sTmp0), ptrMyString, 40)
rchWin.Addstring "  MyString: " & Left$(sTmp0, Instr(sTmp0, Chr$(0)) - 1)
'
DefStr sTmp1 = Space$(50)
memcpy (VarPtr(sTmp1), ptrMyBuffer_1, 40)
rchWin.Addstring "MyBuffer_1: " & sTmp1
'
DefStr sTmp2 = String$(50, "x")  
memcpy (ptrMyBuffer_2, VarPtr(sTmp2), 45)
sTmp2 = Space$(50) & "//"
memcpy (VarPtr(sTmp2), ptrMyBuffer_2, 40)
rchWin.Addstring "MyBuffer_2: " & sTmp2
'
' *************************************
frmRTL_Test.Visible = False
frmRTL_Test.ShowModal
' *************************************
'
Sub OnClose_frmRTL_Test
    Application.Terminate
End Sub
' -------------------------------------------------------------------
'
