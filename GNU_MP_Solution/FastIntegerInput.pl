my $S = "312";
my $B = 10;

my @e = map { sprintf("%b", $_) } reverse split("", $S);

my ($b, $k) = ($B, $#e+1 );
my @tmp;

while ($k > 1)
{
    printf "%d %d\n", $k, ($k/2)-1;
    if ( $k % 2 == 0) {
        @e = map {  sprintf("%b", eval( "0b".$e[$_*2] ."+". $b ."*". "0b".$e[$_*2+1] ))  } ( 0 .. ($k/2)-1 );
    } else {
        @tmp = map {  sprintf("%b", eval( "0b".$e[$_*2] ."+". $b ."*". "0b".$e[$_*2+1] ))  } ( 0 .. ($k-1)/2-1 );
        @e = (@tmp, $e[$k-1]);
    }

    printf "%s\n", join(",", @e);

    ($b, $k) = ( $b**2, int(($k+1)/2) );
}


printf "%s\n", join(",", @e);

print $A;