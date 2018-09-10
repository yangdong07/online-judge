
// P2690 接苹果
// https://www.luogu.org/problemnew/show/P2690

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_W = 30 + 1;
    const int MAX_T = 1000 + 1;
    int T, W, t, w;
    scanf("%d %d", &T, &W);
    int id[MAX_T], dp[MAX_W] = {0};
    for (t = 1; t <= T; ++t)
        scanf("%d", &id[t]);
    for (t = 1; t <= T; ++t)
    {
        for (w = W; w >= 1; --w)
        {
            dp[w] = max(dp[w], dp[w - 1]) + (id[t] == (w % 2 + 1));
        }
        dp[0] += (id[t] == 1);
        // for (w = 0; w <= W; ++w)
        //     printf("%d ", dp[w]);
        // printf("\n");
    }
    int max_dp = 0;
    for (w = 0; w <= W; ++w)
        max_dp = max(max_dp, dp[w]);
    printf("%d", max_dp);
    return 0;
}