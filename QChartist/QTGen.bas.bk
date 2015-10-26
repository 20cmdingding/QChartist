'QChartist charting software source code
'Copyright 2010 Julien Moog - All rights reserved
'contact email: julien.moog@laposte.net
'Copy and paste into your program
''pre cmd FBVERSION=017 FBLANG=deprecated norun enc noopt exe nocon NoDone icon QTGen.ico kill
''pre end
$APPTYPE GUI
$include "includes\QINI.inc"
dim indiini as qini
TYPE mousepos
    xpos AS LONG
    ypos AS LONG
END TYPE
DIM NPOS AS mousepos
DECLARE FUNCTION GetCursorPos LIB "user32.dll" ALIAS "GetCursorPos"(ByRef curpos AS mousepos) AS LONG
DECLARE FUNCTION LoadCursorFromFile LIB "USER32" ALIAS "LoadCursorFromFileA" _
    (CursorFileName AS STRING) AS LONG
SCREEN.Cursors(1) = LoadCursorFromFile("cursors\harrow.cur")
DECLARE SUB genfiles
DECLARE SUB helpbtn1click
DECLARE SUB helpbtn2click
DECLARE SUB helpbtn3click
DECLARE SUB helpbtn4click
DECLARE SUB helpbtn5click
DECLARE SUB quit
DECLARE SUB moveform(btn AS INTEGER , mx AS INTEGER , my AS INTEGER)
DECLARE SUB starttimermvfrm
DECLARE SUB stoptimermvfrm
DIM timermovefrm AS QTIMER
timermovefrm.Interval = 1
timermovefrm.Enabled = 0
timermovefrm.OnTimer = moveform

DIM homepath AS STRING
homepath = CurDir$

DIM titlefont AS QFONT
titlefont.Name = "Arial"
titlefont.Size = 13
titlefont.Color = RGB(255 , 255 , 255)
titlefont.AddStyles(fsBold)

DIM inputnfont AS QFONT
inputnfont.Name = "Arial"
inputnfont.Size = 8
inputnfont.Color = RGB(0 , 0 , 0)
inputnfont.AddStyles(fsBold)


CREATE Form AS QFORM
    BorderStyle = 0
    Caption = "Indicator generator"
    CREATE bgimage AS QIMAGE
        Width = 292
        Height = 170
        BMP = "images\qtgenbg.BMP"
        OnMouseDown = starttimermvfrm
        OnMouseUp = stoptimermvfrm
    END CREATE
    CREATE closebtn AS QBUTTON
        BMP = "images\closebtn.bmp"
        Width = 15
        Height = 15
        OnClick = quit
        ShowHint = 1
        Hint = "Quit"
    END CREATE
    Width = 280
    Height = 180
    Center


    CREATE Label1 AS QLABEL
        Caption = "Indicator name:"
        Left = 0
        Top = 9
        Width = 80
        Color = RGB(255 , 255 , 255)
        Font = inputnfont
    END CREATE
    CREATE Label2 AS QLABEL
        Caption = "Indicator filename:"
        Left = 0
        Top = 34
        Width = 88
        Color = RGB(255 , 255 , 255)
        Font = inputnfont
    END CREATE
    CREATE Label3 AS QLABEL
        Caption = "Indicator description:"
        Left = 0
        Top = 59
        Width = 94
        Color = RGB(255 , 255 , 255)
        Font = inputnfont
    END CREATE
    CREATE Label4 AS QLABEL
        Caption = "Indicator canvas #:"
        Left = 0
        Top = 85
        Width = 94
        Color = RGB(255 , 255 , 255)
        Font = inputnfont
    END CREATE
    CREATE Label5 AS QLABEL
        Caption = "Source code:"
        Left = 0
        Top = 119
        Width = 94
        Color = RGB(255 , 255 , 255)
        Font = inputnfont
    END CREATE
    CREATE codecombobox AS qcombobox
        Left = 95
        Top = 115
        additems "RapidQ"
        additems "C++"
    END CREATE
    CREATE helpbtn5 AS QBUTTON
        Caption = "?"
        Left = 240
        Top = 115
        Width = 20
        Height = 20
        OnClick = helpbtn5click
    END CREATE
    CREATE Edit1 AS QEDIT
        Text = ""
        Left = 114
        Top = 9
    END CREATE
    CREATE helpbtn1 AS QBUTTON
        Caption = "?"
        Left = 240
        Top = 9
        Width = 20
        Height = 20
        OnClick = helpbtn1click
    END CREATE
    CREATE Edit2 AS QEDIT
        Text = ""
        Left = 114
        Top = 31
        TabOrder = 1
    END CREATE
    CREATE helpbtn2 AS QBUTTON
        Caption = "?"
        Left = 240
        Top = 31
        Width = 20
        Height = 20
        OnClick = helpbtn2click
    END CREATE
    CREATE Edit3 AS QEDIT
        Text = ""
        Left = 114
        Top = 59
        TabOrder = 2
    END CREATE
    CREATE helpbtn3 AS QBUTTON
        Caption = "?"
        Left = 240
        Top = 59
        Width = 20
        Height = 20
        OnClick = helpbtn3click
    END CREATE
    CREATE Edit4 AS QEDIT
        Text = "0"
        Left = 114
        Top = 85
        TabOrder = 2
    END CREATE
    CREATE helpbtn4 AS QBUTTON
        Caption = "?"
        Left = 240
        Top = 85
        Width = 20
        Height = 20
        OnClick = helpbtn4click
    END CREATE
    CREATE Button1 AS QBUTTON
        Caption = "Generate files"
        Left = 175
        Top = 140
        TabOrder = 2
        OnClick = genfiles
        Cursor = 1
        Layout = 3
    END CREATE

    CREATE title AS QLABEL
        Caption = "Indicator Generator"
        Color = RGB(0 , 0 , 0)
        Top = Form.Height - 33
        Left = 0
        Font = titlefont
    END CREATE


    CREATE mark AS QLABEL
        Caption = "(c) Julien Moog 2010"
        Color = RGB(255 , 255 , 255)
        Top = Form.Height - 13
        Left = 0
        'font=titlefont
    END CREATE
END CREATE
closebtn.Left = Form.Width - 15

'Insert your initialization code here

Form.ShowModal

SUB genfiles

    DIM file AS QFILESTREAM    
    
    file.Open(homepath + "\indicators\" + Edit2.Text + ".ini" , 65535)
    file.close
    indiini.filename=homepath+"\indicators\"+Edit2.Text + ".ini"
    indiini.section="Settings"
    indiini.Write("name",Edit1.Text)
    'file.WriteLine(Edit1.Text)
    'file.Close

    'file.Open(homepath + "\indicators\" + Edit2.Text + ".qtd" , 65535)
    'file.WriteLine(Edit3.Text)
    'file.Close
    indiini.section="Settings"
    indiini.Write("description",Edit3.Text)
    
    indiini.section="Settings"
    indiini.Write("canvas",Edit4.Text)
    
    indiini.section="Settings"
    indiini.Write("code",codecombobox.item(codecombobox.itemindex))
    
    if codecombobox.item(codecombobox.itemindex)="RapidQ" then

    file.Open(homepath + "\indicators\" + Edit2.Text + ".qtp" , 65535)
    file.WriteLine("declare sub hide" + Edit2.Text + "form")
    file.WriteLine("")
    file.WriteLine("CREATE " + Edit2.Text + "form as qform")
    file.WriteLine("")
    file.WriteLine("    Center")
    file.WriteLine("    Caption = " + CHR$(34) + "Settings for: " + Edit1.Text + CHR$(34))
    file.WriteLine("    visible=0")
    file.WriteLine("")
    file.WriteLine("    ' Put your indicator settings code here")
    file.WriteLine("")
    file.WriteLine("    create " + Edit2.Text + "btnok as qbutton")
    file.WriteLine("        left=0")
    file.WriteLine("        top=0")
    file.WriteLine("        caption=" + CHR$(34) + "OK" + CHR$(34))
    file.WriteLine("        onclick=hide" + Edit2.Text + "form")
    file.WriteLine("    end create")
    file.WriteLine("")
    file.WriteLine("END CREATE")
    file.WriteLine("")
    file.WriteLine("sub hide" + Edit2.Text + "form")
    file.WriteLine("    " + Edit2.Text + "form.visible=0")
    file.WriteLine("end sub")
    file.Close

    file.Open(homepath + "\indicators\" + Edit2.Text + ".qti" , 65535)
    file.WriteLine("declare sub " + Edit2.Text + " ' This line of code must stay here")
    file.WriteLine("dim " + Edit2.Text + "buffer(0 to 1000) as double ' This line of code must stay here.")
    file.WriteLine("")
    file.WriteLine("sub " + Edit2.Text)
    file.WriteLine("' Put your indicator RapidQ code here")
    file.WriteLine("dim i as integer")
    file.WriteLine("for i=200 to 0 step -1")
    file.WriteLine("next i")
    file.WriteLine("end sub")
    file.Close

    'file.Open(homepath + "\indicators\" + Edit2.Text + ".qtc" , 65535)
    'file.WriteLine(Edit4.Text)
    'file.Close
    

    file.Open(homepath + "\indicators\" + Edit2.Text + ".qtr" , 65535)
    file.WriteLine("'------------------------- " + Edit1.Text + " -------------------------------------------------")
    file.WriteLine("indiid++")
    file.WriteLine("if indicatorslistsel.item(indiid)=" + CHR$(34) + "x" + CHR$(34) + " then")
    file.WriteLine("")
    file.WriteLine("if lbar=1 then")
    file.WriteLine(Edit2.Text)
    file.WriteLine("end if")
    file.WriteLine("")
    file.WriteLine("barsback=200 '<--- can also be something like VAL(" + Edit2.Text + "barsbackedit.text)")
    file.WriteLine("")
    file.WriteLine("if ibar>=lastbar-barsback then")
    IF Edit4.Text = "1" THEN
        file.WriteLine("    sepindicolor(drawid)=lightblue '<--- replace with your color")
        file.WriteLine("    canvas.separateindicator1.Cell(drawid,lbar)= STR$(" + Edit2.Text + "buffer(offset))")
    END IF
    IF Edit4.Text = "0" THEN
        file.WriteLine("    indicolor(drawid)=lightblue '<--- replace with your color")
        file.WriteLine("    .Data_Indi.Cell(drawid,lbar)= STR$(" + Edit2.Text + "buffer(offset))")
    END IF
    file.WriteLine("    drawid=drawid+2")
    file.WriteLine("end if")
    file.WriteLine("")
    file.WriteLine("end if")
    file.WriteLine("'------------------------- End " + Edit1.Text + " -------------------------------------------------")
    file.Close
    
    end if
    
    if codecombobox.item(codecombobox.itemindex)="C++" then
    
    file.Open(homepath + "\indicators\" + Edit2.Text + ".qtp" , 65535)
    file.WriteLine("declare sub hide" + Edit2.Text + "form")
    file.WriteLine("")
    file.WriteLine("CREATE " + Edit2.Text + "form as qform")
    file.WriteLine("")
    file.WriteLine("    Center")
    file.WriteLine("    Caption = " + CHR$(34) + "Settings for: " + Edit1.Text + CHR$(34))
    file.WriteLine("    visible=0")
    file.WriteLine("")
    file.WriteLine("    ' Put your indicator settings code here")
    file.WriteLine("")
    file.WriteLine("    create " + Edit2.Text + "periodlab as qlabel")
    file.WriteLine("        left=0")
    file.WriteLine("        top=0")
    file.WriteLine("        caption=" + CHR$(34) + "Period:" + CHR$(34))
    file.WriteLine("    end create")
    file.WriteLine("")
    file.WriteLine("    create " + Edit2.Text + "periodedit as qedit")
    file.WriteLine("        left="+ Edit2.Text + "periodlab.width+100")
    file.WriteLine("        top=0")
    file.WriteLine("        text=" + CHR$(34) + "20" + CHR$(34))
    file.WriteLine("    end create")
    file.WriteLine("")    
    file.WriteLine("    create " + Edit2.Text + "btnok as qbutton")
    file.WriteLine("        left=0")
    file.WriteLine("        top=20")
    file.WriteLine("        caption=" + CHR$(34) + "OK" + CHR$(34))
    file.WriteLine("        onclick=hide" + Edit2.Text + "form")
    file.WriteLine("    end create")
    file.WriteLine("")
    file.WriteLine("END CREATE")
    file.WriteLine("")
    file.WriteLine("sub hide" + Edit2.Text + "form")
    file.WriteLine("    " + Edit2.Text + "form.visible=0")
    file.WriteLine("end sub")
    file.Close
    
    file.Open(homepath + "\indicators\" + Edit2.Text + ".cpp" , 65535)
    'file.WriteLine("declare sub " + Edit2.Text + " ' This line of code must stay here")
    file.WriteLine("static arrayofdoubles " + Edit2.Text + "buffer; // This line of code must stay here.")
    file.WriteLine("")
    file.WriteLine("char* " + Edit2.Text + " (char* period)")
    file.WriteLine("{")
    file.WriteLine("    static char periodd[1000];")
    file.WriteLine("    strncpy(periodd, period, 1000);")
    file.WriteLine("    int intperiod=atoi(periodd);")
    file.WriteLine("    // Put your indicator C++ code here")
    file.WriteLine("        for (int i=200;i>=0;i--)")
    file.WriteLine("        {")
    file.WriteLine("        "+Edit2.Text + "buffer[i]=closea[i];")
    file.WriteLine("        }")
    file.WriteLine("return 0;")
    file.WriteLine("}")
    file.Close
    
    file.Open(homepath + "\indicators\" + Edit2.Text + ".qtr" , 65535)
    file.WriteLine("'------------------------- " + Edit1.Text + " -------------------------------------------------")
    file.WriteLine("indiid++")
    file.WriteLine("if indicatorslistsel.item(indiid)=" + CHR$(34) + "x" + CHR$(34) + " then")
    file.WriteLine("")
    file.WriteLine("if lbar=1 then")
    file.WriteLine("periodstr="+Edit2.Text+"periodedit.text")
    file.WriteLine("cpptmpfuncreturn=varptr$("+Edit2.Text+"(varptr(periodstr)))")
    file.WriteLine("end if")
    file.WriteLine("")
    file.WriteLine("barsback=200 '<--- can also be something like VAL(" + Edit2.Text + "barsbackedit.text)")
    file.WriteLine("")
    file.WriteLine("if ibar>=lastbar-barsback then")
    IF Edit4.Text = "1" THEN
        file.WriteLine("    sepindicolor(drawid)=lightblue '<--- replace with your color")
        file.WriteLine("    bufnamestr="+ CHR$(34) +Edit2.Text+"buffer"+ CHR$(34))
        file.WriteLine("    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))")
    END IF
    IF Edit4.Text = "0" THEN
        file.WriteLine("    indicolor(drawid)=lightblue '<--- replace with your color")
        file.WriteLine("    bufnamestr="+ CHR$(34) +Edit2.Text+"buffer"+ CHR$(34))
        file.WriteLine("    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))")
    END IF
    file.WriteLine("    drawid=drawid+2")
    file.WriteLine("end if")
    file.WriteLine("")
    file.WriteLine("end if")
    file.WriteLine("'------------------------- End " + Edit1.Text + " -------------------------------------------------")
    file.Close
    
    dim filearr(0 TO 10000) as string
    file.open(homepath + "\includes\cppincludes.cpp" , 0)
    dim j as integer:j=0
    dim getdatabufline as string
    getdatabufline="#include "+CHR$(34)+"includes\getbufferdata.cpp"+CHR$(34)
    DO
    j++
    filearr(j) = file.ReadLine
    if instr(filearr(j),getdatabufline)>0 then
    filearr(j)=""
    end if
    LOOP UNTIL file.eof
    file.close
    
    dim k as integer
    file.open(homepath + "\includes\cppincludes.cpp" , 65535)
    for k=1 to j
    file.WriteLine(filearr(k))
    next k
    file.close
    
    file.open(homepath + "\includes\cppincludes.cpp" , 2)
    file.Position = file.Size
    file.WriteLine("// ''RQEXPORT function "+Edit2.Text+"(periodstr)")  
    file.WriteLine("#include "+CHR$(34)+"indicators\"+Edit2.Text+".cpp"+CHR$(34)) 
    file.WriteLine("")
    file.WriteLine(getdatabufline)
    file.close   
    
    file.open(homepath + "\includes\getbufferdata.cpp" , 0)
    j=0
    dim linenbadd as integer
    'dim getdatabufline as string
    'getdatabufline="#include "+CHR$(34)+"includes\getbufferdata.cpp"+CHR$(34)
    DO
    j++
    filearr(j) = file.ReadLine
    if instr(filearr(j),"return 0;")>0 then
    linenbadd=j-1
    end if
    LOOP UNTIL file.eof
    file.close
    
    file.open(homepath + "\includes\getbufferdata.cpp" , 65535)
    for k=1 to linenbadd
    file.WriteLine(filearr(k))
    next k
    file.close
    
    file.open(homepath + "\includes\getbufferdata.cpp" , 2)
    file.Position = file.Size
    file.WriteLine("if (strcmp(buffernamee,"+CHR$(34)+Edit2.Text+"buffer"+CHR$(34)+")==0) { sprintf(convbuf,"+CHR$(34)+"%f"+CHR$(34)+","+Edit2.Text+"buffer[atoi(offsett)]);return convbuf; }")  
    file.WriteLine("return 0;") 
    file.WriteLine("}")
    file.close   
    
    end if

    SHOWMESSAGE "Indicator created! Please edit your indicator's files in the indicator folder"

END SUB

SUB helpbtn1click
    SHOWMESSAGE "Give a name to your indicator"
END SUB

SUB helpbtn2click
    SHOWMESSAGE "This is the indicator filename saved in the indicators folder"
END SUB

SUB helpbtn3click
    SHOWMESSAGE "Give a description to your indicator"
END SUB

SUB helpbtn4click
    SHOWMESSAGE "Enter 0 if your indicator should be displayed in the main canvas or 1 if your indicator should be displayed in the separate canvas"
END SUB

SUB helpbtn5click
    SHOWMESSAGE "Select whether your indicator will be coded in RapidQ or in C++ language"
END SUB

SUB quit
    END
END SUB

SUB moveform(btn AS INTEGER , mx AS INTEGER , my AS INTEGER)
    DIM XVAL AS INTEGER , YVAL AS INTEGER
    GetCursorPos(NPOS)
    XVAL = NPOS.xpos
    YVAL = NPOS.ypos
    'xval=xval-form.left-7'-canvas.left-4
    'yval=yval-form.top-50'-canvas.top-42
    Form.Left = XVAL - mx
    Form.Top = YVAL - my
END SUB

SUB starttimermvfrm
    timermovefrm.Enabled = 1
END SUB

SUB stoptimermvfrm
    timermovefrm.Enabled = 0
END SUB
