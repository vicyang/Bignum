
my $m = "123456789";

my $u = $m/2+1;
my $t;
my $s;
do
{
    $s = $u;
    $t = $s + int($m/$s);
    $u = int($t/2);
} until ( $u >= $s );


print $s;