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
vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b, int abegin);
vector<ULL> BasecaseMultiply( const vector<ULL>& a, const vector<ULL>& b);
int vec_mp_single( const vector<ULL>& a, ULL b, vector<ULL>& c, ULL indent);
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
    if (c[0] == 0ULL ) c.erase( c.begin() );
    cout << vec2str(c) << endl;


    vector<ULL> t( a.size()+1 );
    int test = vec_mp_single(a, 1, t, 0);
    if (t[0] == 0ULL ) t.erase( t.begin() );
    cout << "test: " << test << endl;
    cout << "tval: " << vec2str(t) << endl;

    start = system_clock::now();
    a.assign( 1250, 99999999 );
    b.assign( 1250, 11111111 );
    for (int i=0; i<100; i++) c = BasecaseMultiply( a, b );
    //cout << vec2str(c) << endl;
    time_used( start );

    return 0;
}

// 假设 b.size() >= a.size()
vector<ULL> BasecaseMultiply( const vector<ULL>& a, const vector<ULL>& b)
{
    vector<ULL> c(a.size() + b.size(), 0);
    vector<ULL> t(a.size() + b.size(), 0);
    int tpos = 1, tbegin;
    register const ULL* pa = a.data();
    register const ULL* pb = b.data();
    int bi = b.size() - 1, indent = 1;
    //初始化C值，末尾offset为0
    vec_mp_single( a, pb[bi--], c, 0 );
    while ( bi >= 0 )
    {
        //如果对应的b==0则不计入
        if ( pb[bi] > 0 )
        {
            tbegin = vec_mp_single(a, pb[bi], t, tpos);
            c = vec_plus(t, c, tbegin);
        }
        bi--, indent++, tpos++;
    }
    return c;
}

int vec_mp_single( const vector<ULL>& a, ULL b, vector<ULL>& c, ULL indent)
{
    register const ULL *pa = a.data();
    register ULL *pc = c.data();
    if ( b == 0 ) { c[0] = 0; return 1; }
    //实际末位置
    int ci = c.size() - 1 - indent;
    ULL pool = 0, v;
    for ( int i = a.size()-1; i >=0 ; i-- ) {
        v = pa[i] * b + pool;
        pc[ci--] = v % BASE, pool = v/BASE;
    }
    if (pool > 0) { pc[ci--] = pool; }
    //返回实际起始位置
    return ci+1;
}

// a.size() <= b.size()
vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b, int abegin)
{
    static int ia; // iter
    register const ULL* pa = a.data();
    register const ULL* pb = b.data();
    vector<ULL> c( a.size() );
    register ULL* pc = c.data();
    ULL t, pool=0;
    int ib=b.size()-1;
    for (ia = a.size()-1; ia >= abegin; ia-- )
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
