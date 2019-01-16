#include <iostream>
using namespace std;

int main(int argc, char *argv[] ) 
{
    string a="9876543210123456";
    string b="123456789";
    string c( a.length()+1, '0');

    int len_a = a.length(), len_b = b.length();
    int t, pool;

    for (int iter = 0; iter < len_b; iter++ )
    {
        cout << b[len_b-iter-1] << a[len_a-iter-1] <<endl;
        t = a.tointeger();
    }
    //cout<<c<<endl;
    return 0;
}
