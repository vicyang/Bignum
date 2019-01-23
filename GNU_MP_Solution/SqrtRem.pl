
my ($s, $r) = BasecaseSqrtRem(10);
print "$s $r\n";

my ($q, $u) = DivRem(11, 3);
print "$q $u\n";

($s,$r) = SqrtRem("12345678987654321");
printf "%d %d\n", $s, $r;

sub SqrtRem
{
    my ($num) = @_;
    my $n = length($num);
    my $e = int(($n-1)/4);
    if ( $e == 0 ) {return BasecaseSqrtRem( $num );}
    # 表达式分解
    printf "n %d, e %d\n", $n, $e;
    my @A;
    for (1..3) {
        push @A, substr($num, -$_*$e, $e);
    };
    push @A, substr($num, 0, $n-$e*3);
    printf "%s\n", join(",", @A);
    my ($s, $r) = SqrtRem( $A[3]*10**$e + $A[2] );
    my ($q, $u) = DivRem( $r*10**$e+$A[1], $s*2 );
    
    $S = $s*10**$e + $q;
    $R = $u*10**$e + $A[0] - $q*$q;

    printf "s: %d, r: $u\n", $s, $r;
    printf "q: %d, u: $u\n", $q, $u;
    printf "S: %d, R: $u\n", $S, $R;
    if ($R < 0) {
        $R = $R + $S*2 - 1, $S -= 1;
    }
    return ($S, $R);
}

sub BasecaseSqrtRem
{
    my $num = shift;
    my $s = int(sqrt($num));
    my $r = $num - $s*$s;
    return ( $s, $r );
}

sub DivRem
{
    my ($a, $b) = @_;
    my $q = int($a/$b);
    my $u = $a-$q*$b;
    return ($q, $u);
}
