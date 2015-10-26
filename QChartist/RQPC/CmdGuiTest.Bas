'
''AUTO_PRE --------------------------------
''pre cmd DirIcon
DefStr sBuildCount = "0.001" ''pre + 0.001 3
DefStr sFirstCompiled = "04-07-2007  23:53:10"
''pre end
''END_AUTO_PRE ----------------------------
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Declare Sub OnClose_frmMyForm
'
Create frmMyForm As QForm
    Center
    Width = 800
    height = 500
    Caption = Application.Exename & " - READING ALL RECIEVED COMMAND LINE ARGUMENTS"
    AutoScroll = False
    OnClose = OnClose_frmMyForm
    Create rchWin AS QRichEdit  ' will disply the received datas
        Align = 5
        Font.Name = "courier"
        Font.Size = 8
        Font.Color = &H800000
        Width = 200
        Height = 200
        ReadOnly = True
        WordWrap = False
        ScrollBars = ssBoth
        HideSelection = False
        PlainText = True
    End Create
End Create
'
' --------------------------------------------------------------------
' New Code API Call that lets RapidQ programs minimize to the task bar
DECLARE FUNCTION SetWindowLong LIB "user32" ALIAS "SetWindowLongA" (hWnd AS LONG, _
                                               nIndex AS LONG, dwNewLong AS LONG) AS LONG
'      ----- API Constants and Functions
CONST GWL_HWNDPARENT = (-8)                   'Minimize to task bar
CONST HWND_DESKTOP = 0
setwindowlong(frmMyForm.handle, GWL_HWNDPARENT, HWND_DESKTOP)
setwindowlong(application.handle, GWL_HWNDPARENT, frmMyForm.handle)
' --------------------------------------------------------------------
'
'' *************************************
frmMyForm.Show
'' *************************************
rchWin.Addstring (" - ENUMERATES THE COMMAND LINE ARGUMENTS -\n"_
                 &"   =====================================\n")
DefInt N = 0
While Command$(N) <> ""
    rchWin.Addstring ("Cmds(" & Str$(N) & ") = " & Command$(N))
    N++
Wend
rchWin.Addstring ("\n\n      ***  RQ_Finished  ***")
'
' *************************************
frmMyForm.Visible = False
frmMyForm.ShowModal
' *************************************
Sub OnClose_frmMyForm
    Application.Terminate
    End
End Sub
'
