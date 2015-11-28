curl -b cookies.txt -c cookies.txt -o opened_orders_list.html "http://www.gshareinvest.com/account.php?orders_history&desc&lineslimit=100&opened_only"
echo 0 > isbusyopenedorderslist.txt