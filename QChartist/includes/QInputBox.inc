'============

'QInputBox.inc

'============

'--- QInputBox.bas: <<-- This is the testing module for <QInputBox.inc>

'===========================================

'--- Purpose:

'This Control gives a useful method to querry user for an input

'while running the application. We often encounter that need.

'(C) Stanescu Serban, 2004, GNU-GPL (See http://www.gnu.org)

'==========================

TYPE QInputBox EXTENDS QFORM

    Message AS QEDIT  '--- Add the edit field

    lblQuerry AS QLABEL  '--- Add a label for our message

    annullabtn AS QBUTTON

    OKBtn AS QBUTTON  '--- The button we need to

    'close the window and pass the input value

    '--- Redefine the OKBtn.OnClick Event to according to our purpose

    EVENT annullabtn.OnClick
        QInputBox.Message.Text = ""
        QInputBox.Close
    END EVENT

    EVENT OKBtn.OnClick

        IF QInputBox.Message.Text <> "" THEN

            QInputBox.Close

        ELSE

            '--- Change the message according to the locales...

            '---(EN)

            SHOWMESSAGE "Please type something in the field"


        END IF

    END EVENT

    EVENT message.OnKeyPress(key AS BYTE)

        IF key = 13 THEN

            IF QInputBox.Message.Text <> "" THEN

                QInputBox.Close

            ELSE

                '--- Change the message according to the locales...

                '---(EN)

                SHOWMESSAGE "Please type something in the field"

            END IF

        END IF

    END EVENT

    EVENT OnClose
        'If QInputBox.Message.Text="" Then end


    END EVENT

    FUNCTION INPUT(Querry AS STRING) AS STRING

        '--- Why doesn't this work?!!

        'QInputBox.lblQuerry.Alignment=2 'taCenter '2

        QInputBox.lblQuerry.Caption = " " + Querry

        QInputBox.Message.Font.Bold = 1
        setfocus(QInputBox.message.Handle)

        QInputBox.ShowModal

        Result = QInputBox.Message.Text

        QInputBox.Message.Text = ""

    END FUNCTION


    CONSTRUCTOR

        DelBorderIcons 1 , 2  '--- Minimize and Restore buttons
        BorderStyle = 4
        Height = 150
        Width = 400
        Center

        lblQuerry.Parent = QInputBox

        lblQuerry.AutoSize = 0

        lblQuerry.Height = 100

        lblQuerry.Alignment = 2  'taCenter

        lblQuerry.Top = 5

        lblQuerry.Font.Bold = 1

        lblQuerry.LabelStyle = 1

        Message.Parent = QInputBox

        Message.Left = 5

        OKBtn.Parent = QInputBox
        annullabtn.Parent = QInputBox


        OKBtn.Top = QInputBox.ClientHeight - 27
        annullabtn.Caption = "Cancel"
        annullabtn.Top = QInputBox.ClientHeight - 27
        annullabtn.Left = 315
        okbtn.Left = 5

        Message.Top = QInputBox.OKBtn.Top - 27

        'OKBtn.Left=QInputBox.clientWidth/2-OKBtn.Width/2

        OKBtn.Font.Bold = 1

        lblQuerry.Width = QInputBox.ClientWidth - 10

        Message.Width = QInputBox.ClientWidth - 10

        OKBtn.Caption = "O&K"

    END CONSTRUCTOR

END TYPE
