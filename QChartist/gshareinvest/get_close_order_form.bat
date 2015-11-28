curl -b cookies.txt -c cookies.txt -o close_order_form.html "http://www.gshareinvest.com/account.php?close_order&order_id=%1"
echo 0 > isbusycloseorder.txt