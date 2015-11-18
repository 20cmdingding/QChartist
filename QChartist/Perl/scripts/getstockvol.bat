echo 1 > isbusy.txt
stockvol.exe %1 %2 > quote.txt
echo 0 > isbusy.txt