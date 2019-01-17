#include <iostream>
#include <vector>
using namespace std;

string s_plus(string a, string b);
void check(string a, string b);

int main(int argc, char *argv[] ) 
{
    string a="9999999990123456";
    string b="123456789";
    string c=s_plus(a, b);
    //check(a, b);
    cout<<c<<endl;
    return 0;
}

// plus 属于标准库函数的名称，所以加了前缀
string s_plus(string a, string b)
{
    string s(a.length(), '0');

    int la = a.length(), lb = b.length();
    int t, pool = 0, ia, ib, ic;
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
    return s;
}


void check(string a, string b)
{
    string cmd = "perl -Mbignum -e \"print " + a + "+" + b + "\"";
    system( cmd.c_str() );
    cout << endl;
}