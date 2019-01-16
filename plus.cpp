#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[] ) 
{
    string a="9876543210123456";
    string b="123456789";
    //string c( a.length()+1, '0');
    vector<short> c;

    string cmd = "perl -Mbignum -e \"print " + a + "+" + b + "\"";
    system( cmd.c_str() );
    cout << endl;

    int la = a.length(), lb = b.length();
    int t, pool, ia, ib, ic;
    pool = 0;
    for (int iter = 0; iter < la; iter++ )
    {
        ia = la-iter-1, ib = lb-iter-1;
        t = a[ia]-'0' + pool;
        if (ib >= 0) 
            t = (a[ia]-'0') + (b[ib] - '0') + pool;
        else
            t = (a[ia]-'0') + pool;

        c.push_back( t%10 );
        pool = t/10;
        cout << c[iter] << ",";
    }
    //cout<<c<<endl;
    return 0;
}
