// 大数*单个数，仅针对正整数
// 523066680/vicyang
// 2019-01

#include <iostream>
#include <chrono>
using namespace std;

string s_mp_single(const string& a, const string& b);
string s_mp_int(const string& a, int b);
void check(string a, string b);

int main(int argc, char *argv[] ) 
{
    auto start = chrono::system_clock::now();
    string a(10000000, '9');
    string b("9");
    string c=s_mp_single(a, b);
    // //耗时测试
    //for (int i = 0; i < 10; i++) s_mp_single(a, b);
    auto end = chrono::system_clock::now();
    chrono::duration<double> diff = end-start;
    
    //其他测试
    a="999999";
    b="9";
    int n = stoi(b);
    c = s_mp_int( a, n );
    //check(a, b);
    //cout << c << endl;
    cout << "Time Used: " << diff.count() << " s" << endl;
    return 0;
}

// bignum * single num (str * int)
string s_mp_int(const string& a, int b)
{
    static int idx;
    string s;
    //如果b是0，直接返回0
    if ( b == 0 ) return "0";
    s.assign(a.length(), '0');
    int t, pool = 0;
    for ( idx = a.length()-1; idx >= 0; idx-- )
    {
        t = (a[idx]-'0') * b + pool;
        s[idx] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

// bignum * single num (str*str)
string s_mp_single(const string& a, const string& b)
{
    static int idx;
    string s;
    //如果b是0，直接返回0
    if ( b[0] == '0' ) return "0";
    s.assign(a.length(), '0');
    int t, pool = 0;
    for ( idx = a.length()-1; idx >= 0; idx-- )
    {
        t = (a[idx]-'0') * (b[0] - '0') + pool;
        s[idx] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

void check(string a, string b)
{
    string cmd = "perl -Mbignum -e \"print " + a + "*" + b + "\"";
    system( cmd.c_str() );
    cout << endl;
}