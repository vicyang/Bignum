// BasecaseMultiply - C++ string
// 523066680/vicyang
// 2019-02

#include <iostream>
#include <string>
#include <stdio.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

string s_mp_single(const string& a, char b);
string s_plus(const string& a, const string& b);
string BasecaseMultiply( const string& a, const string& b);
string zeros(10000, '0');
void time_used(system_clock::time_point& time_a);

int main(int argc, char *argv[] ) 
{
    string a;
    string b;
    a.assign(9, '1');
    b.assign(9, '1');
    string c = BasecaseMultiply(a, b);
    cout << c << endl;

    system_clock::time_point start = system_clock::now();
    a.assign(10000, '9'); 
    b.assign(10000, '1');
    for (int i=0; i<10; i++) c = BasecaseMultiply(a,b);
    time_used(start);

    return 0;
}

string BasecaseMultiply( const string& a, const string& b)
{
    register const char *pb = b.data();
    string c;
    string t;
    c = s_mp_single( a, b[0] );
    for (int j = 1; j < a.length(); j++)
    {
        t = s_mp_single(a, pb[j]);
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
    register const char *pa = a.data();
    static int idx;
    string s;
    //如果b是0，直接返回0
    if ( b == '0' ) return "0";
    s.assign(a.length(), '0');
    int t, pool = 0, numb = b - '0';
    for ( idx = a.length()-1; idx >= 0; idx-- )
    {
        t = (pa[idx]-'0') * numb + pool;
        s[idx] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

// plus 属于标准库函数的名称，所以加了前缀
// 备注：此函数假设a.len > b.len
string s_plus(const string& a, const string& b)
{
    register const char *pa = a.data();
    register const char *pb = b.data();
    static int ia;
    string s( a.length(), '0');
    int t, pool=0, ib=b.length()-1;
    for (ia = a.length()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]-'0') + (pb[ib--]-'0') + pool
                    : (pa[ia]-'0') + pool;
        s[ia] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

void time_used(system_clock::time_point& time_a) {
    duration<double> diff;
    diff = chrono::system_clock::now() - time_a;
    cout << "Time used: " << diff.count() << endl;
    time_a = chrono::system_clock::now();
}