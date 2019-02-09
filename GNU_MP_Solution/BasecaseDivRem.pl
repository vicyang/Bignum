=info
<MCA> P14 Naive Division
BasecaseDivRem 假设B的高位数字 B[n-1] >= BASE/2
如果B还未normalized，我们计算 A' = 2^k*A 以及 B' = 2^k*B
来获得归一化的B'

假设
$A = 987654321, $B = 45678;
因为 $B[0] < 5，对其执行 normalized
$A = $A*2, $B = $B * 2
=cut

use bigint;
our $BASE = 10;
my ($A, $B) = ("987654321", "45678");

normalized(\$A, \$B);
BasecaseDivRem($A, $B);
check($A, $B);

sub BasecaseDivRem
{
    my ($A, $B) = @_;
    my ($LA, $LB) = (length($A), length($B) );
    my @q;
    my $m = $LA - $LB;
    my $n = $LB;
    my @Ar = reverse split("", $A);
    my @Br = reverse split("", $B);

    if ( $A >= $BASE**$m*$B ) { $q[$m] = 1; $A -= ($BASE**$m) * $B; }
    else { $q[$m] = 0; }

    printf "A: %s, B: %s\n", $A, $B;
    my $j;
    @Ar = reverse split("", $A);
    for ($j = $m-1; $j >= 0; $j--)
    {
        $qx = int( ($Ar[$n+$j]*$BASE + $Ar[$n+$j-1] )/ $Br[$n-1]);
        $q[$j] = $qx < $BASE-1 ? $qx : $BASE-1;
        printf "%d %d %d %d\n", $Ar[$n+$j], $Ar[$n+$j-1], $Br[$n-1], $q[$j];
        $A -= $q[$j] * ($BASE**$j) * $B;
        while ( $A < 0 )
        {
            $q[$j] -= 1;
            $A = $A + ($BASE**$j)*$B;
        }
        @Ar = reverse split("", $A);
    }
    printf "%s\n", join(",", @q );

}

sub normalized
{
    my ($A, $B) = @_;
    while ( substr($$B, 0, 1) < int($BASE/2) )
    {
        $$B *= 2;
        $$A *= 2;
    }
}

sub check
{
    printf "Check: %s\n", int($A/$B);
}