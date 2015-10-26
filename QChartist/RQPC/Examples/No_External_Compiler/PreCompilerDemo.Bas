'
' -----------------------------------------------------------------------------
' RQPC No External Compiler    PreCompiler Demo        March 4th, 2007 Jacques
' ----------------------------------------------------------------------------- 
'
''pre cmd tiny run encrypt nooptimize exe console
''pre cmd output nokillfiles nobk Rabbit.ico DirIcon addRq32dll 'upx
' all the following will be updated at each compile
' ----------------
DefStr sBuildCount     = "0.060"        ''pre + 0.001 3
DefStr sFirstCompiled  =  "02-03-2007  22:46:40"
DefStr sBuildCount2    = "60.000"       ''pre + 1
DeFStr sJustForFun     = "-930.6"       ''pre - 33.2 1
DefStr sCompileDate    = "05-26-2014"   ''pre Date$
DefStr sCompileTime    = "22:41:51"     ''pre Time$
DefStr sCompileTimer   = "  46395664"   ''pre Timer
' ----------------
''pre end
'
' PreCompiler Short Documentation
' ===============================
'  Within the 30 first non commented lines of the main RapidQ
'  code file (Line begining with a single Quote are not counted):
'
'  Descativated command  (a space between the two quotes, after  "''pre end"  too)
'  --------------------
'  ' 'pre cmd ICON NOCONSOLE NOENCRYPT TINY VOFF OPTIMIZE
'  ' 'pre cmd EXE RUN SHOW LIBS_SUBDIR=HW2005 DIRICON GICO
'  ' 'pre cmd RCEXE=RCx.EXE RQ32DLL=RQ_xxx32.DLL
'  ' 'pre cmd OUTPUT NODONE NOKILLFILES NOBK Upx AddRq32Dll
'  ' 'pre ICON PathWithSpaces.Ico
'  ' 'pre LIBS_SUBDIR PathWithSpaces
'
$ESCAPECHARS ON
$TYPECHECK ON
$INCLUDE "RAPIDQ.INC"
'
Declare Sub OnClose_frmRqpcDemo
Declare Sub OnClic_AnyMenu (Sender As QMenuItem)
'
Create frmRqpcDemo As QForm
    Center
    Width   = 900
    height  = 900
    Caption = "Rqpc: PreCompiler Demo V" &  sBuildCount
    AutoScroll = False
    OnClose = OnClose_frmRqpcDemo
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
        Create mnuAbout AS QMENUITEM
            Caption = "&About"
            OnClick = OnClic_AnyMenu
        End Create
    End Create
End Create
'
DefInt flagMenuBusy = False
'
' *************************************
frmRqpcDemo.Show
' *************************************
rchWin.Addstring "Pre Compiler Variables: (re initialized at each compile)" _
             & "\n======================: " _
             & "\n    BuildCount: " & sBuildCount _
             & "\n FirstCompiled: " & sFirstCompiled _
             & "\n   BuildCount2: " & sBuildCount2 _
             & "\n    JustForFun: " & sJustForFun _
             & "\n   CompileDate: " & sCompileDate _
             & "\n   CompileTime: " & sCompileTime _
             & "\n  CompileTimer: " & sCompileTimer _
           & "\n\n - the code line: \n      \"DefStr sBuildCount  = \"0.011\"  ''pre + 0.001 3\"" _
             & "\n   will be rewritten by the pre compiler, adding 0.001" _
             & "\n   to sBuildCount, sBuildCount will have 3 decimal digits" _
           & "\n\n - the Pre Compiler interpretes the lines beginning with \"''pre cmd\"" _
             & "\n   as if it was a Command Line." _
           & "\n\n - as learning, you should modify, on top of the code, one by one, " _
             & "\n   the parameters of the two following lines, recompile then reset" _
             & "\n   the modified parameter to its original value:" _
           & "\n\n       ''pre cmd tiny run encrypt nooptimize exe console" _
             & "\n       ''pre cmd 'output DirIcon nokillfiles nobk Rabbit.ico' 'upx 'adddll" _
           & "\n\n     1: replace  'tiny'  by  'notiny'" _
             & "\n           will compile large exe as usual" _
             & "\n     2: replace  'run'  by  'norun'" _
             & "\n           the exe (=me) will not be run after compile anymore" _
             & "\n     3: replace  'encrypt'  by  'noencrypt     (enc/noenc valid too)" _
             & "\n           bytecode not encrypted anymore, edit this .exe and ?see" _
             & "\n     4: replace  'nooptimize'  by  'optimize'  (opt/noopt valid too)" _
             & "\n           the size of the exe is smaller with 'opt' (mainly with Tiny)" _
             & "\n     5: replace  'exe'  by  'noexe'" _
             & "\n           no .exe is created, only the bytecode .bc" _
             & "\n     6: replace  'console'  by  'noconsole'    (con/nocon valid too)" _
             & "\n           the boring uggly console will be removed. Can be usefull" _
             & "\n           when a console must be created." _
             & "\n     7: replace  \"'output\"  by  \"output\"" _
             & "\n           the compiler output is showed even if no error"_
             & "\n     8: replace  \"DirIcon\"  by  \"DirIcon'\"" _
             & "\n           the exe will be build with icon Rabbit.Ico"_
             & "\n           'DirIcon', using the first found icon in the directory" _
             & "\n           of your RapidQ source, will be ignored" _
             & "\n     9: replace  'nokillfiles'  by  'killfiles'" _
             & "\n           all the intermediary files created during compilation" _
             & "\n           will be deleted. 'nobk' force the .bk file delete too" _
             & "\n    10: replace  \"'Upx\"  by  \"Upx\"" _
             & "\n           The .Exe will be compressed and its size should" _
             & "\n           be smaller. Better compression rate if encrypt is" _
             & "\n           off:noEncrypt " _
             & "\n    11: replace  \"'adddll\"  by  \"adddll\" the executable" _
             & "\n           will include RQ32.DLL as a resource. RQ32.DLL will " _
             & "\n           be extracted in the directory of the exe at run time." _
             & "\n           Tiny exe is with adddll a 'pseudo' stand alone." _
             & "\n    12: replace encrypt by enc, nooptimize by noopt," _
             & "\n           nokillfiles by nokill, addRq32dll by adddll  and see" _
             & "\n           they are synonyme." _
          &  "\n\n - This version of RQPC better works with Snakedile RapidQ32.Dll" _
            &  "\n   V109 (the form and the application inherit the Icon set in Rqpc)"
'
' *************************************
frmRqpcDemo.Visible = False
frmRqpcDemo.ShowModal
' *************************************
'
Sub OnClose_frmRqpcDemo
    Application.Terminate
End Sub
'
Sub OnClic_AnyMenu (Sender)
    If flagMenuBusy = True Then Exit Sub
    flagMenuBusy = true
    Select Case Sender.Handle
        Case mnuAbout.Handle

    End Select
    flagMenuBusy = False
End Sub
' -----------------------------------------------------------------------------
'

