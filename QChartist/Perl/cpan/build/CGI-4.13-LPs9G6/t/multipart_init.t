use Test::More 'no_plan';

use CGI;

my $q = CGI->new;

my $sv = $q->multipart_init;
like( $sv, qr|Content-Type: multipart/x-mixed-replace;boundary="------- =.*?; charset=ISO-8859-1|, 'multipart_init(), basic');

$sv = $q->multipart_init(-charset=>'utf-8');
like( $sv, qr|Content-Type: multipart/x-mixed-replace;boundary="------- =.*?; charset=utf-8|, 'multipart_init(), -charset');

like( $sv, qr/$CGI::CRLF$/, 'multipart_init(), ends in CRLF' );

$sv = $q->multipart_init( 'this_is_the_boundary' );
like( $sv, qr/boundary="this_is_the_boundary"/, 'multipart_init("simple_boundary")' );
$sv = $q->multipart_init( -boundary => 'this_is_another_boundary' );
like($sv,
     qr/boundary="this_is_another_boundary"/, "multipart_init( -boundary => 'this_is_another_boundary')");

{
    my $sv = $q->multipart_init;
    my $sv2 = $q->multipart_init;
    isnt($sv,$sv2,"due to random boundaries, multiple calls produce different results");
}
