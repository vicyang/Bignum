// SQRT - Decimal Solution, C++ implementation (Only for Positive Integer Number)
// 523066680/vicyang
// 2019-02 Vector

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
typedef unsigned long long int ULL;
const ULL BASE = 100000000;
const ULL LEN = 8;

string sqrt_decimal(vector<ULL> num, int precision);

vector<ULL> vec_mp_single(const vector<ULL> &a, const vector<ULL> &b);
vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b);
vector<ULL> vec_minus(const vector<ULL> &a, const vector<ULL> &b);
string vec2str( const vector<ULL> &vec );
void check(const vector<ULL> &va, const vector<ULL> &vb, const string &op);

// 牛顿迭代法求第一段
ULL SqrtInt_ULL(ULL m)
{
    ULL s, t, u = m/2;
    do {
        s = u,
        u = (s + m/s)/2;
    } while ( s > u );
    return s;
}

int vec_cmp(vector<ULL> &a, vector<ULL> &b)
{
    int len_a = a.size(), len_b= b.size();
    if ( len_a > len_b ) { return 1; }
    else if ( len_a < len_b ) { return -1; }

    register int it = 0;
    for ( ; it < len_a; it++ ) {
             if ( a[it] > b[it] ) { return 1; }
        else if ( a[it] < b[it] ) { return -1; }
    }
    return 0;
}

ULL BinSearch(vector<ULL> &target, vector<ULL> &base)
{
    vector<ULL> tbase = base;
    tbase.push_back(0);
    ULL min = 0, max = BASE, mid = (min+max)/2;
    int tblast = tbase.size()-1;

    vector<ULL> v;
    do {
        tbase[ tblast ] = mid;
        v = vec_mp_single( tbase, vector<ULL> {mid} );
        //cout << vec2str(v) << endl;
             if ( vec_cmp(v, target) == 1 ) { max = mid; mid = (max+min)/2; } 
        else if ( vec_cmp(v, target) ==-1 ) { min = mid; mid = (max+min)/2; }
        else { break; }
        //printf("v: %ld mid: %ld, min: %ld, max: %ld\n", v, mid, min, max );
    } while ( max-min > 1 );

    tbase[ tblast ] = mid;
    // 更新 target 值
    v = vec_mp_single( tbase, vector<ULL> {mid} );
    target = vec_minus( target, v );
    cout << "est v:   " << vec2str(v) << endl;
    cout << "remainder:" << vec2str(target) << endl;

    // 更新 base 值
    ULL carry = mid*2 / BASE;
    if (carry > 0) base[ base.size()-1 ] ++;
    base.push_back( (mid*2) % BASE );
    return mid;
}

int main(int argc, char *argv[] ) 
{
    // check minus
    vector<ULL> a{1,0,0};
    vector<ULL> b{99999999, 32878736};
    cout << vec2str(vec_minus(a, b)) << endl;

    vector<ULL> num{2};
    sqrt_decimal(num, 100);
    
    return 0;
}

string sqrt_decimal(vector<ULL> num, int precision)
{
    bool dec_loop = 1;
    int prec = 0, mp, mid, cmp, dbmid;

    // 求出第一段
    ULL r_int;
    r_int = SqrtInt_ULL( num[0] );
    cout << r_int << endl;
    
    ULL est;
    vector<ULL> result{ r_int };
    vector<ULL> tnum = num;
    vector<ULL> base{ r_int * 2 };
    vector<ULL> target;

    // 求下一段 target
    target = vec_minus( tnum, vector<ULL>{ r_int * r_int } );
    target.push_back(0);
    target.push_back(0);
    cout << "target: " << vec2str(target) << endl;

    // 求下一段结果，同时更新 target
    est = BinSearch( target, base );
    target.push_back(0);
    target.push_back(0);
    cout << "est: " << est << endl;
    cout << "target: " << vec2str(target) << endl;
    cout << "  base: " << vec2str(base) << endl;

    // 求下一段结果，同时更新 target
    est = BinSearch( target, base );
    target.push_back(0);
    target.push_back(0);
    cout << "est: " << est << endl;
    cout << "target: " << vec2str(target) << endl;
    cout << "  base: " << vec2str(base) << endl;

    // while (prec++ < 10)
    // {
    //     target.push_back(0);
    //     target.push_back(0);
    //     est = BinSearch( target, base );
    //     cout << est;
    // }

    cout << endl;
    return "";
}

// vec multiply to one word
vector<ULL> vec_mp_single(const vector<ULL> &a, const vector<ULL> &b)
{
    static int ia; // iter
    //如果b是0，直接返回0
    if ( b[0] == 0 ) return vector<ULL>{0};
    vector<ULL> c( a.size() );
    ULL t, pool=0, ib=b.size()-1;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = a[ia] * b[0] + pool;
        c[ia] = t%BASE, pool = t/BASE;
    }
    if ( pool > 0 ) c.insert(c.begin(), pool);
    return c;
}

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

// vec_minus 设 a.len > b.len
vector<ULL> vec_minus(const vector<ULL> &a, const vector<ULL> &b)
{
    register int ia;
    register int ib = b.size()-1;
    vector<ULL> c( a.size() );
    ULL cut=0, zero=0;
    long long int t; // t可能为负数
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]) - (b[ib--]) + cut
                    : (a[ia]) + cut;
        t < 0 ? t += BASE, cut = -1 : cut = 0;
        zero = t == 0 ? zero+1 : 0;  // 此判断须独立，t有可能+base后才为0
        c[ia] = t;
    }
    c.erase(c.begin(), c.begin()+zero);
    return c;
}

string vec2str( const vector<ULL> &vec )
{
    string s("");
    s += to_string( vec[0] );
    for ( int it = 1; it < vec.size(); it++ )
        s += to_string(vec[it]+BASE).substr(1,LEN);
    return s;
}

void check(const vector<ULL> &va, const vector<ULL> &vb, const string &op)
{
    string a = vec2str(va);
    string b = vec2str(vb);
    string cmd = "perl -Mbignum -e \"print " + a + op + b + "\"";
    system( cmd.c_str() );
    cout << " <- check " << endl;
}
