// BasecaseMultiply - C++
// 523066680/vicyang
// 2019-01

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ULL;

string vec2str( const vector<ULL> &vec );
vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b);
vector<ULL> BasecaseMultiply( const vector<ULL>& a, const vector<ULL>& b);
vector<ULL> vec_mp_single( const vector<ULL>& a, ULL b);
void shift( vector<ULL>& vec, int n );
void time_used(system_clock::time_point& time_a);

const ULL BASE = 100000000;
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
    system_clock::time_point start;
    vector<ULL> a{777, 0, 12345678};
    vector<ULL> b{6, 99999999, 99999999};
    vector<ULL> c;
    check( a, b, "*" );
    c = BasecaseMultiply( a, b );
    cout << vec2str(c) << endl;

    start = system_clock::now();
    a.assign( 1250, 99999999 );
    b.assign( 1250, 11111111 );
    for (int i=0; i<100; i++) c = BasecaseMultiply( a, b );
    //cout << vec2str(c) << endl;
    time_used( start );

    return 0;
}

// 参数：向量引用、 前移的段数（也许需要考虑vec为0的情况）
void shift( vector<ULL>& vec, int n ) 
{
    for (register int i = 1; i <= n; i++) vec.emplace_back(0);
}

// 假设 b.size() >= a.size()
vector<ULL> BasecaseMultiply( const vector<ULL>& a, const vector<ULL>& b)
{
    vector<ULL> c;
    vector<ULL> t;
    register const ULL* pa = a.data();
    register const ULL* pb = b.data();
    int bi = b.size() - 1, indent = 1;
    c = vec_mp_single( a, pb[bi--] );
    while ( bi >= 0 )
    {
        if ( pb[bi] > 0 )
        {
            t = vec_mp_single(a, pb[bi]);
            shift(t, indent);
            c = vec_plus(t, c);
        }
        bi--, indent++;
    }
    return c;
}

vector<ULL> vec_mp_single( const vector<ULL>& a, ULL b)
{
    vector<ULL> c( a.size() );
    register const ULL *pa = a.data();
    register ULL *pc = c.data();

    if ( b == 0 ) { return vector<ULL>{0}; }
    ULL pool = 0, v;
    for ( int i = a.size()-1; i >=0 ; i-- ) {
        v = pa[i] * b + pool;
        pc[i] = v % BASE, pool = v / BASE;
    }
    if (pool > 0) c.insert( c.begin(), pool );
    return c;
}

// a.size() <= b.size()
vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b)
{
    static int ia; // iter
    register const ULL* pa = a.data();
    register const ULL* pb = b.data();
    vector<ULL> c( a.size() );
    register ULL* pc = c.data();
    ULL t, pool=0;
    int ib=b.size()-1;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]) + (pb[ib--]) + pool
                    : (pa[ia]) + pool;
        pc[ia] = t % BASE, pool = t/BASE;
    }
    if ( pool > 0ULL ) c.insert(c.begin(), pool);
    return c;
}

string vec2str( const vector<ULL> &vec )
{
    string s("");
    s += to_string( vec[0] );
    for (unsigned int it = 1; it < vec.size(); it++ )
        s += to_string(vec[it]+BASE).substr(1, MAXLEN);
    return s;
}

void time_used(system_clock::time_point& time_a) {
    duration<double> diff;
    diff = chrono::system_clock::now() - time_a;
    cout << "Time used: " << diff.count() << endl;
    time_a = chrono::system_clock::now();
}
