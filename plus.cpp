#include <iostream>
using namespace std;

int main(int argc, char *argv[] ) 
{
    string a="99999999999999";
    string b="123456789"; 
    string c;
    for (int i=0; i<a.length(); i++ )
    {
        cout << a[i] <<" ";
    }
    cout<<a<<endl;
    return 0;
}
