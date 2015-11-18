   use Finance::Quote;
   $q = Finance::Quote->new;

   $q->timeout(60);

#   $conversion_rate = $q->currency("AUD","USD");
#print $conversion_rate
#   $q->set_currency("EUR");  # Return all info in Euros.

#   $q->require_labels(qw/price date high low volume/);

#   $q->failover(1);     # Set failover support (on by default).

#   %quotes  = $q->fetch("nasdaq",@stocks);
#   $hashref = $q->fetch("nyse",@stocks);

#    %info = $q->fetch("usa","IBM");

#%info = $q->fetch("usa","IBM","MSFT");
#    print "IBM:".$info{"IBM","last"}."\n";
#print "MSFT:".$info{"MSFT","last"}."\n";

%info = $q->fetch($ARGV[0],$ARGV[1]);
print $info{$ARGV[1],"last"}.",".$info{$ARGV[1],"volume"}."\n";