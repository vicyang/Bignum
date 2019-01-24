#include <iostream>
#include <chrono>
#include <vector>
#include <cstdio>
using namespace std;

string s_minus(string a, string b);
int s_cmp( string &a, string &b );

void check(const vector<int> &va, const vector<int> &vb)
{
    string a("");
    string b("");
    for ( int it = 0; it < va.size(); it++ ) a += to_string(va[it]);
    for ( int it = 0; it < vb.size(); it++ ) b += to_string(vb[it]);
    string cmd = "perl -Mbignum -e \"print " + a + "-" + b + "\"";
    system( cmd.c_str() );
    cout << " <- check " << endl;
}

// 测试vector作为参数
vector<int> vec_minus(const vector<int> &a, const vector<int> &b)
{
    static int ia; // iter
    const int base = 1000000;
    vector<int> c( a.size() );
    //string s(20002, '0');
    int t, cut=0, ib=b.size()-1;
    int v, r;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]) - (b[ib--]) + cut
                    : (a[ia]) + cut;
        if ( t < 0 )
            t += base, cut = -1;
        else 
            cut = 0;
        c[ia] = t;
    }
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

    vector<int> va{123456, 654321};
    vector<int> vb{ 93456, 924321};
    check(va, vb);
    vector<int> vc = vec_minus(va,vb);
    for (int it = 0; it < vc.size(); it++) 
        cout << vc[it] << "," ;
    cout << endl;

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
