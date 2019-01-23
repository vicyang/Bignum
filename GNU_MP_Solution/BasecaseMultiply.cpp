#include <iostream>
#include <string>
#include <stdio.h>
#include <chrono>
using namespace std;

string s_mp_single(const string& a, char b);
string s_plus(const string& a, const string& b);
string BasecaseMultiply( const string& a, const string& b);
string zeros(10000, '0');

int main(int argc, char *argv[] ) 
{
    string a;
    string b;
    a.assign(5, '1');
    b.assign(5, '1');
    string c = BasecaseMultiply(a, b);
    cout << c;
    return 0;
}

string BasecaseMultiply( const string& a, const string& b)
{
    string c;
    string t;
    c = s_mp_single( a, b[0] );
    for (int j = 1; j < a.length(); j++)
    {
        t = s_mp_single(a, b[j]);
        if ( t.compare("0") != 0 ) {
            t = t + zeros.substr(0, j);
        }
        c = s_plus( t, c ); // t is longer than c
    }
    return c;
}

// bignum * single num (str * str (one word) )
string s_mp_single(const string& a, char b)
{
    static int idx;
    string s;
    //如果b是0，直接返回0
    if ( b == '0' ) return "0";
    s.assign(a.length(), '0');
    int t, pool = 0, numb = b - '0';
    for ( idx = a.length()-1; idx >= 0; idx-- )
    {
        t = (a[idx]-'0') * numb + pool;
        s[idx] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

// plus 属于标准库函数的名称，所以加了前缀
// 备注：此函数假设a.len > b.len
string s_plus(const string& a, const string& b)
{
    static int ia;
    string s( a.length(), '0');
    int t, pool=0, ib=b.length()-1;
    for (ia = a.length()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]-'0') + (b[ib--]-'0') + pool
                    : (a[ia]-'0') + pool;
        s[ia] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}
