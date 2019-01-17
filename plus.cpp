#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[] ) 
{
    string a="9999999990123456";
    string b="123456789";
    string s(a.length(), '0');

    string cmd = "perl -Mbignum -e \"print " + a + "+" + b + "\"";
    system( cmd.c_str() );
    cout << endl;

    int la = a.length(), lb = b.length();
    int t, pool, ia, ib, ic;
    pool = 0;
    for (int iter = 0; iter < la; iter++ )
    {
        ia = la-iter-1, ib = lb-iter-1, t = a[ia]-'0' + pool;
        if (ib >= 0) 
            t = (a[ia]-'0') + (b[ib] - '0') + pool;
        else
            t = (a[ia]-'0') + pool;

        s[ a.length()-iter-1 ] = t % 10 + '0';
        pool = t/10;
    }

    if ( pool > 0 ) s.insert(0, 1, '1');

    cout<<s<<endl;
    return 0;
}
