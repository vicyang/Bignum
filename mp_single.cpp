// 大数*单个数，仅针对正整数
// 523066680/vicyang
// 2019-01

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

string s_mp_single(const string& a, const string& b);
vector<int> vec_mp_single(const vector<int> &a, const vector<int> &b);

string vec2str( const vector<int> &vec )
{
    const int base = 1000000;
    string s("");
    s += to_string( vec[0] );
    for ( int it = 1; it < vec.size(); it++ )
        s += to_string(vec[it]+base).substr(1,6);
    return s;
}

void check(const vector<int> &va, const vector<int> &vb, const string &op)
{
    string a = vec2str(va);
    string b = vec2str(vb);
    string cmd = "perl -Mbignum -e \"print " + a + op + b + "\"";
    system( cmd.c_str() );
    cout << " <- check " << endl;
}

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
        
    vector<int> va{999,999999};
    vector<int> vb{9};
    check(va, vb, "*");
    vector<int> vc = vec_mp_single(va, vb);
    cout << vec2str(vc) << endl;
    
    auto stage1 = chrono::system_clock::now();
    va.assign( 1700000, 999999 );
    vb.assign( 1, 8 );
    for (int i = 0; i < 10; i++) vec_mp_single(va, vb);
    auto stage2 = chrono::system_clock::now();
    diff = stage2-stage1;
    cout << "Stage 2, Time Used: " << diff.count() << " s" << endl;
    return 0;
}

// vector作为参数
vector<int> vec_mp_single(const vector<int> &a, const vector<int> &b)
{
    static int ia; // iter
    const int base = 1000000;
    //如果b是0，直接返回0
    if ( b[0] == 0 ) return vector<int>{0};
    vector<int> c( a.size() );
    int t, pool=0, ib=b.size()-1;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = a[ia] * b[0] + pool;
        c[ia] = t%base, pool = t/base;
    }
    if ( pool > 0 ) c.insert(c.begin(), pool);
    return c;
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
