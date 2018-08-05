// P2043 质因子分解
// https://www.luogu.org/problemnew/show/P2043

#include <iostream>
#include <cstring>

using namespace std;

#define MAX_N 10001

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

    int t, count;
    for (int i = 2; i <= n; ++i)
        if (is_prime[i])
        {
            for (t = n, count = 0; t; t /= i)
                count += t / i;
            cout << i << " " << count << endl;
        }
}