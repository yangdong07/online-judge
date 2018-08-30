// P1634 禽兽的传染病
// https://www.luogu.org/problemnew/show/P1634

#include <iostream>

using namespace std;

int main()
{
    long long x, n, i;
    cin >> x >> n;

    long long sum = 1;

    for (i = 0; i < n; ++i)
        sum += sum * x;

    cout << sum;
}