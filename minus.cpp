#include <iostream>
#include <chrono>
#include <cstring>
#include <cstdio>
using namespace std;

string s_minus(string a, string b);
char* c_minus(char *a, char *b);

int s_cmp( string &a, string &b );
void check(string a, string b);

int main(int argc, char *argv[] ) 
{
    auto stage0 = chrono::system_clock::now();
    chrono::duration<double> diff;
    string a(10000, '8');
    string b(10000, '9');
    char* ch_a = (char *)malloc( 10001 * sizeof(char) );
    char* ch_b = (char *)malloc( 10001 * sizeof(char) );
    int len_a = 10000, len_b = 10000;
    memset(ch_a, '9', len_a );
    memset(ch_b, '8', len_b );
    ch_a[len_a] = '\0';
    ch_b[len_b] = '\0';
    printf("len_a %d, len_b: %d\n", strlen( ch_a ), strlen( ch_b ) );

    string c;
    //耗时测试
    for (int i = 0; i < 50000; i++) s_minus(a, b);
    auto stage1 = chrono::system_clock::now();
    diff = stage1-stage0;
    printf("Stage1, Time used: %f\n", diff.count());

    char* ch_c = c_minus(ch_a, ch_b);
    //printf("%s\n", ch_c);
    printf("%d\n", strlen(ch_c) );
    stage1 = chrono::system_clock::now();

    //测试 c_minus 性能
    {
        for (int i = 0; i < 50000; i++) c_minus(ch_a, ch_b);
        auto stage2 = chrono::system_clock::now();
        diff = stage2-stage1;
        printf("Stage2, Time used: %f\n", diff.count());
    }

    //其他测试 1
    {
        a="9999", b="19999";
        printf("\nbefore a=%s, b=%s\n", a.c_str(), b.c_str());
        c = s_minus( a, b );
        printf("result = %s\n", c.c_str());
        printf("after a=%s, b=%s\n", a.c_str(), b.c_str());
        c = s_minus( b, a );
        // check(a, b);
    }

    return 0;
}

char* c_minus(char* a, char* b)
{
    static int ia;
    int la = strlen(a), lb = strlen(b), tl;
    char* tp;
    //如果 la < lb， 调换
    if ( la < lb )
        tp = a, a = b, b = tp, tl = la, la = lb, lb = tl;
    else if ( la == lb && strcmp(a,b) < 0 )
        tp = a, a = b, b = tp, tl = la, la = lb, lb = tl;

    char* c = (char *)malloc( strlen(a) * sizeof(char) );

    int t, cut=0, ib=lb-1, zero=0;
    for (ia = la-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (a[ia]-'0') - (b[ib--]-'0') - cut 
                    : (a[ia]-'0') - cut;
        cut = t < 0 ? 1 : 0;
        c[ia] = t + '0' + cut*10;
        c[ia] == '0' ? zero++ : zero=0;
    }
    //if (zero > 0) c.erase(0, zero);
    return c;
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