// P1832 A+B Problem（再升级）
// https://www.luogu.org/problemnew/show/P1832

#include <cstdio>

#define MAX_N 1001

bool is_prime(int n)
{
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

int main()
{
    int n, i, j;
    long long dp[MAX_N] = {0};

    scanf("%d", &n);

    dp[0] = 1;

    // for (j = 0; j <= n; ++j)
    //     printf("%d ", j);
    // printf("\n");

    for (i = 2; i <= n; ++i)
        if (is_prime(i))
        {
            for (j = i; j <= n; ++j)
                dp[j] += dp[j - i];
            // for (j = 0; j <= n; ++j)
            //     printf("%lld ", dp[j]);
            // printf("\n");
        }
    printf("%lld", dp[n]);

    return 0;
}