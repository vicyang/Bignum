#include <iostream>
#include <chrono>
#include <vector>
#include <cstdio>
using namespace std;

string s_minus(string a, string b);
int s_cmp( string &a, string &b );

string vec2str( const vector<int> &vec )
{
    const int base = 1000000;
    string s("");
    s += to_string( vec[0] );
    for ( int it = 1; it < vec.size(); it++ )
        s += to_string(vec[it]+base).substr(1,6);
    return s;
}

void check(const vector<int> &va, const vector<int> &vb)
{
    string a = vec2str(va);
    string b = vec2str(vb);
    string cmd = "perl -Mbignum -e \"print " + a + "-" + b + "\"";
    system( cmd.c_str() );
    cout << " <- check " << endl;
}

// 测试vector作为参数
vector<int> vec_minus(const vector<int> &a, const vector<int> &b)
{
    static int ia; // iter
    const int base = 1000000;
    register const int *pa = a.data();
    register const int *pb = b.data();
    vector<int> c( a.size() );
    register int *pc = c.data();
    int t, cut=0, ib=b.size()-1, zero=0;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]) - (pb[ib--]) + cut
                    : (pa[ia]) + cut;
        t < 0 ? t += base, cut = -1 : cut = 0;
        zero = t == 0 ? zero+1 : 0;  // 此判断须独立，t有可能+base后才为0
        pc[ia] = t;
    }
    c.erase(c.begin(), c.begin()+zero);
    return c;
}

int main(int argc, char *argv[] ) 
{
    auto stage0 = chrono::system_clock::now();
    chrono::duration<double> diff;
    string a(10000, '8');
    string b(10000, '9');
    string c;
    //耗时测试
    for (int i = 0; i < 20000; i++) s_minus(a, b);
    auto stage1 = chrono::system_clock::now();
    diff = stage1-stage0;
    cout << "s_minus, Time used: " << diff.count() << endl;

    // vector<int> test{123, 909, 1};
    // cout << vec2str( test ) << endl;

    vector<int> va{552, 443, 123456, 654321};
    vector<int> vb{ 93456, 924321};
    check(va, vb);
    vector<int> vc = vec_minus(va,vb);
    cout << vec2str(vc) << endl;

    va = {1, 0, 0};
    vb = {999999,999999};
    check(va, vb);
    vc = vec_minus(va, vb);
    cout << vec2str(vc) << endl;

    stage1 = chrono::system_clock::now();
    va.assign( 3500, 999999 );
    vb.assign( 3500, 123456 );
    for (int i = 0; i < 20000; i++) vec_minus(va, vb);
    auto stage2 = chrono::system_clock::now();
    diff = stage2-stage1;
    cout << "s_minus, Time used: " << diff.count() << endl;
    return 0;
}


// 大数减法 字符串操作, 暂时假设 a >= b
// 传参使用副本拷贝，避免调换原数值
string s_minus(string va, string vb)
{
    static int ia;
    string &a = va, &b = vb;
    int cmp = s_cmp(a, b);
    if (cmp == 0) return "0";
    else if (cmp == -1) swap(a, b);

    string s( a.length(), '0');
    int t, cut=0, ib=b.length()-1, zero=0;
    for (ia = a.length()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]-'0') - (b[ib--]-'0') - cut 
                    : (a[ia]-'0') - cut;
        cut = t < 0 ? 1 : 0;
        s[ia] = t + '0' + cut*10;
        s[ia] == '0' ? zero++ : zero=0;
    }
    if (zero > 0) s.erase(0, zero);
    return s;
}

int s_cmp( string &a, string &b )
{
    if ( a.length() > b.length() ) return 1;
    else if ( a.length() < b.length() ) return -1;
    else return a.compare(b);
}
