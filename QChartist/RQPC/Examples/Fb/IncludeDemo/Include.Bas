'
' -------------------------------------------------------------------
' RQPC FB EXAMPLE: ''INCLUDE                      nov 2006   Jacques
' -------------------------------------------------------------------
'
' use ''INCLUDE in an external file, here TestIncl.Fbb
'
$Include "IncludeTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated tiny opt run nocon External.Fbb nodone Icon_2686.ico Kill nobk
DefStr BuildCount     =      "0.0016"  ''pre + 0.0001 4
DefStr FirstCompiled  =  "12-18-2006  22:38:37"
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
' Show FB Datas Exported and Initialised
' --------------------------------------
DefStr sTmp = Space$(50)
'
memcpy (VarPtr(sTmp), ptrMyString, 43)
rchWin.Addstring   "\n   MyString: " & Left$(sTmp, Instr(sTmp, Chr$(0)) - 1)
'
memcpy (VarPtr(sTmp), ptrMyBuffer_1, 43)
rchWin.Addstring   "\n MyBuffer_1: " & sTmp
'
memcpy (VarPtr(sTmp), ptrMyBuffer_2, 43)
rchWin.Addstring   "\n MyBuffer_2: " & sTmp
'
memcpy (VarPtr(sTmp), ptrxMyString, 43)
rchWin.Addstring   "\n  xMyString: " & Left$(sTmp, Instr(sTmp, Chr$(0)) - 1)
'
memcpy (VarPtr(sTmp), ptrxMyBuffer_1, 43)
rchWin.Addstring   "\nxMyBuffer_1: " & sTmp
'
memcpy (VarPtr(sTmp), ptrxMyBuffer_2, 43)
rchWin.Addstring   "\nxMyBuffer_2: " & sTmp
'
' *************************************
frmRTL_Test.Visible = False
frmRTL_Test.ShowModal
' *************************************
'
Sub OnClose_frmRTL_Test
    Application.Terminate
End Sub
'
