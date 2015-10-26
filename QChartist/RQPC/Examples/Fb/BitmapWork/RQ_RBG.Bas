'
' -----------------------------------------------------------------------------
' RQPC FreeBasic DEMO     Bitmap Info + Stats        jan 15th,  2007   Jacques
' -----------------------------------------------------------------------------
'
$Include "RQ_RBGTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated tiny run enc opt exe nocon Kill nobk BitmapShell.Fbb NoDone Bridge.Ico
DefStr BuildCount     = "0.015" ''pre + 0.001 3
DefStr FirstCompiled  = "01-15-2007  17:15:49"
''pre end
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
$OPTION ICON "Frog.Ico"
'
Type INKBMP
    fileSize as Long
    dataSize As Long
    Width As Long
    Height As Long
    Pixelcount As Long
    BitPerPixel As Long
    totRed As Long
    totBlue As Long
    totGreen As Long
    avgRed As Long
    avgBlue As Long
    avgGreen As Long
    Worktime As Long
END TYPE
'
$RESOURCE FORM_ICO AS "Frog.ico"
'
Declare Sub OnClose_frmMyForm
Declare Sub OnClic_AnyMenu (Sender As QMenuItem)
'
Create frmMyForm As QForm
    Center
    Width = 600
    height = 800
    Caption = "frmMyForm V" &  BuildCount
    IcoHandle = FORM_ICO
    AutoScroll = False
    OnClose = OnClose_frmMyForm
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
frmMyForm.Show
' *************************************
'
Dim Bmp As INKBMP
DefInt N
DefStr sTmp
'
Sub GetBmpInfo (sBmp As String)
    sTmp = "File: " & sBmp
    rchWin.AddString "\n" & sTmp
    rchWin.AddString String$(Len(sTmp), "-")
'
    BitMapWork (sBmp, Bmp, 2)  ' 2 full FB, fast, no ASM
'
    rchWin.Addstring   "BMP   file size: " & Str$(Bmp.fileSize)
    rchWin.Addstring   "BMP   data size: " & Str$(bmp.DataSize)
    rchWin.Addstring   "BMP       Width: " & Str$(bmp.Width)
    rchWin.Addstring   "BMP      Height: " & Str$(bmp.Height)
    rchWin.Addstring   "BMP  PixelCount: " & Str$(bmp.PixelCount)
    rchWin.Addstring   "BMP BitPerPixel: " & Str$(bmp.BitPerPixel)

    rchWin.Addstring   "BMP   tot   Red: " & Str$(bmp.totRed)
    rchWin.Addstring   "BMP   tot  Blue: " & Str$(bmp.totBlue)
    rchWin.Addstring   "BMP   tot Green: " & Str$(bmp.totGreen)

    rchWin.Addstring   "BMP   avg   Red: " & Str$(bmp.avgRed)
    rchWin.Addstring   "BMP   avg  Blue: " & Str$(bmp.avgBlue)
    rchWin.Addstring   "BMP   avg Green: " & Str$(bmp.avgGreen)
    rchWin.Addstring "\n   Compute Time: " & Str$(bmp.WorkTime) & " ms"
End Sub

GetBmpInfo ("Red.Bmp")
GetBmpInfo ("Blue.Bmp")
GetBmpInfo ("Green.Bmp")
GetBmpInfo ("Black.Bmp")
GetBmpInfo ("White.Bmp")
GetBmpInfo ("Badgers.Bmp")

rchWin.Addstring "\n\n                  FINISHED"
'
' *************************************
frmMyForm.Visible = False
frmMyForm.ShowModal
' *************************************
'
Sub OnClose_frmMyForm
    Application.Terminate
End Sub
'
' -----------------------------------------------------------------------------
'
