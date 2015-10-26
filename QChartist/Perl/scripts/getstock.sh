echo 1 > isbusy.txt
./stock $1 $2 > quote.txt
echo 0 > isbusy.txt
