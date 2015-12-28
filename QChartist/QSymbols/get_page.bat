wget.exe -e robots=off -w 1 --max-redirect 1 --tries=1 --timeout=15 --dns-timeout=15 --connect-timeout=15 --read-timeout=15 --no-http-keep-alive --no-cookies -o wget_all.log --output-document=page.txt "http://finance.yahoo.com/q/cp?s=^SBF250&alpha=Z"
echo 0 > isbusy.txt
