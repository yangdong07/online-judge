// P1754 球迷购票问题
// https://www.luogu.org/problemnew/show/P1754

#include <cstdio>

#define MAX_N 21

int main()
{
    int n, i, j;
    scanf("%d", &n);

    long long dp[MAX_N] = {0};
    dp[0] = 1;
    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= i; ++j)
            dp[j] = dp[j] + dp[j - 1];
        // for (j = 1; j <= i; ++j)
        //     printf("%lld ", dp[j]);
        // printf("\n");
    }

    printf("%lld", dp[n]);

    return 0;
}