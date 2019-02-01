// bignum minus
// 523066680/vicyang
// 2019-01

#include <iostream>
#include <chrono>
#include <vector>
#include <cstdio>
using namespace std;

vector<int> vec_minus(const vector<int> &a, const vector<int> &b);
string s_minus(const string &a, const string &b);
int s_cmp( const string &a, const string &b );
string vec2str( const vector<int> &vec );

void check(const vector<int> &va, const vector<int> &vb)
{
    string a = vec2str(va);
    string b = vec2str(vb);
    string cmd = "perl -Mbignum -e \"print " + a + "-" + b + "\"";
    system( cmd.c_str() );
    cout << " <- check " << endl;
}

int main(int argc, char *argv[] ) 
{
    auto stage0 = chrono::system_clock::now();
    chrono::duration<double> diff;
    string a(10000, '8');
    string b(10000, '9');
    string c;
    // s_minus 耗时测试 10000位数，2W次
    for (int i = 0; i < 20000; i++) s_minus(a, b);
    auto stage1 = chrono::system_clock::now();
    diff = stage1-stage0;
    cout << "  s_minus, Time used: " << diff.count() << endl;

    // 小范围的"向量"减法测试
    vector<int> va{552, 443, 12345678, 87654321};
    vector<int> vb{ 93456, 92432100};
    //check(va, vb);
    vector<int> vc = vec_minus(va,vb);
    cout << vec2str(vc) << endl;

    // 结果应为1的测试
    va = {1, 0, 0};
    vb = {99999999,99999999};
    //check(va, vb);
    vc = vec_minus(va, vb);
    cout << vec2str(vc) << endl;

    // vec_minus 耗时测试 10000位数，2W次
    stage1 = chrono::system_clock::now();
    va.assign( 1250, 99999999 );
    vb.assign( 1250, 12345678 );
    for (int i = 0; i < 20000; i++) vec_minus(va, vb);
    auto stage2 = chrono::system_clock::now();
    diff = stage2-stage1;
    cout << "vec_minus, Time used: " << diff.count() << endl;
    return 0;
}

// 测试vector作为参数
vector<int> vec_minus(const vector<int> &a, const vector<int> &b)
{
    static int ia; // iter
    const int base = 100000000;
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

// 大数减法 字符串操作, 暂时假设 a >= b
string s_minus(const string &a, const string &b)
{
    static int ia;
    // 获取指针以绕过[]重载，更快地取址
    register const char* pa=a.data();
    register const char* pb=b.data();
    int cmp = s_cmp(a, b);
    if (cmp == 0) return "0";
    string s( a.length(), '0');
    register const char* ps=s.data();
    int t, cut=0, ib=b.length()-1, zero=0;
    for (ia = a.length()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]-'0') - (pb[ib--]-'0') - cut 
                    : (pa[ia]-'0') - cut;
        cut = t < 0 ? 1 : 0;
        s[ia] = t + '0' + cut*10;
        ps[ia] == '0' ? zero++ : zero=0;
    }
    if (zero > 0) s.erase(0, zero);
    return s;
}

string vec2str( const vector<int> &vec )
{
    const int base = 100000000;
    string s("");
    s += to_string( vec[0] );
    for ( int it = 1; it < vec.size(); it++ )
        s += to_string(vec[it]+base).substr(1,8);
    return s;
}

int s_cmp(const string &a, const string &b )
{
    if ( a.length() > b.length() ) return 1;
    else if ( a.length() < b.length() ) return -1;
    else return a.compare(b);
}
