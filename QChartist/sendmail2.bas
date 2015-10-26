''pre cmd FBVERSION=017 FBLANG=deprecated norun enc noopt exe nocon NoDone icon sendmail.ico kill
''pre end

$APPTYPE console
$OPTIMIZE on
$TYPECHECK on

CHDIR "C:\QChartist"

if curdir$<>"C:\QChartist" then
showmessage "QChartist won't function properly, please install it in directory C:\QChartist"
end if

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
    CREATE hostedit AS QEDIT

        Left = 110
        Top = 10
        Width = 130
        Height = 20
        Text = "smtp.sfr.fr"
        'onchange=edit1change
    END CREATE
    CREATE loginlab AS qlabel

        Left = 250
        Top = 10
        Width = 130
        Height = 20
        caption="Login:"
        'onchange=edit1change
    END CREATE
    CREATE loginedit AS qedit

        Left = 320
        Top = 10
        Width = 130
        Height = 20
        text=""
        'onchange=edit1change
    END CREATE
    CREATE fromedit AS QEDIT

        Left = 110
        Top = 37
        Width = 130
        Height = 20
        Text = "julien.moog@laposte.net"
        'onchange=edit2change
    END CREATE
    CREATE passlab AS qlabel

        Left = 250
        Top = 37
        Width = 130
        Height = 20
        caption="Password:"
        'onchange=edit1change
    END CREATE
    CREATE passedit AS qedit

        Left = 320
        Top = 37
        Width = 130
        Height = 20
        text=""
        'onchange=edit1change
        visible=0
    END CREATE
    CREATE toedit AS QEDIT

        Left = 110
        Top = 37 + 27
        Width = 130
        Height = 20
        Text = "julien.moog47@gmail.com"
        'onchange=edit3change
    END CREATE
    CREATE portlab AS qlabel

        Left = 250
        Top = 37 + 27
        Width = 130
        Height = 20
        caption="Port:"
        'onchange=edit1change
    END CREATE
    CREATE portedit AS qedit

        Left = 320
        Top = 37 + 27
        Width = 130
        Height = 20
        text="587"
        'onchange=edit1change
    END CREATE
    CREATE subjectedit AS QEDIT

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
    CREATE messageedit AS QRICHEDIT
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
    hostedit.Text = ini.get("smtp" , "")
    fromedit.Text = ini.get("from" , "")
    toedit.Text = ini.get("to" , "")
    subjectedit.Text = ini.get("subject" , "")
    loginedit.Text = ini.get("maileruserid" , "")
    passedit.Text = ini.get("mailerpass" , "")
    portedit.Text = ini.get("mailerport" , "")
    enablemailer.Checked = VAL(ini.get("mailer" , ""))
    messageedit.Text = ini.get("message" , "")
    ButtonClick
END SUB

SUB savemailersub
    ini.Section = "Settings"
    ini.Write("smtp" , hostedit.Text)
    ini.Write("from" , fromedit.Text)
    ini.Write("to" , toedit.Text)
    ini.Write("subject" , subjectedit.Text)
    ini.Write("message" , messageedit.Text)
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

SUB ButtonClick  'Begin to send the mail

    defint pid
    pid=shell ("cmd.exe /c senditquiet.exe -s "+hostedit.text+" -port "+portedit.text+" -u "+loginedit.text+" -protocol ssl"+" -p "+passedit.Text+" -f "+fromedit.text+" -t "+toedit.text+" -subject "+chr$(34)+subjectedit.text+chr$(34)+" -body "+chr$(34)+messageedit.text+chr$(34),1)
END SUB

SUB beginauto
    beginautotimer.Enabled = 1
END SUB

beginauto

MailForm.ShowModal
