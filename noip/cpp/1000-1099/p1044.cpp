// P1044 栈
// https://www.luogu.org/problemnew/show/P1044

#include <cstdio>

#define MAX_N 20

int main()
{
    int n, i, j;
    scanf("%d", &n);

    long long dp[MAX_N] = {0};

    // i = 0;
    for (j = 1; j <= n; ++j)
        dp[j] = 1;

    for (i = 1; i < n; ++i)
    {
        dp[0] = dp[1];
        for (j = 1; j <= n - i; ++j)
            dp[j] = dp[j - 1] + dp[j + 1];
    }
    printf("%lld", dp[1]);
    return 0;
}