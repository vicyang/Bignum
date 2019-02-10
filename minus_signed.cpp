// bignum minus
// 523066680/vicyang
// 2019-01

#include <iostream>
#include <chrono>
#include <vector>
#include <cstdio>
using namespace std;
typedef long long int LL;
const LL BASE = 100000000;
const LL LEN = 8;

vector<LL> vec_minus(const vector<LL> &a, const vector<LL> &b);
string s_minus(const string &a, const string &b);
string vec2str( const vector<LL> &vec );

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
    //check(va, vb);
    vector<LL> vc = vec_minus(va,vb);
    cout << vec2str(vc) << endl;

    // 结果应为1的测试
    va = {1, 0, 0};
    vb = {99999999,99999999};
    //check(va, vb);
    vc = vec_minus(va, vb);
    cout << vec2str(vc) << endl;

    va.assign( 1250, 99999999 );
    vb.assign( 1250, 12345678 );
    for (int i = 0; i < 20000; i++) vec_minus(va, vb);
    return 0;
}

// 测试vector作为参数
vector<LL> vec_minus(const vector<LL> &a, const vector<LL> &b)
{
    static int ia; // iter
    register const LL *pa = a.data();
    register const LL *pb = b.data();
    vector<LL> c( a.size() );
    register LL *pc = c.data();
    LL t, cut=0, ib=b.size()-1, zero=0;
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

string vec2str( const vector<LL> &vec )
{
    string s("");
    s += to_string( vec[0] );
    for ( int it = 1; it < vec.size(); it++ )
        s += to_string(vec[it]+BASE ).substr(1, LEN);
    return s;
}
