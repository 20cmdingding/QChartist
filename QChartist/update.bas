'QChartist charting software source code
'Copyright 2010-2014 Julien Moog - All rights reserved
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

'Compiler Directrapidqives
$APPTYPE console
$OPTIMIZE on
$TYPECHECK on

$INCLUDE "includes\RAPIDQ2.INC"

declare sub upgrade
declare sub abortsub
declare sub upgradetimersub

DECLARE FUNCTION FGetFileHTTP_URLDownloadToFile LIB "urlmon" ALIAS "URLDownloadToFileA" _
    (ByVal pCaller AS LONG , ByRef szURL AS STRING , ByRef szFileName AS STRING , _
    ByVal dwReserved AS LONG , ByVal lpfnCB AS LONG) AS LONG
    
declare FUNCTION GetFileHTTP(URL AS STRING , toFile AS STRING) AS LONG

Declare Function timeGetTime Lib "winmm.dll" Alias "timeGetTime" () As Long

CHDIR "C:\QChartist"

if curdir$<>"C:\QChartist" then
showmessage "QChartist won't function properly, please install it in directory C:\QChartist"
end if

dim versfile as qfilestream
versfile.open (curdir$+"\build.txt",0)
defstr QC_build=versfile.readline
versfile.close

defint abortvar=0

defstr homepath=curdir$

dim timerupgrade as qtimer
timerupgrade.interval=1
timerupgrade.ontimer=upgrade
timerupgrade.enabled=0

create form as qform
height=150
width=300
center
caption="Update"
onshow=upgradetimersub
CREATE Gauge AS QGauge
top=0
left=0
height=20
width=form.width-20
    Position = 0
    Kind = gkhorizontalbar
    visible=0
  END CREATE
  create abordbtn as qbutton
  top=20
  left=0
  caption="Abort"
  onclick=abortsub
  visible=0
  end create
  create operationlab as qlabel
  top=50
  left=0
  width=form.width-20
  visible=0
  end create
end create

form.showmodal
    
FUNCTION GetFileHTTP(URL AS STRING , toFile AS STRING) AS LONG
    DEFSTR sURL , sToFile
    sURL = URL
    sToFile = toFile
    GetFileHTTP = FGetFileHTTP_URLDownloadToFile(0 , sURL , sToFile , 0 , 0)
END FUNCTION

sub upgrade
timerupgrade.enabled=0
IF MessageDlg("Proceed upgrade?"+chr$(10)+"Important: if you did modify the sources codes, upgrading will overwrite your own modifications!", mtConfirmation, mbYes OR mbNo, 0) = mrYes THEN
operationlab.caption="Downloading builds info..."
'-- Upgrade
defint pid
    defstr url = "http://www.qchartist.net/updates/builds.txt?"+STR$(timeGetTime)

    'DEFSTR outFileName = "readme.txt"
    defstr outFileName = "builds.txt"

    CHDIR homepath + "\updates"

    IF GetFileHTTP(url , outFileName) THEN
        SHOWMESSAGE "Download Error : " & url
        operationlab.caption="Download error"
        EXIT SUB
    ELSE
        'SHOWMESSAGE "Download Finished & OK : " & URL
        operationlab.caption="Download done"
    END IF

dim versionsfile as qfilestream
defstr versionsline
dim dlversion() as string
defint iv=0
defint buildsnb=0

operationlab.caption="Counting builds..."

versionsfile.open(homepath + "\updates\builds.txt",fmopenread)
do
versionsline=versionsfile.readline
if val(versionsline)>val(QC_build) then
buildsnb++
end if
loop until versionsfile.eof
versionsfile.close

versionsfile.open(homepath + "\updates\builds.txt",fmopenread)
do
versionsline=versionsfile.readline
if val(versionsline)>val(QC_build) then
iv++
dlversion(iv)="QChartist_build_"+versionsline+".rar"
end if
loop until versionsfile.eof
versionsfile.close

defint ivl

dim longcmdfile as qfilestream
CHDIR homepath + "\updates"
longcmdfile.open ("update.bat",65535)

'defstr longcmd="cmd.exe /c echo."

for ivl=1 to iv

if fileexists(homepath + "\updates\" + dlversion(ivl)) then
    kill homepath + "\updates\" + dlversion(ivl)
end if

operationlab.caption="Downloading "+dlversion(ivl)+", please wait..."
url = "http://www.qchartist.net/updates/"+dlversion(ivl)'+"?"+STR$(timeGetTime)

    'DEFSTR outFileName = "readme.txt"
'    outFileName = dlversion(ivl)

    

'    IF GetFileHTTP(url , outFileName) THEN
'        SHOWMESSAGE "Download Error : " & url
'        operationlab.caption="Download error"
'        EXIT SUB
'    ELSE
'        'SHOWMESSAGE "Download Finished & OK : " & URL
'        operationlab.caption="Download done"
'    END IF
longcmdfile.writeline ("wget.exe "+url)
longcmdfile.writeline ("unrar.exe x "+dlversion(ivl)+" C:\QChartist\ -y -o+ -ierr")

'longcmd=longcmd+" && "+"wget.exe "+url+" && unrar.exe x "+dlversion(ivl)+" C:\QChartist\ -y -o+ -ierr"
'pid=shell ("cmd.exe /c wget.exe "+url+" && unrar.exe x "+dlversion(ivl)+" C:\QChartist\ -y -o+ -ierr",1)

gauge.position=100*ivl/buildsnb

if abortvar=1 then
exit for
end if

next ivl
longcmdfile.writeline ("echo Upgrade done, please close this update and run QChartist.bat")
longcmdfile.close

pid=shell ("cmd.exe /c update.bat",1)

'showmessage "Once the upgrade is done in the console, please close update and run QChartist.bat"

else

application.terminate

end if

end sub

sub abortsub

abortvar=1

end sub

sub upgradetimersub

timerupgrade.enabled=1

end sub