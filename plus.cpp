#include <iostream>
#include <chrono>
using namespace std;

string s_plus(string a, string b);
void check(string a, string b);

int main(int argc, char *argv[] ) 
{
    auto start = chrono::system_clock::now();
    string a(10000, '9');
    string b(10000, '9');
    string c=s_plus(a, b);
    //check(a, b);
    for (int i = 0; i < 10000; i++) s_plus(a, b);
    auto end = chrono::system_clock::now();
    chrono::duration<double> diff = end-start;
    //cout<<c<<endl;
    cout << "Time Used: " << diff.count() << " s" << endl;
    
    return 0;
}

// plus 属于标准库函数的名称，所以加了前缀
string s_plus(string a, string b)
{
    string s( a.length(), '0');
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