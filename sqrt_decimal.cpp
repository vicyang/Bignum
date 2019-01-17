// SQRT - Decimal Solution (Only for Positive Integer Number)
// 523066680/vicyang
// 2019-01

#include <iostream>
#include <chrono>
using namespace std;

string s_mp_single(const string& a, const string& b);
string s_minus(string a, string b);
int s_cmp( string &a, string &b );
void check(string a, string b);

int main(int argc, char *argv[] ) 
{
    auto start = chrono::system_clock::now();
    
    


    auto end = chrono::system_clock::now();
    chrono::duration<double> diff = end-start;
    cout << "Time Used: " << diff.count() << " s" << endl;
    return 0;
}

// bignum * single num (str*str)
string s_mp_single(const string& a, const string& b)
{
    static int idx;
    string s;
    //如果b是0，直接返回0
    if ( b[0] == '0' ) return "0";
    s.assign(a.length(), '0');
    int t, pool = 0;
    for ( idx = a.length()-1; idx >= 0; idx-- )
    {
        t = (a[idx]-'0') * (b[0] - '0') + pool;
        s[idx] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

// plus 属于标准库函数的名称，所以加了前缀
string s_plus(string& a, string& b)
{
    static int iter;
    string s( a.length(), '0');
    int la = a.length(), lb = b.length();
    int t, pool=0, ia=la-1, ib=lb-1;
    for (iter = 0; iter < la; iter++ )
    {
        t = ib >= 0 ? (a[ia]-'0') + (b[ib--]-'0') + pool
                    : (a[ia]-'0') + pool;
        s[ia--] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
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