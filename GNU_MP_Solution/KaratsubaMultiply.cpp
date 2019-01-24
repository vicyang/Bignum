#include <iostream>
#include <string>
#include <stdio.h>
#include <chrono>
using namespace std;

string s_mp_single(const string& a, char b);
string s_plus(const string& a, const string& b);
string s_minus(string va, string vb);
int s_cmp( string &a, string &b );
string BasecaseMultiply( const string& a, const string& b);
string KaratsubaMultiply( const string& a, const string& b);
string zeros(10000, '0');

int main(int argc, char *argv[] ) 
{
    string a("1111111");
    string b("1111111");
    string c = KaratsubaMultiply(a, b);
    cout << c << endl;

    cout << BasecaseMultiply("1000", "1000");
    return 0;

}

string KaratsubaMultiply( const string& A, const string& B)
{
    static int len = 5;
    if (A.length() < len) return BasecaseMultiply(A, B);
    int k = (A.length()+1)/2; // ceil
    string A0,A1,B0,B1, C0,C1,C2, dtA, dtB, T;
    A0 = A.substr(A.length()-k, k);
    A1 = A.substr(0, A.length()-k);
    B0 = B.substr(B.length()-k, k);
    B1 = B.substr(0, B.length()-k);
    C0 = KaratsubaMultiply(A0, B0);
    C1 = KaratsubaMultiply(A1, B1);
    dtA = s_minus(A0, A1);
    dtB = s_minus(B0, B1);
    C2 = KaratsubaMultiply(dtA, dtB);

    int sA, sB;
    sA = s_cmp(A0, A1);
    sB = s_cmp(B0, B1);
    printf("k = %d, sA,sB = %d %d\n", k, sA, sB);
    printf("A0,A1 = %s %s, B0,B1 = %s %s\n", A0.c_str(), A1.c_str(), B0.c_str(), B1.c_str());
    printf("dtA,dtB = %s %s\n", dtA.c_str(), dtB.c_str() );
    printf("%s %s %s\n", C0.c_str(), C1.c_str(), C2.c_str() );

    T = s_plus(C0, C1);
    T = s_minus( T, C2 );
    //if ( T.compare("0") != 0 ) {
    T += zeros.substr(0, k);
    //}
    T = s_plus(T, C0);
    T = s_plus(T, C1 + zeros.substr(0, 2*k) );
    //printf("%s, %s, %d\n", A0.c_str(), A1.c_str(), k);
    return T;
}

string BasecaseMultiply( const string& a, const string& b)
{
    string c;
    string t;
    c = s_mp_single( a, b[0] );
    for (int j = 1; j < a.length(); j++)
    {
        t = s_mp_single(a, b[j]);
        if ( t.compare("0") != 0 ) {
            t = t + zeros.substr(0, j);
        }
        c = s_plus( t, c ); // t is longer than c
    }
    return c;
}

// bignum * single num (str * str (one word) )
string s_mp_single(const string& a, char b)
{
    static int idx;
    string s;
    //如果b是0，直接返回0
    if ( b == '0' ) return "0";
    s.assign(a.length(), '0');
    int t, pool = 0, numb = b - '0';
    for ( idx = a.length()-1; idx >= 0; idx-- )
    {
        t = (a[idx]-'0') * numb + pool;
        s[idx] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

// plus 属于标准库函数的名称，所以加了前缀
// 备注：此函数假设a.len > b.len
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
