//计时测试
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
int main()
{
    cout << "Hello waiter" << endl;
    auto start = chrono::system_clock::now();
    this_thread::sleep_for(0.06s);
    auto end = chrono::system_clock::now();
    chrono::duration<double> diff = end-start;
    cout << "Waited " << diff.count() << " s\n";
}