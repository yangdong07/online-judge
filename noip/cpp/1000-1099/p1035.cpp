// P1035 级数求和
// https://www.luogu.org/problemnew/show/P1035

#include <iostream>
#include <cstdio>
#include <cstdio>
#include <

using namespace std;

int main()
{
    int k, n = 1;
    double s = 1.0;

    cin >> k;

    while (s <= k)
    {
        s += 1.0 / ++n;
    }
    cout << n;
}
