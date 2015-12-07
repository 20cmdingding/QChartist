function gsi_isconnected() as integer
if loginstatuslabel.caption="Connected" then 
result=1
else 
result=0
end if
end function

function gsi_login(username as string,password as string) as integer
'loginform.visible=1
if loginstatuslabel.caption="Connected" then
result=0
exit sub
end if
usernameloginedit.text=username
passwordedit.text=password


if usernameloginedit.text="" or passwordedit.text="" then 
'showmessage "Enter a valid username and password"
result=0
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
gsi_quiet=1
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


while trying_to_connect=1
doevents
wend
gsi_quiet=0
if loginstatuslabel.caption="Connected" then 
result=1
else 
result=0
end if

end function

function gsi_logout() as integer

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

while not loginstatuslabel.caption="Disconnected"
doevents
wend
result=1

end function

function gsi_order_buy(symbol as string,quantity as integer) as integer

if loginstatuslabel.caption<>"Connected" then
result=0
exit sub
end if

if openorderokbtn.enabled=0 then 
result=0
exit sub
end if

gsi_quiet=1
ordersymboledit.text=symbol
orderqtyedit.text=str$(quantity)
openorderokbtn.enabled=0
accounttimer.enabled=0
pfquotetimer.enabled=0
goingtoopenorder="getformopenorder":busytimeropenorder.enabled=1

while openorderokbtn.enabled=0
doevents
wend
gsi_quiet=0
result=val(last_opened_order_id)

end function

function gsi_order_sell(order_id as integer) as integer

if loginstatuslabel.caption<>"Connected" then
result=0
exit sub
end if

if closeorderokbtn.enabled=0 then 
result=0
exit sub
end if

gsi_quiet=1
closeordernbedit.text=str$(order_id)

closeorderokbtn.enabled=0
accounttimer.enabled=0
pfquotetimer.enabled=0
goingtocloseorder="getformcloseorder":busytimercloseorder.enabled=1

while closeorderokbtn.enabled=0
doevents
wend
gsi_quiet=0
result=last_response_order_close

end function