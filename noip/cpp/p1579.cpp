// P1579 哥德巴赫猜想（升级版）
// https://www.luogu.org/problemnew/show/P1579

#include <iostream>
#include <cstring>

using namespace std;

#define MAX_N 20001

bool is_prime[MAX_N] = { true };

void sieve(int n)
{
    memset(is_prime, true, sizeof(is_prime));
    for (int i = 2; i <= n; ++i)
        if (is_prime[i])
            for (int j = i + i; j <= n; j += i)
                is_prime[j] = false;
}

int main()
{
    int n;
    cin >> n;

    sieve(n);

    int i, j;

    for (i = 2; i < n; ++i)
        if (is_prime[i])
            for (j = i; j < n; ++j)
            {
                if (is_prime[j] && (i + j <= n - 2) && (is_prime[n - i - j]))
                {
                    cout << i << " " << j << " " << n - i - j << endl;
                    return 0;
                }
            }
}