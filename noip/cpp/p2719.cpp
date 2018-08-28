// P2719 搞笑世界杯
// https://www.luogu.org/problemnew/show/P2719

#include <cstdio>

#define MAX_N 1251

int main()
{
    int n, i, j;
    scanf("%d", &n);
    n >>= 1;
    double dp[MAX_N];

    dp[0] = dp[1] = 0.0; // P(0) = P(B) = 0.0
    for (i = 2; i <= n; ++i)
        dp[i] = 1; // P(BBBB..) = 1

    for (i = 1; i <= n; ++i)
    {
        dp[0] = (i > 1);    // P(AB) = 0.0
        for (j = 1; j <= n; ++j)
            dp[j] = (dp[j - 1] + dp[j]) * 0.5;
    }
    printf("%.4lf", dp[n]);
    return 0;
}