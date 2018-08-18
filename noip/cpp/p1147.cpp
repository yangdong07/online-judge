// P1147 连续自然数和
// https://www.luogu.org/problemnew/show/P1147

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n, i;

    cin >> n;

    n <<= 1;  // n *= 2
    for (i = (int)sqrt(n); i > 1; --i)
    {
        if (n % i == 0 && (n / i + i) & 1)
            cout << (n / i - i + 1) / 2 << " " << (n / i + i - 1) / 2 << endl;
    }
    return 0;
}