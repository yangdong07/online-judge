// P1887 乘积最大3
// https://www.luogu.org/problemnew/show/P1887

#include <iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    int x = n / m;
    int r = n % m;
    int i;

    for (i = 0; i < m - r; ++i)
        cout << x << " ";
    for (; i < m; ++i)
        cout << x + 1 << " ";

}