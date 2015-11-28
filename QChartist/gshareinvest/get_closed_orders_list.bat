curl -b cookies.txt -c cookies.txt -o closed_orders_list.html "http://www.gshareinvest.com/account.php?orders_history&desc&lineslimit=100&closed_only"
echo 0 > isbusyclosedorderslist.txt