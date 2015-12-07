wget --output-document=Google_quotes2.txt -o connection_status2.log "http://www.google.com/finance/getprices?i=%1&p=%2d&f=d,o,h,l,c,v&df=cpct&q=%3"
rem i=tf in seconds
rem p=days back e.g. 10d
rem q=SYMBOL
echo 0 > isbusy2.txt