'
' -------------------------------------------------------------------
' RQPC MASM DEMO Include, Data, Function          nov 2006   Jacques
' -------------------------------------------------------------------
'
''pre cmd tiny opt run nocon External.Asm nodone Icon_2686.ico nobk kill
DefStr BuildCount     =      "0.0021"  ''pre + 0.0001 4
DefStr FirstCompiled  =  "12-18-2006  21:38:37"
''pre end
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Declare Sub OnClose_frmRTL_Test
'
Create frmRTL_Test As QForm
    Center
    Width = 1000
    height = 700
    Caption = "Run Time Link Test V" &  BuildCount
    AutoScroll = False
    OnClose = OnClose_frmRTL_Test
    Create rchWin AS QRichEdit
        Align = 5
        Font.Name = "courier"
        Font.Size = 8
        Font.Color = &H800000
        ReadOnly = True
        WordWrap = True
        ScrollBars = ssBoth
        HideSelection = False
        PlainText = True
    End Create
End Create
'
' *************************************
frmRTL_Test.Show
' *************************************
' Call Exported Function
rchWin.Addstring "ptrNameAddress: " & Str$(ptrNameAddress) _
             & "\nLenNameAddress: " & Str$(lenNameAddress) _
             & "\n ptrTestAddInt: " & Str$(ptrTestAddInt) _
             & "\n ptrTestSubInt: " & Str$(ptrTestSubInt) _
             & "\n     ptrAddInt: " & Str$(ptrAddInt) _
             & "\n     ptrSubInt: " & Str$(ptrSubInt) _
             & "\n   ptrMyString: " & Str$(ptrMyString) _
             & "\n ptrMyBuffer_1: " & Str$(ptrMyBuffer_1) _
             & "\n ptrMyBuffer_2: " & Str$(ptrMyBuffer_2) _
             & "\n  ptrxMyString: " & Str$(ptrxMyString) _
             & "\nptrxMyBuffer_1: " & Str$(ptrxMyBuffer_1) _
             & "\nptrxMyBuffer_2: " & Str$(ptrxMyBuffer_2) _
           & "\n\n   NameAddress:\n    " & sNameAddress
'
rchWin.Addstring "\nCall TestAddInt (111111, 222222) = " & Str$(TestAddInt (111111, 222222))
rchWin.Addstring   "Call TestAddInt (ptrTestAddInt, 111111, 333333) = " _
                                         & Str$(cwp_TestAddInt (ptrTestAddInt, 111111, 333333, 0, 0))
'
rchWin.Addstring   "Call TestSubInt (222222, 111111) = " & Str$(TestSubInt (222222, 111111))
rchWin.Addstring   "Call TestSubInt (ptrTestSubInt, 333333, 111111, 0, 0) = " _
                                         & Str$(cwp_TestSubInt (ptrTestSubInt, 333333, 111111, 0, 0))
'
rchWin.Addstring "\nCall AddInt (111111, 222222) = " & Str$(AddInt (111111, 222222))
rchWin.Addstring   "Call AddInt (ptrAddInt, 111111, 333333) = " _
                                         & Str$(cwp_AddInt (ptrAddInt, 111111, 333333, 0, 0))
'
rchWin.Addstring   "Call SubInt (222222, 111111) = " & Str$(SubInt (222222, 111111))
rchWin.Addstring   "Call SubInt (ptrSubInt, 333333, 111111, 0, 0) = " _
                                         & Str$(cwp_SubInt (ptrSubInt, 333333, 111111, 0, 0))
'
' Show Exported Datas
DefStr sTmp0 = Space$(50)
memcpy (VarPtr(sTmp0), ptrMyString, 40)
rchWin.Addstring "\n  xMyString: " & Left$(sTmp0, Instr(sTmp0, Chr$(0)) - 1)
'
DefStr sTmp1 = Space$(50)    ' 1024 bytes in data segment initialised with 'a'
memcpy (VarPtr(sTmp1), ptrMyBuffer_1, 40)
rchWin.Addstring   "xMyBuffer_1: " & sTmp1
''
DefStr sTmp2 = String$(50, "x")
memcpy (ptrMyBuffer_2, VarPtr(sTmp2), 45)
sTmp2 = Space$(50) & "//"
memcpy (VarPtr(sTmp2), ptrMyBuffer_2, 40)
rchWin.Addstring   "xMyBuffer_2: " & sTmp2
'
' Show Exported Datas
DefStr sTmp3 = Space$(50)
memcpy (VarPtr(sTmp3), ptrxMyString, 40)
rchWin.Addstring "\n  xMyString: " & Left$(sTmp3, Instr(sTmp3, Chr$(0)) - 1)
'
DefStr sTmp4 = Space$(50)    ' 1024 bytes in data segment initialised with 'a'
memcpy (VarPtr(sTmp4), ptrxMyBuffer_1, 40)
rchWin.Addstring   "xMyBuffer_1: " & sTmp4
''
DefStr sTmp5 = String$(50, "x")
memcpy (ptrxMyBuffer_2, VarPtr(sTmp5), 45)
sTmp5 = Space$(50) & "//"
memcpy (VarPtr(sTmp2), ptrxMyBuffer_2, 40)
rchWin.Addstring   "MyBuffer_2: " & sTmp5
' *************************************
frmRTL_Test.Visible = False
frmRTL_Test.ShowModal
' *************************************
'
Sub OnClose_frmRTL_Test
    Application.Terminate
End Sub
'
