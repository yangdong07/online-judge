// P1014 Cantor表
// https://www.luogu.org/problemnew/show/P1014


#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int m = int(ceil(sqrt(2 * n + 0.25) - 0.5));
    int k = m * (m + 1) / 2 - n;
    // printf("%d %d %d\n", n, m, k);

    if (m & 1)
        cout << 1 + k << "/" << m - k << endl;
    else
        cout << m - k << "/" << 1 + k << endl;
}