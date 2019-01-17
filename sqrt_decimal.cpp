// SQRT - Decimal Solution (Only for Positive Integer Number)
// 523066680/vicyang
// 2019-01

#include <iostream>
#include <chrono>
using namespace std;

string s_mp_single(const string& a, const string& b);
string s_plus(const string& a, const string& b);
string s_minus(string a, string b);
int s_cmp(const string &a, const string &b );
void check(string a, string b);

int main(int argc, char *argv[] ) 
{
    auto start = chrono::system_clock::now();
    string num("29");
    int len = num.length(), mod = len % 2, skip = 2 - mod;
    string target = num.substr(0, skip);
    string tnum = num.substr( skip );
    
    cout << target;
    int mid, mp, mplen, est, cmp;
    string s_mp;
    string base("");

    // dec loop
    bool decloop = 1, estloop = 1;
    int prec = 0,  base_len = 0, target_len = skip;

    while ( decloop == 1 )
    {   
        //estimate
        while ( estloop == 1 )
        {
            if ( s_cmp(target, base + "0") < 0 ) {
                mid = 0, mp = 0, mplen = 0;
                estloop = 0;
                break;
            }

            if (base_len > 5) 
                est = stoi(target.substr(0, 6)) / stoi(base.substr(0, 5));
            else
            {
                for (int i=0; i < 10; i++)
                {
                    mp = (stoi(base + to_string(i) )) * i;
                    if ( mp > stoi(target) ) {
                        est = i-1;
                        break;
                    }
                }
            }

            if ( est >= 10 ) {
                if (target.length() > base.length() +1) est = 9;
            }

            mid = est;
            s_mp = s_mp_single( base + to_string(mid), to_string(mid) );
            cmp = s_cmp( s_mp, target );

            if ( cmp > 0 ) {
                cout << "what?";
                mid -= 1;
                s_mp = s_mp_single( base + to_string(mid), to_string(mid) );
            }

            break;
        }

        cout << mid;

        target = s_minus(target, s_mp);
        if ( skip > len )
        {
            target += "00";
            prec += 1;
            if (prec == 1) cout << ".";
        }
        else 
        {
            if ( s_cmp( target, "0" ) == 0 ) {
                target = tnum.substr(0,2);
            } else {
                target += tnum.substr(0,2);
            }
            skip+=2;
        }
        target_len+=2;

        if ( s_cmp(base, "0") == 0 ) {
            base = to_string(mid*2), base_len = mid*2 >= 10 ? 2 : 1;
        } else {
            base = s_plus( base + "0", to_string(mid*2) );
            base_len = base.length();
        }


        //break;
    }

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


int s_cmp(const string &a, const string &b )
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