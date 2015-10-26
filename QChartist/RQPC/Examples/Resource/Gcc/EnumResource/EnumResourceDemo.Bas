'
' -----------------------------------------------------------------------------
' RQPC GCC ENUM RESOURCE DEMO                      February 6th, 2007  Jacques
'
' Inspired by: http://vbaccelerator.com/home/VB/Utilities/Icon_Extractor/
'                         VB6_Icon_Extractor_Source_Code_zip_mResource_bas.asp
' -----------------------------------------------------------------------------
''pre cmd nocon enc tiny run kill nobk null.Cpp Gcc_EnumRsrc.Rc opt DirIcon
DefStr sBuildCount    =       "0.005"  ''pre + 0.001 3
''pre end
' -----------------------------------------------------------------------------
' get the 2 following at http://erdemal.webhop.org/RapidQ/ManyRqCallBack.zip
' if you dont already have them
$Include "Functions\CallBack_3.Inc"
$Include "Functions\CallBack_4.Inc"
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
' ---------------------------------------------------------
Declare Function lstrlen Lib "kernel32" Alias "lstrlenA" (ByVal lpString As Long) As Long
Declare Function FindResource Lib "KERNEL32" Alias "FindResourceA" (ByVal hLib As Long, _
                                    ByVal strName As Long, ByVal strType As Long) As Long
Declare Function SizeofResource Lib "KERNEL32"  Alias "SizeofResource" _
                                  (ByVal hModule As Long, ByVal hResInfo As Long) As Long 
Declare Function LoadLibrary Lib "kernel32" Alias "LoadLibraryA" _
                                                  (ByVal lpLibFileName As String) As Long
Declare Function LoadLibraryEx Lib "kernel32" Alias "LoadLibraryExA" _
      (ByVal lpLibFileName As String, ByVal hFile As Long, ByVal dwFlags As Long) As Long
Declare Function EnumResourceNames Lib "kernel32" Alias "EnumResourceNamesA" _
          (ByVal hModule As Long, ByVal lpType As Long, ByVal lpEnumFunc As Long, _
                                                            ByVal lParam As Long) As Long
Declare Function EnumResourceTypes Lib "kernel32" Alias "EnumResourceTypesA" _
          (ByVal hModule As Long, ByVal lpEnumFunc As Long, ByVal lParam As Long) As Long
Declare Function GetLastError Lib "Kernel32" Alias "GetLastError" () As Long
Declare Function LoadResource Lib "Kernel32" Alias "LoadResource" (ByVal hLib As Long, _
                                                              ByVal hRes As Long) As Long
Declare Function LockResource Lib "Kernel32" Alias "LockResource" _
                                                             (ByVal hRes As Long) As Long
' ---------------------------------------------------------
'
Declare Sub OnClic_AnyMenu (Sender As QMenuItem)
Declare Sub OnClose_frmEnumResources
'
Create frmEnumResources As QForm
    Center
    Width = 1000
    height = 800
    Caption = "Enum_Resources in Module used to Create this Process: " & Application.Exename
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
    Create mnuMain AS QMAINMENU
        Create mnuEnumRes AS QMENUITEM
            Caption = "&ENUM_RESOURCES    "
            OnClick = OnClic_AnyMenu
        End Create
        Create mnuSelectModule AS QMENUITEM
            Caption = "&SELECT_MODULE    "
            OnClick = OnClic_AnyMenu
        End Create
        Create mnuClear AS QMENUITEM
            Caption = "&CLEAR    "
            OnClick = OnClic_AnyMenu
        End Create
    End Create
End Create
'
DefInt flagMenuBusy = False
DefStr sAppDir = Command$(0) - Application.Exename
Dim dlgOpenModule As QOpenDialog
dlgOpenModule.InitialDir = sAppdir
DefInt hModule = 0
'
' ENUM RESOURCES NAMES
' ====================
Function EnumResNamesProc(ByVal hMod As Long, ByVal lpszType As Long, _
                              ByVal lpszName As Long, ByVal lParam As Long) As Long
    DefStr sName
    DefInt iName, iLen, hResInfo, iResSize, hRes, ptrRes
    '
    If (lpszName And &HFFFF0000) = 0 Then
        ' resource number:
        iName = lpszName And &HFFFF
        sName = Str$(iName)
    Else
        ' resource string:
        iLen = lstrlen(lpszName)
        If (iLen > 0) Then
            sName = Space$(iLen)
            MemCpy (VarPtr(sName), lpszName, iLen)
        End If
    End If
    hResInfo = FindResource (hModule, lpszName, lpszType)
    iResSize = SizeofResource (hModule, hResInfo)
    hRes     = LoadResource (hModule, hResInfo)
    ptrRes   = LockResource (hRes)
    rchWin.Addstring ( "      Resource name: " & sName _
                   & "\n           hResInfo: " & Str$(hResInfo) _
                   & "\n               size: " & Str$(iResSize) _
                   & "\n               hRes: " & Str$(hRes) _
                   & "\n             ptrRes: " & Str$(ptrRes) & "\n")
    EnumResNamesProc = 1
End Function
'
DefInt iBindProcEnumNames
Bind iBindProcEnumNames To EnumResNamesProc
DefInt lpfnEnumResNamesProc = SetNewCallBack_4 (iBindProcEnumNames)
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
Function EnumResTypesProc (hModule As Long, lpszType As Long, lParam as Long) As Long
    DefStr sType
    DefInt iRet, iType, ilen
    If (lpszType And &HFFFF0000) = 0 Then
        ' standard resource type:
        iType = lpszType And &HFFFF
        sType = Str$(iType)
    Else
        ' resource type:
        iLen = lstrlen(lpszType)
        If (iLen > 0) Then
            sType = Space$(iLen)
            MemCpy (VarPtr(sType), lpszType, iLen)
        End If
   End If
   rchWin.Addstring ("\nEnum Resource Type  " & sType  &  "  in hModule = " & Str$(hModule))
   iRet = EnumResourceNames (hModule, lpszType, lpfnEnumResNamesProc, 0)
   Result = 1
End Function
'
DefInt iBindProcEnumTypes
Bind iBindProcEnumTypes To EnumResTypesProc
DefInt lpfnEnumResTypesProc = SetNewCallBack_3 (iBindProcEnumTypes)
'
rchWin.Addstring ("\n  MENU/ENUM_RESOURCE will enumerate resources in the module used to create this process" _
              & "\n\n  Use Menu/Select_Module to select another module ...")
' *************************************
frmEnumResources.ShowModal
' *************************************
'
Sub OnClose_frmEnumResources
    Application.Terminate
End Sub
'
Sub OnClic_AnyMenu (Sender)
    Defstr sModule
    DefInt iRet
    If flagMenuBusy = True Then Exit Sub
    flagMenuBusy = true
    Select Case Sender.Handle
        Case mnuEnumRes.Handle
            iRet = EnumResourceTypes (hModule, lpfnEnumResTypesProc, 0)
        Case mnuSelectModule.Handle
            dlgOpenModule.Filter = "PE|*.Exe;*.Dll|All Files|*.*"
            dlgOpenModule.FilterIndex = 1
            If dlgOpenModule.Execute = 0 Then flagMenuBusy = False:Exit Sub
            sModule = dlgOpenModule.FileName
            If sModule = "" Then
                hModule = 0
            Else
                hModule = LoadLibrary (sModule)
                If hModule = 0 Then
                    ShowMessage ("LoadLibrary error N°  " & Str$(GetLastError) & "\n\n  *** NOTHING LOADED ***")
                    frmEnumResources.Caption = "Enum_Resources in Module used to Create this Process: " & Application.Exename
                    flagMenuBusy = False:Exit Sub
                End If
            End If
            frmEnumResources.Caption = "Enum_Resources in Module " & sModule & "   hModule: " & Hex$(hModule)
        Case mnuClear.Handle
            rchWin.Clear
    End Select
    flagMenuBusy = False
End Sub
' -----------------------------------------------------------------------------
'
