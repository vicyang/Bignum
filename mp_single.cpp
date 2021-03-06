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
    chrono::duration<double> diff;
    auto stage0 = chrono::system_clock::now();
    string a(10000000, '9');
    string b("9");
    string c;
    // 耗时测试 1
    {
        for (int i = 0; i < 10; i++) s_mp_single(a, b);
        diff = chrono::system_clock::now()-stage0;
        cout << "Time Used: " << diff.count() << " s" << endl;
    }

    auto stage1 = chrono::system_clock::now();
    int n;
    // 耗时测试 2
    {
        n = stoi(b);
        for (int i = 0; i < 10; i++) s_mp_int(a, n);
        diff = chrono::system_clock::now()-stage1;
        cout << "Time Used: " << diff.count() << " s" << endl;
    }

    // 其他测试
    a="999";
    c = s_mp_int( a, n );
    //check(a, b);
    //cout << c << endl;
    
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
    int t, pool = 0, numb = b[0] - '0';
    for ( idx = a.length()-1; idx >= 0; idx-- )
    {
        t = (a[idx]-'0') * numb + pool;
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