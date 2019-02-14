// bignum minus signed
// 需要考虑传入参数已经是负数的情况、vec_cmp亦需要做相应判断
// 523066680/vicyang
// 2019-02

#include <iostream>
#include <chrono>
#include <vector>
#include <cstdio>
using namespace std;
typedef long long int LL;
typedef unsigned long long int ULL;
const LL BASE = 1e8;
const LL LEN = 8;

vector<LL> vec_minus(const vector<LL> &a, const vector<LL> &b);
string s_minus(const string &a, const string &b);
string vec2str( const vector<LL> &vec );
int vec_cmp(const vector<LL> &a, const vector<LL> &b);

void check(const vector<LL> &va, const vector<LL> &vb)
{
    string a = vec2str(va);
    string b = vec2str(vb);
    string cmd = "perl -Mbignum -e \"print " + a + "-" + b + "\"";
    system( cmd.c_str() );
    cout << " <- check " << endl;
}

int main(int argc, char *argv[] ) 
{
    string a(10000, '8');
    string b(10000, '9');
    string c;

    // 小范围的"向量"减法测试
    vector<LL> va{552, 443, 12345678, 87654321};
    vector<LL> vb{ 93456, 92432100};
    check(va, vb);
    vector<LL> vc = vec_minus(va,vb);
    cout << vec2str(vc) << endl;

    // 结果应为1的测试
    vb = {1, 0, 0};
    va = {99999999,99999999};
    //check(va, vb);
    vc = vec_minus(va, vb);
    cout << vec2str(vc) << endl;

    va.assign( 1250, 99999999 );
    vb.assign( 1250, 12345678 );
    for (int i = 0; i < 20000; i++) vec_minus(va, vb);
    return 0;
}

//带符号的减法（为完善）
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

string vec2str( const vector<LL> &vec )
{
    string s("");
    s += to_string( vec[0] );
    for ( int it = 1; it < vec.size(); it++ )
        s += to_string(vec[it]+BASE ).substr(1, LEN);
    return s;
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