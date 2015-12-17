'QChartist charting software source code
'Copyright 2010-2015 Julien Moog - All rights reserred
'Contact email: julien.moog@laposte.net
'Website: http://www.qchartist.net

'>>> SOURCE LICENSE >>>
'This program is free software; you can redistribute it and/or modify
'it under the terms of the GNU General Public License as published by
'the Free Software Foundation (www.fsf.org); either version 2 of the
'License, or (at your option) any later version.
'
'This program is distributed in the hope that it will be useful,
'but WITHOUT ANY WARRANTY; without even the implied warranty of
'MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
'GNU General Public License for more details.
'
'A copy of the GNU General Public License is available at
'http://www.fsf.org/licensing/licenses
'
'>>> END OF LICENSE >>>

$Include "QChartistTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated run enc noopt exe con NoDone icon QChartist.ico kill includes\cppincludes.cpp
''pre end

'Compiler Directrapidqives
$APPTYPE console  'GUI
$OPTIMIZE on
$TYPECHECK on

if curdir$<>"C:\QChartist" then
showmessage "QChartist won't work properly, please install it in directory C:\QChartist"
application.terminate
end if

defstr bksl="\"
declare function MKSubDir (DirDst$) as short
declare Function StripPath (fullname as string) as string
declare sub FileCopy (FileSrc$, FileDst$)

if fileexists(curdir$+"\update2.exe") then ' used in case we need to update update.exe

kill curdir$+"\update.exe"
FileCopy (curdir$+"\update2.exe",curdir$+"\update.exe")
kill curdir$+"\update2.exe"

end if

dim versfile as qfilestream
versfile.open (curdir$+"\build.txt",0)
defstr QC_build=versfile.readline 
versfile.close

' setting budystream to 0 for the quotes grabber
dim busystream as qfilestream
busystream.open("c:\qchartist\perl\scripts\isbusy.txt",65535)
busystream.writeline "0"
busystream.close

PRINT "QChartist charting software"
PRINT "Copyright 2010-2015 Julien Moog - All rights reserved"
PRINT "Contact email: julien.moog@laposte.net"
PRINT "Website: http://www.qchartist.net"
PRINT "If you like my software and find it useful, please consider to make a donation. This will be the counterpart of all my hard work around this project."
PRINT "This program is free software; you can redistribute it and/or modify " + _
    "it under the terms of the GNU General Public License"


$IFNDEF TRUE
    $DEFINE TRUE 1
$ENDIF

$IFNDEF FALSE
    $DEFINE FALSE 0
$ENDIF

$INCLUDE "includes\RAPIDQ2.INC"
$Include "includes\QInputBox.inc"
$include "includes\rq-math.inc"
$include "includes\qcalendar.inc"
$include "includes\like.inc"
$include "includes\windows.inc"
'$Include "includes\CommCtrl.inc"
'$Include "includes\Memory.inc"
'$Include "includes\Callbacks.inc"
'$Include "includes\SysUtils.inc"
'$Include "includes\QUpDown.inc"
$include "includes\QINI.inc"
$include "includes\ap_rq.inc"
$include "includes\gammafunc_rq.inc"
$include "includes\betaf_rq.inc"
$include "includes\igammaf_rq.inc"
$include "includes\chisquaredistr_rq.inc"
$include "includes\dawson_rq.inc"
$include "includes\elliptic_rq.inc"
$include "includes\expintegrals_rq.inc"
$include "includes\normaldistr_rq.inc"
$include "includes\ibetaf_rq.inc"
$include "includes\fdistr_rq.inc"
$include "includes\poissondistr_rq.inc"
$include "includes\studenttdistr_rq.inc"
$include "includes\legendre.inc"
$include "includes\psif.inc"
$include "includes\fresnel.inc"
$include "includes\nearunityunit_rq.inc"
$include "includes\binomialdistr_rq.inc"
$include "includes\hermite_rq.inc"
$include "includes\jarquebera_rq.inc"
$include "includes\trigintegrals.inc"
$include "includes\stmttw.inc"
$include "includes\Ephem101.bas"
$include "includes\Earth_LBR.bas"
$include "includes\Earth_Header.bas"
$include "includes\Jupiter_LBR.bas"
$include "includes\Jupiter_Header.bas"
$include "includes\Mars_LBR.bas"
$include "includes\Mars_Header.bas"
$include "includes\Mercury_LBR.bas"
$include "includes\Mercury_Header.bas"
$include "includes\Neptune_LBR.bas"
$include "includes\Neptune_Header.bas"
$include "includes\Saturn_LBR.bas"
$include "includes\Saturn_Header.bas"
$include "includes\Uranus_LBR.bas"
$include "includes\Uranus_Header.bas"
$include "includes\Venus_LBR.bas"
$include "includes\Venus_Header.bas"
$include "includes\sweph.inc"
$include "includes\fftlib.inc"
$Include "includes\ShellRedir.Inc"
$Include "includes\qprogress.Inc"
$include "includes\clock.bas"

declare sub ShellRedirCallBack (Text As String)

Sub ShellRedirCallBack (Text As String)
'Print Text
End Sub

DefStr platform = ShellRedir ("c:\qchartist\getos.exe")

if like(platform,"*Wine*")=1 then
defstr tmppath0=curdir$
chdir "c:\qchartist\perl\scripts"
defint pid
pid=shell ("/bin/sh -c "+chr$(34)+"chmod u+x getcurrency.sh"+chr$(34),0)
pid=shell ("/bin/sh -c "+chr$(34)+"chmod u+x currency"+chr$(34),0)
pid=shell ("/bin/sh -c "+chr$(34)+"chmod u+x getstock.sh"+chr$(34),0)
pid=shell ("/bin/sh -c "+chr$(34)+"chmod u+x stock"+chr$(34),0)
pid=shell ("/bin/sh -c "+chr$(34)+"chmod u+x getstockvol.sh"+chr$(34),0)
pid=shell ("/bin/sh -c "+chr$(34)+"chmod u+x stockvol"+chr$(34),0)
chdir tmppath0
tmppath0=curdir$
chdir "c:\qchartist\gshareinvest"
'defint pid
pid=shell ("/bin/sh -c "+chr$(34)+"chmod u+x getstock.sh"+chr$(34),0)
pid=shell ("/bin/sh -c "+chr$(34)+"chmod u+x getstock2.sh"+chr$(34),0)
pid=shell ("/bin/sh -c "+chr$(34)+"chmod u+x stock"+chr$(34),0)
chdir tmppath0
end if

DIM orderbuydb AS QSTRINGGRID
DIM orderselldb AS QSTRINGGRID
' --------------- gshareinvest portfolio -------------------
$Include "gshareinvest\login.bas"
' ---------------------------------------------------------

' ------------------------ Text to speech variables----------------
DIM rtn2 AS LONG, counter AS LONG
DIM vdPtr AS LONG, vnPtr AS LONG
DIM voiceTotal AS WORD, currentVoice AS WORD, voiceNumber AS WORD
DIM stg$ AS STRING, volumespeech AS LONG, pitch AS LONG, speed AS LONG

voiceTotal=0 : currentVoice=0 : voiceNumber=0 : volumespeech=0 : pitch=0
speed=0
' -----------------------------------------------------------------

' ------------------------ Hot Keys --------------------------

'DECLARE FUNCTION RegisterHotKey LIB "USER32" ALIAS "RegisterHotKey" _
'                 (hWnd AS LONG, ID AS LONG, fsModifiers AS LONG, _
'                  vk AS LONG) AS LONG
'DECLARE FUNCTION UnRegisterHotKey LIB "USER32" ALIAS "UnregisterHotKey" _
'                 (hWnd AS LONG, ID AS LONG) AS LONG
'DECLARE SUB SetForegroundWindow LIB "USER32" ALIAS "SetForegroundWindow" _
'                 (HWnd AS LONG)

'DECLARE SUB FormWndProc (hWnd&, uMsg&, wParam&, lParam&)

' ----------------------- End Hot Keys ----------------------------

' ----------------------------------------------
'The PeekMessage function checks a thread message queue for a message 
'and places the message (if any) in the specified structure.
'$UNDEF TYPE
$DEFINE WM_CHAR &H102
$DEFINE PM_REMOVE &H01
$DEFINE NULL &H00 
STRUCT MSGStruct
    hwnd AS LONG
    message AS LONG
    wParam AS LONG
    lParam AS LONG
    time AS DWORD
    x as LONG
    y as LONG
END STRUCT
DIM MyMsg As MSGStruct
'DECLARE FUNCTION PeekMessage Lib "user32" Alias "PeekMessageA" _
'                  (ByRef lpMsg As MyMsg, ByVal hwnd As Long, _
'                      ByVal wMsgFilterMin As Long, _
'                      ByVal wMsgFilterMax As Long, _
'                      ByVal wRemoveMsg As Long) _
'                      As Long
'--------------------------------------------   

declare sub fibofanstandardradioclickedsub
declare sub fibofansymetryfrompointradioclickedsub

DECLARE FUNCTION degtorad(deg AS DOUBLE) AS DOUBLE
FUNCTION degtorad(deg AS DOUBLE)
    result = deg * rqPI / 180
END FUNCTION

'Prevent intial resize exception
DIM AppStart AS BYTE :  AppStart = TRUE

'Declaring public variables

DECLARE SUB ButtonClick  '"Send mail" button
DECLARE SUB TimerExpired  'Check for incomming messages from server
CONST DELAY = 500
DIM Timer1 AS QTIMER  'Timer for checking the socket
Timer1.Interval = DELAY
Timer1.OnTimer = TimerExpired
'and continue in sending a mail.
DIM TheFont AS QFONT  'Font for rich edit text box
TheFont.Name = "Courier New"
TheFont.Size = 10

DIM Socket AS QSOCKET  'Internet stuff
DIM SockNum AS INTEGER
SockNum = 0

DIM LastLine AS STRING  'Last line recieved from socket
DIM LastCode AS INTEGER  'Every SMTP response from the server is
'in the format "nnn Text..."
'LastCode=nnn

DIM MailStep AS INTEGER  'Which step have we got to do next?
'Used in SUB TimerExpired.

DIM numbars AS INTEGER
DIM valmin AS DOUBLE
DIM valmax AS DOUBLE
DIM chartstart AS INTEGER
DIM chartbars(1 TO 100) AS INTEGER
dim chartbarsdisplayedfilestr as string
DIM chartbarstmp(1 TO 100) AS INTEGER
dim chartbarstmpdisplayedfilestr as string
dim charttf(1 TO 100) AS INTEGER
DIM Timerdispbarsp AS QTIMER
DIM Timerdispbarsm AS QTIMER
Timerdispbarsp.Interval = 100
Timerdispbarsm.Interval = 100
Timerdispbarsp.Enabled = 0
Timerdispbarsm.Enabled = 0
DIM importedfile(1 TO 100) AS STRING
DIM openedfilesnb AS INTEGER
openedfilesnb = 0
dim openedfilesnbstr as string
dim importedfileopenedfilesnbstr as string
DIM displayedfile AS INTEGER
DIM Grid AS QSTRINGGRID
DIM Gridtmp AS QSTRINGGRID
DIM rowgridoffset AS INTEGER
rowgridoffset = 0
dim rowgridoffsetstr as string
dim offsetstr as string
dim displayedfilestr as string
DIM indigrid() AS DOUBLE
DIM open(0 TO 1000) AS DOUBLE , high(0 TO 1000) AS DOUBLE , low(0 TO 1000) AS DOUBLE , close(0 TO 1000) AS DOUBLE , volume(0 TO 1000) AS INTEGER, date(0 TO 1000) AS STRING, time(0 TO 1000) AS STRING, datetimeserial(0 TO 1000) AS double
DIM open1(0 TO 1000) AS DOUBLE , high1(0 TO 1000) AS DOUBLE , low1(0 TO 1000) AS DOUBLE , close1(0 TO 1000) AS DOUBLE , volume1(0 TO 1000) AS INTEGER, date1(0 TO 1000) AS STRING, time1(0 TO 1000) AS STRING, datetimeserial1(0 TO 1000) AS double
DIM open5(0 TO 1000) AS DOUBLE , high5(0 TO 1000) AS DOUBLE , low5(0 TO 1000) AS DOUBLE , close5(0 TO 1000) AS DOUBLE , volume5(0 TO 1000) AS INTEGER, date5(0 TO 1000) AS STRING, time5(0 TO 1000) AS STRING, datetimeserial5(0 TO 1000) AS double
DIM open15(0 TO 1000) AS DOUBLE , high15(0 TO 1000) AS DOUBLE , low15(0 TO 1000) AS DOUBLE , close15(0 TO 1000) AS DOUBLE , volume15(0 TO 1000) AS INTEGER, date15(0 TO 1000) AS STRING, time15(0 TO 1000) AS STRING, datetimeserial15(0 TO 1000) AS double
DIM open30(0 TO 1000) AS DOUBLE , high30(0 TO 1000) AS DOUBLE , low30(0 TO 1000) AS DOUBLE , close30(0 TO 1000) AS DOUBLE , volume30(0 TO 1000) AS INTEGER, date30(0 TO 1000) AS STRING, time30(0 TO 1000) AS STRING, datetimeserial30(0 TO 1000) AS double
DIM open60(0 TO 1000) AS DOUBLE , high60(0 TO 1000) AS DOUBLE , low60(0 TO 1000) AS DOUBLE , close60(0 TO 1000) AS DOUBLE , volume60(0 TO 1000) AS INTEGER, date60(0 TO 1000) AS STRING, time60(0 TO 1000) AS STRING, datetimeserial60(0 TO 1000) AS double
DIM open240(0 TO 1000) AS DOUBLE , high240(0 TO 1000) AS DOUBLE , low240(0 TO 1000) AS DOUBLE , close240(0 TO 1000) AS DOUBLE , volume240(0 TO 1000) AS INTEGER, date240(0 TO 1000) AS STRING, time240(0 TO 1000) AS STRING, datetimeserial240(0 TO 1000) AS double
DIM open1440(0 TO 1000) AS DOUBLE , high1440(0 TO 1000) AS DOUBLE , low1440(0 TO 1000) AS DOUBLE , close1440(0 TO 1000) AS DOUBLE , volume1440(0 TO 1000) AS INTEGER, date1440(0 TO 1000) AS STRING, time1440(0 TO 1000) AS STRING, datetimeserial1440(0 TO 1000) AS double
DIM open10080(0 TO 1000) AS DOUBLE , high10080(0 TO 1000) AS DOUBLE , low10080(0 TO 1000) AS DOUBLE , close10080(0 TO 1000) AS DOUBLE , volume10080(0 TO 1000) AS INTEGER, date10080(0 TO 1000) AS STRING, time10080(0 TO 1000) AS STRING, datetimeserial10080(0 TO 1000) AS double
DIM open43200(0 TO 1000) AS DOUBLE , high43200(0 TO 1000) AS DOUBLE , low43200(0 TO 1000) AS DOUBLE , close43200(0 TO 1000) AS DOUBLE , volume43200(0 TO 1000) AS INTEGER, date43200(0 TO 1000) AS STRING, time43200(0 TO 1000) AS STRING, datetimeserial43200(0 TO 1000) AS double
dim date2(0 TO 1000) AS STRING
DIM bars AS INTEGER
DIM barsdisplayed2 AS INTEGER
DIM sepindivalmax AS DOUBLE
DIM sepindivalmin AS DOUBLE
'dim sepindizoom as double
'sepindizoom=1
DIM mixgrid AS QSTRINGGRID
DIM mixgridcolcount() AS INTEGER
mixgrid.ColCount = 40
mixgrid.RowCount = 40
DIM mixgrid2 AS QSTRINGGRID
DIM mixgridcolcount2() AS INTEGER
mixgrid2.ColCount = 40
mixgrid2.RowCount = 40
DIM mixgrid3 AS QSTRINGGRID
DIM mixgridcolcount3() AS INTEGER
mixgrid3.ColCount = 40
mixgrid3.RowCount = 40
DIM mixgrid4 AS QSTRINGGRID
DIM mixgridcolcount4() AS INTEGER
mixgrid4.ColCount = 40
mixgrid4.RowCount = 40
DIM scrollchartpositionwait AS INTEGER
DIM graphclick AS INTEGER
graphclick = 0
DIM graphclicktimer AS QTIMER
graphclicktimer.Interval = 1
graphclicktimer.Enabled = 0
DIM firstclickgraph AS INTEGER , firstclickgraphx AS INTEGER , firstclickgraphy AS INTEGER
DIM secondclickgraphx AS INTEGER , secondclickgraphy AS INTEGER
firstclickgraph = 0
DIM sepindiclick AS INTEGER
sepindiclick = 0
DIM sepindiclicktimer AS QTIMER
sepindiclicktimer.Interval = 1
sepindiclicktimer.Enabled = 0
DIM firstclicksepindix AS INTEGER , firstclicksepindiy AS INTEGER
DIM secondclicksepindix AS INTEGER , secondclicksepindiy AS INTEGER
DIM scrollmode AS INTEGER
scrollmode = 0
DIM delsepindirows AS INTEGER
delsepindirows = 0
DIM scrollmodeofftimer AS QTIMER
scrollmodeofftimer.Interval = 2000
scrollmodeofftimer.Enabled = 0
DIM drawtxt AS STRING
DIM btnFont AS QFONT
btnFont.Name = "Arial"
btnFont.AddStyles(fsBold)
btnFont.Color = &h00b4ff
btnFont.Size = 9
DIM showcanvas AS INTEGER
showcanvas = 0
DIM FontDialog AS QFONTDIALOG
DIM Font AS QFONT
Font.Name = "Arial"
Font.Size = 10
DIM red AS INTEGER , orange AS INTEGER , yellow AS INTEGER , green AS INTEGER , blue AS INTEGER , lightblue AS INTEGER , purple AS INTEGER , _
    gray AS INTEGER , black AS INTEGER , pink AS INTEGER , olive AS INTEGER , aqua AS INTEGER , crimson AS INTEGER , gold AS INTEGER , _
    white AS INTEGER , mediumseagreen AS INTEGER , lightgray AS INTEGER , sweetblue AS INTEGER
red = RGB(255 , 0 , 0)
orange = RGB(255 , 128 , 0)
yellow = RGB(255 , 255 , 0)
green = RGB(0 , 255 , 0)
blue = RGB(0 , 0 , 255)
lightblue = RGB(128 , 128 , 255)
purple = RGB(128 , 0 , 255)
gray = RGB(128 , 128 , 128)
black = RGB(0 , 0 , 0)
pink = RGB(255 , 192 , 203)
olive = RGB(0 , 128 , 64)
aqua = RGB(0 , 255 , 255)
crimson = RGB(220 , 20 , 60)
gold = RGB(255 , 215 , 0)
white = RGB(255 , 255 , 255)
lightgray = RGB(208 , 208 , 208)
sweetblue = RGB(166 , 166 , 210)
mediumseagreen = RGB(60 , 179 , 113)
DIM textcolor AS INTEGER
textcolor = blue
DIM sepindicolor(1 TO 100) AS INTEGER
sepindicolor(1) = blue
DIM sepindicolorhisto(1 TO 100,0 TO 1000) AS INTEGER
DIM indicolor(1 TO 100) AS INTEGER
indicolor(1) = blue
DIM pencolor AS INTEGER
pencolor = blue
DIM plotareacolor AS INTEGER
plotareacolor = sweetblue
DIM reverse AS INTEGER
reverse = 0
DIM flip AS INTEGER
flip = 0
DIM homepath AS STRING
homepath = CurDir$
DIM initialpath AS STRING
initialpath = homepath
DIM tmppath AS STRING
DIM ini AS QINI
ini.FileName = homepath + "\QChartist.ini"
dim indiini as qini
DIM mouseexcentricityx AS INTEGER
mouseexcentricityx = 0
DIM mouseexcentricityy AS INTEGER
mouseexcentricityy = 0
DIM graphpriceoncur AS DOUBLE
DIM graphjuliendateoncur AS INTEGER
DIM graphdateoncur AS STRING
DIM graphserialdateoncur AS INTEGER
DIM graphbarnboncur AS INTEGER
DIM graphbarnboncurstatic AS INTEGER
dim graphbarnboncurstaticstr as string
DIM charttypecomboindex AS INTEGER

DIM trendlinesdb AS QSTRINGGRID
DIM fibofandb AS QSTRINGGRID
DIM fiboretdb AS QSTRINGGRID
DIM paradb AS QSTRINGGRID
DIM hlinedb AS QSTRINGGRID
DIM vlinedb AS QSTRINGGRID
DIM sqrdb AS QSTRINGGRID
DIM tridb AS QSTRINGGRID
DIM sqr2db AS QSTRINGGRID
DIM tri2db AS QSTRINGGRID
DIM circledb AS QSTRINGGRID
DIM crossdb AS QSTRINGGRID
DIM invcircledb AS QSTRINGGRID
DIM textdb AS QSTRINGGRID
DIM aimingdb AS QSTRINGGRID
DIM sindb AS QSTRINGGRID
DIM logdb AS QSTRINGGRID
DIM expdb AS QSTRINGGRID
DIM priceextdb AS QSTRINGGRID
DIM ellipsedb AS QSTRINGGRID
DIM pitchforkdb AS QSTRINGGRID
DIM pentagdb AS QSTRINGGRID
DIM sq9fdb AS QSTRINGGRID


' offset of the object drawn on the chart
DIM trendlinesoffset AS INTEGER
DIM fibofanoffset AS INTEGER
DIM fiboretoffset AS INTEGER
DIM paraoffset AS INTEGER
DIM hlineoffset AS INTEGER
DIM vlineoffset AS INTEGER
DIM sqroffset AS INTEGER
DIM trioffset AS INTEGER
DIM sqr2offset AS INTEGER
DIM tri2offset AS INTEGER
DIM circleoffset AS INTEGER
DIM crossoffset AS INTEGER
DIM invcircleoffset AS INTEGER
DIM textoffset AS INTEGER
DIM aimingoffset AS INTEGER
DIM sinoffset AS INTEGER
DIM logoffset AS INTEGER
DIM expoffset AS INTEGER
DIM priceextoffset AS INTEGER
DIM ellipseoffset AS INTEGER
DIM pentagoffset AS INTEGER
DIM pitchforkoffset AS INTEGER
dim sq9foffset AS INTEGER
'DIM orderbuyoffset AS INTEGER
'DIM orderselloffset AS INTEGER

DIM i AS INTEGER , n AS INTEGER
DIM useindi AS QCHECKBOX
DIM leftwidth AS INTEGER
leftwidth = 100
DIM resizesplittimer AS QTIMER
resizesplittimer.Enabled = 0
resizesplittimer.Interval = 1
DECLARE SUB resizesplitcurpos
resizesplittimer.OnTimer = resizesplitcurpos
DIM YVALs AS INTEGER

DIM resizesplithtimer AS QTIMER
resizesplithtimer.Enabled = 0
resizesplithtimer.Interval = 1
DECLARE SUB resizesplithcurpos
resizesplithtimer.OnTimer = resizesplithcurpos
DIM XVALs AS INTEGER
DIM sepindiheight AS INTEGER
sepindiheight = 150
DIM xvalgcp2 AS INTEGER
DIM yvalgcp2 AS INTEGER
TYPE objectcursor
    objtype AS INTEGER
    offset AS INTEGER
END TYPE
DIM moveobjcurtimer AS QTIMER
moveobjcurtimer.Enabled = 0
moveobjcurtimer.Interval = 1
DECLARE SUB moveobjectcursor
moveobjcurtimer.OnTimer = moveobjectcursor
DIM objectcursoroperation AS STRING
DIM xcur1 AS DOUBLE  'integer
DIM xcur2 AS DOUBLE  'integer
DIM ycur1 AS DOUBLE
DIM ycur2 AS DOUBLE
DIM clickedbarnb AS INTEGER
DIM axistypecomboitemindex AS INTEGER
axistypecomboitemindex = 0
DIM xscaletrackbarposition AS DOUBLE
xscaletrackbarposition = 1
DIM beginautotimer AS QTIMER
beginautotimer.Enabled = 0
beginautotimer.Interval = 5000
DECLARE SUB beginauto2
beginautotimer.OnTimer = beginauto2
DIM beginexitsignaltimer AS QTIMER
beginexitsignaltimer.Enabled = 0
beginexitsignaltimer.Interval = 5000
DECLARE SUB beginexitsignal2
DECLARE SUB beginexitsignal3
beginexitsignaltimer.OnTimer = beginexitsignal2


DIM drag AS INTEGER
DIM pbez AS pointapi
DIM curves AS INTEGER
DIM curve AS QMEMORYSTREAM
DIM ipoly AS INTEGER
ipoly = 0
DIM a AS INTEGER
DIM hdc AS LONG
DIM fkey AS INTEGER
DIM sx2(2000) AS INTEGER
DIM sy2(2000) AS INTEGER
DIM btypes(2000) AS BYTE
DIM btype AS INTEGER
btype = 1
DIM bezier? AS INTEGER
bezier? = 0
DIM ptl(600) AS QPANEL
dim cpptmpfuncreturn as string
dim symetryfrompoint as integer
symetryfrompoint=0

trendlinesoffset = 0
fibofanoffset = 0
fiboretoffset = 0
paraoffset = 0
hlineoffset = 0
vlineoffset = 0
sqroffset = 0
trioffset = 0
circleoffset = 0
invcircleoffset = 0
textoffset = 0
aimingoffset = 0
sinoffset = 0
logoffset = 0
expoffset = 0
priceextoffset = 0
ellipseoffset = 0
pitchforkoffset = 0
'orderbuyoffset=0
'orderselloffset=0


DIM firstclickgraphprice AS DOUBLE
DIM secondclickgraphprice AS DOUBLE
DIM firstclickgraphtime AS INTEGER
DIM secondclickgraphtime AS INTEGER
DIM graphserialdateend AS LONG , graphserialdatebegin AS LONG , graphserialdatespace AS LONG
DIM graphhspace AS INTEGER , graphvspace AS INTEGER
DIM graphvlow AS DOUBLE
DIM graphvhigh AS DOUBLE
DIM alltimelow AS DOUBLE
DIM alltimehigh AS DOUBLE
DIM graphpricespace AS DOUBLE
DIM graphhbegin AS INTEGER , graphhend AS INTEGER , graphvbegin AS INTEGER , graphvend AS INTEGER
DIM signaltrigger AS INTEGER
DIM reversecount AS INTEGER
reversecount = 0
DIM upordown AS INTEGER
DIM tmpreverse(0 TO 100) AS STRING
DIM relativecordx AS INTEGER
DIM relativecordy AS INTEGER
dim mousediffx as integer
dim mousediffy as integer
dim mousediffsepindix as integer
dim mousediffsepindiy as integer
DIM relativecordsepindix AS INTEGER
DIM relativecordsepindiy AS INTEGER
DIM mousemovegraphx AS INTEGER
DIM mousemovegraphy AS INTEGER
DIM mousemovesepindix AS INTEGER
DIM mousemovesepindiy AS INTEGER
DIM splitcurposx AS INTEGER
DIM splitcurposy AS INTEGER
dim showdescindopened as integer
showdescindopened=0
dim hidedescindmsgbox as integer
dim cntbarseditstr as string
dim barsstr as string
dim tfmultstr as string
dim lastpointofsymetryx as integer
dim lastpointofsymetryy as integer
dim fibofanangonce as integer
dim cnthotkey as byte
dim ang_a_pub as double
dim chatformtimer as qtimer
chatformtimer.interval=10000
chatformtimer.enabled=0
declare sub chatformtimerexpired
chatformtimer.ontimer=chatformtimerexpired
defdbl ymaxgraphglobal=0.0001
defdbl ymingraphglobal=0.0001

' sweph
Dim iday as integer
Dim imonth as integer
Dim iyear as integer
Dim ihour as single
Dim imin as single
Dim starname As String
Dim lon as double
Dim lat as double
Dim tjd_ut as double
Dim tdj_et as double
defstr parameters

' histogram indicator in separate canvas
dim drawhisto(0 TO 1000) as integer

' helps to know pixel positions of the axes graduations
dim timechartpos(0 to 1000,0 to 1) as long
dim pricechartpos(0 to 1,0 to 1) as double

dim clocktimer as qtimer
declare sub clockontimersub
clocktimer.interval=1000
clocktimer.ontimer=clockontimersub
clocktimer.enabled=1
defstr clockdate,clocktime

dim quotetimer as qtimer
declare sub quoteontimersub
quotetimer.interval=10000
quotetimer.ontimer=quoteontimersub
quotetimer.enabled=0
defstr currentquote="0"

defint astrowheelmarketbar=0

defint lastpricey
defint lastpricex

dim useindiCheckedtmp as integer

declare sub enablegetchartbtnsub
dim getcharttimer as qtimer
getcharttimer.enabled=0
getcharttimer.interval=30000
getcharttimer.ontimer=enablegetchartbtnsub

' ------------------ End of variables declaration ------------------------------

DECLARE SUB moveplanetred
DIM planettimerred AS QTIMER
planettimerred.Enabled = 0
planettimerred.Interval = 100
planettimerred.OnTimer = moveplanetred

DECLARE SUB moveplanetgreen
DIM planettimergreen AS QTIMER
planettimergreen.Enabled = 0
planettimergreen.Interval = 100
planettimergreen.OnTimer = moveplanetgreen

DECLARE SUB moveplanetwhite
DIM planettimerwhite AS QTIMER
planettimerwhite.Enabled = 0
planettimerwhite.Interval = 100
planettimerwhite.OnTimer = moveplanetwhite

DIM planetredbgspeed AS INTEGER
DIM planetgreenbgspeed AS INTEGER
DIM planetwhitebgspeed AS INTEGER
RANDOMIZE
planetredbgspeed = RND(5)
planetgreenbgspeed = RND(5)
planetwhitebgspeed = RND(5)

SCREEN.Cursors(1) = LoadCursorFromFile("cursors\pen_rm.cur")
SCREEN.Cursors(2) = LoadCursorFromFile("cursors\harrow.cur")
SCREEN.Cursors(3) = LoadCursorFromFile("cursors\move_rl.cur")
SCREEN.Cursors(4) = LoadCursorFromFile("cursors\size4_rl.cur")
SCREEN.Cursors(5) = LoadCursorFromFile("cursors\size3_rl.cur")
SCREEN.Cursors(6) = LoadCursorFromFile("cursors\lwait.cur")

DECLARE SUB InitStars

DIM MaxStars AS INTEGER
MaxStars = 333

DIM Starsx(1 TO MaxStars) AS INTEGER
DIM Starsy(1 TO MaxStars) AS INTEGER

SUB InitStars
    DIM Istars AS INTEGER

    RANDOMIZE

    FOR Istars = 1 TO MaxStars
        Starsx(Istars) = RND(600)
        Starsy(Istars) = RND(300 + 10000) - 10000
    NEXT Istars
END SUB

'--------------------------------------------------------------------------------
'Date routines

'From: "cyberrbtmail" <cyberrbtmail@yahoo.com>Thu, 01 Aug 2002 04:50:43 -0000

'To me the easiest technique for working with date and time
'calculations on the PC is to implement DateSerial and TimeSerial.
'The following DateSerial counts the number of days since 1-1-0001.  A
'TimeSerial counts the number of seconds since 00:00:00.

'You can construct numerous library routines founded on these two
'concepts.  Computing TimeSerials is rather simplistic (just count the
'seconds, minutes, and hours ... 60, 60, 24).  Computing DateSerials,
'on the other hand, requires some rather esoteric knowledge of Julian
'and Gregorian calendars.  When PC's were in their infancy, i began
'building such libraries in Assembly.  Later, they were converted to
'C, QBASIC, PASCAL, VB, DELPHI, Perl, JavaScript ... and now to RQ.
'Review the functions and tests below.  This is only a FOUNDATION.
'You can build about two dozen functions using these three:
'IsLeapYear, DateSerial, and DateFromSerial.

'These functions work from Monday January 1, 0001 through Monday, July
'11, 5879611.  VB's DateSerial works for years 100 through 9999.  They
'take into account the Julian to Gregorian transition and the missing
'11 days in the 12th century.

'Here are some advantages of DateSerials:
'* you can store and retrieve dates as numbers
'* you can manipulate dates as numbers
'* you can calculate dates as numbers, e.g.,
'DateSerial + 7 = ThisDayNextWeek
'DateSerialX - DateSerialY = NumberOfDaysBetween
'DateSerial MOD 7 = DayOfWeek (0=SUN; 6=SAT)
'* they are essentially locale independent

'Now to the code.  The Function Declarations here are for ease of use
'due to RQ's single-pass compiler.  Hope this is useful to you and
'others...

DECLARE FUNCTION isLeapYear(Year AS LONG) AS LONG
DECLARE FUNCTION DateSerial(Y AS LONG , M AS LONG , D AS LONG) AS LONG
DECLARE FUNCTION DateFromSerial(DateSerial AS LONG , ByRef Year AS LONG , ByRef Month AS LONG , ByRef Day AS LONG) AS LONG

'SIMPLE USAGE EXAMPLES
'works for Monday January 1, 0001
'through Monday, July 11, 5879611

'the DateSerial long value
'DEFSTR rqcrlf = CHR$(13) + CHR$(10)
'DEFLNG ds1, ds2, DayOfWeek
'ds1 = DateSerial (2002, 7, 27)
'ds2 = DateSerial (2002, 7, 31)
'SHOWMESSAGE "DateSerial (2002, 7, 31) = " + STR$(ds2)

'using DateFromSerial
'DEFLNG yy, mm, dd
'DayOfWeek = DateFromSerial(ds2, yy, mm, dd)
'SHOWMESSAGE "Testing DateFromSerial" + rqcrlf + rqcrlf + _
'"Year = " + STR$(yy) + rqcrlf + _
'"Month = " + STR$(mm) + rqcrlf + _
'"Date = " + STR$(dd) + rqcrlf + _
'"DayOfWeek = " + STR$(DayOfWeek)

'date difference
'DEFLNG DateDiff
'DateDiff = ds2 - ds1
'SHOWMESSAGE "DateSerial(2002, 7, 31) - DateSerial(2002, 7, 27)" + _
'rqcrlf + " = " + STR$(DateDiff)

'quick day of week from DateSerial
'DayOfWeek = ds2 MOD 7
'SHOWMESSAGE "Day of Week from DateSerial" + rqcrlf + _
'"DateSerial(2002, 7, 31) MOD 7 " + rqcrlf + _
'"results in " + STR$(DayOfWeek)

FUNCTION isLeapYear(Year AS LONG) AS LONG
    Result = 0
    IF ((Year MOD 4) = 0) AND ((Year MOD 100) > 0) OR ((Year MOD 400) = 0) THEN Result = 1
END FUNCTION


FUNCTION DateSerial(Y AS LONG , M AS LONG , D AS LONG) AS LONG
    'declare
    DEFLNG daysCount , dayOfMonth , Year , Month

    'initialize
    daysCount = D

    'process
    IF M > 1 THEN
        Month = M
        dayOfMonth = &H3DFF7F9F
        IF Month > 2 AND isLeapYear(Y) THEN dayOfMonth = (dayOfMonth + 32)
        DO
            daysCount = daysCount + (dayOfMonth AND 31)
            IF Month = 2 THEN EXIT DO
            Month = Month - 1
            dayOfMonth = dayOfMonth \ 32
            IF dayOfMonth = 0 THEN dayOfMonth = &H3FEFFBFF
        LOOP
    END IF

    'exit
    Year = (Y - 1)
    Result = daysCount + (CLNG(Year) * 365) + (Year \ 4) - (Year \ 100) + (Year \ 400)
END FUNCTION


FUNCTION DateFromSerial(DateSerial AS LONG , ByRef Year AS LONG , ByRef Month AS LONG , ByRef Day AS LONG) AS LONG
    'declare
    DEFLNG daysCount , dayOfMonth , dayTotal

    'initialize
    Year = 1
    Month = 1
    daysCount = DateSerial - 1

    'pre-process
    IF daysCount > 146096 THEN
        Year = Year + (daysCount \ 146097) * 400
        daysCount = (daysCount MOD 146097)
    END IF
    IF daysCount > 36523 THEN
        dayTotal = (daysCount \ 36524)
        IF dayTotal < 4 THEN
            Year = Year + (dayTotal * 100)
            daysCount = (daysCount MOD 36524)
        ELSE
            Year = Year + 300
            daysCount = 36524
        END IF
    END IF
    IF daysCount > 1460 THEN
        Year = Year + (daysCount \ 1461) * 4
        daysCount = (daysCount MOD 1461)
    END IF
    IF daysCount > 364 THEN
        dayTotal = (daysCount \ 365)
        IF dayTotal < 4 THEN
            Year = Year + dayTotal
            daysCount = (daysCount MOD 365)
        ELSE
            Year = Year + 3
            daysCount = 365
        END IF
    END IF

    'process
    Day = daysCount + 1
    dayOfMonth = &H3DFF7F9F
    IF Day > 58 AND isLeapYear(Year) THEN dayOfMonth = (dayOfMonth + 32)
    DO
        dayTotal = (dayOfMonth AND 31)
        IF dayTotal >= Day THEN EXIT DO
        Day = Day - dayTotal
        Month = Month + 1
        dayOfMonth = (dayOfMonth \ 32)
        IF dayOfMonth = 0 THEN dayOfMonth = &H3FEFFBFF
    LOOP

    'exit
    Result = (DateSerial MOD 7)
END FUNCTION

'This function calculates and returns a julian date given Day,Month,Year.
'Note:
'
FUNCTION JulianDate(Day AS INTEGER , Month AS INTEGER , Year AS INTEGER) AS LONG
    DIM A AS INTEGER
    DIM B AS INTEGER
    DIM Year_Corr AS DOUBLE
    B = 0
    IF Month <= 2 THEN
        DEC(Year)
        INC(Month , 12)
    END IF
    IF (Year * 10000.0 + Month * 100.0 + Day >= 15821015.0) THEN
        A = Year \ 100
        B = 2 - A + A \ 4
    END IF
    IF Year > 0 THEN
        Year_Corr = 0.0
    ELSE
        Year_Corr = 0.75
    END IF
    Result = FIX((365.25 * Year - Year_Corr)) + FIX((30.6001 * (Month + 1) + Day + 1720994 + B))
END FUNCTION

'End date routines
'--------------------------------------------------------------------------------


TYPE mousepos
    xpos AS LONG
    ypos AS LONG
END TYPE

DIM NPOS AS mousepos
DIM nposrela AS mousepos


DIM firsttimevalue AS STRING
DIM firstimefile AS QFILESTREAM
firstimefile.open(homepath + "\config\firsttime.cfg" , fmOpenRead)
firsttimevalue = firstimefile.ReadLine() 'Read an entire line
firstimefile.close

IF firsttimevalue = "1" THEN
    SHOWMESSAGE "Welcome to QChartist!"
END IF


'WinAPI Calls
'CONST GWL_HWNDPARENT = (-8) ' Minimize to task bar
'CONST HWND_DESKTOP = 0
'DECLARE FUNCTION SetWindowLong LIB "user32" ALIAS "SetWindowLongA" (hwnd AS LONG, nIndex AS LONG,_
'dwNewLong AS LONG) AS LONG
DECLARE SUB SetFocus LIB "USER32" ALIAS "SetFocus"(HWnd AS LONG)
DECLARE SUB mouse_event LIB "User32.dll" ALIAS "mouse_event"(dwflag AS LONG , dx AS LONG , dy AS LONG , cbutton AS LONG , dwextra AS LONG)

'-------------------------------------------------------------------------------
'Global hotkeys declaration

'$TYPECHECK ON

'CONST WM_HOTKEY = &H312

'CONST MOD_CTRL = &H2
'CONST MOD_SHFT = &H4
'CONST MOD_ALT = &H1
'CONST MOD_GENERIC = &H0
'Const VK_ESCAPE = &H1B
'Const VK_SPACE = &H20


'DECLARE FUNCTION RegisterHotKey LIB "USER32" ALIAS "RegisterHotKey" _
'(hWnd AS LONG, ID AS LONG, fsModifiers AS LONG, _
'vk AS LONG) AS LONG
'DECLARE FUNCTION UnRegisterHotKey LIB "USER32" ALIAS "UnregisterHotKey" _
'(hWnd AS LONG, ID AS LONG) AS LONG
'DECLARE SUB SetForegroundWindow LIB "USER32" ALIAS "SetForegroundWindow" _
'(HWnd AS LONG)

'DECLARE SUB FormWndProc (hWnd&, uMsg&, wParam&, lParam&)

'End Global hotkeys declaration
'-------------------------------------------------------------------------------


'Code modules (Change path to point to the correct directory on your system)
'$INCLUDE "Common.inc"


DECLARE SUB hide_crossform
DECLARE SUB hide_sq144form
DECLARE SUB hide_sq9form
DECLARE SUB hide_fibofanform
DECLARE SUB hide_polygform
DECLARE SUB hide_sinform
DECLARE SUB crossremovebtnclick
DECLARE SUB crossaddbtnclick
'-====================================== Drawing tools Settings forms =============================================-

CREATE crossform AS QFORM

    Center
    Caption = "Settings for: Cross"
    Visible = 0

    Top = 586
    Left = 422
    Width = 477
    Height = 358
    CREATE crosslevelslab AS QLABEL
        Left = 0
        Top = 0
        Caption = "Levels:"
    END CREATE

    CREATE crosslevelslist AS QLISTBOX
        Left = crosslevelslab.Width + 100
        Top = 0
        AddItems "0"
        AddItems "0.236"
        AddItems "0.382"
        AddItems "0.5"
        AddItems "0.618"
        AddItems "1"
    END CREATE

    CREATE crossremovebtn AS QBUTTON
        Left = crosslevelslab.Width + 100
        Top = crosslevelslist.Top + crosslevelslist.Height
        Width = crosslevelslist.Width / 2
        Caption = "Remove"
        OnClick = crossremovebtnclick
    END CREATE

    CREATE crossaddbtn AS QBUTTON
        Left = crosslevelslab.Width + 100 + crosslevelslist.Width / 2
        Top = crosslevelslist.Top + crosslevelslist.Height
        Width = crosslevelslist.Width / 2
        Caption = "Add"
        OnClick = crossaddbtnclick
    END CREATE

    CREATE crossbtnok AS QBUTTON
        Left = 0
        Top = crosslevelslab.Top + crosslevelslab.Height + 15
        Caption = "OK"
        OnClick = hide_crossform
    END CREATE

END CREATE

SUB hide_crossform
    crossform.Visible = 0
END SUB

CREATE sq144form AS QFORM

    Center
    Caption = "Settings for: SQ144"
    Visible = 0

    Top = 586
    Left = 422
    Width = 477
    Height = 358
    CREATE sq144factlab AS QLABEL
        Left = 0
        Top = 0
        Caption = "Factor:"
    END CREATE

    CREATE sq144edit AS QEDIT
        Left = sq144factlab.Width + 100
        Top = 0
        Text = "1"
    END CREATE

    CREATE sq144dirlab AS QLABEL
        Left = 0
        Top = 30
        Caption = "Direction:"
    END CREATE

    CREATE sq144diredit AS QEDIT
        Left = sq144dirlab.Width + 100
        Top = 30
        Text = "1"
    END CREATE


    CREATE sq144btnok AS QBUTTON
        Left = 0
        Top = sq144dirlab.Top + sq144dirlab.Height + 15
        Caption = "OK"
        OnClick = hide_sq144form
    END CREATE

END CREATE

SUB hide_sq144form
    sq144form.Visible = 0
END SUB

CREATE fibofanform AS QFORM

    Center
    Caption = "Settings for: fibofan"
    Visible = 0

    Top = 586
    Left = 422
    Width = 477
    Height = 358
    CREATE fibofanstandardradio AS qradiobutton
        Left = 0
        Top = 0
        Caption = "Standard"
        checked=1
        onclick=fibofanstandardradioclickedsub
    END CREATE

    CREATE fibofansymetryfrompointradio AS qradiobutton
        Left = 0
        Top = 30
        Caption = "Symetry from point"
        onclick=fibofansymetryfrompointradioclickedsub
    END CREATE

    CREATE fibofanbtnok AS QBUTTON
        Left = 0
        Top = 60
        Caption = "OK"
        OnClick = hide_fibofanform
    END CREATE

END CREATE

SUB hide_fibofanform
    fibofanform.Visible = 0
END SUB

CREATE sq9form AS QFORM

    Center
    Caption = "Settings for: SQ9"
    Visible = 0

    Top = 586
    Left = 422
    Width = 477
    Height = 358
    CREATE sq9factlab AS QLABEL
        Left = 0
        Top = 0
        Caption = "Factor:"
    END CREATE

    CREATE sq9edit AS QEDIT
        Left = sq9factlab.Width + 100
        Top = 0
        Text = "100"
    END CREATE

    CREATE sq9dirlab AS QLABEL
        Left = 0
        Top = 30
        Caption = "Direction:"
    END CREATE

    CREATE sq9diredit AS QEDIT
        Left = sq9dirlab.Width + 100
        Top = 30
        Text = "1"
    END CREATE


    CREATE sq9btnok AS QBUTTON
        Left = 0
        Top = sq9dirlab.Top + sq9dirlab.Height + 15
        Caption = "OK"
        OnClick = hide_sq9form
    END CREATE

END CREATE

SUB hide_sq9form
    sq9form.Visible = 0
END SUB

CREATE polygform AS QFORM

    Center
    Caption = "Settings for: polygone"
    Visible = 0

    Top = 586
    Left = 422
    Width = 477
    Height = 358
    CREATE pentagoneradio AS qradiobutton
        Left = 0
        Top = 0
        Caption = "Pentagone"
        checked=1
    END CREATE

    CREATE hexagoneradio AS qradiobutton
        Left = 0
        Top = 30
        Caption = "Hexagone"
    END CREATE
    
    CREATE octogoneradio AS qradiobutton
        Left = 0
        Top = 60
        Caption = "Octogone"
    END CREATE

    CREATE polygbtnok AS QBUTTON
        Left = 0
        Top = 90
        Caption = "OK"
        OnClick = hide_polygform
    END CREATE

END CREATE

SUB hide_polygform
    polygform.Visible = 0
END SUB

CREATE sinform AS QFORM

    Center
    Caption = "Settings for: sinusoïd"
    Visible = 0

    Top = 586
    Left = 422
    Width = 477
    Height = 358
    CREATE horizsinradio AS qradiobutton
        Left = 0
        Top = 0
        Caption = "Horizontal sinusoïd"
        checked=1
    END CREATE

    CREATE sinfromtrendlineradio AS qradiobutton
        Left = 0
        Top = 30
        Caption = "Sinusoïd from trendline"
    END CREATE        

    CREATE sinbtnok AS QBUTTON
        Left = 0
        Top = 90
        Caption = "OK"
        OnClick = hide_sinform
    END CREATE

END CREATE

SUB hide_sinform
    sinform.Visible = 0
END SUB

'-====================================== End Drawing tools Settings forms =============================================-

SUB crossremovebtnclick
    crosslevelslist.DelItems(crosslevelslist.ItemIndex)
END SUB

SUB crossaddbtnclick
    DIM inputcrosslevel AS qinputbox , crossaddlevelstxt AS STRING
    crossaddlevelstxt = inputcrosslevel.INPUT("Enter your level:")
    crosslevelslist.AddItems VAL(crossaddlevelstxt)
END SUB

declare sub symbolrefreshintervaleditonchange
declare sub getquoteonoffbutonclick
declare sub previousbarbuttonclick
declare sub nextbarbuttonclick

create astrowheelsettingsform as qform

    height=600
    width=600
    
    create pointsper360deglab as qlabel
    caption="Points per 360 degrees:"
    top=0
    left=0
    end create
    
    create pointsper360degedit as qedit
    text="24"
    top=0
    left=pointsper360deglab.left+pointsper360deglab.width
    end create   
    
    create latitudelab as qlabel
    caption="Latitude in degrees:"
    top=40
    left=0
    end create
    
    create latitudeedit as qedit
    text="48.5833"
    top=40
    left=latitudelab.left+latitudelab.width
    end create
    
    create longitudelab as qlabel
    caption="Longitude in degrees:"
    top=60
    left=0
    end create
    
    create longitudeedit as qedit
    text="7.75"
    top=60
    left=longitudelab.left+longitudelab.width
    end create
    
    create timezonelab as qlabel
    caption="Timezone:"
    top=80
    left=0
    end create
    
    create timezoneedit as qedit
    text="-1"
    top=80
    left=timezonelab.left+timezonelab.width
    end create
    
    create summertime as qcheckbox
    caption="Summer time"
    top=80
    left=timezoneedit.left+timezoneedit.width
    end create
    
    create symbollab as qlabel
    caption="Symbol:"
    top=100
    left=0
    end create
    
    create symboledit as qedit
    text="EURUSD"
    top=100
    left=symbollab.left+symbollab.width
    end create
    
    create symboltypegroupbox as qgroupbox
    left=symboledit.left+symboledit.width
    top=100
    width=200
    create currencytype as qradiobutton
    caption="Currency"
    left=0
    top=0
    end create
    create stocktype as qradiobutton
    caption="Stock"
    left=currencytype.left+currencytype.width
    top=0
    end create
    end create  
    
    create placecombobox as qcombobox
    top=100
    left=380
    additems "australia","dwsfunds","fidelity","tiaacref","troweprice","europe","canada","usa","nyse","nasdaq","uk_unit_trusts","vanguard","vwd"
    itemindex=7
    end create
    
    create symbolrefreshintervallab as qlabel
    caption="Refresh every ? ms:"
    top=120
    left=0
    end create
    
    create symbolrefreshintervaledit as qedit
    text="10000"
    top=120
    left=symbolrefreshintervallab.left+symbolrefreshintervallab.width
    onchange=symbolrefreshintervaleditonchange
    end create
    
    create getquoteonofflab as qlabel
    caption="Realtime price-time:"
    top=140
    left=0
    end create
     
    create getquoteonoffbut as qbutton
    caption="Start"
    top=140
    left=getquoteonofflab.left+getquoteonofflab.width
    onclick=getquoteonoffbutonclick
    end create
    
    create specifydatelab as qlabel
    caption="Market date:"
    top=160
    left=0
    end create            
    
    CREATE specifydatecal AS qcalendar
        loadcal(DATE$)
        top=180
        left=0
    END CREATE
    
    CREATE specifytimelab AS QLABEL
        Top = specifydatecal.Top + specifydatecal.Height
        left=0
        Caption = "Market time: "
    END CREATE
    
    CREATE specifytimeedit AS QEDIT
        Top = specifytimelab.Top
        Left = specifytimelab.left+specifytimelab.Width
        Width = 50
        Text = "00:00"
    END CREATE
    
    create previousbarbutton as qbutton
    caption="Previous bar"
    top=specifytimeedit.top
    left=specifytimeedit.left+specifytimeedit.width
    onclick=previousbarbuttonclick
    end create
    
    create nextbarbutton as qbutton
    caption="Next bar"
    top=previousbarbutton.top
    left=previousbarbutton.left+previousbarbutton.width
    onclick=nextbarbuttonclick
    end create
    
    create marketpostponementlab1 as qlabel
    caption="Time of the market +"
    left=0
    top=specifytimeedit.top+30
    end create   
    
    create marketpostponement as qedit
    text="5"
    width=40
    left=marketpostponementlab1.left+marketpostponementlab1.width
    top=marketpostponementlab1.top
    end create
    
    create marketpostponementlab2 as qlabel
    caption="hours = my local time"
    left=marketpostponement.left+marketpostponement.width
    top=marketpostponement.top
    end create
    
    create pricesource as qgroupbox
    top=marketpostponementlab2.top+20
    width=300
    left=0
    create openedchartpriceradio as qradiobutton
    caption="Use price of the opened chart for the specified date time"
    width=300
    top=0
    left=0
    end create
    create specifypriceradio as qradiobutton
    caption="Specify price manually:"
    width=150
    top=20
    left=0
    end create
    create specifypriceedit as qedit
    text=""
    top=20
    left=specifypriceradio.left+specifypriceradio.width
    width=80
    end create
    end create
    
    
end create

$INCLUDE "includes\QChart.inc"
'$Include "includes\Qcolordialog.inc"
'$RESOURCE zoommore AS "images\zoommore.bmp"
'$RESOURCE zoomless AS "images\zoomless.bmp"
$RESOURCE QChartistico AS "QChartist.ico"
$RESOURCE iconcircle AS "images\circle.bmp"
$RESOURCE iconcross AS "images\cross.bmp"
$RESOURCE iconfibofan AS "images\fibofan.bmp"
$RESOURCE iconfiboret AS "images\fiboret.bmp"
$RESOURCE iconhline AS "images\hline.bmp"
$RESOURCE iconinvcircle AS "images\invcircle.bmp"
$RESOURCE iconpara AS "images\para.bmp"
$RESOURCE iconsqr AS "images\sqr.bmp"
$RESOURCE icontrendline AS "images\trendline.bmp"
$RESOURCE iconcursor AS "images\cursor.bmp"
$RESOURCE icontri AS "images\tri.bmp"
$RESOURCE iconvline AS "images\vline.bmp"
$RESOURCE iconclose AS "images\closebtn.bmp"
$RESOURCE iconmove AS "images\move_rl.bmp"
$RESOURCE iconaiming AS "images\aiming.bmp"
$RESOURCE iconhandd AS "images\handd.bmp"
$RESOURCE iconsin AS "images\sin.bmp"
$RESOURCE iconlog AS "images\log.bmp"
$RESOURCE iconexp AS "images\exp.bmp"
$RESOURCE iconpriceext AS "images\priceext.bmp"
$RESOURCE iconreverse AS "images\reverse.bmp"
$RESOURCE iconflip AS "images\flip.bmp"
$RESOURCE iconellipse AS "images\ellipse.bmp"
$RESOURCE iconpitchfork AS "images\pitchfork.bmp"
$RESOURCE iconsettings AS "images\settings.bmp"
$RESOURCE leftarrow AS "images\left_arrow.bmp"
$RESOURCE rightarrow AS "images\right_arrow.bmp"
$RESOURCE icontimeext AS "images\timeext.bmp"
$RESOURCE icontimecycles AS "images\timecycles.bmp"
$RESOURCE iconpricecycles AS "images\pricecycles.bmp"
$RESOURCE iconlogspiral AS "images\logspiral.bmp"
$RESOURCE iconpoly AS "images\poly.bmp"
$RESOURCE iconpentag AS "images\pentagram.bmp"
$RESOURCE iconorcycles AS "images\orcycles.bmp"
$RESOURCE iconpolyg AS "images\polygone.bmp"
$RESOURCE pricescaleplus AS "images\pricescaleplus.bmp"
$RESOURCE pricescaleminus AS "images\pricescaleminus.bmp"
$RESOURCE iconaddbars AS "images\addbars.bmp"

DIM colordlg AS qcolordialog
colordlg.Style = cdFullOpen
colordlg.Caption = "Select Color"


'Form Event declaring sub routines
DECLARE SUB btnOnClick(SENDER AS QBUTTON)
DECLARE SUB frmMainResize(SENDER AS QFORM)
DECLARE SUB frmMainClose(SENDER AS QFORM)
DECLARE SUB Buttonf2Click(Sender AS QBUTTON)
DECLARE SUB importfile()
DECLARE SUB importfile2()
DECLARE SUB exportfile()
DECLARE SUB exportfilename()
DECLARE SUB exportcollection()
DECLARE SUB setup()
DECLARE SUB Scrolling()
DECLARE SUB dispbarsok_click()
DECLARE SUB dispbarspd()
DECLARE SUB dispbarspu()
DECLARE SUB dispbarsmd()
DECLARE SUB dispbarsmu()
DECLARE SUB TimerOverdispbarsp()
DECLARE SUB TimerOverdispbarsm()
DECLARE SUB closedispchart_click()
DECLARE SUB dispchartnbchanged()
DECLARE SUB tfmultok_click()
DECLARE SUB tfmultp_click()
DECLARE SUB tfmultm_click()
DECLARE SUB TimerOvergraphtimer()
DECLARE SUB indiform()
DECLARE SUB btnaddindi_click()
DECLARE SUB btndelindi_click()
DECLARE SUB refresh_chart()
DECLARE SUB reimportfile()
DECLARE SUB settingsclick()
'declare sub sepindizoommoreclick()
'declare sub sepindizoomlessclick()
DECLARE SUB quit()
DECLARE SUB about()
DECLARE SUB mixerform()
DECLARE SUB reversebarscomputesub
DECLARE SUB reversebarscomputesubb(referencialk AS INTEGER)
DECLARE SUB importfileaddition()
DECLARE SUB importfileadditiondel()
DECLARE SUB importfilesubtraction()
DECLARE SUB importfilesubtractiondel()
DECLARE SUB importfilemultiply()
DECLARE SUB importfilemultiplydel()
DECLARE SUB importfiledivide()
DECLARE SUB importfiledividedel()
DECLARE SUB otheropssub()
DECLARE SUB updatemixerlists()
'DEFSNG rad = 3.1415927/180 ' to convert to radians
DECLARE SUB paint
DECLARE SUB paintabout(Sender AS QCANVAS)
DECLARE SUB ClearAll2
DECLARE SUB draw(ang AS SINGLE , dis AS SINGLE)
'DECLARE SUB drawplot(xb AS SINGLE, yb AS SINGLE)
DECLARE SUB drawindi()
DECLARE SUB drawindi2(xb AS SINGLE , yb AS SINGLE)
DECLARE SUB drawchart2
DECLARE SUB drawxy2
DECLARE SUB ClearBuffer2
DECLARE SUB DetPos
DECLARE SUB graphclicked
DECLARE SUB timerovergraphclick
DECLARE SUB trendlinebtnclick
DECLARE SUB cursorbtnclick
DECLARE SUB fibofanbtnclick
DECLARE SUB fiboretbtnclick
DECLARE SUB pricecyclesbtnclick
DECLARE SUB timecyclesbtnclick
DECLARE SUB logspiralbtnclick
declare sub pentagbtnclick
declare sub polygbtnclick
DECLARE SUB parabtnclick
DECLARE SUB orcyclesbtnclick
DECLARE SUB hlinebtnclick
DECLARE SUB polybtnclick
DECLARE SUB vlinebtnclick
DECLARE SUB sqrbtnclick
DECLARE SUB tribtnclick
DECLARE SUB sqr2btnclick
DECLARE SUB tri2btnclick
DECLARE SUB circlebtnclick
DECLARE SUB crossbtnclick
DECLARE SUB invcirclebtnclick
DECLARE SUB textbtnclick
DECLARE SUB aimingbtnclick
DECLARE SUB handdbtnclick
DECLARE SUB clearbtnclick
DECLARE SUB sinbtnclick
DECLARE SUB logbtnclick
DECLARE SUB expbtnclick
DECLARE SUB priceextbtnclick
DECLARE SUB reversebtnclick
DECLARE SUB flipbtnclick
DECLARE SUB ellipsebtnclick
DECLARE SUB pitchforkbtnclick
DECLARE SUB sq9fbtnclick
DECLARE SUB sq144btnclick
DECLARE SUB settingsbtnclick
DECLARE SUB importcsv
DECLARE SUB importbmp
DECLARE SUB showtoolsinfo
DECLARE SUB formtoolsinforesized
DECLARE SUB dispinfotext(infotxt AS STRING)
DECLARE SUB DetPos2
DECLARE SUB sepindiclicked
DECLARE SUB timeroversepindiclick
DECLARE SUB setspaceforwards
DECLARE SUB resetbtns
DECLARE SUB freeze
DECLARE SUB unfreeze
DECLARE SUB scrollmodebtnclick
DECLARE SUB disablescrollmode
DECLARE SUB scrollmodeoff
DECLARE SUB chartscursormode(mode AS INTEGER)
DECLARE SUB enterdrawtxt
DECLARE SUB hide_averagerangeform()
DECLARE SUB hide_cogform()
'declare sub movebtngroupbox
'declare sub movetoolsgroupbox
'declare sub movebtnclick
DECLARE SUB closedispcanvas_click
DECLARE SUB showcanvasclick
DECLARE SUB choosepencolor
DECLARE SUB choosetextfont
DECLARE SUB showdescrindi
DECLARE FUNCTION txtformat(descrmsg AS STRING) AS STRING
DECLARE SUB showeditor
DECLARE SUB graphmousedown(Button AS INTEGER , x AS INTEGER , y AS INTEGER)
DECLARE SUB sepindimousedown(Button AS INTEGER , x AS INTEGER , y AS INTEGER)
DECLARE SUB trackbchange
DECLARE SUB settingsbtnclick
DECLARE SUB hideformp(frmname AS QFORM)
DECLARE SUB showformp(frmname AS QFORM)
DECLARE SUB graphcursorpos(x AS INTEGER , y AS INTEGER)
DECLARE SUB sepindicursorpos(x AS INTEGER , y AS INTEGER)
DECLARE SUB graphcursorpos2
DECLARE SUB chooseplotareacolor
DECLARE SUB showobjectslistfrm
DECLARE SUB charttypecombochange
DECLARE SUB justrefreshchart
DECLARE SUB previoustoolsclick
DECLARE SUB nexttoolsclick
DECLARE SUB timeextbtnclick
DECLARE SUB timesq9fbtnclick
DECLARE SUB timesq144btnclick
DECLARE SUB savebmp
DECLARE SUB printchart
DECLARE SUB frmmainonmw(frmmainr AS INTEGER , frmmainx AS LONG , frmmainy AS LONG , frmmains AS INTEGER)
DECLARE SUB showtoolsclick
DECLARE SUB showtoolbarclick
DECLARE SUB resizesplitmd
DECLARE SUB resizesplitmu
DECLARE SUB resizesplithmd
DECLARE SUB resizesplithmu
DECLARE SUB deleteobjectcursor
DECLARE SUB moveobjectclick(Sender AS QMENUITEM)
DECLARE SUB writetolog(lastlogline AS STRING)
DECLARE SUB refreshgrids
DECLARE SUB refreshgrids2
DECLARE SUB refreshgridsnorefresh
DECLARE SUB useindischeckboxsub
DECLARE SUB tfmultcombosub
DECLARE SUB dispbarsswitchsub
DECLARE SUB findbarfromfile(fbffdate AS STRING , fbfftime AS STRING)
DECLARE SUB useindisub
DECLARE SUB xscaletrackbarsub
DECLARE SUB changepriceratiosub
DECLARE SUB changepriceratiosub2
DECLARE SUB axistypecombosub
DECLARE SUB choosemailer
DECLARE SUB edit1change
DECLARE SUB edit2change
DECLARE SUB edit3change
DECLARE SUB edit4change
DECLARE SUB edit5change

'Setting up separate chart object
DECLARE SUB drawp(TYPE AS INTEGER , xb AS INTEGER , yb AS INTEGER , xc AS INTEGER , yc AS INTEGER , xd AS INTEGER , yd AS INTEGER , txt AS STRING)
DECLARE SUB drawtrendline(xb AS SINGLE , yb AS SINGLE , xc AS SINGLE , yc AS SINGLE)
DECLARE SUB drawfibofan(xb AS SINGLE , yb AS SINGLE , xc AS SINGLE , yc AS SINGLE)
DECLARE SUB initializechart2
DECLARE SUB RedrawChart2
DECLARE SUB savebuffertmp
DECLARE SUB bufcntreset
DECLARE SUB firstbufcntreset
DECLARE SUB savebuffertmpsimple
DECLARE SUB savebuffertmpsimplez
DECLARE SUB restorebuffertmpz
DECLARE SUB restorebuffertmp
DECLARE SUB restorefirstbuffertmpz
DECLARE SUB reversetillend
DECLARE SUB deleteafter
DECLARE SUB reversetillendnorefresh
DECLARE SUB reversetillendfromfile
DECLARE SUB chartconvsub
DECLARE SUB exp10sub
DECLARE SUB showfrmlogreverse
DECLARE SUB frmlogreverseresized
DECLARE SUB frmreadmeresized
DECLARE SUB frmwhatsnewresized
DECLARE SUB tfmultchange
DECLARE SUB findbar
DECLARE SUB findbarsub
DECLARE SUB disableallindis
DECLARE SUB indilist_dblclick
DECLARE SUB autoreverse
DECLARE SUB followmode
DIM followmodetimer AS QTIMER
followmodetimer.Interval = 30000
followmodetimer.Enabled = 0
followmodetimer.OnTimer = followmode
DECLARE SUB stopclicked
DECLARE SUB filesettings
DECLARE SUB ChangeDirectory
DECLARE SUB mtpathform
DECLARE SUB mtpathexitform
DECLARE SUB ChangeDirectories
DECLARE SUB choosefile
DECLARE SUB filesettingsfrmokclicked
DECLARE SUB importfileauto(ifafilename AS STRING)
DECLARE SUB importfileauto2(filenameauto AS STRING)
DECLARE SUB importfileauto3(ifafilename AS STRING)
DECLARE SUB importfile1m(filenameauto AS STRING)
DECLARE SUB signalsnd
DECLARE SUB signalsndfrmclose
DECLARE SUB dirdrivebtnclicked
DECLARE SUB writealive
DECLARE SUB writealive2
DECLARE SUB barsdisplayedchange
DECLARE SUB cntbarseditchange
DECLARE SUB toolssettings
DECLARE SUB beginauto
DECLARE SUB beginexitsignal
DECLARE SUB fdown(button AS LONG , x AS LONG , y AS LONG , shift AS INTEGER)
DECLARE SUB fpaint(sender AS QFORM)
DECLARE SUB pdown(but AS LONG , x AS LONG , y AS LONG , _
    shift AS INTEGER , sender AS QPANEL)
DECLARE SUB pup(button AS LONG , x AS LONG , y AS LONG , _
    shift AS INTEGER , sender AS QPANEL)
DECLARE SUB pmove(x AS LONG , y AS LONG , _
    shift AS INTEGER , sender AS QPANEL)
DECLARE SUB keydown(key AS LONG , sender AS QFORM)
DECLARE SUB fkeyup(sender AS QFORM)
DECLARE SUB operations
DECLARE SUB bezbuttonclick
DECLARE SUB polyclick
DECLARE SUB mailersub
DECLARE SUB followmodeactivate
DECLARE SUB savemailersub
DECLARE SUB restoremailersub
DECLARE SUB datasource
DECLARE SUB dsokclick
DECLARE SUB importfileyahoo()
DECLARE SUB exportfileyahoo()
DECLARE SUB importfilestooq()
DECLARE SUB importfilegoogle()
DECLARE SUB savegridtmp
declare sub attribtf
declare sub attribtfeditItemChanged
declare sub writetf (dispfile as integer,tftowrite as integer)
declare function ibarshift (timeframe as integer,datetimeserial as double,limit as integer) as integer
declare sub openhelpsub
declare sub viewreadme
declare sub viewwhatsnew
declare sub speechinitialization
declare sub speechdeinitialization
declare sub checkusespeech
declare sub showspeechform
declare SUB say(speech AS string)
declare sub exportfileauto()
declare sub exportcollectionauto()
declare Function StripFileName (fullname as string) as string
declare sub updates
Declare Function InetIsOffline Lib "url.dll" Alias "InetIsOffline" (ByVal _
dwFlags As Long) As Long

DECLARE FUNCTION FGetFileHTTP_URLDownloadToFile LIB "urlmon" ALIAS "URLDownloadToFileA" _
    (ByVal pCaller AS LONG , ByRef szURL AS STRING , ByRef szFileName AS STRING , _
    ByVal dwReserved AS LONG , ByVal lpfnCB AS LONG) AS LONG
    
declare sub whatsnewsub  
declare sub websitesub  

FUNCTION GetFileHTTP(URL AS STRING , toFile AS STRING) AS LONG
    DEFSTR sURL , sToFile
    sURL = URL
    sToFile = toFile
    GetFileHTTP = FGetFileHTTP_URLDownloadToFile(0 , sURL , sToFile , 0 , 0)
END FUNCTION

declare sub hotkeysub
declare sub chatformsub
declare sub swephformsub
declare sub swephformonshowsub
declare sub chatformonshowsub
declare sub chatformonclosesub
declare sub sendmsgbtnonclicksub
declare sub sendmsgeditkeydown(Key AS WORD)
declare function monthtostr(month as integer) as string
declare function strtomonth(str as string) as string
declare sub dssymbolcombochange
declare sub reimportfilesub
declare sub pricescaleplusbtnclick
declare sub pricescaleminusbtnclick

' sweph
declare sub Compute_sweph_Click
declare Function outdeg(x As Double) As String
declare Function outdeg3(x As Double) As String
declare Function set_strlen(c$) As String
declare Sub bary_flag_Click()
declare Sub Day_Change()
declare Sub fstar_Change()
declare Sub geolat_Change()
declare Sub geolon_Change()
declare Sub hel_flag_Click()
declare Sub hour_Change()
declare Sub minute_Change()
declare Sub Month_Change()
declare Sub Year_Change()

declare sub detect_timeframe
declare sub addbars

declare sub astrowheelsettingssub

declare sub googlebusytimersub
declare sub googlerealtimebusytimersub
declare sub googlegetquotesub
declare sub googlequotetimerstartsub
declare function timeminute(seconds as double) as double
declare function timehour(seconds as double) as double
declare function timedayofweek(seconds as double) as double
declare sub loginsub
declare sub googlerefreshrateeditchangesub

declare sub showsymbolslist
declare sub loadsymbolslistsub
declare sub markettypecombochangesub
declare sub searchsymbolslistbtnsub
declare sub searchnextsymbolslistbtnsub
declare sub updatesymbolslistbtnsub
declare sub reloadsymbolslistbtnsub
declare sub restoredefaultdatabtnsub
declare sub selectsymbolslistbtnsub
declare sub loadsymbolslistbtnsub
declare sub symbolslistboxonclicksub
declare sub symbolslistboxondblclicksub

dim googlebusytimer as qtimer
googlebusytimer.enabled=0
googlebusytimer.interval=1000
googlebusytimer.ontimer=googlebusytimersub

declare sub googlereadlastquoteontimersub
dim googlereadlastquotetimer as qtimer
googlereadlastquotetimer.enabled=0
googlereadlastquotetimer.interval=5000
googlereadlastquotetimer.ontimer=googlereadlastquoteontimersub


dim googlerealtimebusytimer as qtimer
googlerealtimebusytimer.enabled=0
googlerealtimebusytimer.interval=1000
googlerealtimebusytimer.ontimer=googlerealtimebusytimersub

defstr googlegoingto=""

dim googlegetquotetimer as qtimer
googlegetquotetimer.enabled=0
googlegetquotetimer.interval=3000
googlegetquotetimer.ontimer=googlegetquotesub

defint googlecurrenttimestamp
defint googlereadlastquotetimestamp
defint quotenexttimestamp
defint filevoltmp=0
defint filevol=0
defint firstfilevol=1

'From:  "Pascal Delcombel Wed Dec 11, 2002  4:45 pm
' Add / remove Windows font
'Install Font (just for windows's session, all application may see it)
'P. Delcombel / December 2002
dim FontFileName as string
FontFileName = "c:\qchartist\fonts\astro.ttf"
AddFontResource(FontFileName)

declare function get_helio_longitude(planet as integer,year as string,month as string,day as string,hour as string) as string
declare function get_ascmc(lat2 as double,lon2 as double,year as string,month as string,day as string,hour as string,ascormc as string) as string

' End of functions declaration

' --- Astro include files ---
$include "includes\time.inc"
$include "includes\astro.inc"
' ---------------------------

DIM writealivetimer AS QTIMER
writealivetimer.Interval = 10000
writealivetimer.Enabled = 0
writealivetimer.OnTimer = writealive

DIM bufcntsep AS INTEGER
bufcntsep = 0
DIM firstbufcntsep AS INTEGER
firstbufcnt = 0

'ontimer directives
Timerdispbarsp.OnTimer = TimerOverdispbarsp
Timerdispbarsm.OnTimer = TimerOverdispbarsm
graphclicktimer.OnTimer = timerovergraphclick
sepindiclicktimer.OnTimer = timeroversepindiclick
scrollmodeofftimer.OnTimer = scrollmodeoff

TYPE qchart2 EXTENDS QCANVAS

    PRIVATE :
    BMP AS QBITMAP
    Buffertmp AS QBITMAP
    buffertmpz AS QBITMAP
    buffertmpz2 AS QBITMAP
    firstbuffertmpz AS QBITMAP

    PUBLIC :
    separateindicator1 AS QSTRINGGRID
    demofont AS QFONT
    demofont2 AS QFONT

    PRIVATE :
    SUB ClearBuffer2  'Erase off screen drawing buffer
        WITH qchart2.BMP
            .FillRect(0 , 0 , .Width , .Height , RGB(255 , 255 , 255))
        END WITH
    END SUB

    private :
    SUB restorebuffertmp
        WITH qchart2
            .BMP.BMP = .buffertmp.BMP
        END WITH
    END SUB

    public :
    SUB restorebuffertmpz
        WITH qchart2
            .BMP.BMP = .buffertmpz.BMP
        END WITH
    END SUB

    public :
    SUB restorefirstbuffertmpz
        WITH qchart2
            .BMP.BMP = .firstbuffertmpz.BMP
        END WITH
    END SUB

    PUBLIC :
    SUB initializechart2
        WITH qchart2
            .BMP.Height = .Height
            .BMP.Width = .Width
            .demofont.Name = "Arial"
            .demofont.Size = 36
            .demofont.Color = &H000000
            .demofont.AddStyles(0) 'Bold
            .demofont2.Name = "Arial"
            .demofont2.Size = 10
            .demofont2.Color = &H000000
            .demofont2.AddStyles(0) 'Bold
        END WITH
    END SUB

    PUBLIC :
    SUB paint
        WITH qchart2
            .draw(0 , 0 , .Buffertmp.BMP)
        END WITH
    END SUB

    PUBLIC :
    SUB ClearAll2
        WITH qchart2
            .initializechart2
            .ClearBuffer2
            .paint
        END WITH
    END SUB

    'Here we draw indicator in separate graph
    PRIVATE :
    SUB drawxy2()
        WITH qchart2
            .ClearBuffer2
        END WITH

        DIM graphyaxisheight AS DOUBLE
        graphyaxisheight = sepindivalmax - sepindivalmin

        IF graphyaxisheight = 0 THEN
            EXIT SUB
        END IF

        DIM barsize AS DOUBLE
        barsize = canvas.Width / barsdisplayed2

        DIM graphratio AS DOUBLE
        graphratio = canvas.Height / graphyaxisheight

        DIM locx AS DOUBLE

        DIM baroffset AS INTEGER
        baroffset = chartstart + 1

        DIM value AS DOUBLE , value2 AS DOUBLE
        DIM sepindivalue AS DOUBLE , sepindivalue2 AS DOUBLE
        DIM i AS INTEGER
        DIM j AS INTEGER
        DIM closevalue AS DOUBLE
        DIM closevalue2 AS DOUBLE

        FOR j = 2 TO canvas.separateindicator1.RowCount STEP 2
            locx = 0
            FOR i = 0 TO barsdisplayed2-2
                closevalue = VAL(canvas.separateindicator1.Cell(j , i+1))
                closevalue2 = VAL(canvas.separateindicator1.Cell(j , i + 2))
                IF axistypecomboitemindex = 1 THEN
                    IF closevalue > 0 AND closevalue2 > 0 THEN
                        closevalue = log10(closevalue)
                        closevalue2 = log10(closevalue2)
                    END IF
                END IF
                value = closevalue - sepindivalmin
                value = value * graphratio
                sepindivalue = (canvas.Height - value)
                value2 = closevalue2 - sepindivalmin
                value2 = value2 * graphratio
                sepindivalue2 = (canvas.Height - value2)                
                WITH qchart2
                    'MoveToEx(.bmp.handle,locx,sepindivalue ,0)
                    'LineTo(.bmp.handle,locx+barsize,sepindivalue2 )                    
                    if drawhisto(j)=1 then
                    .bmp.fillrect(locx+ barsize/2,sepindivalue2,locx + barsize+ barsize/2,sepindivalue2-9, sepindicolorhisto(j,i+2))
                    '.BMP.Line(locx , sepindivalue-0.2 , locx + barsize , sepindivalue2-0.2 , sepindicolorhisto(j,i+2))
                    '.BMP.Line(locx , sepindivalue-0.1 , locx + barsize , sepindivalue2-0.1 , sepindicolorhisto(j,i+2))
                    '.BMP.Line(locx , sepindivalue , locx + barsize , sepindivalue2 , sepindicolorhisto(j,i+2))
                    '.BMP.Line(locx , sepindivalue+0.1 , locx + barsize , sepindivalue2+0.1 , sepindicolorhisto(j,i+2))
                    '.BMP.Line(locx , sepindivalue+0.2 , locx + barsize , sepindivalue2+0.2 , sepindicolorhisto(j,i+2))
                    else
                    .BMP.Line(locx , sepindivalue , locx + barsize , sepindivalue2 , sepindicolor(j))
                    end if
                END WITH                
                'if j=2 then print str$(i+2)+" "+canvas.separateindicator1.Cell(j , i + 2)+" "+str$(sepindicolorhisto(j,i+2))
                baroffset ++
                locx = locx + barsize
                doevents
            NEXT i
            doevents
        NEXT j

    END SUB

    'End of draw indicator in separate graph    

    private :
    SUB drawtrendline(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x3,y3)
            .BMP.Line(x2 , y2 , x3 , y3 , pencolor)
            .buffertmp.BMP = .BMP.BMP
            .paint
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawfibofan(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x3,y3)
            .BMP.Line(x2 , y2 , x3 , y3 , pencolor)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            DIM x4 AS DOUBLE
            x4 = x3 + (x3 - x2)
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x4,y3)
            .BMP.Line(x2 , y2 , x4 , y3 , pencolor)
            x4 = x3 + (x3 - x2) * 0.618
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x4,y3)
            .BMP.Line(x2 , y2 , x4 , y3 , pencolor)
            x4 = x3 + (x3 - x2) * 1.618
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x4,y3)
            .BMP.Line(x2 , y2 , x4 , y3 , pencolor)
            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB

    private :
    SUB drawfiboret(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x3,y3)
            .BMP.Line(x2 , y2 , x3 , y3 , pencolor)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x3,y2)
            'MoveToEx(.bmp.handle,x2,y3,0)
            'LineTo(.bmp.handle,x3,y3)
            .BMP.Line(x2 , y2 , x3 , y2 , pencolor)
            .BMP.Line(x2 , y3 , x3 , y3 , pencolor)
            DIM y4 AS DOUBLE
            y4 = y2 + (y3 - y2) * 0.236
            'MoveToEx(.bmp.handle,x2,y4,0)
            'LineTo(.bmp.handle,x3,y4)
            .BMP.Line(x2 , y4 , x3 , y4 , pencolor)
            y4 = y2 + (y3 - y2) * 0.382
            'MoveToEx(.bmp.handle,x2,y4,0)
            'LineTo(.bmp.handle,x3,y4)
            .BMP.Line(x2 , y4 , x3 , y4 , pencolor)
            y4 = y2 + (y3 - y2) * 0.5
            'MoveToEx(.bmp.handle,x2,y4,0)
            'LineTo(.bmp.handle,x3,y4)
            .BMP.Line(x2 , y4 , x3 , y4 , pencolor)
            y4 = y2 + (y3 - y2) * 0.618
            'MoveToEx(.bmp.handle,x2,y4,0)
            'LineTo(.bmp.handle,x3,y4)
            .BMP.Line(x2 , y4 , x3 , y4 , pencolor)
            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB

    private :
    SUB drawpara(xb , yb , xc , yc , xd , yd)

        DEFSNG x2 , y2 , x3 , y3 , x4 , y4
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz2.BMP
            'MoveToEx(.bmp.handle,x3,y3,0)
            'LineTo(.bmp.handle,x3+x4-x2,y3+y4-y2)
            .BMP.Line(x3 , y3 , x3 + x4 - x2 , y3 + y4 - y2 , pencolor)
            .buffertmp.BMP = .BMP.BMP
            .paint
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawhline(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x3,y2)
            .BMP.Line(x2 , y2 , x3 , y2 , pencolor)
            .buffertmp.BMP = .BMP.BMP
            .paint
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawvline(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x2,y3)
            .BMP.Line(x2 , y2 , x2 , y3 , pencolor)
            .buffertmp.BMP = .BMP.BMP
            .paint
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawsqr(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x3,y3)
            .BMP.Line(x2 , y2 , x3 , y3 , pencolor)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            DIM x4 AS DOUBLE , y4 AS DOUBLE
            IF y3 > y2 THEN
                ang_a = ang_a * - 1
            END IF
            x4 = COS((ang_a - 90) * rad) * c + x3
            y4 = y3 - SIN((ang_a - 90) * rad) * c
            'MoveToEx(.bmp.handle,x3,y3,0)
            'LineTo(.bmp.handle,x4,y4)
            .BMP.Line(x3 , y3 , x4 , y4 , pencolor)

            ang_a = ang_a - 90
            'MoveToEx(.bmp.handle,x4,y4,0)
            .BMP.Line(x4 , y4 , COS((ang_a - 90) * rad) * c + x4 , y4 - SIN((ang_a - 90) * rad) * c , pencolor)
            x4 = COS((ang_a - 90) * rad) * c + x4
            y4 = y4 - SIN((ang_a - 90) * rad) * c
            'LineTo(.bmp.handle,x4,y4)

            ang_a = ang_a - 90
            .BMP.Line(x4 , y4 , COS((ang_a - 90) * rad) * c + x4 , y4 - SIN((ang_a - 90) * rad) * c , pencolor)
            'MoveToEx(.bmp.handle,x4,y4,0)
            'x4=cos((ang_a-90)*rad)*c+x4
            'y4=y4-sin((ang_a-90)*rad)*c
            'LineTo(.bmp.handle,x4,y4)

            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB

    private :
    SUB drawtri(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x3,y3)
            .BMP.Line(x2 , y2 , x3 , y3 , pencolor)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            DIM x4 AS DOUBLE , y4 AS DOUBLE
            IF y3 > y2 THEN
                ang_a = ang_a * - 1
            END IF
            x4 = COS((ang_a - 120) * rad) * c + x3
            y4 = y3 - SIN((ang_a - 120) * rad) * c
            'MoveToEx(.bmp.handle,x3,y3,0)
            'LineTo(.bmp.handle,x4,y4)
            .BMP.Line(x3 , y3 , x4 , y4 , pencolor)

            ang_a = ang_a - 120
            'MoveToEx(.bmp.handle,x4,y4,0)
            .BMP.Line(x4 , y4 , COS((ang_a - 120) * rad) * c + x4 , y4 - SIN((ang_a - 120) * rad) * c , pencolor)
            'x4=cos((ang_a-120)*rad)*c+x4
            'y4=y4-sin((ang_a-120)*rad)*c
            'LineTo(.bmp.handle,x4,y4)
            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB

    private :
    SUB drawcircle(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 1.57 STEP 0.001
                IF COS(angle) <> 0 AND SIN(angle <> 0) THEN
                    cs = c * COS(angle)
                    sn = c * SIN(angle)
                    .BMP.Pset(x2 + cs , y2 + sn , pencolor)
                    .BMP.Pset(x2 - cs , y2 + sn , pencolor)
                    .BMP.Pset(x2 + cs , y2 - sn , pencolor)
                    .BMP.Pset(x2 - cs , y2 - sn , pencolor)
                END IF
            NEXT angle
            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB

    private :
    SUB drawcross(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            'MoveToEx(.bmp.handle,x2,y2,0)
            'LineTo(.bmp.handle,x3,y3)
            .BMP.Line(x2 , y2 , x3 , y3 , pencolor)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            DIM x4 AS DOUBLE , y4 AS DOUBLE
            IF y3 > y2 THEN
                ang_a = ang_a * - 1
            END IF
            x4 = COS((ang_a - 90) * rad) * c * 0.5 + x3 - (x3 - x2) / 2
            y4 = y3 - (y3 - y2) / 2 - SIN((ang_a - 90) * rad) * c * 0.5
            'MoveToEx(.bmp.handle,x3-(x3-x2)/2,y3-(y3-y2)/2,0)
            'LineTo(.bmp.handle,x4,y4)
            .BMP.Line(x3 - (x3 - x2) / 2 , y3 - (y3 - y2) / 2 , x4 , y4 , pencolor)

            x4 = COS((ang_a + 90) * rad) * c * 0.5 + x3 - (x3 - x2) / 2
            y4 = y3 - (y3 - y2) / 2 - SIN((ang_a + 90) * rad) * c * 0.5
            'MoveToEx(.bmp.handle,x3-(x3-x2)/2,y3-(y3-y2)/2,0)
            'LineTo(.bmp.handle,x4,y4)
            .BMP.Line(x3 - (x3 - x2) / 2 , y3 - (y3 - y2) / 2 , x4 , y4 , pencolor)
            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB

    private :
    SUB drawinvcircle(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 1.57 STEP 0.001
                IF COS(angle) <> 0 AND SIN(angle <> 0) THEN
                    cs = c / COS(angle)
                    sn = c / SIN(angle)
                    .BMP.Pset(x2 + cs , y2 + sn , pencolor)
                    .BMP.Pset(x2 - cs , y2 + sn , pencolor)
                    .BMP.Pset(x2 + cs , y2 - sn , pencolor)
                    .BMP.Pset(x2 - cs , y2 - sn , pencolor)
                END IF
            NEXT angle
            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB

    private :
    SUB drawaiming(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x2,y3)
            .BMP.Line(x3 , 0 , x3 , canvas.Height , pencolor)
            .BMP.Line(0 , y3 , canvas.Width , y3 , pencolor)
            .buffertmp.BMP = .BMP.BMP
            .paint
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawhand(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            '.ClearBuffer
            '.restorebuffertmp
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y3)
            .BMP.Pset(x3 , y3 , pencolor)
            .BMP.Pset(x3 - 1 , y3 , pencolor)
            .BMP.Pset(x3 - 1 , y3 - 1 , pencolor)
            .BMP.Pset(x3 , y3 - 1 , pencolor)
            .BMP.Pset(x3 + 1 , y3 - 1 , pencolor)
            .BMP.Pset(x3 + 1 , y3 , pencolor)
            .BMP.Pset(x3 + 1 , y3 + 1 , pencolor)
            .BMP.Pset(x3 , y3 + 1 , pencolor)
            .BMP.Pset(x3 - 1 , y3 + 1 , pencolor)
            .buffertmp.BMP = .BMP.BMP
            .paint
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawsin(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 50.24 STEP 0.005
                IF SIN(angle <> 0) THEN
                    .BMP.Pset(x2 + angle * a , y2 + b * SIN(angle) , pencolor)
                END IF
            NEXT angle
            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB

    private :
    SUB drawlog(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM ilog AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR ilog = 1 TO 1000 STEP 0.1
                IF LOG(ilog) <> 0 THEN
                    IF reverse = 0 THEN
                        IF flip = 0 THEN
                            .BMP.Pset(x3 + ilog , y3 - LOG(ilog) * logamplitude , pencolor)
                        ELSE
                            .BMP.Pset(x3 + ilog - 1001 , y3 - LOG(1001 - ilog) * logamplitude , pencolor)
                        END IF
                    ELSE
                        IF flip = 0 THEN
                            .BMP.Pset(x3 + ilog , y3 + LOG(ilog) * logamplitude , pencolor)
                        ELSE
                            .BMP.Pset(x3 + ilog - 1001 , y3 + LOG(1001 - ilog) * logamplitude , pencolor)
                        END IF
                    END IF
                    'for ilog=0 to 21 step 0.003
                    'if exp(ilog)<>0 then
                    '.buffer.pset(x3+ilog*logamplitude,y3-exp(ilog),pencolor)
                END IF
            NEXT angle
            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB

    private :
    SUB drawexp(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM ilog AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            'for ilog=1 to 1000 step 0.1
            'if log(ilog)<>0 then
            '.buffer.pset(x3+ilog,y3-log(ilog)*logamplitude,pencolor)
            FOR ilog = 0 TO 21 STEP 0.003
                IF EXP(ilog) <> 0 THEN
                    IF reverse = 0 THEN
                        IF flip = 0 THEN
                            .BMP.Pset(x3 + ilog * logamplitude , y3 - EXP(ilog) , pencolor)
                        ELSE
                            .BMP.Pset(x3 + (ilog - 21) * logamplitude , y3 - EXP(21 - ilog) , pencolor)
                        END IF
                    ELSE
                        IF flip = 0 THEN
                            .BMP.Pset(x3 + ilog * logamplitude , y3 + EXP(ilog) , pencolor)
                        ELSE
                            .BMP.Pset(x3 + (ilog - 21) * logamplitude , y3 + EXP(21 - ilog) , pencolor)
                        END IF
                    END IF
                END IF
            NEXT angle
            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB

    private :
    SUB drawellipse(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH qchart2
            .ClearBuffer2
            .BMP.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 1.57 STEP 0.001
                IF COS(angle) <> 0 AND SIN(angle) <> 0 THEN
                    cs = a * COS(angle)
                    sn = b * SIN(angle)
                    .BMP.Pset(x3 + cs , y2 + sn , pencolor)
                    .BMP.Pset(x3 - cs , y2 + sn , pencolor)
                    .BMP.Pset(x3 + cs , y2 - sn , pencolor)
                    .BMP.Pset(x3 - cs , y2 - sn , pencolor)
                END IF
            NEXT angle
            .buffertmp.BMP = .BMP.BMP
            .paint
        END WITH

    END SUB
    
    private :
    SUB drawpitchfork(xb , yb , xc , yc , xd , yd)

        DEFSNG x2 , y2 , x3 , y3 , x4 , y4
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd

        WITH QChart2
            .ClearBuffer2
            .bmp.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x3-1,y3,0)
            'LineTo(.Buffer.handle,x3+x4-x2,y3+y4-y2)
            DIM medx AS INTEGER , medy AS INTEGER
            medx = x4 + (x3 - x4) * 0.5
            medy = y4 + (y3 - y4) * 0.5
            .BMP.Line(x2 , y2 , medx + (medx - x2) * 100 , medy + (medy - y2) * 100 , pencolor)
            .BMP.Line(x4 , y4 , x4 + (medx - x2) * 100 , y4 + (medy - y2) * 100 , pencolor)
            .BMP.Line(x3 , y3 , x3 + (medx - x2) * 100 , y3 + (medy - y2) * 100 , pencolor)
            .buffertmp.BMP = .BMP.BMP
            .Paint
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB
    
    private :
    SUB draworcycles(xb , yb , xc , yc , xd , yd)

        DEFSNG x2 , y2 , x3 , y3 , x4 , y4
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd

        WITH QChart2
            .ClearBuffer2
            .bmp.BMP = .buffertmpz2.BMP            
            
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / rqpi
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            

            DIM y5 AS DOUBLE:DIM x5 AS DOUBLE
           
            dim aa as double,bb as double,cc as double,cc2 as double,ang_aa as double
            aa = x4 - x2
            bb = y4 - y2
            cc = SQR(aa^2 + bb^2)
            cc2 = SQR((x4-x3)^2 + (y4-y3)^2)
            IF cc <> 0 THEN ang_aa = ACOS(aa / cc) * 180 / rqpi
            IF y4 > y2 THEN
                ang_aa = ang_aa * - 1
            END IF
            x5 = COS((ang_aa - 90) * rad) * cc2 + x4
            y5 = y4 - SIN((ang_aa - 90) * rad) * cc2
            dim x6 as double,y6 as double
            dim aaa as double, bbb as double,ccc as double,ang_aaa as double
            aaa = x5 - x4
            bbb = y5 - y4
            ccc = SQR(aaa^2 + bbb^2)
            IF ccc <> 0 THEN ang_aaa = ACOS(aaa / ccc) * 180 / rqpi
            IF y5 > y4 THEN
                ang_aaa = ang_aaa * - 1
            END IF
            FOR i = 1 TO 8
            x6=COS((ang_aaa - 90) * rad) * cc + (COS((ang_aa - 90) * rad) * cc2*i + x4)
            y6=(y4 - SIN((ang_aa - 90) * rad) * cc2*i) - SIN((ang_aaa - 90) * rad) * cc
            .bmp.Line((COS((ang_aa - 90) * rad) * cc2*i + x4),(y4 - SIN((ang_aa - 90) * rad) * cc2*i),x6,y6,pencolor)
            NEXT i
                                    
            .buffertmp.BMP = .bmp.BMP
            .Paint

        END WITH

    END SUB

    PUBLIC :
    SUB drawchart2
        WITH qchart2
            .drawxy2
        END WITH
    END SUB

    public :
    SUB bufcntreset
        bufcnt = 0
    END SUB

    public :
    SUB firstbufcntreset
        firstbufcnt = 0
    END SUB

    public :
    SUB savebuffertmp
        WITH qchart2
            IF firstbufcnt = 0 THEN
                .firstbuffertmpz.BMP = .BMP.BMP
                firstbufcnt ++
            END IF
            IF bufcnt = 0 THEN
                .buffertmpz.BMP = .BMP.BMP
                bufcnt ++
            END IF
            .buffertmp.BMP = .BMP.BMP
        END WITH
    END SUB

    public :
    SUB savebuffertmpsimple
        WITH qchart2
            .buffertmp.BMP = .BMP.BMP
        END WITH
    END SUB

    public :
    SUB savebuffertmpsimplez
        WITH qchart2
            .buffertmpz2.BMP = .BMP.BMP
        END WITH
    END SUB

    PUBLIC :
    SUB drawp(TYPE , xb , yb , xc , yc , xd , yd)
        DEFINT x2 , y2 , x3 , y3 , x4 , y4
        DEFINT type2
        type2 = TYPE
        'print type2

        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd
        WITH qchart2
            SELECT CASE type2
                CASE 0 :
                    .drawtrendline(x2 , y2 , x3 , y3)
                CASE 1 :
                    .drawfibofan(x2 , y2 , x3 , y3)
                CASE 2 :
                    .drawfiboret(x2 , y2 , x3 , y3)
                CASE 3 :
                    .drawpara(x2 , y2 , x3 , y3 , x4 , y4)
                CASE 4 :
                    .drawhline(x2 , y2 , x3 , y3)
                CASE 5 :
                    .drawvline(x2 , y2 , x3 , y3)
                CASE 6 :
                    .drawsqr(x2 , y2 , x3 , y3)
                CASE 7 :
                    .drawtri(x2 , y2 , x3 , y3)
                CASE 8 :
                    .drawcircle(x2 , y2 , x3 , y3)
                CASE 9 :
                    .drawcross(x2 , y2 , x3 , y3)
                CASE 10 :
                    .drawinvcircle(x2 , y2 , x3 , y3)
                CASE 11 :
                    .drawaiming(x2 , y2 , x3 , y3)
                CASE 12 :
                    .drawhand(x2 , y2 , x3 , y3)
                CASE 13 :
                    .drawsin(x2 , y2 , x3 , y3)
                CASE 14 :
                    .drawlog(x2 , y2 , x3 , y3)
                CASE 15 :
                    .drawexp(x2 , y2 , x3 , y3)
                CASE 16 :
                    .drawellipse(x2 , y2 , x3 , y3)
                CASE 17 :
                    .drawpitchfork(x2 , y2 , x3 , y3 , x4 , y4)
                CASE 18 :
                    .draworcycles(x2 , y2 , x3 , y3 , x4 , y4)
            END SELECT
        END WITH
    END SUB

    PUBLIC :
    SUB RedrawChart2  '<--- Call this SUB from your FORM.OnResize EVENT SUB
        WITH qchart2
            .BMP.Width = .Width  'recalc dimensions
            .BMP.Height = .Height
            .drawchart2
        END WITH
    END SUB    

END TYPE

'CREATE hotkeysfrm AS QFORM
'Center
'Caption = "Global hotkeys"
'WndProc = FormWndProc
'END CREATE

CREATE signalsndform AS QFORM
    CREATE signallabel AS QLABEL
        Caption = "New signal detected!"
    END CREATE
    OnClose = signalsndfrmclose
    Visible = 0
    Height = 50
    Width = 150
    Caption = "Signal"
    BorderStyle = 3
    Center
END CREATE

DIM aboutform AS QFORM
aboutform.Caption = "About"
aboutform.Width = 600
aboutform.Height = 300
DIM aboutcanvas AS QCANVAS
CREATE bgaboutfrm AS QIMAGE
    Width = aboutform.Width - 20
    Height = aboutform.Height - 20
    Stretch = 1
    AutoSize = 0
    Parent = aboutform
    BMP = homepath + "\images\space.bmp"
END CREATE
CREATE planetredbg AS QIMAGE
    Width = 72
    Height = 65
    Top = 150
    Left = 180
    Stretch = 0
    AutoSize = 0
    Parent = aboutform
    BMP = homepath + "\images\planetred.bmp"
END CREATE
CREATE planetwhitebg AS QIMAGE
    Width = 51
    Height = 49
    Top = 200
    Left = 380
    Stretch = 0
    AutoSize = 0
    Parent = aboutform
    BMP = homepath + "\images\planetwhite.bmp"
END CREATE
CREATE planetgreenbg AS QIMAGE
    Width = 69
    Height = 65
    Top = 180
    Left = 80
    Stretch = 0
    AutoSize = 0
    Parent = aboutform
    BMP = homepath + "\images\planetgreen.bmp"
END CREATE

DIM aboutimg AS QIMAGE
DIM aboutTimer AS QTIMER
aboutTimer.Enabled = FALSE
DIM aboutFont AS QFONT
DIM abouty AS INTEGER
abouty = - 20
aboutform.BorderStyle = 3

aboutform.Center
aboutform.Color = 0
aboutFont.Name = "Courier"
aboutFont.Size = 11
aboutFont.Color = &H00FF00


aboutimg.Parent = aboutform
aboutimg.Top = 0
aboutimg.Left = 0
aboutimg.Height = 200
aboutimg.Width = aboutform.Width
aboutimg.BMP = homepath + "\images\QTGenbg.bmp"
aboutcanvas.Parent = aboutform
aboutcanvas.Top = 150
aboutcanvas.Height = 100
aboutcanvas.Font = aboutFont
aboutcanvas.Color = 0
aboutcanvas.OnPaint = paintabout
DECLARE SUB timerover
DECLARE SUB resize
DECLARE SUB abfrmclose

aboutform.OnClose = abfrmclose

aboutTimer.Interval = 35
aboutTimer.OnTimer = timerover

aboutform.OnResize = resize


'Define the main form
CREATE frmMain AS QFORMEX
    'Center
    Top = 0
    Left = 0
    Width = screen.width
    Height = 0.95*screen.height
    Caption = "QChartist"+" build "+QC_build
    IcoHandle = QChartistico
    OnClose = frmMainClose
    onmousewheel = frmmainonmw
    AutoScroll = 0
    onkeydown=hotkeysub
    'WndProc = FormWndProc ' Used for global hotkeys

    'create bgimg as qimage
    'width=frmmain.width
    'height=frmmain.height
    'Autosize = 0
    'Stretch=0
    'parent=frmmain
    'BMPHandle=bgimage
    'center=1
    'end create


    CREATE toolsPanel AS QDOCKFORM
        'parent=frmmain
        'UndockedForm.Parent = frmmain
        'AltAlign = 0
        'Caption = "Tools"
        'Align = 0
        'DockStyle = 1
        'UnDockStyle = 1
        'style = 0
        'Client.BevelOuter = 0
        'Canvas.Font.Name = "Arial"
        'width=85
        'UndockedWidth = toolsPanel.Width
        'height=650
        'UndockedHeight = toolsPanel.Height
        'CanClose = 1
        'OnClose = FormClosed

        AltPanel.Parent = frmMain
        'AltAlign = 4
        UndockedForm.Parent = frmMain
        Caption = "Tools"
        Align = 3
        DockStyle = 1
        UnDockStyle = 1
        Style = 1
        Client.BevelOuter = 0
        Canvas.Font.Name = "Tahoma"
        UndockedWidth = toolsPanel.Width
        CanClose = 1
        'OnClose = FormClosed
        Width = 85
        Height = 650
        UndockedWidth = toolsPanel.Width
        UndockedHeight = toolsPanel.Height

        'create toolsgroupbox as qgroupbox
        'Parent = toolsPanel.Client
        'height=620
        'width=70
        'onclick=movetoolsgroupbox
        'onmousemove=groupboxonmousemove

        CREATE ToolsPanel2 AS QPANEL
            Parent = toolsPanel.Client
            Align = 5

            CREATE trendlinebtn AS QOVALBTN
                Top = 10
                Left = 5
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw trendline"
                ShowHint = 1
                OnClick = trendlinebtnclick
                BMPHandle = icontrendline
                Cursor = 2
            END CREATE

            CREATE timeextbtn AS QOVALBTN
                Top = 10
                Left = 5
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw time extensions"
                ShowHint = 1
                OnClick = timeextbtnclick
                BMPHandle = icontimeext
                Cursor = 2
                Visible = 0
            END CREATE

            CREATE fibofanbtn AS QOVALBTN
                Top = 10
                Width = 30
                Height = 30
                Left = 35
                Color = &Hcccccc
                Hint = "Draw Fibonacci fan"
                ShowHint = 1
                OnClick = fibofanbtnclick
                BMPHandle = iconfibofan
                Cursor = 2
            END CREATE

            CREATE pricecyclesbtn AS QOVALBTN
                Top = 10
                Width = 30
                Height = 30
                Left = 35
                Color = &Hcccccc
                Hint = "Draw price cycles"
                ShowHint = 1
                OnClick = pricecyclesbtnclick
                BMPHandle = iconpricecycles
                Cursor = 2
                Visible = 0
            END CREATE

            CREATE fiboretbtn AS QOVALBTN
                Left = 5
                Top = 40
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw Fibonacci retracements"
                ShowHint = 1
                OnClick = fiboretbtnclick
                BMPHandle = iconfiboret
                Cursor = 2
            END CREATE

            CREATE timecyclesbtn AS QOVALBTN
                Left = 5
                Top = 40
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw time cycles"
                ShowHint = 1
                OnClick = timecyclesbtnclick
                BMPHandle = icontimecycles
                Cursor = 2
                Visible = 0
            END CREATE


            CREATE parabtn AS QOVALBTN
                Top = 40
                Left = 35
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw parallel lines"
                ShowHint = 1
                OnClick = parabtnclick
                BMPHandle = iconpara
                Cursor = 2
            END CREATE

            CREATE logspiralbtn AS QOVALBTN
                Visible = 0
                Top = 40
                Left = 35
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw logarithmic spiral"
                ShowHint = 1
                OnClick = logspiralbtnclick
                BMPHandle = iconlogspiral
                Cursor = 2
            END CREATE

            CREATE hlinebtn AS QOVALBTN
                Left = 5
                Top = 70
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw horizontal line"
                ShowHint = 1
                OnClick = hlinebtnclick
                BMPHandle = iconhline
                Cursor = 2
            END CREATE

            CREATE polybtn AS QOVALBTN
                Visible = 0
                Left = 5
                Top = 70
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Edit chart"
                ShowHint = 1
                OnClick = polybtnclick
                BMPHandle = iconpoly
                Cursor = 2
            END CREATE
            
            CREATE pentagbtn AS QOVALBTN
                Visible = 0
                Left = 35
                Top = 70
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw pentagram"
                ShowHint = 1
                OnClick = pentagbtnclick
                BMPHandle = iconpentag
                Cursor = 2
            END CREATE
            
            CREATE orcyclesbtn AS QOVALBTN
                Visible = 0
                Left =  5
                Top = 100
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw oriented cycles"
                ShowHint = 1
                OnClick = orcyclesbtnclick
                BMPHandle = iconorcycles
                Cursor = 2
            END CREATE
            
            CREATE polygbtn AS QOVALBTN
                Visible = 0
                Left = 35
                Top = 100
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw polygone"
                ShowHint = 1
                OnClick = polygbtnclick
                BMPHandle = iconpolyg
                Cursor = 2
            END CREATE
            
            CREATE sqr2btn AS QOVALBTN
                Left = 5
                Top = 130
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw square from center"
                ShowHint = 1
                OnClick = sqr2btnclick
                BMPHandle = iconsqr
                Cursor = 2
            END CREATE

            CREATE tri2btn AS QOVALBTN
                Top = 130
                Left = 35
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw triangle from center"
                ShowHint = 1
                OnClick = tri2btnclick
                BMPHandle = icontri
                Cursor = 2
            END CREATE

            CREATE vlinebtn AS QOVALBTN
                Top = 70
                Left = 35
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw vertical line"
                ShowHint = 1
                OnClick = vlinebtnclick
                BMPHandle = iconvline
                Cursor = 2
            END CREATE

            CREATE sqrbtn AS QOVALBTN
                Left = 5
                Top = 100
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw square"
                ShowHint = 1
                OnClick = sqrbtnclick
                BMPHandle = iconsqr
                Cursor = 2
            END CREATE

            CREATE tribtn AS QOVALBTN
                Top = 100
                Left = 35
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw triangle"
                ShowHint = 1
                OnClick = tribtnclick
                BMPHandle = icontri
                Cursor = 2
            END CREATE

            CREATE circlebtn AS QOVALBTN
                Left = 5
                Top = 130
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw circle"
                ShowHint = 1
                OnClick = circlebtnclick
                BMPHandle = iconcircle
                Cursor = 2
            END CREATE

            CREATE crossbtn AS QOVALBTN
                Top = 130
                Left = 35
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw cross"
                ShowHint = 1
                OnClick = crossbtnclick
                BMPHandle = iconcross
                Cursor = 2
            END CREATE

            CREATE invcirclebtn AS QOVALBTN
                Left = 5
                Top = 160
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw inverse circle"
                ShowHint = 1
                OnClick = invcirclebtnclick
                BMPHandle = iconinvcircle
                Cursor = 2
            END CREATE

            CREATE textbtn AS QOVALBTN
                Top = 160
                Left = 35
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Write text"
                ShowHint = 1
                OnClick = textbtnclick
                Caption = "T"
                Cursor = 2
            END CREATE

            CREATE cursorbtn AS QOVALBTN
                Left = 5
                Top = 190
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Selection"
                ShowHint = 1
                OnClick = cursorbtnclick
                BMPHandle = iconcursor
                Cursor = 2
            END CREATE

            CREATE pencolorbtn AS QOVALBTN
                Left = 35
                Top = 190
                Width = 30
                Height = 30
                Color = pencolor
                Hint = "Pen color"
                ShowHint = 1
                OnClick = choosepencolor
                Cursor = 2
            END CREATE

            CREATE textfontbtn AS QOVALBTN
                Left = 5
                Top = 220
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Text font"
                ShowHint = 1
                OnClick = choosetextfont
                Caption = "F"
                Cursor = 2
            END CREATE

            CREATE aimingbtn AS QOVALBTN
                Left = 35
                Top = 220
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Aiming"
                ShowHint = 1
                OnClick = aimingbtnclick
                BMPHandle = iconaiming
                Cursor = 2
            END CREATE

            CREATE clearbtn AS QOVALBTN
                Left = 5
                Top = 250
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Clear graph"
                ShowHint = 1
                OnClick = clearbtnclick
                Caption = "Clr"
                Cursor = 2
            END CREATE

            CREATE handdbtn AS QOVALBTN
                Left = 35
                Top = 250
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Hand draw"
                ShowHint = 1
                OnClick = handdbtnclick
                BMPHandle = iconhandd
                Cursor = 2
            END CREATE

            CREATE sinbtn AS QOVALBTN
                Left = 5
                Top = 280
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw sinusoïd"
                ShowHint = 1
                OnClick = sinbtnclick
                BMPHandle = iconsin
                Cursor = 2
            END CREATE

            CREATE logbtn AS QOVALBTN
                Left = 35
                Top = 280
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw logarithmic curve"
                ShowHint = 1
                OnClick = logbtnclick
                BMPHandle = iconlog
                Cursor = 2
            END CREATE

            CREATE expbtn AS QOVALBTN
                Left = 5
                Top = 310
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw exponential curve"
                ShowHint = 1
                OnClick = expbtnclick
                BMPHandle = iconexp
                Cursor = 2
            END CREATE

            CREATE priceextbtn AS QOVALBTN
                Left = 35
                Top = 310
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw price extensions"
                ShowHint = 1
                OnClick = priceextbtnclick
                BMPHandle = iconpriceext
                Cursor = 2
            END CREATE


            CREATE reversebtn AS QOVALBTN
                Left = 5
                Top = 400
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Reverse Log/Exp curve"
                ShowHint = 1
                OnClick = reversebtnclick
                BMPHandle = iconreverse
                Cursor = 2
            END CREATE

            CREATE flipbtn AS QOVALBTN
                Left = 35
                Top = 400
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Flip Log/Exp curve"
                ShowHint = 1
                OnClick = flipbtnclick
                BMPHandle = iconflip
                Cursor = 2
            END CREATE

            CREATE ellipsebtn AS QOVALBTN
                Left = 5
                Top = 430
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw ellipse"
                ShowHint = 1
                OnClick = ellipsebtnclick
                BMPHandle = iconellipse
                Cursor = 2
            END CREATE

            CREATE pitchforkbtn AS QOVALBTN
                Left = 35
                Top = 430
                Width = 30
                Height = 30
                Color = &Hcccccc
                Hint = "Draw pitchfork"
                ShowHint = 1
                OnClick = pitchforkbtnclick
                BMPHandle = iconpitchfork
                Cursor = 2
            END CREATE

            CREATE sq9fbtn AS QOVALBTN
                Left = 5
                Top = 460
                Width = 60
                Height = 30
                Color = &Hcccccc
                Hint = "Draw Gann Square of 9 Floating"
                ShowHint = 1
                OnClick = sq9fbtnclick
                'bmphandle=iconpitchfork
                Caption = "SQ9F"
                Cursor = 2
            END CREATE

            CREATE tsq9fbtn AS QOVALBTN
                Left = 5
                Top = 460
                Width = 60
                Height = 30
                Color = &Hcccccc
                Hint = "Draw Time Gann Square of 9 Floating"
                ShowHint = 1
                OnClick = timesq9fbtnclick
                'bmphandle=iconpitchfork
                Caption = "TSQ9F"
                Cursor = 2
                Visible = 0
            END CREATE

            CREATE sq144btn AS QOVALBTN
                Left = 5
                Top = 490
                Width = 60
                Height = 30
                Color = &Hcccccc
                Hint = "Draw Gann Square of 144"
                ShowHint = 1
                OnClick = sq144btnclick
                'bmphandle=iconpitchfork
                Caption = "SQ144"
                Cursor = 2
            END CREATE

            CREATE tsq144btn AS QOVALBTN
                Left = 5
                Top = 490
                Width = 60
                Height = 30
                Color = &Hcccccc
                Hint = "Draw Time Gann Square of 144"
                ShowHint = 1
                OnClick = timesq144btnclick
                'bmphandle=iconpitchfork
                Caption = "TSQ144"
                Cursor = 2
                Visible = 0
            END CREATE

            CREATE tarrowleft AS QOVALBTN
                Left = 5 + 7
                Top = 520
                Width = 20
                Height = 20
                BMPHandle = leftarrow
                Hint = "Previous tools"
                ShowHint = 1
                Cursor = 2
                Color = &Hcccccc
                OnClick = previoustoolsclick
            END CREATE

            CREATE tarrowright AS QOVALBTN
                Left = 35 + 7
                Top = 520
                Width = 20
                Height = 20
                BMPHandle = rightarrow
                Hint = "Next tools"
                ShowHint = 1
                Cursor = 2
                Color = &Hcccccc
                OnClick = nexttoolsclick
            END CREATE

            CREATE settingsbtn AS QBUTTON
                Left = 5
                Top = 520 + 20
                Width = 60
                Height = 20
                Color = &Hcccccc
                Hint = "Settings"
                ShowHint = 1
                OnClick = settingsbtnclick
                'bmphandle=iconsettings
                Caption = "Settings"
                Cursor = 2
            END CREATE

            CREATE Indicatorsbtn AS QBUTTON
                Left = 5
                Top = 520 + 50
                Width = 60
                Height = 20
                Hint = "Indicators"
                ShowHint = 1
                Caption = "Indicators"
                OnClick = indiform
                Cursor = 2
            END CREATE

            CREATE Mixerbtn AS QBUTTON
                Left = 5
                Top = 520 + 80
                Width = 60
                Height = 20
                Hint = "Mixer"
                ShowHint = 1
                Caption = "Mixer"
                OnClick = mixerform
                Cursor = 2
            END CREATE

            CREATE trackb AS QTRACKBAR
                Left = 5
                Top = 340
                Width = 60
                Height = 30
                OnChange = trackbchange
                Min = 10
                Max = 100
                Cursor = 2
                Hint = "Log/Exp curve adjustment"
                ShowHint = 1
            END CREATE

            CREATE trackb2 AS QTRACKBAR
                Left = 5
                Top = 370
                Width = 60
                Height = 30
                OnChange = trackbchange
                Min = 10
                Max = 100
                Cursor = 2
                Hint = "Log/Exp curve adjustment"
                ShowHint = 1
                
            END CREATE                        


        END CREATE

    END CREATE

    CREATE ToolbarBox AS QDOCKFORM
        'visible=0 ' not properly implemented yet
        UndockedForm.Parent = frmMain
        'Align = 0
        ''Client.BevelOuter = 0
        'Height = 31
        'width=100
        'DockStyle = 6
        'UnDockStyle = 6
        'UndockedWidth = 600
        'UndockedHeight = 55
        'AltPanel.Parent = frmmain
        'Style = 1
        'Caption = "Toolbar"
        'CanClose = 1
        'Sizeable=1
        Align = 1

        Height = 55
        'width=100
        DockStyle = 6
        UnDockStyle = 6
        UndockedWidth = 1024
        UndockedHeight = 80
        AltPanel.Parent = frmMain
        Style = 1
        Caption = "Toolbar"
        canclose = 1


        CREATE ComponentsPanel AS QPANEL
            Parent = ToolbarBox.Client
            Align = 5
            CREATE openbtn AS QCOOLBTN
                Height = 25
                Width = 25
                Left = 25 * 0
                Top = 0
                BMP = homepath + "\images\open.bmp"
                Hint = "Import CSV"
                ShowHint = 1
                OnClick = importcsv
            END CREATE
            CREATE hotkeyedit AS qedit
                Height = 25
                Width = 50
                Left = 25 * 0
                Top = 25                
                text="Snif key"
                onchange = hotkeysub
            END CREATE
            CREATE savebtn AS QCOOLBTN
                Height = 25
                Width = 25
                Left = 25 * 1
                Top = 0
                BMP = homepath + "\images\save.bmp"
                Hint = "Export CSV"
                ShowHint = 1
                OnClick = exportfile
            END CREATE

            CREATE collbtn AS QCOOLBTN
                Height = 25
                Width = 25
                Left = 25 * 2
                Top = 0
                BMP = homepath + "\images\collection.bmp"
                Hint = "Export collection"
                ShowHint = 1
                OnClick = exportcollection
            END CREATE

            CREATE barsdisplayedlab1 AS QLABEL
                'Parent=frmMain
                Left = 80 + 30
                Caption = "Display"
            END CREATE

            CREATE barsdisplayed AS QEDIT
                'Parent=frmMain
                Left = 120 + 30
                Width = 40
                Text = "300"
                OnChange = barsdisplayedchange
            END CREATE

            CREATE dispbarsp AS QBUTTON
                'Parent=frmMain
                Left = 160 + 30
                Top = 2
                Height = 10
                Width = 15
                Caption = "+"
                OnMouseDown = dispbarspd
                OnMouseUp = dispbarspu
            END CREATE

            CREATE dispbarsm AS QBUTTON
                'Parent=frmMain
                Left = 160 + 30
                Top = 12
                Height = 10
                Width = 15
                Caption = "-"
                OnMouseDown = dispbarsmd
                OnMouseUp = dispbarsmu
            END CREATE

            CREATE barsdisplayedlab2 AS QLABEL
                'Parent=frmMain
                Left = 185 + 30
                Caption = "bars"
            END CREATE

            CREATE dispbarsok AS QBUTTON
                'Parent=frmMain
                Left = 210 + 30
                Height = 20
                Width = 30
                Caption = "OK"
                OnClick = dispbarsok_click
            END CREATE

            CREATE dispbarsswitch AS QCOOLBTN
                'Parent=frmMain
                Left = dispbarsok.Left + dispbarsok.Width + 5
                Height = 20
                Width = 53
                Caption = "10<->100"
                OnClick = dispbarsswitchsub
            END CREATE

            CREATE dispchartnblab1 AS QLABEL
                'Parent=frmMain
                Left = 300 + 30
                Caption = "Display chart:"
            END CREATE

            CREATE dispchartnb AS QCOMBOBOX
                'Parent=frmMain
                Left = 370 + 30
                Height = 20
                Width = 50
                OnChange = dispchartnbchanged
            END CREATE

            CREATE tfmultlab AS QLABEL
                'Parent=frmMain
                Left = 450 + 30
                Caption = "Timeframe multiplier:"
            END CREATE

            CREATE tfmult AS QEDIT
                'Parent=frmMain
                Left = 550 + 30
                Width = 30
                Text = "1"
                OnChange = tfmultchange
            END CREATE

            CREATE tfmultp AS QBUTTON
                'Parent=frmMain
                Left = 580 + 30
                Top = 2
                Height = 10
                Width = 15
                Caption = "+"
                OnClick = tfmultp_click
            END CREATE

            CREATE tfmultm AS QBUTTON
                'Parent=frmMain
                Left = 580 + 30
                Top = 12
                Height = 10
                Width = 15
                Caption = "-"
                OnClick = tfmultm_click
            END CREATE

            CREATE tfmultcombo AS QCOMBOBOX
                'Parent=frmMain
                Left = 600 + 30
                Width = 40
                AddItems "1"
                AddItems "6"
                AddItems "24"
                AddItems "42"
                AddItems "48"
                AddItems "168"
                AddItems "336"
                ItemIndex = 0
                OnChange = tfmultcombosub
            END CREATE

            CREATE tfmultok AS QBUTTON
                'Parent=frmMain
                Left = 650 + 30
                Height = 20
                Width = 30
                Caption = "OK"
                OnClick = tfmultok_click
            END CREATE

            CREATE charttypelab AS QLABEL
                'Parent=frmMain
                Left = 700 + 30
                Caption = "Chart type:"
            END CREATE

            CREATE charttypecombo AS QCOMBOBOX
                'Parent=frmMain
                Left = 750 + 30
                AddItems "Candlesticks"
                AddItems "Line"
                AddItems "Point"
                AddItems "Bar"
                AddItems "Ribbon"
                AddItems "Pretzel"
                AddItems "Stepped"
                AddItems "Polar"
                Additems "Astro wheel"
                ItemIndex = 0
                OnChange = charttypecombochange
            END CREATE

            CREATE stopbtn AS QBUTTON
                Left = 780 + 30 + 30 + 30 + 30 + 30 + 20
                Caption = "Stop"
                Height = 20
                Width = 40
                OnClick = stopclicked
            END CREATE

            CREATE cntbarslab AS QLABEL
                'Parent=frmMain
                Left = 80 + 30
                Top = 30 - 3
                Caption = "Counted bars:"
            END CREATE

            CREATE cntbarsedit AS QEDIT
                'Parent=frmMain
                Left = cntbarslab.Left + cntbarslab.Width + 10
                Top = 30 - 3
                Width = 50
                Text = "300"
                OnChange = cntbarseditchange
            END CREATE

            CREATE spaceforwardslab AS QLABEL
                'parent=frmmain
                Left = cntbarsedit.Left + cntbarsedit.Width + 10
                Top = 30 - 3
                Caption = "Space forwards:"
            END CREATE

            CREATE spaceforwardsedit AS QEDIT
                'Parent=frmMain
                Left = spaceforwardslab.Left + spaceforwardslab.Width + 10
                Top = 30 - 3
                Width = 50
                Text = "0"
            END CREATE

            CREATE spaceforwardsbtn AS QBUTTON
                'Parent=frmMain
                Left = spaceforwardsedit.Left + spaceforwardsedit.Width + 10
                Top = 25 - 3
                Width = 30
                Caption = "OK"
                OnClick = setspaceforwards
            END CREATE

            CREATE scrollmodebtn AS QOVALBTN
                'Parent=frmMain
                Left = spaceforwardsbtn.Left + spaceforwardsbtn.Width + 10
                Top = 20
                Width = 70
                Height = 30
                Color = &Hcccccc
                OnClick = scrollmodebtnclick
                Caption = "Scroll mode"
            END CREATE

            CREATE useindischeckbox AS QCHECKBOX
                'Parent=frmMain
                Left = scrollmodebtn.Left + scrollmodebtn.Width + 10
                Top = 30 - 3
                'width=50
                'height=50
                'color=&Hcccccc
                Checked = 0
                OnClick = useindischeckboxsub
                Caption = "Use indicators"
            END CREATE

            CREATE axistypelab AS QLABEL
                'Parent=frmMain
                Left = useindischeckbox.Left + useindischeckbox.Width + 10
                Top = 30 - 3
                'width=50
                'height=50
                'color=&Hcccccc
                Caption = "Axis type:"
            END CREATE

            CREATE axistypecombo AS QCOMBOBOX
                'Parent=frmMain
                Left = axistypelab.Left + axistypelab.Width + 10
                Top = 30 - 3
                'width=50
                'height=50
                'color=&Hcccccc
                AddItems "Normal"
                AddItems "Logarithmic"
                ItemIndex = 0
                OnChange = axistypecombosub
            END CREATE

            CREATE priceratiolab2 AS QLABEL
                Top = 30 - 3
                Left = axistypecombo.Left + axistypecombo.Width + 10
                Caption = "Price ratio:"
            END CREATE

            CREATE priceratioedit2 AS QEDIT
                Top = 30 - 3
                Left = priceratiolab2.Left + priceratiolab2.Width + 10
                Width = 35
                Text = "1"
            END CREATE

            CREATE priceratiobutton2 AS QBUTTON
                Top = 30 - 6
                Left = priceratioedit2.Left + priceratioedit2.Width + 10
                Width = 35
                Caption = "OK"
                OnClick = changepriceratiosub2
            END CREATE

        END CREATE
    END CREATE

    CREATE drwBox AS QBUTTON
        Caption = "Candlesticks"
        Top = 325
        OnClick = btnOnClick
        Visible = 0
    END CREATE

    CREATE Graph AS QChart  'Create a copy of the new object
        Visible = 0
        Align = 6  'alRight
        Width = frmMain.ClientWidth - leftwidth - 25
        Left = leftwidth + 16
        Height = frmMain.ClientHeight - 180 + leftwidth - 10
        Top = 50
        OnPaint = Graph.paintchart  'This line REQUIRED to process Repaints
        OnClick = graphclicked
        OnMouseDown = graphmousedown
        OnMouseMove = graphcursorpos
    END CREATE


    CREATE canvas AS qchart2
        Visible = 0
        Align = 6
        Width = frmMain.ClientWidth - leftwidth - 144 - spaceforwards
        Height = 180
        Top = Graph.Top + Graph.Height
        Left = leftwidth + 97 - 4
        OnPaint = canvas.paint
        OnClick = sepindiclicked
        OnMouseDown = sepindimousedown
        OnMouseMove = sepindicursorpos
    END CREATE

    'create sepindizoommore as qbutton
    'visible=0
    'align=6
    'Top =graph.top+graph.height+15+10
    'Left=leftwidth+97+canvas.width+15
    'width=25
    'bmpHandle = zoommore
    'onclick=sepindizoommoreclick
    'end create

    'create sepindizoomless as qbutton
    'visible=0
    'align=6
    'Top =graph.top+graph.height+65+10
    'Left=leftwidth+97+canvas.width+15
    'width=25
    'bmpHandle = zoomless
    'onclick=sepindizoomlessclick
    'end create

    'create sepindiheightlab as qlabel
    'visible=0
    'align=6
    'Top =graph.top+graph.height+20+10
    'Left=leftwidth+97+canvas.width+45
    'width=100
    'caption="Canvas height"
    'end create

    'create sepindiheight as qedit
    'visible=0
    'align=6
    'Top =graph.top+graph.height+40+10
    'Left=leftwidth+97+canvas.width+45
    'width=50
    'text="180"
    'end create

    'create sepindiheightok as qbutton
    'visible=0
    'align=6
    'Top =graph.top+graph.height+40+10
    'Left=leftwidth+97+canvas.width+95
    'width=25
    'caption="OK"
    'onclick=showcanvasclick
    'end create

    CREATE sepindivalminlab AS QLABEL
        Visible = 0
        Align = 6
        Top = Graph.Top + Graph.Height + 65 + 10
        Left = leftwidth + 10
        Caption = "Min value"
    END CREATE

    CREATE sepindivalminedit AS QEDIT
        Visible = 0
        Align = 6
        Top = Graph.Top + Graph.Height + 65 + 20 + 10
        Left = leftwidth + 10
        Width = 50
        Text = "0"
    END CREATE

    CREATE sepindivalmaxlab AS QLABEL
        Visible = 0
        Align = 6
        Top = Graph.Top + Graph.Height + 65 - 50 + 10
        Left = leftwidth + 10
        Caption = "Max value"
    END CREATE

    CREATE sepindivalmaxedit AS QEDIT
        Visible = 0
        Align = 6
        Top = Graph.Top + Graph.Height + 65 - 50 + 20 + 10
        Left = leftwidth + 10
        Width = 50
        Text = "0"
    END CREATE

    CREATE sepindivalok AS QBUTTON
        Visible = 0
        Align = 6
        Top = Graph.Top + Graph.Height + 65 - 50 + 20 + 25 + 10
        Left = leftwidth + 10 + 55
        Width = 25
        OnClick = dispbarsok_click
        Caption = "OK"
    END CREATE


    CREATE Scrollchart AS QSCROLLBAR
        'enabled=false
        Visible = 0
        Parent = frmMain
        Align = 6
        Left = Graph.Left
        Top = Graph.Height + 70 - 20
        Width = Graph.Width
        LargeChange = 20
        Height = 20
        Min = 0 :  Max = 255
        ShowHint = 0
        OnChange = Scrolling
    END CREATE

    CREATE split AS QPANEL
        Color = gray
        Left = Graph.Left
        Top = Graph.Height + 70
        Width = Graph.Width
        Height = 2
        Cursor = 4
        Hint = "Resize canvas"
        ShowHint = 1
        OnMouseDown = resizesplitmd
        OnMouseUp = resizesplitmu
        Visible = 0
    END CREATE

    CREATE splith AS QPANEL
        Color = gray
        Left = Graph.Left
        Top = Graph.Top
        Width = 2
        Height = Graph.Height
        Cursor = 5
        Hint = "Resize canvas"
        ShowHint = 1
        OnMouseDown = resizesplithmd
        OnMouseUp = resizesplithmu
        Visible = 0
    END CREATE


    CREATE closedispchart AS QBUTTON
        Visible = 0
        Parent = frmMain
        Align = 6
        Top = Graph.Top + 2
        Left = Graph.Width + 98 + leftwidth - 100
        Height = 16
        Width = 16
        Hint = "Close chart"
        ShowHint = 1
        OnClick = closedispchart_click
        BMPHandle = iconclose
        Cursor = 2
    END CREATE

    CREATE closedispcanvas AS QBUTTON
        Visible = 0
        Parent = frmMain
        Align = 6
        Top = canvas.Top
        Left = canvas.Width + 181 - 4 + leftwidth - 100
        Height = 16
        Width = 16
        Hint = "Close canvas"
        ShowHint = 1
        OnClick = closedispcanvas_click
        BMPHandle = iconclose
        Cursor = 2
    END CREATE
    
    CREATE pricescaleplusbtn AS qbutton
                visible=0
                Top = 10
                Left = Graph.Left - 30
                Top = Graph.Top + 15
                Height = 20
                width=20
                Hint = "Expand price scale"
                ShowHint = 1
                OnClick = pricescaleplusbtnclick
                BMPHandle = pricescaleplus
                Cursor = 2
    END CREATE
    
   CREATE pricescaleminusbtn AS qbutton
                visible=0
                Top = 10
                Left = Graph.Left - 30
                Top = Graph.Top + 15 + 20
                Height = 20
                width=20
                Hint = "Compress price scale"
                ShowHint = 1
                OnClick = pricescaleminusbtnclick
                BMPHandle = pricescaleminus
                Cursor = 2
    END CREATE
    
    CREATE addbarsbtn AS qbutton
                visible=0
                Left = Graph.Left - 30
                Top = Graph.Top + 15 + 20 + 20
                Height = 20
                width=20
                Hint = "Add bars"
                ShowHint = 1
                OnClick = addbars
                BMPHandle = iconaddbars
                Cursor = 2
    END CREATE


    CREATE MainMenu AS QMAINMENU

        CREATE FileMenu AS QMENUITEM
            Caption = "&File"
            CREATE settingsmenu AS QMENUITEM
                Caption = "&Settings..."
                OnClick = filesettings
            END CREATE
        END CREATE

        CREATE EditMenu AS QMENUITEM
            Caption = "&Edit"
        END CREATE

        CREATE WindowsMenu AS QMENUITEM
            Caption = "&Windows"
        END CREATE

        CREATE ToolsMenu AS QMENUITEM
            Caption = "&Tools"
            CREATE automenu AS QMENUITEM
                Caption = "&Automation"
                CREATE autosubmenu AS QMENUITEM
                    Caption = "Follow mode"
                    OnClick = followmode
                END CREATE
            END CREATE
            CREATE tsettingsmenu AS QMENUITEM
                Caption = "&Settings..."
                OnClick = toolssettings
            END CREATE
        END CREATE

        CREATE AboutMenu AS QMENUITEM
            Caption = "&?"
        END CREATE

    END CREATE


    OnResize = setup

END CREATE  'frmMain

'IF RegisterHotKey(frmmain.Handle, 0, , 32) = 0 THEN
'   ShowMessage("Sorry, hot key SPACEBAR already taken!")
'END IF

SUB dispbarsswitchsub
    IF dispbarsswitch.Flat = 0 THEN
        dispbarsswitch.Flat = 1
        barsdisplayed.Text = "10"
        numbars = VAL(barsdisplayed.Text)
        chartstart = Scrollchart.Position - numbars
        justrefreshchart
        say "Displayed bars set to: "+barsdisplayed.Text
        EXIT SUB
    END IF
    IF dispbarsswitch.Flat = 1 THEN
        dispbarsswitch.Flat = 0
        barsdisplayed.Text = "100"
        numbars = VAL(barsdisplayed.Text)
        chartstart = Scrollchart.Position - numbars
        justrefreshchart
        say "Displayed bars set to: "+barsdisplayed.Text
        EXIT SUB
    END IF
END SUB

SUB tfmultcombosub
    SELECT CASE tfmultcombo.ItemIndex
        CASE 0 :
            tfmult.Text = "1"
        CASE 1 :
            tfmult.Text = "6"
        CASE 2 :
            tfmult.Text = "24"
        CASE 3 :
            tfmult.Text = "42"
        CASE 4 :
            tfmult.Text = "48"
        CASE 5 :
            tfmult.Text = "168"
        CASE 6 :
            tfmult.Text = "336"
    END SELECT
    tfmultok_click
END SUB

SUB useindischeckboxsub
    IF useindischeckbox.Checked = 0 THEN
        useindi.Checked = 0
        EXIT SUB
    END IF
    IF useindischeckbox.Checked = 1 THEN
        useindi.Checked = 1
        EXIT SUB
    END IF
END SUB

CREATE calendarform AS QFORM
    Caption = "Find bar"
    Visible = 0
    CREATE calendarobj AS qcalendar
        loadcal(DATE$)
    END CREATE
    CREATE timelab AS QLABEL
        Top = calendarobj.Top + calendarobj.Height
        Caption = "Time: "
    END CREATE
    CREATE timeedit AS QEDIT
        Top = timelab.Top
        Left = timelab.Width
        Width = 50
        Text = "00:00"
    END CREATE
    CREATE findbarbtn AS QBUTTON
        Top = timelab.Top
        Left = timeedit.Left + timeedit.Width
        Caption = "Find bar"
        OnClick = findbarsub
    END CREATE
END CREATE

SUB findbarsub
    DIM caldatey AS STRING
    DIM caldatem AS STRING
    DIM caldated AS STRING
    DIM caldate AS STRING
    DIM caldate2 AS STRING
    DIM i AS INTEGER

    caldatey = STR$(calendarobj.y)
    caldatem = STR$(calendarobj.m)
    caldated = STR$(calendarobj.d)

    i = 0
    WHILE i < 4 - LEN(STR$(calendarobj.y))
        caldatey = "0" + caldatey
        i ++
    WEND

    i = 0
    WHILE i < 2 - LEN(STR$(calendarobj.m))
        caldatem = "0" + caldatem
        i ++
    WEND

    i = 0
    WHILE i < 2 - LEN(STR$(calendarobj.d))
        caldated = "0" + caldated
        i ++
    WEND

    caldate = caldatey + "." + caldatem + "." + caldated
    caldate2 = caldatey + "-" + caldatem + "-" + caldated

    FOR i = 1 TO chartbars(displayedfile)
        IF (like(Grid.Cell(rowgridoffset + 1 , i) , caldate) OR like(Grid.Cell(rowgridoffset + 1 , i) , caldate2)) AND _
         like(Grid.Cell(rowgridoffset + 2 , i) , timeedit.Text) THEN
            Scrollchart.Position = i + numbars - 1
            clickedbarnb = i - chartstart
            graphbarnboncurstatic = clickedbarnb + chartstart
            justrefreshchart
            EXIT FOR
        END IF
    NEXT i
END SUB

CREATE frmlogreverse AS QFORM
    Visible = 0
    Height = 600
    Width = 800
    OnResize = frmlogreverseresized
    CREATE logreverseedit AS QRICHEDIT
        Height = frmlogreverse.Height - 30
        Width = frmlogreverse.Width - 10
        ScrollBars = ssBoth
    END CREATE
END CREATE

DIM readmeFont AS QFONT
readmeFont.Name = "Arial"
readmeFont.size=13


CREATE frmreadme AS QFORM
    caption=homepath+"\docs\readme.txt"
    Visible = 0
    Height = 600
    Width = 800
    OnResize = frmreadmeresized
    CREATE readmeedit AS QRICHEDIT
        Height = frmreadme.Height - 40
        Width = frmreadme.Width - 30
        ScrollBars = ssBoth
        font=readmefont
    END CREATE
END CREATE

CREATE frmwhatsnew AS QFORM
    caption="What's new"
    Visible = 0
    Height = 600
    Width = 800
    OnResize = frmwhatsnewresized
    CREATE whatsnewedit AS QRICHEDIT
        Height = frmwhatsnew.Height - 40
        Width = frmwhatsnew.Width - 30
        ScrollBars = ssBoth
        font=readmefont
    END CREATE
END CREATE

DIM file AS QFILESTREAM
file.open(homepath+"\docs\readme.txt" , 0)

DO

    readmeedit.text = readmeedit.text+file.ReadLine+chr$(10)

LOOP UNTIL file.eof
file.close

SUB frmlogreverseresized
    logreverseedit.Height = frmlogreverse.Height - 30
    logreverseedit.Width = frmlogreverse.Width - 10
END SUB

SUB frmreadmeresized
    readmeedit.Height = frmreadme.Height - 40
    readmeedit.Width = frmreadme.Width - 30
END SUB

SUB frmwhatsnewresized
    whatsnewedit.Height = frmreadme.Height - 40
    whatsnewedit.Width = frmreadme.Width - 30
END SUB

SUB tfmultchange
    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Timeframe multiplier on " + importedfile(displayedfile) + " changed to " + tfmult.Text + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Timeframe multiplier on " + importedfile(displayedfile) + " changed to " + tfmult.Text)
    DIM fileqtp AS QFILESTREAM
    fileqtp.open(homepath + "\reversetmp.log" , 2)
    fileqtp.Position = fileqtp.Size
    fileqtp.WriteLine(DATE$ + " " + TIME$ + " " + "Timeframe multiplier on " + importedfile(displayedfile) + " changed to " + tfmult.Text)
    fileqtp.close
    say "Timeframe multiplier changed to: "+tfmult.text
END SUB

DIM PopupMenu AS QPOPUPMENU
DIM popupItem1 AS QMENUITEM
popupItem1.Caption = "Move"
popupItem1.OnClick = moveobjectclick
DIM popupItem2 AS QMENUITEM
popupItem2.Caption = "Delete"
popupItem2.OnClick = deleteobjectcursor
DIM popupItem3 AS QMENUITEM
popupItem3.Caption = "Duplicate"
popupItem3.OnClick = moveobjectclick
DIM popupItem4 AS QMENUITEM
popupItem4.Caption = "Rotate"
popupItem4.OnClick = moveobjectclick

PopupMenu.AddItems(popupItem1 , popupItem2 , popupItem3, popupItem4)
PopupMenu.windowhandle = frmMain.Handle

DIM popupmenubar AS QPOPUPMENU
DIM popupbaritem1 AS QMENUITEM
popupbaritem1.Caption = "Reverse till end"
popupbaritem1.OnClick = reversetillend
DIM popupbaritem2 AS QMENUITEM
popupbaritem2.Caption = "Delete after"
popupbaritem2.OnClick = deleteafter
popupmenubar.AddItems(popupbaritem1,popupbaritem2)
PopupMenu.windowhandle = frmMain.Handle

SUB deleteobjectcursor

    IF objectcursor.objtype = 1 THEN
        trendlinesdb.deleterow(objectcursor.offset)
        trendlinesoffset --
        IF trendlinesoffset < 0 THEN
            trendlinesoffset = 0
        END IF
        justrefreshchart
    END IF
    
    IF objectcursor.objtype = 2 THEN
        sqr2db.deleterow(objectcursor.offset)
        sqr2offset --
        IF sqr2offset < 0 THEN
            sqr2offset = 0
        END IF
        justrefreshchart
    END IF
    
    IF objectcursor.objtype = 3 THEN
        tri2db.deleterow(objectcursor.offset)
        tri2offset --
        IF tri2offset < 0 THEN
            tri2offset = 0
        END IF
        justrefreshchart
    END IF

END SUB


SUB nexttoolsclick
    trendlinebtn.Visible = 0
    timeextbtn.Visible = 1
    sq9fbtn.Visible = 0
    tsq9fbtn.Visible = 1
    sq144btn.Visible = 0
    tsq144btn.Visible = 1
    fibofanbtn.Visible = 0
    fiboretbtn.Visible = 0
    parabtn.Visible = 0
    hlinebtn.Visible = 0
    vlinebtn.Visible = 0
    sqrbtn.Visible = 0
    tribtn.Visible = 0
    sqr2btn.Visible = 1
    tri2btn.Visible = 1
    circlebtn.Visible = 0
    crossbtn.Visible = 0
    invcirclebtn.Visible = 0
    textbtn.Visible = 0
    pencolorbtn.Visible = 0
    textfontbtn.Visible = 0
    aimingbtn.Visible = 0
    clearbtn.Visible = 0
    handdbtn.Visible = 0
    sinbtn.Visible = 0
    logbtn.Visible = 0
    expbtn.Visible = 0
    trackb.Visible = 0
    trackb2.Visible = 0
    reversebtn.Visible = 0
    flipbtn.Visible = 0
    ellipsebtn.Visible = 0
    pitchforkbtn.Visible = 0
    priceextbtn.Visible = 0
    pricecyclesbtn.Visible = 1
    timecyclesbtn.Visible = 1
    logspiralbtn.Visible = 1
    polybtn.Visible = 1
    pentagbtn.Visible = 1
    orcyclesbtn.Visible = 1
    cursorbtn.Visible = 0
    polygbtn.visible=1
END SUB

SUB previoustoolsclick
    trendlinebtn.Visible = 1
    timeextbtn.Visible = 0
    sq9fbtn.Visible = 1
    tsq9fbtn.Visible = 0
    sq144btn.Visible = 1
    tsq144btn.Visible = 0
    fibofanbtn.Visible = 1
    fiboretbtn.Visible = 1
    parabtn.Visible = 1
    hlinebtn.Visible = 1
    vlinebtn.Visible = 1
    sqrbtn.Visible = 1
    tribtn.Visible = 1
    sqr2btn.Visible = 0
    tri2btn.Visible = 0
    circlebtn.Visible = 1
    crossbtn.Visible = 1
    invcirclebtn.Visible = 1
    textbtn.Visible = 1
    pencolorbtn.Visible = 1
    textfontbtn.Visible = 1
    aimingbtn.Visible = 1
    clearbtn.Visible = 1
    handdbtn.Visible = 1
    sinbtn.Visible = 1
    logbtn.Visible = 1
    expbtn.Visible = 1
    trackb.Visible = 1
    trackb2.Visible = 1
    reversebtn.Visible = 1
    flipbtn.Visible = 1
    ellipsebtn.Visible = 1
    pitchforkbtn.Visible = 1
    priceextbtn.Visible = 1
    pricecyclesbtn.Visible = 0
    timecyclesbtn.Visible = 0
    logspiralbtn.Visible = 0
    polybtn.Visible = 0
    pentagbtn.Visible = 0
    orcyclesbtn.Visible = 0
    cursorbtn.Visible = 1
    polygbtn.visible=0
END SUB

SUB charttypecombochange
    charttypecomboindex = charttypecombo.ItemIndex
    justrefreshchart
    setup
    say "Chart type changed to: "+charttypecombo.item(charttypecombo.ItemIndex)
END SUB

CREATE formtoolsinfo AS QFORM
    'UndockedForm.Parent = frmmain
    'AltAlign = 4
    'Caption = "Tools info"
    'Align = 0
    'DockStyle = 1
    'UnDockStyle = 1
    'style = 1
    'Client.BevelOuter = 0
    'Canvas.Font.Name = "Arial"
    'width=85
    'UndockedWidth = toolsPanel.Width
    'height=620
    'UndockedHeight = toolsPanel.Height
    'CanClose = 1
    'docked=0
    Parent = frmMain
    Visible = 0
    Width = 300
    Height = 300
    Caption = "Tools informations"
    CREATE infotext AS QRICHEDIT
        Width = formtoolsinfo.Width - 10
        Height = 0.5 * (formtoolsinfo.Height - 30)
        'scrollbars=ssboth
    END CREATE
    CREATE infotext2 AS QRICHEDIT
        Width = formtoolsinfo.Width - 10
        Height = 0.5 * (formtoolsinfo.Height - 30)
        Top = 0.5 * (formtoolsinfo.Height - 30)
        'scrollbars=ssboth
    END CREATE
    OnResize = formtoolsinforesized

END CREATE

SUB sepindicursorpos(x AS INTEGER , y AS INTEGER)
    mousemovesepindix = x
    mousemovesepindiy = y
    IF formtoolsinfo.Visible = 0 THEN
        EXIT SUB
    END IF
    DIM XVAL AS INTEGER , YVAL AS INTEGER
    'GetCursorPos(NPOS)
    'XVAL=NPOS.xpos
    'YVAL=NPOS.ypos
    'xval=xval-frmmain.left-graph.left-4-mouseexcentricityx
    'yval=yval-frmmain.top-graph.top-43-mouseexcentricityy
    XVAL = mousemovesepindix
    YVAL = mousemovesepindiy
END SUB


SUB graphcursorpos(x AS INTEGER , y AS INTEGER)
    mousemovegraphx = x
    mousemovegraphy = y
    IF formtoolsinfo.Visible = 0 THEN
        EXIT SUB
    END IF
    infotext2.Text = ""
    'if graphclick=0 then
    DIM XVAL AS INTEGER , YVAL AS INTEGER
    'GetCursorPos(NPOS)
    'XVAL=NPOS.xpos
    'YVAL=NPOS.ypos
    'xval=xval-frmmain.left-graph.left-4-mouseexcentricityx
    'yval=yval-frmmain.top-graph.top-43-mouseexcentricityy
    XVAL = mousemovegraphx
    YVAL = mousemovegraphy

    graphhbegin = 80
    'dim graphhend as integer
    'graphhend=750+graph.width-891
    graphhend = Graph.Width - 41 - spaceforwards
    graphhspace = graphhend - graphhbegin


    graphvbegin = 42

    graphvend = 591 + Graph.Height - 649

    graphvspace = graphvend - graphvbegin


    DIM graphendyear AS INTEGER
    DIM graphendmonth AS INTEGER
    DIM graphendday AS INTEGER
    DIM graphbeginyear AS INTEGER
    DIM graphbeginmonth AS INTEGER
    DIM graphbeginday AS INTEGER


    DIM graphvi AS INTEGER
    graphvhigh = 0
    FOR graphvi = Scrollchart.Position - numbars + 1 TO Scrollchart.Position
        IF VAL(Grid.Cell(rowgridoffset + 4 , graphvi)) > graphvhigh THEN
            graphvhigh = VAL(Grid.Cell(rowgridoffset + 4 , graphvi))
        END IF
    NEXT graphvi
    graphvlow = graphvhigh
    FOR graphvi = Scrollchart.Position - numbars + 1 TO Scrollchart.Position
        IF VAL(Grid.Cell(rowgridoffset + 5 , graphvi)) < graphvlow THEN
            graphvlow = VAL(Grid.Cell(rowgridoffset + 5 , graphvi))
        END IF
    NEXT graphvi

    infotext2.Text = infotext2.Text + "Highest high: " + STR$(graphvhigh) + CHR$(10)
    infotext2.Text = infotext2.Text + "Lowest low: " + STR$(graphvlow) + CHR$(10)

    'dim graphvi as integer
    alltimehigh = 0
    FOR graphvi = 1 TO chartbars(displayedfile)
        IF VAL(Grid.Cell(rowgridoffset + 4 , graphvi)) > alltimehigh THEN
            alltimehigh = VAL(Grid.Cell(rowgridoffset + 4 , graphvi))
        END IF
    NEXT graphvi
    alltimelow = alltimehigh
    FOR graphvi = 1 TO chartbars(displayedfile)
        IF VAL(Grid.Cell(rowgridoffset + 5 , graphvi)) < alltimelow THEN
            alltimelow = VAL(Grid.Cell(rowgridoffset + 5 , graphvi))
        END IF
    NEXT graphvi

    infotext2.Text = infotext2.Text + "All time high: " + STR$(alltimehigh) + CHR$(10)
    infotext2.Text = infotext2.Text + "All time low: " + STR$(alltimelow) + CHR$(10)


    DIM graphenddate AS STRING
    DIM graphbegindate AS STRING

    graphenddate = Grid.Cell(rowgridoffset + 1 , Scrollchart.Position)
    graphbegindate = Grid.Cell(rowgridoffset + 1 , Scrollchart.Position - numbars + 1)

    graphendyear = VAL(MID$(graphenddate , 0 , 4))
    graphendmonth = VAL(MID$(graphenddate , 6 , 2))
    graphendday = VAL(MID$(graphenddate , 9 , 2))
    graphbeginyear = VAL(MID$(graphbegindate , 0 , 4))
    graphbeginmonth = VAL(MID$(graphbegindate , 6 , 2))
    graphbeginday = VAL(MID$(graphbegindate , 9 , 2))

    graphserialdateend = DateSerial(graphendyear , graphendmonth , graphendday)
    graphserialdatebegin = DateSerial(graphbeginyear , graphbeginmonth , graphbeginday)
    graphserialdatespace = graphserialdateend - graphserialdatebegin

    DIM graphbarnbbegin AS INTEGER
    graphbarnbbegin = chartstart
    DIM graphbarnbend AS INTEGER
    graphbarnbend = chartstart + numbars
    DIM graphbarnbspace AS INTEGER
    graphbarnbspace = graphbarnbend - graphbarnbbegin + 1

    DIM yscalehigh AS DOUBLE
    yscalehigh = graphvlow + (graphvhigh - graphvlow) + ymaxgraphglobal '* (1 / yscaletrackbarposition)
    
    DIM yscalelow AS DOUBLE
    yscalelow = graphvhigh - (graphvhigh - graphvlow) - ymingraphglobal '* (1 / yscaletrackbarposition)

    graphpricespace = yscalehigh - yscalelow 'graphvlow

    DIM graphhratio AS DOUBLE
    graphhratio = (XVAL - graphhbegin) / graphhspace

    DIM graphvratio AS DOUBLE
    graphvratio = (YVAL - graphvbegin) / graphvspace

    'graphpriceoncur = (graphvlow + (yscalehigh - graphvlow)) - graphvratio * graphpricespace
    graphpriceoncur = (yscalelow + (yscalehigh - yscalelow)) - graphvratio * graphpricespace

    infotext2.Text = infotext2.Text + "Price on cursor: " + STR$(graphpriceoncur) + CHR$(10)

    graphserialdateoncur = graphserialdatebegin + graphhratio * graphserialdatespace

    graphbarnboncur = graphbarnbbegin + graphhratio * graphbarnbspace


    DEFLNG yy , mm , dd , dayofweek
    dayofweek = DateFromSerial(graphserialdateoncur , yy , mm , dd)
    'SHOWMESSAGE "Testing DateFromSerial" + rqcrlf + rqcrlf + _
    '"Year = " + STR$(yy) + rqcrlf + _
    '"Month = " + STR$(mm) + rqcrlf + _
    '"Date = " + STR$(dd) + rqcrlf + _
    '"DayOfWeek = " + STR$(DayOfWeek)
    'print str$(yy)+"-"+str$(mm)+"-"+str$(dd)

    graphdateoncur = STR$(yy) + "-" + STR$(mm) + "-" + STR$(dd)
    infotext2.Text = infotext2.Text + "Date on cursor: " + graphdateoncur + CHR$(10)


    graphjuliendateoncur = JulianDate(dd , mm , yy) + 1
    infotext2.Text = infotext2.Text + "Julian date on cursor: " + STR$(graphjuliendateoncur) + CHR$(10)

    infotext2.Text = infotext2.Text + "Begin date: " + REPLACESUBSTR$(graphbegindate , "." , "-") + CHR$(10)
    infotext2.Text = infotext2.Text + "End date: " + REPLACESUBSTR$(graphenddate , "." , "-") + CHR$(10)

    infotext2.Text = infotext2.Text + "Begin Julian date: " + STR$(JulianDate(graphbeginday , graphbeginmonth , graphbeginyear) + 1) + CHR$(10)
    infotext2.Text = infotext2.Text + "End Julian date: " + STR$(JulianDate(graphendday , graphendmonth , graphendyear) + 1) + CHR$(10)

    infotext2.Text = infotext2.Text + "Bar # on cursor: " + STR$(graphbarnboncur) + CHR$(10)


    'if formtoolsinfo.visible=1 then
    'setfocus(formtoolsinfo.handle)
    'end if
END SUB

SUB graphcursorpos2
    infotext2.Text = ""
    'if graphclick=0 then
    DIM XVAL AS INTEGER , YVAL AS INTEGER
    'GetCursorPos(NPOS)
    'XVAL=NPOS.xpos
    'YVAL=NPOS.ypos
    'xval=xval-frmmain.left-graph.left-4-mouseexcentricityx
    'yval=yval-frmmain.top-graph.top-43-mouseexcentricityy
    XVAL = mousemovegraphx
    YVAL = mousemovegraphy
    xvalgcp2 = XVAL + frmMain.Left + 4 + Graph.Left
    yvalgcp2 = YVAL + frmMain.Top + 43 + Graph.Top

    graphhbegin = 80
    'dim graphhend as integer
    'graphhend=750+graph.width-891
    graphhend = Graph.Width - 41 - spaceforwards

    graphhspace = graphhend - graphhbegin


    graphvbegin = 42
    DIM graphvend AS INTEGER
    graphvend = 591 + Graph.Height - 649

    graphvspace = graphvend - graphvbegin


    DIM graphendyear AS INTEGER
    DIM graphendmonth AS INTEGER
    DIM graphendday AS INTEGER
    DIM graphbeginyear AS INTEGER
    DIM graphbeginmonth AS INTEGER
    DIM graphbeginday AS INTEGER


    DIM graphvi AS INTEGER
    graphvhigh = 0
    FOR graphvi = Scrollchart.Position - numbars + 1 TO Scrollchart.Position
        IF VAL(Grid.Cell(rowgridoffset + 4 , graphvi)) > graphvhigh THEN
            graphvhigh = VAL(Grid.Cell(rowgridoffset + 4 , graphvi))
        END IF
        'doevents
    NEXT graphvi
    graphvlow = graphvhigh
    FOR graphvi = Scrollchart.Position - numbars + 1 TO Scrollchart.Position
        IF VAL(Grid.Cell(rowgridoffset + 5 , graphvi)) < graphvlow THEN
            graphvlow = VAL(Grid.Cell(rowgridoffset + 5 , graphvi))
        END IF
        'doevents
    NEXT graphvi

    infotext2.Text = infotext2.Text + "Highest high: " + STR$(graphvhigh) + CHR$(10)
    infotext2.Text = infotext2.Text + "Lowest low: " + STR$(graphvlow) + CHR$(10)

    alltimehigh = 0
    FOR graphvi = 1 TO chartbars(displayedfile)
        IF VAL(Grid.Cell(rowgridoffset + 4 , graphvi)) > alltimehigh THEN
            alltimehigh = VAL(Grid.Cell(rowgridoffset + 4 , graphvi))
        END IF
        'doevents
    NEXT graphvi
    alltimelow = alltimehigh
    FOR graphvi = 1 TO chartbars(displayedfile)
        IF VAL(Grid.Cell(rowgridoffset + 5 , graphvi)) < alltimelow THEN
            alltimelow = VAL(Grid.Cell(rowgridoffset + 5 , graphvi))
        END IF
        'doevents
    NEXT graphvi

    infotext2.Text = infotext2.Text + "All time high: " + STR$(alltimehigh) + CHR$(10)
    infotext2.Text = infotext2.Text + "All time low: " + STR$(alltimelow) + CHR$(10)


    DIM graphenddate AS STRING
    DIM graphbegindate AS STRING

    graphenddate = Grid.Cell(rowgridoffset + 1 , Scrollchart.Position)
    graphbegindate = Grid.Cell(rowgridoffset + 1 , Scrollchart.Position - numbars + 1)

    graphendyear = VAL(MID$(graphenddate , 0 , 4))
    graphendmonth = VAL(MID$(graphenddate , 6 , 2))
    graphendday = VAL(MID$(graphenddate , 9 , 2))
    graphbeginyear = VAL(MID$(graphbegindate , 0 , 4))
    graphbeginmonth = VAL(MID$(graphbegindate , 6 , 2))
    graphbeginday = VAL(MID$(graphbegindate , 9 , 2))

    'graphserialdateend = DateSerial(graphendyear , graphendmonth , graphendday)
    'graphserialdatebegin = DateSerial(graphbeginyear , graphbeginmonth , graphbeginday)
    graphserialdateend=timechartpos(graph.data.colcount-1,0)
    graphserialdatebegin=timechartpos(0,0)
    graphserialdatespace = graphserialdateend - graphserialdatebegin

    DIM graphbarnbbegin AS INTEGER
    graphbarnbbegin = chartstart
    DIM graphbarnbend AS INTEGER
    graphbarnbend = chartstart + numbars
    DIM graphbarnbspace AS INTEGER
    graphbarnbspace = graphbarnbend - graphbarnbbegin + 1

    DIM yscalehigh AS DOUBLE
    yscalehigh = graphvlow + (graphvhigh - graphvlow) + ymaxgraphglobal '* (1 / yscaletrackbarposition)
    
    DIM yscalelow AS DOUBLE
    yscalelow = graphvhigh - (graphvhigh - graphvlow) - ymingraphglobal '* (1 / yscaletrackbarposition)

    graphpricespace = yscalehigh - yscalelow 'graphvlow

    DIM graphhratio AS DOUBLE
    graphhratio = (XVAL - graphhbegin) / graphhspace

    DIM graphvratio AS DOUBLE
    graphvratio = (YVAL - graphvbegin) / graphvspace

    'graphpriceoncur = (graphvlow + (yscalehigh - graphvlow)) - graphvratio * graphpricespace
    'graphpriceoncur = (yscalelow + (yscalehigh - yscalelow)) - graphvratio * graphpricespace
    
        ' Computing price on cursor position
if pricechartpos(0,1)-pricechartpos(1,1)>0 then
    defdbl pricepixelratio=(pricechartpos(0,1)-yval)/(pricechartpos(0,1)-pricechartpos(1,1))
    graphpriceoncur=(pricechartpos(1,0)-pricechartpos(0,0))*pricepixelratio+pricechartpos(0,0)
    graphpriceoncur=val(Format$("%12.5f", graphpriceoncur))
end if    
    ' ---------------------------------

    infotext2.Text = infotext2.Text + "Price on cursor: " + STR$(graphpriceoncur) + CHR$(10)

    'graphserialdateoncur = graphserialdatebegin + graphhratio * graphserialdatespace

    graphbarnboncur = graphbarnbbegin + graphhratio * graphbarnbspace

    DEFLNG yy , mm , dd , dayofweek
    dayofweek = DateFromSerial(graphserialdateoncur , yy , mm , dd)
    'SHOWMESSAGE "Testing DateFromSerial" + rqcrlf + rqcrlf + _
    '"Year = " + STR$(yy) + rqcrlf + _
    '"Month = " + STR$(mm) + rqcrlf + _
    '"Date = " + STR$(dd) + rqcrlf + _
    '"DayOfWeek = " + STR$(DayOfWeek)
    'print str$(yy)+"-"+str$(mm)+"-"+str$(dd)
    'dim graphdateoncur as string
      
    'graphdateoncur = STR$(yy) + "-" + STR$(mm) + "-" + STR$(dd)
    
    ' Computing time on cursor position
'if timechartpos(1,1)-timechartpos(0,1)>0 then
'    defdbl timepixelratio=(xval-timechartpos(0,1))/(timechartpos(1,1)-timechartpos(0,1))
'    defdbl unixtimeratio=round((timechartpos(1,0)-timechartpos(0,0))*timepixelratio)+timechartpos(0,0)
'    defstr myunixtimestr=Format$("%12.0f", unixtimeratio)
'    cpptmpfuncreturn=varptr$(unix_time_to_date(varptr(myunixtimestr)))
'defstr year,month,day,hour,minute
'year=mid$(cpptmpfuncreturn,21,4)
'month=mid$(cpptmpfuncreturn,5,3)
'day=mid$(cpptmpfuncreturn,9,2)
'hour=mid$(cpptmpfuncreturn,12,2)
'minute=mid$(cpptmpfuncreturn,15,2)
'    graphdateoncur =year + "-" + strtomonth(month) + "-" + day+" "+hour+":"+minute
'end if    
defint i
defint timepixelinterval=timechartpos(1,1)-timechartpos(0,1)
for i=0 to 1000
if xval>=timechartpos(i,1)-timepixelinterval/2 and xval<timechartpos(i,1)+timepixelinterval/2 then
defdbl unixtimeratio=timechartpos(i,0)
graphserialdateoncur=unixtimeratio
    defstr myunixtimestr=Format$("%12.0f", unixtimeratio)
    cpptmpfuncreturn=varptr$(unix_time_to_date(varptr(myunixtimestr)))
defstr year,month,day,hour,minute
year=mid$(cpptmpfuncreturn,21,4)
month=mid$(cpptmpfuncreturn,5,3)
day=mid$(cpptmpfuncreturn,9,2)
hour=mid$(cpptmpfuncreturn,12,2)
minute=mid$(cpptmpfuncreturn,15,2)
    graphdateoncur =year + "-" + strtomonth(month) + "-" + day+" "+hour+":"+minute
    exit for
end if
'doevents    
next i
    ' ---------------------------------
    
    infotext2.Text = infotext2.Text + "Date on cursor: " + graphdateoncur + CHR$(10)

    'deflng graphjuliendateoncur
    graphjuliendateoncur = JulianDate(dd , mm , yy) + 1
    infotext2.Text = infotext2.Text + "Julian date on cursor: " + STR$(graphjuliendateoncur) + CHR$(10)

    infotext2.Text = infotext2.Text + "Begin date: " + REPLACESUBSTR$(graphbegindate , "." , "-") + CHR$(10)
    infotext2.Text = infotext2.Text + "End date: " + REPLACESUBSTR$(graphenddate , "." , "-") + CHR$(10)

    infotext2.Text = infotext2.Text + "Begin Julian date: " + STR$(JulianDate(graphbeginday , graphbeginmonth , graphbeginyear) + 1) + CHR$(10)
    infotext2.Text = infotext2.Text + "End Julian date: " + STR$(JulianDate(graphendday , graphendmonth , graphendyear) + 1) + CHR$(10)

END SUB


'-------------------------------------------------------------------------------
'Global hotkeys routines

'-- CTRL+A
'IF RegisterHotKey(hotkeysfrm.Handle, 0, MOD_CTRL, ASC("A")) = 0 THEN
'ShowMessage("Sorry, hot key CTRL+A already taken!")
'END IF

'-- CTRL+SHIFT+B
'IF RegisterHotKey(hotkeysfrm.Handle, 1, MOD_CTRL OR MOD_SHFT, ASC("B")) = 0 THEN
'ShowMessage("Sorry, hot key CTRL+SHIFT+B already taken!")
'END IF

'-- ESC
'IF RegisterHotKey(hotkeysfrm.Handle, 0,MOD_GENERIC ,VK_ESCAPE) = 0 THEN
'ShowMessage("Sorry, hot key ESC already taken!")
'END IF

'-- SPACE
'IF RegisterHotKey(hotkeysfrm.Handle, 1,MOD_GENERIC ,VK_SPACE) = 0 THEN
'ShowMessage("Sorry, hot key SPACE already taken!")
'END IF

'Form.ShowModal

'End global hotkeys routines
'-------------------------------------------------------------------------------


'Indexing indicators

DIM indiinilist AS QFILELISTBOX
indiinilist.Visible = 0
indiinilist.Parent = frmMain
indiinilist.Mask = "*.ini"
indiinilist.Directory = homepath + "\indicators"

'DIM qtcList AS QFILELISTBOX
'qtcList.Visible = 0
'qtcList.Parent = frmMain
'qtcList.Mask = "*.ini"
'qtcList.Directory = homepath + "\indicators"

DIM indinames(0 TO indiinilist.ItemCount - 1) AS STRING
DIM nli AS INTEGER
'DIM qtnfile AS QFILESTREAM
FOR nli = 0 TO indiinilist.ItemCount - 1
    'qtnfile.open(indiinilist.Item(nli) , fmOpenRead)
    'indinames(nli) = qtnfile.ReadLine() 'Read an entire line
    indiini.filename=homepath+"\indicators\"+indiinilist.Item(nli)
    indiini.section="Settings"
    indinames(nli)=indiini.get("name","")
NEXT nli
'qtnfile.close

DIM indicanvas(0 TO indiinilist.ItemCount - 1) AS STRING

'dim nli as integer
'DIM qtcfile AS QFILESTREAM
FOR nli = 0 TO indiinilist.ItemCount - 1
    'qtcfile.open(indiinilist.Item(nli) , fmOpenRead)
    'indicanvas(nli) = qtcfile.ReadLine() 'Read an entire line
    indiini.filename=homepath+"\indicators\"+indiinilist.Item(nli)
    indiini.section="Settings"
    indicanvas(nli)=indiini.get("canvas","")
NEXT nli
'qtcfile.close

'Indexing indicators

'DIM descList AS QFILELISTBOX
'descList.Visible = 0
'descList.Parent = frmMain
'descList.Mask = "*.ini"
'descList.Directory = homepath + "\indicators"

DIM indidesc(0 TO indiinilist.ItemCount - 1) AS STRING
DIM indilisty AS INTEGER
DIM nld AS INTEGER
DIM descordercount AS INTEGER
descordercount = 0
'DIM descfile AS QFILESTREAM
FOR indilisty = 0 TO 1
    FOR nld = 0 TO indiinilist.ItemCount - 1
        IF VAL(indicanvas(nld)) = indilisty THEN
            'descfile.open(indiinilist.Item(nld) , fmOpenRead)
            'indidesc(descordercount) = descfile.ReadLine() 'Read an entire line
            indiini.filename=homepath+"\indicators\"+indiinilist.Item(nld)
            indiini.section="Settings"
            indidesc(descordercount)=indiini.get("description","")
            descordercount ++
        END IF
    NEXT nld
NEXT indilisty
'descfile.close

SUB trackbchange
    logamplitude = trackb.Position * 0.2 * trackb2.Position * 0.2
END SUB

SUB resetbtns
    trendlinebtn.Flat = 0
    trendlinebtn.Color = &Hcccccc
    fibofanbtn.Flat = 0
    fibofanbtn.Color = &Hcccccc
    fiboretbtn.Flat = 0
    fiboretbtn.Color = &Hcccccc
    parabtn.Flat = 0
    parabtn.Color = &Hcccccc
    hlinebtn.Flat = 0
    hlinebtn.Color = &Hcccccc
    vlinebtn.Flat = 0
    vlinebtn.Color = &Hcccccc
    sqrbtn.Flat = 0
    sqrbtn.Color = &Hcccccc
    tribtn.Flat = 0
    tribtn.Color = &Hcccccc
    sqr2btn.Flat = 0
    sqr2btn.Color = &Hcccccc
    tri2btn.Flat = 0
    tri2btn.Color = &Hcccccc
    circlebtn.Flat = 0
    circlebtn.Color = &Hcccccc
    crossbtn.Flat = 0
    crossbtn.Color = &Hcccccc
    invcirclebtn.Flat = 0
    invcirclebtn.Color = &Hcccccc
    textbtn.Flat = 0
    textbtn.Color = &Hcccccc
    aimingbtn.Flat = 0
    aimingbtn.Color = &Hcccccc
    handdbtn.Flat = 0
    handdbtn.Color = &Hcccccc
    sinbtn.Flat = 0
    sinbtn.Color = &Hcccccc
    logbtn.Flat = 0
    logbtn.Color = &Hcccccc
    expbtn.Flat = 0
    expbtn.Color = &Hcccccc
    priceextbtn.Flat = 0
    priceextbtn.Color = &Hcccccc
    ellipsebtn.Flat = 0
    ellipsebtn.Color = &Hcccccc
    pitchforkbtn.Flat = 0
    pitchforkbtn.Color = &Hcccccc
    sq9fbtn.Flat = 0
    sq9fbtn.Color = &Hcccccc
    tsq9fbtn.Flat = 0
    tsq9fbtn.Color = &Hcccccc
    sq144btn.Flat = 0
    sq144btn.Color = &Hcccccc
    tsq144btn.Flat = 0
    tsq144btn.Color = &Hcccccc
    timeextbtn.Flat = 0
    timeextbtn.Color = &Hcccccc
    pricecyclesbtn.Flat = 0
    pricecyclesbtn.Color = &Hcccccc
    timecyclesbtn.Flat = 0
    timecyclesbtn.Color = &Hcccccc
    cursorbtn.Flat = 0
    cursorbtn.Color = &Hcccccc
    logspiralbtn.Flat = 0
    logspiralbtn.Color = &Hcccccc
    polybtn.Flat = 0
    polybtn.Color = &Hcccccc
    pentagbtn.Flat = 0
    pentagbtn.Color = &Hcccccc
    orcyclesbtn.Flat = 0
    orcyclesbtn.Color = &Hcccccc
    polygbtn.Flat = 0
    polygbtn.Color = &Hcccccc
END SUB

SUB scrollmodebtnclick
    IF scrollmodebtn.Flat = 0 THEN
        scrollmodebtn.Flat = 1
        scrollmodebtn.Color = &H88cc88
        scrollmode = 1
        'scrollchart.enabled=1
        EXIT SUB
    END IF
    IF scrollmodebtn.Flat = 1 THEN
        scrollmodebtn.Flat = 0
        scrollmodebtn.Color = &Hcccccc
        scrollmode = 0
        IF openedfilesnb = 0 THEN
            EXIT SUB
        END IF
        'scrollchart.enabled=0
        chartstart = Scrollchart.Position - numbars
        IF scrollchartpositionwait = 1 THEN
            btnOnClick(drwBox)
        END IF
        EXIT SUB
    END IF
END SUB

SUB disablescrollmode
    'scrollchart.enabled=0
    scrollmodebtn.Flat = 0
    scrollmodebtn.Color = &Hcccccc
    scrollmode = 0
    'scrollchart.enabled=0
    chartstart = Scrollchart.Position - numbars
    IF scrollchartpositionwait = 1 THEN
        btnOnClick(drwBox)
    END IF
    'scrollchart.enabled=1
END SUB

SUB setspaceforwards
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    disablescrollmode
    spaceforwards = VAL(spaceforwardsedit.Text)
    IF showcanvas = 1 THEN
        canvas.Width = frmMain.ClientWidth - leftwidth - 144 - spaceforwards
        WITH closedispcanvas
            .Top = canvas.Top
            .Left = canvas.Width + 181 - 4 + leftwidth - 100
        END WITH
        'sepindizoommore.Left=leftwidth+97+canvas.width+15
        'sepindizoomless.Left=leftwidth+97+canvas.width+15
    END IF
    Scrollchart.Max = chartbars(displayedfile)
    Scrollchart.Position = chartbars(displayedfile)
    chartstart = Scrollchart.Position - numbars
    btnOnClick(drwBox)

    disablescrollmode
    spaceforwards = VAL(spaceforwardsedit.Text)
    IF showcanvas = 1 THEN
        canvas.Width = frmMain.ClientWidth - leftwidth - 144 - spaceforwards
        WITH closedispcanvas
            .Top = canvas.Top
            .Left = canvas.Width + 181 - 4 + leftwidth - 100
        END WITH
        'sepindizoommore.Left=leftwidth+97+canvas.width+15
        'sepindizoomless.Left=leftwidth+97+canvas.width+15
    END IF
    Scrollchart.Max = chartbars(displayedfile)
    Scrollchart.Position = chartbars(displayedfile)
    chartstart = Scrollchart.Position - numbars
    btnOnClick(drwBox)
END SUB

SUB chartscursormode(mode AS INTEGER)
    WITH Graph
        .Cursor = mode
    END WITH
    WITH canvas
        .Cursor = mode
    END WITH
END SUB

SUB trendlinebtnclick
    IF trendlinebtn.Flat = 0 THEN
        resetbtns
        trendlinebtn.Flat = 1
        trendlinebtn.Color = &H88cc88
        chartscursormode = 1
        say trendlinebtn.hint
        EXIT SUB
    END IF
    IF trendlinebtn.Flat = 1 THEN
        trendlinebtn.Flat = 0
        trendlinebtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB cursorbtnclick
    IF cursorbtn.Flat = 0 THEN
        resetbtns
        cursorbtn.Flat = 1
        cursorbtn.Color = &H88cc88
        chartscursormode = 1
        say cursorbtn.hint
        EXIT SUB
    END IF
    IF cursorbtn.Flat = 1 THEN
        cursorbtn.Flat = 0
        cursorbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB timeextbtnclick
    IF timeextbtn.Flat = 0 THEN
        resetbtns
        timeextbtn.Flat = 1
        timeextbtn.Color = &H88cc88
        chartscursormode = 1
        say timeextbtn.hint
        EXIT SUB
    END IF
    IF timeextbtn.Flat = 1 THEN
        timeextbtn.Flat = 0
        timeextbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB fibofanbtnclick
    IF fibofanbtn.Flat = 0 THEN
        resetbtns
        fibofanbtn.Flat = 1
        fibofanbtn.Color = &H88cc88
        chartscursormode = 1
        say fibofanbtn.hint
        EXIT SUB
    END IF
    IF fibofanbtn.Flat = 1 THEN
        fibofanbtn.Flat = 0
        fibofanbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB fiboretbtnclick
    IF fiboretbtn.Flat = 0 THEN
        resetbtns
        fiboretbtn.Flat = 1
        fiboretbtn.Color = &H88cc88
        chartscursormode = 1
        say fiboretbtn.hint
        EXIT SUB
    END IF
    IF fiboretbtn.Flat = 1 THEN
        fiboretbtn.Flat = 0
        fiboretbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB parabtnclick
    IF parabtn.Flat = 0 THEN
        resetbtns
        parabtn.Flat = 1
        parabtn.Color = &H88cc88
        chartscursormode = 1
        say parabtn.hint
        EXIT SUB
    END IF
    IF parabtn.Flat = 1 THEN
        parabtn.Flat = 0
        parabtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB hlinebtnclick
    IF hlinebtn.Flat = 0 THEN
        resetbtns
        hlinebtn.Flat = 1
        hlinebtn.Color = &H88cc88
        chartscursormode = 1
        say hlinebtn.hint
        EXIT SUB
    END IF
    IF hlinebtn.Flat = 1 THEN
        hlinebtn.Flat = 0
        hlinebtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB vlinebtnclick
    IF vlinebtn.Flat = 0 THEN
        resetbtns
        vlinebtn.Flat = 1
        vlinebtn.Color = &H88cc88
        chartscursormode = 1
        say vlinebtn.hint
        EXIT SUB
    END IF
    IF vlinebtn.Flat = 1 THEN
        vlinebtn.Flat = 0
        vlinebtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB sqrbtnclick
    IF sqrbtn.Flat = 0 THEN
        resetbtns
        sqrbtn.Flat = 1
        sqrbtn.Color = &H88cc88
        chartscursormode = 1
        say sqrbtn.hint
        EXIT SUB
    END IF
    IF sqrbtn.Flat = 1 THEN
        sqrbtn.Flat = 0
        sqrbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB tribtnclick
    IF tribtn.Flat = 0 THEN
        resetbtns
        tribtn.Flat = 1
        tribtn.Color = &H88cc88
        chartscursormode = 1
        say tribtn.hint
        EXIT SUB
    END IF
    IF tribtn.Flat = 1 THEN
        tribtn.Flat = 0
        tribtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB sqr2btnclick
    IF sqr2btn.Flat = 0 THEN
        resetbtns
        sqr2btn.Flat = 1
        sqr2btn.Color = &H88cc88
        chartscursormode = 1
        say sqr2btn.hint
        EXIT SUB
    END IF
    IF sqr2btn.Flat = 1 THEN
        sqr2btn.Flat = 0
        sqr2btn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB tri2btnclick
    IF tri2btn.Flat = 0 THEN
        resetbtns
        tri2btn.Flat = 1
        tri2btn.Color = &H88cc88
        chartscursormode = 1
        say tri2btn.hint
        EXIT SUB
    END IF
    IF tri2btn.Flat = 1 THEN
        tri2btn.Flat = 0
        tri2btn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB circlebtnclick
    IF circlebtn.Flat = 0 THEN
        resetbtns
        circlebtn.Flat = 1
        circlebtn.Color = &H88cc88
        chartscursormode = 1
        say circlebtn.hint
        EXIT SUB
    END IF
    IF circlebtn.Flat = 1 THEN
        circlebtn.Flat = 0
        circlebtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB crossbtnclick
    IF crossbtn.Flat = 0 THEN
        resetbtns
        crossbtn.Flat = 1
        crossbtn.Color = &H88cc88
        chartscursormode = 1
        say crossbtn.hint
        EXIT SUB
    END IF
    IF crossbtn.Flat = 1 THEN
        crossbtn.Flat = 0
        crossbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB invcirclebtnclick
    IF invcirclebtn.Flat = 0 THEN
        resetbtns
        invcirclebtn.Flat = 1
        invcirclebtn.Color = &H88cc88
        chartscursormode = 1
        say invcirclebtn.hint
        EXIT SUB
    END IF
    IF invcirclebtn.Flat = 1 THEN
        invcirclebtn.Flat = 0
        invcirclebtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB textbtnclick
    IF textbtn.Flat = 0 THEN
        resetbtns
        textbtn.Flat = 1
        textbtn.Color = &H88cc88
        chartscursormode = 1
        say textbtn.hint
        EXIT SUB
    END IF
    IF textbtn.Flat = 1 THEN
        textbtn.Flat = 0
        textbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB aimingbtnclick
    IF aimingbtn.Flat = 0 THEN
        resetbtns
        aimingbtn.Flat = 1
        aimingbtn.Color = &H88cc88
        chartscursormode = 1
        say aimingbtn.hint
        EXIT SUB
    END IF
    IF aimingbtn.Flat = 1 THEN
        aimingbtn.Flat = 0
        aimingbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB handdbtnclick
    IF handdbtn.Flat = 0 THEN
        resetbtns
        handdbtn.Flat = 1
        handdbtn.Color = &H88cc88
        chartscursormode = 1
        say handdbtn.hint
        EXIT SUB
    END IF
    IF handdbtn.Flat = 1 THEN
        handdbtn.Flat = 0
        handdbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB sinbtnclick
    IF sinbtn.Flat = 0 THEN
        resetbtns
        sinbtn.Flat = 1
        sinbtn.Color = &H88cc88
        chartscursormode = 1
        say sinbtn.hint
        EXIT SUB
    END IF
    IF sinbtn.Flat = 1 THEN
        sinbtn.Flat = 0
        sinbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB logbtnclick
    IF logbtn.Flat = 0 THEN
        resetbtns
        logbtn.Flat = 1
        logbtn.Color = &H88cc88
        chartscursormode = 1
        say logbtn.hint
        EXIT SUB
    END IF
    IF logbtn.Flat = 1 THEN
        logbtn.Flat = 0
        logbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB expbtnclick
    IF expbtn.Flat = 0 THEN
        resetbtns
        expbtn.Flat = 1
        expbtn.Color = &H88cc88
        chartscursormode = 1
        say expbtn.hint
        EXIT SUB
    END IF
    IF expbtn.Flat = 1 THEN
        expbtn.Flat = 0
        expbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB priceextbtnclick
    IF priceextbtn.Flat = 0 THEN
        resetbtns
        priceextbtn.Flat = 1
        priceextbtn.Color = &H88cc88
        chartscursormode = 1
        say priceextbtn.hint
        EXIT SUB
    END IF
    IF priceextbtn.Flat = 1 THEN
        priceextbtn.Flat = 0
        priceextbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB reversebtnclick
    IF reversebtn.Flat = 0 THEN
        'resetbtns
        reversebtn.Flat = 1
        reversebtn.Color = &H88cc88
        chartscursormode = 1
        reverse = 1
        say reversebtn.hint
        EXIT SUB
    END IF
    IF reversebtn.Flat = 1 THEN
        reversebtn.Flat = 0
        reversebtn.Color = &Hcccccc
        chartscursormode = 0
        reverse = 0
        EXIT SUB
    END IF
END SUB

SUB flipbtnclick
    IF flipbtn.Flat = 0 THEN
        'resetbtns
        flipbtn.Flat = 1
        flipbtn.Color = &H88cc88
        chartscursormode = 1
        flip = 1
        say flipbtn.hint
        EXIT SUB
    END IF
    IF flipbtn.Flat = 1 THEN
        flipbtn.Flat = 0
        flipbtn.Color = &Hcccccc
        chartscursormode = 0
        flip = 0
        EXIT SUB
    END IF
END SUB

SUB ellipsebtnclick
    IF ellipsebtn.Flat = 0 THEN
        resetbtns
        ellipsebtn.Flat = 1
        ellipsebtn.Color = &H88cc88
        chartscursormode = 1
        say ellipsebtn.hint
        EXIT SUB
    END IF
    IF ellipsebtn.Flat = 1 THEN
        ellipsebtn.Flat = 0
        ellipsebtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB pitchforkbtnclick
    IF pitchforkbtn.Flat = 0 THEN
        resetbtns
        pitchforkbtn.Flat = 1
        pitchforkbtn.Color = &H88cc88
        chartscursormode = 1
        say pitchforkbtn.hint
        EXIT SUB
    END IF
    IF pitchforkbtn.Flat = 1 THEN
        pitchforkbtn.Flat = 0
        pitchforkbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB sq9fbtnclick
    IF sq9fbtn.Flat = 0 THEN
        resetbtns
        sq9fbtn.Flat = 1
        sq9fbtn.Color = &H88cc88
        chartscursormode = 1
        say sq9fbtn.hint
        EXIT SUB
    END IF
    IF sq9fbtn.Flat = 1 THEN
        sq9fbtn.Flat = 0
        sq9fbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB timesq9fbtnclick
    IF tsq9fbtn.Flat = 0 THEN
        resetbtns
        tsq9fbtn.Flat = 1
        tsq9fbtn.Color = &H88cc88
        chartscursormode = 1
        say tsq9fbtn.hint
        EXIT SUB
    END IF
    IF tsq9fbtn.Flat = 1 THEN
        tsq9fbtn.Flat = 0
        tsq9fbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB sq144btnclick
    IF sq144btn.Flat = 0 THEN
        resetbtns
        sq144btn.Flat = 1
        sq144btn.Color = &H88cc88
        chartscursormode = 1
        say sq144btn.hint
        EXIT SUB
    END IF
    IF sq144btn.Flat = 1 THEN
        sq144btn.Flat = 0
        sq144btn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB timesq144btnclick
    IF tsq144btn.Flat = 0 THEN
        resetbtns
        tsq144btn.Flat = 1
        tsq144btn.Color = &H88cc88
        chartscursormode = 1
        say tsq144btn.hint
        EXIT SUB
    END IF
    IF tsq144btn.Flat = 1 THEN
        tsq144btn.Flat = 0
        tsq144btn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB pricecyclesbtnclick
    IF pricecyclesbtn.Flat = 0 THEN
        resetbtns
        pricecyclesbtn.Flat = 1
        pricecyclesbtn.Color = &H88cc88
        chartscursormode = 1
        say pricecyclesbtn.hint
        EXIT SUB
    END IF
    IF pricecyclesbtn.Flat = 1 THEN
        pricecyclesbtn.Flat = 0
        pricecyclesbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB timecyclesbtnclick
    IF timecyclesbtn.Flat = 0 THEN
        resetbtns
        timecyclesbtn.Flat = 1
        timecyclesbtn.Color = &H88cc88
        chartscursormode = 1
        say timecyclesbtn.hint
        EXIT SUB
    END IF
    IF timecyclesbtn.Flat = 1 THEN
        timecyclesbtn.Flat = 0
        timecyclesbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB logspiralbtnclick
    IF logspiralbtn.Flat = 0 THEN
        resetbtns
        logspiralbtn.Flat = 1
        logspiralbtn.Color = &H88cc88
        chartscursormode = 1
        say logspiralbtn.hint
        EXIT SUB
    END IF
    IF logspiralbtn.Flat = 1 THEN
        logspiralbtn.Flat = 0
        logspiralbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB polybtnclick
    IF polybtn.Flat = 0 THEN
        resetbtns
        polybtn.Flat = 1
        polybtn.Color = &H88cc88
        chartscursormode = 1
        say polybtn.hint
        EXIT SUB
    END IF
    IF polybtn.Flat = 1 THEN
        polybtn.Flat = 0
        polybtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB pentagbtnclick
    IF pentagbtn.Flat = 0 THEN
        resetbtns
        pentagbtn.Flat = 1
        pentagbtn.Color = &H88cc88
        chartscursormode = 1
        say pentagbtn.hint
        EXIT SUB
    END IF
    IF pentagbtn.Flat = 1 THEN
        pentagbtn.Flat = 0
        pentagbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB orcyclesbtnclick
    IF orcyclesbtn.Flat = 0 THEN
        resetbtns
        orcyclesbtn.Flat = 1
        orcyclesbtn.Color = &H88cc88
        chartscursormode = 1
        say orcyclesbtn.hint
        EXIT SUB
    END IF
    IF orcyclesbtn.Flat = 1 THEN
        orcyclesbtn.Flat = 0
        orcyclesbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB polygbtnclick
    IF polygbtn.Flat = 0 THEN
        resetbtns
        polygbtn.Flat = 1
        polygbtn.Color = &H88cc88
        chartscursormode = 1
        say polygbtn.hint
        EXIT SUB
    END IF
    IF polygbtn.Flat = 1 THEN
        polygbtn.Flat = 0
        polygbtn.Color = &Hcccccc
        chartscursormode = 0
        EXIT SUB
    END IF
END SUB

SUB settingsbtnclick

    IF crossbtn.Flat = 1 THEN
        crossform.Visible = 1
        EXIT SUB
    END IF

    IF sq144btn.Flat = 1 THEN
        sq144form.Visible = 1
        EXIT SUB
    END IF

    IF sq9fbtn.Flat = 1 THEN
        sq9form.Visible = 1
        EXIT SUB
    END IF
    
    IF fibofanbtn.Flat = 1 THEN
        fibofanform.Visible = 1
        EXIT SUB
    END IF
    
    IF polygbtn.Flat = 1 THEN
        polygform.Visible = 1
        EXIT SUB
    END IF
    
    IF sinbtn.Flat = 1 THEN
        sinform.Visible = 1
        EXIT SUB
    END IF

    SHOWMESSAGE "No settings for this tool or no drawing tool selected"

END SUB

DECLARE SUB editorresize
DECLARE SUB topicclick(SENDER AS QLISTBOX)

CREATE topicsfont AS QFONT
    Size = 13
END CREATE

CREATE articlesfont AS QFONT
    Size = 13
END CREATE

CREATE editorfrm AS QFORM
    Width = 600
    Height = 600
    Center
    Caption = "Articles"
    Top = 131
    Left = 0
    CREATE articleslist AS QLISTBOX
        Left = 0
        Width = 150
        Height = editorfrm.Height - 30
        OnClick = topicclick
        Font = topicsfont
        'Articles topics list
        AddItems "Topics:"
        AddItems "Introducing Forex"
        'End Articles topics list
    END CREATE
    CREATE richedit AS QRICHEDIT
        Left = 150
        Width = editorfrm.Width - 160
        Height = editorfrm.Height - 30
        Font = articlesfont
        ReadOnly = 1
        ScrollBars = ssBoth
        Text = "Click on the topic of your choice in the list box."
    END CREATE
    OnResize = editorresize
END CREATE

CREATE MailForm AS QFORM  'Main Form
    Height = 370
    Width = 500
    Caption = "Express Mailer Version 1.01"
    Center
    CREATE Label1 AS QLABEL
        Top = 12
        Left = 5
        Caption = "SMTP Server:"
    END CREATE
    CREATE Label2 AS QLABEL
        Top = 39
        Left = 5
        Caption = "From:"
    END CREATE
    CREATE Label3 AS QLABEL
        Top = 67
        Left = 5
        Caption = "To:"
    END CREATE
    CREATE Label4 AS QLABEL
        Top = 73 + 27
        Left = 5
        Caption = "Subject:"
    END CREATE
    CREATE Edit1 AS QEDIT

        Left = 110
        Top = 10
        Width = 380
        Height = 20
        Text = "smtp.sfr.fr"
        'onchange=edit1change
    END CREATE
    CREATE Edit2 AS QEDIT

        Left = 110
        Top = 37
        Width = 380
        Height = 20
        Text = "email@server.com"
        'onchange=edit2change
    END CREATE
    CREATE Edit3 AS QEDIT

        Left = 110
        Top = 37 + 27
        Width = 380
        Height = 20
        Text = "email@server.com"
        'onchange=edit3change
    END CREATE
    CREATE Edit4 AS QEDIT

        Left = 110
        Top = 71 + 27
        Width = 380
        Height = 20
        Text = "signal"
        'onchange=edit4change
    END CREATE
    CREATE Button AS QBUTTON
        Left = 70
        Top = 250 + 27
        Height = 20
        Width = 420
        Caption = "<<< Send the e-mail... >>>"
        OnClick = ButtonClick
    END CREATE
    CREATE Status AS QLABEL
        Left = 70
        Top = 280 + 27
        Height = 20
        Width = 420
        Caption = "Please enter your e-mail."
    END CREATE
    CREATE TextBox AS QRICHEDIT
        Top = 95 + 5 + 27
        Left = 70
        Width = 420
        Height = 140
        PlainText = TRUE
        Font = TheFont
        Text = "signal"
        'onchange=edit5change
    END CREATE
    CREATE Label5 AS QLABEL
        Top = 98 + 5 + 27
        Left = 5
        Caption = "Message:"
    END CREATE
    CREATE enablemailer AS QCHECKBOX
        Caption = "Enable"
        Checked = 0
        Top = MailForm.Height - 50
        'onclick=mailersub
    END CREATE
    CREATE savemailer AS QBUTTON
        Caption = "Save changes"
        Top = MailForm.Height - 70
        'onclick=mailersub
        Left = MailForm.Width - 100
        OnClick = savemailersub
    END CREATE
    OnShow = restoremailersub
END CREATE

'sub mailersub
'if enablemailer.checked=1 then

'ini.Section="Settings"
'ini.write("mailer","1")
'exit sub
'end if
'if enablemailer.checked=0 then

'ini.Section="Settings"
'ini.write("mailer","0")
'exit sub
'end if
'end sub

SUB restoremailersub
    Edit1.Text = ini.get("smtp" , "")
    Edit2.Text = ini.get("from" , "")
    Edit3.Text = ini.get("to" , "")
    Edit4.Text = ini.get("subject" , "")
    enablemailer.Checked = VAL(ini.get("mailer" , ""))
    TextBox.Text = ini.get("message" , "")
END SUB

SUB savemailersub
    ini.Section = "Settings"
    ini.Write("smtp" , Edit1.Text)
    ini.Write("from" , Edit2.Text)
    ini.Write("to" , Edit3.Text)
    ini.Write("subject" , Edit4.Text)
    ini.Write("message" , TextBox.Text)
    IF enablemailer.Checked = 1 THEN
        ini.Write("mailer" , "1")
        EXIT SUB
    END IF
    IF enablemailer.Checked = 0 THEN
        ini.Write("mailer" , "0")
        EXIT SUB
    END IF
END SUB


'end sub

$TYPECHECK off

SUB TimerExpired  '"Main" routine
    Timer1.Enabled = FALSE
    Timer1.Interval = DELAY
    IF SockNum <= 0 THEN
        Timer1.Enabled = TRUE
        EXIT SUB
    END IF
    IF Socket.IsServerReady(SockNum) THEN
        LastLine = Socket.ReadLine(SockNum)
        IF Socket.Transferred < 0 THEN  'server dropped connection
            SockNum = 0
            'SHOWMESSAGE "Server disconnected unexpectedly!"
            Status.Caption = "Please enter your e-mail."
        END IF
        LastCode = VAL(MID$(LastLine , 1 , 3)) 'Get 3 digit error code
        IF LastCode > 400 THEN  'indicates error message
            'SHOWMESSAGE "Error: "+LastLine               ' -> abort
            Status.Caption = "Please enter your e-mail."
            Timer1.Enabled = FALSE
            Button.Caption = "<<< Send the e-mail... >>>"
            Socket.close(SockNum)
            SockNum = 0
            Timer1.Enabled = TRUE
            MailStep = 0
        END IF
        IF LastCode = 221 AND MailStep = 6 THEN  'last step completed
            'SHOWMESSAGE "Mail sent succesfully."         ' -> done
            Status.Caption = "Please enter your e-mail."
            Timer1.Enabled = FALSE
            Button.Caption = "<<< Send the e-mail... >>>"
            Socket.close(SockNum)
            SockNum = 0
            Timer1.Enabled = TRUE
            MailStep = 0
        END IF
        SELECT CASE MailStep  'Send the mail
            CASE 1  'This mail is from...
                Status.Caption = "Negotiating transfer [step 1/2]..."
                Socket.WriteLine(SockNum , "MAIL FROM:<" + Edit2.Text + ">")
                MailStep = 2
            CASE 2  'We're gonna send it to...
                Status.Caption = "Negotiating transfer [step 2/2]..."
                Socket.WriteLine(SockNum , "RCPT TO:<" + Edit3.Text + ">")
                MailStep = 3
            CASE 3  'Dear server, I'd like to give you this "letter"...
                Status.Caption = "Starting mail transfer..."
                Socket.WriteLine(SockNum , "DATA")
                MailStep = 4
            CASE 4  '... and here it goes
                Socket.WriteLine(SockNum , "From: " + Edit2.Text + " <" + Edit2.Text + ">")
                Socket.WriteLine(SockNum , "To: " + Edit3.Text)
                Socket.WriteLine(SockNum , "X-Priority: 3")
                Socket.WriteLine(SockNum , "X-MSMail-Priority: Normal")
                Socket.WriteLine(SockNum , "X-Mailer: Rapid-Q Express Mailer by DarkWulf V. 1.01")
                Socket.WriteLine(SockNum , "Reply-to: " + Edit2.Text)
                Socket.WriteLine(SockNum , "Subject: " + Edit4.Text)
                Socket.WriteLine(SockNum , "Content-Type: text/plain; charset=" + CHR$(34) + "iso-8859-1" + CHR$(34))
                Socket.WriteLine(SockNum , "Content-transfer-encoding: 8bit")
                Socket.WriteLine(SockNum , "Status:")
                FOR a = 1 TO TextBox.LineCount
                    Status.Caption = "Sending mail [" + LTRIM$(RTRIM$(STR$(INT(100 / TextBox.LineCount * a)))) + "%]..."
                    t$ = TextBox.Line(a)
                    IF MID$(t$ , 1 , 1) = "." THEN
                        t$ = "." + t$  'one single dot=end of mail
                    END IF
                    Socket.WriteLine(SockNum , t$)
                NEXT a
                Socket.WriteLine(SockNum , ".")
                MailStep = 5
            CASE 5  'Log out
                Status.Caption = "Transfer complete ... logging out..."
                Socket.WriteLine(SockNum , "QUIT")
                MailStep = 6
        END SELECT
    END IF
    Timer1.Enabled = TRUE
END SUB

$TYPECHECK on

SUB ButtonClick  'Begin to send the mail
    IF Button.Caption = "<<< SENDING MAIL >>>" THEN  'Abort it
        Status.Caption = "Please enter your e-mail."
        Timer1.Enabled = FALSE
        Button.Caption = "<<< Send the e-mail... >>>"
        Socket.close(SockNum)
        SockNum = 0
        Timer1.Enabled = TRUE
        MailStep = 0
        EXIT SUB
    END IF
    SockNum = Socket.Connect(Edit1.Text , 25) 'Connect to port 25
    MailStep = 0
    IF SockNum > 0 THEN
        Timer1.Enabled = FALSE
        Button.Caption = "<<< SENDING MAIL >>>"
        Status.Caption = "Connecting to " + Edit1.Text + "..."
        LastLine = Socket.ReadLine(SockNum)
        LastCode = VAL(MID$(LastLine , 1 , 3)) 'Get 3 digit error code
        IF LastCode > 400 THEN  'indicates error message
            'SHOWMESSAGE "Error: "+LastLine
            Status.Caption = "Please enter your e-mail."
            Timer1.Enabled = FALSE
            Button.Caption = "<<< Send the e-mail... >>>"
            Socket.close(SockNum)
            SockNum = 0
            Timer1.Enabled = TRUE
            MailStep = 0
        END IF
        MailStep = 1
        Socket.WriteLine(SockNum , "HELO localhost") 'Hello server!
        Timer1.Enabled = TRUE
    ELSE
        SockNum = 0
        'SHOWMESSAGE "Unable to connect to: "+Edit1.Text      'Couldn't connect to
        'server
    END IF
END SUB

SUB editorresize
    WITH articleslist
        .Left = 0
        .Width = 150
        .Height = editorfrm.Height - 30
    END WITH
    WITH richedit
        .Width = editorfrm.Width - 160
        .Height = editorfrm.Height - 30
    END WITH
END SUB

$include "docs\articles.doc"

SUB topicclick(SENDER AS QLISTBOX)
    SELECT CASE SENDER.Item(sender.ItemIndex)
        CASE "Topics:" :
            richedit.Text = article_topics$
        CASE "Introducing Forex" :
            richedit.Text = article_Introducing_Forex$

    END SELECT
END SUB

SUB showeditor
    editorfrm.Visible = 1
END SUB

DIM MenuItem(100) AS QMENUITEM
DIM menui AS INTEGER
menui = 1
MenuItem(menui).Caption = "Data source"
MenuItem(menui).OnClick = datasource
FileMenu.AddItems(MenuItem(menui))
menui ++
MenuItem(menui).Caption = "Login"
MenuItem(menui).OnClick = loginsub
FileMenu.AddItems(MenuItem(menui))
menui ++
MenuItem(menui).Caption = "Import CSV"
MenuItem(menui).OnClick = importcsv
FileMenu.AddItems(MenuItem(menui))
menui ++
MenuItem(menui).Caption = "Export CSV"
MenuItem(menui).OnClick = exportfile
FileMenu.AddItems(MenuItem(menui))
menui ++
MenuItem(menui).Caption = "Export collection"
MenuItem(menui).OnClick = exportcollection
FileMenu.AddItems(MenuItem(menui))
menui ++
MenuItem(menui).Caption = "Open BMP"
MenuItem(menui).OnClick = importbmp
FileMenu.AddItems(MenuItem(menui))
menui ++
MenuItem(menui).Caption = "Save BMP"
MenuItem(menui).OnClick = savebmp
FileMenu.AddItems(MenuItem(menui))
menui ++
MenuItem(menui).Caption = "Mixer"
MenuItem(menui).OnClick = mixerform
FileMenu.AddItems(MenuItem(menui))
menui ++
MenuItem(menui).Caption = "Print chart"
MenuItem(menui).OnClick = printchart
FileMenu.AddItems(MenuItem(menui))
menui ++
MenuItem(menui).Caption = "Quit"
MenuItem(menui).OnClick = quit
FileMenu.AddItems(MenuItem(menui))

DIM MenuItem4(100) AS QMENUITEM
DIM menui4 AS INTEGER
menui4 = 1
MenuItem4(menui4).Caption = "Find bar"
MenuItem4(menui4).OnClick = findbar
EditMenu.AddItems(MenuItem4(menui4))
menui4 ++
MenuItem4(menui4).Caption = "Reverse bars"
MenuItem4(menui4).OnClick = reversetillend
EditMenu.AddItems(MenuItem4(menui4))
menui4 ++
MenuItem4(menui4).Caption = "Reverse bars from file..."
MenuItem4(menui4).OnClick = reversetillendfromfile
EditMenu.AddItems(MenuItem4(menui4))
menui4 ++
MenuItem4(menui4).Caption = "Chart conversions"
MenuItem4(menui4).OnClick = chartconvsub
EditMenu.AddItems(MenuItem4(menui4))
menui4 ++
MenuItem4(menui4).Caption = "Save chart data into tmp grid"
MenuItem4(menui4).OnClick = savegridtmp
EditMenu.AddItems(MenuItem4(menui4))
menui4 ++
MenuItem4(menui4).Caption = "Attribute timeframe"
MenuItem4(menui4).OnClick = attribtf
EditMenu.AddItems(MenuItem4(menui4))
menui4 ++
MenuItem4(menui4).Caption = "Reimport file"
MenuItem4(menui4).OnClick = reimportfilesub
EditMenu.AddItems(MenuItem4(menui4))
menui4 ++
MenuItem4(menui4).Caption = "Tool settings"
MenuItem4(menui4).OnClick = settingsbtnclick
EditMenu.AddItems(MenuItem4(menui4))
menui4 ++

DIM MenuItem2(100) AS QMENUITEM
DIM menui2 AS INTEGER
menui2 = 1
MenuItem2(menui2).Caption = "Tools informations"
MenuItem2(menui2).OnClick = showtoolsinfo
WindowsMenu.AddItems(MenuItem2(menui2))
menui2 ++
MenuItem2(menui2).Caption = "Show separate canvas"
MenuItem2(menui2).OnClick = showcanvasclick
WindowsMenu.AddItems(MenuItem2(menui2))
menui2 ++
MenuItem2(menui2).Caption = "Show tools"
MenuItem2(menui2).OnClick = showtoolsclick
WindowsMenu.AddItems(MenuItem2(menui2))
menui2 ++
MenuItem2(menui2).Caption = "Objects list"
MenuItem2(menui2).OnClick = showobjectslistfrm
WindowsMenu.AddItems(MenuItem2(menui2))
menui2 ++
MenuItem2(menui2).Caption = "Reverse log"
MenuItem2(menui2).OnClick = showfrmlogreverse
WindowsMenu.AddItems(MenuItem2(menui2))
menui2 ++
MenuItem2(menui2).Caption = "Show toolbar"
MenuItem2(menui2).OnClick = showtoolbarclick
WindowsMenu.AddItems(MenuItem2(menui2))
menui2 ++
MenuItem2(menui2).Caption = "Previous tools"
MenuItem2(menui2).OnClick = previoustoolsclick
WindowsMenu.AddItems(MenuItem2(menui2))
menui2 ++
MenuItem2(menui2).Caption = "Next tools"
MenuItem2(menui2).OnClick = nexttoolsclick
WindowsMenu.AddItems(MenuItem2(menui2))

DIM MenuItem3(100) AS QMENUITEM
DIM menui3 AS INTEGER
menui3 = 1
MenuItem3(menui3).Caption = "Pen color"
MenuItem3(menui3).OnClick = choosepencolor
ToolsMenu.AddItems(MenuItem3(menui3))
menui3 ++
MenuItem3(menui3).Caption = "Text font"
MenuItem3(menui3).OnClick = choosetextfont
ToolsMenu.AddItems(MenuItem3(menui3))
menui3 ++
MenuItem3(menui3).Caption = "Articles"
MenuItem3(menui3).OnClick = showeditor
ToolsMenu.AddItems(MenuItem3(menui3))
menui3 ++
MenuItem3(menui3).Caption = "Plot area color"
MenuItem3(menui3).OnClick = chooseplotareacolor
ToolsMenu.AddItems(MenuItem3(menui3))
menui3 ++
MenuItem3(menui3).Caption = "Mailer"
MenuItem3(menui3).OnClick = choosemailer
ToolsMenu.AddItems(MenuItem3(menui3))
menui3 ++
MenuItem3(menui3).Caption = "Indicators"
MenuItem3(menui3).OnClick = indiform
ToolsMenu.AddItems(MenuItem3(menui3))
menui3 ++
MenuItem3(menui3).Caption = "Speech settings"
MenuItem3(menui3).OnClick = showspeechform
ToolsMenu.AddItems(MenuItem3(menui3))
menui3 ++
MenuItem3(menui3).Caption = "Chat"
MenuItem3(menui3).OnClick = chatformsub
ToolsMenu.AddItems(MenuItem3(menui3))
menui3 ++
MenuItem3(menui3).Caption = "Ephemeris"
MenuItem3(menui3).OnClick = swephformsub
ToolsMenu.AddItems(MenuItem3(menui3))
menui3 ++
MenuItem3(menui3).Caption = "Astro wheel settings"
MenuItem3(menui3).OnClick = astrowheelsettingssub
ToolsMenu.AddItems(MenuItem3(menui3))

DIM MenuItem5(100) AS QMENUITEM
DIM menui5 AS INTEGER
menui5 = 1
MenuItem5(menui5).Caption = "Help"
MenuItem5(menui5).OnClick = openhelpsub
AboutMenu.AddItems(MenuItem5(menui5))
menui5 ++
MenuItem5(menui5).Caption = "Readme"
MenuItem5(menui5).OnClick = viewreadme
AboutMenu.AddItems(MenuItem5(menui5))
menui5 ++
MenuItem5(menui5).Caption = "About"
MenuItem5(menui5).OnClick = about
AboutMenu.AddItems(MenuItem5(menui5))
menui5 ++
MenuItem5(menui5).Caption = "Check for updates"
MenuItem5(menui5).OnClick = updates
AboutMenu.AddItems(MenuItem5(menui5))
menui5 ++
MenuItem5(menui5).Caption = "What's new"
MenuItem5(menui5).OnClick = whatsnewsub
AboutMenu.AddItems(MenuItem5(menui5))
menui5 ++
MenuItem5(menui5).Caption = "Website"
MenuItem5(menui5).OnClick = websitesub
AboutMenu.AddItems(MenuItem5(menui5))

SUB findbar
    calendarform.Visible = 1
END SUB


SUB justrefreshchart
    IF openedfilesnb > 0 THEN
        disablescrollmode
        btnOnClick(drwBox) ' need to put this for WineHQ compatibility, else the screen does not update correctly (but this slows down computations)
    END IF
END SUB

DECLARE SUB objectslistfrmresize
DECLARE SUB delallobjdbclick
DECLARE SUB delrowobjdbclick
DECLARE SUB delallallobjdbclick

CREATE objectslistfrm AS QFORM
    Width = 400
    Height = 250
    Caption = "Objects list"
    OnResize = objectslistfrmresize
    CREATE clearallobjdbbtn AS QBUTTON
        Top = objectslistfrm.Height - 70
        Left = 0
        Caption = "Clear grid"
        OnClick = delallobjdbclick
    END CREATE
    CREATE clearrowobjdbbtn AS QBUTTON
        Top = objectslistfrm.Height - 70
        Left = 75
        Caption = "Del row"
        OnClick = delrowobjdbclick
    END CREATE
    CREATE clearallallobjdbbtn AS QBUTTON
        Top = objectslistfrm.Height - 70
        Left = 150
        Caption = "Del all objs"
        OnClick = delallallobjdbclick
    END CREATE
    CREATE updatechartbtn AS QBUTTON
        Top = objectslistfrm.Height - 70
        Left = 225
        Caption = "Update chart"
        OnClick = justrefreshchart
    END CREATE
END CREATE

DECLARE SUB objecttypecombochange

DIM objecttypecombo AS QCOMBOBOX
objecttypecombo.Parent = objectslistfrm
objecttypecombo.Width = 150
objecttypecombo.AddItems "Choose an object" , "Trendlines" , "Fibonacci fans" , "Fibonacci retracements" , "Parallel lines" , _
    "Horizontal lines" , "Vertical lines" , "Squares" , "Equilateral triangles" , "Circles" , "Crosses" , "Inverse circles" , "Texts" , "Aimings" , _
    "Sinusoids" , "Logarithmic curves" , "Exponential curves" , "Ellipses", "Pentagrams", "SQ9Fs","Squares2","Triangles2","Buy orders","Sell orders"
objecttypecombo.ItemIndex = 0
objecttypecombo.OnChange = objecttypecombochange

SUB delallallobjdbclick
    DIM delallalli AS INTEGER
    FOR delallalli = 1 TO objecttypecombo.itemcount-1
        objecttypecombo.ItemIndex = delallalli
        delallobjdbclick
    NEXT delallalli
END SUB


SUB delallobjdbclick
    DIM delalli AS INTEGER
    DIM delallj AS INTEGER
    SELECT CASE objecttypecombo.ItemIndex
        CASE 1 :
            FOR delalli = 1 TO trendlinesdb.RowCount - 1
                FOR delallj = 1 TO trendlinesdb.ColCount - 1
                    trendlinesdb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            trendlinesoffset = 0

        CASE 2 :
            FOR delalli = 1 TO fibofandb.RowCount - 1
                FOR delallj = 1 TO fibofandb.ColCount - 1
                    fibofandb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            fibofanoffset = 0

        CASE 3 :
            FOR delalli = 1 TO fiboretdb.RowCount - 1
                FOR delallj = 1 TO fiboretdb.ColCount - 1
                    fiboretdb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            fiboretoffset = 0

        CASE 4 :
            FOR delalli = 1 TO paradb.RowCount - 1
                FOR delallj = 1 TO paradb.ColCount - 1
                    paradb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            paraoffset = 0

        CASE 5 :
            FOR delalli = 1 TO hlinedb.RowCount - 1
                FOR delallj = 1 TO hlinedb.ColCount - 1
                    hlinedb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            hlineoffset = 0

        CASE 6 :
            FOR delalli = 1 TO vlinedb.RowCount - 1
                FOR delallj = 1 TO vlinedb.ColCount - 1
                    vlinedb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            vlineoffset = 0

        CASE 7 :
            FOR delalli = 1 TO sqrdb.RowCount - 1
                FOR delallj = 1 TO sqrdb.ColCount - 1
                    sqrdb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            sqroffset = 0

        CASE 8 :
            FOR delalli = 1 TO tridb.RowCount - 1
                FOR delallj = 1 TO tridb.ColCount - 1
                    tridb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            trioffset = 0

        CASE 9 :
            FOR delalli = 1 TO circledb.RowCount - 1
                FOR delallj = 1 TO circledb.ColCount - 1
                    circledb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            circleoffset = 0

        CASE 10 :
            FOR delalli = 1 TO crossdb.RowCount - 1
                FOR delallj = 1 TO crossdb.ColCount - 1
                    crossdb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            crossoffset = 0

        CASE 11 :
            FOR delalli = 1 TO invcircledb.RowCount - 1
                FOR delallj = 1 TO invcircledb.ColCount - 1
                    invcircledb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            invcircleoffset = 0

        CASE 12 :
            FOR delalli = 1 TO textdb.RowCount - 1
                FOR delallj = 1 TO textdb.ColCount - 1
                    textdb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            textoffset = 0

        CASE 13 :
            FOR delalli = 1 TO aimingdb.RowCount - 1
                FOR delallj = 1 TO aimingdb.ColCount - 1
                    aimingdb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            aimingoffset = 0

        CASE 14 :
            FOR delalli = 1 TO sindb.RowCount - 1
                FOR delallj = 1 TO sindb.ColCount - 1
                    sindb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            sinoffset = 0

        CASE 15 :
            FOR delalli = 1 TO logdb.RowCount - 1
                FOR delallj = 1 TO logdb.ColCount - 1
                    logdb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            logoffset = 0

        CASE 16 :
            FOR delalli = 1 TO expdb.RowCount - 1
                FOR delallj = 1 TO expdb.ColCount - 1
                    expdb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            expoffset = 0

        CASE 17 :
            FOR delalli = 1 TO ellipsedb.RowCount - 1
                FOR delallj = 1 TO ellipsedb.ColCount - 1
                    ellipsedb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            ellipseoffset = 0
       
        CASE 18 :
            FOR delalli = 1 TO pentagdb.RowCount - 1
                FOR delallj = 1 TO pentagdb.ColCount - 1
                    pentagdb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            pentagoffset = 0
            
        CASE 19 :
            FOR delalli = 1 TO sq9fdb.RowCount - 1
                FOR delallj = 1 TO sq9fdb.ColCount - 1
                    sq9fdb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            sq9foffset = 0    
            
        CASE 20 :
            FOR delalli = 1 TO sqr2db.RowCount - 1
                FOR delallj = 1 TO sqr2db.ColCount - 1
                    sqr2db.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            sqr2offset = 0

        CASE 21 :
            FOR delalli = 1 TO tri2db.RowCount - 1
                FOR delallj = 1 TO tri2db.ColCount - 1
                    tri2db.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli
            tri2offset = 0
            
        CASE 22 :
            FOR delalli = 1 TO orderbuydb.RowCount - 1
                FOR delallj = 1 TO orderbuydb.ColCount - 1
                    orderbuydb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli     
            
        CASE 23 :
            FOR delalli = 1 TO orderselldb.RowCount - 1
                FOR delallj = 1 TO orderselldb.ColCount - 1
                    orderselldb.Cell(delallj , delalli) = ""
                NEXT delallj
            NEXT delalli    

    END SELECT
END SUB

SUB delrowobjdbclick
    SELECT CASE objecttypecombo.ItemIndex
        CASE 1 :
            trendlinesdb.deleterow(trendlinesdb.Row)
            trendlinesoffset --
            IF trendlinesoffset < 0 THEN
                trendlinesoffset = 0
            END IF

        CASE 2 :
            fibofandb.deleterow(fibofandb.Row)
            fibofanoffset --
            IF fibofanoffset < 0 THEN
                fibofanoffset = 0
            END IF

        CASE 3 :
            fiboretdb.deleterow(fiboretdb.Row)
            fiboretoffset --
            IF fiboretoffset < 0 THEN
                fiboretoffset = 0
            END IF

        CASE 4 :
            paradb.deleterow(paradb.Row)
            paraoffset --
            IF paraoffset < 0 THEN
                paraoffset = 0
            END IF

        CASE 5 :
            hlinedb.deleterow(hlinedb.Row)
            hlineoffset --
            IF hlineoffset < 0 THEN
                hlineoffset = 0
            END IF

        CASE 6 :
            vlinedb.deleterow(vlinedb.Row)
            vlineoffset --
            IF vlineoffset < 0 THEN
                vlineoffset = 0
            END IF

        CASE 7 :
            sqrdb.deleterow(sqrdb.Row)
            sqroffset --
            IF sqroffset < 0 THEN
                sqroffset = 0
            END IF

        CASE 8 :
            tridb.deleterow(tridb.Row)
            trioffset --
            IF trioffset < 0 THEN
                trioffset = 0
            END IF

        CASE 9 :
            circledb.deleterow(circledb.Row)
            circleoffset --
            IF circleoffset < 0 THEN
                circleoffset = 0
            END IF

        CASE 10 :
            crossdb.deleterow(crossdb.Row)
            crossoffset --
            IF crossoffset < 0 THEN
                crossoffset = 0
            END IF

        CASE 11 :
            invcircledb.deleterow(invcircledb.Row)
            invcircleoffset --
            IF invcircleoffset < 0 THEN
                invcircleoffset = 0
            END IF

        CASE 12 :
            textdb.deleterow(textdb.Row)
            textoffset --
            IF textoffset < 0 THEN
                textoffset = 0
            END IF

        CASE 13 :
            aimingdb.deleterow(aimingdb.Row)
            aimingoffset --
            IF aimingoffset < 0 THEN
                aimingoffset = 0
            END IF

        CASE 14 :
            sindb.deleterow(sindb.Row)
            sinoffset --
            IF sinoffset < 0 THEN
                sinoffset = 0
            END IF

        CASE 15 :
            logdb.deleterow(logdb.Row)
            logoffset --
            IF logoffset < 0 THEN
                logoffset = 0
            END IF

        CASE 16 :
            expdb.deleterow(expdb.Row)
            expoffset --
            IF expoffset < 0 THEN
                expoffset = 0
            END IF

        CASE 17 :
            ellipsedb.deleterow(ellipsedb.Row)
            ellipseoffset --
            IF ellipseoffset < 0 THEN
                ellipseoffset = 0
            END IF
            
        CASE 18 :
            pentagdb.deleterow(pentagdb.Row)
            pentagoffset --
            IF pentagoffset < 0 THEN
                pentagoffset = 0
            END IF    
            
        CASE 19 :
            sq9fdb.deleterow(sq9fdb.Row)
            sq9foffset --
            IF sq9foffset < 0 THEN
                sq9foffset = 0
            END IF     
            
        CASE 20 :
            sqr2db.deleterow(sqr2db.Row)
            sqr2offset --
            IF sqr2offset < 0 THEN
                sqr2offset = 0
            END IF

        CASE 21 :
            tri2db.deleterow(tri2db.Row)
            tri2offset --
            IF tri2offset < 0 THEN
                tri2offset = 0
            END IF
            
        CASE 22 :
            orderbuydb.deleterow(orderbuydb.Row)
            
        CASE 23 :
            orderselldb.deleterow(orderselldb.Row)     

    END SELECT
END SUB

DECLARE SUB hideallobjectsdb

hideallobjectsdb

SUB hideallobjectsdb
    trendlinesdb.Visible = 0
    fibofandb.Visible = 0
    fiboretdb.Visible = 0
    paradb.Visible = 0
    hlinedb.Visible = 0
    vlinedb.Visible = 0
    sqrdb.Visible = 0
    tridb.Visible = 0
    sqr2db.Visible = 0
    tri2db.Visible = 0
    circledb.Visible = 0
    crossdb.Visible = 0
    invcircledb.Visible = 0
    textdb.Visible = 0
    aimingdb.Visible = 0
    sindb.Visible = 0
    logdb.Visible = 0
    expdb.Visible = 0
    ellipsedb.Visible = 0
    pentagdb.Visible = 0
    sq9fdb.visible=0
    orderbuydb.visible=0
    orderselldb.visible=0
END SUB


SUB objecttypecombochange
    SELECT CASE objecttypecombo.ItemIndex

        CASE 1 :
            hideallobjectsdb
            trendlinesdb.Visible = 1

        CASE 2 :
            hideallobjectsdb
            fibofandb.Visible = 1

        CASE 3 :
            hideallobjectsdb
            fiboretdb.Visible = 1

        CASE 4 :
            hideallobjectsdb
            paradb.Visible = 1

        CASE 5 :
            hideallobjectsdb
            hlinedb.Visible = 1

        CASE 6 :
            hideallobjectsdb
            vlinedb.Visible = 1

        CASE 7 :
            hideallobjectsdb
            sqrdb.Visible = 1

        CASE 8 :
            hideallobjectsdb
            tridb.Visible = 1

        CASE 9 :
            hideallobjectsdb
            circledb.Visible = 1

        CASE 10 :
            hideallobjectsdb
            crossdb.Visible = 1

        CASE 11 :
            hideallobjectsdb
            invcircledb.Visible = 1

        CASE 12 :
            hideallobjectsdb
            textdb.Visible = 1

        CASE 13 :
            hideallobjectsdb
            aimingdb.Visible = 1

        CASE 14 :
            hideallobjectsdb
            sindb.Visible = 1

        CASE 15 :
            hideallobjectsdb
            logdb.Visible = 1

        CASE 16 :
            hideallobjectsdb
            expdb.Visible = 1

        CASE 17 :
            hideallobjectsdb
            ellipsedb.Visible = 1
            
        CASE 18 :
            hideallobjectsdb
            pentagdb.Visible = 1   
            
        CASE 19 :
            hideallobjectsdb
            sq9fdb.Visible = 1  
            
        CASE 20 :
            hideallobjectsdb
            sqr2db.Visible = 1

        CASE 21 :
            hideallobjectsdb
            tri2db.Visible = 1   
            
        CASE 22 :
            hideallobjectsdb
            orderbuydb.Visible = 1
         
        CASE 23 :
            hideallobjectsdb
            orderselldb.Visible = 1        

    END SELECT

END SUB

trendlinesdb.Parent = objectslistfrm
trendlinesdb.Top = 50
trendlinesdb.AddOptions(goEditing , goThumbTracking ,)
trendlinesdb.Width = objectslistfrm.Width - 30
trendlinesdb.Cell(1 , 0) = "Price 1"
trendlinesdb.Cell(2 , 0) = "Price 2"
trendlinesdb.Cell(3 , 0) = "Unix time 1"
trendlinesdb.Cell(4 , 0) = "Unix time 2"
trendlinesdb.RowCount = 100

fibofandb.Parent = objectslistfrm
fibofandb.Top = 50
fibofandb.AddOptions(goEditing , goThumbTracking)
fibofandb.Width = objectslistfrm.Width - 30
fibofandb.Cell(1 , 0) = "Price 1"
fibofandb.Cell(2 , 0) = "Price 2"
fibofandb.Cell(3 , 0) = "Unix time 1"
fibofandb.Cell(4 , 0) = "Unix time 2"
fibofandb.RowCount = 100

fiboretdb.Parent = objectslistfrm
fiboretdb.Top = 50
fiboretdb.AddOptions(goEditing , goThumbTracking)
fiboretdb.Width = objectslistfrm.Width - 30
fiboretdb.Cell(1 , 0) = "Price 1"
fiboretdb.Cell(2 , 0) = "Price 2"
fiboretdb.Cell(3 , 0) = "Unix time 1"
fiboretdb.Cell(4 , 0) = "Unix time 2"
fiboretdb.RowCount = 100

paradb.Parent = objectslistfrm
paradb.Top = 50
paradb.AddOptions(goEditing , goThumbTracking)
paradb.Width = objectslistfrm.Width - 30
paradb.Cell(1 , 0) = "Price 1"
paradb.Cell(2 , 0) = "Price 2"
paradb.Cell(3 , 0) = "Price 3"
paradb.Cell(4 , 0) = "Unix time 1"
paradb.Cell(5 , 0) = "Unix time 2"
paradb.Cell(6 , 0) = "Unix time 3"
paradb.RowCount = 100
paradb.colcount=7

hlinedb.Parent = objectslistfrm
hlinedb.Top = 50
hlinedb.AddOptions(goEditing , goThumbTracking)
hlinedb.Width = objectslistfrm.Width - 30
hlinedb.Cell(1 , 0) = "Price 1"
hlinedb.Cell(2 , 0) = "Price 2"
hlinedb.Cell(3 , 0) = "Unix time 1"
hlinedb.Cell(4 , 0) = "Unix time 2"
hlinedb.RowCount = 100

vlinedb.Parent = objectslistfrm
vlinedb.Top = 50
vlinedb.AddOptions(goEditing , goThumbTracking)
vlinedb.Width = objectslistfrm.Width - 30
vlinedb.Cell(1 , 0) = "Price 1"
vlinedb.Cell(2 , 0) = "Price 2"
vlinedb.Cell(3 , 0) = "Unix time 1"
vlinedb.Cell(4 , 0) = "Unix time 2"
vlinedb.RowCount = 100

sqrdb.Parent = objectslistfrm
sqrdb.Top = 50
sqrdb.AddOptions(goEditing , goThumbTracking)
sqrdb.Width = objectslistfrm.Width - 30
sqrdb.Cell(1 , 0) = "Price 1"
sqrdb.Cell(2 , 0) = "Price 2"
sqrdb.Cell(3 , 0) = "Unix time 1"
sqrdb.Cell(4 , 0) = "Unix time 2"
sqrdb.RowCount = 100

tridb.Parent = objectslistfrm
tridb.Top = 50
tridb.AddOptions(goEditing , goThumbTracking)
tridb.Width = objectslistfrm.Width - 30
tridb.Cell(1 , 0) = "Price 1"
tridb.Cell(2 , 0) = "Price 2"
tridb.Cell(3 , 0) = "Unix time 1"
tridb.Cell(4 , 0) = "Unix time 2"
tridb.RowCount = 100

sqr2db.Parent = objectslistfrm
sqr2db.Top = 50
sqr2db.AddOptions(goEditing , goThumbTracking)
sqr2db.Width = objectslistfrm.Width - 30
sqr2db.Cell(1 , 0) = "Price 1"
sqr2db.Cell(2 , 0) = "Price 2"
sqr2db.Cell(3 , 0) = "Unix time 1"
sqr2db.Cell(4 , 0) = "Unix time 2"
sqr2db.RowCount = 100

tri2db.Parent = objectslistfrm
tri2db.Top = 50
tri2db.AddOptions(goEditing , goThumbTracking)
tri2db.Width = objectslistfrm.Width - 30
tri2db.Cell(1 , 0) = "Price 1"
tri2db.Cell(2 , 0) = "Price 2"
tri2db.Cell(3 , 0) = "Unix time 1"
tri2db.Cell(4 , 0) = "Unix time 2"
tri2db.RowCount = 100

circledb.Parent = objectslistfrm
circledb.Top = 50
circledb.AddOptions(goEditing , goThumbTracking)
circledb.Width = objectslistfrm.Width - 30
circledb.Cell(1 , 0) = "Price 1"
circledb.Cell(2 , 0) = "Price 2"
circledb.Cell(3 , 0) = "Unix time 1"
circledb.Cell(4 , 0) = "Unix time 2"
circledb.RowCount = 100

crossdb.Parent = objectslistfrm
crossdb.Top = 50
crossdb.AddOptions(goEditing , goThumbTracking)
crossdb.Width = objectslistfrm.Width - 30
crossdb.Cell(1 , 0) = "Price 1"
crossdb.Cell(2 , 0) = "Price 2"
crossdb.Cell(3 , 0) = "Unix time 1"
crossdb.Cell(4 , 0) = "Unix time 2"
crossdb.RowCount = 100

invcircledb.Parent = objectslistfrm
invcircledb.Top = 50
invcircledb.AddOptions(goEditing , goThumbTracking)
invcircledb.Width = objectslistfrm.Width - 30
invcircledb.Cell(1 , 0) = "Price 1"
invcircledb.Cell(2 , 0) = "Price 2"
invcircledb.Cell(3 , 0) = "Unix time 1"
invcircledb.Cell(4 , 0) = "Unix time 2"
invcircledb.RowCount = 100

textdb.Parent = objectslistfrm
textdb.Top = 50
textdb.AddOptions(goEditing , goThumbTracking)
textdb.Width = objectslistfrm.Width - 30
textdb.Cell(1 , 0) = "Price 1"
textdb.Cell(2 , 0) = "Price 2"
textdb.Cell(3 , 0) = "Unix time 1"
textdb.Cell(4 , 0) = "Unix time 2"
textdb.RowCount = 100

aimingdb.Parent = objectslistfrm
aimingdb.Top = 50
aimingdb.AddOptions(goEditing , goThumbTracking)
aimingdb.Width = objectslistfrm.Width - 30
aimingdb.Cell(1 , 0) = "Price 1"
aimingdb.Cell(2 , 0) = "Price 2"
aimingdb.Cell(3 , 0) = "Unix time 1"
aimingdb.Cell(4 , 0) = "Unix time 2"
aimingdb.RowCount = 100

sindb.Parent = objectslistfrm
sindb.Top = 50
sindb.AddOptions(goEditing , goThumbTracking)
sindb.Width = objectslistfrm.Width - 30
sindb.Cell(1 , 0) = "Price 1"
sindb.Cell(2 , 0) = "Price 2"
sindb.Cell(3 , 0) = "Unix time 1"
sindb.Cell(4 , 0) = "Unix time 2"
sindb.RowCount = 100

logdb.Parent = objectslistfrm
logdb.Top = 50
logdb.AddOptions(goEditing , goThumbTracking)
logdb.Width = objectslistfrm.Width - 30
logdb.Cell(1 , 0) = "Price 1"
logdb.Cell(2 , 0) = "Price 2"
logdb.Cell(3 , 0) = "Unix time 1"
logdb.Cell(4 , 0) = "Unix time 2"
logdb.RowCount = 100

expdb.Parent = objectslistfrm
expdb.Top = 50
expdb.AddOptions(goEditing , goThumbTracking)
expdb.Width = objectslistfrm.Width - 30
expdb.Cell(1 , 0) = "Price 1"
expdb.Cell(2 , 0) = "Price 2"
expdb.Cell(3 , 0) = "Unix time 1"
expdb.Cell(4 , 0) = "Unix time 2"
expdb.RowCount = 100

ellipsedb.Parent = objectslistfrm
ellipsedb.Top = 50
ellipsedb.AddOptions(goEditing , goThumbTracking)
ellipsedb.Width = objectslistfrm.Width - 30
ellipsedb.Cell(1 , 0) = "Price 1"
ellipsedb.Cell(2 , 0) = "Price 2"
ellipsedb.Cell(3 , 0) = "Unix time 1"
ellipsedb.Cell(4 , 0) = "Unix time 2"
ellipsedb.RowCount = 100

pentagdb.Parent = objectslistfrm
pentagdb.Top = 50
pentagdb.AddOptions(goEditing , goThumbTracking)
pentagdb.Width = objectslistfrm.Width - 30
pentagdb.Cell(1 , 0) = "Price 1"
pentagdb.Cell(2 , 0) = "Price 2"
pentagdb.Cell(3 , 0) = "Unix time 1"
pentagdb.Cell(4 , 0) = "Unix time 2"
pentagdb.RowCount = 100

sq9fdb.Parent = objectslistfrm
sq9fdb.Top = 50
sq9fdb.AddOptions(goEditing , goThumbTracking)
sq9fdb.Width = objectslistfrm.Width - 30
sq9fdb.Cell(1 , 0) = "Price 1"
sq9fdb.Cell(2 , 0) = "Price 2"
sq9fdb.Cell(3 , 0) = "Unix time 1"
sq9fdb.Cell(4 , 0) = "Unix time 2"
sq9fdb.RowCount = 100

orderbuydb.Parent = objectslistfrm
orderbuydb.Top = 50
orderbuydb.AddOptions(goEditing , goThumbTracking ,)
orderbuydb.Width = objectslistfrm.Width - 30
orderbuydb.Cell(1 , 0) = "Price 1"
orderbuydb.Cell(2 , 0) = ""
orderbuydb.Cell(3 , 0) = "Unix time 1"
orderbuydb.Cell(4 , 0) = ""
orderbuydb.RowCount = 100

orderselldb.Parent = objectslistfrm
orderselldb.Top = 50
orderselldb.AddOptions(goEditing , goThumbTracking ,)
orderselldb.Width = objectslistfrm.Width - 30
orderselldb.Cell(1 , 0) = "Price 1"
orderselldb.Cell(2 , 0) = ""
orderselldb.Cell(3 , 0) = "Unix time 1"
orderselldb.Cell(4 , 0) = ""
orderselldb.RowCount = 100

SUB objectslistfrmresize

END SUB

SUB showobjectslistfrm
    objectslistfrm.Visible = 1
END SUB


CREATE Form2 AS QFORM
    Width = 180
    Height = 310
    Center
    Caption = "Parameters"
    CREATE form2Label1 AS QLABEL
        Left = 10
        Top = 10
        Width = 95
        Transparent = 1
        Caption = "Date position:"
    END CREATE
    CREATE form2Edit1 AS QEDIT
        Left = form2Label1.Width + 10
        Top = 10
        Width = 20
        Text = "1"
    END CREATE
    CREATE form2Label2 AS QLABEL
        Left = 10
        Top = form2Label1.Top + 30
        Width = 95
        Transparent = 1
        Caption = "Time position:"
    END CREATE
    CREATE form2Edit2 AS QEDIT
        Left = form2Label2.Width + 10
        Top = form2Label1.Top + 30
        Width = 20
        Text = "2"
    END CREATE
    CREATE form2Label3 AS QLABEL
        Left = 10
        Top = form2Label2.Top + 30
        Width = 95
        Transparent = 1
        Caption = "Open position:"
    END CREATE
    CREATE form2Edit3 AS QEDIT
        Left = form2Label3.Width + 10
        Top = form2Label2.Top + 30
        Width = 20
        Text = "3"
    END CREATE
    CREATE form2Label4 AS QLABEL
        Left = 10
        Top = form2Label3.Top + 30
        Width = 95
        Transparent = 1
        Caption = "High position:"
    END CREATE
    CREATE form2Edit4 AS QEDIT
        Left = form2Label4.Width + 10
        Top = form2Label3.Top + 30
        Width = 20
        Text = "4"
    END CREATE
    CREATE form2Label5 AS QLABEL
        Left = 10
        Top = form2Label4.Top + 30
        Width = 95
        Transparent = 1
        Caption = "Low position:"
    END CREATE
    CREATE form2Edit5 AS QEDIT
        Left = form2Label5.Width + 10
        Top = form2Label4.Top + 30
        Width = 20
        Text = "5"
    END CREATE
    CREATE form2Label6 AS QLABEL
        Left = 10
        Top = form2Label5.Top + 30
        Width = 95
        Transparent = 1
        Caption = "Close position:"
    END CREATE
    CREATE form2Edit6 AS QEDIT
        Left = form2Label6.Width + 10
        Top = form2Label5.Top + 30
        Width = 20
        Text = "6"
    END CREATE
    CREATE form2Label7 AS QLABEL
        Left = 10
        Top = form2Label6.Top + 30
        Width = 95
        Transparent = 1
        Caption = "Volume position:"
    END CREATE
    CREATE form2Edit7 AS QEDIT
        Left = form2Label7.Width + 10
        Top = form2Label6.Top + 30
        Width = 20
        Text = "7"
    END CREATE
    CREATE form2Label8 AS QLABEL
        Left = 10
        Top = form2Label7.Top + 30
        Width = 95
        Transparent = 1
        Caption = "Separator character:"
    END CREATE
    CREATE form2Edit8 AS QEDIT
        Left = form2Label8.Width + 10
        Top = form2Label7.Top + 30
        Width = 20
        Text = ","
    END CREATE
    CREATE Buttonparam AS QBUTTON
        Left = 10
        Top = form2Label8.Top + 30

        Caption = "Open file"
        OnClick = Buttonf2Click
    END CREATE

    Visible = 0

END CREATE

CREATE filesettingsfrm AS QFORM
    Height = 300
    CREATE MTpathbtn AS QBUTTON
        Caption = "Choose CSV path"
        Width = 100
        OnClick = mtpathform
        ShowHint = 1
    END CREATE
    CREATE mtpathedit AS QEDIT
        Top = 30
        Width = 300
        Text = "CSV path not defined yet"
    END CREATE
    CREATE pausesdurationlab AS QLABEL
        Caption = "Pauses duration:"
        Top = 60
    END CREATE
    CREATE pausesdurationedit AS QEDIT
        Text = "2"
        Top = 60
        Left = 100
    END CREATE
    CREATE barsbefonorndlab AS QLABEL
        Caption = "Bars before not rnd:"
        Top = 90
    END CREATE
    CREATE barsbefonorndedit AS QEDIT
        Text = "70"
        Top = 90
        Left = 100
    END CREATE
    CREATE nbtfmultslab AS QLABEL
        Caption = "Nb of tfmults to play:"
        Top = 120
    END CREATE
    CREATE nbtfmultsedit AS QEDIT
        Text = "5"
        Top = 120
        Left = 100
    END CREATE
    CREATE bolliperlab AS QLABEL
        Caption = "Bolli period:"
        Top = 150
    END CREATE
    CREATE bolliperedit AS QEDIT
        Text = "120"
        Top = 150
        Left = 100
    END CREATE

    Visible = 0
    CREATE MTpathexitbtn AS QBUTTON
        Caption = "Choose CSV file for exit signal"
        Width = 200
        Top = 200
        OnClick = mtpathexitform
        ShowHint = 1
    END CREATE
    CREATE mtpathexitedit AS QEDIT
        Top = 220
        Width = 300
        Text = "CSV file for exit signal not defined yet"
    END CREATE
    CREATE fsfrmok AS QBUTTON
        Top = 240
        Caption = "OK"
        OnClick = filesettingsfrmokclicked
    END CREATE
END CREATE

SUB filesettings
    filesettingsfrm.Visible = 1
END SUB

create symbolslistform as qform
caption="Symbols list"
center
height=360
width=360
visible=0
onshow=loadsymbolslistsub

create markettypecombo as qcombobox
left=10
top=10
width=200
additems "AMEX"
additems "COMMODITIES_ENERGY"
additems "COMMODITIES_GRAINS"
additems "COMMODITIES_METALS"
additems "COMMODITIES_SOFTS"
additems "CURRENCIES"
additems "CURRENCY_FUTURES"
additems "CURRENCY_INDICES"
additems "DAX_stocks"
additems "dji_stocks"
additems "German_stocks"
additems "Hungarian_stocks"
additems "INDICES_ASIA"
additems "INDICES_EUROPE"
additems "INDICES_AMERICA"
additems "INDICES_FUTURES_AMERICA"
additems "INDICES_FUTURES_ASIA"
additems "INDICES_FUTURES_EUROPE"
additems "INDICES_OTHERS"
additems "Japan_ETFs_stocks"
additems "Japan_stocks"
additems "MDAX_stocks"
additems "NASDAQ"
additems "nasdaq_stocks"
additems "Nasdaq100_stocks"
additems "Nikkei225_stocks"
additems "nyse_mkt_stocks"
additems "nyse_stocks"
additems "Polish_stocks"
additems "sp500_stocks"
additems "TOPIX30_stocks"
additems "UK_ETFs_stocks"
additems "UK_stocks"
additems "UK100_stocks"
additems "US_ETFs_stocks"
additems "us_stocks"
additems "WIG30_stocks"
itemindex=0
onchange=markettypecombochangesub
end create

create reloadsymbolslistbtn as qbutton
left=markettypecombo.left+markettypecombo.width+10
top=10
height=20
caption="Reload list"
onclick=reloadsymbolslistbtnsub
end create

create symbolslistbox as qlistbox

top=30
left=10
height=200
width=300
onclick=symbolslistboxonclicksub
ondblclick=symbolslistboxondblclicksub

end create

create selectsymbolslistbtn as qbutton
top=symbolslistbox.top+symbolslistbox.height+10
left=10
caption="Select symbol"
onclick=selectsymbolslistbtnsub
end create

create loadsymbolslistbtn as qbutton
top=symbolslistbox.top+symbolslistbox.height+10
left=selectsymbolslistbtn.left+selectsymbolslistbtn.width+10
width=230
caption="Load symbol with current data source settings"
onclick=loadsymbolslistbtnsub
end create

create searchsymbolslistlabel as qlabel
top=selectsymbolslistbtn.top+selectsymbolslistbtn.height+10
left=10
caption="Find:"
end create

create searchsymbolslistedit as qedit
top=searchsymbolslistlabel.top
left=50
end create

create searchsymbolslistbtn as qbutton
top=searchsymbolslistedit.top
left=180
caption="FIND"
onclick=searchsymbolslistbtnsub
end create

create searchnextsymbolslistbtn as qbutton
top=searchsymbolslistedit.top
left=260
caption="FIND NEXT"
onclick=searchnextsymbolslistbtnsub
end create

create updatesymbolslistbtn as qbutton
top=searchnextsymbolslistbtn.top+30
left=10
width=100
caption="Update symbols list"
onclick=updatesymbolslistbtnsub
end create

create restoredefaultdatabtn as qbutton
top=updatesymbolslistbtn.top
left=updatesymbolslistbtn.left+updatesymbolslistbtn.width+10
width=100
caption="Restore default data"
onclick=restoredefaultdatabtnsub
end create

end create

CREATE datasourcefrm AS QFORM
    Caption = "Data source"
    Height = 250
    Width = 300
    CREATE dssourcelbl AS QLABEL
        Caption = "Source:"
    END CREATE
    CREATE dssource AS QCOMBOBOX
        Left = 50
        AddItems "Yahoo! Finance Internet"
        AddItems "Stooq"
        AddItems "Google Finance"
        ItemIndex = 0
    END CREATE
    CREATE dssymbol AS QLABEL
        Top = 20
        Caption = "Symbol:"
    END CREATE
    CREATE dssymboledit AS QEDIT
        Top = 20
        Left = 50
        Text = "YHOO"
    END CREATE
    create dssymbollistshow as qbutton
        top=20
        left=180
        caption="Symbols list"
        onclick=showsymbolslist
    end create   
    CREATE dsstartdate AS QLABEL
        Top = 40
        Caption = "Start date:"
    END CREATE
    CREATE dsstartcalendarobj AS QEDIT
        Top = 40
        Left = 50
        Text = "03-01-1793"
    END CREATE
    CREATE dsenddate AS QLABEL
        Top = 60
        Caption = "End date:"
    END CREATE
    CREATE dsendcalendarobj AS QEDIT
        Top = 60
        Left = 50
        Text = DATE$
    END CREATE
    CREATE dstimeframelbl AS QLABEL
        Top = 80
        Caption = "Timeframe:"
    END CREATE
    CREATE dstimeframe AS QCOMBOBOX
        Top = 80
        Left = 50
        additems "1M"
        additems "5M"
        additems "15M"
        additems "30M"
        additems "60M"
        additems "240M"        
        AddItems "Daily"
        AddItems "Weekly"
        AddItems "Monthly"
        ItemIndex = 6
    END CREATE
    create googledaysbacklabel as qlabel
    top=110
    caption="Days back:"
    end create
    create googledaysbackedit as qedit
    top=110
    left=100
    text="30"
    width=50
    end create
    create googlerealtimecheckbox as qcheckbox
    top=110
    left=150
    caption="Realtime"
    width=120
    end create
    create googlerefreshratelabel as qlabel
    top=130
    caption="Refresh rate (in ms):"
    end create
    create googlerefreshrateedit as qedit
    top=130
    left=100
    text="5000"
    width=50    
    onchange=googlerefreshrateeditchangesub
    end create
    CREATE dsok AS QBUTTON
        Top = 150
        Caption = "Get chart"
        OnClick = dsokclick
    END CREATE
    CREATE dsinfolbl AS QLABEL
        Top = 180
        Caption = "For the full list of symbols, please visit:" + CHR$(10) + "http://eoddata.com/symbols.aspx"
    END CREATE
END CREATE

SUB datasource
    datasourcefrm.Visible = 1
    setfocus(datasourcefrm.handle)
END SUB

SUB dsokclick
    useindiCheckedtmp=0
    if useindi.Checked=1 then useindiCheckedtmp=1
    useindi.Checked = 0
    'InetIsOffline returns 0 if you're connected
    DEFINT A

    A = InetIsOffLine(0)
    IF A = 0 THEN
        'Print "Connected To Internet"
    ELSE
        'Print "Not Connected to Internet"
        SHOWMESSAGE "No internet connection"
        EXIT SUB
    END IF
    dsok.Enabled = 0
    DIM dsstartcalendarobjm AS STRING , dsstartcalendarobjd AS STRING , dsstartcalendarobjy AS STRING , dsendcalendarobjm AS STRING , dsendcalendarobjd AS STRING , dsendcalendarobjy AS STRING
    dsstartcalendarobjd = MID$(dsstartcalendarobj.Text , 4 , 2)
    dsstartcalendarobjm = MID$(dsstartcalendarobj.Text , 1 , 2)
    dsstartcalendarobjy = MID$(dsstartcalendarobj.Text , 7 , 4)
    dsendcalendarobjd = MID$(dsendcalendarobj.Text , 4 , 2)
    dsendcalendarobjm = MID$(dsendcalendarobj.Text , 1 , 2)
    dsendcalendarobjy = MID$(dsendcalendarobj.Text , 7 , 4)

    DEFSTR url
    IF dssource.ItemIndex = 0 THEN url = "http://ichart.finance.yahoo.com/table.csv?s=" + UCASE$(dssymboledit.Text) + "&a=" + dsstartcalendarobjm + "&b=" + dsstartcalendarobjd + "&c=" + dsstartcalendarobjy + "&d=" + dsendcalendarobjm + "&e=" + dsendcalendarobjd + "&f=" + dsendcalendarobjy + "&g=" + LCASE$(LEFT$(dstimeframe.Item(dstimeframe.ItemIndex) , 1)) + "&ignore=.csv"
    IF dssource.ItemIndex = 1 THEN url = "http://stooq.com/q/d/l/?s=" + LCASE$(dssymboledit.Text) + "&d1=" + dsstartcalendarobjy + dsstartcalendarobjm + dsstartcalendarobjd + "&d2=" + dsendcalendarobjy + dsendcalendarobjm + dsendcalendarobjd + "&i=" + LCASE$(LEFT$(dstimeframe.Item(dstimeframe.ItemIndex) , 1))
    IF dssource.ItemIndex = 2 THEN
        googlegetquotesub
        EXIT SUB
    END IF
    IF dssource.ItemIndex = 0 AND googlerealtimecheckbox.Checked = 1 THEN
        googlegetquotesub
        EXIT SUB
    END IF

    DIM dstf AS STRING
    SELECT CASE dstimeframe.ItemIndex
        CASE 0  :
            SHOWMESSAGE "Intraday timeframes are only available for Google Finance"
            dsok.Enabled = 1
            EXIT SUB
        CASE 1  :
            SHOWMESSAGE "Intraday timeframes are only available for Google Finance"
            dsok.Enabled = 1
            EXIT SUB
        CASE 2  :
            SHOWMESSAGE "Intraday timeframes are only available for Google Finance"
            dsok.Enabled = 1
            EXIT SUB
        CASE 3  :
            SHOWMESSAGE "Intraday timeframes are only available for Google Finance"
            dsok.Enabled = 1
            EXIT SUB
        CASE 4  :
            SHOWMESSAGE "Intraday timeframes are only available for Google Finance"
            dsok.Enabled = 1
            EXIT SUB
        CASE 5  :
            SHOWMESSAGE "Intraday timeframes are only available for Google Finance"
            dsok.Enabled = 1
            EXIT SUB
        CASE 6  :
            dstf = "1440"
        CASE 7  :
            dstf = "10080"
        CASE 8  :
            dstf = "43200"
    END SELECT

    DEFSTR outFileName = UCASE$(dssymboledit.Text) + dstf + ".tmp"

    CHDIR homepath + "\csv"
    
    getcharttimer.enabled=1
    IF GetFileHTTP(url , outFileName) THEN
        SHOWMESSAGE "Download Error : " & url
        dsok.Enabled = 1
        EXIT SUB
    ELSE
        'PRINT "Download Finished & OK : " & URL
        'showmessage "Download Finished & OK : " & URL
        DIM filestream AS QFILESTREAM
        DEFSTR filecontentstr = ""
        filestream.Open(outFileName , 0)
        WHILE NOT filestream.eof
            filecontentstr = filecontentstr + filestream.ReadLine
        WEND
        IF VAL(barsdisplayed.Text) > filestream.LineCount - 1 AND LEN(filecontentstr) > 7 THEN barsdisplayed.Text = STR$(filestream.LineCount - 1)
        filestream.Close
        IF LEN(filecontentstr) < 8 THEN
            SHOWMESSAGE "Invalid symbol"
            dsok.Enabled = 1
            EXIT SUB
        END IF
        IF VAL(barsdisplayed.Text) < 1 THEN barsdisplayed.Text = "1"
        IF dssource.ItemIndex = 0 AND googlerealtimecheckbox.Checked = 0 THEN importfileyahoo()
        IF dssource.ItemIndex = 1 THEN
            IF googlerealtimecheckbox.Checked = 1 THEN
                SHOWMESSAGE "There is no real time mode for Stooq data"
                googlerealtimecheckbox.Checked = 0
            END IF
            importfilestooq()
        END IF
    END IF

END SUB



'An form, that displais contents of folders and
'has special icons for image-files.

CREATE dirtreeform AS QFORM
    Height = 300
    Width = 450
    Center
    CREATE DirList AS QFILELISTBOX  'Can double as a Directory list box
        ShowIcons = TRUE
        Mask = "*.*"
        AddFileTypes(ftDirectory) 'Add Directories
        DelFileTypes(ftNormal) 'Remove files (see RAPIDQ.INC for values)
        OnDblClick = ChangeDirectories
        Height = dirtreeform.ClientHeight - 50
        Width = 200
    END CREATE
    CREATE csvList AS QFILELISTBOX
        ShowIcons = TRUE
        Mask = "*.csv"
        'OnDblClick = ExecuteApplication
        Left = 215
        Height = dirtreeform.ClientHeight - 50
        Width = 225
        OnClick = choosefile
    END CREATE
    CREATE dirdrivelab AS QLABEL
        Top = dirtreeform.ClientHeight - 50
        Caption = "Drive letter:"
    END CREATE
    CREATE dirdriveedit AS QEDIT
        Top = dirtreeform.ClientHeight - 50
        Left = 100
        Text = "C"
    END CREATE
    CREATE dirdrivebtn AS QBUTTON
        Top = dirtreeform.ClientHeight - 50
        Left = 150
        Caption = "OK"
        OnClick = dirdrivebtnclicked
    END CREATE
    Visible = 0
    Center
    Caption = DirList.Directory
    'OnResize = ResizeForm
END CREATE

SUB dirdrivebtnclicked
    DirList.Drive = dirdriveedit.Text
    DirList.update
END SUB

SUB filesettingsfrmokclicked
    ini.Section = "Settings"
    ini.Write("csvpath" , mtpathedit.Text)
    ini.Write("csvpathexit" , mtpathexitedit.Text)
    filesettingsfrm.Visible = 0
END SUB

SUB edit1change
    ini.Section = "Settings"
    ini.Write("smtp" , Edit1.Text)
END SUB

SUB edit2change
    ini.Section = "Settings"
    ini.Write("from" , Edit2.Text)
END SUB

SUB edit3change
    ini.Section = "Settings"
    ini.Write("to" , Edit3.Text)
END SUB

SUB edit4change
    ini.Section = "Settings"
    ini.Write("subject" , Edit4.Text)
END SUB

SUB edit5change
    ini.Section = "Settings"
    ini.Write("message" , TextBox.Text)
END SUB


'------------------------------------------------------


SUB ChangeDirectories
    CHDIR(DirList.Item(DirList.ItemIndex) - "[" - "]")
    DirList.Directory = CurDir$  :  csvList.Directory = CurDir$
    dirtreeform.Caption = CurDir$
    mtpathedit.Text = DirList.Directory
END SUB

SUB choosefile
    mtpathexitedit.Text = csvList.Item(csvList.ItemIndex)
END SUB

SUB mtpathform
    dirtreeform.Visible = 1
END SUB

SUB mtpathexitform
    dirtreeform.Visible = 1
END SUB

'Restoring last settings from ini file
IF ini.exist THEN
    ini.Section = "Settings"
    IF ini.get("csvpath" , "") <> "" THEN
        IF DIREXISTS(ini.get("csvpath" , "")) THEN
            DirList.Directory = ini.get("csvpath" , "")  :  csvList.Directory = ini.get("csvpath" , "")
            dirtreeform.Caption = CurDir$
            mtpathedit.Text = DirList.Directory
        END IF
    END IF
    IF ini.get("csvpathexit" , "") <> "" THEN
        'if direxists(ini.get("csvpath","")) then
        'DirList.Directory = ini.get("csvpath","") : csvList.Directory = ini.get("csvpath","")
        FOR i = 0 TO csvList.ItemCount - 1
            IF csvList.Item(i) = ini.get("csvpathexit" , "") THEN
                csvList.ItemIndex = i
                EXIT FOR
            END IF
        NEXT i
        'dirtreeform.Caption = CurDir$
        'mtpathedit.text=DirList.Directory
        'end if
        mtpathexitedit.Text = ini.get("csvpathexit" , "")
    END IF
    IF ini.get("barsdisplayed" , "") <> "" THEN barsdisplayed.Text = ini.get("barsdisplayed" , "")
    IF ini.get("countedbars" , "") <> "" THEN cntbarsedit.Text = ini.get("countedbars" , "")
    IF VAL(ini.get("automation" , "")) > 0 THEN beginauto
    IF VAL(ini.get("exitsignal" , "")) > 0 THEN beginexitsignal
END IF

SUB importcsv
    Form2.Visible = 1
    Form2.WindowState = 0
    SetFocus(Form2.Handle)
END SUB

SUB importbmp

    DIM OpenDialog AS QOPENDIALOG
    IF OpenDialog.Execute THEN
        openedfilesnb ++
        openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(openedfilesnbplusone())
        importedfile(openedfilesnb) = OpenDialog.FileName
        displayedfile = openedfilesnb
        displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setdisplayedfile(varptr(displayedfilestr)))
        mixgrid.Cell(0 , displayedfile) = importedfile(displayedfile)
        mixgridcolcount(displayedfile) = 1
        mixgridcolcount2(displayedfile) = 0
        mixgridcolcount3(displayedfile) = 0
        mixgridcolcount4(displayedfile) = 0
        IF openedfilesnb > 1 THEN
            rowgridoffset = 7 * (openedfilesnb - 1)
            rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
        END IF
        dispchartnb.AddItems STR$(displayedfile)
        dispchartnb.ItemIndex = openedfilesnb - 1
    END IF
    IF FILEEXISTS(OpenDialog.FileName) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF
    'Dim file as Qfilestream
    'file.open(OpenDialog.FileName, 0)
    WITH Graph
        .buffer.LoadFromFile(OpenDialog.FileName)
        'ImgMemory.pixelformat=pf24bit
        '.width=.buffer.width
        '.height=.buffer.height
    END WITH
    'file.close


    scrollchartpositionwait = 0

    scrollchartpositionwait = 1

    updatemixerlists
    'bgimg.visible=0
    Graph.Visible = 1
    split.Visible = 0
    splith.Visible = 0
    closedispchart.Visible = 1
    'Scrollchart.visible=1
    WITH Graph
        .firstbufcntreset
        .savebuffertmp
        .paintchart
    END WITH

END SUB

'sub sepindizoommoreclick()
'sepindizoom=sepindizoom-0.1
'btnOnClick(drwBox)
'end sub

'sub sepindizoomlessclick()
'sepindizoom=sepindizoom+0.1
'btnOnClick(drwBox)
'end sub

SUB tfmultp_click()
    tfmult.Text = STR$(VAL(tfmult.Text) + 1)
    tfmultok_click()
END SUB

SUB tfmultm_click()
    tfmult.Text = STR$(VAL(tfmult.Text) - 1)
    IF tfmult.Text = "0" THEN
        tfmult.Text = "1"
    END IF
    tfmultok_click()
END SUB

SUB refreshgrids
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    DIM i AS INTEGER
    chartbars(displayedfile) = chartbarstmp(displayedfile)
    'chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))
    'dim j as integer
    'dim high as double
    'dim low as double
    'dim vol as integer
    'dim lines as integer
    'lines=1
    FOR i = 1 TO chartbars(displayedfile)
        Grid.Cell(rowgridoffset + 1 , i) = Gridtmp.Cell(rowgridoffset + 1 , i)
        Grid.Cell(rowgridoffset + 2 , i) = Gridtmp.Cell(rowgridoffset + 2 , i)
        Grid.Cell(rowgridoffset + 3 , i) = Gridtmp.Cell(rowgridoffset + 3 , i)
        Grid.Cell(rowgridoffset + 4 , i) = Gridtmp.Cell(rowgridoffset + 4 , i)
        Grid.Cell(rowgridoffset + 5 , i) = Gridtmp.Cell(rowgridoffset + 5 , i)
        Grid.Cell(rowgridoffset + 6 , i) = Gridtmp.Cell(rowgridoffset + 6 , i)
        Grid.Cell(rowgridoffset + 7 , i) = Gridtmp.Cell(rowgridoffset + 7 , i)
 writealive
    NEXT i


    'chartbars(displayedfile)=lines-1
    'print chartbars(displayedfile)
    'Scrollchart.Max=chartbars(displayedfile)
    'Scrollchart.Position=chartbars(displayedfile)
    'chartstart=Scrollchart.Position-numbars
    'btnOnClick(drwBox)
    justrefreshchart
END SUB

sub refreshgrids2

' -------------- This code replaces refreshgrids sub ----------------------------------
    displayedfilestr=str$(displayedfile):chartbars(displayedfile) = val(varptr$(getchartbars(varptr(displayedfilestr))))    

    defstr istr
    FOR i = 1 TO chartbars(displayedfile)
        istr=str$(i)
        rowgridoffsetstr=str$(rowgridoffset + 1):Grid.Cell(rowgridoffset + 1 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
        rowgridoffsetstr=str$(rowgridoffset + 2):Grid.Cell(rowgridoffset + 2 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
        rowgridoffsetstr=str$(rowgridoffset + 3):Grid.Cell(rowgridoffset + 3 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
        rowgridoffsetstr=str$(rowgridoffset + 4):Grid.Cell(rowgridoffset + 4 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
        rowgridoffsetstr=str$(rowgridoffset + 5):Grid.Cell(rowgridoffset + 5 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
        rowgridoffsetstr=str$(rowgridoffset + 6):Grid.Cell(rowgridoffset + 6 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
        rowgridoffsetstr=str$(rowgridoffset + 7):Grid.Cell(rowgridoffset + 7 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
        Gridtmp.Cell(rowgridoffset + 1 , i) = Grid.Cell(rowgridoffset + 1 , i)
        Gridtmp.Cell(rowgridoffset + 2 , i) = Grid.Cell(rowgridoffset + 2 , i)
        Gridtmp.Cell(rowgridoffset + 3 , i) = Grid.Cell(rowgridoffset + 3 , i)
        Gridtmp.Cell(rowgridoffset + 4 , i) = Grid.Cell(rowgridoffset + 4 , i)
        Gridtmp.Cell(rowgridoffset + 5 , i) = Grid.Cell(rowgridoffset + 5 , i)
        Gridtmp.Cell(rowgridoffset + 6 , i) = Grid.Cell(rowgridoffset + 6 , i)
        Gridtmp.Cell(rowgridoffset + 7 , i) = Grid.Cell(rowgridoffset + 7 , i)
 'writealive
    NEXT i
    
writealive
    justrefreshchart
' -------------- End of this code replaces refreshgrids sub -------------------------------  

end sub

SUB refreshgridsnorefresh
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    DIM i AS INTEGER
    chartbars(displayedfile) = chartbarstmp(displayedfile)
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))
    'dim j as integer
    'dim high as double
    'dim low as double
    'dim vol as integer
    'dim lines as integer
    'lines=1
    FOR i = 1 TO chartbars(displayedfile)
        Grid.Cell(rowgridoffset + 1 , i) = Gridtmp.Cell(rowgridoffset + 1 , i)
        Grid.Cell(rowgridoffset + 2 , i) = Gridtmp.Cell(rowgridoffset + 2 , i)
        Grid.Cell(rowgridoffset + 3 , i) = Gridtmp.Cell(rowgridoffset + 3 , i)
        Grid.Cell(rowgridoffset + 4 , i) = Gridtmp.Cell(rowgridoffset + 4 , i)
        Grid.Cell(rowgridoffset + 5 , i) = Gridtmp.Cell(rowgridoffset + 5 , i)
        Grid.Cell(rowgridoffset + 6 , i) = Gridtmp.Cell(rowgridoffset + 6 , i)
        Grid.Cell(rowgridoffset + 7 , i) = Gridtmp.Cell(rowgridoffset + 7 , i)
    NEXT i


    'chartbars(displayedfile)=lines-1
    'print chartbars(displayedfile)
    'Scrollchart.Max=chartbars(displayedfile)
    'Scrollchart.Position=chartbars(displayedfile)
    'chartstart=Scrollchart.Position-numbars
    'btnOnClick(drwBox)
    justrefreshchart
END SUB


SUB savegridtmp
    DIM i AS INTEGER
    FOR i = 1 TO chartbars(displayedfile)
        Gridtmp.Cell(rowgridoffset + 1 , i) = Grid.Cell(rowgridoffset + 1 , i)
        Gridtmp.Cell(rowgridoffset + 2 , i) = Grid.Cell(rowgridoffset + 2 , i)
        Gridtmp.Cell(rowgridoffset + 3 , i) = Grid.Cell(rowgridoffset + 3 , i)
        Gridtmp.Cell(rowgridoffset + 4 , i) = Grid.Cell(rowgridoffset + 4 , i)
        Gridtmp.Cell(rowgridoffset + 5 , i) = Grid.Cell(rowgridoffset + 5 , i)
        Gridtmp.Cell(rowgridoffset + 6 , i) = Grid.Cell(rowgridoffset + 6 , i)
        Gridtmp.Cell(rowgridoffset + 7 , i) = Grid.Cell(rowgridoffset + 7 , i)
    NEXT i
END SUB

SUB tfmultok_click()
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF

    DIM i AS INTEGER
    DIM j AS INTEGER
    DIM high AS DOUBLE
    DIM low AS DOUBLE
    DIM vol AS INTEGER
    DIM lines AS INTEGER
    lines = 1
    chartbars(displayedfile) = chartbarstmp(displayedfile)
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))
    FOR i = 1 TO chartbars(displayedfile)
        Grid.Cell(rowgridoffset + 1 , i) = Gridtmp.Cell(rowgridoffset + 1 , i)
        Grid.Cell(rowgridoffset + 2 , i) = Gridtmp.Cell(rowgridoffset + 2 , i)
        Grid.Cell(rowgridoffset + 3 , i) = Gridtmp.Cell(rowgridoffset + 3 , i)
        Grid.Cell(rowgridoffset + 4 , i) = Gridtmp.Cell(rowgridoffset + 4 , i)
        Grid.Cell(rowgridoffset + 5 , i) = Gridtmp.Cell(rowgridoffset + 5 , i)
        Grid.Cell(rowgridoffset + 6 , i) = Gridtmp.Cell(rowgridoffset + 6 , i)
        Grid.Cell(rowgridoffset + 7 , i) = Gridtmp.Cell(rowgridoffset + 7 , i)
    NEXT i
    FOR j = 1 TO chartbars(displayedfile) STEP VAL(tfmult.Text)
        IF j <= chartbars(displayedfile) - VAL(tfmult.Text) + 1 THEN
            high = VAL(Grid.Cell(rowgridoffset + 4 , j))
            low = VAL(Grid.Cell(rowgridoffset + 5 , j))
            vol = 0
            FOR i = 1 TO VAL(tfmult.Text)
                IF VAL(Grid.Cell(rowgridoffset + 4 , j + i - 1)) > high THEN
                    high = VAL(Grid.Cell(rowgridoffset + 4 , j + i - 1))
                END IF
                IF VAL(Grid.Cell(rowgridoffset + 5 , j + i - 1)) < low THEN
                    low = VAL(Grid.Cell(rowgridoffset + 5 , j + i - 1))
                END IF
                vol = vol + VAL(Grid.Cell(rowgridoffset + 7 , j + i - 1))
            NEXT i
            
            Grid.Cell(rowgridoffset + 4 , lines) = STR$(high)
            Grid.Cell(rowgridoffset + 5 , lines) = STR$(low)
            Grid.Cell(rowgridoffset + 3 , lines) = Grid.Cell(rowgridoffset + 3 , j)
            Grid.Cell(rowgridoffset + 6 , lines) = Grid.Cell(rowgridoffset + 6 , j + VAL(tfmult.Text) - 1)
            Grid.Cell(rowgridoffset + 7 , lines) = STR$(vol)
            lines ++
        END IF
        IF j > chartbars(displayedfile) - VAL(tfmult.Text) + 1 THEN
            high = VAL(Grid.Cell(rowgridoffset + 4 , j))
            low = VAL(Grid.Cell(rowgridoffset + 5 , j))
            vol = 0
            FOR i = 1 TO chartbars(displayedfile) - j + 1
                IF VAL(Grid.Cell(rowgridoffset + 4 , j + i - 1)) > high THEN
                    high = VAL(Grid.Cell(rowgridoffset + 4 , j + i - 1))
                END IF
                IF VAL(Grid.Cell(rowgridoffset + 5 , j + i - 1)) < low THEN
                    low = VAL(Grid.Cell(rowgridoffset + 5 , j + i - 1))
                END IF
                vol = vol + VAL(Grid.Cell(rowgridoffset + 7 , j + i - 1))
            NEXT i
            Grid.Cell(rowgridoffset + 4 , lines) = STR$(high)
            Grid.Cell(rowgridoffset + 5 , lines) = STR$(low)
            Grid.Cell(rowgridoffset + 3 , lines) = Grid.Cell(rowgridoffset + 3 , j)
            Grid.Cell(rowgridoffset + 6 , lines) = Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile))
            Grid.Cell(rowgridoffset + 7 , lines) = STR$(vol)
            lines ++
        END IF
    NEXT j
    chartbars(displayedfile) = lines - 1
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))

    'tfmultstr=tfmult.text:cpptmpfuncreturn=varptr$(tfmultok_clickcpp(varptr(tfmultstr)))  
    'displayedfilestr=str$(displayedfile):chartbars(displayedfile) = val(varptr$(getchartbars(varptr(displayedfilestr))))      

'dim offsetstr as string    
'for i=1 to 7
'    for j=1 to chartbars(displayedfile)
'        rowgridoffsetstr=str$(rowgridoffset + i)
'        offsetstr=str$(j)
'        Grid.Cell(rowgridoffset + i , j)=varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(offsetstr)))
'    next j
'next i
   
    exportfilename()
   
    Scrollchart.Max = chartbars(displayedfile)
    Scrollchart.Position = chartbars(displayedfile)
    chartstart = Scrollchart.Position - numbars
    btnOnClick(drwBox)
END SUB

SUB dispchartnbchanged()
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    displayedfile = dispchartnb.ItemIndex + 1
    displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setdisplayedfile(varptr(displayedfilestr)))
    rowgridoffset = 7 * (displayedfile - 1)
    rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
    Scrollchart.Max = chartbars(displayedfile)
    Scrollchart.Position = chartbars(displayedfile)
    updatemixerlists
    btnOnClick(drwBox)
    say "Display chart number: "+str$(dispchartnb.ItemIndex + 1)
END SUB

SUB closedispcanvas_click()
    say "Separate canvas closed"    
    canvas.Visible = FALSE
    closedispcanvas.Visible = FALSE
    'sepindizoommore.visible=0
    'sepindizoomless.visible=0
    'sepindiheight.visible=0
    'sepindiheightok.visible=0
    'sepindiheightlab.visible=0
    sepindivalminlab.Visible = 0
    sepindivalmaxlab.Visible = 0
    sepindivalminedit.Visible = 0
    sepindivalmaxedit.Visible = 0
    sepindivalok.Visible = 0
    showcanvas = 0
    setup()
    WITH Graph
        .Height = frmMain.ClientHeight - 180 + 100 + 10
        .Width = frmMain.ClientWidth - leftwidth - 25
        IF openedfilesnb > 0 THEN
            .Redrawchart  'Redraw the QChart Object
            .firstbufcntreset
            .savebuffertmp
            .paintchart
        END IF
    END WITH
    WITH Scrollchart
        .Left = Graph.Left
        .Top = Graph.Height + 70 - 20
        .Width = Graph.Width
    END WITH
    WITH pricescaleplusbtn
        .Left = Graph.Left - 30
        .Top = Graph.Top + 15
    END WITH
    WITH pricescaleminusbtn
        .Left = Graph.Left - 30
        .Top = Graph.Top + 15 + 20
    END WITH
    WITH addbarsbtn
        .Left = Graph.Left - 30
        .Top = Graph.Top + 15 + 20+20
    END WITH
    split.Top = Graph.Height + 70
    split.Left = Graph.Left
    split.Width = Graph.Width
    splith.Left = Graph.Left
    splith.Top = Graph.Top
    splith.Height = Graph.Height
    'Plus anything else that needs doing in your form resize
    'Graph.OnPaint = Graph.PaintChart                  'This line REQUIRED to process Repaints
    canvas.OnPaint = canvas.paint
    WITH closedispchart
        .Top = Graph.Top + 2
        .Left = Graph.Width + 98 + leftwidth - 100
    END WITH
END SUB

SUB showcanvasclick()
    'canvas.visible=1
    closedispcanvas.Visible = 1
    'sepindizoommore.visible=1
    'sepindizoomless.visible=1
    'sepindiheight.visible=1
    'sepindiheightok.visible=1
    'sepindiheightlab.visible=1
    'sepindivalminlab.visible=1
    'sepindivalmaxlab.visible=1
    'sepindivalminedit.visible=1
    'sepindivalmaxedit.visible=1
    'sepindivalok.visible=1
    showcanvas = 1
    setup()
    'WITH Graph
    '.Height = frmMain.ClientHeight-180'+130
    '.Width = frmMain.ClientWidth - btngroupbox.Width-25
    'if openedfilesnb>0 then
    '.RedrawChart                                       'Redraw the QChart Object
    'end if
    'END WITH
    'WITH Scrollchart
    '.Left = Graph.Left
    '.Top = Graph.Height+50-20
    '.Width = Graph.Width
    'END WITH
    'Plus anything else that needs doing in your form resize
    'Graph.OnPaint = Graph.PaintChart                  'This line REQUIRED to process Repaints
    'canvas.onpaint=canvas.paint
    'with closedispchart
    '.Top=Graph.Top+2
    '.Left=Graph.Width+98
    'end with
    btnOnClick(drwBox)
    WITH Graph
        .bufcntreset
        .savebuffertmp
    END WITH
    say "Separate canvas shown"
END SUB

SUB closedispchart_click()
    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Close chart " + importedfile(displayedfile) + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Close chart " + importedfile(displayedfile))
    IF openedfilesnb = 0 THEN
        Graph.Visible = FALSE
        split.Visible = 0
        splith.Visible = 0
        canvas.Visible = FALSE
        closedispchart.Visible = FALSE
        Scrollchart.Visible = 0
        pricescaleplusbtn.visible=0
        pricescaleminusbtn.visible=0
        addbarsbtn.visible=0
        'sepindizoommore.visible=0
        'sepindizoomless.visible=0
        'sepindiheight.visible=1
        'sepindiheightok.visible=1
        'sepindiheightlab.visible=1
        sepindivalminlab.Visible = 0
        sepindivalmaxlab.Visible = 0
        sepindivalminedit.Visible = 0
        sepindivalmaxedit.Visible = 0
        sepindivalok.Visible = 0
        showcanvas = 0
        setup()
        closedispcanvas.Visible = 0
        mixgridcolcount(displayedfile) = 0
        mixgridcolcount2(displayedfile) = 0
        mixgridcolcount3(displayedfile) = 0
        mixgridcolcount4(displayedfile) = 0
        updatemixerlists
        tfmult.Text = "1"
        barsdisplayed.Text = "100"
        disableallindis
        EXIT SUB
    END IF
    IF openedfilesnb = 1 THEN
        canvas.Visible = 0
        sepindivalminlab.Visible = 0
        sepindivalmaxlab.Visible = 0
        sepindivalminedit.Visible = 0
        sepindivalmaxedit.Visible = 0
        sepindivalok.Visible = 0
        showcanvas = 0
        setup()
        mixgridcolcount(displayedfile) = 0
        mixgridcolcount2(displayedfile) = 0
        mixgridcolcount3(displayedfile) = 0
        mixgridcolcount4(displayedfile) = 0
        updatemixerlists
        say "Chart closed"
    END IF
    IF openedfilesnb > 1 && displayedfile < openedfilesnb THEN
        rowgridoffset = 7 * (displayedfile - 1)
        rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
    END IF
    IF openedfilesnb > 1 && displayedfile < openedfilesnb THEN
        DIM i AS INTEGER , j AS INTEGER
        FOR i = displayedfile TO openedfilesnb
            FOR j = 1 TO chartbars(i+1)
                Grid.Cell(7 * (i - 1) + 1 , j) = Grid.Cell(7 * (i) + 1 , j)
                Grid.Cell(7 * (i - 1) + 2 , j) = Grid.Cell(7 * (i) + 2 , j)
                Grid.Cell(7 * (i - 1) + 3 , j) = Grid.Cell(7 * (i) + 3 , j)
                Grid.Cell(7 * (i - 1) + 4 , j) = Grid.Cell(7 * (i) + 4 , j)
                Grid.Cell(7 * (i - 1) + 5 , j) = Grid.Cell(7 * (i) + 5 , j)
                Grid.Cell(7 * (i - 1) + 6 , j) = Grid.Cell(7 * (i) + 6 , j)
                Grid.Cell(7 * (i - 1) + 7 , j) = Grid.Cell(7 * (i) + 7 , j)
                Gridtmp.Cell(7 * (i - 1) + 1 , j) = Grid.Cell(7 * (i) + 1 , j)
                Gridtmp.Cell(7 * (i - 1) + 2 , j) = Grid.Cell(7 * (i) + 2 , j)
                Gridtmp.Cell(7 * (i - 1) + 3 , j) = Grid.Cell(7 * (i) + 3 , j)
                Gridtmp.Cell(7 * (i - 1) + 4 , j) = Grid.Cell(7 * (i) + 4 , j)
                Gridtmp.Cell(7 * (i - 1) + 5 , j) = Grid.Cell(7 * (i) + 5 , j)
                Gridtmp.Cell(7 * (i - 1) + 6 , j) = Grid.Cell(7 * (i) + 6 , j)
                Gridtmp.Cell(7 * (i - 1) + 7 , j) = Grid.Cell(7 * (i) + 7 , j)
                mixgrid.Cell(j - 1 , i) = mixgrid.Cell(j - 1 , i + 1)
                mixgrid2.Cell(j - 1 , i) = mixgrid2.Cell(j - 1 , i + 1)
                mixgrid3.Cell(j - 1 , i) = mixgrid3.Cell(j - 1 , i + 1)
                mixgrid4.Cell(j - 1 , i) = mixgrid4.Cell(j - 1 , i + 1)
            NEXT j            
            importedfile(i) = importedfile(i + 1)
            chartbars(i) = chartbars(i + 1)
            mixgridcolcount(i) = mixgridcolcount(i + 1)
            mixgridcolcount2(i) = mixgridcolcount2(i + 1)
            mixgridcolcount3(i) = mixgridcolcount3(i + 1)
            mixgridcolcount4(i) = mixgridcolcount4(i + 1)
        NEXT i
        cpptmpfuncreturn=varptr$(shiftgridsonebackward())
    END IF
    IF openedfilesnb > 1 AND displayedfile = openedfilesnb THEN
        rowgridoffset = 7 * (displayedfile - 2)
        rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
        mixgridcolcount(displayedfile) = 0
        mixgridcolcount2(displayedfile) = 0
        mixgridcolcount3(displayedfile) = 0
        mixgridcolcount4(displayedfile) = 0
        displayedfile --
        cpptmpfuncreturn=varptr$(displayedfileminusone())
    END IF
    openedfilesnb --
    cpptmpfuncreturn=varptr$(openedfilesnbminusone())
    dispchartnb.DelItems = dispchartnb.ItemCount - 1
    dispchartnb.ItemIndex = displayedfile - 1
    IF openedfilesnb > 0 THEN
        Scrollchart.Max = chartbars(displayedfile)
        Scrollchart.Position = chartbars(displayedfile)
        say "Chart closed"
    END IF
    chartstart = Scrollchart.Position - numbars
    updatemixerlists
    IF openedfilesnb = 0 THEN
        Graph.Visible = FALSE
        split.Visible = 0
        splith.Visible = 0
        closedispchart.Visible = FALSE
        Scrollchart.Visible = 0
        pricescaleplusbtn.visible=0
        pricescaleminusbtn.visible=0
        addbarsbtn.visible=0
        'sepindizoommore.visible=0
        'sepindizoomless.visible=0
        'sepindiheight.visible=0
        'sepindiheightok.visible=0
        'sepindiheightlab.visible=0
        'sepindivalminlab.visible=0
        'sepindivalmaxlab.visible=0
        'sepindivalminedit.visible=0
        'sepindivalmaxedit.visible=0
        'sepindivalok.visible=0
        closedispcanvas.Visible = 0
        'bgimg.visible=1
        tfmult.Text = "1"
        barsdisplayed.Text = "100"
        disableallindis         
        EXIT SUB
    END IF
    IF openedfilesnb > 0 THEN
        btnOnClick(drwBox)
    END IF
END SUB


SUB dispbarsok_click()
    numbars = VAL(barsdisplayed.Text)
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    Scrollchart.Max = chartbars(displayedfile)
    Scrollchart.Position = chartbars(displayedfile)
    chartstart = Scrollchart.Position - numbars
    btnOnClick(drwBox)
    say "Displayed bars set to: "+barsdisplayed.Text
END SUB

SUB Scrolling()
    chartstart = Scrollchart.Position - numbars
    IF scrollchartpositionwait = 1 THEN
        IF scrollmodebtn.Flat = 0 THEN
            scrollmodebtn.Flat = 1
            scrollmodebtn.Color = &H88cc88
            scrollmode = 1
            Scrollchart.Enabled = 1
        END IF
        btnOnClick(drwBox)
    END IF
END SUB

SUB TimerOverchartbackward()
    chartstart --
    btnOnClick(drwBox)
END SUB

SUB TimerOverdispbarsp()
    numbars ++
    barsdisplayed.Text = STR$(VAL(barsdisplayed.Text) + 1)
    Scrollchart.Max = chartbars(displayedfile)
    Scrollchart.Position = chartbars(displayedfile)
    chartstart = Scrollchart.Position - numbars
    btnOnClick(drwBox)
END SUB

SUB TimerOverdispbarsm()
    numbars --
    barsdisplayed.Text = STR$(VAL(barsdisplayed.Text) - 1)
    Scrollchart.Max = chartbars(displayedfile)
    Scrollchart.Position = chartbars(displayedfile)
    chartstart = Scrollchart.Position - numbars
    btnOnClick(drwBox)
END SUB

SUB dispbarspd()
    Timerdispbarsp.Enabled = 1
END SUB

SUB dispbarspu()
    Timerdispbarsp.Enabled = 0
END SUB

SUB dispbarsmd()
    Timerdispbarsm.Enabled = 1
END SUB

SUB dispbarsmu()
    Timerdispbarsm.Enabled = 0
END SUB

SUB setup()

    'Prevent initial resize exception
    IF AppStart THEN AppStart = FALSE  :  EXIT SUB
    'de.bug "Resize"


    'with bgimg
    '.width=frmmain.width
    '.height=frmmain.height
    'end with

    'with btngroupbox
    '.top=frmmain.height-265
    'end with

    WITH Graph
        .Height = frmMain.ClientHeight - 70  '+10+leftwidth-180
        IF showcanvas = 1 THEN
            .Height = .Height - 90 - sepindiheight + 110
        END IF
        .Width = frmMain.ClientWidth - leftwidth - 25
        .Left = leftwidth + 16
        IF openedfilesnb > 0 THEN
            .Redrawchart  'Redraw the QChart Object
            .firstbufcntreset
            .savebuffertmp
            .paintchart
        END IF
    END WITH

    split.Top = Graph.Height + 70
    split.Left = Graph.Left
    split.Width = Graph.Width

    splith.Left = Graph.Left
    splith.Top = Graph.Top
    splith.Height = Graph.Height

    IF showcanvas = 1 THEN
        WITH canvas
            .Width = graph.XAxis.LEN 'graph.left+graph.width-52-canvas.left
            .Height = sepindiheight
            .Top = Graph.Top + Graph.Height + 20  '-val(sepindiheight.text)+130
            if charttypecombo.itemindex=1 then .Left = 1.8621*graph.left 'leftwidth + 97 - 4 + 23
            if charttypecombo.itemindex=0 then .Left = graph.left+timechartpos(0,1)
            .RedrawChart2
            .firstbufcntreset
            .savebuffertmp
            .paint
        END WITH        

        WITH closedispcanvas
            .Top = canvas.Top
            .Left = canvas.left+canvas.width'canvas.Width + 181 - 4 + leftwidth - 100 - 5 + 20
        END WITH             

        'with sepindizoommore
        '.Top =graph.top+graph.height+15+10
        '.Left=leftwidth+97+canvas.width+15
        '.width=20
        'end with

        'with sepindizoomless
        '.Top =graph.top+graph.height+65+10
        '.Left=leftwidth+97+canvas.width+15
        '.width=20
        'end with

        'with sepindiheightlab
        '.Top =graph.top+graph.height+20+10
        '.Left=leftwidth+97+canvas.width+45
        '.width=100
        'end with

        'with sepindiheight
        '
        '
        '.Top =graph.top+graph.height+40+10
        '.Left=leftwidth+97+canvas.width+45
        '.width=50
        '
        'end with

        'with sepindiheightok
        '
        '
        '.Top =graph.top+graph.height+40+10
        '.Left=leftwidth+97+canvas.width+95
        '.width=25
        '
        'end with

        WITH sepindivalminlab
            .Visible = 1
            'align=6
            .Top = Graph.Top + Graph.Height + 65 + 10
            .Left = leftwidth + 10
            'caption="Min value"
        END WITH

        WITH sepindivalminedit
            .Visible = 1
            'align=6
            .Top = Graph.Top + Graph.Height + 65 + 20 + 10
            .Left = leftwidth + 10
            'width=50
            'text="0"
        END WITH

        WITH sepindivalmaxlab
            .Visible = 1
            'align=6
            .Top = Graph.Top + Graph.Height + 65 - 50 + 10
            .Left = leftwidth + 10
            'caption="Max value"
        END WITH

        WITH sepindivalmaxedit
            .Visible = 1
            'align=6
            .Top = Graph.Top + Graph.Height + 65 - 50 + 20 + 10
            .Left = leftwidth + 10
            'width=50
            'text="0"
        END WITH

        WITH sepindivalok
            .Visible = 1
            'align=6
            .Top = Graph.Top + Graph.Height + 65 - 50 + 20 + 25 + 10
            .Left = leftwidth + 10 + 55
            'width=25
            'onclick=dispbarsok_click
            'caption="OK"
        END WITH

    END IF

    WITH Scrollchart
        .Left = Graph.Left
        .Top = Graph.Height + 70 - 20
        .Width = Graph.Width
    END WITH
    
    with pricescaleplusbtn
        .Left = Graph.Left - 30
        .Top = Graph.Top + 15
    end with
    
    with pricescaleminusbtn
        .Left = Graph.Left - 30
        .Top = Graph.Top + 15 + 20
    end with
    
    with addbarsbtn
        .Left = Graph.Left - 30
        .Top = Graph.Top + 15 + 20+20
    end with

    'Plus anything else that needs doing in your form resize
    'Graph.OnPaint = Graph.PaintChart                  'This line REQUIRED to process Repaints
    IF showcanvas = 1 THEN
        canvas.OnPaint = canvas.paint
    END IF
    WITH closedispchart
        .Top = Graph.Top + 2
        .Left = Graph.Width + 98 + leftwidth - 100
    END WITH

    IF showcanvas = 1 THEN
        WITH sepindivalminlab
            .Align = 6
            .Top = Graph.Top + Graph.Height + 65 + 10
            .Left = leftwidth + 10
            .Caption = "Min value"
        END WITH

        WITH sepindivalminedit
            .Align = 6
            .Top = Graph.Top + Graph.Height + 65 + 20 + 10
            .Left = leftwidth + 10
            .Width = 50
        END WITH

        WITH sepindivalmaxlab
            .Align = 6
            .Top = Graph.Top + Graph.Height + 65 - 50 + 10
            .Left = leftwidth + 10
            .Caption = "Max value"
        END WITH

        WITH sepindivalmaxedit
            .Align = 6
            .Top = Graph.Top + Graph.Height + 65 - 50 + 20 + 10
            .Left = leftwidth + 10
            .Width = 50
        END WITH

        WITH sepindivalok
            .Align = 6
            .Top = Graph.Top + Graph.Height + 65 - 50 + 20 + 25 + 10
            .Left = leftwidth + 10 + 55
            .Width = 25
        END WITH
    END IF

END SUB


CREATE mixform AS QFORM
    Width = 800
    Height = 600
    Center
    Caption = "Mixer"

    CREATE additionlab AS QLABEL
        Left = 0
        Top = 0
        Caption = "Addition list:"
    END CREATE

    CREATE additionlist AS QLISTBOX
        Left = 0
        Top = additionlab.Top + 20
        Height = 80
        Width = mixform.Width - 23
    END CREATE

    CREATE additionbutton AS QBUTTON
        Left = 0
        Top = additionlist.Top + additionlist.Height
        Caption = "Add chart"
        OnClick = importfileaddition
    END CREATE

    CREATE additionbuttondel AS QBUTTON
        Left = additionbutton.Left + additionbutton.Width + 10
        Top = additionlist.Top + additionlist.Height
        Caption = "Remove chart"
        OnClick = importfileadditiondel
    END CREATE

    CREATE subtractionlab AS QLABEL
        Left = 0
        Top = additionbutton.Top + additionbutton.Height + 10
        Caption = "Subtraction list:"
    END CREATE

    CREATE subtractionlist AS QLISTBOX
        Left = 0
        Top = subtractionlab.Top + 20
        Height = 80
        Width = mixform.Width - 23
    END CREATE

    CREATE subtractionbutton AS QBUTTON
        Left = 0
        Top = subtractionlist.Top + subtractionlist.Height
        Caption = "Add chart"
        OnClick = importfilesubtraction
    END CREATE

    CREATE subtractionbuttondel AS QBUTTON
        Left = subtractionbutton.Left + subtractionbutton.Width + 10
        Top = subtractionlist.Top + subtractionlist.Height
        Caption = "Remove chart"
        OnClick = importfilesubtractiondel
    END CREATE

    CREATE multiplylab AS QLABEL
        Left = 0
        Top = subtractionbutton.Top + subtractionbutton.Height + 10
        Caption = "Multiplication list:"
    END CREATE

    CREATE multiplylist AS QLISTBOX
        Left = 0
        Top = multiplylab.Top + 20
        Height = 80
        Width = mixform.Width - 23
    END CREATE

    CREATE multiplybutton AS QBUTTON
        Left = 0
        Top = multiplylist.Top + multiplylist.Height
        Caption = "Add chart"
        OnClick = importfilemultiply
    END CREATE

    CREATE multiplybuttondel AS QBUTTON
        Left = multiplybutton.Left + multiplybutton.Width + 10
        Top = multiplylist.Top + multiplylist.Height
        Caption = "Remove chart"
        OnClick = importfilemultiplydel
    END CREATE

    CREATE dividelab AS QLABEL
        Left = 0
        Top = multiplybutton.Top + multiplybutton.Height + 10
        Caption = "Division list:"
    END CREATE

    CREATE dividelist AS QLISTBOX
        Left = 0
        Top = dividelab.Top + 20
        Height = 80
        Width = mixform.Width - 23
    END CREATE

    CREATE dividebutton AS QBUTTON
        Left = 0
        Top = dividelist.Top + dividelist.Height
        Caption = "Add chart"
        OnClick = importfiledivide
    END CREATE

    CREATE dividebuttondel AS QBUTTON
        Left = dividebutton.Left + dividebutton.Width + 10
        Top = dividelist.Top + dividelist.Height
        Caption = "Remove chart"
        OnClick = importfiledividedel
    END CREATE

    CREATE otheropbtn AS QBUTTON
        Left = 0
        Top = dividebuttondel.Top + dividebuttondel.Height
        Caption = "Other operations"
        OnClick = otheropssub
    END CREATE


END CREATE

CREATE chartconvform AS QFORM
    Caption = "Chart conversions"
    CREATE exp10btn AS QBUTTON
        Left = 0
        Top = 0
        Caption = "Convert chart to exponential base 10"
        Width = 300
        OnClick = exp10sub
    END CREATE
END CREATE

CREATE attribtfform AS QFORM
    Caption = "Timeframe attribution"
    CREATE attribtflabel AS qlabel
        Left = 0
        Top = 0
        Caption = "Chart TF:"
    END CREATE
    CREATE attribtfcombo AS qcombobox
        Left = 50
        Top = 0
        Width = 70
        AddItems "1"
        AddItems "5"
        AddItems "15"
        AddItems "30"
        AddItems "60"
        AddItems "240"
        AddItems "1440"
        AddItems "10080"
        AddItems "43200"
        OnChange = attribtfeditItemChanged
    END CREATE
    CREATE attribtfminuteslabel AS qlabel
        Left = 120
        Top = 0
        Caption = "minutes"
    END CREATE
END CREATE

sub writetf (dispfile as integer,tftowrite as integer)
 IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
 DIM o AS INTEGER
 defint ii=chartbars(displayedfile) - VAL(cntbarsedit.Text)
 if ii<1 then ii=1
 
 select case tftowrite
 
     case 1:
                        'REDIM Open5(0 TO 0) AS DOUBLE
                        'REDIM high5(0 TO 0) AS DOUBLE
                        'REDIM low5(0 TO 0) AS DOUBLE
                        'REDIM Close5(0 TO 0) AS DOUBLE
                        'REDIM volume5(0 TO 0) AS INTEGER
                        'redim date5(0 TO 0) AS string
                        'redim time5(0 TO 0) AS string
                        'REDIM datetimeserial5(0 TO 0) AS double

                        'REDIM Open5(1 TO 100) AS DOUBLE
                        'REDIM high5(1 TO 100) AS DOUBLE
                        'REDIM low5(1 TO 100) AS DOUBLE
                        'REDIM Close5(1 TO 100) AS DOUBLE
                        'REDIM volume5(1 TO 100) AS INTEGER
                        'redim date5(1 TO 100) AS string
                        'redim time5(1 TO 100) AS string
                        'REDIM datetimeserial5(1 TO 100) AS double

                        
                        o = 0
                        dim year as integer,month as integer,day as integer, hour as integer,minute as integer,second as integer

                        FOR i = chartbars(displayedfile) TO ii STEP - 1
                            date1(o) = Grid.Cell(rowgridoffset + 1 , i)
                            time1(o) = Grid.Cell(rowgridoffset + 2 , i)
                            Open1(o) = VAL(Grid.Cell(rowgridoffset + 3 , i))
                            high1(o) = VAL(Grid.Cell(rowgridoffset + 4 , i))
                            low1(o) = VAL(Grid.Cell(rowgridoffset + 5 , i))
                            Close1(o) = VAL(Grid.Cell(rowgridoffset + 6 , i))
                            volume1(o) = VAL(Grid.Cell(rowgridoffset + 7 , i))
                            year = VAL(MID$(date1(o) , 0 , 4))
                            month = VAL(MID$(date1(o) , 6 , 2))
                            day = VAL(MID$(date1(o) , 9 , 2))
                            hour = VAL(MID$(time1(o) , 0 , 2))
                            minute = VAL(MID$(time1(o) , 4 , 2))
                            second=0
                            parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second)
                            datetimeserial1(o)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day)
                            'datetimeserial5(o)=datetimeserial5(o)*24*60*60
                            'datetimeserial5(o)=datetimeserial5(o)+(hour*60*60)
                            'datetimeserial5(o)=datetimeserial5(o)+(minute*60)
                            o ++
                        NEXT i
 
     case 5:
                        'REDIM Open5(0 TO 0) AS DOUBLE
                        'REDIM high5(0 TO 0) AS DOUBLE
                        'REDIM low5(0 TO 0) AS DOUBLE
                        'REDIM Close5(0 TO 0) AS DOUBLE
                        'REDIM volume5(0 TO 0) AS INTEGER
                        'redim date5(0 TO 0) AS string
                        'redim time5(0 TO 0) AS string
                        'REDIM datetimeserial5(0 TO 0) AS double

                        'REDIM Open5(1 TO 100) AS DOUBLE
                        'REDIM high5(1 TO 100) AS DOUBLE
                        'REDIM low5(1 TO 100) AS DOUBLE
                        'REDIM Close5(1 TO 100) AS DOUBLE
                        'REDIM volume5(1 TO 100) AS INTEGER
                        'redim date5(1 TO 100) AS string
                        'redim time5(1 TO 100) AS string
                        'REDIM datetimeserial5(1 TO 100) AS double

                        
                        o = 0
                        'dim year as integer,month as integer,day as integer, hour as integer,minute as integer,second as integer

                        FOR i = chartbars(displayedfile) TO ii STEP - 1
                            date5(o) = Grid.Cell(rowgridoffset + 1 , i)
                            time5(o) = Grid.Cell(rowgridoffset + 2 , i)
                            Open5(o) = VAL(Grid.Cell(rowgridoffset + 3 , i))
                            high5(o) = VAL(Grid.Cell(rowgridoffset + 4 , i))
                            low5(o) = VAL(Grid.Cell(rowgridoffset + 5 , i))
                            Close5(o) = VAL(Grid.Cell(rowgridoffset + 6 , i))
                            volume5(o) = VAL(Grid.Cell(rowgridoffset + 7 , i))
                            year = VAL(MID$(date5(o) , 0 , 4))
                            month = VAL(MID$(date5(o) , 6 , 2))
                            day = VAL(MID$(date5(o) , 9 , 2))
                            hour = VAL(MID$(time5(o) , 0 , 2))
                            minute = VAL(MID$(time5(o) , 4 , 2))
                            second=0
                            parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second)
                            datetimeserial5(o)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day)
                            'datetimeserial5(o)=datetimeserial5(o)*24*60*60
                            'datetimeserial5(o)=datetimeserial5(o)+(hour*60*60)
                            'datetimeserial5(o)=datetimeserial5(o)+(minute*60)
                            o ++
                        NEXT i
        case 15:
                        'REDIM Open15(0 TO 0) AS DOUBLE
                        'REDIM high15(0 TO 0) AS DOUBLE
                        'REDIM low15(0 TO 0) AS DOUBLE
                        'REDIM Close15(0 TO 0) AS DOUBLE
                        'REDIM volume15(0 TO 0) AS INTEGER
                        'redim date15(0 TO 0) AS string
                        'redim time15(0 TO 0) AS string
                        'REDIM datetimeserial15(0 TO 0) AS double

                        'REDIM Open15(1 TO 100) AS DOUBLE
                        'REDIM high15(1 TO 100) AS DOUBLE
                        'REDIM low15(1 TO 100) AS DOUBLE
                        'REDIM Close15(1 TO 100) AS DOUBLE
                        'REDIM volume15(1 TO 100) AS INTEGER
                        'redim date15(1 TO 100) AS string
                        'redim time15(1 TO 100) AS string
                        'REDIM datetimeserial15(1 TO 100) AS double

                        
                        o = 0

                        FOR i = chartbars(displayedfile) TO ii STEP - 1
                            date15(o) = Grid.Cell(rowgridoffset + 1 , i)
                            time15(o) = Grid.Cell(rowgridoffset + 2 , i)
                            Open15(o) = VAL(Grid.Cell(rowgridoffset + 3 , i))
                            high15(o) = VAL(Grid.Cell(rowgridoffset + 4 , i))
                            low15(o) = VAL(Grid.Cell(rowgridoffset + 5 , i))
                            Close15(o) = VAL(Grid.Cell(rowgridoffset + 6 , i))
                            volume15(o) = VAL(Grid.Cell(rowgridoffset + 7 , i))
                            year = VAL(MID$(date15(o) , 0 , 4))
                            month = VAL(MID$(date15(o) , 6 , 2))
                            day = VAL(MID$(date15(o) , 9 , 2))
                            hour = VAL(MID$(time15(o) , 0 , 2))
                            minute = VAL(MID$(time15(o) , 4 , 2))
                            second=0
                            parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second)
                            datetimeserial15(o)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day)
                            'datetimeserial15(o)=DateSerial (year, month, day)
                            'datetimeserial15(o)=datetimeserial15(o)*24*60*60
                            'datetimeserial15(o)=datetimeserial15(o)+(hour*60*60)
                            'datetimeserial15(o)=datetimeserial15(o)+(minute*60)
                            o ++
                        NEXT i
        case 30:
                        'REDIM Open30(0 TO 0) AS DOUBLE
                        'REDIM high30(0 TO 0) AS DOUBLE
                        'REDIM low30(0 TO 0) AS DOUBLE
                        'REDIM Close30(0 TO 0) AS DOUBLE
                        'REDIM volume30(0 TO 0) AS INTEGER
                        'redim date30(0 TO 0) AS string
                        'redim time30(0 TO 0) AS string
                        'REDIM datetimeserial30(0 TO 0) AS double

                        'REDIM Open30(1 TO 100) AS DOUBLE
                        'REDIM high30(1 TO 100) AS DOUBLE
                        'REDIM low30(1 TO 100) AS DOUBLE
                        'REDIM Close30(1 TO 100) AS DOUBLE
                        'REDIM volume30(1 TO 100) AS INTEGER
                        'redim date30(1 TO 100) AS string
                        'redim time30(1 TO 100) AS string
                        'REDIM datetimeserial30(1 TO 100) AS double

                        
                        o = 0

                        FOR i = chartbars(displayedfile) TO ii STEP - 1
                            date30(o) = Grid.Cell(rowgridoffset + 1 , i)
                            time30(o) = Grid.Cell(rowgridoffset + 2 , i)
                            Open30(o) = VAL(Grid.Cell(rowgridoffset + 3 , i))
                            high30(o) = VAL(Grid.Cell(rowgridoffset + 4 , i))
                            low30(o) = VAL(Grid.Cell(rowgridoffset + 5 , i))
                            Close30(o) = VAL(Grid.Cell(rowgridoffset + 6 , i))
                            volume30(o) = VAL(Grid.Cell(rowgridoffset + 7 , i))
                            year = VAL(MID$(date30(o) , 0 , 4))
                            month = VAL(MID$(date30(o) , 6 , 2))
                            day = VAL(MID$(date30(o) , 9 , 2))
                            hour = VAL(MID$(time30(o) , 0 , 2))
                            minute = VAL(MID$(time30(o) , 4 , 2))
                            second=0
                            parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second)
                            datetimeserial30(o)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day)
                            'datetimeserial30(o)=DateSerial (year, month, day)
                            'datetimeserial30(o)=datetimeserial30(o)*24*60*60
                            'datetimeserial30(o)=datetimeserial30(o)+(hour*60*60)
                            'datetimeserial30(o)=datetimeserial30(o)+(minute*60)
                            o ++
                        NEXT i
        case 60:
                        'REDIM Open60(0 TO 0) AS DOUBLE
                        'REDIM high60(0 TO 0) AS DOUBLE
                        'REDIM low60(0 TO 0) AS DOUBLE
                        'REDIM Close60(0 TO 0) AS DOUBLE
                        'REDIM volume60(0 TO 0) AS INTEGER
                        'redim date60(0 TO 0) AS string
                        'redim time60(0 TO 0) AS string
                        'REDIM datetimeserial60(0 TO 0) AS double

                        'REDIM Open60(1 TO 100) AS DOUBLE
                        'REDIM high60(1 TO 100) AS DOUBLE
                        'REDIM low60(1 TO 100) AS DOUBLE
                        'REDIM Close60(1 TO 100) AS DOUBLE
                        'REDIM volume60(1 TO 100) AS INTEGER
                        'redim date60(1 TO 100) AS string
                        'redim time60(1 TO 100) AS string
                        'REDIM datetimeserial60(1 TO 100) AS double

                        
                        o = 0

                        FOR i = chartbars(displayedfile) TO ii STEP - 1
                            date60(o) = Grid.Cell(rowgridoffset + 1 , i)
                            time60(o) = Grid.Cell(rowgridoffset + 2 , i)
                            Open60(o) = VAL(Grid.Cell(rowgridoffset + 3 , i))
                            high60(o) = VAL(Grid.Cell(rowgridoffset + 4 , i))
                            low60(o) = VAL(Grid.Cell(rowgridoffset + 5 , i))
                            Close60(o) = VAL(Grid.Cell(rowgridoffset + 6 , i))
                            volume60(o) = VAL(Grid.Cell(rowgridoffset + 7 , i))
                            year = VAL(MID$(date60(o) , 0 , 4))
                            month = VAL(MID$(date60(o) , 6 , 2))
                            day = VAL(MID$(date60(o) , 9 , 2))
                            hour = VAL(MID$(time60(o) , 0 , 2))
                            minute = VAL(MID$(time60(o) , 4 , 2))
                            second=0
                            parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second)
                            datetimeserial60(o)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day)
                            'datetimeserial60(o)=DateSerial (year, month, day)
                            'datetimeserial60(o)=datetimeserial60(o)*24*60*60
                            'datetimeserial60(o)=datetimeserial60(o)+(hour*60*60)
                            'datetimeserial60(o)=datetimeserial60(o)+(minute*60)
                            o ++
                        NEXT i
        case 240:
                        'REDIM Open240(0 TO 0) AS DOUBLE
                        'REDIM high240(0 TO 0) AS DOUBLE
                        'REDIM low240(0 TO 0) AS DOUBLE
                        'REDIM Close240(0 TO 0) AS DOUBLE
                        'REDIM volume240(0 TO 0) AS INTEGER
                        'redim date240(0 TO 0) AS string
                        'redim time240(0 TO 0) AS string
                        'REDIM datetimeserial240(0 TO 0) AS double

                        'REDIM Open240(1 TO 100) AS DOUBLE
                        'REDIM high240(1 TO 100) AS DOUBLE
                        'REDIM low240(1 TO 100) AS DOUBLE
                        'REDIM Close240(1 TO 100) AS DOUBLE
                        'REDIM volume240(1 TO 100) AS INTEGER
                        'redim date240(1 TO 100) AS string
                        'redim time240(1 TO 100) AS string
                        'REDIM datetimeserial240(1 TO 100) AS double

                        
                        o = 0

                        FOR i = chartbars(displayedfile) TO ii STEP - 1
                            date240(o) = Grid.Cell(rowgridoffset + 1 , i)
                            time240(o) = Grid.Cell(rowgridoffset + 2 , i)
                            Open240(o) = VAL(Grid.Cell(rowgridoffset + 3 , i))
                            high240(o) = VAL(Grid.Cell(rowgridoffset + 4 , i))
                            low240(o) = VAL(Grid.Cell(rowgridoffset + 5 , i))
                            Close240(o) = VAL(Grid.Cell(rowgridoffset + 6 , i))
                            volume240(o) = VAL(Grid.Cell(rowgridoffset + 7 , i))
                            year = VAL(MID$(date240(o) , 0 , 4))
                            month = VAL(MID$(date240(o) , 6 , 2))
                            day = VAL(MID$(date240(o) , 9 , 2))
                            hour = VAL(MID$(time240(o) , 0 , 2))
                            minute = VAL(MID$(time240(o) , 4 , 2))
                            second=0
                            parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second)
                            datetimeserial240(o)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day)
                            'datetimeserial240(o)=DateSerial (year, month, day)
                            'datetimeserial240(o)=datetimeserial240(o)*24*60*60
                            'datetimeserial240(o)=datetimeserial240(o)+(hour*60*60)
                            'datetimeserial240(o)=datetimeserial240(o)+(minute*60)
                            o ++
                        NEXT i
        case 1440:
                        'REDIM Open1440(0 TO 0) AS DOUBLE
                        'REDIM high1440(0 TO 0) AS DOUBLE
                        'REDIM low1440(0 TO 0) AS DOUBLE
                        'REDIM Close1440(0 TO 0) AS DOUBLE
                        'REDIM volume1440(0 TO 0) AS INTEGER
                        'redim date1440(0 TO 0) AS string
                        'redim time1440(0 TO 0) AS string
                        'REDIM datetimeserial1440(0 TO 0) AS double

                        'REDIM Open1440(1 TO 100) AS DOUBLE
                        'REDIM high1440(1 TO 100) AS DOUBLE
                        'REDIM low1440(1 TO 100) AS DOUBLE
                        'REDIM Close1440(1 TO 100) AS DOUBLE
                        'REDIM volume1440(1 TO 100) AS INTEGER
                        'redim date1440(1 TO 100) AS string
                        'redim time1440(1 TO 100) AS string
                        'REDIM datetimeserial1440(1 TO 100) AS double

                        
                        o = 0

                        FOR i = chartbars(displayedfile) TO ii STEP - 1
                            date1440(o) = Grid.Cell(rowgridoffset + 1 , i)
                            time1440(o) = Grid.Cell(rowgridoffset + 2 , i)
                            Open1440(o) = VAL(Grid.Cell(rowgridoffset + 3 , i))
                            high1440(o) = VAL(Grid.Cell(rowgridoffset + 4 , i))
                            low1440(o) = VAL(Grid.Cell(rowgridoffset + 5 , i))
                            Close1440(o) = VAL(Grid.Cell(rowgridoffset + 6 , i))
                            volume1440(o) = VAL(Grid.Cell(rowgridoffset + 7 , i))
                            year = VAL(MID$(date1440(o) , 0 , 4))
                            month = VAL(MID$(date1440(o) , 6 , 2))
                            day = VAL(MID$(date1440(o) , 9 , 2))
                            hour = VAL(MID$(time1440(o) , 0 , 2))
                            minute = VAL(MID$(time1440(o) , 4 , 2))
                            second=0
                            parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second)
                            datetimeserial1440(o)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day)
                            'datetimeserial1440(o)=DateSerial (year, month, day)
                            'datetimeserial1440(o)=datetimeserial1440(o)*24*60*60
                            'datetimeserial1440(o)=datetimeserial1440(o)+(hour*60*60)
                            'datetimeserial1440(o)=datetimeserial1440(o)+(minute*60)
                            o ++
                        NEXT i
        case 10080:
                        'REDIM Open10080(0 TO 0) AS DOUBLE
                        'REDIM high10080(0 TO 0) AS DOUBLE
                        'REDIM low10080(0 TO 0) AS DOUBLE
                        'REDIM Close10080(0 TO 0) AS DOUBLE
                        'REDIM volume10080(0 TO 0) AS INTEGER
                        'redim date10080(0 TO 0) AS string
                        'redim time10080(0 TO 0) AS string
                        'REDIM datetimeserial10080(0 TO 0) AS double

                        'REDIM Open10080(1 TO 100) AS DOUBLE
                        'REDIM high10080(1 TO 100) AS DOUBLE
                        'REDIM low10080(1 TO 100) AS DOUBLE
                        'REDIM Close10080(1 TO 100) AS DOUBLE
                        'REDIM volume10080(1 TO 100) AS INTEGER
                        'redim date10080(1 TO 100) AS string
                        'redim time10080(1 TO 100) AS string
                        'REDIM datetimeserial10080(1 TO 100) AS double

                        
                        o = 0

                        FOR i = chartbars(displayedfile) TO ii STEP - 1
                            date10080(o) = Grid.Cell(rowgridoffset + 1 , i)
                            time10080(o) = Grid.Cell(rowgridoffset + 2 , i)
                            Open10080(o) = VAL(Grid.Cell(rowgridoffset + 3 , i))
                            high10080(o) = VAL(Grid.Cell(rowgridoffset + 4 , i))
                            low10080(o) = VAL(Grid.Cell(rowgridoffset + 5 , i))
                            Close10080(o) = VAL(Grid.Cell(rowgridoffset + 6 , i))
                            volume10080(o) = VAL(Grid.Cell(rowgridoffset + 7 , i))
                            year = VAL(MID$(date10080(o) , 0 , 4))
                            month = VAL(MID$(date10080(o) , 6 , 2))
                            day = VAL(MID$(date10080(o) , 9 , 2))
                            hour = VAL(MID$(time10080(o) , 0 , 2))
                            minute = VAL(MID$(time10080(o) , 4 , 2))
                            second=0
                            parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second)
                            datetimeserial10080(o)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day)
                            'datetimeserial10080(o)=DateSerial (year, month, day)
                            'datetimeserial10080(o)=datetimeserial10080(o)*24*60*60
                            'datetimeserial10080(o)=datetimeserial10080(o)+(hour*60*60)
                            'datetimeserial10080(o)=datetimeserial10080(o)+(minute*60)
                            o ++
                        NEXT i
        case 43200:
                        'REDIM Open43200(0 TO 0) AS DOUBLE
                        'REDIM high43200(0 TO 0) AS DOUBLE
                        'REDIM low43200(0 TO 0) AS DOUBLE
                        'REDIM Close43200(0 TO 0) AS DOUBLE
                        'REDIM volume43200(0 TO 0) AS INTEGER
                        'redim date43200(0 TO 0) AS string
                        'redim time43200(0 TO 0) AS string
                        'REDIM datetimeserial43200(0 TO 0) AS double

                        'REDIM Open43200(1 TO 100) AS DOUBLE
                        'REDIM high43200(1 TO 100) AS DOUBLE
                        'REDIM low43200(1 TO 100) AS DOUBLE
                        'REDIM Close43200(1 TO 100) AS DOUBLE
                        'REDIM volume43200(1 TO 100) AS INTEGER
                        'redim date43200(1 TO 100) AS string
                        'redim time43200(1 TO 100) AS string
                        'REDIM datetimeserial43200(1 TO 100) AS double

                        
                        o = 0

                        FOR i = chartbars(displayedfile) TO ii STEP - 1
                            date43200(o) = Grid.Cell(rowgridoffset + 1 , i)
                            time43200(o) = Grid.Cell(rowgridoffset + 2 , i)
                            Open43200(o) = VAL(Grid.Cell(rowgridoffset + 3 , i))
                            high43200(o) = VAL(Grid.Cell(rowgridoffset + 4 , i))
                            low43200(o) = VAL(Grid.Cell(rowgridoffset + 5 , i))
                            Close43200(o) = VAL(Grid.Cell(rowgridoffset + 6 , i))
                            volume43200(o) = VAL(Grid.Cell(rowgridoffset + 7 , i))
                            year = VAL(MID$(date43200(o) , 0 , 4))
                            month = VAL(MID$(date43200(o) , 6 , 2))
                            day = VAL(MID$(date43200(o) , 9 , 2))
                            hour = VAL(MID$(time43200(o) , 0 , 2))
                            minute = VAL(MID$(time43200(o) , 4 , 2))
                            second=0
                            parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second)
                            datetimeserial43200(o)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day)
                            'datetimeserial43200(o)=DateSerial (year, month, day)
                            'datetimeserial43200(o)=datetimeserial43200(o)*24*60*60
                            'datetimeserial43200(o)=datetimeserial43200(o)+(hour*60*60)
                            'datetimeserial43200(o)=datetimeserial43200(o)+(minute*60)
                            o ++
                        NEXT i
    end select
        
end sub

sub attribtfeditItemChanged
    charttf(displayedfile)=val(attribtfcombo.item(attribtfcombo.itemindex))
    displayedfilestr=str$(displayedfile):defstr charttfdisplayedfilestr=str$(charttf(displayedfile)):cpptmpfuncreturn=varptr$(setcharttf(varptr(charttfdisplayedfilestr),varptr(displayedfilestr)))
    'print str$(charttf(displayedfile))
    writetf(displayedfile,charttf(displayedfile))
    defstr tftowritestr=str$(charttf(displayedfile)):cpptmpfuncreturn=varptr$(writetfcpp(varptr(tftowritestr)))
end sub

CREATE otheropsform AS QFORM
    Caption = "Other operations"

    CREATE reversebarslab AS QLABEL
        Top = 30
        Caption = "Reverse bars frequency:"
    END CREATE
    CREATE reversebarsnumeratoredit AS QEDIT
        Top = 30
        Left = reversebarslab.Left + reversebarslab.Width
        Width = 50
        Text = "1"
    END CREATE
    CREATE slashlab2 AS QLABEL
        Top = 30
        Left = reversebarsnumeratoredit.Left + reversebarsnumeratoredit.Width
        Caption = "/"
    END CREATE
    CREATE reversebarsdenominatoredit AS QEDIT
        Top = 30
        Left = slashlab2.Left + slashlab2.Width
        Width = 50
        Text = "1"
    END CREATE
    CREATE barslab2 AS QLABEL
        Top = 30
        Left = reversebarsdenominatoredit.Left + reversebarsdenominatoredit.Width
        Caption = "bar(s)"
    END CREATE
    CREATE barnbbeginlab AS QLABEL
        Top = 60
        Caption = "Begin at bar #:"
    END CREATE
    CREATE barnbbeginedit AS QEDIT
        Top = 60
        Left = barnbbeginlab.Left + barnbbeginlab.Width
        Width = 50
        Text = "2"
    END CREATE

    CREATE reversebarscomputebtn AS QBUTTON
        Top = 90
        Caption = "Compute"
        OnClick = reversebarscomputesub
    END CREATE

    CREATE priceratiolab AS QLABEL
        Top = 130
        Caption = "Price ratio:"
    END CREATE

    CREATE priceratioedit AS QEDIT
        Top = 130
        Left = priceratiolab.Left + priceratiolab.Width + 5
        Text = "1"
    END CREATE

    CREATE priceratiobutton AS QBUTTON
        Top = 130
        Left = priceratioedit.Left + priceratioedit.Width + 5
        Caption = "OK"
        OnClick = changepriceratiosub
    END CREATE

END CREATE

SUB exp10sub
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    DIM i AS INTEGER
    DIM j AS INTEGER
    'chartbars(displayedfile)=chartbarstmp(displayedfile)
    'dim j as integer
    'dim high as double
    'dim low as double
    'dim vol as integer
    'dim lines as integer
    'lines=1

    IF alltimehigh >= 1000 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 0.01)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 0.01)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 0.01)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 0.01)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF

    IF alltimehigh >= 300 AND alltimehigh < 1000 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 0.1 * 0.3)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 0.1 * 0.3)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 0.1 * 0.3)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 0.1 * 0.3)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF

    IF alltimehigh >= 100 AND alltimehigh < 300 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 0.1)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 0.1)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 0.1)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 0.1)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF

    IF alltimehigh >= 10 AND alltimehigh < 100 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 0.3)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 0.3)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 0.3)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 0.3)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF

    IF alltimehigh >= 6 AND alltimehigh < 10 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 3)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 3)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 3)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 3)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF
    
    IF alltimehigh >= 4 AND alltimehigh < 6 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 5)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 5)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 5)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 5)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF
    
    IF alltimehigh >= 3 AND alltimehigh < 4 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 7)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 7)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 7)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 7)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF
    
    IF alltimehigh >= 2 AND alltimehigh < 3 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 10)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 10)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 10)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 10)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF
    
    IF alltimehigh >= 1.3 AND alltimehigh < 2 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 15)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 15)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 15)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 15)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF
    
    IF alltimehigh >= 1.1 AND alltimehigh < 1.3 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 23)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 23)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 23)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 23)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF
    
    IF alltimehigh >= 1 AND alltimehigh < 1.1 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 27)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 27)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 27)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 27)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF
    
    IF alltimehigh >= 0.9 AND alltimehigh < 1 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 30)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 30)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 30)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 30)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF
    
    IF alltimehigh >= 0.8 AND alltimehigh < 0.9 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 33)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 33)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 33)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 33)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF
    
    IF alltimehigh >= 0.7 AND alltimehigh < 0.8 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 37)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 37)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 37)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 37)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF
    
    IF alltimehigh > 0 AND alltimehigh < 0.7 THEN
        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 42)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 42)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 42)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 42)
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
        NEXT i
    END IF

    writealive

    FOR i = 1 TO chartbars(displayedfile)
        'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
        'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
        Grid.Cell(rowgridoffset + 3 , i) = STR$(exp10(VAL(Grid.Cell(rowgridoffset + 3 , i))))
        Grid.Cell(rowgridoffset + 4 , i) = STR$(exp10(VAL(Grid.Cell(rowgridoffset + 4 , i))))
        Grid.Cell(rowgridoffset + 5 , i) = STR$(exp10(VAL(Grid.Cell(rowgridoffset + 5 , i))))
        Grid.Cell(rowgridoffset + 6 , i) = STR$(exp10(VAL(Grid.Cell(rowgridoffset + 6 , i))))
        'Grid.Cell(rowgridoffset+7,i)=str$(exp10(val(Grid.Cell(rowgridoffset+7,i))))
        'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
    NEXT i

    writealive


    DIM graphvi AS INTEGER
    alltimehigh = 0
    FOR graphvi = 1 TO chartbars(displayedfile)
        IF VAL(Grid.Cell(rowgridoffset + 4 , graphvi)) > alltimehigh THEN
            alltimehigh = VAL(Grid.Cell(rowgridoffset + 4 , graphvi))
        END IF
    NEXT graphvi
    'for graphvi=1 to chartbars(displayedfile)
    'if val(Grid.cell(rowgridoffset+4,graphvi))=alltimehigh then
    'exit for
    'end if
    'next graphvi

    writealive

    DIM athtmp AS DOUBLE
    athtmp = alltimehigh
    DIM tensinc AS INTEGER
    tensinc = 0

    WHILE INSTR(STR$(athtmp) , "E") > 0
        athtmp = athtmp / 10
        tensinc ++
    WEND

    writealive

    FOR j = 1 TO tensinc + 5

        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) / 10)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) / 10)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) / 10)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) / 10)
            'Grid.Cell(rowgridoffset+7,i)=str$(exp10(val(Grid.Cell(rowgridoffset+7,i))))
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)

        NEXT i

        writealive

    NEXT j

    alltimehigh = 0
    FOR graphvi = 1 TO chartbars(displayedfile)
        IF VAL(Grid.Cell(rowgridoffset + 4 , graphvi)) > alltimehigh THEN
            alltimehigh = VAL(Grid.Cell(rowgridoffset + 4 , graphvi))
        END IF
    NEXT graphvi
    athtmp = alltimehigh
    tensinc = 0

    writealive

    WHILE INSTR(STR$(athtmp) , ".") > 0

        athtmp = athtmp * 10
        tensinc ++

    WEND

    writealive

    FOR j = 1 TO tensinc

        FOR i = 1 TO chartbars(displayedfile)
            'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
            'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
            Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * 10)
            Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * 10)
            Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * 10)
            Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * 10)
            'Grid.Cell(rowgridoffset+7,i)=str$(exp10(val(Grid.Cell(rowgridoffset+7,i))))
            'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)

        NEXT i

        writealive

    NEXT j


    IF LEN(STR$(athtmp)) > 5 THEN

        DIM tensdec AS INTEGER
        tensdec = LEN(STR$(athtmp)) - 5

        FOR j = 1 TO tensdec

            FOR i = 1 TO chartbars(displayedfile)
                'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
                'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
                Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) / 10)
                Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) / 10)
                Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) / 10)
                Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) / 10)
                'Grid.Cell(rowgridoffset+7,i)=str$(exp10(val(Grid.Cell(rowgridoffset+7,i))))
                'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)

            NEXT i

            writealive

        NEXT j

    END IF


    'chartbars(displayedfile)=lines-1
    'print chartbars(displayedfile)
    'Scrollchart.Max=chartbars(displayedfile)
    'Scrollchart.Position=chartbars(displayedfile)
    'chartstart=Scrollchart.Position-numbars
    'btnOnClick(drwBox)
    'justrefreshchart
'DIM Mem AS QMemoryStream
'   dim datavalstr as string
'   for j=3 to 6
'       rowgridoffsetstr=str$(rowgridoffset + j)            
'       
'       FOR i = 1 TO chartbars(displayedfile)
'           offsetstr=str$(i)
'           'datavalstr=StrF$(val(Grid.Cell(rowgridoffset + j , i)),ffFixed,15,15)
'           datavalstr = Grid.Cell(rowgridoffset + j , i)
'           Mem.WriteStr(datavalstr,len(datavalstr))
'           Mem.Position = 0
'           'datavalstr = Mem.ReadStr(LEN(datavalstr))
'           cpptmpfuncreturn=varptr$(setdatagrid(varptr(rowgridoffsetstr),varptr(offsetstr),Mem.pointer)) 
'   
'       next i        
'   next j
'em.Close
    exportfilename()
    btnOnClick(drwBox)

END SUB

SUB changepriceratiosub
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    DIM i AS INTEGER
    'chartbars(displayedfile)=chartbarstmp(displayedfile)
    'dim j as integer
    'dim high as double
    'dim low as double
    'dim vol as integer
    'dim lines as integer
    'lines=1
    FOR i = 1 TO chartbars(displayedfile)
        'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
        'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
        Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * VAL(priceratioedit.Text))
        Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * VAL(priceratioedit.Text))
        Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * VAL(priceratioedit.Text))
        Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * VAL(priceratioedit.Text))
        'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
    NEXT i


    'chartbars(displayedfile)=lines-1
    'print chartbars(displayedfile)
    'Scrollchart.Max=chartbars(displayedfile)
    'Scrollchart.Position=chartbars(displayedfile)
    'chartstart=Scrollchart.Position-numbars
    'btnOnClick(drwBox)
    justrefreshchart
END SUB

SUB changepriceratiosub2
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    DIM i AS INTEGER
    'chartbars(displayedfile)=chartbarstmp(displayedfile)
    'dim j as integer
    'dim high as double
    'dim low as double
    'dim vol as integer
    'dim lines as integer
    'lines=1
    FOR i = 1 TO chartbars(displayedfile)
        'Grid.Cell(rowgridoffset+1,i)=str$(val(Grid.Cell(rowgridoffset+1,i)))
        'Grid.Cell(rowgridoffset+2,i)=Gridtmp.Cell(rowgridoffset+2,i)
        Grid.Cell(rowgridoffset + 3 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 3 , i)) * VAL(priceratioedit2.Text))
        Grid.Cell(rowgridoffset + 4 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 4 , i)) * VAL(priceratioedit2.Text))
        Grid.Cell(rowgridoffset + 5 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 5 , i)) * VAL(priceratioedit2.Text))
        Grid.Cell(rowgridoffset + 6 , i) = STR$(VAL(Grid.Cell(rowgridoffset + 6 , i)) * VAL(priceratioedit2.Text))
        'Grid.Cell(rowgridoffset+7,i)=Gridtmp.Cell(rowgridoffset+7,i)
    NEXT i


    'chartbars(displayedfile)=lines-1
    'print chartbars(displayedfile)
    'Scrollchart.Max=chartbars(displayedfile)
    'Scrollchart.Position=chartbars(displayedfile)
    'chartstart=Scrollchart.Position-numbars
    'btnOnClick(drwBox)
    justrefreshchart
    say "Price ratio set to: "+priceratioedit2.Text
END SUB


CREATE indicatorsform AS QFORM
    Width = 250
    Height = 300
    Center
    Caption = "Indicators"

    CREATE indicatorslab AS QLABEL
        Left = 0
        Top = 0
        Caption = "Indicators:"
    END CREATE

    CREATE indicatorslist AS QLISTBOX
        Left = 0
        Top = 20
        Height = 150
        Width = indicatorsform.Width - 20
        OnDblClick = indilist_dblclick
    END CREATE

    CREATE indicatorslistsel AS QLISTBOX
        Visible = 0
        Left = indicatorsform.Width - 25
        Top = 20
        Height = 80
        Width = 15
    END CREATE

    CREATE btnaddindi AS QBUTTON
        Left = 0
        Width = 90
        Top = indicatorslist.Top + 150
        Caption = "Add indicator"
        OnClick = btnaddindi_click
    END CREATE

    CREATE btnremoveindi AS QBUTTON
        Left = 90
        Width = 90
        Top = indicatorslist.Top + 150
        Caption = "Remove indicator"
        OnClick = btndelindi_click
    END CREATE

    CREATE btnsettingsindi AS QBUTTON
        Left = 0
        Width = 90
        Top = btnaddindi.Top + btnaddindi.Height
        Caption = "Properties"
        OnClick = settingsclick
    END CREATE

    CREATE btndescrindi AS QBUTTON
        Left = btnsettingsindi.Width
        Width = 30
        Top = btnaddindi.Top + btnaddindi.Height
        Caption = "?"
        OnClick = showdescrindi
    END CREATE

    CREATE btnokindi AS QBUTTON
        Left = btndescrindi.Width + btndescrindi.Left
        Width = 30
        Top = btnaddindi.Top + btnaddindi.Height
        Caption = "OK"
        OnClick = refresh_chart
    END CREATE

    CREATE autoadjustsepindi AS QCHECKBOX
        Left = 10
        Width = 200
        Top = btnokindi.Top + btnokindi.Height
        Caption = "Auto adjust indicators in canvas"
        Checked = 1
    END CREATE

END CREATE

useindi.Parent = indicatorsform

useindi.Left = 10
useindi.Width = 200
useindi.Top = autoadjustsepindi.Top + autoadjustsepindi.Height
useindi.Caption = "Use indicators"
useindi.Checked = 0
useindi.OnClick = useindisub    

create swephform as qform

    height=600
    width=600
    onshow=swephformonshowsub

    create logo_label as qlabel
        caption="Swiss Ephemeris"
    end create

    create et_flag as qcheckbox
        caption="Ephemeris time"
        checked=1
        left=100
    end create
    
    create is_apparent as qcheckbox
        caption="apparent pos."
        checked=1
        top=20
        left=100
    end create
    
    create is_sidereal as qcheckbox
        caption="sidereal"
        top=40
        left=100
    end create
    
    create hel_flag as qcheckbox
        caption="heliocentric"
        top=0
        left=200
        onclick=hel_flag_Click
    end create
    
    create bary_flag as qcheckbox
        caption="barycentric"
        top=20
        left=200
        onclick=bary_flag_Click
    end create
    
    create is_j2000 as qcheckbox
        caption="Equinox J2000"
        top=40
        left=200
    end create
    
    create add_hypo as qcheckbox
        caption="with hypothetical bodies"
        top=0
        left=300
    end create
    
    create with_houses as qcheckbox
        caption="with Placidus houses"
        top=20
        left=300
    end create
    
    create geolon as qedit
        text="8.00"
        top=40
        left=300
        width=50
        onchange=geolon_change
    end create
    
    create geolat as qedit
        text="47.00"
        top=40
        left=350
        width=50
        onchange=geolat_change
    end create
    
    create day_label as qlabel
        caption="Day"
        top=60
        left=0
    end create
    
    create Day as qedit
        text="1"
        top=80
        left=0
        width=50
        onchange=Day_Change
    end create
    
    create month_label as qlabel
        caption="Month"
        top=60
        left=50
    end create
    
    create Month as qedit
        text="1"
        top=80
        left=50
        width=50
        onchange=month_change
    end create
    
    create year_label as qlabel
        caption="Year"
        top=60
        left=100
    end create
    
    create Year as qedit
        text="1997"
        top=80
        left=100
        width=50
        onchange=year_change
    end create
    
    create hour_label as qlabel
        caption="Hour"
        top=60
        left=150
    end create
    
    create hour as qedit
        text="00"
        top=80
        left=150
        width=50
        onchange=hour_change
    end create
    
    create min_label as qlabel
        caption="Min."
        top=60
        left=200
    end create
    
    create minute as qedit
        text="00"
        top=80
        left=200
        width=50
        onchange=minute_change
    end create
    
    create fixed_star_label as qlabel
        caption="fixed star"
        top=60
        left=250
    end create
    
    create fstar as qedit
        text=""
        top=80
        left=250
        width=80
        onchange=fstar_change
    end create
    
    create Compute as qbutton
        caption="Compute!"
        top=80
        left=350
        onclick=Compute_sweph_Click
    end create
    
    create swephout as qrichedit
        top=120
        left=0
        width=400
        height=400
        scrollbars=2
    end create

end create

CREATE chatform AS QFORM
    Width = 530
    Height = 400
    Center
    Caption = "Chat"
    visible=0
    onshow=chatformonshowsub
    onclose=chatformonclosesub
    
    create usernamelbl as qlabel
    top=0
    caption="Username:"
    width=100
    end create
    create usernameedit as qedit
    top=0
    left=usernamelbl.width
    end create
    create chatbox as qrichedit
    top=usernameedit.height
    left=0
    width=350
    height=300
    scrollbars=ssboth
    end create
    create usernameslist as qlistbox
    top=chatbox.top
    left=chatbox.width
    height=300
    width=150
    end create
    create sendmsgedit as qedit
    top=chatbox.height+usernameedit.height
    left=0
    width=450
    onkeydown=sendmsgeditkeydown
    end create
    create sendmsgbtn as qbutton
    top=sendmsgedit.top
    left=sendmsgedit.width
    width=50
    caption="Send"
    onclick=sendmsgbtnonclicksub
    end create
    
END CREATE

CREATE speechform AS QFORM
    Width = 250
    Height = 300
    Center
    Caption = "Speech settings"
    visible=0
    
    create usespeech as qcheckbox
    caption="Use speech engine"
    width=150
    checked=0
    onclick=checkusespeech
    end create
    
    
END CREATE

SUB useindisub
    IF useindi.Checked = 0 THEN
        useindischeckbox.Checked = 0
        EXIT SUB
    END IF
    IF useindi.Checked = 1 THEN
        useindischeckbox.Checked = 1
        EXIT SUB
    END IF
END SUB

DIM indilisti AS INTEGER
DIM indicanvascount() AS INTEGER
DIM countcanvas AS INTEGER
FOR indilisty = 0 TO 10
    countcanvas = 0
    FOR indilisti = 0 TO UBOUND(indinames)
        IF VAL(indicanvas(indilisti)) = indilisty THEN
            indicatorslist.AddItems indinames(indilisti) + " ( )"
            countcanvas ++
        END IF
    NEXT indilisti
    indicanvascount(indilisty) = countcanvas
NEXT i

SUB showdescrindi
    if showdescindopened=0 then
    showdescindopened=1

    FOR nli = 0 TO indiinilist.ItemCount - 1
        'qtcfile.open(indiinilist.Item(nli) , fmOpenRead)
        'indicanvas(nli) = qtcfile.ReadLine() 'Read an entire line
        indiini.filename=homepath+"\indicators\"+indiinilist.Item(nli)
        indiini.section="Settings"
        indicanvas(nli)=indiini.get("canvas","")
    NEXT nli
    'qtcfile.close
    'DIM descrmsg AS STRING
    'DIM indidesc(0 TO indiinilist.ItemCount - 1) AS STRING
    'DIM indilisty AS INTEGER
    'DIM nld AS INTEGER
    'DIM descordercount AS INTEGER
    descordercount = 0
    'DIM descfile AS QFILESTREAM
    FOR indilisty = 0 TO 1
        FOR nld = 0 TO indiinilist.ItemCount - 1
            IF VAL(indicanvas(nld)) = indilisty THEN
                'descfile.open(indiinilist.Item(nld) , fmOpenRead)
                'indidesc(descordercount) = descfile.ReadLine() 'Read an entire line
                indiini.filename=homepath+"\indicators\"+indiinilist.Item(nld)
                indiini.section="Settings"
                indidesc(descordercount)=indiini.get("description","")
                descordercount ++
            END IF
        NEXT nld
    NEXT indilisty
    'descfile.close
    end if
    if hidedescindmsgbox=0 then
        MESSAGEDLG(txtformat(indidesc(indicatorslist.ItemIndex)) , 2 , 4 , 0)
    end if
END SUB

'-====================================== Indicators Properties forms =============================================-

'Indexing indicators

DIM qtpList AS QFILELISTBOX
qtpList.Visible = 0
qtpList.Parent = frmMain
qtpList.Mask = "*.qtp"
qtpList.Directory = homepath + "\indicators"

SUB hideformp(frmname AS QFORM)
    frmname.Visible = 0
END SUB

SUB showformp(frmname AS QFORM)
    frmname.Visible = 1
END SUB

$include "includes\includeqtp.inc"

$include "includes\includeset.inc"

'sub settingsclick
'select case indicatorslist.itemindex

'case 0
'maform.visible=1
'case 4
'bbhlform.visible=1
'case 5
'atrchannelform.visible=1
'case 3
'vegasform.visible=1
'case 8
'pricecloseform.visible=1
'case 2
'mfiform.visible=1
'case 9
'atrform.visible=1
'case 10
'valuechartform.visible=1
'case 1
'bandsform.visible=1
'case 6
'averagerangeform.visible=1
'case 7
'cogform.visible=1
'case 11
'spectrometerform.visible=1
'case 12
'vcatrcform.visible=1

'end select
'end sub

'-====================================== END SETTINGS FORMS =============================================-

'-====================================== INDICATORS SCRIPTS =============================================-

$include "includes\includeqti.inc"

'dim vo2(0 to 1000) as double,vh2(0 to 1000) as double,vb2(0 to 1000) as double,vc2(0 to 1000) as double
'dim valuechart2levelup1(0 to 1000) as integer,valuechart2levelup2(0 to 1000) as integer
'dim valuechart2leveldn1(0 to 1000) as integer,valuechart2leveldn2(0 to 1000) as integer
'dim p2 as integer
'p2=5


'-====================================== END INDICATORS SCRIPTS =============================================-

SUB disableallindis
    DIM indilisti AS INTEGER
    FOR indilisti = 0 TO indicatorslist.ItemCount
        indicatorslistsel.Item(indilisti) = ""
        indicatorslist.Item(indilisti) = MID$(indicatorslist.Item(indilisti) , 0 , LEN(indicatorslist.Item(indilisti)) - 2)
        indicatorslist.Item(indilisti) = indicatorslist.Item(indilisti) + " )"
    NEXT indilisti
    'useindischeckbox.checked=0
END SUB

FUNCTION txtformat(descrmsg AS STRING) AS STRING
    DIM txtf AS STRING
    txtf = ""
    DIM i AS INTEGER
    FOR i = 1 TO LEN(descrmsg) STEP 40
        txtf = txtf + MID$(descrmsg , i , 40) + CHR$(10)
    NEXT i
    txtformat = txtf
END FUNCTION

DIM indil AS INTEGER
FOR indil = 1 TO indicatorslist.ItemCount
    indicatorslistsel.AddItems ""
NEXT indil

SUB refresh_chart()
    indicatorsform.Visible = 0
    IF openedfilesnb > 0 THEN
        disablescrollmode
        btnOnClick(drwBox) ' need to put this for WineHQ compatibility, else the screen does not update correctly (but this slows down computations)
    END IF
END SUB


SUB refresh_chartlive()
    Scrollchart.Max = chartbars(displayedfile)
    Scrollchart.Position = chartbars(displayedfile)
    chartstart = Scrollchart.Position - numbars
    btnOnClick(drwBox)
END SUB


SUB indiform()
    indicatorsform.Visible = 1
    indicatorsform.WindowState = 0
    SetFocus(indicatorsform.Handle)
END SUB

SUB mixerform()
    additionlist.Clear
    subtractionlist.Clear
    multiplylist.Clear
    dividelist.Clear
    DIM i AS INTEGER
    FOR i = 0 TO mixgrid.ColCount
        additionlist.AddItems mixgrid.Cell(i , displayedfile)
    NEXT i
    FOR i = 0 TO mixgrid2.ColCount
        subtractionlist.AddItems mixgrid2.Cell(i , displayedfile)
    NEXT i
    FOR i = 0 TO mixgrid3.ColCount
        multiplylist.AddItems mixgrid3.Cell(i , displayedfile)
    NEXT i
    FOR i = 0 TO mixgrid4.ColCount
        dividelist.AddItems mixgrid4.Cell(i , displayedfile)
    NEXT i
    mixform.Visible = 1
    mixform.WindowState = 0
    SetFocus(mixform.Handle)
END SUB

SUB updatemixerlists()
    additionlist.Clear
    subtractionlist.Clear
    multiplylist.Clear
    dividelist.Clear
    DIM i AS INTEGER
    FOR i = 0 TO mixgrid.ColCount
        additionlist.AddItems mixgrid.Cell(i , displayedfile)
    NEXT i
    FOR i = 0 TO mixgrid2.ColCount
        subtractionlist.AddItems mixgrid2.Cell(i , displayedfile)
    NEXT i
    FOR i = 0 TO mixgrid3.ColCount
        multiplylist.AddItems mixgrid3.Cell(i , displayedfile)
    NEXT i
    FOR i = 0 TO mixgrid4.ColCount
        dividelist.AddItems mixgrid4.Cell(i , displayedfile)
    NEXT i
END SUB

SUB btnaddindi_click()
    indicatorslistsel.Item(indicatorslist.ItemIndex) = "x"
    indicatorslist.Item(indicatorslist.ItemIndex) = MID$(indicatorslist.Item(indicatorslist.ItemIndex) , 0 , LEN(indicatorslist.Item(indicatorslist.ItemIndex)) - 2)
    indicatorslist.Item(indicatorslist.ItemIndex) = indicatorslist.Item(indicatorslist.ItemIndex) + "X)"
    IF useindi.Checked = 0 THEN
        useindi.Checked = 1
    END IF
    IF useindischeckbox.Checked = 0 THEN
        useindischeckbox.Checked = 1
    END IF
END SUB

SUB btndelindi_click()
    indicatorslistsel.Item(indicatorslist.ItemIndex) = ""
    indicatorslist.Item(indicatorslist.ItemIndex) = MID$(indicatorslist.Item(indicatorslist.ItemIndex) , 0 , LEN(indicatorslist.Item(indicatorslist.ItemIndex)) - 2)
    indicatorslist.Item(indicatorslist.ItemIndex) = indicatorslist.Item(indicatorslist.ItemIndex) + " )"
END SUB

SUB indilist_dblclick
    IF indicatorslistsel.Item(indicatorslist.ItemIndex) = "" THEN
        btnaddindi_click()
        EXIT SUB
    END IF
    IF indicatorslistsel.Item(indicatorslist.ItemIndex) = "x" THEN
        btndelindi_click()
        EXIT SUB
    END IF
END SUB

SUB Buttonf2Click(Sender AS QBUTTON)
    Form2.Visible = 0
    importfile()

END SUB


SUB showtoolsinfo
    formtoolsinfo.Visible = 1
    formtoolsinfo.WindowState = 0
    'setfocus(formtoolsinfo.handle)
    SetFocus(frmMain.Handle)
END SUB

SUB formtoolsinforesized
    infotext.Width = formtoolsinfo.Width - 10
    infotext.Height = 0.5 * (formtoolsinfo.Height - 30)
    infotext2.Top = formtoolsinfo.Height / 2.2
    infotext2.Width = formtoolsinfo.Width - 10
    infotext2.Height = 0.5 * (formtoolsinfo.Height - 30)
END SUB

SUB dispinfotext(infotxt AS STRING)
    infotext.Text = infotxt
END SUB

SUB choosepencolor
    IF colordlg.Execute THEN
        pencolor = colordlg.Color
        pencolorbtn.Color = colordlg.Color
    END IF
END SUB

SUB chooseplotareacolor
    IF colordlg.Execute THEN
        plotareacolor = colordlg.Color
        btnOnClick(drwBox)
        'pencolorbtn.color=colordlg.Color
    END IF
END SUB

SUB choosemailer
    MailForm.Visible = 1
END SUB

SUB choosetextfont
    FontDialog.GetFont(Font)
    IF FontDialog.Execute THEN
        'ShowMessage "You selected "+FontDialog.Name
        'font.name=FontDialog.Name
        'font.size=FontDialog.size
        FontDialog.SetFont(Font)
    END IF
    Font.Name = FontDialog.Name
    Font.Size = FontDialog.Size
    Font.Color = FontDialog.Color
    Graph.buffer.Font.Name = Font.Name
    Graph.buffer.Font.Size = Font.Size
    canvas.BMP.Font.Name = Font.Name
    canvas.BMP.Font.Size = Font.Size
    textcolor = Font.Color
END SUB

'API Call that lets RapidQ programs minimize to the task bar
setwindowlong(frmMain.Handle , GWL_HWNDPARENT , HWND_DESKTOP)
setwindowlong(application.Handle , GWL_HWNDPARENT , frmMain.Handle)
Graph.ClearAll
canvas.ClearAll2
hidedescindmsgbox=1
showdescrindi
hidedescindmsgbox=0

frmMain.ShowModal

'---------------------------------------------------------------------
'Unregister hotkeys
'UnRegisterHotKey(frmmain.Handle, 0)
'UnRegisterHotKey(hotkeysfrm.Handle, 1)
'
'SUB FormWndProc (hWnd&, uMsg&, wParam&, lParam&)
'IF uMsg& = WM_HOTKEY THEN
''SetForeGroundWindow(hWnd&)
''ShowMessage("Hotkey "+STR$(wParam&)+" hit!")
'if (STR$(wParam&)="0") then
'graphmousedown(1)
'sepindimousedown(1)
'end if

'if (STR$(wParam&)="0") then
'graphclicked
'sepindiclicked
'end if
'
'END IF
'END SUB
'-----------------------------------------------------------------------

'dim qtnnoext as string
'for qtpi=0 to qtplist.itemcount-1
'qtnnoext= mid$( indiinilist.item(qtpi),0,instr(indiinilist.item(qtpi),".")-1 )
'next qtpi

$include "includes\includebtnonclick.inc"

SUB scrollmodeoff
    scrollmodeofftimer.Enabled = FALSE
    IF scrollmodebtn.Flat = 1 THEN
        disablescrollmode
    END IF
END SUB

SUB frmMainResize(SENDER AS QFORM)

    '----- Prevent initial resize exception
    IF AppStart THEN AppStart = FALSE  :  EXIT SUB

    'de.bug "Resize"
    WITH Graph
        .Width = frmMain.ClientWidth - leftwidth  'Calculate new sizes
        .Height = frmMain.ClientHeight - sepindiheight + 130
        .RedrawChart  'Redraw the QChart Object
    END WITH
    split.Top = Graph.Height + 70

    WITH canvas
        .Width = frmMain.ClientWidth - leftwidth - 60  'Calculate new sizes
        .Height = frmMain.ClientHeight  '+val(sepindiheight.text)-130
        .RedrawChart2  'Redraw the QChart Object
    END WITH

    'Plus anything else that needs doing in your form resize

END SUB

'-------------------------------------------------------------------------------------------
SUB frmMainClose(SENDER AS QFORM)

IF usespeech.checked=1 THEN speechdeinitialization     ' CleanUp the Speech (De-Initialize/Un-Initialize).

    Application.Terminate

END SUB

'-------------------------------------------------------------------------------------------

SUB exportfile()
    DIM SaveDialog AS QSAVEDIALOG
    SaveDialog.Caption = "Export Graph"
    SaveDialog.Filter = "CSV File|*.csv"
    SaveDialog.FilterIndex = 1
    SaveDialog.FileName = MID$(importedfile(displayedfile) , 0 , LEN(importedfile(displayedfile)) - 4) + "x" + tfmult.Text + ".csv"

    IF SaveDialog.Execute THEN
        DIM csvFile AS QFILESTREAM
        csvFile.open(SaveDialog.FileName , 65535) '65535 = fmCreate
        DIM csvi AS INTEGER
        DIM datecsv AS STRING
        DIM timecsv AS STRING
        DIM opencsv AS STRING
        DIM highcsv AS STRING
        DIM lowcsv AS STRING
        DIM closecsv AS STRING
        DIM volumecsv AS STRING

        SELECT CASE axistypecomboitemindex
            CASE 0 :
                FOR csvi = 1 TO chartbars(displayedfile) 'val(csvbars)
                    datecsv = Grid.Cell(rowgridoffset + 1 , csvi)
                    timecsv = Grid.Cell(rowgridoffset + 2 , csvi)
                    opencsv = Grid.Cell(rowgridoffset + 3 , csvi)
                    highcsv = Grid.Cell(rowgridoffset + 4 , csvi)
                    lowcsv = Grid.Cell(rowgridoffset + 5 , csvi)
                    closecsv = Grid.Cell(rowgridoffset + 6 , csvi)
                    volumecsv = Grid.Cell(rowgridoffset + 7 , csvi)
                    csvFile.WriteLine(datecsv + "," + timecsv + "," + opencsv + "," + highcsv + "," + lowcsv + "," + closecsv + "," + volumecsv)
                NEXT csvi
            CASE 1 :
                FOR csvi = 1 TO chartbars(displayedfile) 'val(csvbars)
                    datecsv = Grid.Cell(rowgridoffset + 1 , csvi)
                    timecsv = Grid.Cell(rowgridoffset + 2 , csvi)
                    opencsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 3 , csvi))) , ffGeneral , 4 , 4)
                    highcsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 4 , csvi))) , ffGeneral , 4 , 4)
                    lowcsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 5 , csvi))) , ffGeneral , 4 , 4)
                    closecsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 6 , csvi))) , ffGeneral , 4 , 4)
                    volumecsv = ROUND(log10(VAL(Grid.Cell(rowgridoffset + 7 , csvi))))
                    csvFile.WriteLine(datecsv + "," + timecsv + "," + opencsv + "," + highcsv + "," + lowcsv + "," + closecsv + "," + volumecsv)
                NEXT csvi
        END SELECT
        csvFile.close
    END IF
END SUB

SUB exportfilename()
    'DIM SaveDialog AS QSAVEDIALOG
    'SaveDialog.Caption = "Export Graph"
    'SaveDialog.Filter = "CSV File|*.csv"
    'SaveDialog.FilterIndex = 1    
    'SaveDialog.FileName = homepath+"\csv\temp.csv"
    dim savedialogfilename as string
    savedialogfilename=homepath+"\csv\temp.csv"

    'IF SaveDialog.Execute THEN
        DIM csvFile AS QFILESTREAM
        csvFile.open(savedialogfilename , 65535) '65535 = fmCreate
        DIM csvi AS INTEGER
        DIM datecsv AS STRING
        DIM timecsv AS STRING
        DIM opencsv AS STRING
        DIM highcsv AS STRING
        DIM lowcsv AS STRING
        DIM closecsv AS STRING
        DIM volumecsv AS STRING
        'DIM inputcsvbars AS qinputbox
        'dim csvbars as string
        'csvbars=inputcsvbars.input("How many bars to export?")
        SELECT CASE axistypecomboitemindex
            CASE 0 :
                FOR csvi = 1 TO chartbars(displayedfile) 'val(csvbars)
                    datecsv = Grid.Cell(rowgridoffset + 1 , csvi)
                    timecsv = Grid.Cell(rowgridoffset + 2 , csvi)
                    opencsv = Grid.Cell(rowgridoffset + 3 , csvi)
                    highcsv = Grid.Cell(rowgridoffset + 4 , csvi)
                    lowcsv = Grid.Cell(rowgridoffset + 5 , csvi)
                    closecsv = Grid.Cell(rowgridoffset + 6 , csvi)
                    volumecsv = Grid.Cell(rowgridoffset + 7 , csvi)
                    csvFile.WriteLine(datecsv + "," + timecsv + "," + opencsv + "," + highcsv + "," + lowcsv + "," + closecsv + "," + volumecsv)
                NEXT csvi
            CASE 1 :
                FOR csvi = 1 TO chartbars(displayedfile) 'val(csvbars)
                    datecsv = Grid.Cell(rowgridoffset + 1 , csvi)
                    timecsv = Grid.Cell(rowgridoffset + 2 , csvi)
                    opencsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 3 , csvi))) , ffGeneral , 4 , 4)
                    highcsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 4 , csvi))) , ffGeneral , 4 , 4)
                    lowcsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 5 , csvi))) , ffGeneral , 4 , 4)
                    closecsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 6 , csvi))) , ffGeneral , 4 , 4)
                    volumecsv = ROUND(log10(VAL(Grid.Cell(rowgridoffset + 7 , csvi))))
                    csvFile.WriteLine(datecsv + "," + timecsv + "," + opencsv + "," + highcsv + "," + lowcsv + "," + closecsv + "," + volumecsv)
                NEXT csvi
        END SELECT
        csvFile.close
        $ESCAPECHARS ON
    dim strfilename as string
    strfilename=replacesubstr$(savedialogfilename,chr$(92),chr$(92)+chr$(92))
    'dim strfilenamelines as integer
    'strfilenamelines=filegetlinecount(varptr(strfilename))

'    dim mystr as string
'    dim savmystr(0 to 100000) as string
'    dim iinc as integer
'    iinc=0 
    
'    dim reinitfseek as string:reinitfseek="0"
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
'    iinc++
'    savmystr(iinc)=mystr
'    for i=1 to strfilenamelines
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
'    iinc++
'    savmystr(iinc)=mystr
'    next i
'    reinitfseek="1"
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
    cpptmpfuncreturn=varptr$(filegetlinesarray(varptr(strfilename)))
    $ESCAPECHARS OFF
    'END IF
END SUB

SUB exportfileyahoo()
    DIM SaveDialog AS QSAVEDIALOG
    SaveDialog.Caption = "Export Graph"
    SaveDialog.Filter = "CSV File|*.csv"
    SaveDialog.FilterIndex = 1
    SaveDialog.FileName = MID$(importedfile(displayedfile) , 0 , LEN(importedfile(displayedfile)) - 4) + ".csv"
    'IF SaveDialog.Execute THEN
    
    DIM csvFile AS QFILESTREAM
    csvFile.open(SaveDialog.FileName , 65535) '65535 = fmCreate

    DIM csvi AS INTEGER
    DIM datecsv AS STRING
    DIM timecsv AS STRING
    DIM opencsv AS STRING
    DIM highcsv AS STRING
    DIM lowcsv AS STRING
    DIM closecsv AS STRING
    DIM volumecsv AS STRING
    'dim inputcsvbars as qinputbox
    'dim csvbars as string
    'csvbars=inputcsvbars.input("How many bars to export?")
    SELECT CASE axistypecomboitemindex
        CASE 0 :
            FOR csvi = 1 TO chartbars(displayedfile) 'val(csvbars)
                datecsv = Grid.Cell(rowgridoffset + 1 , csvi)
                timecsv = Grid.Cell(rowgridoffset + 2 , csvi)
                opencsv = Grid.Cell(rowgridoffset + 3 , csvi)
                highcsv = Grid.Cell(rowgridoffset + 4 , csvi)
                lowcsv = Grid.Cell(rowgridoffset + 5 , csvi)
                closecsv = Grid.Cell(rowgridoffset + 6 , csvi)
                volumecsv = Grid.Cell(rowgridoffset + 7 , csvi)
                csvFile.WriteLine(datecsv + "," + timecsv + "," + opencsv + "," + highcsv + "," + lowcsv + "," + closecsv + "," + volumecsv)
            NEXT csvi
        CASE 1 :
            FOR csvi = 1 TO chartbars(displayedfile) 'val(csvbars)
                datecsv = Grid.Cell(rowgridoffset + 1 , csvi)
                timecsv = Grid.Cell(rowgridoffset + 2 , csvi)
                opencsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 3 , csvi))) , ffGeneral , 4 , 4)
                highcsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 4 , csvi))) , ffGeneral , 4 , 4)
                lowcsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 5 , csvi))) , ffGeneral , 4 , 4)
                closecsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 6 , csvi))) , ffGeneral , 4 , 4)
                volumecsv = ROUND(log10(VAL(Grid.Cell(rowgridoffset + 7 , csvi))))
                csvFile.WriteLine(datecsv + "," + timecsv + "," + opencsv + "," + highcsv + "," + lowcsv + "," + closecsv + "," + volumecsv)
            NEXT csvi
    END SELECT
    csvFile.close
    'End if
    'dsok.Enabled = 1
END SUB


SUB importfileyahoo()

    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    form2Edit2.Text = "1"
    form2Edit3.Text = "2"
    form2Edit4.Text = "3"
    form2Edit5.Text = "4"
    form2Edit6.Text = "5"
    form2Edit7.Text = "6"


    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)


    DIM OpenDialog AS QOPENDIALOG
    'OpenDialog.initialdir=homepath+"\csv"'mtpathedit.text
    'IF OpenDialog.Execute THEN

    DIM dstf AS STRING
    SELECT CASE dstimeframe.ItemIndex
        CASE 0 :
            dstf = "1"
        CASE 1 :
            dstf = "5"
        CASE 2 :
            dstf = "15"
        CASE 3 :
            dstf = "30"
        case 4 :
            dstf = "60"
        case 5 :
            dstf = "240"
        case 6 :
            dstf = "1440"
        case 7 :
            dstf = "10080"
        case 8 :
            dstf = "43200"
    END SELECT


    openedfilesnb ++
    openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(openedfilesnbplusone())
    importedfile(openedfilesnb) = homepath + "\csv\" + UCASE$(dssymboledit.Text) + dstf + ".tmp"  'OpenDialog.FileName
    importedfileopenedfilesnbstr=str$(importedfile(openedfilesnb)):openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(setimportedfile(varptr(importedfileopenedfilesnbstr),varptr(openedfilesnbstr)))
    displayedfile = openedfilesnb
    displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setdisplayedfile(varptr(displayedfilestr)))
    mixgrid.Cell(0 , displayedfile) = importedfile(displayedfile)
    mixgridcolcount(displayedfile) = 1
    mixgridcolcount2(displayedfile) = 0
    mixgridcolcount3(displayedfile) = 0
    mixgridcolcount4(displayedfile) = 0
    IF openedfilesnb > 1 THEN
        rowgridoffset = 7 * (openedfilesnb - 1)
        rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
    END IF
    dispchartnb.AddItems STR$(displayedfile)
    dispchartnb.ItemIndex = openedfilesnb - 1
    'END IF
    'if FileExists(OpenDialog.FileName) = FALSE THEN
    'print " file not found "
    'exit sub
    'end if

     dim yhooarrtmp(0 TO 100000) as string
     DIM file AS QFILESTREAM,yincr as integer
     file.open(importedfile(displayedfile) , 0)
     yincr=-1
     DO
         yincr++
         yhooarrtmp(yincr) = file.ReadLine
     LOOP UNTIL file.eof
     file.close
     
     file.open(importedfile(displayedfile) , 65535)
     dim yincr2 as integer
     for yincr2=1 to yincr
          
         file.writeline(yhooarrtmp(yincr2))
     next yincr2
     file.close

    
    $ESCAPECHARS ON
    dim strfilename as string
    strfilename=replacesubstr$(importedfile(displayedfile),chr$(92),chr$(92)+chr$(92))
    dim strfilenamelines as integer
    strfilenamelines=filegetlinecount(varptr(strfilename))
    'dim i as integer
    dim mystr as string
    dim savmystr(0 to 100000) as string
    dim iinc as integer
    iinc=0 

    dim reinitfseek as string:reinitfseek="0"
    'openedfilesnbstr=str$(openedfilesnb)
    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
    iinc++
    savmystr(iinc)=mystr
    for i=1 to strfilenamelines
    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
    iinc++
    savmystr(iinc)=mystr
    next i
    reinitfseek="1"
    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))    
    $ESCAPECHARS OFF

    j = 0

    DO

        j ++

        'getline$ = file.ReadLine
        getline$ = savmystr(j)

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        'commapos = 0
        'FOR i = 1 TO timepos - 1
        '    IF timepos = 1 THEN
        '        EXIT FOR
        '    END IF
        '    commapos = INSTR(commapos + 1 , getline$ , separator)
        'NEXT i
        'time = MID$(getline$ , commapos + 1 , LEN(getline$))
        'time = MID$(time , 0 , INSTR(0 , time , separator) - 1)
        time = "00:00"

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)

        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        vol = MID$(vol , 0 , INSTR(0 , vol , separator) - 1)

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open
        Grid.Cell(rowgridoffset + 4 , j) = high
        Grid.Cell(rowgridoffset + 5 , j) = low
        Grid.Cell(rowgridoffset + 6 , j) = close
        Grid.Cell(rowgridoffset + 7 , j) = vol


        Gridtmp.Cell(rowgridoffset + 1 , j) = date
        Gridtmp.Cell(rowgridoffset + 2 , j) = time
        Gridtmp.Cell(rowgridoffset + 3 , j) = open
        Gridtmp.Cell(rowgridoffset + 4 , j) = high
        Gridtmp.Cell(rowgridoffset + 5 , j) = low
        Gridtmp.Cell(rowgridoffset + 6 , j) = close
        Gridtmp.Cell(rowgridoffset + 7 , j) = vol

    LOOP UNTIL j=strfilenamelines
    'file.close
 
    chartbars(displayedfile) = j
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))

    DIM o AS INTEGER
    o = 1
    FOR i = chartbars(displayedfile) TO 1 STEP - 1
        Grid.Cell(rowgridoffset + 1 , i) = Gridtmp.Cell(rowgridoffset + 1 , o)
        Grid.Cell(rowgridoffset + 2 , i) = Gridtmp.Cell(rowgridoffset + 2 , o)
        Grid.Cell(rowgridoffset + 3 , i) = Gridtmp.Cell(rowgridoffset + 3 , o)
        Grid.Cell(rowgridoffset + 4 , i) = Gridtmp.Cell(rowgridoffset + 4 , o)
        Grid.Cell(rowgridoffset + 5 , i) = Gridtmp.Cell(rowgridoffset + 5 , o)
        Grid.Cell(rowgridoffset + 6 , i) = Gridtmp.Cell(rowgridoffset + 6 , o)
        Grid.Cell(rowgridoffset + 7 , i) = Gridtmp.Cell(rowgridoffset + 7 , o)
        o ++
    NEXT i
    FOR i = 1 TO chartbars(displayedfile)
        Gridtmp.Cell(rowgridoffset + 1 , i) = Grid.Cell(rowgridoffset + 1 , i)
        Gridtmp.Cell(rowgridoffset + 2 , i) = Grid.Cell(rowgridoffset + 2 , i)
        Gridtmp.Cell(rowgridoffset + 3 , i) = Grid.Cell(rowgridoffset + 3 , i)
        Gridtmp.Cell(rowgridoffset + 4 , i) = Grid.Cell(rowgridoffset + 4 , i)
        Gridtmp.Cell(rowgridoffset + 5 , i) = Grid.Cell(rowgridoffset + 5 , i)
        Gridtmp.Cell(rowgridoffset + 6 , i) = Grid.Cell(rowgridoffset + 6 , i)
        Gridtmp.Cell(rowgridoffset + 7 , i) = Grid.Cell(rowgridoffset + 7 , i)

    NEXT i


    chartbarstmp(displayedfile) = j
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))
    Scrollchart.Max = chartbars(displayedfile)
    scrollchartpositionwait = 0
    Scrollchart.Position = chartbars(displayedfile)
    scrollchartpositionwait = 1
    chartstart = Scrollchart.Position - numbars

    updatemixerlists
    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb) + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb))
    btnOnClick(drwBox)

    form2Edit2.Text = "2"
    form2Edit3.Text = "3"
    form2Edit4.Text = "4"
    form2Edit5.Text = "5"
    form2Edit6.Text = "6"
    form2Edit7.Text = "7"

    exportfileyahoo()

    'delfile(varptr(strfilename))
    'importedfile(displayedfile)=MID$(importedfile(displayedfile) , 0 , LEN(importedfile(displayedfile)) - 4) + ".csv"
    'reimportfile()
    'updatemixerlists
    'logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb) + CHR$(10)
    'writetolog(DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb))
    dim impfdispfcsv as string:impfdispfcsv=MID$(importedfile(displayedfile) , 0 , LEN(importedfile(displayedfile)) - 4) + ".csv"
    cpptmpfuncreturn=varptr$(filegetlinesarray(varptr(impfdispfcsv)))
    if useindiCheckedtmp=1 then
    useindi.checked=1
    btnOnClick(drwBox)
    end if
    dsok.Enabled = 1
END SUB

SUB importfilestooq()
    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    form2Edit2.Text = "1"
    form2Edit3.Text = "2"
    form2Edit4.Text = "3"
    form2Edit5.Text = "4"
    form2Edit6.Text = "5"
    form2Edit7.Text = "6"


    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)


    DIM OpenDialog AS QOPENDIALOG
    'OpenDialog.initialdir=homepath+"\csv"'mtpathedit.text
    'IF OpenDialog.Execute THEN

    DIM dstf AS STRING
    SELECT CASE dstimeframe.ItemIndex
        CASE 0 :
            dstf = "1"
        CASE 1 :
            dstf = "5"
        CASE 2 :
            dstf = "15"
        CASE 3 :
            dstf = "30"
        case 4 :
            dstf = "60"
        case 5 :
            dstf = "240"
        case 6 :
            dstf = "1440"
        case 7 :
            dstf = "10080"
        case 8 :
            dstf = "43200"
    END SELECT


    openedfilesnb ++
    openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(openedfilesnbplusone())
    importedfile(openedfilesnb) = homepath + "\csv\" + UCASE$(dssymboledit.Text) + dstf + ".tmp"  'OpenDialog.FileName
    importedfileopenedfilesnbstr=str$(importedfile(openedfilesnb)):openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(setimportedfile(varptr(importedfileopenedfilesnbstr),varptr(openedfilesnbstr)))
    displayedfile = openedfilesnb
    displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setdisplayedfile(varptr(displayedfilestr)))
    mixgrid.Cell(0 , displayedfile) = importedfile(displayedfile)
    mixgridcolcount(displayedfile) = 1
    mixgridcolcount2(displayedfile) = 0
    mixgridcolcount3(displayedfile) = 0
    mixgridcolcount4(displayedfile) = 0
    IF openedfilesnb > 1 THEN
        rowgridoffset = 7 * (openedfilesnb - 1)
        rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
    END IF
    dispchartnb.AddItems STR$(displayedfile)
    dispchartnb.ItemIndex = openedfilesnb - 1
    'END IF
    'if FileExists(OpenDialog.FileName) = FALSE THEN
    'print " file not found "
    'exit sub
    'end if

' We do this to suppress the first line of the file and to add a fictive volume
     dim yhooarrtmp(0 TO 100000) as string
     DIM file AS QFILESTREAM,yincr as integer
     file.open(importedfile(displayedfile) , 0)
     yincr=-1
     DO
         yincr++
         yhooarrtmp(yincr) = file.ReadLine
     LOOP UNTIL file.eof
     file.close
     
     file.open(importedfile(displayedfile) , 65535)
     dim yincr2 as integer
     for yincr2=1 to yincr
          
         file.writeline(yhooarrtmp(yincr2)+",1")
     next yincr2
     file.close
' -------------------------------------------------     
    
    
    $ESCAPECHARS ON
    dim strfilename as string
    strfilename=replacesubstr$(importedfile(displayedfile),chr$(92),chr$(92)+chr$(92))
    dim strfilenamelines as integer
    strfilenamelines=filegetlinecount(varptr(strfilename))
    'dim i as integer
    dim mystr as string
    dim savmystr(0 to 100000) as string
    dim iinc as integer
    iinc=0 
    
    dim reinitfseek as string:reinitfseek="0"
    'openedfilesnbstr=str$(openedfilesnb)
    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
    iinc++
    savmystr(iinc)=mystr
    for i=1 to strfilenamelines
    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
    iinc++
    savmystr(iinc)=mystr
    next i
    reinitfseek="1"
    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))    
    $ESCAPECHARS OFF

    j = 0

    DO

        j ++

        'getline$ = file.ReadLine
        getline$ = savmystr(j)

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        'commapos = 0
        'FOR i = 1 TO timepos - 1
        '    IF timepos = 1 THEN
        '        EXIT FOR
        '    END IF
        '    commapos = INSTR(commapos + 1 , getline$ , separator)
        'NEXT i
        'time = MID$(getline$ , commapos + 1 , LEN(getline$))
        'time = MID$(time , 0 , INSTR(0 , time , separator) - 1)
        time = "00:00"

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)


        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        'vol = MID$(vol , 0 , INSTR(0 , vol , separator) - 1)        

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open
        Grid.Cell(rowgridoffset + 4 , j) = high
        Grid.Cell(rowgridoffset + 5 , j) = low
        Grid.Cell(rowgridoffset + 6 , j) = close
        Grid.Cell(rowgridoffset + 7 , j) = vol


        Gridtmp.Cell(rowgridoffset + 1 , j) = date
        Gridtmp.Cell(rowgridoffset + 2 , j) = time
        Gridtmp.Cell(rowgridoffset + 3 , j) = open
        Gridtmp.Cell(rowgridoffset + 4 , j) = high
        Gridtmp.Cell(rowgridoffset + 5 , j) = low
        Gridtmp.Cell(rowgridoffset + 6 , j) = close
        Gridtmp.Cell(rowgridoffset + 7 , j) = vol

    LOOP UNTIL j=strfilenamelines
    'file.close

    chartbars(displayedfile) = j
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))

    chartbarstmp(displayedfile) = j
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))
    Scrollchart.Max = chartbars(displayedfile)
    scrollchartpositionwait = 0
    Scrollchart.Position = chartbars(displayedfile)
    scrollchartpositionwait = 1
    chartstart = Scrollchart.Position - numbars
    
    updatemixerlists
    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb) + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb))
    btnOnClick(drwBox)

    form2Edit2.Text = "2"
    form2Edit3.Text = "3"
    form2Edit4.Text = "4"
    form2Edit5.Text = "5"
    form2Edit6.Text = "6"
    form2Edit7.Text = "7"

    exportfileyahoo()
    'delfile(varptr(strfilename))
    'importedfile(displayedfile)=MID$(importedfile(displayedfile) , 0 , LEN(importedfile(displayedfile)) - 4) + ".csv"
    'reimportfile()
    'updatemixerlists
    'logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb) + CHR$(10)
    'writetolog(DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb))
    dim impfdispfcsv as string:impfdispfcsv=MID$(importedfile(displayedfile) , 0 , LEN(importedfile(displayedfile)) - 4) + ".csv"
    cpptmpfuncreturn=varptr$(filegetlinesarray(varptr(impfdispfcsv)))
    if useindiCheckedtmp=1 then
    useindi.checked=1
    btnOnClick(drwBox)
    end if
    dsok.Enabled = 1
END SUB


SUB importfile2()
    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    DIM OpenDialog AS QOPENDIALOG
    OpenDialog.InitialDir = mtpathedit.Text
    IF OpenDialog.Execute THEN
        openedfilesnb ++
        openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(openedfilesnbplusone())
        importedfile(openedfilesnb) = OpenDialog.FileName
        displayedfile = openedfilesnb
        displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setdisplayedfile(varptr(displayedfilestr)))
        mixgrid.Cell(0 , displayedfile) = importedfile(displayedfile)
        mixgridcolcount(displayedfile) = 1
        mixgridcolcount2(displayedfile) = 0
        mixgridcolcount3(displayedfile) = 0
        mixgridcolcount4(displayedfile) = 0
        IF openedfilesnb > 1 THEN
            rowgridoffset = 7 * (openedfilesnb - 1)
            rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
        END IF
        dispchartnb.AddItems STR$(displayedfile)
        dispchartnb.ItemIndex = openedfilesnb - 1
    END IF
    IF FILEEXISTS(OpenDialog.FileName) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF

    DIM file AS QFILESTREAM
    file.open(OpenDialog.FileName , 0)

    j = 0

    DO

        j ++

        getline$ = file.ReadLine

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        commapos = 0
        FOR i = 1 TO timepos - 1
            IF timepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        time = MID$(getline$ , commapos + 1 , LEN(getline$))
        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)

        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        vol = MID$(vol , 0 , LEN(vol))

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open
        Grid.Cell(rowgridoffset + 4 , j) = high
        Grid.Cell(rowgridoffset + 5 , j) = low
        Grid.Cell(rowgridoffset + 6 , j) = close
        Grid.Cell(rowgridoffset + 7 , j) = vol


        Gridtmp.Cell(rowgridoffset + 1 , j) = date
        Gridtmp.Cell(rowgridoffset + 2 , j) = time
        Gridtmp.Cell(rowgridoffset + 3 , j) = open
        Gridtmp.Cell(rowgridoffset + 4 , j) = high
        Gridtmp.Cell(rowgridoffset + 5 , j) = low
        Gridtmp.Cell(rowgridoffset + 6 , j) = close
        Gridtmp.Cell(rowgridoffset + 7 , j) = vol

    LOOP UNTIL file.eof
    file.close
    chartbars(displayedfile) = j
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))
    chartbarstmp(displayedfile) = j
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))
    Scrollchart.Max = chartbars(displayedfile)
    scrollchartpositionwait = 0
    Scrollchart.Position = chartbars(displayedfile)
    scrollchartpositionwait = 1
    chartstart = Scrollchart.Position - numbars
    updatemixerlists
    'bgimg.visible=0
    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb) + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb))
    btnOnClick(drwBox)
END SUB



SUB importfile()
    
'    DIM date AS STRING , time AS STRING
'    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
'    DIM datepos AS INTEGER
'    DIM timepos AS INTEGER
'    DIM openpos AS INTEGER
'    DIM highpos AS INTEGER
'    DIM lowpos AS INTEGER
'    DIM closepos AS INTEGER
'    DIM volpos AS INTEGER
'    DIM separator AS STRING
'    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
'    DIM getline$ AS STRING

'    datepos = VAL(form2Edit1.Text)
'    timepos = VAL(form2Edit2.Text)
'    openpos = VAL(form2Edit3.Text)
'    highpos = VAL(form2Edit4.Text)
'    lowpos = VAL(form2Edit5.Text)
'    closepos = VAL(form2Edit6.Text)
'    volpos = VAL(form2Edit7.Text)
'    separator = VAL(form2Edit8.Text)
    'numbars = VAL(barsdisplayed.Text)
    
    DIM OpenDialog AS QOPENDIALOG
    OpenDialog.InitialDir = mtpathedit.Text
    IF OpenDialog.Execute THEN
        openedfilesnb ++
        openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(openedfilesnbplusone())
        importedfile(openedfilesnb) = OpenDialog.FileName
        importedfileopenedfilesnbstr=str$(importedfile(openedfilesnb)):openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(setimportedfile(varptr(importedfileopenedfilesnbstr),varptr(openedfilesnbstr)))
        displayedfile = openedfilesnb
        displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setdisplayedfile(varptr(displayedfilestr)))
        mixgrid.Cell(0 , displayedfile) = importedfile(displayedfile)
        mixgridcolcount(displayedfile) = 1
        mixgridcolcount2(displayedfile) = 0
        mixgridcolcount3(displayedfile) = 0
        mixgridcolcount4(displayedfile) = 0
        IF openedfilesnb > 1 THEN
            rowgridoffset = 7 * (openedfilesnb - 1)
            rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
        END IF
        dispchartnb.AddItems STR$(displayedfile)
        dispchartnb.ItemIndex = openedfilesnb - 1
    END IF
    IF FILEEXISTS(OpenDialog.FileName) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF

    $ESCAPECHARS ON
    dim strfilename as string
    strfilename=replacesubstr$(opendialog.filename,chr$(92),chr$(92)+chr$(92))
    dim strfilenamelines as integer
    strfilenamelines=filegetlinecount(varptr(strfilename))

'    dim mystr as string
'    dim savmystr(0 to 100000) as string
'    dim iinc as integer
'    iinc=0 
    
'    dim reinitfseek as string:reinitfseek="0"
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
'    iinc++
'    savmystr(iinc)=mystr
'    for i=1 to strfilenamelines
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
'    iinc++
'    savmystr(iinc)=mystr
'    next i
'    reinitfseek="1"
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
    cpptmpfuncreturn=varptr$(filegetlinesarray(varptr(strfilename)))
    $ESCAPECHARS OFF
    
    defstr istr
    for i=1 to strfilenamelines    
    istr=str$(i)    
    rowgridoffsetstr=str$(rowgridoffset + 1)    
    Grid.Cell(rowgridoffset + 1 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 1 , i) = Grid.Cell(rowgridoffset + 1 , i)
    rowgridoffsetstr=str$(rowgridoffset + 2)    
    Grid.Cell(rowgridoffset + 2 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 2 , i) = Grid.Cell(rowgridoffset + 2 , i)
    rowgridoffsetstr=str$(rowgridoffset + 3)    
    Grid.Cell(rowgridoffset + 3 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 3 , i) = Grid.Cell(rowgridoffset + 3 , i)
    rowgridoffsetstr=str$(rowgridoffset + 4)    
    Grid.Cell(rowgridoffset + 4 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 4 , i) = Grid.Cell(rowgridoffset + 4 , i)
    rowgridoffsetstr=str$(rowgridoffset + 5)    
    Grid.Cell(rowgridoffset + 5 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 5 , i) = Grid.Cell(rowgridoffset + 5 , i)
    rowgridoffsetstr=str$(rowgridoffset + 6)    
    Grid.Cell(rowgridoffset + 6 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 6 , i) = Grid.Cell(rowgridoffset + 6 , i)
    rowgridoffsetstr=str$(rowgridoffset + 7)    
    Grid.Cell(rowgridoffset + 7 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 7 , i) = Grid.Cell(rowgridoffset + 7 , i)    
    next i    
    j=strfilenamelines

'    j = 0
'
'    DO
'
'        j ++
'
'
'        getline$ = savmystr(j)
'
'        commapos = 0
'        FOR i = 1 TO datepos - 1
'            IF datepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        date = MID$(getline$ , commapos + 1 , LEN(getline$))
'        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO timepos - 1
'            IF timepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        time = MID$(getline$ , commapos + 1 , LEN(getline$))
'        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO openpos - 1
'            IF openpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        open = MID$(getline$ , commapos + 1 , LEN(getline$))
'        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO highpos - 1
'            IF highpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        high = MID$(getline$ , commapos + 1 , LEN(getline$))
'        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO lowpos - 1
'            IF lowpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        low = MID$(getline$ , commapos + 1 , LEN(getline$))
'        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO closepos - 1
'            IF closepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        close = MID$(getline$ , commapos + 1 , LEN(getline$))
'        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO volpos - 1
'            IF volpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
'        vol = MID$(vol , 0 , LEN(vol))
'
'        Grid.Cell(rowgridoffset + 1 , j) = date
'        Grid.Cell(rowgridoffset + 2 , j) = time
'        Grid.Cell(rowgridoffset + 3 , j) = open
'        Grid.Cell(rowgridoffset + 4 , j) = high
'        Grid.Cell(rowgridoffset + 5 , j) = low
'        Grid.Cell(rowgridoffset + 6 , j) = close
'        Grid.Cell(rowgridoffset + 7 , j) = vol
'
'
'        Gridtmp.Cell(rowgridoffset + 1 , j) = date
'        Gridtmp.Cell(rowgridoffset + 2 , j) = time
'        Gridtmp.Cell(rowgridoffset + 3 , j) = open
'        Gridtmp.Cell(rowgridoffset + 4 , j) = high
'        Gridtmp.Cell(rowgridoffset + 5 , j) = low
'        Gridtmp.Cell(rowgridoffset + 6 , j) = close
'        Gridtmp.Cell(rowgridoffset + 7 , j) = vol
'
'    LOOP UNTIL j=strfilenamelines

    chartbars(displayedfile) = j
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))
    chartbarstmp(displayedfile) = j
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))
    Scrollchart.Max = chartbars(displayedfile)
    scrollchartpositionwait = 0
    Scrollchart.Position = chartbars(displayedfile)
    scrollchartpositionwait = 1
    if val(barsdisplayed.text)>chartbars(displayedfile) then barsdisplayed.text=str$(chartbars(displayedfile))
    numbars = VAL(barsdisplayed.Text)
    chartstart = Scrollchart.Position - numbars
    updatemixerlists

    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb) + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb))    
    btnOnClick(drwBox)
    detect_timeframe
END SUB



SUB exportcollection()

    useindi.Checked = 0

    exportfile

    barsdisplayed.Text = "7"
    dispbarsok_click

    DIM jjj AS string :
    jjj = importedfile(displayedfile)
    DIM kkk AS INTEGER
    kkk = INSTR(0 , jjj , ".")
    DIM iii AS INTEGER
    DIM lll AS STRING
    FOR iii = kkk - 1 TO 0 STEP - 1
        lll = MID$(jjj , iii , 1)
        IF ASC(lll) < 48 OR ASC(lll) > 57 THEN
            EXIT FOR
        END IF
    NEXT iii
    DIM mmm AS STRING
    mmm = MID$(jjj , iii + 1)
    mmm = MID$(mmm , 0 , INSTR(0 , mmm , ".") - 1)

    SELECT CASE VAL(mmm)

        CASE 30 :
            tfmult.Text = "48"
            tfmultok_click
            exportfile
            tfmult.Text = "336"
            tfmultok_click
            exportfile

        CASE 60 :
            tfmult.Text = "24"
            tfmultok_click
            exportfile
            tfmult.Text = "168"
            tfmultok_click
            exportfile

        CASE 240 :
            tfmult.Text = "6"
            tfmultok_click
            exportfile
            tfmult.Text = "42"
            tfmultok_click
            exportfile

    END SELECT

END SUB

SUB importfileauto(ifafilename AS STRING)  ' use this sub to open the file in the same display nb (no openedfilesnb++)
'    DIM date AS STRING , time AS STRING
'    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
'    DIM datepos AS INTEGER
'    DIM timepos AS INTEGER
'    DIM openpos AS INTEGER
'    DIM highpos AS INTEGER
'    DIM lowpos AS INTEGER
'    DIM closepos AS INTEGER
'    DIM volpos AS INTEGER
'    DIM separator AS STRING
'    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
'    DIM getline$ AS STRING

'    datepos = VAL(form2Edit1.Text)
'    timepos = VAL(form2Edit2.Text)
'    openpos = VAL(form2Edit3.Text)
'    highpos = VAL(form2Edit4.Text)
'    lowpos = VAL(form2Edit5.Text)
'    closepos = VAL(form2Edit6.Text)
'    volpos = VAL(form2Edit7.Text)
'    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    'DIM OpenDialog AS QOpenDialog
    'IF OpenDialog.Execute THEN
    'openedfilesnb++
    importedfile(openedfilesnb) = ifafilename
    importedfileopenedfilesnbstr=str$(importedfile(openedfilesnb)):openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(setimportedfile(varptr(importedfileopenedfilesnbstr),varptr(openedfilesnbstr)))
    displayedfile = openedfilesnb
    displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setdisplayedfile(varptr(displayedfilestr)))
    mixgrid.Cell(0 , displayedfile) = importedfile(displayedfile)
    mixgridcolcount(displayedfile) = 1
    mixgridcolcount2(displayedfile) = 0
    mixgridcolcount3(displayedfile) = 0
    mixgridcolcount4(displayedfile) = 0
    IF openedfilesnb > 1 THEN
        rowgridoffset = 7 * (openedfilesnb - 1)
        rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
    END IF
    dispchartnb.AddItems STR$(displayedfile)
    dispchartnb.ItemIndex = openedfilesnb - 1
    'END IF
    IF FILEEXISTS(ifafilename) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF

    'DIM file AS QFILESTREAM
    'file.open(ifafilename , 0)
    
    $ESCAPECHARS ON
    dim strfilename as string
    strfilename=replacesubstr$(ifafilename,chr$(92),chr$(92)+chr$(92))
    dim strfilenamelines as integer
    strfilenamelines=filegetlinecount(varptr(strfilename))

'    dim mystr as string
'    dim savmystr(0 to 100000) as string
'    dim iinc as integer
'    iinc=0 
    
'    dim reinitfseek as string:reinitfseek="0"
    openedfilesnbstr=str$(openedfilesnb)
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
'    iinc++
'    savmystr(iinc)=mystr
'    for i=1 to strfilenamelines
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
'    iinc++
'    savmystr(iinc)=mystr
'    next i
'    reinitfseek="1"
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
    cpptmpfuncreturn=varptr$(filegetlinesarray(varptr(strfilename)))
    $ESCAPECHARS OFF
    
    defstr istr
    for i=1 to strfilenamelines    
    istr=str$(i)    
    rowgridoffsetstr=str$(rowgridoffset + 1)    
    Grid.Cell(rowgridoffset + 1 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 1 , i) = Grid.Cell(rowgridoffset + 1 , i)
    rowgridoffsetstr=str$(rowgridoffset + 2)    
    Grid.Cell(rowgridoffset + 2 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 2 , i) = Grid.Cell(rowgridoffset + 2 , i)
    rowgridoffsetstr=str$(rowgridoffset + 3)    
    Grid.Cell(rowgridoffset + 3 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 3 , i) = Grid.Cell(rowgridoffset + 3 , i)
    rowgridoffsetstr=str$(rowgridoffset + 4)    
    Grid.Cell(rowgridoffset + 4 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 4 , i) = Grid.Cell(rowgridoffset + 4 , i)
    rowgridoffsetstr=str$(rowgridoffset + 5)    
    Grid.Cell(rowgridoffset + 5 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 5 , i) = Grid.Cell(rowgridoffset + 5 , i)
    rowgridoffsetstr=str$(rowgridoffset + 6)    
    Grid.Cell(rowgridoffset + 6 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 6 , i) = Grid.Cell(rowgridoffset + 6 , i)
    rowgridoffsetstr=str$(rowgridoffset + 7)    
    Grid.Cell(rowgridoffset + 7 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 7 , i) = Grid.Cell(rowgridoffset + 7 , i)    
    next i    
    j=strfilenamelines
    writealive    

'    j = 0

'    DO

'        j ++


'        getline$ = savmystr(j)

'        commapos = 0
'        FOR i = 1 TO datepos - 1
'            IF datepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        date = MID$(getline$ , commapos + 1 , LEN(getline$))
'        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

'        commapos = 0
'        FOR i = 1 TO timepos - 1
'            IF timepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        time = MID$(getline$ , commapos + 1 , LEN(getline$))
'        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)

'        commapos = 0
'        FOR i = 1 TO openpos - 1
'            IF openpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        open = MID$(getline$ , commapos + 1 , LEN(getline$))
'        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

'        commapos = 0
'        FOR i = 1 TO highpos - 1
'            IF highpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        high = MID$(getline$ , commapos + 1 , LEN(getline$))
'        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO lowpos - 1
'            IF lowpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        low = MID$(getline$ , commapos + 1 , LEN(getline$))
'        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO closepos - 1
'            IF closepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        close = MID$(getline$ , commapos + 1 , LEN(getline$))
'        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO volpos - 1
'            IF volpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
'        vol = MID$(vol , 0 , LEN(vol))
'
'        Grid.Cell(rowgridoffset + 1 , j) = date
'        Grid.Cell(rowgridoffset + 2 , j) = time
'        Grid.Cell(rowgridoffset + 3 , j) = open
'        Grid.Cell(rowgridoffset + 4 , j) = high
'        Grid.Cell(rowgridoffset + 5 , j) = low
'        Grid.Cell(rowgridoffset + 6 , j) = close
'        Grid.Cell(rowgridoffset + 7 , j) = vol
'
'
'        Gridtmp.Cell(rowgridoffset + 1 , j) = date
'        Gridtmp.Cell(rowgridoffset + 2 , j) = time
'        Gridtmp.Cell(rowgridoffset + 3 , j) = open
'        Gridtmp.Cell(rowgridoffset + 4 , j) = high
'        Gridtmp.Cell(rowgridoffset + 5 , j) = low
'        Gridtmp.Cell(rowgridoffset + 6 , j) = close
'        Gridtmp.Cell(rowgridoffset + 7 , j) = vol
' writealive
'    LOOP UNTIL j=strfilenamelines


    chartbars(displayedfile) = j
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))
    chartbarstmp(displayedfile) = j
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))
    Scrollchart.Max = chartbars(displayedfile)
    scrollchartpositionwait = 0
    Scrollchart.Position = chartbars(displayedfile)
    scrollchartpositionwait = 1
    chartstart = Scrollchart.Position - numbars
    updatemixerlists

    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb) + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb))
    btnOnClick(drwBox)
END SUB

SUB importfileauto2(filenameauto AS STRING) ' use this sub to open the file in a new display nb (openedfilesnb++)
'    DIM date AS STRING , time AS STRING
'    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
'    DIM datepos AS INTEGER
'    DIM timepos AS INTEGER
'    DIM openpos AS INTEGER
'    DIM highpos AS INTEGER
'    DIM lowpos AS INTEGER
'    DIM closepos AS INTEGER
'    DIM volpos AS INTEGER
'    DIM separator AS STRING
'    DIM commapos AS INTEGER

    DIM i AS INTEGER , j AS INTEGER
'    DIM getline$ AS STRING

'    datepos = VAL(form2Edit1.Text)
'    timepos = VAL(form2Edit2.Text)
'    openpos = VAL(form2Edit3.Text)
'    highpos = VAL(form2Edit4.Text)
'    lowpos = VAL(form2Edit5.Text)
'    closepos = VAL(form2Edit6.Text)
'    volpos = VAL(form2Edit7.Text)
'    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    'DIM OpenDialog AS QOpenDialog
    'IF OpenDialog.Execute THEN
    openedfilesnb ++
    openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(openedfilesnbplusone())
    importedfile(openedfilesnb) = filenameauto
    importedfileopenedfilesnbstr=str$(importedfile(openedfilesnb)):openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(setimportedfile(varptr(importedfileopenedfilesnbstr),varptr(openedfilesnbstr)))
    displayedfile = openedfilesnb
    displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setdisplayedfile(varptr(displayedfilestr)))
    mixgrid.Cell(0 , displayedfile) = importedfile(displayedfile)
    mixgridcolcount(displayedfile) = 1
    mixgridcolcount2(displayedfile) = 0
    mixgridcolcount3(displayedfile) = 0
    mixgridcolcount4(displayedfile) = 0
    IF openedfilesnb > 1 THEN
        rowgridoffset = 7 * (openedfilesnb - 1)
        rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
    END IF
    dispchartnb.AddItems STR$(displayedfile)
    dispchartnb.ItemIndex = openedfilesnb - 1
    'END IF
    IF FILEEXISTS(filenameauto) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF

    'DIM file AS QFILESTREAM
    'file.open(filenameauto , 0)
    
    $ESCAPECHARS ON
    dim strfilename as string
    strfilename=replacesubstr$(filenameauto,chr$(92),chr$(92)+chr$(92))
    dim strfilenamelines as integer
    strfilenamelines=filegetlinecount(varptr(strfilename))
    'dim i as integer
'    dim mystr as string
'    dim savmystr(0 to 100000) as string
'    dim iinc as integer
'    iinc=0 
    
'    dim reinitfseek as string:reinitfseek="0"
    openedfilesnbstr=str$(openedfilesnb)
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
'    iinc++
'    savmystr(iinc)=mystr
'    for i=1 to strfilenamelines
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
'    iinc++
'    savmystr(iinc)=mystr
'    next i
'    reinitfseek="1"
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
cpptmpfuncreturn=varptr$(filegetlinesarray(varptr(strfilename)))
    $ESCAPECHARS OFF
    
    defstr istr
    for i=1 to strfilenamelines    
    istr=str$(i)    
    rowgridoffsetstr=str$(rowgridoffset + 1)    
    Grid.Cell(rowgridoffset + 1 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 1 , i) = Grid.Cell(rowgridoffset + 1 , i)
    rowgridoffsetstr=str$(rowgridoffset + 2)    
    Grid.Cell(rowgridoffset + 2 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 2 , i) = Grid.Cell(rowgridoffset + 2 , i)
    rowgridoffsetstr=str$(rowgridoffset + 3)    
    Grid.Cell(rowgridoffset + 3 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 3 , i) = Grid.Cell(rowgridoffset + 3 , i)
    rowgridoffsetstr=str$(rowgridoffset + 4)    
    Grid.Cell(rowgridoffset + 4 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 4 , i) = Grid.Cell(rowgridoffset + 4 , i)
    rowgridoffsetstr=str$(rowgridoffset + 5)    
    Grid.Cell(rowgridoffset + 5 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 5 , i) = Grid.Cell(rowgridoffset + 5 , i)
    rowgridoffsetstr=str$(rowgridoffset + 6)    
    Grid.Cell(rowgridoffset + 6 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 6 , i) = Grid.Cell(rowgridoffset + 6 , i)
    rowgridoffsetstr=str$(rowgridoffset + 7)    
    Grid.Cell(rowgridoffset + 7 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 7 , i) = Grid.Cell(rowgridoffset + 7 , i)    
    next i    
    j=strfilenamelines 

'    j = 0

'    DO

'        j ++

        'getline$ = file.ReadLine
'        getline$ = savmystr(j)

'        commapos = 0
'        FOR i = 1 TO datepos - 1
'            IF datepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        date = MID$(getline$ , commapos + 1 , LEN(getline$))
'        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO timepos - 1
'            IF timepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        time = MID$(getline$ , commapos + 1 , LEN(getline$))
'        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO openpos - 1
'            IF openpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        open = MID$(getline$ , commapos + 1 , LEN(getline$))
'        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO highpos - 1
'            IF highpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        high = MID$(getline$ , commapos + 1 , LEN(getline$))
'        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO lowpos - 1
'            IF lowpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        low = MID$(getline$ , commapos + 1 , LEN(getline$))
'        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO closepos - 1
'            IF closepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        close = MID$(getline$ , commapos + 1 , LEN(getline$))
'        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO volpos - 1
'            IF volpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
'        vol = MID$(vol , 0 , LEN(vol))
'
'        Grid.Cell(rowgridoffset + 1 , j) = date
'        Grid.Cell(rowgridoffset + 2 , j) = time
'        Grid.Cell(rowgridoffset + 3 , j) = open
'        Grid.Cell(rowgridoffset + 4 , j) = high
'        Grid.Cell(rowgridoffset + 5 , j) = low
'        Grid.Cell(rowgridoffset + 6 , j) = close
'        Grid.Cell(rowgridoffset + 7 , j) = vol
'
'
'        Gridtmp.Cell(rowgridoffset + 1 , j) = date
'        Gridtmp.Cell(rowgridoffset + 2 , j) = time
'        Gridtmp.Cell(rowgridoffset + 3 , j) = open
'        Gridtmp.Cell(rowgridoffset + 4 , j) = high
'        Gridtmp.Cell(rowgridoffset + 5 , j) = low
'        Gridtmp.Cell(rowgridoffset + 6 , j) = close
'        Gridtmp.Cell(rowgridoffset + 7 , j) = vol
'
'    LOOP UNTIL j=strfilenamelines
    'file.close
    chartbars(displayedfile) = j
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))
    chartbarstmp(displayedfile) = j
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))
    Scrollchart.Max = chartbars(displayedfile)
    scrollchartpositionwait = 0
    Scrollchart.Position = chartbars(displayedfile)
    scrollchartpositionwait = 1
    chartstart = Scrollchart.Position - numbars
    updatemixerlists
    'bgimg.visible=0
    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb) + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb))
    btnOnClick(drwBox)
    detect_timeframe
END SUB

SUB importfile1m(filenameauto AS STRING) ' use this sub to open the file in a new display nb (openedfilesnb++)


    DIM i AS INTEGER , j AS INTEGER

    numbars = VAL(barsdisplayed.Text)


    openedfilesnb ++
    openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(openedfilesnbplusone())
    importedfile(openedfilesnb) = filenameauto
    importedfileopenedfilesnbstr=str$(importedfile(openedfilesnb)):openedfilesnbstr=str$(openedfilesnb):cpptmpfuncreturn=varptr$(setimportedfile(varptr(importedfileopenedfilesnbstr),varptr(openedfilesnbstr)))
    displayedfile = openedfilesnb
    displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setdisplayedfile(varptr(displayedfilestr)))
    mixgrid.Cell(0 , displayedfile) = importedfile(displayedfile)
    mixgridcolcount(displayedfile) = 1
    mixgridcolcount2(displayedfile) = 0
    mixgridcolcount3(displayedfile) = 0
    mixgridcolcount4(displayedfile) = 0
    IF openedfilesnb > 1 THEN
        rowgridoffset = 7 * (openedfilesnb - 1)
        rowgridoffsetstr=str$(rowgridoffset):cpptmpfuncreturn=varptr$(setrowgridoffset(varptr(rowgridoffsetstr)))
    END IF
    dispchartnb.AddItems STR$(displayedfile)
    dispchartnb.ItemIndex = openedfilesnb - 1

    IF FILEEXISTS(filenameauto) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF


    
    $ESCAPECHARS ON
    dim strfilename as string
    strfilename=replacesubstr$(filenameauto,chr$(92),chr$(92)+chr$(92))
    dim strfilenamelines as integer
    strfilenamelines=filegetlinecount(varptr(strfilename))

    openedfilesnbstr=str$(openedfilesnb)

cpptmpfuncreturn=varptr$(filegetlinesarray(varptr(strfilename)))
    $ESCAPECHARS OFF
    
    defstr istr
    for i=1 to strfilenamelines    
    istr=str$(i)    
    rowgridoffsetstr=str$(rowgridoffset + 1)    
    Grid.Cell(rowgridoffset + 1 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 1 , i) = Grid.Cell(rowgridoffset + 1 , i)
    date1(strfilenamelines-i)=Grid.Cell(rowgridoffset + 1 , i)
    rowgridoffsetstr=str$(rowgridoffset + 2)    
    Grid.Cell(rowgridoffset + 2 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 2 , i) = Grid.Cell(rowgridoffset + 2 , i)
    time1(strfilenamelines-i)=Grid.Cell(rowgridoffset + 2 , i)
    rowgridoffsetstr=str$(rowgridoffset + 3)    
    Grid.Cell(rowgridoffset + 3 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 3 , i) = Grid.Cell(rowgridoffset + 3 , i)
    open1(strfilenamelines-i)=val(Grid.Cell(rowgridoffset + 3 , i))
    rowgridoffsetstr=str$(rowgridoffset + 4)    
    Grid.Cell(rowgridoffset + 4 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 4 , i) = Grid.Cell(rowgridoffset + 4 , i)
    high1(strfilenamelines-i)=val(Grid.Cell(rowgridoffset + 4 , i))
    rowgridoffsetstr=str$(rowgridoffset + 5)    
    Grid.Cell(rowgridoffset + 5 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 5 , i) = Grid.Cell(rowgridoffset + 5 , i)
    low1(strfilenamelines-i)=val(Grid.Cell(rowgridoffset + 5 , i))
    rowgridoffsetstr=str$(rowgridoffset + 6)    
    Grid.Cell(rowgridoffset + 6 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 6 , i) = Grid.Cell(rowgridoffset + 6 , i)
    close1(strfilenamelines-i)=val(Grid.Cell(rowgridoffset + 6 , i))
    rowgridoffsetstr=str$(rowgridoffset + 7)    
    Grid.Cell(rowgridoffset + 7 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 7 , i) = Grid.Cell(rowgridoffset + 7 , i)
    volume1(strfilenamelines-i)=val(Grid.Cell(rowgridoffset + 7 , i))
    next i    
    j=strfilenamelines 


    chartbars(displayedfile) = j
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))
    chartbarstmp(displayedfile) = j
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))
    Scrollchart.Max = chartbars(displayedfile)
    scrollchartpositionwait = 0
    Scrollchart.Position = chartbars(displayedfile)
    scrollchartpositionwait = 1
    chartstart = Scrollchart.Position - numbars
    updatemixerlists

    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb) + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Import csv " + importedfile(openedfilesnb))
    btnOnClick(drwBox)
    'closedispchart_click()
END SUB

SUB reimportfile()
'    DIM date AS STRING , time AS STRING
'    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
'    DIM datepos AS INTEGER
'    DIM timepos AS INTEGER
'    DIM openpos AS INTEGER
'    DIM highpos AS INTEGER
'    DIM lowpos AS INTEGER
'    DIM closepos AS INTEGER
'    DIM volpos AS INTEGER
'    DIM separator AS STRING
'    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
'    DIM getline$ AS STRING

'    datepos = VAL(form2Edit1.Text)
'    timepos = VAL(form2Edit2.Text)
'    openpos = VAL(form2Edit3.Text)
'    highpos = VAL(form2Edit4.Text)
'    lowpos = VAL(form2Edit5.Text)
'    closepos = VAL(form2Edit6.Text)
'    volpos = VAL(form2Edit7.Text)
'    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

'    DIM OpenDialog AS QOPENDIALOG

    'DIM file AS QFILESTREAM
    'file.open(importedfile(displayedfile) , 0)
    $ESCAPECHARS ON
    dim strfilename as string
    strfilename=replacesubstr$(importedfile(displayedfile),chr$(92),chr$(92)+chr$(92))
    dim strfilenamelines as integer
    strfilenamelines=filegetlinecount(varptr(strfilename))
    'dim i as integer
'    dim mystr as string
'    dim savmystr(0 to 100000) as string
'    dim iinc as integer
'    iinc=0 
    
'    dim reinitfseek as string:reinitfseek="0"
    openedfilesnbstr=str$(openedfilesnb)
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
'    iinc++
'    savmystr(iinc)=mystr
'    for i=1 to strfilenamelines
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
'    iinc++
'    savmystr(iinc)=mystr
'    next i
'    reinitfseek="1"
'    mystr=varptr$(filegetalllines(varptr(strfilename),varptr(reinitfseek)))
cpptmpfuncreturn=varptr$(filegetlinesarray(varptr(strfilename)))
    $ESCAPECHARS OFF
    
    defstr istr
    for i=1 to strfilenamelines    
    istr=str$(i)    
    rowgridoffsetstr=str$(rowgridoffset + 1)    
    Grid.Cell(rowgridoffset + 1 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 1 , i) = Grid.Cell(rowgridoffset + 1 , i)
    rowgridoffsetstr=str$(rowgridoffset + 2)    
    Grid.Cell(rowgridoffset + 2 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 2 , i) = Grid.Cell(rowgridoffset + 2 , i)
    rowgridoffsetstr=str$(rowgridoffset + 3)    
    Grid.Cell(rowgridoffset + 3 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 3 , i) = Grid.Cell(rowgridoffset + 3 , i)
    rowgridoffsetstr=str$(rowgridoffset + 4)    
    Grid.Cell(rowgridoffset + 4 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 4 , i) = Grid.Cell(rowgridoffset + 4 , i)
    rowgridoffsetstr=str$(rowgridoffset + 5)    
    Grid.Cell(rowgridoffset + 5 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 5 , i) = Grid.Cell(rowgridoffset + 5 , i)
    rowgridoffsetstr=str$(rowgridoffset + 6)    
    Grid.Cell(rowgridoffset + 6 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 6 , i) = Grid.Cell(rowgridoffset + 6 , i)
    rowgridoffsetstr=str$(rowgridoffset + 7)    
    Grid.Cell(rowgridoffset + 7 , i) = varptr$(getdatagrid(varptr(rowgridoffsetstr),varptr(istr)))
    Gridtmp.Cell(rowgridoffset + 7 , i) = Grid.Cell(rowgridoffset + 7 , i)    
    next i    
    j=strfilenamelines 
    writealive

'    j = 0

'    DO

'        j ++

        'getline$ = file.ReadLine
'        getline$ = savmystr(j)

'        commapos = 0
'        FOR i = 1 TO datepos - 1
'            IF datepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        date = MID$(getline$ , commapos + 1 , LEN(getline$))
'        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO timepos - 1
'            IF timepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        time = MID$(getline$ , commapos + 1 , LEN(getline$))
'        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO openpos - 1
'            IF openpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        open = MID$(getline$ , commapos + 1 , LEN(getline$))
'        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO highpos - 1
'            IF highpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        high = MID$(getline$ , commapos + 1 , LEN(getline$))
'        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO lowpos - 1
'            IF lowpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        low = MID$(getline$ , commapos + 1 , LEN(getline$))
'        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO closepos - 1
'            IF closepos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        close = MID$(getline$ , commapos + 1 , LEN(getline$))
'        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)
'
'        commapos = 0
'        FOR i = 1 TO volpos - 1
'            IF volpos = 1 THEN
'                EXIT FOR
'            END IF
'            commapos = INSTR(commapos + 1 , getline$ , separator)
'        NEXT i
'        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
'        vol = MID$(vol , 0 , LEN(vol))
'
'        Grid.Cell(rowgridoffset + 1 , j) = date
'        Grid.Cell(rowgridoffset + 2 , j) = time
'        Grid.Cell(rowgridoffset + 3 , j) = open
'        Grid.Cell(rowgridoffset + 4 , j) = high
'        Grid.Cell(rowgridoffset + 5 , j) = low
'        Grid.Cell(rowgridoffset + 6 , j) = close
'        Grid.Cell(rowgridoffset + 7 , j) = vol
'
'        Gridtmp.Cell(rowgridoffset + 1 , j) = date
'        Gridtmp.Cell(rowgridoffset + 2 , j) = time
'        Gridtmp.Cell(rowgridoffset + 3 , j) = open
'        Gridtmp.Cell(rowgridoffset + 4 , j) = high
'        Gridtmp.Cell(rowgridoffset + 5 , j) = low
'        Gridtmp.Cell(rowgridoffset + 6 , j) = close
'        Gridtmp.Cell(rowgridoffset + 7 , j) = vol
' writealive
'    LOOP UNTIL j=strfilenamelines
    'file.close
    chartbars(displayedfile) = j
    chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))
    chartbarstmp(displayedfile) = j
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))
    Scrollchart.Max = chartbars(displayedfile)
    scrollchartpositionwait = 0
    Scrollchart.Position = chartbars(displayedfile)
    scrollchartpositionwait = 1
    chartstart = Scrollchart.Position - numbars
    'tfmultok_click
    btnOnClick(drwBox)

END SUB

SUB importfilemultiply()
    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    DIM OpenDialog AS QOPENDIALOG
    IF OpenDialog.Execute THEN
        mixgrid3.Cell(mixgridcolcount3(displayedfile) , displayedfile) = OpenDialog.FileName
        mixgridcolcount3(displayedfile) = mixgridcolcount3(displayedfile) + 1
    END IF
    IF FILEEXISTS(OpenDialog.FileName) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF
    DIM file AS QFILESTREAM
    file.open(OpenDialog.FileName , 0)

    j = 0

    DO

        j ++

        getline$ = file.ReadLine

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        commapos = 0
        FOR i = 1 TO timepos - 1
            IF timepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        time = MID$(getline$ , commapos + 1 , LEN(getline$))
        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)

        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        vol = MID$(vol , 0 , LEN(vol))

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open
        Grid.Cell(rowgridoffset + 4 , j) = high
        Grid.Cell(rowgridoffset + 5 , j) = low
        Grid.Cell(rowgridoffset + 6 , j) = close
        Grid.Cell(rowgridoffset + 7 , j) = vol

    LOOP UNTIL file.eof
    file.close

    DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    m = 1
    incr = 0

    FOR k = 1 TO chartbars(displayedfile)
        FOR l = m TO j
            IF (Gridtmp.Cell(rowgridoffset + 1 , k) = Grid.Cell(rowgridoffset + 1 , l)) AND (Gridtmp.Cell(rowgridoffset + 2 , k) = Grid.Cell(rowgridoffset + 2 , l)) THEN
                incr ++
                m = l + 1
                Gridtmp.Cell(rowgridoffset + 1 , incr) = Gridtmp.Cell(rowgridoffset + 1 , k)
                Gridtmp.Cell(rowgridoffset + 2 , incr) = Gridtmp.Cell(rowgridoffset + 2 , k)
                Gridtmp.Cell(rowgridoffset + 3 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) * VAL(Grid.Cell(rowgridoffset + 3 , l)))
                Gridtmp.Cell(rowgridoffset + 4 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 4 , k)) * VAL(Grid.Cell(rowgridoffset + 4 , l)))
                Gridtmp.Cell(rowgridoffset + 5 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 5 , k)) * VAL(Grid.Cell(rowgridoffset + 5 , l)))
                Gridtmp.Cell(rowgridoffset + 6 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 6 , k)) * VAL(Grid.Cell(rowgridoffset + 6 , l)))
                Gridtmp.Cell(rowgridoffset + 7 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 7 , k)) + VAL(Grid.Cell(rowgridoffset + 7 , l)))
            END IF
        NEXT l
        mixform.Caption = "Please wait while calculating... " + STR$(INT(100 / chartbars(displayedfile) * k)) + "% done"
    NEXT k

    chartbarstmp(displayedfile) = incr
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))

    tfmultm_click
    mixerform
END SUB

SUB importfilemultiplydel()
    'if additionlist.itemindex=0 then
    'showmessage "Main chart can't be removed from here."
    'exit sub
    'end if
    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    DIM file AS QFILESTREAM
    file.open(multiplylist.Item(multiplylist.ItemIndex) , 0)

    j = 0

    DO

        j ++

        getline$ = file.ReadLine

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        commapos = 0
        FOR i = 1 TO timepos - 1
            IF timepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        time = MID$(getline$ , commapos + 1 , LEN(getline$))
        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)

        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        vol = MID$(vol , 0 , LEN(vol))

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open
        Grid.Cell(rowgridoffset + 4 , j) = high
        Grid.Cell(rowgridoffset + 5 , j) = low
        Grid.Cell(rowgridoffset + 6 , j) = close
        Grid.Cell(rowgridoffset + 7 , j) = vol

    LOOP UNTIL file.eof
    file.close

    DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    m = 1
    incr = 0

    FOR k = 1 TO chartbars(displayedfile)
        FOR l = m TO j
            IF (Gridtmp.Cell(rowgridoffset + 1 , k) = Grid.Cell(rowgridoffset + 1 , l)) AND (Gridtmp.Cell(rowgridoffset + 2 , k) = Grid.Cell(rowgridoffset + 2 , l)) THEN
                incr ++
                m = l + 1
                Gridtmp.Cell(rowgridoffset + 1 , incr) = Gridtmp.Cell(rowgridoffset + 1 , k)
                Gridtmp.Cell(rowgridoffset + 2 , incr) = Gridtmp.Cell(rowgridoffset + 2 , k)
                Gridtmp.Cell(rowgridoffset + 3 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) / VAL(Grid.Cell(rowgridoffset + 3 , l)))
                Gridtmp.Cell(rowgridoffset + 4 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 4 , k)) / VAL(Grid.Cell(rowgridoffset + 4 , l)))
                Gridtmp.Cell(rowgridoffset + 5 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 5 , k)) / VAL(Grid.Cell(rowgridoffset + 5 , l)))
                Gridtmp.Cell(rowgridoffset + 6 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 6 , k)) / VAL(Grid.Cell(rowgridoffset + 6 , l)))
                Gridtmp.Cell(rowgridoffset + 7 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 7 , k)) - VAL(Grid.Cell(rowgridoffset + 7 , l)))
            END IF
        NEXT l
        mixform.Caption = "Please wait while calculating... " + STR$(INT(100 / chartbars(displayedfile) * k)) + "% done"
    NEXT k

    chartbarstmp(displayedfile) = incr
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))

    FOR i = multiplylist.ItemIndex TO mixgridcolcount3(displayedfile) - 1
        mixgrid3.Cell(i , displayedfile) = mixgrid3.Cell(i + 1 , displayedfile)
    NEXT i
    mixgridcolcount3(displayedfile) = mixgridcolcount3(displayedfile) - 1
    tfmultm_click
    mixerform
END SUB


SUB importfiledivide()
    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    DIM OpenDialog AS QOPENDIALOG
    IF OpenDialog.Execute THEN
        mixgrid4.Cell(mixgridcolcount4(displayedfile) , displayedfile) = OpenDialog.FileName
        mixgridcolcount4(displayedfile) = mixgridcolcount4(displayedfile) + 1
    END IF
    IF FILEEXISTS(OpenDialog.FileName) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF
    DIM file AS QFILESTREAM
    file.open(OpenDialog.FileName , 0)

    j = 0

    DO

        j ++

        getline$ = file.ReadLine

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        commapos = 0
        FOR i = 1 TO timepos - 1
            IF timepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        time = MID$(getline$ , commapos + 1 , LEN(getline$))
        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)

        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        vol = MID$(vol , 0 , LEN(vol))

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open
        Grid.Cell(rowgridoffset + 4 , j) = high
        Grid.Cell(rowgridoffset + 5 , j) = low
        Grid.Cell(rowgridoffset + 6 , j) = close
        Grid.Cell(rowgridoffset + 7 , j) = vol

    LOOP UNTIL file.eof
    file.close

    DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    m = 1
    incr = 0

    FOR k = 1 TO chartbars(displayedfile)
        FOR l = m TO j
            IF (Gridtmp.Cell(rowgridoffset + 1 , k) = Grid.Cell(rowgridoffset + 1 , l)) AND (Gridtmp.Cell(rowgridoffset + 2 , k) = Grid.Cell(rowgridoffset + 2 , l)) THEN
                incr ++
                m = l + 1
                Gridtmp.Cell(rowgridoffset + 1 , incr) = Gridtmp.Cell(rowgridoffset + 1 , k)
                Gridtmp.Cell(rowgridoffset + 2 , incr) = Gridtmp.Cell(rowgridoffset + 2 , k)
                Gridtmp.Cell(rowgridoffset + 3 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) / VAL(Grid.Cell(rowgridoffset + 3 , l)))
                Gridtmp.Cell(rowgridoffset + 4 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 4 , k)) / VAL(Grid.Cell(rowgridoffset + 4 , l)))
                Gridtmp.Cell(rowgridoffset + 5 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 5 , k)) / VAL(Grid.Cell(rowgridoffset + 5 , l)))
                Gridtmp.Cell(rowgridoffset + 6 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 6 , k)) / VAL(Grid.Cell(rowgridoffset + 6 , l)))
                Gridtmp.Cell(rowgridoffset + 7 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 7 , k)) + VAL(Grid.Cell(rowgridoffset + 7 , l)))
            END IF
        NEXT l
        mixform.Caption = "Please wait while calculating... " + STR$(INT(100 / chartbars(displayedfile) * k)) + "% done"
    NEXT k

    chartbarstmp(displayedfile) = incr
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))

    tfmultm_click
    mixerform
END SUB

SUB importfiledividedel()
    'if additionlist.itemindex=0 then
    'showmessage "Main chart can't be removed from here."
    'exit sub
    'end if
    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    DIM file AS QFILESTREAM
    file.open(dividelist.Item(dividelist.ItemIndex) , 0)

    j = 0

    DO

        j ++

        getline$ = file.ReadLine

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        commapos = 0
        FOR i = 1 TO timepos - 1
            IF timepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        time = MID$(getline$ , commapos + 1 , LEN(getline$))
        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)

        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        vol = MID$(vol , 0 , LEN(vol))

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open
        Grid.Cell(rowgridoffset + 4 , j) = high
        Grid.Cell(rowgridoffset + 5 , j) = low
        Grid.Cell(rowgridoffset + 6 , j) = close
        Grid.Cell(rowgridoffset + 7 , j) = vol

    LOOP UNTIL file.eof
    file.close

    DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    m = 1
    incr = 0

    FOR k = 1 TO chartbars(displayedfile)
        FOR l = m TO j
            IF (Gridtmp.Cell(rowgridoffset + 1 , k) = Grid.Cell(rowgridoffset + 1 , l)) AND (Gridtmp.Cell(rowgridoffset + 2 , k) = Grid.Cell(rowgridoffset + 2 , l)) THEN
                incr ++
                m = l + 1
                Gridtmp.Cell(rowgridoffset + 1 , incr) = Gridtmp.Cell(rowgridoffset + 1 , k)
                Gridtmp.Cell(rowgridoffset + 2 , incr) = Gridtmp.Cell(rowgridoffset + 2 , k)
                Gridtmp.Cell(rowgridoffset + 3 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) * VAL(Grid.Cell(rowgridoffset + 3 , l)))
                Gridtmp.Cell(rowgridoffset + 4 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 4 , k)) * VAL(Grid.Cell(rowgridoffset + 4 , l)))
                Gridtmp.Cell(rowgridoffset + 5 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 5 , k)) * VAL(Grid.Cell(rowgridoffset + 5 , l)))
                Gridtmp.Cell(rowgridoffset + 6 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 6 , k)) * VAL(Grid.Cell(rowgridoffset + 6 , l)))
                Gridtmp.Cell(rowgridoffset + 7 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 7 , k)) - VAL(Grid.Cell(rowgridoffset + 7 , l)))
            END IF
        NEXT l
        mixform.Caption = "Please wait while calculating... " + STR$(INT(100 / chartbars(displayedfile) * k)) + "% done"
    NEXT k

    chartbarstmp(displayedfile) = incr
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))

    FOR i = dividelist.ItemIndex TO mixgridcolcount4(displayedfile) - 1
        mixgrid4.Cell(i , displayedfile) = mixgrid4.Cell(i + 1 , displayedfile)
    NEXT i
    mixgridcolcount4(displayedfile) = mixgridcolcount4(displayedfile) - 1
    tfmultm_click
    mixerform
END SUB

SUB chartconvsub
    chartconvform.Visible = 1
END SUB

sub attribtf
    attribtfform.visible=1
end sub

SUB otheropssub
    otheropsform.Visible = 1
END SUB

SUB reversebarscomputesub
    DIM i AS INTEGER , j AS INTEGER

    numbars = VAL(barsdisplayed.Text)

    DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    m = 1
    incr = 0
    DIM freq AS INTEGER
    freq = 0
    DIM freqfact AS DOUBLE
    DIM kbarlow AS DOUBLE , kbarlowprev AS DOUBLE
    DIM kbarhigh AS DOUBLE , kbarhighprev AS DOUBLE
    DIM kbaropen AS DOUBLE , kbaropenprev AS DOUBLE
    DIM kbarclose AS DOUBLE , kbarcloseprev AS DOUBLE
    DIM distcloseopen AS DOUBLE , distclosehigh AS DOUBLE , distcloselow AS DOUBLE


    FOR k = VAL(barnbbeginedit.Text) TO chartbars(displayedfile)

        freq ++
        IF freq > VAL(reversebarsdenominatoredit.Text) THEN
            freq = 1
        END IF
        IF freq = 1 THEN  'freq<=val(reversebarsnumeratoredit.text) then
            reversebarscomputesubb(k)
            refreshgrids

        END IF
        IF freq = VAL(reversebarsnumeratoredit.Text) + 1 THEN  'freq<=val(reversebarsnumeratoredit.text) then
            reversebarscomputesubb(k)
            refreshgrids
        END IF

    NEXT k


END SUB

SUB showfrmlogreverse
    frmlogreverse.Visible = 1
END SUB

SUB findbarfromfile(fbffdate AS STRING , fbfftime AS STRING)

    DIM caldatey AS STRING
    DIM caldatem AS STRING
    DIM caldated AS STRING
    DIM caldate AS STRING
    DIM i AS INTEGER

    'caldate=caldatey+"."+caldatem+"."+caldated

    FOR i = 1 TO chartbars(displayedfile)
        IF like(Grid.Cell(rowgridoffset + 1 , i) , fbffdate) AND like(Grid.Cell(rowgridoffset + 2 , i) , fbfftime) THEN
            'Scrollchart.Position=i+numbars-1
            clickedbarnb = i - chartstart
            graphbarnboncurstatic = clickedbarnb + chartstart
            'justrefreshchart
            EXIT FOR
        END IF
    NEXT i

END SUB

SUB reversetillendfromfile


    DIM getline$ AS STRING

    DIM OpenDialog AS QOPENDIALOG
    OpenDialog.InitialDir = homepath
    IF OpenDialog.Execute THEN

    END IF
    IF FILEEXISTS(OpenDialog.FileName) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF

    DIM file AS QFILESTREAM
    file.open(OpenDialog.FileName , 0)

    DEFINT j = 0
    DIM revdate AS STRING
    DIM revtime AS STRING


    DO

        j ++

        getline$ = file.ReadLine

        IF INSTR(getline$ , "Reverse") > 0 THEN
            revdate = MID$(MID$(getline$ , INSTR(getline$ , "From Date: ")) , 12 , INSTR(MID$(getline$ , INSTR(getline$ , "From Date: ") + 11) , " ") - 1)
            revtime = MID$(MID$(getline$ , INSTR(getline$ , "From Date: ") + 11) , INSTR(MID$(getline$ , INSTR(getline$ , "From Date: ") + 11) , " ") + 1 , 5)
            findbarfromfile(revdate , revtime)
            reversetillendnorefresh
        END IF

    LOOP UNTIL file.eof
    file.close
    cpptmpfuncreturn=varptr$(refreshgridscpp())
    'refreshgrids  
    refreshgrids2    
END SUB

SUB reversetillend
    DIM i AS INTEGER , j AS INTEGER

    'numbars = VAL(barsdisplayed.Text)

    'DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    'm = 1
    'incr = 0
    'DIM freq AS INTEGER
    'freq = 0
    'DIM freqfact AS DOUBLE
    'DIM kbarlow AS DOUBLE , kbarlowprev AS DOUBLE
    'DIM kbarhigh AS DOUBLE , kbarhighprev AS DOUBLE
    'DIM kbaropen AS DOUBLE , kbaropenprev AS DOUBLE
    'DIM kbarclose AS DOUBLE , kbarcloseprev AS DOUBLE
    'DIM distcloseopen AS DOUBLE , distclosehigh AS DOUBLE , distcloselow AS DOUBLE
    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Reverse " + importedfile(displayedfile) + " " + "From Date: " + Grid.Cell(rowgridoffset + 1 , clickedbarnb + chartstart) + " " + Grid.Cell(rowgridoffset + 2 , clickedbarnb + chartstart) + " till end" + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Reverse " + importedfile(displayedfile) + " " + "From Date: " + Grid.Cell(rowgridoffset + 1 , clickedbarnb + chartstart) + " " + Grid.Cell(rowgridoffset + 2 , clickedbarnb + chartstart) + " till end")
    'reversebarscomputesubb(graphbarnboncurstatic)
    graphbarnboncurstaticstr=str$(graphbarnboncurstatic)
    cpptmpfuncreturn=varptr$(reversebarscomputesubbcpp(varptr(graphbarnboncurstaticstr)))
    cpptmpfuncreturn=varptr$(refreshgridscpp())
    'refreshgrids
    refreshgrids2  
END SUB

SUB deleteafter

showmessage "not implemented yet"
exit sub

    DIM i AS INTEGER , j AS INTEGER

   
    graphbarnboncurstaticstr=str$(graphbarnboncurstatic)
    cpptmpfuncreturn=varptr$(reversebarscomputesubbcpp(varptr(graphbarnboncurstaticstr)))
    cpptmpfuncreturn=varptr$(refreshgridscpp())

    refreshgrids2  
END SUB

SUB reversetillendnorefresh
    DIM i AS INTEGER , j AS INTEGER

    'numbars = VAL(barsdisplayed.Text)

    'DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    'm = 1
    'incr = 0
    'DIM freq AS INTEGER
    'freq = 0
    'DIM freqfact AS DOUBLE
    'DIM kbarlow AS DOUBLE , kbarlowprev AS DOUBLE
    'DIM kbarhigh AS DOUBLE , kbarhighprev AS DOUBLE
    'DIM kbaropen AS DOUBLE , kbaropenprev AS DOUBLE
    'DIM kbarclose AS DOUBLE , kbarcloseprev AS DOUBLE
    'DIM distcloseopen AS DOUBLE , distclosehigh AS DOUBLE , distcloselow AS DOUBLE
    logreverseedit.Text = logreverseedit.Text + DATE$ + " " + TIME$ + " " + "Reverse " + importedfile(displayedfile) + " " + "From Date: " + Grid.Cell(rowgridoffset + 1 , clickedbarnb + chartstart) + " " + Grid.Cell(rowgridoffset + 2 , clickedbarnb + chartstart) + " till end" + CHR$(10)
    writetolog(DATE$ + " " + TIME$ + " " + "Reverse " + importedfile(displayedfile) + " " + "From Date: " + Grid.Cell(rowgridoffset + 1 , clickedbarnb + chartstart) + " " + Grid.Cell(rowgridoffset + 2 , clickedbarnb + chartstart) + " till end")
    'reversebarscomputesubb(graphbarnboncurstatic)
    graphbarnboncurstaticstr=str$(graphbarnboncurstatic)
    cpptmpfuncreturn=varptr$(reversebarscomputesubbcpp(varptr(graphbarnboncurstaticstr)))
    'refreshgrids
    tmpreverse(reversecount) = DATE$ + " " + TIME$ + " " + "Reverse " + importedfile(displayedfile) + " " + "From Date: " + Grid.Cell(rowgridoffset + 1 , clickedbarnb + chartstart) + " " + Grid.Cell(rowgridoffset + 2 , clickedbarnb + chartstart) + " till end"
    reversecount ++
END SUB

SUB reversebarscomputesubb(referencialk AS INTEGER)

    DIM i AS INTEGER , j AS INTEGER


    numbars = VAL(barsdisplayed.Text)

    DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    m = 1
    incr = 0

    DIM kbarlow AS DOUBLE , kbarlowprev AS DOUBLE
    DIM kbarhigh AS DOUBLE , kbarhighprev AS DOUBLE
    DIM kbaropen AS DOUBLE , kbaropenprev AS DOUBLE
    DIM kbarclose AS DOUBLE , kbarcloseprev AS DOUBLE
    DIM distcloseopen AS DOUBLE , distclosehigh AS DOUBLE , distcloselow AS DOUBLE
    DIM distopenclose AS DOUBLE , distopenhigh AS DOUBLE , distopenlow AS DOUBLE


    FOR k = referencialk TO chartbars(displayedfile)


        kbarlow = VAL(Gridtmp.Cell(rowgridoffset + 5 , k))
        kbarhigh = VAL(Gridtmp.Cell(rowgridoffset + 4 , k))
        kbaropen = VAL(Gridtmp.Cell(rowgridoffset + 3 , k))
        kbarlowprev = VAL(Gridtmp.Cell(rowgridoffset + 5 , referencialk - 1))
        kbarhighprev = VAL(Gridtmp.Cell(rowgridoffset + 4 , referencialk - 1))
        kbaropenprev = VAL(Gridtmp.Cell(rowgridoffset + 3 , referencialk - 1))
        kbarclose = VAL(Gridtmp.Cell(rowgridoffset + 6 , k))
        kbarcloseprev = VAL(Gridtmp.Cell(rowgridoffset + 6 , referencialk - 1))

        'if kbaropen>kbarclose then
        'distcloseopen=-1*(kbaropen-kbarclose)
        'end if
        'if kbaropen<kbarclose then
        'distcloseopen=kbarclose-kbaropen
        'end if

        IF kbaropen >= kbarclose THEN
            distopenclose = kbaropen - kbarclose
        END IF
        IF kbaropen < kbarclose THEN
            distopenclose = - 1 * (kbarclose - kbaropen)
        END IF

        'if kbarhigh>kbarclose then
        'distclosehigh=-1*(kbarhigh-kbarclose)
        'end if
        'if kbarhigh<kbarclose then
        'distclosehigh=kbarclose-kbarhigh
        'end if

        IF kbarhigh >= kbaropen THEN
            distopenhigh = - 1 * (kbarhigh - kbaropen)
        END IF
        IF kbarhigh < kbaropen THEN
            distopenhigh = kbaropen - kbarhigh
        END IF

        'if kbarlow>kbarclose then
        'distcloselow=-1*(kbarlow-kbarclose)
        'end if
        'if kbarlow<kbarclose then
        'distcloselow=kbarclose-kbarlow
        'end if

        IF kbarlow > kbaropen THEN
            distopenlow = - 1 * (kbarlow - kbaropen)
        END IF
        IF kbarlow <= kbaropen THEN
            distopenlow = kbaropen - kbarlow
        END IF

        'if kbarclose>kbarcloseprev then
        'gridtmp.cell(rowgridoffset+6,k)=str$(kbarcloseprev-(kbarclose-kbarcloseprev))
        'end if
        'if kbarclose<kbarcloseprev then
        'gridtmp.cell(rowgridoffset+6,k)=str$(kbarcloseprev+(kbarcloseprev-kbarclose))
        'end if

        IF kbaropen > kbarcloseprev THEN
            Gridtmp.Cell(rowgridoffset + 3 , k) = STR$(kbarcloseprev - (kbaropen - kbarcloseprev))
        END IF
        IF kbaropen < kbarcloseprev THEN
            Gridtmp.Cell(rowgridoffset + 3 , k) = STR$(kbarcloseprev + (kbarcloseprev - kbaropen))
        END IF

        'gridtmp.cell(rowgridoffset+3,k)=str$(val(gridtmp.cell(rowgridoffset+6,k))+distcloseopen)
        Gridtmp.Cell(rowgridoffset + 6 , k) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) + distopenclose)
        'gridtmp.cell(rowgridoffset+4,k)=str$(val(gridtmp.cell(rowgridoffset+6,k))+distcloselow)
        Gridtmp.Cell(rowgridoffset + 4 , k) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) + distopenlow)
        'gridtmp.cell(rowgridoffset+5,k)=str$(val(gridtmp.cell(rowgridoffset+6,k))+distclosehigh)
        Gridtmp.Cell(rowgridoffset + 5 , k) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) + distopenhigh)


        mixform.Caption = "Please wait while calculating... " + STR$(INT(100 / chartbars(displayedfile) * k)) + "% done"
        writealive
    NEXT k


    chartbarstmp(displayedfile) = chartbars(displayedfile)
    'chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))

    'tfmultm_click
    'mixerform

END SUB


SUB importfileaddition()
    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    DIM OpenDialog AS QOPENDIALOG
    IF OpenDialog.Execute THEN
        mixgrid.Cell(mixgridcolcount(displayedfile) , displayedfile) = OpenDialog.FileName
        mixgridcolcount(displayedfile) = mixgridcolcount(displayedfile) + 1
    END IF
    IF FILEEXISTS(OpenDialog.FileName) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF
    DIM file AS QFILESTREAM
    file.open(OpenDialog.FileName , 0)

    j = 0

    DO

        j ++

        getline$ = file.ReadLine

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        commapos = 0
        FOR i = 1 TO timepos - 1
            IF timepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        time = MID$(getline$ , commapos + 1 , LEN(getline$))
        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)

        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        vol = MID$(vol , 0 , LEN(vol))

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open
        Grid.Cell(rowgridoffset + 4 , j) = high
        Grid.Cell(rowgridoffset + 5 , j) = low
        Grid.Cell(rowgridoffset + 6 , j) = close
        Grid.Cell(rowgridoffset + 7 , j) = vol

    LOOP UNTIL file.eof
    file.close

    DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    m = 1
    incr = 0

    FOR k = 1 TO chartbars(displayedfile)
        FOR l = m TO j
            IF (Gridtmp.Cell(rowgridoffset + 1 , k) = Grid.Cell(rowgridoffset + 1 , l)) AND (Gridtmp.Cell(rowgridoffset + 2 , k) = Grid.Cell(rowgridoffset + 2 , l)) THEN
                incr ++
                m = l + 1
                Gridtmp.Cell(rowgridoffset + 1 , incr) = Gridtmp.Cell(rowgridoffset + 1 , k)
                Gridtmp.Cell(rowgridoffset + 2 , incr) = Gridtmp.Cell(rowgridoffset + 2 , k)
                Gridtmp.Cell(rowgridoffset + 3 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) + VAL(Grid.Cell(rowgridoffset + 3 , l)))
                Gridtmp.Cell(rowgridoffset + 4 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 4 , k)) + VAL(Grid.Cell(rowgridoffset + 4 , l)))
                Gridtmp.Cell(rowgridoffset + 5 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 5 , k)) + VAL(Grid.Cell(rowgridoffset + 5 , l)))
                Gridtmp.Cell(rowgridoffset + 6 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 6 , k)) + VAL(Grid.Cell(rowgridoffset + 6 , l)))
                Gridtmp.Cell(rowgridoffset + 7 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 7 , k)) + VAL(Grid.Cell(rowgridoffset + 7 , l)))
            END IF
        NEXT l
        mixform.Caption = "Please wait while calculating... " + STR$(INT(100 / chartbars(displayedfile) * k)) + "% done"
    NEXT k

    chartbarstmp(displayedfile) = incr
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))

    tfmultm_click
    mixerform
END SUB


SUB importfileadditiondel()
    IF additionlist.ItemIndex = 0 THEN
        SHOWMESSAGE "Main chart can't be removed from here."
        EXIT SUB
    END IF
    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    DIM file AS QFILESTREAM
    file.open(additionlist.Item(additionlist.ItemIndex) , 0)

    j = 0

    DO

        j ++

        getline$ = file.ReadLine

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        commapos = 0
        FOR i = 1 TO timepos - 1
            IF timepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        time = MID$(getline$ , commapos + 1 , LEN(getline$))
        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)

        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        vol = MID$(vol , 0 , LEN(vol))

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open
        Grid.Cell(rowgridoffset + 4 , j) = high
        Grid.Cell(rowgridoffset + 5 , j) = low
        Grid.Cell(rowgridoffset + 6 , j) = close
        Grid.Cell(rowgridoffset + 7 , j) = vol

    LOOP UNTIL file.eof
    file.close

    DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    m = 1
    incr = 0

    FOR k = 1 TO chartbars(displayedfile)
        FOR l = m TO j
            IF (Gridtmp.Cell(rowgridoffset + 1 , k) = Grid.Cell(rowgridoffset + 1 , l)) AND (Gridtmp.Cell(rowgridoffset + 2 , k) = Grid.Cell(rowgridoffset + 2 , l)) THEN
                incr ++
                m = l + 1
                Gridtmp.Cell(rowgridoffset + 1 , incr) = Gridtmp.Cell(rowgridoffset + 1 , k)
                Gridtmp.Cell(rowgridoffset + 2 , incr) = Gridtmp.Cell(rowgridoffset + 2 , k)
                Gridtmp.Cell(rowgridoffset + 3 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) - VAL(Grid.Cell(rowgridoffset + 3 , l)))
                Gridtmp.Cell(rowgridoffset + 4 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 4 , k)) - VAL(Grid.Cell(rowgridoffset + 4 , l)))
                Gridtmp.Cell(rowgridoffset + 5 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 5 , k)) - VAL(Grid.Cell(rowgridoffset + 5 , l)))
                Gridtmp.Cell(rowgridoffset + 6 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 6 , k)) - VAL(Grid.Cell(rowgridoffset + 6 , l)))
                Gridtmp.Cell(rowgridoffset + 7 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 7 , k)) - VAL(Grid.Cell(rowgridoffset + 7 , l)))
            END IF
        NEXT l
        mixform.Caption = "Please wait while calculating... " + STR$(INT(100 / chartbars(displayedfile) * k)) + "% done"
    NEXT k

    chartbarstmp(displayedfile) = incr
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))

    FOR i = additionlist.ItemIndex TO mixgridcolcount(displayedfile) - 1
        mixgrid.Cell(i , displayedfile) = mixgrid.Cell(i + 1 , displayedfile)
    NEXT i
    mixgridcolcount(displayedfile) = mixgridcolcount(displayedfile) - 1
    tfmultm_click
    mixerform
END SUB

SUB importfilesubtraction()
    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    DIM OpenDialog AS QOPENDIALOG
    IF OpenDialog.Execute THEN
        mixgrid2.Cell(mixgridcolcount2(displayedfile) , displayedfile) = OpenDialog.FileName
        mixgridcolcount2(displayedfile) = mixgridcolcount2(displayedfile) + 1
    END IF
    IF FILEEXISTS(OpenDialog.FileName) = FALSE THEN
        PRINT " file not found "
        EXIT SUB
    END IF
    DIM file AS QFILESTREAM
    file.open(OpenDialog.FileName , 0)

    j = 0

    DO

        j ++

        getline$ = file.ReadLine

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        commapos = 0
        FOR i = 1 TO timepos - 1
            IF timepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        time = MID$(getline$ , commapos + 1 , LEN(getline$))
        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)

        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        vol = MID$(vol , 0 , LEN(vol))

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open  'open
        Grid.Cell(rowgridoffset + 4 , j) = high  'high
        Grid.Cell(rowgridoffset + 5 , j) = low  'low
        Grid.Cell(rowgridoffset + 6 , j) = close  'close
        Grid.Cell(rowgridoffset + 7 , j) = vol  'vol

    LOOP UNTIL file.eof
    file.close

    DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    m = 1
    incr = 0

    FOR k = 1 TO chartbars(displayedfile)
        FOR l = m TO j
            IF (Gridtmp.Cell(rowgridoffset + 1 , k) = Grid.Cell(rowgridoffset + 1 , l)) AND (Gridtmp.Cell(rowgridoffset + 2 , k) = Grid.Cell(rowgridoffset + 2 , l)) THEN
                incr ++
                m = l + 1
                Gridtmp.Cell(rowgridoffset + 1 , incr) = Gridtmp.Cell(rowgridoffset + 1 , k)
                Gridtmp.Cell(rowgridoffset + 2 , incr) = Gridtmp.Cell(rowgridoffset + 2 , k)
                Gridtmp.Cell(rowgridoffset + 3 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) - VAL(Grid.Cell(rowgridoffset + 3 , l)))
                Gridtmp.Cell(rowgridoffset + 4 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 4 , k)) - VAL(Grid.Cell(rowgridoffset + 4 , l)))
                Gridtmp.Cell(rowgridoffset + 5 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 5 , k)) - VAL(Grid.Cell(rowgridoffset + 5 , l)))
                Gridtmp.Cell(rowgridoffset + 6 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 6 , k)) - VAL(Grid.Cell(rowgridoffset + 6 , l)))
                Gridtmp.Cell(rowgridoffset + 7 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 7 , k)) + VAL(Grid.Cell(rowgridoffset + 7 , l)))
            END IF
        NEXT l
        mixform.Caption = "Please wait while calculating... " + STR$(INT(100 / chartbars(displayedfile) * k)) + "% done"
    NEXT k

    chartbarstmp(displayedfile) = incr
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))

    tfmultm_click
    mixerform
END SUB

SUB importfilesubtractiondel()
    DIM date AS STRING , time AS STRING
    DIM open AS STRING , high AS STRING , low AS STRING , close AS STRING , vol AS STRING
    DIM datepos AS INTEGER
    DIM timepos AS INTEGER
    DIM openpos AS INTEGER
    DIM highpos AS INTEGER
    DIM lowpos AS INTEGER
    DIM closepos AS INTEGER
    DIM volpos AS INTEGER
    DIM separator AS STRING
    DIM commapos AS INTEGER
    DIM i AS INTEGER , j AS INTEGER
    DIM getline$ AS STRING

    datepos = VAL(form2Edit1.Text)
    timepos = VAL(form2Edit2.Text)
    openpos = VAL(form2Edit3.Text)
    highpos = VAL(form2Edit4.Text)
    lowpos = VAL(form2Edit5.Text)
    closepos = VAL(form2Edit6.Text)
    volpos = VAL(form2Edit7.Text)
    separator = VAL(form2Edit8.Text)
    numbars = VAL(barsdisplayed.Text)

    DIM file AS QFILESTREAM
    file.open(subtractionlist.Item(subtractionlist.ItemIndex) , 0)

    j = 0

    DO

        j ++

        getline$ = file.ReadLine

        commapos = 0
        FOR i = 1 TO datepos - 1
            IF datepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        date = MID$(getline$ , commapos + 1 , LEN(getline$))
        date = MID$(date , 0 , INSTR(0 , date , separator) - 1)

        commapos = 0
        FOR i = 1 TO timepos - 1
            IF timepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        time = MID$(getline$ , commapos + 1 , LEN(getline$))
        time = MID$(time , 0 , INSTR(0 , time , separator) - 1)

        commapos = 0
        FOR i = 1 TO openpos - 1
            IF openpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        open = MID$(getline$ , commapos + 1 , LEN(getline$))
        open = MID$(open , 0 , INSTR(0 , open , separator) - 1)

        commapos = 0
        FOR i = 1 TO highpos - 1
            IF highpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        high = MID$(getline$ , commapos + 1 , LEN(getline$))
        high = MID$(high , 0 , INSTR(0 , high , separator) - 1)

        commapos = 0
        FOR i = 1 TO lowpos - 1
            IF lowpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        low = MID$(getline$ , commapos + 1 , LEN(getline$))
        low = MID$(low , 0 , INSTR(0 , low , separator) - 1)

        commapos = 0
        FOR i = 1 TO closepos - 1
            IF closepos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        close = MID$(getline$ , commapos + 1 , LEN(getline$))
        close = MID$(close , 0 , INSTR(0 , close , separator) - 1)

        commapos = 0
        FOR i = 1 TO volpos - 1
            IF volpos = 1 THEN
                EXIT FOR
            END IF
            commapos = INSTR(commapos + 1 , getline$ , separator)
        NEXT i
        vol = MID$(getline$ , commapos + 1 , LEN(getline$))
        vol = MID$(vol , 0 , LEN(vol))

        Grid.Cell(rowgridoffset + 1 , j) = date
        Grid.Cell(rowgridoffset + 2 , j) = time
        Grid.Cell(rowgridoffset + 3 , j) = open
        Grid.Cell(rowgridoffset + 4 , j) = high
        Grid.Cell(rowgridoffset + 5 , j) = low
        Grid.Cell(rowgridoffset + 6 , j) = close
        Grid.Cell(rowgridoffset + 7 , j) = vol

    LOOP UNTIL file.eof
    file.close

    DIM k AS INTEGER , l AS INTEGER , m AS INTEGER , incr AS INTEGER
    m = 1
    incr = 0

    FOR k = 1 TO chartbars(displayedfile)
        FOR l = m TO j
            IF (Gridtmp.Cell(rowgridoffset + 1 , k) = Grid.Cell(rowgridoffset + 1 , l)) AND (Gridtmp.Cell(rowgridoffset + 2 , k) = Grid.Cell(rowgridoffset + 2 , l)) THEN
                incr ++
                m = l + 1
                Gridtmp.Cell(rowgridoffset + 1 , incr) = Gridtmp.Cell(rowgridoffset + 1 , k)
                Gridtmp.Cell(rowgridoffset + 2 , incr) = Gridtmp.Cell(rowgridoffset + 2 , k)
                Gridtmp.Cell(rowgridoffset + 3 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 3 , k)) + VAL(Grid.Cell(rowgridoffset + 3 , l)))
                Gridtmp.Cell(rowgridoffset + 4 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 4 , k)) + VAL(Grid.Cell(rowgridoffset + 4 , l)))
                Gridtmp.Cell(rowgridoffset + 5 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 5 , k)) + VAL(Grid.Cell(rowgridoffset + 5 , l)))
                Gridtmp.Cell(rowgridoffset + 6 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 6 , k)) + VAL(Grid.Cell(rowgridoffset + 6 , l)))
                Gridtmp.Cell(rowgridoffset + 7 , incr) = STR$(VAL(Gridtmp.Cell(rowgridoffset + 7 , k)) - VAL(Grid.Cell(rowgridoffset + 7 , l)))
            END IF
        NEXT l
        mixform.Caption = "Please wait while calculating... " + STR$(INT(100 / chartbars(displayedfile) * k)) + "% done"
    NEXT k

    chartbarstmp(displayedfile) = incr
    chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))

    FOR i = subtractionlist.ItemIndex TO mixgridcolcount2(displayedfile) - 1
        mixgrid2.Cell(i , displayedfile) = mixgrid2.Cell(i + 1 , displayedfile)
    NEXT i
    mixgridcolcount2(displayedfile) = mixgridcolcount2(displayedfile) - 1
    tfmultm_click
    mixerform
END SUB

SUB sepindiclicked
    IF trendlinebtn.Flat = 1 OR fibofanbtn.Flat = 1 OR fiboretbtn.Flat = 1 OR parabtn.Flat = 1 OR hlinebtn.Flat = 1 OR _
        vlinebtn.Flat = 1 OR sqrbtn.Flat = 1 OR tribtn.Flat = 1 OR circlebtn.Flat = 1 OR crossbtn.Flat = 1 OR invcirclebtn.Flat = 1 OR _
        textbtn.Flat = 1 OR aimingbtn.Flat = 1 OR handdbtn.Flat = 1 OR sinbtn.Flat = 1 OR logbtn.Flat = 1 OR expbtn.Flat = 1 OR ellipsebtn.Flat = 1 OR _
        pitchforkbtn.Flat = 1 OR orcyclesbtn.Flat = 1 THEN
        IF sepindiclick = 0 THEN
            sepindiclick = 1
            WITH canvas
                .bufcntreset
                .savebuffertmp
            END WITH

            DIM XVAL AS INTEGER , YVAL AS INTEGER
            'GetCursorPos(NPOS)
            'XVAL=NPOS.xpos
            'YVAL=NPOS.ypos
            'xval=xval-frmmain.left-canvas.left-4-mouseexcentricityx
            'yval=yval-frmmain.top-canvas.top-42-mouseexcentricityy
            XVAL = relativecordsepindix
            YVAL = relativecordsepindiy
            firstclicksepindix = XVAL
            firstclicksepindiy = YVAL
            IF textbtn.Flat = 1 THEN
                enterdrawtxt
            END IF
            IF aimingbtn.Flat = 1 AND graphclick = 0 THEN
                graphmousedown(0, xval+(canvas.left-graph.left) , (canvas.top-graph.top)+yval) 'button 0=left click, but 1=right click, but 2=mouse wheel click
                graphcursorpos(xval+(canvas.left-graph.left) , (canvas.top-graph.top)+yval)
                graphclicked
            END IF
            sepindiclicktimer.Enabled = 1
            EXIT SUB
        END IF
        IF sepindiclick = 1 THEN
            XVAL = mousemovesepindix
            YVAL = mousemovesepindiy
            secondclicksepindix = XVAL
            secondclicksepindiy = YVAL
            IF parabtn.Flat = 1 OR pitchforkbtn.Flat = 1 OR orcyclesbtn.Flat = 1 THEN
                'GetCursorPos(NPOS)
                'XVAL=NPOS.xpos
                'YVAL=NPOS.ypos
                'xval=xval-frmmain.left-canvas.left-4
                'yval=yval-frmmain.top-canvas.top-42                
                canvas.savebuffertmpsimplez
                sepindiclick = 2
                EXIT SUB
            END IF
            IF aimingbtn.Flat = 1 THEN
                graphclick = 0
                graphclicktimer.Enabled = 0
            END IF
            sepindiclick = 0
            sepindiclicktimer.Enabled = 0
            EXIT SUB
        END IF
        IF sepindiclick = 2 THEN
            sepindiclick = 0
            sepindiclicktimer.Enabled = 0
            EXIT SUB
        END IF
    END IF
END SUB

SUB enterdrawtxt
    DIM inputtxt AS qinputbox
    drawtxt = inputtxt.INPUT("Enter your text:")
    say drawtxt
END SUB


SUB graphmousedown(Button AS INTEGER , x AS INTEGER , y AS INTEGER)

    relativecordx = x
    relativecordy = y
    mousediffx=screen.mousex-relativecordx
    mousediffy=screen.mousey-relativecordy
    IF Button = 2 THEN
        IF graphclick = 0 THEN
            aimingbtn.Flat = 0
            aimingbtnclick
            graphclicked
            EXIT SUB
        END IF
        IF graphclick > 0 THEN
            IF aimingbtn.Flat = 1 THEN
                sepindiclick = 0
                sepindiclicktimer.Enabled = 0
            END IF
            graphclick = 0
            graphclicktimer.Enabled = 0
            firstclickgraph = 0
            aimingbtnclick
        END IF

        WITH Graph
            .restorebuffertmpz
        END WITH


        Graph.savebuffertmpsimple
        Graph.paintchart
                
        WITH canvas
            .restorebuffertmpz
        END WITH
        
        canvas.savebuffertmpsimple
        if showcanvas = 1 then
        canvas.paint
        end if

    END IF
    IF Button = 1 THEN

        IF cursorbtn.Flat = 1 THEN
            IF graphclick = 0 THEN
                graphcursorpos2
                graphbarnboncurstatic = graphbarnboncur
                DIM mousxval AS INTEGER , mousyval AS INTEGER
                mousxval = xvalgcp2
                mousyval = yvalgcp2
                DIM i AS INTEGER
                DIM ycurbtn AS INTEGER
                DIM prcurbtnplus AS DOUBLE
                DIM prcurbtnminus AS DOUBLE
                DIM clickedonobj AS INTEGER
                clickedonobj = 0
                ycurbtn = (pricechartpos(1,0) - graphpriceoncur) / (pricechartpos(1,0)-pricechartpos(0,0)) * (pricechartpos(0,1)-pricechartpos(1,1)) + pricechartpos(1,1)
                prcurbtnplus = pricechartpos(1,0) - (ycurbtn + 5 - pricechartpos(1,1)) / (pricechartpos(0,1)-pricechartpos(1,1)) * (pricechartpos(1,0)-pricechartpos(0,0))
                prcurbtnminus = pricechartpos(1,0) - (ycurbtn - 5 - pricechartpos(1,1)) / (pricechartpos(0,1)-pricechartpos(1,1)) * (pricechartpos(1,0)-pricechartpos(0,0))
                for i=0 to 1000
                if graphserialdateoncur=timechartpos(i,0) then
                exit for
                end if
                next i
                defint gsdtp=round((timechartpos(i+1,0)-timechartpos(i,0))/2)
                defint gsdtm=round((timechartpos(i,0)-timechartpos(i-1,0))/2)
                defint timepixelinterval=timechartpos(1,1)-timechartpos(0,1)
                FOR i = 1 TO trendlinesdb.RowCount
                    IF (VAL(trendlinesdb.Cell(1 , i)) <= prcurbtnminus AND _
                        VAL(trendlinesdb.Cell(1 , i)) >= prcurbtnplus AND _
                        VAL(trendlinesdb.Cell(3 , i)) <= graphserialdateoncur + gsdtp AND _
                        VAL(trendlinesdb.Cell(3 , i)) >= graphserialdateoncur - gsdtm) THEN
                        objectcursor.objtype = 1
                        objectcursor.offset = i
                        clickedonobj = 1
                        PopupMenu.Popup(xvalgcp2 , yvalgcp2)
                    END IF
                    IF (VAL(trendlinesdb.Cell(2 , i)) <= prcurbtnminus AND _
                        VAL(trendlinesdb.Cell(2 , i)) >= prcurbtnplus AND _
                        VAL(trendlinesdb.Cell(4 , i)) <= graphserialdateoncur + gsdtp AND _
                        VAL(trendlinesdb.Cell(4 , i)) >= graphserialdateoncur - gsdtm) THEN
                        objectcursor.objtype = 1
                        objectcursor.offset = i
                        clickedonobj = 1
                        PopupMenu.Popup(xvalgcp2 , yvalgcp2)
                    END IF
                NEXT i
                FOR i = 1 TO sqr2db.RowCount
                    IF (VAL(sqr2db.Cell(2 , i)) <= prcurbtnminus AND _
                        VAL(sqr2db.Cell(2 , i)) >= prcurbtnplus AND _
                        VAL(sqr2db.Cell(4 , i)) <= graphserialdateoncur + gsdtp AND _
                        VAL(sqr2db.Cell(4 , i)) >= graphserialdateoncur - gsdtm) THEN
                        objectcursor.objtype = 2
                        objectcursor.offset = i
                        clickedonobj = 1
                        PopupMenu.Popup(xvalgcp2 , yvalgcp2)
                    END IF
                NEXT i
                FOR i = 1 TO tri2db.RowCount
                    IF (VAL(tri2db.Cell(2 , i)) <= prcurbtnminus AND _
                        VAL(tri2db.Cell(2 , i)) >= prcurbtnplus AND _
                        VAL(tri2db.Cell(4 , i)) <= graphserialdateoncur + gsdtp AND _
                        VAL(tri2db.Cell(4 , i)) >= graphserialdateoncur - gsdtm) THEN
                        objectcursor.objtype = 3
                        objectcursor.offset = i
                        clickedonobj = 1
                        PopupMenu.Popup(xvalgcp2 , yvalgcp2)
                    END IF
                NEXT i
            END IF
            IF clickedonobj = 0 and button=0 THEN
                'graphcursorpos2
                clickedbarnb = graphbarnboncurstatic - chartstart
                justrefreshchart
                popupmenubar.Popup(mousxval , mousyval)
            END IF
            EXIT SUB
        END IF


        IF graphclick > 0 THEN
            IF aimingbtn.Flat = 1 THEN
                sepindiclick = 0
                sepindiclicktimer.Enabled = 0
            END IF
            graphclick = 0
            graphclicktimer.Enabled = 0
            firstclickgraph = 0
        END IF

        WITH Graph
            .restorebuffertmpz
        END WITH

        'with canvas
        '.restorebuffertmpz
        'end with
        'graph.visible=0
        'graph.visible=1
        Graph.savebuffertmpsimple
        Graph.paintchart
        'canvas.savebuffertmpsimple
        'canvas.paint
        WITH canvas
            .restorebuffertmpz
        END WITH
        
        canvas.savebuffertmpsimple
        if showcanvas = 1 then
        canvas.paint
        end if
    END IF

END SUB

SUB sepindimousedown(Button AS INTEGER , x AS INTEGER , y AS INTEGER)
    relativecordsepindix = x
    relativecordsepindiy = y
    mousediffsepindix=screen.mousex-relativecordsepindix
    mousediffsepindiy=screen.mousey-relativecordsepindiy
    IF Button = 2 THEN
        IF sepindiclick = 0 THEN
            aimingbtn.Flat = 0
            aimingbtnclick
            sepindiclicked
            EXIT SUB
        END IF
        IF sepindiclick > 0 THEN
            IF aimingbtn.Flat = 1 THEN
                graphclick = 0
                graphclicktimer.Enabled = 0
                firstclickgraph = 0
            END IF
            sepindiclick = 0
            sepindiclicktimer.Enabled = 0
            'firstclicksepindi = 0
            aimingbtnclick
        END IF

        WITH canvas
            .restorebuffertmpz
        END WITH


        canvas.savebuffertmpsimple
        canvas.paint
        
        WITH Graph
            .restorebuffertmpz
        END WITH

        Graph.savebuffertmpsimple
        Graph.paintchart

    END IF
    IF Button = 1 THEN
        IF sepindiclick > 0 THEN
            IF aimingbtn.Flat = 1 THEN
                graphclick = 0
                graphclicktimer.Enabled = 0
                firstclickgraph = 0
            END IF
            sepindiclick = 0
            sepindiclicktimer.Enabled = 0
        END IF

        'with graph
        '.restorebuffertmpz
        'end with

        WITH canvas
            .restorebuffertmpz
        END WITH
        'graph.visible=0
        'graph.visible=1
        'graph.savebuffertmpsimple
        'graph.paintchart
        canvas.savebuffertmpsimple
        canvas.paint
        
        WITH Graph
            .restorebuffertmpz
        END WITH

        Graph.savebuffertmpsimple
        Graph.paintchart
    END IF

END SUB

SUB clearbtnclick

    IF graphclick > 0 THEN
        IF aimingbtn.Flat = 1 THEN
            sepindiclick = 0
            sepindiclicktimer.Enabled = 0
        END IF
        graphclick = 0
        graphclicktimer.Enabled = 0
        firstclickgraph = 0
    END IF
    IF sepindiclick > 0 THEN
        IF aimingbtn.Flat = 1 THEN
            graphclick = 0
            graphclicktimer.Enabled = 0
        END IF
        sepindiclick = 0
        sepindiclicktimer.Enabled = 0
        'firstclicksepindi=0
    END IF

    WITH Graph
        .restorefirstbuffertmpz
    END WITH
    WITH canvas
        .restorefirstbuffertmpz
    END WITH
    WITH Graph
        .firstbufcntreset
        .savebuffertmp
        .paintchart
    END WITH
    WITH canvas
        .firstbufcntreset
        .savebuffertmp
        .paint
    END WITH


END SUB

SUB graphclicked

    IF polybtn.Flat = 1 THEN

        DIM XVAL AS INTEGER , YVAL AS INTEGER
        'GetCursorPos(NPOS)
        'XVAL=NPOS.xpos
        'YVAL=NPOS.ypos
        'xval=xval-frmmain.left-graph.left-5-mouseexcentricityx
        'yval=yval-frmmain.top-graph.top-43-mouseexcentricityy
        XVAL = relativecordx
        YVAL = relativecordy
        'firstclickgraph=1
        'firstclickgraphx=xval
        'firstclickgraphy=yval
        'firstclickgraphprice=graphpriceoncur
        'firstclickgraphtime=graphserialdateoncur

        ptl(ipoly).Parent = frmMain
        ptl(ipoly).Color = &h0000ff
        ptl(ipoly).Width = 6
        ptl(ipoly).Height = 6
        ptl(ipoly).Left = XVAL + Graph.Left
        ptl(ipoly).Top = YVAL + Graph.Top

        ptl(ipoly).OnMouseDown = pdown
        ptl(ipoly).OnMouseUp = pup
        ptl(ipoly).OnMouseMove = pmove
        ptl(ipoly).Visible = 1
        ptl(ipoly).Enabled = 1
        pbez.x = XVAL + Graph.Left
        pbez.y = YVAL + Graph.Top
        ptl(ipoly).tag = curve.Position
        curve.writeudt pbez


        IF ipoly > 0 AND bezier? = 0 THEN
            btypes(ipoly + 1) = PT_LINETO
        ELSE

            btypes(ipoly + 1) = PT_BEZIERTO
        END IF


        ipoly ++
        IF btype = 1 THEN
            btypes(ipoly) = PT_MOVETO

        END IF
        btype = 0

        operations

    END IF

    IF trendlinebtn.Flat = 1 OR fibofanbtn.Flat = 1 OR fiboretbtn.Flat = 1 OR parabtn.Flat = 1 OR hlinebtn.Flat = 1 OR _
        vlinebtn.Flat = 1 OR sqrbtn.Flat = 1 OR tribtn.Flat = 1 OR circlebtn.Flat = 1 OR crossbtn.Flat = 1 OR invcirclebtn.Flat = 1 OR _
        textbtn.Flat = 1 OR aimingbtn.Flat = 1 OR handdbtn.Flat = 1 OR sinbtn.Flat = 1 OR logbtn.Flat = 1 OR expbtn.Flat = 1 OR ellipsebtn.Flat = 1 OR _
        pitchforkbtn.Flat = 1 OR priceextbtn.Flat = 1 OR sq9fbtn.Flat = 1 OR sq144btn.Flat = 1 OR timeextbtn.Flat = 1 OR tsq9fbtn.Flat = 1 _
        OR tsq144btn.Flat = 1 OR pricecyclesbtn.Flat = 1 OR timecyclesbtn.Flat = 1 OR logspiralbtn.Flat = 1 OR pentagbtn.Flat = 1 OR orcyclesbtn.Flat = 1 _
        OR polygbtn.flat=1 OR sqr2btn.Flat = 1 OR tri2btn.Flat THEN

        IF graphclick = 0 THEN
            graphcursorpos2
            graphclick = 1
            WITH Graph
                .bufcntreset
                .savebuffertmp
            END WITH

            'DIM XVAL AS integer, YVAL AS integer
            'GetCursorPos(NPOS)
            'XVAL=NPOS.xpos
            'YVAL=NPOS.ypos
            'nposrela.xpos=npos.xpos
            'nposrela.ypos=npos.ypos
            'ScreenToClient(frmmain.handle,nposrela)
            'xval=xval-frmmain.left-graph.left-5-mouseexcentricityx
            'yval=yval-frmmain.top-graph.top-43-mouseexcentricityy
            XVAL = relativecordx
            YVAL = relativecordy
            'xval=nposrela.xpos
            'yval=nposrela.ypos
            firstclickgraph = 1
            firstclickgraphx = XVAL
            firstclickgraphy = YVAL
            firstclickgraphprice = graphpriceoncur
            defint i
            for i=0 to 1000
            if firstclickgraphx>=timechartpos(i,1) and firstclickgraphx<=timechartpos(i+1,1) then
            defdbl mypixelratio=(xval-timechartpos(i,1))/(timechartpos(i+1,1)-timechartpos(i,1))
            firstclickgraphtime=round((timechartpos(i+1,0)-timechartpos(i,0))*mypixelratio)+timechartpos(i,0)
            exit for
            end if
            next i
            
            'if fibofansymetryfrompointradio.checked=1 and symetryfrompoint=0 then
            '    graphcursorpos2
            '    secondclickgraphx = mousemovegraphx
            '    secondclickgraphy = mousemovegraphy
                
            'end if
            
            if fibofansymetryfrompointradio.checked=1 and symetryfrompoint=1 and fibofanbtn.Flat = 1 then
                'Graph.savebuffertmpsimplez
                graphcursorpos2 
                'graphclicktimer.Enabled = 1
                detpos
                
                'XVAL = mousemovegraphx
                'YVAL = mousemovegraphy
                secondclickgraphx = mousemovegraphx
                secondclickgraphy = mousemovegraphy  
                lastpointofsymetryx=mousemovegraphx
                lastpointofsymetryy=mousemovegraphy
                graphclick = 0                                                                         
                symetryfrompoint=0
                'graphclicktimer.Enabled = 0
                firstclickgraph = 0  
                EXIT SUB    
                
            end if                


            IF textbtn.Flat = 1 THEN
                enterdrawtxt
            END IF
            IF aimingbtn.Flat = 1 AND sepindiclick = 0 AND showcanvas = 1 THEN
                sepindimousedown(0, xval-(canvas.left-graph.left) , -1*(canvas.top-graph.top)+yval) 'button 0=left click, but 1=right click, but 2=mouse wheel click
                sepindicursorpos(xval-(canvas.left-graph.left) , -1*(canvas.top-graph.top)+yval)
                sepindiclicked
            END IF     
            
            graphclicktimer.Enabled = 1
            EXIT SUB
        END IF

        IF graphclick = 1 THEN            
            graphcursorpos2                   
            'GetCursorPos(NPOS)
            'XVAL=NPOS.xpos
            'YVAL=NPOS.ypos
            'xval=xval-frmmain.left-graph.left-4-mouseexcentricityx
            'yval=yval-frmmain.top-graph.top-43-mouseexcentricityy
            XVAL = mousemovegraphx
            YVAL = mousemovegraphy
            secondclickgraphx = XVAL
            secondclickgraphy = YVAL
            secondclickgraphprice = graphpriceoncur
            for i=0 to 1000
            if secondclickgraphx>=timechartpos(i,1) and secondclickgraphx<=timechartpos(i+1,1) then
            mypixelratio=(xval-timechartpos(i,1))/(timechartpos(i+1,1)-timechartpos(i,1))
            secondclickgraphtime=round((timechartpos(i+1,0)-timechartpos(i,0))*mypixelratio)+timechartpos(i,0)
            exit for
            end if
            next i
            IF parabtn.Flat = 1 OR pitchforkbtn.Flat = 1 OR priceextbtn.Flat = 1 OR timeextbtn.Flat = 1 OR orcyclesbtn.Flat = 1 _
            OR (sinbtn.flat=1 and sinfromtrendlineradio.checked=1) THEN
                Graph.savebuffertmpsimplez
                IF parabtn.Flat = 1 AND graphclick = 1 THEN
                paraoffset ++
                paradb.Cell(1 , paraoffset) = STR$(firstclickgraphprice)
                paradb.Cell(2 , paraoffset) = STR$(secondclickgraphprice)
                paradb.Cell(4 , paraoffset) = Format$("%12.0f", firstclickgraphtime)
                paradb.Cell(5 , paraoffset) = Format$("%12.0f", secondclickgraphtime)
                END IF
                graphclick = 2                
                EXIT SUB
            END IF            
            IF aimingbtn.Flat = 1 THEN
                sepindiclick = 0
                sepindiclicktimer.Enabled = 0
            END IF
            graphclick = 0
            graphclicktimer.Enabled = 0
            firstclickgraph = 0
            IF trendlinebtn.Flat = 1 THEN
                trendlinesoffset ++
                trendlinesdb.Cell(1 , trendlinesoffset) = STR$(firstclickgraphprice)
                trendlinesdb.Cell(2 , trendlinesoffset) = STR$(secondclickgraphprice)
                trendlinesdb.Cell(3 , trendlinesoffset) = Format$("%12.0f", firstclickgraphtime)
                trendlinesdb.Cell(4 , trendlinesoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF fibofanbtn.Flat = 1 THEN
                fibofanoffset ++
                fibofandb.Cell(1 , fibofanoffset) = STR$(firstclickgraphprice)
                fibofandb.Cell(2 , fibofanoffset) = STR$(secondclickgraphprice)
                fibofandb.Cell(3 , fibofanoffset) = Format$("%12.0f", firstclickgraphtime)
                fibofandb.Cell(4 , fibofanoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF fiboretbtn.Flat = 1 THEN
                fiboretoffset ++
                fiboretdb.Cell(1 , fiboretoffset) = STR$(firstclickgraphprice)
                fiboretdb.Cell(2 , fiboretoffset) = STR$(secondclickgraphprice)
                fiboretdb.Cell(3 , fiboretoffset) = Format$("%12.0f", firstclickgraphtime)
                fiboretdb.Cell(4 , fiboretoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF            
            IF hlinebtn.Flat = 1 THEN
                hlineoffset ++
                hlinedb.Cell(1 , hlineoffset) = STR$(firstclickgraphprice)
                hlinedb.Cell(2 , hlineoffset) = STR$(secondclickgraphprice)
                hlinedb.Cell(3 , hlineoffset) = Format$("%12.0f", firstclickgraphtime)
                hlinedb.Cell(4 , hlineoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF vlinebtn.Flat = 1 THEN
                vlineoffset ++
                vlinedb.Cell(1 , vlineoffset) = STR$(firstclickgraphprice)
                vlinedb.Cell(2 , vlineoffset) = STR$(secondclickgraphprice)
                vlinedb.Cell(3 , vlineoffset) = Format$("%12.0f", firstclickgraphtime)
                vlinedb.Cell(4 , vlineoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF sqrbtn.Flat = 1 THEN
                sqroffset ++
                sqrdb.Cell(1 , sqroffset) = STR$(firstclickgraphprice)
                sqrdb.Cell(2 , sqroffset) = STR$(secondclickgraphprice)
                sqrdb.Cell(3 , sqroffset) = Format$("%12.0f", firstclickgraphtime)
                sqrdb.Cell(4 , sqroffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF tribtn.Flat = 1 THEN
                trioffset ++
                tridb.Cell(1 , trioffset) = STR$(firstclickgraphprice)
                tridb.Cell(2 , trioffset) = STR$(secondclickgraphprice)
                tridb.Cell(3 , trioffset) = Format$("%12.0f", firstclickgraphtime)
                tridb.Cell(4 , trioffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF sqr2btn.Flat = 1 THEN
                sqr2offset ++
                sqr2db.Cell(1 , sqr2offset) = STR$(firstclickgraphprice)
                sqr2db.Cell(2 , sqr2offset) = STR$(secondclickgraphprice)
                sqr2db.Cell(3 , sqr2offset) = Format$("%12.0f", firstclickgraphtime)
                sqr2db.Cell(4 , sqr2offset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF tri2btn.Flat = 1 THEN
                tri2offset ++
                tri2db.Cell(1 , tri2offset) = STR$(firstclickgraphprice)
                tri2db.Cell(2 , tri2offset) = STR$(secondclickgraphprice)
                tri2db.Cell(3 , tri2offset) = Format$("%12.0f", firstclickgraphtime)
                tri2db.Cell(4 , tri2offset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF circlebtn.Flat = 1 THEN
                circleoffset ++
                circledb.Cell(1 , circleoffset) = STR$(firstclickgraphprice)
                circledb.Cell(2 , circleoffset) = STR$(secondclickgraphprice)
                circledb.Cell(3 , circleoffset) = Format$("%12.0f", firstclickgraphtime)
                circledb.Cell(4 , circleoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF crossbtn.Flat = 1 THEN
                crossoffset ++
                crossdb.Cell(1 , crossoffset) = STR$(firstclickgraphprice)
                crossdb.Cell(2 , crossoffset) = STR$(secondclickgraphprice)
                crossdb.Cell(3 , crossoffset) = Format$("%12.0f", firstclickgraphtime)
                crossdb.Cell(4 , crossoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF invcirclebtn.Flat = 1 THEN
                invcircleoffset ++
                invcircledb.Cell(1 , invcircleoffset) = STR$(firstclickgraphprice)
                invcircledb.Cell(2 , invcircleoffset) = STR$(secondclickgraphprice)
                invcircledb.Cell(3 , invcircleoffset) = Format$("%12.0f", firstclickgraphtime)
                invcircledb.Cell(4 , invcircleoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF textbtn.Flat = 1 THEN
                textoffset ++
                textdb.Cell(1 , textoffset) = STR$(firstclickgraphprice)
                textdb.Cell(2 , textoffset) = STR$(secondclickgraphprice)
                textdb.Cell(3 , textoffset) = Format$("%12.0f", firstclickgraphtime)
                textdb.Cell(4 , textoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF aimingbtn.Flat = 1 THEN
                aimingoffset ++
                aimingdb.Cell(1 , aimingoffset) = STR$(firstclickgraphprice)
                aimingdb.Cell(2 , aimingoffset) = STR$(secondclickgraphprice)
                aimingdb.Cell(3 , aimingoffset) = Format$("%12.0f", firstclickgraphtime)
                aimingdb.Cell(4 , aimingoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF sinbtn.Flat = 1 THEN
                sinoffset ++
                sindb.Cell(1 , sinoffset) = STR$(firstclickgraphprice)
                sindb.Cell(2 , sinoffset) = STR$(secondclickgraphprice)
                sindb.Cell(3 , sinoffset) = Format$("%12.0f", firstclickgraphtime)
                sindb.Cell(4 , sinoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF logbtn.Flat = 1 THEN
                logoffset ++
                logdb.Cell(1 , logoffset) = STR$(firstclickgraphprice)
                logdb.Cell(2 , logoffset) = STR$(secondclickgraphprice)
                logdb.Cell(3 , logoffset) = Format$("%12.0f", firstclickgraphtime)
                logdb.Cell(4 , logoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF expbtn.Flat = 1 THEN
                expoffset ++
                expdb.Cell(1 , expoffset) = STR$(firstclickgraphprice)
                expdb.Cell(2 , expoffset) = STR$(secondclickgraphprice)
                expdb.Cell(3 , expoffset) = Format$("%12.0f", firstclickgraphtime)
                expdb.Cell(4 , expoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF ellipsebtn.Flat = 1 THEN
                ellipseoffset ++
                ellipsedb.Cell(1 , ellipseoffset) = STR$(firstclickgraphprice)
                ellipsedb.Cell(2 , ellipseoffset) = STR$(secondclickgraphprice)
                ellipsedb.Cell(3 , ellipseoffset) = Format$("%12.0f", firstclickgraphtime)
                ellipsedb.Cell(4 , ellipseoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF pentagbtn.Flat = 1 THEN
                pentagoffset ++
                pentagdb.Cell(1 , pentagoffset) = STR$(firstclickgraphprice)
                pentagdb.Cell(2 , pentagoffset) = STR$(secondclickgraphprice)
                pentagdb.Cell(3 , pentagoffset) = Format$("%12.0f", firstclickgraphtime)
                pentagdb.Cell(4 , pentagoffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            IF sq9fbtn.Flat = 1 THEN
                sq9foffset ++
                sq9fdb.Cell(1 , sq9foffset) = STR$(firstclickgraphprice)
                sq9fdb.Cell(2 , sq9foffset) = STR$(secondclickgraphprice)
                sq9fdb.Cell(3 , sq9foffset) = Format$("%12.0f", firstclickgraphtime)
                sq9fdb.Cell(4 , sq9foffset) = Format$("%12.0f", secondclickgraphtime)
            END IF
            if fibofansymetryfrompointradio.checked=1 and symetryfrompoint=0 and fibofanbtn.Flat = 1 then
                symetryfrompoint=1                
            end if
            EXIT SUB
        END IF
        IF graphclick = 2 THEN
            xval=relativecordx
            graphcursorpos2            
            for i=0 to 1000
            if xval>=timechartpos(i,1) and xval<=timechartpos(i+1,1) then
            mypixelratio=(xval-timechartpos(i,1))/(timechartpos(i+1,1)-timechartpos(i,1))
            defint thirdclickgraphtime=round((timechartpos(i+1,0)-timechartpos(i,0))*mypixelratio)+timechartpos(i,0)
            exit for
            end if
            next i
            IF parabtn.Flat = 1 AND graphclick = 2 THEN
                paradb.Cell(3 , paraoffset) = STR$(graphpriceoncur)
                paradb.Cell(6 , paraoffset) = Format$("%12.0f", thirdclickgraphtime)
            END IF
            graphclick = 0
            graphclicktimer.Enabled = 0
            EXIT SUB
        END IF
    END IF

    IF cursorbtn.Flat = 1 THEN
        IF graphclick = 0 THEN
            graphcursorpos2
            DIM mousxval AS INTEGER , mousyval AS INTEGER
            graphbarnboncurstatic = graphbarnboncur
            mousxval = xvalgcp2
            mousyval = yvalgcp2
            clickedbarnb = graphbarnboncur - chartstart
            justrefreshchart
            'xvalgcp2=xval+frmmain.left+4+mouseexcentricityx+graph.left
            'yvalgcp2=yval+frmmain.top+43+mouseexcentricityy+graph.top
            Graph.buffer.TextOut(mousxval - frmMain.Left - 4 - mouseexcentricityx - Graph.Left , mousyval - frmMain.Top - 43 - mouseexcentricityy - Graph.Top , "Bar #" + STR$(clickedbarnb + chartstart) , textcolor , &hffffff)
            Graph.buffer.TextOut(mousxval - frmMain.Left - 4 - mouseexcentricityx - Graph.Left , mousyval - frmMain.Top - 43 - mouseexcentricityy - Graph.Top + 15 , "Date: " + Grid.Cell(rowgridoffset + 1 , clickedbarnb + chartstart) , textcolor , &hffffff)
            Graph.buffer.TextOut(mousxval - frmMain.Left - 4 - mouseexcentricityx - Graph.Left , mousyval - frmMain.Top - 43 - mouseexcentricityy - Graph.Top + 30 , "Time: " + Grid.Cell(rowgridoffset + 2 , clickedbarnb + chartstart) , textcolor , &hffffff)
            Graph.buffer.TextOut(mousxval - frmMain.Left - 4 - mouseexcentricityx - Graph.Left , mousyval - frmMain.Top - 43 - mouseexcentricityy - Graph.Top + 45 , "Open: " + Grid.Cell(rowgridoffset + 3 , clickedbarnb + chartstart) , textcolor , &hffffff)
            Graph.buffer.TextOut(mousxval - frmMain.Left - 4 - mouseexcentricityx - Graph.Left , mousyval - frmMain.Top - 43 - mouseexcentricityy - Graph.Top + 60 , "High: " + Grid.Cell(rowgridoffset + 4 , clickedbarnb + chartstart) , textcolor , &hffffff)
            Graph.buffer.TextOut(mousxval - frmMain.Left - 4 - mouseexcentricityx - Graph.Left , mousyval - frmMain.Top - 43 - mouseexcentricityy - Graph.Top + 75 , "Low: " + Grid.Cell(rowgridoffset + 5 , clickedbarnb + chartstart) , textcolor , &hffffff)
            Graph.buffer.TextOut(mousxval - frmMain.Left - 4 - mouseexcentricityx - Graph.Left , mousyval - frmMain.Top - 43 - mouseexcentricityy - Graph.Top + 90 , "Close: " + Grid.Cell(rowgridoffset + 6 , clickedbarnb + chartstart) , textcolor , &hffffff)
            Graph.buffer.TextOut(mousxval - frmMain.Left - 4 - mouseexcentricityx - Graph.Left , mousyval - frmMain.Top - 43 - mouseexcentricityy - Graph.Top + 105 , "Volume: " + Grid.Cell(rowgridoffset + 7 , clickedbarnb + chartstart) , textcolor , &hffffff)
            'defstr barstr=str$(chartbars(displayedfile)-(clickedbarnb + chartstart))
            'defstr cntbarseditstr=cntbarsedit.Text:cpptmpfuncreturn=varptr$(useindifunc(varptr(cntbarseditstr)))
            'cpptmpfuncreturn=varptr$(timecpp(varptr(barstr)))
            'Graph.buffer.TextOut(mousxval - frmMain.Left - 4 - mouseexcentricityx - Graph.Left , mousyval - frmMain.Top - 43 - mouseexcentricityy - Graph.Top + 120 , "timecpp: " + cpptmpfuncreturn , textcolor , &hffffff)
            Graph.savebuffertmp
            Graph.paintchart
            say "Bar #" + STR$(clickedbarnb + chartstart) + " ."+_
            " Date: " + Grid.Cell(rowgridoffset + 1 , clickedbarnb + chartstart) + " ."+_
            " Time: " + Grid.Cell(rowgridoffset + 2 , clickedbarnb + chartstart) + " ."+_
            " Open: " + Grid.Cell(rowgridoffset + 3 , clickedbarnb + chartstart) + " ."+_
            " High: " + Grid.Cell(rowgridoffset + 4 , clickedbarnb + chartstart) + " ."+_
            " Low: " + Grid.Cell(rowgridoffset + 5 , clickedbarnb + chartstart) + " ."+_
            " Close: " + Grid.Cell(rowgridoffset + 6 , clickedbarnb + chartstart) + " ."+_
            " Volume: " + Grid.Cell(rowgridoffset + 7 , clickedbarnb + chartstart) + " ."
        END IF
        IF graphclick = 1 THEN
            graphclick = 0
            moveobjcurtimer.Enabled = 0
            justrefreshchart
        END IF
    END IF


END SUB

SUB timerovergraphclick
    DetPos
END SUB

SUB timeroversepindiclick
    DetPos2
END SUB

SUB moveobjectclick(Sender AS QMENUITEM)

    IF graphclick = 0 THEN
        'graphcursorpos2
        objectcursoroperation = sender.Caption
        graphclick = 1
        'with graph
        '.bufcntreset
        '.savebuffertmp
        'end with

        'DIM XVAL AS integer, YVAL AS integer
        'GetCursorPos(NPOS)
        'XVAL=NPOS.xpos
        'YVAL=NPOS.ypos
        'xval=xval-frmmain.left-graph.left-5-mouseexcentricityx
        'yval=yval-frmmain.top-graph.top-43-mouseexcentricityy
        'firstclickgraph=1
        'firstclickgraphx=xval
        'firstclickgraphy=yval
        'firstclickgraphprice=graphpriceoncur
        'firstclickgraphtime=graphserialdateoncur
        'if textbtn.flat=1 then
        'enterdrawtxt
        'end if
        'if aimingbtn.flat=1 and sepindiclick=0 and showcanvas=1 then
        'sepindiclicked
        'end if
        IF objectcursoroperation = "Duplicate" THEN
            IF objectcursor.objtype = 1 THEN
                trendlinesoffset ++
            END IF
        END IF
        WITH Graph
            .bufcntreset
            .savebuffertmp
        END WITH
        moveobjcurtimer.Enabled = 1

        'EXIT SUB
    END IF

    'firstclickgraph=0


END SUB

SUB moveobjectcursor
    'graphcursorpos2
    DIM XVAL AS INTEGER , YVAL AS INTEGER
    defint i
    defdbl mytimeratio
    'GetCursorPos(NPOS)
    'XVAL=NPOS.xpos
    'YVAL=NPOS.ypos
    'xval=xval-frmmain.left-graph.left-4--mouseexcentricityx
    'yval=yval-frmmain.top-graph.top-43-mouseexcentricityy
    XVAL = mousemovegraphx
    YVAL = mousemovegraphy

    DIM xcur1px AS DOUBLE  'integer
    DIM xcur2px AS DOUBLE  'integer
    DIM ycur1px AS DOUBLE  'integer
    DIM ycur2px AS DOUBLE  'integer
    
    select case objectcursor.objtype
    case 1:
    ycur1 = VAL(trendlinesdb.Cell(1 , objectcursor.offset))
    ycur2 = VAL(trendlinesdb.Cell(2 , objectcursor.offset))
    xcur1 = VAL(trendlinesdb.Cell(3 , objectcursor.offset))
    xcur2 = VAL(trendlinesdb.Cell(4 , objectcursor.offset))
    case 2:
    ycur1 = VAL(sqr2db.Cell(1 , objectcursor.offset))
    ycur2 = VAL(sqr2db.Cell(2 , objectcursor.offset))
    xcur1 = VAL(sqr2db.Cell(3 , objectcursor.offset))
    xcur2 = VAL(sqr2db.Cell(4 , objectcursor.offset))
    case 3:
    ycur1 = VAL(tri2db.Cell(1 , objectcursor.offset))
    ycur2 = VAL(tri2db.Cell(2 , objectcursor.offset))
    xcur1 = VAL(tri2db.Cell(3 , objectcursor.offset))
    xcur2 = VAL(tri2db.Cell(4 , objectcursor.offset))
    end select
    
    ycur1px = (pricechartpos(1,0) - ycur1) / (pricechartpos(1,0)-pricechartpos(0,0)) * (pricechartpos(0,1)-pricechartpos(1,1)) + pricechartpos(1,1)
    ycur2px = (pricechartpos(1,0) - ycur2) / (pricechartpos(1,0)-pricechartpos(0,0)) * (pricechartpos(0,1)-pricechartpos(1,1)) + pricechartpos(1,1)
    'xcur1px = (xcur1 - graphserialdatebegin) / graphserialdatespace * graphhspace + graphhbegin
    'xcur2px = (xcur2 - graphserialdatebegin) / graphserialdatespace * graphhspace + graphhbegin  
  
    for i=0 to 1000
            if xcur1>=timechartpos(i,0) and xcur1<=timechartpos(i+1,0) then
            mytimeratio=((xcur1)-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            xcur1px=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
    next i
    for i=0 to 1000
            if xcur2>=timechartpos(i,0) and xcur2<=timechartpos(i+1,0) then
            mytimeratio=((xcur2)-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            xcur2px=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
    next i
    'print str$(xcur1px)
    'print str$(xcur1px)+" "+str$(xcur2px)
    WITH Graph

defdbl unixtimeratio
defint timepixelinterval
defstr myunixtimestr
defdbl pricepixelratio

        IF objectcursor.objtype = 1 THEN

            '.drawp(0,xcur1px+xval-xcur1px,ycur1px+yval-ycur1px,xcur2px+xval-xcur2px,ycur2px+yval-ycur2px,0,0)
            .drawp(0 , XVAL , YVAL , XVAL + xcur2px - xcur1px , YVAL + ycur2px - ycur1px , 0 , 0)

timepixelinterval=timechartpos(1,1)-timechartpos(0,1)
for i=0 to 1000
if xval>=timechartpos(i,1)-timepixelinterval/2 and xval<timechartpos(i,1)+timepixelinterval/2 then
unixtimeratio=timechartpos(i,0)
xcur1=unixtimeratio
    exit for
end if    
'print str$(xcur1)
next i
for i=0 to 1000
if (XVAL + xcur2px - xcur1px)>=timechartpos(i,1)-timepixelinterval/2 and (XVAL + xcur2px - xcur1px)<timechartpos(i,1)+timepixelinterval/2 then
unixtimeratio=timechartpos(i,0)
xcur2=unixtimeratio
    exit for
end if    
next i

            pricepixelratio=(pricechartpos(0,1)-yval)/(pricechartpos(0,1)-pricechartpos(1,1))
            ycur1=(pricechartpos(1,0)-pricechartpos(0,0))*pricepixelratio+pricechartpos(0,0)
            'print str$(ycur1)
            'graphpriceoncur=val(Format$("%12.5f", graphpriceoncur))
            pricepixelratio=(pricechartpos(0,1)-(YVAL + ycur2px - ycur1px))/(pricechartpos(0,1)-pricechartpos(1,1))
            ycur2=(pricechartpos(1,0)-pricechartpos(0,0))*pricepixelratio+pricechartpos(0,0)
            IF objectcursoroperation = "Move" THEN
                trendlinesdb.Cell(1 , objectcursor.offset) = STR$(ycur1)
                trendlinesdb.Cell(2 , objectcursor.offset) = STR$(ycur2)
                trendlinesdb.Cell(3 , objectcursor.offset) = STR$(xcur1)
                trendlinesdb.Cell(4 , objectcursor.offset) = STR$(xcur2)

            END IF

            IF objectcursoroperation = "Duplicate" THEN
                trendlinesdb.Cell(1 , trendlinesoffset) = STR$(ycur1)
                trendlinesdb.Cell(2 , trendlinesoffset) = STR$(ycur2)
                trendlinesdb.Cell(3 , trendlinesoffset) = STR$(xcur1)
                trendlinesdb.Cell(4 , trendlinesoffset) = STR$(xcur2)

            END IF

        END IF
        
        
IF objectcursor.objtype = 2 THEN

            '.drawp(0,xcur1px+xval-xcur1px,ycur1px+yval-ycur1px,xcur2px+xval-xcur2px,ycur2px+yval-ycur2px,0,0)
            
            .drawp(31 , xcur1px , ycur1px , XVAL , YVAL , 0 , 0)

timepixelinterval=timechartpos(1,1)-timechartpos(0,1)
for i=0 to 1000
if xval>=timechartpos(i,1)-timepixelinterval/2 and xval<timechartpos(i,1)+timepixelinterval/2 then
unixtimeratio=timechartpos(i,0)
xcur1=unixtimeratio
    exit for
end if    
'print str$(xcur1)
next i

            pricepixelratio=(pricechartpos(0,1)-yval)/(pricechartpos(0,1)-pricechartpos(1,1))
            ycur1=(pricechartpos(1,0)-pricechartpos(0,0))*pricepixelratio+pricechartpos(0,0)
            'print str$(ycur1)
            'graphpriceoncur=val(Format$("%12.5f", graphpriceoncur))

            IF objectcursoroperation = "Rotate" THEN
                sqr2db.Cell(2 , objectcursor.offset) = STR$(ycur1)
                sqr2db.Cell(4 , objectcursor.offset) = STR$(xcur1)

            END IF

'            IF objectcursoroperation = "Duplicate" THEN
'                trendlinesdb.Cell(1 , trendlinesoffset) = STR$(ycur1)
'                trendlinesdb.Cell(2 , trendlinesoffset) = STR$(ycur2)
'                trendlinesdb.Cell(3 , trendlinesoffset) = STR$(xcur1)
'                trendlinesdb.Cell(4 , trendlinesoffset) = STR$(xcur2)
'
'            END IF

        END IF  
        
IF objectcursor.objtype = 3 THEN

            '.drawp(0,xcur1px+xval-xcur1px,ycur1px+yval-ycur1px,xcur2px+xval-xcur2px,ycur2px+yval-ycur2px,0,0)
            
            .drawp(32 , xcur1px , ycur1px , XVAL , YVAL , 0 , 0)

timepixelinterval=timechartpos(1,1)-timechartpos(0,1)
for i=0 to 1000
if xval>=timechartpos(i,1)-timepixelinterval/2 and xval<timechartpos(i,1)+timepixelinterval/2 then
unixtimeratio=timechartpos(i,0)
xcur1=unixtimeratio
    exit for
end if    
'print str$(xcur1)
next i

            pricepixelratio=(pricechartpos(0,1)-yval)/(pricechartpos(0,1)-pricechartpos(1,1))
            ycur1=(pricechartpos(1,0)-pricechartpos(0,0))*pricepixelratio+pricechartpos(0,0)
            'print str$(ycur1)
            'graphpriceoncur=val(Format$("%12.5f", graphpriceoncur))

            IF objectcursoroperation = "Rotate" THEN
                tri2db.Cell(2 , objectcursor.offset) = STR$(ycur1)
                tri2db.Cell(4 , objectcursor.offset) = STR$(xcur1)

            END IF

'            IF objectcursoroperation = "Duplicate" THEN
'                trendlinesdb.Cell(1 , trendlinesoffset) = STR$(ycur1)
'                trendlinesdb.Cell(2 , trendlinesoffset) = STR$(ycur2)
'                trendlinesdb.Cell(3 , trendlinesoffset) = STR$(xcur1)
'                trendlinesdb.Cell(4 , trendlinesoffset) = STR$(xcur2)
'
'            END IF

        END IF              
        
        .savebuffertmp
        .paintchart
        'end with
    END WITH

END SUB


SUB DetPos
    DIM XVAL AS INTEGER , YVAL AS INTEGER
    'GetCursorPos(NPOS)
    'XVAL=NPOS.xpos
    'YVAL=NPOS.ypos
    'xval=xval-frmmain.left-graph.left-4--mouseexcentricityx
    'yval=yval-frmmain.top-graph.top-43-mouseexcentricityy
    'XVAL = mousemovegraphx
    'YVAL = mousemovegraphy
    xval=screen.mousex-mousediffx    
    yval=screen.mousey-mousediffy
    WITH Graph

        IF trendlinebtn.Flat = 1 THEN
            .drawp(0 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF fibofanbtn.Flat = 1 THEN
            .drawp(1 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , secondclickgraphx , secondclickgraphy)
        END IF
        IF fiboretbtn.Flat = 1 THEN
            .drawp(2 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF parabtn.Flat = 1 AND graphclick = 1 THEN
            .drawp(0 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF parabtn.Flat = 1 AND graphclick = 2 THEN
            .drawp(3 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , secondclickgraphx , secondclickgraphy)
        END IF
        IF pitchforkbtn.Flat = 1 AND graphclick = 1 THEN
            .drawp(0 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF pitchforkbtn.Flat = 1 AND graphclick = 2 THEN
            .drawp(17 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , secondclickgraphx , secondclickgraphy)
        END IF
        IF priceextbtn.Flat = 1 AND graphclick = 1 THEN
            .drawp(0 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF priceextbtn.Flat = 1 AND graphclick = 2 THEN
            .drawp(18 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , secondclickgraphx , secondclickgraphy)
        END IF

        IF timeextbtn.Flat = 1 AND graphclick = 1 THEN
            .drawp(0 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF timeextbtn.Flat = 1 AND graphclick = 2 THEN
            .drawp(21 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , secondclickgraphx , secondclickgraphy)
        END IF

        IF hlinebtn.Flat = 1 THEN
            .drawp(4 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF vlinebtn.Flat = 1 THEN
            .drawp(5 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF sqrbtn.Flat = 1 THEN
            .drawp(6 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF tribtn.Flat = 1 THEN
            .drawp(7 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF circlebtn.Flat = 1 THEN
            .drawp(8 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF crossbtn.Flat = 1 THEN
            .drawp(9 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF invcirclebtn.Flat = 1 THEN
            .drawp(10 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF textbtn.Flat = 1 THEN
            Graph.buffer.TextOut(firstclickgraphx , firstclickgraphy , drawtxt , textcolor , &hffffff)
            graphclick = 0
            graphclicktimer.Enabled = 0
        END IF
        IF aimingbtn.Flat = 1 THEN
            .drawp(11 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF handdbtn.Flat = 1 THEN
            .drawp(12 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF (sinbtn.Flat = 1 and horizsinradio.checked=1) THEN
            .drawp(13 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF logbtn.Flat = 1 THEN
            .drawp(14 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF expbtn.Flat = 1 THEN
            .drawp(15 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF ellipsebtn.Flat = 1 THEN
            .drawp(16 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF sq9fbtn.Flat = 1 THEN
            .drawp(19 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF tsq9fbtn.Flat = 1 THEN
            .drawp(22 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF sq144btn.Flat = 1 THEN
            .drawp(20 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF tsq144btn.Flat = 1 THEN
            .drawp(23 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF pricecyclesbtn.Flat = 1 THEN
            .drawp(24 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF timecyclesbtn.Flat = 1 THEN
            .drawp(25 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF logspiralbtn.Flat = 1 THEN
            .drawp(26 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF pentagbtn.Flat = 1 THEN
            .drawp(27 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF orcyclesbtn.Flat = 1 AND graphclick = 1 THEN
            .drawp(0 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF orcyclesbtn.Flat = 1 AND graphclick = 2 THEN
            .drawp(28 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , secondclickgraphx , secondclickgraphy)
        END IF
        if (sinbtn.flat=1 and sinfromtrendlineradio.checked=1) AND graphclick = 1 then
            .drawp(0 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        end if
        if (sinbtn.flat=1 and sinfromtrendlineradio.checked=1) AND graphclick = 2 then
            .drawp(30 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , secondclickgraphx , secondclickgraphy)
        end if
        IF polygbtn.Flat = 1 THEN
            .drawp(29 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF sqr2btn.Flat = 1 THEN
            .drawp(31 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        IF tri2btn.Flat = 1 THEN
            .drawp(32 , firstclickgraphx , firstclickgraphy , XVAL , YVAL , 0 , 0)
        END IF
        '.visible=0
        '.visible=1
        'with graph
        '.firstbufcntreset
        .savebuffertmp
        .paintchart
        'end with
    END WITH

END SUB

SUB DetPos2
    DIM XVAL AS INTEGER , YVAL AS INTEGER
    'GetCursorPos(NPOS)
    'XVAL=NPOS.xpos
    'YVAL=NPOS.ypos
    'xval=xval-frmmain.left-canvas.left-4-mouseexcentricityx
    'yval=yval-frmmain.top-canvas.top-43-mouseexcentricityy
    'XVAL = mousemovesepindix
    'YVAL = mousemovesepindiy
    xval=screen.mousex-mousediffsepindix    
    yval=screen.mousey-mousediffsepindiy

    WITH canvas

        IF trendlinebtn.Flat = 1 THEN
            .drawp(0 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF fibofanbtn.Flat = 1 THEN
            .drawp(1 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF fiboretbtn.Flat = 1 THEN
            .drawp(2 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF parabtn.Flat = 1 AND sepindiclick = 1 THEN
            .drawp(0 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF parabtn.Flat = 1 AND sepindiclick = 2 THEN
            .drawp(3 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , secondclicksepindix , secondclicksepindiy)
        END IF
        IF pitchforkbtn.Flat = 1 AND sepindiclick = 1 THEN
            .drawp(0 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF pitchforkbtn.Flat = 1 AND sepindiclick = 2 THEN
            .drawp(17 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , secondclicksepindix , secondclicksepindiy)
        END IF
        IF orcyclesbtn.Flat = 1 AND sepindiclick = 1 THEN
            .drawp(0 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF orcyclesbtn.Flat = 1 AND sepindiclick = 2 THEN
            .drawp(18 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , secondclicksepindix , secondclicksepindiy)
        END IF
        IF hlinebtn.Flat = 1 THEN
            .drawp(4 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF vlinebtn.Flat = 1 THEN
            .drawp(5 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF sqrbtn.Flat = 1 THEN
            .drawp(6 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF tribtn.Flat = 1 THEN
            .drawp(7 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF circlebtn.Flat = 1 THEN
            .drawp(8 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF crossbtn.Flat = 1 THEN
            .drawp(9 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF invcirclebtn.Flat = 1 THEN
            .drawp(10 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF textbtn.Flat = 1 THEN
            canvas.BMP.TextOut(firstclicksepindix , firstclicksepindiy , drawtxt , textcolor , &hffffff)
            sepindiclick = 0
            sepindiclicktimer.Enabled = 0
        END IF
        IF aimingbtn.Flat = 1 THEN
            .drawp(11 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF handdbtn.Flat = 1 THEN
            .drawp(12 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF sinbtn.Flat = 1 THEN
            .drawp(13 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF logbtn.Flat = 1 THEN
            .drawp(14 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF expbtn.Flat = 1 THEN
            .drawp(15 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        IF ellipsebtn.Flat = 1 THEN
            .drawp(16 , firstclicksepindix , firstclicksepindiy , XVAL , YVAL , 0 , 0)
        END IF
        
        '.visible=0
        '.visible=1
        .savebuffertmp
        .paint
    END WITH

END SUB

'Pixel by pixel credit scroller for Rapid-Q by William Yu


SUB resize
    aboutcanvas.Height = aboutform.ClientHeight
    aboutcanvas.Width = aboutform.ClientWidth
END SUB

DIM yposabout AS INTEGER
SUB paintabout(Sender AS QCANVAS)   
    DIM abmargin AS INTEGER
    abmargin = 3
    yposabout = 0
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "QChartist is a free charting software written in Basic and C++ language" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Contact email: julien.moog@laposte.net" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Website: http://www.qchartist.net" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Copyright 2010-2015 Julien Moog - All rights reserved" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Special thanks to:" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "William Yu for his RAPID-Q compiler and all its extends" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "John Kelly for his RapidQ2.inc and Windows.inc and rapidq.chm" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Inprise Corporation for the Borland C++ Compiler 5.5" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Jacques Phillipe for his excellent RapidQ Pre Compiler and rapidq.chm" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Paul Ludgate for his revised version of the RapidQ Compiler" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Michael J. Zito for his great QChart object" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Pasquale Battistelli for his Api Date and QCalendar" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Bruno Schäfer for his rq-math.inc" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Stanescu Serban for his QInputBox and rapidq.chm" , purple , 0)    
    yposabout = yposabout + 30  
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Jens Altmann for his File Editor" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Andrew Shelkovenko for rapidq.chm" , purple , 0)    
    yposabout = yposabout + 30 
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "D. Glodt for the rapidq.chm" , purple , 0)    
    yposabout = yposabout + 30 
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "MetaQuotes Software Corp. for the accelerator indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "MetaQuotes Software Corp. for the ATR indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "MetaQuotes Software Corp. for the Bollinger Bands indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Shinigami for his ADR lines indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Luis Guilherme Damiani for the ATR Channels indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "David W. Thomas for the BB - HL indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Forex-TSD.com and IgorAD for the CandleAverage indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "NG3110 and Linuxser for the Center of Gravity indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "MetaQuotes Software Corp. and Nikolay Kositsin for the Envelope indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "MetaQuotes Software Corp. for the Force Index indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "MetaQuotes Software Corp. for the MFI indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "MetaQuotes Software Corp. for the RSI indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "njel for the smaFibo indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "TrendLaboratory Ltd. and igorad for the StepRSI indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Mark W. Helweg, David C. Stendahl and smallcaps90 for the" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "valuechart indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "S.B.T. for the Volatility Pivot indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "MetaQuotes Software Corp. for the Zigzag indicator" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Myles Wilson Walker for his article on W.D. Gann methods" , purple , 0)    
    yposabout = yposabout + 30  
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "for using the planet longitudes" , purple , 0)    
    yposabout = yposabout + 30   
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Mladen for his dynamic balance point indicator" , purple , 0)    
    yposabout = yposabout + 30 
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Brijon, NorthPro, Pipo, Walter, Charvo, Pacific_trip, Habeeb," , purple , 0)    
    yposabout = yposabout + 30 
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Skyline & Hornet for the WaterLevel indicator" , purple , 0)    
    yposabout = yposabout + 30 
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Earik Beann for the declination system" , purple , 0)    
    yposabout = yposabout + 30 
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Scribd's team for the pdf documentations" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Traders world magazine for their articles" , purple , 0)    
    yposabout = yposabout + 30 
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "Yuriy Tokman for the spectrometer indicator" , purple , 0)    
    yposabout = yposabout + 30 
    aboutcanvas.TextOut(abmargin , abouty - yposabout , "And many thanks to all thoses who helped me to build this project" , purple , 0)    
    yposabout = yposabout + 30
    aboutcanvas.Top = abouty / yposabout + 165
    DIM Istars AS INTEGER
    FOR Istars = 1 TO MaxStars
        IF NOT (_
            (Starsx(Istars) >= planetredbg.Left AND Starsx(Istars) <= planetredbg.Left + planetredbg.Width AND _
            Starsy(Istars) >= planetredbg.Top - 135 - abouty / 4 AND Starsy(Istars) <= planetredbg.Top - 135 - abouty / 4 + planetredbg.Height) _
            OR (Starsx(Istars) >= planetgreenbg.Left AND Starsx(Istars) <= planetgreenbg.Left + planetgreenbg.Width AND _
            Starsy(Istars) >= planetgreenbg.Top - 135 - abouty / 4 AND Starsy(Istars) <= planetgreenbg.Top - 135 - abouty / 4 + planetgreenbg.Height) _
            OR (Starsx(Istars) >= planetwhitebg.Left AND Starsx(Istars) <= planetwhitebg.Left + planetwhitebg.Width AND _
            Starsy(Istars) >= planetwhitebg.Top - 135 - abouty / 4 AND Starsy(Istars) <= planetwhitebg.Top - 135 - abouty / 4 + planetwhitebg.Height) _
            ) THEN
            aboutcanvas.Pset(Starsx(Istars) , Starsy(Istars) , white)
            aboutcanvas.Pset(Starsx(Istars) + 1 , Starsy(Istars) , white)
            aboutcanvas.Pset(Starsx(Istars) + 1 , Starsy(Istars) + 1 , white)
            aboutcanvas.Pset(Starsx(Istars) , Starsy(Istars) + 1 , white)
            aboutcanvas.Pset(Starsx(Istars) - 1 , Starsy(Istars) + 1 , white)
            aboutcanvas.Pset(Starsx(Istars) - 1 , Starsy(Istars) , white)
            aboutcanvas.Pset(Starsx(Istars) - 1 , Starsy(Istars) - 1 , white)
            aboutcanvas.Pset(Starsx(Istars) , Starsy(Istars) - 1 , white)
            aboutcanvas.Pset(Starsx(Istars) + 1 , Starsy(Istars) - 1 , white)
        END IF

        'aboutcanvas.fillrect(planetredbg.left,planetredbg.top-135-abouty/4,planetredbg.left+5,planetredbg.top-135+5+-abouty/4,lightblue)

    NEXT Istars


END SUB


SUB moveplanetred
    planetredbg.Top = planetredbg.Top + planetredbgspeed
    IF planetredbg.Top >= aboutform.Height THEN
        planetredbg.Top = - planetredbg.Height - RND(50)
        planetredbg.Left = RND(aboutform.Width + planetredbg.Width) - planetredbg.Width
        planetredbgspeed = RND(5) + 1
    END IF
END SUB

SUB moveplanetgreen
    planetgreenbg.Top = planetgreenbg.Top + planetgreenbgspeed
    IF planetgreenbg.Top >= aboutform.Height THEN
        planetgreenbg.Top = - planetgreenbg.Height - RND(50)
        planetgreenbg.Left = RND(aboutform.Width + planetgreenbg.Width) - planetgreenbg.Width
        planetgreenbgspeed = RND(5) + 1
    END IF
END SUB

SUB moveplanetwhite
    planetwhitebg.Top = planetwhitebg.Top + planetwhitebgspeed
    IF planetwhitebg.Top >= aboutform.Height THEN
        planetwhitebg.Top = - planetwhitebg.Height - RND(50)
        planetwhitebg.Left = RND(aboutform.Width + planetwhitebg.Width) - planetwhitebg.Width
        planetwhitebgspeed = RND(5) + 1
    END IF
END SUB


SUB timerover
    'aboutTimer.Interval = 35  'Can't go any lower!
    abouty = abouty + 1  'Pixel by pixel!
    'if abouty>aboutcanvas.height then
    IF abouty > yposabout+100 THEN
        abouty = - 20
        DIM Istars AS INTEGER
        FOR Istars = 1 TO MaxStars
            Starsy(Istars) = Starsy(Istars) + 50
        NEXT Istars
    END IF
    paintabout(aboutcanvas)
END SUB

SUB closeaboutform
    aboutTimer.Enabled = 0
    'aboutform.modalresult=1
    'aboutform.visible=0
    PLAYWAV "" , SND_ASYNC OR SND_LOOP
    planettimerred.Enabled = 0
    planettimergreen.Enabled = 0
    planettimerwhite.Enabled = 0
END SUB

SUB abfrmclose
    aboutTimer.Enabled = 0
    PLAYWAV "" , SND_ASYNC OR SND_LOOP
    planettimerred.Enabled = 0
    planettimergreen.Enabled = 0
    planettimerwhite.Enabled = 0
END SUB

SUB about()
    
    if usespeech.checked=0 then
    aboutTimer.Interval = 35
    else
    aboutTimer.Interval = 125
    end if
    
    InitStars

    abouty = - 20
    aboutform.Visible = 1
    aboutTimer.Enabled = 1
    planettimerred.Enabled = 1
    planettimergreen.Enabled = 1
    planettimerwhite.Enabled = 1
    if usespeech.checked=0 then PLAYWAV homepath + "\wav\Melody.wav" , SND_ASYNC OR SND_LOOP
    say "QChartist is a free charting software written in Basic and C++ language"+" . "+_
    "Contact email: julien.moog@laposte.net"+" . "+_
    "Website: http://www.qchartist.net"+" . "+_
    "Copyright 2010-2015 Julien Moog - All rights reserved"+" . "+_
    "Special thanks to:"+" . "+_
    "William Yu for his RAPID-Q compiler and all its extends"+" . "+_
    "John Kelly for his RapidQ2.inc and Windows.inc and rapidq.chm"+" . "+_
    "Inprise Corporation for the Borland C++ Compiler 5.5"+" . "+_
    "Jacques Phillipe for his excellent RapidQ Pre Compiler and rapidq.chm"+" . "+_
    "Paul Ludgate for his revised version of the RapidQ Compiler"+" . "+_
    "Michael J. Zito for his great QChart object"+" . "+_
    "Pasquale Battistelli for his Api Date and QCalendar"+" . "+_
    "Bruno Schäfer for his rq-math.inc"+" . "+_
    "Stanescu Serban for his QInputBox and rapidq.chm"+" . "+_
    "Jens Altmann for his File Editor"+" . "+_
    "Andrew Shelkovenko for rapidq.chm"+" . "+_
    "D. Glodt for the rapidq.chm"+" . "+_
    "MetaQuotes Software Corp. for the accelerator indicator"+" . "+_
    "MetaQuotes Software Corp. for the ATR indicator"+" . "+_
    "MetaQuotes Software Corp. for the Bollinger Bands indicator"+" . "+_
    "Shinigami for his ADR lines indicator"+" . "+_
    "Luis Guilherme Damiani for the ATR Channels indicator"+" . "+_
    "David W. Thomas for the BB - HL indicator"+" . "+_
    "Forex-TSD.com and IgorAD for the CandleAverage indicator"+" . "+_
    "NG3110 and Linuxser for the Center of Gravity indicator"+" . "+_
    "MetaQuotes Software Corp. and Nikolay Kositsin for the Envelope indicator"+" . "+_
    "MetaQuotes Software Corp. for the Force Index indicator"+" . "+_
    "MetaQuotes Software Corp. for the MFI indicator"+" . "+_
    "MetaQuotes Software Corp. for the RSI indicator"+" . "+_
    "njel for the smaFibo indicator"+" . "+_
    "TrendLaboratory Ltd. and igorad for the StepRSI indicator"+" . "+_
    "Mark W. Helweg, David C. Stendahl and smallcaps90 for the valuechart indicator"+" . "+_
    "S.B.T. for the Volatility Pivot indicator"+" . "+_
    "MetaQuotes Software Corp. for the Zigzag indicator"+" . "+_
    "Myles Wilson Walker for his article on W.D. Gann methods for using the planet longitudes"+" . "+_
    "Mladen for his dynamic balance point indicator"+" . "+_
    "Brijon, NorthPro, Pipo, Walter, Charvo, Pacific_trip, Habeeb, Skyline & Hornet for the WaterLevel indicator"+" . "+_
    "Earik Beann for the declination system"+" . "+_
    "Scribd's team for the pdf documentations"+" . "+_
    "Traders world magazine for their articles"+" . "+_
    "Yuriy Tokman for the spectrometer indicator"+" . "+_
    "And many thanks to all thoses who helped me to build this project"+" . "
END SUB


SUB quit()
    frmMain.close
END SUB

SUB savebmp
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    Graph.SaveChart("")
END SUB

SUB printchart
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    Graph.printchart(Printer.PrinterIndex , 1 , 40 , 1 , FALSE)
END SUB

SUB frmmainonmw(frmmainr AS INTEGER , frmmainx AS LONG , frmmainy AS LONG , frmmains AS INTEGER)
    IF openedfilesnb < 1 THEN
        EXIT SUB
    END IF
    IF frmmainr = 1 THEN
        Scrollchart.Position = Scrollchart.Position + 15
    END IF
    IF frmmainr = - 1 THEN
        Scrollchart.Position = Scrollchart.Position - 15
    END IF
    chartstart = Scrollchart.Position - numbars
    IF scrollchartpositionwait = 1 THEN
        IF scrollmodebtn.Flat = 0 THEN
            scrollmodebtn.Flat = 1
            scrollmodebtn.Color = &H88cc88
            scrollmode = 1
            Scrollchart.Enabled = 1
        END IF
        btnOnClick(drwBox)
    END IF

END SUB

SUB showtoolsclick
    toolsPanel.dock(1)
END SUB

SUB showtoolbarclick
    ToolbarBox.dock(1)
END SUB

SUB resizesplitmd
    resizesplittimer.Enabled = 1
END SUB

SUB resizesplithmd
    resizesplithtimer.Enabled = 1
END SUB

SUB resizesplitmu
    resizesplittimer.Enabled = 0
    sepindiheight = STR$(sepindiheight + canvas.Top - YVALs)
    showcanvasclick
END SUB

SUB resizesplithmu
    resizesplithtimer.Enabled = 0
    leftwidth = XVALs - 15
    'print str$(leftwidth)
    'showcanvasclick
    setup()
END SUB

SUB resizesplitcurpos

    GetCursorPos(NPOS)

    YVALs = NPOS.ypos
    'yvals=yvals-frmmain.top-graph.top-43-mouseexcentricityy
    YVALs = YVALs - frmMain.Top - 43 - mouseexcentricityy

    split.Top = YVALs

END SUB

SUB resizesplithcurpos

    GetCursorPos(NPOS)

    XVALs = NPOS.xpos
    'Xvals=Xval-frmmain.top-graph.top-43-mouseexcentricityy
    'xval=xval-frmmain.left-graph.left-4-mouseexcentricityx
    XVALs = XVALs - frmMain.Left - 4 - mouseexcentricityx

    splith.Left = XVALs
    'print str$(xvals)
END SUB

SUB writetolog(lastlogline AS STRING)
    DIM fileqtp AS QFILESTREAM
    IF FILEEXISTS(homepath + "\QChartist.log") = FALSE THEN
        fileqtp.open(homepath + "\QChartist.log" , fmCreate)
        fileqtp.close
    END IF
    fileqtp.open(homepath + "\QChartist.log" , 2)
    fileqtp.Position = fileqtp.Size
    fileqtp.WriteLine(lastlogline)
    fileqtp.close
END SUB

SUB writealive
    DIM fileqtp AS QFILESTREAM
    'if FileExists(homepath+"\alive.log") = FALSE THEN
    'fileqtp.open(homepath+"\alive.log",fmCreate)
    'fileqtp.close
    'end if
    fileqtp.open(homepath + "\alive.log" , fmCreate)
    'fileqtp.position=fileqtp.size
    fileqtp.WriteLine(STR$(timeGetTime))
    fileqtp.close

END SUB

SUB axistypecombosub
    axistypecomboitemindex = axistypecombo.ItemIndex
    justrefreshchart
    say "Axis type changed to: "+axistypecombo.Item(axistypecombo.ItemIndex)
END SUB

SUB xscaletrackbarsub
    'xscaletrackbarposition=exp(xscaletrackbar.position/50)-1
    'justrefreshchart
END SUB

SUB followmodeactivate
    IF followmodetimer.Enabled = 0 THEN
        followmodetimer.Enabled = 1
        EXIT SUB
    END IF
    IF followmodetimer.Enabled = 1 THEN
        followmodetimer.Enabled = 0
        EXIT SUB
    END IF
END SUB

DIM followmodepath AS STRING
followmodepath = importedfile(displayedfile)

SUB followmode

    tfmult.Text = "1"
    importfileauto(followmodepath)
    reimportfile()

    DIM getline$ AS STRING

    IF FILEEXISTS(homepath + "\reversetmp.log") = FALSE THEN

        PRINT " file not found "
        EXIT SUB
    END IF

    DIM file AS QFILESTREAM
    file.open(homepath + "\reversetmp.log" , 0)

    DEFINT j = 0
    DIM revdate AS STRING
    DIM revtime AS STRING


    DO

        j ++

        getline$ = file.ReadLine

        IF INSTR(getline$ , "Reverse") > 0 THEN
            revdate = MID$(MID$(getline$ , INSTR(getline$ , "From Date: ")) , 12 , INSTR(MID$(getline$ , INSTR(getline$ , "From Date: ") + 11) , " ") - 1)
            revtime = MID$(MID$(getline$ , INSTR(getline$ , "From Date: ") + 11) , INSTR(MID$(getline$ , INSTR(getline$ , "From Date: ") + 11) , " ") + 1 , 5)
            findbarfromfile(revdate , revtime)
            reversetillendnorefresh
        END IF

    LOOP UNTIL file.eof
    file.close

    'file.open(homepath+"\reversetmp.log", 0)
    'dim revtfmu as string
    'revtfmu=""
    'do
    '
    ''j++
    '
    'getline$=file.readline
    '
    'if instr(getline$,"changed")>0 then
    'if revtfmu="" then
    'revtfmu=mid$(getline$,instr(getline$,"to")+3,3)
    'end if
    'end if
    '
    'loop until file.eof
    'file.close

    refreshgrids

    'tfmult.text=revtfmu
    'tfmultok_click

    EXIT SUB  'not fully functional yet

    SLEEP 5

    '-================================== Export algo ==========================================-
    DIM csvFile AS QFILESTREAM
    csvFile.open(homepath + "\reversetmp.csv" , 65535) '65535 = fmCreate
    DIM csvi AS INTEGER
    DIM datecsv AS STRING
    DIM timecsv AS STRING
    DIM opencsv AS STRING
    DIM highcsv AS STRING
    DIM lowcsv AS STRING
    DIM closecsv AS STRING
    DIM volumecsv AS STRING
    'dim inputcsvbars as qinputbox
    'dim csvbars as string
    'csvbars=inputcsvbars.input("How many bars to export?")
    SELECT CASE axistypecomboitemindex
        CASE 0 :
            FOR csvi = 1 TO chartbars(displayedfile) 'val(csvbars)
                datecsv = Grid.Cell(rowgridoffset + 1 , csvi)
                timecsv = Grid.Cell(rowgridoffset + 2 , csvi)
                opencsv = Grid.Cell(rowgridoffset + 3 , csvi)
                highcsv = Grid.Cell(rowgridoffset + 4 , csvi)
                lowcsv = Grid.Cell(rowgridoffset + 5 , csvi)
                closecsv = Grid.Cell(rowgridoffset + 6 , csvi)
                volumecsv = Grid.Cell(rowgridoffset + 7 , csvi)
                csvFile.WriteLine(datecsv + "," + timecsv + "," + opencsv + "," + highcsv + "," + lowcsv + "," + closecsv + "," + volumecsv)
            NEXT csvi
        CASE 1 :
            FOR csvi = 1 TO chartbars(displayedfile) 'val(csvbars)
                datecsv = Grid.Cell(rowgridoffset + 1 , csvi)
                timecsv = Grid.Cell(rowgridoffset + 2 , csvi)
                opencsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 3 , csvi))) , ffGeneral , 4 , 4)
                highcsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 4 , csvi))) , ffGeneral , 4 , 4)
                lowcsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 5 , csvi))) , ffGeneral , 4 , 4)
                closecsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 6 , csvi))) , ffGeneral , 4 , 4)
                volumecsv = ROUND(log10(VAL(Grid.Cell(rowgridoffset + 7 , csvi))))
                csvFile.WriteLine(datecsv + "," + timecsv + "," + opencsv + "," + highcsv + "," + lowcsv + "," + closecsv + "," + volumecsv)
            NEXT csvi
    END SELECT
    csvFile.close

    '-===================================== End of export algo ================================

END SUB

SUB autoreverse

    signaltrigger = 0

    'if indicatorslistsel.Item(indicatorslist.itemindex)="" then
    'btnaddindi_click()
    'exit sub
    'end if
    'barsdisplayed.Text=200
    'justrefreshchart

    WHILE signaltrigger = 0

        IF ini.exist THEN
            ini.Section = "Settings"
            IF VAL(ini.get("automation" , "")) = 0 THEN
                signaltrigger = 1
                EXIT SUB
            END IF
        END IF

        writealive

        DIM i AS INTEGER
        FOR i = 0 TO indicatorslist.ItemCount - 1
            indicatorslist.ItemIndex = i
            btndelindi_click()
        NEXT i
        useindischeckbox.Checked = 0

        tfmult.Text = STR$(1)

        'sleep 2
        'print csvlist.directory+"\"+csvlist.item(rnd(csvlist.itemcount))


        DIM rndcsvlistitem AS INTEGER
        DIM checkfilesize AS QFILESTREAM
        DIM csvlistsize AS INTEGER
        csvlistsize = 0
        DIM dfhvalue AS STRING
        DIM dfhfile AS QFILESTREAM
        DIM dfhlogfile AS STRING
        DIM dfhup AS STRING , dfhdn AS STRING , dfhpc AS STRING
        DIM rangeupdn AS DOUBLE , rangepcdn AS DOUBLE , gaugedfh AS DOUBLE

        WHILE csvlistsize < 102400
            rndcsvlistitem = RND(csvList.ItemCount)
            checkfilesize.open(DirList.Directory + "\" + csvList.Item(rndcsvlistitem) , fmOpenRead)
            csvlistsize = checkfilesize.Size
            checkfilesize.close

            dfhlogfile = MID$(csvList.Item(rndcsvlistitem) , 0 , INSTR(0 , csvList.Item(rndcsvlistitem) , ".") - 1) + ".log"
            dfhfile.open(DirList.Directory + "\" + dfhlogfile , fmOpenRead)
            dfhvalue = dfhfile.ReadLine() 'Read an entire line
            dfhfile.close

            dfhup = MID$(dfhvalue , 0 , INSTR(0 , dfhvalue , ",") - 1)
            dfhdn = MID$(dfhvalue , LEN(dfhup) + 2 , INSTR(0 , dfhvalue , ",") - 1)
            dfhpc = MID$(dfhvalue , LEN(dfhup) + 1 + LEN(dfhdn) + 2 , LEN(dfhvalue))

            rangeupdn = VAL(dfhup) - VAL(dfhdn)
            rangepcdn = VAL(dfhpc) - VAL(dfhdn)
            gaugedfh = rangepcdn / rangeupdn

            IF gaugedfh < 0.8 AND gaugedfh > 0.2 THEN
                csvlistsize = 0
            END IF
            'writealive
        WEND
        writealive
        DIM jjj AS string :
        jjj = csvList.Item(rndcsvlistitem)
        DIM kkk AS INTEGER
        kkk = INSTR(0 , jjj , ".")
        DIM iii AS INTEGER
        DIM lll AS STRING
        FOR iii = kkk - 1 TO 0 STEP - 1
            lll = MID$(jjj , iii , 1)
            IF ASC(lll) < 48 OR ASC(lll) > 57 THEN
                EXIT FOR
            END IF
            'writealive
        NEXT iii
        writealive
        DIM mmm AS STRING
        mmm = MID$(jjj , iii + 1)
        mmm = MID$(mmm , 0 , INSTR(0 , mmm , ".") - 1)

        WHILE VAL(mmm) < 30
            rndcsvlistitem = RND(csvList.ItemCount)
            checkfilesize.open(DirList.Directory + "\" + csvList.Item(rndcsvlistitem) , fmOpenRead)
            csvlistsize = checkfilesize.Size
            checkfilesize.close
            jjj = csvList.Item(rndcsvlistitem)
            kkk = INSTR(0 , jjj , ".")
            FOR iii = kkk - 1 TO 0 STEP - 1
                lll = MID$(jjj , iii , 1)
                IF ASC(lll) < 48 OR ASC(lll) > 57 THEN
                    EXIT FOR
                END IF
                'writealive
            NEXT iii
            mmm = MID$(jjj , iii + 1)
            mmm = MID$(mmm , 0 , INSTR(0 , mmm , ".") - 1)
     'writealive
        WEND
        writealive
        importfileauto(DirList.Directory + "\" + csvList.Item(rndcsvlistitem))
        writealive
        reimportfile()
        writealive
        '''SLEEP(VAL(pausesdurationedit.Text))
        FOR i = 0 TO indicatorslist.ItemCount - 1
            IF INSTR(0 , indicatorslist.Item(i) , "ZigZag cpp") > 0 THEN
                EXIT FOR
            END IF
        NEXT i
        indicatorslist.ItemIndex = i
        btnaddindi_click()
        justrefreshchart
        writealive
        '''SLEEP(VAL(pausesdurationedit.Text))
        DIM lowsarr(0 TO 200) AS DOUBLE
        DIM highsarr(0 TO 200) AS DOUBLE
        DIM zzarr(0 TO 1000) AS DOUBLE
        DIM j AS INTEGER , k AS INTEGER , l AS INTEGER
        j = 0
        k = 0
        l = 0
        dim zzbufferstr as string:zzbufferstr="zigzagbuffer":dim zzistr as string
        FOR i = 0 TO 1000
            'zzarr(i) = zigzagbuffer(i)
            zzistr=str$(i)            
            zzarr(i)=val(varptr$(getbufferdata(varptr(zzbufferstr),varptr(zzistr))))
        NEXT i
        btndelindi_click()
        useindischeckbox.Checked = 0
        reversecount = 0
        FOR i = 0 TO 100
            tmpreverse(i) = ""
        NEXT i
' Sometimes it crashs bellow
        FOR i = numbars - 1 TO 0 STEP - 1
            IF zzarr(i) <> 0 THEN
                IF (RND(2) = 1 OR i <= VAL(barsbefonorndedit.Text)) THEN
                    clickedbarnb = chartbars(displayedfile) - chartstart - i
                    graphbarnboncurstatic = chartstart + clickedbarnb
                    reversetillendnorefresh
                END IF
            END IF
            'writealive
        NEXT i
        writealive
' End of sometimes it crashs 
        'refreshgrids
    refreshgrids2
        DIM fileqtp AS QFILESTREAM
        fileqtp.open(homepath + "\reversetmp.log" , fmCreate)
        'fileqtp.position=fileqtp.size
        FOR i = 0 TO reversecount
            fileqtp.WriteLine(tmpreverse(i))
        NEXT i
        fileqtp.close
        writealive
        '''SLEEP(VAL(pausesdurationedit.Text))

        'exp10sub
        'writealive
        'sleep (val(pausesdurationedit.text))
        'savegridtmp

        DIM rndnbtfmults AS INTEGER
        rndnbtfmults = RND(VAL(nbtfmultsedit.Text))
        tfmult.Text = STR$(rndnbtfmults + 1)
        tfmultok_click
        writealive
        '''SLEEP(VAL(pausesdurationedit.Text))

        FOR i = 0 TO indicatorslist.ItemCount - 1
            IF INSTR(0 , indicatorslist.Item(i) , "Bollinger Bands cpp") > 0 THEN
                EXIT FOR
            END IF
        NEXT i
        indicatorslist.ItemIndex = i
        btnaddindi_click()
        justrefreshchart
        DIM presignal0 AS integer : presignal0 = 0
        writealive
        '''SLEEP(VAL(pausesdurationedit.Text))
        defstr zerostr="0"
        defstr bdslowerbufferstr="bandslowerbuffer"
        defstr bdsupperbufferstr="bandsupperbuffer"
        IF (high(0) >= (val(varptr$(getbufferdata(varptr(bdslowerbufferstr),varptr(zerostr)))) + 0.75 * (val(varptr$(getbufferdata(varptr(bdsupperbufferstr),varptr(zerostr)))) - val(varptr$(getbufferdata(varptr(bdslowerbufferstr),varptr(zerostr))))))) THEN
            'writealivetimer.enabled=1
            'signalsnd
            'ini.Section="Settings"
            'ini.write("automation","0")
            'signaltrigger=1
            presignal0 = 1
            upordown = 1
            IF FRAC(reversecount / 2) <> 0 THEN
                upordown = 0
            END IF
        END IF
        IF (low(0) <= (val(varptr$(getbufferdata(varptr(bdslowerbufferstr),varptr(zerostr)))) + 0.25 * (val(varptr$(getbufferdata(varptr(bdsupperbufferstr),varptr(zerostr)))) - val(varptr$(getbufferdata(varptr(bdslowerbufferstr),varptr(zerostr))))))) THEN
            'writealivetimer.enabled=1
            'signalsnd
            'ini.Section="Settings"
            'ini.write("automation","0")
            'signaltrigger=1
            presignal0 = 1
            upordown = 0
            IF FRAC(reversecount / 2) <> 0 THEN
                upordown = 1
            END IF
        END IF
        
        FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "Bollinger Bands cpp") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()

        IF (((gaugedfh >= 0.8 AND upordown = 1) OR (gaugedfh <= 0.2 AND upordown = 0)) AND (presignal0 = 1)) THEN

            tfmult.Text = STR$(1)
            tfmultok_click
            writealive
            '''SLEEP(VAL(pausesdurationedit.Text))

            exp10sub
            writealive
            '''SLEEP(VAL(pausesdurationedit.Text))
            savegridtmp
            cpptmpfuncreturn=varptr$(savegridtmpcpp())

            tfmult.Text = STR$(rndnbtfmults + 1)
            tfmultok_click
            writealive
            '''SLEEP(VAL(pausesdurationedit.Text))
            
' -------------------------- Timeframes attribution -------------------------------------            
            
            useindi.Checked = 0

DIM jjj2 AS string :
    jjj2 = importedfile(displayedfile)
    DIM kkk2 AS INTEGER
    kkk2 = INSTR(0 , jjj2 , ".")
    DIM iii2 AS INTEGER
    DIM lll2 AS STRING
    FOR iii2 = kkk2 - 1 TO 0 STEP - 1
        lll2 = MID$(jjj2 , iii2 , 1)
        IF ASC(lll2) < 48 OR ASC(lll2) > 57 THEN
            EXIT FOR
        END IF
    NEXT iii2
    DIM mmm2 AS STRING
    mmm2 = MID$(jjj2 , iii2 + 1)
    mmm2 = MID$(mmm2 , 0 , INSTR(0 , mmm2 , ".") - 1)

SELECT CASE VAL(mmm2)

        CASE 30 :        
        attribtfcombo.itemindex=3
        attribtfeditItemChanged
        writealive
        barsdisplayed.Text = "7"
            dispbarsok_click
            tfmult.Text = "48"
            tfmultok_click
            attribtfcombo.itemindex=6
        attribtfeditItemChanged
        writealive
            tfmult.Text = "336"
            tfmultok_click
            attribtfcombo.itemindex=7
        attribtfeditItemChanged
        writealive

        CASE 60 :
        attribtfcombo.itemindex=4
        attribtfeditItemChanged
        writealive
        barsdisplayed.Text = "7"
            dispbarsok_click
            tfmult.Text = "24"
            tfmultok_click
            attribtfcombo.itemindex=6
        attribtfeditItemChanged
        writealive
            tfmult.Text = "168"
            tfmultok_click
            attribtfcombo.itemindex=7
        attribtfeditItemChanged
        writealive

    END SELECT

tfmult.Text = STR$(rndnbtfmults + 1)
tfmultok_click                
barsdisplayed.Text = "300"  
useindi.Checked = 1  
dispbarsok_click
            writealive                
' --------------------------------------------------------------------------------    

            waterlevelcppcurtfedit.text=mmm2
            FOR i = 0 TO indicatorslist.ItemCount - 1
                IF INSTR(0 , indicatorslist.Item(i) , "WaterLevel cpp") > 0 THEN
                    EXIT FOR
                END IF
            NEXT i
            indicatorslist.ItemIndex = i
            btnaddindi_click()                   
            
            justrefreshchart
            writealive
            
            DIM presignal AS integer : presignal = 0
            DIM presignal2 AS integer : presignal2 = 0
            DIM presignal3 AS integer : presignal3 = 0
            DIM presignal4 AS integer : presignal4 = 0
            DIM presignal5 AS integer : presignal5 = 0
            DIM presignal6 AS integer : presignal6 = 0
            DIM presignal7 AS integer : presignal7 = 0

            defstr sellpricebufferstr="SellPrice"
            defstr buypricebufferstr="BuyPrice"
            
            IF ( high(0) >= (val(varptr$(getbufferdata(varptr(buypricebufferstr),varptr(zerostr))))+0.9*(val(varptr$(getbufferdata(varptr(sellpricebufferstr),varptr(zerostr))))-val(varptr$(getbufferdata(varptr(buypricebufferstr),varptr(zerostr)))))) ) THEN
            presignal = 1
            end if
            
            IF ( low(0) <= (val(varptr$(getbufferdata(varptr(buypricebufferstr),varptr(zerostr))))+0.1*(val(varptr$(getbufferdata(varptr(sellpricebufferstr),varptr(zerostr))))-val(varptr$(getbufferdata(varptr(buypricebufferstr),varptr(zerostr)))))) ) THEN
            presignal = 1
            end if
            
            FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "WaterLevel cpp") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()
            
            IF presignal = 1 THEN
                                    
            FOR i = 0 TO indicatorslist.ItemCount - 1
                IF INSTR(0 , indicatorslist.Item(i) , "ADR112 cpp") > 0 THEN
                    EXIT FOR
                END IF
            NEXT i
            indicatorslist.ItemIndex = i
            btnaddindi_click()
            ADR112cpptfbasecombo.itemindex=0 ' Timeframe basement: Daily
            justrefreshchart
            writealive
            
            defstr ADR112cppbuffer2str="ADR112cppbuffer2"
            defstr ADR112cppbuffer4str="ADR112cppbuffer4"
            
            IF ( high(0) >= val(varptr$(getbufferdata(varptr(ADR112cppbuffer2str),varptr(zerostr)))) ) then
            presignal2=1
            end if
            
            IF ( low(0) <= val(varptr$(getbufferdata(varptr(ADR112cppbuffer4str),varptr(zerostr)))) ) then
            presignal2=1
            end if
            
            FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "ADR112 cpp") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()
            
            END IF
            
            IF presignal2 = 1 THEN
                                    
            FOR i = 0 TO indicatorslist.ItemCount - 1
                IF INSTR(0 , indicatorslist.Item(i) , "ADR112 cpp") > 0 THEN
                    EXIT FOR
                END IF
            NEXT i
            indicatorslist.ItemIndex = i
            btnaddindi_click()
            ADR112cpptfbasecombo.itemindex=1 ' Timeframe basement: Weekly
            justrefreshchart
            writealive
            
            'defstr ADR112cppbuffer2str="ADR112cppbuffer2"
            'defstr ADR112cppbuffer4str="ADR112cppbuffer4"
            
            IF ( high(0) >= val(varptr$(getbufferdata(varptr(ADR112cppbuffer2str),varptr(zerostr)))) ) then
            presignal3=1
            end if
            
            IF ( low(0) <= val(varptr$(getbufferdata(varptr(ADR112cppbuffer4str),varptr(zerostr)))) ) then
            presignal3=1
            end if
            
            FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "ADR112 cpp") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()
            
            END IF
            
            IF presignal3 = 1 THEN

            FOR i = 0 TO indicatorslist.ItemCount - 1
                IF INSTR(0 , indicatorslist.Item(i) , "Center Of Gravity cpp") > 0 THEN
                    EXIT FOR
                END IF
            NEXT i
            indicatorslist.ItemIndex = i
            btnaddindi_click()
            FOR i = 0 TO indicatorslist.ItemCount - 1
                IF INSTR(0 , indicatorslist.Item(i) , "BB - HL cpp") > 0 THEN
                    EXIT FOR
                END IF
            NEXT i
            indicatorslist.ItemIndex = i
            btnaddindi_click()
            FOR i = 0 TO indicatorslist.ItemCount - 1
                IF INSTR(0 , indicatorslist.Item(i) , "COG of RSTL") > 0 THEN
                    EXIT FOR
                END IF
            NEXT i
            indicatorslist.ItemIndex = i
            btnaddindi_click()
            FOR i = 0 TO indicatorslist.ItemCount - 1
                IF INSTR(0 , indicatorslist.Item(i) , "Levels") > 0 THEN
                    EXIT FOR
                END IF
            NEXT i
            indicatorslist.ItemIndex = i
            btnaddindi_click()
            FOR i = 0 TO indicatorslist.ItemCount - 1
                IF INSTR(0 , indicatorslist.Item(i) , "bowels") > 0 THEN
                    EXIT FOR
                END IF
            NEXT i
            indicatorslist.ItemIndex = i
            btnaddindi_click()
            bbhlperiodedit.Text = bolliperedit.Text
            bbhlcppperiodedit.Text = bolliperedit.Text

            justrefreshchart
            writealive
            '''SLEEP(VAL(pausesdurationedit.Text))

            'DIM presignal AS integer : presignal = 0
            'DIM presignal2 AS integer : presignal2 = 0

            defstr sqlbufferstr="sql"
            defstr sqhbufferstr="sqh"
            defstr lowerbandbufferstr="lowerbandbuffer"
            defstr upperbandbufferstr="upperbandbuffer"
            defstr sql2bufferstr="sql2"
            defstr sqh2bufferstr="sqh2"
            defstr fx2bufferstr="fx2"
            defstr sopr1bufferstr="sopr1"
            defstr pod1bufferstr="pod1"
            defstr s3bufferstr="s3"
            defstr r3bufferstr="r3"
            IF (high(0) >= val(varptr$(getbufferdata(varptr(r3bufferstr),varptr(zerostr)))) AND high(0) >= val(varptr$(getbufferdata(varptr(sopr1bufferstr),varptr(zerostr)))) AND high(0) >= (val(varptr$(getbufferdata(varptr(fx2bufferstr),varptr(zerostr)))) + 0.9 * (val(varptr$(getbufferdata(varptr(sqh2bufferstr),varptr(zerostr)))) - val(varptr$(getbufferdata(varptr(fx2bufferstr),varptr(zerostr)))))) AND high(0) >= (val(varptr$(getbufferdata(varptr(sqlbufferstr),varptr(zerostr)))) + 0.75 * (val(varptr$(getbufferdata(varptr(sqhbufferstr),varptr(zerostr)))) - val(varptr$(getbufferdata(varptr(sqlbufferstr),varptr(zerostr)))))) AND high(0) >= (val(varptr$(getbufferdata(varptr(lowerbandbufferstr),varptr(zerostr)))) + 0.8 * (val(varptr$(getbufferdata(varptr(upperbandbufferstr),varptr(zerostr)))) - val(varptr$(getbufferdata(varptr(lowerbandbufferstr),varptr(zerostr))))))) THEN
                'writealivetimer.enabled=1
                'signalsnd
                'ini.Section="Settings"
                'ini.write("automation","0")
                'signaltrigger=1
                presignal4 = 1
                'upordown=1
                'IF FRAC( reversecount / 2 ) <> 0 THEN
                'upordown=0
                'end if
            END IF
            IF (low(0) <= val(varptr$(getbufferdata(varptr(s3bufferstr),varptr(zerostr)))) AND low(0) <= val(varptr$(getbufferdata(varptr(pod1bufferstr),varptr(zerostr)))) AND low(0) <= (val(varptr$(getbufferdata(varptr(sql2bufferstr),varptr(zerostr)))) + 0.1 * (val(varptr$(getbufferdata(varptr(fx2bufferstr),varptr(zerostr)))) - val(varptr$(getbufferdata(varptr(sql2bufferstr),varptr(zerostr)))))) AND low(0) <= (val(varptr$(getbufferdata(varptr(sqlbufferstr),varptr(zerostr)))) + 0.25 * (val(varptr$(getbufferdata(varptr(sqhbufferstr),varptr(zerostr)))) - val(varptr$(getbufferdata(varptr(sqlbufferstr),varptr(zerostr)))))) AND low(0) <= (val(varptr$(getbufferdata(varptr(lowerbandbufferstr),varptr(zerostr)))) + 0.2 * (val(varptr$(getbufferdata(varptr(upperbandbufferstr),varptr(zerostr)))) - val(varptr$(getbufferdata(varptr(lowerbandbufferstr),varptr(zerostr))))))) THEN
                'writealivetimer.enabled=1
                'signalsnd
                'ini.Section="Settings"
                'ini.write("automation","0")
                'signaltrigger=1
                presignal4 = 1
                'upordown=0
                'IF FRAC( reversecount / 2 ) <> 0 THEN
                'upordown=1
                'end if
            END IF
            
            FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "Center Of Gravity cpp") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()
                
            FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "BB - HL cpp") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()   
                
            FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "COG of RSTL") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()
                
            FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "Levels") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()   
                
            FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "bowels") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()          
            
            END IF
            
            IF presignal4 = 1 THEN
                Ehlersfishertransformcurtfedit.text=mmm2
                FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "Ehlers fisher transform") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btnaddindi_click()
                showcanvasclick
                'justrefreshchart
                writealive
                '''SLEEP(VAL(pausesdurationedit.Text))
                
                defstr Ehlersfishertransformbuffer1str="Ehlersfishertransformbuffer1"
                defstr eftbandsmovingbufferstr="eftbandsmovingbuffer"
            IF (val(varptr$(getbufferdata(varptr(Ehlersfishertransformbuffer1str),varptr(zerostr)))) > val(varptr$(getbufferdata(varptr(eftbandsmovingbufferstr),varptr(zerostr)))) ) THEN
                'writealivetimer.enabled=1
                'signalsnd
                'ini.Section="Settings"
                'ini.write("automation","0")
                'signaltrigger=1
                presignal5 = 1
                'upordown=1
                'IF FRAC( reversecount / 2 ) <> 0 THEN
                'upordown=0
                'end if
            END IF               

                FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "Ehlers fisher transform") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()


            END IF
            
            IF presignal5 = 1 THEN
                'Ehlersfishertransformcurtfedit.text=mmm2
                FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "Money Flow Index") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btnaddindi_click()
                showcanvasclick
                'justrefreshchart
                writealive
                '''SLEEP(VAL(pausesdurationedit.Text))
                
                'defstr Ehlersfishertransformbuffer1str="Ehlersfishertransformbuffer1"
                'defstr eftbandsmovingbufferstr="eftbandsmovingbuffer"
            IF (extmfibuffer(0)>=80 ) THEN
                'writealivetimer.enabled=1
                'signalsnd
                'ini.Section="Settings"
                'ini.write("automation","0")
                'signaltrigger=1
                presignal6 = 1
                'upordown=1
                'IF FRAC( reversecount / 2 ) <> 0 THEN
                'upordown=0
                'end if
            END IF               

                FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "Money Flow Index") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()


            END IF
            
            IF presignal6 = 1 THEN
                threeD_Oscilatorcurtfedit.text=mmm2
                FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "threeD Oscilator") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btnaddindi_click()
                showcanvasclick
                'justrefreshchart
                writealive
                '''SLEEP(VAL(pausesdurationedit.Text))
                
                defstr sig1nstr="sig1n"
                defstr sig2nstr="sig2n"
            IF (val(varptr$(getbufferdata(varptr(sig1nstr),varptr(zerostr)))) < val(varptr$(getbufferdata(varptr(sig2nstr),varptr(zerostr)))) ) THEN
                'writealivetimer.enabled=1
                'signalsnd
                'ini.Section="Settings"
                'ini.write("automation","0")
                'signaltrigger=1
                presignal7 = 1
                'upordown=1
                'IF FRAC( reversecount / 2 ) <> 0 THEN
                'upordown=0
                'end if
            END IF               

                FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "threeD Oscilator") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()


            END IF

            IF presignal7 = 1 THEN

                FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "StepRSI") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btnaddindi_click()
                'showcanvasclick
                'justrefreshchart
                writealive
                '''SLEEP(VAL(pausesdurationedit.Text))
                IF ((line1buffer(0) >= 80 AND line2buffer(0) >= 80) OR (line1buffer(0) <= 20 AND line2buffer(0) <= 20)) THEN
                    'writealivetimer.enabled=1
                    IF (VAL(mmm) <> 240 AND VAL(tfmult.Text) <> 6) THEN

                        'if upordown=1 then
                        'signallabel.caption="New sell signal detected!"
                        'end if
                        'if upordown=0 then
                        'signallabel.caption="New buy signal detected!"
                        'end if
                        'signalsnd
                        'mailform.visible=1
                        'if enablemailer.checked=1 then
                        'buttonclick
                        'end if
                        'ini.Section="Settings"
                        'ini.write("automation","0")
                        'signaltrigger=1
                        'presignal2=1

                        DIM getline$ AS STRING
                        getline$ = ""
                        DIM file AS QFILESTREAM
                        file.open(homepath + "\reversetmp.log" , 0)
                        DO
                            getline$ = getline$ + file.ReadLine + CHR$(10)

                        LOOP UNTIL file.eof
                        file.close

                        'Edit3chat.text=replacesubstr$(getline$,chr$(10),"\n")
                        'SendButtonClickchat

                        DIM fileqtp2 AS QFILESTREAM
                        fileqtp2.open(homepath + "\" + STR$(timegettime) + csvList.Item(rndcsvlistitem) + "x" + tfmult.Text + ".log" , 65535)
                        fileqtp2.Position = fileqtp2.Size
                        fileqtp2.WriteLine(getline$)
                        fileqtp2.close

                        Graph.autoSaveChart(homepath + "\" + STR$(timegettime) + csvList.Item(rndcsvlistitem) + "x" + tfmult.Text + ".bmp")

                        tmppath = CurDir$
                        CHDIR initialpath
                        PLAYWAV homepath + "\wav\C-1MAJ.WAV" , SND_ASYNC
                        ini.Section = "Settings"
                        IF VAL(ini.get("mailer" , "")) = 1 THEN                        
                            'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)                            
                            DEFSTR url
                            DEFSTR outFileName
                            url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                            outFileName = "signalmail.txt"
                            defstr tmppath2 = CurDir$
                            CHDIR homepath
                            IF GetFileHTTP(url , outFileName) THEN
                            'SHOWMESSAGE "Download Error : " & url
                            'EXIT SUB
                            ELSE
                            'SHOWMESSAGE "Download Finished & OK : " & URL
                            END IF
                            CHDIR tmppath2                            
                        end if

                        CHDIR tmppath
                        
                        FOR i = 0 TO indicatorslist.ItemCount - 1
                        IF INSTR(0 , indicatorslist.Item(i) , "StepRSI") > 0 THEN
                            EXIT FOR
                        END IF
                        NEXT i
                        indicatorslist.ItemIndex = i
                        btndelindi_click()
                        justrefreshchart
                        writealive
                        
                        useindischeckbox.Checked = 0
                        exportcollectionauto
                        writealive                        
                        tfmult.Text = "1"
                        tfmultok_click
                        barsdisplayed.Text = "300"
                        dispbarsok_click
                        writealive

                    END IF
                END IF


                FOR i = 0 TO indicatorslist.ItemCount - 1
                    IF INSTR(0 , indicatorslist.Item(i) , "StepRSI") > 0 THEN
                        EXIT FOR
                    END IF
                NEXT i
                indicatorslist.ItemIndex = i
                btndelindi_click()


            END IF

        END IF

        'if presignal2=1 then
        '
        'for i=0 to indicatorslist.Itemcount-1
        'if instr(0,indicatorslist.Item(i),"LSS Oscillator")>0 then
        'exit for
        'end if
        'next i
        'indicatorslist.itemindex=i
        'btnaddindi_click()
        'showcanvasclick
        ''justrefreshchart
        'writealive
        'sleep (val(pausesdurationedit.text))
        '
        'if (LSSbuffer(0)<=25 and LSSbuffer(0)>=-25) then
        'writealivetimer.enabled=1
        'if (val(mmm)<>240 and val(tfmult.text)<>6) then
        'if upordown=1 then
        'signallabel.caption="New sell signal detected!"
        'end if
        'if upordown=0 then
        'signallabel.caption="New buy signal detected!"
        'end if
        'signalsnd
        'mailform.visible=1
        'if enablemailer.checked=1 then
        '
        'buttonclick
        'end if
        'ini.Section="Settings"
        'ini.write("automation","0")
        'signaltrigger=1
        ''presignal2=1
        'end if
        'end if
        '
        'for i=0 to indicatorslist.Itemcount-1
        'if instr(0,indicatorslist.Item(i),"LSS Oscillator")>0 then
        'exit for
        'end if
        'next i
        'indicatorslist.itemindex=i
        'btndelindi_click()
        '
        'end if

    WEND

END SUB


SUB signalsndfrmclose
    writealivetimer.Enabled = 0
    PLAYWAV "" , SND_ASYNC OR SND_LOOP
END SUB

SUB signalsnd
    PLAYWAV homepath + "\wav\C-1MAJ.WAV" , SND_ASYNC OR SND_LOOP
    signalsndform.Visible = 1
    'playwav "",snd_async or snd_loop
END SUB

SUB stopclicked
    signaltrigger = 1
END SUB

SUB barsdisplayedchange
    ini.Section = "Settings"
    ini.Write("barsdisplayed" , barsdisplayed.Text)
END SUB

SUB cntbarseditchange
    ini.Section = "Settings"
    ini.Write("countedbars" , cntbarsedit.Text)
END SUB

SUB beginauto
    beginautotimer.Enabled = 1
END SUB

SUB beginexitsignal
    beginexitsignaltimer.Enabled = 1
END SUB

SUB beginauto2
    beginautotimer.Enabled = 0
    writealive
    barsdisplayed.Text = "300"
    cntbarsedit.Text = "400"
    DirList.update
    DIM rndcsvlistitem AS INTEGER
    DIM checkfilesize AS QFILESTREAM
    DIM csvlistsize AS INTEGER
    csvlistsize = 0
    WHILE csvlistsize < 102400
        rndcsvlistitem = RND(csvList.ItemCount)
        checkfilesize.open(DirList.Directory + "\" + csvList.Item(rndcsvlistitem) , fmOpenRead)
        csvlistsize = checkfilesize.Size
        checkfilesize.close
 'writealive
    WEND
    writealive

    DIM jjj AS string : jjj = csvList.Item(rndcsvlistitem)
    DIM kkk AS INTEGER
    kkk = INSTR(0 , jjj , ".")
    DIM lll AS STRING
    DIM iii AS INTEGER
    FOR iii = kkk - 1 TO 0 STEP - 1
        lll = MID$(jjj , iii , 1)
        IF ASC(lll) < 48 OR ASC(lll) > 57 THEN
            EXIT FOR
        END IF
 'writealive
    NEXT iii
    writealive
    DIM mmm AS STRING
    mmm = MID$(jjj , i + 1)
    mmm = MID$(mmm , 0 , INSTR(0 , mmm , ".") - 1)

    WHILE VAL(mmm) < 30
        rndcsvlistitem = RND(csvList.ItemCount)
        checkfilesize.open(DirList.Directory + "\" + csvList.Item(rndcsvlistitem) , fmOpenRead)
        csvlistsize = checkfilesize.Size
        checkfilesize.close
        jjj = csvList.Item(rndcsvlistitem)
        kkk = INSTR(0 , jjj , ".")
        FOR iii = kkk - 1 TO 0 STEP - 1
            lll = MID$(jjj , iii , 1)
            IF ASC(lll) < 48 OR ASC(lll) > 57 THEN
                EXIT FOR
            END IF
     'writealive
        NEXT iii
        mmm = MID$(jjj , iii + 1)
        mmm = MID$(mmm , 0 , INSTR(0 , mmm , ".") - 1)
 'writealive
    WEND    
    writealive
    importfileauto2(DirList.Directory + "\" + csvList.Item(rndcsvlistitem))
    writealive
    bbhlperiodedit.Text = bolliperedit.Text
    bbhlcppperiodedit.Text = bolliperedit.Text
    DIM iba AS INTEGER
    FOR iba = 0 TO indicatorslist.ItemCount - 1
        IF INSTR(0 , indicatorslist.Item(iba) , "BB - HL cpp") > 0 THEN
            EXIT FOR
        END IF
    NEXT iba
    indicatorslist.ItemIndex = iba
    btnaddindi_click()
    refresh_chart
    writealive
    autoreverse
END SUB

SUB beginexitsignal2
    beginexitsignaltimer.Enabled = 0
    barsdisplayed.Text = "300"
    cntbarsedit.Text = "300"
    DirList.update


    'if indicatorslistsel.Item(indicatorslist.itemindex)="" then
    'btnaddindi_click()
    'exit sub
    'end if
    'barsdisplayed.Text=200
    'justrefreshchart

    importfileauto2(DirList.Directory + "\" + csvList.Item(csvList.ItemIndex))
    refresh_chart
    'autoreverse
    beginexitsignal3
END SUB

SUB beginexitsignal3

    'section unfinished and portion of code not tested yet

    signaltrigger = 0

    'if indicatorslistsel.Item(indicatorslist.itemindex)="" then
    'btnaddindi_click()
    'exit sub
    'end if
    'barsdisplayed.Text=200
    'justrefreshchart

    WHILE signaltrigger = 0

        IF ini.exist THEN
            ini.Section = "Settings"
            IF VAL(ini.get("exitsignal" , "")) = 0 THEN
                signaltrigger = 1
                EXIT SUB
            END IF
        END IF

        writealive

        DIM i AS INTEGER
        FOR i = 0 TO indicatorslist.ItemCount - 1
            indicatorslist.ItemIndex = i
            btndelindi_click()
        NEXT i
        useindischeckbox.Checked = 0

        tfmult.Text = STR$(1)

        'sleep 2
        'print csvlist.directory+"\"+csvlist.item(rnd(csvlist.itemcount))
        DIM rndcsvlistitem AS INTEGER
        DIM checkfilesize AS QFILESTREAM
        DIM csvlistsize AS INTEGER
        csvlistsize = 0

        importfileauto(DirList.Directory + "\" + csvList.Item(csvList.ItemIndex))
        reimportfile()

        writealive
        'SLEEP(VAL(pausesdurationedit.Text))

        '---------------------------- Reversing

        DIM getline$ AS STRING

        IF FILEEXISTS(homepath + "\reversetmp.log") = FALSE THEN

            PRINT " file not found "
            EXIT SUB
        END IF

        DIM file AS QFILESTREAM
        file.open(homepath + "\reversetmp.log" , 0)

        DEFINT j = 0
        DIM revdate AS STRING
        DIM revtime AS STRING


        DO

            j ++

            getline$ = file.ReadLine

            IF INSTR(getline$ , "Reverse") > 0 THEN
                revdate = MID$(MID$(getline$ , INSTR(getline$ , "From Date: ")) , 12 , INSTR(MID$(getline$ , INSTR(getline$ , "From Date: ") + 11) , " ") - 1)
                revtime = MID$(MID$(getline$ , INSTR(getline$ , "From Date: ") + 11) , INSTR(MID$(getline$ , INSTR(getline$ , "From Date: ") + 11) , " ") + 1 , 5)
                findbarfromfile(revdate , revtime)
                reversetillendnorefresh
            END IF

        LOOP UNTIL file.eof
        file.close

        file.open(homepath + "\reversetmp.log" , 0)
        DIM revtfmu AS STRING
        revtfmu = ""
        DO

            'j++

            getline$ = file.ReadLine

            IF INSTR(getline$ , "changed") > 0 THEN
                IF revtfmu = "" THEN
                    revtfmu = MID$(getline$ , INSTR(getline$ , "to") + 3 , 3)
                END IF
            END IF

        LOOP UNTIL file.eof
        file.close

        'refreshgrids
    refreshgrids2  

        writealive
        'SLEEP(VAL(pausesdurationedit.Text))

        exp10sub
        writealive
        'SLEEP(VAL(pausesdurationedit.Text))
        savegridtmp
        cpptmpfuncreturn=varptr$(savegridtmpcpp())

        tfmult.Text = revtfmu
        tfmultok_click

        writealive
        'SLEEP(VAL(pausesdurationedit.Text))
        '--------------------------------------

        goto justexport
        FOR i = 0 TO indicatorslist.ItemCount - 1
            IF INSTR(0 , indicatorslist.Item(i) , "Center Of Gravity cpp") > 0 THEN
                EXIT FOR
            END IF
        NEXT i
        indicatorslist.ItemIndex = i
        btnaddindi_click()
        FOR i = 0 TO indicatorslist.ItemCount - 1
            IF INSTR(0 , indicatorslist.Item(i) , "Volatility Stop") > 0 THEN
                EXIT FOR
            END IF
        NEXT i
        indicatorslist.ItemIndex = i
        btnaddindi_click()
        'bbhlperiodedit.text=bolliperedit.text

        justrefreshchart

        writealive
        'SLEEP(VAL(pausesdurationedit.Text))    
defstr tmppath2      
DEFSTR url  
DEFSTR outFileName          
defstr zerostr="0"
defstr sqlbufferstr="sql"
defstr sqhbufferstr="sqh"
defstr fxbufferstr="fx"
defstr volatilitystopBuffer2str="volatilitystopBuffer2"
        ini.Section = "Settings"
        IF VAL(ini.get("exitsignaldir" , "")) = 1 THEN

            IF ((high(0) >= (val(varptr$(getbufferdata(varptr(sqlbufferstr),varptr(zerostr)))) + 0.5 * (val(varptr$(getbufferdata(varptr(fxbufferstr),varptr(zerostr)))) - val(varptr$(getbufferdata(varptr(sqlbufferstr),varptr(zerostr))))))) ) THEN ' OR (high(0) >= volatilitypivotema(0))
                writealivetimer.Enabled = 1
                signalsnd
                ini.Section = "Settings"
                ini.Write("exitsignal" , "0")
                'MailForm.Visible = 1
                ini.Section = "Settings"
                IF VAL(ini.get("mailer" , "")) = 1 THEN
                    'ButtonClick
                    'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)
                    url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                    outFileName = "signalmail.txt"
                    tmppath2 = CurDir$
                    CHDIR homepath
                    IF GetFileHTTP(url , outFileName) THEN
                    'SHOWMESSAGE "Download Error : " & url
                    'EXIT SUB
                    ELSE
                    'SHOWMESSAGE "Download Finished & OK : " & URL
                    END IF
                    CHDIR tmppath2

                END IF
                signaltrigger = 1
            END IF
        END IF

        ini.Section = "Settings"
        IF VAL(ini.get("exitsignaldir" , "")) = 0 THEN

            IF ((low(0) <= (val(varptr$(getbufferdata(varptr(sqhbufferstr),varptr(zerostr)))) - 0.5 * (val(varptr$(getbufferdata(varptr(sqhbufferstr),varptr(zerostr)))) - val(varptr$(getbufferdata(varptr(fxbufferstr),varptr(zerostr))))))) OR (low(0) <= val(varptr$(getbufferdata(varptr(volatilitystopBuffer2str),varptr(zerostr))))) ) THEN 
                writealivetimer.Enabled = 1
                signalsnd
                ini.Section = "Settings"
                ini.Write("exitsignal" , "0")
                'MailForm.Visible = 1
                ini.Section = "Settings"
                IF VAL(ini.get("mailer" , "")) = 1 THEN
                    'ButtonClick
                    'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)
                    url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                    outFileName = "signalmail.txt"
                    tmppath2 = CurDir$
                    CHDIR homepath
                    IF GetFileHTTP(url , outFileName) THEN
                    'SHOWMESSAGE "Download Error : " & url
                    'EXIT SUB
                    ELSE
                    'SHOWMESSAGE "Download Finished & OK : " & URL
                    END IF
                    CHDIR tmppath2

                END IF
                signaltrigger = 1
            END IF
        END IF


        FOR i = 0 TO indicatorslist.ItemCount - 1
            indicatorslist.ItemIndex = i
            btndelindi_click()
        NEXT i

        'justrefreshchart

        FOR i = 0 TO indicatorslist.ItemCount - 1
            IF INSTR(0 , indicatorslist.Item(i) , "Candle Average") > 0 THEN
                EXIT FOR
            END IF
        NEXT i
        indicatorslist.ItemIndex = i
        btnaddindi_click()

        'cntbarsedit.text="320"
        showcanvasclick

        'justrefreshchart
        writealive
        'SLEEP(VAL(pausesdurationedit.Text))

        ini.Section = "Settings"
        IF VAL(ini.get("exitsignaldir" , "")) = 1 THEN

            IF (candleavgsma(1) = 1) THEN
                writealivetimer.Enabled = 1
                signalsnd
                ini.Section = "Settings"
                ini.Write("exitsignal" , "0")
                'MailForm.Visible = 1
                ini.Section = "Settings"
                IF VAL(ini.get("mailer" , "")) = 1 THEN
                    'ButtonClick
                    'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)
                    url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                    outFileName = "signalmail.txt"
                    tmppath2 = CurDir$
                    CHDIR homepath
                    IF GetFileHTTP(url , outFileName) THEN
                    'SHOWMESSAGE "Download Error : " & url
                    'EXIT SUB
                    ELSE
                    'SHOWMESSAGE "Download Finished & OK : " & URL
                    END IF
                    CHDIR tmppath2

                END IF
                signaltrigger = 1
            END IF
        END IF
        'cntbarsedit.text="300"

        ini.Section = "Settings"
        IF VAL(ini.get("exitsignaldir" , "")) = 0 THEN

            IF (candleavgsma(1) = - 1) THEN
                writealivetimer.Enabled = 1
                signalsnd
                ini.Section = "Settings"
                ini.Write("exitsignal" , "0")
                'MailForm.Visible = 1
                ini.Section = "Settings"
                IF VAL(ini.get("mailer" , "")) = 1 THEN
                    'ButtonClick
                    'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)
                    url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                    outFileName = "signalmail.txt"
                    tmppath2 = CurDir$
                    CHDIR homepath
                    IF GetFileHTTP(url , outFileName) THEN
                    'SHOWMESSAGE "Download Error : " & url
                    'EXIT SUB
                    ELSE
                    'SHOWMESSAGE "Download Finished & OK : " & URL
                    END IF
                    CHDIR tmppath2

                END IF
                signaltrigger = 1
            END IF
        END IF


        FOR i = 0 TO indicatorslist.ItemCount - 1
            indicatorslist.ItemIndex = i
            btndelindi_click()
        NEXT i

        FOR i = 0 TO indicatorslist.ItemCount - 1
            IF INSTR(0 , indicatorslist.Item(i) , "Value Chart") > 0 THEN
                EXIT FOR
            END IF
        NEXT i
        indicatorslist.ItemIndex = i
        btnaddindi_click()
        'showcanvasclick
        justrefreshchart
        writealive
        'SLEEP(VAL(pausesdurationedit.Text))

        ini.Section = "Settings"
        IF VAL(ini.get("exitsignaldir" , "")) = 1 THEN
            IF (vh(0) >= 3.5) THEN
                writealivetimer.Enabled = 1
                signalsnd
                ini.Section = "Settings"
                ini.Write("exitsignal" , "0")
                'MailForm.Visible = 1
                ini.Section = "Settings"
                IF VAL(ini.get("mailer" , "")) = 1 THEN
                    'ButtonClick
                    'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)
                    url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                    outFileName = "signalmail.txt"
                    tmppath2 = CurDir$
                    CHDIR homepath
                    IF GetFileHTTP(url , outFileName) THEN
                    'SHOWMESSAGE "Download Error : " & url
                    'EXIT SUB
                    ELSE
                    'SHOWMESSAGE "Download Finished & OK : " & URL
                    END IF
                    CHDIR tmppath2

                END IF
                signaltrigger = 1
            END IF
        END IF

        ini.Section = "Settings"
        IF VAL(ini.get("exitsignaldir" , "")) = 0 THEN
            IF (vb(0) <= - 3.5) THEN
                writealivetimer.Enabled = 1
                signalsnd
                ini.Section = "Settings"
                ini.Write("exitsignal" , "0")
                'MailForm.Visible = 1
                ini.Section = "Settings"
                IF VAL(ini.get("mailer" , "")) = 1 THEN
                    'ButtonClick
                    'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)
                    url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                    outFileName = "signalmail.txt"
                    tmppath2 = CurDir$
                    CHDIR homepath
                    IF GetFileHTTP(url , outFileName) THEN
                    'SHOWMESSAGE "Download Error : " & url
                    'EXIT SUB
                    ELSE
                    'SHOWMESSAGE "Download Finished & OK : " & URL
                    END IF
                    CHDIR tmppath2

                END IF
                signaltrigger = 1
            END IF
        END IF


        FOR i = 0 TO indicatorslist.ItemCount - 1
            indicatorslist.ItemIndex = i
            btndelindi_click()
        NEXT i

        FOR i = 0 TO indicatorslist.ItemCount - 1
            IF INSTR(0 , indicatorslist.Item(i) , "Accelerator") > 0 THEN
                EXIT FOR
            END IF
        NEXT i
        indicatorslist.ItemIndex = i
        btnaddindi_click()
        'showcanvasclick
        justrefreshchart
        writealive
        'SLEEP(VAL(pausesdurationedit.Text))

        ini.Section = "Settings"
        IF VAL(ini.get("exitsignaldir" , "")) = 1 THEN
            IF (acceleratorbuffer0(1) >= 0) THEN
                writealivetimer.Enabled = 1
                signalsnd
                ini.Section = "Settings"
                ini.Write("exitsignal" , "0")
                'MailForm.Visible = 1
                ini.Section = "Settings"
                IF VAL(ini.get("mailer" , "")) = 1 THEN
                    'ButtonClick
                    'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)
                    url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                    outFileName = "signalmail.txt"
                    tmppath2 = CurDir$
                    CHDIR homepath
                    IF GetFileHTTP(url , outFileName) THEN
                    'SHOWMESSAGE "Download Error : " & url
                    'EXIT SUB
                    ELSE
                    'SHOWMESSAGE "Download Finished & OK : " & URL
                    END IF
                    CHDIR tmppath2

                END IF
                signaltrigger = 1
            END IF
        END IF

        ini.Section = "Settings"
        IF VAL(ini.get("exitsignaldir" , "")) = 0 THEN
            IF (acceleratorbuffer0(1) <= 0) THEN
                writealivetimer.Enabled = 1
                signalsnd
                ini.Section = "Settings"
                ini.Write("exitsignal" , "0")
                'MailForm.Visible = 1
                ini.Section = "Settings"
                IF VAL(ini.get("mailer" , "")) = 1 THEN
                    'ButtonClick
                    'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)
                    url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                    outFileName = "signalmail.txt"
                    tmppath2 = CurDir$
                    CHDIR homepath
                    IF GetFileHTTP(url , outFileName) THEN
                    'SHOWMESSAGE "Download Error : " & url
                    'EXIT SUB
                    ELSE
                    'SHOWMESSAGE "Download Finished & OK : " & URL
                    END IF
                    CHDIR tmppath2

                END IF
                signaltrigger = 1
            END IF
        END IF


        FOR i = 0 TO indicatorslist.ItemCount - 1
            indicatorslist.ItemIndex = i
            btndelindi_click()
        NEXT i

        FOR i = 0 TO indicatorslist.ItemCount - 1
            IF INSTR(0 , indicatorslist.Item(i) , "Force Index") > 0 THEN
                EXIT FOR
            END IF
        NEXT i
        indicatorslist.ItemIndex = i
        btnaddindi_click()
        'showcanvasclick
        justrefreshchart
        writealive
        'SLEEP(VAL(pausesdurationedit.Text))

        ini.Section = "Settings"
        IF VAL(ini.get("exitsignaldir" , "")) = 1 THEN
            IF (forceindexbuffer(1) >= 0) THEN
                writealivetimer.Enabled = 1
                signalsnd
                ini.Section = "Settings"
                ini.Write("exitsignal" , "0")
                'MailForm.Visible = 1
                ini.Section = "Settings"
                IF VAL(ini.get("mailer" , "")) = 1 THEN
                    'ButtonClick
                    'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)
                    url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                    outFileName = "signalmail.txt"
                    tmppath2 = CurDir$
                    CHDIR homepath
                    IF GetFileHTTP(url , outFileName) THEN
                    'SHOWMESSAGE "Download Error : " & url
                    'EXIT SUB
                    ELSE
                    'SHOWMESSAGE "Download Finished & OK : " & URL
                    END IF
                    CHDIR tmppath2

                END IF
                signaltrigger = 1
            END IF
        END IF

        ini.Section = "Settings"
        IF VAL(ini.get("exitsignaldir" , "")) = 0 THEN
            IF (forceindexbuffer(1) <= 0) THEN
                writealivetimer.Enabled = 1
                signalsnd
                ini.Section = "Settings"
                ini.Write("exitsignal" , "0")
                'MailForm.Visible = 1
                ini.Section = "Settings"
                IF VAL(ini.get("mailer" , "")) = 1 THEN
                    'ButtonClick
                    'RUN CHR$(34) + homepath + "\sendmail2.exe" + CHR$(34)
                    url = "http://www.qchartist.net/signalmail/signalmail.php?"+STR$(timeGetTime)
                    outFileName = "signalmail.txt"
                    tmppath2 = CurDir$
                    CHDIR homepath
                    IF GetFileHTTP(url , outFileName) THEN
                    'SHOWMESSAGE "Download Error : " & url
                    'EXIT SUB
                    ELSE
                    'SHOWMESSAGE "Download Finished & OK : " & URL
                    END IF
                    CHDIR tmppath2

                END IF
                signaltrigger = 1
            END IF
        END IF
        
        FOR i = 0 TO indicatorslist.ItemCount - 1
            indicatorslist.ItemIndex = i
            btndelindi_click()
        NEXT i
        justexport:
        useindischeckbox.Checked = 0
        justrefreshchart
        writealive
        useindischeckbox.Checked = 0
        exportcollectionauto
        writealive                        
        tfmult.Text = "1"
        tfmultok_click
        barsdisplayed.Text = "300"
        dispbarsok_click
        writealive

    WEND

END SUB

SUB operations

    hdc = getdc(frmMain.Handle)
    'polybezier(hdc,curve.pointer,i)
    PolyDraw(hdc , curve.pointer , btypes(1) , ipoly)
    releasedc(hdc , frmMain.Handle)
END SUB

SUB pdown
    drag = 1
END SUB

SUB pup
    drag = 0
END SUB

SUB pmove

    IF drag = 1 THEN

        DIM XVAL AS INTEGER , YVAL AS INTEGER
        'GetCursorPos(NPOS)
        'XVAL=NPOS.xpos
        'YVAL=NPOS.ypos
        'xval=xval-frmmain.left-graph.left-5-mouseexcentricityx
        'yval=yval-frmmain.top-graph.top-43-mouseexcentricityy
        XVAL = mousemovegraphx
        YVAL = mousemovegraphy

        sx2(sender.tag + 1) = SCREEN.MouseX - sender.Left
        sy2(sender.tag + 1) = SCREEN.MouseY - sender.Top

        sender.Left = XVAL + Graph.Left  'screen.mousex - frmmain.left-8
        sender.Top = YVAL + Graph.Top  'screen.mousey - frmmain.top-28
        sx2(sender.TabOrder + 1) = SCREEN.MouseX - frmMain.Left - 8
        sy2(sender.sender.TabOrder + 1) = SCREEN.MouseY - frmMain.Top - 28


        pbez.x = XVAL + Graph.Left  'sender.left
        pbez.y = YVAL + Graph.Top  'sender.top
        DIM old AS INTEGER
        old = curve.Position
        curve.Position = sender.tag
        curve.writeudt pbez
        curve.Position = old
        frmMain.Repaint
        operations
    END IF


END SUB

function ibarshift (timeframe as integer,datetimeserial as double, limit as integer) as integer

dim i as integer
dim proxiarray(0 TO 1000) as double
dim proxihighest as double,proxilowest as double

select case timeframe

    case 1:

    proxihighest = 0
    FOR i = 0 TO limit
        proxiarray(i)=datetimeserial1(i)/datetimeserial
        if proxiarray(i)>=1 then
            proxiarray(i)=proxiarray(i)-1
        else
            proxiarray(i)=1-proxiarray(i)
        end if
        IF proxiarray(i) > proxihighest THEN
                proxihighest = proxiarray(i)
            END IF
    NEXT i
    proxilowest = proxihighest
    FOR i = 0 TO limit
            IF proxiarray(i) < proxilowest THEN
                proxilowest = proxiarray(i)
            END IF
        NEXT i
    FOR i = 0 TO limit
            IF proxiarray(i)=proxilowest THEN
                result=i
                exit for
            END IF
        NEXT i

    case 5:

    proxihighest = 0
    FOR i = 0 TO limit
        proxiarray(i)=datetimeserial5(i)/datetimeserial
        if proxiarray(i)>=1 then
            proxiarray(i)=proxiarray(i)-1
        else
            proxiarray(i)=1-proxiarray(i)
        end if
        IF proxiarray(i) > proxihighest THEN
                proxihighest = proxiarray(i)
            END IF
    NEXT i
    proxilowest = proxihighest
    FOR i = 0 TO limit
            IF proxiarray(i) < proxilowest THEN
                proxilowest = proxiarray(i)
            END IF
        NEXT i
    FOR i = 0 TO limit
            IF proxiarray(i)=proxilowest THEN
                result=i
                exit for
            END IF
        NEXT i
    
    case 15:

    proxihighest = 0
    FOR i = 0 TO limit
        proxiarray(i)=datetimeserial15(i)/datetimeserial
        if proxiarray(i)>=1 then
            proxiarray(i)=proxiarray(i)-1
        else
            proxiarray(i)=1-proxiarray(i)
        end if
        IF proxiarray(i) > proxihighest THEN
                proxihighest = proxiarray(i)
            END IF
    NEXT i
    proxilowest = proxihighest
    FOR i = 0 TO limit
            IF proxiarray(i) < proxilowest THEN
                proxilowest = proxiarray(i)
            END IF
        NEXT i
    FOR i = 0 TO limit
            IF proxiarray(i)=proxilowest THEN
                result=i
                exit for
            END IF
        NEXT i
    
    case 30:

    proxihighest = 0
    FOR i = 0 TO limit
        proxiarray(i)=datetimeserial30(i)/datetimeserial
        if proxiarray(i)>=1 then
            proxiarray(i)=proxiarray(i)-1
        else
            proxiarray(i)=1-proxiarray(i)
        end if
        IF proxiarray(i) > proxihighest THEN
                proxihighest = proxiarray(i)
            END IF
    NEXT i
    proxilowest = proxihighest
    FOR i = 0 TO limit
            IF proxiarray(i) < proxilowest THEN
                proxilowest = proxiarray(i)
            END IF
        NEXT i
    FOR i = 0 TO limit
            IF proxiarray(i)=proxilowest THEN
                result=i
                exit for
            END IF
        NEXT i
    
    case 60:

    proxihighest = 0
    FOR i = 0 TO limit
        proxiarray(i)=datetimeserial60(i)/datetimeserial
        if proxiarray(i)>=1 then
            proxiarray(i)=proxiarray(i)-1
        else
            proxiarray(i)=1-proxiarray(i)
        end if
        IF proxiarray(i) > proxihighest THEN
                proxihighest = proxiarray(i)
            END IF
    NEXT i
    proxilowest = proxihighest
    FOR i = 0 TO limit
            IF proxiarray(i) < proxilowest THEN
                proxilowest = proxiarray(i)
            END IF
        NEXT i
    FOR i = 0 TO limit
            IF proxiarray(i)=proxilowest THEN
                result=i
                exit for
            END IF
        NEXT i
    
    case 240:

    proxihighest = 0
    FOR i = 0 TO limit
        proxiarray(i)=datetimeserial240(i)/datetimeserial
        if proxiarray(i)>=1 then
            proxiarray(i)=proxiarray(i)-1
        else
            proxiarray(i)=1-proxiarray(i)
        end if
        IF proxiarray(i) > proxihighest THEN
                proxihighest = proxiarray(i)
            END IF
    NEXT i
    proxilowest = proxihighest
    FOR i = 0 TO limit
            IF proxiarray(i) < proxilowest THEN
                proxilowest = proxiarray(i)
            END IF
        NEXT i
    FOR i = 0 TO limit
            IF proxiarray(i)=proxilowest THEN
                result=i
                exit for
            END IF
        NEXT i
    
    case 1440:

    proxihighest = 0
    FOR i = 0 TO limit
        proxiarray(i)=datetimeserial1440(i)/datetimeserial
        if proxiarray(i)>=1 then
            proxiarray(i)=proxiarray(i)-1
        else
            proxiarray(i)=1-proxiarray(i)
        end if
        IF proxiarray(i) > proxihighest THEN
                proxihighest = proxiarray(i)
            END IF
    NEXT i
    proxilowest = proxihighest
    FOR i = 0 TO limit
            IF proxiarray(i) < proxilowest THEN
                proxilowest = proxiarray(i)
            END IF
        NEXT i
    FOR i = 0 TO limit
            IF proxiarray(i)=proxilowest THEN
                result=i
                exit for
            END IF
        NEXT i
    
    case 10080:

    proxihighest = 0
    FOR i = 0 TO limit
        proxiarray(i)=datetimeserial10080(i)/datetimeserial
        if proxiarray(i)>=1 then
            proxiarray(i)=proxiarray(i)-1
        else
            proxiarray(i)=1-proxiarray(i)
        end if
        IF proxiarray(i) > proxihighest THEN
                proxihighest = proxiarray(i)
            END IF
    NEXT i
    proxilowest = proxihighest
    FOR i = 0 TO limit
            IF proxiarray(i) < proxilowest THEN
                proxilowest = proxiarray(i)
            END IF
        NEXT i
    FOR i = 0 TO limit
            IF proxiarray(i)=proxilowest THEN
                result=i
                exit for
            END IF
        NEXT i
    
    case 43200:

    proxihighest = 0
    FOR i = 0 TO limit
        proxiarray(i)=datetimeserial43200(i)/datetimeserial
        if proxiarray(i)>=1 then
            proxiarray(i)=proxiarray(i)-1
        else
            proxiarray(i)=1-proxiarray(i)
        end if
        IF proxiarray(i) > proxihighest THEN
                proxihighest = proxiarray(i)
            END IF
    NEXT i
    proxilowest = proxihighest
    FOR i = 0 TO limit
            IF proxiarray(i) < proxilowest THEN
                proxilowest = proxiarray(i)
            END IF
        NEXT i
    FOR i = 0 TO limit
            IF proxiarray(i)=proxilowest THEN
                result=i
                exit for
            END IF
        NEXT i
    
end select

end function

sub openhelpsub

run "hh.exe "+homepath + "\docs\QChartist.chm"

end sub

sub viewreadme
    
    frmreadme.Visible = 1
end sub

sub viewwhatsnew
    
    frmwhatsnew.Visible = 1
end sub

sub speechinitialization
' --------------------------- Setup/Initializations ---------------------

' Initialize Speech (Only needs to be called here, once).
rtn2=Begin_Speech(TEXT_BUFFER_SIZE)
IF rtn2=1 THEN
' Get the number of (TTS Engines) Voices.
voiceTotal=Count_Voices
IF voiceTotal>0 THEN
' Store the Voice Data (Name, Age, etc) for each (TTS Engine) Voice.
Enum_VoiceData
' Get Voice Data for the Current (TTS Engine) Voice.
vdPtr=Get_VoiceData(currentVoice)

ELSE
usespeech.checked=0
  Select Case MessageBox("SAPI4 Error - SAPI4 and/or Voice Engines NOT Installed."+chr$(10)+"Would you like QChartist to install them for you now?", "SAPI4/Voice Engines installation", 4)
      Case 6'// User selected Yes
            '// Add Yes code here
            run homepath + "\speech\spchapi.exe"
            run homepath + "\speech\msttsl.exe"

      Case 7'// User selected No
            '// Add No code here

  End Select

END IF
ELSE
usespeech.checked=0
ShowMessage("Speech Library Error - Library Speech NOT Available.")

END IF

defint i
for i= currentVoice to voiceTotal-1

if VarPtr$(vdPtr+512)="Mary" then
vdPtr=Get_VoiceData(i)   ' Get Voice Data for the Current (TTS Engine) Voice.
IF vdPtr<>0 THEN ' vdPtr is a pointer to the voiceData (index) Array.
volumespeech=Get_Volume(i)
pitch=Get_Pitch(i)
speed=Get_Speed(i)
end if
exit for
END IF

next i

say "Speech engine enabled"

end sub

SUB say(speech AS string)
if usespeech.checked=0 then exit sub
' Speak Text using the Current (TTS Engine) Voice. The text is ASCII Text
' (The C DLL uses WCHAR Text, but I convert it to BYTE/CHAR).
'
' REUSE_CURRENT_TTS - Do not delete the Current TTS Engine - No pause
'                     between button presses.
' NEW_TTS_ALWAYS    - Delete the Current TTS Engine - Pause between
'                     button presses (Safe Option)
'
' USE_CLIPBOARD or USE_TEXT. Using a string requires the address of that
' string (any Address so that this can utilize a Buffer). The clipboard
' will be read into internal buffers by the DLL. CLEAR_TEXT_BUFFER,
' CLEAR_CLIPBOARD_BUFFER and CLEAR_TEXTSPEECH_BUFFER allow you to zero
' the buffer/s before copying clipboard/text data to the buffer/s.
' CLEAR_ options were added so you can read the clipboard on the Fly
' (I.e Copy Clipboard, Read Clipboard and then copy again, read again
' without the first buffer overlapping. Use DONT_CLEAR_BUFFERS for
' overlap work.
stg$=speech
Speak_String(USE_TEXT,VarPtr(stg$),CLEAR_TEXTSPEECH_BUFFER,currentVoice,NEW_TTS_ALWAYS,USE_DEFAULT_VOLUME,volumespeech,USE_DEFAULT_PITCH,pitch,USE_DEFAULT_SPEED,speed)

' Set the volume to 32768 and Pause for 5 seconds. Tags on work whilst
' speaking (after Speak_String() has been called).
'
'Tag_Speech("\Vol=32768\ \Pau=5000\")


' As an example of Save_WAVFileEx I will save a WAV file with fast speech,
' to show that a WAV file can be saved differently to Speak_String.
' If you use the same parameters as Speak_String, with Save_WAVEFileEx,
' you can save the same voice/speech.
'
' Save_WAVFileEx on its own does not allow you to hear the speech - It
' just saves the speech (or whatevers in the Voice Engine`s buffer at
' the time. I.e nothing!) to a .WAV file. If you want to hear the speech
' before saving, use Speak_String and then Save_WAVFileEx.
'
' The clipboard TEXT contents can be saved as a WAV file if you
' USE_CLIPBOARD. 5000 is the default buffer size for text (add more
' if need be).
'
'Save_WAVFileEx("C:\\My Documents\\WAVFile1.wav",5000,USE_TEXT,VarPtr(stg$),CLEAR_TEXT_BUFFER,currentVoice,USE_DEFAULT_VOLUME,volume,USE_DEFINED_PITCH,&HBB,USE_DEFINED_SPEED,&HFF)


' The voice to use does not have to be the current voice. The buffer
' (text) and voiceNumber can be unique to this function or they can be
' the same as Speak_String()`s values. In other words. Either use
' Save_WAVFile() on its own (for simple text) or use Speak_String() for
' speech with more options.
'
'Save_WAVFile("C:\\My Documents\\WAVFile1.wav",currentVoice,VarPtr(stg$))
END SUB

sub speechdeinitialization
End_Speech     ' CleanUp the Speech (De-Initialize/Un-Initialize).
end sub

sub checkusespeech
if usespeech.checked=1 then 
speechinitialization
else 
speechdeinitialization
end if
end sub

sub showspeechform
speechform.visible=1
end sub

SUB exportfileauto()    

dim expfilename as string
    expfilename=homepath+"\"+StripFileName(importedfile(displayedfile))
    expfilename=MID$(expfilename , 0 , LEN(expfilename) - 4) + "x" + tfmult.Text + ".csv"    
    
        DIM csvFile AS QFILESTREAM
        csvFile.open(expfilename , 65535) '65535 = fmCreate
        DIM csvi AS INTEGER
        DIM datecsv AS STRING
        DIM timecsv AS STRING
        DIM opencsv AS STRING
        DIM highcsv AS STRING
        DIM lowcsv AS STRING
        DIM closecsv AS STRING
        DIM volumecsv AS STRING

        SELECT CASE axistypecomboitemindex
            CASE 0 :
                FOR csvi = 1 TO chartbars(displayedfile) 'val(csvbars)
                    datecsv = Grid.Cell(rowgridoffset + 1 , csvi)
                    timecsv = Grid.Cell(rowgridoffset + 2 , csvi)
                    opencsv = Grid.Cell(rowgridoffset + 3 , csvi)
                    highcsv = Grid.Cell(rowgridoffset + 4 , csvi)
                    lowcsv = Grid.Cell(rowgridoffset + 5 , csvi)
                    closecsv = Grid.Cell(rowgridoffset + 6 , csvi)
                    volumecsv = Grid.Cell(rowgridoffset + 7 , csvi)
                    csvFile.WriteLine(datecsv + "," + timecsv + "," + opencsv + "," + highcsv + "," + lowcsv + "," + closecsv + "," + volumecsv)
                NEXT csvi
            CASE 1 :
                FOR csvi = 1 TO chartbars(displayedfile) 'val(csvbars)
                    datecsv = Grid.Cell(rowgridoffset + 1 , csvi)
                    timecsv = Grid.Cell(rowgridoffset + 2 , csvi)
                    opencsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 3 , csvi))) , ffGeneral , 4 , 4)
                    highcsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 4 , csvi))) , ffGeneral , 4 , 4)
                    lowcsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 5 , csvi))) , ffGeneral , 4 , 4)
                    closecsv = strf$(log10(VAL(Grid.Cell(rowgridoffset + 6 , csvi))) , ffGeneral , 4 , 4)
                    volumecsv = ROUND(log10(VAL(Grid.Cell(rowgridoffset + 7 , csvi))))
                    csvFile.WriteLine(datecsv + "," + timecsv + "," + opencsv + "," + highcsv + "," + lowcsv + "," + closecsv + "," + volumecsv)
                NEXT csvi
        END SELECT
        csvFile.close
    
END SUB

SUB exportcollectionauto()

    useindi.Checked = 0

    exportfileauto

    barsdisplayed.Text = "7"
    dispbarsok_click

    DIM jjj AS string :
    jjj = importedfile(displayedfile)
    DIM kkk AS INTEGER
    kkk = INSTR(0 , jjj , ".")
    DIM iii AS INTEGER
    DIM lll AS STRING
    FOR iii = kkk - 1 TO 0 STEP - 1
        lll = MID$(jjj , iii , 1)
        IF ASC(lll) < 48 OR ASC(lll) > 57 THEN
            EXIT FOR
        END IF
    NEXT iii
    DIM mmm AS STRING
    mmm = MID$(jjj , iii + 1)
    mmm = MID$(mmm , 0 , INSTR(0 , mmm , ".") - 1)

    SELECT CASE VAL(mmm)

        CASE 30 :
            tfmult.Text = "48"
            tfmultok_click
            exportfileauto
            tfmult.Text = "336"
            tfmultok_click
            exportfileauto

        CASE 60 :
            tfmult.Text = "24"
            tfmultok_click
            exportfileauto
            tfmult.Text = "168"
            tfmultok_click
            exportfileauto

        CASE 240 :
            tfmult.Text = "6"
            tfmultok_click
            exportfileauto
            tfmult.Text = "42"
            tfmultok_click
            exportfileauto

    END SELECT

END SUB

'===============================================================================
' STRIPFILENAME : Returns file name (without path)
Function StripFileName (fullname as string) as string
result = right$(fullname, len(fullname) - rinstr(fullname, "\"))
end function
'===============================================================================

sub updates
'InetIsOffline returns 0 if you're connected
DefInt A

A = InetIsOffLine(0)
If A = 0 Then
'Print "Connected To Internet"
Else
'Print "Not Connected to Internet"
showmessage "No internet connection"
exit sub
End If

DEFSTR url = "http://www.qchartist.net/updates/builds.txt?"+STR$(timeGetTime)

    DEFSTR outFileName = "builds.txt"

    CHDIR homepath + "\updates"

    IF GetFileHTTP(url , outFileName) THEN
        SHOWMESSAGE "Download Error : " & url
        EXIT SUB
    ELSE
        'SHOWMESSAGE "Download Finished & OK : " & URL
    END IF
    
DIM lastver AS STRING
DIM lastverfile AS QFILESTREAM
lastverfile.open(homepath + "\updates\builds.txt" , fmOpenRead)
do
lastver = lastverfile.ReadLine() 'Read an entire line
loop until lastverfile.eof
lastverfile.close  

if (val(QC_build)<val(lastver)) then
'using DateFromSerial
'DEFLNG yy, mm, dd,DayOfWeek
'DayOfWeek = DateFromSerial(val(lastver), yy, mm, dd)
'defstr lastverstr=str$(yy)+"-"+str$(mm)+"-"+str$(dd)
'showmessage "A new version of QChartist is available (your version: "+QC_version+", last version: "+lastver+")"+chr$(10)+"Go to http://www.qchartist.net to download it."
IF MessageDlg("A new version of QChartist is available (your build: "+QC_build+", last build: "+lastver+")"+chr$(10)+"Upgrade now?", mtConfirmation, mbYes OR mbNo, 0) = mrYes THEN
    '-- Upgrade
    run homepath+"\update.exe"
    application.terminate

end if

else
showmessage "Your already have the lastest version of QChartist (build: "+QC_build+")"
end if
end sub

sub fibofanstandardradioclickedsub
symetryfrompoint=0
end sub

sub fibofansymetryfrompointradioclickedsub
symetryfrompoint=1
end sub

sub whatsnewsub

DEFSTR url = "http://www.qchartist.net/updates/readme.txt?"+STR$(timeGetTime)

    DEFSTR outFileName = "readme.txt"

    CHDIR homepath + "\updates"

    IF GetFileHTTP(url , outFileName) THEN
        SHOWMESSAGE "Download Error : " & url
        EXIT SUB
    ELSE
        'SHOWMESSAGE "Download Finished & OK : " & URL
    END IF
    
'dim whatsnewfile as qfilestream
    
'whatsnewfile.open (homepath + "\updates\readme.txt",fmopenread)
'dim whatsnewline as string

frmwhatsnew.visible=1

whatsnewedit.text=""
whatsnewedit.loadfromfile homepath + "\updates\readme.txt"

'do

'whatsnewline=whatsnewfile.readline
'whatsnewedit.text=whatsnewedit.text+whatsnewline+chr$(10)

'loop until whatsnewfile.eof    

'whatsnewfile.close

end sub

'-- ***********************************************************************'
sub FileCopy (FileSrc$, FileDst$) '- -----------------------------------'
'Andrew Shelkovenko dec 2003
'Copy FileSrc$ to FileDst$
' if path dest is not exists - create it.

dim FileSrc as QFileStream
dim FileDst as QFileStream
defstr dr$

dr$=StripPath (FileDst$) 
'print "dr$=" ,dr$

'MKDIR dr$ 'StripPath (FileDst$)

if dr$<>"" then
MKSubDir dr$
if DIREXISTS(dr$ ) =0 then showmessage ("FileCopy Can't create directory "+dr$ ): 'exit sub
end if

FileSrc.Open(FileSrc$, fmOpenRead) 
FileDst.Open(FileDst$, fmCreate) 

FileDst.CopyFrom  (FileSrc, 0)
        FileSrc.close
        FileDst.close
'print "FileCopy (";FileSrc$, FileDst$;") done" 
end sub

'===============================================================================
' STRIPPATH : Returns file path (without file name) 
Function StripPath (fullname as string) as string
result = left$(fullname, rinstr(fullname, "\"))
end function

'-- *****************************************************'
function MKSubDir (DirDst$) as short
'Andrew Shelkovenko dec 2003, jul 2004
'Create DirDst$ directory with full subdir structure
'----------------------------------------------
'print "MKSubDir DirDst$="; DirDst$
result=0
dim DirDst1$ as string
defint z1,z2
defstr SubDirDst$
DirDst1$=string$(len(DirDst$),"a") 
'chartooem DirDst$,DirDst1$ 
DirDst1$=DirDst$ 

if right$(DirDst1$,1)<>BkSl then DirDst1$=DirDst1$+BkSl 
z1=instr(DirDst1$,BkSl)
z2=0
while z1>0
SubDirDst$=left$(DirDst1$,z1 )
if DIREXISTS(SubDirDst$)=0 then MKDIR SubDirDst$ :'print "MKSubDir SubDirDst$=" ,SubDirDst$
z2=z1+1
z1=instr(z2,DirDst1$,BkSl)
wend

result=1
end function

declare sub datetest

sub hotkeysub

'For Cnthotkey = 0 To 255
'        If GetAsyncKeyState(Cnthotkey) <> 0 Then
'            print str$(Cnthotkey)
'            Exit sub
'        End If
'Next Cnthotkey

cnthotkey=82
If GetAsyncKeyState(Cnthotkey) <> 0 Then
'print "ok"
reimportfilesub
end if

cnthotkey=83
If GetAsyncKeyState(Cnthotkey) <> 0 Then
'print "ok"
defstr sndfreqstr=str$(400+ang_a_pub*3)
defstr snddurstr=str$(400)
cpptmpfuncreturn=varptr$(playsoundcpp(varptr(sndfreqstr),varptr(snddurstr)))
end if

cnthotkey=84
If GetAsyncKeyState(Cnthotkey) <> 0 Then
showmessage str$(datetimeserial(0))
defint zeroint=0
showmessage varptr$(timebcpp(varptr(zeroint)))
end if

cnthotkey=32
If GetAsyncKeyState(Cnthotkey) <> 0 Then
'print "ok"
graphclicked
end if

end sub

sub chatformsub
chatform.visible=1
end sub

sub swephformsub
swephform.visible=1
end sub

sub chatformtimerexpired
if usernameedit.text="" then exit sub
'InetIsOffline returns 0 if you're connected
DefInt A

A = InetIsOffLine(0)
If A = 0 Then
'Print "Connected To Internet"
Else
'Print "Not Connected to Internet"
'showmessage "No internet connection"
exit sub
End If

DEFSTR url
DEFSTR outFileName

url = "http://www.qchartist.net/messages/user_alive.php?user="+usernameedit.text+"&"+STR$(timeGetTime)

    outFileName = "user_alive.txt"

    CHDIR homepath + "\chat"

    IF GetFileHTTP(url , outFileName) THEN
        'SHOWMESSAGE "Download Error : " & url
        EXIT SUB
    ELSE
        'SHOWMESSAGE "Download Finished & OK : " & URL
    END IF
    
 
url = "http://www.qchartist.net/messages/retreive_users.php?"+STR$(timeGetTime)

    outFileName = "retreive_users.txt"

    CHDIR homepath + "\chat"

    IF GetFileHTTP(url , outFileName) THEN
        'SHOWMESSAGE "Download Error : " & url
        EXIT SUB
    ELSE
        'SHOWMESSAGE "Download Finished & OK : " & URL
    END IF

usernameslist.clear   
DIM retuser AS STRING
DIM retuserfile AS QFILESTREAM
retuserfile.open(homepath + "\chat\retreive_users.txt" , fmOpenRead)
do
usernameslist.additems retuserfile.ReadLine() 'Read an entire line
loop until retuserfile.eof
retuserfile.close 

url = "http://www.qchartist.net/messages/read_messages.php?"+STR$(timeGetTime)

    outFileName = "read_messages.txt"

    CHDIR homepath + "\chat"

    IF GetFileHTTP(url , outFileName) THEN
        'SHOWMESSAGE "Download Error : " & url
        EXIT SUB
    ELSE
        'SHOWMESSAGE "Download Finished & OK : " & URL
    END IF

chatbox.clear   
DIM readmsg AS STRING
DIM readmsgfile AS QFILESTREAM
readmsgfile.open(homepath + "\chat\read_messages.txt" , fmOpenRead)
do
chatbox.text=chatbox.text+readmsgfile.ReadLine()+chr$(10) 'Read an entire line
loop until readmsgfile.eof
readmsgfile.close 


end sub

sub chatformonshowsub
if usernameedit.text="" then
usernameedit.text="Guest"+STR$(timeGetTime)
end if
chatformtimerexpired
chatformtimer.enabled=1
end sub

sub chatformonclosesub
chatformtimer.enabled=0
end sub

sub sendmsgbtnonclicksub
if usernameedit.text="" then exit sub
if sendmsgedit.text="" then exit sub
'InetIsOffline returns 0 if you're connected
DefInt A

A = InetIsOffLine(0)
If A = 0 Then
'Print "Connected To Internet"
Else
'Print "Not Connected to Internet"
showmessage "No internet connection"
exit sub
End If

DEFSTR url
DEFSTR outFileName

url = "http://www.qchartist.net/messages/send_message.php?user="+usernameedit.text+"&message="+sendmsgedit.text+"&"+STR$(timeGetTime)

    outFileName = "send_message.txt"

    CHDIR homepath + "\chat"

    IF GetFileHTTP(url , outFileName) THEN
        'SHOWMESSAGE "Download Error : " & url
        EXIT SUB
    ELSE
        'SHOWMESSAGE "Download Finished & OK : " & URL
    END IF
    
sendmsgedit.text=""

chatformtimerexpired    

end sub

sub sendmsgeditkeydown(Key AS WORD)

IF Key = 13 then
sendmsgbtnonclicksub
CALL PeekMessage(MyMsg,NULL,WM_CHAR,WM_CHAR,PM_REMOVE) 'Remove message from queue
end if

end sub

function monthtostr(month as integer) as string
select case month
case 1: result="Jan"
case 2: result="Feb"
case 3: result="Mar"
case 4: result="Apr"
case 5: result="May"
case 6: result="Jun"
case 7: result="Jul"
case 8: result="Aug"
case 9: result="Sep"
case 10: result="Oct"
case 11: result="Nov"
case 12: result="Dec"
end select
end function

function strtomonth(str as string) as string
select case str
case "Jan": result="01"
case "Feb": result="02"
case "Mar": result="03"
case "Apr": result="04"
case "May": result="05"
case "Jun": result="06"
case "Jul": result="07"
case "Aug": result="08"
case "Sep": result="09"
case "Oct": result="10"
case "Nov": result="11"
case "Dec": result="12"
end select
end function

sub reimportfilesub
importfileauto(importedfile(displayedfile))
reimportfile()
end sub

sub pricescaleplusbtnclick
ymaxgraphglobal=ymaxgraphglobal/2
ymingraphglobal=ymingraphglobal/2
IF scrollchartpositionwait = 1 THEN
        IF scrollmodebtn.Flat = 0 THEN
            scrollmodebtn.Flat = 1
            scrollmodebtn.Color = &H88cc88
            scrollmode = 1
            Scrollchart.Enabled = 1
        END IF
        btnOnClick(drwBox)
    END IF
end sub

sub pricescaleminusbtnclick
ymaxgraphglobal=ymaxgraphglobal*2
ymingraphglobal=ymingraphglobal*2
IF scrollchartpositionwait = 1 THEN
        IF scrollmodebtn.Flat = 0 THEN
            scrollmodebtn.Flat = 1
            scrollmodebtn.Color = &H88cc88
            scrollmode = 1
            Scrollchart.Enabled = 1
        END IF
        btnOnClick(drwBox)
    END IF
end sub

' Sweph
Function outdeg(x As Double) As String
  defdbl fract = Abs(x) - Int(Abs(x))
  defdbl Min = Int(fract * 60)
  defdbl sec = fract * 3600 - Min * 60
  'result = Format(Sgn(x) * Int(Abs(x)), "###0") + "°" + Format(Min, "00") + "'" + Format(sec, "00.0000")
  defstr minstr=str$(min)
  if len(minstr)<2 then minstr="0"+minstr
  defstr secstr=replacesubstr$(Format$("%2.4f",sec),".",",")
  if len(mid$(secstr,1,instr(secstr,",")-1))<2 then secstr="0"+secstr
  result = str$(Sgn(x) * Int(Abs(x))) + "°" + minstr + "'" + secstr
End Function

Function outdeg3(x As Double) As String
  defdbl fract = Abs(x) - Int(Abs(x))
  defdbl Min = Int(fract * 60)
  defdbl sec = fract * 3600 - Min * 60
  'result = Format(Sgn(x) * Int(Abs(x)), "###0") + "°" + Format(Min, "00") + "'" + Format(sec, "00.0000")
  defstr hourstr=str$(Sgn(x) * Int(Abs(x)))
  if len(hourstr)=1 then hourstr="00"+hourstr
  if len(hourstr)=2 then hourstr="0"+hourstr  
  defstr minstr=str$(min)
  if len(minstr)<2 then minstr="0"+minstr
  defstr secstr=replacesubstr$(Format$("%2.4f",sec),".",",")
  if len(mid$(secstr,1,instr(secstr,",")-1))<2 then secstr="0"+secstr
  result = hourstr + "°" + minstr + "'" + secstr
End Function

' the DLL returns Null-terminated C strings; for VB the terminating NULL
' character must befound and the string length must be set accordingly
Function set_strlen(c$) As String
defint i = InStr(c$, Chr$(0))
If (i > 0) Then c$ = Left$(c$, i - 1)
result = c$
End Function

Sub bary_flag_Click()
 If bary_flag.checked=1 Then hel_flag.checked = 0
End Sub

Sub Compute_sweph_Click()
   
    Dim x(6) As Double
    Dim x2(6) As Double
    Dim cusp(13) As Double
    Dim ascmc(10) As Double
    Dim attr(20) As Double
    Dim tret(20) As Double
    Dim geopos(10) As Double
    Dim geoposx(10) As Double
    Dim xnasc(6) As Double
    Dim xndsc(6) As Double
    Dim xperi(6) As Double
    Dim xaphe(6) As Double
    Dim cal As Byte
    Dim o As orient
    Dim ss As String * 16
    cal = 103  ' g for gregorian calendar
    swephout.clear
    defdbl h = ihour + imin / 60
    'olen = LenB(ss)
    geopos(0) = lon
    geopos(1) = lat
    geopos(2) = 0
    
 ' the next two functions do the same job, converting a calendar date
 ' into a Julian day number
 ' swe_date_conversion() checks for legal dates while swe_julday() handles
 ' even illegal things like 45 Januar etc.

    defstr iyearstr,imonthstr,idaystr,hstr
    iyearstr=str$(iyear)
    imonthstr=str$(imonth)
    idaystr=str$(iday)
    hstr=str$(h)
    parameters=iyearstr+";"+imonthstr+";"+idaystr+";"+hstr+";1"
    defstr tjd_utstr=varptr$(swe_julday(varptr(parameters)))
    tjd_ut=val(tjd_utstr)
            
    parameters=iyearstr+";"+imonthstr+";"+idaystr+";"+hstr+";g;"+tjd_utstr
    defstr retvalstr=varptr$(swe_date_conversion(varptr(parameters)))
    deflng retval = val(retvalstr)

    If retval <> 0 Then
        showmessage "Illegal Date"
        Exit Sub
    End If        
    
    If et_flag.checked=1 Then
     defdbl tjd_et = tjd_ut
     defstr tjd_etstr=str$(tjd_et)
     tjd_ut = tjd_et - val(varptr$(swe_deltat(varptr(tjd_etstr))))
    Else    
     tjd_et = tjd_ut + val(varptr$(swe_deltat(varptr(tjd_utstr))))
    End If    
    
    defdbl t2 = tjd_ut - 2415018.5
    If t2 < 0 Then
      t2 = t2
    End If
    
    defstr tjd_ut_formated=Format$("%.8f", tjd_ut)
    defstr tjd_et_formated=Format$("%.8f", tjd_et)   
    
    defstr ut$
    
    'If is_equal(varptr(tjd_ut_formated),varptr(tjd_et_formated))=1 Then
    'If val(tjd_ut_formated)=val(tjd_et_formated) Then
    If tjd_ut=tjd_et Then
      ut$ = ""
      
    Else
      'ut$ = "  UT=" + Format(tjd_ut)
      ut$ = "  UT=" + tjd_ut_formated
    End If    
 
    swephout.text=swephout.text+"ET="+tjd_et_formated+" "+ ut$ + chr$(10)

    defint planet
     For planet = SE_SUN To SE_PLUTO_PICKERING
        deflng iflag = SEFLG_SPEED + SEFLG_SWIEPH
        If bary_flag.checked = 1 Then
            iflag = iflag + SEFLG_BARYCTR
        End If
        If hel_flag.checked = 1 Then
            iflag = iflag + SEFLG_HELCTR
        End If
        If is_j2000.checked = 1 Then
            iflag = iflag + SEFLG_J2000
        End If
        If Not is_apparent.checked = 1 Then
           iflag = iflag + SEFLG_TRUEPOS
        End If
        If is_sidereal.checked = 1 Then
           iflag = iflag + SEFLG_SIDEREAL
           'a = swe_set_sid_mode(SEFLG_SIDM_FAGAN_BRADLEY, 0, 0)
        End If
        defstr serr$ = String$(255, 0)
        defstr plnam$ = String$(20, 0)
        tjd_etstr=str$(tjd_et)
        defstr planetstr=str$(planet)
        defstr iflagstr=str$(iflag)
        defstr x0str=str$(x(0))
        parameters=tjd_etstr+";"+planetstr+";"+iflagstr
        defdbl ret_flag = val(varptr$(swe_calc(varptr(parameters),varptr(x(0)),varptr(serr$))))        

        serr$ = set_strlen(serr$)
        If ret_flag <> iflag And Len(serr$) > 0 Then
            swephout.text=swephout.text+"swe_calc reports: "+ serr$+chr$(10)
        End If

        parameters=planetstr+";"
        cpptmpfuncreturn=varptr$(swe_get_planet_name(varptr(parameters),varptr(plnam$)))

        plnam$ = set_strlen(plnam$)
        plnam$ = Left$(plnam$, 10)
        swephout.text=swephout.text+ plnam$+" "+ outdeg3(x(0))+" "+ outdeg(x(1))+"  "+ str$(x(2))+chr$(10)
        swephout.text=swephout.text+ plnam$+" "+ str$(x(0)* 0.017453)+" "+ str$(x(1)* 0.017453)+"  "+ str$(x(2))+chr$(10)

        If planet = SE_VESTA Then
          If add_hypo.checked = 0 Then Exit For
          planet = SE_CUPIDO    ' skip undefined planet numbers
          swephout.text=swephout.text+ ""
        End If
        'serr$ = String(255, 0)
        'retflag = swe_nod_aps_ut(tjd_ut, planet, iflag, 0, xnasc(0), xndsc(0), xperi(0), xaphe(0), serr$)
        'fMainForm.out.Print "  node", outdeg3(xnasc(0)), outdeg(xnasc(1)); "  ", xnasc(2)
        'serr$ = String(255, 0)
        'retflag = swe_rise_trans(tjd_ut, planet, "", 0, SE_CALC_RISE, geopos(0), 0, 0, tret(0), serr$)
        'fMainForm.out.Print "  rise", tret(0)
     Next planet
     ' if something was entered in the fixed star field, it is computed
     If Len(starname) > 0 Then
       serr$ = String$(255, "0")
       starname = starname + String$(40, "0")  ' make it at least 40 bytes
       'ret_flag = swe_fixstar(starname, tjd_et, iflag, x(0), serr$)
       serr$ = set_strlen(serr$)
       starname = set_strlen(starname)
       If ret_flag < 0 Then
         swephout.text=swephout.text+ "swe_fixstar() reports: "+ serr$
       Else
       swephout.text=swephout.text+ starname+" "+ outdeg3(x(0))+" "+ outdeg(x(1))+ "  "+ x(2)
       End If
     End If
     ' now come the houses
     If with_houses.checked=1 Then
       swephout.text=swephout.text+ ""
       'ret_flag = swe_houses_ex(tjd_ut, iflag, lat, lon, Asc("P"), cusp(0), ascmc(0))
       defint i
     For i = 1 To 12
        ' x(0) = cusp(i)
        ' x(1) = 0
        swephout.text=swephout.text+ "House "+" "+ i+" "+ outdeg3(cusp(i)) ' outdeg3(x(1)),
        If i Mod 3 = 0 Then swephout.text=swephout.text+ ""
       Next i
     End If
     'serr$ = String(255, 0)
     'ret_flag = swe_sol_eclipse_when_glob(tjd_ut, SEFLG_SWIEPH, 0, tret(0), 0, serr$)
     'serr$ = String(255, 0)
     'ret_flag = swe_sol_eclipse_where(tret(0), SEFLG_SWIEPH, geoposx(0), attr(0), serr$)
     'fMainForm.out.Print "eclipse "; ret_flag, tret(0), outdeg3(geoposx(0)), outdeg3(geopos(1)),
     'serr$ = String(255, 0)
     'ret_flag = swe_rise_trans(tjd_ut, SE_MOON, "", SEFLG_SWIEPH, SE_CALC_RISE, geopos(0), 1013.25, 10, tret(0), serr$)
     'fMainForm.out.Print "next rise of Moon "; ret_flag, tret(0), 'outdeg3(geoposx(0)), outdeg3(geopos(1)),
     'serr$ = String(255, 0)
     'retc = swe_time_equ(tjd_ut, tret(0), serr$)
     'fMainForm.out.Print " te", tret(0)
    'swe_close
End Sub

function get_helio_longitude(planet as integer,year as string,month as string,day as string,hour as string) as string
   
    Dim x(6) As Double
    Dim x2(6) As Double
    Dim cusp(13) As Double
    Dim ascmc(10) As Double
    Dim attr(20) As Double
    Dim tret(20) As Double
    Dim geopos(10) As Double
    Dim geoposx(10) As Double
    Dim xnasc(6) As Double
    Dim xndsc(6) As Double
    Dim xperi(6) As Double
    Dim xaphe(6) As Double
    Dim cal As Byte
    Dim o As orient
    Dim ss As String * 16
    cal = 103  ' g for gregorian calendar
    swephout.clear
    defdbl h = ihour + imin / 60
    'olen = LenB(ss)
    geopos(0) = lon
    geopos(1) = lat
    geopos(2) = 0
    
 ' the next two functions do the same job, converting a calendar date
 ' into a Julian day number
 ' swe_date_conversion() checks for legal dates while swe_julday() handles
 ' even illegal things like 45 Januar etc.

    defstr iyearstr,imonthstr,idaystr,hstr
    iyearstr=year 'str$(iyear)
    imonthstr=month 'str$(imonth)
    idaystr=day 'str$(iday)
    hstr=hour 'str$(h)
    parameters=iyearstr+";"+imonthstr+";"+idaystr+";"+hstr+";1"
    defstr tjd_utstr=varptr$(swe_julday(varptr(parameters)))
    tjd_ut=val(tjd_utstr)
            
    parameters=iyearstr+";"+imonthstr+";"+idaystr+";"+hstr+";g;"+tjd_utstr
    defstr retvalstr=varptr$(swe_date_conversion(varptr(parameters)))
    deflng retval = val(retvalstr)

    If retval <> 0 Then
        showmessage "Illegal Date"
        Exit Sub
    End If        
    
    'If et_flag.checked=1 Then
     defdbl tjd_et = tjd_ut
     defstr tjd_etstr=str$(tjd_et)
     tjd_ut = tjd_et - val(varptr$(swe_deltat(varptr(tjd_etstr))))
    'Else    
    ' tjd_et = tjd_ut + val(varptr$(swe_deltat(varptr(tjd_utstr))))
    'End If    
    
    defdbl t2 = tjd_ut - 2415018.5
    If t2 < 0 Then
      t2 = t2
    End If
    
    defstr tjd_ut_formated=Format$("%.8f", tjd_ut)
    defstr tjd_et_formated=Format$("%.8f", tjd_et)   
    
    defstr ut$
    
    'If is_equal(varptr(tjd_ut_formated),varptr(tjd_et_formated))=1 Then
    'If val(tjd_ut_formated)=val(tjd_et_formated) Then
    If tjd_ut=tjd_et Then
      ut$ = ""
      
    Else
      'ut$ = "  UT=" + Format(tjd_ut)
      ut$ = "  UT=" + tjd_ut_formated
    End If    
 
    'swephout.text=swephout.text+"ET="+tjd_et_formated+" "+ ut$ + chr$(10)

    'defint planet
     'For planet = SE_SUN To SE_PLUTO_PICKERING
        deflng iflag = SEFLG_SPEED + SEFLG_SWIEPH
        'If bary_flag.checked = 1 Then
        '    iflag = iflag + SEFLG_BARYCTR
        'End If
        'If hel_flag.checked = 1 Then
            iflag = iflag + SEFLG_HELCTR
        'End If
        'If is_j2000.checked = 1 Then
        '    iflag = iflag + SEFLG_J2000
        'End If
        'If Not is_apparent.checked = 1 Then
        '   iflag = iflag + SEFLG_TRUEPOS
        'End If
        'If is_sidereal.checked = 1 Then
        '   iflag = iflag + SEFLG_SIDEREAL
        '   'a = swe_set_sid_mode(SEFLG_SIDM_FAGAN_BRADLEY, 0, 0)
        'End If
        defstr serr$ = String$(255, 0)
        defstr plnam$ = String$(20, 0)
        tjd_etstr=str$(tjd_et)
        defstr planetstr=str$(planet)
        defstr iflagstr=str$(iflag)
        defstr x0str=str$(x(0))
        parameters=tjd_etstr+";"+planetstr+";"+iflagstr
        defdbl ret_flag = val(varptr$(swe_calc(varptr(parameters),varptr(x(0)),varptr(serr$))))        

        serr$ = set_strlen(serr$)
        If ret_flag <> iflag And Len(serr$) > 0 Then
            swephout.text=swephout.text+"swe_calc reports: "+ serr$+chr$(10)
        End If

        parameters=planetstr+";"
        cpptmpfuncreturn=varptr$(swe_get_planet_name(varptr(parameters),varptr(plnam$)))

        plnam$ = set_strlen(plnam$)
        plnam$ = Left$(plnam$, 10)
        'swephout.text=swephout.text+ plnam$+" "+ outdeg3(x(0))+" "+ outdeg(x(1))+"  "+ str$(x(2))+chr$(10)
        'swephout.text=swephout.text+ plnam$+" "+ str$(x(0)* 0.017453)+" "+ str$(x(1)* 0.017453)+"  "+ str$(x(2))+chr$(10)
        result=str$(x(0))

        'If planet = SE_VESTA Then
        '  If add_hypo.checked = 0 Then Exit For
        '  planet = SE_CUPIDO    ' skip undefined planet numbers
        '  swephout.text=swephout.text+ ""
        'End If
        'serr$ = String(255, 0)
        'retflag = swe_nod_aps_ut(tjd_ut, planet, iflag, 0, xnasc(0), xndsc(0), xperi(0), xaphe(0), serr$)
        'fMainForm.out.Print "  node", outdeg3(xnasc(0)), outdeg(xnasc(1)); "  ", xnasc(2)
        'serr$ = String(255, 0)
        'retflag = swe_rise_trans(tjd_ut, planet, "", 0, SE_CALC_RISE, geopos(0), 0, 0, tret(0), serr$)
        'fMainForm.out.Print "  rise", tret(0)
     'Next planet
     ' if something was entered in the fixed star field, it is computed
'     If Len(starname) > 0 Then
'       serr$ = String$(255, "0")
'       starname = starname + String$(40, "0")  ' make it at least 40 bytes
'       'ret_flag = swe_fixstar(starname, tjd_et, iflag, x(0), serr$)
'       serr$ = set_strlen(serr$)
'       starname = set_strlen(starname)
'       If ret_flag < 0 Then
'         swephout.text=swephout.text+ "swe_fixstar() reports: "+ serr$
'       Else
'       swephout.text=swephout.text+ starname+" "+ outdeg3(x(0))+" "+ outdeg(x(1))+ "  "+ x(2)
'       End If
'     End If
     ' now come the houses
'     If with_houses.checked=1 Then
'       swephout.text=swephout.text+ ""
'       'ret_flag = swe_houses_ex(tjd_ut, iflag, lat, lon, Asc("P"), cusp(0), ascmc(0))
'       defint i
'     For i = 1 To 12
'        ' x(0) = cusp(i)
'        ' x(1) = 0
'        swephout.text=swephout.text+ "House "+" "+ i+" "+ outdeg3(cusp(i)) ' outdeg3(x(1)),
'        If i Mod 3 = 0 Then swephout.text=swephout.text+ ""
'       Next i
'     End If
     'serr$ = String(255, 0)
     'ret_flag = swe_sol_eclipse_when_glob(tjd_ut, SEFLG_SWIEPH, 0, tret(0), 0, serr$)
     'serr$ = String(255, 0)
     'ret_flag = swe_sol_eclipse_where(tret(0), SEFLG_SWIEPH, geoposx(0), attr(0), serr$)
     'fMainForm.out.Print "eclipse "; ret_flag, tret(0), outdeg3(geoposx(0)), outdeg3(geopos(1)),
     'serr$ = String(255, 0)
     'ret_flag = swe_rise_trans(tjd_ut, SE_MOON, "", SEFLG_SWIEPH, SE_CALC_RISE, geopos(0), 1013.25, 10, tret(0), serr$)
     'fMainForm.out.Print "next rise of Moon "; ret_flag, tret(0), 'outdeg3(geoposx(0)), outdeg3(geopos(1)),
     'serr$ = String(255, 0)
     'retc = swe_time_equ(tjd_ut, tret(0), serr$)
     'fMainForm.out.Print " te", tret(0)
    'swe_close
End function

function get_ascmc(lat2 as double,lon2 as double,year as string,month as string,day as string,hour as string,ascormc as string) as string
   
    Dim x(6) As Double
    Dim x2(6) As Double
    Dim cusp(13) As Double
    Dim ascmc(10) As Double
    Dim attr(20) As Double
    Dim tret(20) As Double
    Dim geopos(10) As Double
    Dim geoposx(10) As Double
    Dim xnasc(6) As Double
    Dim xndsc(6) As Double
    Dim xperi(6) As Double
    Dim xaphe(6) As Double
    Dim cal As Byte
    Dim o As orient
    Dim ss As String * 16
    cal = 103  ' g for gregorian calendar
    swephout.clear
    defdbl h = ihour + imin / 60
    'olen = LenB(ss)
    geopos(0) = lon
    geopos(1) = lat
    geopos(2) = 0
    defstr latstr=str$(lat2)
    defstr lonstr=str$(lon2)
    
 ' the next two functions do the same job, converting a calendar date
 ' into a Julian day number
 ' swe_date_conversion() checks for legal dates while swe_julday() handles
 ' even illegal things like 45 Januar etc.

    defstr iyearstr,imonthstr,idaystr,hstr
    iyearstr=year 'str$(iyear)
    imonthstr=month 'str$(imonth)
    idaystr=day 'str$(iday)
    hstr=hour 'str$(h)
    parameters=iyearstr+";"+imonthstr+";"+idaystr+";"+hstr+";1"
    defstr tjd_utstr=varptr$(swe_julday(varptr(parameters)))
    tjd_ut=val(tjd_utstr)
            
    parameters=iyearstr+";"+imonthstr+";"+idaystr+";"+hstr+";g;"+tjd_utstr
    defstr retvalstr=varptr$(swe_date_conversion(varptr(parameters)))
    deflng retval = val(retvalstr)

    If retval <> 0 Then
        showmessage "Illegal Date"
        Exit Sub
    End If        
    
    'If et_flag.checked=1 Then
     defdbl tjd_et = tjd_ut
     defstr tjd_etstr=str$(tjd_et)
     tjd_ut = tjd_et - val(varptr$(swe_deltat(varptr(tjd_etstr))))
     tjd_utstr=str$(tjd_ut)
    'Else    
    ' tjd_et = tjd_ut + val(varptr$(swe_deltat(varptr(tjd_utstr))))
    'End If    
    
    defdbl t2 = tjd_ut - 2415018.5
    If t2 < 0 Then
      t2 = t2
    End If
    
    defstr tjd_ut_formated=Format$("%.8f", tjd_ut)
    defstr tjd_et_formated=Format$("%.8f", tjd_et)   
    
    defstr ut$
    
    'If is_equal(varptr(tjd_ut_formated),varptr(tjd_et_formated))=1 Then
    'If val(tjd_ut_formated)=val(tjd_et_formated) Then
    If tjd_ut=tjd_et Then
      ut$ = ""
      
    Else
      'ut$ = "  UT=" + Format(tjd_ut)
      ut$ = "  UT=" + tjd_ut_formated
    End If    
 
    'swephout.text=swephout.text+"ET="+tjd_et_formated+" "+ ut$ + chr$(10)

    'defint planet
     'For planet = SE_SUN To SE_PLUTO_PICKERING
        deflng iflag = SEFLG_SPEED + SEFLG_SWIEPH
        'If bary_flag.checked = 1 Then
        '    iflag = iflag + SEFLG_BARYCTR
        'End If
        'If hel_flag.checked = 1 Then
            iflag = iflag + SEFLG_HELCTR
        'End If
        'If is_j2000.checked = 1 Then
        '    iflag = iflag + SEFLG_J2000
        'End If
        'If Not is_apparent.checked = 1 Then
        '   iflag = iflag + SEFLG_TRUEPOS
        'End If
        'If is_sidereal.checked = 1 Then
        '   iflag = iflag + SEFLG_SIDEREAL
        '   'a = swe_set_sid_mode(SEFLG_SIDM_FAGAN_BRADLEY, 0, 0)
        'End If
        defstr serr$ = String$(255, 0)
        defstr plnam$ = String$(20, 0)
        tjd_etstr=str$(tjd_et)
        defstr planetstr=str$(planet)
        defstr iflagstr=str$(iflag)
        defstr x0str=str$(x(0))
        parameters=tjd_etstr+";"+planetstr+";"+iflagstr
        'defdbl ret_flag = val(varptr$(swe_calc(varptr(parameters),varptr(x(0)),varptr(serr$))))        

        'serr$ = set_strlen(serr$)
        'If ret_flag <> iflag And Len(serr$) > 0 Then
        '    swephout.text=swephout.text+"swe_calc reports: "+ serr$+chr$(10)
        'End If

        'parameters=planetstr+";"
        'cpptmpfuncreturn=varptr$(swe_get_planet_name(varptr(parameters),varptr(plnam$)))

        'plnam$ = set_strlen(plnam$)
        'plnam$ = Left$(plnam$, 10)
        'swephout.text=swephout.text+ plnam$+" "+ outdeg3(x(0))+" "+ outdeg(x(1))+"  "+ str$(x(2))+chr$(10)
        'swephout.text=swephout.text+ plnam$+" "+ str$(x(0)* 0.017453)+" "+ str$(x(1)* 0.017453)+"  "+ str$(x(2))+chr$(10)
        'result=str$(x(0))

        'If planet = SE_VESTA Then
        '  If add_hypo.checked = 0 Then Exit For
        '  planet = SE_CUPIDO    ' skip undefined planet numbers
        '  swephout.text=swephout.text+ ""
        'End If
        'serr$ = String(255, 0)
        'retflag = swe_nod_aps_ut(tjd_ut, planet, iflag, 0, xnasc(0), xndsc(0), xperi(0), xaphe(0), serr$)
        'fMainForm.out.Print "  node", outdeg3(xnasc(0)), outdeg(xnasc(1)); "  ", xnasc(2)
        'serr$ = String(255, 0)
        'retflag = swe_rise_trans(tjd_ut, planet, "", 0, SE_CALC_RISE, geopos(0), 0, 0, tret(0), serr$)
        'fMainForm.out.Print "  rise", tret(0)
     'Next planet
     ' if something was entered in the fixed star field, it is computed
'     If Len(starname) > 0 Then
'       serr$ = String$(255, "0")
'       starname = starname + String$(40, "0")  ' make it at least 40 bytes
'       'ret_flag = swe_fixstar(starname, tjd_et, iflag, x(0), serr$)
'       serr$ = set_strlen(serr$)
'       starname = set_strlen(starname)
'       If ret_flag < 0 Then
'         swephout.text=swephout.text+ "swe_fixstar() reports: "+ serr$
'       Else
'       swephout.text=swephout.text+ starname+" "+ outdeg3(x(0))+" "+ outdeg(x(1))+ "  "+ x(2)
'       End If
'     End If
     ' now come the houses
'     If with_houses.checked=1 Then
'       swephout.text=swephout.text+ ""
iflag =0
iflagstr=str$(iflag)
'parameters=latstr+";"+lonstr+";"+tjd_utstr+";"+str$(asc("P"))
'defdbl ret_flag = val(varptr$(swe_houses(varptr(parameters),varptr(cusp(0)),varptr(ascmc(0)))))
parameters=latstr+";"+lonstr+";"+tjd_utstr+";"+iflagstr+";"+str$(asc("P"))
'defdbl ret_flag = val(varptr$(swe_houses(varptr(parameters),varptr(cusp(0)),varptr(ascmc(0)))))
defdbl ret_flag = val(varptr$(swe_houses_ex(varptr(parameters),varptr(cusp(0)),varptr(ascmc(0)))))
if ascormc="asc" then result=str$(ascmc(0))
if ascormc="mc" then result=str$(ascmc(1))
'       'ret_flag = swe_houses_ex(tjd_ut, iflag, lat, lon, Asc("P"), cusp(0), ascmc(0))
'       defint i
'     For i = 1 To 12
'        ' x(0) = cusp(i)
'        ' x(1) = 0
'        swephout.text=swephout.text+ "House "+" "+ i+" "+ outdeg3(cusp(i)) ' outdeg3(x(1)),
'        If i Mod 3 = 0 Then swephout.text=swephout.text+ ""
'       Next i
'     End If
     'serr$ = String(255, 0)
     'ret_flag = swe_sol_eclipse_when_glob(tjd_ut, SEFLG_SWIEPH, 0, tret(0), 0, serr$)
     'serr$ = String(255, 0)
     'ret_flag = swe_sol_eclipse_where(tret(0), SEFLG_SWIEPH, geoposx(0), attr(0), serr$)
     'fMainForm.out.Print "eclipse "; ret_flag, tret(0), outdeg3(geoposx(0)), outdeg3(geopos(1)),
     'serr$ = String(255, 0)
     'ret_flag = swe_rise_trans(tjd_ut, SE_MOON, "", SEFLG_SWIEPH, SE_CALC_RISE, geopos(0), 1013.25, 10, tret(0), serr$)
     'fMainForm.out.Print "next rise of Moon "; ret_flag, tret(0), 'outdeg3(geoposx(0)), outdeg3(geopos(1)),
     'serr$ = String(255, 0)
     'retc = swe_time_equ(tjd_ut, tret(0), serr$)
     'fMainForm.out.Print " te", tret(0)
    'swe_close
End function

Sub Day_Change()
 iday = Val(Day.Text)
End Sub

Sub swephformonshowsub()
    iday = 1
    imonth = 1
    iyear = 1997
    lon = 8
    lat = 47
End Sub

Sub fstar_Change()
 starname = fstar.Text
End Sub

Sub geolat_Change()
  lat = Val(geolat)
End Sub

Sub geolon_Change()
  lon = Val(geolon)
End Sub

Sub hel_flag_Click()
  If hel_flag.checked=1 Then bary_flag.checked = 0
End Sub

Sub hour_Change()
 ihour = Val(hour.Text)
End Sub

Sub minute_Change()
 imin = Val(minute.Text)
End Sub

Sub Month_Change()
imonth = Val(Month.Text)
End Sub

Sub Year_Change()
iyear = Val(Year.Text)
End Sub

sub datetest

defstr $mydate="2015;02;15;00;00;00"
cpptmpfuncreturn=varptr$(date_to_unix_time(varptr($mydate)))
defdbl myunixtime=val(cpptmpfuncreturn)+3600
defstr myunixtimestr=Format$("%12.0f", myunixtime)
cpptmpfuncreturn=varptr$(unix_time_to_date(varptr(myunixtimestr)))
showmessage cpptmpfuncreturn
defstr year,month,day,hour,minute
year=mid$(cpptmpfuncreturn,21,4)
month=mid$(cpptmpfuncreturn,5,3)
day=mid$(cpptmpfuncreturn,9,2)
hour=mid$(cpptmpfuncreturn,12,2)
minute=mid$(cpptmpfuncreturn,15,2)
showmessage year+"-"+strtomonth(month)+"-"+day+" "+hour+":"+minute

end sub

sub detect_timeframe

defstr year0,month0,day0,hours0,minutes0
defstr year1,month1,day1,hours1,minutes1
defstr year2,month2,day2,hours2,minutes2
defdbl unix0,unix1,unix2

year0=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)),1,4)
month0=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)),6,2)
day0=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)),9,2)
hours0=mid$(Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile)),1,2)
minutes0=mid$(Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile)),4,2)

year1=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)-1),1,4)
month1=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)-1),6,2)
day1=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)-1),9,2)
hours1=mid$(Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile)-1),1,2)
minutes1=mid$(Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile)-1),4,2)

year2=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)-2),1,4)
month2=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)-2),6,2)
day2=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)-2),9,2)
hours2=mid$(Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile)-2),1,2)
minutes2=mid$(Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile)-2),4,2)

defstr $mydate0=year0+";"+month0+";"+day0+";"+hours0+";"+minutes0+";"+"00"
cpptmpfuncreturn=varptr$(date_to_unix_time(varptr($mydate0)))
unix0=val(cpptmpfuncreturn)
defstr $mydate1=year1+";"+month1+";"+day1+";"+hours1+";"+minutes1+";"+"00"
cpptmpfuncreturn=varptr$(date_to_unix_time(varptr($mydate1)))
unix1=val(cpptmpfuncreturn)
defstr $mydate2=year2+";"+month2+";"+day2+";"+hours2+";"+minutes2+";"+"00"
cpptmpfuncreturn=varptr$(date_to_unix_time(varptr($mydate2)))
unix2=val(cpptmpfuncreturn)

' Check if there is a week end in the interval
defdbl unixdiff_minutes
if (unix0-unix1)>(unix1-unix2) then
unixdiff_minutes=(unix1-unix2)/60
else
unixdiff_minutes=(unix0-unix1)/60
end if

charttf(displayedfile)=unixdiff_minutes
displayedfilestr=str$(displayedfile):defstr charttfdisplayedfilestr=str$(charttf(displayedfile)):cpptmpfuncreturn=varptr$(setcharttf(varptr(charttfdisplayedfilestr),varptr(displayedfilestr)))
writetf(displayedfile,charttf(displayedfile))
defstr tftowritestr=str$(charttf(displayedfile)):cpptmpfuncreturn=varptr$(writetfcpp(varptr(tftowritestr)))

end sub

sub addbars

DIM inputaddbars AS qinputbox , inputaddbarstxt AS STRING
inputaddbarstxt = inputaddbars.INPUT("How many bars to add?")
defint nbbarstoadd=val(inputaddbarstxt)

defint i

defstr year0,month0,day0,hours0,minutes0    
year0=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)),1,4)
month0=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)),6,2)
day0=mid$(Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)),9,2)
hours0=mid$(Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile)),1,2)
minutes0=mid$(Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile)),4,2)

defdbl myunixtime  
defstr myunixtimestr
defstr year,month,day,hour,minute  
    
defstr $mydate=year0+";"+month0+";"+day0+";"+hours0+";"+minutes0+";"+"00"
cpptmpfuncreturn=varptr$(date_to_unix_time(varptr($mydate)))
myunixtime=val(cpptmpfuncreturn)    
  
for i=chartbars(displayedfile)+1 to chartbars(displayedfile)+nbbarstoadd

myunixtime=myunixtime+charttf(displayedfile)*60

myunixtimestr=Format$("%12.0f", myunixtime)
cpptmpfuncreturn=varptr$(unix_time_to_date(varptr(myunixtimestr)))

year=mid$(cpptmpfuncreturn,21,4)
month=mid$(cpptmpfuncreturn,5,3)
day=mid$(cpptmpfuncreturn,9,2)
hour=mid$(cpptmpfuncreturn,12,2)
minute=mid$(cpptmpfuncreturn,15,2)

Grid.Cell(rowgridoffset + 1 , i) = year+"."+strtomonth(month)+"."+day
Grid.Cell(rowgridoffset + 2 , i) = hour+":"+minute
Grid.Cell(rowgridoffset + 3 , i) = Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile))
Grid.Cell(rowgridoffset + 4 , i) = Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile))
Grid.Cell(rowgridoffset + 5 , i) = Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile))
Grid.Cell(rowgridoffset + 6 , i) = Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile))
Grid.Cell(rowgridoffset + 7 , i) = "0"

next i    

chartbars(displayedfile) = chartbars(displayedfile)+nbbarstoadd
chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))

exportfilename

Scrollchart.Max = chartbars(displayedfile)
    Scrollchart.Position = chartbars(displayedfile)
    chartstart = Scrollchart.Position - numbars
    btnOnClick(drwBox)

end sub

sub astrowheelsettingssub
astrowheelsettingsform.visible=1
end sub

sub clockontimersub

clockdate=date$ ' MM-DD-YYYY
clocktime=time$ ' HH:MM:SS

end sub

sub symbolrefreshintervaleditonchange
quotetimer.interval=val(symbolrefreshintervaledit.text)
end sub

sub getquoteonoffbutonclick

if getquoteonoffbut.caption="Start" then
quotetimer.enabled=1
getquoteonoffbut.caption="Stop"
exit sub
end if

if getquoteonoffbut.caption="Stop" then
quotetimer.enabled=0
getquoteonoffbut.caption="Start"
end if

end sub

sub quoteontimersub

dim quotestream as qfilestream
defstr curquote=""
quotestream.open("c:\qchartist\perl\scripts\quote.txt",0)
while not quotestream.eof
curquote=curquote+quotestream.readline
wend
quotestream.close

if curquote<>"" then currentquote=curquote

btnOnClick(drwBox)

dim busystream as qfilestream
busystream.open("c:\qchartist\perl\scripts\isbusy.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

defstr cur1=mid$(symboledit.text,1,3)
defstr cur2=mid$(symboledit.text,4,3)

if val(isbusy)=0 then
dim pid as long
defstr tmppath=curdir$
chdir "c:\qchartist\perl\scripts"
if like(platform,"*Wine*")=0 then
if currencytype.checked=1 then pid=shell ("getcurrency.bat "+cur1+" "+cur2,0)
if stocktype.checked=1 then pid=shell ("getstock.bat "+placecombobox.item(placecombobox.itemindex)+" "+symboledit.text,0)
end if
if like(platform,"*Wine*")=1 then
if currencytype.checked=1 then pid=shell ("/bin/sh -c "+chr$(34)+"./getcurrency.sh "+cur1+" "+cur2+chr$(34),0)
if stocktype.checked=1 then pid=shell ("/bin/sh -c "+chr$(34)+"./getstock.sh "+placecombobox.item(placecombobox.itemindex)+" "+symboledit.text+chr$(34),0)
end if
'else
'showmessage "busy"
chdir tmppath
end if

end sub

sub previousbarbuttonclick

if astrowheelmarketbar>1 and getquoteonoffbut.caption="Start" and openedchartpriceradio.checked=1 then

astrowheelmarketbar=astrowheelmarketbar-1

defstr date=Grid.Cell(rowgridoffset + 1 , astrowheelmarketbar)
defstr time=Grid.Cell(rowgridoffset + 2 , astrowheelmarketbar)                    

defstr year,month,day,hour,minute

year=mid$(date,1,4)
month=mid$(date,6,2)
day=mid$(date,9,2)
specifydatecal.y=val(year)
specifydatecal.m=val(month)
specifydatecal.d=val(day)     
specifydatecal.panel2.caption=year+"-"+month+"-"+day
specifytimeedit.Text=time

btnOnClick(drwBox)

end if

end sub

sub nextbarbuttonclick

if astrowheelmarketbar<chartbars(displayedfile) and getquoteonoffbut.caption="Start" and openedchartpriceradio.checked=1 then

if astrowheelmarketbar=0 then btnOnClick(drwBox)

astrowheelmarketbar=astrowheelmarketbar+1

defstr date=Grid.Cell(rowgridoffset + 1 , astrowheelmarketbar)
defstr time=Grid.Cell(rowgridoffset + 2 , astrowheelmarketbar)                    

defstr year,month,day,hour,minute

year=mid$(date,1,4)
month=mid$(date,6,2)
day=mid$(date,9,2)
specifydatecal.y=val(year)
specifydatecal.m=val(month)
specifydatecal.d=val(day)
Dim pBuffer As String, ST As SYSTEMTIME     
specifydatecal.panel2.caption=year+"-"+month+"-"+day
specifytimeedit.Text=time

btnOnClick(drwBox)

end if

end sub

sub googlegetquotesub

IF dssource.ItemIndex = 2 THEN
    SELECT CASE dstimeframe.ItemIndex
        CASE 5  :
            SHOWMESSAGE "Google Finance supports only timeframes between 1M and 60M"
            dsok.Enabled = 1
            EXIT SUB
        CASE 6  :
            SHOWMESSAGE "Google Finance supports only timeframes between 1M and 60M"
            dsok.Enabled = 1
            EXIT SUB
        CASE 7  :
            SHOWMESSAGE "Google Finance supports only timeframes between 1M and 60M"
            dsok.Enabled = 1
            EXIT SUB
        CASE 8  :
            SHOWMESSAGE "Google Finance supports only timeframes between 1M and 60M"
            dsok.Enabled = 1
            EXIT SUB
    END SELECT
END IF

IF dssource.ItemIndex = 0 THEN
    SELECT CASE dstimeframe.ItemIndex
        CASE 0  :
            SHOWMESSAGE "Yahoo Finance real time supports only daily timeframe"
            dsok.Enabled = 1
            EXIT SUB
        CASE 1  :
            SHOWMESSAGE "Yahoo Finance real time supports only daily timeframe"
            dsok.Enabled = 1
            EXIT SUB
        CASE 2  :
            SHOWMESSAGE "Yahoo Finance real time supports only daily timeframe"
            dsok.Enabled = 1
            EXIT SUB
        CASE 3  :
            SHOWMESSAGE "Yahoo Finance real time supports only daily timeframe"
            dsok.Enabled = 1
            EXIT SUB
        CASE 4  :
            SHOWMESSAGE "Yahoo Finance real time supports only daily timeframe"
            dsok.Enabled = 1
            EXIT SUB
        CASE 5  :
            SHOWMESSAGE "Yahoo Finance real time supports only daily timeframe"
            dsok.Enabled = 1
            EXIT SUB
        CASE 7  :
            SHOWMESSAGE "Yahoo Finance real time supports only daily timeframe"
            dsok.Enabled = 1
            EXIT SUB
        CASE 8  :
            SHOWMESSAGE "Yahoo Finance real time supports only daily timeframe"
            dsok.Enabled = 1
            EXIT SUB            
    END SELECT
END IF

busystream.Open("c:\qchartist\csv\google\isbusy.txt" , fmCreate)
busystream.WriteLine("1")
busystream.Close

'dim pid as integer
'pid=shell ("getcurrency.bat EUR USD",1)
'goingto="readquote":busytimer.enabled=1

DEFSTR tmpdir = CurDir$
CHDIR "c:\qchartist\csv\google"

DIM pid AS INTEGER

DIM dstf AS STRING
SELECT CASE dstimeframe.ItemIndex
    CASE 0  :
        dstf = "1"
    CASE 1  :
        dstf = "5"
    CASE 2  :
        dstf = "15"
    CASE 3  :
        dstf = "30"
    CASE 4  :
        dstf = "60"
    CASE 5  :
        dstf = "240"
    CASE 6  :
        dstf = "1440"
    CASE 7  :
        dstf = "10080"
    CASE 8  :
        dstf = "43200"
END SELECT

IF googlerealtimecheckbox.Checked = 0 THEN
    pid = SHELL("getdata.bat " + STR$(VAL(dstf) * 60) + " " + googledaysbackedit.Text + " " + UCASE$(dssymboledit.Text) , 0)
ELSE
    pid = SHELL("getdata.bat " + STR$(1 * 60) + " " + googledaysbackedit.Text + " " + UCASE$(dssymboledit.Text) , 0)
    IF dssource.ItemIndex = 2 THEN pid = SHELL("getdata2.bat " + STR$(VAL(dstf) * 60) + " " + googledaysbackedit.Text + " " + UCASE$(dssymboledit.Text) , 0)
    IF dssource.ItemIndex = 0 THEN
        DEFINT A

        A = InetIsOffLine(0)
        IF A = 0 THEN
            'Print "Connected To Internet"
        ELSE
            'Print "Not Connected to Internet"
            SHOWMESSAGE "No internet connection"
            EXIT SUB
        END IF
        dsok.Enabled = 0
        DIM dsstartcalendarobjm AS STRING , dsstartcalendarobjd AS STRING , dsstartcalendarobjy AS STRING , dsendcalendarobjm AS STRING , dsendcalendarobjd AS STRING , dsendcalendarobjy AS STRING
        dsstartcalendarobjd = MID$(dsstartcalendarobj.Text , 4 , 2)
        dsstartcalendarobjm = MID$(dsstartcalendarobj.Text , 1 , 2)
        dsstartcalendarobjy = MID$(dsstartcalendarobj.Text , 7 , 4)
        dsendcalendarobjd = MID$(dsendcalendarobj.Text , 4 , 2)
        dsendcalendarobjm = MID$(dsendcalendarobj.Text , 1 , 2)
        dsendcalendarobjy = MID$(dsendcalendarobj.Text , 7 , 4)

        DEFSTR url
        IF dssource.ItemIndex = 0 THEN url = "http://ichart.finance.yahoo.com/table.csv?s=" + UCASE$(dssymboledit.Text) + "&a=" + dsstartcalendarobjm + "&b=" + dsstartcalendarobjd + "&c=" + dsstartcalendarobjy + "&d=" + dsendcalendarobjm + "&e=" + dsendcalendarobjd + "&f=" + dsendcalendarobjy + "&g=" + LCASE$(LEFT$(dstimeframe.Item(dstimeframe.ItemIndex) , 1)) + "&ignore=.csv"
        'if dssource.itemindex=1 then url = "http://stooq.com/q/d/l/?s=" + LCASE$(dssymboledit.Text) + "&d1="+dsstartcalendarobjy+dsstartcalendarobjm+dsstartcalendarobjd+"&d2="+dsendcalendarobjy+dsendcalendarobjm+dsendcalendarobjd+"&i="+ LCASE$(LEFT$(dstimeframe.Item(dstimeframe.ItemIndex) , 1))
        'if dssource.itemindex=2 then
        'googlegetquotesub
        'exit sub
        'end if
        DEFSTR outFileName = UCASE$(dssymboledit.Text) + dstf + ".csv"

        CHDIR homepath + "\csv"

        IF GetFileHTTP(url , outFileName) THEN
            SHOWMESSAGE "Download Error : " & url
            dsok.Enabled = 1
            EXIT SUB
        ELSE
            'PRINT "Download Finished & OK : " & URL
            'showmessage "Download Finished & OK : " & URL
            DIM filestream AS QFILESTREAM
            DEFSTR filecontentstr = ""
            filestream.Open(outFileName , 0)
            WHILE NOT filestream.eof
                filecontentstr = filecontentstr + filestream.ReadLine
            WEND
            IF VAL(barsdisplayed.Text) > filestream.LineCount - 1 AND LEN(filecontentstr) > 7 THEN barsdisplayed.Text = STR$(filestream.LineCount - 1)
            filestream.Close
            IF LEN(filecontentstr) < 8 THEN
                SHOWMESSAGE "Invalid symbol"
                dsok.Enabled = 1
                EXIT SUB
            END IF
            IF VAL(barsdisplayed.Text) < 1 THEN barsdisplayed.Text = "1"
        END IF
    END IF
END IF
googlegoingto = "googlereadquote"  :  googlebusytimer.Interval = 1000  :  googlebusytimer.Enabled = 1

CHDIR tmpdir

end sub

SUB googlebusytimersub

    'defint pid
    DIM googlebusystream AS QFILESTREAM
    IF googlegoingto = "googlereadquote" THEN googlebusystream.Open("c:\qchartist\csv\google\isbusy.txt" , 0)
    IF googlegoingto = "googlereadlastquote" THEN googlebusystream.Open("c:\qchartist\perl\scripts\isbusy.txt" , 0)
    DEFSTR isbusy = ""
    WHILE NOT googlebusystream.eof
        isbusy = isbusy + googlebusystream.ReadLine
    WEND
    googlebusystream.Close

    IF googlegoingto = "googlereadquote" AND googlerealtimecheckbox.Checked = 1 THEN
        googlebusystream.Open("c:\qchartist\csv\google\isbusy2.txt" , 0)
        DEFSTR isbusy2 = ""
        WHILE NOT googlebusystream.eof
            isbusy2 = isbusy2 + googlebusystream.ReadLine
        WEND
        googlebusystream.Close
    END IF

    IF googlerealtimecheckbox.Checked = 1 AND VAL(isbusy2) = 1 THEN EXIT SUB

    IF VAL(isbusy) = 0 THEN

        googlebusytimer.Enabled = 0
        SELECT CASE googlegoingto

            CASE "googlereadquote"
                GOTO googlereadquote
                'case "googlereadlastquote"
                'goto googlereadlastquote

        END SELECT

    END IF

    EXIT SUB

    googlereadquote :
    DIM dstf AS STRING
    SELECT CASE dstimeframe.ItemIndex
        CASE 0  :
            dstf = "1"
        CASE 1  :
            dstf = "5"
        CASE 2  :
            dstf = "15"
        CASE 3  :
            dstf = "30"
        CASE 4  :
            dstf = "60"
        CASE 5  :
            dstf = "240"
        CASE 6  :
            dstf = "1440"
        CASE 7  :
            dstf = "10080"
        CASE 8  :
            dstf = "43200"
    END SELECT

    IF googlerealtimecheckbox.Checked = 1 THEN
        DEFSTR dstfreal = dstf
        dstf = "1"
    END IF

    DEFSTR currentime00 = VARPTR$(current_time())
    DEFSTR ft00 = VARPTR$(unix_time_to_date(VARPTR(currentime00)))
    DEFSTR year00 = MID$(ft00 , 21 , 4)
    DEFSTR month00 = MID$(ft00 , 5 , 3)
    DEFSTR day00 = MID$(ft00 , 9 , 2)
    DEFSTR hour00 = MID$(ft00 , 12 , 2)
    DEFSTR minute00 = MID$(ft00 , 15 , 2)

    'if val(dstf)<>1 and googlerealtimecheckbox.checked=1 then
    'showmessage "Realtime mode only works for 1M timeframe until now. Please choose 1M instead."
    'dsok.enabled=1
    'exit sub
    'end if

    'if dstf="1" then
    IF VAL(MID$(TIME$ , 7 , 2)) > 10 AND googlerealtimecheckbox.Checked = 1 THEN
        clock.Visible = 1
        timclock.Enabled = 1
        pleasewaitclocklabel.Caption = "Please wait " + STR$(60 - VAL(MID$(TIME$ , 7 , 2))) + "s"
        googlegoingto = "googlereadquote" : googlebusytimer.Enabled = 1
        EXIT SUB
    END IF
    'end if

    DIM filestream AS QFILESTREAM
    filestream.Open("c:\qchartist\csv\google\connection_status.log" , 0)
    DEFSTR filestr = ""
    WHILE NOT filestream.eof
        filestr = filestr + filestream.ReadLine
    WEND
    filestream.Close
    'check if connection exists
    IF like(filestr , "*80... connected*200 OK*") = 0 THEN
        PRINT "Can't connect to Google Finance"
        googlerealtimecheckbox.Checked = 0
        dsok.Enabled = 1
        'googlerealtimebusytimer.enabled=0
        EXIT SUB
    END IF

    googlecurrenttimestamp = VAL(VARPTR$(current_time())) 'val(Format$("%.8f",varptr$(current_time())))

    filestream.Open("c:\qchartist\csv\google\Google_quotes.txt" , 0)
    filestr = ""
    WHILE NOT filestream.eof
        filestr = filestr + filestream.ReadLine
        DOEVENTS
    WEND
    filestream.Close
    IF like(filestr , "*EXCHANGE*NASDAQ*") = 1 THEN
        'showmessage "realtime"
    END IF
    IF like(filestr , "*a*") = 0 THEN
        PRINT "Invalid symbol"
        dsok.Enabled = 1
        'googlerealtimebusytimer.enabled=0
        EXIT SUB
    END IF


    DEFSTR outFileName = UCASE$(dssymboledit.Text) + dstf + ".csv"
    DEFINT lineloop = 0

    filestream.Open("c:\qchartist\csv\google\Google_quotes.txt" , 0)
    DIM filestream2 AS QFILESTREAM
    filestream2.Open("c:\qchartist\csv\" + outFileName , fmCreate)
    filestr = ""
    DEFSTR fileline = ""

    WHILE NOT filestream.eof

        fileline = filestream.ReadLine
        lineloop ++

        IF lineloop > 7 THEN


            IF MID$(fileline , 1 , 1) = "a" THEN
                DEFINT comaposition = INSTR(fileline , ",")
                DEFINT comaposition2 = INSTR(comaposition + 1 , fileline , ",")
                DEFINT comaposition3 = INSTR(comaposition2 + 1 , fileline , ",")
                DEFINT comaposition4 = INSTR(comaposition3 + 1 , fileline , ",")
                DEFINT comaposition5 = INSTR(comaposition4 + 1 , fileline , ",")
                DEFSTR closestr = MID$(fileline , comaposition + 1 , comaposition2 - comaposition - 1)
                DEFSTR highstr = MID$(fileline , comaposition2 + 1 , comaposition3 - comaposition2 - 1)
                DEFSTR lowstr = MID$(fileline , comaposition3 + 1 , comaposition4 - comaposition3 - 1)
                DEFSTR openstr = MID$(fileline , comaposition4 + 1 , comaposition5 - comaposition4 - 1)
                DEFSTR volumestr = MID$(fileline , comaposition5 + 1 , LEN(fileline) - comaposition5 - 1)
                DEFSTR ut = MID$(fileline , 2 , comaposition - 2)
                DEFSTR ft = VARPTR$(unix_time_to_date(VARPTR(ut)))
                DEFSTR year , month , day , hour , minute
                year = MID$(ft , 21 , 4)
                month = MID$(ft , 5 , 3)
                day = MID$(ft , 9 , 2)
                hour = MID$(ft , 12 , 2)
                minute = MID$(ft , 15 , 2)
                ft = year + "-" + strtomonth(month) + "-" + day + "," + hour + ":" + minute
                fileline = ft + "," + openstr + "," + highstr + "," + lowstr + "," + closestr + "," + volumestr

            ELSE
                IF LEFT$(fileline , 8) <> "TIMEZONE" THEN
                    comaposition = INSTR(fileline , ",")
                    comaposition2 = INSTR(comaposition + 1 , fileline , ",")
                    comaposition3 = INSTR(comaposition2 + 1 , fileline , ",")
                    comaposition4 = INSTR(comaposition3 + 1 , fileline , ",")
                    comaposition5 = INSTR(comaposition4 + 1 , fileline , ",")
                    closestr = MID$(fileline , comaposition + 1 , comaposition2 - comaposition - 1)
                    highstr = MID$(fileline , comaposition2 + 1 , comaposition3 - comaposition2 - 1)
                    lowstr = MID$(fileline , comaposition3 + 1 , comaposition4 - comaposition3 - 1)
                    openstr = MID$(fileline , comaposition4 + 1 , comaposition5 - comaposition4 - 1)
                    volumestr = MID$(fileline , comaposition5 + 1 , LEN(fileline) - comaposition5 - 1)
                    DEFSTR nb = MID$(fileline , 1 , comaposition - 1)
                    DEFSTR utn = Format$("%.8f" , VAL(ut) + (VAL(dstf) * 60) * VAL(nb))
                    ft = VARPTR$(unix_time_to_date(VARPTR(utn)))
                    year = MID$(ft , 21 , 4)
                    month = MID$(ft , 5 , 3)
                    day = MID$(ft , 9 , 2)
                    hour = MID$(ft , 12 , 2)
                    minute = MID$(ft , 15 , 2)
                    ft = year + "-" + strtomonth(month) + "-" + day + "," + hour + ":" + minute
                    fileline = ft + "," + openstr + "," + highstr + "," + lowstr + "," + closestr + "," + volumestr
                END IF

            END IF
            IF LEFT$(fileline , 8) <> "TIMEZONE" THEN filestream2.WriteLine(fileline) 'filestr=filestr+fileline+chr$(10)

        END IF
        DOEVENTS
    WEND

    IF googlerealtimecheckbox.Checked = 1 THEN
        DEFINT currt = VAL(VARPTR$(current_time()))
        IF currt - VAL(dstf) * 60 <= VAL(utn) + 60 * (VAL(dstf) - 1) + 59 AND currt > VAL(utn) + 60 * (VAL(dstf) - 1) + 59 THEN
            'if val(minute)<val(mid$(time$,4,2)) then
            DEFSTR nextutn = STR$(VAL(utn) + VAL(dstf) * 60)
            DEFSTR nextutn2 = Format$("%.8f" , VAL(nextutn))
            DEFSTR nextft = VARPTR$(unix_time_to_date(VARPTR(nextutn2)))
            DEFSTR nextyear = MID$(nextft , 21 , 4)
            DEFSTR nextmonth = MID$(nextft , 5 , 3)
            DEFSTR nextday = MID$(nextft , 9 , 2)
            DEFSTR nexthour = MID$(nextft , 12 , 2)
            DEFSTR nextminute = MID$(nextft , 15 , 2)
            nextft = nextyear + "-" + strtomonth(nextmonth) + "-" + nextday + "," + nexthour + ":" + nextminute
            DEFSTR nextfileline = nextft + "," + closestr + "," + closestr + "," + closestr + "," + closestr + "," + "0"

            filestream2.WriteLine(nextfileline)
        END IF
        IF currt - VAL(dstf) * 60 > VAL(utn) + 60 * (VAL(dstf) - 1) + 59 THEN
            googlerealtimecheckbox.Checked = 0
            SHOWMESSAGE "US market closed"
            clock.Visible = 0
            timclock.Enabled = 0
        END IF
    END IF

    filestream.Close
    filestream2.Close

    IF googlerealtimecheckbox.Checked = 1 THEN
        IF currt - VAL(dstf) * 60 <= VAL(utn) + 60 * (VAL(dstf) - 1) + 59 AND currt > VAL(utn) + 60 * (VAL(dstf) - 1) + 59 THEN
            'if val(minute)<val(mid$(time$,4,2)) then
            'defdbl quotenexttimestamp1=val(nextutn)
            'quotenexttimestamp1=timeminute(quotenexttimestamp1)
            'defdbl quotenexttimestamp2=quotenexttimestamp1/val(dstf)
            'quotenexttimestamp2=(floor(quotenexttimestamp2)+1)*val(dstf)
            'quotenexttimestamp2=quotenexttimestamp2-quotenexttimestamp1
            'quotenexttimestamp=quotenexttimestamp2*60+(val(utn)+60)
            quotenexttimestamp = VAL(nextutn) + 60 * VAL(dstf)
        ELSE
            'quotenexttimestamp1=val(utn)
            'quotenexttimestamp1=timeminute(quotenexttimestamp1)
            'quotenexttimestamp2=quotenexttimestamp1/val(dstf)
            'quotenexttimestamp2=(floor(quotenexttimestamp2)+1)*val(dstf)
            'quotenexttimestamp2=quotenexttimestamp2-quotenexttimestamp1
            'quotenexttimestamp=quotenexttimestamp2*60+val(utn)
            quotenexttimestamp = VAL(utn) + 60 * VAL(dstf)
        END IF
    END IF

    'print utn
    'print str$(quotenexttimestamp)

    filestream.Open("c:\qchartist\csv\" + UCASE$(dssymboledit.Text) + dstf + ".csv" , 0)
    IF VAL(barsdisplayed.Text) > filestream.LineCount AND filestream.LineCount > 0 THEN barsdisplayed.Text = STR$(filestream.LineCount)
    IF filestream.LineCount = 0 THEN
        IF googlerealtimecheckbox.Checked = 1 THEN
            filestream.Close
            'googlereadlastquotetimestamp=val(varptr$(current_time()))
            firstfilevol = 1
            googlegetquotesub
            PRINT "no data"
            EXIT SUB
        END IF
    END IF
    filestream.Close

    IF googlerealtimecheckbox.Checked = 0 THEN
        importfileauto2("c:\qchartist\csv\" + UCASE$(dssymboledit.Text) + dstf + ".csv")
    ELSE

        importfile1m("c:\qchartist\csv\" + UCASE$(dssymboledit.Text) + dstf + ".csv")


        IF dssource.ItemIndex = 2 THEN

            filestream.Open("c:\qchartist\csv\google\Google_quotes2.txt" , 0)
            filestr = ""
            WHILE NOT filestream.eof
                filestr = filestr + filestream.ReadLine
                DOEVENTS
            WEND
            filestream.Close
            IF like(filestr , "*EXCHANGE*NASDAQ*") = 1 THEN
                'showmessage "realtime"
            END IF
            IF like(filestr , "*a*") = 0 THEN
                PRINT "Invalid symbol"
                dsok.Enabled = 1
                'googlerealtimebusytimer.enabled=0
                EXIT SUB
            END IF


            outFileName = UCASE$(dssymboledit.Text) + dstfreal + ".csv"
            lineloop = 0

            filestream.Open("c:\qchartist\csv\google\Google_quotes2.txt" , 0)
            'dim filestream2 as qfilestream
            filestream2.Open("c:\qchartist\csv\" + outFileName , fmCreate)
            filestr = ""
            fileline = ""

            WHILE NOT filestream.eof

                fileline = filestream.ReadLine
                lineloop ++

                IF lineloop > 7 THEN


                    IF MID$(fileline , 1 , 1) = "a" THEN
                        comaposition = INSTR(fileline , ",")
                        comaposition2 = INSTR(comaposition + 1 , fileline , ",")
                        comaposition3 = INSTR(comaposition2 + 1 , fileline , ",")
                        comaposition4 = INSTR(comaposition3 + 1 , fileline , ",")
                        comaposition5 = INSTR(comaposition4 + 1 , fileline , ",")
                        closestr = MID$(fileline , comaposition + 1 , comaposition2 - comaposition - 1)
                        highstr = MID$(fileline , comaposition2 + 1 , comaposition3 - comaposition2 - 1)
                        lowstr = MID$(fileline , comaposition3 + 1 , comaposition4 - comaposition3 - 1)
                        openstr = MID$(fileline , comaposition4 + 1 , comaposition5 - comaposition4 - 1)
                        volumestr = MID$(fileline , comaposition5 + 1 , LEN(fileline) - comaposition5 - 1)
                        ut = MID$(fileline , 2 , comaposition - 2)
                        utn=ut
                        ft = VARPTR$(unix_time_to_date(VARPTR(ut)))
                        'defstr year,month,day,hour,minute
                        year = MID$(ft , 21 , 4)
                        month = MID$(ft , 5 , 3)
                        day = MID$(ft , 9 , 2)
                        hour = MID$(ft , 12 , 2)
                        minute = MID$(ft , 15 , 2)
                        ft = year + "-" + strtomonth(month) + "-" + day + "," + hour + ":" + minute
                        fileline = ft + "," + openstr + "," + highstr + "," + lowstr + "," + closestr + "," + volumestr

                    ELSE
                        IF LEFT$(fileline , 8) <> "TIMEZONE" THEN
                            comaposition = INSTR(fileline , ",")
                            comaposition2 = INSTR(comaposition + 1 , fileline , ",")
                            comaposition3 = INSTR(comaposition2 + 1 , fileline , ",")
                            comaposition4 = INSTR(comaposition3 + 1 , fileline , ",")
                            comaposition5 = INSTR(comaposition4 + 1 , fileline , ",")
                            closestr = MID$(fileline , comaposition + 1 , comaposition2 - comaposition - 1)
                            highstr = MID$(fileline , comaposition2 + 1 , comaposition3 - comaposition2 - 1)
                            lowstr = MID$(fileline , comaposition3 + 1 , comaposition4 - comaposition3 - 1)
                            openstr = MID$(fileline , comaposition4 + 1 , comaposition5 - comaposition4 - 1)
                            volumestr = MID$(fileline , comaposition5 + 1 , LEN(fileline) - comaposition5 - 1)
                            nb = MID$(fileline , 1 , comaposition - 1)
                            utn = Format$("%.8f" , VAL(ut) + (VAL(dstfreal) * 60) * VAL(nb))
                            ft = VARPTR$(unix_time_to_date(VARPTR(utn)))
                            year = MID$(ft , 21 , 4)
                            month = MID$(ft , 5 , 3)
                            day = MID$(ft , 9 , 2)
                            hour = MID$(ft , 12 , 2)
                            minute = MID$(ft , 15 , 2)
                            ft = year + "-" + strtomonth(month) + "-" + day + "," + hour + ":" + minute
                            fileline = ft + "," + openstr + "," + highstr + "," + lowstr + "," + closestr + "," + volumestr
                        END IF

                    END IF
                    IF LEFT$(fileline , 8) <> "TIMEZONE" THEN filestream2.WriteLine(fileline) 'filestr=filestr+fileline+chr$(10)

                END IF
                DOEVENTS
            WEND


            currt = VAL(VARPTR$(current_time()))
            IF currt - VAL(dstfreal) * 60 <= VAL(utn) + 60 * (VAL(dstfreal) - 1) + 59 AND currt > VAL(utn) + 60 * (VAL(dstfreal) - 1) + 59 THEN
                'if val(minute)<val(mid$(time$,4,2)) then
                nextutn = STR$(VAL(utn) + VAL(dstfreal) * 60)
                nextutn2 = Format$("%.8f" , VAL(nextutn))
                nextft = VARPTR$(unix_time_to_date(VARPTR(nextutn2)))
                nextyear = MID$(nextft , 21 , 4)
                nextmonth = MID$(nextft , 5 , 3)
                nextday = MID$(nextft , 9 , 2)
                nexthour = MID$(nextft , 12 , 2)
                nextminute = MID$(nextft , 15 , 2)
                nextft = nextyear + "-" + strtomonth(nextmonth) + "-" + nextday + "," + nexthour + ":" + nextminute
                nextfileline = nextft + "," + closestr + "," + closestr + "," + closestr + "," + closestr + "," + "0"

                filestream2.WriteLine(nextfileline)
            END IF


            filestream.Close
            filestream2.Close

        END IF


        IF dssource.ItemIndex = 0 THEN

            outFileName = UCASE$(dssymboledit.Text) + dstfreal + ".csv"
            
            
            dim yhooarrtmp(0 TO 100000) as string
            DIM file AS QFILESTREAM,yincr as integer
            file.open("c:\qchartist\csv\" + outFileName , 0)
            yincr=-1
            DO
                yincr++
                yhooarrtmp(yincr) = file.ReadLine
            LOOP UNTIL file.eof
            file.close
     
            file.open("c:\qchartist\csv\" + outFileName , 65535)
            dim yincr2 as integer
            defstr linetmp
            defint linetmploc
            for yincr2=yincr to 1 step -1
                linetmp=mid$(yhooarrtmp(yincr2),1,11)+"00:00,"+mid$(yhooarrtmp(yincr2),12,len(yhooarrtmp(yincr2)))
                linetmp=mid$(linetmp,1,rinstr(linetmp,",")-1)
                file.writeline(linetmp)
            next yincr2
            file.close
            
            
            lineloop = 0

            filestream2.Open("c:\qchartist\csv\" + outFileName , 0)
            filestr = ""
            fileline = ""

            WHILE NOT filestream2.eof

                lineloop ++
                
                filestr=filestream2.ReadLine

                IF lineloop = filestream2.LineCount THEN

                    'filestr = filestream2.ReadLine

                    DEFSTR year0 , month0 , day0 , hours0 , minutes0
                    year0 = MID$(filestr , 1 , 4)
                    month0 = MID$(filestr , 6 , 2)
                    day0 = MID$(filestr , 9 , 2)
                    hours0 = MID$(filestr , 12 , 2)
                    minutes0 = MID$(filestr , 15 , 2)

                    DEFDBL myunixtime
                    DEFSTR myunixtimestr


                    DEFSTR $mydate = year0 + ";" + month0 + ";" + day0 + ";" + hours0 + ";" + minutes0 + ";" + "00"

                    cpptmpfuncreturn = VARPTR$(date_to_unix_time(VARPTR($mydate)))
                    utn = VAL(cpptmpfuncreturn)

                END IF
                DOEVENTS
            WEND
            filestream2.Close

            currt = VAL(VARPTR$(current_time()))
            IF currt - VAL(dstfreal) * 60 <= VAL(utn) + 60 * (VAL(dstfreal) - 1) + 59 AND currt > VAL(utn) + 60 * (VAL(dstfreal) - 1) + 59 THEN
                'if val(minute)<val(mid$(time$,4,2)) then
                nextutn = STR$(VAL(utn) + VAL(dstfreal) * 60)
                nextutn2 = Format$("%.8f" , VAL(nextutn))
                nextft = VARPTR$(unix_time_to_date(VARPTR(nextutn2)))
                nextyear = MID$(nextft , 21 , 4)
                nextmonth = MID$(nextft , 5 , 3)
                nextday = MID$(nextft , 9 , 2)
                nexthour = MID$(nextft , 12 , 2)
                nextminute = MID$(nextft , 15 , 2)
                nextft = nextyear + "-" + strtomonth(nextmonth) + "-" + nextday + "," + nexthour + ":" + nextminute
                nextfileline = nextft + "," + closestr + "," + closestr + "," + closestr + "," + closestr + "," + "0"

                filestream2.Open("c:\qchartist\csv\" + outFileName , 2)
                filestream2.position=filestream2.size
                filestream2.WriteLine(nextfileline)
                filestream2.Close
            END IF

        END IF


        'firstfilevol = 1


        IF googlerealtimecheckbox.Checked = 1 THEN
            IF currt - VAL(dstfreal) * 60 <= VAL(utn) + 60 * (VAL(dstfreal) - 1) + 59 AND currt > VAL(utn) + 60 * (VAL(dstfreal) - 1) + 59 THEN

                quotenexttimestamp = VAL(nextutn) + 60 * VAL(dstfreal)
            ELSE

                quotenexttimestamp = VAL(utn) + 60 * VAL(dstfreal)
            END IF
        END IF


        importfileauto2("c:\qchartist\csv\" + UCASE$(dssymboledit.Text) + dstfreal + ".csv")

        DEFINT i
        DEFINT j
        FOR i = 0 TO chartbars(displayedfile) - 1
            if VAL(dstfreal)<1440 then
            IF date1(i) = Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)) AND time1(i) = Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile)) THEN
                j = i
                EXIT FOR
            END IF
            end if
            if VAL(dstfreal)=1440 then
            IF date1(i) = Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)) AND time1(i) = "14:30" THEN
                j = i
                EXIT FOR
            END IF
            end if
        NEXT i
        DEFDBL lasthigh , lastlow
        defint volumacc=0
        lasthigh = high1(j)
        lastlow = low1(j)
        FOR i = j TO 0 STEP - 1
            IF high1(i) > lasthigh THEN lasthigh = high1(i)
            IF low1(i) < lastlow THEN lastlow = low1(i)
            volumacc=volumacc+volume1(i)
        NEXT i
        Grid.Cell(rowgridoffset + 4 , chartbars(displayedfile)) = STR$(lasthigh)
        Grid.Cell(rowgridoffset + 5 , chartbars(displayedfile)) = STR$(lastlow)
        Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile)) = STR$(close1(0))
        Grid.Cell(rowgridoffset + 7 , chartbars(displayedfile)) = STR$(volumacc)
    END IF
    
    defint k
    ' getting volume since the opening of the day
    FOR i = 0 TO 999 'chartbars(displayedfile) - 1
            IF date1(i+1)<>date1(i) THEN
                k=i
                EXIT FOR
            END IF
    NEXT i
    volumacc=0
    for i=k to j+1 step -1
        volumacc=volumacc+volume1(i)
    next i
    filevoltmp=volumacc
    

    'if googlerealtimebusytimer.enabled=1 then
    'importfileauto("c:\qchartist\csv\"+UCASE$(dssymboledit.Text) + dstf + ".csv")
    'reimportfile()
    'end if

    exportfilename
    btnOnClick(drwBox)

    clock.Visible = 0
    timclock.Enabled = 0

    IF googlerealtimecheckbox.Checked = 0 THEN
        dsok.Enabled = 1
    ELSE
        googlebusytimer.Interval = 1000
        '-----------------------------------------------------------------
        busystream.Open("c:\qchartist\perl\scripts\isbusy.txt" , fmCreate)
        busystream.WriteLine("1")
        busystream.Close

        DEFSTR tmpdir = CurDir$
        CHDIR "c:\qchartist\perl\scripts"

        DIM pid AS INTEGER
        IF like(platform , "*Wine*") = 0 THEN pid = SHELL("getstockvol.bat usa " + UCASE$(dssymboledit.Text) , 0)
        IF like(platform , "*Wine*") = 1 THEN pid = SHELL("/bin/sh -c " + CHR$(34) + "./getstockvol.sh usa " + UCASE$(dssymboledit.Text) + CHR$(34) , 0)
        CHDIR tmpdir
        '----------------------------------------------------------------
        googlegoingto = "googlereadlastquote"  ':googlebusytimer.enabled=1
        googlereadlastquotetimer.Enabled = 1
        'googlereadlastquotetimestamp=val(varptr$(current_time())):googlerealtimebusytimer.enabled=1
    END IF
    GOTO endlabel

    endlabel :

END SUB


SUB googlereadlastquoteontimersub

    
IF googlerealtimecheckbox.Checked = 0 THEN
            'googlerealtimebusytimer.enabled=0
            googlereadlastquotetimer.Enabled = 0
            dsok.Enabled = 1
            exit sub
    END IF

DIM googlebusystream AS QFILESTREAM
    googlebusystream.Open("c:\qchartist\perl\scripts\isbusy.txt" , 0)
    DEFSTR isbusy = ""
    WHILE NOT googlebusystream.eof
        isbusy = isbusy + googlebusystream.ReadLine
    WEND
    googlebusystream.Close

    'if val(isbusy)=1 then exit sub

    'googlereadlastquotetimestamp=val(varptr$(current_time()))

    DIM filestream AS QFILESTREAM
    filestream.Open("c:\qchartist\perl\scripts\quote.txt" , 0)
    DEFSTR filestr = ""
    WHILE NOT filestream.eof
        filestr = filestr + filestream.ReadLine
    WEND
    filestream.Close

    DEFSTR filestr2 = filestr
    filestr = MID$(filestr , 1 , INSTR(filestr , ",") - 1)

    IF VAL(filestr) > 0 THEN
        filevol = VAL(MID$(filestr2 , INSTR(filestr2 , ",") + 1 , LEN(filestr2)))
    ELSE
        filevol = VAL(Grid.Cell(rowgridoffset + 7 , chartbars(displayedfile))) + filevoltmp
    END IF
    IF firstfilevol = 1 THEN
        firstfilevol = 0
        filevoltmp = filevol
    END IF
    DEFINT volum = filevol - filevoltmp

    'check if connection exists
    IF VAL(filestr) > 0 THEN
        'ok
    ELSE
        'print "Can't get quote, retrying next time"

        'googlerealtimecheckbox.checked=0
        'dsok.enabled=1
        'googlerealtimebusytimer.enabled=0

        'googlereadlastquotetimestamp=val(varptr$(current_time()))
        'firstfilevol=1
        'googlegetquotesub
        'exit sub

        filestr = Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile))

    END IF

    DEFINT googlecurrenttimestamptmp = googlecurrenttimestamp
    googlecurrenttimestamp = VAL(VARPTR$(current_time())) 'val(Format$("%.8f",varptr$(current_time())))
    IF googlecurrenttimestamp - googlecurrenttimestamptmp > 30 THEN
        PRINT "Connection lagging"
        'googlerealtimecheckbox.checked=0
        'dsok.enabled=1
        'googlerealtimebusytimer.enabled=0

        'googlereadlastquotetimestamp=val(varptr$(current_time()))
        'firstfilevol=1
        'googlegetquotesub
        'exit sub
    END IF

    DEFSTR dstf
    SELECT CASE dstimeframe.ItemIndex
        CASE 0  :
            dstf = "1"
        CASE 1  :
            dstf = "5"
        CASE 2  :
            dstf = "15"
        CASE 3  :
            dstf = "30"
        CASE 4  :
            dstf = "60"
        CASE 5  :
            dstf = "240"
        CASE 6  :
            dstf = "1440"
        CASE 7  :
            dstf = "10080"
        CASE 8  :
            dstf = "43200"
    END SELECT

    DEFSTR outFileName = UCASE$(dssymboledit.Text) + dstf + ".csv"

    'print str$(googlecurrenttimestamp)+" "+str$(quotenexttimestamp)

    IF googlecurrenttimestamp < quotenexttimestamp THEN

        IF VAL(filestr) > VAL(Grid.Cell(rowgridoffset + 4 , chartbars(displayedfile))) THEN Grid.Cell(rowgridoffset + 4 , chartbars(displayedfile)) = filestr
        IF VAL(filestr) < VAL(Grid.Cell(rowgridoffset + 5 , chartbars(displayedfile))) THEN Grid.Cell(rowgridoffset + 5 , chartbars(displayedfile)) = filestr
        Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile)) = filestr
        Grid.Cell(rowgridoffset + 7 , chartbars(displayedfile)) = STR$(volum)

        exportfilename
        btnOnClick(drwBox)

        IF googlerealtimecheckbox.Checked = 0 THEN
            'googlerealtimebusytimer.enabled=0
            googlereadlastquotetimer.Enabled = 0
            dsok.Enabled = 1
        ELSE

            googlebusytimer.Interval = 1000
            '-----------------------------------------
            IF VAL(isbusy) = 0 THEN
                busystream.Open("c:\qchartist\perl\scripts\isbusy.txt" , fmCreate)
                busystream.WriteLine("1")
                busystream.Close


                DEFSTR tmpdir = CurDir$
                CHDIR "c:\qchartist\perl\scripts"


                IF like(platform , "*Wine*") = 0 THEN pid = SHELL("getstockvol.bat usa " + UCASE$(dssymboledit.Text) , 0)
                IF like(platform , "*Wine*") = 1 THEN pid = SHELL("/bin/sh -c " + CHR$(34) + "./getstockvol.sh usa " + UCASE$(dssymboledit.Text) + CHR$(34) , 0)

                CHDIR tmpdir
            END IF
            '------------------------------------------------
            googlegoingto = "googlereadlastquote"  ':googlebusytimer.enabled=1

        END IF

    END IF

    IF googlecurrenttimestamp >= quotenexttimestamp THEN

        'if googlerealtimecheckbox.checked=1 then
        'googlereadlastquotetimestamp=val(varptr$(current_time()))
        'firstfilevol=1
        'googlegetquotesub
        'exit sub
        'end if

        DEFSTR nextutn = STR$(quotenexttimestamp)
        DEFSTR nextutn2 = Format$("%.8f" , VAL(nextutn))
        DEFSTR nextft = VARPTR$(unix_time_to_date(VARPTR(nextutn2)))
        DEFSTR nextyear = MID$(nextft , 21 , 4)
        DEFSTR nextmonth = MID$(nextft , 5 , 3)
        DEFSTR nextday = MID$(nextft , 9 , 2)
        DEFSTR nexthour = MID$(nextft , 12 , 2)
        DEFSTR nextminute = MID$(nextft , 15 , 2)

        quotenexttimestamp = quotenexttimestamp + 60 * VAL(dstf)

        Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile) + 1) = nextyear + "-" + strtomonth(nextmonth) + "-" + nextday
        Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile) + 1) = nexthour + ":" + nextminute
        Grid.Cell(rowgridoffset + 3 , chartbars(displayedfile) + 1) = filestr
        Grid.Cell(rowgridoffset + 4 , chartbars(displayedfile) + 1) = filestr
        Grid.Cell(rowgridoffset + 5 , chartbars(displayedfile) + 1) = filestr
        Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile) + 1) = filestr
        Grid.Cell(rowgridoffset + 7 , chartbars(displayedfile) + 1) = "0"
        
        firstfilevol = 1

        chartbars(displayedfile) = chartbars(displayedfile) + 1
        chartbarsdisplayedfilestr = STR$(chartbars(displayedfile))  : displayedfilestr = STR$(displayedfile)  : cpptmpfuncreturn = VARPTR$(setchartbars(VARPTR(chartbarsdisplayedfilestr) , VARPTR(displayedfilestr)))

        exportfilename

        Scrollchart.Max = chartbars(displayedfile)
        IF Scrollchart.Position = chartbars(displayedfile) - 1 THEN Scrollchart.Position = chartbars(displayedfile)
        chartstart = Scrollchart.Position - numbars

        btnOnClick(drwBox)

        IF googlerealtimecheckbox.Checked = 0 THEN
            'googlerealtimebusytimer.enabled=0
            googlereadlastquotetimer.Enabled = 0
            dsok.Enabled = 1
        ELSE
            googlebusytimer.Interval = 1000
            '-----------------------------------------
            IF VAL(isbusy) = 0 THEN
                busystream.Open("c:\qchartist\perl\scripts\isbusy.txt" , fmCreate)
                busystream.WriteLine("1")
                busystream.Close


                tmpdir = CurDir$
                CHDIR "c:\qchartist\perl\scripts"


                IF like(platform , "*Wine*") = 0 THEN pid = SHELL("getstockvol.bat usa " + UCASE$(dssymboledit.Text) , 0)
                IF like(platform , "*Wine*") = 1 THEN pid = SHELL("/bin/sh -c " + CHR$(34) + "./getstockvol.sh usa " + UCASE$(dssymboledit.Text) + CHR$(34) , 0)

                CHDIR tmpdir
            END IF
            '------------------------------------------------
            'filevoltmp = filevol
            googlegoingto = "googlereadlastquote"  ':googlebusytimer.enabled=1
        END IF

    END IF
    

END SUB

'sub googlerealtimebusytimersub
'
'if googlereadlastquotetimestamp<val(varptr$(current_time()))-10 then 'googlecurrenttimestamp<val(varptr$(current_time()))-40 then
'   
'    if googlerealtimecheckbox.checked=1 then
'        'googlereadlastquotetimestamp=val(varptr$(current_time()))
'        'googlegetquotesub
'
'    else
'        
'        'googlerealtimecheckbox.checked=0
'        'dsok.enabled=1
'        'googlerealtimebusytimer.enabled=0
'        'exit sub
'    
'    end if
'    
'end if

'end sub

function timeminute(seconds as double) as double

defdbl inhours=seconds/60/60
defdbl minutes=(inhours-floor(inhours))*60
result=minutes

end function

function timehour(seconds as double) as double

defdbl indays=seconds/60/60/24
defdbl hours=(indays-floor(indays))*24
result=hours
      
end function

function timedayofweek(seconds as double) as double

defstr mydate
defstr secondsstr=seconds
mydate=varptr$(unix_time_to_date(varptr(secondsstr)))
defstr datestr=mid$(mydate,1,3)          

if datestr="Mon" then result= 1
if datestr="Tue" then result= 2
if datestr="Wed" then result= 3
if datestr="Thu" then result= 4
if datestr="Fri" then result= 5
if datestr="Sat" then result= 6
if datestr="Sun" then result= 0

end sub

sub websitesub  

ShellExecute 0, "open", "http://www.qchartist.net", "", "", 1

end sub

sub loginsub
loginform.visible=1
end sub

sub googlerefreshrateeditchangesub
googlereadlastquotetimer.interval=val(googlerefreshrateedit.text)
end sub

sub loadsymbolslistsub
symbolslistbox.clear
dim filestream as qfilestream
filestream.Open("c:\qchartist\qsymbols\"+markettypecombo.item(markettypecombo.itemindex)+".txt" , 0)
defstr filestr = ""
WHILE NOT filestream.eof
    filestr = filestream.ReadLine
    symbolslistbox.additems mid$(filestr,1,instr(filestr,",")-1)+" | "+mid$(filestr,instr(filestr,",")+1,len(filestr))
WEND
filestream.Close 
end sub

sub markettypecombochangesub
loadsymbolslistsub
end sub

sub searchsymbolslistbtnsub
defint i
defstr searchsymbolsliststr="*"+searchsymbolslistedit.text+"*"
for i=0 to symbolslistbox.itemcount-1
if like(lcase$(symbolslistbox.item(i)),lcase$(searchsymbolsliststr))=1 then
symbolslistbox.itemindex=i
exit for
end if
doevents
next i
end sub

sub searchnextsymbolslistbtnsub
defint i
defstr searchsymbolsliststr="*"+searchsymbolslistedit.text+"*"
for i=symbolslistbox.itemindex+1 to symbolslistbox.itemcount-1
if like(lcase$(symbolslistbox.item(i)),lcase$(searchsymbolsliststr))=1 then
symbolslistbox.itemindex=i
exit for
end if
doevents
next i
end sub

sub updatesymbolslistbtnsub
run "c:\qchartist\qsymbols\qsymbols.exe"
end sub

sub reloadsymbolslistbtnsub
loadsymbolslistsub
end sub

sub restoredefaultdatabtnsub
IF MessageDlg("Restoring default data will overwrite current data. Are you sure?", mtWarning, mbYes OR mbNo, 0) = mrYes THEN
    defint pid
    pid=shell("c:\qchartist\qsymbols\restore_default_data.bat",0)
END IF
end sub

sub selectsymbolslistbtnsub
dssymboledit.text=mid$(symbolslistbox.item(symbolslistbox.itemindex),1,instr(symbolslistbox.item(symbolslistbox.itemindex)," |")-1)
if markettypecombo.item(markettypecombo.itemindex)="AMEX" or markettypecombo.item(markettypecombo.itemindex)="NASDAQ" then
dssource.itemindex=0
else
dssource.itemindex=1
end if
datasourcefrm.visible=1
setfocus(datasourcefrm.handle)
end sub

sub loadsymbolslistbtnsub
dssymboledit.text=mid$(symbolslistbox.item(symbolslistbox.itemindex),1,instr(symbolslistbox.item(symbolslistbox.itemindex)," |")-1)
if markettypecombo.item(markettypecombo.itemindex)="AMEX" or markettypecombo.item(markettypecombo.itemindex)="NASDAQ" then
dssource.itemindex=0
else
dssource.itemindex=1
end if
if dsok.enabled=1 then
barsdisplayed.text="333"
dsokclick
end if
end sub

sub showsymbolslist
symbolslistform.visible=1
setfocus(symbolslistform.handle)
end sub

sub symbolslistboxonclicksub
dssymboledit.text=mid$(symbolslistbox.item(symbolslistbox.itemindex),1,instr(symbolslistbox.item(symbolslistbox.itemindex)," |")-1)
if markettypecombo.item(markettypecombo.itemindex)="AMEX" or markettypecombo.item(markettypecombo.itemindex)="NASDAQ" then
dssource.itemindex=0
else
dssource.itemindex=1
end if
end sub

sub symbolslistboxondblclicksub
loadsymbolslistbtnsub
end sub

sub enablegetchartbtnsub
getcharttimer.enabled=0
dsok.enabled=1
if useindiCheckedtmp=1 then useindi.checked=1
end sub
