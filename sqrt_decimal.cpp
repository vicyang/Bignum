// SQRT - Decimal Solution (Only for Positive Integer Number)
// 523066680/vicyang
// 2019-01

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
typedef unsigned long long int ULL;
const ULL BASE = 100000000;
const ULL LEN = 8;

string s_mp_single(const string& a, const string& b);
string s_plus(const string& a, const string& b);
string s_minus(const string& a, const string& b);
int s_cmp(const string &a, const string &b );
string sqrt_decimal(ULL num, int precision);

vector<int> vec_mp_single(const vector<int> &a, const vector<int> &b);
vector<int> vec_minus(const vector<int> &a, const vector<int> &b);
string vec2str( const vector<int> &vec );
void check(const vector<int> &va, const vector<int> &vb, const string &op);

int main(int argc, char *argv[] ) 
{
    chrono::duration<double> diff;
    auto stage0 = chrono::system_clock::now();

    vector<ULL> num{2};
    sqrt_decimal(num[0], 100);
    auto stage1 = chrono::system_clock::now();
    
    diff = stage1-stage0;
    cout << "Time Used: " << diff.count() << " s" << endl;
    return 0;
}

string sqrt_decimal(ULL num, int precision)
{
    bool dec_loop = 1;
    int prec = 0, est, mp, mid, cmp, dbmid;



    cout << endl;
    return "";
}

// vec multiply to one word
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

// vec_minus 设 a.len > b.len
vector<int> vec_minus(const vector<int> &a, const vector<int> &b)
{
    static int ia; // iter
    const int base = 1000000;
    vector<int> c( a.size() );
    int t, cut=0, ib=b.size()-1, zero=0;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]) - (b[ib--]) + cut
                    : (a[ia]) + cut;
        t < 0 ? t += base, cut = -1 : cut = 0;
        zero = t == 0 ? zero+1 : 0;  // 此判断须独立，t有可能+base后才为0
        c[ia] = t;
    }
    c.erase(c.begin(), c.begin()+zero);
    return c;
}

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

// bignum * single num (str*str)
string s_mp_single(const string& a, const string& b)
{
    static int idx;
    string s;
    //如果b是0，直接返回0
    if ( b[0] == '0' ) return "0";
    if ( b[0] == '1' ) return a;
    s.assign(a.length(), '0');
    int t, pool = 0, numb = b[0]-'0';
    for ( idx = a.length()-1; idx >= 0; idx-- )
    {
        t = (a[idx]-'0') * numb + pool;
        s[idx] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

// 大数减法 字符串操作, 暂时假设 a >= b
string s_minus(const string& a, const string& b)
{
    const char* pa = a.data();
    const char* pb = b.data();
    static int ia;
    if ( a.compare(b) == 0 ) return "0";
    string s( a.length(), '0');
    int t, v, cut=0, ib=b.length()-1, zero=0;
    for (ia = a.length()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]-'0') - (pb[ib--]-'0') - cut 
                    : (pa[ia]-'0') - cut;
        cut = t < 0 ? 1 : 0;
        v = t + '0' + cut*10, s[ia] = v;
        v == '0' ? zero++ : zero=0;
    }
    if (zero > 0) s.erase(0, zero);
    return s;
}

int s_cmp(const string &a, const string &b )
{
    if ( a.length() > b.length() ) return 1;
    else if ( a.length() < b.length() ) return -1;
    else return a.compare(b);
}
