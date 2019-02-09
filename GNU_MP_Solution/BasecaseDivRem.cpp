// BasecaseMultiply - C++ Vector
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
vector<ULL> BasecaseMultiply( const vector<ULL>& a, const vector<ULL>& b);
vector<ULL> vec_mp_single(const vector<ULL> &a, const vector<ULL> &b);
vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b);
vector<ULL> vec_minus(const vector<ULL> &a, const vector<ULL> &b);
int vec_cmp(vector<ULL> &a, vector<ULL> &b);
int vec_accum(vector<ULL> &a, vector<ULL> &b, int bbegin);

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

// 参数：向量引用、 前移的段数（也许需要考虑vec为0的情况）
void shift( vector<ULL>& vec, int n )
{
    for (int i = 0; i < n; i++) vec.push_back(0);
}

vector<ULL> BasecaseDivRem( const vector<ULL> &a, const vector<ULL> &b )
{
    int asize = a.size(), bsize = b.size();
    int n = b.size(), m = a.size() - b.size();
    vector<ULL> tb = b;
    vector<ULL> ta = a;
    vector<ULL> q(m+1);
    shift(tb, m);
    if ( vec_cmp(ta, tb) > -1 ) {
        q[m] = 1;
        ta = vec_minus(ta, tb);
    } else {
        q[m] = 0;
    }

    int tq;
    for ( int j = m-1; j >= 0; j-- )
    {
        tq = int( ta[asize-(n+j)] );
    }

    return vector<ULL>{0};
}

int main(int argc, char *argv[] ) 
{
    system_clock::time_point start;
    start = system_clock::now();

    vector<ULL> a{9999, 0, 12345678};
    //vector<ULL> b{58765432};
    vector<ULL> b{5876};
    vector<ULL> c;
    check( a, b, "/" );
    BasecaseDivRem(a, b);

    
    time_used( start );

    return 0;
}

// 在原来的基础上叠加数值
int vec_accum(vector<ULL> &a, vector<ULL> &b, int bbegin)
{
    static int ia; // iter
    register ULL* pa = a.data();
    register ULL* pb = b.data();
    ULL t, pool=0;
    register int ib = b.size()-1;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]) + (pb[ib--]) + pool
                    : (pa[ia]) + pool;
        pa[ia] = t % BASE, pool = t/BASE;
        if ( pool == 0 and ib < bbegin ) break;
    }
    if ( pool > 0ULL ) pa[ia] = pool;
    return ia;
}

// vec multiply to one word
vector<ULL> vec_mp_single(const vector<ULL> &a, const vector<ULL> &b)
{
    register const ULL *pa = a.data();
    register const ULL *pb = b.data();
    static int ia; // iter
    //如果b是0，直接返回0
    if ( b[0] == 0 ) return vector<ULL>{0};
    vector<ULL> c( a.size() );
    register ULL *pc = c.data();
    ULL t, pool=0, ib=b.size()-1;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = pa[ia] * pb[0] + pool;
        pc[ia] = t%BASE, pool = t/BASE;
    }
    if ( pool > 0 ) c.insert(c.begin(), pool);
    return c;
}

vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b)
{
    static int ia; // iter
    vector<ULL> c( a.size() );
    register const ULL *pa = a.data();
    register const ULL *pb = b.data();
    register ULL *pc = c.data();
    int t, pool=0, ib=b.size()-1;
    int v, r;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]) + (pb[ib--]) + pool
                    : (pa[ia]) + pool;
        pc[ia] = t % BASE, pool = t/BASE;
    }
    if ( pool > 0 ) c.insert(c.begin(), pool);
    return c;
}

// vec_minus 设 a.len > b.len
vector<ULL> vec_minus(const vector<ULL> &a, const vector<ULL> &b)
{
    register int ia;
    register int ib = b.size()-1;
    vector<ULL> c( a.size() );
    register const ULL *pa = a.data();
    register const ULL *pb = b.data();
    register ULL *pc = c.data();
    int cut=0, zero=0;
    long long int t; // t可能为负数
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]) - (pb[ib--]) + cut
                    : (pa[ia]) + cut;
        t < 0 ? t += BASE, cut = -1 : cut = 0;
        zero = t == 0 ? zero+1 : 0;  // 此判断须独立，t有可能+base后才为0
        pc[ia] = t;
    }
    c.erase(c.begin(), c.begin()+zero);
    return c;
}

int vec_cmp(vector<ULL> &a, vector<ULL> &b)
{
    register ULL* pa = a.data();
    register ULL* pb = b.data();
    int len_a = a.size(), len_b= b.size();
    if ( len_a > len_b ) { return 1; }
    else if ( len_a < len_b ) { return -1; }

    register int it = 0;
    for ( ; it < len_a; it++ ) {
             if ( pa[it] > pb[it] ) { return 1; }
        else if ( pa[it] < pb[it] ) { return -1; }
    }
    return 0;
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
