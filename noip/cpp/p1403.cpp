// P1403 [AHOI2005]约数研究
// https://www.luogu.org/problemnew/show/P1403

#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    // n = 100;
    int sum = 0, i, j;
    for (i = 1; i <= n; i += j)
    {
        j = (n % i) / (n / i) + 1;
        sum += (n / i) * j;
        // printf("%4d/%4d=%4d, %d\n", n, i, n / i, j);
    }
    
    cout << sum;
    return 0;
}