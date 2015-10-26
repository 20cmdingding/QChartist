''pre cmd FBVERSION=017 FBLANG=deprecated norun enc noopt exe nocon NoDone icon sendmail.ico kill
''pre end

$APPTYPE GUI
$OPTIMIZE on
$TYPECHECK on


$IFNDEF TRUE
    $DEFINE TRUE 1
$ENDIF

$IFNDEF FALSE
    $DEFINE FALSE 0
$ENDIF

DECLARE SUB ButtonClick  '"Send mail" button
DECLARE SUB TimerExpired  'Check for incomming messages from server
DECLARE SUB mailersub
DECLARE SUB savemailersub
DECLARE SUB restoremailersub
DECLARE SUB beginauto

$include "includes\QINI.inc"

DIM homepath AS STRING
homepath = CurDir$
DIM ini AS QINI
ini.FileName = homepath + "\QChartist.ini"

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

DIM beginautotimer AS QTIMER
beginautotimer.Enabled = 0
beginautotimer.Interval = 5000
beginautotimer.OnTimer = restoremailersub

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
        Text = "julien.moog@laposte.net"
        'onchange=edit2change
    END CREATE
    CREATE Edit3 AS QEDIT

        Left = 110
        Top = 37 + 27
        Width = 380
        Height = 20
        Text = "julien.moog47@gmail.com"
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
        Checked = 1
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
    'onshow=restoremailersub
    'showmodal
END CREATE

SUB restoremailersub
    beginautotimer.Enabled = 0
    ini.Section = "Settings"
    Edit1.Text = ini.get("smtp" , "")
    Edit2.Text = ini.get("from" , "")
    Edit3.Text = ini.get("to" , "")
    Edit4.Text = ini.get("subject" , "")
    enablemailer.Checked = VAL(ini.get("mailer" , ""))
    TextBox.Text = ini.get("message" , "")
    ButtonClick
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
            Socket.Close(SockNum)
            SockNum = 0
            Timer1.Enabled = TRUE
            MailStep = 0
        END IF
        IF LastCode = 221 AND MailStep = 6 THEN  'last step completed
            'SHOWMESSAGE "Mail sent succesfully."         ' -> done
            Status.Caption = "Please enter your e-mail."
            Timer1.Enabled = FALSE
            Button.Caption = "<<< Send the e-mail... >>>"
            Socket.Close(SockNum)
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
        Socket.Close(SockNum)
        SockNum = 0
        Timer1.Enabled = TRUE
        MailStep = 0
        EXIT SUB
    END IF
    SockNum = Socket.Connect(Edit1.Text , 587) 'Connect to port 25
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
        'SHOWMESSAGE "Unable to connect to: "+Edit1.Text      'Couldn't connect to
        'server
    END IF
END SUB

SUB beginauto
    beginautotimer.Enabled = 1
END SUB

beginauto

MailForm.ShowModal
