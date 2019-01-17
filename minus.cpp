#include <iostream>
#include <chrono>
using namespace std;

string s_minus(string a, string b);
int s_cmp( string &a, string &b );
void check(string a, string b);

int main(int argc, char *argv[] ) 
{
    auto start = chrono::system_clock::now();
    string a(10000, '8');
    string b(10000, '9');
    string c;
    //耗时测试
    for (int i = 0; i < 1000; i++) s_minus(a, b);
    auto end = chrono::system_clock::now();
    chrono::duration<double> diff = end-start;

    //其他测试 1
    a="9999", b="19999";
    cout << "before a=" << a << ", b=" << b << endl;

    c = s_minus( a, b );
    check(a, b);
    cout << c << endl;
    cout << "after a=" << a << ", b=" << b << endl;
    c = s_minus( b, a );
    check(a, b);
    cout << c << endl;

    cout << "Time Used: " << diff.count() << " s" << endl;
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

void check(string a, string b)
{
    string cmd = "perl -Mbignum -e \"print qq(check: ), " + a + "-" + b + "\"";
    system( cmd.c_str() );
    cout << endl;
}