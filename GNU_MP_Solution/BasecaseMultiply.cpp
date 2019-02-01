#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
typedef unsigned long long ULL;

string vec2str( const vector<ULL> &vec );
vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b);
vector<ULL> BasecaseMultiply( const vector<ULL>& a, const vector<ULL>& b);
vector<ULL> mp_single( const vector<ULL>& a, int b);
string zeros(10000, '0');

const unsigned long long BASE = 1000000;
const int MAXLEN = 6;

int main(int argc, char *argv[] ) 
{
    vector<ULL> a{123, 666666};
    vector<ULL> b{456, 999999};
    // string c = BasecaseMultiply(a, b);
    //cout << c;

    vector<ULL> c;
    c = mp_single( a, b[1] );
    for ( int x : c )
        cout << x << ",";


    return 0;
}

vector<ULL> mp_single( const vector<ULL>& a, int b)
{
    vector<ULL> c( a.size() );
    ULL pool = 0, v;
    for ( int i = a.size()-1; i >=0 ; i-- )
    {
        v = a[i] * b + pool;
        //cout << a[i] << "*" << b << "+pool=" << v << endl;
        c[i] = v % BASE, pool = v / BASE;
    }
    if (pool > 0) c.push_back( pool );
    return c;
}

vector<ULL> BasecaseMultiply( const vector<ULL>& a, const vector<ULL>& b)
{
    vector<ULL> c;
    vector<ULL> t;

    return c;
}

// 测试vector作为参数
vector<ULL> vec_plus(const vector<ULL> &a, const vector<ULL> &b)
{
    static int ia; // iter
    vector<ULL> c( a.size() );
    //string s(20002, '0');
    int t, pool=0, ib=b.size()-1;
    int v, r;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]) + (b[ib--]) + pool
                    : (a[ia]) + pool;
        v = t % BASE, pool = t/BASE;
        c[ia] = v;
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