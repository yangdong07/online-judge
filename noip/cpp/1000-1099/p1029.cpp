// P1029 最大公约数和最小公倍数问题
// https://www.luogu.org/problemnew/show/P1029

#include <iostream>
#include <cmath>

using namespace std;

int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main()
{
    int x, y;
    cin >> x >> y;

    if (y % x)
    {
        cout << 0;
        return 0;
    }

    int m = y / x;

    int count = 0;
    for (int i = 1; i < sqrt(m); ++i)
    {
        if (m % i == 0 && gcd(i, m / i) == 1)
            count++;
    }
    cout << count * 2;

}