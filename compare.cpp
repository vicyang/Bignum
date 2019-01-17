#include <iostream>
using namespace std;

int s_cmp( string &a, string &b );

int main(int argc, char *argv[] ) 
{
    string a("4");
    string b("121231312");

    int cmp = a.compare(b);
    cout << cmp << endl;

    cmp = s_cmp(a, b);
    cout << cmp << endl;

    return 0;
}

int s_cmp( string &a, string &b )
{
    if ( a.length() > b.length() ) return 1;
    else if ( a.length() < b.length() ) return -1;
    else return a.compare(b);
}
