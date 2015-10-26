   use Finance::Quote;
   $q = Finance::Quote->new;

   $q->timeout(60);

#$numArgs = $#ARGV + 1;
#print "thanks, you gave me $numArgs command-line arguments.\n";

$conversion_rate = $q->currency($ARGV[0],$ARGV[1]);
print $conversion_rate."\n";