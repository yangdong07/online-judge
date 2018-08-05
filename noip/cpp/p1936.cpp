// P1936 水晶灯火灵
// https://www.luogu.org/problemnew/show/P1936

#include <iostream>

using namespace std;

int main()
{
    int k;
    cin >> k;

    int m, n, t;
    for (m = n = 1; m + n <= k;)
    {
        t = m + n;
        m = n;
        n = t;
    }
    cout << "m=" << m << endl;
    cout << "n=" << n << endl;
}