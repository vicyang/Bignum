// BasecaseMultiply - C++
// 523066680/vicyang
// 2019-01

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
typedef unsigned long long ULL;

string vec2str( const vector<ULL> &vec );
vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b);
vector<ULL> BasecaseMultiply( const vector<ULL>& a, const vector<ULL>& b);
vector<ULL> vec_mp_single( const vector<ULL>& a, int b);
void shift( vector<ULL>& vec, int n );

const unsigned long long BASE = 100000000;
const int MAXLEN = 8;

void check(const vector<ULL> &va, const vector<ULL> &vb, const string &op)
{
    string a = vec2str(va);
    string b = vec2str(vb);
    string cmd = "perl -Mbignum -e \"print " + a + op + b + "\"";
    system( cmd.c_str() );
    cout << " <- check " << endl;
}

int main(int argc, char *argv[] ) 
{
    vector<ULL> a{777, 0, 12345678};
    vector<ULL> b{6, 99999999, 99999999};
    vector<ULL> c;
    check( a, b, "*" );
    c = BasecaseMultiply( a, b );
    cout << vec2str(c);
    return 0;
}

vector<ULL> vec_mp_single( const vector<ULL>& a, int b)
{
    vector<ULL> c( a.size() );
    if ( b == 0 ) { return vector<ULL>{0}; }
    ULL pool = 0, v;
    for ( int i = a.size()-1; i >=0 ; i-- ) {
        v = a[i] * b + pool;
        c[i] = v % BASE, pool = v / BASE;
    }
    if (pool > 0) c.insert( c.begin(), pool );
    return c;
}

// 参数：向量引用、 前移的段数（也许需要考虑vec为0的情况）
void shift( vector<ULL>& vec, int n )
{
    for (int i = 1; i <= n; i++) vec.push_back(0);
}

// 假设 b.size() >= a.size()
vector<ULL> BasecaseMultiply( const vector<ULL>& a, const vector<ULL>& b)
{
    vector<ULL> c;
    vector<ULL> t;
    int bi = b.size() - 1, indent = 1;
    c = vec_mp_single( a, b[bi--] );
    while ( bi >= 0 )
    {
        if ( b[bi] > 0 )
        {
            t = vec_mp_single(a, b[bi]);
            shift(t, indent);
            c = vec_plus(t, c);
        }
        bi--, indent++;
    }
    return c;
}

// 测试vector作为参数
vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b)
{
    static int ia; // iter
    vector<ULL> c( a.size() );
    int t, pool=0, ib=b.size()-1;
    int v, r;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]) + (b[ib--]) + pool
                    : (a[ia]) + pool;
        c[ia] = t % BASE, pool = t/BASE;
    }
    if ( pool > 0 ) c.insert(c.begin(), pool);
    return c;
}

string vec2str( const vector<ULL> &vec )
{
    string s("");
    s += to_string( vec[0] );
    for ( int it = 1; it < vec.size(); it++ )
        s += to_string(vec[it]+BASE).substr(1, MAXLEN);
    return s;
}