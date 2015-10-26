'
' -----------------------------------------------------------------------------
' RQPC FreeBasic DEMO     Bitmap Info + Stats        jan 15th,  2007   Jacques
' -----------------------------------------------------------------------------
'
$Include "RQ_BitmapTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated tiny run enc opt exe nocon Kill nobk BitmapShell.Fbb NoDone DirIcon
DefStr BuildCount     = "0.025" ''pre + 0.001 3
DefStr FirstCompiled  = "01-15-2007  19:15:49"
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
'
rchWin.Addstring "Method 1  can be very slow ??? be patient"
For N = 1 To 4   ' Do the 4 methods    1 is very slow
    rchWin.AddString "\nMETHOD: " & Str$(N)
    rchWin.AddString   "---------"
'
    BitMapWork ("Badgers.Bmp", bmp, N)
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
Next N
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
' -----------------------------------------------------------------------------
'
