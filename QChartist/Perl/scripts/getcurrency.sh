echo 1 > isbusy.txt
./currency $1 $2 > quote.txt
echo 0 > isbusy.txt
