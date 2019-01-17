#include <iostream>
#include <chrono>
using namespace std;

string s_plus(string& a, string& b);
void check(string a, string b);

int main(int argc, char *argv[] ) 
{
    auto start = chrono::system_clock::now();
    string a(10000, '9');
    string b(10000, '9');
    string c=s_plus(a, b);
    //check(a, b);
    //耗时测试
    for (int i = 0; i < 1000; i++) s_plus(a, b);
    auto end = chrono::system_clock::now();
    chrono::duration<double> diff = end-start;

    //其他测试
    a="99999", b="9999";
    c=s_plus( a, b );
    cout << c << endl;
    cout << "Time Used: " << diff.count() << " s" << endl;
    return 0;
}

// plus 属于标准库函数的名称，所以加了前缀
string s_plus(string& a, string& b)
{
    static int iter;
    string s( a.length(), '0');
    int la = a.length(), lb = b.length();
    int t, pool=0, ia=la-1, ib=lb-1;
    for (iter = 0; iter < la; iter++ )
    {
        if (ib >= 0)
            t = (a[ia]-'0') + (b[ib--]-'0') + pool;
        else
            t = (a[ia]-'0') + pool;
        s[ia--] = t%10 + '0', pool = t/10;
    }

    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}


void check(string a, string b)
{
    string cmd = "perl -Mbignum -e \"print " + a + "+" + b + "\"";
    system( cmd.c_str() );
    cout << endl;
}