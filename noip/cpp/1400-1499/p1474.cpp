// P1474 货币系统 Money Systems
// https://www.luogu.org/problemnew/show/P1474

#include <cstdio>

#define MAX_N 26
#define MAX_NUM 10001

int main()
{
    int n, num, i, j;
    scanf("%d %d", &n, &num);

    int a[MAX_N];   // base
    for (i = 0; i < n; ++i)
        scanf("%d", &a[i]);

    long long dp[MAX_NUM] = {0};
    dp[0] = 1;
    for (i = 0; i < n; ++i)
        for (j = a[i]; j <= num; ++j)
            dp[j] = dp[j] + dp[j - a[i]];

    printf("%lld", dp[num]);

    return 0;
}