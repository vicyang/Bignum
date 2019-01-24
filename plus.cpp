#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

string s_plus(const string& a, const string& b);
string sn_plus(const string& a, const string& b);
vector<int> vec_plus(const vector<int>& a, const vector<int>& b, int len);

void check(const vector<int> &va, const vector<int> &vb)
{
    string a("");
    string b("");
    for ( int it = 0; it < va.size(); it++ ) a += to_string(va[it]);
    for ( int it = 0; it < vb.size(); it++ ) b += to_string(vb[it]);
    string cmd = "perl -Mbignum -e \"print " + a + "+" + b + "\"";
    system( cmd.c_str() );
    cout << " <- check " << endl;
}

int main(int argc, char *argv[] ) 
{
    auto stage0 = chrono::system_clock::now();
    chrono::duration<double> diff;
    string a(20000, '9');
    string b(20000, '9');
    string c=s_plus(a, b);
    //check(a, b);
    //耗时测试
    for (int i = 0; i < 1000; i++) s_plus(a, b);
    auto stage1 = chrono::system_clock::now();
    diff = stage1-stage0;
    cout << "Stage 1, Time Used: " << diff.count() << " s" << endl;
    
    vector<int> va{999,406789};
    vector<int> vb{123,906789};
    check(va, vb);
    stage1 = chrono::system_clock::now();

    int len = 12;
    vector<int> vc = vec_plus(va, vb, len);
    for (int it = 0; it < vc.size(); it++) 
        cout << vc[it] << "," ;
    cout << endl;
    //耗时测试

    va.assign( 4000, 999999 );
    vb.assign( 4000, 999999 );
    for (int i = 0; i < 1000; i++) vec_plus(va, vb, len);
    auto stage2 = chrono::system_clock::now();
    diff = stage2-stage1;
    cout << "Stage 2, Time Used: " << diff.count() << " s" << endl;

    string na(20000, 9);
    string nb(20000, 9);
    string nc = sn_plus(na, nb);
    //cout << sc << endl;
    //耗时测试
    for (int i = 0; i < 1000; i++) sn_plus(na, nb);
    auto stage3 = chrono::system_clock::now();
    diff = stage3-stage2;
    cout << "Stage 3, Time Used: " << diff.count() << " s" << endl;

    //其他测试
    a="99999", b="9999";
    c=s_plus( a, b );
    cout << c << endl;
    return 0;
}

// 测试vector作为参数
vector<int> vec_plus(const vector<int> &a, const vector<int> &b, int len)
{
    static int ia; // iter
    const int base = 1000000;
    vector<int> c( a.size() );
    //string s(20002, '0');
    int t, pool=0, ib=b.size()-1;
    int v, r;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]) + (b[ib--]) + pool
                    : (a[ia]) + pool;
        v = t % base, pool = t/base;
        c[ia] = v;
    }
    if ( pool > 0 ) c.insert(c.begin(), pool);
    return c;
}

// plus 属于标准库函数的名称，所以加了前缀
string s_plus(const string& a, const string& b)
{
    static int ia;
    string s( a.length(), '0');
    int t, pool=0, ib=b.length()-1;
    for (ia = a.length()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]-'0') + (b[ib--]-'0') + pool
                    : (a[ia]-'0') + pool;
        s[ia] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

// 同样是字符串接口，但元素不是字符而是数值
string sn_plus(const string& a, const string& b)
{
    static int ia;
    string s( a.length(), 0);
    int t, pool=0, ib=b.length()-1;
    for (ia = a.length()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]) + (b[ib--]) + pool
                    : (a[ia]) + pool;
        s[ia] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

