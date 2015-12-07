'$apptype gui

'$include "rapidq2.inc"
'$include "like.inc"
'$include "qprogress.inc"

'$typecheck on

declare sub busytimerloginsub
declare sub loginsub
declare sub busy(isbusy as integer)
declare sub showportfoliosub
declare sub accounttimersub
declare sub pfquotetimersub
declare sub accountbalancesub
declare sub orderslistsub
declare sub openedorderslistsub
declare sub closedorderslistsub
declare sub clearopenedordersfields
declare sub showorderformsub
declare sub ordergetpricesub
declare sub openordersendsub
declare sub closeordersendsub
declare sub busytimergetpricesub
declare sub busytimeropenordersub
declare sub busytimercloseordersub
declare sub logoutsub
declare sub busytimerlogoutsub
declare sub gshareinvest_register_sub
declare sub showportfoliosub

' ---------------- functions
declare function gsi_isconnected() as integer
declare function gsi_login(username as string,password as string) as integer
declare function gsi_logout() as integer
declare function gsi_order_buy(symbol as string,quantity as integer) as integer
declare function gsi_order_sell(order_id as integer) as integer
' ----------------------------------

defint accountincr=0
defint openedpositionsnb=0
defint openedpositionsnbincr=0
defstr tmppathgsi
defstr last_opened_order_id
defint gsi_quiet=0
defint last_response_order_close
defint trying_to_connect=0

dim accounttimer as qtimer
accounttimer.enabled=0
accounttimer.interval=2000
accounttimer.ontimer=accounttimersub

dim pfquotetimer as qtimer
pfquotetimer.enabled=0
pfquotetimer.interval=2000
pfquotetimer.ontimer=pfquotetimersub

dim busytimerlogin as qtimer
busytimerlogin.enabled=0
busytimerlogin.interval=1000
busytimerlogin.ontimer=busytimerloginsub

dim busytimerlogout as qtimer
busytimerlogout.enabled=0
busytimerlogout.interval=1000
busytimerlogout.ontimer=busytimerlogoutsub

dim busytimeropenorder as qtimer
busytimeropenorder.enabled=0
busytimeropenorder.interval=1000
busytimeropenorder.ontimer=busytimeropenordersub

dim busytimercloseorder as qtimer
busytimercloseorder.enabled=0
busytimercloseorder.interval=1000
busytimercloseorder.ontimer=busytimercloseordersub

dim busytimergetprice as qtimer
busytimergetprice.enabled=0
busytimergetprice.interval=1000
busytimergetprice.ontimer=busytimergetpricesub

'dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusy.txt",65535)
busystream.writeline "0"
busystream.close
busystream.open("c:\qchartist\gshareinvest\isbusyaccountbalance.txt",65535)
busystream.writeline "0"
busystream.close
busystream.open("c:\qchartist\gshareinvest\isbusyorderslist.txt",65535)
busystream.writeline "0"
busystream.close
busystream.open("c:\qchartist\gshareinvest\isbusyopenedorderslist.txt",65535)
busystream.writeline "0"
busystream.close
busystream.open("c:\qchartist\gshareinvest\isbusypfquote.txt",65535)
busystream.writeline "0"
busystream.close
busystream.open("c:\qchartist\gshareinvest\isbusyclosedorderslist.txt",65535)
busystream.writeline "0"
busystream.close
busystream.open("c:\qchartist\gshareinvest\isbusygetprice.txt",65535)
busystream.writeline "0"
busystream.close
busystream.open("c:\qchartist\gshareinvest\isbusyopenorder.txt",65535)
busystream.writeline "0"
busystream.close
busystream.open("c:\qchartist\gshareinvest\isbusycloseorder.txt",65535)
busystream.writeline "0"
busystream.close
busystream.open("c:\qchartist\gshareinvest\isbusylogout.txt",65535)
busystream.writeline "0"
busystream.close

defstr goingto=""
defstr goingtogetprice=""
defstr goingtoopenorder=""
defstr goingtocloseorder=""
defstr querystring=""
defstr pwd=""
defint accountbusy=0


create loginform as qform
caption="Login"
width=260
height=400
center
visible=0

create gshareinvest as qlabel
caption="Enter your gshareinvest account info:"
end create

create logingroupbox as qgroupbox
top=20
height=170
width=230

create usernamelabel as qlabel
caption="Username:"
top=10
left=10
end create

create usernameloginedit as qedit
text=""
top=10
left=100
end create

create passwordlabel as qlabel
caption="Password:"
top=35
left=10
end create

create passwordedit as qedit
text=""
top=35
left=100
passwordchar="*"
end create

create loginbtn as qbutton
top=65
left=10
width=50
caption="Login"
onclick=loginsub

end create

create logoutbtn as qbutton
top=65
left=70
width=50
caption="Logout"
onclick=logoutsub
enabled=0
end create

create showportfoliobtn as qbutton
top=65
left=130
width=80
caption="Show portfolio"
onclick=showportfoliosub
enabled=0
end create

create newlabel as qlabel
caption="New?"
top=100
left=10
end create

create creategsaccount as qbutton
caption="Create an account"
top=100
left=40
width=130
onclick=gshareinvest_register_sub
end create

create secureimage as qimage
bmp="c:\qchartist\gshareinvest\images\secure.bmp"
top=130
left=10
end create

create logininfolabel as qlabel
top=130
left=50
caption="Your password is encrypted before"+chr$(10)+_
"being sent through the network"
end create
end create

create gsdescriptionlabel as qlabel
top=200
caption="Trade stocks with bitcoins via gshareinvest.com"+chr$(10)+_
"No account fees, no transaction fees, no spead."+chr$(10)+chr$(10)+_
"The team of QChartist has no liability, is not"+chr$(10)+_
"affiliated and does not endorse any responsability"+chr$(10)+_
"with gshareinvest.com"+chr$(10)+_
"This is a third party service. Use it at your own risks."
end create

create loginstatuslabel as qlabel
top=300
left=50

end create

'onshow=showportfoliosub
end create

create portfolioform as qform
height=700
width=1000
center

create portfoliobalancelabel as qlabel
    top=0
    left=0
    caption="FUNDS (USD):"
end create    

create portfoliobalancepanel as qpanel
    top=20
    height=50
    width=400 

CREATE portfoliobalancegrid AS QSTRINGGRID
        Align = alClient
        FixedRows = 1
        FixedCols = 0
        ColCount = 3
        RowCount = 2
        DefaultRowHeight = 20
        Defaultcolwidth = 120
        Cell(0,0) = "Total deposits"
        Cell(1,0) = "Usable funds"
        Cell(2,0) = "Total funds withdrawn"
END CREATE
end create
    
create portfolioorderslabel as qlabel
    top=80
    left=0
    caption="ALL ORDERS:"
end create    
    
create portfolioorderspanel as qpanel
    top=100
    height=100
    width=810
    
CREATE portfolioordersgrid AS QSTRINGGRID

        Align = alClient
        FixedRows = 1
        FixedCols = 0
        ColCount = 12
        RowCount = 100
        DefaultRowHeight = 20
        Defaultcolwidth = 60
        Cell(0,0) = "Order #"
        Cell(1,0) = "Symbol"
        Cell(2,0) = "Qty"        
        Cell(3,0) = "Open price"
        Cell(4,0) = "Amount inv."
        Cell(5,0) = "Open date"
        Cell(6,0) = "Close price"
        Cell(7,0) = "Profit amount"
        Cell(8,0) = "Close date"
        Cell(9,0) = "Status"
        Cell(10,0) = "Buy #"
        Cell(11,0) = "Sell #"
        colwidths(0)=50
        colwidths(1)=50
        colwidths(2)=30
        colwidths(3)=60
        colwidths(4)=60
        colwidths(5)=110
        colwidths(6)=60
        colwidths(7)=60
        colwidths(8)=110
        colwidths(9)=95
        colwidths(10)=40
        colwidths(11)=40
    END CREATE    
end create

create portfolioopenedorderslabel as qlabel
    top=210
    left=0
    caption="OPENED ORDERS:"
end create    
    
create portfolioopenedorderspanel as qpanel
    top=230
    height=100
    width=730
    
CREATE portfolioopenedordersgrid AS QSTRINGGRID

        Align = alClient
        FixedRows = 1
        FixedCols = 0
        ColCount = 11
        RowCount = 100
        DefaultRowHeight = 20
        Defaultcolwidth = 60
        Cell(0,0) = "Order #"
        Cell(1,0) = "Symbol"
        Cell(2,0) = "Qty"
        Cell(3,0) = "Open price"
        Cell(4,0) = "Amount inv."
        Cell(5,0) = "Open date"
        Cell(6,0) = "Status"
        Cell(7,0) = "Buy #"
        Cell(8,0) = "Current price"
        Cell(9,0) = "Current profit"
        cell(10,0)="Difference"
        colwidths(0)=50
        colwidths(1)=50
        colwidths(2)=30
        colwidths(3)=60
        colwidths(4)=60
        colwidths(5)=110        
        colwidths(6)=95
        colwidths(7)=40
        colwidths(8)=60
        colwidths(9)=60
        colwidths(10)=60
        
    END CREATE    
end create

create sumamountinvpanel as qpanel
height=20
width=60
top=330
left=197
color=rgb(255,255,255)
create sumamountinvlabel as qlabel

end create
end create

create sumprofitpanel as qpanel
height=20
width=60
top=330
left=567
color=rgb(255,255,255)
create sumprofitlabel as qlabel

end create
end create

create sumdiffpanel as qpanel
height=20
width=60
top=330
left=628
color=rgb(255,255,255)
create sumdifflabel as qlabel
caption=""
end create
end create

create portfolioclosedorderslabel as qlabel
    top=350
    left=0
    caption="CLOSED ORDERS:"
end create    
    
create portfolioclosedorderspanel as qpanel
    top=370
    height=100
    width=880
    
CREATE portfolioclosedordersgrid AS QSTRINGGRID

        Align = alClient
        FixedRows = 1
        FixedCols = 0
        ColCount = 13
        RowCount = 100
        DefaultRowHeight = 20
        Defaultcolwidth = 60
        Cell(0,0) = "Order #"
        Cell(1,0) = "Symbol"
        Cell(2,0) = "Qty"        
        Cell(3,0) = "Open price"
        Cell(4,0) = "Amount inv."
        Cell(5,0) = "Open date"
        Cell(6,0) = "Close price"
        Cell(7,0) = "Profit amount"
        Cell(8,0) = "Close date"
        Cell(9,0) = "Status"
        Cell(10,0) = "Buy #"
        Cell(11,0) = "Sell #"
        cell(12,0)="Difference"
        colwidths(0)=50
        colwidths(1)=50
        colwidths(2)=30
        colwidths(3)=60
        colwidths(4)=60
        colwidths(5)=110
        colwidths(6)=60
        colwidths(7)=60
        colwidths(8)=110
        colwidths(9)=95
        colwidths(10)=40
        colwidths(11)=40
        colwidths(12)=60
    END CREATE    
end create

create sumamountinvclosedorderspanel as qpanel
height=20
width=60
top=470
left=197
color=rgb(255,255,255)
create sumamountinvclosedorderslabel as qlabel

end create
end create

create sumprofitclosedorderspanel as qpanel
height=20
width=60
top=470
left=430
color=rgb(255,255,255)
create sumprofitclosedorderslabel as qlabel

end create
end create

create sumdiffclosedorderspanel as qpanel
height=20
width=60
top=470
left=780
color=rgb(255,255,255)
create sumdiffclosedorderslabel as qlabel
caption=""
end create
end create

create neworderbtn as qbutton
caption="New order"
onclick=showorderformsub
top=500
left=20
end create

create closeordertlabel as qlabel
caption="Close order #:"
top=530
left=20
end create

create closeordernbedit as qedit
top=530
left=100
width=50
end create

create closeorderokbtn as qbutton
caption="Sell"
top=530
left=150
onclick=closeordersendsub
end create

create ordernoticegrids as qlabel
caption="Notice: All calculations are made for the last 100 transactions only."
top=580
left=80
end create

end create    

create orderform as qform
height=240
width=320
caption="New order"
center

create ordersymbollabel as qlabel
caption="Enter a symbol:"
end create
create ordersymboledit as qedit
left=100
width=70
end create
create ordergetpricebtn as qbutton
caption="Get price"
onclick=ordergetpricesub
left=180
end create
create orderqtylabel as qlabel
caption="Enter a quantity:"
top=30
end create
create orderqtyedit as qedit
top=30
left=100
width=50
end create
create openorderokbtn as qbutton
caption="Buy"
top=60
left=0
onclick=openordersendsub
end create
create ordercurpricetlabel as qlabel
top=100
left=0
caption="Unit price: $"
end create
create ordercurpricelabel as qlabel
top=100
left=60
caption=""
end create
create orderamounttlabel as qlabel
top=120
left=0
caption="Order amount: $"
end create
create orderamountlabel as qlabel
top=120
left=80
caption=""
end create

end create

dim loginprogress as qprogress
loginprogress.parent=loginform.handle
loginprogress.top=330
loginprogress.left=20
loginprogress.width=200
loginprogress.value=0


sub loginsub

if usernameloginedit.text="" or passwordedit.text="" then 
showmessage "Enter a valid username and password"
exit sub
end if

loginbtn.enabled=0
busy(1)
loginprogress.value=0
loginstatuslabel.caption="Connecting, please wait..."
dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusy.txt",fmopenread)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then
trying_to_connect=1
busystream.open("c:\qchartist\gshareinvest\isbusy.txt",fmopenwrite)
busystream.writeline("1")
busystream.close


dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\get_form.bat",0)
chdir tmppathgsi
goingto="getform":busytimerlogin.enabled=1

end if

end sub

sub logoutsub

logoutbtn.enabled=0
accountbusy=1

accounttimer.enabled=0
pfquotetimer.enabled=0
busytimerlogin.enabled=0
busytimeropenorder.enabled=0
busytimercloseorder.enabled=0
busytimergetprice.enabled=0
defint accountincr=0
defint openedpositionsnb=0
defint openedpositionsnbincr=0
defstr goingto=""
defstr goingtogetprice=""
defstr goingtoopenorder=""
defstr goingtocloseorder=""
defstr querystring=""
portfolioform.visible=0

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusylogout.txt",fmopenread)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then

busystream.open("c:\qchartist\gshareinvest\isbusylogout.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\logout.bat",0)
chdir tmppathgsi
busytimerlogout.enabled=1

end if

end sub

sub busytimerlogoutsub

'defint pid

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusylogout.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then

busytimerlogout.enabled=0
loginstatuslabel.caption="Disconnected"
loginprogress.value=0
loginbtn.enabled=1
showportfoliobtn.enabled=0
accountbusy=0
PLAYWAV "c:\qchartist\gshareinvest\sounds\disconnect.wav", SND_ASYNC

end if

end sub

sub busytimerloginsub

'defint pid

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusy.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then

busytimerlogin.enabled=0
select case goingto

case "getform"
goto getformlogin

case "getaccountinfo"
goto getaccountinfo

case "readencpass"
goto readencpass

case "readaccount"
goto readaccount

end select

end if

exit sub

getformlogin:
loginprogress.value=25
defstr filestr=""
dim filestream as qfilestream
filestream.open("c:\qchartist\gshareinvest\form.html",0)
while not filestream.eof
filestr=filestr+filestream.readline
wend
filestream.close

defint portionloc=instr(filestr,chr$(34)+"salt"+chr$(34))
defstr portion=mid$(filestr,portionloc+14,len(filestr))
portionloc=instr(portion,chr$(34))
portion=mid$(portion,1,portionloc-1)
defstr salt=portion

portionloc=instr(filestr,chr$(34)+"key"+chr$(34))
portion=mid$(filestr,portionloc+13,len(filestr))
portionloc=instr(portion,chr$(34))
portion=mid$(portion,1,portionloc-1)
defstr key=portion


'busystream.open("isbusy.txt",fmopenwrite)
'busystream.writeline("1")
'busystream.close

'dim pid as integer
'pid=shell ("perform_login.bat "+usernameloginedit.text+" "+passwordedit.text+" "+salt+" "+key,1)
'pid=shell ("/bin/sh -c "+chr$(34)+"./getstock_buy.sh "+filestr+chr$(34),1)
'goingto="getaccountinfo":querystring="":busytimerlogin.enabled=1

filestr=""
defstr line
filestream.open("c:\qchartist\gshareinvest\encrypt_model.html",0)
while not filestream.eof
line=filestream.readline
if instr(line,chr$(34)+"pass_field"+chr$(34))>0 then
filestr=filestr+"<input type="+chr$(34)+"password"+chr$(34)+" name="+chr$(34)+"pass_field"+chr$(34)+" value="+chr$(34)+passwordedit.text+chr$(34)+" />"+chr$(10)
elseif instr(line,chr$(34)+"salt"+chr$(34))>0 then
filestr=filestr+"<input type="+chr$(34)+"hidden"+chr$(34)+" name="+chr$(34)+"salt"+chr$(34)+" value="+chr$(34)+salt+chr$(34)+" />"+chr$(10)
elseif instr(line,chr$(34)+"key"+chr$(34))>0 then
filestr=filestr+"<input type="+chr$(34)+"hidden"+chr$(34)+" name="+chr$(34)+"key"+chr$(34)+" value="+chr$(34)+key+chr$(34)+" />"+chr$(10)
else
filestr=filestr+line+chr$(10)
end if
wend
filestream.close

filestream.open("c:\qchartist\gshareinvest\encrypt.html",65535)
filestream.writeline (filestr)
filestream.close

busystream.open("c:\qchartist\gshareinvest\isbusy.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\encrypt.bat",0)
chdir tmppathgsi
'pid=shell ("/bin/sh -c "+chr$(34)+"./getstock_buy.sh "+filestr+chr$(34),1)
goingto="readencpass":busytimerlogin.enabled=1

goto busytimerloginsubend

getaccountinfo:
loginprogress.value=75
busystream.open("c:\qchartist\gshareinvest\isbusy.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\get_account_info.bat "+querystring,0)
chdir tmppathgsi
'pid=shell ("/bin/sh -c "+chr$(34)+"./getstock_buy.sh "+filestr+chr$(34),1)
goingto="readaccount":busytimerlogin.enabled=1

goto busytimerloginsubend

readencpass:
loginprogress.value=50
defstr filestr2=""
filestream.open("c:\qchartist\gshareinvest\encrypted.html",0)
while not filestream.eof
filestr2=filestr2+filestream.readline
wend
filestream.close

portionloc=instr(filestr2,"encrypted pass:"+chr$(34))
portion=mid$(filestr2,portionloc+16,len(filestr2))
portionloc=instr(portion,chr$(34))
portion=mid$(portion,1,portionloc-1)
defstr encpass=portion

busystream.open("c:\qchartist\gshareinvest\isbusy.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

defint i
defstr fakepass=""
for i=1 to len(passwordedit.text)
fakepass=fakepass+"-"
next i

'dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\perform_login.bat "+usernameloginedit.text+" "+fakepass+" "+encpass+" "+salt+" "+key,0)
chdir tmppathgsi
'pid=shell ("/bin/sh -c "+chr$(34)+"./getstock_buy.sh "+filestr+chr$(34),1)
goingto="getaccountinfo":querystring="":busytimerlogin.enabled=1

goto busytimerloginsubend



readaccount:
defstr filestr3=""
filestream.open("c:\qchartist\gshareinvest\account.html",0)
while not filestream.eof
filestr3=filestr3+filestream.readline
wend
filestream.close

if like(filestr3,"*Welcome "+usernameloginedit.text+"*")=1 then
loginstatuslabel.caption="Connected"
PLAYWAV "c:\qchartist\gshareinvest\sounds\connect.wav", SND_ASYNC
busy(0)
loginbtn.enabled=0
if gsi_quiet=0 then showportfoliosub
showportfoliobtn.enabled=1
loginbtn.enabled=0
loginprogress.value=100
accounttimer.enabled=1
pfquotetimer.enabled=1
trying_to_connect=0
else
loginstatuslabel.caption="Unable to connect"
PLAYWAV "c:\qchartist\gshareinvest\sounds\timeout.wav", SND_ASYNC
loginbtn.enabled=1
showportfoliobtn.enabled=0
busy(0)
logoutbtn.enabled=0
loginprogress.value=0
trying_to_connect=0
end if

goto busytimerloginsubend


busytimerloginsubend:

end sub


sub busytimeropenordersub

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusyaccountbalance.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusyorderslist.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusyopenedorderslist.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusyclosedorderslist.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusycloseorder.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

'dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusyopenorder.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then

busytimeropenorder.enabled=0
select case goingtoopenorder

case "getformopenorder"
goto getformopenorder

case "readformopenorder"
goto readformopenorder

case "readresultopenorder"
goto readresultopenorder

end select

end if

exit sub

getformopenorder:

dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\get_open_order_form.bat",0)
chdir tmppathgsi
'pid=shell ("/bin/sh -c "+chr$(34)+"./getstock_buy.sh "+filestr+chr$(34),1)
goingtoopenorder="readformopenorder":busytimeropenorder.enabled=1

goto busytimeropenordersubend

readformopenorder:

defstr filestr=""
dim filestream as qfilestream
filestream.open("c:\qchartist\gshareinvest\open_order_form.html",0)
while not filestream.eof
filestr=filestr+filestream.readline
wend
filestream.close

defint portionloc=instr(filestr,chr$(34)+"invoice_number"+chr$(34))
defstr portion=mid$(filestr,portionloc+24,len(filestr))
portionloc=instr(portion,chr$(34))
portion=mid$(portion,1,portionloc-1)
defstr invoice_number=portion

busystream.open("c:\qchartist\gshareinvest\isbusyopenorder.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\open_order.bat "+invoice_number+" "+ordersymboledit.text+" "+orderqtyedit.text,0)
chdir tmppathgsi
'pid=shell ("/bin/sh -c "+chr$(34)+"./getstock_buy.sh "+filestr+chr$(34),1)
goingtoopenorder="readresultopenorder":busytimeropenorder.enabled=1

goto busytimeropenordersubend

readresultopenorder:
defstr filestr2=""
filestream.open("c:\qchartist\gshareinvest\open_order_result.html",0)
while not filestream.eof
filestr2=filestr2+filestream.readline
wend
filestream.close

if like(filestr2,"*Order sent, thank you !*")=1 then
last_opened_order_id=mid$(filestr2,instr(filestr2,"Order #")+7,instr(instr(filestr2,"Order #")+7,filestr2,"<")-1)
PLAYWAV "c:\qchartist\gshareinvest\sounds\ok.wav", SND_ASYNC
if gsi_quiet=0 then showmessage "Order sent"
else
last_opened_order_id="0"
PLAYWAV "c:\qchartist\gshareinvest\sounds\timeout.wav", SND_ASYNC
if gsi_quiet=0 then showmessage "Error"
end if

openedpositionsnbincr=0
accountincr=0
openedpositionsnb=0
accounttimer.enabled=1
pfquotetimer.enabled=1
openorderokbtn.enabled=1

goto busytimeropenordersubend

busytimeropenordersubend:

end sub


sub busytimercloseordersub

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusyaccountbalance.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusyorderslist.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusyopenedorderslist.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusyclosedorderslist.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusyopenorder.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

'dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusycloseorder.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then

busytimercloseorder.enabled=0
select case goingtocloseorder

case "getformcloseorder"
goto getformcloseorder

case "readformcloseorder"
goto readformcloseorder

case "readresultcloseorder"
goto readresultcloseorder

end select

end if

exit sub

getformcloseorder:

dim pid as integer

tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\get_close_order_form.bat "+closeordernbedit.text,0)
chdir tmppathgsi
'pid=shell ("/bin/sh -c "+chr$(34)+"./getstock_buy.sh "+filestr+chr$(34),1)
goingtocloseorder="readformcloseorder":busytimercloseorder.enabled=1

goto busytimercloseordersubend

readformcloseorder:

defstr filestr=""
dim filestream as qfilestream
filestream.open("c:\qchartist\gshareinvest\close_order_form.html",0)
while not filestream.eof
filestr=filestr+filestream.readline
wend
filestream.close

defint portionloc=instr(filestr,"'invoice_number'")
defstr portion=mid$(filestr,portionloc+24,len(filestr))
portionloc=instr(portion,"'")
portion=mid$(portion,1,portionloc-1)
defstr invoice_number=portion

busystream.open("c:\qchartist\gshareinvest\isbusycloseorder.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\close_order.bat "+invoice_number+" "+closeordernbedit.text,0)
chdir tmppathgsi
'pid=shell ("/bin/sh -c "+chr$(34)+"./getstock_buy.sh "+filestr+chr$(34),1)
goingtocloseorder="readresultcloseorder":busytimercloseorder.enabled=1

goto busytimercloseordersubend

readresultcloseorder:
defstr filestr2=""
filestream.open("c:\qchartist\gshareinvest\close_order_result.html",0)
while not filestream.eof
filestr2=filestr2+filestream.readline
wend
filestream.close

if like(filestr2,"*Order sent, thank you !*")=1 then
last_response_order_close=1
PLAYWAV "c:\qchartist\gshareinvest\sounds\ok.wav", SND_ASYNC
if gsi_quiet=0 then showmessage "Order sent"
else
last_response_order_close=0
PLAYWAV "c:\qchartist\gshareinvest\sounds\timeout.wav", SND_ASYNC
if gsi_quiet=0 then showmessage "Error"
end if

openedpositionsnbincr=0
accountincr=0
openedpositionsnb=0
accounttimer.enabled=1
pfquotetimer.enabled=1
closeorderokbtn.enabled=1

goto busytimercloseordersubend

busytimercloseordersubend:


end sub






sub busytimergetpricesub

'defint pid

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusygetprice.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then

busytimergetprice.enabled=0
select case goingtogetprice

case "getstockprice"
goto getstockprice

case "readstockprice"
goto readstockprice

end select

end if

exit sub

getstockprice:

busystream.open("c:\qchartist\gshareinvest\isbusygetprice.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
if like(platform,"*Wine*")=0 then pid=shell ("c:\qchartist\gshareinvest\getstock2.bat "+ordersymboledit.text,0)
if like(platform,"*Wine*")=1 then pid=shell ("/bin/sh -c "+chr$(34)+"./getstock2.sh "+ordersymboledit.text+chr$(34),0)
chdir tmppathgsi
'pid=shell ("/bin/sh -c "+chr$(34)+"./getstock_buy.sh "+filestr+chr$(34),1)
goingtogetprice="readstockprice":busytimergetprice.enabled=1

goto busytimergetpricesubend

readstockprice:
defstr filestr=""
dim filestream as qfilestream
filestream.open("c:\qchartist\gshareinvest\stockquote.txt",0)
while not filestream.eof
filestr=filestr+filestream.readline
wend
filestream.close

if val(filestr)>0 then
ordercurpricelabel.caption=filestr
orderamountlabel.caption=str$(val(orderqtyedit.text)*val(filestr))
end if

ordergetpricebtn.enabled=1

goto busytimergetpricesubend

busytimergetpricesubend:


end sub







sub busy(isbusy as integer)

if isbusy=1 then
loginbtn.enabled=0
logoutbtn.enabled=0
accountbusy=1
else
loginbtn.enabled=1
logoutbtn.enabled=1
accountbusy=0
end if

end sub

sub showportfoliosub
portfolioform.visible=1
end sub

sub accountbalancesub

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusyaccountbalance.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then

dim filestream as qfilestream

if fileexists("c:\qchartist\gshareinvest\account_balance.html")=0 then
filestream.open("c:\qchartist\gshareinvest\account_balance.html",65535)
filestream.close
end if

defstr filestr=""
filestream.open("c:\qchartist\gshareinvest\account_balance.html",0)
while not filestream.eof
filestr=filestr+filestream.readline
wend
filestream.close

if len(filestr)>0 then

defint instrbegin=instr(filestr,"total_deposits_id")+19
defint instrend=instr(instr(filestr,"total_deposits_id")+19,filestr,"</td>")
defstr total_deposits=mid$(filestr,instrbegin,instrend-instrbegin)
portfoliobalancegrid.cell(0,1)=total_deposits

instrbegin=instr(filestr,"usable_funds_id")+17
instrend=instr(instr(filestr,"usable_funds_id")+17,filestr,"</td>")
defstr usable_funds=mid$(filestr,instrbegin,instrend-instrbegin)
portfoliobalancegrid.cell(1,1)=usable_funds

instrbegin=instr(filestr,"total_funds_withdrawn_id")+26
instrend=instr(instr(filestr,"total_funds_withdrawn_id")+26,filestr,"</td>")
defstr total_funds_withdrawn=mid$(filestr,instrbegin,instrend-instrbegin)
portfoliobalancegrid.cell(2,1)=total_funds_withdrawn

end if

busystream.open("c:\qchartist\gshareinvest\isbusyaccountbalance.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\get_account_balance.bat",0)
chdir tmppathgsi

end if

end sub

sub orderslistsub

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusyorderslist.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then

dim filestream as qfilestream

if fileexists("c:\qchartist\gshareinvest\orders_list.html")=0 then
filestream.open("c:\qchartist\gshareinvest\orders_list.html",65535)
filestream.close
end if

defstr filestr=""
filestream.open("c:\qchartist\gshareinvest\orders_list.html",0)
while not filestream.eof
filestr=filestr+filestream.readline
wend
filestream.close

if len(filestr)>0 then

defint i

for i=1 to 100

if instr(filestr,"order_id_id")<1 then
exit for
end if

defint instrbegin=instr(filestr,"order_id_id")+13
defint instrend=instr(instr(filestr,"order_id_id")+13,filestr,"</td>")
defstr order_id=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(0,i)=order_id

instrbegin=instr(filestr,"symbol_id")+11
defint instrinter=instr(instr(filestr,"symbol_id")+11,filestr,">")+1
instrend=instr(instrinter,filestr,"</a>")
defstr symbol=mid$(filestr,instrinter,instrend-instrinter)
portfolioordersgrid.cell(1,i)=symbol

instrbegin=instr(filestr,"qty_id")+8
instrend=instr(instr(filestr,"qty_id")+8,filestr,"</td>")
defstr qty=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(2,i)=qty

instrbegin=instr(filestr,"open_price_id")+15
instrend=instr(instr(filestr,"open_price_id")+15,filestr,"</td>")
defstr open_price=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(3,i)=open_price

instrbegin=instr(filestr,"invested_id")+13
instrend=instr(instr(filestr,"invested_id")+13,filestr,"</td>")
defstr invested=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(4,i)=invested

instrbegin=instr(filestr,"buy_processed_date_id")+23
instrend=instr(instr(filestr,"buy_processed_date_id")+23,filestr,"</td>")
defstr buy_processed_date=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(5,i)=buy_processed_date

instrbegin=instr(filestr,"close_price_id")+16
instrend=instr(instr(filestr,"close_price_id")+16,filestr,"</td>")
defstr close_price=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(6,i)=close_price

instrbegin=instr(filestr,"profit_id")+11
instrend=instr(instr(filestr,"profit_id")+11,filestr,"</td>")
defstr profit=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(7,i)=profit

instrbegin=instr(filestr,"sell_processed_date_id")+24
instrend=instr(instr(filestr,"sell_processed_date_id")+24,filestr,"</td>")
defstr sell_processed_date=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(8,i)=sell_processed_date

instrbegin=instr(filestr,"status_id")+11
instrend=instr(instr(filestr,"status_id")+11,filestr,"</td>")
defstr status=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(9,i)=status

instrbegin=instr(filestr,"invoice_number_buy_id")+23
instrend=instr(instr(filestr,"invoice_number_buy_id")+23,filestr,"</td>")
defstr invoice_number_buy=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(10,i)=invoice_number_buy

instrbegin=instr(filestr,"invoice_number_sell_id")+24
instrend=instr(instr(filestr,"invoice_number_sell_id")+24,filestr,"</td>")
defstr invoice_number_sell=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioordersgrid.cell(11,i)=invoice_number_sell

filestr=mid$(filestr,instrend,len(filestr))

next i

end if

busystream.open("c:\qchartist\gshareinvest\isbusyorderslist.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\get_orders_list.bat",0)
chdir tmppathgsi

end if

end sub

sub closedorderslistsub

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusyclosedorderslist.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then

dim filestream as qfilestream

if fileexists("c:\qchartist\gshareinvest\closed_orders_list.html")=0 then
filestream.open("c:\qchartist\gshareinvest\closed_orders_list.html",65535)
filestream.close
end if

defstr filestr=""
filestream.open("c:\qchartist\gshareinvest\closed_orders_list.html",0)
while not filestream.eof
filestr=filestr+filestream.readline
wend
filestream.close

if len(filestr)>0 then

defint i
defdbl sumaminv=0
defdbl sumprofit=0
for i=1 to 100

if instr(filestr,"order_id_id")<1 then
exit for
end if

defint instrbegin=instr(filestr,"order_id_id")+13
defint instrend=instr(instr(filestr,"order_id_id")+13,filestr,"</td>")
defstr order_id=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(0,i)=order_id

instrbegin=instr(filestr,"symbol_id")+11
defint instrinter=instr(instr(filestr,"symbol_id")+11,filestr,">")+1
instrend=instr(instrinter,filestr,"</a>")
defstr symbol=mid$(filestr,instrinter,instrend-instrinter)
portfolioclosedordersgrid.cell(1,i)=symbol

instrbegin=instr(filestr,"qty_id")+8
instrend=instr(instr(filestr,"qty_id")+8,filestr,"</td>")
defstr qty=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(2,i)=qty

instrbegin=instr(filestr,"open_price_id")+15
instrend=instr(instr(filestr,"open_price_id")+15,filestr,"</td>")
defstr open_price=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(3,i)=open_price

instrbegin=instr(filestr,"invested_id")+13
instrend=instr(instr(filestr,"invested_id")+13,filestr,"</td>")
defstr invested=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(4,i)=invested
sumaminv=sumaminv+val(invested)

instrbegin=instr(filestr,"buy_processed_date_id")+23
instrend=instr(instr(filestr,"buy_processed_date_id")+23,filestr,"</td>")
defstr buy_processed_date=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(5,i)=buy_processed_date

instrbegin=instr(filestr,"close_price_id")+16
instrend=instr(instr(filestr,"close_price_id")+16,filestr,"</td>")
defstr close_price=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(6,i)=close_price

instrbegin=instr(filestr,"profit_id")+11
instrend=instr(instr(filestr,"profit_id")+11,filestr,"</td>")
defstr profit=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(7,i)=profit
sumprofit=sumprofit+val(profit)

instrbegin=instr(filestr,"sell_processed_date_id")+24
instrend=instr(instr(filestr,"sell_processed_date_id")+24,filestr,"</td>")
defstr sell_processed_date=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(8,i)=sell_processed_date

instrbegin=instr(filestr,"status_id")+11
instrend=instr(instr(filestr,"status_id")+11,filestr,"</td>")
defstr status=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(9,i)=status

instrbegin=instr(filestr,"invoice_number_buy_id")+23
instrend=instr(instr(filestr,"invoice_number_buy_id")+23,filestr,"</td>")
defstr invoice_number_buy=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(10,i)=invoice_number_buy

instrbegin=instr(filestr,"invoice_number_sell_id")+24
instrend=instr(instr(filestr,"invoice_number_sell_id")+24,filestr,"</td>")
defstr invoice_number_sell=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioclosedordersgrid.cell(11,i)=invoice_number_sell

portfolioclosedordersgrid.cell(12,i)=str$(val(profit)-val(invested))

filestr=mid$(filestr,instrend,len(filestr))

next i

sumamountinvclosedorderslabel.caption=str$(sumaminv)
sumprofitclosedorderslabel.caption=str$(sumprofit)
sumdiffclosedorderslabel.caption=str$(sumprofit-sumaminv)

end if

busystream.open("c:\qchartist\gshareinvest\isbusyclosedorderslist.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\get_closed_orders_list.bat",0)
chdir tmppathgsi

end if

end sub

sub openedorderslistsub
defint openedpositionsnb_tmp=openedpositionsnb
openedpositionsnb=0

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusyopenedorderslist.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close

if val(isbusy)=0 then

dim filestream as qfilestream

if fileexists("c:\qchartist\gshareinvest\opened_orders_list.html")=0 then
filestream.open("c:\qchartist\gshareinvest\opened_orders_list.html",65535)
filestream.close
end if

defstr filestr=""
filestream.open("c:\qchartist\gshareinvest\opened_orders_list.html",0)
while not filestream.eof
filestr=filestr+filestream.readline
wend
filestream.close

if len(filestr)>0 then

defint i
defdbl sumaminv=0
for i=1 to 100

if instr(filestr,"order_id_id")<1 then
exit for
end if

defint instrbegin=instr(filestr,"order_id_id")+13
defint instrend=instr(instr(filestr,"order_id_id")+13,filestr,"</td>")
defstr order_id=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioopenedordersgrid.cell(0,i)=order_id

instrbegin=instr(filestr,"symbol_id")+11
defint instrinter=instr(instr(filestr,"symbol_id")+11,filestr,">")+1
instrend=instr(instrinter,filestr,"</a>")
defstr symbol=mid$(filestr,instrinter,instrend-instrinter)
portfolioopenedordersgrid.cell(1,i)=symbol

instrbegin=instr(filestr,"qty_id")+8
instrend=instr(instr(filestr,"qty_id")+8,filestr,"</td>")
defstr qty=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioopenedordersgrid.cell(2,i)=qty

instrbegin=instr(filestr,"open_price_id")+15
instrend=instr(instr(filestr,"open_price_id")+15,filestr,"</td>")
defstr open_price=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioopenedordersgrid.cell(3,i)=open_price

instrbegin=instr(filestr,"invested_id")+13
instrend=instr(instr(filestr,"invested_id")+13,filestr,"</td>")
defstr invested=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioopenedordersgrid.cell(4,i)=invested
sumaminv=sumaminv+val(invested)

instrbegin=instr(filestr,"buy_processed_date_id")+23
instrend=instr(instr(filestr,"buy_processed_date_id")+23,filestr,"</td>")
defstr buy_processed_date=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioopenedordersgrid.cell(5,i)=buy_processed_date

instrbegin=instr(filestr,"status_id")+11
instrend=instr(instr(filestr,"status_id")+11,filestr,"</td>")
defstr status=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioopenedordersgrid.cell(6,i)=status

instrbegin=instr(filestr,"invoice_number_buy_id")+23
instrend=instr(instr(filestr,"invoice_number_buy_id")+23,filestr,"</td>")
defstr invoice_number_buy=mid$(filestr,instrbegin,instrend-instrbegin)
portfolioopenedordersgrid.cell(7,i)=invoice_number_buy

openedpositionsnb++

filestr=mid$(filestr,instrend,len(filestr))

next i

sumamountinvlabel.caption=str$(sumaminv)

if openedpositionsnb_tmp<>openedpositionsnb then
clearopenedordersfields
openedpositionsnbincr=0
end if

end if

busystream.open("c:\qchartist\gshareinvest\isbusyopenedorderslist.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
pid=shell ("c:\qchartist\gshareinvest\get_opened_orders_list.bat",0)
chdir tmppathgsi

end if

end sub

sub accounttimersub

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusyaccountbalance.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusyorderslist.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusyopenedorderslist.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

busystream.open("c:\qchartist\gshareinvest\isbusyclosedorderslist.txt",0)
isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub

accountincr++

if accountincr>4 then
accountincr=1
end if

select case accountincr

case 1
accountbalancesub

case 2
orderslistsub

case 3
openedorderslistsub

case 4
closedorderslistsub

end select

end sub

sub pfquotetimersub

if openedpositionsnb=0 then exit sub

dim busystream as qfilestream
busystream.open("c:\qchartist\gshareinvest\isbusypfquote.txt",0)
defstr isbusy=""
while not busystream.eof
isbusy=isbusy+busystream.readline
wend
busystream.close
if val(isbusy)=1 then exit sub


dim filestream as qfilestream

if fileexists("c:\qchartist\gshareinvest\pfquote.txt")=0 then
filestream.open("c:\qchartist\gshareinvest\pfquote.txt",65535)
filestream.close
end if

defstr filestr2=""
filestream.open("c:\qchartist\gshareinvest\pfquote.txt",0)
while not filestream.eof
filestr2=filestr2+filestream.readline
wend
filestream.close

if val(filestr2)>0 and openedpositionsnbincr>0 then
portfolioopenedordersgrid.cell(8,openedpositionsnbincr)=filestr2
portfolioopenedordersgrid.cell(9,openedpositionsnbincr)=str$(val(portfolioopenedordersgrid.cell(2,openedpositionsnbincr))*val(portfolioopenedordersgrid.cell(8,openedpositionsnbincr)))
portfolioopenedordersgrid.cell(10,openedpositionsnbincr)=str$(val(portfolioopenedordersgrid.cell(9,openedpositionsnbincr))-val(portfolioopenedordersgrid.cell(4,openedpositionsnbincr)))
end if

if openedpositionsnbincr=openedpositionsnb then
defint i
defdbl sumprofit=0
for i=1 to openedpositionsnbincr
sumprofit=sumprofit+val(portfolioopenedordersgrid.cell(9,i))
next i
sumprofitlabel.caption=str$(sumprofit)
sumdifflabel.caption=str$(val(sumprofitlabel.caption)-val(sumamountinvlabel.caption))
end if

openedpositionsnbincr++

if openedpositionsnbincr>openedpositionsnb then
openedpositionsnbincr=1
end if

busystream.open("c:\qchartist\gshareinvest\isbusypfquote.txt",fmopenwrite)
busystream.writeline("1")
busystream.close

dim pid as integer
tmppathgsi=curdir$
chdir "c:\qchartist\gshareinvest"
if like(platform,"*Wine*")=0 then pid=shell ("c:\qchartist\gshareinvest\getstock.bat "+portfolioopenedordersgrid.cell(1,openedpositionsnbincr),0)
if like(platform,"*Wine*")=1 then pid=shell ("/bin/sh -c "+chr$(34)+"./getstock.sh "+portfolioopenedordersgrid.cell(1,openedpositionsnbincr)+chr$(34),0)
chdir tmppathgsi

end sub

sub clearopenedordersfields
defint i=0,j=0
for i=0 to 10
for j=1 to 100
portfolioopenedordersgrid.cell(i,j)=""
next j
next i
sumamountinvlabel.caption=""
sumprofitlabel.caption=""
sumdifflabel.caption=""
end sub

sub showorderformsub

orderform.visible=1

end sub

sub ordergetpricesub

ordergetpricebtn.enabled=0
goingtogetprice="getstockprice":busytimergetprice.enabled=1

end sub

sub openordersendsub

openorderokbtn.enabled=0
accounttimer.enabled=0
pfquotetimer.enabled=0
goingtoopenorder="getformopenorder":busytimeropenorder.enabled=1

end sub

sub closeordersendsub

closeorderokbtn.enabled=0
accounttimer.enabled=0
pfquotetimer.enabled=0
goingtocloseorder="getformcloseorder":busytimercloseorder.enabled=1

end sub

sub gshareinvest_register_sub

ShellExecute 0, "open", "http://www.gshareinvest.com/register.php", "", "", 1

end sub

$include "c:\qchartist\gshareinvest\functions.bas"

'loginform.showmodal    