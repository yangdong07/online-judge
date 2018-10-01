
// P1063 能量项链
// https://www.luogu.org/problemnew/show/P1063

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_N = 100;
    int n, i;
    int a[MAX_N * 2];
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
        a[i + n] = a[i];
    }
    // for (i = 0; i <= n; ++i)
    //     printf("%d ", a[i]);
    // printf("\n");

    int dp[MAX_N * 2][MAX_N] = {0};
    int l, k;
    for (l = 0; l < n; ++l)
        for (i = 0; i < 2 * n - l; ++i)
        {
            for (k = 0; k < l; ++k)
                dp[i][l] = max(dp[i][l],
                               dp[i][k] + dp[i + l + 1][l - k - 1] + a[i] * a[i + k + 1] * a[i + l + 1]);
        }

    int max_dp = 0;
    for (i = 0; i < n; ++i)
        max_dp = max(max_dp, dp[i][n - 1]);

    printf("%d\n", max_dp);

    return 0;
}