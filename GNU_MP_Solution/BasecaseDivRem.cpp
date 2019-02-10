// BasecaseMultiply - C++ Vector
// Notes: 实现该方法应先实现 有符号的加减函数。
// 523066680/vicyang
// 2019-02

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ULL;
typedef long long LL;

string vec2str( const vector<LL> &vec );
vector<LL> BasecaseMultiply( const vector<LL>& a, const vector<LL>& b);
vector<LL> vec_mp_single(const vector<LL> &a, const vector<LL> &b);
vector<LL> vec_plus(const vector<LL> &a, const vector<LL> &b);
vector<LL> vec_minus(const vector<LL> &a, const vector<LL> &b);
int vec_cmp(const vector<LL> &a, const vector<LL> &b);
int vec_accum(vector<LL> &a, vector<LL> &b, int bbegin);

void time_used(system_clock::time_point& time_a);

const LL BASE = 100000000;
const int MAXLEN = 8;

void check(const vector<LL> &va, const vector<LL> &vb, const string &op)
{
    string a = vec2str(va);
    string b = vec2str(vb);
    string cmd = "perl -Mbignum -e \"print " + a + op + b + "\"";
    system( cmd.c_str() );
    cout << " <- check " << endl;
}

// 参数：向量引用、 前移的段数（也许需要考虑vec为0的情况）
void shift( vector<LL>& vec, int n )
{
    for (int i = 0; i < n; i++) vec.push_back(0);
}

vector<LL> BasecaseDivRem( const vector<LL> &a, const vector<LL> &b )
{
    int asize = a.size(), bsize = b.size();
    int n = b.size(), m = a.size() - b.size();
    vector<LL> tb = b;
    vector<LL> ta = a;
    vector<LL> q(m+1);
    shift(tb, m);
    if ( vec_cmp(ta, tb) > -1 ) {
        q[m] = 1;
        ta = vec_minus(ta, tb);
    } else {
        q[m] = 0;
    }

    cout << "ta befor fo: " << vec2str(ta) << endl;
    LL tq;
    vector<LL> tv;
    for ( int j = m-1; j >= 0; j-- )
    {
        tq = (ta[asize-(n+j)-1]*BASE + ta[asize-(n+j)])/b[0];
        cout << "tq: " << tq << endl;

        q[j] = tq < BASE - 1 ? tq : BASE - 1;
        // ta = vec_minus(ta, tb);
        tv = vec_mp_single( b, vector<LL>{q[j]} );
        shift(tv, j);
        ta = vec_minus( ta, tv );
        cout << "ta before while: " << vec2str(ta) << endl;

        tb = b;
        while ( ta[0] < 0 )
        {
            q[j] -= 1;
            shift(tb, 1);
            cout << "before: " << vec2str(ta) << "," << vec2str(tb) << endl;
            ta[0] *= -1;
            ta = vec_minus(tb, ta);
            cout << "while: " << vec2str(ta) << "," << vec2str(tb) << endl;
        }

        cout << "next" <<endl;
        //cout << ta[asize-(n+j)-1] << ",";
    }

    cout << vec2str( q ) << endl;

    cout << endl;
    return vector<LL>{0};
}

int main(int argc, char *argv[] ) 
{
    system_clock::time_point start;
    start = system_clock::now();

    vector<LL> a{9999, 0, 12345678};
    //vector<LL> b{58765432};
    vector<LL> b{5876};
    vector<LL> c;
    check( a, b, "/" );
    BasecaseDivRem(a, b);

    
    time_used( start );

    return 0;
}

// 在原来的基础上叠加数值
int vec_accum(vector<LL> &a, vector<LL> &b, int bbegin)
{
    static int ia; // iter
    register LL* pa = a.data();
    register LL* pb = b.data();
    LL t, pool=0;
    register int ib = b.size()-1;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]) + (pb[ib--]) + pool
                    : (pa[ia]) + pool;
        pa[ia] = t % BASE, pool = t/BASE;
        if ( pool == 0 and ib < bbegin ) break;
    }
    if ( pool > 0LL ) pa[ia] = pool;
    return ia;
}

// vec multiply to one word
vector<LL> vec_mp_single(const vector<LL> &a, const vector<LL> &b)
{
    register const LL *pa = a.data();
    register const LL *pb = b.data();
    static int ia; // iter
    //如果b是0，直接返回0
    if ( b[0] == 0 ) return vector<LL>{0};
    vector<LL> c( a.size() );
    register LL *pc = c.data();
    LL t, pool=0, ib=b.size()-1;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = pa[ia] * pb[0] + pool;
        pc[ia] = t%BASE, pool = t/BASE;
    }
    if ( pool > 0 ) c.insert(c.begin(), pool);
    return c;
}

vector<LL> vec_plus(const vector<LL> &a, const vector<LL> &b)
{
    static int ia; // iter
    vector<LL> c( a.size() );
    register const LL *pa = a.data();
    register const LL *pb = b.data();
    register LL *pc = c.data();
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

//带符号的减法（待更）
vector<LL> vec_minus(const vector<LL> &a, const vector<LL> &b)
{
    static int ia, asize, bsize; 
    LL sign = 1;
    register const LL *pa, *pb;
    vector<LL> c;
    //如果 a < b，指针调换，sign 为 -1
    if ( vec_cmp(a, b) == -1 ) {
        c.assign(b.size(), 0);
        pa = b.data(), pb = a.data(), sign = -1;
        asize = b.size(), bsize = a.size();
    } else {
        c.assign(a.size(), 0);
        pa = a.data(), pb = b.data();
        asize = a.size(), bsize = b.size();
    }
    
    register LL *pc = c.data();
    LL t, cut=0, ib=bsize-1, zero=0;
    for (ia = asize-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]) - (pb[ib--]) + cut
                    : (pa[ia]) + cut;
        t < 0 ? t += BASE, cut = -1 : cut = 0;
        zero = t == 0 ? zero+1 : 0;  // 此判断须独立，t有可能+base后才为0
        pc[ia] = t;
    }
    c.erase(c.begin(), c.begin()+zero);
    c[0] *= sign;
    return c;
}

int vec_cmp(const vector<LL> &a, const vector<LL> &b)
{
    register const LL* pa = a.data();
    register const LL* pb = b.data();
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

string vec2str( const vector<LL> &vec )
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
