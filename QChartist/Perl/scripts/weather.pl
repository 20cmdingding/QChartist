    use WWW::Weather::Yahoo;
#    my $yw = WWW::Weather::Yahoo->new( $location, 'c' );#by city name
#   my $yw = WWW::Weather::Yahoo->new( 'São Paulo, SP', 'f' );#by city name
#   my $yw = WWW::Weather::Yahoo->new( 455827 , 'c' );        #by woeid
#    print $yw->{ _weather }{location_city}."\n";
#    print $yw->{ _weather }{location_region}."\n";       
#    print $yw->{ _weather }{location_country}."\n";
#    print $yw->{ _weather }{unit_temperature}."\n";
#    print $yw->{ _weather }{unit_distance};
#    print $yw->{ _weather }{unit_pressure};
#    print $yw->{ _weather }{unit_speed};
#    print $yw->{ _weather }{wind_chill};
#    print $yw->{ _weather }{wind_direction};
#    print $yw->{ _weather }{wind_speed};
#    print $yw->{ _weather }{atmosphere_humidity};
#    print $yw->{ _weather }{atmosphere_visibility};
#    print $yw->{ _weather }{atmosphere_pressure};
#    print $yw->{ _weather }{atmosphere_rising};
#    print $yw->{ _weather }{astronomy_sunrise};
#    print $yw->{ _weather }{astronomy_sunset};
#    print $yw->{ _weather }{location_lat};
#    print $yw->{ _weather }{location_lng};
#    print $yw->{ _weather }{condition_text};
#    print $yw->{ _weather }{condition_code};
#    print $yw->{ _weather }{condition_temp}."\n";
#    print $yw->{ _weather }{condition_date}."\n";
#    print $yw->{ _weather }{condition_img_src};
#    print $yw->{ _weather }{forecast_tomorrow_day};
#    print $yw->{ _weather }{forecast_tomorrow_date};
#    print $yw->{ _weather }{forecast_tomorrow_low};
#    print $yw->{ _weather }{forecast_tomorrow_high};
#    print $yw->{ _weather }{forecast_tomorrow_text};
#    print $yw->{ _weather }{forecast_tomorrow_code};


$numArgs = $#ARGV + 1;
#print "thanks, you gave me $numArgs command-line arguments.\n";

foreach $argnum (0 .. $#ARGV) {

#   print "$ARGV[$argnum]";
my $location = WWW::Weather::Yahoo->new( $ARGV[$argnum], 'c' );
print $ARGV[$argnum]." temperature: ".$location->{ _weather }{condition_temp}."\n";


}
