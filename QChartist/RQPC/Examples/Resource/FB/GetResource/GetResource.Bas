'
' -----------------------------------------------------------------------------
' RQPC  FREEBASIC  RESOURCE  DEMO                  February 5th, 2007  Jacques
' -----------------------------------------------------------------------------
''pre cmd nocon enc tiny run kill nobk null.Fbb FB_GetRsrc.Rc opt DirIcon nodone
DefStr sBuildCount    =       "0.006"  ''pre + 0.001 3
''pre end
' -----------------------------------------------------------------------------
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
' ---------------------------------------------------------
Declare Function FindResource Lib "KERNEL32" Alias "FindResourceA" (ByVal hLib As Long, _
                                    ByVal strName As Long, ByVal strType As Long) As Long
Declare Function SizeofResource Lib "KERNEL32"  Alias "SizeofResource" _
                                  (ByVal hModule As Long, ByVal hResInfo As Long) As Long 
Declare Function LoadResource Lib "Kernel32" Alias "LoadResource" (ByVal hLib As Long, ByVal hRes As Long) As Long
Declare Function LockResource Lib "KERNEL32" Alias "LockResource" (ByVal hRes As Long) As Long
' ---------------------------------------------------------
'
Declare Sub OnClic_AnyMenu (Sender As QMenuItem)
Declare Sub OnClose_frmEnumResources
'
Create frmEnumResources As QForm
    Center
    Width = 1000
    height = 800
    Caption = "GetResource in current Module: " & Application.Exename & " (v" & sBuildCount & ")"
    AutoScroll = False
    OnClose = OnClose_frmEnumResources
    Create rchWin AS QRichEdit
        Align = 5
        Font.Name = "courier"
        Font.Size = 12
        Font.Color = &H800000
        ReadOnly = True
        WordWrap = False
        ScrollBars = ssBoth
        HideSelection = False 
        PlainText = True
    End Create
End Create
'
' ENUM RESOURCES TYPES
' ====================
'RT_CURSOR                1
'RT_BITMAP                2
'RT_ICON                  3
'RT_MENU                  4
'RT_DIALOG                5
'RT_STRING                6
'RT_FONTDIR               7
'RT_FONT                  8
'RT_ACCELERATOR           9
'RT_RCDATA               10
'RT_MESSAGETABLE         11
'RT_GROUP_CURSOR         12
'RT_GROUP_ICON           14
'RT_VERSION              16
'RT_DLGINCLUDE           17
'RT_PLUGPLAY             19
'RT_VXD                  20
'RT_ANICURSOR            21
'RT_ANIICON              22
'RT_HTML                 23
'
' Resource set in Masm_2.Rc with:
' ------------------------------
' BAS_CODE RCDATA "GetResource.Bas"
'
' Resource Name and Type
Const FB_RCDATA = 6868        ' Type of resource (as RT_ above)
DefInt hModule = 0           ' Zero for this application
DefStr sName = "BAS_CODE"    ' Name or ID of the resource
' Get Resource Size and Address (=handle)
DefInt hResInfo = FindResource (hModule, VarPtr(sName), FB_RCDATA)
DefInt iResSize = SizeofResource (hModule, hResInfo)
DefInt hRes     = LoadResource (hModule, hResInfo)
DefInt ptrRes   = LockResource (hRes)
'
rchWin.Addstring "\n  Get Resource Position and Size" _
               & "\n  ------------------------------" _
               & "\n  hRes Info: " & Str$(hResInfo) _
               & "\n  iRes Size: " & Str$(iResSize) _
               & "\n  hResource: " & Str$(hRes) _
               & "\n    ptrRsrc: " & Str$(ptrRes)

' Copy resource in a string to display it
DefStr sData = Space$(iResSize)
MemCpy (VarPtr(sData), hRes, iResSize)
'
rchWin.Text = rchWin.Text & _
        & "\n\n\n" & String$(80, "=") _
            & "\nContent of Resource \"BAS_CODE\":" _
            & "\n" & String$(80, "=") _
            & "\n" & sData _
            & "\n" & String$(80, "=") _
            & "\nEnd of Resource \"BAS_CODE\":" _
            & "\n" & String$(80, "=")
'
' *************************************
frmEnumResources.ShowModal
' *************************************
'
Sub OnClose_frmEnumResources
    Application.Terminate
End Sub
'
