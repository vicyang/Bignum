my $S = "312";
my @S = split("", $S);
my $B = 10;

printf("%b\n", $S);


my $A = 0;
for (my $i = 0; $i <= $#S; $i++ )
{
    my $t = sprintf("%b", eval("0b$A * 10") );
    $A = sprintf("%b", eval("0b$t + $S[$i]") );
    printf "%d %s %s\n",  $S[$i], $t, sprintf("%b", $S[$i]);
}

print $A;