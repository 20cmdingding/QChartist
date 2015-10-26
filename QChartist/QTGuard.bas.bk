'QChartist charting software source code
'Copyright 2010-2014 Julien Moog - All rights reserved
'contact email: julien.moog@laposte.net

'Compiler Directrapidqives
''pre cmd FBVERSION=017 FBLANG=deprecated norun enc noopt exe nocon NoDone icon QTGuard.ico kill
''pre end
$APPTYPE GUI
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

DIM ini AS QINI
ini.FileName = homepath + "\QChartist.ini"

DECLARE FUNCTION timeGetTime LIB "winmm.dll" ALIAS "timeGetTime"() AS LONG
DECLARE SUB checkalive
DECLARE SUB checkalive2
DECLARE SUB playwavtimersub
DECLARE SUB changedelay
DECLARE SUB alivetimerbtnclick
DECLARE SUB autobtnclick
DECLARE SUB giveupclick
DECLARE SUB signaltypechangesub
DECLARE SUB silencesub
DECLARE SUB ButtonClick  '"Send mail" button
DECLARE SUB TimerExpired  'Check for incomming messages from server
DECLARE SUB mailformsub
DECLARE SUB smtpchange
DECLARE SUB fromchange
DECLARE SUB tochange
DECLARE SUB subjectchange
DECLARE SUB messagechange
DECLARE SUB startresetalivesub
DECLARE SUB resetalivesub
DECLARE SUB buyradioclick
DECLARE SUB sellradioclick
declare sub runoncesub

CONST DELAY = 500

DIM Timer1 AS QTIMER  'Timer for checking the socket
Timer1.Interval = DELAY
Timer1.OnTimer = TimerExpired
'and continue in sending a mail.

'DIM apprunning AS INTEGER
'apprunning = 0

DIM resetalivetimer AS QTIMER
resetalivetimer.Enabled = 0
resetalivetimer.Interval = 100
resetalivetimer.OnTimer = resetalivesub

DIM alivetimer AS QTIMER
alivetimer.Interval = 120000
alivetimer.Enabled = 0
alivetimer.OnTimer = checkalive

DIM runoncetimer AS QTIMER
runoncetimer.Interval = 5000
runoncetimer.Enabled = 0
runoncetimer.OnTimer = runoncesub

DIM alivetimer2 AS QTIMER
alivetimer2.Interval = 300000
alivetimer2.Enabled = 0
alivetimer2.OnTimer = checkalive2

DIM playwavtimer AS QTIMER
playwavtimer.Interval = 1000
playwavtimer.Enabled = 0
playwavtimer.OnTimer = playwavtimersub

DIM alivelogtmp AS STRING

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

DIM smssent AS INTEGER
smssent = 0

CREATE form AS QFORM
    Caption = "QTGuard"
    BorderStyle = 3
    CREATE checkdelaylab AS QLABEL
        Caption = "Maximum lag accepted in milliseconds:"
    END CREATE
    CREATE checkdelayedit AS QEDIT
        Top = 20
        Text = "120000"
    END CREATE
    CREATE alivetimerbtn AS QOVALBTN
        Top = 45
        Caption = "Start timer"
        OnClick = alivetimerbtnclick
        Flat = 0
    END CREATE
    CREATE autobtn AS QOVALBTN
        Top = 95
        Caption = "Start expert"
        OnClick = autobtnclick
        Flat = 0
    END CREATE
    CREATE giveupbtn AS QBUTTON
        Top = 155
        Caption = "Give up"
        OnClick = giveupclick
    END CREATE
    CREATE enablesounds AS QCHECKBOX
        Top = 185
        Caption = "Enable sounds"
        Checked = 1
    END CREATE
    CREATE alertmt4disconnections AS QCHECKBOX
        Top = 165
        Left = 100
        Width = 200
        Caption = "Alert MT4 disconnections"
        Checked = 0
    END CREATE
    CREATE mt4alivepath AS QEDIT
        Top = 185
        Left = 100
        Text = "C:\Program Files\MetaTrader 4 Oanda\experts\files\alive.log"
    END CREATE
    CREATE silence AS QBUTTON
        Top = 185
        Left = 230
        Caption = "Silence"
        OnClick = silencesub
    END CREATE
    CREATE mailfrm AS QBUTTON
        Top = 133
        Left = 230
        Caption = "Mailer"
        OnClick = mailformsub
    END CREATE
    CREATE signaltypelab AS QLABEL
        Top = 50
        Left = 130
        Caption = "Look for:"
    END CREATE
    CREATE signaltype AS QCOMBOBOX
        Top = 65
        Left = 130
        AddItems "Entry signal" , "Exit signal"
        ItemIndex = 0
        OnChange = signaltypechangesub
    END CREATE
    CREATE buyradio AS QRADIOBUTTON
        Parent = form
        Top = 90
        Left = 130
        Caption = "Buy"
        Visible = 0
        OnClick = buyradioclick
    END CREATE
    CREATE sellradio AS QRADIOBUTTON
        Parent = form
        Top = 90
        Left = 180
        Caption = "Sell"
        Visible = 0
        OnClick = sellradioclick
    END CREATE
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
        OnChange = smtpchange
    END CREATE
    CREATE Edit2 AS QEDIT
        Left = 110
        Top = 37
        Width = 380
        Height = 20
        Text = "julien.moog@laposte.net"
        OnChange = fromchange
    END CREATE
    CREATE Edit3 AS QEDIT
        Left = 110
        Top = 37 + 27
        Width = 380
        Height = 20
        Text = "julienmoog@orange.fr"
        OnChange = tochange
    END CREATE
    CREATE Edit4 AS QEDIT
        Left = 110
        Top = 71 + 27
        Width = 380
        Height = 20
        Text = "deco"
        OnChange = subjectchange
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
        Text = "deco"
        OnChange = messagechange
    END CREATE
    CREATE Label5 AS QLABEL
        Top = 98 + 5 + 27
        Left = 5
        Caption = "Message:"
    END CREATE
    CREATE enablemailer AS QCHECKBOX
        Caption = "Enable"
        Checked = 1
        Top = MailForm.Height - 50
    END CREATE
END CREATE

SUB mailformsub
    MailForm.Visible = 1
END SUB

ini.Section = "Settings"
Edit1.Text = ini.get("smtp" , "")
Edit2.Text = ini.get("from" , "")
Edit3.Text = ini.get("to" , "")

SUB startresetalivesub
    resetalivetimer.Enabled = 1
END SUB

SUB resetalivesub
    resetalivetimer.Enabled = 0
    DIM fileqtp AS QFILESTREAM

    fileqtp.Open(homepath + "\alive.log" , fmCreate)

    fileqtp.WriteLine(STR$(0))
    fileqtp.Close

END SUB

SUB smtpchange
    ini.Section = "Settings"
    ini.Write("smtp" , Edit1.Text)
END SUB

SUB fromchange
    ini.Section = "Settings"
    ini.Write("from" , Edit2.Text)
END SUB

SUB tochange
    ini.Section = "Settings"
    ini.Write("to" , Edit3.Text)
END SUB

SUB subjectchange
    'ini.Section="Settings"
    'ini.write("subject",edit4.text)
END SUB

SUB messagechange
    'ini.Section="Settings"
    'ini.write("message",textbox.text)
END SUB


SUB ButtonClick  'Begin to send the mail
    IF Button.Caption = "<<< SENDING MAIL >>>" THEN  'Abort it
        Status.Caption = "Please enter your e-mail."
        Timer1.Enabled = FALSE
        Button.Caption = "<<< Send the e-mail... >>>"
        Socket.Close(SockNum)
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
            SHOWMESSAGE "Error: " + LastLine
            Status.Caption = "Please enter your e-mail."
            Timer1.Enabled = FALSE
            Button.Caption = "<<< Send the e-mail... >>>"
            Socket.Close(SockNum)
            SockNum = 0
            Timer1.Enabled = TRUE
            MailStep = 0
        END IF
        MailStep = 1
        Socket.WriteLine(SockNum , "HELO localhost") 'Hello server!
        Timer1.Enabled = TRUE
    ELSE
        SockNum = 0
        SHOWMESSAGE "Unable to connect to: " + Edit1.Text  'Couldn't connect to
        'server
    END IF
END SUB

startresetalivesub

form.ShowModal

SUB checkalive
    DIM alivetime AS STRING
    DIM alivefile AS QFILESTREAM
    alivefile.Open(homepath + "\alive.log" , fmOpenRead)
    alivetime = alivefile.ReadLine() 'Read an entire line
    alivefile.Close
    IF timeGetTime <= VAL(alivetime) + VAL(checkdelayedit.Text) THEN
        'playwavtimer.Enabled = 0
        'apprunning = 0
    ELSE
        playwavtimer.Enabled = 1
    END IF
END SUB

SUB checkalive2

    IF alertmt4disconnections.Checked = 0 THEN
        EXIT SUB
    END IF

    IF FILEEXISTS(mt4alivepath.Text) = 0 THEN
        EXIT SUB
    END IF

    DIM alivelog AS STRING
    DIM qtnfile AS QFILESTREAM
    qtnfile.Open(mt4alivepath.Text , fmOpenRead)
    alivelog = qtnfile.ReadLine() 'Read an entire line
    qtnfile.Close

    IF VAL(alivelog) = VAL(alivelogtmp) THEN

        'IF enablesounds.Checked = 1 THEN
            PLAYWAV "" , SND_ASYNC
            PLAYWAV homepath + "\wav\disconnect.wav" , SND_ASYNC OR SND_LOOP
        'END IF

        'IF smssent = 0 THEN
            'smssent = 1
            'MailForm.Visible = 1
            'ButtonClick
        'END IF

    END IF

    alivelogtmp = alivelog

END SUB

SUB playwavtimersub
    playwavtimer.enabled=0
    IF enablesounds.Checked = 1 THEN
        PLAYWAV homepath + "\wav\fx_215.wav" , SND_ASYNC
    END IF
    IF ini.exist THEN
        ini.Section = "Settings"
        IF (VAL(ini.get("automation" , "")) > 0 OR VAL(ini.get("exitsignal" , "")) > 0) THEN
            'IF apprunning = 0 THEN
                'apprunning = 1
                RUN CHR$(34) + homepath + "\QCKill.exe" + CHR$(34)
                RUN CHR$(34) + homepath + "\sendmailKill.exe" + CHR$(34)
                RUN CHR$(34) + homepath + "\QChartist.exe" + CHR$(34)
            'END IF
        END IF
    END IF

END SUB

SUB alivetimerbtnclick
    IF alivetimerbtn.Flat = 0 THEN
        alivetimerbtn.Flat = 1
        alivetimerbtn.Caption = "Stop timer"
        alivetimer.Enabled = 1
	runoncetimer.enabled=1
        IF alertmt4disconnections.Checked = 1 THEN alivetimer2.Enabled = 1
        EXIT SUB
    END IF
    IF alivetimerbtn.Flat = 1 THEN
        alivetimerbtn.Flat = 0
        alivetimerbtn.Caption = "Start timer"
        alivetimer.Enabled = 0
        alivetimer2.Enabled = 0
        EXIT SUB
    END IF
END SUB

SUB autobtnclick
    IF autobtn.Flat = 0 THEN
        autobtn.Flat = 1
        autobtn.Caption = "Stop expert"
        ini.Section = "Settings"
        SELECT CASE signaltype.ItemIndex
            CASE 0 :
                ini.Write("automation" , "1")
            CASE 1 :
                ini.Write("exitsignal" , "1")
        END SELECT
        EXIT SUB
    END IF
    IF autobtn.Flat = 1 THEN
        autobtn.Flat = 0
        autobtn.Caption = "Start expert"
        ini.Section = "Settings"
        SELECT CASE signaltype.ItemIndex
            CASE 0 :
                ini.Write("automation" , "0")
            CASE 1 :
                ini.Write("exitsignal" , "0")
        END SELECT
        EXIT SUB
    END IF
END SUB

SUB giveupclick
    playwavtimer.Enabled = 0
END SUB

SUB signaltypechangesub
    ini.Section = "Settings"
    ini.Write("automation" , "0")
    ini.Write("exitsignal" , "0")
    alivetimerbtn.Flat = 0
    alivetimerbtn.Caption = "Start timer"
    alivetimer.Enabled = 0
    alivetimer2.Enabled = 0
    autobtn.Flat = 0
    autobtn.Caption = "Start expert"
    SELECT CASE signaltype.ItemIndex
        CASE 0 :
            buyradio.Visible = 0
            sellradio.Visible = 0
        CASE 1 :
            buyradio.Visible = 1
            sellradio.Visible = 1
    END SELECT
END SUB

SUB silencesub
    PLAYWAV "" , SND_ASYNC
END SUB

SUB buyradioclick
    ini.Write("exitsignaldir" , "1")
END SUB

SUB sellradioclick
    ini.Write("exitsignaldir" , "0")
END SUB

sub runoncesub
    runoncetimer.enabled=0
    IF enablesounds.Checked = 1 THEN
        PLAYWAV homepath + "\wav\fx_215.wav" , SND_ASYNC
    END IF
    IF ini.exist THEN
        ini.Section = "Settings"
        IF (VAL(ini.get("automation" , "")) > 0 OR VAL(ini.get("exitsignal" , "")) > 0) THEN
            'IF apprunning = 0 THEN
                'apprunning = 1                
                RUN CHR$(34) + homepath + "\QChartist.exe" + CHR$(34)
            'END IF
        END IF
    END IF
end sub

