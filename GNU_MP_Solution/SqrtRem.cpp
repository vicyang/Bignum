// Algorithm 1.12 SqrtRem
// C++ Version by vicyang/523066680
// 2019-01

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <chrono>
using namespace std;

struct SR { int s, r; };

struct SR BasecaseSqrtRem( int u )
{
    struct SR sr = {0, -1};
    int square, min = 0, max = u/2+1, mid;

    while ( max - min > 1 )
    {
        mid = (min+max)/2, square = mid*mid;
        printf("square %d, mid %d, min %d, max %d \n", square, mid, min, max);
        // square > u ? ( max = mid ) :
        // square < u ? ( min = mid ) :
        //              (sr.s = mid, sr.r = 0, max = min);
        if (square > u )     { max = mid; }
        else if (square < u) { min = mid; }
        else                 { sr.s = mid, sr.r = 0; break; }
    }

    if ( sr.r == -1 ) sr.s = mid-1, sr.r = u - sr.s*sr.s;
    return sr;
}

int main(int argc, char *argv[] ) 
{
    auto start = chrono::system_clock::now();

    struct SR sr;
    for (int i = 1; i < 81; i++)
    {
        cout << "test number: " << i << endl;
        sr = BasecaseSqrtRem( i );
        cout << "s: " << sr.s << ", r: " << sr.r << endl << endl;
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double> diff = end-start;

    cout << "Time Used: " << diff.count() << " s" << endl;
    return 0;
}

