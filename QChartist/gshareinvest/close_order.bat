curl -b cookies.txt -c cookies.txt -o close_order_result.html -d "invoice_number=%1&order_id=%2&confirm_btn=" http://www.gshareinvest.com/account.php?close_order
echo 0 > isbusycloseorder.txt