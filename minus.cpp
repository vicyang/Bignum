#include <iostream>
#include <chrono>
using namespace std;

string s_minus(string& a, string& b);
void check(string a, string b);

int main(int argc, char *argv[] ) 
{
    auto start = chrono::system_clock::now();
    string a(10000, '9');
    string b(10000, '9');
    string c=s_minus(a, b);
    //耗时测试
    for (int i = 0; i < 1000; i++) s_minus(a, b);
    auto end = chrono::system_clock::now();
    chrono::duration<double> diff = end-start;

    //其他测试
    a="10000", b="9999";
    c=s_minus( a, b );
    check(a, b);
    cout << c << endl;
    cout << "Time Used: " << diff.count() << " s" << endl;
    return 0;
}

// 大数减法 字符串操作, 暂时假设 a > b
string s_minus(string& a, string& b)
{
    static int iter;
    string s( a.length(), '0');
    int la = a.length(), lb = b.length();
    int t, cut=0, ia=la-1, ib=lb-1;
    for (iter = 0; iter < la; iter++ )
    {
        t = ib >= 0 ? (a[ia]-'0') - (b[ib--]-'0') - cut 
                    : (a[ia]-'0') - cut;
        if (t < 0)
            s[ia] = 10+t+'0', cut = 1;
        else 
            s[ia] = t + '0', cut = 0;
        ia--;
    }

    return s;
}


void check(string a, string b)
{
    string cmd = "perl -Mbignum -e \"print " + a + "-" + b + "\"";
    system( cmd.c_str() );
    cout << endl;
}