echo 1 > isbusy.txt
./stockvol $1 $2 > quote.txt
echo 0 > isbusy.txt
