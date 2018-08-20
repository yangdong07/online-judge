// P1616 疯狂的采药
// https://www.luogu.org/problemnew/show/P1616

#include <cstdio>

#define MAX_W 100001
#define MAX_N 10001
#define max(a, b) (a) > (b) ? (a) : (b)

int main()
{
    int W, n, w[MAX_N], v[MAX_N];
    int i, j;
    scanf("%d %d", &W, &n);
    for (j = 0; j < n; ++j)
        scanf("%d %d", &w[j], &v[j]);

    int dp[MAX_W] = {0};
    for (j = 0; j < n; ++j)
        for (i = w[j]; i <= W; ++i)
            dp[i] = max(dp[i], dp[i - w[j]] + v[j]);
    // for (i = 1; i <= W; ++i)
    //     for (j = 0; j < n; ++j)
    //         if (w[j] <= i)
    //             dp[i] = max(dp[i], dp[i - w[j]] + v[j]);
    printf("%d", dp[W]);

    return 0;
}