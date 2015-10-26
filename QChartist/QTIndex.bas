'QChartist charting software source code
'Copyright 2010 Julien Moog - All rights reserved
'contact email: julien.moog@laposte.net

'Compiler Directrapidqives
''pre cmd FBVERSION=017 FBLANG=deprecated norun enc noopt exe con NoDone icon QTIndex.ico kill
''pre end
$APPTYPE CONSOLE
$OPTIMIZE ON
$TYPECHECK ON

$IFNDEF TRUE
    $DEFINE TRUE 1
$ENDIF

$IFNDEF FALSE
    $DEFINE FALSE 0
$ENDIF

$INCLUDE "includes\RAPIDQ2.INC"
$include "includes\QINI.inc"

DIM homepath AS STRING
homepath = CurDir$

dim indiini as qini

DIM qtform AS QFORM

DIM qtpList AS QFILELISTBOX
qtpList.Visible = 0
qtpList.Parent = qtform
qtpList.Mask = "*.qtp"
qtpList.Directory = homepath + "\indicators"

PRINT STR$(qtpList.ItemCount) + " indicators found"


DIM qtpi AS INTEGER
DIM fileqtp AS QFILESTREAM
fileqtp.Open(homepath + "\includes\includeqtp.inc" , 65535)

FOR qtpi = 0 TO qtpList.ItemCount - 1
    fileqtp.WriteLine("$include " + CHR$(34) + homepath + "\indicators\" + qtpList.Item(qtpi) + CHR$(34))
NEXT qtpi

fileqtp.Close

DIM qtiList AS QFILELISTBOX
qtiList.Visible = 0
qtiList.Parent = qtform
qtiList.Mask = "*.qti"
qtiList.Directory = homepath + "\indicators"

fileqtp.Open(homepath + "\includes\includeqti.inc" , 65535)

FOR qtpi = 0 TO qtiList.ItemCount - 1
    fileqtp.WriteLine("$include " + CHR$(34) + homepath + "\indicators\" + qtiList.Item(qtpi) + CHR$(34))
NEXT qtpi

fileqtp.Close


'Indexing indicators

DIM indiinilist AS QFILELISTBOX
indiinilist.Visible = 0
indiinilist.Parent = qtform
indiinilist.Mask = "*.ini"
indiinilist.Directory = homepath + "\indicators"

DIM indinames(0 TO indiinilist.ItemCount - 1) AS STRING
DIM nli AS INTEGER
'DIM qtnfile AS QFILESTREAM
FOR nli = 0 TO indiinilist.ItemCount - 1
    'qtnfile.Open(indiinilist.Item(nli) , fmOpenRead)
    'indinames(nli) = qtnfile.ReadLine() 'Read an entire line
    indiini.filename=homepath+"\indicators\"+indiinilist.Item(nli)
    indiini.section="Settings"
    indinames(nli)=indiini.get("name","")
NEXT nli
'qtnfile.Close

'DIM qtcList AS QFILELISTBOX
'qtcList.Visible = 0
'qtcList.Parent = qtform
'qtcList.Mask = "*.ini"
'qtcList.Directory = homepath + "\indicators"

DIM indicanvas(0 TO indiinilist.ItemCount - 1) AS STRING
'dim nli as integer
'DIM qtcfile AS QFILESTREAM
FOR nli = 0 TO indiinilist.ItemCount - 1
    'qtcfile.Open(indiinilist.Item(nli) , fmOpenRead)
    'indicanvas(nli) = qtcfile.ReadLine() 'Read an entire line
    indiini.filename=homepath+"\indicators\"+indiinilist.Item(nli)
    indiini.section="Settings"
    indicanvas(nli)=indiini.get("canvas","")
NEXT nli
'qtcfile.Close

DIM indilisti AS INTEGER
DIM indilisty AS INTEGER
DIM indicanvascount() AS INTEGER
DIM countcanvas AS INTEGER


'dim qtpi as integer
'dim fileqtp as qfilestream
fileqtp.Open(homepath + "\includes\includeset.inc" , 65535)

DIM qtnnoext AS STRING
DIM caseordercnt AS INTEGER
caseordercnt = 0
fileqtp.WriteLine("sub settingsclick")
fileqtp.WriteLine("select case indicatorslist.itemindex")

indilisty = 0
FOR qtpi = 0 TO qtpList.ItemCount - 1
    IF VAL(indicanvas(qtpi)) = indilisty THEN
        qtnnoext = MID$(indiinilist.Item(qtpi) , 0 , INSTR(indiinilist.Item(qtpi) , ".") - 1)
        fileqtp.WriteLine("case " + STR$(caseordercnt)) ' + CHR$(34) + homepath + "\indicators\" + qtpList.Item(qtpi) + CHR$(34))
        caseordercnt ++
        fileqtp.WriteLine(qtnnoext + "form.visible=1")
    END IF
NEXT qtpi

indilisty = 1
FOR qtpi = 0 TO qtpList.ItemCount - 1
    IF VAL(indicanvas(qtpi)) = indilisty THEN
        qtnnoext = MID$(indiinilist.Item(qtpi) , 0 , INSTR(indiinilist.Item(qtpi) , ".") - 1)
        fileqtp.WriteLine("case " + STR$(caseordercnt)) ' + CHR$(34) + homepath + "\indicators\" + qtpList.Item(qtpi) + CHR$(34))
        caseordercnt ++
        fileqtp.WriteLine(qtnnoext + "form.visible=1")
    END IF
NEXT qtpi

fileqtp.WriteLine("end select")
fileqtp.WriteLine("end sub")

fileqtp.Close


DIM qtrList AS QFILELISTBOX
qtrList.Visible = 0
qtrList.Parent = qtform
qtrList.Mask = "*.qtr"
qtrList.Directory = homepath + "\indicators"

DIM getline$ AS STRING
DIM file2 AS QFILESTREAM
DIM file3 AS QFILESTREAM
'dim file4 as qfilestream

file2.Open(homepath + "\includes\includebtnonclickpart1.inc" , 0)
file3.Open(homepath + "\includes\includebtnonclick.inc" , 65535)
DO

    getline$ = file2.ReadLine
    file3.WriteLine(getline$)
LOOP UNTIL file2.eof
file2.Close


indilisty = 0
countcanvas = 0
FOR indilisti = 0 TO UBOUND(indinames)
    IF VAL(indicanvas(indilisti)) = indilisty THEN
        'indicatorslist.AddItems indinames(indilisti)+" ( )"
        'fileqtp.writeline("$include "+chr$(34)+homepath+"\indicators\"+qtrlist.item(indilisti)+chr$(34))
        file2.Open(homepath + "\indicators\" + qtrList.Item(indilisti) , 0)
        DO
            getline$ = file2.ReadLine
            file3.WriteLine(getline$)
        LOOP UNTIL file2.eof
        file2.Close

    END IF
NEXT indilisti


file2.Open(homepath + "\includes\includebtnonclickpart2.inc" , 0)
'file3.open(homepath+"\includes\includebtnonclick.inc",65535)
DO

    getline$ = file2.ReadLine
    file3.WriteLine(getline$)
LOOP UNTIL file2.eof
file2.Close


indilisty = 1
countcanvas = 0
FOR indilisti = 0 TO UBOUND(indinames)
    IF VAL(indicanvas(indilisti)) = indilisty THEN
        'indicatorslist.AddItems indinames(indilisti)+" ( )"
        'fileqtp.writeline("$include "+chr$(34)+homepath+"\indicators\"+qtrlist.item(indilisti)+chr$(34))
        file2.Open(homepath + "\indicators\" + qtrList.Item(indilisti) , 0)
        DO
            getline$ = file2.ReadLine
            file3.WriteLine(getline$)
        LOOP UNTIL file2.eof
        file2.Close

    END IF
NEXT indilisti

file2.Open(homepath + "\includes\includebtnonclickpart3.inc" , 0)
'file3.open(homepath+"\includes\includebtnonclick.inc",65535)
DO

    getline$ = file2.ReadLine
    file3.WriteLine(getline$)
LOOP UNTIL file2.eof
file2.Close

file3.Close


