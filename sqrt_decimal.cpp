// SQRT - Decimal Solution (Only for Positive Integer Number)
// 523066680/vicyang
// 2019-01

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

string s_mp_single(const string& a, const string& b);
string s_plus(const string& a, const string& b);
string s_minus(const string& a, const string& b);
int s_cmp(const string &a, const string &b );
string sqrt_decimal(const string &num, int precision);

vector<int> vec_mp_single(const vector<int> &a, const vector<int> &b);
vector<int> vec_minus(const vector<int> &a, const vector<int> &b);
string vec2str( const vector<int> &vec );
void check(const vector<int> &va, const vector<int> &vb, const string &op);

int main(int argc, char *argv[] ) 
{
    chrono::duration<double> diff;
    auto stage0 = chrono::system_clock::now();
    sqrt_decimal("2", 10000);
    auto stage1 = chrono::system_clock::now();
    
    diff = stage1-stage0;
    cout << "Time Used: " << diff.count() << " s" << endl;
    return 0;
}

string sqrt_decimal(const string &num, int precision)
{
    int BASE = 10^6;
    static string itoc("0123456789");
    static vector<string> itos{"0","1","2","3","4","5","6","7","8","9"};

    int len = num.length(), mod = len % 2, skip = 2 - mod;
    string target = num.substr(0, skip);
    string tnum = num.substr(skip);

    bool dec_loop = 1;
    int prec = 0, est, mp, mid, cmp, dbmid;
    string base("");

    string s_mp;

    while (dec_loop && prec < precision )
    {
        if ( s_cmp(target, base + "0") < 0 ) {
            mid = 0, est = 0, s_mp = "0";
        } else {
            //评估下一个数字（est）
            if ( base.length() > 5 )
                est = stoi(target.substr(0, 6)) / stoi(base.substr(0, 5));
            else
            {
                est = 9;  // 如果遍历0-9均没有超越target，est取值为9
                for (int i = 0; i <= 9; i++ )
                {
                    mp = stoi(base+itoc[i]) * i;
                    if ( mp > stoi(target) ) { est = i-1; break; }
                }
            }
        }

        //如果估值大于10，考虑取9还是取首位数
        if ( est >= 10 ) 
            est = target.length() > (base.length()+1) ? 9 : est/10;

        mid = est;
        s_mp = s_mp_single( base+itoc[mid], itos[mid] );
        cmp = s_cmp( s_mp, target );

        //如果 最后乘出来的结果大于 target
        if ( cmp > 0 ) {
            //cout << "what?";
            mid -= 1;
            s_mp = s_mp_single( base+itoc[mid], itos[mid] );
        }
        
        cout << mid;
        //printf(" est %d, tg %16s, base, %s, s_mp %s, \n", est, target.c_str(), base.c_str(), s_mp.c_str());

        // 更新 target 值
        target = s_minus(target, s_mp);
        if (tnum.length() == 0 ) {
            //if ( target.compare("00") == 0 ) break;
            if ( target.compare("0") == 0 ) break;
            if ( cmp == 0 ) break;
            target += "00";
            prec += 1;
            if (prec == 1) cout << ".";
        } else {
            if ( target.compare("0") == 0 ) {
                target = tnum.substr(0,2);
                if ( target[0] == '0' ) target.erase(0,1);
            } else {
                target += tnum.substr(0,2);
            }
            tnum = tnum.substr(2);
        }

        //更新 base - 基数
        if ( base.length() == 0 ) {
            base = to_string(mid*2);
        } else {
            // mid*2 有可能是两位数，确保base至少有1位（s_plus假设a长度大于等于b）
            dbmid = mid*2;
            if (dbmid > 9)
                if ( base.back() < '9' )
                    base.back() += 1, base += (dbmid-10)+'0';
                else
                    cerr << "what's wrong with you?" << endl;
            else
                base += dbmid+'0';
        }
        
    }
    cout << endl;
    return "";
}

// vec multiply to one word
vector<int> vec_mp_single(const vector<int> &a, const vector<int> &b)
{
    static int ia; // iter
    const int base = 1000000;
    //如果b是0，直接返回0
    if ( b[0] == 0 ) return vector<int>{0};
    vector<int> c( a.size() );
    int t, pool=0, ib=b.size()-1;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = a[ia] * b[0] + pool;
        c[ia] = t%base, pool = t/base;
    }
    if ( pool > 0 ) c.insert(c.begin(), pool);
    return c;
}

// vec_minus 设 a.len > b.len
vector<int> vec_minus(const vector<int> &a, const vector<int> &b)
{
    register const int* pa = a.data();
    register const int* pb = b.data();
    static int ia; // iter
    const int base = 1000000;
    vector<int> c( a.size() );
    int t, cut=0, ib=b.size()-1, zero=0;
    for (ia = a.size()-1; ia >= 0; ia-- )
    {
        t = ib >= 0 ? (pa[ia]) - (pb[ib--]) + cut
                    : (pa[ia]) + cut;
        t < 0 ? t += base, cut = -1 : cut = 0;
        zero = t == 0 ? zero+1 : 0;  // 此判断须独立，t有可能+base后才为0
        c[ia] = t;
    }
    c.erase(c.begin(), c.begin()+zero);
    return c;
}

string vec2str( const vector<int> &vec )
{
    const int base = 1000000;
    string s("");
    s += to_string( vec[0] );
    for ( int it = 1; it < vec.size(); it++ )
        s += to_string(vec[it]+base).substr(1,6);
    return s;
}

void check(const vector<int> &va, const vector<int> &vb, const string &op)
{
    string a = vec2str(va);
    string b = vec2str(vb);
    string cmd = "perl -Mbignum -e \"print " + a + op + b + "\"";
    system( cmd.c_str() );
    cout << " <- check " << endl;
}

// bignum * single num (str*str)
string s_mp_single(const string& a, const string& b)
{
    static int idx;
    string s;
    //如果b是0，直接返回0
    if ( b[0] == '0' ) return "0";
    if ( b[0] == '1' ) return a;
    s.assign(a.length(), '0');
    int t, pool = 0, numb = b[0]-'0';
    for ( idx = a.length()-1; idx >= 0; idx-- )
    {
        t = (a[idx]-'0') * numb + pool;
        s[idx] = t%10 + '0', pool = t/10;
    }
    if ( pool > 0 ) s.insert(0, 1, pool+'0');
    return s;
}

// 大数减法 字符串操作, 暂时假设 a >= b
string s_minus(const string& a, const string& b)
{
    static int ia;
    if ( a.compare(b) == 0 ) return "0";
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

int s_cmp(const string &a, const string &b )
{
    if ( a.length() > b.length() ) return 1;
    else if ( a.length() < b.length() ) return -1;
    else return a.compare(b);
}
