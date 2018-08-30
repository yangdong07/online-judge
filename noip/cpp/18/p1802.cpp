// P1802 5倍经验日
// https://www.luogu.org/problemnew/show/P1802

#include <cstdio>
#include <algorithm>

#define MAX_W 1001   // max weight, knapsack max capacity
#define MAX_N 1001   // max objects

int main()
{
    int n, W;
    scanf("%d %d", &n, &W);

    int v1, v2, w, i, j;
    int vsum = 0;
    long long dp[MAX_W] = {0};
    for (i = 0; i < n; ++i)
    {
        scanf("%d %d %d", &v1, &v2, &w);
        vsum += v1;
        for (j = W; j >= w; --j)
            dp[j] = std::max(dp[j], dp[j - w] + v2 - v1);
    }
    printf("%lld", (dp[W] + vsum) * 5);

    return 0;
}