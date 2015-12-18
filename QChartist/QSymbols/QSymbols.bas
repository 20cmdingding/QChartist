$apptype gui
$typecheck on

chdir "c:\qchartist\qsymbols"

$include "rapidq.inc"
$include "qprogress.inc"

' setting busystream to 0
dim busystream as qfilestream
busystream.open("isbusy.txt",65535)
busystream.writeline "0"
busystream.close

declare sub start_update_sub

create form as qform

caption="Update symbols lists"
height=380
width=630
icon="Net5.ico"

create start_update_btn as qbutton

onclick=start_update_sub
caption="Start update"

end create

create msglabel as qlabel

caption=""
width=form.width-130
top=5
left=100

end create

create statuslabel as qlabel

caption=""
width=form.width-10
top=30
left=0

end create

create symbolslistbox as qlistbox
top=80
left=0
width=form.Width-10
height=150
end create

create infolabel as qlabel

caption="This program updates stocks symbols and names for use with QChartist data source."
width=form.width-10
top=symbolslistbox.top+symbolslistbox.height+10
left=0

end create

create savestatusrichedit as qrichedit

width=form.width-10
top=symbolslistbox.top+symbolslistbox.height+30
left=0
scrollbars=ssboth

end create

end create

DIM bar AS qprogress
bar.Parent = form.Handle
bar.Top = 50
bar.Left = 0
bar.Width = form.Width-10
bar.Height = 25
bar.value = 0

form.showmodal

sub start_update_sub

start_update_btn.enabled=0
msglabel.caption="Please do not close this program until the update is finished."

defint ascletter
defstr letter
defint pid
dim filestream as qfilestream
DIM longcmdfile AS QFILESTREAM
defstr loadingstatuslabel
symbolslistbox.clear
savestatusrichedit.text=""

' Nasdaq
bar.value = 0
loadingstatuslabel="Loading Nasdaq symbols"
symbolslistbox.additems "-= NASDAQ SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("nasdaq.txt" , 65535)
filestream.close

ascletter=64

do
ascletter++
letter=chr$(ascletter)
statuslabel.caption=loadingstatuslabel+" with letter "+letter

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt http://eoddata.com/stocklist/NASDAQ/"+letter+".htm")
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
defstr busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
defstr pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

defint tableloc,endtableloc
defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"<TR><TH>Code</TH><TH>Name</TH>")
tablestr=mid$(pagestr,tableloc+3,len(pagestr))
defint tablelineloc,cellloc,symbolloc,nameloc
defstr symbolstr,namestr
defint istableend

istableend=0
filestream.Open("nasdaq.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td>")
tablestr=mid$(tablestr,cellloc+4,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td>")
tablestr=mid$(tablestr,cellloc+4,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*(27-(91-ascletter))/26
doevents
loop until letter="Z"
savestatusrichedit.text=savestatusrichedit.text+"- All Nasdaq symbols and names saved to nasdaq.txt"+chr$(10)

' Amex
bar.value = 0
loadingstatuslabel="Loading Amex symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= AMEX SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("amex.txt" , 65535)
filestream.close

ascletter=64

do
ascletter++
letter=chr$(ascletter)
statuslabel.caption=loadingstatuslabel+" with letter "+letter

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt http://eoddata.com/stocklist/AMEX/"+letter+".htm")
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"<TR><TH>Code</TH><TH>Name</TH>")
tablestr=mid$(pagestr,tableloc+3,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend

istableend=0
filestream.Open("amex.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td>")
tablestr=mid$(tablestr,cellloc+4,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td>")
tablestr=mid$(tablestr,cellloc+4,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*(27-(91-ascletter))/26
doevents
loop until letter="Z"
savestatusrichedit.text=savestatusrichedit.text+"- All Amex symbols and names saved to amex.txt"+chr$(10)


defint pagenb
defint lastpagenbloc
defstr lastpagenbstr,lastpagestr


' U.S. Stocks
bar.value = 0
loadingstatuslabel="Loading U.S. Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= U.S. Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("us_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=518&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("us_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All U.S. Stocks symbols and names saved to us_stocks.txt"+chr$(10)



' NYSE Stocks
bar.value = 0
loadingstatuslabel="Loading NYSE Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= NYSE Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("nyse_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=515&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("nyse_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All NYSE Stocks symbols and names saved to nyse_stocks.txt"+chr$(10)

' NASDAQ Stocks
bar.value = 0
loadingstatuslabel="Loading NASDAQ Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= NASDAQ Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("nasdaq_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=516&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("nasdaq_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All NASDAQ Stocks symbols and names saved to nasdaq_stocks.txt"+chr$(10)

' NYSE MKT Stocks
bar.value = 0
loadingstatuslabel="Loading NYSE MKT Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= NYSE MKT Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("nyse_mkt_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=517&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("nyse_mkt_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All NYSE MKT Stocks symbols and names saved to nyse_mkt_stocks.txt"+chr$(10)

' DJI Stocks
bar.value = 0
loadingstatuslabel="Loading DJI Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= DJI Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("dji_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=578&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("dji_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All DJI Stocks symbols and names saved to dji_stocks.txt"+chr$(10)

' S&P500 Stocks
bar.value = 0
loadingstatuslabel="Loading S&P500 Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= S&P500 Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("sp500_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=579&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("sp500_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All S&P500 Stocks symbols and names saved to sp500_stocks.txt"+chr$(10)

' Nasdaq100 Stocks
bar.value = 0
loadingstatuslabel="Loading Nasdaq100 Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= Nasdaq100 Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("Nasdaq100_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=580&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("Nasdaq100_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All Nasdaq100 Stocks symbols and names saved to Nasdaq100_stocks.txt"+chr$(10)

' US_ETFs Stocks
bar.value = 0
loadingstatuslabel="Loading US_ETFs Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= US_ETFs Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("US_ETFs_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=609&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("US_ETFs_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All US_ETFs Stocks symbols and names saved to US_ETFs_stocks.txt"+chr$(10)

' UK Stocks
bar.value = 0
loadingstatuslabel="Loading UK Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= UK Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("UK_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=610&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("UK_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All UK Stocks symbols and names saved to UK_stocks.txt"+chr$(10)

' UK100 Stocks
bar.value = 0
loadingstatuslabel="Loading UK100 Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= UK100 Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("UK100_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=611&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("UK100_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All UK100 Stocks symbols and names saved to UK100_stocks.txt"+chr$(10)

' UK_ETFs Stocks
bar.value = 0
loadingstatuslabel="Loading UK_ETFs Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= UK_ETFs Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("UK_ETFs_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=612&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("UK_ETFs_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All UK_ETFs Stocks symbols and names saved to UK_ETFs_stocks.txt"+chr$(10)

' Japan Stocks
bar.value = 0
loadingstatuslabel="Loading Japan Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= Japan Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("Japan_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=519&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("Japan_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All Japan Stocks symbols and names saved to Japan_stocks.txt"+chr$(10)

' TOPIX30 Stocks
bar.value = 0
loadingstatuslabel="Loading TOPIX30 Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= TOPIX30 Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("TOPIX30_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=581&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("TOPIX30_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All TOPIX30 Stocks symbols and names saved to TOPIX30_stocks.txt"+chr$(10)

' Nikkei225 Stocks
bar.value = 0
loadingstatuslabel="Loading Nikkei225 Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= Nikkei225 Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("Nikkei225_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=589&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("Nikkei225_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All Nikkei225 Stocks symbols and names saved to Nikkei225_stocks.txt"+chr$(10)

' Japan_ETFs Stocks
bar.value = 0
loadingstatuslabel="Loading Japan_ETFs Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= Japan_ETFs Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("Japan_ETFs_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=613&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("Japan_ETFs_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All Japan_ETFs Stocks symbols and names saved to Japan_ETFs_stocks.txt"+chr$(10)

' German Stocks
bar.value = 0
loadingstatuslabel="Loading German Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= German Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("German_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=521&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("German_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All German Stocks symbols and names saved to German_stocks.txt"+chr$(10)

' DAX Stocks
bar.value = 0
loadingstatuslabel="Loading DAX Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= DAX Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("DAX_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=560&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("DAX_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All DAX Stocks symbols and names saved to DAX_stocks.txt"+chr$(10)

' MDAX Stocks
bar.value = 0
loadingstatuslabel="Loading MDAX Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= MDAX Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("MDAX_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=586&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("MDAX_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All MDAX Stocks symbols and names saved to MDAX_stocks.txt"+chr$(10)

' Polish Stocks
bar.value = 0
loadingstatuslabel="Loading Polish Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= Polish Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("Polish_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=523&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("Polish_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All Polish Stocks symbols and names saved to Polish_stocks.txt"+chr$(10)

' WIG30 Stocks
bar.value = 0
loadingstatuslabel="Loading WIG30 Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= WIG30 Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("WIG30_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=582&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("WIG30_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All WIG30 Stocks symbols and names saved to WIG30_stocks.txt"+chr$(10)

' Hungarian Stocks
bar.value = 0
loadingstatuslabel="Loading Hungarian Stocks symbols"
symbolslistbox.additems ""
symbolslistbox.additems "-= Hungarian Stocks SYMBOL,NAME =-"
symbolslistbox.additems ""

filestream.Open("Hungarian_stocks.txt" , 65535)
filestream.close

pagenb=0

do
pagenb++
statuslabel.caption=loadingstatuslabel+" page "+str$(pagenb)

filestream.Open("isbusy.txt" , fmOpenWrite)
filestream.WriteLine("1")
filestream.Close    

longcmdfile.Open("get_page.bat" , 65535)
longcmdfile.WriteLine("wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "+chr$(34)+"http://stooq.com/t/?i=522&v=0&l="+str$(pagenb)+chr$(34))
longcmdfile.WriteLine("echo 0 > isbusy.txt")
longcmdfile.Close
pid = SHELL("get_page.bat" , 1)

do
filestream.Open("isbusy.txt" , 0)
busystr = ""
WHILE NOT filestream.eof
    busystr = busystr + filestream.ReadLine
WEND
filestream.Close    
sleep 1
doevents
loop until val(busystr)=0

filestream.Open("page.txt" , 0)
pagestr = ""
WHILE NOT filestream.eof
    pagestr = pagestr + filestream.ReadLine
WEND
filestream.Close 

'defint tableloc,endtableloc
'defstr tablestr,tablestrtmp
tableloc=instr(pagestr,"Symbol</a></th>")
tablestr=mid$(pagestr,tableloc,len(pagestr))
'defint tablelineloc,cellloc,symbolloc,nameloc
'defstr symbolstr,namestr
'defint istableend
if pagenb=1 then
lastpagenbloc=instr(pagestr,">Last</a>")
lastpagestr=mid$(pagestr,1,lastpagenbloc-1)
lastpagenbloc=rinstr(lastpagestr,"=")
lastpagenbstr=mid$(lastpagestr,lastpagenbloc+1,len(lastpagestr))
end if

istableend=0
filestream.Open("Hungarian_stocks.txt" , 2)
filestream.position=filestream.size
do
tablelineloc=instr(tablestr,"<tr")
tablestr=mid$(tablestr,tablelineloc+3,len(tablestr))
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolloc=instr(tablestr,">")
tablestr=mid$(tablestr,symbolloc+1,len(tablestr))
symbolstr=mid$(tablestr,1,instr(tablestr,"<")-1)
cellloc=instr(tablestr,"<td")
tablestr=mid$(tablestr,cellloc+3,len(tablestr))
cellloc=instr(tablestr,">")
tablestr=mid$(tablestr,cellloc+1,len(tablestr))
namestr=mid$(tablestr,1,instr(tablestr,"</td>")-1)
filestream.writeline (symbolstr+","+namestr)
symbolslistbox.additems symbolstr+","+namestr
symbolslistbox.itemindex=symbolslistbox.itemcount-1
tablelineloc=instr(tablestr,"<tr")
endtableloc=instr(tablestr,"</table>")
if tablelineloc=0 then istableend=1
if tablelineloc>0 then
if endtableloc<tablelineloc then istableend=1
end if
doevents
loop until istableend=1
filestream.close
bar.value = 100*pagenb/val(lastpagenbstr)
doevents
loop until pagenb=val(lastpagenbstr)
savestatusrichedit.text=savestatusrichedit.text+"- All Hungarian Stocks symbols and names saved to Hungarian_stocks.txt"+chr$(10)

' finishing
msglabel.caption="Update successfully done, you can close the program."
start_update_btn.enabled=1

end sub