'
' ------------------------------------------------------------------
' RQPC BCC example:  RapidQ External CallBack      Jan 2007, Jacques
' ------------------------------------------------------------------
''pre cmd con enc tiny run DirIcon opt kill nobk CallBack.Bpp noDone printf upx output
DefStr sBuildCount    =       "0.009"  ''pre + 0.001 3
DefStr sCompileTime   =    "21:57:17"  ''pre time$
DefStr sCompileDate   =  "02-28-2007"  ''pre date$
DefStr FirstCompiled  =  "01-08-2007  21:06:21"
''pre end
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" _
    (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long
'
Declare Sub OnClose_frmCallBackTest
Declare Sub OnClic_AnyMenu (Sender As QMenuItem)
'
Create frmCallBackTest As QForm
    Center
    Width  = 800
    height = 800
    Caption = "Multiple CallBack Test"
    AutoScroll = False
    OnClose = OnClose_frmCallBackTest
    Create rchWinTop AS QRichEdit
        Align = alTop
        Color = &HBEFCCF
        Height = 400
        Font.Name = "courier"
        ReadOnly = False
        WordWrap = False
        ScrollBars = ssBoth
        HideSelection = False
        PlainText = True
        Text = "NoMouse"
    End Create
    Create rchWinBottom AS QRichEdit
        Align = 5
        Font.Name = "courier"
        ReadOnly = False
        WordWrap = False
        ScrollBars = ssBoth
        HideSelection = False
        PlainText = True
    End Create
    Create mnuMain AS QMAINMENU
        Create mnuMouseTopOnOff AS QMENUITEM
            Caption = "&MouseTop_On"
            OnClick = OnClic_AnyMenu
        End Create
        Create mnuMouseBottomOnOff AS QMENUITEM
            Caption = "&MouseBottom_On"
            OnClick = OnClic_AnyMenu
        End Create
    End Create
End Create
' *************************************
frmCallBackTest.Show
' *************************************
rchWinTop.LoadFromFile ("RQ_CB_NoMouse.Bas")
rchWinBottom.LoadFromFile ("RQ_CB_NoMouse.Bas")
'
InitSubClass
'
ShowMessage ("THE EFFECT OF THIS RICHEDIT SUBCLASSINGS" _
       & "\n\nIS THAT MOUSE HAS NO EFFECT IN RICHEDIT" _
       & "\n\nCLIC MENU \"MOUSE OFF\" TO RESTABLISH MOUSE" _
       & "\n\nIN UPPER/LOWER WINDOW.")
' ------------------------------------------------
Print "\nRapidQ Print ... "
' *************************************
frmCallBackTest.Visible = False
frmCallBackTest.ShowModal
' *************************************
' Mouse On/Off in Upper/Lower RichEdit Window
Sub OnClic_AnyMenu (Sender As QMenuItem)
    Select Case Sender.Handle
        ' Mouse On/Off in Upper RichEdit Window
        Case mnuMouseTopOnOff.Handle
            SubClassTop (rchWinTop.Handle)
            If mnuMouseTopOnOff.Caption = "&MouseTop_Off" Then
                mnuMouseTopOnOff.Caption = "&MouseTop_On"
            Else
                mnuMouseTopOnOff.Caption = "&MouseTop_Off"
            End If

        ' Mouse On/Off in Lower RichEdit Window
        Case mnuMouseBottomOnOff.Handle
            SubClassBottom (rchWinBottom.Handle)
            If mnuMouseBottomOnOff.Caption = "&MouseBottom_Off" Then
                mnuMouseBottomOnOff.Caption = "&MouseBottom_On"
            Else
                mnuMouseBottomOnOff.Caption = "&MouseBottom_Off"
            End If
    End Select
End Sub
'
Sub OnClose_frmCallBackTest
    Application.Terminate
    End
End Sub
'
