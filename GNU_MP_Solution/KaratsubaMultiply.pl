my $A = "55551111";
my $B = "11115555";

print kmp($A, $B);

sub kmp 
{
    my ($A, $B) = @_;
    my ($A0, $A1, $B0, $B1, $sA, $sB, $C0, $C1, $C2, $C);
    my $n = length($A);
    my $k = int(($n+1)/2);
    return $A*$B if $n < 5;

    $A0 = $A % (10**$k), $A1 = int($A / 10**$k),
    $B0 = $B % (10**$k), $B1 = int($B / 10**$k);
    $C0 = kmp( $A0, $B0 );
    $C1 = kmp( $A1, $B1 );
    $C2 = kmp( abs($A0-$A1), abs($B0-$B1) );
    $sA = $A0-$A1 > 0 ? 1:-1;
    $sB = $B0-$B1 > 0 ? 1:-1;

    printf("A0,A1 = %s %s, B0,B1 = %s %s, sA,sB = %s %s\n", $A0, $A1, $B0, $B1, $sA, $sB);
    printf("%s %s %s\n", $C0, $C1, $C2);
    return $C0+($C0+$C1-$sA*$sB*$C2)*(10**$k)+$C1*(10**(2*$k));
}
